#include <ros/ros.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <std_msgs/UInt32.h>
#define buzzer_pin 18
void callback(const std_msgs::UInt32::ConstPtr& msg){
  int input=msg->data;
  int pulse=0;
  ROS_INFO("received %d", msg->data);
  pinMode(buzzer_pin, OUTPUT);
  softPwmCreate(buzzer_pin, 0, 20000);
  if(input>160){
   ROS_INFO("PRINT 1\n");
   digitalWrite(buzzer_pin, 1);
}
  else if(input >80 && input < 160){
    pulse=input*10000/255;

    softPwmCreate(buzzer_pin,0,10000);
    softPwmWrite(buzzer_pin, pulse);
    ROS_INFO("PRINT %d/10000\n", pulse);
}
  else{
    softPwmCreate(buzzer_pin,0,10000);
    softPwmWrite(buzzer_pin, 100);
}
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "endanger_buzzer");
  ros::NodeHandle nh;
  wiringPiSetupGpio();
  ros::Subscriber sub = nh.subscribe<std_msgs::UInt32>("/detect/danger_topic", 1, callback);
  

  ROS_INFO("endanger_buzzer : node started...");

  ros::spin();
  return 0;
}

