add_executable(hello-concurrent-world hello-concurrent-world.cpp)

target_link_libraries(
  hello-concurrent-world
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(hello-concurrent-world PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

