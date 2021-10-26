add_executable(main main.cpp)
target_include_directories(main PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(main ${PROJECT_LINK_LIBRARIES})

add_custom_target(mex_function ALL
   COMMAND
      mkoctfile -mex ${PROJECT_SOURCE_DIR}/src/mex_function.c
   COMMAND
      mv mex_function.mex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
   VERBATIM
)