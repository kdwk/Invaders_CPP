#include <bits/stdc++.h>
#include <ncurses.h>
#include "frame.h"
#include "lib.h"

using namespace std;

Frame::Frame() {
    // Initialize a new frame
    for (int i=0; i<NUM_COLS; i++) {
        vector<string> col = {};
        for (int i=0; i<NUM_ROWS; i++){
            col.push_back(" ");
        }
        content.push_back(col);
    }
};

void Frame::composite(int score, int NUM_INVADERS) {
    // Adds game score below bottom of frame
    mvaddstr(NUM_ROWS+1, 0, to_string(score).c_str());
    mvaddstr(NUM_ROWS+1, 2, "/");
    mvaddstr(NUM_ROWS+1, 3, to_string(NUM_INVADERS).c_str());
}


void Frame::render(int score, int NUM_INVADERS) {
    // Iterate through contents of the frame and push it to screen
    for (int y=0; y<NUM_ROWS; y++) {
        for (int x=0; x<NUM_COLS; x++) {
            mvaddstr(y, x, content[x][y].c_str());
        }
    }
    composite(score, NUM_INVADERS); // Add game status
    refresh();                      // Flush buffer
};

