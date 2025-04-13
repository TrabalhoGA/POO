# Documentação do Projeto POO

Este projeto implementa um sistema de personagem com equipamentos e armaduras, utilizando conceitos de Programação Orientada a Objetos.

## Classes

### Equipamento

Classe base que representa itens de equipamento genéricos no jogo.

#### Atributos:
- `nome`: Nome do equipamento
- `descricao`: Descrição detalhada do equipamento
- `habilidade_minima_necessaria`: Nível mínimo de habilidade que o jogador precisa para usar o equipamento
- `resistencia_minima_necessaria`: Nível mínimo de resistência que o jogador precisa para usar o equipamento

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual

### Armadura

Subclasse de Equipamento que representa especificamente as armaduras no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_resistencia`: Bônus de resistência que a armadura proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, requisitos mínimos e buff de resistência
- `evoluirArmadura`: Permite melhorar o buff de resistência da armadura

### Player

Classe que representa o personagem jogável.

#### Atributos:
- `energia`: Pontos de vida do personagem
- `habilidade`: Nível de habilidade para usar equipamentos e realizar ações
- `resistencia`: Capacidade de resistir a danos
- `magia`: Poder mágico do personagem
- `sorte`: Influencia eventos aleatórios a favor do personagem
- `moedas_de_ouro`: Moeda do jogo
- `armadura`: Referência para a armadura equipada pelo jogador

#### Métodos:
- Getters e setters para todos os atributos
- Construtor que inicializa os atributos base do personagem
- `equiparArmadura`: Permite equipar uma armadura ao personagem
- `getArmadura`: Retorna a armadura atualmente equipada