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


#include <coffee/portfolios/all_portfolios.hpp>
#include <coffee/optimisers/all_optimisers.hpp>
#include <coffee/optimisers/utils/progressive_widening.hpp>
#include <coffee/tools/logs.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

#include "ctga/gfd/gutierez.hpp"
#include "ctga/gfd/pwm_evaluator.hpp"
#include "ctga/tools/io.hpp"
#include "ctga/tools/random_generator.hpp"
#include "ctga/tools/mann_whitney.hpp"
#include "ctga/tools/statistics.hpp"

using std::cout;
using std::endl;
using std::vector;
using ctga::dna::Sequence;

int main(int, char**) {

  Coffee::Tools::configure_logs(11, "", Coffee::Tools::Logs::Source::all);

  // initialize random generation
  ctga::tools::RandomGenerator::get();

  auto data = ctga::tools::io::read_file("../data/dm02r.fasta");
  ctga::dna::Sequence full{data};

  cout << "Sequence read: " << full << endl;

  unsigned motif_width{9};
  auto nParams = motif_width * 4;

  auto evaluator = ctga::gfd::PWM_Evaluator{50 * 1000, full};
  unsigned portfolioType{};


  std::vector<unsigned> optimisers{8};
  auto reevalFormula = GiNaC::numeric{1};
  // Optimisers params
  auto params = Coffee::Optimisers::get_default_parameters(optimisers, nParams);
  params[0]->bounds = Coffee::Optimisers::Bounds{0., 1.};
  std::vector<double> mean{0.5};
  params[0]->meanInit = mean;
  params[0]->sigmaInit = std::vector<double>{1. / 6};
  params[0]->minimise = false;
  params[0]->mu = 60;
  auto portfolio = Coffee::Portfolios::get_portfolio(
      portfolioType, &evaluator, optimisers, params);
  portfolio->set_restart(false);

  // Running decision making
  (*portfolio)(5 * 60);

  // Get selected parameters
  Eigen::VectorXd best{portfolio->best_params()};
  ctga::dna::PWM best_pwm{best};

  auto list = full.count_similar(best_pwm.consensus(), 2);

  for (const auto& s : full.find_similar(best_pwm.consensus(), 2))
    cout << "At " << s << ":\t" << full.subsequence(s, s + motif_width) << endl;
  for (const auto& s : full.rev_complement().find_similar(best_pwm.consensus(), 2))
    cout << "At " << full.size() - s << "\t: "
         << full.rev_complement().subsequence(s, s + motif_width) << endl;

  cout << "Matched " << list << endl;

  cout << "Optimization result:\n" << best_pwm.to_proba() << endl
       << "Consensus is: " << best_pwm.consensus()
       << "\nReverse is  : " << best_pwm.consensus().rev_complement() << endl;

  return 0;
}

//
// main.cpp ends here
