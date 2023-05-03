#include <bits/stdc++.h>
#include <curses.h>
#include "clear.h"
#include "frame.h"
#include "invader.h"
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

void Frame::composite() {
    // TODO
    // Everyone do csd
    // Add status bar
}


void Frame::render() {
    // TODO: change to flush mechanism instead of clear to eliminate flickering
    // aclear();
    // for (int y=0; y<NUM_ROWS; y++){
    //     for (int x=0; x<NUM_COLS; x++) {
    //         cout << content[x][y];
    //     }
    //     cout << endl;
    // }
    for (int y=0; y<NUM_ROWS; y++) {
        for (int x=0; x<NUM_COLS; x++) {
            mvaddstr(y, x, content[x][y].c_str());
        }
    }
    refresh();
};

