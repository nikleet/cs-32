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

// Declarations for custom public functions declared in "main.cpp"
bool tryCapture(Board& b, Side s, Side endSide, int endHole);
void sweep(Board& b);

#endif // SIDE_H