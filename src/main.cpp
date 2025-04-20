#include "../include/Jogo.h"
#include "../include/TelaInicial.h"
#include "../include/Personagem.h"
#include <iostream>

using namespace std;

int main() {
    // Inicializando o jogo
    Jogo* jogo = Jogo::getInstance();
	// Inicializando a tela inicial
	jogo->mudarEstado(new TelaInicial(jogo));
    
    // Criando o personagem
    Personagem* jogador = Personagem::getInstance(0, 0, 0, 0, 0);
    
	while(true){
		jogo->exibirTela();
	}
    
    return 0;
}