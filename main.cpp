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
            state = Endgame::lose;
            myqueue.push(state);
            break;
        case Endgame::win:
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
    initscr(); // Initialize ncurses
    cbreak();
    keypad(stdscr, TRUE); // Allows interception of more keyboard keys
    curs_set(0); // Hide cursor
    noecho(); // Typed letters will not be shown on screen
    timeout(5); // 5 millisecond timeout for get character so it doesn't block the program
    clear(); // Clear screen, enter alternate screen mode
    Army invaders;
    Player player;
    int64_t invaders_time_now = millis();
    int invaders_update_duration = 2500;
    int rows_descended = 0;
    int64_t shots_time_now = millis();
    int shots_update_duration = 50;
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
        if (millis()-invaders_time_now >= invaders_update_duration) {
            update_invaders(invaders);
            if (invaders_update_duration-250 >= 250 && invaders.rows_descended > rows_descended) {
                invaders_update_duration -= 250;
                rows_descended = invaders.rows_descended;
            }
            invaders_time_now = millis();
        }
        if (millis()-shots_time_now >= shots_update_duration){
            player.update_shots(invaders);
            shots_time_now = millis();
        }
        // Draw and render
        invaders.draw(f);
        player.draw(f);
        f.render();
        // Ensure this is not too fast
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    Endgame result = myqueue.front();
    switch (result) {
        case Endgame::lose:
            l();
            break;
        case Endgame::win:
            w();
            break;
    }
    curs_set(1); // Show cursor
    endwin(); // Leave alternate screen mode
    return 0;
}