import matplotlib.pyplot as plt

# Given data
sizes = [9, 8, 7, 6, 5]
times = [0.000021, 0.000016, 0.000018, 0.000017, 0.000015]

# Plot
plt.figure()
plt.plot(sizes, times, marker='o')
plt.xlabel("Input Size")
plt.ylabel("Time (seconds)")
plt.title("Linear Search Time Complexity")
plt.grid(True)

plt.show()

