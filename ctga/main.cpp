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

#include "ctga/gfd/gutierez.hpp"
#include "ctga/tools/io.hpp"
#include "ctga/tools/random_generator.hpp"
#include "ctga/tools/mann_whitney.hpp"
#include "ctga/tools/statistics.hpp"

using std::cout;
using std::endl;
using std::vector;
using ctga::dna::Sequence;

int main(int, char**) {
  // initialize random generation
  ctga::tools::RandomGenerator::get();

  auto data = ctga::tools::io::read_file("../data/example.fasta");
  ctga::dna::Sequence full{data};

  cout << "Sequence read: " << full << endl;
  vector<double> vec{full};
  cout << vec.size() << endl;
  vector<double> test{1.22, 0.122, 1.99, 2, 3.2, 3.5, 4, 1.1, 1, 2.4};
  cout << "Test conversion: " << ctga::dna::Sequence{test} << endl;

  ctga::gfd::Gutierez gut{300, data};
  gut.refresh();
  gut.init_population(10);

  vector<double> test1{3, 4, 2, 6, 2, 5};
  vector<double> test2{9, 7, 5, 10, 6, 8};

  ctga::tools::statistics::MannWhitney mw{test1, test2};

  cout << "P-value: " << mw() << endl;

  ctga::dna::Sequence
      seq{"GTCTTAAATGTGACCGCGTCTTCCCCATTGCTCGAGCTGGAGATGCTTTTCCTCAGTCCCTCACTGTGGTGGTAGGAGGGGCTGTTGTGCCACCATCCACAGCTATTCTTCCATGTGGTTAGAGAAGCTGAGAAATAACGAGAGTTTCCGTTCCATGGCAAGGAATGGGTTTGGAGTGTTTATTCACAGAACGGTTCTCATGAGATGGGACCAGCTAAGAATAGCCCTGGGTTGACACTGTCCTACCTCCTCCTGCTCATAAGAGAAACTACTTCCCCACAAGAAGAAAGAATAGGTCACGAGTTGAGAGCTGAGACTTATATCTCAGAGATGCTATTCTTAGATATCCTGGGCCCCTGTGGTCACTGTGGACCCTGGGTTGTGTAATATCCATCATGACACCATTGCTGTGCTTAAAATTTTCCCTCCTCAGCCCCGGATTCCATTTCCTCATCTGCTAGGGCTACCTATAAGAGAAGGGGCATATGGCTTCAGACACC"};
  ctga::dna::Sequence motif{"AGTCCCTC"};
  std::vector<unsigned> pos{};

  auto p = seq.find_similar(motif, 2);
  pos.insert(pos.end(), p.begin(), p.end());
  p = seq.find_similar(motif.rev_complement(), 2);
  pos.insert(pos.end(), p.begin(), p.end());
  sort(pos.begin(), pos.end());

  cout << "Looking for:\n" << motif << "\n" << motif.rev_complement() << endl;
  cout << "Similar found = " << seq.count_similar(motif, 2) << endl;
  cout << "Pos found: " << pos << endl;

  for (const auto i : pos)
    cout << "Motif: " << seq.subsequence(i, i + motif.size()) << endl;

  std::vector<Sequence> test_consensus{Sequence{"AACCTGGT"},
        Sequence{"AACCTGAA"},
            Sequence{"AACCGGTT"},
                Sequence{"AACCTCTT"},
                    Sequence{"AACCAGAT"},
                        Sequence{"CACCTGGT"},
                            Sequence{"CCCCGGTT"},
                                Sequence{"CCCCTGCT"},
                                    Sequence{"CCCGTGTT"},
                                        Sequence{"CCCAAGTT"},
                                            Sequence{"GCTGGGTT"},
                                                Sequence{"GCTGTGTA"},
                                                    Sequence{"GGTGTGTC"},
                                                        Sequence{"GGTGTGTT"},
                                                            Sequence{"GGTGTGCC"},
                                                                Sequence{"TGTGTTCT"},
                                                                    Sequence{"TGTCTGTT"},
                                                                        Sequence{"TGTGTCTG"},
                                                                            Sequence{"TTTGGCTT"},
                                                                                Sequence{"TTTGTGGT"}};

  cout << "Consensus: " <<   Sequence::find_consensus(test_consensus) << endl;



  return 0;
}

//
// main.cpp ends here
