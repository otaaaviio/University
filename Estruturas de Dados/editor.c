#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int typePPM;
    int side_x, side_y;
    int maxColor;
} tPPMFile;

typedef struct
{
    int R, G, B;
} color;

char *skip_comments(char *buffer)
{
    do
    {
        fgets(buffer, 256, stdin);
    } while (buffer[0] == '#');
    return buffer;
}

void check_PPM_File(tPPMFile *f)
{
    bool valid = true;
    char buffer[256];
    fgets(buffer, 256, stdin);
    if (buffer[0] != 'P' || (buffer[1] != '2' && buffer[1] != '3'))
        valid = false;
    f->typePPM = buffer[1] - '0';
    skip_comments(buffer);
    if (sscanf(buffer, "%d %d", &f->side_x, &f->side_y) == EOF)
        valid = false;
    skip_comments(buffer);
    if (sscanf(buffer, "%d", &f->maxColor) == EOF)
        valid = false;

    if (valid)
    {
        printf("Arquivo válido.\n\n");
    }
    else
    {
        printf("Arquivo inválido.\n\n");
        exit(1);
    }
}

void print_PPM_File(tPPMFile *f)
{
    fprintf(stdout, "P%d\n#gerado por <filtro.c>\n%d %d\n%d\n", f->typePPM, f->side_x, f->side_y, f->maxColor);
    // implement
}

void filter() {}

void clipping() {}

void clip() {}

void scale() {}

void select_subset() {}

void main_menu()
{
    int select;
    printf("(1) Operações de filtro\n(2) Operação de recorte\n(3) Operação de colar\n(4) Operação de escala\n(5) Selecionar subconjunto da imagem para realizar operação\nDigite qual operação você quer realizar:");
    scanf(" %d", &select);

    switch (select)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    default:
        printf("Operação inválida.");
        return;
    }
}

int main(int argc, char *argv[])
{
    tPPMFile PPMFile;
    check_PPM_File(&PPMFile);

    main_menu();

    exit(0);
}