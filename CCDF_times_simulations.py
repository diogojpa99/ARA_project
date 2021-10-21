import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('types_costs_simulations.txt')
sorted_data = np.sort(data)
cumulative = np.cumsum(sorted_data)

plt.plot(cumulative)
plt.show()