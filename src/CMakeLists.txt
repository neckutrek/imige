set(SOURCES
   image_filters.cpp)

add_library(image_filters ${SOURCES})

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(main ${PROJECT_LINK_LIBRARIES} image_filters)

set(OCTARGS -mex -DMATLAB_MEX_FILE)
add_custom_target(mexmain ALL
   COMMAND
      mkoctfile ${PROJECT_SOURCE_DIR}/src/mexmain.cc
   COMMAND
      mv mexmain.oct ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
   VERBATIM
)

add_subdirectory("./tests")