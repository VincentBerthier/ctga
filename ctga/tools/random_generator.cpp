// random_generator.cpp ---
//
// Copyright (c) 2015 Université Paris-Sud. All rights reserved.
//
// Filename: random_generator.cpp
// Description:
// Author: Vincent Berthier
// Email: vincent.berthier@inria.fr
//
// Created: 2015-11-18T11:10:15+0000
// Version:
// Last-Updated: 2015-12-10T15:19:45+0000
//           By: Vincent Berthier
//     Update #: 65
//

// Change Log:
//
//
//
// License: GNU General Public License v3 (GPLv3):
// COFFEE is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// COFFEE is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with COFFEE.  If not, see <http://www.gnu.org/licenses/>.
//

// Code:

#include "ctga/tools/random_generator.hpp"

#include <boost/bind.hpp>
#include <boost/random.hpp>

#include <chrono>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

// #include "tools/logs.hpp"
// #include "tools/utils.hpp"

namespace ctga {
namespace tools {

using std::string;
using Eigen::VectorXd;

RandomGenerator *RandomGenerator::_instance = nullptr;

RandomGenerator *RandomGenerator::get(unsigned seed, bool qr, string path,
                                      string normal_path, string uniform_path) {
  if (_instance == nullptr)
    _instance = new RandomGenerator(seed, qr, path, normal_path, uniform_path);
  return _instance;
}

RandomGenerator *RandomGenerator::get(unsigned seed, bool qr, string path) {
  if (_instance == nullptr)
    _instance =
        new RandomGenerator(seed, qr, path, "qr_normal.dat", "qr_uniform.dat");
  return _instance;
}

RandomGenerator *RandomGenerator::get(unsigned seed) {

  if (_instance == nullptr)
    _instance = get(seed, false, "./", "qr_normal.dat", "qr_uniform.dat");
  return _instance;
}

RandomGenerator *RandomGenerator::get() {
  if (_instance == nullptr)
    _instance = get(std::chrono::system_clock::now().time_since_epoch().count(),
                    false, "./", "qr_normal.dat", "qr_uniform.dat");
  return _instance;
}

void RandomGenerator::default_engine(std::string e) {
  if (e == "taus88")
    _defaultEngine = Engine::taus88;
  else if (e == "mersenne")
    _defaultEngine = Engine::mersenne;
}

void RandomGenerator::default_distribution(std::string d) {
  if (d == "normal")
    _defaultDistribution = Distribution::normal;
  else if (d == "cauchy")
    _defaultDistribution = Distribution::cauchy;
  else if (d == "fisher")
    _defaultDistribution = Distribution::fisher;
}

double RandomGenerator::uniform() {
  double res{};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = _tausUnif();
      break;
    case Engine::mersenne:
      res = _mersenneUnif();
      break;
  }
  return res;
}

double RandomGenerator::normal() {
  double res{};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = _tausNormal();
      break;
    case Engine::mersenne:
      res = _mersenneNormal();
      break;
  }
  return res;
}

double RandomGenerator::lognormal() {
  double res{};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = _tausLogNormal();
      break;
    case Engine::mersenne:
      res = _mersenneLogNormal();
      break;
  }
  return res;
}

double RandomGenerator::cauchy() {
  double res{};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = _tausCauchy();
      break;
    case Engine::mersenne:
      res = _mersenneCauchy();
      break;
  }
  return res;
}

double RandomGenerator::fisher() {
  double res{};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = _tausFisher();
      break;
    case Engine::mersenne:
      res = _mersenneFisher();
      break;
  }
  return res;
}

double RandomGenerator::random() {
  double res{};
  switch (_defaultDistribution) {
    case Distribution::normal:
      res = normal();
      break;
    case Distribution::cauchy:
      res = cauchy();
      break;
    case Distribution::fisher:
      res = fisher();
      break;
  }
  return res;
}

int RandomGenerator::uniform(int max, int min) {
  int res{};
  boost::random::uniform_int_distribution<> dist{min, max};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = dist(_taus88);
      break;
    case Engine::mersenne:
      res = dist(_mersenne);
      break;
  }
  return res;
}

double RandomGenerator::normal(double mean, double std) {
  double res{};
  boost::random::normal_distribution<> dist{mean, std};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = dist(_taus88);
      break;
    case Engine::mersenne:
      res = dist(_mersenne);
      break;
  }
  return res;
}

double RandomGenerator::lognormal(double mean, double std) {
  double res{};
  boost::random::lognormal_distribution<> dist{mean, std};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = dist(_taus88);
      break;
    case Engine::mersenne:
      res = dist(_mersenne);
      break;
  }
  return res;
}

double RandomGenerator::cauchy(double loc, double scale) {
  double res{};
  boost::random::cauchy_distribution<> dist{loc, scale};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = dist(_taus88);
      break;
    case Engine::mersenne:
      res = dist(_mersenne);
      break;
  }
  return res;
}

double RandomGenerator::fisher(double m, double n) {
  double res{};
  boost::random::fisher_f_distribution<> dist{m, n};
  switch (_defaultEngine) {
    case Engine::taus88:
      res = dist(_taus88);
      break;
    case Engine::mersenne:
      res = dist(_mersenne);
      break;
  }
  return res;
}

VectorXd RandomGenerator::draw(unsigned n) {
  VectorXd res(n);
  if (_qr) {
    if (n > _qrNormalMatrix.cols()) {
      auto nQR = _qrNormalMatrix.cols();
      res.head(nQR) = quasi_random_normal(nQR);
      std::generate(res.data() + nQR, res.data() + n,
                    boost::bind(&RandomGenerator::random, this));
    } else {
      return quasi_random_normal(n);
    }
  } else {
    std::generate_n(res.data(), n, boost::bind(&RandomGenerator::random, this));
  }
  return res;
}

VectorXd RandomGenerator::draw_uniform(unsigned n) {
  VectorXd res(n);
  if (_qr) {
    if (n > _qrUniformMatrix.cols()) {
      auto nQR = _qrUniformMatrix.cols();
      res.head(nQR) = quasi_random_uniform(nQR);
      std::generate(res.data() + nQR, res.data() + n,
                    boost::bind(&RandomGenerator::random, this));
    } else {
      return quasi_random_uniform(n);
    }
  } else {
    std::generate_n(res.data(), n,
                    boost::bind(&RandomGenerator::uniform, this));
  }
  return res;
}

VectorXd RandomGenerator::quasi_random_normal(unsigned n) {
  VectorXd res;
  if (n > 0) {
    static unsigned r{static_cast<unsigned>(uniform(_qrNormalMatrix.rows()))};
    // lock.acquire();
    ++r;
    if (r > _qrNormalMatrix.rows())
      r = 0;
    // lock.release();
    res = _qrNormalMatrix.row(r).head(n);
  }
  return res;
}

VectorXd RandomGenerator::quasi_random_uniform(unsigned n) {
  VectorXd res;
  if (n > 0) {
    static unsigned r{static_cast<unsigned>(uniform(_qrUniformMatrix.rows()))};
    // lock.acquire();
    ++r;
    if (r > _qrUniformMatrix.rows())
      r = 0;
    // lock.release();
    res = _qrUniformMatrix.row(r).head(n);
  }
  return res;
}

RandomGenerator::RandomGenerator(unsigned seed, bool qr, string path,
                                 string normal_path, string uniform_path)
    : _taus88{seed}, _mersenne{seed}, _qr{qr},
      _qrNormalMatrix{/*read_matrix(path + normal_path, 10000, 50)*/},
      _qrUniformMatrix{/*read_matrix(path + uniform_path, 10000, 50)*/} {}
} // namespace tools
} // namespace ctga

//
// random_generator.cpp ends here
