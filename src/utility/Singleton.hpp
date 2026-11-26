#pragma once

namespace adas {

// 单体类模板：懒加载 + C++11 起保证的静态局部变量线程安全初始化。
template <typename T>
class Singleton final {
public:
    static T& Instance(void) noexcept {
        static T instance;
        return instance;
    }

    Singleton(void) = delete;
    ~Singleton(void) = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

}  // namespace adas
