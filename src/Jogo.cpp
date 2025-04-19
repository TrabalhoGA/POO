#include "../include/Jogo.h"

using namespace std;

// Inicialização da variável estática
Jogo* Jogo::instance = nullptr;

// Implementação do método getInstance com Lazy Initialization
Jogo* Jogo::getInstance() {
    if (instance == nullptr) {
        instance = new Jogo();
    }
    return instance;
}

Jogo::Jogo() {
    estadoAtual = nullptr;
}

Jogo::~Jogo() {
    delete estadoAtual;
}

void Jogo::exibirTela() {
    if (estadoAtual) {
        estadoAtual->exibirTela();
    }
}

void Jogo::handleInput(int input) {
    if (estadoAtual) {
        estadoAtual->handleInput(input);
    }
}

void Jogo::mudarEstado(TelaEstado* novoEstado) {
    if (estadoAtual) {
        delete estadoAtual;
    }
    estadoAtual = novoEstado;
}