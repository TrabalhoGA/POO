#include "../include/TelaInicial.h"
#include "../include/TelaPadrao.h"
#include "../include/ArquivoManager.h"
#include "../include/Personagem.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

TelaInicial::TelaInicial(Jogo* jogo) : jogo(jogo) {
    // ctor
}

TelaInicial::~TelaInicial() {
    // dtor
}

void TelaInicial::exibirTela() {
	// Limpar a tela
	jogo->limparTela();

    // Iniciar a variável que armazena a opção do usuário
    int opcao;

    // Ler o conteúdo do arquivo de texto para exibir o menu
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tela_menu.txt");
    
    // Exibir o conteúdo do arquivo e guardar a opção do usuário
    cout << conteudo << endl;
    if (jogo->getEstadoAnterior() != nullptr) {
        cout << "5 - Voltar";
    }
    cout << "\n=========================================\n";
    cin >> opcao;
    cin.ignore(); // Limpar o buffer de entrada

    // Chamar o método handleInput para processar a opção escolhida
    handleInput(opcao);
}

void TelaInicial::handleInput(unsigned int input) {
    switch (input) {
        case 1: // Carregar jogo
            escolherSave();
            break;
        case 2: // Novo jogo
            novoJogo();
            break;
        case 3: // Créditos
            exibirCreditos();
            break;
        case 4: // Sair
            cout << "Saindo do jogo...\n";
            jogo->setSairJogo(true);
            break;
        case 5: // Voltar
            if (jogo->getEstadoAnterior() != nullptr) {
                jogo->voltarEstadoAnterior();
                break;
            }
        default:
            cout << "Opcao inválida. Tente novamente.\n";
            break;
    }
}

void TelaInicial::exibirCreditos() {
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tela_creditos.txt");
    jogo->limparTela();
    cout << conteudo << endl;
    cin.get();
    return; 
}

void TelaInicial::carregarJogo() {
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string save = arquivoManager->lerArquivo(jogo->getNomeSave());
    if (save.empty()) {
        cout << "Nenhum jogo salvo encontrado! Pressione Enter para continuar.\n";
        cin.get(); 
        return;
    }

    // Dividir o conteúdo do arquivo por linhas
    vector<string> linhas;
    size_t pos = 0;
    string linha;
    while ((pos = save.find("\n")) != string::npos) {
        linha = save.substr(0, pos);
        linhas.push_back(linha);
        save.erase(0, pos + 1);
    }
    linhas.push_back(save); // Adiciona a última linha

    // Definir diretório atual e fase atual com base na primeira linha do arquivo
    string diretorioFase = linhas[0];
    size_t separador = diretorioFase.find(":");
    if (separador != string::npos) {
        string diretorio = diretorioFase.substr(0, separador);
        int fase = stoi(diretorioFase.substr(separador + 1));
        jogo->setDiretorioAtual(diretorio);
        jogo->setFaseAtual(fase);
    }

    // Setar os atributos e itens do personagem com base na segunda linha do arquivo
    if (linhas.size() > 1) {
        string atributos = linhas[1];
        vector<string> atributosArray;
        size_t pos_attr = 0;
        string attr;
        while ((pos_attr = atributos.find(",")) != string::npos) {
            attr = atributos.substr(0, pos_attr);
            atributosArray.push_back(attr);
            atributos.erase(0, pos_attr + 1);
        }
        atributosArray.push_back(atributos);
        Personagem* p = Personagem::getInstance();
        p->setMaxEnergia(stoi(atributosArray[0]));
        p->setEnergiaAtual(stoi(atributosArray[1])); 
        p->setHabilidade(stoi(atributosArray[2]));
        p->setResistencia(stoi(atributosArray[3]));
        p->setMagia(stoi(atributosArray[4]));
        p->setSorte(stoi(atributosArray[5]));
        p->setMoedasDeOuro(stoi(atributosArray[6]));
        
        // Processar armadura com base na terceira linha do arquivo
        if (linhas.size() > 2 && linhas[2] != "Nenhuma") {
            vector<string> armaduraInfo;
            string armaduraStr = linhas[2];
            pos_attr = 0;
            while ((pos_attr = armaduraStr.find(",")) != string::npos) {
                attr = armaduraStr.substr(0, pos_attr);
                armaduraInfo.push_back(attr);
                armaduraStr.erase(0, pos_attr + 1);
            }
            armaduraInfo.push_back(armaduraStr);
            if (armaduraInfo.size() >= 5) {
                Armadura* armadura = new Armadura(
                    armaduraInfo[0], // nome
                    armaduraInfo[1], // descrição
                    stoi(armaduraInfo[2]), // habilidade mínima
                    stoi(armaduraInfo[3]), // resistência mínima
                    stoi(armaduraInfo[4])  // buff resistência
                );
                p->equiparArmadura(armadura);
            }
        }
        
        // Processar arma com base na quarta linha do arquivo
        if (linhas.size() > 3 && linhas[3] != "Nenhuma") {
            vector<string> armaInfo;
            string armaStr = linhas[3];
            pos_attr = 0;
            while ((pos_attr = armaStr.find(",")) != string::npos) {
                attr = armaStr.substr(0, pos_attr);
                armaInfo.push_back(attr);
                armaStr.erase(0, pos_attr + 1);
            }
            armaInfo.push_back(armaStr);
            if (armaInfo.size() >= 5) {
                Arma* arma = new Arma(
                    armaInfo[0], // nome
                    armaInfo[1], // descrição
                    stoi(armaInfo[2]), // habilidade mínima
                    stoi(armaInfo[3]), // resistência mínima
                    stoi(armaInfo[4])  // buff habilidade
                );
                p->equiparArma(arma);
            }
        }
        
        // Processar provisões com base na quinta linha do arquivo
        if (linhas.size() > 4 && linhas[4] != "Nenhuma") {
            string provisoesStr = linhas[4];
            vector<string> provisoesArray;
            size_t pos_prov = 0;
            string provisao;
            while ((pos_prov = provisoesStr.find(";")) != string::npos) {
                provisao = provisoesStr.substr(0, pos_prov);
                provisoesArray.push_back(provisao);
                provisoesStr.erase(0, pos_prov + 1);
            }
            for (int i = 0; i < provisoesArray.size(); i++) {
                string provStr = provisoesArray[i];
                vector<string> provInfo;
                pos_attr = 0;
                while ((pos_attr = provStr.find(",")) != string::npos) {
                    attr = provStr.substr(0, pos_attr);
                    provInfo.push_back(attr);
                    provStr.erase(0, pos_attr + 1);
                }
                provInfo.push_back(provStr);
                if (provInfo.size() >= 4) {
                    Provisao* prov = new Provisao(
                        provInfo[0], // nome
                        provInfo[1], // descrição
                        stoi(provInfo[2]), // magia mínima
                        stoi(provInfo[3])  // bonus energia
                    );
                    p->adicionarProvisao(prov);
                }
            }
        }
        
        // Processar relíquias mágicas com base na sexta linha do arquivo
        if (linhas.size() > 5 && linhas[5] != "Nenhuma") {
            string reliquiasStr = linhas[5];
            vector<string> reliquiasArray;
            size_t pos_rel = 0;
            string reliquia;
            while ((pos_rel = reliquiasStr.find(";")) != string::npos) {
                reliquia = reliquiasStr.substr(0, pos_rel);
                reliquiasArray.push_back(reliquia);
                reliquiasStr.erase(0, pos_rel + 1);
            }
            for (int i = 0; i < reliquiasArray.size(); i++) {
                string relStr = reliquiasArray[i];
                vector<string> relInfo;
                pos_attr = 0;
                while ((pos_attr = relStr.find(",")) != string::npos) {
                    attr = relStr.substr(0, pos_attr);
                    relInfo.push_back(attr);
                    relStr.erase(0, pos_attr + 1);
                }
                relInfo.push_back(relStr);
                if (relInfo.size() >= 8) {
                    ReliquiaMagica* rel = new ReliquiaMagica(
                        relInfo[0],
                        relInfo[1],
                        stoi(relInfo[2])
                    );
                    rel->setBuffEnergia(stoi(relInfo[3]));
                    rel->setBuffHabilidade(stoi(relInfo[4]));
                    rel->setBuffResistencia(stoi(relInfo[5]));
                    rel->setBuffMagia(stoi(relInfo[6]));
                    rel->setBuffSorte(stoi(relInfo[7]));
                    p->adicionarReliquiaMagica(rel);
                }
            }
        }

        if (linhas.size() > 6 && linhas[6] != "Nenhum") {
            string equipamentosStr = linhas[6];
            vector<string> equipamentosArray;
            size_t pos_eq = 0;
            string equipamento;
            while ((pos_eq = equipamentosStr.find(";")) != string::npos) {
                equipamento = equipamentosStr.substr(0, pos_eq);
                equipamentosArray.push_back(equipamento);
                equipamentosStr.erase(0, pos_eq + 1);
            }
            for (int i = 0; i < equipamentosArray.size(); i++) {
                string eqStr = equipamentosArray[i];
                vector<string> eqInfo;
                pos_attr = 0;
                while ((pos_attr = eqStr.find(",")) != string::npos) {
                    attr = eqStr.substr(0, pos_attr);
                    eqInfo.push_back(attr);
                    eqStr.erase(0, pos_attr + 1);
                }
                eqInfo.push_back(eqStr);
                if (eqInfo.size() >= 6) {  // Alterar para >= 6
                    Equipamento* equip = nullptr;
                    if (eqInfo[5] == "armadura") {
                        equip = new Armadura(
                            eqInfo[0], // nome
                            eqInfo[1], // descrição
                            stoi(eqInfo[2]), // habilidade mínima
                            stoi(eqInfo[3]), // resistência mínima
                            stoi(eqInfo[4])  // buff resistência
                        );
                    } else if (eqInfo[5] == "arma") {
                        equip = new Arma(
                            eqInfo[0], // nome
                            eqInfo[1], // descrição
                            stoi(eqInfo[2]), // habilidade mínima
                            stoi(eqInfo[3]), // resistência mínima
                            stoi(eqInfo[4])  // buff habilidade
                        );
                    }
                    if (equip) {
                        p->adicionarEquipamento(equip);
                    }
                }
            }
        }
    }

    // Recuperar configurações da tela padrão (isTesteSorteFalhou, isTelaMercado, isEnigma)
    bool isTesteSorteFalhou = false;
    bool isTelaMercado = false;
    bool isEnigma = false;
    if (linhas.size() > 7) { // Se existe a linha de configurações extras
        string configLinha = linhas[7];
        vector<string> configVals;
        size_t pos = 0;
        string token;
        string temp = configLinha;
        while ((pos = temp.find(",")) != string::npos) {
            token = temp.substr(0, pos);
            configVals.push_back(token);
            temp.erase(0, pos + 1);
        }
        configVals.push_back(temp);
        if (configVals.size() >= 3) {
            isTesteSorteFalhou = (configVals[0] == "1");
            isTelaMercado = (configVals[1] == "1");
            isEnigma = (configVals[2] == "1");
        }
    }

    jogo->mudarEstado(new TelaPadrao(jogo, isEnigma, isTelaMercado, isTesteSorteFalhou));
    cout << "Jogo carregado com sucesso! Pressione Enter para continuar...\n";
    cin.get();
    return;
}

void TelaInicial::novoJogo() {
    // Limpar a tela
    jogo->limparTela();

    Personagem* p = Personagem::getInstance();

    if (p != nullptr) {
        // Resetar a instância do personagem
        Personagem::resetInstance();
    }

    // Obter o nome do personagem
    string nome;
    cout << "Bem-vindo ao novo jogo!\n";
    cout << "Por favor, digite o nome do seu personagem (sem espacos ou caracteres especiais):\n";
    cout << "Nome: ";
    cin >> nome;
    cin.ignore(); // Limpar o buffer de entrada

    // Substituir espaços por underscores, se houver
    // (não deve haver espaços, mas é uma precaução)
    for (char& c : nome) {
        if (c == ' ') {
            c = '_';
        }
    }

    // Remover caracteres especiais
    nome.erase(remove_if(nome.begin(), nome.end(), [](char c) {
        return !isalnum(c) && c != '_';
    }), nome.end());

    jogo->setNomeSave("save_" + nome + ".txt");
    jogo->setDiretorioAtual("inicio");
    jogo->setFaseAtual(0);
    jogo->mudarEstado(new TelaPadrao(jogo));
}

void TelaInicial::escolherSave(){
    jogo->limparTela();
    // Obter todos os arquivos que comecem com "save_" no diretório atual
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    vector<string>* saves = arquivoManager->listarArquivos("save_");
    
    // Verificar se existem saves disponíveis
    if (saves->empty()) {
        cout << "Nenhum arquivo de save encontrado!" << endl;
        cout << "Pressione Enter para voltar ao menu principal..." << endl;
        cin.get();
        arquivoManager->liberarListaArquivos(saves); // Liberar a memória alocada para o vector
        return;
    }

    // Exibir a lista de saves disponíveis
    cout << "    Saves disponíveis:" << endl;
    cout << "----------------------------" << endl;
    
    for (int i = 0; i < saves->size(); i++) {
        // Extrair apenas o nome do personagem removendo "save_" e ".txt"
        string nome = (*saves)[i];
        nome = nome.substr(5); // Remove "save_" (5 caracteres)
        nome = nome.substr(0, nome.length() - 4); // Remove ".txt" (4 caracteres)
        cout << i + 1 << ". " << nome << endl;
    }
    
    cout << endl << "0. Voltar ao menu principal" << endl;
    cout << "----------------------------" << endl;
    cout << "Escolha um save (1-" << saves->size() << ") ou 0 para voltar: ";
    
    // Obter a escolha do usuário
    int escolha;
    cin >> escolha;
    cin.ignore(); // Limpar o buffer de entrada
    
    // Verificar a escolha
    if (escolha == 0) {
        // Voltar ao menu principal
        arquivoManager->liberarListaArquivos(saves); // Liberar a memória alocada para o vector
        return;
    }
    else if (escolha >= 1 && escolha <= saves->size()) {
        // Definir o nome do arquivo de save selecionado
        jogo->setNomeSave((*saves)[escolha - 1]);
        arquivoManager->liberarListaArquivos(saves); // Liberar a memória alocada para o vector
    }
    else {
        // Escolha inválida
        cout << "Escolha inválida!" << endl;
        cout << "Pressione Enter para tentar novamente..." << endl;
        cin.get();
        arquivoManager->liberarListaArquivos(saves); // Liberar a memória alocada para o vector
        escolherSave(); // Chamar a função novamente para tentar de novo
        return;
    }
    carregarJogo();
}