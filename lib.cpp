#include <bits/stdc++.h>
#include <curses.h>
#include "lib.h"

using namespace std;

void w() {
    clear();
    mvaddstr(NUM_ROWS/2, NUM_COLS/2, "🎉 You've won!");
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
};

void l() {
    clear();
    mvaddstr(NUM_ROWS/2, NUM_COLS/2, "🎉 You've won!");
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
}