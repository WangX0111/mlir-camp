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
mlir-camp
├─ LICENSE.TXT
├─ README.md
└─ toyalone
   ├─ .gitignore
   ├─ CMakeLists.txt
   ├─ LICENSE.TXT
   ├─ README.md
   ├─ build
   ├─ include
   ├─ lib
   ├─ python
   ├─ standalone-opt
   │  ├─ CMakeLists.txt
   │  └─ standalone-opt.cpp
   ├─ standalone-translate
   │  ├─ CMakeLists.txt
   │  └─ standalone-translate.cpp
   ├─ test
   │  ├─ CAPI
   │  ├─ CMakeLists.txt
   │  ├─ Standalone
   │  ├─ ast.toy
   │  ├─ codegen.toy
   │  ├─ empty.toy
   │  ├─ lit.cfg.py
   │  ├─ lit.site.cfg.py.in
   │  └─ python
   └─ toy
      ├─ CMakeLists.txt
      ├─ README.md
      ├─ include
      │  ├─ CMakeLists.txt
      │  └─ toy
      │     ├─ AST.h
      │     ├─ CMakeLists.txt
      │     ├─ Dialect.h
      │     ├─ Lexer.h
      │     ├─ MLIRGen.h
      │     ├─ Ops.td
      │     ├─ Parser.h
      │     ├─ Passes.h
      │     ├─ ShapeInferenceInterface.h
      │     └─ ShapeInferenceInterface.td
      ├─ mlir
      │  ├─ Dialect.cpp
      │  ├─ LowerToAffineLoops.cpp
      │  ├─ LowerToLLVM.cpp
      │  ├─ MLIRGen.cpp
      │  ├─ ShapeInferencePass.cpp
      │  ├─ ToyCombine.cpp
      │  └─ ToyCombine.td
      ├─ parser
      │  └─ AST.cpp
      └─ toyc.cpp

```