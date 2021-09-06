#include <iostream>
#include <queue>
#include <string>
using namespace std;


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

//int main()
//{
//    string maze[10] = {
//                "XXXXXXXXXX",
//                "X........X",
//                "XX.X.XXXXX",
//                "X..X.X...X",
//                "X..X...X.X",
//                "XXXX.XXX.X",
//                "X.X....XXX",
//                "X..XX.XX.X",
//                "X...X....X",
//                "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10, 10, 6, 4, 1, 1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//
//}



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;

    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '*';

    while (!coordQueue.empty())
    {
        Coord curr = coordQueue.front();
        coordQueue.pop();
      /*  cout << "(" << curr.r() << "," << curr.c() << ")" << endl;*/

        if (curr.r() == er && curr.c() == ec)
            return true;
        else
        {
            // move North
            if (curr.r() - 1 > 0 && maze[curr.r() - 1][curr.c()] == '.')
            {
                coordQueue.push(Coord(curr.r() - 1, curr.c()));
                maze[curr.r() - 1][curr.c()] = '*';
            }
            // move East
            if (curr.c() + 1 < nCols - 1 && maze[curr.r()][curr.c() + 1] == '.')
            {
                coordQueue.push(Coord(curr.r(), curr.c() + 1));
                maze[curr.r()][curr.c() + 1] = '*';
            }
            // move South
            if (curr.r() + 1 < nRows - 1 && maze[curr.r() + 1][curr.c()] == '.')
            {
                coordQueue.push(Coord(curr.r() + 1, curr.c()));
                maze[curr.r() + 1][curr.c()] = '*';
            }
            // move West
            if (curr.c() - 1 > 0 && maze[curr.r()][curr.c() - 1] == '.')
            {
                coordQueue.push(Coord(curr.r(), curr.c() - 1));
                maze[curr.r()][curr.c() - 1] = '*';
            }
        }
    }
    return false;

}