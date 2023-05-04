#include <bits/stdc++.h>
#include <ncurses.h>
#include "lib.h"

using namespace std;

void w() {
    clear();
    string str = "🎉 You win!";
    mvaddwstr(NUM_ROWS/2, NUM_COLS/2, wstring(str.begin(), str.end()).c_str());
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
};

void l() {
    clear();
    string str = "😕 You lose";
    mvaddwstr(NUM_ROWS/2, NUM_COLS/2, wstring(str.begin(), str.end()).c_str());
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
}

void greet() {
    clear();
    int y = NUM_ROWS/2-6;
    mvaddstr(y, 0, " __  .__   __. ____    ____  ___       _______   _______ .______          _______.");
    mvaddstr(y+1, 0, "|  | |  \\ |  | \\   \\  /   / /   \\     |       \\ |   ____||   _  \\        /       |");
    mvaddstr(y+2, 0, "|  | |   \\|  |  \\   \\/   / /  ^  \\    |  .--.  ||  |__   |  |_)  |      |   (----`");
    mvaddstr(y+3, 0, "|  | |  . `  |   \\      / /  /_\\  \\   |  |  |  ||   __|  |      /        \\   \\    ");
    mvaddstr(y+4, 0, "|  | |  |\\   |    \\    / /  _____  \\  |  '--'  ||  |____ |  |\\  \\----.----)   |   ");
    mvaddstr(y+5, 0, "|__| |__| \\__|     \\__/ /__/     \\__\\ |_______/ |_______|| _| `._____|_______/    ");
    mvaddstr(y+7, 0, "Shoot down the horde of intergalatic invaders threatening your spaceship!");
    mvaddstr(y+8, 0, "Press SPACE to shoot, LEFT/RIGHT to move, P to pause, any key to resume, Q to quit");
    mvaddstr(y+9, 0, "You can fire three bullets at the same time. You cannot fire while you move.");
    mvaddstr(y+10, 0, "You LOSE if the invaders reach you -- beware: the closer they are the faster they move!");
    mvaddstr(y+12, 0, "Press any key to continue");
    refresh();
    getch();
}
void present_options(int y) {
    mvaddstr(y, NUM_COLS/2-2, "Easy");
    mvaddstr(y+1, NUM_COLS/2-3, "Medium");
    mvaddstr(y+2, NUM_COLS/2-2, "Hard");
    mvaddstr(y+3, NUM_COLS/2-3, "Extreme");
}

Level cursor_to_level(int y, int cursor_at_level) {
    if (cursor_at_level==y) {
        return Level::easy;
    } else if (cursor_at_level==y+1) {
        return Level::medium;
    } else if (cursor_at_level==y+2) {
        return Level::hard;
    } else if (cursor_at_level==y+3) {
        return Level::extreme;
    }
}

Level choose_difficulty() {
    clear();
    int y = NUM_ROWS/2-2;
    Level level = Level::easy;
    int cursor_at_level = y;
    present_options(y);
    mvaddstr(y, NUM_COLS/2-5, ">");
    mvaddstr(y, NUM_COLS/2+5, "<");
    refresh();
    int keypress = getch();
    while (keypress != 10) {
        switch (keypress) {
            case KEY_UP:
                switch (level) {
                    case Level::easy:
                        break;
                    default:
                        present_options(y);
                        mvaddstr(cursor_at_level, NUM_COLS/2-5, " ");
                        mvaddstr(cursor_at_level, NUM_COLS/2+5, " ");
                        mvaddstr(cursor_at_level-1, NUM_COLS/2-5, ">");
                        mvaddstr(cursor_at_level-1, NUM_COLS/2+5, "<");
                        cursor_at_level -= 1;
                        level = cursor_to_level(y, cursor_at_level);
                        refresh();
                        break;
                }
                break;
            case KEY_DOWN:
                switch (level) {
                    case Level::extreme:
                        break;
                    default:
                        present_options(y);
                        mvaddstr(cursor_at_level, NUM_COLS/2-5, " ");
                        mvaddstr(cursor_at_level, NUM_COLS/2+5, " ");
                        mvaddstr(cursor_at_level+1, NUM_COLS/2-5, ">");
                        mvaddstr(cursor_at_level+1, NUM_COLS/2+5, "<");
                        cursor_at_level += 1;
                        level = cursor_to_level(y, cursor_at_level);
                        refresh();
                        break;
                }
                break;
            case 10:
                return level;
            default:
                break;
        }
        keypress = getch();
    }
    return level;
}