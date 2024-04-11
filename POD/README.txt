Trabalho 1 - POD - Relatório

Introdução:
    Este relatório apresenta a implementação de dois algoritmos de ordenação híbrida: QuickSort com InsertionSort e BucketSort com HeapSort.
    O código segue padrões, incluindo funções e documentações em inglês, além de uma formatação consistente.
    O código implementa ordenação interna e externa, o número que define o uso de memória está definido como MAX_SIZE em file-operations.c, isso pode
    influenciar nos resultados, por favor defina ele antes de rodar o programa.

O porquê de cada algoritmo de ordenação:
    QuickSort com InsertionSort: 
        Este algoritmo é uma fusão eficiente do QuickSort e do InsertionSort. O QuickSort é famoso pela sua eficácia em lidar com grandes conjuntos de dados, 
        enquanto o InsertionSort é notável pela sua eficiência em tratar conjuntos de dados menores. No código em questão, se o tamanho do subarray que 
        precisa ser ordenado é inferior a 100, o algoritmo recorre ao InsertionSort. Se for maior, o QuickSort é acionado. Esta estratégia permite que o 
        algoritmo tire proveito das forças de ambos os métodos de ordenação.

    BucketSort com HeapSort: 
        Este algoritmo é uma combinação do BucketSort e do HeapSort. O BucketSort é um método de ordenação que divide um array em vários ‘baldes’ e, em 
        seguida, ordena cada balde individualmente. Após a ordenação de todos os baldes, os valores são concatenados. No código fornecido, o HeapSort é 
        aplicado após a execução do BucketSort para ordenar o array. O HeapSort é um algoritmo de ordenação baseado em comparação que utiliza uma estrutura 
        de dados binária heap.

Resultados - Os resultados em arquivos com diferentes padrões de ordenação dos números e com 1000000 numeros inteiros são apresentados abaixo:

    Ordenação interna:
        Conjunto de Dados Aleatório:
            QuickSort com InsertionSort:
                Tempo de leitura: 0.053435
                Tempo de ordenação: 0.063741
                Tempo de geração do arquivo ordenado: 0.255877
                Tempo total: 0.373053

            BucketSort com HeapSort:
                Tempo de leitura: 0.074352
                Tempo de ordenação: 0.076796
                Tempo de geração do arquivo ordenado: 0.257270
                Tempo total: 0.408418

        Conjunto de Dados Decrescente:
            QuickSort com InsertionSort:
                Tempo de leitura: 0.068732
                Tempo de ordenação: 0.031090
                Tempo de geração do arquivo ordenado: 0.262613
                Tempo total: 0.362435

            BucketSort com HeapSort:
                Tempo de leitura: 0.058192
                Tempo de ordenação: 0.074161
                Tempo de geração do arquivo ordenado: 0.263991
                Tempo total: 0.396344

    Ordenação externa:
        Conjunto de Dados Aleatório:
            QuickSort com InsertionSort:
                Tempo de leitura: 0.062674
                Tempo de ordenação: 0.055247
                Tempo de geração do arquivo ordenado: 0.269573
                Tempo total: 0.387494

            BucketSort com HeapSort:
                Tempo de leitura: 0.066660
                Tempo de ordenação: 0.089368
                Tempo de geração do arquivo ordenado: 0.259888
                Tempo total: 0.415916

        Conjunto de Dados Decrescente:
            QuickSort com InsertionSort:
                Tempo de leitura: 0.054653
                Tempo de ordenação: 0.036100
                Tempo de geração do arquivo ordenado: 0.299209
                Tempo total: 0.389962

            BucketSort com HeapSort:
                Tempo de leitura: 0.061806
                Tempo de ordenação: 0.064513
                Tempo de geração do arquivo ordenado: 0.262499
                Tempo total: 0.388818

Conclusão:
    Através dos resultados apresentados, é possível observar a eficácia dos algoritmos de ordenação híbrida QuickSort com InsertionSort e 
    BucketSort com HeapSort. Ambos os algoritmos demonstraram ser eficientes para diferentes conjuntos de dados e tamanhos de array. 
    No entanto, a eficiência de cada algoritmo pode variar dependendo do conjunto de dados específico e do tamanho do array. Além disso, a implementação 
    de ordenação interna e externa permitiu uma maior flexibilidade no uso de memória, o que pode ser crucial para conjuntos de dados muito grandes.
    O trabalho foi desenvolvido individualmente e contempla todas especificações citadas no enunciado do moodle.

Para compilar e executar o código execute o seguinte comando:
    gcc -O3 -ansi -g -o main main.c && ./main (caminho para o arquivo desordenado)
