#include <bits/stdc++.h>
#include "player.h"
#include "lib.h"
#include "invader.h"

Player::Player() {
    x = NUM_COLS/2;
    y = NUM_ROWS-1;
    shots = {};
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
    if (shots.size() < 2) {
        shots.push_back(Shot(x, y-1));
        return true;
    } else {
        return false;
    }
}

void Player::update_shots(Army &army) {
    for (auto shot=shots.begin(); shot!=shots.end(); shot++) {
        shot->update(army);
        switch (shot->stat) {
            case Health::dead:
                shots.erase(shot);
                break;
            case Health::alive:
                continue;
                break;
            default:
                int a = 1; // Do nothing but idk how to actually do nothing
                break;
        }
    }
}

void Player::draw(Frame &f) {
    f.content[x][y] = "A";
    for (Shot shot: shots) {
        shot.draw(f);
    }
}