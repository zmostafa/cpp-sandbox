# option(CPP_SANDBOX_TARGETNAME"Enable compilation of TARGETNAME" ON)
option(CPP_SANDBOX_CONTAINERS "Enable compilation of Containers" ON)

# SOLID Principles
if(CPP_SANDBOX_CONTAINERS)
  message("Building Container folder")
  add_subdirectory(containers)
  # add_subdirectory()
  # add_subdirectory()
endif()
