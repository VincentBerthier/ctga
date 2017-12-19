// pwm.hpp ---
//
// Filename: pwm.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-18T02:16:43+0000
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

#ifndef CTGA_DNA_PWM_HPP_
#define CTGA_DNA_PWM_HPP_


#include <eigen3/Eigen/Core>
#include <map>
#include <vector>

#include "ctga/dna/base.hpp"
#include "ctga/dna/sequence.hpp"

namespace ctga {
namespace dna {

class PWM {
 public:
  explicit PWM(const Eigen::VectorXd& probas)  :
      PWM{probas, std::map<Base, double>{
      {Base::A, 0.25},
      {Base::C, 0.25},
      {Base::G, 0.25},
      {Base::T, 0.25}}} {}
  PWM(const Eigen::VectorXd& probas,
      const std::map<Base, double>& frequencies);

  double score(const Sequence& sequence) const;

  inline double norm() const { return values_.norm(); }

  /**
   *  \brief Find subsequences matching the PWM
   *
   *  \param pwm Position Weights Matrix
   *  \return List of sequences matcing the PWM
   */
  std::vector<Sequence> find_matches(const Sequence& sequence) const;

  Eigen::MatrixXd to_proba() const;

  Sequence consensus() const;

  inline unsigned size() const { return values_.cols(); }

  friend std::ostream& operator<<(std::ostream& os, const PWM& c) {
    os << c.values_;
    return os;
  }

 private:
  Eigen::MatrixXd values_;
  double score(unsigned col, Base b) const;
};



}  // namespace dna
}  // namespace ctga

#endif  // CTGA_DNA_PWM_HPP_

//
// pwm.hpp ends here
