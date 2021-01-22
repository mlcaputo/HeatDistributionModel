# HeatDistributionModel
Model of the static heat distribution of a room with a fireplace using a stencil pattern.

The room is simulated in 2 dimensions. The room is 10 feet wide and 10 feet long with a fireplace along one wall. The fireplace is 4 feet wide and is centered
along one wall (it takes up 40% of the wall, with 30% of the walls on either side). The fireplace emits 100º C of heat. The walls are considered to be
20ºC and are considered to be fixed temperatures. 

We can find the temperature distribution by dividing the area into a fine mesh of points. The temperature at an inside point can be taken to be the average of 
the temperatures of the four neighboring points. 

Current parameters set to N=1000 and T=5000, where N is the size of the NxN matrix and T is the number of iterations.

Sequential: 
Time of computation: 44.168751 seconds
Random sample point (8,500): 89.789786
            
Parallel: 
Time of computation: 1.965030 seconds
Random sample point (8,500): 84.011907
