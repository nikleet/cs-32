#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 1; r <= m_rows; r++)
		for (int c = 1; c <= m_cols; c++)
			m_grid[r - 1][c - 1] = 0;
}

bool History::record(int r, int c)
{
	if (r <= m_rows && c <= m_cols) 
	{
		m_grid[r - 1][c - 1]++;
		return true;
	}
	return false;
}

void History::display() const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid 
    for (r = 1; r <= m_rows; r++)
        for (c = 1; c <= m_cols; c++)
        {
            int gridVal = m_grid[r - 1][c - 1];
            if (gridVal == 0)
                displayGrid[r - 1][c - 1] = '.';
            if (0 < gridVal && gridVal < 25)
                displayGrid[r - 1][c - 1] = char(64 + gridVal);
            if (gridVal >= 26)
                displayGrid[r - 1][c - 1] = 'Z';
        }

    // Draw the grid
    clearScreen();
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;
}