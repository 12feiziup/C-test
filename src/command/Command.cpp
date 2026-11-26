#include "command/Command.hpp"

namespace adas {

namespace {

ActionType MoveActionOf(const PoseHandler& poseHandler) noexcept {
    return poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
}

// 倒车状态下左右转互换，用「是否左转」与「是否倒车」的异或表达。
ActionType TurnActionOf(const PoseHandler& poseHandler, const bool toLeft) noexcept {
    const bool turnLeft = (toLeft != poseHandler.IsReverse());
    return turnLeft ? ActionType::TURNLEFT_ACTION : ActionType::TURNRIGHT_ACTION;
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
    actionGroup.PushAction(TurnActionOf(poseHandler, true));
    return actionGroup;
}

ActionGroup TurnRightCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    ActionGroup actionGroup;
    if (poseHandler.IsFast()) {
        actionGroup.PushAction(MoveActionOf(poseHandler));
    }
    actionGroup.PushAction(TurnActionOf(poseHandler, false));
    return actionGroup;
}

ActionGroup FastCommand::operator()(const PoseHandler& /* poseHandler */) const noexcept {
    ActionGroup actionGroup;
    actionGroup.PushAction(ActionType::BE_FAST_ACTION);
    return actionGroup;
}

ActionGroup ReverseCommand::operator()(const PoseHandler& /* poseHandler */) const noexcept {
    ActionGroup actionGroup;
    actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
    return actionGroup;
}

ActionGroup TurnRoundCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    // 倒车状态下 TR 指令不生效。
    if (poseHandler.IsReverse()) {
        return ActionGroup();
    }

    ActionGroup actionGroup;

    if (poseHandler.IsFast()) {
        // 加速状态：前进 1 格 -> 左转 -> 前进 1 格 -> 左转
        actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
        actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
        actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
        actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
        return actionGroup;
    }

    // 正常状态：左转 -> 前进 1 格 -> 左转
    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
    actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
    return actionGroup;
}

}  // namespace adas
