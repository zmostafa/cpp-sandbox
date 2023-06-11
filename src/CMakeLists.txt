# option(CPP_SANDBOX_TARGETNAME"Enable compilation of TARGETNAME" ON)
option(CPP_SANDBOX_CONTAINERS "Enable compilation of Containers" OFF)
option(CPP_SANDBOX_CONCURRENCY_IN_ACTION "Enable compilation of Concurrency in Action Book" ON)
option(CPP_SANDBOX_DESIGN_PATTERNS "Enable compilation of Design patterns folder" ON)

# SOLID Principles
if(CPP_SANDBOX_CONTAINERS)
  message("Building Container folder")
  add_subdirectory(containers)
  # add_subdirectory()
  # add_subdirectory()
endif()

# Concurrency In Action Book
if(CPP_SANDBOX_CONCURRENCY_IN_ACTION)
  message("Building Concurrency in Action folder") 
  add_subdirectory(concurrency-in-action)
endif()

# Design patterns
if(CPP_SANDBOX_DESIGN_PATTERNS)
  message("Building Design Patterns folder") 
  add_subdirectory(design-patterns)
endif()
