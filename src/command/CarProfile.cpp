#include "command/CarProfile.hpp"

namespace adas {

const CarProfile& GetCarProfile(const CarType carType) noexcept {
    // 默认车辆：M 前进 1 格，L/R 原地转向。
    static const CarProfile normalProfile{1, TurnPattern{0, 0}, TurnPattern{0, 0}};

    // 跑车：M 前进 2 格，L/R 先转向再前进 1 格。
    static const CarProfile sportsCarProfile{2, TurnPattern{0, 1}, TurnPattern{0, 1}};

    // 公交车：车长 2 格，M 前进 1 格，L/R 先前进 1 格再转向。
    static const CarProfile busProfile{1, TurnPattern{1, 0}, TurnPattern{1, 0}};

    switch (carType) {
        case CarType::SPORTS_CAR:
            return sportsCarProfile;
        case CarType::BUS:
            return busProfile;
        case CarType::NORMAL:
        default:
            return normalProfile;
    }
}

}  // namespace adas
