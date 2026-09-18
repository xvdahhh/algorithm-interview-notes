# 验证记录

- `python algorithm-interview-notes/site-src/verify.py`：16 个 HTML 页面、63 个小节、556 处本地引用通过检查；86 份 C++ 下载（含第一章新增 7 份、第二章新增 16 份）与讲义内容一致，前两章合计 63 个问答的答案完整显示。
- `node --check algorithm-interview-notes/assets/app.js`：JavaScript 语法检查通过。
- 使用本机 Chrome 与 Playwright 逐页打开离线 HTML：未出现页面脚本错误。
- 交互检查：章节筛选、无结果提示、代码复制、刷新后保持掌握勾选、移动端目录与 Escape 关闭通过。
- 390 像素宽度下检查全部 16 页：页面无横向溢出，长代码在代码区内部横向滚动。
- 已人工检查 1440 像素桌面首页、动态规划章节及 390 像素移动章节截图；截图在 `qa/`。
- 第一章扩展后，另检查桌面讲义、不变量证明、移动端表格和长答案截图；320 与 390 像素宽度下无页面横向溢出，表格可在自身区域横向滚动，关键问答默认展开。
- 第二章扩展后，另检查 34 个问答、16 份补充示例下载、10 张知识与手推表格、最小覆盖代码复制，以及桌面首页、窗口反例、移动端前缀和与矩阵答案截图。320 与 390 像素宽度下无页面横向溢出。
- 当前环境未发现可用的 C++ 编译器。示例经过内容审阅并提供标准头文件，但本次没有完成 C++ 编译与运行验证；浏览器检查不等于算法代码测试。

## 复查命令

在工作区根目录运行：

```powershell
python algorithm-interview-notes/site-src/build.py
python algorithm-interview-notes/site-src/verify.py
node --check algorithm-interview-notes/assets/app.js
```

浏览器检查脚本需要 Playwright；可将已安装的包绝对路径作为第二个参数传入：

```powershell
node algorithm-interview-notes/site-src/browser-check.cjs <playwright包路径>
```

示例可分别用支持 C++17 的编译器执行 `g++ -std=c++17 -Wall -Wextra -c 示例.cpp` 检查。含 `main` 的示例可编译运行；函数型示例需要调用入口和针对性测试。
