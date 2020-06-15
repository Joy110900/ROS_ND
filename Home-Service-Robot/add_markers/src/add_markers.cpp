#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <complex>

float pickup_zone[3] = {5.8, 0.2, 1.0};
float dropoff_zone[3] = {-4.8, 3.4, 1.0};
float thresh = 0.3;

bool inPickupZone = false;
bool inDropoffZone = false;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{ 
	float odom_x = msg->pose.pose.position.x;
  	float odom_y = msg->pose.pose.position.y;

//Pick up zone
	if (std::abs(pickup_zone[0] - odom_x) < thresh && std::abs(pickup_zone[1] - odom_y) < thresh)
   { 
     inPickupZone = true;
   }
 
	else
		inPickupZone = false;

//Drop off zone
	if (std::abs(dropoff_zone[0] - odom_x) < thresh && std::abs(dropoff_zone[1] - odom_y) < thresh)
	{ 
	 	inDropoffZone = true;
   	}
   	
	else
		inDropoffZone = false;
}

int main( int argc, char** argv )
{
  ROS_INFO("Main");
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 1000, odomCallback);
  


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
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

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickup_zone[0];
    marker.pose.position.y = pickup_zone[1];
    marker.pose.position.z = 0;
    
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = pickup_zone[2];

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    
   marker_pub.publish(marker);
   ROS_INFO("Pick-up marker displayed");
   
   //Wait for Pick-Up
   while(!inPickupZone)
   {
    ros::spinOnce();
   }
   
   if(inPickupZone)
   {
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Pick-up marker removed");
   }  
   
   //Wait for Drop-Off
   while(!inDropoffZone)
   {
    ros::spinOnce();
   }

   if(inDropoffZone)
   {
    marker.pose.position.x = dropoff_zone[0];
    marker.pose.position.y = dropoff_zone[1];
    marker.pose.orientation.w = dropoff_zone[2];;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Drop-off marker displayed");
    ros::Duration(10.0).sleep();
   }  
    return 0;
  }
 
}
