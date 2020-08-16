//
//  main.cpp
//  libgobang
//
//  Created by Han Li on 23/7/2020.
//  Copyright © 2020 Han Li. All rights reserved.
//

#include <iostream>
#include <libgobang.h>

void printGobang(const char* board, int size) {
    const char* out;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch (board[i * size + j]) {
                case 0:
                    out = " _ ";
                    break;
                case 1:
                    out = " x ";
                    break;
                default:
                    out = " o ";
                    break;
            }
            std::cout << out;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void self() {
    GobangGame game;
    printGobang(game.getGameBoard(), 19);
    int row, col;
    while (!game.getWinner()) {
        std::cout << "输入您的位置（行 列）";
        std::cin >> row >> col;
        game.playerMove(row, col);
        printGobang(game.getGameBoard(), 19);
        // ai move
        game.AIMove();
        printGobang(game.getGameBoard(), 19);
    }
}

void ai() {
    GobangGame game;
    game.playerMove(10, 10);
    printGobang(game.getGameBoard(), 19);
    while (!game.getWinner()) {
        game.AIMove();
        printGobang(game.getGameBoard(), 19);
        // ai move
        game.AIMove();
        printGobang(game.getGameBoard(), 19);
    }
    if (game.getWinner() == 1) {
        std::cout << "x won." << std::endl;
    } else {
        std::cout << "o won." << std::endl;
    }
}

void interface() {
    self();
}
