# Udacity Project: Home Service Robot
To program a home service robot that will autonomously map an environment and navigate to pickup and deliver objects.
## Build
After cloning the repo to the src folder of catkin workspace, open a new terminal and run 
```
$ cd <Your catkin workspace>
$ catkin_make
$ source devel/setup.bash
```
## Packages Used
- [gmapping](http://wiki.ros.org/gmapping)  
Using `gmapping_demo.launch` to perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.
- [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop)  
To manually control a robot using keyboard commands with **keyuboard_teleop.launch**.
- [turtlebot_rviz_launchers](http://wiki.ros.org/turtlebot_rviz_launchers)  
Using the `view_nagivation.launch` to load a preconfigured rviz workspace for visualization (e.g. robot model, trajectories, map for environment).
- [turtlebot_gazebo](http://wiki.ros.org/turtlebot_gazebo)  
With `turtlebot_world.launch` to deploy a turtlebot in a gazebo environment by linking the world file into it. `amcl_demo.launch` also used for localization.
## Scripts
- Shell scripts  
To automate launching of ros commands via command lines. Located in **scripts** folder.
## Configuration Files
- `zheshien.pgm`, `zheshien_world.yaml`  
Both files are required to provide a map for amcl, located in the turtlebot_gazebo package **maps** folder.
- `zheshien.world`  
World file to setup the environment in Gazebo, located in the turtleboot_gazebo package **worlds** folder.
## Before Running
The scripts open terminals in Terminator, please install Terminator before running. To install Terminator, open a new terminal and run
```
$ sudo apt-get install terminator
```
## Running the Scripts
1. **`launch.sh`**  
To launch Gazebo and Rviz without any configuration.  
2. **`test_slam.sh`**  
To manually test SLAM. Controlling of turtlebot is done by keyboard commands.  
3. **`test_navigation.sh`**  
To make sure turtlebot is able to reach positions by manually setting 2D navigation goals using Rviz.  
4. **`pick_objects.sh`**  
To make sure robot is able to reach its two predefined poses. The robot will travel to a desired pickup goal, wait 5 seconds, then travel to desired drop off zone.  
5. **`add_marker.sh`**  
To visualize and test marker's behaviors. A cube marker will first appear at initial position for 5 seconds, then disappear for 5 seconds, and lastly show up at another position.  
6. **`home_service.sh`**  
The final script for robot's movements utilizing all the packages in previous testings. An object (marker) will first show up in a pickup zone for the robot to move towards to. Upon reaching the position, the marker will disappear. The robot will then move towards the drop off position and drop off the object, the marker will reappear at the drop off position.
