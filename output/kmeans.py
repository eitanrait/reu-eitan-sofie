import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.cluster import KMeans

title = "2d avg x var, k-means colors manually labeled"
csvfile = "2d-avg-var.csv"
df = pd.read_csv(csvfile,usecols=['ent','var']) #read entropy and variance from csv
activity = pd.read_csv(csvfile,usecols=['act']) #read activity of each sample from csv
color = []
for i in activity.index: #assign colors to each activity that was labeled in csv
	if activity['act'][i] == "chasing":
		color.append('green')
	if activity['act'][i] == "following":
		color.append('orange')
	if activity['act'][i] == "random":
		color.append('red')
km = KMeans(n_clusters=3) #kmeans with n clusters
km.fit(df) #fit data from dataframe into kmeans
y_km = km.predict(df) #store predicted cluster of sample points, automatically set color
cdf = pd.DataFrame(km.cluster_centers_,columns=["ent","var"]) #store cluster centers in dataframe
print(cdf)
ax = df.plot.scatter(x="ent",y="var",c=color,s=5) #plot points
cdf.plot.scatter(x="ent",y="var",s=200,alpha=0.3,ax=ax) #plot clusters
plt.title(title)
plt.show()
path = 'graphs/'+title+'.png'
fig = ax.get_figure()
fig.savefig(path)