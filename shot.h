#ifndef SHOTS
#define SHOTS
// This header declares the Shot class

#include <bits/stdc++.h>
#include "drawable_parent.h"
#include "lib.h"
#include "frame.h"
#include "invader.h"

class Shot : public Drawable {
    public:
        int x;
        int y;
        Health stat;  // Keep track of whether it's alive
        Shot(int init_x, int init_y); // Initialize a shot at a coordinate
        bool update(Army &army);      // Update the shot; kills the invader if the shot reaches one
        void draw(Frame &f);          // Draw the shot on the frame
};

#endif