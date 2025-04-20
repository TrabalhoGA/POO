#include "../include/TelaInicial.h"
#include "../include/TelaPadrao.h"
#include "../include/ArquivoManager.h"
#include "../include/Personagem.h"
#include <iostream>

using namespace std;

TelaInicial::TelaInicial(Jogo* jogo) : jogo(jogo) {
    // ctor
}

TelaInicial::~TelaInicial() {
    // dtor
}

void TelaInicial::exibirTela() {
    // Iniciar a variável que armazena a opção do usuário
    int opcao;

    // Ler o conteúdo do arquivo de texto para exibir o menu
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tela_menu.txt");
    
    // Exibir o conteúdo do arquivo e guardar a opção do usuário
    cout << conteudo << endl;
    cin >> opcao;
    cin.ignore(); // Limpar o buffer de entrada

    // Chamar o método handleInput para processar a opção escolhida
    handleInput(opcao);
}

void TelaInicial::handleInput(int input) {
    switch (input) {
        case 1: // Carregar jogo
            carregarJogo();
            break;
        case 2: // Novo jogo
            // Define o arquivo inicial para um novo jogo
            jogo->setDiretorioAtual("inicio");
            jogo->setFaseAtual(1);
            jogo->mudarEstado(new TelaPadrao(jogo));
            break;
        case 3: // Créditos
            exibirCreditos();
            break;
        case 4: // Sair
            cout << "Saindo do jogo...\n";
            Personagem::releaseInstance();
            Jogo::releaseInstance();
            exit(0);
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
            break;
    }
}

void TelaInicial::exibirCreditos() {
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tela_creditos.txt");
    
    cout << conteudo << endl;
    cin.ignore();
    cin.get();
    
    // Exibir a tela inicial novamente
    exibirTela();
}

// Novo método para carregar um jogo salvo
void TelaInicial::carregarJogo() {
    // 1. Ler arquivo de save (a ser implementado)
    // 2. Setar os atributos e itens do personagem com base no arquivo
    // 3. Definir o arquivo atual da história com base no save
    // 4. Mudar o estado do jogo para a tela padrão
    // 5. Exibir tela padrão
    // 6. Retornar para a tela inicial se não houver save
}