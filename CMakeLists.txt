cmake_minimum_required(VERSION 2.8)
project(NetflixRouletteC)

set(NFLX_TARGET nflx)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/output)

option(NFLX_BUILD_STATIC
  "Build NetflixRouletteC as a static library" ON)

set(BUILD_TYPE STATIC)

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

set(PLATFORM_LIBS )

if(UNIX AND NOT APPLE)
  set(PLATFORM_LIBS m)
endif()

foreach(source ${SOURCES})
  list(APPEND HEADERS ${CMAKE_SOURCE_DIR}/${source})
endforeach(source)

if(NFLX_BUILD_STATIC)
  add_definitions(-DNFLX_STATIC)
  set(CURL_STATICLIB ON)
else()
  add_definitions(-DNFLX_EXPORTS)
  set(BUILD_TYPE SHARED)
  set(CURL_STATICLIB OFF)
endif(NFLX_BUILD_STATIC)

add_library(${NFLX_TARGET} ${BUILD_TYPE} ${SOURCES} ${HEADERS})
target_link_libraries(${NFLX_TARGET} libcurl ${PLATFORM_LIBS})
add_dependencies(${NFLX_TARGET} libcurl)

foreach(test ${TESTS})
  add_executable(${test} ${test}.c)
  target_link_libraries(${test} ${NFLX_TARGET} libcurl ${PLATFORM_LIBS})
  add_dependencies(${test} ${NFLX_TARGET} libcurl)
endforeach(test)
