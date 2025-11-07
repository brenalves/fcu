#pragma once

#include <iostream>
#include <fstream>

#include <FGFDMExec.h>
#include <initialization/FGInitialCondition.h>

struct FlightData
{
    double latitude;
    double longitude;
    double altitude;
    double roll;
    double pitch;
    double heading;
    double airspeed;
};

class JSBSimInterface
{
public:
    JSBSimInterface(const char* aircraftPath, const char* enginePath, const char* systemPath, double updateFrequencyHz);
    ~JSBSimInterface();

    void initializeSimulation(const char* aircraft, FlightData initialConditions);
    void stepSimulation();
    
    inline FlightData& getInitialConditions() { return _initialConditions; }
    inline FlightData& getCurrentFlightData() { return _currentFlightData; }

private:
    JSBSim::FGFDMExec _fdm;
    FlightData _initialConditions;
    FlightData _currentFlightData;
};