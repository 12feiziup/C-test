#include "command/Command.hpp"

#include <cstddef>

namespace adas {

namespace {

ActionType MoveActionOf(const PoseHandler& poseHandler) noexcept {
    return poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
}

void PushMoves(ActionGroup& actionGroup, const ActionType moveAction, const std::size_t count) noexcept {
    for (std::size_t i = 0; i < count; ++i) {
        actionGroup.PushAction(moveAction);
    }
}

// 转向指令的通用编排：转向前移动 -> 转向 -> 转向后移动。
// 倒车状态下移动方向取反，且左右转互换；加速状态下转向前多移动 1 格。
ActionGroup MakeTurnActionGroup(const PoseHandler& poseHandler,
                                const TurnPattern& turnPattern,
                                const bool toLeft) noexcept {
    const auto moveAction = MoveActionOf(poseHandler);
    const bool turnLeft = (toLeft != poseHandler.IsReverse());
    const auto turnAction = turnLeft ? ActionType::TURNLEFT_ACTION : ActionType::TURNRIGHT_ACTION;

    const std::size_t movesBeforeTurn = turnPattern.movesBeforeTurn + (poseHandler.IsFast() ? 1U : 0U);

    ActionGroup actionGroup;
    PushMoves(actionGroup, moveAction, movesBeforeTurn);
    actionGroup.PushAction(turnAction);
    PushMoves(actionGroup, moveAction, turnPattern.movesAfterTurn);
    return actionGroup;
}

}  // namespace

MoveCommand::MoveCommand(const CarProfile& profile) noexcept : profile(profile) {}

ActionGroup MoveCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    const std::size_t steps = profile.stepsPerMove * (poseHandler.IsFast() ? 2U : 1U);

    ActionGroup actionGroup;
    PushMoves(actionGroup, MoveActionOf(poseHandler), steps);
    return actionGroup;
}

TurnLeftCommand::TurnLeftCommand(const CarProfile& profile) noexcept : profile(profile) {}

ActionGroup TurnLeftCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    return MakeTurnActionGroup(poseHandler, profile.leftTurn, true);
}

TurnRightCommand::TurnRightCommand(const CarProfile& profile) noexcept : profile(profile) {}

ActionGroup TurnRightCommand::operator()(const PoseHandler& poseHandler) const noexcept {
    return MakeTurnActionGroup(poseHandler, profile.rightTurn, false);
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
