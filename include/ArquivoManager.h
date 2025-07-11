#pragma once
#ifndef ARQUIVOMANAGER_H
#define ARQUIVOMANAGER_H

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class ArquivoManager {
public:
    static ArquivoManager* getInstance();
    ~ArquivoManager();

    string lerArquivo(const string& caminho);
    string lerArquivoHistoria(const string& caminho);
    string lerOpcoesHistoria(const string& caminho);
    void escreverArquivo(const string& caminho, const string& conteudo);
    
    // Modificado para retornar um ponteiro para vector
    vector<string>* listarArquivos(const string& prefixo);
    
    // Método para liberar a memoria do vector alocado
    void liberarListaArquivos(vector<string>* vetor);
    
private:
    ArquivoManager();
    
    static ArquivoManager* instance;
    
    ArquivoManager(const ArquivoManager&) = delete;
    ArquivoManager& operator=(const ArquivoManager&) = delete;
};

#endif // ARQUIVOMANAGER_H