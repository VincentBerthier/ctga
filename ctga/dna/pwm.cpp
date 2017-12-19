// pwm.cpp ---
//
// Filename: pwm.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-18T02:33:54+0000
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

#include "ctga/dna/pwm.hpp"

#include <cmath>
#include <map>
#include <vector>

#include "ctga/dna/base.hpp"
#include "ctga/dna/sequence.hpp"
#include "ctga/tools/statistics.hpp"

namespace ctga {
namespace dna {

PWM::PWM(const Eigen::VectorXd& probas,
         const std::map<Base, double>& frequencies) :
    values_{Eigen::MatrixXd(4, probas.rows() / 4)} {
  Eigen::VectorXd f(4);

  for (auto i = 0U; i < probas.size(); i += 4) {
    auto norm_col = tools::statistics::normalise(probas.segment(i, 4), 0.001);
    values_.col(i / 4) = norm_col;
  }
  values_.row(0) = values_.row(0) / frequencies.at(Base::A);
  values_.row(1) = values_.row(1) / frequencies.at(Base::C);
  values_.row(2) = values_.row(2) / frequencies.at(Base::G);
  values_.row(3) = values_.row(3) / frequencies.at(Base::T);
  values_ = values_.unaryExpr([](double x) { return std::log2(x); });
}

double PWM::score(const Sequence &sequence) const {
  double res{};

  for (auto i = 0U; i < sequence.size(); ++i)
    res += score(i, sequence[i]);

  return res;
}

std::vector<Sequence> PWM::find_matches(const Sequence& sequence) const {
  std::vector<Sequence> res{};

  for (auto i = 0U; i < sequence.size() - size(); ++i) {
    auto sub = sequence.subsequence(i, i + size());
    if (score(sub) > 0.) res.push_back(sub);
  }
  return res;
}

Sequence PWM::consensus() const {
  std::vector<Base> res;
  for (auto i = 0U; i < size(); ++i) {
    unsigned r;
    values_.col(i).maxCoeff(&r);
    switch (r) {
      case 0: res.push_back(Base::A); break;
      case 1: res.push_back(Base::C); break;
      case 2: res.push_back(Base::G); break;
      case 3: res.push_back(Base::T); break;
    }
  }
  return Sequence{res};
}

Eigen::MatrixXd PWM::to_proba() const {
  auto vals = values_.unaryExpr([](double d) { return std::pow(2, d); });
  return vals * 0.25;
}

double PWM::score(unsigned col, Base b) const {
  double res{};
  switch (b) {
    case Base::A: res = values_(0, col); break;
    case Base::C: res = values_(1, col); break;
    case Base::G: res = values_(2, col); break;
    case Base::T: res = values_(3, col); break;
    default: throw std::runtime_error{"Can't score this…"};
  }
  return res;
}

}  // namespace dna
}  // namespace ctga


//
// pwm.cpp ends here
