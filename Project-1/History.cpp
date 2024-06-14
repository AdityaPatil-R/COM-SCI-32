#include "History.h"

// Initialize rows, columns, and history array
History::History(int nRows, int nCols) {
    m_rows = nRows;
    m_cols = nCols;

    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            m_history[r][c] = '.';
        }
    }
}

bool History::record(int r, int c) {
    // Checks if location is in bounds
    if (r < 1 || c < 1 || r > m_rows || c > m_cols) {
        return false;
    }

    // References the point to change it directly rather than a copy of it
    char& point = m_history[r - 1][c - 1];

    // Changes the point to the next letter unless it is . or Z
    if (point == '.') {
        point = 'A';
    } else if (point == 'Z') {
        return true;
    } else {
        // Treats char as int if its between B and Y (Inclusive)
        point++;
    }

    return true;
}

// Same as display() in City.cpp
void History::display() const {
    clearScreen();

    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            cout << m_history[r][c];
        }

        cout << endl;
    }

    cout << endl;
}