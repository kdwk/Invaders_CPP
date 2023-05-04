#include <bits/stdc++.h>
#include <ncurses.h>
#include <form.h>
#include "lib.h"

using namespace std;

void update_leaderboard(string player_name, double seconds) {
    system("test -f leaderboard.txt || touch leaderboard.txt");
    ofstream fout;
    fout.open("leaderboard.txt", ios::app);
    if (fout.fail()) {
        clear();
        mvaddstr(0, 0, "Cannot open leaderboard.txt");
    } else {
        fout << fixed << setprecision(2);
        fout << player_name << " " << seconds << endl;
        fout.close();
        system("sort leaderboard.txt -o leaderboard.txt");
        system("sort -t ' ' -k 1,1 -u leaderboard.txt -o leaderboard.txt");
        system("sort -t ' ' -k 2,2 -n leaderboard.txt -o leaderboard.txt");
    }
}

string get_player_name() {
    string player_name = "";
    int keypress = getch();
    while (keypress != 10) {
        switch (keypress) {
            case KEY_BACKSPACE:
                if (player_name.length()==0) {break;}
                else {player_name.pop_back();}
            default:
                if (isalnum(keypress)) {
                    player_name.push_back(keypress);
                }
        }
        keypress = getch();
    }
    if (player_name.length()==0) {player_name = "Anonymous";}
    return player_name;
}

void w(double seconds) {
    clear();
    string str = "You win!";
    mvaddwstr(NUM_ROWS/2, NUM_COLS/2-4, wstring(str.begin(), str.end()).c_str());
    refresh();
    this_thread::sleep_for(chrono::milliseconds(2000));
    clear();
    string message = "You have eliminated the invaders in ";
    message += to_string(seconds);
    message += " seconds!";
    mvaddstr(NUM_ROWS/2-1, 0, message.c_str());
    mvaddstr(NUM_ROWS/2+1, 0, "Enter your name: ");
    move(NUM_ROWS/2+1, 17);
    curs_set(1);
    echo();
    refresh();
    string player_name = get_player_name();
    update_leaderboard(player_name, seconds);
};

void l() {
    clear();
    string str = "You lose";
    mvaddwstr(NUM_ROWS/2, NUM_COLS/2-4, wstring(str.begin(), str.end()).c_str());
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
    if (keypress=='t') {return Level::test;}
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