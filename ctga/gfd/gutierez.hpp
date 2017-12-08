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

#include <unordered_set>
#include <vector>

#include "ctga/dna/sequence.hpp"
#include "ctga/gfd/individual.hpp"

namespace ctga {
namespace gfd {


class Gutierez {
 public:
  /**
   *  \brief Initialises a Genetic Algorithm for motif finding

   *  \param size Size of the submotifs
   *  \param seqs Sequences of DNA to analyse
   */
  Gutierez(unsigned size, const std::vector<dna::Sequence>& seqs) :
      sub_size_{size},
      original_{seqs},
      shuffled_{},
      super_{""},
      subs_{}
  {}

  /**
   *  \brief Reinitialises the random sequences
   */
  void refresh();

  /**
   *  \brief Check that the current position is valid

   *  \param position
   *  \return True if the position is valid, False otherwise
   */
  bool is_valid_position(unsigned pos) const;

  /**
   *  \brief Check that the current position is unique
   *
   *  \param pos
   *  \return True if the position is unused, False otherwise
   */
  inline bool is_unique(unsigned pos) const {
    return taken_.find(pos) == taken_.end();
  }

  /**
   *  \brief Initialises a population
   *
   *  \param pop_size Number of individuals in the population
   */
  void init_population(unsigned pop_size);

 private:
  unsigned sub_size_;
  unsigned motif_size_;
  std::vector<dna::Sequence> original_;
  std::vector<dna::Sequence> shuffled_;
  dna::Sequence super_;
  std::vector<dna::Sequence> subs_;

  std::vector<Individual> pop_{};
  std::unordered_set<unsigned> taken_{};
};


}  // namespace gfd
}  // namespace ctga

#endif  // CTGA_GFD_GUTIEREZ_HPP_

//
// gutierez.hpp ends here
