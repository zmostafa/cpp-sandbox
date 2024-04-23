add_library(single-resposibility single-resposibility.cpp)

target_link_libraries(
  singleton
  PRIVATE cpp-sandbox::project_options
          cpp-sandbox::project_warnings
  )

target_include_directories(solid PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
