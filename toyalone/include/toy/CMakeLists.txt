# Most dialects should use add_mlir_dialect().  See examples/standalone.
# set(LLVM_TARGET_DEFINITIONS Ops.td)
# mlir_tablegen(Ops.h.inc -gen-op-decls)
# mlir_tablegen(Ops.cpp.inc -gen-op-defs)
# CMake 最佳实践，注意，使用add_mlir_dialect(source, target) 会得到targetDialect
add_mlir_dialect(Ops toy)
# add_mlir_doc(Ops ToyDialect  Dialects/ -gen-dialect-doc)
# mlir_tablegen(Dialect.h.inc -gen-dialect-decls)
# mlir_tablegen(Dialect.cpp.inc -gen-dialect-defs)
# add_public_tablegen_target(ToyOpsIncGen)

# Most dialects should use add_mlir_interfaces().
set(LLVM_TARGET_DEFINITIONS ShapeInferenceInterface.td)
mlir_tablegen(ShapeInferenceOpInterfaces.h.inc -gen-op-interface-decls)
mlir_tablegen(ShapeInferenceOpInterfaces.cpp.inc -gen-op-interface-defs)
add_public_tablegen_target(ToyShapeInferenceInterfaceIncGen)

set(LLVM_TARGET_DEFINITIONS ToyCombine.td)
mlir_tablegen(ToyCombine.inc -gen-rewriters)
add_public_tablegen_target(ToyCombineIncGen)

# add_mlir_dialect(StandaloneOps standalone)
# add_mlir_doc(StandaloneDialect StandaloneDialect Standalone/ -gen-dialect-doc)
# add_mlir_doc(StandaloneOps StandaloneOps Standalone/ -gen-op-doc)