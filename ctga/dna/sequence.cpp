// sequence.cpp ---
//
// Filename: sequence.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T07:09:54+0000
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

#include "ctga/dna/sequence.hpp"

#include <assert.h>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

namespace ctga {
namespace dna {

using std::string;
using std::vector;

Sequence::Sequence(std::string str) : bases_{} {
  std::stringstream ss{str};
  bases_ = vector<Base>((std::istream_iterator<Base>(ss)),
                        std::istream_iterator<Base>());
}

Sequence::Sequence(std::vector<double> vec): bases_{} {
  for (auto d : vec) {
    assert((d <= 4) && (d >= 0));
    switch (static_cast<unsigned>(ceil(d))) {
      case 1U: {
        bases_.push_back(Base::A);
        break;
      }
      case 2U: {
        bases_.push_back(Base::C);
        break;
      }
      case 3U: {
        bases_.push_back(Base::G);
        break;
      }
      case 4U: {
        bases_.push_back(Base::T);
        break;
      }
    }
  }
}

Sequence::Sequence(std::vector<Sequence> vec) : bases_{} {
  for (auto seq : vec) append(seq);
}

Sequence Sequence::subsequence(unsigned start, unsigned stop) {
  assert(start >= 0);
  assert(start < stop);

  if (stop > bases_.size())
    stop = bases_.size();

  std::vector<Base> bases(stop - start);
  std::copy(bases_.begin() + start, bases_.begin() + stop, bases.begin());

  return Sequence{bases};
}


void Sequence::append(Sequence seq) {
  bases_.insert(bases_.end(), seq.bases_.begin(), seq.bases_.end());
}

std::string Sequence::to_string() const {
  std::stringstream ss{};
  ss << *this;
  return ss.str();
}

Sequence::operator std::vector<double>() const {
  vector<double> res{};
  for (Base b : bases_) {
    switch (b) {
      case Base::A: {
        res.push_back(1.);
        break;
      }
      case Base::C: {
        res.push_back(2.);
        break;
      }
      case Base::G: {
        res.push_back(3.);
        break;
      }
      case Base::T: {
        res.push_back(4.);
        break;
      }
      default:
        break;
    }
  }
  return res;
}


std::istream& operator>>(std::istream& is, Sequence& s) {
  s.bases_ = vector<Base>{};
  Base b{};
  while (!(is.eof() || is.peek() == std::char_traits<char>::eof())) {
    is >> b;
    s.bases_.push_back(b);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Sequence& s) {
  std::copy(s.bases_.begin(),
            s.bases_.end(),
            std::ostream_iterator<Base>{os, ""});
  return os;
}


}  // namespace dna
}  // namespace ctga

//
// sequence.cpp ends here
