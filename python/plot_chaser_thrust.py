'''
Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
Distributed under the MIT License.
See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
'''

# Set up modules and packages
# Plotting
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from matplotlib import rcParams
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d import axes3d

# I/O
import commentjson
import json
from pprint import pprint

# Numerical
import numpy as np
import pandas as pd

# System
import sys
import time

print ""
print "------------------------------------------------------------------"
print "                              RVDSim                              "
print "         Copyright (c) 2016, K. Kumar (me@kartikkumar.com)        "
print "------------------------------------------------------------------"
print ""

# Start timer.
start_time = time.time( )

print ""
print "******************************************************************"
print "                          Input parameters                        "
print "******************************************************************"
print ""

# Parse JSON configuration file
# Raise exception if wrong number of inputs are provided to script
if len(sys.argv) != 2:
    raise Exception("Only provide a JSON config file as input!")

json_data = open(sys.argv[1])
config = commentjson.load(json_data)
json_data.close()
pprint(config)

print ""
print "******************************************************************"
print "                            Operations                            "
print "******************************************************************"
print ""

print "Input data files being read ..."

input_path_prefix = config["input_directory"] + "/"
output_path_prefix = config["output_directory"] + '/'

# Read and store data files.
chaser_thrust = pd.read_csv(input_path_prefix + config["chaser_thrust"])

print "Input data files successfully read!"

print "figures being generated ..."

# Generate figure with 2D views
fig = plt.figure()
ax1 = fig.add_subplot(2, 2, 1)
ax2 = fig.add_subplot(2, 2, 2)
ax3 = fig.add_subplot(2, 2, 3)
ax4 = fig.add_subplot(2, 2, 4, frameon=False)

# Plot time-history of x-component of thrust history.
ax1.plot(chaser_thrust['t'],chaser_thrust['Tx'],color='k')
ax1.set_xlabel('t [s]')
ax1.set_ylabel('x [N]')
ax1.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax1.grid()

# Plot time-history of z-component of thrust history.
ax2.plot(chaser_thrust['t'],chaser_thrust['Tz'],color='k')
ax2.set_xlabel('t [s]')
ax2.set_ylabel('z [N]')
ax2.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax2.grid()

# Plot time-history of y-component of thrust history.
ax3.plot(chaser_thrust['t'],chaser_thrust['Ty'],color='k')
ax3.set_xlabel('t [s]')
ax3.set_ylabel('y [N]')
ax3.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax3.grid()

# # Plot metadata table
# ax4.axis('off')
# the_table = ax4.table(cellText=metadata_table,colLabels=None,cellLoc='center',loc='center')
# table_props = the_table.properties()
# table_cells = table_props['child_artists']
# for cell in table_cells: cell.set_height(0.15)
# cell_dict = the_table.get_celld()
# for row in xrange(0,7): cell_dict[(row,2)].set_width(0.1)

# Save figure
plt.tight_layout()
plt.savefig(output_path_prefix + config["2D_figure"], dpi=config["figure_dpi"])

# # Generate 3D figure if requested.
# if config["show_3D_figure"]:
#     fig = plt.figure()
#     ax = fig.gca(projection='3d')
#     ax.set_xlabel('x [km]')
#     ax.set_ylabel('y [km]')
#     ax.set_zlabel('z [km]')
#     ax.ticklabel_format(style='sci', axis='both', scilimits=(0,0))

#     # Plot sphere for the Earth
#     radius_Earth = 6371.0 # km
#     u = np.linspace(0, 2 * np.pi, 100)
#     v = np.linspace(0, np.pi, 100)
#     x = radius_Earth * np.outer(np.cos(u), np.sin(v))
#     y = radius_Earth * np.outer(np.sin(u), np.sin(v))
#     z = radius_Earth * np.outer(np.ones(np.size(u)), np.cos(v))
#     ax.plot_surface(x, y, z,  rstride=4, cstride=4, color='b',edgecolors='b')

#     # Plot departure and arrival orbits
#     ax.plot3D(departure_orbit['x'],departure_orbit['y'],departure_orbit['z'],'g')
#     ax.plot3D(arrival_orbit['x'],arrival_orbit['y'],arrival_orbit['z'],'r')

#     # Plot transfer trajectory
#     ax.plot3D(transfer_path['x'],transfer_path['y'],transfer_path['z'],'k')
#     ax.scatter(transfer_path['x'][0],transfer_path['y'][0],transfer_path['z'][0], \
#                s=100,marker='o',c='g')
#     ax.scatter(transfer_path['x'][transfer_path.index[-1]], \
#                transfer_path['y'][transfer_path.index[-1]], \
#                transfer_path['z'][transfer_path.index[-1]],s=100,marker='o',c='r')

#     # Create cubic bounding box to simulate equal aspect ratio
#     X = transfer_path['x']
#     Y = transfer_path['y']
#     Z = transfer_path['z']
#     max_range = np.array([X.max()-X.min(), Y.max()-Y.min(), Z.max()-Z.min()]).max() / 2.0
#     mean_x = X.mean()
#     mean_y = Y.mean()
#     mean_z = Z.mean()
#     ax.set_xlim(mean_x - max_range, mean_x + max_range)
#     ax.set_ylim(mean_y - max_range, mean_y + max_range)
#     ax.set_zlim(mean_z - max_range, mean_z + max_range)

#     plt.grid()
#     plt.show()

print "Figures generated successfully!"
print ""

# Stop timer
end_time = time.time( )

# Print elapsed time
print "Script time: " + str("{:,g}".format(end_time - start_time)) + "s"

print ""
print "------------------------------------------------------------------"
print "                         Exited successfully!                     "
print "------------------------------------------------------------------"
print ""
