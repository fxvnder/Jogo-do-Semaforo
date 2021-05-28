// Trabalho Pratico de Programação
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

#ifndef CODIGO_JOGO_H
#define CODIGO_JOGO_H

#define TAMANHOX 30

typedef struct Players{
    char UserName[TAMANHOX];
    int PowerUps[2];
}Player;

typedef struct TabuleiroStruct{
    int coluna;
    int linha;
    char simbolo;
}TabuleiroStr;

void StartGame();

#endif //CODIGO_JOGO_H