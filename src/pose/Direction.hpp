#pragma once

#include "pose/Point.hpp"

namespace adas {

// 朝向抽象：把 4 个朝向统一为「索引 + 单位位移向量 + 左右旋转」，消除 4 分支的 if/else。
class Direction final {
public:
    static const Direction& GetDirection(const char heading) noexcept;

public:
    Direction(const unsigned index, const char heading) noexcept;

public:
    const Point& Move(void) const noexcept;
    const Direction& LeftOne(void) const noexcept;
    const Direction& RightOne(void) const noexcept;
    char GetHeading(void) const noexcept;

private:
    unsigned index;
    char heading;
};

}  // namespace adas
