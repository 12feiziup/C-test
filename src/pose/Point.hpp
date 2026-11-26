#pragma once

#include <cstdint>

namespace adas {

// 二维平面上的整数坐标点，封装 4 个方向上的位置增量模型。
class Point final {
public:
    Point(const std::int32_t x, const std::int32_t y) noexcept;
    Point(const Point& rhs) noexcept;
    Point& operator=(const Point& rhs) noexcept;
    Point& operator+=(const Point& rhs) noexcept;
    Point& operator-=(const Point& rhs) noexcept;

public:
    std::int32_t GetX(void) const noexcept;
    std::int32_t GetY(void) const noexcept;

private:
    std::int32_t x;
    std::int32_t y;
};

}  // namespace adas
