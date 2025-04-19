#pragma once
#ifndef TELAINICIAL_H
#define TELAINICIAL_H

#include "Jogo.h"

using namespace std;

class TelaInicial : public TelaEstado {
public:
	TelaInicial(Jogo* jogo);
	~TelaInicial();

	void exibirTela() override;
	void handleInput(int input) override;

private:
	Jogo* jogo;
};

#endif // TELAINICIAL_H