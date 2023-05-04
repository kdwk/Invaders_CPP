#ifndef INVADER_CONST
#define INVADER_CONST

#include <bits/stdc++.h>

const int NUM_COLS = 40;
const int NUM_ROWS = 30;
#define KEY_SPACE 32
#define KEY_Q 113
#define KEY_P 112

const int NUM_INVADERS = 50;
const int INITIAL_INVADER_SPEED = 1000; // Initial update duration in milliseconds

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

void w();
void l();
void p();

void greet();

#endif