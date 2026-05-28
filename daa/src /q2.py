import matplotlib.pyplot as plt

# Input sizes
x = [500, 1000, 2000, 4000, 8000]

# Time data (seconds)
linear = [0.000002, 0.000002, 0.000008, 0.000003, 0.000011]
bubble = [0.000270, 0.001595, 0.006781, 0.021474, 0.029585]
binary = [0.000001, 0.000002, 0.000000, 0.000000, 0.000000]

# Plot
plt.plot(x, linear, marker='o', label="Linear Search")
plt.plot(x, bubble, marker='o', label="Bubble Sort")
plt.plot(x, binary, marker='o', label="Binary Search")

plt.xlabel("Input Size")
plt.ylabel("Time (seconds)")
plt.title("Algorithm Time Complexity Comparison")
plt.legend()
plt.grid(True)
plt.show()
