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
    if (goal->nth_prime_number == 0)
    {
      RCLCPP_INFO(this->get_logger(), "You must inform a number greater than 0!");
      return rclcpp_action::GoalResponse::REJECT;
    }

    RCLCPP_INFO(this->get_logger(), "Received goal to compute the %d nth prime number", goal->nth_prime_number);
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
  RCLCPP_INFO(this->get_logger(), "Executing goal");
  const auto goal = goal_handle->get_goal();
  auto feedback = std::make_shared<PrimeNumberInterface::Feedback>();
  auto result = std::make_shared<PrimeNumberInterface::Result>();
  
  feedback->current_nth_prime_number = 1;
  feedback->current_number_in_test = 2;
  result->nth_prime_number_value = 2;

  rclcpp::Rate loop_rate(1000); //it is necessary for user receive the complete feedback

  while (rclcpp::ok())
  {
    if (feedback->current_nth_prime_number == goal->nth_prime_number) // no feadback for the first prime number
      break;

    feedback->current_number_in_test++;

    uint8_t number_of_divisions = 0;
    for (uint64_t i = 2; i < feedback->current_number_in_test; i++) //1 and the number i do nmot test
    {
      if (feedback->current_number_in_test % i == 0)
        number_of_divisions++;

      if (number_of_divisions > 1)
        break;
    }

    goal_handle->publish_feedback(feedback);

    if (number_of_divisions == 0) //since I do not test 1 and the number itself, number_of_divisions must be 0
    {
      feedback->current_nth_prime_number++;
      result->nth_prime_number_value = feedback->current_number_in_test;
    }


    if (goal_handle->is_canceling()) {
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
      }

    loop_rate.sleep();
  }
  
  // Check if goal is done
  if (rclcpp::ok())
  {
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "Goal succeeded");
  }
}

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PrimeNumbers>());
  rclcpp::shutdown();
  return 0;
}