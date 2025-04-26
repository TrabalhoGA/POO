#include "../include/Jogo.h"
#include "../include/TelaInicial.h"
#include "../include/Personagem.h"
#include "../include/Monstro.h"
#include <locale>
#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "pt-br.UTF-8");

    // Inicializando o jogo
    Jogo* jogo = Jogo::getInstance();
	// Inicializando a tela inicial
	jogo->mudarEstado(new TelaInicial(jogo));
    
	while(!jogo->sairJogo()) {
		jogo->exibirTela();
	}

	// Liberando instâncias
	Jogo::releaseInstance();
    Personagem::releaseInstance();
	Monstro::releaseInstance();

    return 0;
}