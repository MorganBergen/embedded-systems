import matplotlib.pyplot as plt

# Your code goes here to generate the plot

plt.savefig('output.png')  # Save the plot as a PNG file

import matplotlib.pyplot as plt

# data
cores = [1, 2, 3, 4]
mean_times = [26.220, 26.836, 23.217, 21.190]
max_times = [58.336, 36.114, 29.310, 25.620]

# plot
fig, ax = plt.subplots()
ax.bar(cores, mean_times, color='blue', label='Mean Time')
ax.bar(cores, max_times, color='orange', label='Max Time')
ax.set_xticks(cores)
ax.set_xlabel('CPU Cores')
ax.set_ylabel('Time (ms)')
ax.set_title('Inferencing Operation Time vs. CPU Cores')
ax.legend()

plt.show()

