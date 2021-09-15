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
find_package(rcutils REQUIRED)
find_package(rosidl_runtime_c REQUIRED)
find_package(rosidl_runtime_cpp REQUIRED)
find_package(rosidl_typesupport_introspection_c REQUIRED)
find_package(rosidl_typesupport_introspection_cpp REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)

# See config.hpp.in
option(DYNMSG_VALUE_ONLY "Write message member value directly instead default+value" ON)
option(DYNMSG_YAML_CPP_BAD_INT8_HANDLING "Work around buggy [u]int8_t handling by yaml-cpp" ON)
option(DYNMSG_PARSER_DEBUG "Enable debugging-related logs for YAML->msg conversion" OFF)
configure_file(include/${PROJECT_NAME}/config.hpp.in include/${PROJECT_NAME}/config.hpp)

add_library(dynmsg STATIC
  src/msg_parser_c.cpp
  src/msg_parser_cpp.cpp
  src/message_reading_c.cpp
  src/message_reading_cpp.cpp
  src/typesupport.cpp
  src/vector_utils.cpp
  src/string_utils.cpp
  src/yaml_utils.cpp
)
ament_target_dependencies(dynmsg
  rcutils
  rosidl_runtime_c
  rosidl_runtime_cpp
  rosidl_typesupport_introspection_c
  rosidl_typesupport_introspection_cpp
  yaml_cpp_vendor
)
target_include_directories(dynmsg PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_libraries(dynmsg)
ament_export_targets(dynmsg HAS_LIBRARY_TARGET)
ament_export_dependencies(rcutils)
ament_export_dependencies(rosidl_runtime_c)
ament_export_dependencies(rosidl_runtime_cpp)
ament_export_dependencies(rosidl_typesupport_introspection_c)
ament_export_dependencies(rosidl_typesupport_introspection_cpp)
ament_export_dependencies(yaml_cpp_vendor)

install(
  DIRECTORY include/ ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION include
  PATTERN "*.in" EXCLUDE
)
install(
  TARGETS dynmsg
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
  find_package(std_msgs REQUIRED)

  ament_add_gtest(wide_strings test/test_wide_strings.cpp)
  target_link_libraries(wide_strings dynmsg)

  ament_add_gtest(test_vector_utils test/test_vector_utils.cpp)
  target_link_libraries(test_vector_utils dynmsg)

  ament_add_gtest(test_typesupport test/test_typesupport.cpp)
  target_link_libraries(test_typesupport dynmsg)
  ament_target_dependencies(test_typesupport std_msgs)
endif()

ament_package()
