#include "../include/ArquivoManager.h"
#include <iostream>
#include <sstream>

using namespace std;

ArquivoManager* ArquivoManager::instance = nullptr;

ArquivoManager* ArquivoManager::getInstance() {
    if (instance == nullptr) {
        instance = new ArquivoManager();
    }
    return instance;
}

ArquivoManager::ArquivoManager() {
    // ctor
}

ArquivoManager::~ArquivoManager() {
    // dtor
}

string ArquivoManager::lerArquivo(const string& caminho) {
    ifstream arquivo(caminho);
    stringstream buffer;
    
    if (arquivo.is_open()) {
        buffer << arquivo.rdbuf();
        arquivo.close();
        return buffer.str();
    } else {
        cerr << "Erro ao abrir o arquivo: " << caminho << endl;
        return "";
    }
}

string ArquivoManager::lerArquivoHistoria(const string& caminho) {
    ifstream arquivo(caminho);
    string linha;
    stringstream buffer;
    bool primeiraLinha = true;
    
    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            // Ignora a primeira linha (opções de navegação)
            if (primeiraLinha) {
                primeiraLinha = false;
                continue;
            }
            buffer << linha << endl;
        }
        arquivo.close();
        return buffer.str();
    } else {
        cerr << "Erro ao abrir o arquivo: " << caminho << endl;
        return "";
    }
}

string ArquivoManager::lerOpcoesHistoria(const string& caminho) {
    ifstream arquivo(caminho);
    string linha;
    
    if (arquivo.is_open()) {
        // Lê apenas a primeira linha (opções de navegação)
        getline(arquivo, linha);
        arquivo.close();
        return linha;
    } else {
        cerr << "Erro ao abrir o arquivo: " << caminho << endl;
        return "";
    }
}

bool ArquivoManager::escreverArquivo(const string& caminho, const string& conteudo) {
    ofstream arquivo(caminho);
    
    if (arquivo.is_open()) {
        arquivo << conteudo;
        arquivo.close();
        return true;
    } else {
        cerr << "Erro ao abrir o arquivo para escrita: " << caminho << endl;
        return false;
    }
}