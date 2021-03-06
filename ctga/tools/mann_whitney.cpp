// mann_whitney.cpp ---
//
// Filename: mann_whitney.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-07T06:05:44+0000
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

#include "ctga/tools/mann_whitney.hpp"

#include <boost/math/distributions.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "ctga/tools/statistics.hpp"

namespace ctga {
namespace tools {
namespace statistics {

void MannWhitney::reset(const std::vector<double> &s1,
                        const std::vector<double> &s2) {
  valid_ = false;
  probability_ = -1;
  s1_ = s1;
  s2_ = s2;
  nranks_ = 0;
  ties_.clear();
}

void MannWhitney::compute() {
  auto ranks = rank(s1_, s2_, &ties_);
  double u1 = std::accumulate(ranks.first.begin(), ranks.first.end(), 0.);
  // auto u2 = std::accumulate(ranks.second.begin(), ranks.second.end(), 0.);
  auto n1 = s1_.size();
  auto n2 = s2_.size();
  auto u = u1 - (n1 * (n1 + 1))/ 2;

  // Mean of the distribution
  auto Mu = static_cast<double>(n1 * n2) / 2.;

  // Tie correction
  double TS{};
  auto n = n1 + n2;
  for (auto i = 0U; i < nranks_; i++) {
    TS += static_cast<double>(std::pow(ties_[i], 3) - ties_[i]) / (n * (n - 1));
  }

  // Standard deviation of the distribution
  auto Varu = std::sqrt((static_cast<double>(n1 * n2) / 12) * (n + 1 - TS));

  // Standardized value
  auto z = (u - Mu) / Varu;
  std::cout << "Z = " << z << std::endl;

  // Compute the p-value
  boost::math::normal_distribution<> nd{0, 1};
  probability_ = boost::math::cdf(boost::math::complement(nd, fabs(z)));
}

}  // namespace statistics
}  // namespace tools
}  // namespace ctga

//
// mann_whitney.cpp ends here
