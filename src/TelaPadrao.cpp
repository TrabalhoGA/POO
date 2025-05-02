#include "../include/TelaPadrao.h"
#include "../include/TelaInicial.h"
#include "../include/TelaBatalha.h"
#include "../include/TelaInventario.h"
#include "../include/Personagem.h"
#include "../include/Arma.h"
#include "../include/ArquivoManager.h"
#include <iostream>
#include <limits>
#include <map>

using namespace std;

TelaPadrao::TelaPadrao(Jogo* jogo) : jogo(jogo) 
{
    isEnigma = false;
    isTelaMercado = false;
    testeSorteFalhou = false;
    srand(static_cast<unsigned int>(time(0))); // Inicializa o gerador de números aleatórios
}

TelaPadrao::~TelaPadrao() 
{
    // Destructor
}

void TelaPadrao::exibirTela() {
    jogo->limparTela();
    jogo->salvarJogo();

    Personagem* jogador = Personagem::getInstance();
    
    string diretorioAtual = jogo->getDiretorioAtual();
    int faseAtual = jogo->getFaseAtual();
    
    // Corrigindo o caminho do arquivo para usar "Arquivos.txt/"
    string caminhoArquivo = "Arquivos.txt/" + diretorioAtual + "/" + diretorioAtual + "_" + to_string(faseAtual) + ".txt";

    // Se estiver em uma página especial, como 'atributos' ou 'mercado':
    if (diretorioAtual == "inicio"){
        if (faseAtual == 1) {
            exibirTelaAtributos(caminhoArquivo);
            return;
        }
    }
    else if (diretorioAtual == "caverna" && faseAtual == 7) {
        Arma* espadaDante = new Arma("Espada de Dante", "Forjada com o sangue do filho de Sparda.", 0, 0, 16);
        jogador->equiparArma(espadaDante);
    }
    else if (diretorioAtual == "floresta" && faseAtual == 6) {
        jogador->setMagia(16);
        Arma* cajadoAncestral = new Arma("Cajado Ancestral", "Feito com os galhos da arvore sagrada.", 0, 0,jogador->getMagia());
        jogador->equiparArma(cajadoAncestral);
    }
    
    if (this->isTelaMercado) {
        exibirTelaMercado(caminhoArquivo);
        return;
    }

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    // Usa a função para ler apenas o conteúdo da história (ignorando a primeira linha)
    string conteudo = arquivoManager->lerArquivoHistoria(caminhoArquivo);
    
    cout << conteudo << endl;
    
    if (diretorioAtual == "batalha") {
        cin.get(); // Espera o usuário pressionar Enter antes de continuar
        jogo->mudarEstado(new TelaBatalha(jogo));
        return;
    } else if (diretorioAtual == "torre"){
        if (faseAtual == 7 || faseAtual == 8) {
            cin.get();
            jogo->gameOver();
            // Seleciona a opcao 3 da tela inicial (creditos)
            cin.putback('\n');
            cin.putback('3');
            return;
        }
    }
    
    int opcao;
    cin >> opcao;
    cin.ignore();
    
    handleInput(opcao);
}

void TelaPadrao::exibirTelaAtributos(string caminhoArquivo)
{
    int pontosDisponiveis = 12;
    int habilidade = 0;
    int energia = 0;
    int sorte = 0;

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(caminhoArquivo);

    // Exibir o conteúdo do arquivo de atributos
    cout << conteudo << endl;

    // Obter habilidade
    habilidade = 0;
    cout << "Habilidade (1-" << min(pontosDisponiveis, 6) << "): ";
    while (habilidade < 1 || habilidade > min(pontosDisponiveis, 6)) {
        cin >> habilidade;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Digite um número entre 1 e " << min(pontosDisponiveis, 6) << ": ";
            continue;
        }
        if (habilidade < 1 || habilidade > min(pontosDisponiveis, 6)) {
            cout << "Habilidade deve ser entre 1 e " << min(pontosDisponiveis, 6) << ". Tente novamente: ";
        }
    }

    int pontosRestantes = pontosDisponiveis - habilidade;
    cout << "Pontos restantes: " << pontosRestantes << endl;

    // Obter energia
    energia = 0;
    cout << "Energia (1-" << min(pontosRestantes, 12) << "): ";
    while (energia < 1 || energia > min(pontosRestantes, 12)) {
        cin >> energia;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Digite um número entre 1 e " << min(pontosRestantes, 12) << ": ";
            continue;
        }
        if (energia < 1 || energia > min(pontosRestantes, 12)) {
            cout << "Energia deve ser entre 1 e " << min(pontosRestantes, 12) << ". Tente novamente: ";
        }
    }

    pontosRestantes -= energia;
    cout << "Pontos restantes: " << pontosRestantes << endl;

    // A sorte recebe automaticamente os pontos restantes, mas respeita o limite de 6
    sorte = min(pontosRestantes, 6);
    cout << "Sorte definida automaticamente como: " << sorte << endl;

    int habilidadeFinal = habilidade + 6;
    int energiaFinal = energia + 12;
    int sorteFinal = sorte + 6;

    Personagem::getInstance()->setHabilidade(habilidadeFinal);
    Personagem::getInstance()->setMaxEnergia(energiaFinal);
    Personagem::getInstance()->setEnergiaAtual(energiaFinal);
    Personagem::getInstance()->setSorte(sorteFinal);
    cout << "Você está pronto para começar a aventura!" << endl;
    cout << "Pressione Enter para continuar..." << endl;
    cin.ignore();
    cin.get();

    // Avançar para a próxima fase
    jogo->avancarFase();

    return;
}


void TelaPadrao::exibirTelaMercado(string caminhoArquivo)
{
    Personagem* jogador = Personagem::getInstance();
    
    // Se estamos no mercado inicial, damos 50 moedas ao jogador
    if (jogo->getDiretorioAtual() == "inicio" && jogo->getFaseAtual() == 3) {
        jogador->setMoedasDeOuro(50);
    }
    
    string entrada;
    bool comprasFinalizadas = false;

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivoHistoria(caminhoArquivo);
    
    // Exibir o conteúdo do arquivo de mercado
    cout << conteudo << endl;
    
    // Obter informações dos itens do cabeçalho (primeira linha do arquivo)
    string opcoesNavegacao = arquivoManager->lerOpcoesHistoria(caminhoArquivo);
    
    // Verificar se a linha começa com "mercado:"
    if (opcoesNavegacao.substr(0, 8) != "mercado:") {
        cout << "Erro: Arquivo de mercado não está no formato correto." << endl;
        cin.get();
        jogo->avancarFase();
        return;
    }
    
    // Extrair os itens do mercado
    string mercadoStr = opcoesNavegacao.substr(8);
    
    // Dividir a string em itens individuais separados por ';'
    vector<vector<string>> itens;
    size_t pos = 0;
    string itemStr;
    
    while ((pos = mercadoStr.find(';')) != string::npos) {
        itemStr = mercadoStr.substr(0, pos);
        vector<string> itemData;
        
        // Dividir os dados do item por ','
        size_t itemPos = 0;
        while ((itemPos = itemStr.find(',')) != string::npos) {
            itemData.push_back(itemStr.substr(0, itemPos));
            itemStr.erase(0, itemPos + 1);
        }
        if (!itemStr.empty()) {
            itemData.push_back(itemStr);
        }
        
        // Adicionar o item à lista apenas se tiver dados
        if (!itemData.empty()) {
            itens.push_back(itemData);
        }
        
        mercadoStr.erase(0, pos + 1);
    }
    
    // Registrar os itens que já foram comprados para controle de limite
    map<int, int> itensComprados; // itemId -> quantidade comprada
    
    while(!comprasFinalizadas) {
        cout << "\nMoedas restantes: " << jogador->getMoedasDeOuro() << " ouro" << endl;

        if (jogador->getMoedasDeOuro() <= 0) {
            break;
        }

        cin >> entrada;
        
        if (entrada == "FIM" || entrada == "fim") {
            comprasFinalizadas = true;
            continue;
        }
        
        int itemId = 0;
        int quantidade = 0;
        
        try {
            itemId = stoi(entrada);
            cin >> quantidade;
            
            if (quantidade <= 0) {
                cout << "Quantidade inválida. Deve ser maior que zero." << endl;
                continue;
            }
            
            // Verificar se o ID do item é válido (1 a N)
            if (itemId <= 0 || itemId > itens.size()) {
                cout << "Item inválido. Escolha um número de 1 a " << itens.size() << "." << endl;
                continue;
            }
            
        } catch (...) {
            cout << "Entrada inválida. Digite o número do item seguido da quantidade." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        // Dados do item selecionado (ajuste para índice base-0)
        vector<string>& itemData = itens[itemId - 1];
        
        // Verificar se temos dados suficientes
        if (itemData.size() < 3) {
            cout << "Erro: Dados insuficientes para o item." << endl;
            continue;
        }
        
        string nome = itemData[0];
        string descricao = itemData[1];
        string tipoItem = "";
        int preco = 0;
        int limite = 99; // Limite padrão alto se não for especificado
        
        // Pegar o tipo do item, que deve ser um dos últimos campos
        for (int i = itemData.size() - 2; i >= 0; i--) {
            if (itemData[i] == "Arma" || itemData[i] == "Armadura" || 
                itemData[i] == "ReliquiaMagica" || itemData[i] == "Provisao") {
                tipoItem = itemData[i];
                // O preço deve estar antes do tipo
                preco = stoi(itemData[i - 1]);
                // O limite deve estar após o tipo
                if (i + 1 < itemData.size()) {
                    limite = stoi(itemData[i + 1]);
                }
                break;
            }
        }
        
        // Se tipoItem ainda for vazio, algo está errado
        if (tipoItem.empty()) {
            cout << "Erro: Tipo de item não reconhecido." << endl;
            continue;
        }
        
        // Verificar limite do item
        int compradosAnteriormente = itensComprados[itemId];
        if (compradosAnteriormente + quantidade > limite) {
            cout << "Você só pode comprar " << limite << " unidade(s) deste item. ";
            cout << "Já comprou " << compradosAnteriormente << "." << endl;
            continue;
        }
        
        // Verificar se tem dinheiro suficiente
        if (jogador->getMoedasDeOuro() >= preco * quantidade) {
            // Deduzir o dinheiro
            jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - preco * quantidade);
            
            // Criar e adicionar o item ao inventário conforme o tipo
            for (int i = 0; i < quantidade; i++) {
                if (tipoItem == "Arma") {
                    int buffHabilidade = stoi(itemData[4]); // Posição do BuffHabilidade
                    Arma* arma = new Arma(nome, descricao, 0, 0, buffHabilidade);
                    jogador->equiparArma(arma);
                    
                    // Se for uma varinha, também define magia
                    if (nome.find("Varinha") != string::npos) {
                        jogador->setMagia(buffHabilidade);
                    }
                    
                    cout << "Você equipou " << nome << "!" << endl;
                }
                else if (tipoItem == "Armadura") {
                    int buffResistencia = stoi(itemData[4]); // Posição do BuffResistencia
                    Armadura* armadura = new Armadura(nome, descricao, 0, 0, buffResistencia);
                    jogador->equiparArmadura(armadura);
                    cout << "Você equipou " << nome << "!" << endl;
                }
                else if (tipoItem == "ReliquiaMagica") {
                    ReliquiaMagica* reliquia = new ReliquiaMagica(nome, descricao, 0);
                    
                    // Pegar os buffs da reliquia
                    int buff_energia = stoi(itemData[2]);
                    int buff_habilidade = stoi(itemData[3]);
                    int buff_resistencia = stoi(itemData[4]);
                    int buffMagia = stoi(itemData[5]);
                    int buffSorte = stoi(itemData[6]);

                    // Adiciona os buffs à reliquia
                    reliquia->setBuffEnergia(buff_energia);
                    reliquia->setBuffHabilidade(buff_habilidade);
                    reliquia->setBuffResistencia(buff_resistencia);
                    reliquia->setBuffMagia(buffMagia);
                    reliquia->setBuffSorte(buffSorte);
                    
                    // Adiciona a reliquia ao inventário do jogador
                    jogador->adicionarReliquiaMagica(reliquia);
                    
                    // Não precisamos mais definir possuiTocha ou possuiCorda
                    // A verificação agora é feita pela função verificarItem
                }
                else if (tipoItem == "Provisao") {
                    int valorRecuperacao = stoi(itemData[3]);
                    Provisao* provisao = new Provisao(nome, descricao, 0, valorRecuperacao);
                    jogador->adicionarProvisao(provisao);
                }
            }
            
            // Atualizar contagem de itens comprados
            itensComprados[itemId] += quantidade;
            
        } else {
            cout << "Moedas insuficientes para esta compra." << endl;
        }
    }
    
    cout << "\nCompras finalizadas! Você tem " << jogador->getMoedasDeOuro() << " moedas de ouro restantes." << endl;
    cout << "Pressione Enter para continuar sua jornada..." << endl;
    cin.ignore();
    cin.get();
    
    // Avançar para a próxima fase
    jogo->avancarFase();
    isTelaMercado = false; // Resetar o estado de tela de mercado
}

void TelaPadrao::handleInput(unsigned int input) {
    // Se o input for 9, exibe o inventário
    if (input == 9) {
        jogo->mudarEstado(new TelaInventario(jogo));
        return;
    } else if (input == 0) {
        jogo->mudarEstado(new TelaInicial(jogo));
        return;
    }

    // Carregar o diretorio atual e a fase atual do jogo
    string diretorioAtual = jogo->getDiretorioAtual();
    int faseAtual = jogo->getFaseAtual();
    
    // Corrigindo o caminho do arquivo para usar "Arquivos.txt/"
    string caminhoArquivo = "Arquivos.txt/" + diretorioAtual + "/" + diretorioAtual + "_" + to_string(faseAtual) + ".txt";
    
    // Obter as opções de navegação da primeira linha do arquivo
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string opcoesNavegacao = arquivoManager->lerOpcoesHistoria(caminhoArquivo);
    
    // Analisar as opções de navegação - Alocação dinâmica do vetor
    vector<string>* acoes = new vector<string>();
    size_t pos = 0;
    string token;
    while ((pos = opcoesNavegacao.find(';')) != string::npos) {
        token = opcoesNavegacao.substr(0, pos);
        acoes->push_back(token);
        opcoesNavegacao.erase(0, pos + 1);
    }
    
    // Verificar se a opção selecionada pelo usuário é válida
    if (input > 0 && input <= acoes->size()) {
        string acao = (*acoes)[input-1];
        
        // Verificar se é uma mudança de diretório e fase (formato "diretorio:fase")
        size_t separador = acao.find(':'); 
        if (separador != string::npos) {
            // Extrair o novo diretório
            string novoDiretorio = acao.substr(0, separador);

            if (novoDiretorio == "i") { // fazemos isso antes de converter a fase para int, pois o formato é diferente
                // Verifica se o jogador possui o item necessário para avançar
                verificarItem(acao.substr(separador + 1, acao.find(',') - separador - 1), 
                             stoi(acao.substr(acao.find(',') + 1)));
                delete acoes;
                return;
            }
            
            // Extrair a nova fase
            int novaFase = stoi(acao.substr(separador + 1));

            if (novoDiretorio == "s") {
                if (testeSorteFalhou) {
                    // Não é possível testar a sorte novamente se já falhou
                    cout << "Voce ja falhou no teste de sorte. Nao pode tentar novamente." << endl;
                    cout << "Pressione Enter para continuar..." << endl;
                    cin.get();
                    delete acoes; // Liberar memória alocada
                    return;
                }
                testarSorte(novaFase);
                delete acoes; // Liberar memória alocada
                return;
            }
            
            // Mudança de diretório e fase
            jogo->setDiretorioAtual(novoDiretorio);
            jogo->setFaseAtual(novaFase);
        }
        else if (acao == "e"){ // Verifica se a próxima fase é um enigma
            setTelaEnigma(true); 
            jogo->avancarFase(); // Avança para a próxima fase
            delete acoes; // Liberar memória alocada
            return;
        }
        else if (acao == "mercado"){
            isTelaMercado = true; // Define que estamos na tela de mercado
            jogo->avancarFase(); // Avança para a próxima fase
            delete acoes; // Liberar memória alocada
            return;
        }
        else {
            // Avançar o número específico de fases
            int incremento = stoi(acao);
            if(isTelaEnigma()) {
                // Se for um enigma, exibir a tela de sucesso ou falha
                string arquivo = incremento>0?"Desafio_Sucesso.txt":"Desafio_Falha.txt";
                string conteudo = arquivoManager->lerArquivo("Arquivos.txt/" + arquivo);
                // Exibir o conteúdo do arquivo de enigma
                jogo->limparTela();
                cout << conteudo << endl;
                cin.get();
                if (!incremento) {
                    jogo->gameOver();
                    delete acoes; // Liberar memória alocada
                    return; 
                }
                setTelaEnigma(false); // Resetar o estado de tela de enigma
            }

            if (jogo->getDiretorioAtual()=="inicio" && faseAtual == 0 && incremento == 2) {
                Personagem::getInstance()->carregarAtributosAleatoriamente();
            }
    
            jogo->setFaseAtual(faseAtual + incremento);
            testeSorteFalhou = false; // Resetar o estado de teste de sorte falhou
        }
    }
    else {
        delete acoes; // Liberar memória alocada
        return; // Opção inválida, não faz nada
    }

    delete acoes; // Liberar memória alocada
}

bool TelaPadrao::isTelaEnigma() const {
    return isEnigma;
}

void TelaPadrao::setTelaEnigma(bool isEnigma) {
    this->isEnigma = isEnigma;
}

void TelaPadrao::testarSorte(int avancoFase) {
    Personagem* jogador = Personagem::getInstance();
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo;
    string diretorioAtual = jogo->getDiretorioAtual();
    int faseAtual = jogo->getFaseAtual();
    int sorte = jogador->getSorte()*2;
    int resultado = rand() % 40 + 1; // Gera um número aleatório entre 1 e 40
    jogo->limparTela();

    if (resultado <= sorte) {
        // Jogador teve sucesso
        jogo->avancarFase(avancoFase);
        if (jogo->getDiretorioAtual() == "torre") {
			// Se o jogador avançou para a fase da torre, exibe o conteúdo do arquivo de sucesso
			conteudo = arquivoManager->lerArquivo("Arquivos.txt/" + diretorioAtual + "/" + diretorioAtual + "_" + to_string(faseAtual) + "_sucesso.txt");
            if (faseAtual == 5) {
				// Dar amuleto mágico ao jogador
				ReliquiaMagica* amuleto = new ReliquiaMagica("Amuleto de Vergil", "Aumenta muito o dano contra Sparda", 0);
				amuleto->setBuffHabilidade(jogador->getHabilidade()/ 3);
				jogador->adicionarReliquiaMagica(amuleto);
            }
        }
        else {
            conteudo = arquivoManager->lerArquivo("Arquivos.txt/TesteSorte_Vitoria.txt");
        }
    } else {
        // Jogador perde -2 de energia
        testeSorteFalhou = true;
        if (jogador->getEnergiaAtual() > 2) {
            jogador->setEnergiaAtual(jogador->getEnergiaAtual() - 2);
        }
        
		if (jogo->getDiretorioAtual() == "torre") {
			// Se o jogador falhou na fase da torre, exibe o conteúdo do arquivo de falha
			conteudo = arquivoManager->lerArquivo("Arquivos.txt/" + diretorioAtual + "/" + diretorioAtual + "_" + to_string(faseAtual) + "_falha.txt");
            if (faseAtual == 5) {
                jogo->avancarFase(avancoFase);
            }
		} else if (jogo->getDiretorioAtual() == "floresta" && faseAtual == 4) {
            // Se o jogador falhou na fase da floresta 4, avança mesmo assim
            jogo->avancarFase(avancoFase);
            conteudo = arquivoManager->lerArquivo("Arquivos.txt/TesteSorte_Derrota.txt");
            testeSorteFalhou = false;
        }
		else {
			conteudo = arquivoManager->lerArquivo("Arquivos.txt/TesteSorte_Derrota.txt");
		}
    }
	cout << conteudo << endl;
    cin.get(); // Espera o usuário pressionar Enter antes de continuar
    jogo->limparTela();
}

void TelaPadrao::verificarItem(string nomeItem, int avancoFase) {
    Personagem* jogador = Personagem::getInstance();
    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    bool possuiItem = false;
    
    // Verificar na lista de relíquias mágicas do jogador
    vector<ReliquiaMagica*> reliquias = jogador->getReliquiasMagicas();
    for (auto& reliquia : reliquias) {
        if (reliquia->getNome().find(nomeItem) != string::npos) {
            possuiItem = true;
            break;
        }
    }
    
    if (possuiItem) {
        // Jogador possui o item, avança a fase e exibe mensagem de vitória
        jogo->avancarFase(avancoFase);
        
        string arquivoVitoria;

        // Para novos itens, usar um arquivo genérico ou criar novos arquivos conforme necessário
        arquivoVitoria = "Arquivos.txt/" + nomeItem + "_Vitoria.txt";
        
        string conteudo = arquivoManager->lerArquivo(arquivoVitoria);
        
        // Exibe o conteúdo do arquivo de vitória
        jogo->limparTela();
        cout << conteudo << endl;
        cin.get();
    }
    else {
        // Jogador não possui o item, exibe mensagem informando a ausência do item
        cout << "Voce nao possui " << nomeItem << " no inventario!" << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();
    }
}