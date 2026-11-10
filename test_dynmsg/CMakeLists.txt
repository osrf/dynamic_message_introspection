cmake_minimum_required(VERSION 3.5)
project(test_dynmsg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros_core REQUIRED)
find_package(dynmsg REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(conversion_cpp
  examples/conversion_cpp.cpp
)

target_link_libraries(conversion_cpp
  ament_cmake_ros_core::ament_ros_defaults
  dynmsg::dynmsg
  std_msgs::std_msgs
)

install(TARGETS
  conversion_cpp
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(conversion_c
  examples/conversion_c.cpp
)

target_link_libraries(conversion_c
  ament_cmake_ros_core::ament_ros_defaults
  dynmsg::dynmsg
  std_msgs::std_msgs
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
  target_link_libraries(test_conversion
    ament_cmake_ros_core::ament_ros_defaults
    builtin_interfaces::builtin_interfaces
    dynmsg::dynmsg
    rcl_interfaces::rcl_interfaces
    std_msgs::std_msgs
    test_msgs::test_msgs
  )
endif()

ament_package()
