#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>

#include <pcl_conversions/pcl_conversions.h>

#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <tf2_ros/transform_listener.h>

#include <boost/foreach.hpp>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
typedef sensor_msgs::PointCloud2 PC2;


ros::Publisher pub;
geometry_msgs::TransformStamped transformToBase_link;


const std::string FRAME_IN  = "camera_depth_optical_frame";
const std::string FRAME_OUT = "camera_link";
const int FREQUENCY = 20;

sensor_msgs::PointCloud2 latestMsg;

pcl::PointCloud<pcl::PointXYZ> transformLocalization(pcl::PointCloud<pcl::PointXYZ> input)
{
    pcl::PointCloud<pcl::PointXYZ> transformed = input; 
    transformed.header.frame_id = FRAME_OUT;

    return transformed;
}

void pc2_callback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
    // printf (cloud_msg.header.frame_id);
    ROS_INFO("req.header.frame_id: [%s]", cloud_msg->header.frame_id.c_str());

    // ROS_INFO(*cloud_msg);
}


void pointcloud_callback(const PointCloud::ConstPtr& msg)
{
    printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);


    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

    // pcl::PCLPointCloud2 pcl_pc2;

    // // pcl_conversions::toPCL(*msg,pcl_pc2);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inliers(new pcl::PointCloud<pcl::PointXYZ>);
    // // do somethings...
     pcl::PCLPointCloud2 cloud_inliers_pcl2;
    // pcl::toPCLPointCloud2(*cloud_inliers, cloud_inliers_pcl2);
    pcl::toPCLPointCloud2(*msg, cloud_inliers_pcl2);

    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (0.0, 1.0);
    pass.filter(*cloud_filtered);
    // cloud_filtered.header.frame_id = FRAME_OUT;
    // pub.publish(transformLocalization(*cloud_filtered));
    
    // pub.publish(*cloud_filtered);
    // apply passthrough filter

    // printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
    // BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points)
    //     printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "ros_hologram_pointcloud");
    ros::NodeHandle nh;
    // ros::Subscriber sub = nh.subscribe<PointCloud>("/camera/depth/color/points", 1, pointcloud_callback);
    ros::Subscriber sub2 = nh.subscribe<PC2>("/camera/depth/color/points", 1, pc2_callback);


    tf2_ros::Buffer tBuffer;
    tf2_ros::TransformListener tf2_listener (tBuffer);

    pub = nh.advertise<PointCloud> ("/hologram/test", 1);

    ros::Rate rate(FREQUENCY);

    while(ros::ok())
    {
        try
        {
            transformToBase_link = tBuffer.lookupTransform(FRAME_OUT, FRAME_IN, ros::Time(0));
        }
        catch(tf2::TransformException e)
        {
            ROS_INFO("%s \n", e.what());
        }

        ros::spinOnce();
        // publishLatest();
        rate.sleep();   
    }

    return 0;

}