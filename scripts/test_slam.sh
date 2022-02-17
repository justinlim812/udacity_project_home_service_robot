#!/bin/sh
terminator  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
terminator  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/robond/catkin_ws/src/udacity_project_home_service_robot/maps/zheshien.world" &
sleep 5
terminator  -e  " rosrun turtlebot_gazebo gmapping_demo.launch" &
sleep 5
terminator  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
terminator  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch"