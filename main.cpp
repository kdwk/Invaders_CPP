#include <bits/stdc++.h>
#include "constants.h"
#include "clear.h"
#include "frame.h"

using namespace std;

int main() {
    clear();
    cout << "Cleared";
    Frame f;
    f.draw(3,NUM_ROWS-1,"A");
    f.render();
    return 0;
}