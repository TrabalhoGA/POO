#pragma once
#ifndef TELAINVENTARIO_H
#define TELAINVENTARIO_H

#include "Jogo.h"

using namespace std;

class TelaInventario : public TelaEstado {
public:
	TelaInventario(Jogo* jogo);
	~TelaInventario();

	void exibirTela() override;
	void handleInput(int input) override;

private:
	Jogo* jogo;
};

#endif // TELAINVENTARIO_H