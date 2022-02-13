#!/bin/sh
terminator  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
terminator  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch" &  
sleep 5
terminator  -e  " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
terminator  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
terminator  -e  " rosrun using_markers basic_shapes" &