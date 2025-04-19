#pragma once
#ifndef TELAPADRAO_H
#define TELAPADRAO_H

#include "TelaEstado.h"
#include "Jogo.h"
#include <map>
#include <string>

using namespace std;

class TelaPadrao : public TelaEstado {
public:
	TelaPadrao(Jogo* jogo);
	~TelaPadrao();

	void exibirTela() override;
	void handleInput(int input) override;

	void exibirTelaAtributos(string currentFile);

private:
	Jogo* jogo;
	map<string, string> storyMetadata; // Armazena metadados como próximos arquivos
	
	// Método para analisar os metadados do arquivo
	void parseFileMetadata(const string& fileContent);
};

#endif // TELAPADRAO_H