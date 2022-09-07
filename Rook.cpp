/*
TEAM
Zhang, Katie    kzhang70  (Section 3)
Zhou, Jeffrey   jzhou91    (Section 3)
Simeng Zhang    szhan146    (Section 5)
Chujian Yu      cyu62       (Section 5)

A rook may move any number of squares, but only along a horizontal or vertical line on the board. 
A rook may not move through other pieces.
*/
#include "Rook.h"

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    int horizontal_displacement = abs((int)(start.first - end.first));
    int vertical_displacement = abs((int)(start.second - end.second));
    if ( (horizontal_displacement != 0 && vertical_displacement == 0) || (horizontal_displacement == 0 && vertical_displacement != 0) )
        return true;
    return false;
  }
}
