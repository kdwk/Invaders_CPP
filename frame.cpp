#include <bits/stdc++.h>
#include <ncurses.h>
#include "frame.h"
#include "lib.h"

using namespace std;

Frame::Frame() {
    for (int i=0; i<NUM_COLS; i++) {
        vector<string> col = {};
        for (int i=0; i<NUM_ROWS; i++){
            col.push_back(" ");
        }
        content.push_back(col);
    }
};

void Frame::composite(int score) {
    for (vector<string> col: content) {
        // Adds one row to frame at the bottom
        col.push_back(" ");
    }
    char char5 = to_string(NUM_INVADERS)[1];
    char char4 = to_string(NUM_INVADERS)[0];
    char char3 = '/';
    if (to_string(score).length() == 2) {
        char char2 = to_string(score)[1];
        char char1 = to_string(score)[0];
        vector<char> chars = {char1, char2, char3, char4, char5};
        for (int i=0; i<5; i++) {content[NUM_COLS-1-i][NUM_ROWS-1] = to_string(chars[4-i]);}
    } else if (to_string(score).length() == 1) {
        char char1 = to_string(score)[0];
        vector<char> chars = {char1, char3, char4, char5};
        for (int i=0; i<4; i++) {content[NUM_COLS-1-i][NUM_ROWS-1] = to_string(chars[3-i]);}
    }

}


void Frame::render(int score) {
    mvaddstr(0, 0, "\33[40;94m");
    composite(score); // Add game status
    for (int y=0; y<NUM_ROWS; y++) {
        for (int x=0; x<NUM_COLS; x++) {
            mvaddstr(y, x, content[x][y].c_str());
        }
    }
    refresh(); // Flush buffer
};

