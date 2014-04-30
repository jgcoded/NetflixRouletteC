cmake_minimum_required(VERSION 2.8)

set(CURL_VER 7.36.0)
set(CURL_MIRROR http://curl.haxx.se/download/curl-${CURL_VER}.tar.gz)
set(CURL_TARGET ${CMAKE_SOURCE_DIR}/deps/curl-${CURL_VER})
set(CURL_FILE ${CURL_TARGET}.tar.gz)

if(NOT EXISTS ${CURL_FILE} AND NOT EXISTS ${CURL_TARGET})
  message(STATUS "  Downloading libcurl")
  file(DOWNLOAD ${CURL_MIRROR} ${CURL_FILE} SHOW_PROGRESS TIMEOUT 60)
endif()

if(NOT EXISTS ${CURL_TARGET} AND EXISTS ${CURL_FILE})
  message(STATUS "  unpacking libcurl")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${CURL_FILE} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/deps)
  message(STATUS "  removing ${CURL_FILE}")
  file(REMOVE ${CURL_FILE})
endif()

if(EXISTS ${CURL_TARGET})
  add_subdirectory(${CURL_TARGET})
endif()

