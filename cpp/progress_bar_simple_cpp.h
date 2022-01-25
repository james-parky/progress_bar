/*Class for printing custom progress bars

Author: James Parkington
License: Prublic Domain
Version: 1.0
*/
#include <iostream>
#include <stdexcept>

#define TARGET_TICK '@'
#define FILLED_TICK '#'
#define EMPTY_TICK '-'

void setProgressBar(char* progressBar, int increment, int percentage,
                    int target) {
  int numberOfTicks = 100 / increment;
  for (int i = 0; i < numberOfTicks; i++) {
    progressBar[i] = EMPTY_TICK;
  }
  int intPercentage = (int)percentage;
  int roundedPercentage = intPercentage - (intPercentage % increment);
  int numberOfFilledTicks = roundedPercentage / increment;
  for (int i = 0; i < numberOfFilledTicks; i++) {
    progressBar[i] = FILLED_TICK;
  }
  int roundedTarget = target - (target % increment);
  progressBar[(roundedTarget / increment) - 1] = TARGET_TICK;
}

void drawProgressBar(int increment, int target, int percentage,
                     bool annotation) {
  if (!(increment == 1 || increment == 2 || increment == 5)) {
    throw std::invalid_argument(
        "Increment must be an integer, either 1, 2 or 5.");
  }

  if (!(target >= 0 && target <= 100)) {
    throw std::invalid_argument(
        "Target must be an integer in the range 0-100.");
  }

  if (!(percentage >= 0 && percentage <= 100)) {
    throw std::invalid_argument(
        "Percentage must be an integer in the range 0-100.");
  }

  char progressBar[100 / increment];
  setProgressBar(progressBar, increment, percentage, target);

  std::cout << '|';
  for (int i = 0; i < 100 / increment; i++) {
    std::cout << progressBar[i];
  }
  std::cout << '|';
  if (annotation) std::cout << percentage << '%';
  std::cout << std::endl;
}
