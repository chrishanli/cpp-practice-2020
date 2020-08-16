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

#ifndef libgobang_h
#define libgobang_h

#ifdef USING_DLL
#define DLLPORT _declspec(dllimport)
#elif BUILDING_DLL
#define DLLPORT _declspec(dllexport)
#else
#define DLLPORT
#endif

class DLLPORT GobangGame {
    
    const int DEFAULT_DEEP = -1;
    const int DEFAULT_TIME_LIM = 500;
    const int DEFAULT_GAME_BOARD_SIZE = 19;
    
    /// the game board (19 * 19 by default)
    char *game_board;
    
    /// the winner (1 or 2, 0 indicates no one wins)
    int winner;
    
    /// indicates current player (1 or 2)
    int current_player;
    
    /// last move
    int last_r, last_c;
    
public:
    
    struct Point {
        int r;
        int w;
    };
    
    /// Generates a gobang game
    GobangGame();
    
    /// Degenerates a gobang game
    ~GobangGame();
    
    /// Automatically judges a move due to current state
    bool AIMove();
    
    /// Set a move by a player
    /// @param move_r the place's row
    /// @param move_c the place's column
    bool playerMove(int move_r, int move_c);
    
    /// Gets the winner (1 / 2, 0 if null)
    inline int getWinner() { return winner; }
    
    /// Gets the current player
    inline int getCurrentPlayer() { return current_player; }
    
    /// Gets last movement
    inline Point getLastMove() { return Point{last_r, last_c}; }
    
    /// Gets the gameboard
    inline const char* getGameBoard() { return this->game_board; }
};

#endif /* libgobang_h */
