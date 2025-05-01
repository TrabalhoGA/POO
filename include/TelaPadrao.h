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
	void handleInput(unsigned int input) override;

	void exibirTelaAtributos(string caminhoArquivo);
	void exibirTelaMercado(string caminhoArquivo);

	bool isTelaEnigma() const;
	void setTelaEnigma(bool isEnigma);

	void testarSorte(int avancoFase);
	
	void verificarItem(string nomeItem, int avancoFase);

private:
	Jogo* jogo;
	bool isEnigma;
	bool isTelaMercado;
	bool testeSorteFalhou;
};

#endif // TELAPADRAO_H