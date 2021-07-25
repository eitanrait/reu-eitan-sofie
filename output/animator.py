# -*- coding: utf-8 -*-
"""
Created on Fri Jul 16 09:48:07 2021

@author: karso
"""
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation

# extract data
# chasing_vertical.csv and output.csv
csvfile = "chasing_R_1234120_prob_35.csv"
f = r"chasing_animation90.gif"

data = np.genfromtxt(csvfile, delimiter=",",dtype = float)
u_i = [row[0] for row in data]
u_j = [row[1] for row in data]
v_i = [row[2] for row in data]
v_j = [row[3] for row in data]

u_coords = zip(u_i, u_j)
v_coords = zip(v_i, v_j);

# set up plot
fig = plt.figure()
ax1 = plt.axes(xlim=(v_i[0] - 20, u_i[-1] + 20), ylim=(v_j[0] - 100, u_j[-1] + 20))
line, = ax1.plot([], [], lw=2)
plt.xlabel('X Position')
plt.ylabel('Y Position')
plotlays, plotcols = [2], ["orange","blue"]
lines = []
for index in range(2):
    lobj = ax1.plot([],[],lw=2,color=plotcols[index])[0]
    lines.append(lobj)


def init():
    for line in lines:
        line.set_data([],[])
    return lines

u_x,u_y = [],[]
v_x,v_y = [],[]
print("len:",len(u_i))
def animate(i):
    #print("test")
    x = u_i[i]
    y = u_j[i]
    u_x.append(x)
    u_y.append(y)

    x = v_i[i]
    y = v_j[i]
    v_x.append(x)
    v_y.append(y)

    xlist = [u_x, v_x]
    ylist = [u_y, v_y]

    #for index in range(0,1):
    for lnum,line in enumerate(lines):
        line.set_data(xlist[lnum], ylist[lnum]) # set data for each line separately.

    return lines

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=len(u_i), interval=.1, blit=True)

FFwriter = animation.FFMpegWriter(fps=30, extra_args=['-vcodec', 'libx264'])
#print(" ", FFwriter)
#anim.save('animation.mp4', writer = FFwriter)
anim.save('clip1.mov')

# save as gif, takes forever
#writergif = animation.PillowWriter(fps=1)
#anim.save(f, writer=writergif)


#plt.show()