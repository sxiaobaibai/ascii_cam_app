cmake_minimum_required(VERSION 3.8)
project("ascii_cpp_cam")

set(CMAKE_CXX_FLAGS "-O3 -std=c++17 -Wall")

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/main.cc ./src/ascii_cpp_cam.cc)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${OpenCV_INCLUDE_DIRS}
  inc/
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} -lncurses -lpthread)
