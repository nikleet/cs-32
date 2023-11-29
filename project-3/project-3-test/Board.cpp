#include "Board.h"
#include <iostream> // remove after done testing
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
{

	nInitialBeansPerHole = (nInitialBeansPerHole < 0 ? 0 : nInitialBeansPerHole);
	m_nHoles = (nHoles > 0 ? nHoles : 1);

	m_nBeans = 2 * m_nHoles * nInitialBeansPerHole;

	for (int i = 0; i < NSIDES; i++)
	{
		m_board[i] = std::vector<int>(m_nBeans + 1, nInitialBeansPerHole);
		m_board[i][POT] = 0;
	}
}

// Return the number of holes on a side(not counting the pot).
int Board::holes() const { return m_nHoles; }

// Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
	hole = convertHole(s, hole);
	if (isValidHole(hole))
		return m_board[s][hole];
	else
		return -1;
}

// Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const // may need to optimize for efficiency if used in chooseMove()
{
	int count = 0;
	for (int i = 0; i <= m_nHoles; ++i)
	{
		if (i != POT)
			count += m_board[s][i];
	}

	return count;
}

// Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const { return m_nBeans; }

// If the hole indicated by(s, hole) is empty or invalid or a pot, this 
// function returns false without changing anything. Otherwise, it will 
// return true after sowing the beans : the beans are removed from 
// hole(s, hole) and sown counterclockwise, including s's pot if 
// encountered, but skipping s's opponent's pot. The function sets the
// parameters endSide and endHole to the side and hole where the last bean
// was placed. (This function does not make captures or multiple turns; 
// different Kalah variants have different rules about these issues, 
// so dealing with them should not be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	hole = convertHole(s, hole);
	if (!isValidHole(hole) || hole == POT || m_board[s][hole] == 0)
		return false;

	int beans = m_board[s][hole];
	m_board[s][hole] = 0;

	Side current_side = s;
	int h = hole - 1;

	while (beans > 0) {
		for (; h >= 0 && beans > 0; h--) {
			if (!(h == POT && current_side == opponent(s)))
			{
				m_board[current_side][h]++;
				beans--;
				endSide = current_side;
				endHole = convertHole(current_side, h);
			}
		}
		h = m_nHoles;
		current_side = opponent(current_side);
	}

	return true;
}

// If the indicated hole is invalid or a pot, return false without changing 
// anything. Otherwise, move all the beans in hole(s, hole) into the pot 
// belonging to pot Owner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	hole = convertHole(s, hole);
	if (!isValidHole(hole) || hole == POT)
		return false;

	m_board[potOwner][POT] += m_board[s][hole];
	m_board[s][hole] = 0;
	return true;
}

// If the indicated hole is invalid or beans is negative, this function 
// returns false without changing anything. Otherwise, it will return true
// after setting the number of beans in the indicated hole or pot to the
// value of the third parameter. (This could change what beansInPlay and 
// totalBeans return if they are called later.) This function exists solely
// so that w eand you can more easily test your program : None of your code 
// that implements the member functions of any class is allowed to call this 
// function directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
	hole = convertHole(s, hole);

	if (!isValidHole(hole) || beans < 0)
		return false;

	m_nBeans += beans - m_board[s][hole];
	m_board[s][hole] = beans;
	return true;
}

bool Board::isValidHole(int hole) const
{
	if (hole < 0 || hole > m_nHoles)
		return false;
	return true;
}

// REMOVE AFTER DEBUGGING
void Board::displayBoard()
{
	int nHoles = holes();

	cerr << endl;
	// print north holes
	for (int i = 1; i <= nHoles; ++i)
		cerr << "\t" << beans(NORTH, i);

	// print pots
	cerr << "\n" << beans(NORTH, POT);
	for (int i = 0; i < nHoles + 1; i++)
		cerr << "\t";
	cerr << beans(SOUTH, POT) << endl;

	// print south holes 
	for (int i = 1; i <= nHoles; i++)
		cerr << "\t" << beans(SOUTH, i);

	cout << endl << endl;
}


int Board::convertHole(Side s, int hole) const
{
	if (s == SOUTH && hole != POT)
		return hole = m_nHoles + 1 - hole;
	else
		return hole;
}