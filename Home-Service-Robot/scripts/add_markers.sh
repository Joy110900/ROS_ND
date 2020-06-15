#!/bin/bash

# Build the catkin_ws
cd $(pwd)/../../; catkin_make; source devel/setup.bash

export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/worlds/joy.world"
export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/worlds/map.yaml"

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
xterm  -e  " rosrun rviz rviz -d $(pwd)/src/rvizConfig/home_service.rviz" &
sleep 10
xterm -e  "rosrun add_markers add_markers_test"
