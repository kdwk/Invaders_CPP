#ifndef INVADER_CONST
#define INVADER_CONST

#include <bits/stdc++.h>

const int NUM_COLS = 40;
const int NUM_ROWS = 30;
// #define KEY_UP 72
// #define KEY_DOWN 80
// #define KEY_LEFT 75
// #define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_Q 113

// std::mutex mtx;

enum Health {
    alive,
    dead
};

enum Endgame {
    win,
    lose,
    cont
};

void w();

void l();

#endif