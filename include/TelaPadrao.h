#pragma once
#ifndef TELAPADRAO_H
#define TELAPADRAO_H

#include "Jogo.h"

using namespace std;

class TelaPadrao : public TelaEstado {
public:
	TelaPadrao(Jogo* jogo);
	~TelaPadrao();

	void exibirTela() override;
	void handleInput(int input) override;

private:
	Jogo* jogo;
};

#endif // TELAPADRAO_H