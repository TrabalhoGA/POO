#pragma once
#ifndef TELAPADRAO_H
#define TELAPADRAO_H

#include "TelaEstado.h"
#include "Jogo.h"

using namespace std;

class TelaPadrao : public TelaEstado {
public:
	TelaPadrao(Jogo* jogo);
	~TelaPadrao();

	void exibirTela() override;
	void handleInput(int input) override;

	void exibirTelaAtributos(string currentFile);
	void exibirTelaMercado(string currentFile);

private:
	Jogo* jogo;
};

#endif // TELAPADRAO_H