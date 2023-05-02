#include <bits/stdc++.h>
#include "shot.h"
#include "lib.h"
#include "frame.h"
#include "invader.h"

Shot::Shot(int init_x, int init_y) {
    x = init_x;
    y = init_y;
    exploding = false;
}

void Shot::update(Army &army) {
    if (y-1 >= 0) {
        y -= 1;
    } else {
        stat = Health::dead;
    }
    for (Invader &invader: army.army) {
        if (invader.x == x && invader.y == y) {
            invader.stat = Health::dead;
            stat = Health::dead;
            break;
        }
    }
}

void Shot::draw(Frame &f) {
    if (exploding) {
        f.content[x][y] = "*";
    } else {
        f.content[x][y] = "|";
    }
}
