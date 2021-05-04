# Trabalho Pratico de Programação
# DEIS-ISEC 2020-2021
# João Oliveira, nº 2018012875

cmake_minimum_required(VERSION 3.17)
project(Codigo C)

set(CMAKE_C_STANDARD 99)

add_executable(Codigo main.c utils.c utils.h menus.c menus.h jogo.c jogo.h)