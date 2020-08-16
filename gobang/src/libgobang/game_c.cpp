/*
* libgobang based on blupig
* Copyright (C) 2020 Han Li
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define BUILDING_DLL 1

#include <ai/ai_controller.h>
#include <judge/judge.h>
#include <utils/utils.h>
#include <libgobang_c.h>

GobangGame* NewGame() {
    GobangGame* game = new GobangGame;
    
    game->current_player = 1;
    game->winner = game->last_r = game->last_c = 0;
    game->game_board = new char [DEFAULT_GAME_BOARD_SIZE * DEFAULT_GAME_BOARD_SIZE + 1];
    
    return game;
}

Bool AIMove(GobangGame* game) {
    // Judge if anyone wins at current state
    int _winning_player = GobangJudge::winningPlayer(game->game_board);
    if (_winning_player != 0) {
        game->winner = _winning_player;
        game->current_player = game->current_player == 1 ? 2 : 1;
        return YES;
    }

    // Generate the AI move (1 thread)
    int actual_depth, move_r, move_c;
    unsigned int node_count, eval_count, pm_count;
    
    RenjuAIController::generateMove(game->game_board,
                                    game->current_player,
                                    DEFAULT_DEEP,
                                    DEFAULT_TIME_LIM,
                                    &actual_depth,
                                    &move_r,
                                    &move_c,
                                    &node_count,
                                    &eval_count,
                                    &pm_count);
    
    // Execute the move
    GobangUtils::setCell(game->game_board,
                         move_r, move_c,
                         static_cast<char>(game->current_player));
    game->last_r = move_r;
    game->last_c = move_c;
    
    // Judge if anyone wins at current state
    _winning_player = GobangJudge::winningPlayer(game->game_board);
    if (_winning_player != 0) {
        game->winner = _winning_player;
    }
    
    // Exchange the player
    game->current_player = game->current_player == 1 ? 2 : 1;
    return YES;
}

Bool PlayerMove(GobangGame* game, int move_r, int move_c) {
    // Judge if anyone wins at current state
    int _winning_player = GobangJudge::winningPlayer(game->game_board);
    if (_winning_player != 0) {
        game->winner = _winning_player;
        game->current_player = game->current_player == 1 ? 2 : 1;
        return YES;
    }
    
    // Execute the move
    GobangUtils::setCell(game->game_board,
                         move_r, move_c,
                         static_cast<char>(game->current_player));
    game->last_r = move_r;
    game->last_c = move_c;
    
    // Judge if anyone wins at current state
    _winning_player = GobangJudge::winningPlayer(game->game_board);
    if (_winning_player != 0) {
        game->winner = _winning_player;
    }
    
    // Exchange the player
    game->current_player = game->current_player == 1 ? 2 : 1;
    
    return YES;
}

