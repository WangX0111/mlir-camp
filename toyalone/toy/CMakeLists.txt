# set(LLVM_LINK_COMPONENTS
#   Core
#   Support
#   nativecodegen
#   OrcJIT
#   )

# 生成可执行文件
add_llvm_executable(toyc-main
  toyc.cpp
  AST.cpp
)

 # 链接库到执行文件上，执行文件在上一步add_executable生成
target_link_libraries(toyc-main
  PRIVATE
    MLIRToy

    MLIRAnalysis
    MLIRCallInterfaces
    MLIRCastInterfaces
    MLIRExecutionEngine
    MLIRIR
    MLIRLLVMToLLVMIRTranslation
    MLIRParser
    MLIRPass
    MLIRSideEffectInterfaces
    MLIRTargetLLVMIRExport
    MLIRTransforms
    )
