#include "../include/TelaPadrao.h"
#include "../include/TelaInicial.h"
#include "../include/Personagem.h"
#include "../include/ArquivoManager.h"
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <limits>

using namespace std;

TelaPadrao::TelaPadrao(Jogo* jogo) : jogo(jogo) 
{
    // Constructor
}

TelaPadrao::~TelaPadrao() 
{
    // Destructor
}

void TelaPadrao::exibirTela() 
{
    // Obter o arquivo atual a ser exibido
    string currentFile = jogo->getCurrentStoryFile();
    
    // Verifica se estamos na tela de atributos (o caminho completo deve conter "Tela_atributos.txt")
    if (currentFile.find("Tela_atributos.txt") != string::npos) {
        exibirTelaAtributos(currentFile);
        return;
    }
    
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(currentFile);
    
    // Analisar metadados do arquivo
    parseFileMetadata(conteudo);
    
    // Exibir o conteúdo da história (sem os metadados)
    cout << conteudo << endl;
    
    // Esperar pela entrada do usuário
    int opcao;
    cin >> opcao;
    cin.ignore(); // Limpar buffer
    handleInput(opcao);
}

void TelaPadrao::handleInput(int input) 
{
    string proximaTela;
    
    // Verifica se estamos na tela de escolha de caminho
    if (jogo->getCurrentStoryFile() == "Arquivos.txt/arquivos Inicio/EscolhaCaminho.txt") {
        switch (input) {
            case 1: // Floresta
                proximaTela = "proxima_tela_floresta";
                break;
            case 2: // Caverna
                proximaTela = "proxima_tela_caverna";
                break;
            default:
                cout << "Opção inválida." << endl;
                exibirTela();
                return;
        }
    } else {
        // Para todas as outras telas, o input 1 avança para o próximo arquivo
        if (input == 1) {
            proximaTela = "proxima_tela";
        } else {
            cout << "Opção inválida." << endl;
            exibirTela();
            return;
        }
    }
    
    // Busca o próximo arquivo nos metadados
    if (storyMetadata.count(proximaTela) > 0) {
        jogo->setCurrentStoryFile(storyMetadata[proximaTela]);
        exibirTela();
    } else {
        cout << "Fim da história ou caminho não definido." << endl;
        cout << "Retornando ao menu principal..." << endl;
        jogo->setCurrentStoryFile("Arquivos.txt/Tela_menu.txt");
        jogo->mudarEstado(new TelaInicial(jogo));
    }
}

void TelaPadrao::parseFileMetadata(const string& fileContent)
{
    // Limpar metadados anteriores
    storyMetadata.clear();
    
    // Procurar por metadados no formato <!-- CHAVE: VALOR -->
    // Modificando o regex para capturar caminhos completos com espaços e caracteres especiais
    regex metadataPattern("<!--\\s*([A-Za-z_]+):\\s*([^>]+?)\\s*-->");
    
    // Capturar todas as ocorrências
    auto words_begin = sregex_iterator(fileContent.begin(), fileContent.end(), metadataPattern);
    auto words_end = sregex_iterator();
    
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        string key = match[1];
        string value = match[2];
        // Remover espaços extras no início e fim do valor
        value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
        value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);
        
        cout << "Metadado encontrado - Chave: [" << key << "] Valor: [" << value << "]" << endl;
        storyMetadata[key] = value;
    }
}

void TelaPadrao::exibirTelaAtributos(string currentFile)
{
    int pontosDisponiveis = 12;
    int habilidade = 0;
    int energia = 0;
    int sorte = 0;
    bool distribuicaoValida = false;

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(currentFile);
    
    // Analisar metadados do arquivo para definir o próximo arquivo
    parseFileMetadata(conteudo);
    
    // Exibir o conteúdo do arquivo de atributos
    cout << conteudo << endl;

    // Obter habilidade
    habilidade = 0;
    cout << "Habilidade (1-" << pontosDisponiveis << "): ";
    while (habilidade < 1 || habilidade > pontosDisponiveis) {
        cin >> habilidade;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Digite um número entre 1 e " << pontosDisponiveis << ": ";
            continue;
        }
        if (habilidade < 1 || habilidade > pontosDisponiveis) {
            cout << "Habilidade deve ser entre 1 e " << pontosDisponiveis << ". Tente novamente: ";
        }
    }
        
    int pontosRestantes = pontosDisponiveis - habilidade;
    cout << "Pontos restantes: " << pontosRestantes << endl;
        
    // Obter energia
    energia = 0;
    cout << "Energia (1-" << pontosRestantes << "): ";
    while (energia < 1 || energia > pontosRestantes) {
        cin >> energia;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Digite um número entre 1 e " << pontosRestantes << ": ";
            continue;
        }
        if (energia < 1 || energia > pontosRestantes) {
            cout << "Energia deve ser entre 1 e " << pontosRestantes << ". Tente novamente: ";
        }
    }
        
    pontosRestantes -= energia;
    cout << "Pontos restantes para Sorte: " << pontosRestantes << endl;
    
    // A sorte recebe automaticamente os pontos restantes
    sorte = pontosRestantes;
    cout << "Sorte definida como: " << sorte << endl;
    
    // Mostrar resumo da distribuição
    cout << "\nResumo da distribuição de pontos:" << endl;
    cout << "Habilidade: " << habilidade << endl;
    cout << "Energia: " << energia << endl;
    cout << "Sorte: " << sorte << endl;

    Personagem::getInstance()->setHabilidade(habilidade);
    Personagem::getInstance()->setEnergiaAtual(energia);
    Personagem::getInstance()->setSorte(sorte);
    cout << "Você está pronto para começar a aventura!" << endl;
    cout << "Pressione Enter para continuar..." << endl;
    cin.ignore();
    cin.get();
    
    // Define o próximo arquivo a ser exibido baseado nos metadados
    if (storyMetadata.count("proxima_tela") > 0) {
        string proximoArquivo = storyMetadata["proxima_tela"];
        
        // Verificar se o arquivo existe antes de tentar acessá-lo
        try {
            // Tenta ler o próximo arquivo para verificar se ele existe
            string testeConteudo = arquivoManager->lerArquivo(proximoArquivo);
            
            // Se chegou aqui, o arquivo existe e pode ser definido
            jogo->setCurrentStoryFile(proximoArquivo);
            exibirTela();
        } catch (const exception& e) {
            // Se ocorrer uma exceção, o arquivo provavelmente não existe
            cout << "Erro ao acessar o próximo arquivo: " << e.what() << endl;
            cout << "Retornando ao menu principal..." << endl;
            jogo->mudarEstado(new TelaInicial(jogo));
        }
    } else {
        cout << "Próxima tela não definida nos metadados." << endl;
        cout << "Retornando ao menu principal..." << endl;
        jogo->mudarEstado(new TelaInicial(jogo));
    }
}