// Trabalho Pratico de Programação
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

#include <stdio.h>
//#include <conio.h> - getch()? nah. getchar() supremacy. Digam não ao conio.h
#include "menus.h"

// decidi acabar por nao usar estas figuras pois podem dar problemas com alguns compiladores :(

void MenuInicial(){
    //printf(R"EOF(
    //                   ##
    //                 [DEIS]
    //                _[ISEC]_
    //             .2020'  '2021.
    //         .===|    .==.    |===.
    //         \   |   /    \   |   /
    //         /   |   \    /   |   \
    //         '===|    `""`    |==='
    //         .===|    .==.    |===.
    //         \   |   /    \   |   /
    //         /   |   \    /   |   \
    //         '===|    `""`    |==='
    //         .===|    .==.    |===.
    //         \   |   /    \   |   /
    //         /   |   \    /   |   \
    //         '===|    `""`    |==='
    //             '--.______.--'
    //)EOF");

    printf("\nBem vindo ao jogo do semaforo!\n");
    printf("\nSelecione\n\n1 - Novo Jogo\n2 - Carregar Jogo\n3 - Ajuda\n9 - Sair\n>");
}

void ComandoAjuda(){
    //printf(R"EOF(
    //                            JOGO DO SEMAFORO
    //                            by Joao Oliveira
    //                            ISEC 2020 / 2021

    //    O jogo do semaforo desenrola-se num tabuleiro dividido em celulas.
    //    No inicio, o tabuleiro esta vazio. Alternadamente os jogadores vao jogando
    //pecas de cor Verde, Amarela ou Vermelha.
    //    Ganha o jogador que coloque uma peca que permita formar uma linha, coluna ou
    //diagonal completa com pecas da mesma cor.
    //    As pecas irao mudar sempre na ordem: Sem peca > Verde > Amarela > Vermelha
    //    Duas jogadas adicionais que podem ser efetuadas:
    //        - Colocar uma pedra numa celula vazia (max. 1x/jogador)
    //        - Adicionar uma linha ou coluna no fim do tabuleiro (max. 2x/jogador)
    //)EOF");

    printf("\n\nJOGO DO SEMAFORO\nby Joao Oliveira - 2018012875\nISEC 2020 / 2021");
    printf("\n\nO jogo do semaforo desenrola-se num tabuleiro dividido em celulas.");
    printf("\nNo inicio, o tabuleiro esta vazio. Alternadamente os jogadores vao jogando pecas de cor Verde, Amarela ou Vermelha.");
    printf("\nGanha o jogador que coloque uma peca que permita formar uma linha, coluna ou diagonal completa com pecas da mesma cor.");
    printf("\nAs pecas irao mudar sempre na ordem: Sem peca > Verde > Amarela > Vermelha");
    printf("\n\nDuas jogadas adicionais que podem ser efetuadas:");
    printf("\n - Colocar uma pedra numa celula vazia (max. 1x/jogador)");
    printf("\n - Adicionar uma linha ou coluna no fim do tabuleiro (max. 2x/jogador)");

    getchar();
    printf("\n\n");
    MenuInicial();
}