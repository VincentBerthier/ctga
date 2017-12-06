SET(tools_src
  random_generator.cpp
  parser.cpp
  )

SET(tools_hpp
  random_generator.hpp
  parser.hpp
  )

SET(tools_files ${tools_src} ${tools_hpp} )
add_sources(${tools_src})
add_headers(${tools_hpp})

ADD_LIBRARY(tools STATIC ${tools_src})
