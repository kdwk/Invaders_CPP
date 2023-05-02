#include <iostream>
#include "clear.h"

void aclear() {
    cout << "\033[2J\033[1;1H";
}