#include "../include/TelaPadrao.h"
#include "../include/TelaInicial.h"
#include "../include/TelaBatalha.h"
#include "../include/TelaInventario.h"
#include "../include/Personagem.h"
#include "../include/Arma.h"
#include "../include/ArquivoManager.h"
#include <iostream>
#include <limits>

using namespace std;

TelaPadrao::TelaPadrao(Jogo* jogo) : jogo(jogo) 
{
    isEnigma = false;
	possuiTocha = false;
    possuiCorda = false;
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
        else if (faseAtual == 3) {
            exibirTelaMercado(caminhoArquivo);
            return;
        }
    } 
    else if (diretorioAtual == "torre") {
        if (faseAtual == 2) {
            exibirMercadorTorre(caminhoArquivo);
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
    cout << "Pontos restantes: " << pontosRestantes << endl;    
    // A sorte recebe automaticamente os pontos restantes
    sorte = pontosRestantes;
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
    int moedas = 50; // Começamos com 50 moedas
    jogador->setMoedasDeOuro(moedas);
    string entrada;
    bool comprasFinalizadas = false;

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(caminhoArquivo);
    
    // Exibir o conteúdo do arquivo de mercado
    cout << conteudo << endl;

    // Limites para itens únicos
    bool temEspada = false;
    bool temVarinha = false;
    bool temTocha = false;

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
        } catch (...) {
            cout << "Entrada inválida. Digite o número do item seguido da quantidade." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        // Verificar qual item foi selecionado e processar a compra
        switch(itemId) {
            case 1: // Espada de Ferro - 20 ouro
                if (temEspada) {
                    cout << "Você já comprou uma Espada de Ferro. Limite: 1" << endl;
                } else if (quantidade > 1) {
                    cout << "Você só pode comprar 1 Espada de Ferro." << endl;
                } else if (jogador->getMoedasDeOuro() >= 20 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 20 * quantidade);
                    Arma* espada = new Arma("Espada de Ferro", "Aumenta sua chance de sucesso em combates físicos", 0, 0, 8);
                    jogador->equiparArma(espada);
                    temEspada = true;
                    cout << "Você comprou uma Espada de Ferro!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 2: // Varinha de Feitiços - 20 ouro
                if (temVarinha) {
                    cout << "Você já comprou uma Varinha de Feitiços. Limite: 1" << endl;
                } else if (quantidade > 1) {
                    cout << "Você só pode comprar 1 Varinha de Feitiços." << endl;
                } else if (jogador->getMoedasDeOuro() >= 20 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 20 * quantidade);
					jogador->setMagia(8);
                    Arma* varinha = new Arma("Varinha de Feitiços", "Pode ser usada em situações mágicas e contra inimigos arcanos", 0,0, jogador->getMagia());
					jogador->equiparArma(varinha);
                    temVarinha = true;
                    cout << "Você comprou uma Varinha de Feitiços!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 3: // Corda Mágica - 5 ouro
                if (jogador->getMoedasDeOuro() >= 5 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 5 * quantidade);
                    for (int i = 0; i < quantidade; i++) {
                        ReliquiaMagica* corda = new ReliquiaMagica("Corda Mágica", "Útil para atravessar lugares perigosos ou escapar de armadilhas", 0);
                        jogador->adicionarReliquiaMagica(corda);
						possuiCorda = true; // Atualiza o status de possuir a corda
                    }
                    cout << "Você comprou " << quantidade << " Corda(s) Mágica(s)!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 4: // Tocha Eterna - 5 ouro
                if (temTocha) {
                    cout << "Você já comprou uma Tocha Eterna. Limite: 1" << endl;
                } else if (quantidade > 1) {
                    cout << "Você só pode comprar 1 Tocha Eterna." << endl;
                } else if (jogador->getMoedasDeOuro() >= 5 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 5 * quantidade);
                    ReliquiaMagica* tocha = new ReliquiaMagica("Tocha Eterna", "Ilumina locais escuros e pode afugentar criaturas", 0);
                    jogador->adicionarReliquiaMagica(tocha);
                    temTocha = true;
					possuiTocha = true;
                    cout << "Você comprou uma Tocha Eterna!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 5: // Poção de Vida - 10 ouro
                if (jogador->getMoedasDeOuro() >= 10 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 10 * quantidade);
                    for (int i = 0; i < quantidade; i++) {
                        Provisao* pocaoVida = new Provisao("Poção de Vida", "Recupera todo o seu vigor e disposição durante a aventura", 0, jogador->getMaxEnergia());
                        jogador->adicionarProvisao(pocaoVida);
                    }
                    cout << "Você comprou " << quantidade << " Poção(ões) de Vida!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 6: // Frasco de Energia - 5 ouro
                if (jogador->getMoedasDeOuro() >= 5 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 5 * quantidade);
                    for (int i = 0; i < quantidade; i++) {
                        Provisao* frascoEnergia = new Provisao("Frasco de Energia", "Recupera parte da sua energia", 0, int(jogador->getMaxEnergia() / 2)); // Recupera metade da energia máxima
                        jogador->adicionarProvisao(frascoEnergia);
                    }
                    cout << "Você comprou " << quantidade << " Frasco(s) de Energia!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            default:
                cout << "Opção inválida. Escolha um número entre 1 e 6." << endl;
                break;
        }
    }
    
    cout << "\nCompras finalizadas! Você tem " << jogador->getMoedasDeOuro() << " moedas de ouro restantes." << endl;
    cout << "Pressione Enter para continuar sua jornada..." << endl;
    cin.ignore();
    cin.get();
    
    // Avançar para a próxima fase
    jogo->avancarFase();
}

void TelaPadrao::exibirMercadorTorre(string caminhoArquivo)
{
    Personagem* jogador = Personagem::getInstance();
    string entrada;
    bool comprasFinalizadas = false;

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(caminhoArquivo);
    
    // Exibir o conteúdo do arquivo do mercador da torre
    cout << conteudo << endl;

    while(!comprasFinalizadas) {
        cout << "\nMoedas restantes: " << jogador->getMoedasDeOuro() << " ouro" << endl;
        
        cin >> entrada;
        
        if (entrada == "FIM" || entrada == "fim" || jogador->getMoedasDeOuro() <= 0) {
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
        } catch (...) {
            cout << "Entrada inválida. Digite o número do item seguido da quantidade." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        // Verificar qual item foi selecionado e processar a compra
        switch(itemId) {
            case 1: // Elixir de Vida - 20 ouro
                if (jogador->getMoedasDeOuro() >= 20 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 20 * quantidade);
                    for (int i = 0; i < quantidade; i++) {
                        Provisao* elixirVida = new Provisao("Elixir de Vida", "Recupera totalmente sua ENERGIA atual", 0, jogador->getMaxEnergia());
                        jogador->adicionarProvisao(elixirVida);
                    }
                    cout << "Você comprou " << quantidade << " Elixir(es) de Vida!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 2: // Armadura de Ferro - 40 ouro
                if (quantidade > 1) {
                    cout << "Você só pode comprar 1 Armadura de Ferro." << endl;
                } else if (jogador->getMoedasDeOuro() >= 40) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 40);
                    Armadura* armaduraFerro = new Armadura("Armadura de Ferro", "Aumenta sua RESISTÊNCIA em combate", 0, 0, 5);
                    jogador->equiparArmadura(armaduraFerro);
                    cout << "Você comprou uma Armadura de Ferro!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 3: // Amuleto Mágico - 40 ouro
                if (quantidade > 1) {
                    cout << "Você só pode comprar 1 Amuleto Mágico." << endl;
                } else if (jogador->getMoedasDeOuro() >= 40) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 40);
                    ReliquiaMagica* amuletoMagico = new ReliquiaMagica("Amuleto Mágico", "Aumenta sua SORTE e sua MAGIA em +15 pontos", 0);
                    amuletoMagico->setBuffSorte(15);
                    amuletoMagico->setBuffMagia(15);
                    jogador->adicionarReliquiaMagica(amuletoMagico);
                    cout << "Você comprou um Amuleto Mágico!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            default:
                cout << "Opção inválida. Escolha um número entre 1 e 3." << endl;
                break;
        }
    }
    
    cout << "\nCompras finalizadas! Voce tem " << jogador->getMoedasDeOuro() << " moedas de ouro restantes." << endl;
    cout << "Pressione Enter para continuar sua jornada..." << endl;
    cin.get();
    
    // Avançar para a próxima fase
    jogo->avancarFase();
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
            string novoDiretorio = acao.substr(0, separador);
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
            jogo->setFaseAtual(faseAtual + 1);
            delete acoes; // Liberar memória alocada
            return;
        }
        else if (acao == "t") { // Verifica se a próxima fase é um teste de tocha
            acaoTocha(possuiTocha);
            delete acoes; // Liberar memória alocada
            return;
        }
        else if (acao == "c") { // Verifica se a próxima fase é um teste de corda
            acaoCorda(possuiCorda);
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

void TelaPadrao::acaoTocha(bool possuiTocha) {
    if (possuiTocha) {
        // Jogador possui a tocha, avança a fase e exibe mensagem de vitória
        jogo->avancarFase();
        ArquivoManager* arquivoManager = ArquivoManager::getInstance();
        string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Tocha_Vitoria.txt");

        // Exibe o conteúdo do arquivo de vitória
        jogo->limparTela();
        cout << conteudo << endl;
        cin.get(); 
    }
    else {
        // Jogador não possui a tocha, exibe mensagem informando a ausência do item
        cout << "Voce nao possui uma tocha no inventario!" << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();
    }
}
void TelaPadrao::acaoCorda(bool possuiCorda) {
    if (possuiCorda) {
        // Jogador possui a corda, avança a fase e exibe mensagem de vitória
        jogo->avancarFase(2);
        ArquivoManager* arquivoManager = ArquivoManager::getInstance();
        string conteudo = arquivoManager->lerArquivo("Arquivos.txt/Corda_Vitoria.txt");

        // Exibe o conteúdo do arquivo de vitória
        jogo->limparTela();
        cout << conteudo << endl;
        cin.get();
    }
    else {
        // Jogador não possui a tocha, exibe mensagem informando a ausência do item
        cout << "Voce nao possui uma corda no inventario!" << endl;
        cout << "Pressione Enter para continuar..." << endl;
        cin.get();
    }
}