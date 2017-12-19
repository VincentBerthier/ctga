# - Try to find the Cln library

if ((NOT CLN_LIB) OR ("${CLN_LIB}" STREQUAL "CLN_LIB-NOTFOUND"))
  # Check if we need the static or shared library
  get_property(STATIC GLOBAL PROPERTY STATIC)
  if (STATIC)
    set(LIB_NAME "libcln.a")
  else()
    set(LIB_NAME "libcln.so")
  endif(STATIC)

  # Try to find the correct library
  find_library(CLN_LIB
    NAMES ${LIB_NAME}
    PATHS
    ${CMAKE_SOURCE_DIR}/depends/lib
    /usr/lib64 /usr/local/lib64 /usr/lib /usr/local/lib
    )
endif ((NOT CLN_LIB) OR ("${CLN_LIB}" STREQUAL "CLN_LIB-NOTFOUND"))
