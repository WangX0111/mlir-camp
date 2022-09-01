get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

add_mlir_dialect_library(MLIRToy
    OpsDialect.cpp
    MLIRGen.cpp
    LowerToAffineLoops.cpp
    LowerToLLVM.cpp
    ShapeInferencePass.cpp
    ToyCombine.cpp

    DEPENDS
    MLIROpsIncGen
    ToyShapeInferenceInterfaceIncGen
    ToyCombineIncGen

    LINK_LIBS PUBLIC
    ${dialect_libs}
    ${conversion_libs}
    MLIRAnalysis
    MLIRIR
    MLIRPass
    MLIRSideEffectInterfaces
    MLIRTransforms
    MLIRCallInterfaces
    MLIRCastInterfaces
)

