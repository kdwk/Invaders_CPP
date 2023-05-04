#ifndef INVADER
#define INVADER

#include <bits/stdc++.h>
#include "lib.h"
#include "frame.h"
#include "drawable_parent.h"

enum Symbol {
    plus,
    cross
};

struct Invader {
    int x;
    int y;
    Health stat;
};

enum Direction {
    left,
    right,
    down
};

class Army : public Drawable{
    Direction vec;
    Symbol sym;
    bool reached_bottom();
    bool reached_left_wall();
    bool reached_right_wall();
    public:
        int rows_descended;
        std::vector<Invader> army;
        Army(int NUM_INVADERS);
        bool are_all_dead();
        Status update();
        void draw(Frame &f);
};

#endif
