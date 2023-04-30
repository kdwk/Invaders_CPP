#include <bits/stdc++.h>
#include "invader.h"
#include "constants.h"
#include "later.h"
#include "endgame.h"

using namespace std;

extern Frame f;

bool Army::are_all_dead() {
    bool all_dead = true;
    for (Invader invader: army) {
        if (invader.stat == alive) {
            all_dead = false;
            break;
        }
    }
    return all_dead;
}

bool Army::reached_bottom() {
    for (Invader invader: army) {
        if (invader.stat == alive && invader.y >= NUM_ROWS-1) {
            return true;
        }
    }
    return false;
}

bool Army::reached_left_wall() {
    for (Invader invader: army) {
        if (invader.stat == alive && invader.x <= 0) {
            return true;
        }
    }
    return false;
}

bool Army::reached_right_wall() {
    for (Invader invader: army) {
        if (invader.stat == alive && invader.x >= NUM_COLS-1) {
            return true;
        }
    }
    return false;
}

void Army::csd() {
    for (Invader invader: army) {
        switch (sym) {
            case Symbol::plus: f.content[invader.x][invader.y] = '+'; // TODO
            case Symbol::cross: f.content[invader.x][invader.y] = 'x'; // TODO
        }
    }
}

Army::Army() {
    for (int x=1; x<NUM_COLS-2; x++) {
        for (int y=1; y<9; y++) {
            int decision = rand()%2;
            if (decision) {
                army.push_back(Invader{x,y,alive});
            }
        }
    }
    vec = Direction::left;
    sym = Symbol::plus;
    // TODO: hook up update mechanism
}


void Army::update() {
    // If army all dead, trigger win
    if (are_all_dead()) {win();}
    if (vec == Direction::left) {
        // Move to the left by one
        // If to the left wall set next move as down
        for (Invader &invader: army) {invader.x -= 1;}
        if (reached_left_wall()) {vec = Direction::down;}
    } else if (vec == Direction::right) {
        // Move to the right by one
        // If to the right wall set next move as down
        for (Invader &invader: army) {invader.x += 1;}
        if (reached_right_wall()) {vec = Direction::down;}
    } else if (vec == Direction::down) {
        // Move down by one
        // If at left wall set next move as right
        // If at right wall set next move as left
        // If reached the bottom, trigger lose
        for (Invader &invader: army) {invader.y += 1;}
        if (reached_bottom()) {lose();}
        if (reached_left_wall()) {vec = Direction::right;}
        else if (reached_right_wall()) {vec = Direction::left;}
    }
}