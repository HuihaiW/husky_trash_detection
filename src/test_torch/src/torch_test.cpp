#include <torch/torch.h>
#include <iostream>
#include <ros/ros.h>

int main(int argc, char **argv){
    
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    
    torch::Tensor tensor = torch::eye(3);
    std::cout << tensor << std::endl;

    return 0;
}
