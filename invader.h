#ifndef INVADER
#define INVADER
// This header declares the Army class and related enums

#include <bits/stdc++.h>
#include "lib.h"
#include "frame.h"
#include "drawable_parent.h"

enum Symbol {      // Enum to represent the symbol of the army at a point in time (it varies regularly)
    plus,
    cross
};

struct Invader {   // An invader has x, y coordinates and a health status
    int x;
    int y;
    Health stat;
};

enum Direction {   // An army can travel in any of these directions
    left,
    right,
    down
};

class Army : public Drawable{
    Direction vec;                 // Current direction of the army
    Symbol sym;                    // Current symbol of the army
    bool reached_bottom();
    bool reached_left_wall();
    bool reached_right_wall();
    public:
        int rows_descended;        // Keeps track of number of rows descended by the army
        std::vector<Invader> army; // An army is a vector of invaders
        Army(int NUM_INVADERS);    // Initialize an army
        bool are_all_dead();
        Status update();           // Update the army, returns a game statuss
        void draw(Frame &f);       // Draw the whole army to the frame
};

#endif
