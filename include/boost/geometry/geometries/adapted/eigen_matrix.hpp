// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010 Alfredo Correa
// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2016 Norbert Wenzel

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Modified from the orignal code by Tim Keitt 4/7/17
// Changes Copyright (c) 2017 Tim Keitt

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_EIGEN_MATRIX_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_EIGEN_MATRIX_HPP

#define BOOST_GEOMETRY_ADAPTED_EIGEN_MATRIX_TAG_DEFINED

#include <cstddef>

#include <boost/type_traits/is_arithmetic.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <Eigen/Dense>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// Create class and specialization to indicate the tag
// for normal cases and the case that the type of the std-array is arithmetic
template <bool>
struct eigen_matrix_tag
{
  typedef geometry_not_recognized_tag type;
};


template <>
struct eigen_matrix_tag<true>
{
  typedef point_tag type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// Assign the point-tag, preventing arrays of points getting a point-tag
template <typename CoordinateType, std::size_t DimensionCount>
struct tag<Eigen::Matrix<CoordinateType, DimensionCount, 1> >
  : detail::eigen_matrix_tag<boost::is_arithmetic<CoordinateType>::value> {};


template <typename CoordinateType, std::size_t DimensionCount>
struct coordinate_type<Eigen::Matrix<CoordinateType, DimensionCount, 1> >
{
  typedef CoordinateType type;
};


template <typename CoordinateType, std::size_t DimensionCount>
struct dimension<Eigen::Matrix<CoordinateType, DimensionCount, 1> >: boost::mpl::int_<DimensionCount> {};


template <typename CoordinateType, std::size_t DimensionCount, std::size_t Dimension>
struct access<Eigen::Matrix<CoordinateType, DimensionCount, 1>, Dimension>
{
  static inline CoordinateType get(Eigen::Matrix<CoordinateType, DimensionCount, 1> const& a)
  {
    return a(Dimension);
  }

  static inline void set(Eigen::Matrix<CoordinateType, DimensionCount, 1>& a,
                         CoordinateType const& value)
  {
    a(Dimension) = value;
  }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#define BOOST_GEOMETRY_REGISTER_EIGEN_MATRIX_CS(CoordinateSystem) \
namespace boost { namespace geometry { namespace traits {      \
template <class T, std::size_t N>                              \
struct coordinate_system<Eigen::Matrix<T, N, 1> >              \
{                                                              \
  typedef CoordinateSystem type;                               \
};                                                             \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_EIGEN_MATRIX_HPP
