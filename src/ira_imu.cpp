#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

ros::Publisher pub_imu;

void imuCallback(const sensor_msgs::Imu::ConstPtr& inImu)
{
  ROS_INFO("get imu msg");
  sensor_msgs::Imu outIMU;
  outIMU.angular_velocity.x = inImu->angular_velocity.x;
  outIMU.angular_velocity.y = inImu->angular_velocity.y;
  outIMU.angular_velocity.z = inImu->angular_velocity.z;
  outIMU.angular_velocity_covariance = inImu->angular_velocity_covariance;
  outIMU.linear_acceleration.x = inImu->linear_acceleration.x;
  outIMU.linear_acceleration.y = inImu->linear_acceleration.y;
  outIMU.linear_acceleration.z = inImu->linear_acceleration.z;
  outIMU.linear_acceleration_covariance = inImu->linear_acceleration_covariance;
  outIMU.orientation.x = inImu->orientation.x;
  outIMU.orientation.y = inImu->orientation.y;
  outIMU.orientation.z = inImu->orientation.z;
  outIMU.orientation.w = inImu->orientation.w;
  outIMU.orientation_covariance = inImu->orientation_covariance;
  outIMU.header.stamp = inImu->header.stamp;
  outIMU.header.frame_id = "imu_link";
  outIMU.header.seq = 0;
  pub_imu.publish(outIMU);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "imu_utility");
  ros::NodeHandle nh;
  ros::Rate r(100);
  ros::Subscriber imuSub = nh.subscribe<sensor_msgs::Imu>("/imu", 1, &imuCallback);
  pub_imu = nh.advertise<sensor_msgs::Imu>("/imu_new", 1);
  
  while(ros::ok())
  {
    
    r.sleep();
    ros::spinOnce();
    
  }
  return 0;
}