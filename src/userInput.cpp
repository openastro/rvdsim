/*
 * Copyright (c) 2014-2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <iostream>
#include <limits>

#include "rvdsim/userInput.hpp"

namespace rvdsim
{

//! Check input parameters.
UserInput checkInput( const rapidjson::Document& config )
{
    // Search for propagation settings in config.
    rapidjson::Value::ConstMemberIterator propagationSettingsIterator
        = config.FindMember( "propagation_settings" );
    if ( propagationSettingsIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"propagation_settings\" could not be found in "
                  << "JSON input!"
                  << std::endl;
        throw;
    }

    const rvdsim::Real startTime = propagationSettingsIterator->value[ 0 ].GetDouble( );
    std::cout << "Start time                    [s]             " << startTime << std::endl;
    const rvdsim::Real endTime   = propagationSettingsIterator->value[ 1 ].GetDouble( );
    std::cout << "End time                      [s]             " << endTime << std::endl;

    // Search for Earth gravitational parameter in config [m^3 s^-2].
    rapidjson::Value::ConstMemberIterator gravitationalParameterIterator
        = config.FindMember( "earth_gravitational_parameter" );
    if ( gravitationalParameterIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"earth_gravitational_parameter\" could not be "
                  << "found in JSON input!"
                  << std::endl;
        throw;
    }
    const rvdsim::Real earthGravitationalParameter
        = gravitationalParameterIterator->value.GetDouble( );
    std::cout << "Earth gravitational parameter [m^3 s^-2]      "
              << earthGravitationalParameter << std::endl;

    // Search for target's semi-major axis in config [m].
    rapidjson::Value::ConstMemberIterator targetSemiMajorAxisIterator
        = config.FindMember( "target_semi_major_axis" );
    if ( targetSemiMajorAxisIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"target_semi_major_axis\" could not be found in "
                  << "JSON input!"
                  << std::endl;
        throw;
    }
    const rvdsim::Real targetSemiMajorAxis = targetSemiMajorAxisIterator->value.GetDouble( );
    std::cout << "Target semi-major axis        [m]             "
              << targetSemiMajorAxis << std::endl;

    // Search for chaser initial state in config.
    rapidjson::Value::ConstMemberIterator chaserInitialStateIterator
        = config.FindMember( "chaser_initial_state" );
    if ( chaserInitialStateIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"chaser_initial_state\" could not be found in "
                  << "JSON input!"
                  << std::endl;
        throw;
    }
    rvdsim::Vector6 chaserInitialState( 6 );
    for ( int i = 0; i < 6; ++i )
    {
        chaserInitialState[ i ] = chaserInitialStateIterator->value[ i ].GetDouble( );
    }
    std::cout << "Chaser initial state          [m; m/s]        "
              << "[";
    for ( int i = 0; i < 5; ++i )
    {
        std::cout << chaserInitialState[ i ] << ", ";
    }
    std::cout << chaserInitialState[ 5 ] << "]" << std::endl;

    // Search for chaser thruster settings in config.
    rapidjson::Value::ConstMemberIterator chaserThrustSettingsIterator
        = config.FindMember( "chaser_thrust_settings" );
    if ( chaserThrustSettingsIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"chaser_thrust_settings\" could not be found in "
                  << "JSON input!"
                  << std::endl;
        throw;
    }
    std::string chaserThrustModeString = chaserThrustSettingsIterator->value[ 0 ].GetString( );
    ThrustMode chaserThrustMode;
    std::cout << "Chaser thrust mode                            ";
    if ( !chaserThrustModeString.compare( "off" ) )
    {
        chaserThrustMode = off;
        std::cout << "OFF" << std::endl;
    }
    else if ( !chaserThrustModeString.compare( "throttle" ) )
    {
        chaserThrustMode = throttle;
        std::cout << "throttle" << std::endl;
    }
    else if ( !chaserThrustModeString.compare( "on_off" ) )
    {
        chaserThrustMode = onOff;
        std::cout << "ON-OFF" << std::endl;
    }
    else
    {
        std::cerr << "ERROR: 2nd configuration option for \"chaser_thrust_settings\" should be "
                  << "\"throttle\", \"on_off\" or \"off\"!"
                  << std::endl;
        throw;
    }
    const rvdsim::Real chaserThrustMaximum = chaserThrustSettingsIterator->value[ 1 ].GetDouble( );
    std::cout << "Chaser thrust maximum         [N]             ";
    if ( chaserThrustMaximum < 0.0 )
    {
        std::cout << std::endl;
        std::cerr << "ERROR: \"chaser thrust maximum\" should be non-negative!" << std::endl;
        throw;
    }
    else if ( chaserThrustMaximum < std::numeric_limits< double >::epsilon( ) )
    {
        std::cout << "UNCONSTRAINED" << std::endl;
    }
    else
    {
        std::cout << chaserThrustMaximum << std::endl;
    }

    const rvdsim::Real chaserThrustFrequency
        = chaserThrustSettingsIterator->value[ 2 ].GetDouble( );
    if ( chaserThrustFrequency < std::numeric_limits< double >::epsilon( ) )
    {
        std::cout << std::endl;
        std::cerr << "ERROR: \"chaser thrust frequency\" should be positive!" << std::endl;
        throw;
    }
    std::cout << "Chaser thrust frequency       [Hz]            "
              << chaserThrustFrequency << std::endl;

    // Search for chaser mass in config.
    rapidjson::Value::ConstMemberIterator chaserWetMassIterator
        = config.FindMember( "chaser_wet_mass" );
    if ( chaserWetMassIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"chaser_wet_mass\" could not be found in JSON "
                  << "input!" << std::endl;
        throw;
    }
    const rvdsim::Real chaserWetMass = chaserWetMassIterator->value.GetDouble( );
    std::cout << "Chaser wet mass               [kg]            " << chaserWetMass << std::endl;

    // Search for arrival distance tolerance in config.
    rapidjson::Value::ConstMemberIterator arrivalDistanceToleranceIterator
        = config.FindMember( "arrival_distance_tolerance" );
    if ( arrivalDistanceToleranceIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"arrival_distance_tolerance\" could not be "
                  << "found in JSON input!"
                  << std::endl;
        throw;
    }
    const rvdsim::Real arrivalDistanceTolerance
        = arrivalDistanceToleranceIterator->value.GetDouble( );
    std::cout << "Arrival distance tolerance    [m]             "
              << arrivalDistanceTolerance << std::endl;

    // Search for output directory in config.
    rapidjson::Value::ConstMemberIterator outputDirectoryIterator
        = config.FindMember( "output_directory" );
    if ( outputDirectoryIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"output_directory\" could not be found in "
                  << "JSON input!"
                  << std::endl;
        throw;
    }
    const std::string outputDirectory = outputDirectoryIterator->value.GetString( );
    std::cout << "Output directory                              "
              << outputDirectory << std::endl;

    // Search for chaser state history filename in config.
    rapidjson::Value::ConstMemberIterator chaserStateHistoryFilenameIterator
        = config.FindMember( "chaser_state_history_filename" );
    if ( chaserStateHistoryFilenameIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"chaser_state_history_filename\" could not be "
                  << "found in JSON input!"
                  << std::endl;
        throw;
    }
    const std::string chaserStateHistoryFilename
        = chaserStateHistoryFilenameIterator->value.GetString( );
    std::cout << "State history output file                     "
              << chaserStateHistoryFilename << std::endl;

    // Search for chaser thrust history filename in config.
    rapidjson::Value::ConstMemberIterator chaserThrustHistoryFilenameIterator
        = config.FindMember( "chaser_thrust_history_filename" );
    if ( chaserThrustHistoryFilenameIterator == config.MemberEnd( ) )
    {
        std::cerr << "ERROR: Configuration option \"chaser_thrust_history_filename\" could not be "
                  << "found in JSON input!"
                  << std::endl;
        throw;
    }
    const std::string chaserThrustHistoryFilename
        = chaserThrustHistoryFilenameIterator->value.GetString( );
    std::cout << "Thrust history output file                    "
              << chaserThrustHistoryFilename << std::endl;

    return UserInput( startTime,
                      endTime,
                      earthGravitationalParameter,
                      targetSemiMajorAxis,
                      chaserInitialState,
                      chaserThrustMode,
                      chaserThrustMaximum,
                      chaserThrustFrequency,
                      chaserWetMass,
                      arrivalDistanceTolerance,
                      outputDirectory,
                      chaserStateHistoryFilename,
                      chaserThrustHistoryFilename );
}

} // namespace rvdsim
