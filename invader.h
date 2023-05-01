#ifndef INVADER
#define INVADER

#include <bits/stdc++.h>
#include "frame.h"

enum Health {
    alive,
    dead
};

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

class Army {
    std::vector<Invader> army;
    Direction vec;
    int move_timer_value;
    Symbol sym;
    bool are_all_dead();
    bool reached_bottom();
    bool reached_left_wall();
    bool reached_right_wall();
    void csd(Frame &f);
    public:
        Army();
        void update(Frame &f);
};

#endif
