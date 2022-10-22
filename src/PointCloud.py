#!/usr/bin/env python3

from sensor_msgs.msg import PointCloud2

import rospy

class messageConverter:
    
    def __init__(self):
        rospy.init_node('Hologram_PointCloud', anonymous = True)
        self.pointcloud2_sub = rospy.Subscriber("/camera/depth/color/points", PointCloud2, self.pointcloud_callback)
        self.pointcloud2_pub = rospy.Publisher("/hologram/pointcloud2", PointCloud2, queue_size=1)
        rospy.spin()
        
    def pointcloud_callback(self, data):
        self.pointcloud2_pub.publish(data)
        # print(data)

if __name__ == '__main__':
    converter = messageConverter()