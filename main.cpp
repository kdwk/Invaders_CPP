#include <bits/stdc++.h>
#include "later.h"
#include "constants.h"
#include "clear.h"
#include "frame.h"


using namespace std;

void test(Frame f) {
    f.render();
}

Frame f;

int main() {
    clear();
    f.draw(3,NUM_ROWS-1,"A");
    Later render1(1000, false, &test, f);
    cout << "success" << endl;
    return 0;
}