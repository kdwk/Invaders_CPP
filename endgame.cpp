#include <bits/stdc++.h>
#include "clear.h"
#include "later.h"

using namespace std;

void bye() {
    exit(0);
}

void win() {
    clear();
    cout << "🎉 You've won!" << endl;
    Later end_program(2000, false, &bye);
}

void lose() {
    clear();
    cout << "😕 You lose" << endl;
    Later end_program(2000, false, &bye);
}