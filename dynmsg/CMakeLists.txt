cmake_minimum_required(VERSION 3.5)
project(dynmsg)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # -fPIC for building a static lib (yaml-cpp) that later gets linked into a dynamic lib
  add_compile_options(-Wall -Wextra -Wpedantic -fPIC)
  set(FLAG_NO_WARNINGS "-w")
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_runtime_c REQUIRED)
find_package(rosidl_typesupport_introspection_c REQUIRED)

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
add_library(dynmsg STATIC
  src/msg_parser.cpp
  src/message_reading.cpp
  src/typesupport.cpp
  src/string_utils.cpp
)
ament_target_dependencies(dynmsg
  rosidl_runtime_c
  rosidl_typesupport_introspection_c
)
target_link_libraries(dynmsg yaml-cpp)
target_include_directories(dynmsg PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_libraries(dynmsg)
ament_export_targets(dynmsg HAS_LIBRARY_TARGET)
ament_export_dependencies(rosidl_runtime_c)
ament_export_dependencies(rosidl_typesupport_introspection_c)

install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS dynmsg yaml-cpp
  EXPORT dynmsg
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(wide_strings test/test_wide_strings.cpp)
  target_link_libraries(wide_strings dynmsg)
endif()

ament_package()
