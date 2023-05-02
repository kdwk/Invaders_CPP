#ifndef SHOTS
#define SHOTS

#include <bits/stdc++.h>
#include "drawable_parent.h"
#include "lib.h"

class Shot : public Drawable {
    public:
        int x;
        int y;
        bool exploding;
        Health stat;
        void update();
        void explode();
};

#endif