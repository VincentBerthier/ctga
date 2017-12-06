// gutierez.cpp ---
//
// Filename: gutierez.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-05T02:25:40+0000
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


#include "ctga/gfd/gutierez.hpp"

#include "ctga/tools/random_generator.hpp"

namespace ctga {

namespace gfd {

void Gutierez::refresh() {
  auto copy{original_};
  auto gen = tools::RandomGenerator::get();
  gen->permutation(copy.begin(), copy.end(), copy.size());
  super_ = dna::Sequence{copy};

  subs_.clear();

  for (auto i = 0U; i < super_.size(); i += sub_size_)
    subs_.push_back(super_.subsequence(i, i + sub_size_));
}
}  // namespace gfd
}  // namespace ctga

//
// gutierez.cpp ends here
