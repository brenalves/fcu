# FCU Hardware

The FCU Hardware are composed by:

- Power Supply System [PSS]
- Sensors System [SS]
- Sensor Computing System [SCS]
- Flight Control System [FCS]
- Persistence System [PS]

## Power Supply System

The PSU distribute and verify the raw input supply sending to FCU supply informations like current, voltage and power. That system convert the raw input (>=5V) to stable 5V and 3.3V to supply all other systems.

Initially the PSU receives the input supply via an Deans T Plug connector and send to a Bulk Regulator to convert to stable 5V. That 5V goes through an Linear Regulator to drop voltage to 3.3V.

Additionally the PSU send raw input to a power monitor to measure current, voltage drop and power, that information are sent to FCU to maintenance and supervision purposes.

## Sensors System

The SU are responsible to send airplane behavior to SCU through sensor data, at moment the required sensors are:

- Inertial Measurement Unit [IMU]
- Magnetometer [MAG]
- Barometer [BARO]
- GNSS receiver [GRX]
- Temperature [TEMP]
- Airspeed module [AISPD] (optional via I2C protocol)

The IMU contains a gyroscope for inclination measurements and accelerometer for gravity effects, that component is very important.

The magnetometer is responsible to measure the Earth's magnetic field to localization and heading purposes.

The barometer will measure the atmospheric pressure to calculate the altitude from sea level.

GNSS receiver will be responsible for localization in Earth with latitude and longitude measurements, other infos like speed and altitude will be used to support and reference to other more accurate methods.

Temperature sensor for monitoring cabin temperature, detect overheats and protect the system, maybe can be used to detect outside temperature.

Airspeed module will be optional, to be connected via an JST connector to communicate with NU via I2C protocol. Once connected the AISPD module will be the primary source of speed information with support of GNSS data.

## Sensor Computing System
