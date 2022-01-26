#include <iostream>

#include "ProgressBar.h"

int main() {
    PB::drawProgressBar<int>(2, 60, 30, true);
    return 0;
}