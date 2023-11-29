/**
 * CS 32, Project 3, Game.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/30/2023
*/

#include "Game.h"
#include <iostream>
#include <climits>

using namespace std;

// Construct a Game to be played with the indicated players on a copy 
// of the board b. The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north)
	:  m_np(north), m_sp(south), m_b(b)
{
	m_p = std::vector<Player*>(NSIDES);
	m_p[NORTH] = north;
	m_p[SOUTH] = south;
	
	m_over = false;
	m_hasWinner = false;
	// m_winner is initialized here to ignore warnings. 
	// Its value is meaningless until the game ends.
	m_winner = SOUTH; 
}

// Display the game's board in a manner of your choosing, provided you 
// show the names of the players and a reasonable representation of the
// state of the board.
void Game::display() const
{
	int nHoles = m_b.holes();
	
	cout << endl;
	// print north name
	for (int i = 0; i < nHoles / 2; ++i)
		cout << "\t";
	cout << m_np->name() << endl;
	
	// print north holes
	cout << "North";
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
	cout << "\tSouth" << endl;

	// print south name
	for (int i = 0; i < m_b.holes() / 2; ++i)
		cout << "\t";
	cout << m_sp->name() << endl;
}

// If the game is over(i.e., the move member function has been called 
// and returned false), set over to true; otherwise, set over to false
// and do not change anything else. If the game is over, set hasWinner 
// to true if the game has a winner, or false if it resulted in a tie.
// If hasWinner is set to false, leave winner unchanged; otherwise, 
// set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (m_b.beansInPlay(NORTH) == 0 || m_b.beansInPlay(SOUTH) == 0)
	{
		over = true;
		if (m_b.beans(NORTH, POT) > m_b.beans(SOUTH, POT))
		{
			hasWinner = true;
			winner = NORTH;
		}
		else if (m_b.beans(NORTH, POT) < m_b.beans(SOUTH, POT))
		{
			hasWinner = true;
			winner = SOUTH;
		}
		else
			hasWinner = false;
	}
	else
		over = false;
}

// Attempt to make a complete move for the player playing side s. 
// "Complete" means that the player sows the seeds from a hole and
// takes any additional turns required or completes a capture. Whenever
// the player gets an additional turn, you should display the board so 
// someone looking at the screen can follow what's happening. If the 
// move can be completed, return true; if not, because the move is not 
// yet completed but side s has no holes with beans to pick up and sow, 
// sweep any beans in s's opponent's holes into that opponent's pot and
// return false.
bool Game::move(Side s)
{
	int move;
	int endHole;
	Side endSide;
	
	do {
		move = m_p[s]->chooseMove(m_b, s);
		
		// sweep if chooseMove is invalid (game over)
		if (move <= 0) {
			for (int h = 1; h <= m_b.holes(); h++)
				m_b.moveToPot(opponent(s), h, opponent(s));
			return false;
		}
			
		m_b.sow(s, move, endSide, endHole);
		tryCapture(m_b, s, endSide, endHole);

		display();	// display board

	} while (endHole == POT && endSide == s);

	return true;
}

// Play the game. Display the progress of the game in a manner of your 
// choosing, provided that someone looking at the screen can follow 
// what's happening. If neither player is interactive, then to keep the
// display from quickly scrolling through the whole game, it would be
// reasonable periodically to prompt the viewer to press ENTER to 
// continue and not proceed until ENTER is pressed. (The ignore function
// for input streams is useful here.) Announce the winner at the end of 
// the game. You can apportion to your liking the responsibility for 
// displaying the board between this function and the move function.
void Game::play()
{
	Side currentSide = SOUTH; // this side will play first
	bool bothRobo = (!m_np->isInteractive() && !m_sp->isInteractive());

	display(); // display initial board state

	while (!m_over) 
	{
		cout << m_p[currentSide]->name() + "'s turn!" << endl;
		
		if (bothRobo) 
		{
			cout << "Press ENTER to continue." << endl;
			cin.ignore(INT_MAX, '\n');
		}
		
		move(currentSide);
		status(m_over, m_hasWinner, m_winner);	// update status variables

		if (m_over)
		{
			sweep(m_b);
			break;
		}
		
		currentSide = opponent(currentSide);
	}

	cout << "\nGAME OVER! ";

	if (m_hasWinner) 
	{
		cout << m_p[m_winner]->name() + " wins." << endl;
	}
	else
	{
		cout << "The game was a tie." << endl;
	}
	
	cout << "Final board:" << endl;
	display(); // display final board state
}

// Return the number of beans in the indicated hole or pot of the game's
// board, or −1 if the hole number is invalid. This function exists so
// that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
	return m_b.beans(s, hole);
}