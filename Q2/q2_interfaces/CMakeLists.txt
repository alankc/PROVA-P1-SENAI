cmake_minimum_required(VERSION 3.8)
project(q2_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
#find_package(action_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Pkg1Interface.msg"
  "srv/SensorReaderData.srv"
  "srv/SensorReaderClean.srv"
  "action/PrimeNumber.action"
  DEPENDENCIES std_msgs
)

ament_package()
