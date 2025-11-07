import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv('../build/jsbsim_flight_log.csv')

fig, axs = plt.subplots(4, 2, figsize=(10, 12), sharex=True)

axs[0][0].plot(df['Time'], df['Altitude'], label='Altitude (ft)', color='blue')
axs[0][0].set_ylabel('Altitude (ft)')
axs[0][0].grid(True)
axs[0][0].legend()

axs[1][0].plot(df['Time'], df['Airspeed'], label='Airspeed (kts)', color='orange')
axs[1][0].set_ylabel('Airspeed (kts)')
axs[1][0].grid(True)
axs[1][0].legend()

axs[2][0].plot(df['Time'], df['Pitch'], label='Pitch (deg)', color='green')
axs[2][0].set_ylabel('Pitch (deg)')
axs[2][0].grid(True)
axs[2][0].legend()

axs[3][0].plot(df['Time'], df['Roll'], label='Roll (deg)', color='red')
axs[3][0].set_ylabel('Roll (deg)')
axs[3][0].set_xlabel('Time (sec)')
axs[3][0].grid(True)
axs[3][0].legend()

axs[0][1].plot(df['Time'], df['Heading'], label='Heading (deg)', color='purple')
axs[0][1].set_ylabel('Heading (deg)')
axs[0][1].grid(True)
axs[0][1].legend()

axs[1][1].plot(df['Time'], df['Latitude'], label='Latitude (deg)', color='brown')
axs[1][1].set_ylabel('Latitude (deg)')
axs[1][1].grid(True)
axs[1][1].legend()

axs[2][1].plot(df['Time'], df['Longitude'], label='Longitude (deg)', color='pink')
axs[2][1].set_ylabel('Longitude (deg)')
axs[2][1].grid(True)
axs[2][1].legend()

plt.tight_layout()
plt.show()