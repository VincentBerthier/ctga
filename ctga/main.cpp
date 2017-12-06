// main.cpp ---
//
// Filename: main.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-05T07:15:32+0000
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


#include <algorithm>
#include <iostream>
#include <vector>

#include "gfd/gutierez.hpp"
#include "tools/parser.hpp"
#include "tools/random_generator.hpp"

using std::cout;
using std::endl;
using std::vector;

int main(int, char**) {
  // initialize random generation
  ctga::tools::RandomGenerator::get();

  auto data = ctga::tools::parser::read_file("example.fasta");
  ctga::dna::Sequence full{data};

  cout << "Sequence read: " << full << endl;
  vector<double> vec{full};
  cout << vec.size() << endl;
  vector<double> test{1.22, 0.122, 1.99, 2, 3.2, 3.5, 4, 1.1, 1, 2.4};
  cout << "Test conversion: " << ctga::dna::Sequence{test} << endl;

  ctga::gfd::Gutierez gut{300, data};
  gut.refresh();

  ctga::dna::Sequence random{gut.get_subs()};

  cout << "Random permutation: " << random << endl;

  return 0;
}

//
// main.cpp ends here
