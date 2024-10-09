cmake_minimum_required(VERSION 3.21)
project(Prog_MariaAbreu_2020130937 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Prog_MariaAbreu_2020130937
        guardaJogadas.c
        guardaJogadas.h
        interromperJogo.c
        interromperJogo.h
        jogo.c
        jogo.h
        main.c
        menus.c
        menus.h
        tabuleiro.c
        tabuleiro.h
        utils.c
        utils.h)
