#include "command/Command.hpp"

namespace adas {

namespace {

ActionType MoveActionOf(const PoseHandler& poseHandler) noexcept {
    // 倒车需求（需求 3）落地前只有前进方向。
    (void)poseHandler;
    return ActionType::FORWARD_1_STEP_ACTION;
}

}  // namespace

ActionGroup MoveCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    ActionGroup actionGroup;
    if (poseHandler.IsFast()) {
        actionGroup.PushAction(MoveActionOf(poseHandler));
    }
    actionGroup.PushAction(MoveActionOf(poseHandler));
    return actionGroup;
}

ActionGroup TurnLeftCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    ActionGroup actionGroup;
    if (poseHandler.IsFast()) {
        actionGroup.PushAction(MoveActionOf(poseHandler));
    }
    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
    return actionGroup;
}

ActionGroup TurnRightCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    ActionGroup actionGroup;
    if (poseHandler.IsFast()) {
        actionGroup.PushAction(MoveActionOf(poseHandler));
    }
    actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
    return actionGroup;
}

ActionGroup FastCommand::operator()(const PoseHandler& /* poseHandler */) const noexcept {
    ActionGroup actionGroup;
    actionGroup.PushAction(ActionType::BE_FAST_ACTION);
    return actionGroup;
}

}  // namespace adas
