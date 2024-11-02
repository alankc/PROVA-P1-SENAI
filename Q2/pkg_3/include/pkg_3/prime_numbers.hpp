#ifndef PKG_3__PRIME_NUMBERS_HPP_
#define PKG_3__PRIME_NUMBERS_HPP_

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "q2_interfaces/action/prime_number.hpp"

namespace pkg_3
{
class PrimeNumbers : public rclcpp::Node
{
public:
    using PrimeNumberInterface = q2_interfaces::action::PrimeNumber;
    using GoalHandlePrimeNumber = rclcpp_action::ServerGoalHandle<PrimeNumberInterface>;

    PrimeNumbers();

private:
    rclcpp_action::Server<PrimeNumberInterface>::SharedPtr action_server_;

    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const PrimeNumberInterface::Goal> goal);
    rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandlePrimeNumber> goal_handle);
    void handle_accepted(const std::shared_ptr<GoalHandlePrimeNumber> goal_handle);
    void execute(const std::shared_ptr<GoalHandlePrimeNumber> goal_handle);

};
}  // namespace pkg3
#endif  // PKG_3__PRIME_NUMBERS_HPP_
