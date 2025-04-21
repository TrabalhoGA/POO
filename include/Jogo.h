#pragma once
#ifndef JOGO_H
#define JOGO_H

#include "TelaEstado.h"
#include <string>
#include <cstdlib>

using namespace std;

class Jogo {
public:
	// Destrutor
	~Jogo();

	// Método estático para obter a instância única (Singleton)
	static Jogo* getInstance();

	static void resetInstance();
	static void releaseInstance();

	void exibirTela();
	void handleInput(int input);
	void mudarEstado(TelaEstado* novoEstado);

	void setDiretorioAtual(const string& diretorio);
	string getDiretorioAtual() const;

	TelaEstado* getEstadoAtual() const;

	int getFaseAtual() const;
	void setFaseAtual(int fase);
	void avancarFase(int incremento = 1);

	void limparTela();

private:
	// Construtor privado (Singleton)
	Jogo();
	
	// Instância estática única (Singleton)
	static Jogo* instance;
	
	TelaEstado* estadoAtual;

	// Diretório atual
	string diretorioAtual;

	// Fase atual
	int faseAtual;
	
	// Impede cópias do objeto (Singleton)
	Jogo(const Jogo&) = delete;
	Jogo& operator=(const Jogo&) = delete;
};

#endif // JOGO_H