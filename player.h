#ifndef PLAYER
#define PLAYER

#include <bits/stdc++.h>
#include "drawable_parent.h"

class Player : public Drawable {
    public:
        int x;
        int y;
        void move_left();
        void move_right();
        bool shoot();
        void update_shots();
        Player();
};

#endif