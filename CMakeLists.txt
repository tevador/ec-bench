cmake_minimum_required(VERSION 3.5)

project(ec_bench)

set(ec_bench_sources
src/main.c
src/platform.c)

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH_ID)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Setting default build type: ${CMAKE_BUILD_TYPE}")
endif()

if(ARCH_ID STREQUAL "x86_64" OR ARCH_ID STREQUAL "x86-64" OR ARCH_ID STREQUAL "amd64")
  if(MSVC)
    enable_language(ASM_MASM)
    list(APPEND ec_bench_sources src/fe_masm.asm)
    set_property(SOURCE src/fe_masm.asm PROPERTY LANGUAGE ASM_MASM)
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /DRELWITHDEBINFO")
  else()
    list(APPEND ec_bench_sources src/fe_gnu.S)
	set_property(SOURCE src/fe_gnu.S PROPERTY LANGUAGE C)
    set_property(SOURCE src/fe_gnu.S PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.asm)
  endif()
else()
    message(FATAL_ERROR "Only x64 is supported")
endif()

add_executable(ec_bench ${ec_bench_sources})
set_property(TARGET ec_bench PROPERTY POSITION_INDEPENDENT_CODE ON)
