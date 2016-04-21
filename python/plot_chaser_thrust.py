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
ax1.set_ylabel('Tx [N]')
ax1.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax1.grid()

# Plot time-history of z-component of thrust history.
ax2.plot(chaser_thrust['t'],chaser_thrust['Tz'],color='k')
ax2.set_xlabel('t [s]')
ax2.set_ylabel('Tz [N]')
ax2.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax2.grid()

# Plot time-history of y-component of thrust history.
ax3.plot(chaser_thrust['t'],chaser_thrust['Ty'],color='k')
ax3.set_xlabel('t [s]')
ax3.set_ylabel('Ty [N]')
ax3.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax3.grid()

# Plot time-history of magnitude of thrust history.
ax4.plot(chaser_thrust['t'],np.sqrt(np.square(chaser_thrust[['Tx','Ty','Tz']]).sum(axis=1)),color='k')
ax4.set_xlabel('t [s]')
ax4.set_ylabel('T [N]')
ax4.ticklabel_format(style='sci', axis='both', scilimits=(0,0))
ax4.grid()

# Save figure.
plt.tight_layout()
plt.savefig(output_path_prefix + config["2D_figure"], dpi=config["figure_dpi"])

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
