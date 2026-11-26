#include <gtest/gtest.h>

#include <cctype>
#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

// 课后综合作业：支持不同的车辆类型。
// 采用数据驱动测试（DDT）把「车辆类型 x 指令 x 期望位姿」的用例表与测试逻辑分离。
namespace adas {
namespace {

struct CarTypeCase {
    CarType carType;
    std::string commands;
    Pose expected;
};

std::string CarTypeName(const CarType carType) {
    switch (carType) {
        case CarType::SPORTS_CAR:
            return "sports_car";
        case CarType::BUS:
            return "bus";
        case CarType::NORMAL:
        default:
            return "normal_car";
    }
}

std::string MakeTestName(const testing::TestParamInfo<CarTypeCase>& info) {
    std::string name = CarTypeName(info.param.carType) + "_" + info.param.commands;
    for (auto& ch : name) {
        if (std::isalnum(static_cast<unsigned char>(ch)) == 0) {
            ch = '_';
        }
    }
    return name;
}

}  // namespace

class ExecutorCarTypeTest : public testing::TestWithParam<CarTypeCase> {};

TEST_P(ExecutorCarTypeTest, should_return_target_pose_given_car_type_and_command) {
    // given
    const auto& param = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, param.carType));

    // when
    executor->Execute(param.commands);

    // then
    ASSERT_EQ(param.expected, executor->Query());
}

INSTANTIATE_TEST_SUITE_P(
    VehicleTypes,
    ExecutorCarTypeTest,
    testing::Values(
        // 默认车辆：M 前进 1 格，L/R 原地转向
        CarTypeCase{CarType::NORMAL, "M", {1, 0, 'E'}},
        CarTypeCase{CarType::NORMAL, "L", {0, 0, 'N'}},
        CarTypeCase{CarType::NORMAL, "R", {0, 0, 'S'}},
        CarTypeCase{CarType::NORMAL, "BM", {-1, 0, 'E'}},
        CarTypeCase{CarType::NORMAL, "BL", {0, 0, 'S'}},
        CarTypeCase{CarType::NORMAL, "BR", {0, 0, 'N'}},
        CarTypeCase{CarType::NORMAL, "FM", {2, 0, 'E'}},
        CarTypeCase{CarType::NORMAL, "FL", {1, 0, 'N'}},
        CarTypeCase{CarType::NORMAL, "FR", {1, 0, 'S'}},
        CarTypeCase{CarType::NORMAL, "BFM", {-2, 0, 'E'}},
        CarTypeCase{CarType::NORMAL, "BFL", {-1, 0, 'S'}},
        CarTypeCase{CarType::NORMAL, "BFR", {-1, 0, 'N'}},

        // 跑车：M 前进 2 格，L/R 先转向再前进 1 格
        CarTypeCase{CarType::SPORTS_CAR, "M", {2, 0, 'E'}},
        CarTypeCase{CarType::SPORTS_CAR, "L", {0, 1, 'N'}},
        CarTypeCase{CarType::SPORTS_CAR, "R", {0, -1, 'S'}},
        CarTypeCase{CarType::SPORTS_CAR, "BM", {-2, 0, 'E'}},
        CarTypeCase{CarType::SPORTS_CAR, "BL", {0, 1, 'S'}},
        CarTypeCase{CarType::SPORTS_CAR, "BR", {0, -1, 'N'}},
        CarTypeCase{CarType::SPORTS_CAR, "FM", {4, 0, 'E'}},
        CarTypeCase{CarType::SPORTS_CAR, "FL", {1, 1, 'N'}},
        CarTypeCase{CarType::SPORTS_CAR, "FR", {1, -1, 'S'}},
        CarTypeCase{CarType::SPORTS_CAR, "BFM", {-4, 0, 'E'}},
        CarTypeCase{CarType::SPORTS_CAR, "BFL", {-1, 1, 'S'}},
        CarTypeCase{CarType::SPORTS_CAR, "BFR", {-1, -1, 'N'}},

        // 公交车：车长 2 格，M 前进 1 格，L/R 先前进 1 格再转向
        CarTypeCase{CarType::BUS, "M", {1, 0, 'E'}},
        CarTypeCase{CarType::BUS, "L", {1, 0, 'N'}},
        CarTypeCase{CarType::BUS, "R", {1, 0, 'S'}},
        CarTypeCase{CarType::BUS, "BM", {-1, 0, 'E'}},
        CarTypeCase{CarType::BUS, "BL", {-1, 0, 'S'}},
        CarTypeCase{CarType::BUS, "BR", {-1, 0, 'N'}},
        CarTypeCase{CarType::BUS, "FM", {2, 0, 'E'}},
        CarTypeCase{CarType::BUS, "FL", {2, 0, 'N'}},
        CarTypeCase{CarType::BUS, "FR", {2, 0, 'S'}},
        CarTypeCase{CarType::BUS, "BFM", {-2, 0, 'E'}},
        CarTypeCase{CarType::BUS, "BFL", {-2, 0, 'S'}},
        CarTypeCase{CarType::BUS, "BFR", {-2, 0, 'N'}}),
    MakeTestName);

}  // namespace adas
