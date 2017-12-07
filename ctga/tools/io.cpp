// io.cpp ---
//
// Filename: io.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-05T07:24:17+0000
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


#include "ctga/tools/io.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ctga/dna/sequence.hpp"

namespace ctga {
namespace tools {
namespace io {


using std::string;
using std::vector;

std::vector<dna::Sequence> read_file(std::string path) {
  std::vector<dna::Sequence> res{};
  string data{};
  std::ifstream input{path};
  if (input.is_open()) {
    while (getline(input, data)) {
      if (data[0] != '>') res.push_back(dna::Sequence{data});
    }
  }
  input.close();
  return res;
}

}  // namespace io
}  // namespace tools
}  // namespace ctga

//
// parser.cpp ends here
