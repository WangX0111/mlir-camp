//===- ToyCombine.cpp - Toy High Level Optimizer --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements a set of simple combiners for optimizing operations in
// the Toy dialect.
//
//===----------------------------------------------------------------------===//

#include "mlir/IR/Matchers.h"
#include "mlir/IR/PatternMatch.h"
#include "toy/Dialect.h"
#include <numeric>
using namespace mlir;
using namespace toy;

namespace {
/// Include the patterns defined in the Declarative Rewrite framework.
#include "ToyCombine.inc"
} // namespace

/// Fold constants.
OpFoldResult ConstantOp::fold(ArrayRef<Attribute> operands) {
  return getValue();
}

/// Fold struct constants.
OpFoldResult StructConstantOp::fold(ArrayRef<Attribute> operands) {
  return getValue();
}

/// Fold simple struct access operations that access into a constant.
OpFoldResult StructAccessOp::fold(ArrayRef<Attribute> operands) {
  auto structAttr = operands.front().dyn_cast_or_null<mlir::ArrayAttr>();
  if (!structAttr)
    return nullptr;

  size_t elementIndex = getIndex();
  return structAttr[elementIndex];
}

/// This is an example of a c++ rewrite pattern for the TransposeOp. It
/// optimizes the following scenario: transpose(transpose(x)) -> x
struct SimplifyRedundantTranspose : public mlir::OpRewritePattern<TransposeOp> {
  /// We register this pattern to match every toy.transpose in the IR.
  /// The "benefit" is used by the framework to order the patterns and process
  /// them in order of profitability.
  SimplifyRedundantTranspose(mlir::MLIRContext *context)
      : OpRewritePattern<TransposeOp>(context, /*benefit=*/1) {}

  /// This method attempts to match a pattern and rewrite it. The rewriter
  /// argument is the orchestrator of the sequence of rewrites. The pattern is
  /// expected to interact with it to perform any changes to the IR from here.
  mlir::LogicalResult
  matchAndRewrite(TransposeOp op,
                  mlir::PatternRewriter &rewriter) const override {
    // Look through the input of the current transpose.
    mlir::Value transposeInput = op.getOperand();
    TransposeOp transposeInputOp = transposeInput.getDefiningOp<TransposeOp>();

    // Input defined by another transpose? If not, no match.
    if (!transposeInputOp)
      return failure();

    // Otherwise, we have a redundant transpose. Use the rewriter.
    rewriter.replaceOp(op, {transposeInputOp.getOperand()});
    return success();
  }
};

//matmul
struct RepositionRedundantMatmul:public mlir::OpRewritePattern<MatmulOp>{
  RepositionRedundantMatmul(mlir::MLIRContext *context)
    :OpRewritePattern<MatmulOp>(context,2){}
  mlir::LogicalResult matchAndRewrite(MatmulOp op,mlir::PatternRewriter &rewriter)const override{
    mlir::Value MatmulLhs = op.getOperands()[0];//获取第一个操作数
    mlir::Value MatmulRhs = op.getOperands()[1];
    MatmulOp matmulLhsOp = MatmulLhs.getDefiningOp<MatmulOp>();
    if(!matmulLhsOp)return failure();//判断第一个操作数是否依然为MatmulOp
    auto BxC = rewriter.create<MatmulOp>(op.getLoc(),matmulLhsOp.getOperands()[1],MatmulRhs);//重现创建Op
    auto AxBC = rewriter.create<MatmulOp>(op.getLoc(),matmulLhsOp.getOperands()[0],BxC);
    rewriter.replaceOp(op,{AxBC});//Op替换
    return success();
  }
};

//exp
struct SimplifyRedundantExp : public mlir::OpRewritePattern<ExpOp> {
  
  SimplifyRedundantExp(mlir::MLIRContext *context)
      : OpRewritePattern<ExpOp>(context, /*benefit=*/1) {}

  /// This method attempts to match a pattern and rewrite it. The rewriter
  /// argument is the orchestrator of the sequence of rewrites. The pattern is
  /// expected to interact with it to perform any changes to the IR from here.
  mlir::LogicalResult
  matchAndRewrite(ExpOp op,
                  mlir::PatternRewriter &rewriter) const override {
    // Look through the input of the current transpose.
    mlir::Value expInput = op.getOperand();
    ExpOp expInputOp = expInput.getDefiningOp<ExpOp>();

    // Input defined by another transpose? If not, no match.
    if (!expInputOp)
      return failure();

    // Otherwise, we have a redundant transpose. Use the rewriter.
    rewriter.replaceOp(op, {expInputOp.getOperand()});
    return success();
  }
};

/// Register our patterns as "canonicalization" patterns on the TransposeOp so
/// that they can be picked up by the Canonicalization framework.
void TransposeOp::getCanonicalizationPatterns(RewritePatternSet &results,
                                              MLIRContext *context) {
  results.add<SimplifyRedundantTranspose>(context);
}

/// Register our patterns as "canonicalization" patterns on the ReshapeOp so
/// that they can be picked up by the Canonicalization framework.
void ReshapeOp::getCanonicalizationPatterns(RewritePatternSet &results,
                                            MLIRContext *context) {
  results.add<ReshapeReshapeOptPattern, RedundantReshapeOptPattern,
              FoldConstantReshapeOptPattern>(context);
}

//相当于注册吧，启用canonicalization pass
void MatmulOp::getCanonicalizationPatterns(RewritePatternSet &results,MLIRContext *context){
  results.add<RepositionRedundantMatmul>(context);
}

void ExpOp::getCanonicalizationPatterns(RewritePatternSet &results,MLIRContext *context){
  results.add<SimplifyRedundantExp>(context);
}