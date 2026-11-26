#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>

#include "command/Command.hpp"

namespace adas {

using Cmder = std::function<ActionGroup(const PoseHandler& poseHandler)>;
using CmderList = std::list<Cmder>;

// 指令工厂：把指令字符串解析为待执行的指令对象列表，是唯一持有「指令 -> 动作」映射的地方。
// 新增指令时只需要在映射表中注册，无需修改 ExecutorImpl。
class CmderFactory final {
public:
    CmderFactory(void) noexcept;
    ~CmderFactory(void) noexcept = default;

    CmderFactory(const CmderFactory&) = delete;
    CmderFactory& operator=(const CmderFactory&) = delete;

public:
    CmderList GetCmders(const std::string& commands, const CarType carType) const noexcept;

private:
    static std::string ParseCommandString(std::string_view commands) noexcept;
    static void ReplaceAll(std::string& inout, std::string_view what, std::string_view with) noexcept;

private:
    static constexpr std::size_t CAR_TYPE_COUNT = 3;
    std::array<std::unordered_map<char, Cmder>, CAR_TYPE_COUNT> cmderMaps;
};

}  // namespace adas
