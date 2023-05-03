#include <bits/stdc++.h>
#include <curses.h>
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

// char keypress = 0;
// mutex keypress_mutex;
// queue<char> myqueue2;

// void get_input(Player &player) {
//     // Does not work
//     while (true) {
//         int keypress = 0;
//         switch (keypress=getchar()) {
//             case KEY_LEFT:
//                 player.move_left();
//                 break;
//             case KEY_RIGHT:
//                 player.move_right();
//                 break;
//             case KEY_SPACE:
//                 player.shoot();
//                 break;
//             case KEY_Q:
//                 cout << "Lose";
//                 state = Endgame::lose;
//                 state_mutex.lock();
//                 myqueue.push(state);
//                 state_mutex.unlock();
//                 break;
//         }
//     }
// }

void update_invaders(Army &invaders) {
    int rows_descended = 0;
    int duration = 2500;
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(duration));
        tuple<Endgame, int> result = invaders.update();
        switch (get<0>(result)) {
            case Endgame::cont:
                cout << "Cont";
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
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

bool stdinHasData() {
    // using a timeout of 0 so we aren't waiting:
    struct timespec timeout{ 0l, 0l };

    // create a file descriptor set
    fd_set fds{};

    // initialize the fd_set to 0
    FD_ZERO(&fds);
    // set the fd_set to target file descriptor 0 (STDIN)
    FD_SET(0, &fds);

    // pselect the number of file descriptors that are ready, since
    //  we're only passing in 1 file descriptor, it will return either
    //  a 0 if STDIN isn't ready, or a 1 if it is.
    return pselect(0 + 1, &fds, nullptr, nullptr, &timeout, nullptr) == 1;
}

void get_input(Player &player) {
    int keypress{ 0 };
    // continue looping until the user enters a lowercase 'q'
    while (true)
    {
        if (stdinHasData()) {
            keypress = std::cin.get();
            switch (keypress) {
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
}

int main() {
    // aclear();
    initscr();
    cbreak();
    noecho();
    clear();
    Army invaders;
    Player player;
    thread update_army_thread(&update_invaders, ref(invaders));
    thread update_shots_thread(&update_player_shots, ref(player), ref(invaders));
    // thread input_thread(&get_input, ref(player));
    // bool init_render_thread = false;
    state_mutex.lock();

    // Game loop
    while (myqueue.empty()) {
        state_mutex.unlock();
        Frame f;
        // Update player

        // Draw and render
        // vector<Drawable*> drawables = {&invaders};
        // // for (Drawable* drawable: drawables) {
        // //     drawable->draw(f);
        // // }
        invaders.draw(f);
        player.draw(f);
        f.render();
        // if (!init_render_thread) {
        //     // Very hacky, but will have to do
        //     thread render_thread(&render, ref(f));
        //     init_render_thread = true;
        // }
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
    endwin();
    return 0;
}