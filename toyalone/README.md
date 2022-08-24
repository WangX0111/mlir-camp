<!--
 * @Author: WangX 
 * @Date: 2022-08-22 14:43:17
 * @LastEditors: WangX 
 * @LastEditTime: 2022-08-25 
 * @FilePath: /toyalone/README.md
 * @Description: toyalone readme.md
-->

# MLIR TRAINING CAMP
toy standalone 

build -- 编译生成的文件
toy -- 原toy-ch7的相关代码

修改对应的cmakeList

# An out-of-tree MLIR dialect

This is an example of an out-of-tree [MLIR](https://mlir.llvm.org/) dialect along with a standalone `opt`-like tool to operate on that dialect.

## Building

This setup assumes that you have built LLVM and MLIR in `$BUILD_DIR` and installed them to `$PREFIX`. To build and launch the tests, run
```sh
mkdir build && cd build
cmake -G Ninja .. -DMLIR_DIR=/Users/wangchenhao/Documents/Enflame/workSpace/llvm-project/build/lib/cmake/mlir -DLLVM_EXTERNAL_LIT=/Users/wangchenhao/Documents/Enflame/workSpace/llvm-project/build/bin/llvm-lit
cmake --build . --target check-standalone
```
To build the documentation from the TableGen description of the dialect operations, run
```sh
cmake --build . --target mlir-doc
```
**Note**: Make sure to pass `-DLLVM_INSTALL_UTILS=ON` when building LLVM with CMake in order to install `FileCheck` to the chosen installation prefix.

