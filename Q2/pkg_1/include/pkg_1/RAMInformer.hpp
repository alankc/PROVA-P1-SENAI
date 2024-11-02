#ifndef PKG_1_RAMInformer_HPP_
#define PKG_1_RAMInformer_HPP_

#include "rclcpp/rclcpp.hpp"
#include "q2_interfaces/msg/pkg1_interface.hpp"

namespace pkg_1
{
class RAMInformer : public rclcpp::Node
{
public:
    RAMInformer();

private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<q2_interfaces::msg::Pkg1Interface>::SharedPtr pub_;
    void publish_info_timer_callback();
    double parse_mem_info(std::string line);

    std::string mem_total_;
    std::string mem_free_;

};
}  // namespace pkg1
#endif  // PKG_1_RAMInformer_HPP_
