#include <bits/stdc++.h>
#include <ncurses.h>
#include "lib.h"
#include "frame.h"
#include "invader.h"
#include "player.h"
#include "drawable_parent.h"

using namespace std;

Status state = Status::cont; // The default game status should be 'continue'
int NUM_INVADERS = 50;
int INITIAL_INVADER_SPEED = 2500; // Default update duration in milliseconds

// Retrieved from https://stackoverflow.com/questions/3557221/how-do-i-measure-time-in-c#3557272
int64_t millis() {
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return ((int64_t) now.tv_sec) * 1000 + ((int64_t) now.tv_nsec) / 1000000;
}

void update_invaders(Army &invaders) {
    state = invaders.update(); // Returns a game status to see if there is need to end the game
}

void update_level_info(Level level) {
    // Set number of invaders and invader speed according to level selected
    switch (level) {
        case Level::easy:
            break;
        case Level::medium:
            NUM_INVADERS = 70;
            INITIAL_INVADER_SPEED = 1500;
            break;
        case Level::hard:
            NUM_INVADERS = 100;
            INITIAL_INVADER_SPEED = 600;
            break;
        case Level::extreme:
            NUM_INVADERS = 140;
            INITIAL_INVADER_SPEED = 500;
            break;
        case Level::test:
            NUM_INVADERS = 1;
            INITIAL_INVADER_SPEED = 10000;
            break;
    }
}

int main() {
    initscr();                     // Initialize ncurses
    cbreak();
    keypad(stdscr, TRUE);          // Allows interception of more keyboard keys
    setlocale(LC_ALL, "");         // Allows UTF-8 characters to be displayed correctly...?
    curs_set(0);                   // Hide cursor
    noecho();                      // Typed letters will not be shown on screen
    start_color();                 // Allows usage of colours
    greet();                       // Shows greeting
    update_level_info(choose_difficulty());
    timeout(5);                    // 5 millisecond timeout for get character so it doesn't block the program
    clear();                       // Clear screen, enter alternate screen mode
    Army invaders(NUM_INVADERS);
    Player player;
    int64_t invaders_time_now = millis();                  // Invaders: mark time
    int invaders_update_duration = INITIAL_INVADER_SPEED;  // Initial invaders update rate
    int rows_descended = 0;                                // Number of rows invaders have descended
    int64_t shots_time_now = millis();    // Shots: mark time
    int shots_update_duration = 50;       // Shots update rate

    int64_t game_duration_start = millis(); // Game duration: mark time
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
                state = Status::lose;   // Loop will break next cycle
                break;
            case KEY_P:
                state = Status::paus;   // Loop will break next cycle
                break;
        }
        // Updates
        if (millis()-shots_time_now >= shots_update_duration){                                     // Check whether it is time to update the shots again
            player.update_shots(invaders);
            shots_time_now = millis();                                                             // Shots: reset mark time
        }
        if (invaders.are_all_dead() || millis()-invaders_time_now >= invaders_update_duration) {   // Check whether it is time to update the invaders again
            update_invaders(invaders);
            if (invaders_update_duration-250 >= 500 && invaders.rows_descended > rows_descended) { // If invaders descended a row, increase speed, min update duration 250ms
                invaders_update_duration -= 250;
                rows_descended = invaders.rows_descended;
            }
            invaders_time_now = millis();                                                          // Invaders: reset mark time
        }
        // Draw and render
        invaders.draw(f);        // Army draws itself on the frame
        player.draw(f);          // Player draws itself on the frame
        f.render(player.score, NUM_INVADERS);            // Frame pushed to screen
        this_thread::sleep_for(chrono::milliseconds(1)); // Ensure this is not too fast
        if (state == Status::paus) {
            timeout(-1);            // getch() have indefinite timeout, block execution
            getch();                // Press any key to continue
            state = Status::cont;   // Continue
            timeout(5);             // Restore original timeout of getch() such that it doesn't block execution
        }
    }
    int64_t game_duration_end = millis(); // Game duration: mark time end
    double game_duration_seconds = (game_duration_end-game_duration_start)/1000.0; // Game duration in milliseconds

    switch (state) {            // A game status update broke the game loop; check what it is
        case Status::lose:
            l();
            break;
        case Status::win:
            w(game_duration_seconds);
            break;
    }
    curs_set(1); // Show cursor
    endwin();    // Leave alternate screen mode
    return 0;
}