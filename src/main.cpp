#include <iostream>
#include <thread>
#include <chrono>
#include "JSBSimInterface.h"

#define UPDATE_FREQUENCY_HZ 50
#define SIMULATION_MAX_TIME_SEC 30

struct FlightData
{
    double roll;
    double pitch;
    double heading;
    double airspeed;
    double latitude;
    double longitude;
    double altitude;
};

struct FlightControls
{
    double aileron;
    double elevator;
    double rudder;
    double throttle;
};

int main()
{
    std::cout << "Starting FCU application..." << std::endl;

    JSBSimInterface jsbsimInterface("simulation/aircraft", "simulation/engine", "simulation/systems", UPDATE_FREQUENCY_HZ);
    InitialConditions initConds;
    initConds.latitude = 37.6188056;   // Example: San Francisco Intl Airport
    initConds.longitude = -122.3754167;
    initConds.altitude = 3000.0;         // Feet
    initConds.roll = 0.0;
    initConds.pitch = 0.0;
    initConds.heading = 90.0;           // East
    initConds.airspeed = 150.0;         // Knots
    jsbsimInterface.initializeSimulation("c172p", initConds);

    std::ofstream logFile("jsbsim_flight_log.csv");
    logFile << "Time,Latitude,Longitude,Altitude,Roll,Pitch,Heading,Airspeed,Aileron,Elevator,Rudder,Throttle" << std::endl;

    FlightData fd;
    FlightControls fc;

    fc.aileron = jsbsimInterface.getValue("fcs/aileron-cmd-norm");
    fc.elevator = jsbsimInterface.getValue("fcs/elevator-cmd-norm");
    fc.rudder = jsbsimInterface.getValue("fcs/rudder-cmd-norm");
    fc.throttle = jsbsimInterface.getValue("fcs/throttle-cmd-norm");

    double simulationTime = 0.0;
    while(simulationTime < SIMULATION_MAX_TIME_SEC)
    {
        jsbsimInterface.stepSimulation();

        fd.roll = jsbsimInterface.getValue("attitude/phi-deg");
        fd.pitch = jsbsimInterface.getValue("attitude/theta-deg");
        fd.heading = jsbsimInterface.getValue("attitude/psi-deg");
        fd.altitude = jsbsimInterface.getValue("position/h-sl-ft");
        fd.latitude = jsbsimInterface.getValue("position/lat-geod-deg");
        fd.longitude = jsbsimInterface.getValue("position/long-gc-deg");
        fd.airspeed = jsbsimInterface.getValue("velocities/vtrue-kts");

        logFile << simulationTime << ","
                 << fd.latitude << ","
                 << fd.longitude << ","
                 << fd.altitude << ","
                 << fd.roll << ","
                 << fd.pitch << ","
                 << fd.heading << ","
                 << fd.airspeed << ","
                 << fc.aileron << ","
                 << fc.elevator << ","
                 << fc.rudder << ","
                 << fc.throttle << std::endl;

        simulationTime += 1.0 / UPDATE_FREQUENCY_HZ;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0 / UPDATE_FREQUENCY_HZ)));
    }

    logFile.close();

    std::cout << "Simulation finished." << std::endl;

    return 0;
}