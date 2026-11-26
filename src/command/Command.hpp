#pragma once

#include "command/ActionGroup.hpp"
#include "command/CarProfile.hpp"
#include "pose/PoseHandler.hpp"

namespace adas {

// Command 层：只负责把「一条用户指令 + 当前车辆状态」编排成原子操作列表，
// 不直接修改状态，便于脱离 Executor 独立测试（面向接口编程）。
class MoveCommand final {
public:
    explicit MoveCommand(const CarProfile& profile) noexcept;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;

private:
    const CarProfile& profile;
};

class TurnLeftCommand final {
public:
    explicit TurnLeftCommand(const CarProfile& profile) noexcept;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;

private:
    const CarProfile& profile;
};

class TurnRightCommand final {
public:
    explicit TurnRightCommand(const CarProfile& profile) noexcept;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;

private:
    const CarProfile& profile;
};

class FastCommand final {
public:
    FastCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

class ReverseCommand final {
public:
    ReverseCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

class TurnRoundCommand final {
public:
    TurnRoundCommand(void) noexcept = default;

public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept;
};

}  // namespace adas
