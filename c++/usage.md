# whenwords for C++17

人类友好的时间格式化和解析库。

## 安装

将 `src/whenwords.h` 和 `src/whenwords.cpp` 复制到您的项目中，然后编译：

```bash
mkdir build && cd build
cmake ..
make
./test_whenwords
```

## 快速开始

```cpp
#include "whenwords.h"
#include <iostream>

int main() {
    // 当前时间（Unix 时间戳）
    int64_t now = 1704067200; // 2024-01-01 00:00:00 UTC
    
    std::cout << "Time ago: " << whenwords::timeago(1704067110, now) << std::endl;
    std::cout << "Duration: " << whenwords::duration(3661) << std::endl;
    std::cout << "Parse: '2h30m': " << whenwords::parse_duration("2h30m") << std::endl;
    std::cout << "Human date: " << whenwords::human_date(1705190400, now) << std::endl;
    std::cout << "Date range: " << whenwords::date_range(1705276800, 1705363200) << std::endl;
    
    return 0;
}
```

## 函数

### timeago(timestamp, reference?) → string

返回人类可读的相对时间字符串。

**签名：**
```cpp
std::string timeago(int64_t timestamp, int64_t reference = -1);
std::string timeago(double timestamp, double reference = -1);
std::string timeago(const std::string& timestamp, const std::string& reference = "");
```

**参数：**
- `timestamp`：Unix 时间戳（自 1970-01-01 UTC 以来的秒数）
- `reference`：可选的参考时间戳。如果省略，默认为 timestamp

**返回值：** 人类可读的字符串

**示例：**
```cpp
auto result = whenwords::timeago(1704067110, 1704067200);
// result: "2 minutes ago"

auto result = whenwords::timeago(1704067260, 1704067200);
// result: "in 1 minute"
```

### duration(seconds, options?) → string

格式化时长（不相对于当前时间）。

**签名：**
```cpp
std::string duration(double seconds, const DurationOptions& options = DurationOptions());
```

**参数：**
- `seconds`：非负的秒数
- `options`：可选的 `DurationOptions` 结构体
  - `compact`：bool（默认 false）- 使用 "2h 30m" 风格
  - `max_units`：int（默认 2）- 显示的最大单位数

**返回值：** 格式化的时长字符串

**示例：**
```cpp
auto result = whenwords::duration(3661);
// result: "1 hour, 1 minute"

auto result = whenwords::duration(3661, {true, 2});
// result: "1h 1m"

auto result = whenwords::duration(3661, {false, 1});
// result: "1 hour"
```

### parse_duration(string) → int64_t

将人类编写的时长字符串解析为秒数。

**签名：**
```cpp
int64_t parse_duration(const std::string& input);
```

**参数：**
- `input`：时长字符串（如 "2h 30m"、"2 hours 30 minutes"）

**返回值：** 时长秒数

**抛出：** 如果输入为空、无单位或为负数，抛出 `ParseError`

**接受的格式：**
- 紧凑格式："2h30m"、"2h 30m"、"2h, 30m"
- 详细格式："2 hours 30 minutes"、"2 hours and 30 minutes"
- 小数格式："2.5 hours"、"1.5h"
- 冒号格式："2:30"（h:mm）、"1:30:00"（h:mm:ss）

**示例：**
```cpp
auto result = whenwords::parse_duration("2h 30m");
// result: 9000

auto result = whenwords::parse_duration("2 hours and 30 minutes");
// result: 9000

auto result = whenwords::parse_duration("2:30");
// result: 9000
```

### human_date(timestamp, reference?) → string

返回上下文相关的日期字符串。

**签名：**
```cpp
std::string human_date(int64_t timestamp, int64_t reference = -1);
std::string human_date(double timestamp, double reference = -1);
std::string human_date(const std::string& timestamp, const std::string& reference = "");
```

**参数：**
- `timestamp`：要格式化的日期
- `reference`：用于比较的"当前"日期

**返回值：** 上下文相关的日期字符串，如 "Today"、"Yesterday"、"Last Friday"、"January 15"

**示例：**
```cpp
auto result = whenwords::human_date(1705190400, 1705276800);
// result: "Yesterday"

auto result = whenwords::human_date(1705104000, 1705276800);
// result: "Last Saturday"
```

### date_range(start, end) → string

格式化日期范围，智能缩写。

**签名：**
```cpp
std::string date_range(int64_t start, int64_t end);
std::string date_range(double start, double end);
std::string date_range(const std::string& start, const std::string& end);
```

**参数：**
- `start`：开始时间戳
- `end`：结束时间戳

**返回值：** 格式化的日期范围字符串

**示例：**
```cpp
auto result = whenwords::date_range(1705276800, 1705276800);
// result: "January 15, 2024"

auto result = whenwords::date_range(1705276800, 1705363200);
// result: "January 15–16, 2024"

auto result = whenwords::date_range(1705276800, 1707955200);
// result: "January 15 – February 15, 2024"
```

## 错误处理

对于无效输入，库会抛出 `ParseError`。

**示例：**
```cpp
try {
    whenwords::parse_duration("invalid");
} catch (const whenwords::ParseError& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

## 构建说明

```bash
mkdir build && cd build
cmake ..
make
./test_whenwords
```

## 许可证

MIT License
