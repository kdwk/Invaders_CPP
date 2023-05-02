#include <bits/stdc++.h>
#include "later.h"
#include "constants.h"
#include "clear.h"
#include "frame.h"
#include "invader.h"
#include "drawable_parent.h"
#include "endgame.h"


using namespace std;

// void get_input() {
//     while (true) {

//     }
// }

Endgame state = Endgame::cont;
mutex state_mutex;
queue<Endgame> myqueue;

Endgame update_invaders(Army &invaders) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1000));
        switch (invaders.update()) {
            case Endgame::cont:
                cout << "Cont";
                int a; // Do nothing, but idk how to actually do nothing
                break;
            case Endgame::lose:
                cout << "Lose";
                state = Endgame::lose;
                state_mutex.lock();
                myqueue.push(state);
                state_mutex.unlock();
                break;
            case Endgame::win:
                cout << "Win";
                state = Endgame::win;
                state_mutex.lock();
                myqueue.push(state);
                state_mutex.unlock();
                break;
        }
    }
}

void test() {
    w();
}

int main() {
    clear();
    // f.draw(3,NUM_ROWS-1,"A");
    // Later render1(1000, false, &test, f);
    // cout << "success" << endl;
    // TODO: gameloop
    Army invaders;
    thread update_army(&update_invaders, ref(invaders));
    state_mutex.lock();
    while (myqueue.empty()) {
        state_mutex.unlock();
        Frame f;
        // Get user input
        
        // Update player

        // Draw and render
        // vector<Drawable*> drawables = {&invaders};
        // // for (Drawable* drawable: drawables) {
        // //     drawable->draw(f);
        // // }
        invaders.draw(f);
        f.render();
        // Ensure this is not too fast
        this_thread::sleep_for(chrono::milliseconds(1));
        state_mutex.lock();
    }
    cout << "Out of while loop";
    Endgame result = myqueue.front();
    switch (result) {
        case Endgame::lose:
            l();
            break;
        case Endgame::win:
            w();
            break;
        default:
            cout << "What??" << endl;
            break;
    }
    update_army.join();
    return 0;
}