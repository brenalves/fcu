#pragma once

#include <algorithm>

class PID
{
public:
    PID(double kp, double ki, double kd, double minOutput, double maxOutput);

    double update(double setpoint, double measuredValue, double dt);

    void reset();

private:
    double _kp;
    double _ki;
    double _kd;
    double _minOutput;
    double _maxOutput;
    double _previousError;
    double _integral;
};