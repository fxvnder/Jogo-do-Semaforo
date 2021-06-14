// Trabalho Pratico de Programação
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

#include <stdbool.h>

#ifndef CODIGO_JOGO_H
#define CODIGO_JOGO_H

#define TAMANHOX 30

// #define TAMANHOMINIMO 3

// struct dos Jogadores

typedef struct Players{
    bool isBot;
    char UserName[TAMANHOX];
    int PowerUps[2]; // [1] = nPedras ... [2] = AumentoTamanho
}Player;

// struct do tabuleiro

typedef struct TabuleiroStruct{
    int coluna;
    int linha;
    char **tab;
}TabuleiroStr;

void menu();

void limparMemoriaTab(TabuleiroStr tabuleiroJogo);

void StartGame();

#endif //CODIGO_JOGO_H
