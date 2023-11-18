#include <ros/ros.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <std_msgs/UInt32.h>
#define pin_a 21
#define pin_b 20
#define pin_c 26
#define pin_d 16
#define pin_dp 19
void print_lcd(int number){
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);
  if(number==0){
    digitalWrite(pin_a, 0);
    digitalWrite(pin_b, 0);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_d, 0);
}
else if(number==1){
    digitalWrite(pin_a, 0);
    digitalWrite(pin_b, 0);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_d, 1);
}
else if(number==2){
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 0);
}
else if(number==3){
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 1);
}
else if(number==4){
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 0);
}
else if(number==5){
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
}
else if(number==6){
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 0);
}
else if(number==7){
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 1);
}
else if(number==8){
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 0);
}
else if(number==9){
    digitalWrite(pin_c, 1);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 0);
    digitalWrite(pin_c, 1);
}

}

void callback(const std_msgs::UInt32::ConstPtr& msg){
  int input=msg->data;
  int first_digit=0;
  int second_digit=0;


ROS_INFO("velocity is : %d", msg->data);
  if(input>=10){
    first_digit=input/10;
    second_digit=input%10;
}
  else{
    first_digit=0;
    second_digit=input;
}
  digitalWrite(pin_dp, 1);
  delay(10);
  print_lcd(first_digit);
  delay(10);
  digitalWrite(pin_dp, 0);
  print_lcd(second_digit);


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "print_lcd");
  ros::NodeHandle nh;
  wiringPiSetupGpio();
  ros::Subscriber sub = nh.subscribe<std_msgs::UInt32>("/detect/velocity", 1, callback);
  

  ROS_INFO("print_lcd : node started...");

  ros::spin();
  return 0;
}

