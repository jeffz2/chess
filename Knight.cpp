/*
TEAM
Zhang, Katie    kzhang70  (Section 3)
Zhou, Jeffrey   jzhou91    (Section 3)
Simeng Zhang    szhan146    (Section 5)
Chujian Yu      cyu62       (Section 5)

A knight may move in an L-shape, of length either two-by-one or one-by-two. 
The knight is the only piece that is not stopped by other pieces in its way (i.e. it can move through other pieces to get to an open square).
*/
#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    int horizontal_displacement = abs((int)(start.first - end.first));
    int vertical_displacement = abs((int)(start.second - end.second));
    if (horizontal_displacement == 2 && vertical_displacement == 1)
        return true;       
    if (horizontal_displacement == 1 && vertical_displacement == 2)
        return true;
    return false;
  }
}
