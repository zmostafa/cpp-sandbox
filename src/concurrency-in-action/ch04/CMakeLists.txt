add_library(conditional-variable conditional-variable.cpp)

target_link_libraries(
  conditional-variable
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(conditional-variable PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

