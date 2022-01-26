/*
Class for printing custom progress bars

Author: James Parkington
License: Prublic Domain
Version: 1.4
*/

#ifndef _PROGRESS_BAR_
#define _PROGRESS_BAR_

#include <iostream>
#include <stdexcept>
#include <vector>

#define TARGET_TICK '@'
#define FILLED_TICK '#'
#define EMPTY_TICK '-'

template <typename T>
class ProgressBar {
   private:
    int m_increment;
    T m_target;
    T m_percentage;
    bool m_b_annotation;

   private:
    void setIncrement(int value);
    void setTarget(T value);
    void setPercentage(T value);
    std::vector<char> constructProgressBar();

   public:
    ProgressBar(int increment, T target, T percentage, bool b_annotation);
    void draw();
};

#endif

template <typename T>
void ProgressBar<T>::setIncrement(int value) {
    if (value == 1 || value == 2 || value == 5) {
        m_increment = value;
    } else {
        throw std::invalid_argument(
            "Increment must be an integer, either 1, 2 or 5.");
    }
}

template <typename T>
void ProgressBar<T>::setPercentage(T value) {
    if (value >= 0.0 && value <= 100.0) {
        m_percentage = value;
    } else {
        throw std::invalid_argument(
            "Percentage must be an float in the range 0.0-100.0.");
    }
}

template <typename T>
void ProgressBar<T>::setTarget(T value) {
    if (value >= 0 && value <= 100) {
        m_target = value;
    } else {
        throw std::invalid_argument(
            "Target must be an integer in the range 0-100.");
    }
}

template <typename T>
ProgressBar<T>::ProgressBar(int increment, T target, T percentage, bool b_annotation) {
    setIncrement(increment);
    setTarget(target);
    setPercentage(percentage);
    m_b_annotation = b_annotation;
}

template <typename T>
std::vector<char> ProgressBar<T>::constructProgressBar() {
    std::vector<char> bar;
    int numberOfTicks = 100 / m_increment;
    for (int i = 0; i < numberOfTicks; i++) {
        bar.push_back(EMPTY_TICK);
    }
    int intPercentage = (int)m_percentage;
    int roundedPercentage = intPercentage - (intPercentage % m_increment);
    int numberOfFilledTicks = roundedPercentage / m_increment;
    for (int i = 0; i < numberOfFilledTicks; i++) {
        bar[i] = FILLED_TICK;
    }
    int rounded_target = m_target - (m_target % m_increment);
    bar[(rounded_target / m_increment) - 1] = TARGET_TICK;
    return bar;
}

template <typename T>
void ProgressBar<T>::draw() {
    std::vector<char> bar = constructProgressBar();
    std::cout << '|';
    for (char mark : bar) {
        std::cout << mark;
    }
    std::cout << '|';
    if (m_b_annotation) std::cout << m_percentage << '%';
    std::cout << std::endl;
}
