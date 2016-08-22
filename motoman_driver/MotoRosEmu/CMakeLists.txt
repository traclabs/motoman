cmake_minimum_required(VERSION 2.8.3)

project(MotoRosEmu C)

set(CTRLR_TYPE FS100)

# for now
if (NOT CTRLR_TYPE STREQUAL "FS100")
  message(WARNING "
    WARNING: Only the 'FS100' controller type is expected to work
    with MotoRosEmu at this time.")
endif()


find_package(Threads REQUIRED)

add_definitions(-D${CTRLR_TYPE})
add_definitions(-DMRE_CTRLR="${CTRLR_TYPE}")
add_definitions(-Wimplicit-function-declaration)
#add_definitions(-fsigned-char)
add_definitions(-Wall)
#add_definitions(-Werror)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif()


set(MotoPlus_DIR ../MotoPlus)

include_directories(include ${MotoPlus_DIR})


set(MotoRos_SRCS
  ${MotoPlus_DIR}/Controller.c
  ${MotoPlus_DIR}/CtrlGroup.c
  ${MotoPlus_DIR}/MotionServer.c
  ${MotoPlus_DIR}/SimpleMessage.c
  ${MotoPlus_DIR}/StateServer.c
  ${MotoPlus_DIR}/mpMain.c
)


# emu rtl - Linux only for now
add_library(MotoRosRtlLinux SHARED
  mempool.c
  misc.c
  motion_ctrl.c
  network.c
  system_ctrl.c
  system_mon.c
  task_ctrl.c
)
target_link_libraries(MotoRosRtlLinux
  ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(MotoRosRtlLinux
  PROPERTIES
    COMPILE_FLAGS "-m32"
    LINK_FLAGS "-m32"
)


# main wrapper
add_executable(MotoRosEmu${CTRLR_TYPE}.out
  ${MotoRos_SRCS}
  FakeParameterExtraction.c
  main.c
)
target_link_libraries(MotoRosEmu${CTRLR_TYPE}.out
  MotoRosRtlLinux)
set_target_properties(MotoRosEmu${CTRLR_TYPE}.out
  PROPERTIES
    COMPILE_FLAGS "-m32"
    LINK_FLAGS "-m32"
)
