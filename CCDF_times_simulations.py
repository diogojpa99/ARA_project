# defining the libraries
from types import LambdaType
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd



                    ## TIMES OF SIMULATIONS ##

##Just Simulation
data_times = np.loadtxt('times_simulations.txt')

# getting data of the histogram
count, bins_count = np.histogram(data_times, bins=10)
plt.hist(data_times, bins_count, label='Histograma tos tempos de término das simulações')
plt.legend()

#plt.show()


# finding the PDF of the histogram using count values
pdf = count / sum(count)

# using numpy np.cumsum to calculate the CDF
# We can also find using the PDF values by looping and adding
cdf = np.cumsum(pdf)
ccdf = 1 - cdf 

# plotting CDF and CCDF
#plt.plot(bins_count[1:], pdf, color = "red", label = "PDF")
plt.plot(bins_count[1:], cdf, color = 'green', label = "Times CDF")
plt.plot(bins_count[1:], ccdf, color = "blue", label = "Times CCDF")
plt.legend()
plt.show()


                    ## TYPES AND COSTS OF ROUTES
##Simulation
data_types_costs = np.loadtxt('types_costs_simulations.txt')
data_types = np.copy(data_types_costs[:,0])
data_costs = np.copy(data_types_costs[:,1])

#PDF of the type of route with which a node reaches a destination, over all nodes and all destinations
# getting data of the histogram
count, bins_count = np.histogram(data_types, bins=10)
plt.hist(data_types, bins_count)
plt.show()


# finding the PDF of the histogram using count values
pdf = count / sum(count)
plt.plot(bins_count[1:], pdf, color = "red", label = "Types PDF")
plt.legend()
plt.show()

