#include "pid.h"

PID::PID(double kp, double ki, double kd, double minOutput, double maxOutput)
    : _kp(kp), _ki(ki), _kd(kd),
      _minOutput(minOutput), _maxOutput(maxOutput),
      _previousError(0.0), _integral(0.0)
{
}

double PID::update(double setpoint, double measuredValue, double dt)
{
    double error = setpoint - measuredValue;

    _integral += error * dt;

    double derivative = (error - _previousError);

    double output = _kp * error + _ki * _integral + _kd * derivative;

    if(output < _minOutput || output > _maxOutput) {
        // Anti-windup: prevent integral from accumulating further
        _integral -= error * dt; // revert last integral addition
    }

    output = std::clamp(output, _minOutput, _maxOutput);

    _previousError = error;
    return output;
}

void PID::reset()
{
    _previousError = 0.0;
    _integral = 0.0;
}
