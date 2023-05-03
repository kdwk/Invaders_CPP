#ifndef PLAYER
#define PLAYER

#include <bits/stdc++.h>
#include "drawable_parent.h"
#include "shot.h"
#include "invader.h"

class Player : public Drawable {
    public:
        int x;
        int y;
        int score;
        std::vector<Shot> shots;
        void move_left();
        void move_right();
        bool shoot();
        void update_shots(Army &army);
        void draw(Frame &f);
        Player();
};

#endif