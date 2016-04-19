/*
 * Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef RVDSIM_RELATIVE_MOTION_HPP
#define RVDSIM_RELATIVE_MOTION_HPP

#include <cmath>
#include <vector>

#include <Astro/astro.hpp>

namespace rvdsim
{

//! Propagate constant-force Clohessy-Wiltshire solution.
template< typename Real, typename Vector6, typename Vector3 >
Vector6 propagateClohessyWiltshireSolution( const Vector6& initialState,
                                            const Real finalTime,
                                            const Real targetMeanMotion,
                                            const Vector3& thrustAcceleration )
{
    Vector6 finalState = initialState;

    finalState[ astro::xPositionIndex ]
        = // unperturbed terms
          ( 4.0 / targetMeanMotion * initialState[ astro::xVelocityIndex ]
            - 6.0 * initialState[ astro::zPositionIndex ] )
            * std::sin( targetMeanMotion * finalTime )
          - 2.0 * initialState[ astro::zVelocityIndex ] / targetMeanMotion
            * std::cos( targetMeanMotion * finalTime )
          + ( 6.0 * targetMeanMotion * initialState[ astro::zPositionIndex ]
              - 3.0 * initialState[ astro::xVelocityIndex ] ) * finalTime
          + ( initialState[ astro::xPositionIndex ]
              + 2.0 * initialState[ astro::zVelocityIndex ] / targetMeanMotion )
          // constant force terms
          + 2.0 / ( targetMeanMotion * targetMeanMotion )
            * thrustAcceleration[ astro::zPositionIndex ]
            * ( targetMeanMotion * finalTime - std::sin( targetMeanMotion * finalTime ) )
          + thrustAcceleration[ astro::xPositionIndex ]
            * ( 4.0 / ( targetMeanMotion * targetMeanMotion )
                * ( 1.0 - std::cos( targetMeanMotion * finalTime ) )
                - 1.5 * finalTime * finalTime );

    finalState[ astro::yPositionIndex ]
        = // unperturbed terms
          initialState[ astro::yPositionIndex ] * std::cos( targetMeanMotion * finalTime )
          + initialState[ astro::yVelocityIndex ] / targetMeanMotion
            * std::sin( targetMeanMotion * finalTime )
          // constant force terms
          + thrustAcceleration[ astro::yPositionIndex ] / ( targetMeanMotion * targetMeanMotion )
            * ( 1.0 - std::cos( targetMeanMotion * finalTime ) );

    finalState[ astro::zPositionIndex ]
        = // unperturbed terms
          ( 2.0 * initialState[ astro::xVelocityIndex ] / targetMeanMotion
            - 3.0 * initialState[ astro::zPositionIndex ] )
            * std::cos( targetMeanMotion * finalTime )
          + initialState[ astro::zVelocityIndex ] / targetMeanMotion
          * std::sin( targetMeanMotion * finalTime )
          + ( 4.0 * initialState[ astro::zPositionIndex ]
            - 2.0 * initialState[ astro::xVelocityIndex ] / targetMeanMotion )
          // constant force terms
          + 2.0 / ( targetMeanMotion * targetMeanMotion )
            * thrustAcceleration[ astro::xPositionIndex ]
            * ( std::sin( targetMeanMotion * finalTime ) - targetMeanMotion * finalTime )
          + thrustAcceleration[ astro::zPositionIndex ] / ( targetMeanMotion * targetMeanMotion )
            * (1.0 - std::cos( targetMeanMotion * finalTime ) );

    finalState[ astro::xVelocityIndex ]
        = targetMeanMotion * ( 4.0 / targetMeanMotion * initialState[ astro::xVelocityIndex ]
            - 6.0 * initialState[ astro::zPositionIndex ] )
            * std::cos( targetMeanMotion * finalTime )
          + 2.0 * initialState[ astro::zVelocityIndex ]
            * std::sin( targetMeanMotion * finalTime )
          + ( 6.0 * targetMeanMotion * initialState[ astro::zPositionIndex]
              - 3.0 * initialState[ astro::xVelocityIndex ] );

    finalState[ astro::yVelocityIndex ]
        = -targetMeanMotion * initialState[ astro::yPositionIndex ]
          * std::sin( targetMeanMotion * finalTime );

    finalState[ astro::zVelocityIndex ]
        = -targetMeanMotion * ( 2.0 * initialState[ astro::xVelocityIndex ] / targetMeanMotion
            - 3.0 * initialState[ astro::zPositionIndex ] )
            * std::sin( targetMeanMotion * finalTime )
          + initialState[ astro::zVelocityIndex ] * std::cos( targetMeanMotion * finalTime );

    return finalState;
}

//! Compute unperturbed Hill equations.
template< typename Real, typename Vector6 >
Vector6 computeUnperturbedHillEquations( const Vector6& state, const Real targetMeanMotion )
{
    Vector6 stateDerivative = state;

    stateDerivative[ astro::xPositionIndex ] = state[ astro::xVelocityIndex ];
    stateDerivative[ astro::yPositionIndex ] = state[ astro::yVelocityIndex ];
    stateDerivative[ astro::zPositionIndex ] = state[ astro::zVelocityIndex ];
    stateDerivative[ astro::xVelocityIndex ]
        = 2.0 * targetMeanMotion * state[ astro::zVelocityIndex ];
    stateDerivative[ astro::yVelocityIndex ]
        = -targetMeanMotion * targetMeanMotion * state[ astro::yPositionIndex ];
    stateDerivative[ astro::zVelocityIndex ]
        = 3.0 * targetMeanMotion * targetMeanMotion * state[ astro::zPositionIndex ]
          - 2.0 * targetMeanMotion * state[ astro::xVelocityIndex ];

    return stateDerivative;
}

} // namespace rvdsim

#endif // RVDSIM_RELATIVE_MOTION_HPP
