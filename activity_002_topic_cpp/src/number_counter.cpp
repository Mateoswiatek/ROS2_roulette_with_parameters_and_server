#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

// zrobic node, clienta, kiedy jest równe 9 to dajemy reset. i np zapisujemy ile minęło.

class NumberCounterNode : public rclcpp::Node {
public:
    NumberCounterNode() : Node("number_counter"), counter_(0){
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounterNode::callbackNumber, this, std::placeholders::_1));
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);

        reset_counter_server_ = this->create_service<example_interfaces::srv::SetBool>("reset_counter",
        std::bind(&NumberCounterNode::callbackResetCounter, this,
                   std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Number Counter has been started");
    }

private:
// można by dac w callbacku odrazu wyslanie dalej, ale tak jest bardziej klarowanie. 
// jedna funkcja, jedno zadanie.
    void callbackNumber(const example_interfaces::msg::Int64::SharedPtr msg){
        // RCLCPP_INFO(this->get_logger(), "Przychodzi %ld", msg->data);
        if(msg->data < 4){
            RCLCPP_INFO(this->get_logger(), "You won!, it's %ld", msg->data);
        }
        counter_++;
        publishCount();
    }

    void callbackResetCounter(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                              const example_interfaces::srv::SetBool::Response::SharedPtr response){
        if(request->data){
            this->counter_ = 0;
            response->success = 1;
            response->message = "Done";
        } else {
            response->message = "If you want restart, send data: 1";
            response->success = 0;
        }
        
    }

    void publishCount(){
        auto msg = example_interfaces::msg::Int64();
        msg.data = counter_;
        publisher_->publish(msg);
    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr reset_counter_server_;
    int counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}