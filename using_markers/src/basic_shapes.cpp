#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

geometry_msgs::PoseWithCovarianceStamped robot;


void odomCallback(geometry_msgs::PoseWithCovarianceStamped amcl_pose){
    robot.pose = amcl_pose.pose;
    ROS_INFO("Call back successful");
}

// bool is_difference_small(std_msgs::Float64 x2, std_msgs::Float64 x1){
bool is_difference_small(double x2, double x1){
  if (abs(x2 - x1) <= 0.25){
    return true;
  }
  else{
    return false;
  }
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1, true);
  ros::Subscriber odom_sub = n.subscribe("amcl_pose", 1000, odomCallback);  

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  bool marker_show = true;
  bool is_first_goal_reached = false;


  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    visualization_msgs::Marker goal_marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    if(is_first_goal_reached == false){
      // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
      marker.pose.position.x = 5.707;
      marker.pose.position.y = -0.434;
      // marker.pose.position.z = 0.25;
      marker.pose.position.z = 0.0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = -0.698;
      marker.pose.orientation.w = 0.715;
    }
    else{
      marker.pose.position.x = 3.620;
      marker.pose.position.y = 8.105;
      
      marker.pose.position.z = 0.712;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.712;
      marker.pose.orientation.w = 0.701;
    }

    

    // goal_marker.header.frame_id = "map";
    // goal_marker.header.stamp = ros::Time::now();

    // goal_marker.pose.position.x = 3.620;
    // goal_marker.pose.position.y = 8.105;
    
    // goal_marker.pose.position.z = 0.712;
    // goal_marker.pose.orientation.x = 0.0;
    // goal_marker.pose.orientation.y = 0.0;
    // goal_marker.pose.orientation.z = 0.712;
    // goal_marker.pose.orientation.w = 0.701;
    // goal_marker.lifetime = ros::Duration();

    if(is_first_goal_reached == false){
      // ROS_INFO("Publish object and wait for the robot to pickup");
      marker_pub.publish(marker);
      if(is_difference_small(robot.pose.pose.position.x, marker.pose.position.x) && is_difference_small(robot.pose.pose.position.y, marker.pose.position.y)){
        marker.action = visualization_msgs::Marker::DELETE;  
        ROS_INFO("Robot picked up the object");
        marker_pub.publish(marker);  
        marker_show = false;
        is_first_goal_reached = true;


        


        ros::Duration(5.0).sleep();
      }
    }
    else{
      if(is_difference_small(robot.pose.pose.position.x, marker.pose.position.x) && is_difference_small(robot.pose.pose.position.y, marker.pose.position.y)){
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
      }   
    }
    ros::spinOnce();
  }
}