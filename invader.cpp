#include <bits/stdc++.h>
#include "invader.h"
#include "lib.h"
#include "frame.h"

using namespace std;

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
        if (invader.stat == alive && invader.y >= NUM_ROWS-2) {
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

Army::Army() {
    for (int x=1; x<NUM_COLS-2; x++) {
        for (int y=1; y<9; y++) {
            if (army.size() >= NUM_INVADERS) {break;}
            int decision = rand()%2;
            if (decision) {
                army.push_back(Invader{x,y,alive});
            }
        }
    }
    vec = Direction::left;
    sym = Symbol::plus;
    // TODO: hook up update mechanism...?
}

Endgame Army::update() {
    // If army all dead, trigger win
    if (are_all_dead()) {return Endgame::win;}
    switch (sym) {
        case Symbol::plus:
            sym = Symbol::cross;
            break;
        case Symbol::cross:
            sym = Symbol::plus;
            break;
    }
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
        rows_descended += 1;
        if (reached_bottom()) {return Endgame::lose;}
        if (reached_left_wall()) {vec = Direction::right;}
        else if (reached_right_wall()) {vec = Direction::left;}
    }
    if (reached_bottom()) {return Endgame::lose;}
    return Endgame::cont;
}

void Army::draw(Frame &f) {
    switch (sym) {
        case Symbol::plus:
            for (Invader invader: army) {
                if (invader.stat == Health::alive) {
                    f.content[invader.x][invader.y] = "+";
                }
            }
            break;
        case Symbol::cross:
            for (Invader invader: army) {
                if (invader.stat == Health::alive) {
                    f.content[invader.x][invader.y] = "x";
                }
            }
            break;
    }
}