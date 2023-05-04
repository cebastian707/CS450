#ifndef APYTHONINTERPRETER_RANGE_HPP
#define APYTHONINTERPRETER_RANGE_HPP

class Range{

public:
    Range(int _rangeValue);  // set initValue to zero and stepValue to 1.
    Range(int _initValue, int _rangeValue);  // set stepVlaue to 1.
    Range(int _initValue, int _rangeValue, int _stepVaue);

    bool condition(); // should we iterate?
    int next();       // the value to be assigned to the loop counter.

private:
    int initValue, stepValue, rangeValue;

    int start_value();
};
#endif