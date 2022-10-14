#include "ros/ros.h"
#include "std_msgs/String.h"
// include "geometry_msgs/PoseWithCovarianceStamped"
#include "get_pose/getTrigger.h"
#include <string>
#include <iostream>

int main(int argc, char **argv){
    ros::init(argc, argv, "recorder");
    ros::NodeHandle n;
    getTrigger receiver(n);
    while (ros::ok()){
        std::string s = receiver.get();
        //ROS_INFO(s);
        std::cout << s << std::endl;
    }
    return 0;
}
