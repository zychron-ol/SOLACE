import matplotlib.pyplot as plt

solar_radiation_with_tracker = [900, 800, 700, 600, 500]  # W/m²
solar_radiation_without_tracker = [800, 700, 600, 500, 400]  # W/m²

efficiency_with_tracker = []
efficiency_without_tracker = []

for sr_with_tracker, sr_without_tracker in zip(solar_radiation_with_tracker, solar_radiation_without_tracker):
    efficiency_with_tracker.append(
        (1 + 0.005 * (35 - 25)) * 0.8 * 0.95 * (0.98 * 25 * 8 + 0.4 * 100) / sr_with_tracker * 100
    )
    efficiency_without_tracker.append(
        (1 + 0.005 * (35 - 25)) * 0.75 * 0.9 * (0.98 * 20 * 6 + 0.4 * 100) / sr_without_tracker * 100
    )

plt.plot(solar_radiation_with_tracker, efficiency_with_tracker, label='With Tracker')
plt.plot(solar_radiation_without_tracker, efficiency_without_tracker, label='Without Tracker')
plt.xlabel('Solar Radiation (W/m²)')
plt.ylabel('Efficiency (%)')
plt.title('Efficiency of Solar Panel with and without Tracker')
plt.legend()
plt.grid()
plt.show()
