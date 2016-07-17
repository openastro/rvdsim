/*
 * Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <cstdlib>
#include <limits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <rapidjson/document.h>

#include <Astro/astro.hpp>
#include <SML/sml.hpp>

#include "rvdsim/userInput.hpp"
#include "rvdsim/typedefs.hpp"

int main( const int numberOfInputs, const char* inputArguments[ ] )
{

    ///////////////////////////////////////////////////////////////////////////

    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                              rvdsim                              " << std::endl;
    std::cout << std::endl;
    std::cout << "         Copyright (c) 2016, K. Kumar (me@kartikkumar.com)        " << std::endl;
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////

    std::cout << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "                          Input parameters                        " << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;

    // Check that only one input has been provided (a JSON file).
    if ( numberOfInputs - 1 != 1 )
    {
        std::cerr << "ERROR: Number of inputs is wrong. Please only provide a JSON input file!"
                  << std::endl;
        throw;
    }

    ///////////////////////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////////////////////

    // Read and store JSON input document (filter out comment lines).
    // TODO: Need to make comment-line filtering more robust.
    std::ifstream inputFile( inputArguments[ 1 ] );
    std::stringstream jsonDocumentBuffer;
    std::string inputLine;
    while ( std::getline( inputFile, inputLine ) )
    {
        size_t startPosition = inputLine.find_first_not_of( " \t" );
        if ( std::string::npos != startPosition )
        {
            inputLine = inputLine.substr( startPosition );
        }

        if ( inputLine.substr( 0, 2 ) != "//" )
        {
            jsonDocumentBuffer << inputLine << "\n";
        }
    }

    // Parse JSON document.
    rapidjson::Document config;
    config.Parse( jsonDocumentBuffer.str( ).c_str( ) );

    // // Verify config parameters. Exception is thrown if any of the parameters are missing.
    // const UserInput input = checkInput( config );

    ///////////////////////////////////////////////////////////////////////////

    // ///////////////////////////////////////////////////////////////////////////

    // // Execute RVD simulation.

    // std::cout << std::endl;
    // std::cout << "******************************************************************" << std::endl;
    // std::cout << "                       Simulation & Output                        " << std::endl;
    // std::cout << "******************************************************************" << std::endl;
    // std::cout << std::endl;

    // // Compute maximum thrust acceleration available to chaser.
    // const rvdsim::Real thrustAccelerationMaximum = chaserThrustMaximum / chaserMass;
    // std::cout << "Chaser thrust acceleration maximum [m/s^2]    "
    //           << thrustAccelerationMaximum << std::endl;

    // // Compute length of thruster pulse [s].
    // const rvdsim::Real thrustPulseTime = 1.0 / chaserThrustFrequency;
    // std::cout << "Chaser thrust pulse time [s]                  " << thrustPulseTime << std::endl;

    // // Compute current chaser epoch, state and Time-To-Go (TTG) [s].
    // rvdsim::Real    currentTime      = startTime;
    // rvdsim::Vector6 currentState     = chaserInitialState;
    // rvdsim::Real    timeToGo         = endTime - startTime;

    // // Compute mean motion of target's orbit [rad/s].
    // const rvdsim::Real targetMeanMotion
    //     = astro::computeKeplerMeanMotion( targetSemiMajorAxis, earthGravitationalParameter );
    // std::cout << "Target mean motion [rad/s]                    " << targetMeanMotion << std::endl;

    // rvdsim::Vector3 zeroThrustAcceleration( 3 );
    // zeroThrustAcceleration[ astro::xPositionIndex ] = 0.0;
    // zeroThrustAcceleration[ astro::yPositionIndex ] = 0.0;
    // zeroThrustAcceleration[ astro::zPositionIndex ] = 0.0;

    // rvdsim::Vector3 zeroEffortMiss( 3 );
    // rvdsim::Vector3 zeroEffortVelocity( 3 );

    // rvdsim::StateHistory chaserStateHistory;
    // chaserStateHistory[ currentTime ] = currentState;

    // rvdsim::ThrustHistory chaserThrustHistory;

    // bool isThrottleMax = false;

    // std::cout << std::endl;
    // std::cout << "Executing simulation ... " << std::endl;

    // while ( timeToGo > 0.0 )
    // {
    //     // Compute end state resulting from ballistic trajectory.
    //     rvdsim::Vector6 zeroThrustEndState
    //         = astro::propagateClohessyWiltshireSolution( currentState,
    //                                                      timeToGo,
    //                                                      targetMeanMotion,
    //                                                      zeroThrustAcceleration );

    //     // Compute control action using ZEM/ZEM feedback law.
    //     rvdsim::Vector3 thrustAcceleration( 3 );

    //     if ( !chaserThrustMode.compare( "off" ) )
    //     {
    //         thrustAcceleration = zeroThrustAcceleration;
    //     }
    //     else
    //     {
    //         zeroEffortMiss[ astro::xPositionIndex ] = -zeroThrustEndState[ astro::xPositionIndex ];
    //         zeroEffortMiss[ astro::yPositionIndex ] = -zeroThrustEndState[ astro::yPositionIndex ];
    //         zeroEffortMiss[ astro::zPositionIndex ] = -zeroThrustEndState[ astro::zPositionIndex ];

    //         zeroEffortVelocity[ astro::xPositionIndex ]
    //             = -zeroThrustEndState[ astro::xVelocityIndex ];
    //         zeroEffortVelocity[ astro::yPositionIndex ]
    //             = -zeroThrustEndState[ astro::yVelocityIndex ];
    //         zeroEffortVelocity[ astro::zPositionIndex ]
    //             = -zeroThrustEndState[ astro::zVelocityIndex ];

    //         for ( int i = 0; i < 3; ++i )
    //         {
    //             thrustAcceleration[ i ] = 6.0 / ( timeToGo * timeToGo ) * zeroEffortMiss [ i ]
    //                                       -2.0 / timeToGo * zeroEffortVelocity[ i ];
    //         }

    //         if ( thrustAccelerationMaximum > 0.0 )
    //         {
    //             const rvdsim::Real thrustAccelerationNorm
    //                 = sml::norm< double >( thrustAcceleration );

    //             if ( !chaserThrustMode.compare( "throttle" )
    //                  && thrustAccelerationNorm > thrustAccelerationMaximum )
    //             {
    //                 isThrottleMax = true;

    //                 for ( int i = 0; i < 3; ++i )
    //                 {
    //                     thrustAcceleration[ i ] = thrustAccelerationMaximum
    //                                               * thrustAcceleration[ i ]
    //                                               / thrustAccelerationNorm;
    //                 }
    //             }
    //             else if ( !chaserThrustMode.compare( "on_off" ) )
    //             {
    //                 if ( thrustAccelerationNorm > thrustAccelerationMaximum / 2.0 )
    //                 {
    //                     for ( int i = 0; i < 3; ++i )
    //                     {
    //                         thrustAcceleration[ i ] = thrustAccelerationMaximum
    //                                                   * thrustAcceleration[ i ]
    //                                                   / thrustAccelerationNorm;
    //                     }
    //                 }
    //                 else
    //                 {
    //                     thrustAcceleration = zeroThrustAcceleration;
    //                 }
    //             }
    //         }

    //     }

    //     // Propagate dynamics under control action.
    //     rvdsim::Vector6 constantThrustEndState
    //         = astro::propagateClohessyWiltshireSolution( currentState,
    //                                                      thrustPulseTime,
    //                                                      targetMeanMotion,
    //                                                      thrustAcceleration );

    //     // Add chaser thrust to history.
    //     rvdsim::Vector3 chaserThrust( 3 );
    //     for ( int i = 0; i < 3; ++i )
    //     {
    //         chaserThrust[ i ] = thrustAcceleration[ i ] * chaserMass;
    //     }

    //     chaserThrustHistory[ currentTime ] = chaserThrust;

    //     // Update current state to state at end of thruster pulse.
    //     currentState = constantThrustEndState;

    //     // Update current time to end of thruster pulse.
    //     currentTime = currentTime + thrustPulseTime;

    //     // Recompute Time-To-Go [s].
    //     timeToGo = timeToGo - thrustPulseTime;

    //     // Add current time and state to chaser history.
    //     chaserStateHistory[ currentTime ] = currentState;
    // }

    // if ( isThrottleMax )
    // {
    //     std::cout << "Maximum thrust level reached, thruster throttled!" << std::endl;
    // }

    // std::cout << "Simulation completed successfully!" << std::endl;
    // std::cout << std::endl;

    // std::cout << "Writing output to file ... " << std::endl;

    // // Write chaser state history to CSV file.
    // std::ostringstream chaserStateHistoryPath;
    // chaserStateHistoryPath << outputDirectory << "/" << chaserStateHistoryFilename;
    // std::ofstream chaserStateHistoryFile(  chaserStateHistoryPath.str( ) );
    // chaserStateHistoryFile << "t,x,y,z,xdot,ydot,zdot" << std::endl;
    // for ( rvdsim::StateHistory::iterator it = chaserStateHistory.begin( );
    //       it != chaserStateHistory.end( );
    //       ++it )
    // {
    //     chaserStateHistoryFile << it->first << ","
    //                            << it->second[ 0 ] << ","
    //                            << it->second[ 1 ] << ","
    //                            << it->second[ 2 ] << ","
    //                            << it->second[ 3 ] << ","
    //                            << it->second[ 4 ] << ","
    //                            << it->second[ 5 ] << std::endl;
    // }
    // chaserStateHistoryFile.close( );

    // // Write chaser thrust history to CSV file.
    // std::ostringstream chaserThrustHistoryPath;
    // chaserThrustHistoryPath << outputDirectory << "/" << chaserThrustHistoryFilename;
    // std::ofstream chaserThrustHistoryFile(  chaserThrustHistoryPath.str( ) );
    // chaserThrustHistoryFile << "t,Tx,Ty,Tz" << std::endl;
    // for ( rvdsim::ThrustHistory::iterator it = chaserThrustHistory.begin( );
    //       it != chaserThrustHistory.end( );
    //       ++it )
    // {
    //     chaserThrustHistoryFile << it->first << ","
    //                             << it->second[ 0 ] << ","
    //                             << it->second[ 1 ] << ","
    //                             << it->second[ 2 ] << std::endl;
    // }
    // chaserThrustHistoryFile.close( );

    // std::cout << "Output written to file successfully!" << std::endl;
    // std::cout << std::endl;

    // // Check if target was reached.
    // rvdsim::Vector6 finalState = chaserStateHistory.rbegin( )->second;
    // const rvdsim::Real finalDistanceToTarget = sml::norm< double >( finalState );
    // if ( finalDistanceToTarget > arrivalDistanceTolerance )
    // {
    //     std::cout << "Target not reached! :(" << std::endl;
    //     std::cout << "You are " << finalDistanceToTarget << " m from the target" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Congrats! You reached the target! :)" << std::endl;
    // }

    // ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////

    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                         Exited successfully!                     " << std::endl;
    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;

    ///////////////////////////////////////////////////////////////////////////
}
