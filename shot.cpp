#include <bits/stdc++.h>
#include "shot.h"
#include "lib.h"
#include "frame.h"

Shot::Shot(int init_x, int init_y) {
    x = init_x;
    y = init_y;
    exploding = false;
}

void Shot::update() {
    if (y-1 >= 0) {
        y -= 1;
    } else {
        stat = Health::dead;
    }
    // Parent function should check whether shot touches invader
}

void Shot::draw(Frame &f) {
    if (exploding) {
        f.content[x][y] = "*";
    } else {
        f.content[x][y] = "|";
    }
}

void Shot::explode() {
    exploding = true;
}