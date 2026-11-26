#include "pose/Point.hpp"

namespace adas {

Point::Point(const std::int32_t x, const std::int32_t y) noexcept : x(x), y(y) {}

Point::Point(const Point& rhs) noexcept = default;
Point& Point::operator=(const Point& rhs) noexcept = default;

Point& Point::operator+=(const Point& rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Point& Point::operator-=(const Point& rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

std::int32_t Point::GetX(void) const noexcept {
    return x;
}

std::int32_t Point::GetY(void) const noexcept {
    return y;
}

}  // namespace adas
