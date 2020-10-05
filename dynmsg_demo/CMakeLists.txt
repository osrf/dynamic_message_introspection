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

set(source_files
  src/cli.cpp
  src/msg_parser.cpp
  src/typesupport_utils.cpp
  src/string_utils.cpp
)

add_executable(dynmsg_demo
  src/dynmsg_demo.cpp
  ${source_files}
)
# should have been PRIVATE, but ament uses the old signature and we can't mix them
target_link_libraries(dynmsg_demo yaml-cpp)
ament_target_dependencies(dynmsg_demo rcl rcl_action)

install(TARGETS dynmsg_demo DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(test_msgs REQUIRED)
  find_package(dynmsg_msgs REQUIRED)

  # TODO: export main funcs as a static lib so we can use target linking?
  find_package(PkgConfig REQUIRED)
  pkg_search_module(GTEST REQUIRED gtest_main)
  add_executable(dynmsg_demo_test
    ${source_files}
    test/msg_parser_test.cpp
  )
  # should have been PRIVATE, but ament uses the old signature and we can't mix them
  target_link_libraries(dynmsg_demo_test yaml-cpp)
  ament_target_dependencies(dynmsg_demo_test rcl test_msgs dynmsg_msgs GTEST)
  target_compile_options(dynmsg_demo_test PUBLIC ${GTEST_CFLAGS})
  include(GoogleTest)
  gtest_discover_tests(dynmsg_demo_test)
endif()

ament_package()
