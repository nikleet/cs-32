/**
 * CS 32, Project 3, Player.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/30/2023
*/

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

// Advance jumpy timer only after jumpInterval calls to elapsed
class JumpyTimer
{
public:
	JumpyTimer(int jumpInterval)
		: m_jumpInterval(jumpInterval), m_callsMade(0)
	{
		actualElapsed();
	}
	double elapsed()
	{
		m_callsMade++;
		if (m_callsMade == m_jumpInterval)
		{
			m_lastElapsed = m_timer.elapsed();
			m_callsMade = 0;
		}
		return m_lastElapsed;
	}
	double actualElapsed()
	{
		m_lastElapsed = m_timer.elapsed();
		return m_lastElapsed;
	}
private:
	Timer m_timer;
	int m_jumpInterval;
	int m_callsMade;
	int m_lastElapsed;
};

//========================================================================


#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

// Prompts a human player to enter his or her move
int HumanPlayer::chooseMove(const Board& b, Side s) const 
{
	int move = -1;
	if (b.beansInPlay(s) > 0) 
	{
		do {
			cout << "Choose a pot to sow [(left) 1 to " << b.holes() << " (right)]: ";
			cin >> move;
		} while (b.beans(s, move) <= 0);
	}

	return move;
}


// Chooses a random legal move
int BadPlayer::chooseMove(const Board& b, Side s) const
{
	int move;
	
	vector<int> legalMoves;
	for (int i = 1; i <= b.holes(); i++)
		if (b.beans(s, i) > 0)
			legalMoves.push_back(i);
	
	if (!legalMoves.empty())
		move = legalMoves[rand() % legalMoves.size()];
	else
		return -1;

	return move;
}


/*
	Interface for chooseMove calls minimax to determine the best move, searching to a tree
	depth specified by the third parameter in minimax().
*/
int SmartPlayer::chooseMove(const Board& b, Side s) const 
{
	int bestHole, value, maxSearchDepth = 8;
	double timeLimit = 5000;  // 2.5 seconds
	JumpyTimer timer(1000);

	minimax(b, s, bestHole, value, maxSearchDepth, timeLimit, timer);
	cerr << "Time elapsed: " << timer.actualElapsed() << " ms" << endl;
	
	return bestHole;
}


/*
	Minimax algorithm generates tree of possible moves to the depth specified by 
	the third parameter. SOUTH player maximizes value, NORTH player minimizes 
	value. The actor alternates with every recursive call. Side s is the player 
	taking the current move, bestHole is set to the best move for that player.
*/
void SmartPlayer::minimax(const Board& b, Side s, int& bestHole, int& value, int depth, double timeLimit, JumpyTimer& timer) const 
{
	double startTime = timer.elapsed();

	// terminates if the game ends, depth limit is reached, or time limit is reached
	if (b.beansInPlay(s) == 0 || depth == 0 || startTime >= timeLimit) 
	{  
		bestHole = -1;
		value = evaluate(b);
		return;
	}
	
	int tempBestHole = 0;
	int tempBestVal = bestForSide(opponent(s), INT_MIN, INT_MAX);

	// call minimax recursively for each possible move from the current board state
	for (int i = 1; i <= b.holes(); ++i) {
		if (b.beans(s, i) > 0) 
		{	
			Board copy = b;
			// calls simulateTurn to make a move and resolve possible extra turns
			// resulting from that move
			simulateTurn(copy, s, i);
			minimax(copy, opponent(s), bestHole, value, depth - 1, timeLimit, timer);
				
			if (value == bestForSide(s, tempBestVal, value)) {
				tempBestVal = value;
				tempBestHole = i;
			}
		}
	}

	bestHole = tempBestHole;
}


/*
	Simulates a move from the parameter hole on the Board b, and if this move would result
	in an extra turn, this function calls itself recursively to resolve the turn with the
	choice of hole that yields the greatest value.
*/
int SmartPlayer::simulateTurn(Board& b, Side s, int hole) const 
{
	Side endSide;
	int endHole;

	b.sow(s, hole, endSide, endHole);
	tryCapture(b, s, endSide, endHole);

	// check if game over
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0) {
		sweep(b);
		return evaluate(b);
	}

	// check if extra turn
	if (endHole == POT && endSide == s) 
	{
		int bestVal = bestForSide(opponent(s), INT_MIN, INT_MAX);
		for (int i = 1; i <= b.holes(); ++i) {
			if (b.beans(s, i) > 0)
			{
				Board copy = b;
				int value = simulateTurn(copy, s, i);
				if (value == bestForSide(s, value, bestVal))
					bestVal = value;
			}
		}
		return bestVal;
	}

	return evaluate(b);
}

/*
	Returns the best of the two provided values for the specified side: the maximum 
	of the two for the SOUTH side, or the minimum for the NORTH side.
*/
int SmartPlayer::bestForSide(Side s, int v1, int v2) const
{
	if (s == NORTH)
		return min(v1, v2);
	else // s == SOUTH
		return max(v1, v2);
}


/*
	Hueristic to evaluate the current board state, returns a score. Larger score is better 
	for SOUTH, smaller score is better for NORTH. The score is based on the difference 
	between the current player and his or her opponent's beans. The value of beans in the 
	pot are weighted twice as heavily as the value of beans in the pots. If the current
	board state represents the end of the game, score becomes the best possible value
	for the winner (positive or negative infinity for SOUTH or NORTH, respectively), 
	or zero in the case of a tie.
*/
int SmartPlayer::evaluate(const Board& b) const
{
	int score = (2 * b.beans(SOUTH, POT) + b.beansInPlay(SOUTH)) 
				- (2 * b.beans(NORTH, POT) + b.beansInPlay(NORTH));

	if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
	{
		if (score > 0)
			score = INT_MAX;
		else if (score < 0)
			score = INT_MIN;
		else
			score = 0;
	}

	return score;
}