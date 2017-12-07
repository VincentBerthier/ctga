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
#include <vector>

namespace ctga {
namespace gfd {

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
