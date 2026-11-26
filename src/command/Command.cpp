#include "command/Command.hpp"

namespace adas {

ActionGroup MoveCommand::operator()(const PoseHandler& /* poseHandler */) const noexcept {
    ActionGroup actionGroup;
    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
    return actionGroup;
}

ActionGroup TurnLeftCommand::operator()(const PoseHandler& /* poseHandler */) const noexcept {
    ActionGroup actionGroup;
    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
    return actionGroup;
}

ActionGroup TurnRightCommand::operator()(const PoseHandler& /* poseHandler */) const noexcept {
    ActionGroup actionGroup;
    actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
    return actionGroup;
}

}  // namespace adas
