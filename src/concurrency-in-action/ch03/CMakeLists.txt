# add_executable(thread_management thread_management.cpp)
#
# target_link_libraries(
#   thread_management
#   PRIVATE cpp-sandbox::project_options
#           cpp-sandbox::project_warnings
#   )
#
# target_include_directories(thread_management PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

# add_library(protecting-data protecting-data.cpp)
#
# target_link_libraries(
#   protecting-data
#   PRIVATE cpp-sandbox::project_options
#           cpp-sandbox::project_warnings
#   )
#
# target_include_directories(protecting-data PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(threadsafe-stack threadsafe-stack.cpp)

target_link_libraries(
  threadsafe-stack
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(threadsafe-stack PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

