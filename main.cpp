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
    int rows_descended = 0;
    int duration = 2500;
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(duration));
        tuple<Endgame, int> result = invaders.update();
        switch (get<0>(result)) {
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
        if (get<1>(result) > rows_descended && duration-250 > 250) {
            duration -= 250;
        }
    }
}

void update_player_shots(Player &player, Army &invaders) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(25));
        player.update_shots(invaders);
    }
}

void render(Frame &f) {
    while (true) {
        f.render();
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

static char get_input() {
    char input;
    cin >> input;
    return input;
}

int main() {
    aclear();
    // struct termios term_settings;
    // SetKeyboardNonBlock(&term_settings);
    chrono::milliseconds timeout(10);
    Army invaders;
    Player player;
    thread update_army_thread(&update_invaders, ref(invaders));
    thread update_shots_thread(&update_player_shots, ref(player), ref(invaders));
    // thread input_thread(&get_input, ref(player));
    bool init_render_thread = false;
    state_mutex.lock();

    // Game loop
    while (myqueue.empty()) {
        state_mutex.unlock();
        Frame f;
        // Get user input
        future<char> future = async()
        int keypress = 0;
        switch (???) { // TODO
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
        // Update player

        // Draw and render
        // vector<Drawable*> drawables = {&invaders};
        // // for (Drawable* drawable: drawables) {
        // //     drawable->draw(f);
        // // }
        invaders.draw(f);
        player.draw(f);
        if (!init_render_thread) {
            // Very hacky, but will have to do
            thread render_thread(&render, ref(f));
            init_render_thread = true;
        }
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
    update_army_thread.join();
    update_shots_thread.join();
    // input_thread.join();
    return 0;
}