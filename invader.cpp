#include <bits/stdc++.h>
#include "invader.h"
#include "constants.h"

using namespace std;

Army::Army() {
    vector<Invader> army;
    for (int x=1; x<NUM_COLS-2; x++) {
        for (int y=1; y<9; y++) {
            if (x%2==0 && y%2==0) {
                army.push_back(Invader{x,y});
            }
        }
    }
    // TODO: set a move_timer
}