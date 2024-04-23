option(CPP_SANDBOX_DESIGN_PATTERNS_SINGLETON "Enable compilation of Singleton design pattern" ON)

if(CPP_SANDBOX_DESIGN_PATTERNS_SINGLETON)
  message("Building singleton design pattern folder")
  add_subdirectory(singleton)
  add_subdirectory(solid)
endif()
