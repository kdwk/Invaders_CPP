#include <bits/stdc++.h>
#include "clear.h"
#include "frame.h"
#include "constants.h"

using namespace std;

Frame::Frame() {
    for (int i=0; i<NUM_COLS; i++) {
        vector<string> col = {};
        for (int i=0; i<NUM_ROWS; i++){
            col.push_back(" ");
        }
        content.push_back(col);
    }
};

void Frame::render() {
    clear();
    for (int y=0; y<NUM_ROWS; y++){
        for (int x=0; x<NUM_COLS; x++) {
            cout << content[x][y];
        }
        cout << endl;
    }
};

bool Frame::draw(int x, int y, string object) {
    if (content[x][y] != " ") {
        content[x][y] = object;
        return true;
    }
    return false;
}
