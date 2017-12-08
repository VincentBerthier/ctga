// mann_whithey.hpp ---
//
// Filename: mann_whithey.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-07T05:46:09+0000
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

#ifndef CTGA_TOOLS_MANN_WHITNEY_HPP_
#define CTGA_TOOLS_MANN_WHITNEY_HPP_

#include <utility>
#include <vector>

namespace ctga {
namespace tools {
namespace statistics {

/**
 *  \brief Class performing the Mann-Whitney test
 *
 *  Class performing the Mann-Whitney test (@see
 *  https://en.wikipedia.org/wiki/Mann%E2%80%93Whitney_U_test)
 */
class MannWhitney {
 public:
  /**
   *  \brief MannWhitney constructor
   *
   *  \param s1 Vector containing the first serie of observations
   *  \param s2 Vector containing the second serie of observations
   */
  MannWhitney(const std::vector<double> &s1, const std::vector<double> &s2) :
      s1_{s1},
      s2_{s2} {}

  /**
   *  \brief Reset the class with two new series of observations
   *
   *  \param s1 Vector containing the first serie of observations
   *  \param s2 Vector containing the second serie of observations
   */
  void reset(const std::vector<double> &s1,
             const std::vector<double> &s2);

  /**
   *  \brief Get the p-value computed according to the Mann-Whitney test
   *
   *  \return p-value
   */
  inline double operator()() {
    if (!valid_)
      compute();
    return probability_;
  }

 private:
  bool valid_{false};
  double probability_{-1};
  std::vector<double> s1_;
  std::vector<double> s2_;

  unsigned nranks_{};
  std::vector<unsigned> ties_{};

  // Compute the p-value of the two series of observations
  void compute();
};

}  // namespace statistics
}  // namespace tools
}  // namespace ctga

#endif  // CTGA_TOOLS_MANN_WHITNEY_HPP_


//
// mann_whithey.hpp ends here
