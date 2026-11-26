#pragma once

#include <cstdint>

#include "Executor.hpp"

namespace adas {

// 车辆转向时的底盘动作模式：转向前、转向后各需要移动几格。
struct TurnPattern final {
    std::uint8_t movesBeforeTurn{0};
    std::uint8_t movesAfterTurn{0};
};

// 不同车辆类型的运动学参数：一次 M 移动几格，左右转时前后各移动几格。
// 加速状态下 M 的步数翻倍、转向前的步数 +1，倒车状态下移动方向取反、转向方向取反。
struct CarProfile final {
    std::uint8_t stepsPerMove{1};
    TurnPattern leftTurn{};
    TurnPattern rightTurn{};
};

const CarProfile& GetCarProfile(const CarType carType) noexcept;

}  // namespace adas
