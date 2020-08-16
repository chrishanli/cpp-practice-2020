//
//  main.c
//  gobang
//
//  Created by Han Li on 23/7/2020.
//  Copyright © 2020 Han Li. All rights reserved.
//

#include <stdio.h>
#include <libgobang_c.h>

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
            printf("%s", out);
        }
        printf("\n");
    }
    printf("\n");
}

void self() {
    GobangGame* game = NewGame();
    int row, col;
    while (!game->winner) {
        printf("%s", "输入您的位置（行 列）");
        scanf("%d %d", &row, &col);
        PlayerMove(game, row, col);
        printGobang(game->game_board, 19);
        // ai move
        AIMove(game);
        printGobang(game->game_board, 19);
    }
}

int main(int argc, const char * argv[]) {
    self();
    return 0;
}
