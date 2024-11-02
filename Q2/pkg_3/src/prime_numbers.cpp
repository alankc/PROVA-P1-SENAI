#include "pkg_3/prime_numbers.hpp"

using namespace pkg_3;

PrimeNumbers::PrimeNumbers() : Node("prime_numbers")
{

}

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PrimeNumbers>());
  rclcpp::shutdown();
  return 0;
}