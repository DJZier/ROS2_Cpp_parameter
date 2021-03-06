#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <string>
#include <functional>

using namespace std::chrono_literals;

class ParametersClass: public rclcpp::Node
{
  public:
    ParametersClass()
      : Node("parameter_node")
    {
    //Our parameter has the name my_parameter and is assigned the default value world
      this->declare_parameter<std::string>("my_parameter", "world");
    //timer_ is initialized, which causes the respond function to be executed once a second.
      timer_ = this->create_wall_timer(
      1000ms, std::bind(&ParametersClass::respond, this));
    }
    void respond()
    {
    //our respond function gets the parameter my_parameter from the node, and stores it in parameter_string_
      this->get_parameter("my_parameter", parameter_string_);
    //The RCLCPP_INFO function ensures the message is logged.
      RCLCPP_INFO(this->get_logger(), "Hello %s", parameter_string_.c_str());
    }
  private:
    std::string parameter_string_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
//Here ROS 2 is initialized, and rclcpp::spin starts processing data from the node.
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ParametersClass>());
  rclcpp::shutdown();
  return 0;
}