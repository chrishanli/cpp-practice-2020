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

#ifndef judge_h
#define judge_h

class GobangJudge {
public:
    // Check if any player is winning based on a given state
    static int winningPlayer(const char *gs);
};

#endif /* judge_h */
