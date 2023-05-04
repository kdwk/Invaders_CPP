#ifndef PLAYER
#define PLAYER
// This header declares the Player class

#include <bits/stdc++.h>
#include "drawable_parent.h"
#include "shot.h"
#include "invader.h"

class Player : public Drawable {
    public:
        int x;
        int y;
        int score;
        std::vector<Shot> shots;       // Keep track of all the shots fired by the player that are still alive
        void move_left();
        void move_right();
        bool shoot();
        void update_shots(Army &army); // Calls the update function of each shot
        void draw(Frame &f);           // Draw the player on the frame
        Player();                      // Initialize a new player
};

#endif