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
    cout << "           INVENTÁRIO DO AVENTUREIRO   " << endl;
    cout << "=======================================" << endl;
    cout << "HABILIDADE: " << jogador->getHabilidade()
        << "     ENERGIA: " << jogador->getEnergiaAtual() << " / " << jogador->getMaxEnergia()
        << "     SORTE: " << jogador->getSorte()
        << "     MAGIA: " << jogador->getMagia()
        << "     OURO: " << jogador->getMoedasDeOuro() << endl;
    cout << "---------------------------------------" << endl;
    cout << "    |         LISTA DE ITENS              |" << endl;
    cout << "---------------------------------------" << endl;

    // Obter lista de provisoes e equipamentos
    vector<Provisao*> provisoes = jogador->getProvisoes();
    vector<Equipamento*> equipamentos = jogador->getEquipamentos();

    cout << "Arma equipada: " << (jogador->getArma() ? jogador->getArma()->getNome() : "Nenhuma") << endl;
    cout << "Armadura equipada: " << (jogador->getArmadura() ? jogador->getArmadura()->getNome() : "Nenhuma") << endl;

    // Exibir provisoes
    cout << "---------------------------------------" << endl;
    cout << "Provisões: " << endl;
    for (size_t i = 0; i < provisoes.size(); ++i) {
        cout << (i + 1) << " - " << provisoes[i]->getNome() << endl;
    }
    
    // Exibir equipamentos disponíveis
    cout << "---------------------------------------" << endl;
    cout << "Equipamentos: " << endl;
    if (equipamentos.empty()) {
        cout << "Nenhum equipamento disponível" << endl;
    } else {
        for (size_t i = 0; i < equipamentos.size(); ++i) {
            cout << (i + 1) << " - " << equipamentos[i]->getNome() << endl;
        }
    }

    cout << "---------------------------------------" << endl;
    cout << "[ Usar Provisão ] = U" << endl;
    cout << "[ Equipar Item ] = E" << endl;
    cout << "[ Sair ] = S" << endl;

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
			cout << "Você não possui itens para usar!" << endl;
			cout << "Pressione Enter para voltar ao inventário..." << endl;
			cin.get(); // Remover o cin.ignore() antes
			return;
		}
		
        // Exibir lista de itens e solicitar ao usuario que escolha um item
        int index;
        cout << "Digite o número do item para usar: ";
        cin >> index;
        cin.ignore(); // Adicionar esta linha para limpar o buffer
        usarProvisao(index - 1);
    }
    else if (opcao == 'E' || opcao == 'e') {
        // Verificar se o personagem possui equipamentos
        vector<Equipamento*> equipamentos = Personagem::getInstance()->getEquipamentos();
        if (equipamentos.empty()) {
            cout << "Você não possui equipamentos para equipar!" << endl;
            cout << "Pressione Enter para voltar ao inventário..." << endl;
            cin.get();
            return;
        }
        
        // Exibir lista de equipamentos e solicitar que escolha um
        int index;
        cout << "Digite o número do equipamento para equipar: ";
        cin >> index;
        cin.ignore();
        equiparEquipamento(index - 1);
    }
    else if (opcao == 'S' || opcao == 's') {
		jogo->voltarEstadoAnterior();
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

void TelaInventario::equiparEquipamento(int index) {
    Personagem* jogador = Personagem::getInstance();
    vector<Equipamento*> equipamentos = jogador->getEquipamentos();

    if (index >= 0 && index < static_cast<int>(equipamentos.size())) {
        // Chama o método do personagem para equipar o item selecionado
        jogador->equiparEquipamento(index);
    }
}