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

void update_invaders(Army &invaders) {
    while (true) {
        sleep(1);
        invaders.update();
    }
}

int main() {
    clear();
    // f.draw(3,NUM_ROWS-1,"A");
    // Later render1(1000, false, &test, f);
    // cout << "success" << endl;
    // TODO: gameloop
    Army invaders;
    while (true) {
        Frame f;
        thread update_army(&update_invaders, invaders);
        
    }
    return 0;
}