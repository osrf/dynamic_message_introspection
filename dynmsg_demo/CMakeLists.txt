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
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rcl REQUIRED)
find_package(rcl_action REQUIRED)

# downloads and imports yaml-cpp into the build tree, we need to do this because we want to
# statically link yaml-cpp.
include(FetchContent)
FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  GIT_TAG yaml-cpp-0.6.3
  GIT_SHALLOW true
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DYAML_CPP_BUILD_TESTS=OFF -DYAML_CPP_INSTALL=OFF)
set(YAML_CPP_BUILD_TESTS OFF)
set(YAML_CPP_INSTALL OFF)
FetchContent_MakeAvailable(yaml-cpp)

include_directories(include)
add_library(dynmsg_demo_library STATIC
  src/cli.cpp
  src/msg_parser.cpp
  src/message_reading.cpp
  src/typesupport_utils.cpp
  src/string_utils.cpp
  )
ament_target_dependencies(dynmsg_demo_library rcl rcl_action)
target_link_libraries(dynmsg_demo_library yaml-cpp)

add_executable(clitool src/cli_tool.cpp)
# should have been PRIVATE, but ament uses the old signature and we can't mix them
target_link_libraries(clitool dynmsg_demo_library yaml-cpp)
ament_target_dependencies(clitool rcl)

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
  ament_add_gtest(wide_strings test/test_wide_strings.cpp)
  target_link_libraries(wide_strings dynmsg_demo_library)
  ament_add_gtest(read_msg_buffer test/test_read_msg_buffer.cpp)
  ament_target_dependencies(read_msg_buffer example_interfaces test_msgs)
  target_link_libraries(read_msg_buffer dynmsg_demo_library)
endif()

ament_package()
