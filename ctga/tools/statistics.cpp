// statistics.cpp ---
//
// Filename: statistics.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-07T04:21:17+0000
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

#include "ctga/tools/statistics.hpp"

#include <cmath>
#include <map>
#include <utility>
#include <vector>

namespace ctga {
namespace tools {
namespace statistics {

double mean(const std::vector<double>& vec) {
  return std::accumulate(vec.begin(), vec.end(), 0.) / vec.size();
}


double standard_deviation(const std::vector<double>& vec) {
  auto m = mean(vec);
  auto lambda = [m](double sum, double val)
                { return sum += std::pow(val - m, 2); };
  return sqrt(1. / vec.size() * std::accumulate(vec.begin(),
                                                vec.end(),
                                                0., lambda));
}

std::pair<double, double> mean_std(const std::vector<double>& vec) {
  auto m = mean(vec);
  auto lambda = [m](double sum, double val)
                { return sum += std::pow(val - m, 2); };
  double sd = sqrt(1. / vec.size() * std::accumulate(vec.begin(),
                                                     vec.end(),
                                                     0., lambda));
  return {m, sd};
}

double dist_kurtosis(double fit, const std::vector<double>& vec) {
  std::map<unsigned, double> counts{};
  for (const auto& val : vec) {
    if (counts.find(val) == counts.end())
      counts[val] = 1;
    else
      counts[val]++;
  }
  std::vector<double> counts_values{};
  for (const auto& pair : counts)
    counts_values.push_back(pair.second);

  auto stats = mean_std(counts_values);

  double res{};

  if ((vec.size() - 1) * std::pow(stats.second, 4) != 0)
    res = std::pow(counts[fit] - stats.first, 4)
          * vec.size()
          / ((vec.size() - 1) * std::pow(stats.second, 4))
          - 3;

  return res;
}

double thinness(double val, const std::vector<double> &vec) {
  auto std_error = 2 * sqrt(6. / vec.size());
  return (dist_kurtosis(val, vec) + (2 * std_error)) / (4 + std_error);
}

}  // namespace statistics
}  // namespace tools
}  // namespace ctga

//
// statistics.cpp ends here
