#include "get_pose/getTrigger.h"

getTrigger::getTrigger(ros::NodeHandle &n){
    _trigger = "0";
    _sub = n.subscribe("/trigger", 1, &getTrigger::receiveTrigger, this);
}

void getTrigger::receiveTrigger(const std_msgs::String::ConstPtr &t){
   this-> _trigger = t->data.c_str();
}
std::string getTrigger::get(){
    return _trigger;
}
