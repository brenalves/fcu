#include "JSBSimInterface.h"

JSBSimInterface::JSBSimInterface(const char* aircraftPath, const char* enginePath, const char* systemPath, double updateFrequencyHz)
{
    _fdm.SetAircraftPath(SGPath(aircraftPath));
    _fdm.SetEnginePath(SGPath(enginePath));
    _fdm.SetSystemsPath(SGPath(systemPath));

    _fdm.Setdt(1.0 / updateFrequencyHz);

    std::cout << "JSBSimInterface created." << std::endl;   
}

JSBSimInterface::~JSBSimInterface()
{
    std::cout << "JSBSimInterface destroyed." << std::endl;
}

void JSBSimInterface::initializeSimulation(const char* aircraft, FlightData initialConditions)
{
    _initialConditions = initialConditions;

    _fdm.LoadModel(aircraft);

    auto ic = _fdm.GetIC();
    ic->InitializeIC();
    ic->SetLatitudeDegIC(_initialConditions.latitude);
    ic->SetLongitudeDegIC(_initialConditions.longitude);
    ic->SetAltitudeASLFtIC(_initialConditions.altitude);
    ic->SetPhiDegIC(_initialConditions.roll);
    ic->SetThetaDegIC(_initialConditions.pitch);
    ic->SetPsiDegIC(_initialConditions.heading);
    ic->SetVtrueKtsIC(_initialConditions.airspeed);

    _fdm.RunIC();

    std::cout << "Simulation initialized with aircraft: " << aircraft << std::endl;
    std::cout << "Initial Conditions:" << std::endl;
    std::cout << "  Latitude: " << _initialConditions.latitude << " deg" << std::endl;
    std::cout << "  Longitude: " << _initialConditions.longitude << " deg" << std::endl;
    std::cout << "  Altitude: " << _initialConditions.altitude << " ft" << std::endl;
    std::cout << "  Roll: " << _initialConditions.roll << " deg" << std::endl;
    std::cout << "  Pitch: " << _initialConditions.pitch << " deg" << std::endl;
    std::cout << "  Heading: " << _initialConditions.heading << " deg" << std::endl;
    std::cout << "  Airspeed: " << _initialConditions.airspeed << " kts" << std::endl;

    // Log all properties to a file for debugging
    std::ofstream catalogFile("jsbsim_property_catalog.txt");
    for(auto& prop: _fdm.GetPropertyCatalog())
    {
        catalogFile << prop << std::endl;
    }
    catalogFile.close();
}

void JSBSimInterface::stepSimulation()
{
    _fdm.Run();

    _currentFlightData.latitude = _fdm.GetPropertyValue("position/lat-geod-deg");
    _currentFlightData.longitude = _fdm.GetPropertyValue("position/long-gc-deg");
    _currentFlightData.altitude = _fdm.GetPropertyValue("position/h-sl-ft");
    _currentFlightData.roll = _fdm.GetPropertyValue("attitude/phi-deg");
    _currentFlightData.pitch = _fdm.GetPropertyValue("attitude/theta-deg");
    _currentFlightData.heading = _fdm.GetPropertyValue("attitude/psi-deg");
    _currentFlightData.airspeed = _fdm.GetPropertyValue("velocities/vtrue-kts");
}