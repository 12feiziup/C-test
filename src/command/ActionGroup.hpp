#pragma once

#include <cstdint>
#include <list>

#include "pose/PoseHandler.hpp"

namespace adas {

// 8 种原子操作：所有指令都可以分解为这些原子操作的组合。
enum class ActionType : std::uint16_t {
    FORWARD_1_STEP_ACTION = 0,
    BACKWARD_1_STEP_ACTION,
    TURNLEFT_ACTION,
    REVERSE_TURNLEFT_ACTION,
    TURNRIGHT_ACTION,
    REVERSE_TURNRIGHT_ACTION,
    BE_FAST_ACTION,
    BE_REVERSE_ACTION,
};

// 原子操作集合：负责保存编排结果，并按顺序批量执行。
class ActionGroup final {
public:
    ActionGroup(void) = default;
    explicit ActionGroup(const std::list<ActionType>& actions) noexcept;
    ~ActionGroup(void) = default;

    ActionGroup(const ActionGroup&) noexcept = default;
    ActionGroup& operator=(const ActionGroup&) noexcept = default;

public:
    void PushAction(const ActionType actionType) noexcept;
    void DoOperate(PoseHandler& poseHandler) const noexcept;

private:
    std::list<ActionType> actions;
};

}  // namespace adas
