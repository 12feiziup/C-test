#pragma once

#include "Executor.hpp"
#include "pose/Direction.hpp"
#include "pose/Point.hpp"

namespace adas {

// 车辆状态容器：位置、朝向，以及加速(F)/倒车(B) 两个可叠加的状态位。
class PoseHandler final {
public:
    explicit PoseHandler(const Pose& pose) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    void Forward(void) noexcept;
    void Backward(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Fast(void) noexcept;
    void Reverse(void) noexcept;

    bool IsFast(void) const noexcept;
    bool IsReverse(void) const noexcept;
    Pose Query(void) const noexcept;

private:
    Point point;
    const Direction* facing;
    bool fast{false};
    bool reverse{false};
};

}  // namespace adas
