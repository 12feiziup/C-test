#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

// 需求 3：倒车指令 B（M 后退，L/R 左右互换，与 F 可叠加，再次收到 B 取消倒车）。
namespace adas {

TEST(ExecutorReverseTest, should_return_x_minus_1_given_status_is_reverse_command_is_M_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BM");

    // then
    const Pose target{-1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_minus_1_given_status_is_reverse_command_is_M_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    // when
    executor->Execute("BM");

    // then
    const Pose target{0, -1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_x_plus_1_given_status_is_reverse_command_is_M_and_facing_is_W) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    // when
    executor->Execute("BM");

    // then
    const Pose target{1, 0, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_plus_1_given_status_is_reverse_command_is_M_and_facing_is_S) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

    // when
    executor->Execute("BM");

    // then
    const Pose target{0, 1, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_facing_S_given_status_is_reverse_command_is_L_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BL");

    // then
    const Pose target{0, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_facing_N_given_status_is_reverse_command_is_R_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BR");

    // then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_y_plus_1_given_command_is_BBM_and_facing_is_N) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when
    executor->Execute("BBM");

    // then
    const Pose target{0, 1, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_x_minus_2_given_status_is_fast_and_reverse_command_is_M_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFM");

    // then
    const Pose target{-2, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_S_and_x_minus_1_given_status_is_fast_and_reverse_command_is_L_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFL");

    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_N_and_x_minus_1_given_status_is_fast_and_reverse_command_is_R_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BFR");

    // then
    const Pose target{-1, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_S_and_x_minus_1_given_batch_command_is_BML_and_facing_is_E) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("BML");

    // then
    const Pose target{-1, 0, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorReverseTest, should_return_init_pose_given_command_is_BB) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({1, 1, 'E'}));

    // when
    executor->Execute("BB");

    // then
    const Pose target{1, 1, 'E'};
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas
