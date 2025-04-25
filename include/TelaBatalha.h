#pragma once
#ifndef TELABATALHA_H
#define TELABATALHA_H

#include "Jogo.h"
#include "Monstro.h"
#include "Personagem.h"
#include "ArquivoManager.h"
#include <string>

using namespace std;

class TelaBatalha : public TelaEstado {
public:
	TelaBatalha(Jogo* jogo);
	~TelaBatalha();

	void exibirTela() override;
	void handleInput(unsigned int input) override;

	void inicializarMonstro();
	
	void atacar();
	void defender();
	void acessarInventario();
	bool tentarFugir();
	void acaoMonstro();
	void finalizarBatalha();

private:
	Jogo* jogo;
	Personagem* jogador;
	Monstro* monstro;
	string diretorioDestino;
	int faseDestino;

	bool jogadorDefendendo;
	bool monstroDefendendo;
};

#endif // TELABATALHA_H