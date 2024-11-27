# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/zbuffer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/zbuffer_autogen.dir/ParseCache.txt"
  "zbuffer_autogen"
  )
endif()
