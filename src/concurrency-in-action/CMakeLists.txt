# option(CPP_SANDBOX_TARGETNAME"Enable compilation of TARGETNAME" ON)
option(CPP_SANDBOX_CONCURRENCY_IN_ACTION_CH01 "Enable compilation of Concurrency in action ch01" ON)
option(CPP_SANDBOX_CONCURRENCY_IN_ACTION_CH02 "Enable compilation of Concurrency in action ch02" ON)
option(CPP_SANDBOX_CONCURRENCY_IN_ACTION_CH03 "Enable compilation of Concurrency in action ch03" ON)

if(CPP_SANDBOX_CONCURRENCY_IN_ACTION_CH01)
  message("Building Concurrency in action ch01")
  add_subdirectory(ch01)
endif()

if(CPP_SANDBOX_CONCURRENCY_IN_ACTION_CH02)
  message("Building Concurrency in action ch02")
  add_subdirectory(ch02)
endif()

if(CPP_SANDBOX_CONCURRENCY_IN_ACTION_CH03)
  message("Building Concurrency in action ch03")
  add_subdirectory(ch03)
endif()
