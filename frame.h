#ifndef FRAME
#define FRAME

#include <bits/stdc++.h>

class Frame {
    void composite(int score, int NUM_INVADERS);
    public:
        std::vector<std::vector<std::string>> content;
        Frame();
        void render(int score, int NUM_INVADERS);
};

#endif