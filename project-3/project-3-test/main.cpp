#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

bool tryCapture(Board& b, Side s, Side endSide, int endHole)
{
	if (b.beans(s, endHole) == 1
		&& b.beans(opponent(s), endHole) != 0
		&& endSide == s)
	{
		b.moveToPot(opponent(s), endHole, s);
		return true;
	}
	
	return false;
}

int main()
{
	BadPlayer p1("Nik");
	SmartPlayer p2("Leila");
	Board b(6, 4);
	Game g(b, &p1, &p2);
	g.play();

	cout << "Passed all tests" << endl;
}