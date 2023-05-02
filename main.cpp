#include <bits/stdc++.h>
#include "later.h"
#include "lib.h"
#include "clear.h"
#include "frame.h"
#include "invader.h"
#include "player.h"
#include "drawable_parent.h"
#include "endgame.h"

using namespace std;

Endgame state = Endgame::cont;
mutex state_mutex;
queue<Endgame> myqueue;

void get_input(Player &player) {
    // Does not work
    while (true) {
        int keypress = 0;
        switch (keypress=getchar()) {
            case KEY_LEFT:
                player.move_left();
                break;
            case KEY_RIGHT:
                player.move_right();
                break;
            case KEY_SPACE:
                player.shoot();
                break;
            case KEY_Q:
                cout << "Lose";
                state = Endgame::lose;
                state_mutex.lock();
                myqueue.push(state);
                state_mutex.unlock();
                break;
        }
    }
}

void update_invaders(Army &invaders) {
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

void update_player_shots(Player &player, Army &invaders) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(25));
        player.update_shots(invaders);
    }
}

// void test() {
//     w();
// }

int main() {
    clear();
    // f.draw(3,NUM_ROWS-1,"A");
    // Later render1(1000, false, &test, f);
    // cout << "success" << endl;
    // TODO: gameloop
    Army invaders;
    Player player;
    thread update_army(&update_invaders, ref(invaders));
    thread update_shots(&update_player_shots, ref(player), ref(invaders));
    thread input(&get_input, ref(player));
    state_mutex.lock();
    // Game loop
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
        player.draw(f);
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