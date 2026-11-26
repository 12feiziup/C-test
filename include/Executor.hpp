#pragma once

#include <cstdint>
#include <string>

namespace adas {

// 车辆位置与朝向。x 轴为 EW 方向，y 轴为 NS 方向。
struct Pose {
    std::int32_t x;
    std::int32_t y;
    char heading;
};

// Executor 组件对外接口：初始化位置朝向、执行批量指令、查询当前位姿。
class Executor {
public:
    // Caller should delete *executor when it is no longer needed.
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}) noexcept;

public:
    Executor(void) = default;
    virtual ~Executor(void) = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

public:
    virtual void Execute(const std::string& commands) noexcept = 0;
    virtual Pose Query(void) const noexcept = 0;
};

}  // namespace adas
