# cpp-training：ADAS Executor 执行器组件

《C++ 企业软件开发实践》四次实验与课后综合作业的完整实现。

`Executor` 是 ADAS（高级驾驶辅助系统）中的执行器组件：接收 Controller 下发的指令串，维护车辆的位置与朝向。
本仓库按「需求澄清 -> 接口设计 -> 测试先行 -> 小步提交」的企业级开发流程完成需求 1~4 与多车型作业，
共 **84 个单元测试** 全部通过。

## 需求与完成情况

| 编号 | 需求 | 关键行为 | 状态 |
| --- | --- | --- | --- |
| 1 | 基本控制指令 | `M` 前进 1 格；`L`/`R` 原地左/右转 90°；支持批量指令；未初始化默认 `(0,0,N)` | ✅ |
| 2 | 加速指令 `F` | 加速态：`M` 前进 2 格，`L`/`R` 先前进 1 格再转向；再次 `F` 取消 | ✅ |
| 3 | 倒车指令 `B` | 倒车态：`M` 后退 1 格，`L`/`R` 左右互换；可与 `F` 叠加（后退 2 格）；再次 `B` 取消 | ✅ |
| 4 | 掉头指令 `TR` | 左转 -> 前进 1 格 -> 左转；受 `F` 影响（前进-左转-前进-左转）；不受 `B` 影响 | ✅ |
| 作业 | 支持不同车辆类型 | 默认车 / 跑车 / 公交车三种运动学模型 | ✅ |

指令语义（默认车，坐标为车当前位置，x 轴 EW，y 轴 NS）：

| 指令 | 正常 | 加速 `F` | 倒车 `B` | 倒车 + 加速 |
| --- | --- | --- | --- | --- |
| `M` | 前进 1 格 | 前进 2 格 | 后退 1 格 | 后退 2 格 |
| `L` | 左转 | 前进 1 格 + 左转 | 右转 | 后退 1 格 + 右转 |
| `R` | 右转 | 前进 1 格 + 右转 | 左转 | 后退 1 格 + 左转 |
| `TR` | 左转 + 前进 1 格 + 左转 | 前进 1 格 + 左转 + 前进 1 格 + 左转 | 不生效 | 不生效 |
| `F` / `B` | 切换加速 / 倒车状态 | — | — | — |

车型差异（`CarType`）：

| 车型 | `M` | `L` / `R`（正常） | 说明 |
| --- | --- | --- | --- |
| `NORMAL` 默认车 | 1 格 | 原地转向 | 需求 1~4 的基线行为 |
| `SPORTS_CAR` 跑车 | 2 格 | 转向后再前进 1 格 | 加速时 `M` 前进 4 格 |
| `BUS` 公交车 | 1 格 | 先前进 1 格再转向 | 车长 2 格，坐标为车头 |

## 架构设计

分三层，依赖方向单向向下，`Command` 层不对 `ExecutorImpl` 产生反向依赖（消除循环依赖）：

```
          ┌──────────────────────────────┐
          │  include/Executor.hpp        │  公共接口：Pose / CarType / Executor
          └──────────────┬───────────────┘
                         │ 实现
          ┌──────────────▼───────────────┐
          │  executor/ExecutorImpl       │  持有 PoseHandler，取指令列表并批量执行
          └──────────────┬───────────────┘
                         │ 委托
   ┌─────────────────────▼──────────────────────┐
   │  command/  CmderFactory  Command  ActionGroup │  指令 -> 原子操作编排
   └─────────────────────┬──────────────────────┘
                         │ 操作
          ┌──────────────▼───────────────┐
          │  pose/ PoseHandler Point Direction │  位置、朝向、F/B 状态
          └──────────────────────────────┘
```

- **表驱动**：`CmderFactory` 是唯一的「指令字符 -> 指令对象」映射表；新增指令只改映射表，`Execute` 主干不动。
- **任务编排**：`Command` 只把指令翻译成 8 种原子操作（前进/后退 1 格、左/右转、反向左/右转、置加速/倒车），
  由 `ActionGroup` 顺序执行。`TR` 这类多步骤指令因此只是「排列组合」，不引入分支复杂度。
- **车型参数化**：`CarProfile` 用「每步格数 + 转向前/后移动格数」描述底盘差异，
  `SPORTS_CAR{2, 前0 后1}`、`BUS{1, 前1 后0}`，配合状态位推导出加速/倒车的全部组合行为，避免为每种车型复制一套指令类。
- **状态抽象**：`Direction` 把 4 个朝向统一为「索引 + 单位向量 + 左右旋转」，消除四分支 `if/else`；
  `Point` 统一 4 个方向的位移增量。
- **单体工厂**：`Singleton<CmderFactory>` 懒加载且 C++11 起线程安全，避免每次 `Execute` 重建映射表。

目录结构：

```
cpp-training/
├── CMakeLists.txt
├── include/Executor.hpp          # 对外发布的唯一头文件（自满足、最小依赖）
├── src/
│   ├── pose/                     # Point / Direction / PoseHandler
│   ├── command/                  # ActionGroup / Command / CarProfile / CmderFactory
│   ├── executor/                 # ExecutorImpl
│   └── utility/Singleton.hpp     # 泛型单体模板
├── tests/                        # gtest 用例 + PoseEq（Pose 相等重载）
├── docs/requirements/            # 原始需求文档
└── script/                       # 一键构建 / 运行脚本
```

## 构建与运行

依赖：支持 C++17 的 g++（Windows 可用 MinGW-w64）、CMake 3.16+、随仓库附带的 googletest 1.12.1。

Windows（MinGW）：

```bat
script\build_and_run.bat
```

Linux / macOS：

```bash
bash script/build_and_run.sh
```

等价的手工步骤：

```bash
mkdir -p build && cd build
cmake -G "MinGW Makefiles" ..      # Linux/macOS 用 -G "Unix Makefiles" 或省略
mingw32-make                       # Linux/macOS 用 make
./tests/training_main              # Windows: tests\training_main.exe
```

`CTest` 亦可驱动：

```bash
cd build && ctest --output-on-failure
```

## 测试

| 测试套件 | 文件 | 用例数 | 覆盖内容 |
| --- | --- | --- | --- |
| `ExecutorTest` | tests/ExecutorTest.cpp | 17 | 默认位姿、初始化、四方向 `M`、四方向 `L`/`R`、批量指令、空指令 |
| `ExecutorFastTest` | tests/ExecutorFastTest.cpp | 11 | 加速下四方向 `M`、`L`/`R`、`FF` 取消、状态中途翻转、批量 |
| `ExecutorReverseTest` | tests/ExecutorReverseTest.cpp | 12 | 倒车下四方向 `M`、`L`/`R` 互换、`BB` 取消、`B&F` 叠加 |
| `ExecutorTurnRoundTest` | tests/ExecutorTurnRoundTest.cpp | 8 | `TR`、`FTR`、`BTR`、`BFTR`、`TRTR`、`TRM` |
| `VehicleTypes/ExecutorCarTypeTest` | tests/ExecutorCarTypeTest.cpp | 36 | 三种车型 x 四状态 x `M`/`L`/`R`，数据驱动（DDT） |

测试用例遵循课程要求：

- **FIRST**：用例无共享状态，可任意顺序、任意次数运行；全部使用 `ASSERT_EQ` 自校验。
- **正交分解**：以「朝向 x 指令 x 状态（正常/F/B/BF）」降维，每个维度取最小等价类。
- **命名即文档**：`should_<期望>_given_<条件>`，失败时可直接定位到需求条目。
- **测试先行与小步提交**：每次提交都包含新增用例与对应实现，且保证编译、测试通过。

## 提交记录

```
feat: 支持不同类型的车辆（跑车/Bus）
feat: 实现需求4 掉头指令 TR
feat: 实现需求3 倒车指令 B
feat: 实现需求2 加速指令 F
feat: 实现需求1 基本控制指令 M/L/R
chore: 导入 cpp-training 初始工程与 googletest 依赖
```

## 使用示例

```cpp
#include <memory>
#include "Executor.hpp"

int main() {
    std::unique_ptr<adas::Executor> executor(
        adas::Executor::NewExecutor({0, 0, 'N'}, adas::CarType::SPORTS_CAR));

    executor->Execute("FMTR");           // 指令串可任意组合
    const adas::Pose pose = executor->Query();
    // pose.x / pose.y / pose.heading

    return 0;
}
```
