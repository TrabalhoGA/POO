#pragma once
#ifndef TELAESTADO_H
#define TELAESTADO_H

#include <iostream>

using namespace std;

class TelaEstado {
public:
	virtual ~TelaEstado() = default;

	virtual void exibirTela() = 0;
	virtual void handleInput(unsigned int input) = 0;
};

#endif // TELAESTADO_H