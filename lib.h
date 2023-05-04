#ifndef INVADER_CONST
#define INVADER_CONST

#include <bits/stdc++.h>

const int NUM_COLS = 40;
const int NUM_ROWS = 30;
#define KEY_SPACE 32
#define KEY_Q 113

const int NUM_INVADERS = 50;
const int INITIAL_INVADER_SPEED = 2500; // Initial update duration in milliseconds

const std::string INVADERS_ASCII = "░▀█▀░█▀█░█░█░█▀█░█▀▄░█▀▀░█▀▄░█▀▀░░█░░█░█░▀▄▀░█▀█░█░█░█▀▀░█▀▄░▀▀█░▀▀▀░▀░▀░░▀░░▀░▀░▀▀░░▀▀▀░▀░▀░▀▀▀";

enum Health {
    alive,
    dead
};

enum Status {
    win,
    lose,
    cont
};

void w();

void l();

void greet();

#endif