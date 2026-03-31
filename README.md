# whenwords：一个没有代码的开源库

今天我发布了 [`whenwords`](https://github.com/dbreunig/whenwords)，一个相对时间格式化库，它_不包含任何代码_。

`whenwords` 提供以下函数：

- **timeago** — 将时间戳转换为相对时间字符串，如 "3 hours ago" 或 "in 2 days"，基于参考时间。
- **duration** — 将秒数格式化为人类可读的时长，如 "2 hours, 30 minutes" 或紧凑模式下的 "2h 30m"。
- **parse_duration** — duration 的逆操作——将 "2h 30m" 或 "2 hours and 30 minutes" 等字符串解析为秒数。
- **human_date** — 返回上下文相关的日期字符串，如 "Today"、"Yesterday"、"Last Tuesday" 或 "March 5"，取决于日期与参考点的距离。
- **date_range** — 将开始和结束时间戳格式化为智能日期范围，折叠冗余信息："March 5–7, 2024" 而非 "March 5, 2024 – March 7, 2024"。

有_很多_库执行类似的功能。但它们都不是语言无关的。

`whenwords` 支持 Ruby、Python、Rust、Elixir、Swift、PHP 和 Bash。我相信它在其他语言中也能工作。[这些只是我尝试并测试过的语言](https://github.com/dbreunig/whenwords-examples)。

（我甚至将其实现为 Excel 公式。不过那个需要一些安装工作。）

但正如我所说：`whenwords` 库_不包含代码_。相反，`whenwords` 包含规范和测试，具体包括：

- **SPEC.md**：库应如何行为和实现的详细描述。
- **tests.yaml**：语言无关的测试用例列表，定义为输入/输出对，任何实现都必须通过。
- **INSTALL.md**：构建 `whenwords` 的说明，为您——人类——准备。

安装说明非常简单，只是一个粘贴到 Claude、Codex、Cursor 或其他工具中的提示词。它短到可以完整打印在这里：

```markdown
使用 [LANGUAGE] 语言实现 whenwords 库。

1. 阅读 SPEC.md 了解完整的行为规范
2. 解析 tests.yaml 并生成测试文件
3. 实现全部五个函数：timeago、duration、parse_duration、human_date、date_range
4. 运行测试直到全部通过
5. 将实现放在 [LOCATION]

所有 tests.yaml 测试用例必须通过。参见 SPEC.md "Testing" 部分的测试生成示例。
```

选择您的语言，选择您的位置，复制、粘贴，然后开始。

[我在这里写了关于 `whenwords` 的文章](https://www.dbreunig.com/2026/01/08/a-software-library-with-no-code.html)。
