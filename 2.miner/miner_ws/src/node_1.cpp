#include "rclcpp/rclcpp.hpp"
#include "miner_cpp/src/miner_ros2_interfaces"  // 包含自定义消息

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("mining_world_node");

    auto mineral_pub = node->create_publisher<your_package_name::msg::Mineral>("mineral_info", 10);

    rclcpp::Rate rate(1);  // 每秒发布一次矿石信息

    while (rclcpp::ok()) {
        auto mineral_msg = std::make_unique<your_package_name::msg::Mineral>();
        mineral_msg->type = "gold";
        mineral_msg->value = 100.0;

        mineral_pub->publish(std::move(mineral_msg));
        rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
