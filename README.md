# zcol — Single-header C++23 colored terminal output & logging

A minimal, modern C++ header-only library for colored terminal output and source-location logging.

## Requirements

- C++23 compiler (MSVC 2022 17.6+, GCC 14+, Clang 18+)
- CMake 4.0+ (optional — the header can be used directly)

## Integration

### Option 1: CMake FetchContent (recommended)

```cmake
include(FetchContent)

FetchContent_Declare(
    zcol
    GIT_REPOSITORY https://github.com/<your-org>/zcol.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(zcol)

target_link_libraries(your_target PRIVATE zcol::zcol)
```

### Option 2: Copy the header

Just drop `col_zzj.hpp` into your project and include it.

## Usage

```cpp
#include <col_zzj.hpp>
using namespace zcol::literals;

// One-shot colored print
zcol::println(zcol::Color::Red, "error message");

// RAII scope color guard
{
    zcol::ScopedColor guard(zcol::Color::Blue);
    // terminal is blue within this scope
}

// Log with source location (file:line)
zcol::log("starting process...", zcol::Color::Cyan);

// Deferred log via UDL
auto log = "warning"_log;
log.display();

// UDL shorthand for colored println (yellow)
"hello"_col;

// Low-level
zcol::set_color(zcol::Color::Green);
```

## API

| Function / Class | Description |
|---|---|
| `ansi(Color)` | Get raw ANSI escape code string |
| `set_color(Color)` | Immediately set terminal color |
| `println(Color, string_view)` | One-shot colored println |
| `ScopedColor(Color, restore = Reset)` | RAII: set color, auto-restore on scope exit |
| `log(message, color, source_location)` | One-shot log with file:line prefix |
| `BasicLogger<true/false>` | Template with compile-time toggle |
| `Logger` | Alias for `BasicLogger<log_enabled>` |
| `""_log` | UDL returning a Logger |
| `""_col` | UDL for yellow println shortcut |

## Compile-time disable

Set `zcol::log_enabled` to `false` to eliminate all logging code at compile time.

```cpp
// before including col_zzj.hpp
#define ZCOL_LOG_DISABLE
```

Or directly in code:

```cpp
inline constexpr bool zcol::log_enabled = false;  // now Logger = BasicLogger<false>
```
