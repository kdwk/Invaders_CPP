#include <bits/stdc++.h>
#include "player.h"
#include "lib.h"
#include "invader.h"

using namespace std;

Player::Player() {
    // New player should be on middle of bottom row
    x = NUM_COLS/2;
    y = NUM_ROWS-1;
    shots = {};
    score = 0;
}

void Player::move_left() {
    if (x > 0) {
        x -= 1;
    }
}

void Player::move_right() {
    if (x < NUM_COLS-1) {
        x += 1;
    }
}

bool Player::shoot() {
    // If player has less than max no of shots allowed, add a new shot at 1 pixel above the player
    if (shots.size() < NUM_SHOTS_ALLOWED) {
        shots.push_back(Shot(x, y-1));
        return true;
    } else {
        return false;
    }
}

void Player::update_shots(Army &army) {
    vector<int> dead_shots = {};                     // All the dead shots to be erased
    for (int i=0; i<shots.size(); i++) {
        bool killed_invader = shots[i].update(army); // Call the update function of the shot
        switch (shots[i].stat) {
            case Health::dead:
                dead_shots.push_back(i);
                break;
            case Health::alive:
                break;
        }
        if (killed_invader) {score += 1;}
    }
    for (int dead_shot: dead_shots) {
        shots.erase(shots.begin()+dead_shot);        // Erase all the dead shots
    }
}

void Player::draw(Frame &f) {
    // Draw the player on the frame
    f.content[x][y] = "A";
    // Draw the shots on the frame
    for (Shot shot: shots) {
        shot.draw(f);
    }
}