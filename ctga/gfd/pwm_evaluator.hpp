// pwm_evaluator.hpp ---
//
// Filename: pwm_evaluator.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-18T04:28:50+0000
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

#ifndef CTGA_GFD_PWM_EVALUATOR_HPP_
#define CTGA_GFD_PWM_EVALUATOR_HPP_

#include <coffee/tools/evaluation.hpp>

#include "ctga/dna/sequence.hpp"
#include "ctga/dna/pwm.hpp"

namespace ctga {
namespace gfd {

class PWM_Evaluator : public Coffee::Tools::Evaluator {
 public:
  explicit PWM_Evaluator(unsigned budget, dna::Sequence seq) :
      Evaluator{budget},
      sequence_{seq},
      rev_comp_{seq.rev_complement()} {}

 protected:
  double work(const Eigen::VectorXd& params) override;

 private:
  dna::Sequence sequence_;
  dna::Sequence rev_comp_;
};

}  // namespace gfd
}  // namespace ctga


#endif  // CTGA_GFD_PWM_EVALUATOR_HPP_


//
// pwm_evaluator.hpp ends here
