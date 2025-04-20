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

// Método para liberar a instância
void Jogo::releaseInstance(){
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

// Método para resetar a instância
void Jogo::resetInstance(){
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

Jogo::Jogo() : estadoAtual(nullptr) {
    // Construtor
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

void Jogo::setDiretorioAtual(const string& diretorio) {
    diretorioAtual = diretorio;
}

string Jogo::getDiretorioAtual() const {
    return diretorioAtual;
}

void Jogo::setFaseAtual(int fase){
    faseAtual = fase;
}

int Jogo::getFaseAtual() const {
    return faseAtual;
}

void Jogo::avancarFase(int incremento) {
    setFaseAtual(faseAtual + incremento);
}

void Jogo::limparTela() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux / macOS
#endif
}