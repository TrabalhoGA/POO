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
	void exibirMercadorTorre(string caminhoArquivo);

	bool isTelaEnigma() const;
	void setTelaEnigma(bool isEnigma);

	bool isTelaTesteSorte() const;
	void setTelaTesteSorte(bool isTesteSorte);

	void acaoTocha(bool possuiTocha);

private:
	Jogo* jogo;
	bool isEnigma;
	bool isTesteSorte;
	bool possuiTocha;
};

#endif // TELAPADRAO_H