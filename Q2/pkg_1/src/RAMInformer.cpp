#include "pkg_1/RAMInformer.hpp"

#include <fstream>
#include <string>

using namespace pkg_1;

RAMInformer::RAMInformer() : Node("ram_informer")
{   
    this->declare_parameter<std::string>("use_mem_free_as", "MemAvailable");

    std::string use_mem_free_as;
    this->get_parameter("use_mem_free_as", use_mem_free_as);
    if (use_mem_free_as != "MemAvailable" && use_mem_free_as != "MemFree")
    {
        use_mem_free_as = "MemAvailable";
    }

    mem_total_ = "MemTotal";
    mem_free_ = use_mem_free_as;

    RCLCPP_INFO(this->get_logger(), "Total memory from: %s", mem_total_.c_str());
    RCLCPP_INFO(this->get_logger(), "Memory free from: %s", mem_free_.c_str());

    pub_ = this->create_publisher<q2_interfaces::msg::Pkg1Interface>("/ram_informer", rclcpp::QoS(rclcpp::SystemDefaultsQoS()));
    timer_ = this->create_wall_timer(
        std::chrono::seconds(1),
        std::bind(&RAMInformer::publish_info_timer_callback, this));
}

void RAMInformer::publish_info_timer_callback()
{
    q2_interfaces::msg::Pkg1Interface msg;
    msg.mem_total = 0;
    msg.mem_used = 0;
    msg.percentage_in_use = 0;

    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open()) {
        RCLCPP_ERROR(this->get_logger(), "Failed to access /proc/meminfo!");
        return;
    }

    std::string line;
    // It will be aways in this sequence:
    // MemTotal:       32595704 kB
    // MemFree:        16161388 kB
    // MemAvailable:   25362356 kB

    while (std::getline(meminfo, line))
    {
        if (line.find(mem_total_) == 0)
            msg.mem_total  = parse_mem_info(line);

        if (line.find(mem_free_) == 0)
        {
            msg.mem_used  = msg.mem_total  - parse_mem_info(line);
            break;
        }
    }
    
    meminfo.close();

    msg.percentage_in_use = 100.0 * std::round(1000.0 * msg.mem_used / msg.mem_total) / 1000.0;

    pub_->publish(msg);
}

double RAMInformer::parse_mem_info(std::string line)
{
    auto delimiter_begin = line.find(':') + 1;
    auto delimiter_end = line.find("kB");
    double value_in_kB = std::stod(line.substr(delimiter_begin, delimiter_end));

    double value_in_GB = (value_in_kB / 1024.0) / 1024.0;
    return value_in_GB;
}


int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RAMInformer>());
  rclcpp::shutdown();
  return 0;
}