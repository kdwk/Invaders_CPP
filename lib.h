#ifndef INVADER_CONST
#define INVADER_CONST

#include <bits/stdc++.h>

const int NUM_COLS = 30;
const int NUM_ROWS = 25;
#define KEY_SPACE 32
#define KEY_Q 113
#define KEY_P 112

const int NUM_SHOTS_ALLOWED = 3;

enum Health {
    alive,
    dead
};

enum Status {
    win,
    lose,
    cont,
    paus      // pause is already defined in a header so cannot be redeclared here
};

enum Level {
    easy,
    medium,
    hard,
    extreme
};

void w();
void l();
void p();

void greet();
Level choose_difficulty();

#endif