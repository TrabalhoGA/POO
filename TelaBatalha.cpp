#include "C:/Users/user/source/repos/POO/include/TelaBatalha.h"   // Só funcionou assim
#include "C:/Users/user/source/repos/POO/include/TelaInventario.h"
#include "C:/Users/user/source/repos/POO/include/TelaPadrao.h"
#include "C:/Users/user/source/repos/POO/include/ArquivoManager.h"
#include "C:/Users/user/source/repos/POO/include/Personagem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

TelaBatalha::TelaBatalha(Jogo* jogo, Monstro* monstro, const string& diretorioDestino, const string& diretorioBatalhaAtual)
    : jogo(jogo), monstro(monstro), diretorioDestino(diretorioDestino), diretorioBatalhaAtual(diretorioBatalhaAtual), fugaFalhou(false) {
    srand(static_cast<unsigned>(time(0))); // Inicializa o gerador de números aleatórios
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
    cout << "Escolha sua ação:" << endl;
    cout << endl;
    cout << "[1] Atacar" << endl;
    cout << "[2] Inventário" << endl;
    cout << "[3] Defender" << endl;
    cout << "[4] Fugir" << endl;
    cout << endl;
    cout << "========================" << endl;
    cout << "Digite o número da opção desejada: ";
}

void TelaBatalha::handleInput(int input) {
    
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
        cout << "Opção inválida!" << endl;
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
    int bonusArma = jogador->getArma() ? jogador->getArma()->getBuffHabilidade() : 0;
    int resistenciaMonstro = monstro->getResistencia();

    int dano = (habilidadeJogador + bonusArma) - resistenciaMonstro;
    if (dano < 0) dano = 0;

    monstro->setEnergia(monstro->getEnergia() - dano);

    cout << "Você atacou o " << monstro->getNome() << " causando " << dano << " de dano!" << endl;

    if (monstro->getEnergia() <= 0) {
        cout << "Você derrotou o " << monstro->getNome() << "!" << endl;
    }
}

void TelaBatalha::defender() {
    Personagem* jogador = Personagem::getInstance();
    jogador->setResistencia(jogador->getResistencia() + 5);

    cout << "Você se defendeu! Sua resistência aumentou temporariamente." << endl;
}

void TelaBatalha::acessarInventario() {
    jogo->mudarEstado(new TelaInventario(jogo));
}

void TelaBatalha::tentarFugir() {
    // Verificar se a fuga já falhou anteriormente
    if (fugaFalhou) {
        cout << "Você já tentou fugir e falhou! Não pode mais tentar fugir desta batalha." << endl;
        return;
    }

    Personagem* jogador = Personagem::getInstance();

    int sorteJogador = jogador->getSorte();

    // Calcular a chance de fuga com base na SORTE
    int chanceFuga = sorteJogador * 2;
    if (chanceFuga > 90) {
        chanceFuga = 90; // Limita a chance máxima de fuga a 90%
    }

    // Gerar um número aleatório entre 0 e 99
    int chance = rand() % 100;

    // Verificar se o jogador conseguiu fugir
    if (chance < chanceFuga) {
        cout << "Você conseguiu fugir da batalha!" << endl;
        jogo->setDiretorioAtual(diretorioDestino);
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
    else {
        cout << "Você falhou em fugir!" << endl;
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

        int dano = habilidadeMonstro - (resistenciaJogador + bonusArmadura);
        if (dano < 0) dano = 0;

        jogador->setEnergiaAtual(jogador->getEnergiaAtual() - dano);

        cout << monstro->getNome() << " atacou você causando " << dano << " de dano!" << endl;

        if (jogador->getEnergiaAtual() <= 0) {
            cout << "Você foi derrotado pelo " << monstro->getNome() << "!" << endl;
        }
    }
    else {
        monstro->setResistencia(monstro->getResistencia() + 3);
        cout << monstro->getNome() << " se defendeu! Sua resistência aumentou temporariamente." << endl;
    }
}

void TelaBatalha::finalizarBatalha() {

    Personagem* jogador = Personagem::getInstance();

    if (monstro->getEnergia() <= 0) {
        // Monstro derrotado: Drop de itens
        int ouroDropado = rand() % 50 + 10; // Ouro aleatório entre 10 e 50

        // Criar o frasco de energia (poção de vida)
        Provisao* frascoEnergia = new Provisao("Frasco de Energia", "Restaura 20 pontos de energia", 0, 20);

        // Adicionar itens ao jogador
        jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() + ouroDropado);
        jogador->adicionarProvisao(frascoEnergia);

        // Mensagens de drop
        cout << "Você derrotou o " << monstro->getNome() << "!" << endl;
        cout << "Você recebeu " << ouroDropado << " moedas de ouro!" << endl;
        cout << "Você recebeu um " << frascoEnergia->getNome() << "!" << endl;

        // Atualizar o estado do jogo
        jogo->setDiretorioAtual(diretorioDestino);
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
    else if (jogador->getEnergiaAtual() <= 0) {
        jogo->setDiretorioAtual("Arquivos.txt/Batalha_Derrota.txt"); //Implementar GAME OVER
        jogo->mudarEstado(new TelaPadrao(jogo));
    }
}