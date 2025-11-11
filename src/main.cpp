#include <FGFDMExec.h>
#include <initialization/FGInitialCondition.h>
#include <input_output/net_fdm.hxx>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "pid.h"

#define SIMULATION_DURATION 20     // seconds
#define SIMULATION_FREQUENCY 120.0 // Hz

struct FlightData
{
    double latitude;
    double longitude;
    double altitude;
    double trueAirspeed;
    double pitch;
    double roll;
    double yaw;
    double verticalSpeed;
};

JSBSim::FGFDMExec fdm;
FlightData flightData;

int main()
{
    // Set up paths
    fdm.SetAircraftPath(SGPath("aircraft"));
    fdm.SetEnginePath(SGPath("engine"));
    fdm.SetSystemsPath(SGPath("systems"));

    // Load model
    if (!fdm.LoadModel("c172x"))
    {
        std::cerr << "Failed to load aircraft." << std::endl;
        return -1;
    }

    double dt = 1.0 / SIMULATION_FREQUENCY;
    fdm.Setdt(dt);

    // Set initial conditions
    fdm.SetPropertyValue("ic/lat-geod-deg", 37.6188056); // San Francisco Intl Airport
    fdm.SetPropertyValue("ic/long-gc-deg", -122.3754167);
    fdm.SetPropertyValue("ic/h-sl-ft", 5000); // 5000 feet
    fdm.SetPropertyValue("ic/vt-kts", 120);   // 120 knots
    fdm.SetPropertyValue("ic/phi-deg", 0);
    fdm.SetPropertyValue("ic/theta-deg", 0);
    fdm.SetPropertyValue("ic/psi-deg", 90);  // East
    fdm.SetPropertyValue("ic/roc-fpm", 0); // Level flight

    if (!fdm.RunIC())
    {
        std::cerr << "Failed to run initial conditions." << std::endl;
        return -1;
    }

    // Turn engine #0 on
    fdm.SetPropertyValue("propulsion/set-running", 0);

    // Print property catalog
    std::ofstream propertyCatalogFile("property_catalog.txt");

    const auto &catalog = fdm.GetPropertyCatalog();
    for (const auto &entry : catalog)
    {
        propertyCatalogFile << entry << std::endl;
    }
    propertyCatalogFile.close();

    std::ofstream logFile("flight_log.csv");
    logFile << "time,latitude,longitude,altitude,true_airspeed,vertical_speed,roll,pitch,heading,roll_target,pitch_target,aileron,elevator,throttle" << std::endl;

    PID rollPID(0.2, 0.1, 0.0, -1.0, 1.0);
    PID pitchPID(0.002, 0.05, 0.0, -1.0, 1.0);

    // Main simulation loop
    double simTime = 0.0;
    while (simTime <= SIMULATION_DURATION)
    {
        fdm.Run();

        flightData.latitude = fdm.GetPropertyValue("position/lat-geod-deg");
        flightData.longitude = fdm.GetPropertyValue("position/long-gc-deg");
        flightData.altitude = fdm.GetPropertyValue("position/h-sl-ft");
        flightData.trueAirspeed = fdm.GetPropertyValue("velocities/vtrue-kts");
        flightData.roll = fdm.GetPropertyValue("attitude/phi-deg");
        flightData.pitch = fdm.GetPropertyValue("attitude/theta-deg");
        flightData.yaw = fdm.GetPropertyValue("attitude/psi-deg");
        flightData.verticalSpeed = fdm.GetPropertyValue("velocities/h-dot-fps");

        double aileronCmd = rollPID.update(0.0, flightData.roll, dt);   // Target roll: 0 degrees
        double elevatorCmd = -pitchPID.update(0.0, flightData.pitch, dt); // Target pitch: 0 degrees

        fdm.SetPropertyValue("fcs/aileron-cmd-norm", aileronCmd);
        fdm.SetPropertyValue("fcs/elevator-cmd-norm", elevatorCmd);
        fdm.SetPropertyValue("fcs/throttle-cmd-norm", 1.0); // 70% throttle

        logFile << simTime << ","
                << flightData.latitude << ","
                << flightData.longitude << ","
                << flightData.altitude << ","
                << flightData.trueAirspeed << ","
                << flightData.verticalSpeed << ","
                << flightData.roll << ","
                << flightData.pitch << ","
                << flightData.yaw << ","
                << 0.0 << ","  // Target heading
                << 0.0 << ","  // Target roll
                << aileronCmd << ","
                << elevatorCmd << ","
                << 1.0
                << std::endl;

        std::cout << "Time: " << simTime
                  << " Latitude: " << flightData.latitude
                  << " Longitude: " << flightData.longitude
                  << " Altitude: " << flightData.altitude
                  << " TrueAirspeed: " << flightData.trueAirspeed
                  << " VerticalSpeed: " << flightData.verticalSpeed
                  << std::endl;

        simTime = fdm.GetSimTime();
        //std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0 / SIMULATION_FREQUENCY)));
    }

    return 0;
}