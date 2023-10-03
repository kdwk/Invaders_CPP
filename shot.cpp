#include "stdcpp.h"
#include "shot.h"
#include "lib.h"
#include "frame.h"
#include "invader.h"

using namespace std;

Shot::Shot(int init_x, int init_y) {
    x = init_x;
    y = init_y;
}

bool Shot::update(Army &army) {
    // If the shot hasn't reached top, move it upwards
    if (y-1 >= 0) {
        y -= 1;
    } else {
        stat = Health::dead;  // If shot has reached top, kill it
        return false;
    }
    for (Invader &invader: army.army) {
        if (invader.x == x && invader.y == y && invader.stat!=Health::dead) { // If the shot reaches an invader that is alive, kill it
            invader.stat = Health::dead;
            stat = Health::dead; // The shot dies too
            return true;
        }
    }
    return false;
}

void Shot::draw(Frame &f) {
    // Draw the shot on the frame
    f.content[x][y] = "|";
}
