#ifndef SHOTS
#define SHOTS

#include <bits/stdc++.h>
#include "drawable_parent.h"
#include "lib.h"
#include "frame.h"
#include "invader.h"

class Shot : public Drawable {
    public:
        int x;
        int y;
        bool exploding;
        Health stat;
        Shot(int init_x, int init_y);
        void update(Army &army);
        void draw(Frame &f);
};

#endif