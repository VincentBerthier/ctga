// sequence.hpp ---
//
// Filename: sequence.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T06:52:06+0000
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


#ifndef CTGA_DNA_SEQUENCE_HPP_
#define CTGA_DNA_SEQUENCE_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "ctga/dna/base.hpp"

namespace ctga {
namespace dna {


/** \brief Class defining a strand of DNA */
class Sequence {
 private:
  std::vector<Base> bases_; /*!< list of bases in the sequence */
 public:
  /**
   *  \brief Sequence constructor
   *
   *  \param bases Vector of bases in the sequence
   */
  explicit Sequence(const std::vector<Base>& bases) : bases_{bases} {}
  /**
   *  \brief Sequence constructor
   *
   *  Builds a sequence of DNA from a string
   *
   *  \param str String containing the definition of the strand of DNA
   */
  explicit Sequence(std::string str);
  /**
   *  \brief Sequence constructor
   *
   *  Builds a sequence of DNA from a vector of doubles.
   *  The doubles are first raised to the first integer of same or higher
   *  value (using the ceil function)
   *  then mapped to a base: 1 -> A, 2 -> C, 3 -> G, 4 -> T.
   *  If the doubles are inferior to 0 or higher than 4, the conversion fails.
   *
   *  \param vec Vector of double matching DNA bases.
   */
  explicit Sequence(std::vector<double> vec);

  /**
   *  \brief Sequence constructor
   *
   *  Builds a new sequence from a vector of sequences
   *
   *  \param vec Vector of sequences
   */
  explicit Sequence(std::vector<Sequence> vec);

  /**
   *  \brief Get the number of bases in the sequence
   *
   *  \return return Number of bases in the sequence
   */
  inline unsigned size() const { return bases_.size(); }

  /**
   *  \brief Appends another sequence to the current one
   *
   *  \param seq Sequence to append
   */
  void append(Sequence seq);

  /**
   *  \brief Get a subsequence of the current sequence
   *
   *  \param start Index of the first base to retrieve (included)
   *  \param stop Index of the last base to retrieve (excluded)
   *  \return return type
   */
  Sequence subsequence(unsigned start, unsigned stop);

  /**
   *  \brief Convert the DNA strand to a string representation
   *
   *  \return String representation of the DNA sequence
   */
  std::string to_string() const;

  /**
   *  \brief Convert the DNA sequence to a vector of doubles

   *  \return Vector of doubles representation
   */
  operator std::vector<double>() const;
  /** \brief Write a sequence into a stream */
  friend std::ostream& operator<<(std::ostream& os, const Sequence& s);
  /** \brief Read a sequence from a stream */
  friend std::istream& operator>>(std::istream& is, Sequence& s);
};
}  // namespace dna
}  // namespace ctga


#endif  // CTGA_DNA_SEQUENCE_HPP_

//
// sequence.hpp ends here
