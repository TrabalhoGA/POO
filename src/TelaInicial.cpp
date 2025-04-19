#include "../include/TelaInicial.h"
#include "../include/TelaPadrao.h"
//#include "../include/TelaCreditos.h"
#include <iostream>

using namespace std;

TelaInicial::TelaInicial(Jogo* jogo) : jogo(jogo) {
    // ctor
}

TelaInicial::~TelaInicial() {
    // dtor
}

void TelaInicial::exibirTela() {
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tela_menu.txt");
    
    cout << conteudo << endl;
}

void TelaInicial::handleInput(int input) {
    switch (input) {
        case 1: // Carregar jogo
            jogo->mudarEstado(new TelaPadrao(jogo)); // Futuramente, devemos criar um método para carregar o jogo na classe Jogo
            break;
        case 2: // Novo jogo
            jogo->mudarEstado(new TelaPadrao(jogo));
            break;
        case 3: // Mostrar créditos
            //jogo->mudarEstado(new TelaCreditos(jogo));
            // Futura classe TelaCreditos
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