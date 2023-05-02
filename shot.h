#ifndef SHOTS
#define SHOTS

#include <bits/stdc++.h>
#include "drawable_parent.h"

class Shot : public Drawable {
    public:
        int x;
        int y;
        bool exploding;
};

#endif