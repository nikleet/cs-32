#ifndef SIDE_H
#define SIDE_H

class Board;

enum Side {NORTH, SOUTH}; // NORTH = 0, SOUTH = 1
const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}

bool tryCapture(Board& b, Side s, Side endSide, int endHole);

#endif // SIDE_H