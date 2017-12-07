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

double mean(const std::vector<double>& vec);

double standard_deviation(const std::vector<double>& vec);

std::pair<double, double> mean_std(const std::vector<double>& vec);

double dist_kurtosis(double val, const std::vector<double>& vec);

double thinness(double val, const std::vector<double> &vec);

}  // namespace statistics
}  // namespace tools
}  // namespace ctga

#endif  // CTGA_TOOLS_STATISTICS_HPP_


//
// statistics.hpp ends here
