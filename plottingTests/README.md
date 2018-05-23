Plotting using matplotlib-cpp
=============================

From https://github.com/lava/matplotlib-cpp 
Library version current May 22, 2018. 


```
g++ plot.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
./a.out
```

## What this does 
Takes in points and adds them to graph. Shows each graph incrementally. 

# What it should do / TODO 
Read in ROS messages to plot them in realtime 
Ex: lin\_reg, Roomba positions, etc 

### Niceties to add
- Autoclose the graph window when new point so that the graph with the next point appears 
- Delete out points that are too old and no longer matter (eg lin\_reg points of Roomba position >5 sec as Roomba has now changed direction)
