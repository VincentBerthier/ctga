// random_generator.hpp ---
//
// Filename: random_generator.hpp
// Description:
// Author: Vincent Berthier
// Maintainer:
// Copyright 2018 <Vincent Berthier>
// Created: 2017-12-06T01:42:04+0000
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


#ifndef CTGA_TOOLS_RANDOM_GENERATOR_HPP_
#define CTGA_TOOLS_RANDOM_GENERATOR_HPP_

// #include <boost/random.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/fisher_f_distribution.hpp>
#include <boost/random/lognormal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/taus88.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <eigen3/Eigen/Core>

#include <algorithm>
// #include <chrono>
#include <random>
#include <string>
#include <utility>

namespace ctga {
namespace tools {

/** \brief Generation of random numbers
 *
 * RandomGenerator allows the generation of random numbers using C++11
 * library.
 */
class RandomGenerator {
 public:

  /** \brief Define the default random distribution to use */
  enum class Distribution {
    normal, /*!< Normal (gaussian) distribution */
    cauchy, /*!< Cauchy distribution */
    fisher /*!< Fisher distribution */
  };

  /** \brief Define the random engine to use */
  enum class Engine {
    taus88,    /*!< Taus88 engine */
    mersenne /*!< Mersenne twister engine */
  };

  /** \brief  Get or construct the random generator
   * \param seed Seed to initialise the random engines
   * \param quasi_random Use quasi random whenever possible?
   * \param path Base path in where the quasi random files are located
   * \param normal_path File defining quasi random values with normal distribution
   * \param uniform_path File defining quasi random values with uniform distribution
   *
   * @return Pointer to the random generator
   */
  static RandomGenerator *get(unsigned seed, bool quasi_random,
                              std::string path, std::string normal_path,
                              std::string uniform_path);

  /** \brief  Get or construct the random generator, assuming standard file names
   * \param seed Seed to initialise the random engines
   * \param quasi_random Use quasi random whenever possible?
   * \param path Base path in where the quasi random files are located
   *
   * @return Pointer to the random generator
   */
  static RandomGenerator *get(unsigned seed, bool quasi_random,
                              std::string path);

  static RandomGenerator *get(unsigned seed);

  /** \brief  Get or construct the random generator with default values
   *
   * @return Pointer to the random generator
   */
  static RandomGenerator *get();

  /** \brief  Set the default engine
   * \param e New default engine
   */
  void default_engine(std::string e);
  /** \brief  Set the default distribution to use
   * \param d New default distribution
   */
  void default_distribution(std::string);

  /** \brief  Draws true or false
   * \param p Probability to dwaw true
   *
   * @return Random true or false
   */
  double uniform();
  /** \brief  Randomly draws a number
   * \param max Maximum allowed value
   * \param min Minimum allowed value
   *
   * @return Random int between min and max
   */
  int uniform(int max, int min);
  /** \brief  Randomly draws a number
   * \param max Maximum allowed value
   *
   * @return Random int between 0 and max
   */
  int uniform(int max) { return uniform(max, 0); }
  /** \brief  Randomly draws a number with a normal distribution
   * \param mean Mean of the distribution
   * \param std Standard deviation of the distribution
   *
   * @return Random number
   */
  double normal(double mean, double std);
  /** \brief  Randomly draws a number with a normal distribution N(0,1)
   *
   * @return Random number
   */
  double normal();
  /** \brief  Randomly draws a number with a log-normal distribution
   * \param mean Mean of the distribution
   * \param std Standard deviation of the distribution
   *
   * @return Random number
   */
  double lognormal(double mean, double std);
  /** \brief  Randomly draws a number with a log-normal distribution of mean = 0. and
   * standard deviation = 1.0
   *
   * @return Random number
   */
  double lognormal();
  /** \brief  Randomly draws a number with a Cauchy distribution
   * \param loc Location of the distribution
   * \param scale Scale of the distribution
   *
   * @return Random number
   */
  double cauchy(double loc, double scale);
  /** \brief  Randomly draws a number with a Cauchy distribution of location = 0. and
   * scale = 1.
   *
   * @return Random number
   */
  double cauchy();
  /** \brief  Randomly draws a number with a Fisher distribution
   * \param m M parameter of the Fisher distribution
   * \param n N parameter of the Fisher distribution
   *
   * @return Random number
   */
  double fisher(double m, double n);
  /** \brief  Randomly draws a number with a Fisher distribution with m = 1 and n = 1.
   *
   * @return Random number
   */
  double fisher();
  /** \brief   Randomly draw a number with the default distribution and default
   * parameters
   *
   * @return Random number
   */
  double random();
  /** \brief  Randomly chooses a given number of values
   * \param n Number of values to draw
   *
   * Randomly draw a given number of values, using the default distribution
   * with default parameters.
   *
   * @return Random values
   */
  inline bool flip(double p) { return uniform() < p; }

  /** \brief  Draws true or false with probability 1/2
   *
   * @return Random true or false
   */
  inline bool flip() { return flip(0.5); }
  /** \brief  Randomly draws a uniform number in [0,1)
   *
   * @return Random value in [0,1)
   */
  Eigen::VectorXd draw(unsigned n);
  /** \brief  Randomly chooses a given number of values in [0,1)
   * \param n Number of values to draw
   *
   * Randomly draw a given number of values, using the uniform distribution
   *
   * @return Random values
   */
  Eigen::VectorXd draw_uniform(unsigned n);
  /** \brief  Set Quasi-Random draw
   * \param qr New quasi-random state
   */
  void set_quasi_random(bool qr) { _qr = qr; }
  /** \brief  Use normal quasi-random to draw values
   * \param n Number of values to draw
   *
   * @return Quasi-random values
   */
  Eigen::VectorXd quasi_random_normal(unsigned n);
  /** \brief  Use uniform quasi-random to draw values
   * \param n Number of values to draw
   *
   * @return Quasi-random uniform values
   */
  Eigen::VectorXd quasi_random_uniform(unsigned n);
  /** \brief  Restricted random permutation
   * \param fwditer Container type
   * \param start First element
   * \param end Last element
   * \param number Number of element to randomly select
   *
   * With this function, only number elements are randomly selected among all
   * the elements and placed at the start of the vector/list/etc. This allows a
   * significant speed-up when the number of chosen elements is much less than
   * the number of elmements in the collection.
   *
   * @return the new vector with a given number of elements randomly selected at
   * the beginning
   */
  template <typename fwditer>
  fwditer permutation(fwditer start, fwditer end, unsigned number);

 private:
  RandomGenerator(unsigned seed, bool quasi_random, std::string path,
                  std::string normal_path, std::string uniform_path);

  static RandomGenerator *_instance;
  // Defaults
  Distribution _defaultDistribution{Distribution::normal};
  Engine _defaultEngine{Engine::taus88};
  // Generation engines
  boost::random::taus88 _taus88;
  boost::random::mt19937 _mersenne;

  // Tauss88 generators
  boost::variate_generator<boost::random::taus88, boost::random::uniform_01<>>
  _tausUnif{_taus88, boost::random::uniform_01<>{}};
  boost::variate_generator<boost::random::taus88,
                           boost::random::normal_distribution<>> _tausNormal{
    _taus88, boost::random::normal_distribution<>{}};
  boost::variate_generator<boost::random::taus88,
                           boost::random::lognormal_distribution<>>
  _tausLogNormal{_taus88, boost::random::lognormal_distribution<>{}};
  boost::variate_generator<boost::random::taus88,
                           boost::random::cauchy_distribution<>> _tausCauchy{
    _taus88, boost::random::cauchy_distribution<>{}};
  boost::variate_generator<boost::random::taus88,
                           boost::random::fisher_f_distribution<>> _tausFisher{
    _taus88, boost::random::fisher_f_distribution<>{}};
  // Mersenne generators
  boost::variate_generator<boost::random::mt19937, boost::random::uniform_01<>>
  _mersenneUnif{_mersenne, boost::random::uniform_01<>{}};
  boost::variate_generator<boost::random::mt19937,
                           boost::random::normal_distribution<>>
  _mersenneNormal{_mersenne, boost::random::normal_distribution<>{}};
  boost::variate_generator<boost::random::mt19937,
                           boost::random::lognormal_distribution<>>
  _mersenneLogNormal{_mersenne, boost::random::lognormal_distribution<>{}};
  boost::variate_generator<boost::random::mt19937,
                           boost::random::cauchy_distribution<>>
  _mersenneCauchy{_mersenne, boost::random::cauchy_distribution<>{}};
  boost::variate_generator<boost::random::mt19937,
                           boost::random::fisher_f_distribution<>>
  _mersenneFisher{_mersenne, boost::random::fisher_f_distribution<>{}};

  // Quasi random configuration
  bool _qr{false};
  // QR normal matrix
  const Eigen::MatrixXd _qrNormalMatrix{};
  // QR normal matrix
  const Eigen::MatrixXd _qrUniformMatrix{};
};

template <typename fwditer>
fwditer RandomGenerator::permutation(fwditer begin, fwditer end,
                                     unsigned num_random) {
  size_t left = std::distance(begin, end) - 1;
  while (--num_random) {
    fwditer r = begin;
    auto i = uniform(left);
    std::advance(r, i);
    std::swap(*begin, *r);
    ++begin;
    --left;
  }
  return begin;
}
}  // namespace tools
}  // namespace ctga

#endif  // CTGA_TOOLS_RANDOM_GENERATOR_HPP_

//
// random_generator.hpp ends here
