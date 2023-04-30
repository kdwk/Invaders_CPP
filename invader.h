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
    char symbol;
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
    bool are_all_dead();
    bool reached_bottom();
    bool reached_left_wall();
    bool reached_right_wall();
    public:
        Army();
        void update();
};

#endif
