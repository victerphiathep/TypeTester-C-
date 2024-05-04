# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/TypeTest-qt_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TypeTest-qt_autogen.dir/ParseCache.txt"
  "TypeTest-qt_autogen"
  )
endif()
