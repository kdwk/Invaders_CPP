#ifndef FRAME
#define FRAME
// This header declares the Frame class

#include "stdcpp.h"

class Frame {
    void composite(int score, int NUM_INVADERS);       // Add game score below the bottom of frame
    public:
        std::vector<std::vector<std::string>> content; // A frame is a vector of vectors of strings; outer vector contains columns, inner vector is rows of that column; each 'pixel' is a string
        Frame();                                       // Initialize a new frame
        void render(int score, int NUM_INVADERS);      // Uses the ncurses library to push a frame to screen
};

#endif