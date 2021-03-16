# Gazebo World
[Project 1](https://classroom.udacity.com/nanodegrees/nd209/parts/a431d446-05df-4641-9e3d-79e1d55a7a2f/modules/469bf8d2-a532-4ce1-b163-7a7b62c81de7/lessons/7dfe4265-e484-4efc-89e7-088540ff6720/concepts/2ab0200c-3c61-4ca6-bfb6-2b33cf81b743) of Udacity's Robotics Software Engineer Nanodegree Program

![World](myworld.jpg)

## Project Overview
In this project we will design a Gazebo World environment by including multiple models.

### Objectives
1. Build a single floor wall structure using the Building Editor tool in Gazebo. Apply at least one feature, one color, and optionally one texture to your structure. Make sure there's enough space between the walls for a robot to navigate.
2. Model any object of your choice using the Model Editor tool in Gazebo. Your model links should be connected with joints.
3. Import your structure and two instances of your model inside an empty Gazebo World.
4. Import at least one model from the Gazebo online library and implement it in your existing Gazebo world.
5. Write a C++ World Plugin to interact with your world. Your code should display “Welcome to Joy’s World!” message as soon as you launch the Gazebo world file.


## Project Description
Directory Structure
```
 .Build-My-World                          
    ├── model                                   
    │   ├── humanoid                    
    │   │   ├── model.config
    │   │   ├── model.sdf
    │   ├── mybuilding                     
    │   │   ├── model.config
    │   │   ├── model.sdf            
    ├── images  
        ├── ...
    ├── script  
        ├── welcome_message.cpp
    ├── world
        ├── myworld.world
    ├── CMakeLists.txt             
    ├── deploy.sh                             
```
## Setup 
---
### Prerequisites
- Linux 16.04
- Gazebo >= 7.0
- ROS Kinetic
- make >= 4.1
- gcc/g++ >= 5.4
---
### Run the project
- Clone the repository
```
$ git clone https://github.com/Joy110900/ROS_ND.git
```
- Initialise a catkin workspace
```
$ mkdir -p /catkin_ws/src
$ cd /catkin/src
$ catkin_init_workspace
```
Copy all folders from cloned repository `ROS_ND/Gazebo_World/` to your catkin workspace `catkin_ws/src` and then build your packages and source repository.
```
$ cd /catkin_ws/src
$ catkin_make
$ souce devel/setup.bash
```

- To launch script and open gazebo  
```
$ cd ./deploy.sh
```