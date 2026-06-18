#pragma once

#include <print>
#include <string_view>
#include <string>
#include <array>
#include <source_location>
#include <cstdint>

namespace zcol {

// ─── Color ──────────────────────────────────────────────────────

enum class Color : std::uint_fast8_t {
    Reset = 0,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
};

namespace detail {
    inline constexpr std::array<std::string_view, 8> ansi_table = { {
        "\033[0m",  "\033[31m", "\033[32m", "\033[33m",
        "\033[34m", "\033[35m", "\033[36m", "\033[37m",
    } };

    constexpr std::string_view to_ansi(Color c) noexcept {
        return ansi_table[static_cast<std::size_t>(c)];
    }
}

[[nodiscard]] constexpr std::string_view ansi(Color c) noexcept {
    return detail::to_ansi(c);
}

inline void set_color(Color c) noexcept {
    std::print("{}", ansi(c));
}

inline void println(Color c, std::string_view msg) noexcept {
    std::print("{}{}\n", ansi(c), msg);
}

// ─── ScopedColor (RAII) ─────────────────────────────────────────

class ScopedColor {
    std::string_view m_restore;
public:
    ScopedColor() = delete;
    ScopedColor(ScopedColor const&) = delete;
    ScopedColor& operator=(ScopedColor const&) = delete;
    ScopedColor(ScopedColor&&) = delete;
    ScopedColor& operator=(ScopedColor&&) = delete;

    explicit ScopedColor(Color c, Color restore = Color::Reset) noexcept
        : m_restore(ansi(restore))
    {
        set_color(c);
    }

    ~ScopedColor() {
        std::print("{}", m_restore);
    }
};

// ─── Logger ──────────────────────────────────────────────────────

#ifndef ZCOL_LOG_ENABLED
#  define ZCOL_LOG_ENABLED 1
#endif
inline constexpr bool log_enabled = static_cast<bool>(ZCOL_LOG_ENABLED);

template <bool E>
class BasicLogger;

template <>
class BasicLogger<false> {
public:
    BasicLogger(std::string_view, Color = Color::Yellow,
                std::source_location const& = std::source_location::current()) noexcept {}
    void display() const noexcept {}
};

template <>
class BasicLogger<true> {
    std::string m_msg;
    Color m_color;
public:
    BasicLogger(std::string_view message,
                Color c = Color::Yellow,
                std::source_location const& loc = std::source_location::current())
        : m_msg(std::format("[{}:{}] {}", loc.file_name(), loc.line(), message)),
          m_color(c)
    {}

    void display() const {
        std::print("{}{}\n", ansi(m_color), m_msg);
    }
};

using Logger = BasicLogger<log_enabled>;

inline void log(std::string_view message,
                Color c = Color::Yellow,
                std::source_location const& loc = std::source_location::current())
{
    std::print("{}{}\n", ansi(c),
               std::format("[{}:{}] {}", loc.file_name(), loc.line(), message));
}

// ─── Literals ────────────────────────────────────────────────────

inline namespace literals {
    inline Logger operator""_log(char const* s, std::size_t len) {
        return Logger{std::string_view(s, len)};
    }

    inline void operator""_col(char const* s, std::size_t len) {
        println(Color::Yellow, std::string_view(s, len));
    }
}

} // namespace zcol
