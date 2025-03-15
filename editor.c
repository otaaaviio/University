#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int typePPM;
    int width, height;
    int maxColor;
    int clipped_width;
    int clipped_height;
} tPPMFile;

typedef struct
{
    int R, G, B;
} color;

void main_menu(tPPMFile *f, color **image);
void menu_sub_image(tPPMFile *f, color **image);

void clean_screen()
{
    printf("\033[H\033[J");
}

void memory_release(color **image, int height)
{
    for (int i = 0; i < height; i++)
    {
        free(image[i]);
    }

    free(image);
}

FILE *get_filename()
{
    char filename[256];
    printf("Digite o nome do arquivo: ");
    scanf("%255s", filename);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo '%s'\n", filename);
        exit(1);
    }
    return file;
}

int correct_value(tPPMFile *f, int value)
{
    if (value > f->maxColor)
        return f->maxColor;
    if (value < 0)
        return 0;

    return value;
}

char *skip_comments(char *buffer, FILE *file)
{
    do
    {
        fgets(buffer, 256, file);
    } while (buffer[0] == '#');
    return buffer;
}

color **create_image_matrix(int height, int width)
{
    color **image = (color **)malloc(height * sizeof(color *));
    for (int i = 0; i < height; i++)
        image[i] = (color *)malloc(width * sizeof(color));

    return image;
}

void read_color(char **ptr, int *color)
{
    sscanf(*ptr, "%d", color);
    while (**ptr != ' ' && **ptr != '\t' && **ptr != '\n' && **ptr != '\0')
    {
        (*ptr)++;
    }
    while (**ptr == ' ' || **ptr == '\t')
    {
        (*ptr)++;
    }
}

color **check_PPM_File(tPPMFile *f, FILE *file)
{
    bool valid = true;
    char buffer[256];
    fgets(buffer, 256, file);
    if (buffer[0] != 'P' || (buffer[1] != '2' && buffer[1] != '3'))
        valid = false;
    f->typePPM = buffer[1] - '0';
    skip_comments(buffer, file);
    if (sscanf(buffer, "%d %d", &f->height, &f->width) == EOF)
        valid = false;
    skip_comments(buffer, file);
    if (sscanf(buffer, "%d", &f->maxColor) == EOF)
        valid = false;

    skip_comments(buffer, file);
    char *ptr = buffer;
    if (valid)
    {
        printf("Arquivo válido.\n\n");
        color **image = create_image_matrix(f->height, f->width);
        for (int i = 0; i < f->height; i++)
        {
            for (int j = 0; j < f->width; j++)
            {
                read_color(&ptr, &image[i][j].R);
                read_color(&ptr, &image[i][j].G);
                read_color(&ptr, &image[i][j].B);
            }
            fgets(buffer, 256, file);
            ptr = buffer;
        }

        return image;
    }
    else
    {
        printf("Arquivo inválido.\n\n");
        exit(1);
    }
}

void create_PPM_File(const char *filename, int height, int width, color **image, tPPMFile *f)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Erro ao criar o arquivo");
        return;
    }

    fprintf(file, "P%d\n#gerado por <filtro.c>\n%d %d\n%d\n", f->typePPM, height, width, f->maxColor);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fprintf(file, "%d %d %d ", image[i][j].R, image[i][j].G, image[i][j].B);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void increase_brightness(color **image, tPPMFile *f)
{
    int increaseValue;
    clean_screen();
    printf("Digite o valor a aumentar do brilho: ");
    scanf("%d", &increaseValue);
    for (int i = 0; i < f->height; i++)
    {
        for (int j = 0; j < f->width; j++)
        {
            image[i][j].R += increaseValue;
            image[i][j].G += increaseValue;
            image[i][j].B += increaseValue;

            image[i][j].R = correct_value(f, image[i][j].R);
            image[i][j].G = correct_value(f, image[i][j].G);
            image[i][j].B = correct_value(f, image[i][j].B);
        }
    }
}

void change_color_channel(color **image, tPPMFile *f)
{
    int value, select;
    clean_screen();
    printf("(1)Vermelho\n(2)Verde\n(3)Azul\nEscolha qual canal quer alterar: ");
    scanf("%d", &select);
    printf("Digite quanto vc quer alterar: ");
    scanf("%d", &value);

    for (int i = 0; i < f->height; i++)
    {
        for (int j = 0; j < f->width; j++)
        {
            switch (select)
            {
            case 1:
                image[i][j].R += value;
                break;
            case 2:
                image[i][j].G += value;
                break;
            case 3:
                image[i][j].B += value;
                break;
            }

            image[i][j].R = correct_value(f, image[i][j].R);
            image[i][j].G = correct_value(f, image[i][j].G);
            image[i][j].B = correct_value(f, image[i][j].B);
        }
    }
}

void rotation_image(color **image, tPPMFile *f)
{
    int select;
    clean_screen();
    printf("(1)direita\n(2)esquerda\nDigite para qual lado vc quer rotacionar: ");
    scanf("%d", &select);
    color **aux_image = create_image_matrix(f->height, f->width);

    for (int i = 0; i < f->width; i++)
    {
        for (int j = 0; j < f->height; j++)
        {
            if (select == 1)
            {
                aux_image[i][j] = image[f->height - j - 1][i];
            }
            else if (select == 2)
            {
                aux_image[i][j] = image[j][f->width - i - 1];
            }
        }
    }

    int temp = f->width;
    f->width = f->height;
    f->height = temp;

    for (int i = 0; i < f->width; i++)
        for (int j = 0; j < f->height; j++)
            image[i][j] = aux_image[i][j];

    memory_release(aux_image, f->height);
}

void image_mirroring(color **image, tPPMFile *f)
{
    color **aux_image = create_image_matrix(f->height, f->width);

    for (int i = 0; i < f->height; i++)
    {
        for (int j = 0; j < f->width; j++)
        {
            aux_image[i][j] = image[i][f->width - j - 1];
        }
    }

    for (int i = 0; i < f->height; i++)
        for (int j = 0; j < f->width; j++)
            image[i][j] = aux_image[i][j];

    memory_release(aux_image, f->height);
}

void filter(color **image, tPPMFile *f)
{
    int select;
    do
    {
        clean_screen();
        printf("Voce selecionou 'operações de filtro', agora selecione qual filtro quer aplicar: ");
        printf("\n(1)Alterar canal de cor\n(2)Alterar brilho\n(3)Realizar rotação\n(4)Realizar espelhamento\n(5)Voltar para o menu inicial\nDigite qual operação você quer realizar: ");
        scanf("%d", &select);

        while (select > 5 || select < 1)
        {
            printf("Operação inválida, digite novamente: ");
            scanf("%d", &select);
        }

        switch (select)
        {
        case 1:
            change_color_channel(image, f);
            break;
        case 2:
            increase_brightness(image, f);
            break;
        case 3:
            rotation_image(image, f);
            break;
        case 4:
            image_mirroring(image, f);
            break;
        }
    } while (select != 5);
}

color **clipping(color **image, tPPMFile *f)
{
    int _x, _y, x, y;
    clean_screen();
    printf("Informe as coordenadas para o corte da imagem. Digite o valor de x inicial, x final, y inicial e y final, separados por espaços:\n");
    scanf("%d %d %d %d", &_x, &x, &_y, &y);
    color **clipped_image = create_image_matrix(x - _x + 1, y - _y + 1);
    for (int i = _x; i <= x; i++)
        for (int j = _y; j <= y; j++)
            clipped_image[i - _x][j - _y] = image[i][j];

    f->clipped_width = x - _x + 1;
    f->clipped_height = y - _y + 1;
    return clipped_image;
}

void clip(color **image, color **clipped_image, tPPMFile *f)
{
    int select, _height, _width;
    clean_screen();
    printf("Se deseja colar um corte realizado no programa anteriormente digite '1', caso deseje colar de algum arquivo secundario digite '2'.\n");
    scanf("%d", &select);

    if (select == 1)
    {
        printf("Digite as coordenadas iniciais aonde deseja colar, a altura final e a largura inicial: ");
        scanf("%d %d", &_height, &_width);
        if (_height + f->clipped_height > f->height || _width + f->clipped_width > f->width)
        {
            printf("Erro: A imagem cortada excede as dimensões da imagem original.\n");
            return;
        }
        for (int i = 0; i < f->height; i++)
            for (int j = 0; j < f->width; j++)
                if (i >= _height && i < _height + f->clipped_height && j >= _width && j < _width + f->clipped_width)
                    image[i][j] = clipped_image[i - _height][j - _width];
    }
    else if (select == 2)
    {
        tPPMFile PPMFile2;
        FILE *file = get_filename();
        color **second_file = check_PPM_File(&PPMFile2, file);

        printf("Digite as coordenadas iniciais aonde deseja colar, a altura final e a largura inicial: ");
        scanf("%d %d", &_height, &_width);
        if (_height + PPMFile2.height > f->height || _width + PPMFile2.width > f->width)
        {
            printf("Erro: A imagem do arquivo secundário excede as dimensões da imagem original.\n");
            memory_release(second_file, PPMFile2.height);
            fclose(file);
            return;
        }
        for (int i = 0; i < f->height; i++)
            for (int j = 0; j < f->width; j++)
                if (i >= _height && i < _height + PPMFile2.height && j >= _width && j < _width + PPMFile2.width)
                    image[i][j] = second_file[i - _height][j - _width];

        memory_release(second_file, PPMFile2.height);
        fclose(file);
    }
}

void scale(color **image, tPPMFile *f)
{
    clean_screen();
    int select, factor, height, width;
    printf("Escolha uma das seguintes opções para ajustar a escala da imagem:\n(1) Aumentar\n(2) Diminuir\nDigite o número da operação desejada: ");
    scanf("%d", &select);

    if (select == 1)
    {
        printf("Você escolheu aumentar a escala.\nDigite o fator de multiplicação desejado(são aceitos apenas multiplos de 2): ");
        scanf("%d", &factor);
        height = f->height * factor;
        width = f->width * factor;
    }
    else if (select == 2)
    {
        printf("Você escolheu diminuir a escala.\nDigite o fator de divisão desejado(são aceitos apenas multiplos de 2): ");
        scanf("%d", &factor);
        height = f->height / factor;
        width = f->width / factor;
    }

    color **scale_image = create_image_matrix(height, width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int original_i = i / factor;
            int original_j = j / factor;
            scale_image[i][j] = image[original_i][original_j];
        }
    }

    printf("Obrigado por utilizar a operação de escala, foi salvo um arquivo chamado 'scale_image.ppm' com as alterações.");
    create_PPM_File("scale_image.ppm", height, width, scale_image, f);

    getchar();
    getchar();

    for (int i = 0; i < height; i++)
        free(scale_image[i]);

    free(scale_image);
}

void select_subset(color **image, tPPMFile *f)
{
    int _x, _y, x, y;
    clean_screen();
    printf("Informe as coordenadas para a seleção de subconjunto de pixels da imagem. Digite o valor de x inicial, x final, y inicial e y final, separados por espaços:\n");
    scanf("%d %d %d %d", &_x, &x, &_y, &y);

    tPPMFile sub_image_type;
    color **sub_image = create_image_matrix(x - _x + 1, y - _y + 1);
    for (int i = _x; i <= x; i++)
        for (int j = _y; j <= y; j++)
            sub_image[i - _x][j - _y] = image[i][j];

    sub_image_type = *f;
    sub_image_type.height = x - _x + 1;
    sub_image_type.width = y - _y + 1;

    menu_sub_image(&sub_image_type, sub_image);

    memory_release(sub_image, x - _x + 1);
}

void menu_sub_image(tPPMFile *f, color **image)
{
    int select;
    color **clipped_image = NULL;
    do
    {
        clean_screen();
        printf("(1) Operações de filtro\n(2) Operação de recorte\n(3) Operação de escala\n(4) Operação de Colar\n(5) Voltar pro menu inicial");
        printf("\nDigite qual operação você quer realizar: ");
        scanf("%d", &select);

        while (select < 0 || select > 6)
        {
            printf("Operação inválida, digite novamente: ");
            scanf("%d", &select);
        }

        switch (select)
        {
        case 1:
            filter(image, f);
            break;
        case 2:
            clipped_image = clipping(image, f);
            break;
        case 3:
            scale(image, f);
            break;
        case 4:
            clip(image, clipped_image, f);
            break;
        }
    } while (select != 5);

    if (clipped_image != NULL)
        memory_release(clipped_image, f->clipped_height);

    printf("Obrigado por utilizar o editor, seu arquivo de saida é 'sub_image.ppm'.\n");
    create_PPM_File("sub_image.ppm", f->height, f->width, image, f);
}

void main_menu(tPPMFile *f, color **image)
{
    int select;
    color **clipped_image = NULL;
    do
    {
        clean_screen();
        printf("(1) Operações de filtro\n(2) Operação de recorte\n(3) Operação de escala\n(4) Operação de Colar\n(5) Selecionar subconjunto da imagem para realizar operação\n(6) Sair do programa");
        printf("\nDigite qual operação você quer realizar: ");
        scanf("%d", &select);

        while (select < 0 || select > 6)
        {
            printf("Operação inválida, digite novamente: ");
            scanf("%d", &select);
        }

        switch (select)
        {
        case 1:
            filter(image, f);
            break;
        case 2:
            clipped_image = clipping(image, f);
            break;
        case 3:
            scale(image, f);
            break;
        case 4:
            clip(image, clipped_image, f);
            break;
        case 5:
            select_subset(image, f);
            break;
        }
    } while (select != 6);

    if (clipped_image != NULL)
        memory_release(clipped_image, f->clipped_height);

    printf("Obrigado por utilizar o editor, seu arquivo de saida é 'image.ppm'.\n");
    create_PPM_File("image.ppm", f->height, f->width, image, f);
}

int main(int argc, char *argv[])
{
    tPPMFile PPMFile;
    FILE *file = get_filename();
    color **image = check_PPM_File(&PPMFile, file);

    main_menu(&PPMFile, image);

    memory_release(image, PPMFile.height);
    fclose(file);
    exit(0);
}