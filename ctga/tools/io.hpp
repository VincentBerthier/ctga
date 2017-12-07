// io.hpp ---
//
// Filename: io.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-05T07:25:09+0000
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


#ifndef CTGA_TOOLS_IO_HPP_
#define CTGA_TOOLS_IO_HPP_

#include <algorithm>
#include <string>
#include <vector>

#include "ctga/dna/sequence.hpp"

/** \namespace gfd::tools::parser
 * Handles all operation related to files reading
 */

/**
 *  \brief Print a vector
 *
 *  \param vec Vector to print
 *  \return Modified stream
 */

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  os << "[";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>{os, ", "});
  os << "]";
  return os;
}

namespace ctga {
namespace tools {
namespace io {

/**
 *  \brief Reads a fasta formated file and gets the sequences it contains.
 *
 *  Reads a file under the fasta format, collects the sequences it contains.
 *
 *  \param path Path to the file to read
 *  \return Vector of DNA sequences
 */
std::vector<dna::Sequence> read_file(std::string path);


}  // namespace io
}  // namespace tools
}  // namespace ctga
#endif  // CTGA_TOOLS_IO_HPP__

//
// parser.hpp ends here
