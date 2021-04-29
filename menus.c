// Trabalho Pratico de P
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

#include <stdio.h>
#include "menus.h"

void MenuInicial(){
    printf(R"EOF(
                       ##
                    _[DEIS]_
                     [ISEC]
                 .2020'  '2021.
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
                 '--.______.--'
    )EOF");

    printf("Bem vindo ao jogo do semaforo!\n");
    printf("Selecione\n\n1 - Novo Jogo\n2 - Carregar Jogo\n3 - Sair\n>");
}