<!--
 * @Author: WangX 
 * @Date: 2022-08-22 14:43:17
 * @LastEditors: WangX 
 * @LastEditTime: 2022-08-25 
 * @FilePath: /README.md
 * @Description: mlir-camp readme.md
-->

# MLIR TRAINING CAMP

## 项目目标
- 分析MLIR典型示例的代码结构
- CMake编译配置
- 自定义算子描述（TD文件及TableGen）
- MLIR代码生成及算子调用
- 自定义算子类型推断
- 单操作数与多操作数算子的Lowering/Dialect转换
- 管理Lowering Pass
- 完成测试 (Emit到MLIR-Affine和JIT执行)
- 撰写报告

## 项目结构
```
MLIR-Camp
├── LICENSE.TXT
├── README.md
├── docs
└── toyalone
    ├── CMakeLists.txt
    ├── LICENSE.TXT
    ├── README.md
    ├── build
    │   ├── CMakeCache.txt
    │   ├── CMakeFiles
    │   │   ├── 3.23.1
    │   │   │   ├── CMakeCCompiler.cmake
    │   │   │   ├── CMakeCXXCompiler.cmake
    │   │   │   ├── CMakeDetermineCompilerABI_C.bin
    │   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
    │   │   │   ├── CMakeSystem.cmake
    │   │   │   ├── CompilerIdC
    │   │   │   │   ├── CMakeCCompilerId.c
    │   │   │   │   ├── CMakeCCompilerId.o
    │   │   │   │   └── tmp
    │   │   │   └── CompilerIdCXX
    │   │   │       ├── CMakeCXXCompilerId.cpp
    │   │   │       ├── CMakeCXXCompilerId.o
    │   │   │       └── tmp
    │   │   ├── CMakeError.log
    │   │   ├── CMakeOutput.log
    │   │   ├── CMakeTmp
    │   │   ├── TargetDirectories.txt
    │   │   ├── cmake.check_cache
    │   │   └── rules.ninja
    │   ├── bin
    │   │   └── toyc-main
    │   ├── build.ninja
    │   ├── cmake_install.cmake
    │   ├── include
    │   │   ├── CMakeFiles
    │   │   ├── cmake_install.cmake
    │   │   └── toy
    │   │       ├── CMakeFiles
    │   │       ├── Ops.cpp.inc
    │   │       ├── Ops.cpp.inc.d
    │   │       ├── Ops.h.inc
    │   │       ├── Ops.h.inc.d
    │   │       ├── OpsDialect.cpp.inc
    │   │       ├── OpsDialect.cpp.inc.d
    │   │       ├── OpsDialect.h.inc
    │   │       ├── OpsDialect.h.inc.d
    │   │       ├── OpsTypes.cpp.inc
    │   │       ├── OpsTypes.cpp.inc.d
    │   │       ├── OpsTypes.h.inc
    │   │       ├── OpsTypes.h.inc.d
    │   │       ├── ShapeInferenceOpInterfaces.cpp.inc
    │   │       ├── ShapeInferenceOpInterfaces.cpp.inc.d
    │   │       ├── ShapeInferenceOpInterfaces.h.inc
    │   │       ├── ShapeInferenceOpInterfaces.h.inc.d
    │   │       ├── ToyCombine.inc
    │   │       ├── ToyCombine.inc.d
    │   │       └── cmake_install.cmake
    │   ├── lib
    │   │   ├── CMakeFiles
    │   │   ├── cmake_install.cmake
    │   │   ├── libMLIRToy.a
    │   │   └── mlir
    │   │       ├── CMakeFiles
    │   │       │   ├── MLIRToy.dir
    │   │       │   └── obj.MLIRToy.dir
    │   │       │       ├── LowerToAffineLoops.cpp.o
    │   │       │       ├── LowerToLLVM.cpp.o
    │   │       │       ├── MLIRGen.cpp.o
    │   │       │       ├── OpsDialect.cpp.o
    │   │       │       ├── ShapeInferencePass.cpp.o
    │   │       │       └── ToyCombine.cpp.o
    │   │       └── cmake_install.cmake
    │   ├── tablegen_compile_commands.yml
    │   ├── test
    │   │   ├── CMakeFiles
    │   │   ├── cmake_install.cmake
    │   │   └── lit.site.cfg.py
    │   └── toy
    │       ├── CMakeFiles
    │       │   └── toyc-main.dir
    │       │       ├── AST.cpp.o
    │       │       └── toyc.cpp.o
    │       └── cmake_install.cmake
    ├── include
    │   ├── CMakeLists.txt
    │   └── toy
    │       ├── AST.h
    │       ├── CMakeLists.txt
    │       ├── Lexer.h
    │       ├── MLIRGen.h
    │       ├── Ops.td
    │       ├── OpsDialect.h
    │       ├── Parser.h
    │       ├── Passes.h
    │       ├── ShapeInferenceInterface.h
    │       ├── ShapeInferenceInterface.td
    │       └── ToyCombine.td
    ├── lib
    │   ├── CMakeLists.txt
    │   ├── mlir
    │   │   ├── CMakeLists.txt
    │   │   ├── LowerToAffineLoops.cpp
    │   │   ├── LowerToLLVM.cpp
    │   │   ├── MLIRGen.cpp
    │   │   ├── OpsDialect.cpp
    │   │   ├── ShapeInferencePass.cpp
    │   │   └── ToyCombine.cpp
    │   └── parser
    ├── python
    │   ├── CMakeLists.txt
    │   ├── StandaloneExtension.cpp
    │   └── mlir_standalone
    │       └── dialects
    │           ├── StandaloneOps.td
    │           └── standalone.py
    ├── test
    │   ├── CMakeLists.txt
    │   ├── ast.toy
    │   ├── codegen.toy
    │   ├── empty.toy
    │   ├── exp-test.toy
    │   ├── lit.cfg.py
    │   ├── lit.site.cfg.py.in
    │   ├── matmul-test.toy
    │   └── python
    │       ├── lit.local.cfg
    │       └── smoketest.py
    └── toy
        ├── AST.cpp
        ├── CMakeLists.txt
        └── toyc.cpp

```