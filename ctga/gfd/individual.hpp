// individual.hpp ---
//
// Filename: individual.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T08:44:10+0000
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

#ifndef CTGA_GFD_INDIVIDUAL_HPP_
#define CTGA_GFD_INDIVIDUAL_HPP_

#include <iostream>
#include <vector>

namespace ctga {
namespace gfd {

class Individual {
 public:
  explicit Individual(unsigned pos, unsigned parent = 0) :
      position_{pos},
      parent_{parent} {}
  inline unsigned position() const { return position_; }

  friend std::ostream& operator<<(std::ostream& os, const Individual& i);

 private:
  unsigned position_;
  unsigned parent_;
  bool survived_{true};
  double fitness_{};
  std::vector<double> mw_orig_{};
  std::vector<double> mw_shuf_{};
};


}  // namespace gfd
}  // namespace ctga

#endif  // CTGA_GFD_INDIVIDUAL_HPP_

//
// individual.hpp ends here
