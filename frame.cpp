#include "stdcpp.h"
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
    // Add a border around the frame
    string top_and_bottom = "+";
    for (int i=0; i<NUM_COLS; i++) {
        top_and_bottom.push_back('-');
    }
    top_and_bottom.push_back('+');
    mvaddstr(0, 0, top_and_bottom.c_str());
    for (int iter_row=1; iter_row<NUM_ROWS+1; iter_row++) {
        mvaddstr(iter_row, 0, "|");
        mvaddstr(iter_row, NUM_COLS+1, "|");
    }
    mvaddstr(NUM_ROWS+1, 0, top_and_bottom.c_str());
    // Adds game score below bottom of frame
    mvaddstr(NUM_ROWS+2, 0, to_string(score).c_str());
    mvaddstr(NUM_ROWS+2, 2, "/");
    mvaddstr(NUM_ROWS+2, 3, to_string(NUM_INVADERS).c_str());
}


void Frame::render(int score, int NUM_INVADERS) {
    // Iterate through contents of the frame and push it to screen
    for (int y=0; y<NUM_ROWS; y++) {
        for (int x=0; x<NUM_COLS; x++) {
            mvaddstr(y+1, x+1, content[x][y].c_str());
        }
    }
    composite(score, NUM_INVADERS); // Add game status
    refresh();                      // Flush buffer
};

