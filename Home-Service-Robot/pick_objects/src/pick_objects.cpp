#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

float pickup_goal[3] = {5.9, 0.24, -0.4};
float dropoff_goal[3] = {-4.84, 3.5, 1.0};

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = pickup_goal[0];
  goal.target_pose.pose.position.y = pickup_goal[1];
  goal.target_pose.pose.orientation.w = pickup_goal[2] ;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending Pick up goal");
  ac.sendGoal(goal);
  ROS_INFO("Robot reaching Pick-Up Zone.........");
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
     {
     ROS_INFO("Robot reached Pick-Up Zone successfully");
     ros::Duration(5.0).sleep();

	 ROS_INFO("Sending Drop off Goal");
     goal.target_pose.pose.position.x = dropoff_goal[0];
     goal.target_pose.pose.position.y = dropoff_goal[1];
     goal.target_pose.pose.orientation.w = dropoff_goal[2];
     ac.sendGoal(goal);
	 ROS_INFO("Robot reaching Drop off Zone.........");
     ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
     {
	  	ROS_INFO("Robot reached Drop-off Zone successfully");
     	ros::Duration(5.0).sleep();
	 }

  else
     ROS_INFO("Robot failed to reach Drop off location");
    }

  else
    ROS_INFO("Robot failed to reach pick up location for some reason");

  return 0;
}
