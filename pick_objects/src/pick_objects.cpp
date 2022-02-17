#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  // Tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // Set up frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define first goal position
  goal.target_pose.pose.position.x = 5.707;
  goal.target_pose.pose.position.y = -0.434;
  goal.target_pose.pose.orientation.z = -0.698;
  goal.target_pose.pose.orientation.w = 0.715;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Robot moving to the first goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("The robot reached its first goal");
  }
  else{
    ROS_INFO("The robot failed to reach the first goal for some reason");
  }

  ros::Duration(5.0).sleep();

  // Define second goal position
  goal.target_pose.pose.position.x = 3.620;
  goal.target_pose.pose.position.y = 8.105;
  goal.target_pose.pose.orientation.z = 0.712;
  goal.target_pose.pose.orientation.w = 0.701;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Robot moving to the second goal");
  ac.sendGoal(goal);
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("The robot reached its second goal");
  }
  else{
    ROS_INFO("The base failed to reach the second goal for some reason");
  }

  return 0;
}