/* TEAM
Zhang, Katie    kzhang70  (Section 3)
Zhou, Jeffrey   jzhou91    (Section 3)
Simeng Zhang    szhan146    (Section 5)
Chujian Yu      cyu62       (Section 5)

A bishop may move diagonally only but may move any number of spaces. 
A bishop may not move through other pieces.
*/
#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    int horizontal_displacement = abs((int)(start.first - end.first));
    int vertical_displacement = abs((int)(start.second - end.second));
    if (vertical_displacement == horizontal_displacement) {
      return true;
    }
    return false;
  }
}
