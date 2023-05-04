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
    int y = NUM_ROWS/2-3;
    int slice_begin = 0;
    mvaddstr(y, 0, " __  .__   __. ____    ____  ___       _______   _______ .______          _______.");
    mvaddstr(y+1, 0, "|  | |  \\ |  | \\   \\  /   / /   \\     |       \\ |   ____||   _  \\        /       |");
    mvaddstr(y+2, 0, "|  | |   \\|  |  \\   \\/   / /  ^  \\    |  .--.  ||  |__   |  |_)  |      |   (----`");
    mvaddstr(y+3, 0, "|  | |  . `  |   \\      / /  /_\\  \\   |  |  |  ||   __|  |      /        \\   \\    ");
    mvaddstr(y+4, 0, "|  | |  |\\   |    \\    / /  _____  \\  |  '--'  ||  |____ |  |\\  \\----.----)   |   ");
    mvaddstr(y+5, 0, "|__| |__| \\__|     \\__/ /__/     \\__\\ |_______/ |_______|| _| `._____|_______/    ");
    mvaddstr(y+7, 0, "Press any key to continue");
    getch();
}