#pragma once

#include <iostream>
#include <fstream>

#include <FGFDMExec.h>
#include <initialization/FGInitialCondition.h>

struct InitialConditions
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

    void initializeSimulation(const char* aircraft, InitialConditions initialConditions);
    void stepSimulation();

    inline double getValue(const char* name) { return _fdm.GetPropertyValue(std::string(name)); }
    inline void setValue(const char* name, double value) { _fdm.SetPropertyValue(std::string(name), value); }
    
    inline InitialConditions& getInitialConditions() { return _initialConditions; }

private:
    JSBSim::FGFDMExec _fdm;
    InitialConditions _initialConditions;
};