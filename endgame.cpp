#include <bits/stdc++.h>
#include <curses.h>
#include "clear.h"
#include "later.h"
#include "lib.h"

using namespace std;

void w() {
    clear();
    mvaddstr(NUM_ROWS/2, NUM_COLS/2, "🎉 You've won!");
}

void l() {
    clear();
    mvaddstr(NUM_ROWS/2, NUM_COLS/2, "🎉 You've won!");
}