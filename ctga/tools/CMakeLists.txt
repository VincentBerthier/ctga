SET(tools_src
  random_generator.cpp
  io.cpp
  statistics.cpp
  mann_whitney.cpp
  )

SET(tools_hpp
  random_generator.hpp
  io.hpp
  statistics.hpp
  mann_whitney.hpp
  )

SET(tools_files ${tools_src} ${tools_hpp} )
add_sources(${tools_src})
add_headers(${tools_hpp})

ADD_LIBRARY(tools STATIC ${tools_src})
