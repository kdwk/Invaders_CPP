#include <bits/stdc++.h>
#include <ncurses.h>
#include "lib.h"

using namespace std;

void w() {
    clear();
    mvaddstr(NUM_ROWS/2, NUM_COLS/2, "🎉 You win!");
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
};

void l() {
    clear();
    mvaddstr(NUM_ROWS/2, NUM_COLS/2, "😕 You lose");
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
}

void greet() {
    clear();
    int init_y = NUM_ROWS/2-1;
    int slice_begin = 0;
    for (int y=init_y; y<init_y+3; y++){
        mvaddstr(y, NUM_COLS/2-16, INVADERS_ASCII.substr(slice_begin, 32).c_str());
        slice_begin += 32;
    }
    mvaddstr(init_y+3, NUM_COLS/2-11, "Press any key to continue");
    getch();
}