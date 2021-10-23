# defining the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = np.loadtxt('times_simulations.txt')

# initializing subplots


# getting data of the histogram
count, bins_count = np.histogram(data, bins=10)
plt.hist(data, bins_count)
plt.show()


# finding the PDF of the histogram using count values
pdf = count / sum(count)

# using numpy np.cumsum to calculate the CDF
# We can also find using the PDF values by looping and adding
cdf = np.cumsum(pdf)
ccdf = 1 - cdf 

# plotting PDF and CDF
#plt.plot(bins_count[1:], pdf, color = "red", label = "PDF")
plt.plot(bins_count[1:], cdf, color = 'green', label = "CDF")
plt.plot(bins_count[1:], ccdf, color = "blue", label = "ccdf")
plt.legend()
plt.show()

