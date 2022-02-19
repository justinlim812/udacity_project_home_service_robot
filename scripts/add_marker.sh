#!/bin/sh
terminator  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
terminator  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/zheshien.world" &	
sleep 5
terminator  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find turtlebot_gazebo)/maps/zheshien_world.yaml" &
sleep 5
terminator  -e  " roslaunch turtlebot_rviz_launchers view_navigation_with_marker.launch" &
sleep 5
terminator  -e  " rosrun add_markers add_markers_test"