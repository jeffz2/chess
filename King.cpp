/*
TEAM
Zhang, Katie    kzhang70  (Section 3)
Zhou, Jeffrey   jzhou91    (Section 3)
Simeng Zhang    szhan146    (Section 5)
Chujian Yu      cyu62       (Section 5)

A king may move in any direction, including diagonally, but may only move one square.
*/
#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    int horizontal_displacement = abs((int)(start.first - end.first));
    int vertical_displacement = abs((int)(start.second - end.second));
    if (horizontal_displacement + vertical_displacement == 1)
        return true;      
    if (horizontal_displacement == 1 && vertical_displacement == 1)
        return true;
    return false;
  }
}