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
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DYAML_CPP_BUILD_TESTS=OFF -DYAML_CPP_INSTALL=OFF)
set(YAML_CPP_BUILD_TESTS OFF)
set(YAML_CPP_INSTALL OFF)
FetchContent_MakeAvailable(yaml-cpp)

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
