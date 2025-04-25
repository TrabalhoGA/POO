#include "../include/TelaInventario.h"
#include "../include/Personagem.h"
#include "../include/TelaBatalha.h"
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
        << "     MAGIA: " << jogador->getMagia()
        << "     OURO: " << jogador->getMoedasDeOuro() << endl;
    cout << "---------------------------------------" << endl;
    cout << "    |         LISTA DE ITENS              |" << endl;
    cout << "---------------------------------------" << endl;

    // Obter lista de provisoes
    vector<Provisao*> provisoes = jogador->getProvisoes();

    cout << "Arma equipada: " << (jogador->getArma() ? jogador->getArma()->getNome() : "Nenhuma") << endl;
    cout << "Armadura equipada: " << (jogador->getArmadura() ? jogador->getArmadura()->getNome() : "Nenhuma") << endl;

    // Exibir provisoes
    for (size_t i = 0; i < provisoes.size(); ++i) {
        cout << (i + 1) << " - " << provisoes[i]->getNome() << endl;
    }

    cout << "---------------------------------------" << endl;
    cout << "[ Usar Item ] = U" << endl;
    cout << "[ Voltar a Batalha ] = S" << endl;

    char opcao;
    cin.clear(); 
    cin >> opcao;
    cin.ignore();
    handleInput(opcao);
}

void TelaInventario::handleInput(unsigned int opcao) {
    if (opcao == 'U' || opcao == 'u') {
        // Verificar se o personagem possui itens
		vector<Provisao*> provisoes = Personagem::getInstance()->getProvisoes();
		if (provisoes.empty()) {
			cout << "Voce nao possui itens para usar!" << endl;
			cout << "Pressione Enter para voltar ao inventário..." << endl;
			cin.get(); // Remover o cin.ignore() antes
			return;
		}
		
        // Exibir lista de itens e solicitar ao usuurio que escolha um item
        int index;
        cout << "Digite o numero do item para usar: ";
        cin >> index;
        cin.ignore(); // Adicionar esta linha para limpar o buffer
        usarProvisao(index - 1);
    }
    else if (opcao == 'S' || opcao == 's') {
		jogo->mudarEstado(new TelaBatalha(jogo)); // Voltar para a tela de batalha
		cout << "Voltando..." << endl;
    }
}

void TelaInventario::usarProvisao(int index) {
    Personagem* jogador = Personagem::getInstance();
    vector<Provisao*> provisoes = jogador->getProvisoes(); 

    if (index >= 0 && index < static_cast<int>(provisoes.size())) {
        Provisao* provisao = provisoes[index];
        // Aplicar o efeito de cura
        jogador->usarProvisao(provisao);

        delete provisao; // Liberar memoria da provisao
    }
}