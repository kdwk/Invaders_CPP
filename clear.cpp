#include <iostream>
#include "clear.h"

void clear() {
    cout << "\033[2J\033[1;1H";
}