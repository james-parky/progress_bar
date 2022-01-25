/*Functions for printing custom progress bars

Author: James Parkington
License: Prublic Domain
Version: 1.4
*/
#include "ProgressBar.h"

#include <iostream>
#include <stdexcept>

#define TARGET_TICK '@'
#define FILLED_TICK '#'
#define EMPTY_TICK '-'

#define TARGET_ERROR "Target must be an integer in the range 0-100."
#define INCREMENT_ERROR "Increment must be an integer, either 1, 2 or 5."
#define PERCENTAGE_ERROR "Percentage must be an integer in the range 0-100."

void setProgressBar(char* progressBar, int increment, int percentage,
                    int target) {
  for (int i = 0; i < 100 / increment; i++) {
    progressBar[i] = EMPTY_TICK;
  }
  int roundedPercentage = percentage - (percentage % increment);
  for (int i = 0; i < roundedPercentage / increment; i++) {
    progressBar[i] = FILLED_TICK;
  }
  int roundedTarget = target - (target % increment);
  progressBar[(roundedTarget / increment) - 1] = TARGET_TICK;
}

void drawProgressBar(int increment, int target, int percentage,
                     bool b_annotation) {
  if (!(increment == 1 || increment == 2 || increment == 5)) {
    throw std::invalid_argument(INCREMENT_ERROR);
  }

  if (!(target >= 0 && target <= 100)) {
    throw std::invalid_argument(TARGET_ERROR);
  }

  if (!(percentage >= 0 && percentage <= 100)) {
    throw std::invalid_argument(PERCENTAGE_ERROR);
  }

  char progressBar[100 / increment];
  setProgressBar(progressBar, increment, percentage, target);

  std::cout << '|';
  for (int i = 0; i < 100 / increment; i++) {
    std::cout << progressBar[i];
  }
  std::cout << '|';
  if (b_annotation) std::cout << percentage << '%';
  std::cout << std::endl;
}
