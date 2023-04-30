#ifndef FRAME
#define FRAME

#include <bits/stdc++.h>

class Frame {
    std::vector<std::vector<std::string>> content;
    void composite();
    public:
        Frame();
        void render();
};

#endif