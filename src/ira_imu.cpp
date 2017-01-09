#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h"

double LIN_TH = 0.3; // This is in rad.
double ANG_TH = 0.3; // This is in rad.
double LIN_CMD_VEL = 1.2;
double ANG_CMD_VEL = 1.0;
bool INIT = true;
ros::Publisher g_cmd_pub;

#if 1
void judge_cmd_vel(double roll, double pitch, double yaw)
{
  geometry_msgs::Twist vel_msg;
  vel_msg.linear.x = 0.0;
  vel_msg.linear.y = 0.0;
  vel_msg.linear.z = 0.0;
  vel_msg.angular.x = 0.0;
  vel_msg.angular.y = 0.0;
  vel_msg.angular.z = 0.0;

  // forward, see the pitch
  if(pitch > LIN_TH)
    vel_msg.linear.x = LIN_CMD_VEL;

  // backward, see the pitch
  if(pitch < -LIN_TH)
    vel_msg.linear.x = -LIN_CMD_VEL;

  // turn right, see the roll
  //if(yaw > 0 && yaw < ANG_TH)
  if(roll > ANG_TH)
    vel_msg.angular.z = -ANG_CMD_VEL;

  // turn left, see the roll
  //if(yaw < 0 && yaw > -ANG_TH)
  if(roll < -ANG_TH)
    vel_msg.angular.z = ANG_CMD_VEL;

  g_cmd_pub.publish(vel_msg);

     
}
#endif

void imuCallback(const sensor_msgs::Imu::ConstPtr& inImu)
{
  double qx, qy, qz, qw;
  double roll, pitch, yaw;
  static double h_roll, h_pitch, h_yaw;
  //tf::Quaternion qh;

  qx = inImu -> orientation.x;
  qy = inImu -> orientation.y;
  qz = inImu -> orientation.z;
  qw = inImu -> orientation.w;

  tf::Quaternion q(qx, qy, qz, qw);
  tf::Matrix3x3 m(q);
  m.getRPY(roll, pitch, yaw);
  std::cout << "oRoll: " << roll << ", oPitch: " << pitch << ", oYaw: " << yaw << std::endl;

  judge_cmd_vel(roll, pitch, yaw);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "imu_utility");
  ros::NodeHandle nh;
  ros::Rate r(100);
  ros::Subscriber imuSub = nh.subscribe<sensor_msgs::Imu>("/imu", 1, &imuCallback);
  g_cmd_pub = nh.advertise<geometry_msgs::Twist>("/diff_drive_controller/cmd_vel", 1);
  
  while(ros::ok())
  {
    r.sleep();
    ros::spinOnce();
  }
  return 0;
}
