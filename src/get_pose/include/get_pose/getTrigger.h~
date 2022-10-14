#ifndef GET_TRIGGER_H
#define GET_TRIGGER_H

#include <std_msgs/String.h>
#include <string>
#include "ros/ros.h"

class getTrigger {
protected:
    ros::Subscriber _sub;
    std::string _trigger;
public:
    getTrigger(ros::NodeHandle &n);
    void receiveTrigger(const std_msgs::String::ConstPtr &t);
    std::string get();
};

#endif
