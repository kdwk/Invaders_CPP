#include <bits/stdc++.h>
#include "player.h"
#include "lib.h"
#include "invader.h"

using namespace std;

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
    vector<int> dead_shots = {};
    for (int i=0; i<shots.size(); i++) {
        shots[i].update(army);
        switch (shots[i].stat) {
            case Health::dead:
                dead_shots.push_back(i);
                break;
            case Health::alive:
                continue;
                break;
        }
    }
    for (int dead_shot: dead_shots) {
        shots.erase(shots.begin()+dead_shot);
    }
}

void Player::draw(Frame &f) {
    f.content[x][y] = "A";
    for (Shot shot: shots) {
        shot.draw(f);
    }
}