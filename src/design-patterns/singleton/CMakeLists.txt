add_library(singleton singleton.cpp)

target_link_libraries(
  singleton
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(singleton PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
