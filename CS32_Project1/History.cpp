#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
: m_rows(nRows), m_cols(nCols)
{
    // Initialize 2D array to store the counting variable at each grid
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++)
            count[i][j] = 0;

}

bool History::record(int r, int c) 
{
    // it's invalid when the location is not in the city
    if (r < 1|| r > m_rows || c < 1 || c > m_cols)
        return false;

    // start recording
    count[r - 1][c - 1] ++; // C++ starts with 0 => r-1, c-1 are indexes for count array
    
    return true;
}
void History::display() const
{
    
    clearScreen();

    // displaying the history
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            // 1- 25 times will display as A-Y 
            if (count[i][j] > 0 && count[i][j] < 26)
            {
               
                // starts with A as 1 time, not 0 time
                cout << static_cast <char> ('A' + count[i][j] - 1); 
              
            }
            // equal of greater than 26 times will display Z
            else if (count[i][j] >= 26)
                 cout << 'Z';

            // 0 time.
            else
                 cout << '.';
            
        }
        cout << endl;

    }
    cout << endl;

    
}