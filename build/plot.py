import numpy as np
import matplotlib.pyplot as plt

with open('data.dat') as g:
    lines_g = g.readlines()
    x_g = [line.split()[0] for line in lines_g]
    y_g = [line.split()[1] for line in lines_g]
x_traj=[]
y_traj=[]
for elem in x_g:
  x_traj.append(float(elem))
for elem in y_g:
  y_traj.append(float(elem)) 
  
   
with open('lines.dat') as h:
    lines_h = h.readlines()
    x_h = [line.split()[0] for line in lines_h]
    y_h = [line.split()[1] for line in lines_h]
x_line=[]
y_line=[]
for elem in x_h:
  x_line.append(float(elem))
for elem in y_h:
  y_line.append(float(elem)) 
  
with open('rays.dat') as ray:
    lines_ray = ray.readlines()
    x_r = [line.split()[0] for line in lines_ray]
    y_r = [line.split()[1] for line in lines_ray]
x_ray=[]
y_ray=[]
for elem in x_r:
  x_ray.append(float(elem))
for elem in y_r:
  y_ray.append(float(elem)) 
      
fig = plt.figure()


plt.plot(x_traj,y_traj,linewidth=2, color='purple' )
plt.scatter(x_line,y_line)
plt.plot(x_ray,y_ray, linewidth=1,color='green')
#plt.savefig('image.png')
plt.show()
