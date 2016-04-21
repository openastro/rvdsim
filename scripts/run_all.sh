#!/bin/bash
# Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

set -ev

# Run simulator and plotting scripts.
# The path to the config files should be passed as a command-line parameter to this script.
../build/bin/rvdsim $1/rvdsim_config.json
python ../python/plot_chaser_path.py $1/plot_chaser_path.json
python ../python/plot_chaser_thrust.py $1/plot_chaser_thrust.json
