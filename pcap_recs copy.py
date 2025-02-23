from ouster.sdk import *
import ouster.sdk.client as client
import matplotlib.pyplot as plt
import numpy as np

# Open the source (pcap file and metadata JSON)
source = open_source("OS-1-16-A0_122026000092_1024x20_20250223_121052.pcap", meta=["OS-1-16-A0_122026000092_1024x20_20250223_121052.json"])
metadata = source.metadata

all_x = []
all_y = []
all_z = []
x = 0
cnt = 0
for test in source:
    scan = test

    xyzlut = client.XYZLut(metadata)
    xyz = xyzlut(scan)

    x, y, z = [c.flatten() for c in np.dsplit(xyz, 3)]

    all_x.append(x)
    all_y.append(y)
    all_z.append(z)
    cnt += 1
    if cnt >= 3:
        break
single_scan_length = len(x)


x = np.concatenate(all_x)
y = np.concatenate(all_y)
z = np.concatenate(all_z)

print("Points:", x.shape)

# 3D visualization
ax = plt.axes(projection='3d')
r = 10
ax.set_xlim3d([-r, r])
ax.set_ylim3d([-r, r])
ax.set_zlim3d([-r/2, r/2])

# Set color based on the z-coordinate
z_col = np.minimum(np.abs(z), 5)

ax.scatter(x, y, z, c=z_col, s=0.2)

plt.axis('off')
# plt.show()


with open('vectors.txt', 'w') as f:
    f.write(f"{len(x)}\n")
    f.write(f"{(single_scan_length)}\n")
    
    for i in range(len(x)):
        f.write(f"{x[i]} {y[i]} {z[i]}\n")


