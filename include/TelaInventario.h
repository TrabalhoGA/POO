#pragma once
#ifndef TELAINVENTARIO_H
#define TELAINVENTARIO_H

#include "Jogo.h"
#include <vector>
#include <string>

using namespace std;

class TelaInventario : public TelaEstado {
public:
	TelaInventario(Jogo* jogo);
	~TelaInventario();

	void exibirTela() override;
	void handleInput(unsigned int input) override;

private:
	Jogo* jogo;

	void usarItem(int index);
};

#endif // TELAINVENTARIO_H