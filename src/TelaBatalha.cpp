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

TelaBatalha::TelaBatalha(Jogo* jogo): jogo(jogo){
    srand(static_cast<unsigned>(time(0))); // Inicializa o gerador de numeros aleatorios
    jogador = Personagem::getInstance(); // Obtém a instância do jogador
    inicializarMonstro(); // Inicializa o monstro

	jogadorDefendendo = false; // Inicializa o estado de defesa do jogador
	monstroDefendendo = false; // Inicializa o estado de defesa do monstro
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

    if (monstroDefendendo == true) {
        dano = static_cast<int>(dano * 2.0 / 3.0); // Reduz para dois terços
    }

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
	jogadorDefendendo = true; // O jogador está se defendendo

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

	if (jogo->getFaseAtual() == 7) {
		cout << "Voce nao pode fugir desta batalha!" << endl;
		cout << "Pressione Enter para continuar..." << endl;
		cin.get();
		return false;
	}
	else if (jogo->getFaseAtual() == 3) {
		cout << "Os lobos te cercaram, voce nao pode fugir desta batalha!" << endl;
		cout << "Pressione Enter para continuar..." << endl;
		cin.get();
		return false;
	}

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

        // Reduz o dano se o jogador estiver defendendo
        if (jogadorDefendendo == true) {
            dano = static_cast<int>(dano * 2.0 / 3.0); // Reduz para dois terços
        }

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
		monstroDefendendo = true; // O monstro está se defendendo
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
       
        string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Batalha_Vitoria.txt");
        cout << conteudo << endl;
        cin.get();
        
        // Monstro derrotado: Drop de itens
        int ouroDropado = rand() % 50 + 10; // Ouro aleatorio entre 10 e 50

        // Adicionar itens ao jogador
        jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() + ouroDropado);
        
        // Determinar se o jogador receberá um item (66% de chance)
        int chanceDrop = rand() % 100; // Gera um número entre 0 e 99
        if (chanceDrop < 66) { // 66% de chance
            Provisao* frascoEnergia = new Provisao("Frasco de Energia", "Recupera parte da sua energia", 0, int(jogador->getMaxEnergia() / 2));
            jogador->adicionarProvisao(frascoEnergia);

            // Mensagem de drop do item
            cout << "Você recebeu uma " << frascoEnergia->getNome() << "!" << endl;
        }

        // Mensagens de drop
        cout << "Voce recebeu " << ouroDropado << " moedas de ouro!" << endl;
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

        if (jogo->getFaseAtual() == 7) {
            jogo->setDiretorioAtual("torre");
            jogo->setFaseAtual(8); // Fase 8 é o texto de derrota
            jogo->mudarEstado(new TelaPadrao(jogo));
            return;
        }

        // Excluir o save do jogador
        jogo->excluirSave();
        jogo->mudarEstado(new TelaInicial(jogo));
        jogador->releaseInstance();
        
        return;
    }
}

void TelaBatalha::inicializarMonstro() {
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

    // Processar o destino
    size_t separadorDestino = destinoParte.find(':');
    if (separadorDestino == string::npos) {
        cerr << "Erro: Formato do destino inválido!" << endl;
        exit(1);
    }
    
    // Extrair o diretório e a fase de destino
    this->diretorioDestino = destinoParte.substr(0, separadorDestino);
    this->faseDestino = stoi(destinoParte.substr(separadorDestino + 1));

    // Se o monstro já estiver inicializado, não faça nada
    if (Monstro::getInstance()->getNome()!="") { // Sei que não é a melhor forma de verificar, mas é a única que funciona
        this->monstro = Monstro::getInstance();
        return;
    }
    
    // Processar a configuração do monstro
    size_t separadorMonstro = configMonstroParte.find(':');
    if (separadorMonstro == string::npos || configMonstroParte.substr(0, separadorMonstro) != "m") {
        cerr << "Erro: Formato da configuração do monstro inválido!" << endl;
        exit(1);
    }
    
    // Extrair os dados do monstro
    string dadosMonstro = configMonstroParte.substr(separadorMonstro + 1);
    
    // Contar número de vírgulas para determinar o tamanho do vetor
    int contVirgulas = 0;
    for (size_t i = 0; i < dadosMonstro.length(); i++) {
        if (dadosMonstro[i] == ',') {
            contVirgulas++;
        }
    }
    
    // Alocar memória dinamicamente para o vetor de dados
    int tamanhoVetor = contVirgulas + 1;
    string* dadosArray = new string[tamanhoVetor];
    
    // Separar os dados do monstro por vírgulas
    size_t pos = 0;
    string token;
    int index = 0;
    
    while ((pos = dadosMonstro.find(',')) != string::npos && index < tamanhoVetor) {
        token = dadosMonstro.substr(0, pos);
        dadosArray[index++] = token;
        dadosMonstro.erase(0, pos + 1);
    }
    
    // Adicionar o último valor
    if (index < tamanhoVetor) {
        dadosArray[index] = dadosMonstro;
    }
    
    // Verificar se temos todos os dados necessários (nome, energia, habilidade, resistência)
    if (tamanhoVetor < 4) {
        cerr << "Erro: Dados do monstro incompletos!" << endl;
        delete[] dadosArray; // Liberar a memória antes de sair
        exit(1);
    }
    
    // Extrair os dados do monstro
    string nomeMonstro = dadosArray[0];
    int energiaMonstro = stoi(dadosArray[1]);
    int habilidadeMonstro = stoi(dadosArray[2]);
    int resistenciaMonstro = stoi(dadosArray[3]);
    
    // Liberar a memória alocada
    delete[] dadosArray;
    
    // Criar o monstro usando o padrão Singleton
    this->monstro = Monstro::getInstance(nomeMonstro, energiaMonstro, habilidadeMonstro, resistenciaMonstro);
}