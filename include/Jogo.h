#pragma once
#ifndef JOGO_H
#define JOGO_H

#include "TelaEstado.h"

using namespace std;

class Jogo {
public:
	Jogo();
	~Jogo();

	void exibirTela();
	void handleInput(int input);

	void mudarEstado(TelaEstado* novoEstado);

private:
	TelaEstado* estadoAtual;
};

#endif // JOGO_H