#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

// 需求 2：加速指令 F（M 前进 2 格，L/R 先前进 1 格再转向，再次收到 F 取消加速）。
namespace adas {

TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("FM");

    // then
    const Pose target{2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_y_plus_2_given_status_is_fast_command_is_M_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("FM");

    // then
    const Pose target{0, 2, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_x_minus_2_given_status_is_fast_command_is_M_and_facing_is_W) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    // when
    executor->Execute("FM");

    // then
    const Pose target{-2, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_y_minus_2_given_status_is_fast_command_is_M_and_facing_is_S) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

    // when
    executor->Execute("FM");

    // then
    const Pose target{0, -2, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("FL");

    // then
    const Pose target{1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_command_is_R_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("FR");

    // then
    const Pose target{1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_W_and_y_plus_1_given_status_is_fast_command_is_L_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("FL");

    // then
    const Pose target{0, 1, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_E_and_y_plus_1_given_status_is_fast_command_is_R_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("FR");

    // then
    const Pose target{0, 1, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->Execute("FFM");

    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_F_and_W_given_command_is_FLFL_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("FLFL");

    // then
    const Pose target{1, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorFastTest, should_return_N_and_x_plus_5_given_batch_command_is_FMML_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("FMML");

    // then
    const Pose target{5, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
