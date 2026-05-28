import matplotlib.pyplot as plt

# Input sizes
sizes = [500, 1000, 2000, 4000, 8000]

# Time values (seconds)
linear_time = [0.000002, 0.000001, 0.000002, 0.000007, 0.000007]
bubble_time = [0.000173, 0.000734, 0.003451, 0.014330, 0.027696]
binary_time = [0.000001, 0.000000, 0.000001, 0.000001, 0.000001]

# Plot
plt.figure()
plt.plot(sizes, linear_time, marker='o', label='Linear Search')
plt.plot(sizes, bubble_time, marker='o', label='Bubble Sort')
plt.plot(sizes, binary_time, marker='o', label='Binary Search')

plt.xlabel("Input Size")
plt.ylabel("Time (seconds)")
plt.title("Time Complexity Comparison")
plt.legend()
plt.grid(True)
plt.show()

