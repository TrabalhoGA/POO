#include "../include/ArquivoManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#ifdef _WIN32
    // Para Windows
    #include <windows.h>
#else
    // Para Mac/Linux
    // Na descricao do trabalho, eh dito que nao podem ser usadas bibliotecas de uso exclusivo do Windows
    // Por isso, nao eh incluido <windows.h> para o Linux/Mac
    #include <dirent.h>
    #include <sys/stat.h>
#endif

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
            // Ignora a primeira linha (opcoes de navegacao)
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
        // Le apenas a primeira linha (opcoes de navegacao)
        getline(arquivo, linha);
        arquivo.close();
        return linha;
    } else {
        cerr << "Erro ao abrir o arquivo: " << caminho << endl;
        return "";
    }
}

void ArquivoManager::escreverArquivo(const string& caminho, const string& conteudo) {
    ofstream arquivo(caminho, ios::out | ios::trunc);
    
    if (arquivo.is_open()) {
        arquivo << conteudo;
        arquivo.close();
        return;
    } else {
        // Tenta criar o arquivo se nao existir
        arquivo.open(caminho, ios::out);
        if (arquivo.is_open()) {
            arquivo << conteudo;
            arquivo.close();
            return;
        }
    }
}

vector<string>* ArquivoManager::listarArquivos(const string& prefixo) {
    vector<string>* arquivos = new vector<string>(); // Alocacao dinamica do vetor
    
#ifdef _WIN32
    // Implementacao para Windows
    WIN32_FIND_DATAA findFileData;
    string searchPattern = "*.*";
    HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findFileData);
    
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Verificar se eh um arquivo (nao diretorio)
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                string nomeArquivo = findFileData.cFileName; 
                // Verificar se o arquivo começa com o prefixo especificado
                if (nomeArquivo.find(prefixo) == 0) {
                    arquivos->push_back(nomeArquivo); 
                }
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
#else
    // Implementacao para sistemas Unix/Linux
    DIR* dir = opendir(".");
    if (dir != NULL) {
        struct dirent* entrada;
        while ((entrada = readdir(dir)) != NULL) {
            string nomeArquivo = entrada->d_name;
            
            // Verificar se eh um arquivo regular
            struct stat st;
            if (stat(nomeArquivo.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
                // Verificar se o arquivo começa com o prefixo especificado
                if (nomeArquivo.find(prefixo) == 0) {
                    arquivos->push_back(nomeArquivo);
                }
            }
        }
        closedir(dir);
    }
#endif

    return arquivos; // Retorna o ponteiro para o vetor alocado dinamicamente
}

void ArquivoManager::liberarListaArquivos(vector<string>* vetor) {
    if (vetor != nullptr) {
        delete vetor;
    }
}