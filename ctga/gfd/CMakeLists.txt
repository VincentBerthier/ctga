SET(gfd_src
  gutierez.cpp)

SET(gfd_hpp
  gutierez.hpp)

SET(gfd_files ${gfd_src} ${gfd_hpp})

add_sources(${gfd_src})
add_headers(${gfd_hpp})

add_library(gfd STATIC ${gfd_src})
