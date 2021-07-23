import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

import csv
with open('entropy.csv',"r") as csvfile:
	data = list(csv.reader(csvfile))

y = [0] * len(data)

km = KMeans(n_clusters=2)
km.fit(data)
y_km = km.predict(data)
centers = km.cluster_centers_
y_center = [0] * len(centers)

fig = plt.figure()
ax = fig.add_subplot(511)
ax.grid(True)

ax.scatter(data[:],y[:],c=y_km,s=20,cmap='viridis')
ax.scatter(centers[:],y_center[:],c='green',marker = "*", s=800,alpha=0.3)

plt.show()