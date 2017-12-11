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

#include "ctga/dna/sequence.hpp"

namespace ctga {
namespace gfd {

/**
 *  \brief Individual to use in the genetic algorithm's population
 */
class Individual {
 public:
  /**
   *  \brief Individual constructor
   *
   *  \param pos Starting position of the considered motif on the DNA sequence
   *  \param size Length of the motif represented by the individual
   */
  Individual(unsigned pos, unsigned size) :
      position_{pos},
      size_{size},
      parent_{} {}

  /**
   *  \brief Individual constructor
   *
   *  \param pos Starting position of the considered motif on the DNA sequence
   *  \param size Length of the motif represented by the individual
   *  \param parent Individual who produced this one
   */
  Individual(unsigned pos, unsigned size, unsigned parent) :
      position_{pos},
      size_{size},
      parent_{parent} {}

  bool operator<(const Individual& other) const {
    return fitness_ <= other.fitness_;
  }

  bool operator>(const Individual& other) const {
    return !(operator<(other));
  }

  /**
   *  \brief Get the starting position on the DNA sequence of the motif
   *
   *  \return Starting position on the DNA motif that this individual represents
   */
  inline unsigned position() const { return position_; }

  inline double fitness() const { return fitness_; }

  /**
   *  \brief Formats an Individual for output
   *
   *  \param os Output stream
   *  \param i Individual to format and output
   *  \return Modified stream now containing the individual
   */
  friend std::ostream& operator<<(std::ostream& os, const Individual& i);

  /**
   *  \brief Reset the fitness
   */
  inline void reset() { fitness_ = 0.; }

  /**
   *  \brief Evaluates the individual
   *
   *  \param sequence DNA sequence against which the individual will be scored
   *  \param Tolerance Max allowed difference for retrieved motifs
   */
  void evaluate(const dna::Sequence& sequence, unsigned tolerance);

  /**
   *  \brief Evaluates the individual
   *
   *  \param sequence DNA sequence against which the individual will be scored
   */
  inline void evaluate(const dna::Sequence& sequence) {
    return evaluate(sequence, 2);
  }

  inline void kill() { survived_ = false; }

  /**
   *  \brief Get the Mann-Whitney score of the individual
   *
   *  \param force If true, ignore the size restriction
   *  \return Mann-Whitney score of the individual
   */
  double mw_score(bool force) const;

  inline double mw_score() const { return mw_score(false); }

  inline unsigned alive_for() const { return mw_orig_.size(); }

 private:
  unsigned position_;
  unsigned size_;
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
