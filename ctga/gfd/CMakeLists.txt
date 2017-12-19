SET(gfd_src
  individual.cpp
  gutierez.cpp
  pwm_evaluator.cpp)

SET(gfd_hpp
  individual.hpp
  gutierez.hpp
  pwm_evaluator.hpp)

SET(gfd_files ${gfd_src} ${gfd_hpp})

add_sources(${gfd_src})
add_headers(${gfd_hpp})

add_library(gfd STATIC ${gfd_src})
