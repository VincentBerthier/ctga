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

bool Gutierez::is_valid_position(unsigned int pos) const {
  bool res{true};
  unsigned shift{};

  for (auto s : shuffled_) {
    shift += s.size();
    if ((pos < shift) && (pos + sub_size_ > shift))
      res = false;
  }
  return res;
}

void Gutierez::init_population(unsigned int pop_size) {
  auto gen = tools::RandomGenerator::get();
  for (auto i = 0U; i < pop_size; ++i) {
    bool is_ok{false};
    unsigned pos{};
    while (!is_ok) {
      pos = gen->uniform(super_.size());
      auto valid = is_valid_position(pos);
      auto unique = is_unique(pos);
      is_ok = valid && unique;
    }
    taken_.emplace(pos);
    pop_.push_back(Individual{pos, motif_size_});
    std::cout << pop_.back() << std::endl;
  }
}
}  // namespace gfd
}  // namespace ctga

//
// gutierez.cpp ends here
