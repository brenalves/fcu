import matplotlib.pyplot as plt
import pandas as pd

# Load the flight log data
data = pd.read_csv('flight_log.csv')

# Plot Roll and Pitch with their targets
plt.figure(figsize=(12, 6))
plt.plot(data['time'], data['roll'], label='Roll', color='blue')
plt.plot(data['time'], data['roll_target'], label='Roll Target', color='red', linestyle='--')
plt.plot(data['time'], data['pitch'], label='Pitch', color='orange')
plt.plot(data['time'], data['pitch_target'], label='Pitch Target', color='green', linestyle='--')
plt.title('Roll and Pitch over Time')
plt.xlabel('Time (s)')
plt.ylabel('Degrees')
plt.legend()
plt.grid(True)

# Plot Airspeed and Altitude
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(data['time'], data['true_airspeed'], label='True Airspeed', color='purple')
plt.title('True Airspeed over Time')
plt.xlabel('Time (s)')
plt.ylabel('Airspeed (knots)')
plt.legend()
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(data['time'], data['altitude'], label='Altitude', color='brown')
plt.title('Altitude over Time')
plt.xlabel('Time (s)')
plt.ylabel('Altitude (feet)')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()