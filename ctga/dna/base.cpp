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

namespace ctga {
namespace dna {

Base complement(const Base& b) {
  switch (b) {
    case Base::A: {
      return Base::T;
      break;
    }
    case Base::G: {
      return Base::C;
      break;
    }
    case Base::C: {
      return Base::G;
      break;
    }
    case Base::T: {
      return Base::A;
      break;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Base& b) {
  switch (b) {
    case Base::A: {
      os << 'A';
      break;
    }
    case Base::C: {
      os << 'C';
      break;
    }
    case Base::G: {
      os << 'G';
      break;
    }
    case Base::T: {
      os << 'T';
      break;
    }
  }
  return os;
}


std::istream& operator>>(std::istream& is, Base& b) {
  char c{};
  is >> c;
  switch (c) {
    case 'A': {
      b = Base::A;
      break;
    }
    case 'C': {
      b = Base::C;
      break;
    }
    case 'G': {
      b = Base::G;
      break;
    }
    case 'T': {
      b = Base::T;
      break;
    }
  }
  return is;
}
}  // namespace dna
}  // namespace ctga

//
// base.cpp ends here
