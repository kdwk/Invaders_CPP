#ifndef FRAME
#define FRAME

#include <bits/stdc++.h>
#include "invader.h"

class Frame {
    void composite();
    public:
        std::vector<std::vector<std::string>> content;
        Frame();
        void render();
};

#endif