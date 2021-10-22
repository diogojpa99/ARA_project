import numpy as np
import matplotlib.pyplot as plt


data = np.loadtxt("types_costs_simulations.txt")

types=data[:,0]
costs=data[:,1]

i=0

while i< len(types):
    if types[i] == 0:
        types = np.delete(types, i)
        costs = np.delete(costs, i)
    i +=1

'''
count, bins_count = np.histogram(types, bins=20, range=(types.min(),types.max()))
  
# finding the PDF of the histogram using count values
pdf = count / sum(count)
  
# using numpy np.cumsum to calculate the CDF
# We can also find using the PDF values by looping and adding
cdf = np.cumsum(pdf)
  
# plotting PDF and CDF
#plt.plot(bins_count[1:], pdf, color="red", label="PDF")
plt.plot(bins_count[1:], 1 - cdf, label="CDF")
plt.show()
plt.legend()

'''

types = np.sort(types)

y = np.arrange(1, len(types)+1) / len(types)

#plt.plot(x,y,marker='.',