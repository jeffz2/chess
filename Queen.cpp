/*
TEAM
Zhang, Katie    kzhang70  (Section 3)
Zhou, Jeffrey   jzhou91    (Section 3)
Simeng Zhang    szhan146    (Section 5)
Chujian Yu      cyu62       (Section 5)

A queen may move any number of spaces in one direction, including diagonally. 
A queen may not move through other pieces.
*/
#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
    int horizontal_displacement = abs((int)(start.first - end.first));
    int vertical_displacement = abs((int)(start.second - end.second));
    
    if(horizontal_displacement == vertical_displacement)
    if (horizontal_displacement == vertical_displacement)
        return true;      
    if ( (horizontal_displacement != 0 && vertical_displacement == 0) || (horizontal_displacement == 0 && vertical_displacement != 0) )
        return true;
    return false;
  }
}