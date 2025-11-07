#include <iostream>
#include <thread>
#include <chrono>
#include "JSBSimInterface.h"

#define UPDATE_FREQUENCY_HZ 50
#define SIMULATION_MAX_TIME_SEC 30

int main()
{
    std::cout << "Starting FCU application..." << std::endl;

    JSBSimInterface jsbsimInterface("simulation/aircraft", "simulation/engine", "simulation/systems", UPDATE_FREQUENCY_HZ);
    FlightData initConds;
    initConds.latitude = 37.6188056;   // Example: San Francisco Intl Airport
    initConds.longitude = -122.3754167;
    initConds.altitude = 3000.0;         // Feet
    initConds.roll = 0.0;
    initConds.pitch = 0.0;
    initConds.heading = 90.0;           // East
    initConds.airspeed = 80.0;         // Knots
    jsbsimInterface.initializeSimulation("c172p", initConds);

    std::ofstream logFile("jsbsim_flight_log.csv");
    logFile << "Time,Latitude,Longitude,Altitude,Roll,Pitch,Heading,Airspeed" << std::endl;

    double simulationTime = 0.0;
    while(simulationTime < SIMULATION_MAX_TIME_SEC)
    {
        jsbsimInterface.stepSimulation();
        FlightData currentData = jsbsimInterface.getCurrentFlightData();

        std::cout << "Time: " << simulationTime << " sec | "
                  << "Lat: " << currentData.latitude << " deg, "
                  << "Lon: " << currentData.longitude << " deg, "
                  << "Alt: " << currentData.altitude << " ft, "
                  << "Roll: " << currentData.roll << " deg, "
                  << "Pitch: " << currentData.pitch << " deg, "
                  << "Heading: " << currentData.heading << " deg, "
                  << "Airspeed: " << currentData.airspeed << " kts"
                  << std::endl;

        logFile << simulationTime << ", "
                 << currentData.latitude << ", "
                 << currentData.longitude << ", "
                 << currentData.altitude << ", "
                 << currentData.roll << ", "
                 << currentData.pitch << ", "
                 << currentData.heading << ", "
                 << currentData.airspeed << std::endl;

        simulationTime += 1.0 / UPDATE_FREQUENCY_HZ;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0 / UPDATE_FREQUENCY_HZ)));
    }

    logFile.close();

    std::cout << "Simulation finished." << std::endl;

    return 0;
}