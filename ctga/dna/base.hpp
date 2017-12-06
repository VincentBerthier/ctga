// base.hpp ---
//
// Filename: base.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T06:48:23+0000
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


#ifndef CTGA_DNA_BASE_HPP_
#define CTGA_DNA_BASE_HPP_

#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>

/** \namespace gfd
 * Main namespace of the application
 */

/** \namespace gfd::tools::dna
 * Contains all the tools relating to the DNA itself
 */

namespace ctga {
namespace dna {
/** \brief Enumeration of the different type of bases found in DNA */
enum class Base {
  A = 1, /*!< Adenine */
  C = 2, /*!< Cytosine */
  G = 3, /*!< Guanine */
  T = 4 /*!< Thymine */
};

/** \brief Write a Base into a stream */
std::ostream& operator<<(std::ostream& os, const Base& b);
/** \brief Read a base from a stream */
std::istream& operator>>(std::istream& is, Base& b);

}  // namespace dna
}  // namespace ctga


#endif  // CTGA_DNA_BASE_HPP_

//
// base.hpp ends here
