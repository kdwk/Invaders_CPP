#include <bits/stdc++.h>
#include "invader.h"
#include "lib.h"
#include "frame.h"

using namespace std;

bool Army::are_all_dead() {
    // Returns if all the invaders are dead
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
    // Returns if the army has reached the player's starship
    for (Invader invader: army) {
        if (invader.stat == alive && invader.y >= NUM_ROWS-1) {
            return true;
        }
    }
    return false;
}

bool Army::reached_left_wall() {
    // Returns if the army has reached the left edge of the screen
    for (Invader invader: army) {
        if (invader.stat == alive && invader.x <= 0) {
            return true;
        }
    }
    return false;
}

bool Army::reached_right_wall() {
    // Returns if the army has reached the right edge of the screen
    for (Invader invader: army) {
        if (invader.stat == alive && invader.x >= NUM_COLS-1) {
            return true;
        }
    }
    return false;
}

Army::Army(int NUM_INVADERS) {
    srand(time(NULL));
    for (int y=1; y<9; y++) {
        for (int x=1; x<NUM_COLS-2; x++) {
            if (army.size() >= NUM_INVADERS) {break;} // If army size is already at maximum, don't add new invaders
            int decision = rand()%2;                  // Randomly decide if there should be an invader here at this coordinate
            if (decision) {
                army.push_back(Invader{x,y,Health::alive});   // Add an invader to the army
            }
        }
    }
    vec = Direction::left;   // Go left first
    sym = Symbol::plus;      // Army symbol is a plus sign at first
    rows_descended = 0;
}

Status Army::update() {
    if (are_all_dead()) {return Status::win;}  // If army all dead, trigger win
    vector<int> dead_invaders = {};
    for (int index: dead_invaders) {
        army.erase(army.begin()+index);
    }
    if (vec == Direction::left) {
        // Move to the left by one
        // If to the left wall set next move as down
        for (Invader &invader: army) {
            if (invader.x-1 >= 0 && invader.stat==Health::alive) {
                invader.x -= 1;
            }
        }
        if (reached_left_wall()) {
            prev_vec = vec;
            vec = Direction::down;
        }
    } else if (vec == Direction::right) {
        // Move to the right by one
        // If to the right wall set next move as down
        for (Invader &invader: army) {
            if (invader.x+1 <= NUM_COLS-1 && invader.stat==Health::alive) {
                invader.x += 1;
            }
        }
        if (reached_right_wall()) {
            prev_vec = vec;
            vec = Direction::down;
        }
    } else if (vec == Direction::down) {
        // Move down by one
        // If at left wall set next move as right
        // If at right wall set next move as left
        // If reached the bottom, trigger lose
        for (Invader &invader: army) {
            if (invader.stat == Health::alive) {
                invader.y += 1;
            }
        }
        rows_descended += 1;
        if (reached_bottom()) {return Status::lose;} // Invaders have reached the starship
        if (prev_vec == Direction::left) {           // Switch directions after going down
            prev_vec = vec;
            vec = Direction::right;
        }
        else if (prev_vec == Direction::right) {
            prev_vec = vec;
            vec = Direction::left;
        }
    }
    switch (sym) {                             // Change symbol of the army
        case Symbol::plus:
            sym = Symbol::cross;
            break;
        case Symbol::cross:
            sym = Symbol::plus;
            break;
    }
    if (reached_bottom()) {return Status::lose;}
    return Status::cont;
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
