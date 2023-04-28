#ifndef FRAME
#define FRAME

#include <bits/stdc++.h>

class Frame {
    std::vector<std::vector<std::string>> content;
    public:
        Frame();
        void render();
        bool draw(int x, int y, std::string content);
};

#endif