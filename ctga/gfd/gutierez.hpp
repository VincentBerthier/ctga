// gutierez.hpp ---
//
// Filename: gutierez.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-05T02:22:05+0000
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


#ifndef CTGA_GFD_GUTIEREZ_HPP_
#define CTGA_GFD_GUTIEREZ_HPP_

#include <vector>

#include "ctga/dna/sequence.hpp"

namespace ctga {
namespace gfd {


class Gutierez {
 private:
  unsigned sub_size_;
  std::vector<dna::Sequence> original_;
  dna::Sequence super_;
  std::vector<dna::Sequence> subs_;

 public:
  Gutierez(unsigned size, const std::vector<dna::Sequence>& seqs) :
      sub_size_{size},
      original_{seqs},
      super_{""},
      subs_{}
  {}

  std::vector<dna::Sequence> get_subs() const { return subs_; }

  void refresh();
};


}  // namespace gfd
}  // namespace ctga

#endif  // CTGA_GFD_GUTIEREZ_HPP_

//
// gutierez.hpp ends here
