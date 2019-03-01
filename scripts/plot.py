#!/usr/bin/python

import sys
import matplotlib
matplotlib.use('TKAgg')
import matplotlib.pyplot as plt
from matplotlib import animation

timeline=[]
with open(sys.argv[1]) as f:
    niter = f.readline()
    nb = f.readline()
    niter = int(niter)
    nb = int(nb)
    for _ in range(niter):
        X=[]
        Y=[]
        Z=[]

        for _ in range(nb):
            x,y,z=f.readline().split()
            X.append(x)
            Y.append(y)
            Z.append(z)

        timeline.append((X,Y,Z))


fig = plt.figure()
boxDim=2e12
ax = plt.axes(xlim=(-boxDim, boxDim), ylim=(-boxDim, boxDim))
plt.xlabel("x-coordinate [m]")
plt.ylabel("y-coordinate [m]")
line, = ax.plot([], [],marker='o',linestyle='none')
def init():
    line.set_data([], [])
    return line,

def animate(i):
    line.set_data(timeline[i][0], timeline[i][1])
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=niter, interval=20, blit=True)

#plt.plot(X,Y, marker="o", linestyle="none")
plt.show()
