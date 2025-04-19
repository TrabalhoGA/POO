#pragma once
#ifndef JOGO_H
#define JOGO_H

#include "TelaEstado.h"

using namespace std;

class Jogo {
public:
	// Destrutor
	~Jogo();

	// Método estático para obter a instância única (Singleton)
	static Jogo* getInstance();

	void exibirTela();
	void handleInput(int input);
	void mudarEstado(TelaEstado* novoEstado);

private:
	// Construtor privado (Singleton)
	Jogo();
	
	// Instância estática única (Singleton)
	static Jogo* instance;
	
	TelaEstado* estadoAtual;
	
	// Impede cópias do objeto (Singleton)
	Jogo(const Jogo&) = delete;
	Jogo& operator=(const Jogo&) = delete;
};

#endif // JOGO_H