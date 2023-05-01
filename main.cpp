#include <bits/stdc++.h>
#include "later.h"
#include "constants.h"
#include "clear.h"
#include "frame.h"
#include "invader.h"


using namespace std;

// void get_input() {
//     while (true) {

//     }
// }

int main() {
    clear();
    // f.draw(3,NUM_ROWS-1,"A");
    // Later render1(1000, false, &test, f);
    // cout << "success" << endl;
    // TODO: gameloop
    Army invaders;
    while (true) {
        Frame f;
        invaders.update(f);
        
    }
    return 0;
}