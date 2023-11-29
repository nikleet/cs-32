/**
 * CS 32, Homework 2, mazestack.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/3/2023
*/

#include <stack>
// #include <iostream>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

// starting coordinate: (sr, sc), ending coordinate: (er, ec)
// coordinate form (row, columns)
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    stack<Coord> coords;
    coords.push(Coord(sr, sc));
    maze[sr][sc] = 'X';
    while (!coords.empty()) {
        int cr = coords.top().r();
        int cc = coords.top().c();
        coords.pop();
        if (cr == er && cc == ec)
            return true;
        if (cr + 1 < 9 && maze[cr + 1][cc] != 'X') {
            coords.push(Coord(cr + 1, cc));
            maze[cr+1][cc] = 'X';
        }
        if (cc + 1 < 9 && maze[cr][cc + 1] != 'X') {
            coords.push(Coord(cr, cc + 1));
            maze[cr][cc + 1] = 'X';
        }
        if (cr - 1 > 0 && maze[cr - 1][cc] != 'X') {
            coords.push(Coord(cr - 1, cc));
            maze[cr - 1][cc] = 'X';
        }
        if (cc - 1 > 0 && maze[cr][cc - 1] != 'X') {
            coords.push(Coord(cr, cc - 1));
            maze[cr][cc - 1] = 'X';
        }
    }
    return false;
}

/*
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 4, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
*/