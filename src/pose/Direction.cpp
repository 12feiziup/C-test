#include "pose/Direction.hpp"

#include <array>
#include <cstddef>

namespace adas {

namespace {

// 索引顺序与左转方向一致：E(0) -> N(1) -> W(2) -> S(3) -> E(0)
constexpr std::array<char, 4> HEADINGS{'E', 'N', 'W', 'S'};
constexpr std::size_t DIRECTION_COUNT = HEADINGS.size();

}  // namespace

const Direction& Direction::GetDirection(const char heading) noexcept {
    static const Direction directions[DIRECTION_COUNT]{
        Direction(0, 'E'),
        Direction(1, 'N'),
        Direction(2, 'W'),
        Direction(3, 'S'),
    };

    for (const auto& direction : directions) {
        if (direction.heading == heading) {
            return direction;
        }
    }

    // 调用者保证朝向合法，这里兜底返回默认朝向 N，避免未定义行为。
    return directions[1];
}

Direction::Direction(const unsigned index, const char heading) noexcept : index(index), heading(heading) {}

const Point& Direction::Move(void) const noexcept {
    static const Point moves[DIRECTION_COUNT]{
        Point(1, 0),   // E
        Point(0, 1),   // N
        Point(-1, 0),  // W
        Point(0, -1),  // S
    };

    return moves[index];
}

const Direction& Direction::LeftOne(void) const noexcept {
    return GetDirection(HEADINGS[(index + 1) % DIRECTION_COUNT]);
}

const Direction& Direction::RightOne(void) const noexcept {
    return GetDirection(HEADINGS[(index + DIRECTION_COUNT - 1) % DIRECTION_COUNT]);
}

char Direction::GetHeading(void) const noexcept {
    return heading;
}

}  // namespace adas
