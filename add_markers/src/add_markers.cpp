#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

geometry_msgs::PoseWithCovarianceStamped robot;

void odomCallback(geometry_msgs::PoseWithCovarianceStamped amcl_pose){
    robot.pose = amcl_pose.pose;
}

double threshold = 0.01;
bool is_difference_small(double x2, double x1)
{
  if (abs(x2 - x1) <= threshold){
    return true;
  }
  else{
    return false;
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1, true);
  ros::Subscriber odom_sub = n.subscribe("amcl_pose", 1000, odomCallback);  

  uint32_t shape = visualization_msgs::Marker::CUBE;
  bool is_first_goal_reached = false;
  bool show_status = true;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    visualization_msgs::Marker goal_marker;

    // Set the frame ID and timestamp
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type
    marker.type = shape;

    // Set the marker action
    marker.action = visualization_msgs::Marker::ADD;

    // Set the scale of the marker
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    // Set marker lifetime to not expire
    marker.lifetime = ros::Duration();

    // Check whether the robot reaches first goal
    if(is_first_goal_reached == false)
    {
      // Set the pose of the marker
      marker.pose.position.x = 5.707;
      marker.pose.position.y = -0.434;
      marker.pose.position.z = 0.0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = -0.698;
      marker.pose.orientation.w = 0.715;

      // Show marker
      marker_pub.publish(marker);

      // If robot reaches the goal position
      if(is_difference_small(robot.pose.pose.position.x, marker.pose.position.x) && is_difference_small(robot.pose.pose.position.y, marker.pose.position.y))
      {
        marker.action = visualization_msgs::Marker::DELETE;  
        marker_pub.publish(marker);
        if(show_status){
          ROS_INFO("Robot picked up the object");  
        }  
        is_first_goal_reached = true;
        ros::Duration(5.0).sleep();
      }
    }
    else
    {
      marker.pose.position.x = 3.620;
      marker.pose.position.y = 8.105;
      marker.pose.position.z = 0.0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.712;
      marker.pose.orientation.w = 0.701;

      if(is_difference_small(robot.pose.pose.position.x, marker.pose.position.x) && is_difference_small(robot.pose.pose.position.y, marker.pose.position.y))
      {
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
        if(show_status){
          ROS_INFO("Robot delivered the object");
          show_status = false;
        }
      } 
    }
    ros::spinOnce();
  }
}