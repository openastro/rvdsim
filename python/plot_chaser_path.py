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
chaser_path = pd.read_csv(input_path_prefix + config["chaser_path"])

print "Input data files successfully read!"

print "figures being generated ..."

# Generate figure with 2D views
fig = plt.figure()
ax1 = fig.add_subplot(2, 2, 1)
ax2 = fig.add_subplot(2, 2, 2)
ax3 = fig.add_subplot(2, 2, 3)
ax4 = fig.add_subplot(2, 2, 4, frameon=False)

# Plot X-Z projection
ax1.plot(chaser_path['x'],chaser_path['z'],color='k')
ax1.plot(chaser_path['x'].iloc[0],chaser_path['z'].iloc[0],color='g',marker='o')
ax1.plot(chaser_path['x'].iloc[-1],chaser_path['z'].iloc[-1],color='r',marker='o')
ax1.set_xlabel('x [m]')
ax1.set_ylabel('z [m]')
ax1.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax1.grid()

# Plot X-Y projection
ax2.plot(chaser_path['x'],chaser_path['y'],color='k')
ax2.plot(chaser_path['x'].iloc[0],chaser_path['y'].iloc[0],color='g',marker='o')
ax2.plot(chaser_path['x'].iloc[-1],chaser_path['y'].iloc[-1],color='r',marker='o')
ax2.set_xlabel('x [m]')
ax2.set_ylabel('y [m]')
ax2.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax2.grid()

# Plot Z-Y projection
ax3.plot(chaser_path['z'],chaser_path['y'],color='k')
ax3.plot(chaser_path['z'].iloc[0],chaser_path['y'].iloc[0],color='g',marker='o')
ax3.plot(chaser_path['z'].iloc[-1],chaser_path['y'].iloc[-1],color='r',marker='o')
ax3.set_xlabel('z [m]')
ax3.set_ylabel('y [m]')
ax3.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax3.grid()

# Plot metadata table
ax4.axis('off')
# the_table = ax4.table(cellText=metadata_table,colLabels=None,cellLoc='center',loc='center')
# table_props = the_table.properties()
# table_cells = table_props['child_artists']
# for cell in table_cells: cell.set_height(0.15)
# cell_dict = the_table.get_celld()
# for row in xrange(0,7): cell_dict[(row,2)].set_width(0.1)

# Save figure
plt.tight_layout()
plt.savefig(output_path_prefix + config["2D_figure"], dpi=config["figure_dpi"])

# Generate 3D figure if requested.
if config["show_3D_figure"]:
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.set_xlabel('x [m]')
    ax.set_ylabel('y [m]')
    ax.set_zlabel('z [m]')
    ax.ticklabel_format(style='sci', axis='both', scilimits=(0,0))

    # Plot chaser path.
    ax.scatter(chaser_path['x'].iloc[0],chaser_path['y'].iloc[0],chaser_path['z'].iloc[0], \
              color='g',marker='o')
    ax.scatter(chaser_path['x'].iloc[0],chaser_path['y'].iloc[0],chaser_path['z'].iloc[0], \
              color='r',marker='o')
    ax.plot3D(chaser_path['x'],chaser_path['y'],chaser_path['z'],'k')

    # Plot target.
    ax.scatter(0.0,0.0,0.0,color='k',marker='D')

    plt.grid()
    plt.show()

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
