# defining the libraries
from types import LambdaType
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd



                    ## TIMES OF SIMULATIONS ##

##Just Simulation
data_times = np.loadtxt('times_simulations.txt')

fig1, plot1 = plt.subplots()
# getting data of the histogram
count, bins_count = np.histogram(data_times, bins=10)
plot1.hist(data_times, bins_count, label='Histograma tos tempos de término das simulações')



# finding the PDF of the histogram using count values
pdf = count / sum(count)

# using numpy np.cumsum to calculate the CDF
# We can also find using the PDF values by looping and adding
cdf = np.cumsum(pdf)
ccdf = 1 - cdf 

# plotting CDF and CCDF
fig2, plot2 = plt.subplots()
plot2.plot(bins_count[1:], cdf, color = 'green', label = "Times CDF")
plot2.plot(bins_count[1:], ccdf, color = "blue", label = "Times CCDF")
plot2.legend()

plt.show()



