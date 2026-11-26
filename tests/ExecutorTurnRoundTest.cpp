#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

// 需求 4：掉头指令 TR（左转 -> 前进 1 格 -> 左转，不受 B 影响，受 F 影响）。
namespace adas {

TEST(ExecutorTurnRoundTest, should_normal_tr_build_left_forward_left_and_facing_is_W) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("TR");

    // then
    const Pose target{0, 1, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_normal_tr_build_left_forward_left_and_facing_is_S) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("TR");

    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_fast_tr_build_forward_left_forward_left) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("FTR");

    // then
    const Pose target{1, 1, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_fast_tr_build_forward_left_forward_left_and_facing_is_S) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("FTR");

    // then
    const Pose target{-1, 1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_return_init_pose_given_status_is_reverse_command_is_TR) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BTR");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_return_init_pose_given_status_is_reverse_and_fast_command_is_TR) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFTR");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_return_init_pose_given_command_is_TRTR) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("TRTR");

    // then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_return_target_pose_given_batch_command_is_TRM) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("TRM");

    // then
    const Pose target{-1, 1, 'W'};
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
