// gutierez.cpp ---
//
// Filename: gutierez.cpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-05T02:25:40+0000
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


#include "ctga/gfd/gutierez.hpp"

#include <algorithm>
#include <vector>

#include "ctga/tools/random_generator.hpp"
#include "ctga/tools/statistics.hpp"

#define MAX_MW 0.1
#define MUTATION_RATE 0.1
#define MIN_FITNESS 0.1

namespace ctga {

namespace gfd {

void Gutierez::operator()(unsigned ngens, unsigned pop_size) {
  // init GA
  unsigned generation{};

  // init sequences
  refresh();

  // init population and evaluate it
  init_population(pop_size);
  for (auto& indiv : pop_)
    indiv.evaluate(subs_[generation % subs_.size()]);

  // run generations
  while (generation < ngens) {
    generation++;

    std::sort(pop_.begin(), pop_.end());

    decimate();

    create_offsprings(pop_size, MUTATION_RATE);

    // Evaluate the population
    for (auto& indiv : pop_) {
      if (generation % subs_.size() == 0) indiv.reset();
      indiv.evaluate(subs_[generation % subs_.size()]);
    }
    // Refresh the subsequences
    if (generation % subs_.size() == 0) refresh();
  }  // end while

  // select best solutions

  // save to file or something
}

void Gutierez::refresh() {
  auto copy{original_};
  auto gen = tools::RandomGenerator::get();
  gen->permutation(copy.begin(), copy.end(), copy.size());
  super_ = dna::Sequence{copy};

  subs_.clear();

  for (auto i = 0U; i < super_.size(); i += sub_size_)
    subs_.push_back(super_.subsequence(i, i + sub_size_));
}

void Gutierez::decimate() {
  // Get the mean and std of the population's fitness
  std::vector<double> fits{};


  for (const auto& indiv : pop_)
    fits.push_back(indiv.fitness());

  auto stats = tools::statistics::mean_std(fits);

  for (auto& indiv : pop_) {
    if (indiv.fitness() - stats.first / stats.second < MIN_FITNESS)
      indiv.kill();
    auto mw = indiv.mw_score();
    if (mw >= 0.) {
      if (mw > MAX_MW) {
        indiv.kill();
      } else if ((indiv.alive_for() == 9)
                 && (mw <= MAX_MW / 2.)
                 && tools::statistics::thinness(indiv.fitness(), fits)) {
        std::vector<dna::Sequence> seqs{};
        auto motif = super_.subsequence(indiv.position(),
                                        indiv.position() + motif_size_);

        for (const auto& seq : original_) {
          auto pos = seq.find_similar(motif, 2);
          for (auto p : pos) seqs.push_back(seq.subsequence(p, motif_size_));
          pos = seq.find_similar(motif.rev_complement(), 2);
          for (auto p : pos) seqs.push_back(seq.subsequence(p, motif_size_));
        }

        std::cout << "Candidate found: at " << indiv.position()
                  << " for " << dna::Sequence::find_consensus(seqs)
                  << " with proba " << mw / (motif_size_ / 10) << std::endl;
      }
    }
  }
}

void Gutierez::create_offsprings(unsigned pop_size, double mutation_rate) {
  std::vector<Individual> offsprings{};
  auto gen = tools::RandomGenerator::get();

  for (auto i = 0U; i < pop_size; ++i) {
    auto id1 = pop_[gen->uniform(pop_.size())];
    auto id2 = pop_[gen->uniform(pop_.size())];

    // Get the motifs represented by the parents
    auto parent1 = super_.subsequence(id1.position(),
                                      id1.position() + motif_size_);
    auto parent2 = super_.subsequence(id2.position(),
                                      id2.position() + motif_size_);

    // Select which parts of the parents are transmitted
    auto point = gen->uniform(motif_size_ - 1) + 1;

    // Create the child
    dna::Sequence child{""};
    child.append(parent1.subsequence(0, point));
    child.append(parent2.subsequence(point, motif_size_));

    // We now try to match the child to the closest sequence
    // actully found in the sequence
    int pos{-1};
    unsigned errors{};
    while (pos == -1) {
      // Finding a list of possible matches
      auto possibles = super_.find_similar(child, errors);
      // Selecting a match at random until a free one is found
      if (possibles.size() > 0) {
        while (pos == -1 && possibles.size() > 0) {
          auto choice = gen->uniform(possibles.size());
          if (is_unique(choice) && is_valid_position(choice))
            pos = choice;
          else  // Another individual is there or pos not valid
            possibles.erase(possibles.begin() + choice);
        }
      }
      errors++;
    }
    int final_position{pos};

    // Mutation of the child
    if (gen->uniform() < mutation_rate) {
      final_position = -1;
      while (final_position == -1) {
        auto mut = gen->uniform(motif_size_ - 1) + 1;
        auto test_position = (pos + mut) % super_.size();
        if (is_unique(test_position)
            && is_valid_position(test_position))
          final_position = test_position;
      }
    }
    // We now have a good position, create the offspring
    offsprings.push_back(Individual{static_cast<unsigned>(final_position),
            motif_size_});
  }

  pop_.insert(pop_.end(), offsprings.begin(), offsprings.end());
}

bool Gutierez::is_valid_position(unsigned int pos) const {
  bool res{true};
  unsigned shift{};

  for (auto s : shuffled_) {
    shift += s.size();
    if ((pos < shift) && (pos + sub_size_ > shift))
      res = false;
  }
  return res;
}

void Gutierez::init_population(unsigned int pop_size) {
  auto gen = tools::RandomGenerator::get();
  for (auto i = 0U; i < pop_size; ++i) {
    bool is_ok{false};
    unsigned pos{};
    while (!is_ok) {
      pos = gen->uniform(super_.size());
      auto valid = is_valid_position(pos);
      auto unique = is_unique(pos);
      is_ok = valid && unique;
    }
    taken_.emplace(pos);
    pop_.push_back(Individual{pos, motif_size_});
    std::cout << pop_.back() << std::endl;
  }
}
}  // namespace gfd
}  // namespace ctga

//
// gutierez.cpp ends here
