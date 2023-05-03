#include <bits/stdc++.h>
#include <curses.h>
#include "lib.h"
#include "frame.h"
#include "invader.h"
#include "player.h"
#include "drawable_parent.h"

using namespace std;

Endgame state = Endgame::cont;
queue<Endgame> myqueue;
queue<int> index_invaders_killed;

// Retrieved from https://stackoverflow.com/questions/3557221/how-do-i-measure-time-in-c#3557272
int64_t millis()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return ((int64_t) now.tv_sec) * 1000 + ((int64_t) now.tv_nsec) / 1000000;
}

void update_invaders(Army &invaders) {
    Endgame result = invaders.update();
    switch (result) {
        case Endgame::cont:
            break;
        case Endgame::lose:
            // cout << "Lose";
            state = Endgame::lose;
            myqueue.push(state);
            break;
        case Endgame::win:
            // cout << "Win";
            state = Endgame::win;
            myqueue.push(state);
            break;
    }
}

void render(Frame &f) {
    while (true) {
        f.render();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    // aclear();
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    timeout(5);
    clear();
    Army invaders;
    Player player;
    int64_t time_now = millis();
    int duration = 2500;
    int rows_descended = 0;
    // Game loop
    while (myqueue.empty()) {
        Frame f;
        int keypress = getch();
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
                myqueue.push(Endgame::lose);
                break;
        }
        // Updates
        if (millis()-time_now >= duration) {
            update_invaders(invaders);
            if (duration-250 >= 250 && invaders.rows_descended > rows_descended) {
                duration -= 250;
                rows_descended = invaders.rows_descended;
            }
            time_now = millis();
        }
        player.update_shots(invaders);
        //Draw and render
        invaders.draw(f);
        player.draw(f);
        f.render();
        // Ensure this is not too fast
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    // cout << "Out of while loop";
    Endgame result = myqueue.front();
    switch (result) {
        case Endgame::lose:
            l();
            break;
        case Endgame::win:
            w();
            break;
        default:
            // cout << "What??" << endl;
            break;
    }
    curs_set(1);
    endwin();
    return 0;
}