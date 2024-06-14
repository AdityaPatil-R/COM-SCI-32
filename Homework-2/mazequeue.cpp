#include <queue>
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
    queue<Coord> path;
    path.push(Coord(sr, sc));
    maze[sr][sc] = 'X';

    while (!path.empty()) {
        Coord cur = path.front();
        path.pop();

        if (cur.r() == er && cur.c() == ec) {
            return true;
        } else {
            if (maze[cur.r()][cur.c() + 1] == '.') {
                path.push(Coord(cur.r(), cur.c() + 1));
                maze[cur.r()][cur.c() + 1] = 'X';
            }
            
            if (maze[cur.r() + 1][cur.c()] == '.') {
                path.push(Coord(cur.r() + 1, cur.c()));
                maze[cur.r() + 1][cur.c()] = 'X';
            }
            
            if (maze[cur.r()][cur.c() - 1] == '.') {
                path.push(Coord(cur.r(), cur.c() - 1));
                maze[cur.r()][cur.c() - 1] = 'X';
            }
            
            if (maze[cur.r() - 1][cur.c()] == '.') {
                path.push(Coord(cur.r() - 1, cur.c()));
                maze[cur.r() - 1][cur.c()] = 'X';
            }
        }
    }

    return false;
}