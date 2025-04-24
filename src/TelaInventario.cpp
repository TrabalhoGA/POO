#include "../include/TelaInventario.h"
#include "../include/Personagem.h"
#include "../include/TelaPadrao.h"
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

    // Exibir cabecalho
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

    char opcao;
    cin.clear(); // Limpa o estado do cin
    cin >> opcao;
    handleInput(opcao);
}


void TelaInventario::handleInput(unsigned int opcao) {
    if (opcao == 'U' || opcao == 'u') {
        // Verificar se o personagem possui itens
		vector<Provisao*> provisoes = Personagem::getInstance()->getProvisoes();
		if (provisoes.empty()) {
			cout << "Voc� n�o possui itens para usar!" << endl;
			cout << "Pressione Enter para voltar ao invent�rio..." << endl;
			cin.ignore();
			cin.get();
			return;
		}
		// Exibir lista de itens e solicitar ao usu�rio que escolha um item
        int index;
        cout << "Digite o numero do item para usar: ";
        cin >> index;
        usarItem(index - 1);
    }
    else if (opcao == 'S' || opcao == 's') {
		jogo->mudarEstado(new TelaPadrao(jogo)); // Retorna para a tela padrao, mas futuramente retornara a tela de batalha
		cout << "Voltando..." << endl;
    }
    else {
        cout << "Opcao invalida!" << endl;
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

        // Remover o item do inventario apos o uso
        jogador->removerProvisao(item);
        delete item; // Liberar memoria do item usado
    }
    else {
        cout << "Item invalido!" << endl;
    }
}