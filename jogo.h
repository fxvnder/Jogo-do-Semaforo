// Trabalho Pratico de Programação
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

#ifndef CODIGO_JOGO_H
#define CODIGO_JOGO_H

#define TAMANHOX 30

#define TAMANHOMINIMO 3

// struct dos Jogadores

typedef struct Players{
    char UserName[TAMANHOX];
    int PowerUps[2];
}Player;

// struct do tabuleiro

typedef struct TabuleiroStruct{
    int coluna;
    int linha;
    char **tab;
}TabuleiroStr;

void StartGame();

#endif //CODIGO_JOGO_H