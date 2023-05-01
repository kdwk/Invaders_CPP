#include <bits/stdc++.h>
#include "later.h"
#include "constants.h"
#include "clear.h"
#include "frame.h"
#include "invader.h"
#include "drawable_parent.h"


using namespace std;

// void get_input() {
//     while (true) {

//     }
// }

void update_invaders(Army &invaders) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1000));
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
    thread update_army(&update_invaders, invaders);
    while (true) {
        Frame f;
        // Get user input
        
        // Update player

        // Draw and render
        vector<Drawable*> drawables = {&invaders};
        for (Drawable* drawable: drawables) {
            drawable->draw(f);
        }
        f.render();
        // Ensure this is not too fast
        this_thread::sleep_for(chrono::milliseconds(1));
    }
    return 0;
}