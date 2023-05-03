#include <bits/stdc++.h>
#include "shot.h"
#include "lib.h"
#include "frame.h"
#include "invader.h"

using namespace std;

Shot::Shot(int init_x, int init_y) {
    x = init_x;
    y = init_y;
    exploding = false;
}

bool Shot::update(Army &army) {
    if (y-1 >= 0) {
        y -= 1;
    } else {
        stat = Health::dead;
        return false;
    }
    for (Invader &invader: army.army) {
        if (invader.x == x && invader.y == y && invader.stat!=Health::dead) {
            invader.stat = Health::dead;
            // exploding = true;
            stat = Health::dead;
            return true;
        }
    }
    return false;
}

void Shot::draw(Frame &f) {
    if (exploding) {
        f.content[x][y] = "*";
    } else {
        f.content[x][y] = "|";
    }
}
