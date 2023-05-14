# add_executable(thread_management thread_management.cpp)
#
# target_link_libraries(
#   thread_management
#   PRIVATE cpp-sandbox::project_options
#           cpp-sandbox::project_warnings
#   )
#
# target_include_directories(thread_management PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(joining_thread joining_thread.cpp)

target_link_libraries(
  joining_thread
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(joining_thread PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

