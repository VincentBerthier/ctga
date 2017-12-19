// base.cpp ---
//
// Filename: base.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T07:07:45+0000
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

#include "ctga/dna/base.hpp"

#include <iostream>
#include <map>
#include <unordered_set>
#include <utility>

namespace ctga {
namespace dna {

std::map<Base, std::unordered_set<Base>> base_matches =
    boost::assign::map_list_of
    (Base::A, std::unordered_set<Base>{Base::A})
    (Base::C, std::unordered_set<Base>{Base::C})
    (Base::G, std::unordered_set<Base>{Base::G})
    (Base::T, std::unordered_set<Base>{Base::T})
    (Base::M, std::unordered_set<Base>{Base::A, Base::C})
    (Base::R, std::unordered_set<Base>{Base::A, Base::G})
    (Base::W, std::unordered_set<Base>{Base::A, Base::T})
    (Base::S, std::unordered_set<Base>{Base::C, Base::G})
    (Base::Y, std::unordered_set<Base>{Base::C, Base::T})
    (Base::K, std::unordered_set<Base>{Base::G, Base::T})
    (Base::V, std::unordered_set<Base>{Base::A, Base::C, Base::G})
    (Base::H, std::unordered_set<Base>{Base::A, Base::C, Base::T})
    (Base::D, std::unordered_set<Base>{Base::A, Base::G, Base::T})
    (Base::B, std::unordered_set<Base>{Base::C, Base::G, Base::T})
    (Base::N, std::unordered_set<Base>{Base::A, Base::C, Base::G, Base::T});

Base complement(const Base& b) {
  Base sel;
  switch (b) {
    case Base::A: sel = Base::T; break;
    case Base::G: sel = Base::C; break;
    case Base::C: sel = Base::G; break;
    case Base::T: sel = Base::A; break;
    case Base::M: sel = Base::K; break;
    case Base::R: sel = Base::Y; break;
    case Base::W: sel = Base::W; break;
    case Base::S: sel = Base::S; break;
    case Base::Y: sel = Base::R; break;
    case Base::K: sel = Base::M; break;
    case Base::V: sel = Base::B; break;
    case Base::H: sel = Base::D; break;
    case Base::D: sel = Base::H; break;
    case Base::B: sel = Base::V; break;
    case Base::N: sel = Base::N; break;
  }
  return sel;
}

std::unordered_set<Base> match(const Base& a, const Base& b) {
  std::unordered_set<Base> res{};
  if (a == b) {
    res = base_matches[a];
  } else {
    for (const auto& elt : base_matches[a]) {
      if (base_matches[b].find(elt) != base_matches[b].end())
        res.emplace(elt);
    }
  }
  return res;
}

std::ostream& operator<<(std::ostream& os, const Base& b) {
  switch (b) {
    case Base::A: os << 'A'; break;
    case Base::C: os << 'C'; break;
    case Base::G: os << 'G'; break;
    case Base::T: os << 'T'; break;
    case Base::M: os << 'M'; break;
    case Base::R: os << 'R'; break;
    case Base::W: os << 'W'; break;
    case Base::S: os << 'S'; break;
    case Base::Y: os << 'Y'; break;
    case Base::K: os << 'K'; break;
    case Base::V: os << 'V'; break;
    case Base::H: os << 'H'; break;
    case Base::D: os << 'D'; break;
    case Base::B: os << 'B'; break;
    case Base::N: os << 'N'; break;
  }
  return os;
}


std::istream& operator>>(std::istream& is, Base& b) {
  char c{};
  is >> c;
  switch (c) {
    case 'A': b = Base::A; break;
    case 'C': b = Base::C; break;
    case 'G': b = Base::G; break;
    case 'T': b = Base::T; break;
    case 'M': b = Base::M; break;
    case 'R': b = Base::R; break;
    case 'W': b = Base::W; break;
    case 'S': b = Base::S; break;
    case 'Y': b = Base::Y; break;
    case 'K': b = Base::K; break;
    case 'V': b = Base::V; break;
    case 'H': b = Base::H; break;
    case 'D': b = Base::D; break;
    case 'B': b = Base::B; break;
    case 'N': b = Base::N; break;
  }
  return is;
}
}  // namespace dna
}  // namespace ctga

//
// base.cpp ends here
