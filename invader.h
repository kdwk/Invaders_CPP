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
    int move_timer_value;
    Symbol sym;
    bool are_all_dead();
    bool reached_bottom();
    bool reached_left_wall();
    bool reached_right_wall();
    // void csd(Frame &f);
    public:
        int rows_descended;
        std::vector<Invader> army;
        Army();
        Endgame update();
        void draw(Frame &f);
};

#endif
