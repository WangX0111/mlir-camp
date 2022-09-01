# 指定 cmake 的最小版本
cmake_minimum_required(VERSION 3.13.4)
# 设置项目名称，它会引入两个变量 demo_BINARY_DIR 和 demo_SOURCE_DIR，同时，cmake 自动定义了两个等价的变量 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR。
project(standalone-dialect LANGUAGES CXX C)

# 设置变量
set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")

# 寻找MLIR需要的库
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# 设定LLVM运行时与库文件的输出路径bin、lib，设定MLIR编译目录
set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR})

# 追加设置，设置cmake的搜索路径，添加cmake_dir到CMAKE_MODULE_PATH路径列表中
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
# 在搜索路径中搜索*.cmake文件
include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

# 如果启用python绑定
if(MLIR_ENABLE_BINDINGS_PYTHON)
  include(MLIRDetectPythonEnv)
  mlir_configure_python_dev_packages()
endif()

# 设置包含的目录，头文件目录
# 寻找第三方库和添加头文件
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
# 自己写的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
# 设置链接库搜索目录
link_directories(${LLVM_BUILD_LIBRARY_DIR})
# 设置编译选项
add_definitions(${LLVM_DEFINITIONS})
message(STATUS, "LLVM_BUILD_LIB/DEF: ${LLVM_BUILD_LIBRARY_DIR} ${LLVM_DEFINITIONS}")

# 增加子目录
add_subdirectory(include)
add_subdirectory(lib)
if(MLIR_ENABLE_BINDINGS_PYTHON)
  message(STATUS "Enabling Python API")
  add_subdirectory(python)
endif()
add_subdirectory(test)
add_subdirectory(toy)