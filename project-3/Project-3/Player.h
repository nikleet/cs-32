/**
 * CS 32, Project 3, Player.h
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/30/2023
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Side.h"

using namespace std;

class JumpyTimer;

class Player {
	public:
		Player(std::string name) : m_name(name) {}
		string name() const { return m_name; }
		virtual bool isInteractive() const { return false; }
		virtual int chooseMove(const Board& b, Side s) const = 0;
		virtual ~Player() {}

	private:
		string m_name;
};

class BadPlayer : public Player {
	public:
		BadPlayer(string name) : Player(name) {}
		virtual bool isInteractive() const { return false; }
		virtual int chooseMove(const Board& b, Side s) const;
		virtual ~BadPlayer() {}
};

class HumanPlayer : public Player
{
	public:
		HumanPlayer(string name) : Player(name) {}
		virtual bool isInteractive() const { return true; }
		virtual int chooseMove(const Board& b, Side s) const;
		virtual ~HumanPlayer() {}
};


class SmartPlayer :public Player {
	public:
		SmartPlayer(string name) : Player(name) {}
		virtual bool isInteractive() const { return false; }
		virtual int chooseMove(const Board& b, Side s) const;
		virtual ~SmartPlayer() {}
	private:
		int simulateTurn(Board& b, Side s, int hole) const;
		void minimax(const Board& b, Side s, int& bestHole, int& value,int depth, double timeLimit, JumpyTimer& timer) const;
		int evaluate(const Board& b) const;
		int bestForSide(Side s, int v1, int v2) const;
};
#endif // PLAYER_H

