#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

#include <boost/foreach.hpp>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

ros::Publisher pub;

void pointcloud_callback(const PointCloud::ConstPtr& msg)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (0.0, 1.0);
    pass.filter (*cloud_filtered);
    
    pub.publish(*cloud_filtered);
    
    // apply passthrough filter

    // printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
    // BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points)
    //     printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "ros_hologram_pointcloud");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe<PointCloud>("/camera/depth/color/points", 1, pointcloud_callback);
  
  pub = nh.advertise<PointCloud> ("/hologram/test", 1);

  ros::spin();
}