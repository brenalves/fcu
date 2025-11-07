#include "JSBSimInterface.h"

JSBSimInterface::JSBSimInterface()
{
    // Initialize JSBSim
    _fdm.SetAircraftPath(SGPath("jsbsim/aircraft"));
    _fdm.SetEnginePath(SGPath("jsbsim/engine"));
    _fdm.SetSystemsPath(SGPath("jsbsim/systems"));

    // Load a default aircraft model, e.g., Cessna 172P
    _fdm.LoadModel("c172p");

    // Set initial conditions, for example:
    // Airport: SBCH (Chapeco, Brazil)
    // Altitude: 3000ft
    // Heading: 90 degrees
    // Airspeed: 60 knots

    auto ic = _fdm.GetIC();
    ic->SetLatitudeDegIC(-27.1000);   // Latitude for SBCH
    ic->SetLongitudeDegIC(-52.6150);  // Longitude for SBCH
    ic->SetAltitudeAGLFtIC(3000.0);   // Altitude above ground level
    ic->SetPhiDegIC(0.0);             // Roll angle
    ic->SetThetaDegIC(0.0);           // Pitch angle
    ic->SetPsiDegIC(90.0);            // Heading
    ic->SetVcalibratedKtsIC(60.0);    // Calibrated airspeed

    // Initialize the simulation
    _fdm.RunIC();

    // Initialize control inputs to zero
    _controlInputs.aileron = 0.0;
    _controlInputs.elevator = 0.0;
    _controlInputs.rudder = 0.0;
    _controlInputs.throttle = 0.0;
}

void JSBSimInterface::Step()
{
    _fdm.Run();

    _flightData.roll = _fdm.GetPropertyValue("/orientation/roll-deg");
    _flightData.pitch = _fdm.GetPropertyValue("/orientation/pitch-deg");
    _flightData.yaw = _fdm.GetPropertyValue("/orientation/yaw-deg");
    _flightData.heading = _fdm.GetPropertyValue("/orientation/heading-deg");
    _flightData.altitude = _fdm.GetPropertyValue("/position/altitude-ft");
    _flightData.airspeed = _fdm.GetPropertyValue("/velocities/airspeed-kt");
    _flightData.latitude = _fdm.GetPropertyValue("/position/latitude-deg");
    _flightData.longitude = _fdm.GetPropertyValue("/position/longitude-deg");

    _fdm.SetPropertyValue("/controls/aileron-cmd-norm", _controlInputs.aileron);
    _fdm.SetPropertyValue("/controls/elevator-cmd-norm", _controlInputs.elevator);
    _fdm.SetPropertyValue("/controls/rudder-cmd-norm", _controlInputs.rudder);
    _fdm.SetPropertyValue("/controls/throttle-cmd-norm", _controlInputs.throttle);
}

JSBSimInterface::~JSBSimInterface()
{
}