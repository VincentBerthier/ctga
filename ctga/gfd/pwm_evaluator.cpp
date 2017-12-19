// pwm_evaluator.cpp ---
//
// Filename: pwm_evaluator.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-18T05:18:55+0000
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

#include "ctga/gfd/pwm_evaluator.hpp"

#include <iostream>

#include "ctga/dna/pwm.hpp"
#include "ctga/tools/random_generator.hpp"

namespace ctga {
namespace gfd {

double PWM_Evaluator::work(const Eigen::VectorXd& params) {
  double res{};
  double n{};

  auto pwm = dna::PWM{params};
  auto consensus = pwm.consensus();

  auto similar = sequence_.count_similar(consensus, 2);

  for (auto i = 0U; i < sequence_.size() - pwm.size(); ++i) {
    auto score = pwm.score(sequence_.subsequence(i, i + pwm.size()));
    if (score > 0.) {
      res += score;
      n += 1.;
    }
  }

  // Looking in the reverse complement
  for (auto i = 0U; i < sequence_.size() - pwm.size(); ++i) {
    auto score = pwm.score(rev_comp_.subsequence(i, i + pwm.size()));
    if (score > 0.) {
      res += score;
      n += 1.;
    }
  }

  // std::cout << "Found " << n << " positive scores\n";

  return res / (n + 1) * (similar - 1.);
}

}  // namespace gfd
}  // namespace ctga


//
// pwm_evaluator.cpp ends here
