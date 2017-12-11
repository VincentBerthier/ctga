// individual.cpp ---
//
// Filename: individual.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T09:30:37+0000
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

#include "ctga/gfd/individual.hpp"

#include <iostream>
#include <numeric>
#include <vector>

#include "ctga/dna/sequence.hpp"
#include "ctga/tools/mann_whitney.hpp"

namespace ctga {
namespace gfd {

void Individual::evaluate(const dna::Sequence &sequence, unsigned tolerance) {
  auto motif = sequence.subsequence(position_, position_ + size_);
  auto shuffled = motif.shuffle();

  auto score1 = sequence.count_similar(motif, tolerance);
  auto score2 = sequence.count_similar(motif, tolerance);

  mw_orig_.push_back(score1);
  mw_shuf_.push_back(score2);

  fitness_ += score1 - score2;
}

double Individual::mw_score(bool force) const {
  double res{};
  if (mw_orig_.size() >= 5 || force) {
    if (std::accumulate(mw_orig_.begin(), mw_orig_.end(), 0.0) == 0.) {
      res = 1.;
    } else if (std::accumulate(mw_shuf_.begin(), mw_shuf_.end(), 0.0) == 0.) {
      res = 0.05;
    } else {
      res = tools::statistics::MannWhitney {mw_orig_, mw_shuf_}();
    }
  } else {
    res = -1.;
  }
  return res;
}

std::ostream& operator<<(std::ostream& os, const Individual& i)
{
  os << "Position: " << i.position_ << std::endl
     << "Parent: " << i.parent_ << std::endl
     << "Survived: " << i.survived_ << std::endl
     << "Fitness: " << i.fitness_;
  return os;
}

}  // namespace gfd
}  // namespace ctga


//
// individual.cpp ends here
