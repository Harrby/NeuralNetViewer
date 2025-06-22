# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NeuralNetViewer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NeuralNetViewer_autogen.dir\\ParseCache.txt"
  "NeuralNetViewer_autogen"
  )
endif()
