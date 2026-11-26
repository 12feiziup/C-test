#include "command/ActionGroup.hpp"

#include <functional>
#include <vector>

namespace adas {

namespace {

using Action = std::function<void(PoseHandler& poseHandler)>;

class ForwardAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        poseHandler.Forward();
    }
};

class TurnLeftAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        poseHandler.TurnLeft();
    }
};

class TurnRightAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        poseHandler.TurnRight();
    }
};

// 原子操作表：下标与 ActionType 的枚举值一一对应，新增原子操作只需扩展此表。
const std::vector<Action>& GetActionTable(void) noexcept {
    static const std::vector<Action> actionTable{
        ForwardAction(),   // FORWARD_1_STEP_ACTION
        TurnLeftAction(),  // TURNLEFT_ACTION
        TurnRightAction(), // TURNRIGHT_ACTION
    };

    return actionTable;
}

}  // namespace

ActionGroup::ActionGroup(const std::list<ActionType>& actions) noexcept : actions(actions) {}

void ActionGroup::PushAction(const ActionType actionType) noexcept {
    actions.push_back(actionType);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept {
    const auto& actionTable = GetActionTable();

    for (const auto actionType : actions) {
        actionTable[static_cast<std::size_t>(actionType)](poseHandler);
    }
}

}  // namespace adas
