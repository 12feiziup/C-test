#pragma once

#include "command/ActionGroup.hpp"
#include "pose/PoseHandler.hpp"

namespace adas {

// Command 层：只负责把「一条用户指令 + 当前车辆状态」编排成原子操作列表，
// 不直接修改状态，便于脱离 Executor 独立测试（面向接口编程）。
class MoveCommand final {
public:
    MoveCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

class TurnLeftCommand final {
public:
    TurnLeftCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

class TurnRightCommand final {
public:
    TurnRightCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

class FastCommand final {
public:
    FastCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

}  // namespace adas
