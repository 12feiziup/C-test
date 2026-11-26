#include "command/CmderFactory.hpp"

namespace adas {

namespace {

// TR 由两个字符组成，为了保持「一条指令一个字符」的映射表结构，
// 解析阶段先把 TR 替换为内部指令码 Z。
constexpr char TURN_ROUND_COMMAND_CODE = 'Z';

}  // namespace

CmderFactory::CmderFactory(void) noexcept
    : cmderMap{
          {'M', MoveCommand()},
          {'L', TurnLeftCommand()},
          {'R', TurnRightCommand()},
          {'F', FastCommand()},
          {'B', ReverseCommand()},
          {TURN_ROUND_COMMAND_CODE, TurnRoundCommand()},
      } {}

CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept {
    CmderList cmders;
    for (const auto cmd : ParseCommandString(commands)) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            cmders.push_back(it->second);
        }
    }
    return cmders;
}

std::string CmderFactory::ParseCommandString(std::string_view commands) noexcept {
    std::string result(commands);
    ReplaceAll(result, "TR", std::string_view(&TURN_ROUND_COMMAND_CODE, 1));
    return result;
}

void CmderFactory::ReplaceAll(std::string& inout, std::string_view what, std::string_view with) noexcept {
    if (what.empty()) {
        return;
    }

    for (std::string::size_type pos = 0; (pos = inout.find(what.data(), pos, what.length())) != std::string::npos;
         pos += with.length()) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
}

}  // namespace adas
