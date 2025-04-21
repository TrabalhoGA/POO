#include "include/TelaInventario.h"
#include "include/Personagem.h"
#include <iostream>
#include <iomanip>

using namespace std;

TelaInventario::TelaInventario(Jogo* jogo) : jogo(jogo) {
    // Construtor
}

TelaInventario::~TelaInventario() {
    // Destrutor
}

void TelaInventario::exibirTela() {
    jogo->limparTela();

    // Obter o personagem principal
    Personagem* jogador = Personagem::getInstance();

    // Exibir cabeçalho
    cout << "=======================================" << endl;
    cout << "           INVENTARIO DO AVENTUREIRO   " << endl;
    cout << "=======================================" << endl;
    cout << "HABILIDADE: " << jogador->getHabilidade()
        << "     ENERGIA: " << jogador->getEnergiaAtual() << " / " << jogador->getMaxEnergia()
        << "     SORTE: " << jogador->getSorte()
        << "     OURO: " << jogador->getMoedasDeOuro() << endl;
    cout << "---------------------------------------" << endl;
    cout << "    |         LISTA DE ITENS              |" << endl;
    cout << "---------------------------------------" << endl;

    // Obter lista de itens
    vector<Provisao*> itens = jogador->getProvisoes();

    cout << "Arma equipada: " << (jogador->getArma() ? jogador->getArma()->getNome() : "Nenhuma") << endl;
    cout << "Armadura equipada: " << (jogador->getArmadura() ? jogador->getArmadura()->getNome() : "Nenhuma") << endl;

    // Exibir itens
    for (size_t i = 0; i < itens.size(); ++i) {
        cout << (i + 1) << " - " << itens[i]->getNome() << endl;
    }

    cout << "---------------------------------------" << endl;
    cout << "[ Usar Item ] = U" << endl;
    cout << "[ Voltar ao Jogo ] = S" << endl;
}


void TelaInventario::handleInput(int input) {
    char opcao;
    cin.clear(); // Limpa o estado do cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove caracteres residuais do buffer
    cin >> opcao;

    if (opcao == 'U' || opcao == 'u') {
        int index;
        cout << "Digite o numero do item para usar: ";
        cin >> index;
        usarItem(index - 1);
    }
    /*else if (opcao == 'E' || opcao == 'e') {
        int index;
        cout << "Digite o número do item para equipar: ";
        cin >> index;
        equiparItem(index - 1);
    }*/
    else if (opcao == 'S' || opcao == 's') {
        jogo->mudarEstado(jogo->getEstadoAnterior());
    }
    else {
        cout << "Opção invalida!" << endl;
		exibirTela();   
    }
}

void TelaInventario::usarItem(int index) {
    Personagem* jogador = Personagem::getInstance();
    vector<Provisao*> provisoes = jogador->getProvisoes(); 

    if (index >= 0 && index < static_cast<int>(provisoes.size())) {
        Provisao* item = provisoes[index];
        cout << "Usando o item: " << item->getNome() << endl;

        // Aplicar o efeito de cura
        jogador->setEnergiaAtual(jogador->getEnergiaAtual() + item->getBonusEnergia());

        // Remover o item do inventário após o uso
        jogador->removerProvisao(item);
        delete item; // Liberar memória do item usado
    }
    else {
        cout << "Item invalido!" << endl;
    }
}

/*void TelaInventario::equiparItem(int index) {
    
    Personagem* jogador = Personagem::getInstance();
    if (index >= 0 && index < jogador->getInventario().size()) {
        jogador->equiparItem(index);
    }
    else {
        cout << "Item inválido!" << endl;
    }
}*/
