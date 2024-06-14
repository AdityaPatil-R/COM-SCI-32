#include <stack>
#include <iostream>

using namespace std;

class Coord {
    public:
        Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
        int r() const {return m_row;}
        int c() const {return m_col;}
    private:
        int m_row;
        int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    stack<Coord> path;
    // Push the starting coordinate (sr,sc) onto the coordinate stack and
    // update maze[sr][sc] to indicate that the algorithm has encountered
    // it (i.e., set maze[sr][sc] to have a value other than '.').
    path.push(Coord(sr, sc));
    maze[sr][sc] = 'X';

    // While the stack is not empty,
    while (!path.empty()) {
        Coord cur = path.top();
        // Pop the top coordinate off the stack. This gives you the current
        // (r,c) location that your algorithm is exploring.
        path.pop();

        // If the current (r,c) coordinate is equal to the ending coordinate,
        // then we've solved the maze so return true!
        if (cur.r() == er && cur.c() == ec) {
            return true;
        // Check each place you can move from the current cell as follows:
        } else {
            // If you can move EAST and haven't encountered that cell yet,
            if (maze[cur.r()][cur.c() + 1] == '.') {
                // then push the coordinate (r,c+1) onto the stack and update
                path.push(Coord(cur.r(), cur.c() + 1));
                // update maze to indicate the algorithm has encountered it.
                maze[cur.r()][cur.c() + 1] = 'X';
            }

            // If you can move SOUTH and haven't encountered that cell yet,
            if (maze[cur.r() + 1][cur.c()] == '.') {
                // then push the coordinate (r+1,c) onto the stack and update
                path.push(Coord(cur.r() + 1, cur.c()));
                // update maze to indicate the algorithm has encountered it.
                maze[cur.r() + 1][cur.c()] = 'X';
            }
            
            // If you can move WEST and haven't encountered that cell yet,
            if (maze[cur.r()][cur.c() - 1] == '.') {
                // then push the coordinate (r,c-1) onto the stack and update
                path.push(Coord(cur.r(), cur.c() - 1));
                // update maze to indicate the algorithm has encountered it.
                maze[cur.r()][cur.c() - 1] = 'X';
            }
            
            // If you can move NORTH and haven't encountered that cell yet,
            if (maze[cur.r() - 1][cur.c()] == '.') {
                // then push the coordinate (r-1,c) onto the stack and update
                path.push(Coord(cur.r() - 1, cur.c()));
                // update maze to indicate the algorithm has encountered it.
                maze[cur.r() - 1][cur.c()] = 'X';
            }
        }
    }

    // There was no solution, so return false
    return false;
}