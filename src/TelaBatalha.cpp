#include "../include/TelaBatalha.h"
#include "../include/TelaInventario.h"
#include "../include/TelaPadrao.h"
#include "../include/ArquivoManager.h"
#include "../include/Personagem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

TelaBatalha::TelaBatalha(Jogo* jogo, Monstro* monstro, const string& diretorioDestino, const string& diretorioBatalhaAtual)
    : jogo(jogo), monstro(monstro), diretorioDestino(diretorioDestino), diretorioBatalhaAtual(diretorioBatalhaAtual), fugaFalhou(false) {
    srand(static_cast<unsigned>(time(0))); // Inicializa o gerador de numeros aleatorios
}


TelaBatalha::~TelaBatalha() {}

void TelaBatalha::exibirTela() {
    jogo->limparTela();
    cout << "Exibindo a tela de batalha..." << endl;
    // Obter o personagem principal
    Personagem* jogador = Personagem::getInstance();

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(diretorioBatalhaAtual);

    cout << "========================" << endl;
    cout << "       BATALHA " << endl;
    cout << "========================" << endl;
    cout << endl;
    cout << "Inimigo: " << monstro->getNome() << endl;
    cout << "Energia (HP): " << monstro->getEnergia() << endl;
    cout << endl;
    cout << "------------------------" << endl;
    cout << endl;
    cout << "Sua Energia: " << jogador->getHabilidade() << endl;
    cout << "Sua Habilidade: " << jogador->getEnergiaAtual() << endl;
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
    handleInput(opcao);
}

void TelaBatalha::handleInput(unsigned int input) {
    
    Personagem* jogador = Personagem::getInstance();

    switch (input) {
    case 1:
        atacar();
        break;
    case 2:
        acessarInventario();
        break;
    case 3:
        defender();
        break;
    case 4:
        tentarFugir();
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

    monstro->setEnergia(monstro->getEnergia() - dano);

    cout << "Voce atacou o " << monstro->getNome() << " causando " << dano << " de dano!" << endl;

    if (monstro->getEnergia() <= 0) {
        cout << "Voce derrotou o " << monstro->getNome() << "!" << endl;
    }
}

void TelaBatalha::defender() {
    Personagem* jogador = Personagem::getInstance();
    jogador->setResistencia(jogador->getResistencia() + 5);

    cout << "Voce se defendeu! Sua resistencia aumentou temporariamente." << endl;
}

void TelaBatalha::acessarInventario() {
    jogo->mudarEstado(new TelaInventario(jogo));
}

void TelaBatalha::tentarFugir() {
    // Verificar se a fuga ja falhou anteriormente
    if (fugaFalhou) {
        cout << "Voce ja tentou fugir e falhou! Nao pode mais tentar fugir desta batalha." << endl;
        return;
    }

    Personagem* jogador = Personagem::getInstance();

    int sorteJogador = jogador->getSorte();

    // Calcular a chance de fuga com base na SORTE
    int chanceFuga = sorteJogador * 2;
    if (chanceFuga > 90) {
        chanceFuga = 90; // Limita a chance m�xima de fuga a 90%
    }

    // Gerar um n�mero aleat�rio entre 0 e 99
    int chance = rand() % 100;

    // Verificar se o jogador conseguiu fugir
    if (chance < chanceFuga) {
        cout << "Voce conseguiu fugir da batalha!" << endl;
        jogo->setDiretorioAtual(diretorioDestino);
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
    else {
        cout << "Voce falhou em fugir!" << endl;
        fugaFalhou = true; // Marcar que a fuga falhou
    }
}
void TelaBatalha::acaoMonstro() {
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

        if (jogador->getEnergiaAtual() <= 0) {
            cout << "Voce foi derrotado pelo " << monstro->getNome() << "!" << endl;
        }
    }
    else {
        monstro->setResistencia(monstro->getResistencia() + 3);
        cout << monstro->getNome() << " se defendeu! Sua resistencia aumentou temporariamente." << endl;
    }
}

void TelaBatalha::finalizarBatalha() {

    Personagem* jogador = Personagem::getInstance();

    if (monstro->getEnergia() <= 0) {
        // Monstro derrotado: Drop de itens
        int ouroDropado = rand() % 50 + 10; // Ouro aleatorio entre 10 e 50

        // Criar o frasco de energia (pocao de vida)
        Provisao* frascoEnergia = new Provisao("Frasco de Energia", "Restaura 20 pontos de energia", 0, 20);

        // Adicionar itens ao jogador
        jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() + ouroDropado);
        jogador->adicionarProvisao(frascoEnergia);

        // Mensagens de drop
        cout << "Voce derrotou o " << monstro->getNome() << "!" << endl;
        cout << "Voce recebeu " << ouroDropado << " moedas de ouro!" << endl;
        cout << "Voce recebeu um " << frascoEnergia->getNome() << "!" << endl;

        // Atualizar o estado do jogo
        jogo->setDiretorioAtual(diretorioDestino);
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
    else if (jogador->getEnergiaAtual() <= 0) {
        jogo->setDiretorioAtual("Arquivos.txt/Batalha_Derrota.txt"); //Implementar GAME OVER
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
}