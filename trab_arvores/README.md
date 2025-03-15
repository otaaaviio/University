## Notas de Implementação

### Lista de carros
Foi utilizada uma estrutura de lista encadeada para manter a lista de carros. Cada nó da lista contém informações sobre a placa, marca e ano do carro. Foram implementadas três árvores binárias para atender aos requisitos de ordenação: uma árvore relativa à placa, uma árvore relativa à marca e uma árvore relativa ao ano dos carros.

### Inclusão e Exclusão de Carros
Para incluir carros na lista, o programa oferece uma função `insert` na classe `List` que ordena os carros na lista de acordo com suas placas. A exclusão de carros é realizada através da função `remove`, também na classe `List`, que busca o carro pela placa e o remove da lista.

### Árvores Auxiliares
A árvore relativa à placa dos carros é criada e mantida atualizada à medida que os carros são inseridos ou removidos da lista. As árvores relativas à marca e ao ano dos carros são criadas separadamente a partir da lista ordenada por esses critérios.

### Ordenação e Busca
A ordenação da lista de carros é realizada pela placa, marca e ano, conforme especificado nos requisitos. A busca por carros é implementada usando a árvore relativa à placa, permitindo a rápida localização de carros específicos.

### Instruções de Compilação e Execução
Para compilar e executar o programa, o código é o seguinte:
```sh
g++ exe.cpp -o exe && ./exe
```

### Finalização
Diante do relatório apresentado, é evidente que todas as especificações do trabalho foram devidamente implementadas. O programa gerencia a lista de carros de acordo com os critérios estabelecidos no enunciado.
