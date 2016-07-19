/*
 * Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <map>
#include <typeinfo>
#include <vector>

#include <catch.hpp>

#include "rvdsim/typedefs.hpp"

namespace rvdsim
{
namespace tests
{

TEST_CASE( "Test typedefs", "[typedef]" )
{
    REQUIRE( typeid( Real )             == typeid( double ) );
    REQUIRE( typeid( Vector3 )          == typeid( std::vector< Real > ) );
    REQUIRE( typeid( Vector6 )          == typeid( std::vector< Real > ) );
    REQUIRE( typeid( StateHistory )     == typeid( std::map< Real, Vector6 > ) );
    REQUIRE( typeid( ThrustHistory )    == typeid( std::map< Real, Vector3 > ) );
}

} // namespace tests
} // namespace rvdsim
