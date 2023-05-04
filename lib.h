#ifndef INVADER_CONST
#define INVADER_CONST
// This header contains multiple constants, enums and functions used throughout the game

#include <bits/stdc++.h>

const int NUM_COLS = 30;             // Number of columns of the game area
const int NUM_ROWS = 25;             // Number of rows of the game area
#define KEY_SPACE 32
#define KEY_Q 113
#define KEY_P 112

const int NUM_SHOTS_ALLOWED = 3;     // Maximum number of shots allowed for the player

enum Health {                        // An enum to represent health condition
    alive,
    dead
};

enum Status {                        // An enum to represent game status
    win,
    lose,
    cont,
    paus      // pause is already defined in an included header so cannot be redeclared here
};

enum Level {                         // An enum to represent game difficulty level
    test,
    easy,
    medium,
    hard,
    extreme
};

void w(double seconds);              // What to do if the player wins
void l();                            // What to do if the player loses

void greet();                        // Greet the player when the game starts
Level choose_difficulty();           // Choose the difficulty of the game

#endif