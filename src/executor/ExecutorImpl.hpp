#pragma once

#include <string>

#include "Executor.hpp"
#include "pose/PoseHandler.hpp"

namespace adas {

// Executor 的唯一实现：持有车辆状态，把指令解析与执行委托给 Command 层。
class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& pose, const CarType carType) noexcept;
    ~ExecutorImpl(void) noexcept = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& commands) noexcept override;
    Pose Query(void) const noexcept override;

private:
    PoseHandler poseHandler;
    CarType carType;
};

}  // namespace adas
