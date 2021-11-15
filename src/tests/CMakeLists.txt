set(SOURCES
   catch_main.cpp
   element_filters_test.cpp
   image_test.cpp
   image_filters_test.cpp
   fileformats_test.cpp)
add_executable(unittests ${SOURCES})
target_link_libraries(unittests ${PROJECT_LINK_LIBRARIES} image_filters)
target_include_directories(unittests PUBLIC ${PROJECT_INCLUDE_DIR} "../")