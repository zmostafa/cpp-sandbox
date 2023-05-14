add_executable(thread_management thread_management.cpp)

target_link_libraries(
  thread_management
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(thread_management PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

