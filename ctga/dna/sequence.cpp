// sequence.cpp ---
//
// Filename: sequence.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T07:09:54+0000
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

#include "ctga/dna/sequence.hpp"

#include <assert.h>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "ctga/tools/random_generator.hpp"

namespace ctga {
namespace dna {

using std::string;
using std::vector;

Sequence::Sequence(const std::string& str) : bases_{} {
  std::stringstream ss{str};
  bases_ = vector<Base>((std::istream_iterator<Base>(ss)),
                        std::istream_iterator<Base>());
}

Sequence::Sequence(const std::vector<double>& vec): bases_{} {
  for (const auto& d : vec) {
    assert((d <= 4) && (d >= 0));
    switch (static_cast<unsigned>(ceil(d))) {
      case 1U: {
        bases_.push_back(Base::A);
        break;
      }
      case 2U: {
        bases_.push_back(Base::C);
        break;
      }
      case 3U: {
        bases_.push_back(Base::G);
        break;
      }
      case 4U: {
        bases_.push_back(Base::T);
        break;
      }
    }
  }
}

Sequence::Sequence(const std::vector<Sequence>& vec) : bases_{} {
  for (const auto& seq : vec) append(seq);
}

Sequence Sequence::subsequence(unsigned start, unsigned stop) const {
  assert(start >= 0);
  assert(start < stop);

  if (stop > bases_.size())
    stop = bases_.size();

  std::vector<Base> bases{};
  bases.insert(bases.end(), bases_.begin() + start, bases_.begin() + stop);
  // std::copy(bases_.begin() + start, bases_.begin() + stop, bases.begin());

  return Sequence{bases};
}


void Sequence::append(const Sequence& seq) {
  bases_.insert(bases_.end(), seq.bases_.begin(), seq.bases_.end());
}

std::string Sequence::to_string() const {
  std::stringstream ss{};
  ss << *this;
  return ss.str();
}

Sequence Sequence::complement() const {
  std::vector<Base> comp{};
  for (const auto& b : bases_)
    comp.push_back(dna::complement(b));
  return Sequence{comp};
}

Sequence Sequence::reverse() const {
  std::vector<Base> rev{};
  for (auto rit = bases_.rbegin(); rit != bases_.rend(); rit++)
    rev.push_back(*rit);
  return Sequence{rev};
}

Sequence Sequence::rev_complement() const {
  return complement().reverse();
}

Sequence Sequence::shuffle() const {
  auto shuffled = bases_;
  auto gen = tools::RandomGenerator::get();

  gen->permutation(shuffled.begin(), shuffled.end(), shuffled.size());

  return Sequence{shuffled};
}

bool Sequence::is_similar(const Sequence& motif, unsigned tolerance) {
  unsigned i{}, diff{};
  while (diff <= tolerance && i < motif.size()) {
    if (bases_[i] != motif.bases_[i]) diff++;
    i++;
  }
  return diff <= tolerance;
}

std::vector<unsigned> Sequence::find_similar(const Sequence& motif,
                                             unsigned tolerance,
                                             unsigned width) const {
  std::vector<unsigned> res{};
  for (auto i = 0U; i < bases_.size() - width; ++i) {
    if (subsequence(i, i + width).is_similar(motif, tolerance))
      res.push_back(i);
  }
  return res;
}

unsigned Sequence::count_similar(const Sequence& motif,
                                 unsigned tolerance,
                                 unsigned width) const {
  return find_similar(motif, tolerance, width).size()
      + find_similar(motif.rev_complement(), tolerance, width).size();
}

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p)
{
  return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src)
{
  std::multimap<B, A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                 flip_pair<A, B>);
  return dst;
}

Sequence Sequence::find_consensus(const Sequence& motif,
                                  unsigned tolerance) const {
  // Find similar motifs
  auto sim1 = find_similar(motif, tolerance);
  auto sim2 = find_similar(motif.rev_complement(), tolerance);

  std::vector<Sequence> seqs{};

  // Retrieve all the sequences
  for (auto i : sim1)
    seqs.push_back(subsequence(i, i + motif.size()));
  for (auto i : sim2)
    seqs.push_back(subsequence(i, i + motif.size()));

  std::vector<Base> consensus{};

  // At each position, find the most present bases
  // What about ties??

  for (auto i = 0U; i < motif.size(); ++i) {
    std::map<Base, unsigned> counts{};
    for (const auto& s : seqs) {
      auto elt = counts.find(s[i]);
      if (elt == counts.end())
        counts.emplace(s[i], 0);
      else
        elt->second++;
    }
    // Reverse map, it is now sorted by value.
    // Last one is the most frequent bases
    auto sorted = flip_map(counts);

    consensus.push_back(sorted.rbegin()->second);
  }
  return Sequence{consensus};
}


Sequence::operator std::vector<double>() const {
  vector<double> res{};
  for (Base b : bases_) {
    switch (b) {
      case Base::A: {
        res.push_back(1.);
        break;
      }
      case Base::C: {
        res.push_back(2.);
        break;
      }
      case Base::G: {
        res.push_back(3.);
        break;
      }
      case Base::T: {
        res.push_back(4.);
        break;
      }
      default:
        break;
    }
  }
  return res;
}


std::istream& operator>>(std::istream& is, Sequence& s) {
  s.bases_ = vector<Base>{};
  Base b{};
  while (!(is.eof() || is.peek() == std::char_traits<char>::eof())) {
    is >> b;
    s.bases_.push_back(b);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Sequence& s) {
  std::copy(s.bases_.begin(),
            s.bases_.end(),
            std::ostream_iterator<Base>{os, ""});
  return os;
}


}  // namespace dna
}  // namespace ctga

//
// sequence.cpp ends here
