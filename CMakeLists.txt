cmake_minimum_required(VERSION 3.30)
project(FancyInfo CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME finfo)

set(SOURCE_FILES
  src/main.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

target_compile_options(${EXECUTABLE_NAME} PRIVATE
  -Wall
  -Wextra
  -Wpedantic
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)
