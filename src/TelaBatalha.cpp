#include "../include/TelaBatalha.h"
#include "../include/TelaInventario.h"
#include "../include/TelaPadrao.h"
#include "../include/TelaInicial.h"
#include "../include/ArquivoManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

TelaBatalha::TelaBatalha(Jogo* jogo): jogo(jogo) {
    srand(static_cast<unsigned>(time(0))); // Inicializa o gerador de numeros aleatorios
    jogador = Personagem::getInstance(); // Obtém a instância do jogador
    inicializarMonstro(); // Inicializa o monstro
}

TelaBatalha::~TelaBatalha() {}

void TelaBatalha::exibirTela() {
    jogo->limparTela();

    // Exibir a tela de batalha
    cout << "========================" << endl;
    cout << "       BATALHA " << endl;
    cout << "========================" << endl;
    cout << endl;
    cout << "Inimigo: " << monstro->getNome() << endl;
    cout << "Energia (HP): " << monstro->getEnergia() << endl;
    cout << "Habilidade: " << monstro->getHabilidade() << endl;
    cout << "Resistencia: " << monstro->getResistencia() << endl;
    cout << endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Sua Energia: " << jogador->getEnergiaAtual() << "/" << jogador->getMaxEnergia() << endl;
    cout << "Sua Habilidade: " << jogador->getHabilidade() << endl;
    cout << "Sua Resistencia: " << jogador->getResistencia() << endl;
    cout << "Sua Sorte: " << jogador->getSorte() << endl;
    cout << endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Escolha sua acao:" << endl;
    cout << endl;
    cout << "[1] Atacar" << endl;
    cout << "[2] Inventario" << endl;
    cout << "[3] Defender" << endl;
    cout << "[4] Fugir" << endl;
    cout << endl;
    cout << "========================" << endl;
    cout << "Digite o numero da opcao desejada: ";

    int opcao;
    cin >> opcao;
    cin.ignore(); // Adicionar esta linha para limpar o buffer
    handleInput(opcao);
}

void TelaBatalha::handleInput(unsigned int input) {
    
    Personagem* jogador = Personagem::getInstance();
    bool fugiu = false;

    switch (input) {
    case 1:
        atacar();
        break;
    case 2:
        acessarInventario();
        return; // Retorna para a tela de batalha após acessar o inventário
    case 3:
        defender();
        break;
    case 4:
        fugiu = tentarFugir();
        if (fugiu) {
            return; // O uso do return aqui é para evitar que a ação do monstro ocorra após a fuga
        }
        break;
    default:
        cout << "Opcao invalida!" << endl;
        break;
    }

    if (monstro->getEnergia() > 0 && jogador->getEnergiaAtual() > 0) {
        acaoMonstro();
    }
    else {
        finalizarBatalha();
    }
}

void TelaBatalha::atacar() {
    Personagem* jogador = Personagem::getInstance();

    int habilidadeJogador = jogador->getHabilidade();
    // removi o bonus arma, pois já é somado quando equipamos ela
    int resistenciaMonstro = monstro->getResistencia();

    int dano = habilidadeJogador - resistenciaMonstro;
    if (dano < 0) dano = 0;

    // Para debug:
    dano = 9999; // Dano máximo para teste (remover depois)

    monstro->setEnergia(monstro->getEnergia() - dano);

    jogo->limparTela();
    cout << "Voce atacou o " << monstro->getNome() << " causando " << dano << " de dano!" << endl;
    if (monstro->getEnergia() <= 0) {
        cout << "Parabens! Voce derrotou o " << monstro->getNome() << "!" << endl;
    }
    cout << "Pressione Enter para continuar..." << endl;
    cin.get();
}

void TelaBatalha::defender() {
    Personagem* jogador = Personagem::getInstance();
    jogador->setResistencia(jogador->getResistencia() + 5);
    jogo->limparTela();
    cout << "Voce se defendeu! Sua resistencia aumentou temporariamente." << endl;
    cout << "Pressione Enter para continuar..." << endl;
    cin.get();
}

void TelaBatalha::acessarInventario() {
    jogo->mudarEstado(new TelaInventario(jogo));
}

bool TelaBatalha::tentarFugir() {
    // Limpar a tela
    jogo->limparTela();

    Personagem* jogador = Personagem::getInstance();

    int sorteJogador = jogador->getSorte();

    // Calcular a chance de fuga com base na SORTE
    int chanceFuga = sorteJogador * 2;
    if (chanceFuga > 90) {
        chanceFuga = 90; // Limita a chance maxima de fuga a 90%
    }

    // Gerar um numero aleatorio entre 0 e 99
    int chance = rand() % 100;

    // Verificar se o jogador conseguiu fugir
    if (chance < chanceFuga) {
        cout << "Voce conseguiu fugir da batalha!" << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();
        
        // Liberar a instância do monstro quando o jogador foge com sucesso
        Monstro::releaseInstance();
        
        jogo->setDiretorioAtual(diretorioDestino);
        jogo->setFaseAtual(faseDestino);
        jogo->mudarEstado(new TelaPadrao(jogo));
        return true;
    }
    else {
        cout << "Voce falhou em fugir!" << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();
        return false;
    }
}

void TelaBatalha::acaoMonstro() {
    jogo->limparTela();

    int acao = rand() % 2;

    if (acao == 0) {
        Personagem* jogador = Personagem::getInstance();

        int habilidadeMonstro = monstro->getHabilidade();
        int resistenciaJogador = jogador->getResistencia();
        int bonusArmadura = jogador->getArmadura() ? jogador->getArmadura()->getBuffResistencia() : 0;

        int dano = habilidadeMonstro - resistenciaJogador; // removi tambem o bonus da armadura
        if (dano < 0) dano = 0;

        jogador->setEnergiaAtual(jogador->getEnergiaAtual() - dano);

        cout << monstro->getNome() << " atacou voce causando " << dano << " de dano!" << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();

        if (jogador->getEnergiaAtual() <= 0) {
            cout << "Voce foi derrotado pelo " << monstro->getNome() << "!" << endl;
            finalizarBatalha();
        }
    }
    else {
        monstro->setResistencia(monstro->getResistencia() + 3);
        cout << monstro->getNome() << " se defendeu! Sua resistencia aumentou temporariamente." << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();
    }
}

void TelaBatalha::finalizarBatalha() {
    jogo->limparTela();

    Personagem* jogador = Personagem::getInstance();
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();

    if (monstro->getEnergia() <= 0) {
        // Monstro derrotado: Drop de itens
        int ouroDropado = rand() % 50 + 10; // Ouro aleatorio entre 10 e 50

        // Criar o frasco de energia (pocao de vida)
        Provisao* frascoEnergia = new Provisao("Frasco de Energia", "Restaura 20 pontos de energia", 0, 20);

        // Adicionar itens ao jogador
        jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() + ouroDropado);
        jogador->adicionarProvisao(frascoEnergia);

        string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Batalha_Vitoria.txt");
        cout << conteudo << endl;
        cin.get();

        // Mensagens de drop
        jogo->limparTela();
        cout << "Voce recebeu " << ouroDropado << " moedas de ouro!" << endl;
        cout << "Voce recebeu um " << frascoEnergia->getNome() << "!" << endl;
        cout << "\nPressione Enter para continuar..." << endl;
        cin.get();

        // Liberar a instância do monstro
        Monstro::releaseInstance();

        // Atualizar o estado do jogo
        jogo->setDiretorioAtual(diretorioDestino);
        jogo->setFaseAtual(faseDestino);
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
    else if (jogador->getEnergiaAtual() <= 0) {
        string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Batalha_Derrota.txt");
        cout << conteudo << endl;
        cin.get();

        // Liberar a instância do monstro
        Monstro::releaseInstance();

        jogo->mudarEstado(new TelaInicial(jogo));
        return;
    }
}

void TelaBatalha::inicializarMonstro() {
    // exemplo de configMonstro: "m:Rato Gigante,20,4,5;caverna:4" m:Nome,Energia,Habilidade,Resistencia;diretorioDestino:faseDestino
    // sempre deixe na primeira linha, com o mostro e destino separados por ";"
    // e as configurações do monstro separadas por ","

    // Ler a configuração do monstro
    string caminhoAtual = "Arquivos.txt/" + jogo->getDiretorioAtual() + "/" + jogo->getDiretorioAtual() + "_" + to_string(jogo->getFaseAtual()) + ".txt";
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string configMonstro = arquivoManager->lerOpcoesHistoria(caminhoAtual);

    // Verificar se a string de configuração não está vazia
    if (configMonstro.empty()) {
        cerr << "Erro: Configuração do monstro vazia!" << endl;
        exit(1);
    }
    
    // Separar a configuração do monstro e o destino
    size_t separadorPrincipal = configMonstro.find(';');
    if (separadorPrincipal == string::npos) {
        cerr << "Erro: Formato da configuração inválido!" << endl;
        exit(1);
    }
    
    // Parte da configuração do monstro
    string configMonstroParte = configMonstro.substr(0, separadorPrincipal);
    
    // Parte do destino
    string destinoParte = configMonstro.substr(separadorPrincipal + 1);
    
    // Processar a configuração do monstro
    size_t separadorMonstro = configMonstroParte.find(':');
    if (separadorMonstro == string::npos || configMonstroParte.substr(0, separadorMonstro) != "m") {
        cerr << "Erro: Formato da configuração do monstro inválido!" << endl;
        exit(1);
    }
    
    // Extrair os dados do monstro (Rato Gigante,50,10,15)
    string dadosMonstro = configMonstroParte.substr(separadorMonstro + 1);
    
    // Separar os dados do monstro por vírgulas
    vector<string> dadosArray;
    size_t pos = 0;
    string token;
    while ((pos = dadosMonstro.find(',')) != string::npos) {
        token = dadosMonstro.substr(0, pos);
        dadosArray.push_back(token);
        dadosMonstro.erase(0, pos + 1);
    }
    dadosArray.push_back(dadosMonstro); // Adicionar o último valor
    
    // Verificar se temos todos os dados necessários (nome, energia, habilidade, resistência)
    if (dadosArray.size() < 4) {
        cerr << "Erro: Dados do monstro incompletos!" << endl;
        exit(1);
    }
    
    // Extrair os dados do monstro
    string nomeMonstro = dadosArray[0];
    int energiaMonstro = stoi(dadosArray[1]);
    int habilidadeMonstro = stoi(dadosArray[2]);
    int resistenciaMonstro = stoi(dadosArray[3]);
    
    // Criar o monstro usando o padrão Singleton
    this->monstro = Monstro::getInstance(nomeMonstro, energiaMonstro, habilidadeMonstro, resistenciaMonstro);
    
    // Processar o destino
    size_t separadorDestino = destinoParte.find(':');
    if (separadorDestino == string::npos) {
        cerr << "Erro: Formato do destino inválido!" << endl;
        exit(1);
    }
    
    // Extrair o diretório e a fase de destino
    this->diretorioDestino = destinoParte.substr(0, separadorDestino);
    this->faseDestino = stoi(destinoParte.substr(separadorDestino + 1));
}