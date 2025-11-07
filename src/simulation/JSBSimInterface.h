#pragma once

#include <FGFDMExec.h>
#include <initialization/FGInitialCondition.h>

// That struct simulate the state estimation step
struct FlightData
{
    double roll;
    double pitch;
    double yaw;
    double heading;
    double altitude;
    double airspeed;
    double latitude;
    double longitude;
};

struct ControlInputs
{
    double aileron;
    double elevator;
    double rudder;
    double throttle;
};

class JSBSimInterface
{
public:
    JSBSimInterface();
    ~JSBSimInterface();

    void Step();

    const FlightData& GetFlightData() const { return _flightData; }
    const ControlInputs& GetControlInputs() const { return _controlInputs; }

private:
    JSBSim::FGFDMExec _fdm;
    FlightData _flightData;
    ControlInputs _controlInputs;
};