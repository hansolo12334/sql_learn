# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/main_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/main_autogen.dir/ParseCache.txt"
  "CMakeFiles/test_sql_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/test_sql_autogen.dir/ParseCache.txt"
  "CMakeFiles/test_sql_rrys_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/test_sql_rrys_autogen.dir/ParseCache.txt"
  "main_autogen"
  "test_sql_autogen"
  "test_sql_rrys_autogen"
  )
endif()
