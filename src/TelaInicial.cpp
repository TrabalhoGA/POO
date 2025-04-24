#include "../include/TelaInicial.h"
#include "../include/TelaPadrao.h"
#include "../include/ArquivoManager.h"
#include "../include/Personagem.h"
#include <iostream>

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
    cin >> opcao;
    cin.ignore(); // Limpar o buffer de entrada

    // Chamar o método handleInput para processar a opção escolhida
    handleInput(opcao);
}

void TelaInicial::handleInput(unsigned int input) {
    switch (input) {
        case 1: // Carregar jogo
            carregarJogo();
            break;
        case 2: // Novo jogo
            // Define o arquivo inicial para um novo jogo
            jogo->setDiretorioAtual("inicio");
            jogo->setFaseAtual(1);
            jogo->mudarEstado(new TelaPadrao(jogo));
            break;
        case 3: // Créditos
            exibirCreditos();
            break;
        case 4: // Sair
            cout << "Saindo do jogo...\n";
            Personagem::releaseInstance();
            Jogo::releaseInstance();
            exit(0);
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
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
    // Instanciar o arquivo manager e ler o arquivo de save
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string save = arquivoManager->lerArquivo("save.txt");
    if (save.empty()) {
        cout << "Nenhum jogo salvo encontrado! Pressione Enter para voltar ao menu inicial.\n";
        cin.get(); // Remover o cin.ignore() antes do cin.get()
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
        
        // Dividir a string de atributos por vírgulas
        size_t pos_attr = 0;
        string attr;
        while ((pos_attr = atributos.find(",")) != string::npos) {
            attr = atributos.substr(0, pos_attr);
            atributosArray.push_back(attr);
            atributos.erase(0, pos_attr + 1);
        }
        atributosArray.push_back(atributos);
        
        // Criar ou obter a instância do personagem
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
            
            // Dividir a string de armadura por vírgulas
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
            
            // Dividir a string de arma por vírgulas
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
            
            // Dividir a string de provisões por ponto e vírgula (cada provisão)
            size_t pos_prov = 0;
            string provisao;
            while ((pos_prov = provisoesStr.find(";")) != string::npos) {
                provisao = provisoesStr.substr(0, pos_prov);
                provisoesArray.push_back(provisao);
                provisoesStr.erase(0, pos_prov + 1);
            }
            
            // Processar cada provisão
            for (string provStr : provisoesArray) {
                vector<string> provInfo;
                
                // Dividir a string de provisão por vírgulas
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
            
            // Dividir a string de relíquias por ponto e vírgula (cada relíquia)
            size_t pos_rel = 0;
            string reliquia;
            while ((pos_rel = reliquiasStr.find(";")) != string::npos) {
                reliquia = reliquiasStr.substr(0, pos_rel);
                reliquiasArray.push_back(reliquia);
                reliquiasStr.erase(0, pos_rel + 1);
            }
            
            // Processar cada relíquia
            for (string relStr : reliquiasArray) {
                vector<string> relInfo;
                
                // Dividir a string de relíquia por vírgulas
                pos_attr = 0;
                while ((pos_attr = relStr.find(",")) != string::npos) {
                    attr = relStr.substr(0, pos_attr);
                    relInfo.push_back(attr);
                    relStr.erase(0, pos_attr + 1);
                }
                relInfo.push_back(relStr);
                
                if (relInfo.size() >= 4) {
                    ReliquiaMagica* rel = new ReliquiaMagica(
                        relInfo[0], // nome
                        relInfo[1], // descrição
                        stoi(relInfo[2]) // magia mínima
                    );
                    rel->setBuffEnergia(stoi(relInfo[3])); // buff energia
                    rel->setBuffHabilidade(stoi(relInfo[4])); // buff habilidade
                    rel->setBuffResistencia(stoi(relInfo[5])); // buff resistência
                    rel->setBuffMagia(stoi(relInfo[6])); // buff magia
                    rel->setBuffSorte(stoi(relInfo[7])); // buff sorte
                    p->adicionarReliquiaMagica(rel);
                }
            }
        }
    }

    // Mudar o estado do jogo para a tela padrão
    jogo->mudarEstado(new TelaPadrao(jogo));
    cout << "Jogo carregado com sucesso! Pressione Enter para continuar...\n";
    cin.get();
    
    return;
}