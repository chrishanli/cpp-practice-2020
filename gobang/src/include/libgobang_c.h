/*
* libgobang
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

#ifndef libgobang_c_h
#define libgobang_c_h

#define DEFAULT_DEEP -1
#define DEFAULT_TIME_LIM 500
#define DEFAULT_GAME_BOARD_SIZE 19

#define YES 1
#define NO 0

#ifdef USING_DLL
#define DLLPORT _declspec(dllimport)
#elif BUILDING_DLL
#define DLLPORT _declspec(dllexport)
#else
#define DLLPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /// the game board (19 * 19 by default)
    char *game_board;
    
    /// the winner (1 or 2, 0 indicates no one wins)
    int winner;
    
    /// indicates current player (1 or 2)
    int current_player;
    
    /// last move
    int last_r, last_c;
} GobangGame;

typedef char Bool;

/// Allocates a new gobang game object
DLLPORT GobangGame* NewGame(void);

/// Automatically judges a move due to current state
/// @param game the game object
DLLPORT Bool AIMove(GobangGame* game);

/// Set a move by a player
/// @param move_r the place's row
/// @param move_c the place's column
/// @param game the game object
DLLPORT Bool PlayerMove(GobangGame* game, int move_r, int move_c);

/// Destroys a given gobang game object
/// @param game the game object
DLLPORT void DestroyGame(GobangGame* game);

/// Restart a given gobang game object
/// @param game the game object
DLLPORT void RestartGame(GobangGame* game);

/// Extracts the winner (if any) from a given game
/// @param game the game object
DLLPORT int GetWinner(GobangGame* game);

/// Extracts the row index of the last move from a given game
/// @param game the game object
DLLPORT int GetLastRow(GobangGame* game);

/// Extracts the column index of the last move from a given game
/// @param game the game object
DLLPORT int GetLastCol(GobangGame* game);

/// Extracts the current player (if any) from a given game
/// @param game the game object
DLLPORT int GetCurrentPlayer(GobangGame* game);

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* libgobang_c_h */
