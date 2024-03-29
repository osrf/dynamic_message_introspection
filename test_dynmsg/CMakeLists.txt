cmake_minimum_required(VERSION 3.5)
project(test_dynmsg)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(dynmsg REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(conversion_cpp
  examples/conversion_cpp.cpp
)
ament_target_dependencies(conversion_cpp
  dynmsg
  std_msgs
)
install(TARGETS
  conversion_cpp
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(conversion_c
  examples/conversion_c.cpp
)
ament_target_dependencies(conversion_c
  dynmsg
  std_msgs
)
install(TARGETS
  conversion_c
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  find_package(builtin_interfaces REQUIRED)
  find_package(rcl_interfaces REQUIRED)
  find_package(test_msgs REQUIRED)

  ament_add_gtest(test_conversion
    test/test_conversion.cpp
  )
  ament_target_dependencies(test_conversion
    builtin_interfaces
    dynmsg
    rcl_interfaces
    std_msgs
    test_msgs
  )
endif()

ament_package()
