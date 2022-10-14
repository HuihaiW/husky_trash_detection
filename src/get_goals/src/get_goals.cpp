#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
using namespace std;

geometry_msgs::PoseWithCovarianceStamped goal;

void get_pose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg){
    goal.header = msg->header;
    goal.pose = msg->pose;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "target");
    ros::NodeHandle n;

    ros::Rate loop_rate(0.025);

    ros::Subscriber sub = n.subscribe("/amcl_pose", 1, get_pose);

    ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("get_targets", 1);

    while (ros::ok()){
	pub.publish(goal);
	ros::spinOnce();
	loop_rate.sleep();
    }

    return 0;

}
