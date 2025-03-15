# Edição de Imagens em C

Este código de edição de imagens em C se destaca pelo uso intensivo de alocações dinâmicas para gerenciar a matriz de pixels e para aplicar operações de filtro. As operações de filtro, como aumento de brilho, alteração do canal de cor, rotação, espelhamento e recorte, são realizadas em uma matriz dinamicamente alocada para armazenar os pixels da imagem.

## Funções Principais

### `create_image_matrix`

A função `create_image_matrix` é responsável por alocar dinamicamente a matriz de pixels, adaptando-se às dimensões da imagem lida do arquivo PPM. As operações de filtro, como aumento de brilho e alteração do canal de cor, são aplicadas dinamicamente em cada pixel da matriz alocada dinamicamente. Para garantir que os valores dos canais de cor permaneçam dentro do intervalo permitido (de 0 a `maxColor`), a função `correct_value` é utilizada.

### Operações de Filtro

Além disso, o código também suporta a alocação dinâmica de uma nova matriz para realizar operações como recorte e escala. Por exemplo, na operação de recorte, uma nova matriz dinamicamente alocada é criada para armazenar a parte recortada da imagem original. Da mesma forma, na operação de escala, uma nova matriz é alocada dinamicamente para armazenar a imagem resultante após a aplicação do fator de escala.

## Gerenciamento de Memória

O código cuidadosamente gerencia essas alocações dinâmicas para garantir que a memória seja utilizada eficientemente e liberada corretamente quando não for mais necessária, evitando vazamentos de memória. O uso extensivo de alocações dinâmicas não apenas permite a manipulação flexível da imagem, mas também contribui para um código mais modular e escalável, facilitando a adição de novas funcionalidades no futuro.
