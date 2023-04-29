#include <bits/stdc++.h>
#include "invader.h"
#include "constants.h"

using namespace std;

Army::Army() {
    vector<Invader> army;
    for (int x=1; x<NUM_COLS-2; x++) {
        for (int y=1; y<9; y++) {
            int decision = rand()%2;
            if (decision) {
                army.push_back(Invader{x,y,alive});
            }
        }
    }
    vec = left; // TODO
}

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
    int max_y = max() // TODO
}