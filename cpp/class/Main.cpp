#include <iostream>

#include "ProgressBar.h"

int main() {
    ProgressBar<int> bar(2, 30, 60, true);
    bar.draw();
}