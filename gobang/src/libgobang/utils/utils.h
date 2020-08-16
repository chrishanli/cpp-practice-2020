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

#ifndef utils_h
#define utils_h

#include <utils/globals.h>

class GobangUtils {
public:
    GobangUtils();
    ~GobangUtils();

    static inline char getCell(const char *gs, int r, int c) {
        if (r < 0 || r >= G_BOARD_SIZE || c < 0 || c >= G_BOARD_SIZE) return -1;
        return gs[G_BOARD_SIZE * r + c];
    }

    static inline bool setCell(char *gs, int r, int c, char value) {
        if (r < 0 || r >= G_BOARD_SIZE || c < 0 || c >= G_BOARD_SIZE) return false;
        gs[G_BOARD_SIZE * r + c] = value;
        return true;
    }

    static bool remoteCell(const char *gs, int r, int c);

    // Game state hashing
    static void zobristInit(int size, uint64_t *z1, uint64_t *z2);
    static uint64_t zobristHash(const char *gs, int size, uint64_t *z1, uint64_t *z2);
    static inline void zobristToggle(uint64_t *state, uint64_t *z1, uint64_t *z2,
                                     int row_size, int r, int c, int player) {
        if (player == 1) {
            *state ^= z1[row_size * r + c];
        } else if (player == 2) {
            *state ^= z2[row_size * r + c];
        }
    }

};

#endif /* utils_h */
