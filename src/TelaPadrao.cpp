#include "../include/TelaPadrao.h"
#include "../include/TelaInicial.h"
#include "../include/Personagem.h"
#include "../include/Arma.h"
#include "../include/ArquivoManager.h"
#include <iostream>
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

void TelaPadrao::exibirTela() {
    jogo->limparTela();
    
    string diretorioAtual = jogo->getDiretorioAtual();
    int faseAtual = jogo->getFaseAtual();
    
    // Corrigindo o caminho do arquivo para usar "Arquivos.txt/"
    string caminhoArquivo = "Arquivos.txt/" + diretorioAtual + "/" + diretorioAtual + "_" + to_string(faseAtual) + ".txt";

    // Se estiver em uma página especial, como 'atributos' ou 'mercado':
    if (diretorioAtual == "inicio"){
        if (faseAtual == 1) {
            exibirTelaAtributos(caminhoArquivo);
            return;
        } else if (faseAtual == 3) {
            exibirTelaMercado(caminhoArquivo);
            return;
        }
    }

    if (diretorioAtual == "caverna" || diretorioAtual == "floresta") {
        if(faseAtual == 5){
            jogo->setDiretorioAtual("torre");
            jogo->setFaseAtual(1);
            return;
        }
    }

    ArquivoManager* arquivoManager = ArquivoManager::getInstance();
    string conteudo = arquivoManager->lerArquivo(caminhoArquivo);
    
    cout << conteudo << endl;
    
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
    bool distribuicaoValida = false;

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

    Personagem::getInstance()->setHabilidade(habilidade);
    Personagem::getInstance()->setEnergiaAtual(energia);
    Personagem::getInstance()->setSorte(sorte);
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
                    Arma* espada = new Arma("Espada de Ferro", "Aumenta sua chance de sucesso em combates físicos.", 0, 0, 5);
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
                    ReliquiaMagica* varinha = new ReliquiaMagica("Varinha de Feitiços", "Pode ser usada em situações mágicas e contra inimigos arcanos.", 0);
                    varinha->setBuffMagia(5); // Adiciona bônus de magia
                    jogador->adicionarReliquiaMagica(varinha);
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
                        ReliquiaMagica* corda = new ReliquiaMagica("Corda Mágica", "Útil para atravessar lugares perigosos ou escapar de armadilhas.", 0);
                        corda->setBuffSorte(2); // Pequeno bônus de sorte
                        jogador->adicionarReliquiaMagica(corda);
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
                    ReliquiaMagica* tocha = new ReliquiaMagica("Tocha Eterna", "Ilumina locais escuros e pode afugentar criaturas.", 0);
                    jogador->adicionarReliquiaMagica(tocha);
                    temTocha = true;
                    cout << "Você comprou uma Tocha Eterna!" << endl;
                } else {
                    cout << "Moedas insuficientes para esta compra." << endl;
                }
                break;
                
            case 5: // Poção de Vida - 10 ouro
                if (jogador->getMoedasDeOuro() >= 10 * quantidade) {
                    jogador->setMoedasDeOuro(jogador->getMoedasDeOuro() - 10 * quantidade);
                    for (int i = 0; i < quantidade; i++) {
                        Provisao* pocaoVida = new Provisao("Poção de Vida", "Recupera todo o seu vigor e disposição durante a aventura.", 0, jogador->getMaxEnergia());
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
                        Provisao* frascoEnergia = new Provisao("Frasco de Energia", "Recupera parte da sua energia.", 0, int(jogador->getMaxEnergia() / 2)); // Recupera metade da energia máxima
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

void TelaPadrao::handleInput(int input) {
    string diretorioAtual = jogo->getDiretorioAtual();
    int faseAtual = jogo->getFaseAtual();
    
    switch (input) {
        case 1: 
            if(diretorioAtual == "inicio" && faseAtual == 4) {
                jogo->setDiretorioAtual("floresta");
                jogo->setFaseAtual(1);
                break;
            }
            jogo->avancarFase();
            break;
        case 2:
            if(diretorioAtual == "inicio" && faseAtual == 4) {
                jogo->setDiretorioAtual("caverna");
                jogo->setFaseAtual(1);
                break;
            }
            jogo->avancarFase();
            break;
        // Outras opcoes a serem implementadas
    }
}