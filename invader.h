#ifndef INVADER
#define INVADER

#include <bits/stdc++.h>

struct Invader {
    int x;
    int y;
    bool alive;
};

enum direction {
    left,
    right
};

class Army {
    std::vector<Invader> army;
    int direction;
    bool alive;
    // TODO: add a move_timer
    public:
        Army();
};

#endif