#pragma once
#ifndef TELABATALHA_H
#define TELABATALHA_H

#include "Jogo.h"

using namespace std;

class TelaBatalha : public TelaEstado {
public:
	TelaBatalha(Jogo* jogo);
	~TelaBatalha();

	void exibirTela() override;
	void handleInput(unsigned int input) override;

private:
	Jogo* jogo;
};

#endif // TELABATALHA_H