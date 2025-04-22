# Documentação do Projeto POO

Este projeto implementa um sistema de personagem com itens, equipamentos e armaduras, utilizando conceitos de Programação Orientada a Objetos.

## Classes

### Item

Classe abstrata para os itens do jogo.

#### Atributos:
- `nome`: Nome do item
- `descricao`: Descrição detalhada do item
- `magia_minima_necessaria`: Nível mínimo de magia que o jogador precisa para usar o item

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual
- `exibir_atributos`: Método virtual puro para forçar a implementação nas classes derivadas

### Provisao

Subclasse de Item que representa itens consumíveis no jogo.

#### Atributos:
- Herda todos os atributos da classe Item
- `bonus_energia`: Quantidade de energia que a provisão recupera quando consumida

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, magia mínima necessária e bônus de energia
- `exibir_atributos`: Exibe a quantidade de energia que a provisão recupera

### ReliquiaMagica

Subclasse de Item que representa relíquias mágicas especiais que concedem buffs aos atributos do jogador.

#### Atributos:
- Herda todos os atributos da classe Item
- `buff_energia`: Buff de energia que a relíquia proporciona ao jogador
- `buff_habilidade`: Buff de habilidade que a relíquia proporciona ao jogador
- `buff_resistencia`: Buff de resistência que a relíquia proporciona ao jogador
- `buff_magia`: Buff de magia que a relíquia proporciona ao jogador
- `buff_sorte`: Buff de sorte que a relíquia proporciona ao jogador

#### Métodos:
- Getters e setters para todos os atributos específicos
- Construtor que inicializa nome, descrição e magia mínima necessária
- `exibir_atributos`: Exibe todos os buffs que a relíquia proporciona

### Monstro

Classe que representa os inimigos do jogo.

#### Atributos:
- `nome`: Nome do monstro
- `energia`: Pontos de vida do monstro
- `habilidade`: Nível de habilidade de combate do monstro
- `resistencia`: Capacidade de resistir a danos

#### Métodos:
- Getters e setters para todos os atributos
- Construtor que inicializa nome, energia, habilidade e resistência
- Destrutor virtual

### Equipamento

Classe abstrata para os equipamentos do jogo.

#### Atributos:
- `nome`: Nome do equipamento
- `descricao`: Descrição detalhada do equipamento
- `habilidade_minima_necessaria`: Nível mínimo de habilidade que o jogador precisa para usar o equipamento
- `resistencia_minima_necessaria`: Nível mínimo de resistência que o jogador precisa para usar o equipamento

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual
- `evoluir_equipamento`: Método virtual puro para forçar a implementação nas classes derivadas

### Arma

Subclasse de Equipamento que representa especificamente as armas no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_habilidade`: Buff de habilidade que a arma proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, habilidade mínima, resistência mínima, e buff de habilidade
- `evoluir_equipamento`: Permite melhorar o buff de habilidade da arma

### Armadura

Subclasse de Equipamento que representa especificamente as armaduras no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_resistencia`: Buff de resistência que a armadura proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, requisitos mínimos e buff de resistência
- `evoluir_equipamento`: Permite melhorar o buff de resistência da armadura

### Personagem

Classe que representa o personagem jogável, implementada usando o padrão de projeto Singleton com Lazy Initialization.

#### Padrão Singleton:
- Garante que exista apenas uma instância do Personagem em toda a aplicação
- Implementa Lazy Initialization, que cria a instância apenas quando necessário
- Fornece um ponto global de acesso à instância única através do método `getInstance()`

#### Atributos:
- `max_energia`: Energia máxima do personagem
- `energia_atual`: Energia atual do personagem
- `habilidade`: Nível de habilidade e dano do personagem
- `resistencia`: Capacidade de resistir a danos
- `magia`: Poder mágico do personagem
- `sorte`: Influencia eventos aleatórios a favor do personagem
- `moedas_de_ouro`: Moeda do jogo
- `armadura`: Referência para a armadura equipada pelo jogador
- `arma`: Referência para a arma equipada pelo jogador
- `provisoes`: Vetor que referencia as provisões no inventário do jogador
- `reliquias_magicas`: Vetor que referencia as relíquias mágicas do jogador
- `instance`: Atributo estático que armazena a referência para a única instância do personagem (Singleton)

#### Métodos:
- Construtor privado para implementar o padrão Singleton
- `getInstance()`: Método estático que retorna a instância única do personagem (cria se não existir)
- `resetInstance()`: Reset da instância para um novo jogo
- `releaseInstance()`: Libera a instância e os recursos alocados
- Getters e setters para todos os atributos
- `equiparArmadura`: Permite equipar uma armadura ao personagem
- `getArmadura`: Retorna a armadura atualmente equipada
- `equiparArma`: Permite equipar uma arma ao personagem
- `getArma`: Retorna a arma atualmente equipada
- `adicionarProvisao`: Adiciona a provisão ao inventário do jogador
- `removerProvisao`: Remove a provisão do inventário do jogador
- `getProvisoes`: Retorna todas as provisões que estão no inventário do jogador
- `adicionarReliquiaMagica`: Adiciona uma relíquia mágica ao jogador
- `removerReliquiaMagica`: Remove uma relíquia mágica do jogador
- `getReliquiasMagicas`: Retorna todas as relíquias mágicas do jogador

### Jogo

Classe que gerencia o fluxo principal do jogo, implementada usando o padrão Singleton.

#### Padrão Singleton:
- Garante que exista apenas uma instância do Jogo em toda a aplicação
- Fornece acesso global à instância através do método `getInstance()`

#### Atributos:
- `instance`: Atributo estático que armazena a referência para a única instância do jogo (Singleton)
- `estadoAtual`: Referência para o estado atual do jogo (tela que está sendo exibida)
- `diretorioAtual`: Diretório atual do jogo, usado para localização de arquivos
- `faseAtual`: Fase atual em que o jogador se encontra

#### Métodos:
- Construtor privado para implementar o padrão Singleton
- `getInstance()`: Método estático que retorna a instância única do jogo
- `resetInstance()`: Reset da instância para um novo jogo
- `releaseInstance()`: Libera a instância e os recursos alocados
- `exibirTela()`: Exibe a tela atual do jogo
- `handleInput()`: Processa a entrada do usuário
- `mudarEstado()`: Altera o estado atual do jogo para uma nova tela
- `setDiretorioAtual()`: Define o diretório atual do jogo
- `getDiretorioAtual()`: Retorna o diretório atual do jogo
- `getEstadoAtual()`: Retorna o estado atual do jogo
- `getFaseAtual()`: Retorna a fase atual do jogo
- `setFaseAtual()`: Define a fase atual do jogo
- `avancarFase()`: Avança o jogo para a próxima fase
- `limparTela()`: Limpa o terminal para uma nova exibição
- `salvarJogo()`: Salva o progresso atual do jogo

### TelaEstado

Classe abstrata que define a interface para os diferentes estados (telas) do jogo, seguindo o padrão State.

#### Padrão State:
- Permite que o objeto altere seu comportamento quando seu estado interno muda
- Encapsula estados em classes separadas e delega o trabalho ao objeto de estado atual

#### Métodos:
- Destrutor virtual
- `exibirTela()`: Método virtual puro para exibir o conteúdo da tela
- `handleInput()`: Método virtual puro para processar a entrada do usuário na tela atual

### TelaInicial

Subclasse de TelaEstado que representa a tela inicial do jogo.

#### Atributos:
- `jogo`: Referência para a instância do jogo

#### Métodos:
- Construtor que recebe uma referência para o objeto Jogo
- `exibirTela()`: Exibe o menu principal do jogo
- `handleInput()`: Processa a entrada do usuário na tela inicial
- `exibirCreditos()`: Exibe os créditos do jogo
- `carregarJogo()`: Carrega um jogo salvo anteriormente

### TelaPadrao

Subclasse de TelaEstado que representa as telas padrão do jogo durante a aventura.

#### Atributos:
- `jogo`: Referência para a instância do jogo

#### Métodos:
- Construtor que recebe uma referência para o objeto Jogo
- `exibirTela()`: Exibe o conteúdo da tela atual da aventura
- `handleInput()`: Processa a entrada do usuário durante a aventura
- `exibirTelaAtributos()`: Exibe os atributos do personagem
- `exibirTelaMercado()`: Exibe a interface do mercado para compra de itens
- `exibirMercadorTorre()`: Exibe a interface do mercador na torre

### TelaInventario

Subclasse de TelaEstado que representa a tela de inventário do personagem.

#### Atributos:
- `jogo`: Referência para a instância do jogo

#### Métodos:
- Construtor que recebe uma referência para o objeto Jogo
- `exibirTela()`: Exibe o conteúdo do inventário do personagem
- `handleInput()`: Processa a entrada do usuário na tela de inventário
- `usarItem()`: Método privado para usar um item selecionado

### ArquivoManager

Classe responsável pelo gerenciamento de operações de leitura e escrita de arquivos no jogo, implementada usando o padrão de projeto Singleton.

#### Padrão Singleton:
- Garante que exista apenas uma instância do ArquivoManager em toda a aplicação
- Fornece um ponto global de acesso à instância única através do método `getInstance()`

#### Atributos:
- `instance`: Atributo estático que armazena a referência para a única instância do ArquivoManager (Singleton)

#### Métodos:
- Construtor privado para implementar o padrão Singleton
- `getInstance()`: Método estático que retorna a instância única do ArquivoManager (cria se não existir)
- `lerArquivo(const string& caminho)`: Lê todo o conteúdo de um arquivo e retorna como string
- `lerArquivoHistoria(const string& caminho)`: Lê o conteúdo de um arquivo de história ignorando a primeira linha (opções de navegação)
- `lerOpcoesHistoria(const string& caminho)`: Lê apenas a primeira linha de um arquivo de história (contendo as opções de navegação)
- `escreverArquivo(const string& caminho, const string& conteudo)`: Escreve o conteúdo fornecido em um arquivo no caminho especificado