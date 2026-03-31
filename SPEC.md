# whenwords 规范 v0.1.0

## 概述

whenwords 是一个用于人类友好时间格式化和解析的库。它将时间戳转换为可读字符串如 "3 hours ago"，并将时长字符串如 "2h 30m" 解析为秒数。

所有函数都是纯函数——无副作用、无 I/O、无系统时钟访问。参考时间戳始终显式传递。

## 设计原则

1. **仅纯函数。** 无副作用、无系统时钟访问、无 I/O。当前时间始终显式传递。

2. **时间戳为 Unix 秒。** 内部所有函数使用 Unix 时间戳（自 1970-01-01 UTC 以来的秒数）。实现也应接受语言原生 datetime 类型以方便使用。

3. **字符串为 UTF-8。** 所有字符串输入和输出均为 UTF-8 编码。

4. **仅英语（v0.1）。** 此版本仅输出英语字符串。未来版本可能添加区域设置支持。除非规范明确定义，否则不要实现 i18n。

5. **确定性。** 给定相同输入，函数始终返回相同输出。无随机性、无环境依赖行为。

---

## 输出结构

生成使用和测试库所需的最小文件集。不要创建包分发脚手架。

**要生成：**
- 库源文件
- 测试文件
- usage.md

**不要生成：**
- setup.py、pyproject.toml 及构建/发布元数据（Python）
- 可发布的 Cargo.toml 字段如 description、license、repository、keywords（Rust——仅保留 `[package]` name、version、edition）
- 包含发布配置的 package.json（Node）
- gemspec 文件（Ruby）
- 指向仓库的模块路径的 go.mod（Go——使用简单的本地模块名）
- 任何 CI/CD 配置、GitHub Actions 等

目标是可复制到项目中的可用实现，而非可发布的包。

---

## 类型约定

由于此规范面向多种语言，类型以抽象方式描述：

| 规范类型 | 含义 | 示例 |
|-----------|---------|----------|
| `timestamp` | Unix 秒（整数或浮点数）或 ISO 8601 字符串或语言原生 datetime | `1704067200`、`"2024-01-01T00:00:00Z"`、`Date`、`datetime` |
| `number` | 适当的整数或浮点数 | `3600`、`3600.5` |
| `string` | UTF-8 文本 | `"2 hours ago"` |
| `options` | 语言惯用的选项对象 | `{compact: true}`、`Options { compact: true }` |
| `error` | 语言惯用的错误 | `ValueError`、`Err(...)`、`null`、`throw` |

### 时间戳规范化

当函数接收 `timestamp` 时：
1. 如果是整数/浮点数：视为 Unix 秒
2. 如果是 ISO 8601 字符串：解析为 Unix 秒（无效则报错）
3. 如果是语言原生 datetime：转换为 Unix 秒

如果明确记录，实现可以接受毫秒，但规范测试用例使用秒。

---

## 错误处理

错误应以目标语言的惯用方式报告：

| 语言 | 错误风格 |
|----------|-------------|
| Python | 抛出带描述性消息的 `ValueError` |
| TypeScript | 抛出 `Error` 或返回 `null`（记录选择哪种） |
| Rust | 返回 `Result<T, ParseError>` |
| Go | 返回 `(value, error)` 元组 |
| Java | 抛出 `IllegalArgumentException` |

**各函数的错误条件：**

| 函数 | 错误条件 |
|----------|------------|
| `timeago` | 无效时间戳格式 |
| `duration` | 负秒数、NaN、无限 |
| `parse_duration` | 空字符串、无法解析的输入、负结果 |
| `human_date` | 无效时间戳格式 |
| `date_range` | 无效时间戳格式 |

如有疑问，输入要宽松（接受合理的变体），输出要严格（始终返回符合规范的字符串）。

---

## 时区处理

**对于相对函数（`timeago`、`duration`、`parse_duration`）：** 时区无关紧要。这些函数操作时间戳之间的时长。

**对于日历函数（`human_date`、`date_range`）：**
- 时间戳是时间瞬间（UTC）
- 输出取决于该瞬间落在哪个日历日
- 默认在 **UTC** 中解释时间戳
- 实现可以添加可选的 `timezone` 参数
- 如果添加时区支持，使用 IANA 时区名称（`America/New_York`）

规范测试假设 UTC。支持时区的实现在使用 UTC 时仍必须通过所有规范测试。

---

## 舍入和边界

### timeago 阈值

阈值使用 `>=` 在下界进行评估：

```
0 <= diff < 45 秒     → "just now"
45 <= diff < 90 秒    → "1 minute ago"
90 秒 <= diff < 45 分钟 → "{n} minutes ago" （舍入）
...
```

计算 `n` 时，舍入到最接近的整数。使用四舍五入（2.5 → 3，2.4 → 2）。

### duration 舍入

当 `max_units` 截断输出时，舍入最小显示单位：
- `duration(3659)` 使用默认 max_units=2 → "1 hour"（59 秒向下舍入）
- `duration(3690)` 使用 max_units=1 → "1 hour"（90 秒 = 1.5 分钟，舍入为 2，但我们只显示小时，舍入为 1）

舍入应用于*显示*，而非中间计算。

### 复数形式

- 1 个任何单位：单数形式（"1 minute"、"1 hour"、"1 day"）
- 0 或 2+ 个任何单位：复数形式（"0 seconds"、"2 minutes"、"5 hours"）

---

## 函数

### timeago(timestamp, reference?) → string

返回人类可读的相对时间字符串。

**参数：**
- `timestamp`：Unix 时间戳（秒）或 ISO 8601 字符串
- `reference`：可选。如果省略，默认为 `timestamp`（返回 "just now"）。实际使用中，调用者传递当前时间。

**行为：**

| 条件 | 输出 |
|-----------|--------|
| 0–44 秒 | "just now" |
| 45–89 秒 | "1 minute ago" |
| 90 秒 – 44 分钟 | "{n} minutes ago" |
| 45–89 分钟 | "1 hour ago" |
| 90 分钟 – 21 小时 | "{n} hours ago" |
| 22–35 小时 | "1 day ago" |
| 36 小时 – 25 天 | "{n} days ago" |
| 26–45 天 | "1 month ago" |
| 46 天 – 319 天 | "{n} months ago" |
| 320–547 天 | "1 year ago" |
| 548+ 天 | "{n} years ago" |

未来时间使用 "in {n} {units}" 而非 "{n} {units} ago"。

**理由：** 阈值的选择使输出永远不会让人感觉错误。"2 days ago" 不应该描述 47 小时前的事物（感觉像昨天）。45 秒的 "just now" 窗口防止 UI 抖动显示 "1 second ago"。

**边界情况：**
- 相同时间戳 → "just now"
- 负差值（未来）→ "in 3 hours"
- 非常大的值 → 以年为单位上限，无溢出

---

### duration(seconds, options?) → string

格式化时长（不相对于现在）。

**参数：**
- `seconds`：非负数
- `options`：包含可选字段的对象：
  - `compact`：布尔值（默认 false）。如果为 true，使用 "2h 34m" 风格。
  - `max_units`：整数（默认 2）。显示的最大单位数。

**行为：**
- 单位：年（365天）、月（30天）、天、小时、分钟、秒
- 仅显示非零单位
- 舍入最小显示单位

**示例：**
- `duration(3661)` → "1 hour, 1 minute"
- `duration(3661, {compact: true})` → "1h 1m"
- `duration(3661, {max_units: 1})` → "1 hour"
- `duration(45)` → "45 seconds"
- `duration(0)` → "0 seconds"

---

### parse_duration(string) → number | error

将人类编写的时长字符串解析为秒数。

**接受的格式：**
- 紧凑格式："2h30m"、"2h 30m"、"2h, 30m"
- 详细格式："2 hours 30 minutes"、"2 hours and 30 minutes"
- 小数："2.5 hours"、"1.5h"
- 单一单位："90 minutes"、"90m"、"90min"
- 冒号表示法："2:30"（解释为 h:mm）、"2:30:00"（h:mm:ss）

**单位别名：**
- 秒：s、sec、secs、second、seconds
- 分钟：m、min、mins、minute、minutes
- 小时：h、hr、hrs、hour、hours
- 天：d、day、days
- 周：w、wk、wks、week、weeks

**错误条件：**
- 空字符串
- 无可解析单位
- 负值

**理由：** 对接受的输入要宽松。用户以多种方式输入时长。

---

### human_date(timestamp, reference?) → string

返回上下文相关的日期字符串。

**参数：**
- `timestamp`：要格式化的日期
- `reference`：用于比较的"当前"日期

**行为：**

| 条件 | 输出 |
|-----------|--------|
| 同一天 | "Today" |
| 前一天 | "Yesterday" |
| 后一天 | "Tomorrow" |
| 过去 7 天内 | "Last {weekday}" |
| 未来 7 天内 | "This {weekday}" |
| 同年 | "{Month} {day}" |
| 不同年 | "{Month} {day}, {year}" |

---

### date_range(start, end) → string

格式化日期范围，智能缩写。

**参数：**
- `start`：开始时间戳
- `end`：结束时间戳

**行为：**
- 同一天："March 5, 2024"
- 同一月："March 5–7, 2024"
- 同一年："March 5 – April 7, 2024"
- 不同年："December 28, 2024 – January 3, 2025"

**边界情况：**
- `start` 等于 `end`：视为单日
- `start` 在 `end` 之后：静默交换

---

## 测试

### 测试数据格式

测试在 `tests.yaml` 中定义为语言无关的输入/输出对。

结构：
```yaml
function_name:
  - name: "人类可读的测试名称"
    input: { ... }        # 函数参数
    output: "expected"    # 期望返回值
    error: true           # 仅在函数应报错时存在
```

### 使用 tests.yaml

实现必须通过所有 tests.yaml 测试用例。工作流程：

1. **解析 tests.yaml**（使用目标语言）
2. **生成或编写测试用例**：
   - 使用 `input` 参数调用函数
   - 断言返回值等于 `output`
   - 如果 `error: true`，断言函数抛出/返回错误
3. **运行测试**并迭代直到全部通过

### 输入字段映射

每个函数有特定的输入字段：

**timeago：**
```yaml
input: { timestamp: <number>, reference: <number> }
```

**duration：**
```yaml
input: { seconds: <number>, options?: { compact?: bool, max_units?: int } }
```

**parse_duration：**
```yaml
input: "<string>"  # 直接字符串输入，不是对象
```

**human_date：**
```yaml
input: { timestamp: <number>, reference: <number> }
```

**date_range：**
```yaml
input: { start: <number>, end: <number> }
```

### 测试生成示例

给定此 tests.yaml 条目：
```yaml
timeago:
  - name: "2 minutes ago - 90 seconds"
    input: { timestamp: 1704067110, reference: 1704067200 }
    output: "2 minutes ago"
```

生成（Python）：
```python
def test_timeago_2_minutes_ago_90_seconds():
    result = timeago(1704067110, reference=1704067200)
    assert result == "2 minutes ago"
```

生成（TypeScript）：
```typescript
test('timeago: 2 minutes ago - 90 seconds', () => {
  expect(timeago(1704067110, 1704067200)).toBe('2 minutes ago');
});
```

生成（Rust）：
```rust
#[test]
fn test_timeago_2_minutes_ago_90_seconds() {
    assert_eq!(timeago(1704067110, 1704067200), "2 minutes ago");
}
```

### 错误测试处理

对于带有 `error: true` 的条目：

```yaml
parse_duration:
  - name: "error - empty string"
    input: ""
    error: true
```

生成（Python）：
```python
def test_parse_duration_error_empty_string():
    with pytest.raises(ValueError):
        parse_duration("")
```

生成（TypeScript）：
```typescript
test('parse_duration: error - empty string', () => {
  expect(() => parse_duration("")).toThrow();
});
```

### 附加测试

实现可以包含 tests.yaml 之外的附加测试，但：
- 所有 tests.yaml 测试必须原样通过
- 附加测试不得与规范行为矛盾
- tests.yaml 未覆盖的边界情况由实现定义

---

## 生成的文档

实现必须包含一个 `usage.md` 文件，记录如何在目标语言中使用该库。

### usage.md 要求

文件应简洁实用。包括：

1. **安装** — 如何将库添加到项目（导入路径、包名等）

2. **快速开始** — 展示每个函数基本用法的小型代码示例

3. **函数参考** — 对于每个函数：
   - 目标语言语法的签名
   - 参数类型和描述
   - 返回类型
   - 一两个示例

4. **错误处理** — 错误如何报告以及如何惯用地处理

5. **类型转换** — 除了 Unix 时间戳，库还接受哪些 datetime 类型

### usage.md 模板

```markdown
# whenwords for [LANGUAGE]

Human-friendly time formatting and parsing.

## Installation

[如何导入/引入/添加库]

## Quick start

[5-10 行示例展示典型用法]

## Functions

### timeago(timestamp, reference?) → string

[签名、参数、示例]

### duration(seconds, options?) → string

[签名、参数、示例]

### parse_duration(string) → number

[签名、参数、示例]

### human_date(timestamp, reference?) → string

[签名、参数、示例]

### date_range(start, end) → string

[签名、参数、示例]

## Error handling

[语言特定的错误处理模式]

## Accepted types

[每个函数接受的类型]
```

保持在 150 行以内。开发者应该能在不到一分钟内浏览完。

---

## 实现清单

在认为实现完成之前：

- [ ] 所有五个函数已实现
- [ ] 所有 tests.yaml 测试通过
- [ ] 函数接受语言原生 datetime 类型（不仅仅是 Unix 时间戳）
- [ ] 错误以惯用方式抛出/返回
- [ ] 复数形式正确（"1 minute" vs "2 minutes"）
- [ ] 未来时间返回 "in X" 而非 "X ago"
- [ ] 零时长返回 "0 seconds"
- [ ] 代码符合目标语言惯用法
- [ ] usage.md 已生成，包含函数签名和示例

---

## 版本历史

- **v0.1.0** - 初始规范
