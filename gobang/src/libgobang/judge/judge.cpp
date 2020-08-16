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

#include <utils/globals.h>
#include <ai/eval.h>
#include <judge/judge.h>

int GobangJudge::winningPlayer(const char *gs) {
    if (gs == nullptr) return 0;
    for (int r = 0; r < G_BOARD_SIZE; ++r) {
        for (int c = 0; c < G_BOARD_SIZE; ++c) {
            int cell = gs[G_BOARD_SIZE * r + c];
            if (cell == 0) continue;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc <= 0) continue;
                    RenjuAIEval::DirectionMeasurement dm;
                    RenjuAIEval::measureDirection(gs, r, c, dr, dc, cell, 1, &dm);
                    if (dm.length >= 5) return cell;
                }
            }
        }
    }
    return 0;
}
