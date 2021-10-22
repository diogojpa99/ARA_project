import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('times_simulations.txt')

cdf = data.cumsum(0)
ccdf = 1 - cdf

plt.plot(range(len(cdf)),cdf,'bo')
plt.ylabel('CCDF')
plt.xlabel('Degree')
plt.show()