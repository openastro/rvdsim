/*
 * Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef RVDSIM_TYPEDEFS_HPP
#define RVDSIM_TYPEDEFS_HPP

#include <cmath>
#include <map>
#include <vector>

#include <Astro/astro.hpp>

namespace rvdsim
{

//! Define type for real, floating-point numbers.
typedef double Real;

//! Define container for vector of length 3.
typedef std::vector< Real > Vector3;

//! Define container for vector of length 6.
typedef std::vector< Real > Vector6;

//! Define container for state history.
typedef std::map< Real, Vector6 > StateHistory;

//! Define container for thrust history.
typedef std::map< Real, Vector3 > ThrustHistory;

} // namespace rvdsim

#endif // RVDSIM_TYPEDEFS_HPP

