cmake_minimum_required(VERSION 3.5)
project(dynmsg_demo)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
  set(FLAG_NO_WARNINGS "-w")
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(dynmsg REQUIRED)
find_package(rcl REQUIRED)
find_package(rcl_action REQUIRED)

# downloads and imports yaml-cpp into the build tree, we need to do this because we want to
# statically link yaml-cpp.
include(FetchContent)
FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  GIT_TAG yaml-cpp-0.6.3
  GIT_SHALLOW true
)
# Set policy to 'NEW' to allow options to be set through variables
# (needed for cmake<=3.12): https://stackoverflow.com/a/66342383
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(YAML_CPP_BUILD_TESTS OFF)
set(YAML_CPP_INSTALL OFF)
set(CMAKE_BUILD_TYPE_PUSH "${CMAKE_BUILD_TYPE}")
set(CMAKE_C_FLAGS_PUSH "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS_PUSH "${CMAKE_CXX_FLAGS}")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG_NO_WARNINGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG_NO_WARNINGS}")
FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE_PUSH}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_PUSH}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_PUSH}")

include_directories(include)
add_library(dynmsg_demo_library STATIC
  src/cli.cpp
  src/typesupport_utils.cpp
)
ament_target_dependencies(dynmsg_demo_library dynmsg rcl rcl_action)
target_link_libraries(dynmsg_demo_library yaml-cpp)
target_include_directories(dynmsg_demo_library PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_libraries(dynmsg_demo_library)
ament_export_targets(dynmsg_demo_library HAS_LIBRARY_TARGET)
ament_export_dependencies(dynmsg)
ament_export_dependencies(rcl)
ament_export_dependencies(rcl_action)

install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS dynmsg_demo_library yaml-cpp
  EXPORT dynmsg_demo_library
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

add_executable(clitool src/cli_tool.cpp)
# should have been PRIVATE, but ament uses the old signature and we can't mix them
target_link_libraries(clitool dynmsg_demo_library yaml-cpp)
ament_target_dependencies(clitool dynmsg rcl)

install(TARGETS clitool DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  find_package(test_msgs REQUIRED)
  find_package(example_interfaces REQUIRED)
  find_package(dynmsg_msgs REQUIRED)
  find_package(geometry_msgs REQUIRED)
  find_package(std_msgs REQUIRED)

  if (TEST_ASAN)
    set(asan_link_lib -fsanitize=address)
  endif()

  ament_add_gtest(msg_parser_test test/msg_parser_test.cpp)
  if (TEST_ASAN)
    target_compile_options(msg_parser_test PRIVATE -fsanitize=address)
  endif()
  target_link_libraries(msg_parser_test dynmsg_demo_library yaml-cpp ${asan_link_lib})
  ament_target_dependencies(msg_parser_test
    rcl
    test_msgs
    std_msgs
    dynmsg_msgs
  )
  ament_add_gtest(read_msg_buffer test/test_read_msg_buffer.cpp)
  ament_target_dependencies(read_msg_buffer example_interfaces test_msgs)
  target_link_libraries(read_msg_buffer dynmsg_demo_library)
endif()

ament_package()
