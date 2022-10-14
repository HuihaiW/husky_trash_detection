#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "get_pose/getTrigger.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

std::string s = " ";
float x;
float y;

void get_trigger(const std_msgs::String::ConstPtr& msg){
   s = msg->data.c_str();
   //std::cout << "in function: " << s << std::endl; 
}

void get_pose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
    x = msg->pose.pose.position.x;
    y = msg->pose.pose.position.y;
}

int findIndex(vector<int> &arr, int item){
  for(int i = 0; i < arr.size(); ++i){
    if(arr[i] == item)
      return i;
  }
  return -1;
}

int main(int argc, char **argv){
    int x0 = 0;
    int y0 = 0;
    int x1;
    int y1;
    float oriRes = 1; // orginial resolution
    int new_location;

    vector<int> location; // location of the detected point at resolution of 1m
    vector<int> count; // point count in that location with resolutioin of 1m
    vector<int> mean; // mean of trash count in that location with resolution of 1m

    std::ofstream myFile("/home/huihai/trash_pose.csv");
    std::ofstream my_new_File("/home/huihai/trash_pose_1m.csv");

    ros::init(argc, argv, "recorder");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("trigger", 1, get_trigger);
    ros::Subscriber sub1 = n.subscribe("amcl_pose", 1, get_pose);
    
    while(ros::ok()){
	if(s != "0" && s != " "){
	    cout << s << endl;

	    //calculate the position at resolution of 1m
	    x1 = int((x - x0) * oriRes);
	    y1 = int((y - y0) * oriRes);
	    int row_max = 1000; //assume one row can have 1000 by max
	    new_location = x1 * 1000 + y1 + 1;

	    std::string newline = std::to_string(x) +  " , " + std::to_string(y) + " , " + s + std::to_string(x1) + " , " + std::to_string(y1) + "\n"; 
	    myFile << newline;
	    //check if the new_location is in vector of location
	    //if not, add new location to the end of <location> + add 1 to the end of <count> + add int(s) to the end of <mean>
	    int yes = findIndex(location, new_location);
	    if(yes != -1){
		int sum = count[yes] * mean[yes] + std::stoi(s);
		int new_mean = int(sum / (count[yes] + 1));
		count[yes] += 1;
		mean[yes] = new_mean;
	    }else{
		location.push_back(new_location);
		count.push_back(1);
		mean.push_back(stoi(s));
	    }
	}
	ros::spinOnce();
    }
    myFile.close();

    for (int i = 0; i < location.size(); ++i){
	int loc = location.at(i);
	int new_x = int(loc/1000);
	int new_y = loc - new_x * 1000 - 1;
	string new_line_1 = std::to_string(new_x) + " , " + std::to_string(new_y) + " , "  + std::to_string(mean.at(i)) + "\n";
	my_new_File << new_line_1;
    }
    my_new_File.close();
    return 0;
}
