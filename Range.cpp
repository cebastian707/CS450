#include "Range.hpp"

Range::Range(int _rangeValue) : initValue(0), stepValue(1), rangeValue(_rangeValue) {}

Range::Range(int _initValue, int _rangeValue) : initValue(_initValue), stepValue(1), rangeValue(_rangeValue) {}

Range::Range(int _initValue, int _rangeValue, int _stepValue) : initValue(_initValue), stepValue(_stepValue), rangeValue(_rangeValue) {}


int Range::start_value() {
    return initValue;
}

bool Range::condition() {
    if (stepValue >= 0) {
        return initValue < rangeValue;
    } else {
        return initValue > rangeValue;
    }
}

int Range::next() {
    int currentValue = initValue;
    initValue += stepValue;
    return currentValue;
}
