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

#include <ai/ai_controller.h>
#include <ai/eval.h>
#include <ai/negamax.h>
#include <utils/globals.h>
#include <utils/utils.h>
#include <judge/judge.h>
#include <cstring>

void RenjuAIController::generateMove(const char *gs,
                                     int player,
                                     int search_depth,
                                     int time_limit,
                                     int *actual_depth,
                                     int *move_r,
                                     int *move_c,
                                     unsigned int *node_count,
                                     unsigned int *eval_count,
                                     unsigned int *pm_count) {
    // Check arguments
    if (gs == nullptr ||
        player  < 1 || player > 2 ||
        search_depth == 0 || search_depth > 10 ||
        time_limit < 0 ||
        move_r == nullptr || move_c == nullptr) return;

    // Initialize counters
    g_eval_count = 0;
    g_pm_count = 0;

    // Initialize data
    *move_r = -1;
    *move_c = -1;
    if (actual_depth != nullptr) *actual_depth = 0;

    // Copy game state into a modifiable one
    char *_gs = new char[G_GS_SIZE];
    std::memcpy(_gs, gs, G_GS_SIZE);

    // Run negamax
    RenjuAINegamax::heuristicNegamax(_gs, player, search_depth, time_limit, true, actual_depth, move_r, move_c);
    
    // Write output
    if (node_count != nullptr) *node_count = g_node_count;
    if (eval_count != nullptr) *eval_count = g_eval_count;
    if (pm_count != nullptr) *pm_count = g_pm_count;

    delete[] _gs;
}
