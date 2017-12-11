// statistics.hpp ---
//
// Filename: statistics.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-07T03:47:30+0000
// Version:
// Last-Updated:
//           By:
//     Update #: 0
//

// Commentary:
//
//
//
//

// Change Log:
//
//
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
//
//

// Code:

#ifndef CTGA_TOOLS_STATISTICS_HPP_
#define CTGA_TOOLS_STATISTICS_HPP_

#include <gsl/gsl_statistics.h>

#include <map>
#include <numeric>
#include <utility>
#include <vector>

namespace ctga {
namespace tools {
namespace statistics {

/**
 *  \brief Sums the elements of a vector
 *
 *  \return Sum of the elements
 */
template <typename T>
inline double sum(typename std::vector<T>::iterator begin,
                  typename std::vector<T>::iterator end) {
  return std::accumulate(begin, end, 0.0);
}

/**
 *  \brief Compute the mean of a vector
 *
 *  \param vec Vector containing the values for which to compute the mean
 *  \return Mean of the values
 */
double mean(const std::vector<double>& vec);

/**
 *  \brief Compute the standard deviation of vector
 *
 *  \param vec Vector containing the values for which to compute the standard
 *  deviation
 *  \return Standard deviation
 */
double standard_deviation(const std::vector<double>& vec);

/**
 *  \brief Compute the mean and the standard deviation of a vector
 *
 *  \param vec Vector containing the values for which to compute the mean and
 *  the standard deviation
 *  \return Mean and standard deviation
 */
std::pair<double, double> mean_std(const std::vector<double>& vec);

/**
 *  \brief Compute the rank of the elements of two vectors
 *
 *  The values of both vectors are assembled into a third vector, and a rank is
 *  given independently of the origin vector.
 *
 *  \param s1 First vector of values
 *  \param s2 Second vecor of values
 *  \param ties Pointer to a vector registering the number of ties at each rank
 *  (@see MannWhitney)
 *  \return Pair, ranks of the first vector, ranks of the second vector
 */
std::pair<std::vector<double>, std::vector<double>>
rank(const std::vector<double>& s1, const std::vector<double>& s2,
     std::vector<unsigned>* ties);

/**
 *  \brief Compute the rank of the elements of two vectors
 *
 *  The values of both vectors are assembled into a third vector, and a rank is
 *  given independently of the origin vector.
 *
 *  \param s1 First vector of values
 *  \param s2 Second vecor of values
 *  \return Pair, ranks of the first vector, ranks of the second vector
 */
inline std::pair<std::vector<double>, std::vector<double>>
rank(const std::vector<double>& s1, const std::vector<double>& s2) {
  return rank(s1, s2, nullptr);
}

/**
 *  \brief Compute the rank of the elements in the vector
 *
 *  \param s1 Vector of values
 *  \param ties Pointer to a vector registering the number of ties at each rank
 *  \return Ranks of the values of the vector
 */
inline std::vector<double> rank(const std::vector<double>& s1,
                                std::vector<unsigned>* ties) {
  return rank(s1, std::vector<double>{}, ties).first;
}

/**
 *  \brief Compute the rank of the elements of the vector
 *
 *  \param s1 Vector of values
 *  \return ranks of the values of the vector
 */
inline std::vector<double> rank(const std::vector<double>& s1) {
  return rank(s1, std::vector<double>{}, nullptr).first;
}

/**
 *  \brief Compute the current point's distance to the Kurtosis
 *
 *  \param val Current point
 *  \param vec Vector containing all points
 *  \return Distance to the Kurtosis
 */
double dist_kurtosis(double val, const std::vector<double>& vec);

/**
 *  \brief Compute the thinness of a point relative to every known points
 *
 *  \param val Current point
 *  \param vec Vector containing all points
 *  \return Thinness of the current point
 */
double thinness(double val, const std::vector<double> &vec);

}  // namespace statistics
}  // namespace tools
}  // namespace ctga

#endif  // CTGA_TOOLS_STATISTICS_HPP_


//
// statistics.hpp ends here
