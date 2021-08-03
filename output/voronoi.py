import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy.spatial import Voronoi, voronoi_plot_2d
from sklearn.cluster import KMeans
title = "2d avg x var, k-means colors manually labeled"
csvfile = "exp4results.csv"

colors = []
data = np.genfromtxt(csvfile, delimiter=",",dtype=float,usecols=(0,2),skip_header=1) #read entropy and variance from csv
activities = np.genfromtxt(csvfile,delimiter=",",usecols=(4),dtype=None,encoding=None,skip_header=1)

kmeans = KMeans(n_clusters=3) #k means with n clusters
kmeans.fit(data[:,:2]) 				
y_kmeans = kmeans.predict(data[:,:2]) #cluster index for each coordinate
centers = kmeans.cluster_centers_ #center coordinates
vor = Voronoi(centers)

for activity in activities: #assign colors to each activity that was labeled in csv
	if activity == "chasing":
		colors.append('green')
	if activity == "following":
		colors.append('orange')
	if activity == "random":
		colors.append('red')

#print(centers)
print(vor.points)
print(vor.vertices)
print(vor.point_region)
voronoi_plot_2d(vor,show_points=False,show_vertices=True,line_width=2,line_colors='orange',point_size=20,line_alpha=1)
#plt.xlim(-1,4)
#plt.ylim(-10,10)
plt.xlim(-.1,3.2)
plt.ylim(-.1,1.6)
plt.scatter(data[:,0], data[:,1], c=colors, s=10)
plt.scatter(centers[:,0],centers[:,1],c='black',s = 300, alpha = .25)
plt.show()