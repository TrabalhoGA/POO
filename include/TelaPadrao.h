#pragma once
#ifndef TELAPADRAO_H
#define TELAPADRAO_H

#include "TelaEstado.h"
#include "Jogo.h"

using namespace std;

class TelaPadrao : public TelaEstado {
public:
	TelaPadrao(Jogo* jogo);
	TelaPadrao(Jogo* jogo, bool isEnigma, bool isTelaMercado, bool testeSorteFalhou);
	~TelaPadrao();

	void exibirTela() override;
	void handleInput(unsigned int input) override;

	void exibirTelaAtributos(string caminhoArquivo);
	void exibirTelaMercado(string caminhoArquivo);

	void testarSorte(int avancoFase);
	
	void verificarItem(string nomeItem, int avancoFase);

	bool isTesteSorteFalhou() const { return testeSorteFalhou; }
	bool isTelaMercado() const { return telaMercado; }
	bool isEnigma() const { return enigma; }

private:
	Jogo* jogo;
	bool enigma;
	bool telaMercado;
	bool testeSorteFalhou;
};

#endif // TELAPADRAO_H