#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberPublisherNode : public rclcpp::Node {
public:
    NumberPublisherNode() : Node("number_publisher"){
        this->declare_parameter("ceil_of_random_number", 10);
        this->declare_parameter("publish_frequency", 1.0);
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(
            (int)(1000.0 / this->get_parameter("publish_frequency").as_double())),
            std::bind(&NumberPublisherNode::publishNumer, this));
        RCLCPP_INFO(this->get_logger(), "Number Publisher has been started");
    }

private:
    void publishNumer(){
        auto msg = example_interfaces::msg::Int64();
        msg.data = rand() % this->get_parameter("ceil_of_random_number").as_int();
        publisher_->publish(msg);
    }
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}