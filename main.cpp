#include <bits/stdc++.h>
#include <ncurses.h>
#include "lib.h"
#include "frame.h"
#include "invader.h"
#include "player.h"
#include "drawable_parent.h"

using namespace std;

Status state = Status::cont; // The default game status should be 'continue'

// Retrieved from https://stackoverflow.com/questions/3557221/how-do-i-measure-time-in-c#3557272
int64_t millis() {
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return ((int64_t) now.tv_sec) * 1000 + ((int64_t) now.tv_nsec) / 1000000;
}

void update_invaders(Army &invaders) {
    state = invaders.update(); // Returns a game status to see if there is need to end the game
}

int main() {
    initscr();                     // Initialize ncurses
    cbreak();
    keypad(stdscr, TRUE);          // Allows interception of more keyboard keys
    setlocale(LC_ALL, "");         // Allows UTF-8 characters to be displayed correctly
    curs_set(0);                   // Hide cursor
    noecho();                      // Typed letters will not be shown on screen
    greet();                       // Shows greeting
    timeout(5);                    // 5 millisecond timeout for get character so it doesn't block the program
    clear();                       // Clear screen, enter alternate screen mode
    Army invaders;
    Player player;
    int64_t invaders_time_now = millis(); // Invaders: mark time
    int invaders_update_duration = INITIAL_INVADER_SPEED;  // Initial invaders update rate
    int rows_descended = 0;               // Number of rows invaders have descended
    int64_t shots_time_now = millis();    // Shots: mark time
    int shots_update_duration = 50;       // Shots update rate

    // Game loop
    while (state == Status::cont) {       // If the game status is "continue", keep looping
        Frame f;
        int keypress = getch();           // Get keyboard input
        switch (keypress) {               // Respond to keyboard input
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
                state = Status::lose;   // Put 'lose' status in the queue, loop will break next cycle
                break;
        }
        // Updates
        if (millis()-invaders_time_now >= invaders_update_duration) {                              // Check whether it is time to update the invaders again
            update_invaders(invaders);
            if (invaders_update_duration-250 >= 250 && invaders.rows_descended > rows_descended) { // If invaders descended a row, increase speed, min update duration 250ms
                invaders_update_duration -= 250;
                rows_descended = invaders.rows_descended;
            }
            invaders_time_now = millis();                                                          // Invaders: reset mark time
        }
        if (millis()-shots_time_now >= shots_update_duration){                                     // Check whether it is time to update the shots again
            player.update_shots(invaders);
            shots_time_now = millis();                                                             // Shots: reset mark time
        }
        // Draw and render
        invaders.draw(f);        // Army draws itself on the frame
        player.draw(f);          // Player draws itself on the frame
        f.render(player.score);  // Frame pushed to screen
        // Ensure this is not too fast
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    switch (state) {            // A game status update broke the game loop; check what it is
        case Status::lose:
            l();
            break;
        case Status::win:
            w();
            break;
    }
    curs_set(1); // Show cursor
    endwin();    // Leave alternate screen mode
    return 0;
}