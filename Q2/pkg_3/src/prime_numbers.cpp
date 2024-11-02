#include "pkg_3/prime_numbers.hpp"

using namespace pkg_3;

PrimeNumbers::PrimeNumbers() : Node("prime_numbers")
{
  using namespace std::placeholders;

    this->action_server_ = rclcpp_action::create_server<PrimeNumberInterface>(
      this,
      "/prime_number",
      std::bind(&PrimeNumbers::handle_goal, this, _1, _2),
      std::bind(&PrimeNumbers::handle_cancel, this, _1),
      std::bind(&PrimeNumbers::handle_accepted, this, _1));
}

rclcpp_action::GoalResponse PrimeNumbers::handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const PrimeNumberInterface::Goal> goal)
{
    RCLCPP_INFO(this->get_logger(), "Received goal to compute %d nth prime number", goal->nth_prime_number);
    (void)uuid;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse PrimeNumbers::handle_cancel(const std::shared_ptr<GoalHandlePrimeNumber> goal_handle)
{
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
}

void PrimeNumbers::handle_accepted(const std::shared_ptr<GoalHandlePrimeNumber> goal_handle)
{
    using namespace std::placeholders;
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&PrimeNumbers::execute, this, _1), goal_handle}.detach();
}

void PrimeNumbers::execute(const std::shared_ptr<GoalHandlePrimeNumber> goal_handle)
{

}

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PrimeNumbers>());
  rclcpp::shutdown();
  return 0;
}