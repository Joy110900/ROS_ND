#!/bin/bash

# Build the catkin_ws
cd $(pwd)/../../; catkin_make; source devel/setup.bash

export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/worlds/joy.world"

sleep 3
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 3
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" 

