#include "../include/TelaInicial.h"
#include "../include/TelaPadrao.h"
#include <iostream>

using namespace std;

TelaInicial::TelaInicial(Jogo* jogo) : jogo(jogo) {
    // ctor
}

TelaInicial::~TelaInicial() {
    // dtor
}

void TelaInicial::exibirTela() {
    int opcao;

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tela_menu.txt");
    
    cout << conteudo << endl;
    cin >> opcao;
    cin.ignore(); // Limpar o buffer de entrada
    handleInput(opcao);
}

void TelaInicial::handleInput(int input) {
    switch (input) {
        case 1: // Carregar jogo
            jogo->mudarEstado(new TelaPadrao(jogo)); // Futuramente, devemos criar um método para carregar o jogo na classe Jogo
            break;
        case 2: // Novo jogo
            jogo->mudarEstado(new TelaPadrao(jogo));
            break;
        case 3: // Créditos
            exibirCreditos();
            break;
        case 4: // Sair
            cout << "Saindo do jogo...\n";
            exit(0);
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
            break;
    }
}

void TelaInicial::exibirCreditos() {
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Creditos.txt");
    
    cout << conteudo << endl;
    cin.ignore();
    cin.get();
    
    // Exibir a tela inicial novamente
    exibirTela();
}