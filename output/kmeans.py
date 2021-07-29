import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.cluster import KMeans

title = "1d variance of entropy, k-means colors manually labeled"
csvfile = "exp4results.csv"
colors = []

data = np.genfromtxt(csvfile, delimiter=",",dtype=float,usecols=(0,5),skip_header=1) #read entropy and variance from csv
activities = np.genfromtxt(csvfile,delimiter=",",usecols=(4),dtype=None,encoding=None,skip_header=1)
for activity in activities: #assign colors to each activity that was labeled in csv
	if activity == "chasing":
		colors.append('green')
	if activity == "following":
		colors.append('orange')
	if activity == "random":
		colors.append('red')

kmeans = KMeans(n_clusters=3) #k means with n clusters

kmeans.fit(data[:,:2]) 				
y_kmeans = kmeans.predict(data[:,:2]) #cluster index for each coordinate
centers = kmeans.cluster_centers_ #center coordinates

fig = plt.figure()
#ax = fig.add_subplot(111)
ax = fig.add_subplot(611)
ax.grid(True)
#ax.set_xlim(-.1,3.2)
#ax.set_ylim(-.1,1.6)
#ax.set_xlim(-.1,3.2)
#ax.set_ylim(-.1,.1)
ax.set_title(title)

ax.scatter(data[:,0], data[:,1], c=colors, s=10)
ax.scatter(centers[:,0],centers[:,1],c='black',s = 10, alpha = 1)

path = 'graphs/kmeans/'+title+'.png'
plt.savefig(path,dpi=400)
plt.show()