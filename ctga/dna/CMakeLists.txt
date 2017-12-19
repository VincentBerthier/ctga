SET(dna_src
  base.cpp
  sequence.cpp
  pwm.cpp)

SET(dna_hpp
  base.hpp
  sequence.hpp
  pwm.hpp)

SET(dna_files ${dna_src} ${dna_hpp})

add_sources(${dna_src})
add_headers(${dna_hpp})

add_library(dna STATIC ${dna_src})
