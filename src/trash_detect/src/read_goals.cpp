#include <fstream>
#include <ros/ros.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <move_base_msgs/MoveBaseAction.h>
using namespace std;

vector<double> get_data(string path){
    ifstream inFile;
    string x;
    vector<double> x_vector;

    inFile.open(path);
    if(!inFile){
	cout << "Unable to open File";
	exit(1);
    }

    while(inFile >> x){
//	cout << "Read data: " << x << endl;
	if(x == "---") continue;
	else {
//	    cout << "getting data: " << x << endl;
	    double temp = stod(x);
	    x_vector.push_back(temp);
	}
    }

    inFile.close();
    return x_vector;
}


int main(){

    string pathX = "/home/huihai/x.txt";
    string pathY = "/home/huihai/y.txt";
    string pathZ = "/home/huihai/z.txt";
    string pathw = "/home/huihai/w.txt";
    
    vector<double> x_vector;
    vector<double> y_vector;
    vector<double> z_vector;
    vector<double> w_vector;

    x_vector = get_data(pathX);
    y_vector = get_data(pathY);
    z_vector = get_data(pathZ);
    w_vector = get_data(pathW);

    move_base_msgs::MoveBaseGoal goal;

    for(int i = 0; i < x_vector.size()o; i++){

	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = x_vector[i];
	goal.target_pose.pose.position.y = y_vector[i];

	goal.target_pose.pose.orientation.z = z_vector[i];
	goal.target_pose.pose.orientation.w = w_vector[i];

	cout << goal << endl;
	
    }
    return 0;
}

