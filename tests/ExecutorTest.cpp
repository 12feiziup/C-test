#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

// 需求 1：基本控制指令（M / L / R）与初始化、查询接口。
namespace adas {
namespace {

constexpr std::int32_t ORIGIN = 0;

std::unique_ptr<Executor> MakeExecutor(const Pose& pose) {
    return std::unique_ptr<Executor>(Executor::NewExecutor(pose));
}

}  // namespace

TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    // then
    const Pose target{ORIGIN, ORIGIN, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_init_pose_when_without_command) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({3, -2, 'W'}));

    // when
    // then
    const Pose target{3, -2, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E) {
    // given
    auto executor = MakeExecutor({0, 0, 'E'});

    // when
    executor->Execute("M");

    // then
    const Pose target{1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W) {
    // given
    auto executor = MakeExecutor({0, 0, 'W'});

    // when
    executor->Execute("M");

    // then
    const Pose target{-1, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N) {
    // given
    auto executor = MakeExecutor({0, 0, 'N'});

    // when
    executor->Execute("M");

    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S) {
    // given
    auto executor = MakeExecutor({0, 0, 'S'});

    // when
    executor->Execute("M");

    // then
    const Pose target{0, -1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E) {
    // given
    auto executor = MakeExecutor({0, 0, 'E'});

    // when
    executor->Execute("L");

    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N) {
    // given
    auto executor = MakeExecutor({0, 0, 'N'});

    // when
    executor->Execute("L");

    // then
    const Pose target{0, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W) {
    // given
    auto executor = MakeExecutor({0, 0, 'W'});

    // when
    executor->Execute("L");

    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_E_given_command_is_L_and_facing_is_S) {
    // given
    auto executor = MakeExecutor({0, 0, 'S'});

    // when
    executor->Execute("L");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_S_given_command_is_R_and_facing_is_E) {
    // given
    auto executor = MakeExecutor({0, 0, 'E'});

    // when
    executor->Execute("R");

    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_R_and_facing_is_S) {
    // given
    auto executor = MakeExecutor({0, 0, 'S'});

    // when
    executor->Execute("R");

    // then
    const Pose target{0, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_N_given_command_is_R_and_facing_is_W) {
    // given
    auto executor = MakeExecutor({0, 0, 'W'});

    // when
    executor->Execute("R");

    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_E_given_command_is_R_and_facing_is_N) {
    // given
    auto executor = MakeExecutor({0, 0, 'N'});

    // when
    executor->Execute("R");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_target_pose_given_batch_command_is_MLMMRM) {
    // given
    auto executor = MakeExecutor({0, 0, 'N'});

    // when
    executor->Execute("MLMMRM");

    // then
    const Pose target{-2, 2, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_target_pose_given_batch_command_is_MMM_and_facing_is_E) {
    // given
    auto executor = MakeExecutor({0, 0, 'E'});

    // when
    executor->Execute("MMM");

    // then
    const Pose target{3, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_init_pose_given_empty_command) {
    // given
    auto executor = MakeExecutor({1, 2, 'S'});

    // when
    executor->Execute("");

    // then
    const Pose target{1, 2, 'S'};
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
