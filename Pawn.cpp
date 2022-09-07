/*
TEAM
Zhang, Katie    kzhang70  (Section 3)
Zhou, Jeffrey   jzhou91    (Section 3)
Simeng Zhang    szhan146    (Section 5)
Chujian Yu      cyu62       (Section 5)

A pawn can move only forward towards the opponent’s side of the board, but with restrictions. 
On its first move of the game, a pawn may move forward either one or two squares; 
on subsequent moves, a pawn may only move forward one square. 
A pawn may not move through other pieces. 
Furthermore, the pawn may not use a forward move to land in a square that is occupied by any player’s piece. 
In a separate type of action, a pawn may make a special move to “capture” an opponent piece
*/

#include "Pawn.h"
#include <iostream>
namespace Chess
{
    bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
        bool is_initial = false;
        bool white = is_white();
        if ( (start.second == '2' && white) || (start.second == '7' && !white) ) 
            is_initial = true;
        int horizontal_displacement = (int)(end.first - start.first);
        int vertical_displacement = (int)(end.second - start.second);
        if (white && vertical_displacement == 1 && horizontal_displacement == 0)
            return true;
        if (!white && vertical_displacement == -1 && horizontal_displacement == 0)
            return true;
        if (white && is_initial && vertical_displacement == 2 && horizontal_displacement == 0)
            return true;       
        if (!white && is_initial && vertical_displacement == -2 && horizontal_displacement == 0)
            return true;
        return false;
  }
    bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
        if (legal_move_shape(start, end)){
            return false;
        }
        bool white = is_white();
        int horizontal_displacement = (int)(end.first - start.first);
        int vertical_displacement = (int)(end.second - start.second);
        if (white && vertical_displacement == 1 && abs(horizontal_displacement) == 1 ){
            return true;
        }

        if (!white && vertical_displacement == -1 && abs(horizontal_displacement) == 1 )
            return true;
        return false;
	}

}
