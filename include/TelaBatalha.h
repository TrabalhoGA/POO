#pragma once
#ifndef TELABATALHA_H
#define TELABATALHA_H

#include "Jogo.h"
#include "Monstro.h"
#include "ArquivoManager.h"
#include <string>

using namespace std;

class TelaBatalha : public TelaEstado {
public:
	TelaBatalha(Jogo* jogo, Monstro* monstro, const string& diretorioDestino, const string& diretorioBatalhaAtual);
	~TelaBatalha();

	void exibirTela() override;
	void handleInput(unsigned int input) override;
	
	void atacar();
	void defender();
	void acessarInventario();
	void tentarFugir();
	void acaoMonstro();
	void finalizarBatalha();

private:
	Jogo* jogo;
	Monstro* monstro;
	string diretorioDestino;
	string diretorioBatalhaAtual;

	bool fugaFalhou;
};

#endif // TELABATALHA_H