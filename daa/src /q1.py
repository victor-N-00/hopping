import matplotlib.pyplot as plt

# Data
x = [500, 1000, 2000, 4000, 8000]
y = [0.000167, 0.000353, 0.000853, 0.002037, 0.004894]

# Plot
plt.plot(x, y, marker='o')
plt.xlabel("Input Size")
plt.ylabel("Time (seconds)")
plt.title("Input Size vs Time")
plt.grid(True)
plt.show()

