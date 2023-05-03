#ifndef FRAME
#define FRAME

#include <bits/stdc++.h>

class Frame {
    void composite(int score);
    public:
        std::vector<std::vector<std::string>> content;
        Frame();
        void render(int score);
};

#endif