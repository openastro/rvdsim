/*
 * Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef RVDSIM_USER_INPUT_HPP
#define RVDSIM_USER_INPUT_HPP

#include <string>

#include <rapidjson/document.h>

#include "rvdsim/typedefs.hpp"

namespace rvdsim
{

//! Chaser thrust mode.
/*!
 * Definition of chaser thrust modes:
 *  - off      : thruster is switched off completely and the system will be propagated under free
 *               motion
 *  - throttle : thruster can be throttled between 0% and 100%, where 100% is unbounded if maximum
 *               thrust is not defined
 *  - on_off   : thruster can only take on values of 0% and 100% (this mode only works if a maximum
 *               thrust level is defined)
 */
enum ThrustMode
{
    off,
    throttle,
    onOff
};

//! Input parameters provided by user for rvdsim.
struct UserInput
{
public:

    //! Define default constructor.
    UserInput( const Real               aStartTime,
               const Real               anEndTime,
               const Real               anEarthGravitationalParameter,
               const Real               aTargetSemiMajorAxis,
               const Vector6            aChaserInitialState,
               const ThrustMode         aThrustMode,
               const Real               aThrustMaximum,
               const Real               aThrustFrequency,
               const Real               aChaserWetMass,
               const Real               anArrivalDistanceTolerance,
               const std::string&       anOutputDirectory,
               const std::string&       aChaserStateHistoryFilename,
               const std::string&       aChaserThrustHistoryFilename )
        : startTime( aStartTime ),
          endTime( anEndTime ),
          earthGravitationalParameter( anEarthGravitationalParameter ),
          targetSemiMajorAxis( aTargetSemiMajorAxis ),
          chaserInitialState( aChaserInitialState ),
          thrustMode( aThrustMode ),
          thrustMaximum( aThrustMaximum ),
          thrustFrequency( aThrustFrequency ),
          chaserWetMass( aChaserWetMass ),
          arrivalDistanceTolerance( anArrivalDistanceTolerance ),
          outputDirectory( anOutputDirectory ),
          chaserStateHistoryFilename( aChaserStateHistoryFilename ),
          chaserThrustHistoryFilename( aChaserThrustHistoryFilename )
    { }

    //! Simulation start time [s].
    const Real startTime;

    //! Simulation end time [s].
    const Real endTime;

    //! Earth gravitational parameter [m^3 s^-2].
    const Real earthGravitationalParameter;

    //! Target semi-major axis [m].
    const Real targetSemiMajorAxis;

    //! Chaser initial state [m; m/s].
    const Vector6 chaserInitialState;

    //! Chaser thrust mode.
    const ThrustMode thrustMode;

    //! Chaser thrust maximum [N].
    const Real thrustMaximum;

    //! Chaser thrust frequency [Hz].
    const Real thrustFrequency;

    //! Chaser wet mass [kg].
    const Real chaserWetMass;

    //! Arrival distance tolerance [-] used to determine when to terminate simulation.
    const Real arrivalDistanceTolerance;

    //! Path to output directory.
    const std::string outputDirectory;

    //! Chaser state history filename [-].
    const std::string chaserStateHistoryFilename;

    //! Chaser thrust history filename [-].
    const std::string chaserThrustHistoryFilename;

protected:
private:
};

//! Check input parameters.
/*!
 * Checks that all inputs for the application are valid. If not, an error is thrown with a short
 * description of the problem. If all inputs are valid, a data struct containing all the inputs is
 * returned, which is subsequently used to execute the application.
 *
 * @sa UserInput
 * @param[in] config User-defined configuration options (extracted from JSON input file)
 * @return           Struct containing all valid input to execute application
 */
UserInput checkInput( const rapidjson::Document& config );

} // namespace rvdsim

#endif // RVDSIM_USER_INPUT_HPP
