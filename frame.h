#ifndef FRAME
#define FRAME

#include <bits/stdc++.h>

class Frame {
    int num_cols;
    int num_rows;
    std::vector<std::vector<std::string>> content;
    public:
        Frame();
        void render();
        bool draw(int x, int y, std::string content);
};

#endif