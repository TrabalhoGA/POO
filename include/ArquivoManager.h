#pragma once
#ifndef ARQUIVOMANAGER_H
#define ARQUIVOMANAGER_H

#include <string>
#include <fstream>

using namespace std;

class ArquivoManager {
public:
    static ArquivoManager* getInstance();
    ~ArquivoManager();

    string lerArquivo(const string& caminho);
    string lerArquivoHistoria(const string& caminho);
    string lerOpcoesHistoria(const string& caminho);
    bool escreverArquivo(const string& caminho, const string& conteudo);
    
private:
    ArquivoManager();
    
    static ArquivoManager* instance;
    
    ArquivoManager(const ArquivoManager&) = delete;
    ArquivoManager& operator=(const ArquivoManager&) = delete;
};

#endif // ARQUIVOMANAGER_H