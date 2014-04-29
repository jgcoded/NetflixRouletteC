cmake_minimum_required(VERSION 2.8)
project(NetflixRouletteC)

set(NFLX_TARGET nflx)

option(NFLX_BUILD_STATIC
  "Build NetflixRouletteC as a shared library" OFF)

add_subdirectory(deps)

include_directories(
  ${CMAKE_SOURCE_DIR}/deps/cJSON
  ${CMAKE_SOURCE_DIR}/deps/curl-7.36.0/include
  ${CMAKE_SOURCE_DIR}
)

set(SOURCES
  deps/cJSON/cJSON.c
  netflixroulettec.c
)

set(HEADERS
  deps/cJSON/cJSON.h
  netflixroulettec.h
)

set(TESTS
  test
)

foreach(source ${SOURCES})
  list(APPEND HEADERS ${CMAKE_SOURCE_DIR}/${source})
endforeach(source)

add_library(${NFLX_TARGET} ${SOURCES} ${HEADERS})
target_link_libraries(${NFLX_TARGET} libcurl)
add_dependencies(${NFLX_TARGET} libcurl)

foreach(test ${TESTS})
  add_executable(${test} ${test}.c)
  target_link_libraries(${test} ${NFLX_TARGET} libcurl)
  add_dependencies(${test} ${NFLX_TARGET} libcurl)
endforeach(test)
