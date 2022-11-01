

#include "ros/ros.h"
#include <geometry_msgs/PoseArray.h>

ros::Publisher pose_pub;

int main (int argc, char** argv)
{
    // Initialize ROS
    ros::init (argc, argv, "ros_hologram_pointcloud2");
    ros::NodeHandle nh;

    pose_pub = nh.advertise<geometry_msgs::PoseArray> ("/hologram/pointcloud_filtered", 1);
    ros::spin ();

}
