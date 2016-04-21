#!/bin/bash
# Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

function pause(){
   read -p "$*"
}

# Run simulator and plotting scripts.
# The path to the config files should be passed as a command-line parameter to this script.

echo ''
pause 'Press [Enter] to run the Rvdsim simulator ...'
../build/bin/rvdsim $1/rvdsim_config.json

pause 'Press [Enter] to generate a plot of the chaser path ...'
python ../python/plot_chaser_path.py $1/plot_chaser_path.json

pause 'Press [Enter] to generate a plot of the chaser thrust profile ...'
python ../python/plot_chaser_thrust.py $1/plot_chaser_thrust.json
