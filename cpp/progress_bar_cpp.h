/*
Class for printing custom progress bars

Author: James Parkington
License: Prublic Domain
Version: 1.2
*/
#include <iostream>
#include <stdexcept>

#define TARGET_TICK '@'
#define FILLED_TICK '#'
#define EMPTY_TICK '-'

class ProgressBar {
 private:
  int increment;
  int target;
  float percentage;
  bool annotation;

 public:
  void setIncrement(int value) {
    if (value == 1 || value == 2 || value == 5) {
      increment = value;
    } else {
      throw std::invalid_argument(
          "Increment must be an integer, either 1, 2 or 5.");
    }
  }

  void setTarget(int value) {
    if (value >= 0 && value <= 100) {
      target = value;
    } else {
      throw std::invalid_argument(
          "Target must be an integer in the range 0-100.");
    }
  }

  void setPercentage(float value) {
    if (value >= 0.0 && value <= 100.0) {
      percentage = value;
    } else {
      throw std::invalid_argument(
          "Percentage must be an float in the range 0.0-100.0.");
    }
  }

  void setAnnotation(bool value) { annotation = value; }

  void setProgressBar(char* progressBar) {
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

  ProgressBar(int inc, int tar, float per, bool anno) {
    setIncrement(inc);
    setTarget(tar);
    setPercentage(per);
    setAnnotation(anno);
  }

  void draw() {
    char progressBar[100 / increment];
    setProgressBar(progressBar);

    std::cout << '|';
    for (int i = 0; i < 100 / increment; i++) {
      std::cout << progressBar[i];
    }
    std::cout << '|';
    if (annotation) std::cout << percentage << '%';
    std::cout << std::endl;
  }
};
