#ifndef INVADER
#define INVADER

#include <bits/stdc++.h>

enum Health {
    alive,
    dead
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
    // TODO: add a move_timer
    public:
        Army();
        bool are_all_dead();
        bool reached_bottom();
};

#endif
