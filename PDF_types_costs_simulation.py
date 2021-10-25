# defining the libraries
from types import LambdaType
import numpy as np
import matplotlib.pyplot as plt
from numpy.core.fromnumeric import cumprod
import pandas as pd      

##Simulation
                    ## TYPES OF ROUTES

data_types_costs = np.loadtxt('types_costs_simulations.txt')
data_types = np.sort(np.copy(data_types_costs[:,0]))
data_costs = np.sort(np.copy(data_types_costs[:,1]))

""""Histogram"""
# getting data of the histogram
fig1, plot1 = plt.subplots()
count, bins_count = np.histogram(data_types, bins=10)
plot1.hist(data_types, bins_count, label='Histograma')
plot1.set_title('Histograma dos tipos das rotas resultantes da simulação')


""""PDF"""
#PDF of the type of route with which a node reaches a destination, over all nodes and all destinations
fig2, plot2 = plt.subplots()
pdf_types = count / sum(count)
plot2.plot(bins_count[1:], pdf_types, color = "red", label = "PDF dos tipos de rotas")
plot2.set_title('PDF dos tipos de rotas resultantes da simulação')

plt.show()

                    ## COSTS OF ROUTES

""""Histogram"""
# getting data of the histogram
fig3, plot3 = plt.subplots()
count, bins_count = np.histogram(data_costs, bins=10)
plot3.hist(data_types, bins_count, label='Histograma')
plot3.set_title('Histograma dos custos das rotas resultantes da simulação')


""""PDF"""
#PDF of the type of route with which a node reaches a destination, over all nodes and all destinations
fig4, plot4 = plt.subplots()
pdf_costs = count / sum(count)
plot4.plot(bins_count[1:], pdf_costs, color = "red", label = "PDF dos custos")
plot4.set_title('PDF dos custos das rotas resultantes da simulação')

fig5, plot5 = plt.subplots()
ccdf_costs = 1 - np.cumsum(pdf_costs)
plot5.plot(bins_count[1:], ccdf_costs, color = "red", label = "CCDF dos custos")

plt.show()