/**
 * CS 32, Homework 3, maze.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/8/2023
*/

/*
#include <iostream>
#include <stdlib.h>

using namespace std;

void printMaze(char maze[][10]) {
    system("CLS");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}
*/

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = '*';
    // printMaze(maze);

    // explore north
    if (sr - 1 > 0 && maze[sr - 1][sc] == '.')
        if (pathExists(maze, sr - 1, sc, er, ec))
            return true;
    // explore east
    if (sc + 1 < 9 && maze[sr][sc + 1] == '.')
        if (pathExists(maze, sr, sc + 1, er, ec))
            return true;
    // explore south
    if (sr + 1 < 9 && maze[sr + 1][sc] == '.')
        if (pathExists(maze, sr + 1, sc, er, ec))
            return true;
    // explore west
    if (sc - 1 > 0 && maze[sr][sc - 1] == '.')
        if (pathExists(maze, sr, sc - 1, er, ec))
            return true;
    
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

    if (pathExists(maze, 3, 4, 5, 1))
        cout << "Solvable!" << endl;
    else
        cout << "\nOut of luck!" << endl;
}
*/

