import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

title = "k means clustering entropy of tests"
csvfile = "average_entropy.csv"

import csv
with open(csvfile,"r") as csvfile:
	data = list(csv.reader(csvfile))

y = [0] * len(data)

km = KMeans(n_clusters=3)
km.fit(data)
y_km = km.predict(data)
centers = km.cluster_centers_
y_center = [0] * len(centers)

fig = plt.figure()
ax = fig.add_subplot(511)
ax.set_title(title)
ax.grid(True)

ax.scatter(data[:],y[:],c=y_km,s=20,cmap='viridis')
ax.scatter(centers[:],y_center[:],c='green',marker = ".", s=800,alpha=0.3)

path = 'graphs/'+title+'.png'
plt.savefig(path, dpi=400)
plt.show()