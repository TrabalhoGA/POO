#pragma once
#ifndef TELAINICIAL_H
#define TELAINICIAL_H

#include "Jogo.h"
#include "ArquivoManager.h"

using namespace std;

class TelaInicial : public TelaEstado {
public:
	TelaInicial(Jogo* jogo);
	~TelaInicial();

	void exibirTela() override;
	void handleInput(unsigned int input) override;

	void exibirCreditos();
    void carregarJogo();
	void novoJogo();
	void escolherSave();
private:
	Jogo* jogo;
};

#endif // TELAINICIAL_H