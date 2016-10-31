/*
 * Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch.hpp>
#include <vector>

#include "rvdsim/userInput.hpp"

namespace rvdsim
{
namespace tests
{

//! Define type for real, floating-point numbers.
typedef double Real;

//! Define container for vector of length 6.
typedef std::vector< Real > Vector6;

TEST_CASE( "Test thrust modes", "[input]" )
{
    // Enum type assigns integers to each thrust mode.
    REQUIRE( off      == 0 );
    REQUIRE( throttle == 1 );
    REQUIRE( onOff    == 2 );
}

TEST_CASE( "Test user input struct", "[input]" )
{
    // Create dummy initial state.
    Vector6 dummyInitialState( 6 );
    dummyInitialState[ 0 ] = 0.15;
    dummyInitialState[ 1 ] = -1.16;
    dummyInitialState[ 2 ] = 5.19;
    dummyInitialState[ 3 ] = -0.011;
    dummyInitialState[ 4 ] = 0.0613;
    dummyInitialState[ 5 ] = 0.0000001;

    // Create dummy user input struct.
    UserInput dummyUserInput( 0.3,
                              10.2,
                              1234.567,
                              10.0215,
                              dummyInitialState,
                              off,
                              1.522,
                              62.3,
                              1250.91,
                              1.0e-7,
                              "/path/to/output/directory",
                              "/path/to/chaser/state/history",
                              "/path/to/chaser/thrust/history" );

    REQUIRE( dummyUserInput.startTime                       == 0.3 );
    REQUIRE( dummyUserInput.endTime                         == 10.2 );
    REQUIRE( dummyUserInput.earthGravitationalParameter     == 1234.567 );
    REQUIRE( dummyUserInput.targetSemiMajorAxis             == 10.0215 );
    REQUIRE( dummyUserInput.chaserInitialState[ 0 ]         == dummyInitialState[ 0 ] );
    REQUIRE( dummyUserInput.chaserInitialState[ 1 ]         == dummyInitialState[ 1 ] );
    REQUIRE( dummyUserInput.chaserInitialState[ 2 ]         == dummyInitialState[ 2 ] );
    REQUIRE( dummyUserInput.chaserInitialState[ 3 ]         == dummyInitialState[ 3 ] );
    REQUIRE( dummyUserInput.chaserInitialState[ 4 ]         == dummyInitialState[ 4 ] );
    REQUIRE( dummyUserInput.chaserInitialState[ 5 ]         == dummyInitialState[ 5 ] );
    REQUIRE( dummyUserInput.thrustMode                      == off );
    REQUIRE( dummyUserInput.thrustMaximum                   == 1.522 );
    REQUIRE( dummyUserInput.thrustFrequency                 == 62.3 );
    REQUIRE( dummyUserInput.chaserWetMass                   == 1250.91 );
    REQUIRE( dummyUserInput.arrivalDistanceTolerance        == 1.0e-7 );
    REQUIRE( dummyUserInput.outputDirectory                 == "/path/to/output/directory" );
    REQUIRE( dummyUserInput.chaserStateHistoryFilename      == "/path/to/chaser/state/history" );
    REQUIRE( dummyUserInput.chaserThrustHistoryFilename     == "/path/to/chaser/thrust/history" );
}

} // namespace tests
} // namespace rvdsim
