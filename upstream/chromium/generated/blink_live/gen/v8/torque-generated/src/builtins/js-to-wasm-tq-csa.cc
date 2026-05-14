#include "src/ast/ast.h"
#include "src/builtins/builtins-array-gen.h"
#include "src/builtins/builtins-bigint-gen.h"
#include "src/builtins/builtins-call-gen.h"
#include "src/builtins/builtins-collections-gen.h"
#include "src/builtins/builtins-constructor-gen.h"
#include "src/builtins/builtins-data-view-gen.h"
#include "src/builtins/builtins-iterator-gen.h"
#include "src/builtins/builtins-object-gen.h"
#include "src/builtins/builtins-promise-gen.h"
#include "src/builtins/builtins-promise.h"
#include "src/builtins/builtins-proxy-gen.h"
#include "src/builtins/builtins-regexp-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-typed-array-gen.h"
#include "src/builtins/builtins-utils-gen.h"
#include "src/builtins/builtins-wasm-gen.h"
#include "src/builtins/builtins.h"
#include "src/codegen/code-factory.h"
#include "src/debug/debug-wasm-objects.h"
#include "src/heap/factory-inl.h"
#include "src/ic/binary-op-assembler.h"
#include "src/ic/handler-configuration-inl.h"
#include "src/objects/arguments.h"
#include "src/objects/bigint.h"
#include "src/objects/call-site-info.h"
#include "src/objects/elements-kind.h"
#include "src/objects/free-space.h"
#include "src/objects/intl-objects.h"
#include "src/objects/js-atomics-synchronization.h"
#include "src/objects/js-break-iterator.h"
#include "src/objects/js-collator.h"
#include "src/objects/js-date-time-format.h"
#include "src/objects/js-display-names.h"
#include "src/objects/js-disposable-stack.h"
#include "src/objects/js-duration-format.h"
#include "src/objects/js-function.h"
#include "src/objects/js-generator.h"
#include "src/objects/js-iterator-helpers.h"
#include "src/objects/js-list-format.h"
#include "src/objects/js-locale.h"
#include "src/objects/js-number-format.h"
#include "src/objects/js-objects.h"
#include "src/objects/js-plural-rules.h"
#include "src/objects/js-promise.h"
#include "src/objects/js-raw-json.h"
#include "src/objects/js-regexp-string-iterator.h"
#include "src/objects/js-relative-time-format.h"
#include "src/objects/js-segment-iterator-inl.h"
#include "src/objects/js-segmenter.h"
#include "src/objects/js-segments.h"
#include "src/objects/js-shadow-realm.h"
#include "src/objects/js-shared-array.h"
#include "src/objects/js-struct.h"
#include "src/objects/js-weak-refs.h"
#include "src/objects/objects.h"
#include "src/objects/ordered-hash-table.h"
#include "src/objects/property-array.h"
#include "src/objects/property-descriptor-object.h"
#include "src/objects/sort-state.h"
#include "src/objects/source-text-module.h"
#include "src/objects/swiss-hash-table-helpers.h"
#include "src/objects/swiss-name-dictionary.h"
#include "src/objects/synthetic-module.h"
#include "src/objects/template-objects.h"
#include "src/objects/torque-defined-classes.h"
#include "src/objects/turbofan-types.h"
#include "src/objects/turboshaft-types.h"
#include "src/torque/runtime-support.h"
#include "src/wasm/value-type.h"
#include "src/wasm/wasm-linkage.h"
#include "src/wasm/wasm-module.h"
#include "src/codegen/code-stub-assembler-inl.h"
// Required Builtins:
#include "torque-generated/src/builtins/js-to-wasm-tq-csa.h"
#include "torque-generated/src/builtins/array-findindex-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-splice-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/builtins-bigint-tq-csa.h"
#include "torque-generated/src/builtins/builtins-string-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frames-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/cell-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-function-tq-csa.h"
#include "torque-generated/test/torque/test-torque-tq-csa.h"
#include "torque-generated/src/builtins/js-to-wasm-tq-csa.h"
#include "torque-generated/src/builtins/wasm-tq-csa.h"
#include "torque-generated/src/builtins/wasm-to-js-tq-csa.h"
#include "torque-generated/src/wasm/wasm-objects-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=68&c=1
TNode<Int32T> FromConstexpr_Promise_constexpr_kPromise_0(compiler::CodeAssemblerState* state_, wasm::Promise p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  TNode<Int32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Int32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Int32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Int32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=68&c=1
TNode<Int32T> FromConstexpr_Promise_constexpr_kNoPromise_0(compiler::CodeAssemblerState* state_, wasm::Promise p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  TNode<Int32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Int32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Int32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Int32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=68&c=1
TNode<Int32T> FromConstexpr_Promise_constexpr_kStressSwitch_0(compiler::CodeAssemblerState* state_, wasm::Promise p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Int32T> tmp0;
  TNode<Int32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Int32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Int32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Int32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=74&c=1
TNode<Uint32T> FromConstexpr_StandardType_constexpr_kExtern_0(compiler::CodeAssemblerState* state_, wasm::StandardType p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=74&c=1
TNode<Uint32T> FromConstexpr_StandardType_constexpr_kNoExtern_0(compiler::CodeAssemblerState* state_, wasm::StandardType p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=74&c=1
TNode<Uint32T> FromConstexpr_StandardType_constexpr_kString_0(compiler::CodeAssemblerState* state_, wasm::StandardType p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=74&c=1
TNode<Uint32T> FromConstexpr_StandardType_constexpr_kEq_0(compiler::CodeAssemblerState* state_, wasm::StandardType p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=74&c=1
TNode<Uint32T> FromConstexpr_StandardType_constexpr_kI31_0(compiler::CodeAssemblerState* state_, wasm::StandardType p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=74&c=1
TNode<Uint32T> FromConstexpr_StandardType_constexpr_kAny_0(compiler::CodeAssemblerState* state_, wasm::StandardType p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=84&c=1
TNode<Uint32T> FromConstexpr_RefTypeKind_constexpr_kStruct_0(compiler::CodeAssemblerState* state_, wasm::RefTypeKind p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=84&c=1
TNode<Uint32T> FromConstexpr_RefTypeKind_constexpr_kArray_0(compiler::CodeAssemblerState* state_, wasm::RefTypeKind p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=84&c=1
TNode<Uint32T> FromConstexpr_RefTypeKind_constexpr_kFunction_0(compiler::CodeAssemblerState* state_, wasm::RefTypeKind p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.Uint32Constant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<Uint32T>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=149&c=1
TNode<Uint32T> Bitcast_uint32_float32_0(compiler::CodeAssemblerState* state_, TNode<Float32T> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).BitcastFloat32ToInt32(TNode<Float32T>{p_v});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Uint32T>{tmp0};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=158&c=1
TNode<IntPtrT> TruncateBigIntToI64_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_input) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).Is64()));
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 160});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is64()' failed", pos_stack);
    }
  }

  TNode<BigInt> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = CodeStubAssembler(state_).ToBigInt(TNode<Context>{p_context}, TNode<JSAny>{p_input});
    tmp2 = BigIntBuiltinsAssembler(state_).ReadBigIntLength(TNode<BigInt>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp5;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block1, tmp5);
  }

  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<Uint32T> tmp8;
  TNode<Uint32T> tmp9;
  TNode<BoolT> tmp10;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp6 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = CodeStubAssembler(state_).LoadBigIntDigit(TNode<BigInt>{tmp1}, TNode<IntPtrT>{tmp6});
    tmp8 = BigIntBuiltinsAssembler(state_).ReadBigIntSign(TNode<BigInt>{tmp1});
    tmp9 = kPositiveSign_0(state_);
    tmp10 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp8}, TNode<Uint32T>{tmp9});
    ca_.Branch(tmp10, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp11 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp7});
    ca_.Goto(&block1, tmp11);
  }

  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp7});
    tmp13 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp14 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp12});
    ca_.Goto(&block1, tmp14);
  }

  TNode<IntPtrT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block8, phi_bb1_2);
  }

  TNode<IntPtrT> phi_bb8_2;
    ca_.Bind(&block8, &phi_bb8_2);
  return TNode<IntPtrT>{phi_bb8_2};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=272&c=1
TorqueStructReturnSlotAllocator_0 NewReturnSlotAllocator_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<BoolT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_intptr_0(state_, arraysize(wasm::kGpReturnRegisters));
    tmp1 = FromConstexpr_intptr_constexpr_intptr_0(state_, arraysize(wasm::kFpReturnRegisters));
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReturnSlotAllocator_0{TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp1}, TNode<BoolT>{tmp3}, TNode<BoolT>{tmp4}, TNode<IntPtrT>{tmp2}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=405&c=1
TorqueStructLocationAllocator_0 LocationAllocatorForParams_0(compiler::CodeAssemblerState* state_, TorqueStructReference_intptr_0 p_paramBuffer, TNode<IntPtrT> p_paramBufferSize) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).UniqueIntPtrConstant(arraysize(wasm::kGpParamRegisters) - 1);
    tmp1 = CodeStubAssembler(state_).UniqueIntPtrConstant(arraysize(wasm::kFpParamRegisters));
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp3 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp2});
    if (((CodeStubAssembler(state_).ConstexprBoolNot((CodeStubAssembler(state_).Is64()))))) {
      ca_.Goto(&block2);
    } else {
      ca_.Goto(&block3);
    }
  }

  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp5 = CodeStubAssembler(state_).WordAnd(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp4});
    tmp6 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp5});
    ca_.Goto(&block4, tmp6);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4, tmp3);
  }

  TNode<IntPtrT> phi_bb4_7;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_7);
    tmp7 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x8ull));
    tmp8 = CodeStubAssembler(state_).IntPtrMod(TNode<IntPtrT>{phi_bb4_7}, TNode<IntPtrT>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp10 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp9});
    ca_.Branch(tmp10, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 417});
      CodeStubAssembler(state_).FailAssert("Torque assert 'result.nextFPReg % 8 == 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<BoolT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp11 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb4_7}, TNode<IntPtrT>{p_paramBuffer.offset});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp13});
    tmp15 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp17 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp18 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{p_paramBufferSize}, TNode<IntPtrT>{tmp17});
    ca_.Branch(tmp18, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp19 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{p_paramBuffer.offset}, TNode<IntPtrT>{p_paramBufferSize});
    ca_.Goto(&block9, tmp19);
  }

  TNode<IntPtrT> tmp20;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp20 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block9, tmp20);
  }

  TNode<IntPtrT> phi_bb9_10;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_10);
    ca_.Goto(&block10);
  }

    ca_.Bind(&block10);
  return TorqueStructLocationAllocator_0{TNode<Union<HeapObject, TaggedIndex>>{p_paramBuffer.object}, TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{p_paramBuffer.offset}, TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{phi_bb9_10}, TNode<IntPtrT>{tmp15}, TNode<BoolT>{tmp16}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=432&c=1
TorqueStructLocationAllocator_0 LocationAllocatorForReturns_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_gpRegs, TNode<RawPtrT> p_fpRegs, TNode<RawPtrT> p_stack) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<TaggedIndex> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<BoolT> tmp13;
  TNode<IntPtrT> tmp14;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kZeroBitPattern_0(state_);
    tmp1 = FromConstexpr_intptr_constexpr_intptr_0(state_, arraysize(wasm::kGpReturnRegisters));
    tmp2 = FromConstexpr_intptr_constexpr_intptr_0(state_, arraysize(wasm::kFpReturnRegisters));
    tmp3 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{p_gpRegs});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, kHeapObjectTag);
    tmp5 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp4});
    tmp6 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{p_fpRegs});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, kHeapObjectTag);
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp7});
    tmp9 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{p_stack});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, kHeapObjectTag);
    tmp11 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp10});
    tmp12 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp13 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp14 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructLocationAllocator_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp14}, TNode<IntPtrT>{tmp12}, TNode<BoolT>{tmp13}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=450&c=1
TNode<Object> JSToWasmObject_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<Uint32T> p_targetType, TNode<JSAny> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Object> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Uint32T> tmp0;
  TNode<Uint32T> tmp1;
  TNode<Uint32T> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kHasIndexBit);
    tmp1 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{p_targetType}, TNode<Uint32T>{tmp0});
    tmp2 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp1}, TNode<Uint32T>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<Uint32T> tmp4;
  TNode<Uint32T> tmp5;
  TNode<Uint32T> tmp6;
  TNode<Uint32T> tmp7;
  TNode<Uint32T> tmp8;
  TNode<Uint32T> tmp9;
  TNode<Uint32T> tmp10;
  TNode<BoolT> tmp11;
  TNode<Uint32T> tmp12;
  TNode<BoolT> tmp13;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIndexBits);
    tmp5 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{p_targetType}, TNode<Uint32T>{tmp4});
    tmp6 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIndexShift);
    tmp7 = CodeStubAssembler(state_).Word32Shr(TNode<Uint32T>{tmp5}, TNode<Uint32T>{tmp6});
    tmp8 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsNullableBit);
    tmp9 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{p_targetType}, TNode<Uint32T>{tmp8});
    tmp10 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp11 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp9}, TNode<Uint32T>{tmp10});
    tmp12 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(wasm::StandardType::kExtern));
    tmp13 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp7}, TNode<Uint32T>{tmp12});
    ca_.Branch(tmp13, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp14;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp14 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp11});
    ca_.Branch(tmp14, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  TNode<Null> tmp15;
  TNode<BoolT> tmp16;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp15 = Null_0(state_);
    tmp16 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{p_value}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp15});
    ca_.Goto(&block10, tmp16);
  }

  TNode<BoolT> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp17 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block10, tmp17);
  }

  TNode<BoolT> phi_bb10_7;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_7);
    ca_.Branch(phi_bb10_7, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kWasmTrapJSTypeError));
  }

  TNode<Uint32T> tmp18;
  TNode<Uint32T> tmp19;
  TNode<Uint32T> tmp20;
  TNode<BoolT> tmp21;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp18 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsSharedBit);
    tmp19 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{p_targetType}, TNode<Uint32T>{tmp18});
    tmp20 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp21 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp19}, TNode<Uint32T>{tmp20});
    ca_.Branch(tmp21, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block1, p_value);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block5);
  }

  TNode<Uint32T> tmp22;
  TNode<BoolT> tmp23;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp22 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(wasm::StandardType::kString));
    tmp23 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp7}, TNode<Uint32T>{tmp22});
    ca_.Branch(tmp23, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp24;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp24 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{p_value});
    ca_.Branch(tmp24, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kWasmTrapJSTypeError));
  }

  TNode<HeapObject> tmp25;
  TNode<BoolT> tmp26;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp25 = UnsafeCast_HeapObject_0(state_, TNode<Context>{p_context}, TNode<Object>{p_value});
    tmp26 = CodeStubAssembler(state_).IsString(TNode<HeapObject>{tmp25});
    ca_.Branch(tmp26, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block1, p_value);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Branch(tmp11, &block21, std::vector<compiler::Node*>{}, &block22, std::vector<compiler::Node*>{});
  }

  TNode<Null> tmp27;
  TNode<BoolT> tmp28;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp27 = Null_0(state_);
    tmp28 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{p_value}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp27});
    ca_.Goto(&block23, tmp28);
  }

  TNode<BoolT> tmp29;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp29 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block23, tmp29);
  }

  TNode<BoolT> phi_bb23_7;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_7);
    ca_.Branch(phi_bb23_7, &block19, std::vector<compiler::Node*>{}, &block20, std::vector<compiler::Node*>{});
  }

  TNode<WasmNull> tmp30;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp30 = kWasmNull_0(state_);
    ca_.Goto(&block1, tmp30);
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kWasmTrapJSTypeError));
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block3);
  }

  TNode<Smi> tmp31;
  TNode<JSAny> tmp32;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp31 = Convert_Smi_uint32_0(state_, TNode<Uint32T>{p_targetType});
    tmp32 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kWasmJSToWasmObject, p_context, p_value, tmp31)); 
    ca_.Goto(&block1, tmp32);
  }

  TNode<Object> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block24, phi_bb1_3);
  }

  TNode<Object> phi_bb24_3;
    ca_.Bind(&block24, &phi_bb24_3);
  return TNode<Object>{phi_bb24_3};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=478&c=1
void HandleF32Params_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TorqueStructLocationAllocator_0 p_locationAllocator, TorqueStructReference_intptr_0 p_toRef, TNode<JSAny> p_param) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    if ((wasm::kIsFpAlwaysDouble)) {
      ca_.Goto(&block2);
    } else {
      ca_.Goto(&block3);
    }
  }

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{p_locationAllocator.remainingFPRegs}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Float32T> tmp4;
  TNode<Float64T> tmp5;
  TNode<Float64T> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    std::tie(tmp2, tmp3) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{p_toRef.object}, TNode<IntPtrT>{p_toRef.offset}, TorqueStructUnsafe_0{}}).Flatten();
    tmp4 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_param);
    tmp5 = CodeStubAssembler(state_).ChangeFloat32ToFloat64(TNode<Float32T>{tmp4});
    tmp6 = CodeStubAssembler(state_).Float64SilenceNaN(TNode<Float64T>{tmp5});
    CodeStubAssembler(state_).StoreReference<Float64T>(CodeStubAssembler::Reference{tmp2, tmp3}, tmp6);
    ca_.Goto(&block8);
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Float32T> tmp9;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    std::tie(tmp7, tmp8) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{p_toRef.object}, TNode<IntPtrT>{p_toRef.offset}, TorqueStructUnsafe_0{}}).Flatten();
    tmp9 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_param);
    CodeStubAssembler(state_).StoreReference<Float32T>(CodeStubAssembler::Reference{tmp7, tmp8}, tmp9);
    ca_.Goto(&block8);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block4);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    if ((wasm::kIsBigEndian)) {
      ca_.Goto(&block9);
    } else {
      ca_.Goto(&block10);
    }
  }

  TNode<Float32T> tmp10;
  TNode<Uint32T> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp10 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_param);
    tmp11 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp10});
    tmp12 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp11});
    tmp13 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp14 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp13});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{p_toRef.object, p_toRef.offset}, tmp14);
    ca_.Goto(&block11);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    if ((wasm::kIsBigEndianOnSim)) {
      ca_.Goto(&block12);
    } else {
      ca_.Goto(&block13);
    }
  }

  TNode<IntPtrT> tmp15;
  TNode<BoolT> tmp16;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp15 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{p_locationAllocator.remainingFPRegs}, TNode<IntPtrT>{tmp15});
    ca_.Branch(tmp16, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<Float32T> tmp17;
  TNode<Uint32T> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp17 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_param);
    tmp18 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp17});
    tmp19 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp18});
    tmp20 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp21 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{tmp19}, TNode<IntPtrT>{tmp20});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{p_toRef.object, p_toRef.offset}, tmp21);
    ca_.Goto(&block18);
  }

  TNode<Float32T> tmp22;
  TNode<Uint32T> tmp23;
  TNode<IntPtrT> tmp24;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp22 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_param);
    tmp23 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp22});
    tmp24 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp23});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{p_toRef.object, p_toRef.offset}, tmp24);
    ca_.Goto(&block18);
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block14);
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block14);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block11);
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block4);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block19);
  }

    ca_.Bind(&block19);
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=505&c=1
TNode<JSAny> JSToWasmWrapperHelper_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<JSAny> p__receiver, TNode<JSFunction> p_target, TorqueStructArguments p_arguments, wasm::Promise p_promise) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block87(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block91(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block96(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block101(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block100(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT, IntPtrT> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT, IntPtrT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT, IntPtrT> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, IntPtrT, IntPtrT, BoolT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block122(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block123(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block127(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block129(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT> block124(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT> block125(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block139(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block140(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block145(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block146(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block147(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block156(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block158(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block161(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block157(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block154(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block163(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block164(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block165(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block168(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block172(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block173(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block174(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block178(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block179(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block181(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block177(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block171(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block185(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block193(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block196(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block198(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block194(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block191(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block189(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block201(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block202(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block204(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block205(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block207(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block208(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block203(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block200(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block210(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block211(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block213(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block214(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block217(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block212(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block209(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block219(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block218(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, Union<FixedArray, Smi>, IntPtrT> block220(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, Union<FixedArray, Smi>, IntPtrT> block221(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block226(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block227(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block187(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block170(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block131(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block230(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block233(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block234(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block231(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, JSAny> block232(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block235(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block238(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block239(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block242(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block240(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block245(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block251(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block252(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block256(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block257(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block259(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block260(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block262(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block263(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block258(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block255(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block246(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block241(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block236(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block266(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, IntPtrT> block267(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block271(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block272(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, BoolT> block273(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block270(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block269(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block274(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block275(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block277(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block278(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block280(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>> block281(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, JSAny> block279(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, IntPtrT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<FixedArray, Smi>, JSAny> block276(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block283(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<SharedFunctionInfo> tmp1;
  TNode<WasmExportedFunctionData> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp1 = CodeStubAssembler(state_).LoadReference<SharedFunctionInfo>(CodeStubAssembler::Reference{p_target, tmp0});
    tmp2 = CodeStubAssembler(state_).LoadSharedFunctionInfoWasmExportedFunctionData(TNode<SharedFunctionInfo>{tmp1});
    if (((CodeStubAssembler(state_).ConstexprBoolNot(((CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kPromise))) || (CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kStressSwitch)))))))) {
      ca_.Goto(&block2);
    } else {
      ca_.Goto(&block3);
    }
  }

  TNode<IntPtrT> tmp3;
  TNode<Cell> tmp4;
  TNode<Object> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp4 = CodeStubAssembler(state_).LoadReference<Cell>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = LoadCellValue_0(state_, TNode<Cell>{tmp4});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp5});
    tmp7 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp8 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp6}, TNode<Smi>{tmp7});
    ca_.Branch(tmp8, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 515});
      CodeStubAssembler(state_).FailAssert("Torque assert 'budget > 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Cell> tmp12;
  TNode<Smi> tmp13;
  TNode<BoolT> tmp14;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp10 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp6}, TNode<Smi>{tmp9});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp12 = CodeStubAssembler(state_).LoadReference<Cell>(CodeStubAssembler::Reference{tmp2, tmp11});
    StoreCellValue_0(state_, TNode<Cell>{tmp12}, TNode<Object>{tmp10});
    tmp13 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp14 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp10}, TNode<Smi>{tmp13});
    ca_.Branch(tmp14, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp15;
  TNode<JSAny> tmp16;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp15 = kNoContext_0(state_);
    tmp16 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kTierUpJSToWasmWrapper, tmp15, tmp2)); 
    ca_.Goto(&block8);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block4);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block4);
  }

  TNode<WasmInternalFunction> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<RawPtrT> tmp19;
  TNode<Union<WasmImportData, WasmTrustedInstanceData>> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Union<HeapObject, TaggedIndex>> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Union<HeapObject, TaggedIndex>> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<RawPtrT> tmp32;
  TNode<RawPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<Union<HeapObject, TaggedIndex>> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Undefined> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<BoolT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<BoolT> tmp42;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp17 = CodeStubAssembler(state_).LoadWasmInternalFunctionFromFunctionData(TNode<WasmFunctionData>{tmp2});
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp19 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{tmp17, tmp18});
    tmp20 = CodeStubAssembler(state_).LoadImplicitArgFromWasmInternalFunction(TNode<WasmInternalFunction>{tmp17});
    tmp21 = FromConstexpr_intptr_constexpr_intptr_0(state_, wasm::FunctionSig::kParameterCountOffset);
    std::tie(tmp22, tmp23) = GetRefAt_intptr_RawFunctionSigPtr_0(state_, TNode<RawPtrT>{tmp19}, TNode<IntPtrT>{tmp21}).Flatten();
    tmp24 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp22, tmp23});
    tmp25 = FromConstexpr_intptr_constexpr_intptr_0(state_, wasm::FunctionSig::kReturnCountOffset);
    std::tie(tmp26, tmp27) = GetRefAt_intptr_RawFunctionSigPtr_0(state_, TNode<RawPtrT>{tmp19}, TNode<IntPtrT>{tmp25}).Flatten();
    tmp28 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp26, tmp27});
    tmp29 = FromConstexpr_intptr_constexpr_intptr_0(state_, wasm::FunctionSig::kRepsOffset);
    std::tie(tmp30, tmp31) = GetRefAt_RawPtr_RawFunctionSigPtr_0(state_, TNode<RawPtrT>{tmp19}, TNode<IntPtrT>{tmp29}).Flatten();
    tmp32 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{tmp30, tmp31});
    tmp33 = (TNode<RawPtrT>{tmp32});
    tmp34 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp24}, TNode<IntPtrT>{tmp28});
    std::tie(tmp35, tmp36, tmp37) = NewOffHeapConstSlice_uint32_0(state_, TNode<RawPtrT>{tmp33}, TNode<IntPtrT>{tmp34}).Flatten();
    tmp38 = Undefined_0(state_);
    tmp39 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp40 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp41 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp42 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp41});
    ca_.Branch(tmp42, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{tmp38, tmp39, tmp40});
  }

  TNode<Smi> tmp43;
  TNode<JSArray> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<Union<HeapObject, TaggedIndex>> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<IntPtrT> tmp48;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp43 = CodeStubAssembler(state_).SmiFromIntPtr(TNode<IntPtrT>{tmp28});
    tmp44 = ca_.CallBuiltin<JSArray>(Builtin::kWasmAllocateJSArray, p_context, tmp43);
    tmp45 = Convert_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    compiler::CodeAssemblerLabel label49(&ca_);
    std::tie(tmp46, tmp47, tmp48) = Subslice_uint32_0(state_, TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp35}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp37}, TorqueStructUnsafe_0{}}, TNode<IntPtrT>{tmp45}, TNode<IntPtrT>{tmp28}, &label49).Flatten();
    ca_.Goto(&block13);
    if (label49.is_used()) {
      ca_.Bind(&label49);
      ca_.Goto(&block14);
    }
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/js-to-wasm.tq:551:19");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<BoolT> tmp52;
  TNode<BoolT> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<IntPtrT> tmp56;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    std::tie(tmp50, tmp51, tmp52, tmp53, tmp54) = NewReturnSlotAllocator_0(state_).Flatten();
    tmp55 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{tmp48});
    tmp56 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp47}, TNode<IntPtrT>{tmp55});
    ca_.Goto(&block18, tmp40, tmp50, tmp51, tmp52, tmp53, tmp54, tmp47);
  }

  TNode<BoolT> phi_bb18_19;
  TNode<IntPtrT> phi_bb18_23;
  TNode<IntPtrT> phi_bb18_24;
  TNode<BoolT> phi_bb18_25;
  TNode<BoolT> phi_bb18_26;
  TNode<IntPtrT> phi_bb18_27;
  TNode<IntPtrT> phi_bb18_29;
  TNode<BoolT> tmp57;
  TNode<BoolT> tmp58;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_19, &phi_bb18_23, &phi_bb18_24, &phi_bb18_25, &phi_bb18_26, &phi_bb18_27, &phi_bb18_29);
    tmp57 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb18_29}, TNode<IntPtrT>{tmp56});
    tmp58 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp57});
    ca_.Branch(tmp58, &block16, std::vector<compiler::Node*>{phi_bb18_19, phi_bb18_23, phi_bb18_24, phi_bb18_25, phi_bb18_26, phi_bb18_27, phi_bb18_29}, &block17, std::vector<compiler::Node*>{phi_bb18_19, phi_bb18_23, phi_bb18_24, phi_bb18_25, phi_bb18_26, phi_bb18_27, phi_bb18_29});
  }

  TNode<BoolT> phi_bb16_19;
  TNode<IntPtrT> phi_bb16_23;
  TNode<IntPtrT> phi_bb16_24;
  TNode<BoolT> phi_bb16_25;
  TNode<BoolT> phi_bb16_26;
  TNode<IntPtrT> phi_bb16_27;
  TNode<IntPtrT> phi_bb16_29;
  TNode<BoolT> tmp59;
  TNode<BoolT> tmp60;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_19, &phi_bb16_23, &phi_bb16_24, &phi_bb16_25, &phi_bb16_26, &phi_bb16_27, &phi_bb16_29);
    tmp59 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb16_29}, TNode<IntPtrT>{tmp56});
    tmp60 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp59});
    ca_.Branch(tmp60, &block22, std::vector<compiler::Node*>{phi_bb16_19, phi_bb16_23, phi_bb16_24, phi_bb16_25, phi_bb16_26, phi_bb16_27, phi_bb16_29}, &block23, std::vector<compiler::Node*>{phi_bb16_19, phi_bb16_23, phi_bb16_24, phi_bb16_25, phi_bb16_26, phi_bb16_27, phi_bb16_29});
  }

  TNode<BoolT> phi_bb23_19;
  TNode<IntPtrT> phi_bb23_23;
  TNode<IntPtrT> phi_bb23_24;
  TNode<BoolT> phi_bb23_25;
  TNode<BoolT> phi_bb23_26;
  TNode<IntPtrT> phi_bb23_27;
  TNode<IntPtrT> phi_bb23_29;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_19, &phi_bb23_23, &phi_bb23_24, &phi_bb23_25, &phi_bb23_26, &phi_bb23_27, &phi_bb23_29);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/torque-internal.tq", 245});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.Empty()' failed", pos_stack);
    }
  }

  TNode<BoolT> phi_bb22_19;
  TNode<IntPtrT> phi_bb22_23;
  TNode<IntPtrT> phi_bb22_24;
  TNode<BoolT> phi_bb22_25;
  TNode<BoolT> phi_bb22_26;
  TNode<IntPtrT> phi_bb22_27;
  TNode<IntPtrT> phi_bb22_29;
  TNode<Union<HeapObject, TaggedIndex>> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Uint32T> tmp65;
  TNode<Uint32T> tmp66;
  TNode<BoolT> tmp67;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_19, &phi_bb22_23, &phi_bb22_24, &phi_bb22_25, &phi_bb22_26, &phi_bb22_27, &phi_bb22_29);
    std::tie(tmp61, tmp62) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp46}, TNode<IntPtrT>{phi_bb22_29}).Flatten();
    tmp63 = FromConstexpr_intptr_constexpr_int31_0(state_, kInt32Size);
    tmp64 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb22_29}, TNode<IntPtrT>{tmp63});
    tmp65 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp61, tmp62});
    tmp66 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp67 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp65}, TNode<Uint32T>{tmp66});
    ca_.Branch(tmp67, &block25, std::vector<compiler::Node*>{phi_bb22_19, phi_bb22_23, phi_bb22_24, phi_bb22_25, phi_bb22_26, phi_bb22_27}, &block26, std::vector<compiler::Node*>{phi_bb22_19, phi_bb22_23, phi_bb22_24, phi_bb22_25, phi_bb22_26, phi_bb22_27});
  }

  TNode<BoolT> phi_bb25_19;
  TNode<IntPtrT> phi_bb25_23;
  TNode<IntPtrT> phi_bb25_24;
  TNode<BoolT> phi_bb25_25;
  TNode<BoolT> phi_bb25_26;
  TNode<IntPtrT> phi_bb25_27;
  TNode<IntPtrT> tmp68;
  TNode<BoolT> tmp69;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_19, &phi_bb25_23, &phi_bb25_24, &phi_bb25_25, &phi_bb25_26, &phi_bb25_27);
    tmp68 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp69 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb25_23}, TNode<IntPtrT>{tmp68});
    ca_.Branch(tmp69, &block29, std::vector<compiler::Node*>{phi_bb25_19, phi_bb25_23, phi_bb25_24, phi_bb25_25, phi_bb25_26, phi_bb25_27}, &block30, std::vector<compiler::Node*>{phi_bb25_19, phi_bb25_23, phi_bb25_24, phi_bb25_25, phi_bb25_26, phi_bb25_27});
  }

  TNode<BoolT> phi_bb29_19;
  TNode<IntPtrT> phi_bb29_23;
  TNode<IntPtrT> phi_bb29_24;
  TNode<BoolT> phi_bb29_25;
  TNode<BoolT> phi_bb29_26;
  TNode<IntPtrT> phi_bb29_27;
  TNode<IntPtrT> tmp70;
  TNode<IntPtrT> tmp71;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_19, &phi_bb29_23, &phi_bb29_24, &phi_bb29_25, &phi_bb29_26, &phi_bb29_27);
    tmp70 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp71 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb29_23}, TNode<IntPtrT>{tmp70});
    ca_.Goto(&block28, phi_bb29_19, tmp71, phi_bb29_24, phi_bb29_25, phi_bb29_26, phi_bb29_27);
  }

  TNode<BoolT> phi_bb30_19;
  TNode<IntPtrT> phi_bb30_23;
  TNode<IntPtrT> phi_bb30_24;
  TNode<BoolT> phi_bb30_25;
  TNode<BoolT> phi_bb30_26;
  TNode<IntPtrT> phi_bb30_27;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_19, &phi_bb30_23, &phi_bb30_24, &phi_bb30_25, &phi_bb30_26, &phi_bb30_27);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block32, phi_bb30_19, phi_bb30_23, phi_bb30_24, phi_bb30_25, phi_bb30_26, phi_bb30_27);
    } else {
      ca_.Goto(&block33, phi_bb30_19, phi_bb30_23, phi_bb30_24, phi_bb30_25, phi_bb30_26, phi_bb30_27);
    }
  }

  TNode<BoolT> phi_bb32_19;
  TNode<IntPtrT> phi_bb32_23;
  TNode<IntPtrT> phi_bb32_24;
  TNode<BoolT> phi_bb32_25;
  TNode<BoolT> phi_bb32_26;
  TNode<IntPtrT> phi_bb32_27;
  TNode<IntPtrT> tmp72;
  TNode<IntPtrT> tmp73;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_19, &phi_bb32_23, &phi_bb32_24, &phi_bb32_25, &phi_bb32_26, &phi_bb32_27);
    tmp72 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp73 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb32_27}, TNode<IntPtrT>{tmp72});
    ca_.Goto(&block34, phi_bb32_19, phi_bb32_23, phi_bb32_24, phi_bb32_25, phi_bb32_26, tmp73);
  }

  TNode<BoolT> phi_bb33_19;
  TNode<IntPtrT> phi_bb33_23;
  TNode<IntPtrT> phi_bb33_24;
  TNode<BoolT> phi_bb33_25;
  TNode<BoolT> phi_bb33_26;
  TNode<IntPtrT> phi_bb33_27;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_19, &phi_bb33_23, &phi_bb33_24, &phi_bb33_25, &phi_bb33_26, &phi_bb33_27);
    ca_.Branch(phi_bb33_25, &block35, std::vector<compiler::Node*>{phi_bb33_19, phi_bb33_23, phi_bb33_24, phi_bb33_25, phi_bb33_26, phi_bb33_27}, &block36, std::vector<compiler::Node*>{phi_bb33_19, phi_bb33_23, phi_bb33_24, phi_bb33_25, phi_bb33_26, phi_bb33_27});
  }

  TNode<BoolT> phi_bb35_19;
  TNode<IntPtrT> phi_bb35_23;
  TNode<IntPtrT> phi_bb35_24;
  TNode<BoolT> phi_bb35_25;
  TNode<BoolT> phi_bb35_26;
  TNode<IntPtrT> phi_bb35_27;
  TNode<BoolT> tmp74;
  TNode<BoolT> tmp75;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_19, &phi_bb35_23, &phi_bb35_24, &phi_bb35_25, &phi_bb35_26, &phi_bb35_27);
    tmp74 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp75 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block37, phi_bb35_19, phi_bb35_23, phi_bb35_24, tmp74, tmp75, phi_bb35_27);
  }

  TNode<BoolT> phi_bb36_19;
  TNode<IntPtrT> phi_bb36_23;
  TNode<IntPtrT> phi_bb36_24;
  TNode<BoolT> phi_bb36_25;
  TNode<BoolT> phi_bb36_26;
  TNode<IntPtrT> phi_bb36_27;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<BoolT> tmp78;
  TNode<BoolT> tmp79;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_19, &phi_bb36_23, &phi_bb36_24, &phi_bb36_25, &phi_bb36_26, &phi_bb36_27);
    tmp76 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp77 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb36_27}, TNode<IntPtrT>{tmp76});
    tmp78 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp79 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block37, phi_bb36_19, phi_bb36_23, phi_bb36_24, tmp78, tmp79, tmp77);
  }

  TNode<BoolT> phi_bb37_19;
  TNode<IntPtrT> phi_bb37_23;
  TNode<IntPtrT> phi_bb37_24;
  TNode<BoolT> phi_bb37_25;
  TNode<BoolT> phi_bb37_26;
  TNode<IntPtrT> phi_bb37_27;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_19, &phi_bb37_23, &phi_bb37_24, &phi_bb37_25, &phi_bb37_26, &phi_bb37_27);
    ca_.Goto(&block34, phi_bb37_19, phi_bb37_23, phi_bb37_24, phi_bb37_25, phi_bb37_26, phi_bb37_27);
  }

  TNode<BoolT> phi_bb34_19;
  TNode<IntPtrT> phi_bb34_23;
  TNode<IntPtrT> phi_bb34_24;
  TNode<BoolT> phi_bb34_25;
  TNode<BoolT> phi_bb34_26;
  TNode<IntPtrT> phi_bb34_27;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_19, &phi_bb34_23, &phi_bb34_24, &phi_bb34_25, &phi_bb34_26, &phi_bb34_27);
    ca_.Goto(&block28, phi_bb34_19, phi_bb34_23, phi_bb34_24, phi_bb34_25, phi_bb34_26, phi_bb34_27);
  }

  TNode<BoolT> phi_bb28_19;
  TNode<IntPtrT> phi_bb28_23;
  TNode<IntPtrT> phi_bb28_24;
  TNode<BoolT> phi_bb28_25;
  TNode<BoolT> phi_bb28_26;
  TNode<IntPtrT> phi_bb28_27;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_19, &phi_bb28_23, &phi_bb28_24, &phi_bb28_25, &phi_bb28_26, &phi_bb28_27);
    ca_.Goto(&block27, phi_bb28_19, phi_bb28_23, phi_bb28_24, phi_bb28_25, phi_bb28_26, phi_bb28_27);
  }

  TNode<BoolT> phi_bb26_19;
  TNode<IntPtrT> phi_bb26_23;
  TNode<IntPtrT> phi_bb26_24;
  TNode<BoolT> phi_bb26_25;
  TNode<BoolT> phi_bb26_26;
  TNode<IntPtrT> phi_bb26_27;
  TNode<Uint32T> tmp80;
  TNode<BoolT> tmp81;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_19, &phi_bb26_23, &phi_bb26_24, &phi_bb26_25, &phi_bb26_26, &phi_bb26_27);
    tmp80 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp81 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp65}, TNode<Uint32T>{tmp80});
    ca_.Branch(tmp81, &block38, std::vector<compiler::Node*>{phi_bb26_19, phi_bb26_23, phi_bb26_24, phi_bb26_25, phi_bb26_26, phi_bb26_27}, &block39, std::vector<compiler::Node*>{phi_bb26_19, phi_bb26_23, phi_bb26_24, phi_bb26_25, phi_bb26_26, phi_bb26_27});
  }

  TNode<BoolT> phi_bb38_19;
  TNode<IntPtrT> phi_bb38_23;
  TNode<IntPtrT> phi_bb38_24;
  TNode<BoolT> phi_bb38_25;
  TNode<BoolT> phi_bb38_26;
  TNode<IntPtrT> phi_bb38_27;
  TNode<IntPtrT> tmp82;
  TNode<BoolT> tmp83;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_19, &phi_bb38_23, &phi_bb38_24, &phi_bb38_25, &phi_bb38_26, &phi_bb38_27);
    tmp82 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp83 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb38_23}, TNode<IntPtrT>{tmp82});
    ca_.Branch(tmp83, &block42, std::vector<compiler::Node*>{phi_bb38_19, phi_bb38_23, phi_bb38_24, phi_bb38_25, phi_bb38_26, phi_bb38_27}, &block43, std::vector<compiler::Node*>{phi_bb38_19, phi_bb38_23, phi_bb38_24, phi_bb38_25, phi_bb38_26, phi_bb38_27});
  }

  TNode<BoolT> phi_bb42_19;
  TNode<IntPtrT> phi_bb42_23;
  TNode<IntPtrT> phi_bb42_24;
  TNode<BoolT> phi_bb42_25;
  TNode<BoolT> phi_bb42_26;
  TNode<IntPtrT> phi_bb42_27;
  TNode<IntPtrT> tmp84;
  TNode<IntPtrT> tmp85;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_19, &phi_bb42_23, &phi_bb42_24, &phi_bb42_25, &phi_bb42_26, &phi_bb42_27);
    tmp84 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp85 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb42_23}, TNode<IntPtrT>{tmp84});
    ca_.Goto(&block41, phi_bb42_19, tmp85, phi_bb42_24, phi_bb42_25, phi_bb42_26, phi_bb42_27);
  }

  TNode<BoolT> phi_bb43_19;
  TNode<IntPtrT> phi_bb43_23;
  TNode<IntPtrT> phi_bb43_24;
  TNode<BoolT> phi_bb43_25;
  TNode<BoolT> phi_bb43_26;
  TNode<IntPtrT> phi_bb43_27;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_19, &phi_bb43_23, &phi_bb43_24, &phi_bb43_25, &phi_bb43_26, &phi_bb43_27);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block45, phi_bb43_19, phi_bb43_23, phi_bb43_24, phi_bb43_25, phi_bb43_26, phi_bb43_27);
    } else {
      ca_.Goto(&block46, phi_bb43_19, phi_bb43_23, phi_bb43_24, phi_bb43_25, phi_bb43_26, phi_bb43_27);
    }
  }

  TNode<BoolT> phi_bb45_19;
  TNode<IntPtrT> phi_bb45_23;
  TNode<IntPtrT> phi_bb45_24;
  TNode<BoolT> phi_bb45_25;
  TNode<BoolT> phi_bb45_26;
  TNode<IntPtrT> phi_bb45_27;
  TNode<IntPtrT> tmp86;
  TNode<IntPtrT> tmp87;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_19, &phi_bb45_23, &phi_bb45_24, &phi_bb45_25, &phi_bb45_26, &phi_bb45_27);
    tmp86 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp87 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb45_27}, TNode<IntPtrT>{tmp86});
    ca_.Goto(&block47, phi_bb45_19, phi_bb45_23, phi_bb45_24, phi_bb45_25, phi_bb45_26, tmp87);
  }

  TNode<BoolT> phi_bb46_19;
  TNode<IntPtrT> phi_bb46_23;
  TNode<IntPtrT> phi_bb46_24;
  TNode<BoolT> phi_bb46_25;
  TNode<BoolT> phi_bb46_26;
  TNode<IntPtrT> phi_bb46_27;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_19, &phi_bb46_23, &phi_bb46_24, &phi_bb46_25, &phi_bb46_26, &phi_bb46_27);
    ca_.Branch(phi_bb46_25, &block48, std::vector<compiler::Node*>{phi_bb46_19, phi_bb46_23, phi_bb46_24, phi_bb46_25, phi_bb46_26, phi_bb46_27}, &block49, std::vector<compiler::Node*>{phi_bb46_19, phi_bb46_23, phi_bb46_24, phi_bb46_25, phi_bb46_26, phi_bb46_27});
  }

  TNode<BoolT> phi_bb48_19;
  TNode<IntPtrT> phi_bb48_23;
  TNode<IntPtrT> phi_bb48_24;
  TNode<BoolT> phi_bb48_25;
  TNode<BoolT> phi_bb48_26;
  TNode<IntPtrT> phi_bb48_27;
  TNode<BoolT> tmp88;
  TNode<BoolT> tmp89;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_19, &phi_bb48_23, &phi_bb48_24, &phi_bb48_25, &phi_bb48_26, &phi_bb48_27);
    tmp88 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp89 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block50, phi_bb48_19, phi_bb48_23, phi_bb48_24, tmp88, tmp89, phi_bb48_27);
  }

  TNode<BoolT> phi_bb49_19;
  TNode<IntPtrT> phi_bb49_23;
  TNode<IntPtrT> phi_bb49_24;
  TNode<BoolT> phi_bb49_25;
  TNode<BoolT> phi_bb49_26;
  TNode<IntPtrT> phi_bb49_27;
  TNode<IntPtrT> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<BoolT> tmp92;
  TNode<BoolT> tmp93;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_19, &phi_bb49_23, &phi_bb49_24, &phi_bb49_25, &phi_bb49_26, &phi_bb49_27);
    tmp90 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp91 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb49_27}, TNode<IntPtrT>{tmp90});
    tmp92 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp93 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block50, phi_bb49_19, phi_bb49_23, phi_bb49_24, tmp92, tmp93, tmp91);
  }

  TNode<BoolT> phi_bb50_19;
  TNode<IntPtrT> phi_bb50_23;
  TNode<IntPtrT> phi_bb50_24;
  TNode<BoolT> phi_bb50_25;
  TNode<BoolT> phi_bb50_26;
  TNode<IntPtrT> phi_bb50_27;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_19, &phi_bb50_23, &phi_bb50_24, &phi_bb50_25, &phi_bb50_26, &phi_bb50_27);
    ca_.Goto(&block47, phi_bb50_19, phi_bb50_23, phi_bb50_24, phi_bb50_25, phi_bb50_26, phi_bb50_27);
  }

  TNode<BoolT> phi_bb47_19;
  TNode<IntPtrT> phi_bb47_23;
  TNode<IntPtrT> phi_bb47_24;
  TNode<BoolT> phi_bb47_25;
  TNode<BoolT> phi_bb47_26;
  TNode<IntPtrT> phi_bb47_27;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_19, &phi_bb47_23, &phi_bb47_24, &phi_bb47_25, &phi_bb47_26, &phi_bb47_27);
    ca_.Goto(&block41, phi_bb47_19, phi_bb47_23, phi_bb47_24, phi_bb47_25, phi_bb47_26, phi_bb47_27);
  }

  TNode<BoolT> phi_bb41_19;
  TNode<IntPtrT> phi_bb41_23;
  TNode<IntPtrT> phi_bb41_24;
  TNode<BoolT> phi_bb41_25;
  TNode<BoolT> phi_bb41_26;
  TNode<IntPtrT> phi_bb41_27;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_19, &phi_bb41_23, &phi_bb41_24, &phi_bb41_25, &phi_bb41_26, &phi_bb41_27);
    if (((CodeStubAssembler(state_).ConstexprBoolNot((CodeStubAssembler(state_).Is64()))))) {
      ca_.Goto(&block51, phi_bb41_19, phi_bb41_23, phi_bb41_24, phi_bb41_25, phi_bb41_26, phi_bb41_27);
    } else {
      ca_.Goto(&block52, phi_bb41_19, phi_bb41_23, phi_bb41_24, phi_bb41_25, phi_bb41_26, phi_bb41_27);
    }
  }

  TNode<BoolT> phi_bb51_19;
  TNode<IntPtrT> phi_bb51_23;
  TNode<IntPtrT> phi_bb51_24;
  TNode<BoolT> phi_bb51_25;
  TNode<BoolT> phi_bb51_26;
  TNode<IntPtrT> phi_bb51_27;
  TNode<IntPtrT> tmp94;
  TNode<BoolT> tmp95;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_19, &phi_bb51_23, &phi_bb51_24, &phi_bb51_25, &phi_bb51_26, &phi_bb51_27);
    tmp94 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp95 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb51_23}, TNode<IntPtrT>{tmp94});
    ca_.Branch(tmp95, &block55, std::vector<compiler::Node*>{phi_bb51_19, phi_bb51_23, phi_bb51_24, phi_bb51_25, phi_bb51_26, phi_bb51_27}, &block56, std::vector<compiler::Node*>{phi_bb51_19, phi_bb51_23, phi_bb51_24, phi_bb51_25, phi_bb51_26, phi_bb51_27});
  }

  TNode<BoolT> phi_bb55_19;
  TNode<IntPtrT> phi_bb55_23;
  TNode<IntPtrT> phi_bb55_24;
  TNode<BoolT> phi_bb55_25;
  TNode<BoolT> phi_bb55_26;
  TNode<IntPtrT> phi_bb55_27;
  TNode<IntPtrT> tmp96;
  TNode<IntPtrT> tmp97;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_19, &phi_bb55_23, &phi_bb55_24, &phi_bb55_25, &phi_bb55_26, &phi_bb55_27);
    tmp96 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp97 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb55_23}, TNode<IntPtrT>{tmp96});
    ca_.Goto(&block54, phi_bb55_19, tmp97, phi_bb55_24, phi_bb55_25, phi_bb55_26, phi_bb55_27);
  }

  TNode<BoolT> phi_bb56_19;
  TNode<IntPtrT> phi_bb56_23;
  TNode<IntPtrT> phi_bb56_24;
  TNode<BoolT> phi_bb56_25;
  TNode<BoolT> phi_bb56_26;
  TNode<IntPtrT> phi_bb56_27;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_19, &phi_bb56_23, &phi_bb56_24, &phi_bb56_25, &phi_bb56_26, &phi_bb56_27);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block58, phi_bb56_19, phi_bb56_23, phi_bb56_24, phi_bb56_25, phi_bb56_26, phi_bb56_27);
    } else {
      ca_.Goto(&block59, phi_bb56_19, phi_bb56_23, phi_bb56_24, phi_bb56_25, phi_bb56_26, phi_bb56_27);
    }
  }

  TNode<BoolT> phi_bb58_19;
  TNode<IntPtrT> phi_bb58_23;
  TNode<IntPtrT> phi_bb58_24;
  TNode<BoolT> phi_bb58_25;
  TNode<BoolT> phi_bb58_26;
  TNode<IntPtrT> phi_bb58_27;
  TNode<IntPtrT> tmp98;
  TNode<IntPtrT> tmp99;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_19, &phi_bb58_23, &phi_bb58_24, &phi_bb58_25, &phi_bb58_26, &phi_bb58_27);
    tmp98 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp99 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb58_27}, TNode<IntPtrT>{tmp98});
    ca_.Goto(&block60, phi_bb58_19, phi_bb58_23, phi_bb58_24, phi_bb58_25, phi_bb58_26, tmp99);
  }

  TNode<BoolT> phi_bb59_19;
  TNode<IntPtrT> phi_bb59_23;
  TNode<IntPtrT> phi_bb59_24;
  TNode<BoolT> phi_bb59_25;
  TNode<BoolT> phi_bb59_26;
  TNode<IntPtrT> phi_bb59_27;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_19, &phi_bb59_23, &phi_bb59_24, &phi_bb59_25, &phi_bb59_26, &phi_bb59_27);
    ca_.Branch(phi_bb59_25, &block61, std::vector<compiler::Node*>{phi_bb59_19, phi_bb59_23, phi_bb59_24, phi_bb59_25, phi_bb59_26, phi_bb59_27}, &block62, std::vector<compiler::Node*>{phi_bb59_19, phi_bb59_23, phi_bb59_24, phi_bb59_25, phi_bb59_26, phi_bb59_27});
  }

  TNode<BoolT> phi_bb61_19;
  TNode<IntPtrT> phi_bb61_23;
  TNode<IntPtrT> phi_bb61_24;
  TNode<BoolT> phi_bb61_25;
  TNode<BoolT> phi_bb61_26;
  TNode<IntPtrT> phi_bb61_27;
  TNode<BoolT> tmp100;
  TNode<BoolT> tmp101;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_19, &phi_bb61_23, &phi_bb61_24, &phi_bb61_25, &phi_bb61_26, &phi_bb61_27);
    tmp100 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp101 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block63, phi_bb61_19, phi_bb61_23, phi_bb61_24, tmp100, tmp101, phi_bb61_27);
  }

  TNode<BoolT> phi_bb62_19;
  TNode<IntPtrT> phi_bb62_23;
  TNode<IntPtrT> phi_bb62_24;
  TNode<BoolT> phi_bb62_25;
  TNode<BoolT> phi_bb62_26;
  TNode<IntPtrT> phi_bb62_27;
  TNode<IntPtrT> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<BoolT> tmp104;
  TNode<BoolT> tmp105;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_19, &phi_bb62_23, &phi_bb62_24, &phi_bb62_25, &phi_bb62_26, &phi_bb62_27);
    tmp102 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp103 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb62_27}, TNode<IntPtrT>{tmp102});
    tmp104 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp105 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block63, phi_bb62_19, phi_bb62_23, phi_bb62_24, tmp104, tmp105, tmp103);
  }

  TNode<BoolT> phi_bb63_19;
  TNode<IntPtrT> phi_bb63_23;
  TNode<IntPtrT> phi_bb63_24;
  TNode<BoolT> phi_bb63_25;
  TNode<BoolT> phi_bb63_26;
  TNode<IntPtrT> phi_bb63_27;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_19, &phi_bb63_23, &phi_bb63_24, &phi_bb63_25, &phi_bb63_26, &phi_bb63_27);
    ca_.Goto(&block60, phi_bb63_19, phi_bb63_23, phi_bb63_24, phi_bb63_25, phi_bb63_26, phi_bb63_27);
  }

  TNode<BoolT> phi_bb60_19;
  TNode<IntPtrT> phi_bb60_23;
  TNode<IntPtrT> phi_bb60_24;
  TNode<BoolT> phi_bb60_25;
  TNode<BoolT> phi_bb60_26;
  TNode<IntPtrT> phi_bb60_27;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_19, &phi_bb60_23, &phi_bb60_24, &phi_bb60_25, &phi_bb60_26, &phi_bb60_27);
    ca_.Goto(&block54, phi_bb60_19, phi_bb60_23, phi_bb60_24, phi_bb60_25, phi_bb60_26, phi_bb60_27);
  }

  TNode<BoolT> phi_bb54_19;
  TNode<IntPtrT> phi_bb54_23;
  TNode<IntPtrT> phi_bb54_24;
  TNode<BoolT> phi_bb54_25;
  TNode<BoolT> phi_bb54_26;
  TNode<IntPtrT> phi_bb54_27;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_19, &phi_bb54_23, &phi_bb54_24, &phi_bb54_25, &phi_bb54_26, &phi_bb54_27);
    ca_.Goto(&block53, phi_bb54_19, phi_bb54_23, phi_bb54_24, phi_bb54_25, phi_bb54_26, phi_bb54_27);
  }

  TNode<BoolT> phi_bb52_19;
  TNode<IntPtrT> phi_bb52_23;
  TNode<IntPtrT> phi_bb52_24;
  TNode<BoolT> phi_bb52_25;
  TNode<BoolT> phi_bb52_26;
  TNode<IntPtrT> phi_bb52_27;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_19, &phi_bb52_23, &phi_bb52_24, &phi_bb52_25, &phi_bb52_26, &phi_bb52_27);
    ca_.Goto(&block53, phi_bb52_19, phi_bb52_23, phi_bb52_24, phi_bb52_25, phi_bb52_26, phi_bb52_27);
  }

  TNode<BoolT> phi_bb53_19;
  TNode<IntPtrT> phi_bb53_23;
  TNode<IntPtrT> phi_bb53_24;
  TNode<BoolT> phi_bb53_25;
  TNode<BoolT> phi_bb53_26;
  TNode<IntPtrT> phi_bb53_27;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_19, &phi_bb53_23, &phi_bb53_24, &phi_bb53_25, &phi_bb53_26, &phi_bb53_27);
    ca_.Goto(&block40, phi_bb53_19, phi_bb53_23, phi_bb53_24, phi_bb53_25, phi_bb53_26, phi_bb53_27);
  }

  TNode<BoolT> phi_bb39_19;
  TNode<IntPtrT> phi_bb39_23;
  TNode<IntPtrT> phi_bb39_24;
  TNode<BoolT> phi_bb39_25;
  TNode<BoolT> phi_bb39_26;
  TNode<IntPtrT> phi_bb39_27;
  TNode<Uint32T> tmp106;
  TNode<BoolT> tmp107;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_19, &phi_bb39_23, &phi_bb39_24, &phi_bb39_25, &phi_bb39_26, &phi_bb39_27);
    tmp106 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp107 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp65}, TNode<Uint32T>{tmp106});
    ca_.Branch(tmp107, &block64, std::vector<compiler::Node*>{phi_bb39_19, phi_bb39_23, phi_bb39_24, phi_bb39_25, phi_bb39_26, phi_bb39_27}, &block65, std::vector<compiler::Node*>{phi_bb39_19, phi_bb39_23, phi_bb39_24, phi_bb39_25, phi_bb39_26, phi_bb39_27});
  }

  TNode<BoolT> phi_bb64_19;
  TNode<IntPtrT> phi_bb64_23;
  TNode<IntPtrT> phi_bb64_24;
  TNode<BoolT> phi_bb64_25;
  TNode<BoolT> phi_bb64_26;
  TNode<IntPtrT> phi_bb64_27;
  TNode<IntPtrT> tmp108;
  TNode<BoolT> tmp109;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_19, &phi_bb64_23, &phi_bb64_24, &phi_bb64_25, &phi_bb64_26, &phi_bb64_27);
    tmp108 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp109 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb64_24}, TNode<IntPtrT>{tmp108});
    ca_.Branch(tmp109, &block68, std::vector<compiler::Node*>{phi_bb64_19, phi_bb64_23, phi_bb64_24, phi_bb64_25, phi_bb64_26, phi_bb64_27}, &block69, std::vector<compiler::Node*>{phi_bb64_19, phi_bb64_23, phi_bb64_24, phi_bb64_25, phi_bb64_26, phi_bb64_27});
  }

  TNode<BoolT> phi_bb68_19;
  TNode<IntPtrT> phi_bb68_23;
  TNode<IntPtrT> phi_bb68_24;
  TNode<BoolT> phi_bb68_25;
  TNode<BoolT> phi_bb68_26;
  TNode<IntPtrT> phi_bb68_27;
  TNode<IntPtrT> tmp110;
  TNode<IntPtrT> tmp111;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_19, &phi_bb68_23, &phi_bb68_24, &phi_bb68_25, &phi_bb68_26, &phi_bb68_27);
    tmp110 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp111 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb68_24}, TNode<IntPtrT>{tmp110});
    ca_.Goto(&block67, phi_bb68_19, phi_bb68_23, tmp111, phi_bb68_25, phi_bb68_26, phi_bb68_27);
  }

  TNode<BoolT> phi_bb69_19;
  TNode<IntPtrT> phi_bb69_23;
  TNode<IntPtrT> phi_bb69_24;
  TNode<BoolT> phi_bb69_25;
  TNode<BoolT> phi_bb69_26;
  TNode<IntPtrT> phi_bb69_27;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_19, &phi_bb69_23, &phi_bb69_24, &phi_bb69_25, &phi_bb69_26, &phi_bb69_27);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block71, phi_bb69_19, phi_bb69_23, phi_bb69_24, phi_bb69_25, phi_bb69_26, phi_bb69_27);
    } else {
      ca_.Goto(&block72, phi_bb69_19, phi_bb69_23, phi_bb69_24, phi_bb69_25, phi_bb69_26, phi_bb69_27);
    }
  }

  TNode<BoolT> phi_bb71_19;
  TNode<IntPtrT> phi_bb71_23;
  TNode<IntPtrT> phi_bb71_24;
  TNode<BoolT> phi_bb71_25;
  TNode<BoolT> phi_bb71_26;
  TNode<IntPtrT> phi_bb71_27;
  TNode<IntPtrT> tmp112;
  TNode<IntPtrT> tmp113;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_19, &phi_bb71_23, &phi_bb71_24, &phi_bb71_25, &phi_bb71_26, &phi_bb71_27);
    tmp112 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp113 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb71_27}, TNode<IntPtrT>{tmp112});
    ca_.Goto(&block73, phi_bb71_19, phi_bb71_23, phi_bb71_24, phi_bb71_25, phi_bb71_26, tmp113);
  }

  TNode<BoolT> phi_bb72_19;
  TNode<IntPtrT> phi_bb72_23;
  TNode<IntPtrT> phi_bb72_24;
  TNode<BoolT> phi_bb72_25;
  TNode<BoolT> phi_bb72_26;
  TNode<IntPtrT> phi_bb72_27;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_19, &phi_bb72_23, &phi_bb72_24, &phi_bb72_25, &phi_bb72_26, &phi_bb72_27);
    ca_.Branch(phi_bb72_25, &block74, std::vector<compiler::Node*>{phi_bb72_19, phi_bb72_23, phi_bb72_24, phi_bb72_25, phi_bb72_26, phi_bb72_27}, &block75, std::vector<compiler::Node*>{phi_bb72_19, phi_bb72_23, phi_bb72_24, phi_bb72_25, phi_bb72_26, phi_bb72_27});
  }

  TNode<BoolT> phi_bb74_19;
  TNode<IntPtrT> phi_bb74_23;
  TNode<IntPtrT> phi_bb74_24;
  TNode<BoolT> phi_bb74_25;
  TNode<BoolT> phi_bb74_26;
  TNode<IntPtrT> phi_bb74_27;
  TNode<BoolT> tmp114;
  TNode<BoolT> tmp115;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_19, &phi_bb74_23, &phi_bb74_24, &phi_bb74_25, &phi_bb74_26, &phi_bb74_27);
    tmp114 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp115 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block76, phi_bb74_19, phi_bb74_23, phi_bb74_24, tmp114, tmp115, phi_bb74_27);
  }

  TNode<BoolT> phi_bb75_19;
  TNode<IntPtrT> phi_bb75_23;
  TNode<IntPtrT> phi_bb75_24;
  TNode<BoolT> phi_bb75_25;
  TNode<BoolT> phi_bb75_26;
  TNode<IntPtrT> phi_bb75_27;
  TNode<IntPtrT> tmp116;
  TNode<IntPtrT> tmp117;
  TNode<BoolT> tmp118;
  TNode<BoolT> tmp119;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_19, &phi_bb75_23, &phi_bb75_24, &phi_bb75_25, &phi_bb75_26, &phi_bb75_27);
    tmp116 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp117 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb75_27}, TNode<IntPtrT>{tmp116});
    tmp118 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp119 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block76, phi_bb75_19, phi_bb75_23, phi_bb75_24, tmp118, tmp119, tmp117);
  }

  TNode<BoolT> phi_bb76_19;
  TNode<IntPtrT> phi_bb76_23;
  TNode<IntPtrT> phi_bb76_24;
  TNode<BoolT> phi_bb76_25;
  TNode<BoolT> phi_bb76_26;
  TNode<IntPtrT> phi_bb76_27;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_19, &phi_bb76_23, &phi_bb76_24, &phi_bb76_25, &phi_bb76_26, &phi_bb76_27);
    ca_.Goto(&block73, phi_bb76_19, phi_bb76_23, phi_bb76_24, phi_bb76_25, phi_bb76_26, phi_bb76_27);
  }

  TNode<BoolT> phi_bb73_19;
  TNode<IntPtrT> phi_bb73_23;
  TNode<IntPtrT> phi_bb73_24;
  TNode<BoolT> phi_bb73_25;
  TNode<BoolT> phi_bb73_26;
  TNode<IntPtrT> phi_bb73_27;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_19, &phi_bb73_23, &phi_bb73_24, &phi_bb73_25, &phi_bb73_26, &phi_bb73_27);
    ca_.Goto(&block67, phi_bb73_19, phi_bb73_23, phi_bb73_24, phi_bb73_25, phi_bb73_26, phi_bb73_27);
  }

  TNode<BoolT> phi_bb67_19;
  TNode<IntPtrT> phi_bb67_23;
  TNode<IntPtrT> phi_bb67_24;
  TNode<BoolT> phi_bb67_25;
  TNode<BoolT> phi_bb67_26;
  TNode<IntPtrT> phi_bb67_27;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_19, &phi_bb67_23, &phi_bb67_24, &phi_bb67_25, &phi_bb67_26, &phi_bb67_27);
    ca_.Goto(&block66, phi_bb67_19, phi_bb67_23, phi_bb67_24, phi_bb67_25, phi_bb67_26, phi_bb67_27);
  }

  TNode<BoolT> phi_bb65_19;
  TNode<IntPtrT> phi_bb65_23;
  TNode<IntPtrT> phi_bb65_24;
  TNode<BoolT> phi_bb65_25;
  TNode<BoolT> phi_bb65_26;
  TNode<IntPtrT> phi_bb65_27;
  TNode<Uint32T> tmp120;
  TNode<BoolT> tmp121;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_19, &phi_bb65_23, &phi_bb65_24, &phi_bb65_25, &phi_bb65_26, &phi_bb65_27);
    tmp120 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp121 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp65}, TNode<Uint32T>{tmp120});
    ca_.Branch(tmp121, &block77, std::vector<compiler::Node*>{phi_bb65_19, phi_bb65_23, phi_bb65_24, phi_bb65_25, phi_bb65_26, phi_bb65_27}, &block78, std::vector<compiler::Node*>{phi_bb65_19, phi_bb65_23, phi_bb65_24, phi_bb65_25, phi_bb65_26, phi_bb65_27});
  }

  TNode<BoolT> phi_bb77_19;
  TNode<IntPtrT> phi_bb77_23;
  TNode<IntPtrT> phi_bb77_24;
  TNode<BoolT> phi_bb77_25;
  TNode<BoolT> phi_bb77_26;
  TNode<IntPtrT> phi_bb77_27;
  TNode<IntPtrT> tmp122;
  TNode<BoolT> tmp123;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_19, &phi_bb77_23, &phi_bb77_24, &phi_bb77_25, &phi_bb77_26, &phi_bb77_27);
    tmp122 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp123 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb77_24}, TNode<IntPtrT>{tmp122});
    ca_.Branch(tmp123, &block81, std::vector<compiler::Node*>{phi_bb77_19, phi_bb77_23, phi_bb77_24, phi_bb77_25, phi_bb77_26, phi_bb77_27}, &block82, std::vector<compiler::Node*>{phi_bb77_19, phi_bb77_23, phi_bb77_24, phi_bb77_25, phi_bb77_26, phi_bb77_27});
  }

  TNode<BoolT> phi_bb81_19;
  TNode<IntPtrT> phi_bb81_23;
  TNode<IntPtrT> phi_bb81_24;
  TNode<BoolT> phi_bb81_25;
  TNode<BoolT> phi_bb81_26;
  TNode<IntPtrT> phi_bb81_27;
  TNode<IntPtrT> tmp124;
  TNode<IntPtrT> tmp125;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_19, &phi_bb81_23, &phi_bb81_24, &phi_bb81_25, &phi_bb81_26, &phi_bb81_27);
    tmp124 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp125 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb81_24}, TNode<IntPtrT>{tmp124});
    ca_.Goto(&block80, phi_bb81_19, phi_bb81_23, tmp125, phi_bb81_25, phi_bb81_26, phi_bb81_27);
  }

  TNode<BoolT> phi_bb82_19;
  TNode<IntPtrT> phi_bb82_23;
  TNode<IntPtrT> phi_bb82_24;
  TNode<BoolT> phi_bb82_25;
  TNode<BoolT> phi_bb82_26;
  TNode<IntPtrT> phi_bb82_27;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_19, &phi_bb82_23, &phi_bb82_24, &phi_bb82_25, &phi_bb82_26, &phi_bb82_27);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block83, phi_bb82_19, phi_bb82_23, phi_bb82_24, phi_bb82_25, phi_bb82_26, phi_bb82_27);
    } else {
      ca_.Goto(&block84, phi_bb82_19, phi_bb82_23, phi_bb82_24, phi_bb82_25, phi_bb82_26, phi_bb82_27);
    }
  }

  TNode<BoolT> phi_bb83_19;
  TNode<IntPtrT> phi_bb83_23;
  TNode<IntPtrT> phi_bb83_24;
  TNode<BoolT> phi_bb83_25;
  TNode<BoolT> phi_bb83_26;
  TNode<IntPtrT> phi_bb83_27;
  TNode<IntPtrT> tmp126;
  TNode<IntPtrT> tmp127;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_19, &phi_bb83_23, &phi_bb83_24, &phi_bb83_25, &phi_bb83_26, &phi_bb83_27);
    tmp126 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp127 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb83_27}, TNode<IntPtrT>{tmp126});
    ca_.Goto(&block85, phi_bb83_19, phi_bb83_23, phi_bb83_24, phi_bb83_25, phi_bb83_26, tmp127);
  }

  TNode<BoolT> phi_bb84_19;
  TNode<IntPtrT> phi_bb84_23;
  TNode<IntPtrT> phi_bb84_24;
  TNode<BoolT> phi_bb84_25;
  TNode<BoolT> phi_bb84_26;
  TNode<IntPtrT> phi_bb84_27;
  TNode<IntPtrT> tmp128;
  TNode<IntPtrT> tmp129;
  TNode<BoolT> tmp130;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_19, &phi_bb84_23, &phi_bb84_24, &phi_bb84_25, &phi_bb84_26, &phi_bb84_27);
    tmp128 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp129 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb84_27}, TNode<IntPtrT>{tmp128});
    tmp130 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block85, phi_bb84_19, phi_bb84_23, phi_bb84_24, phi_bb84_25, tmp130, tmp129);
  }

  TNode<BoolT> phi_bb85_19;
  TNode<IntPtrT> phi_bb85_23;
  TNode<IntPtrT> phi_bb85_24;
  TNode<BoolT> phi_bb85_25;
  TNode<BoolT> phi_bb85_26;
  TNode<IntPtrT> phi_bb85_27;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_19, &phi_bb85_23, &phi_bb85_24, &phi_bb85_25, &phi_bb85_26, &phi_bb85_27);
    ca_.Goto(&block80, phi_bb85_19, phi_bb85_23, phi_bb85_24, phi_bb85_25, phi_bb85_26, phi_bb85_27);
  }

  TNode<BoolT> phi_bb80_19;
  TNode<IntPtrT> phi_bb80_23;
  TNode<IntPtrT> phi_bb80_24;
  TNode<BoolT> phi_bb80_25;
  TNode<BoolT> phi_bb80_26;
  TNode<IntPtrT> phi_bb80_27;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_19, &phi_bb80_23, &phi_bb80_24, &phi_bb80_25, &phi_bb80_26, &phi_bb80_27);
    ca_.Goto(&block79, phi_bb80_19, phi_bb80_23, phi_bb80_24, phi_bb80_25, phi_bb80_26, phi_bb80_27);
  }

  TNode<BoolT> phi_bb78_19;
  TNode<IntPtrT> phi_bb78_23;
  TNode<IntPtrT> phi_bb78_24;
  TNode<BoolT> phi_bb78_25;
  TNode<BoolT> phi_bb78_26;
  TNode<IntPtrT> phi_bb78_27;
  TNode<Uint32T> tmp131;
  TNode<Uint32T> tmp132;
  TNode<Uint32T> tmp133;
  TNode<BoolT> tmp134;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_19, &phi_bb78_23, &phi_bb78_24, &phi_bb78_25, &phi_bb78_26, &phi_bb78_27);
    tmp131 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp132 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp65}, TNode<Uint32T>{tmp131});
    tmp133 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp134 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp132}, TNode<Uint32T>{tmp133});
    ca_.Branch(tmp134, &block86, std::vector<compiler::Node*>{phi_bb78_19, phi_bb78_23, phi_bb78_24, phi_bb78_25, phi_bb78_26, phi_bb78_27}, &block87, std::vector<compiler::Node*>{phi_bb78_19, phi_bb78_23, phi_bb78_24, phi_bb78_25, phi_bb78_26, phi_bb78_27});
  }

  TNode<BoolT> phi_bb87_19;
  TNode<IntPtrT> phi_bb87_23;
  TNode<IntPtrT> phi_bb87_24;
  TNode<BoolT> phi_bb87_25;
  TNode<BoolT> phi_bb87_26;
  TNode<IntPtrT> phi_bb87_27;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_19, &phi_bb87_23, &phi_bb87_24, &phi_bb87_25, &phi_bb87_26, &phi_bb87_27);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 570});
      CodeStubAssembler(state_).FailAssert("Torque assert '(retType & kValueTypeIsRefBit) != 0' failed", pos_stack);
    }
  }

  TNode<BoolT> phi_bb86_19;
  TNode<IntPtrT> phi_bb86_23;
  TNode<IntPtrT> phi_bb86_24;
  TNode<BoolT> phi_bb86_25;
  TNode<BoolT> phi_bb86_26;
  TNode<IntPtrT> phi_bb86_27;
  TNode<BoolT> tmp135;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_19, &phi_bb86_23, &phi_bb86_24, &phi_bb86_25, &phi_bb86_26, &phi_bb86_27);
    tmp135 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block79, tmp135, phi_bb86_23, phi_bb86_24, phi_bb86_25, phi_bb86_26, phi_bb86_27);
  }

  TNode<BoolT> phi_bb79_19;
  TNode<IntPtrT> phi_bb79_23;
  TNode<IntPtrT> phi_bb79_24;
  TNode<BoolT> phi_bb79_25;
  TNode<BoolT> phi_bb79_26;
  TNode<IntPtrT> phi_bb79_27;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_19, &phi_bb79_23, &phi_bb79_24, &phi_bb79_25, &phi_bb79_26, &phi_bb79_27);
    ca_.Goto(&block66, phi_bb79_19, phi_bb79_23, phi_bb79_24, phi_bb79_25, phi_bb79_26, phi_bb79_27);
  }

  TNode<BoolT> phi_bb66_19;
  TNode<IntPtrT> phi_bb66_23;
  TNode<IntPtrT> phi_bb66_24;
  TNode<BoolT> phi_bb66_25;
  TNode<BoolT> phi_bb66_26;
  TNode<IntPtrT> phi_bb66_27;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_19, &phi_bb66_23, &phi_bb66_24, &phi_bb66_25, &phi_bb66_26, &phi_bb66_27);
    ca_.Goto(&block40, phi_bb66_19, phi_bb66_23, phi_bb66_24, phi_bb66_25, phi_bb66_26, phi_bb66_27);
  }

  TNode<BoolT> phi_bb40_19;
  TNode<IntPtrT> phi_bb40_23;
  TNode<IntPtrT> phi_bb40_24;
  TNode<BoolT> phi_bb40_25;
  TNode<BoolT> phi_bb40_26;
  TNode<IntPtrT> phi_bb40_27;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_19, &phi_bb40_23, &phi_bb40_24, &phi_bb40_25, &phi_bb40_26, &phi_bb40_27);
    ca_.Goto(&block27, phi_bb40_19, phi_bb40_23, phi_bb40_24, phi_bb40_25, phi_bb40_26, phi_bb40_27);
  }

  TNode<BoolT> phi_bb27_19;
  TNode<IntPtrT> phi_bb27_23;
  TNode<IntPtrT> phi_bb27_24;
  TNode<BoolT> phi_bb27_25;
  TNode<BoolT> phi_bb27_26;
  TNode<IntPtrT> phi_bb27_27;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_19, &phi_bb27_23, &phi_bb27_24, &phi_bb27_25, &phi_bb27_26, &phi_bb27_27);
    ca_.Goto(&block18, phi_bb27_19, phi_bb27_23, phi_bb27_24, phi_bb27_25, phi_bb27_26, phi_bb27_27, tmp64);
  }

  TNode<BoolT> phi_bb17_19;
  TNode<IntPtrT> phi_bb17_23;
  TNode<IntPtrT> phi_bb17_24;
  TNode<BoolT> phi_bb17_25;
  TNode<BoolT> phi_bb17_26;
  TNode<IntPtrT> phi_bb17_27;
  TNode<IntPtrT> phi_bb17_29;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_19, &phi_bb17_23, &phi_bb17_24, &phi_bb17_25, &phi_bb17_26, &phi_bb17_27, &phi_bb17_29);
    ca_.Branch(phi_bb17_19, &block88, std::vector<compiler::Node*>{phi_bb17_19, phi_bb17_23, phi_bb17_24, phi_bb17_25, phi_bb17_26, phi_bb17_27, phi_bb17_29}, &block89, std::vector<compiler::Node*>{phi_bb17_19, phi_bb17_23, phi_bb17_24, phi_bb17_25, phi_bb17_26, phi_bb17_27, phi_bb17_29, tmp56});
  }

  TNode<BoolT> phi_bb88_19;
  TNode<IntPtrT> phi_bb88_23;
  TNode<IntPtrT> phi_bb88_24;
  TNode<BoolT> phi_bb88_25;
  TNode<BoolT> phi_bb88_26;
  TNode<IntPtrT> phi_bb88_27;
  TNode<IntPtrT> phi_bb88_29;
  TNode<BoolT> tmp136;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_19, &phi_bb88_23, &phi_bb88_24, &phi_bb88_25, &phi_bb88_26, &phi_bb88_27, &phi_bb88_29);
    tmp136 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb88_26});
    ca_.Branch(tmp136, &block91, std::vector<compiler::Node*>{phi_bb88_19, phi_bb88_23, phi_bb88_24, phi_bb88_25, phi_bb88_26, phi_bb88_27, phi_bb88_29}, &block92, std::vector<compiler::Node*>{phi_bb88_19, phi_bb88_23, phi_bb88_24, phi_bb88_25, phi_bb88_26, phi_bb88_27, phi_bb88_29});
  }

  TNode<BoolT> phi_bb91_19;
  TNode<IntPtrT> phi_bb91_23;
  TNode<IntPtrT> phi_bb91_24;
  TNode<BoolT> phi_bb91_25;
  TNode<BoolT> phi_bb91_26;
  TNode<IntPtrT> phi_bb91_27;
  TNode<IntPtrT> phi_bb91_29;
  TNode<BoolT> tmp137;
  if (block91.is_used()) {
    ca_.Bind(&block91, &phi_bb91_19, &phi_bb91_23, &phi_bb91_24, &phi_bb91_25, &phi_bb91_26, &phi_bb91_27, &phi_bb91_29);
    tmp137 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block92, phi_bb91_19, phi_bb91_23, phi_bb91_24, tmp137, phi_bb91_26, phi_bb91_27, phi_bb91_29);
  }

  TNode<BoolT> phi_bb92_19;
  TNode<IntPtrT> phi_bb92_23;
  TNode<IntPtrT> phi_bb92_24;
  TNode<BoolT> phi_bb92_25;
  TNode<BoolT> phi_bb92_26;
  TNode<IntPtrT> phi_bb92_27;
  TNode<IntPtrT> phi_bb92_29;
  TNode<IntPtrT> tmp138;
  TNode<IntPtrT> tmp139;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_19, &phi_bb92_23, &phi_bb92_24, &phi_bb92_25, &phi_bb92_26, &phi_bb92_27, &phi_bb92_29);
    tmp138 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{tmp48});
    tmp139 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp47}, TNode<IntPtrT>{tmp138});
    ca_.Goto(&block96, phi_bb92_19, phi_bb92_23, phi_bb92_24, phi_bb92_25, phi_bb92_26, phi_bb92_27, tmp47);
  }

  TNode<BoolT> phi_bb96_19;
  TNode<IntPtrT> phi_bb96_23;
  TNode<IntPtrT> phi_bb96_24;
  TNode<BoolT> phi_bb96_25;
  TNode<BoolT> phi_bb96_26;
  TNode<IntPtrT> phi_bb96_27;
  TNode<IntPtrT> phi_bb96_29;
  TNode<BoolT> tmp140;
  TNode<BoolT> tmp141;
  if (block96.is_used()) {
    ca_.Bind(&block96, &phi_bb96_19, &phi_bb96_23, &phi_bb96_24, &phi_bb96_25, &phi_bb96_26, &phi_bb96_27, &phi_bb96_29);
    tmp140 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb96_29}, TNode<IntPtrT>{tmp139});
    tmp141 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp140});
    ca_.Branch(tmp141, &block94, std::vector<compiler::Node*>{phi_bb96_19, phi_bb96_23, phi_bb96_24, phi_bb96_25, phi_bb96_26, phi_bb96_27, phi_bb96_29}, &block95, std::vector<compiler::Node*>{phi_bb96_19, phi_bb96_23, phi_bb96_24, phi_bb96_25, phi_bb96_26, phi_bb96_27, phi_bb96_29});
  }

  TNode<BoolT> phi_bb94_19;
  TNode<IntPtrT> phi_bb94_23;
  TNode<IntPtrT> phi_bb94_24;
  TNode<BoolT> phi_bb94_25;
  TNode<BoolT> phi_bb94_26;
  TNode<IntPtrT> phi_bb94_27;
  TNode<IntPtrT> phi_bb94_29;
  TNode<BoolT> tmp142;
  TNode<BoolT> tmp143;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_19, &phi_bb94_23, &phi_bb94_24, &phi_bb94_25, &phi_bb94_26, &phi_bb94_27, &phi_bb94_29);
    tmp142 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb94_29}, TNode<IntPtrT>{tmp139});
    tmp143 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp142});
    ca_.Branch(tmp143, &block100, std::vector<compiler::Node*>{phi_bb94_19, phi_bb94_23, phi_bb94_24, phi_bb94_25, phi_bb94_26, phi_bb94_27, phi_bb94_29}, &block101, std::vector<compiler::Node*>{phi_bb94_19, phi_bb94_23, phi_bb94_24, phi_bb94_25, phi_bb94_26, phi_bb94_27, phi_bb94_29});
  }

  TNode<BoolT> phi_bb101_19;
  TNode<IntPtrT> phi_bb101_23;
  TNode<IntPtrT> phi_bb101_24;
  TNode<BoolT> phi_bb101_25;
  TNode<BoolT> phi_bb101_26;
  TNode<IntPtrT> phi_bb101_27;
  TNode<IntPtrT> phi_bb101_29;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_19, &phi_bb101_23, &phi_bb101_24, &phi_bb101_25, &phi_bb101_26, &phi_bb101_27, &phi_bb101_29);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/torque-internal.tq", 245});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.Empty()' failed", pos_stack);
    }
  }

  TNode<BoolT> phi_bb100_19;
  TNode<IntPtrT> phi_bb100_23;
  TNode<IntPtrT> phi_bb100_24;
  TNode<BoolT> phi_bb100_25;
  TNode<BoolT> phi_bb100_26;
  TNode<IntPtrT> phi_bb100_27;
  TNode<IntPtrT> phi_bb100_29;
  TNode<Union<HeapObject, TaggedIndex>> tmp144;
  TNode<IntPtrT> tmp145;
  TNode<IntPtrT> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<Uint32T> tmp148;
  TNode<Uint32T> tmp149;
  TNode<Uint32T> tmp150;
  TNode<Uint32T> tmp151;
  TNode<BoolT> tmp152;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_19, &phi_bb100_23, &phi_bb100_24, &phi_bb100_25, &phi_bb100_26, &phi_bb100_27, &phi_bb100_29);
    std::tie(tmp144, tmp145) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp46}, TNode<IntPtrT>{phi_bb100_29}).Flatten();
    tmp146 = FromConstexpr_intptr_constexpr_int31_0(state_, kInt32Size);
    tmp147 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb100_29}, TNode<IntPtrT>{tmp146});
    tmp148 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp144, tmp145});
    tmp149 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp150 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp148}, TNode<Uint32T>{tmp149});
    tmp151 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp152 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp150}, TNode<Uint32T>{tmp151});
    ca_.Branch(tmp152, &block103, std::vector<compiler::Node*>{phi_bb100_19, phi_bb100_23, phi_bb100_24, phi_bb100_25, phi_bb100_26, phi_bb100_27}, &block104, std::vector<compiler::Node*>{phi_bb100_19, phi_bb100_23, phi_bb100_24, phi_bb100_25, phi_bb100_26, phi_bb100_27});
  }

  TNode<BoolT> phi_bb103_19;
  TNode<IntPtrT> phi_bb103_23;
  TNode<IntPtrT> phi_bb103_24;
  TNode<BoolT> phi_bb103_25;
  TNode<BoolT> phi_bb103_26;
  TNode<IntPtrT> phi_bb103_27;
  TNode<IntPtrT> tmp153;
  TNode<BoolT> tmp154;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_19, &phi_bb103_23, &phi_bb103_24, &phi_bb103_25, &phi_bb103_26, &phi_bb103_27);
    tmp153 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp154 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb103_23}, TNode<IntPtrT>{tmp153});
    ca_.Branch(tmp154, &block106, std::vector<compiler::Node*>{phi_bb103_19, phi_bb103_23, phi_bb103_24, phi_bb103_25, phi_bb103_26, phi_bb103_27}, &block107, std::vector<compiler::Node*>{phi_bb103_19, phi_bb103_23, phi_bb103_24, phi_bb103_25, phi_bb103_26, phi_bb103_27});
  }

  TNode<BoolT> phi_bb106_19;
  TNode<IntPtrT> phi_bb106_23;
  TNode<IntPtrT> phi_bb106_24;
  TNode<BoolT> phi_bb106_25;
  TNode<BoolT> phi_bb106_26;
  TNode<IntPtrT> phi_bb106_27;
  TNode<IntPtrT> tmp155;
  TNode<IntPtrT> tmp156;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_19, &phi_bb106_23, &phi_bb106_24, &phi_bb106_25, &phi_bb106_26, &phi_bb106_27);
    tmp155 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp156 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb106_23}, TNode<IntPtrT>{tmp155});
    ca_.Goto(&block105, phi_bb106_19, tmp156, phi_bb106_24, phi_bb106_25, phi_bb106_26, phi_bb106_27);
  }

  TNode<BoolT> phi_bb107_19;
  TNode<IntPtrT> phi_bb107_23;
  TNode<IntPtrT> phi_bb107_24;
  TNode<BoolT> phi_bb107_25;
  TNode<BoolT> phi_bb107_26;
  TNode<IntPtrT> phi_bb107_27;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_19, &phi_bb107_23, &phi_bb107_24, &phi_bb107_25, &phi_bb107_26, &phi_bb107_27);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block109, phi_bb107_19, phi_bb107_23, phi_bb107_24, phi_bb107_25, phi_bb107_26, phi_bb107_27);
    } else {
      ca_.Goto(&block110, phi_bb107_19, phi_bb107_23, phi_bb107_24, phi_bb107_25, phi_bb107_26, phi_bb107_27);
    }
  }

  TNode<BoolT> phi_bb109_19;
  TNode<IntPtrT> phi_bb109_23;
  TNode<IntPtrT> phi_bb109_24;
  TNode<BoolT> phi_bb109_25;
  TNode<BoolT> phi_bb109_26;
  TNode<IntPtrT> phi_bb109_27;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_19, &phi_bb109_23, &phi_bb109_24, &phi_bb109_25, &phi_bb109_26, &phi_bb109_27);
    tmp157 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp158 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb109_27}, TNode<IntPtrT>{tmp157});
    ca_.Goto(&block111, phi_bb109_19, phi_bb109_23, phi_bb109_24, phi_bb109_25, phi_bb109_26, tmp158);
  }

  TNode<BoolT> phi_bb110_19;
  TNode<IntPtrT> phi_bb110_23;
  TNode<IntPtrT> phi_bb110_24;
  TNode<BoolT> phi_bb110_25;
  TNode<BoolT> phi_bb110_26;
  TNode<IntPtrT> phi_bb110_27;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_19, &phi_bb110_23, &phi_bb110_24, &phi_bb110_25, &phi_bb110_26, &phi_bb110_27);
    ca_.Branch(phi_bb110_25, &block112, std::vector<compiler::Node*>{phi_bb110_19, phi_bb110_23, phi_bb110_24, phi_bb110_25, phi_bb110_26, phi_bb110_27}, &block113, std::vector<compiler::Node*>{phi_bb110_19, phi_bb110_23, phi_bb110_24, phi_bb110_25, phi_bb110_26, phi_bb110_27});
  }

  TNode<BoolT> phi_bb112_19;
  TNode<IntPtrT> phi_bb112_23;
  TNode<IntPtrT> phi_bb112_24;
  TNode<BoolT> phi_bb112_25;
  TNode<BoolT> phi_bb112_26;
  TNode<IntPtrT> phi_bb112_27;
  TNode<BoolT> tmp159;
  TNode<BoolT> tmp160;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_19, &phi_bb112_23, &phi_bb112_24, &phi_bb112_25, &phi_bb112_26, &phi_bb112_27);
    tmp159 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp160 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block114, phi_bb112_19, phi_bb112_23, phi_bb112_24, tmp159, tmp160, phi_bb112_27);
  }

  TNode<BoolT> phi_bb113_19;
  TNode<IntPtrT> phi_bb113_23;
  TNode<IntPtrT> phi_bb113_24;
  TNode<BoolT> phi_bb113_25;
  TNode<BoolT> phi_bb113_26;
  TNode<IntPtrT> phi_bb113_27;
  TNode<IntPtrT> tmp161;
  TNode<IntPtrT> tmp162;
  TNode<BoolT> tmp163;
  TNode<BoolT> tmp164;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_19, &phi_bb113_23, &phi_bb113_24, &phi_bb113_25, &phi_bb113_26, &phi_bb113_27);
    tmp161 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp162 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb113_27}, TNode<IntPtrT>{tmp161});
    tmp163 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp164 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block114, phi_bb113_19, phi_bb113_23, phi_bb113_24, tmp163, tmp164, tmp162);
  }

  TNode<BoolT> phi_bb114_19;
  TNode<IntPtrT> phi_bb114_23;
  TNode<IntPtrT> phi_bb114_24;
  TNode<BoolT> phi_bb114_25;
  TNode<BoolT> phi_bb114_26;
  TNode<IntPtrT> phi_bb114_27;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_19, &phi_bb114_23, &phi_bb114_24, &phi_bb114_25, &phi_bb114_26, &phi_bb114_27);
    ca_.Goto(&block111, phi_bb114_19, phi_bb114_23, phi_bb114_24, phi_bb114_25, phi_bb114_26, phi_bb114_27);
  }

  TNode<BoolT> phi_bb111_19;
  TNode<IntPtrT> phi_bb111_23;
  TNode<IntPtrT> phi_bb111_24;
  TNode<BoolT> phi_bb111_25;
  TNode<BoolT> phi_bb111_26;
  TNode<IntPtrT> phi_bb111_27;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_19, &phi_bb111_23, &phi_bb111_24, &phi_bb111_25, &phi_bb111_26, &phi_bb111_27);
    ca_.Goto(&block105, phi_bb111_19, phi_bb111_23, phi_bb111_24, phi_bb111_25, phi_bb111_26, phi_bb111_27);
  }

  TNode<BoolT> phi_bb105_19;
  TNode<IntPtrT> phi_bb105_23;
  TNode<IntPtrT> phi_bb105_24;
  TNode<BoolT> phi_bb105_25;
  TNode<BoolT> phi_bb105_26;
  TNode<IntPtrT> phi_bb105_27;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_19, &phi_bb105_23, &phi_bb105_24, &phi_bb105_25, &phi_bb105_26, &phi_bb105_27);
    ca_.Goto(&block104, phi_bb105_19, phi_bb105_23, phi_bb105_24, phi_bb105_25, phi_bb105_26, phi_bb105_27);
  }

  TNode<BoolT> phi_bb104_19;
  TNode<IntPtrT> phi_bb104_23;
  TNode<IntPtrT> phi_bb104_24;
  TNode<BoolT> phi_bb104_25;
  TNode<BoolT> phi_bb104_26;
  TNode<IntPtrT> phi_bb104_27;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_19, &phi_bb104_23, &phi_bb104_24, &phi_bb104_25, &phi_bb104_26, &phi_bb104_27);
    ca_.Goto(&block96, phi_bb104_19, phi_bb104_23, phi_bb104_24, phi_bb104_25, phi_bb104_26, phi_bb104_27, tmp147);
  }

  TNode<BoolT> phi_bb95_19;
  TNode<IntPtrT> phi_bb95_23;
  TNode<IntPtrT> phi_bb95_24;
  TNode<BoolT> phi_bb95_25;
  TNode<BoolT> phi_bb95_26;
  TNode<IntPtrT> phi_bb95_27;
  TNode<IntPtrT> phi_bb95_29;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_19, &phi_bb95_23, &phi_bb95_24, &phi_bb95_25, &phi_bb95_26, &phi_bb95_27, &phi_bb95_29);
    ca_.Goto(&block89, phi_bb95_19, phi_bb95_23, phi_bb95_24, phi_bb95_25, phi_bb95_26, phi_bb95_27, phi_bb95_29, tmp139);
  }

  TNode<BoolT> phi_bb89_19;
  TNode<IntPtrT> phi_bb89_23;
  TNode<IntPtrT> phi_bb89_24;
  TNode<BoolT> phi_bb89_25;
  TNode<BoolT> phi_bb89_26;
  TNode<IntPtrT> phi_bb89_27;
  TNode<IntPtrT> phi_bb89_29;
  TNode<IntPtrT> phi_bb89_30;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_19, &phi_bb89_23, &phi_bb89_24, &phi_bb89_25, &phi_bb89_26, &phi_bb89_27, &phi_bb89_29, &phi_bb89_30);
    ca_.Branch(phi_bb89_26, &block116, std::vector<compiler::Node*>{phi_bb89_19, phi_bb89_23, phi_bb89_24, phi_bb89_25, phi_bb89_26, phi_bb89_27, phi_bb89_29, phi_bb89_30}, &block117, std::vector<compiler::Node*>{phi_bb89_19, phi_bb89_23, phi_bb89_24, phi_bb89_25, phi_bb89_26, phi_bb89_27, phi_bb89_29, phi_bb89_30});
  }

  TNode<BoolT> phi_bb116_19;
  TNode<IntPtrT> phi_bb116_23;
  TNode<IntPtrT> phi_bb116_24;
  TNode<BoolT> phi_bb116_25;
  TNode<BoolT> phi_bb116_26;
  TNode<IntPtrT> phi_bb116_27;
  TNode<IntPtrT> phi_bb116_29;
  TNode<IntPtrT> phi_bb116_30;
  TNode<IntPtrT> tmp165;
  TNode<IntPtrT> tmp166;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_19, &phi_bb116_23, &phi_bb116_24, &phi_bb116_25, &phi_bb116_26, &phi_bb116_27, &phi_bb116_29, &phi_bb116_30);
    tmp165 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp166 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb116_27}, TNode<IntPtrT>{tmp165});
    ca_.Goto(&block115, phi_bb116_19, phi_bb116_23, phi_bb116_24, phi_bb116_25, phi_bb116_26, phi_bb116_27, phi_bb116_29, phi_bb116_30, tmp166);
  }

  TNode<BoolT> phi_bb117_19;
  TNode<IntPtrT> phi_bb117_23;
  TNode<IntPtrT> phi_bb117_24;
  TNode<BoolT> phi_bb117_25;
  TNode<BoolT> phi_bb117_26;
  TNode<IntPtrT> phi_bb117_27;
  TNode<IntPtrT> phi_bb117_29;
  TNode<IntPtrT> phi_bb117_30;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_19, &phi_bb117_23, &phi_bb117_24, &phi_bb117_25, &phi_bb117_26, &phi_bb117_27, &phi_bb117_29, &phi_bb117_30);
    ca_.Goto(&block115, phi_bb117_19, phi_bb117_23, phi_bb117_24, phi_bb117_25, phi_bb117_26, phi_bb117_27, phi_bb117_29, phi_bb117_30, phi_bb117_27);
  }

  TNode<BoolT> phi_bb115_19;
  TNode<IntPtrT> phi_bb115_23;
  TNode<IntPtrT> phi_bb115_24;
  TNode<BoolT> phi_bb115_25;
  TNode<BoolT> phi_bb115_26;
  TNode<IntPtrT> phi_bb115_27;
  TNode<IntPtrT> phi_bb115_29;
  TNode<IntPtrT> phi_bb115_30;
  TNode<IntPtrT> phi_bb115_31;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_19, &phi_bb115_23, &phi_bb115_24, &phi_bb115_25, &phi_bb115_26, &phi_bb115_27, &phi_bb115_29, &phi_bb115_30, &phi_bb115_31);
    ca_.Goto(&block10, tmp44, phi_bb115_31, phi_bb115_19);
  }

  TNode<JSAny> phi_bb10_17;
  TNode<IntPtrT> phi_bb10_18;
  TNode<BoolT> phi_bb10_19;
  TNode<Union<HeapObject, TaggedIndex>> tmp167;
  TNode<IntPtrT> tmp168;
  TNode<IntPtrT> tmp169;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_17, &phi_bb10_18, &phi_bb10_19);
    compiler::CodeAssemblerLabel label170(&ca_);
    std::tie(tmp167, tmp168, tmp169) = Subslice_uint32_0(state_, TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp35}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp37}, TorqueStructUnsafe_0{}}, TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp24}, &label170).Flatten();
    ca_.Goto(&block121, phi_bb10_17, phi_bb10_18, phi_bb10_19);
    if (label170.is_used()) {
      ca_.Bind(&label170);
      ca_.Goto(&block122, phi_bb10_17, phi_bb10_18, phi_bb10_19);
    }
  }

  TNode<JSAny> phi_bb122_17;
  TNode<IntPtrT> phi_bb122_18;
  TNode<BoolT> phi_bb122_19;
  if (block122.is_used()) {
    ca_.Bind(&block122, &phi_bb122_17, &phi_bb122_18, &phi_bb122_19);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/js-to-wasm.tq:590:17");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb121_17;
  TNode<IntPtrT> phi_bb121_18;
  TNode<BoolT> phi_bb121_19;
  TNode<IntPtrT> tmp171;
  TNode<BoolT> tmp172;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_17, &phi_bb121_18, &phi_bb121_19);
    tmp171 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0xaull));
    tmp172 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp24}, TNode<IntPtrT>{tmp171});
    ca_.Branch(tmp172, &block123, std::vector<compiler::Node*>{phi_bb121_17, phi_bb121_18, phi_bb121_19}, &block124, std::vector<compiler::Node*>{phi_bb121_17, phi_bb121_18, phi_bb121_19});
  }

  TNode<JSAny> phi_bb123_17;
  TNode<IntPtrT> phi_bb123_18;
  TNode<BoolT> phi_bb123_19;
  TNode<IntPtrT> tmp173;
  TNode<IntPtrT> tmp174;
  TNode<BoolT> tmp175;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_17, &phi_bb123_18, &phi_bb123_19);
    tmp173 = CodeStubAssembler(state_).UniqueIntPtrConstant(arraysize(wasm::kFpParamRegisters));
    tmp174 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x8ull));
    tmp175 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp173}, TNode<IntPtrT>{tmp174});
    ca_.Branch(tmp175, &block126, std::vector<compiler::Node*>{phi_bb123_17, phi_bb123_18, phi_bb123_19}, &block127, std::vector<compiler::Node*>{phi_bb123_17, phi_bb123_18, phi_bb123_19});
  }

  TNode<JSAny> phi_bb127_17;
  TNode<IntPtrT> phi_bb127_18;
  TNode<BoolT> phi_bb127_19;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_17, &phi_bb127_18, &phi_bb127_19);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 629});
      CodeStubAssembler(state_).FailAssert("Torque assert 'UniqueIntPtrConstant(kNumFPRegisterParameters) <= kMaxFPRegParams' failed", pos_stack);
    }
  }

  TNode<JSAny> phi_bb126_17;
  TNode<IntPtrT> phi_bb126_18;
  TNode<BoolT> phi_bb126_19;
  TNode<IntPtrT> tmp176;
  TNode<IntPtrT> tmp177;
  TNode<BoolT> tmp178;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_17, &phi_bb126_18, &phi_bb126_19);
    tmp176 = CodeStubAssembler(state_).UniqueIntPtrConstant(arraysize(wasm::kGpParamRegisters) - 1);
    tmp177 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x8ull));
    tmp178 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp176}, TNode<IntPtrT>{tmp177});
    ca_.Branch(tmp178, &block128, std::vector<compiler::Node*>{phi_bb126_17, phi_bb126_18, phi_bb126_19}, &block129, std::vector<compiler::Node*>{phi_bb126_17, phi_bb126_18, phi_bb126_19});
  }

  TNode<JSAny> phi_bb129_17;
  TNode<IntPtrT> phi_bb129_18;
  TNode<BoolT> phi_bb129_19;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_17, &phi_bb129_18, &phi_bb129_19);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 630});
      CodeStubAssembler(state_).FailAssert("Torque assert 'UniqueIntPtrConstant(kNumGPRegisterParameters) <= kMaxFPRegParams' failed", pos_stack);
    }
  }

  TNode<JSAny> phi_bb128_17;
  TNode<IntPtrT> phi_bb128_18;
  TNode<BoolT> phi_bb128_19;
  TNode<RawPtrT> tmp179;
  TNode<RawPtrT> tmp180;
  TNode<IntPtrT> tmp181;
  TNode<Union<HeapObject, TaggedIndex>> tmp182;
  TNode<IntPtrT> tmp183;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_17, &phi_bb128_18, &phi_bb128_19);
    tmp179 = CodeStubAssembler(state_).StackSlotPtr(CastIfEnumClass<int32_t>((CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, (CodeStubAssembler(state_).ConstexprIntegerLiteralAdd((CodeStubAssembler(state_).ConstexprIntegerLiteralAdd(IntegerLiteral(false, 0xaull), IntegerLiteral(false, 0x8ull))), IntegerLiteral(false, 0x2ull))))), (SizeOf_float64_0(state_))))), CastIfEnumClass<int32_t>((SizeOf_float64_0(state_))));
    tmp180 = (TNode<RawPtrT>{tmp179});
    tmp181 = Convert_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, (CodeStubAssembler(state_).ConstexprIntegerLiteralAdd((CodeStubAssembler(state_).ConstexprIntegerLiteralAdd(IntegerLiteral(false, 0xaull), IntegerLiteral(false, 0x8ull))), IntegerLiteral(false, 0x2ull))))), (SizeOf_float64_0(state_)))));
    std::tie(tmp182, tmp183) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp180}).Flatten();
    ca_.Goto(&block125, phi_bb128_17, phi_bb128_18, phi_bb128_19, tmp182, tmp183, tmp181);
  }

  TNode<JSAny> phi_bb124_17;
  TNode<IntPtrT> phi_bb124_18;
  TNode<BoolT> phi_bb124_19;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<IntPtrT> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<IntPtrT> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<RawPtrT> tmp190;
  TNode<Union<HeapObject, TaggedIndex>> tmp191;
  TNode<IntPtrT> tmp192;
  if (block124.is_used()) {
    ca_.Bind(&block124, &phi_bb124_17, &phi_bb124_18, &phi_bb124_19);
    tmp184 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp185 = CodeStubAssembler(state_).UniqueIntPtrConstant(arraysize(wasm::kFpParamRegisters));
    tmp186 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp185}, TNode<IntPtrT>{tmp24});
    tmp187 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp188 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp186}, TNode<IntPtrT>{tmp187});
    tmp189 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp188}, TNode<IntPtrT>{tmp184});
    tmp190 = CodeStubAssembler(state_).AllocateBuffer(TNode<IntPtrT>{tmp189});
    std::tie(tmp191, tmp192) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp190}).Flatten();
    ca_.Goto(&block125, phi_bb124_17, phi_bb124_18, phi_bb124_19, tmp191, tmp192, tmp189);
  }

  TNode<JSAny> phi_bb125_17;
  TNode<IntPtrT> phi_bb125_18;
  TNode<BoolT> phi_bb125_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb125_23;
  TNode<IntPtrT> phi_bb125_24;
  TNode<IntPtrT> phi_bb125_25;
  TNode<Union<HeapObject, TaggedIndex>> tmp193;
  TNode<IntPtrT> tmp194;
  TNode<IntPtrT> tmp195;
  TNode<IntPtrT> tmp196;
  TNode<IntPtrT> tmp197;
  TNode<IntPtrT> tmp198;
  TNode<IntPtrT> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<IntPtrT> tmp201;
  TNode<BoolT> tmp202;
  TNode<BoolT> tmp203;
  TNode<Smi> tmp204;
  TNode<IntPtrT> tmp205;
  if (block125.is_used()) {
    ca_.Bind(&block125, &phi_bb125_17, &phi_bb125_18, &phi_bb125_19, &phi_bb125_23, &phi_bb125_24, &phi_bb125_25);
    std::tie(tmp193, tmp194, tmp195, tmp196, tmp197, tmp198, tmp199, tmp200, tmp201, tmp202) = LocationAllocatorForParams_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb125_23}, TNode<IntPtrT>{phi_bb125_24}, TorqueStructUnsafe_0{}}, TNode<IntPtrT>{phi_bb125_25}).Flatten();
    tmp203 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp204 = Convert_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp205 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block132, phi_bb125_17, phi_bb125_18, phi_bb125_19, phi_bb125_23, phi_bb125_24, phi_bb125_25, tmp194, tmp195, tmp196, tmp197, tmp198, tmp201, tmp202, tmp203, tmp204, tmp205);
  }

  TNode<JSAny> phi_bb132_17;
  TNode<IntPtrT> phi_bb132_18;
  TNode<BoolT> phi_bb132_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb132_23;
  TNode<IntPtrT> phi_bb132_24;
  TNode<IntPtrT> phi_bb132_25;
  TNode<IntPtrT> phi_bb132_27;
  TNode<IntPtrT> phi_bb132_28;
  TNode<IntPtrT> phi_bb132_29;
  TNode<IntPtrT> phi_bb132_30;
  TNode<IntPtrT> phi_bb132_31;
  TNode<IntPtrT> phi_bb132_34;
  TNode<BoolT> phi_bb132_35;
  TNode<BoolT> phi_bb132_36;
  TNode<Union<FixedArray, Smi>> phi_bb132_37;
  TNode<IntPtrT> phi_bb132_38;
  TNode<BoolT> tmp206;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_17, &phi_bb132_18, &phi_bb132_19, &phi_bb132_23, &phi_bb132_24, &phi_bb132_25, &phi_bb132_27, &phi_bb132_28, &phi_bb132_29, &phi_bb132_30, &phi_bb132_31, &phi_bb132_34, &phi_bb132_35, &phi_bb132_36, &phi_bb132_37, &phi_bb132_38);
    tmp206 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb132_38}, TNode<IntPtrT>{tmp24});
    ca_.Branch(tmp206, &block130, std::vector<compiler::Node*>{phi_bb132_17, phi_bb132_18, phi_bb132_19, phi_bb132_23, phi_bb132_24, phi_bb132_25, phi_bb132_27, phi_bb132_28, phi_bb132_29, phi_bb132_30, phi_bb132_31, phi_bb132_34, phi_bb132_35, phi_bb132_36, phi_bb132_37, phi_bb132_38}, &block131, std::vector<compiler::Node*>{phi_bb132_17, phi_bb132_18, phi_bb132_19, phi_bb132_23, phi_bb132_24, phi_bb132_25, phi_bb132_27, phi_bb132_28, phi_bb132_29, phi_bb132_30, phi_bb132_31, phi_bb132_34, phi_bb132_35, phi_bb132_36, phi_bb132_37, phi_bb132_38});
  }

  TNode<JSAny> phi_bb130_17;
  TNode<IntPtrT> phi_bb130_18;
  TNode<BoolT> phi_bb130_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb130_23;
  TNode<IntPtrT> phi_bb130_24;
  TNode<IntPtrT> phi_bb130_25;
  TNode<IntPtrT> phi_bb130_27;
  TNode<IntPtrT> phi_bb130_28;
  TNode<IntPtrT> phi_bb130_29;
  TNode<IntPtrT> phi_bb130_30;
  TNode<IntPtrT> phi_bb130_31;
  TNode<IntPtrT> phi_bb130_34;
  TNode<BoolT> phi_bb130_35;
  TNode<BoolT> phi_bb130_36;
  TNode<Union<FixedArray, Smi>> phi_bb130_37;
  TNode<IntPtrT> phi_bb130_38;
  TNode<JSAny> tmp207;
  TNode<IntPtrT> tmp208;
  TNode<IntPtrT> tmp209;
  TNode<Union<HeapObject, TaggedIndex>> tmp210;
  TNode<IntPtrT> tmp211;
  TNode<Uint32T> tmp212;
  TNode<Uint32T> tmp213;
  TNode<BoolT> tmp214;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_17, &phi_bb130_18, &phi_bb130_19, &phi_bb130_23, &phi_bb130_24, &phi_bb130_25, &phi_bb130_27, &phi_bb130_28, &phi_bb130_29, &phi_bb130_30, &phi_bb130_31, &phi_bb130_34, &phi_bb130_35, &phi_bb130_36, &phi_bb130_37, &phi_bb130_38);
    tmp207 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{p_arguments.frame}, TNode<RawPtrT>{p_arguments.base}, TNode<IntPtrT>{p_arguments.length}, TNode<IntPtrT>{p_arguments.actual_count}}, TNode<IntPtrT>{phi_bb130_38});
    tmp208 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{phi_bb130_38});
    tmp209 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp168}, TNode<IntPtrT>{tmp208});
    std::tie(tmp210, tmp211) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp167}, TNode<IntPtrT>{tmp209}).Flatten();
    tmp212 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp210, tmp211});
    tmp213 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp214 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp212}, TNode<Uint32T>{tmp213});
    ca_.Branch(tmp214, &block135, std::vector<compiler::Node*>{phi_bb130_17, phi_bb130_18, phi_bb130_19, phi_bb130_23, phi_bb130_24, phi_bb130_25, phi_bb130_27, phi_bb130_28, phi_bb130_29, phi_bb130_30, phi_bb130_31, phi_bb130_34, phi_bb130_35, phi_bb130_36, phi_bb130_37, phi_bb130_38}, &block136, std::vector<compiler::Node*>{phi_bb130_17, phi_bb130_18, phi_bb130_19, phi_bb130_23, phi_bb130_24, phi_bb130_25, phi_bb130_27, phi_bb130_28, phi_bb130_29, phi_bb130_30, phi_bb130_31, phi_bb130_34, phi_bb130_35, phi_bb130_36, phi_bb130_37, phi_bb130_38});
  }

  TNode<JSAny> phi_bb135_17;
  TNode<IntPtrT> phi_bb135_18;
  TNode<BoolT> phi_bb135_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb135_23;
  TNode<IntPtrT> phi_bb135_24;
  TNode<IntPtrT> phi_bb135_25;
  TNode<IntPtrT> phi_bb135_27;
  TNode<IntPtrT> phi_bb135_28;
  TNode<IntPtrT> phi_bb135_29;
  TNode<IntPtrT> phi_bb135_30;
  TNode<IntPtrT> phi_bb135_31;
  TNode<IntPtrT> phi_bb135_34;
  TNode<BoolT> phi_bb135_35;
  TNode<BoolT> phi_bb135_36;
  TNode<Union<FixedArray, Smi>> phi_bb135_37;
  TNode<IntPtrT> phi_bb135_38;
  TNode<IntPtrT> tmp215;
  TNode<IntPtrT> tmp216;
  TNode<IntPtrT> tmp217;
  TNode<BoolT> tmp218;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_17, &phi_bb135_18, &phi_bb135_19, &phi_bb135_23, &phi_bb135_24, &phi_bb135_25, &phi_bb135_27, &phi_bb135_28, &phi_bb135_29, &phi_bb135_30, &phi_bb135_31, &phi_bb135_34, &phi_bb135_35, &phi_bb135_36, &phi_bb135_37, &phi_bb135_38);
    tmp215 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp216 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb135_27}, TNode<IntPtrT>{tmp215});
    tmp217 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp218 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb135_27}, TNode<IntPtrT>{tmp217});
    ca_.Branch(tmp218, &block139, std::vector<compiler::Node*>{phi_bb135_17, phi_bb135_18, phi_bb135_19, phi_bb135_23, phi_bb135_24, phi_bb135_25, phi_bb135_28, phi_bb135_29, phi_bb135_30, phi_bb135_31, phi_bb135_34, phi_bb135_35, phi_bb135_36, phi_bb135_37, phi_bb135_38}, &block140, std::vector<compiler::Node*>{phi_bb135_17, phi_bb135_18, phi_bb135_19, phi_bb135_23, phi_bb135_24, phi_bb135_25, phi_bb135_28, phi_bb135_29, phi_bb135_30, phi_bb135_31, phi_bb135_34, phi_bb135_35, phi_bb135_36, phi_bb135_37, phi_bb135_38});
  }

  TNode<JSAny> phi_bb139_17;
  TNode<IntPtrT> phi_bb139_18;
  TNode<BoolT> phi_bb139_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb139_23;
  TNode<IntPtrT> phi_bb139_24;
  TNode<IntPtrT> phi_bb139_25;
  TNode<IntPtrT> phi_bb139_28;
  TNode<IntPtrT> phi_bb139_29;
  TNode<IntPtrT> phi_bb139_30;
  TNode<IntPtrT> phi_bb139_31;
  TNode<IntPtrT> phi_bb139_34;
  TNode<BoolT> phi_bb139_35;
  TNode<BoolT> phi_bb139_36;
  TNode<Union<FixedArray, Smi>> phi_bb139_37;
  TNode<IntPtrT> phi_bb139_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp219;
  TNode<IntPtrT> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<IntPtrT> tmp222;
  if (block139.is_used()) {
    ca_.Bind(&block139, &phi_bb139_17, &phi_bb139_18, &phi_bb139_19, &phi_bb139_23, &phi_bb139_24, &phi_bb139_25, &phi_bb139_28, &phi_bb139_29, &phi_bb139_30, &phi_bb139_31, &phi_bb139_34, &phi_bb139_35, &phi_bb139_36, &phi_bb139_37, &phi_bb139_38);
    std::tie(tmp219, tmp220) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb139_29}).Flatten();
    tmp221 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp222 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb139_29}, TNode<IntPtrT>{tmp221});
    ca_.Goto(&block138, phi_bb139_17, phi_bb139_18, phi_bb139_19, phi_bb139_23, phi_bb139_24, phi_bb139_25, phi_bb139_28, tmp222, phi_bb139_30, phi_bb139_31, phi_bb139_34, phi_bb139_35, phi_bb139_36, phi_bb139_37, phi_bb139_38, tmp219, tmp220);
  }

  TNode<JSAny> phi_bb140_17;
  TNode<IntPtrT> phi_bb140_18;
  TNode<BoolT> phi_bb140_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb140_23;
  TNode<IntPtrT> phi_bb140_24;
  TNode<IntPtrT> phi_bb140_25;
  TNode<IntPtrT> phi_bb140_28;
  TNode<IntPtrT> phi_bb140_29;
  TNode<IntPtrT> phi_bb140_30;
  TNode<IntPtrT> phi_bb140_31;
  TNode<IntPtrT> phi_bb140_34;
  TNode<BoolT> phi_bb140_35;
  TNode<BoolT> phi_bb140_36;
  TNode<Union<FixedArray, Smi>> phi_bb140_37;
  TNode<IntPtrT> phi_bb140_38;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_17, &phi_bb140_18, &phi_bb140_19, &phi_bb140_23, &phi_bb140_24, &phi_bb140_25, &phi_bb140_28, &phi_bb140_29, &phi_bb140_30, &phi_bb140_31, &phi_bb140_34, &phi_bb140_35, &phi_bb140_36, &phi_bb140_37, &phi_bb140_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block142, phi_bb140_17, phi_bb140_18, phi_bb140_19, phi_bb140_23, phi_bb140_24, phi_bb140_25, phi_bb140_28, phi_bb140_29, phi_bb140_30, phi_bb140_31, phi_bb140_34, phi_bb140_35, phi_bb140_36, phi_bb140_37, phi_bb140_38);
    } else {
      ca_.Goto(&block143, phi_bb140_17, phi_bb140_18, phi_bb140_19, phi_bb140_23, phi_bb140_24, phi_bb140_25, phi_bb140_28, phi_bb140_29, phi_bb140_30, phi_bb140_31, phi_bb140_34, phi_bb140_35, phi_bb140_36, phi_bb140_37, phi_bb140_38);
    }
  }

  TNode<JSAny> phi_bb142_17;
  TNode<IntPtrT> phi_bb142_18;
  TNode<BoolT> phi_bb142_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb142_23;
  TNode<IntPtrT> phi_bb142_24;
  TNode<IntPtrT> phi_bb142_25;
  TNode<IntPtrT> phi_bb142_28;
  TNode<IntPtrT> phi_bb142_29;
  TNode<IntPtrT> phi_bb142_30;
  TNode<IntPtrT> phi_bb142_31;
  TNode<IntPtrT> phi_bb142_34;
  TNode<BoolT> phi_bb142_35;
  TNode<BoolT> phi_bb142_36;
  TNode<Union<FixedArray, Smi>> phi_bb142_37;
  TNode<IntPtrT> phi_bb142_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp223;
  TNode<IntPtrT> tmp224;
  TNode<IntPtrT> tmp225;
  TNode<IntPtrT> tmp226;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_17, &phi_bb142_18, &phi_bb142_19, &phi_bb142_23, &phi_bb142_24, &phi_bb142_25, &phi_bb142_28, &phi_bb142_29, &phi_bb142_30, &phi_bb142_31, &phi_bb142_34, &phi_bb142_35, &phi_bb142_36, &phi_bb142_37, &phi_bb142_38);
    std::tie(tmp223, tmp224) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb142_31}).Flatten();
    tmp225 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp226 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb142_31}, TNode<IntPtrT>{tmp225});
    ca_.Goto(&block141, phi_bb142_17, phi_bb142_18, phi_bb142_19, phi_bb142_23, phi_bb142_24, phi_bb142_25, phi_bb142_28, phi_bb142_29, phi_bb142_30, tmp226, phi_bb142_34, phi_bb142_35, phi_bb142_36, phi_bb142_37, phi_bb142_38, tmp223, tmp224);
  }

  TNode<JSAny> phi_bb143_17;
  TNode<IntPtrT> phi_bb143_18;
  TNode<BoolT> phi_bb143_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb143_23;
  TNode<IntPtrT> phi_bb143_24;
  TNode<IntPtrT> phi_bb143_25;
  TNode<IntPtrT> phi_bb143_28;
  TNode<IntPtrT> phi_bb143_29;
  TNode<IntPtrT> phi_bb143_30;
  TNode<IntPtrT> phi_bb143_31;
  TNode<IntPtrT> phi_bb143_34;
  TNode<BoolT> phi_bb143_35;
  TNode<BoolT> phi_bb143_36;
  TNode<Union<FixedArray, Smi>> phi_bb143_37;
  TNode<IntPtrT> phi_bb143_38;
  TNode<IntPtrT> tmp227;
  TNode<BoolT> tmp228;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_17, &phi_bb143_18, &phi_bb143_19, &phi_bb143_23, &phi_bb143_24, &phi_bb143_25, &phi_bb143_28, &phi_bb143_29, &phi_bb143_30, &phi_bb143_31, &phi_bb143_34, &phi_bb143_35, &phi_bb143_36, &phi_bb143_37, &phi_bb143_38);
    tmp227 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp228 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb143_34}, TNode<IntPtrT>{tmp227});
    ca_.Branch(tmp228, &block145, std::vector<compiler::Node*>{phi_bb143_17, phi_bb143_18, phi_bb143_19, phi_bb143_23, phi_bb143_24, phi_bb143_25, phi_bb143_28, phi_bb143_29, phi_bb143_30, phi_bb143_31, phi_bb143_34, phi_bb143_35, phi_bb143_36, phi_bb143_37, phi_bb143_38}, &block146, std::vector<compiler::Node*>{phi_bb143_17, phi_bb143_18, phi_bb143_19, phi_bb143_23, phi_bb143_24, phi_bb143_25, phi_bb143_28, phi_bb143_29, phi_bb143_30, phi_bb143_31, phi_bb143_34, phi_bb143_35, phi_bb143_36, phi_bb143_37, phi_bb143_38});
  }

  TNode<JSAny> phi_bb145_17;
  TNode<IntPtrT> phi_bb145_18;
  TNode<BoolT> phi_bb145_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb145_23;
  TNode<IntPtrT> phi_bb145_24;
  TNode<IntPtrT> phi_bb145_25;
  TNode<IntPtrT> phi_bb145_28;
  TNode<IntPtrT> phi_bb145_29;
  TNode<IntPtrT> phi_bb145_30;
  TNode<IntPtrT> phi_bb145_31;
  TNode<IntPtrT> phi_bb145_34;
  TNode<BoolT> phi_bb145_35;
  TNode<BoolT> phi_bb145_36;
  TNode<Union<FixedArray, Smi>> phi_bb145_37;
  TNode<IntPtrT> phi_bb145_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp229;
  TNode<IntPtrT> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<BoolT> tmp232;
  if (block145.is_used()) {
    ca_.Bind(&block145, &phi_bb145_17, &phi_bb145_18, &phi_bb145_19, &phi_bb145_23, &phi_bb145_24, &phi_bb145_25, &phi_bb145_28, &phi_bb145_29, &phi_bb145_30, &phi_bb145_31, &phi_bb145_34, &phi_bb145_35, &phi_bb145_36, &phi_bb145_37, &phi_bb145_38);
    std::tie(tmp229, tmp230) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb145_34}).Flatten();
    tmp231 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp232 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block141, phi_bb145_17, phi_bb145_18, phi_bb145_19, phi_bb145_23, phi_bb145_24, phi_bb145_25, phi_bb145_28, phi_bb145_29, phi_bb145_30, phi_bb145_31, tmp231, tmp232, phi_bb145_36, phi_bb145_37, phi_bb145_38, tmp229, tmp230);
  }

  TNode<JSAny> phi_bb146_17;
  TNode<IntPtrT> phi_bb146_18;
  TNode<BoolT> phi_bb146_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb146_23;
  TNode<IntPtrT> phi_bb146_24;
  TNode<IntPtrT> phi_bb146_25;
  TNode<IntPtrT> phi_bb146_28;
  TNode<IntPtrT> phi_bb146_29;
  TNode<IntPtrT> phi_bb146_30;
  TNode<IntPtrT> phi_bb146_31;
  TNode<IntPtrT> phi_bb146_34;
  TNode<BoolT> phi_bb146_35;
  TNode<BoolT> phi_bb146_36;
  TNode<Union<FixedArray, Smi>> phi_bb146_37;
  TNode<IntPtrT> phi_bb146_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp233;
  TNode<IntPtrT> tmp234;
  TNode<IntPtrT> tmp235;
  TNode<IntPtrT> tmp236;
  TNode<IntPtrT> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<BoolT> tmp239;
  if (block146.is_used()) {
    ca_.Bind(&block146, &phi_bb146_17, &phi_bb146_18, &phi_bb146_19, &phi_bb146_23, &phi_bb146_24, &phi_bb146_25, &phi_bb146_28, &phi_bb146_29, &phi_bb146_30, &phi_bb146_31, &phi_bb146_34, &phi_bb146_35, &phi_bb146_36, &phi_bb146_37, &phi_bb146_38);
    std::tie(tmp233, tmp234) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb146_31}).Flatten();
    tmp235 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp236 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb146_31}, TNode<IntPtrT>{tmp235});
    tmp237 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp238 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp236}, TNode<IntPtrT>{tmp237});
    tmp239 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block141, phi_bb146_17, phi_bb146_18, phi_bb146_19, phi_bb146_23, phi_bb146_24, phi_bb146_25, phi_bb146_28, phi_bb146_29, phi_bb146_30, tmp238, tmp236, tmp239, phi_bb146_36, phi_bb146_37, phi_bb146_38, tmp233, tmp234);
  }

  TNode<JSAny> phi_bb141_17;
  TNode<IntPtrT> phi_bb141_18;
  TNode<BoolT> phi_bb141_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb141_23;
  TNode<IntPtrT> phi_bb141_24;
  TNode<IntPtrT> phi_bb141_25;
  TNode<IntPtrT> phi_bb141_28;
  TNode<IntPtrT> phi_bb141_29;
  TNode<IntPtrT> phi_bb141_30;
  TNode<IntPtrT> phi_bb141_31;
  TNode<IntPtrT> phi_bb141_34;
  TNode<BoolT> phi_bb141_35;
  TNode<BoolT> phi_bb141_36;
  TNode<Union<FixedArray, Smi>> phi_bb141_37;
  TNode<IntPtrT> phi_bb141_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb141_41;
  TNode<IntPtrT> phi_bb141_42;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_17, &phi_bb141_18, &phi_bb141_19, &phi_bb141_23, &phi_bb141_24, &phi_bb141_25, &phi_bb141_28, &phi_bb141_29, &phi_bb141_30, &phi_bb141_31, &phi_bb141_34, &phi_bb141_35, &phi_bb141_36, &phi_bb141_37, &phi_bb141_38, &phi_bb141_41, &phi_bb141_42);
    ca_.Goto(&block138, phi_bb141_17, phi_bb141_18, phi_bb141_19, phi_bb141_23, phi_bb141_24, phi_bb141_25, phi_bb141_28, phi_bb141_29, phi_bb141_30, phi_bb141_31, phi_bb141_34, phi_bb141_35, phi_bb141_36, phi_bb141_37, phi_bb141_38, phi_bb141_41, phi_bb141_42);
  }

  TNode<JSAny> phi_bb138_17;
  TNode<IntPtrT> phi_bb138_18;
  TNode<BoolT> phi_bb138_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb138_23;
  TNode<IntPtrT> phi_bb138_24;
  TNode<IntPtrT> phi_bb138_25;
  TNode<IntPtrT> phi_bb138_28;
  TNode<IntPtrT> phi_bb138_29;
  TNode<IntPtrT> phi_bb138_30;
  TNode<IntPtrT> phi_bb138_31;
  TNode<IntPtrT> phi_bb138_34;
  TNode<BoolT> phi_bb138_35;
  TNode<BoolT> phi_bb138_36;
  TNode<Union<FixedArray, Smi>> phi_bb138_37;
  TNode<IntPtrT> phi_bb138_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb138_41;
  TNode<IntPtrT> phi_bb138_42;
  TNode<Smi> tmp240;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_17, &phi_bb138_18, &phi_bb138_19, &phi_bb138_23, &phi_bb138_24, &phi_bb138_25, &phi_bb138_28, &phi_bb138_29, &phi_bb138_30, &phi_bb138_31, &phi_bb138_34, &phi_bb138_35, &phi_bb138_36, &phi_bb138_37, &phi_bb138_38, &phi_bb138_41, &phi_bb138_42);
    compiler::CodeAssemblerLabel label241(&ca_);
    tmp240 = Cast_Smi_0(state_, TNode<Object>{tmp207}, &label241);
    ca_.Goto(&block149, phi_bb138_17, phi_bb138_18, phi_bb138_19, phi_bb138_23, phi_bb138_24, phi_bb138_25, phi_bb138_28, phi_bb138_29, phi_bb138_30, phi_bb138_31, phi_bb138_34, phi_bb138_35, phi_bb138_36, phi_bb138_37, phi_bb138_38, phi_bb138_41, phi_bb138_42);
    if (label241.is_used()) {
      ca_.Bind(&label241);
      ca_.Goto(&block150, phi_bb138_17, phi_bb138_18, phi_bb138_19, phi_bb138_23, phi_bb138_24, phi_bb138_25, phi_bb138_28, phi_bb138_29, phi_bb138_30, phi_bb138_31, phi_bb138_34, phi_bb138_35, phi_bb138_36, phi_bb138_37, phi_bb138_38, phi_bb138_41, phi_bb138_42);
    }
  }

  TNode<JSAny> phi_bb150_17;
  TNode<IntPtrT> phi_bb150_18;
  TNode<BoolT> phi_bb150_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb150_23;
  TNode<IntPtrT> phi_bb150_24;
  TNode<IntPtrT> phi_bb150_25;
  TNode<IntPtrT> phi_bb150_28;
  TNode<IntPtrT> phi_bb150_29;
  TNode<IntPtrT> phi_bb150_30;
  TNode<IntPtrT> phi_bb150_31;
  TNode<IntPtrT> phi_bb150_34;
  TNode<BoolT> phi_bb150_35;
  TNode<BoolT> phi_bb150_36;
  TNode<Union<FixedArray, Smi>> phi_bb150_37;
  TNode<IntPtrT> phi_bb150_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb150_41;
  TNode<IntPtrT> phi_bb150_42;
  TNode<Int32T> tmp242;
  TNode<IntPtrT> tmp243;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_17, &phi_bb150_18, &phi_bb150_19, &phi_bb150_23, &phi_bb150_24, &phi_bb150_25, &phi_bb150_28, &phi_bb150_29, &phi_bb150_30, &phi_bb150_31, &phi_bb150_34, &phi_bb150_35, &phi_bb150_36, &phi_bb150_37, &phi_bb150_38, &phi_bb150_41, &phi_bb150_42);
    tmp242 = ca_.CallBuiltin<Int32T>(Builtin::kWasmTaggedNonSmiToInt32, p_context, ca_.UncheckedCast<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, String, Symbol, Undefined>>(tmp207));
    tmp243 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp242});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb150_41, phi_bb150_42}, tmp243);
    ca_.Goto(&block147, phi_bb150_17, phi_bb150_18, phi_bb150_19, phi_bb150_23, phi_bb150_24, phi_bb150_25, phi_bb150_28, phi_bb150_29, phi_bb150_30, phi_bb150_31, phi_bb150_34, phi_bb150_35, phi_bb150_36, phi_bb150_37, phi_bb150_38, phi_bb150_41, phi_bb150_42);
  }

  TNode<JSAny> phi_bb149_17;
  TNode<IntPtrT> phi_bb149_18;
  TNode<BoolT> phi_bb149_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb149_23;
  TNode<IntPtrT> phi_bb149_24;
  TNode<IntPtrT> phi_bb149_25;
  TNode<IntPtrT> phi_bb149_28;
  TNode<IntPtrT> phi_bb149_29;
  TNode<IntPtrT> phi_bb149_30;
  TNode<IntPtrT> phi_bb149_31;
  TNode<IntPtrT> phi_bb149_34;
  TNode<BoolT> phi_bb149_35;
  TNode<BoolT> phi_bb149_36;
  TNode<Union<FixedArray, Smi>> phi_bb149_37;
  TNode<IntPtrT> phi_bb149_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb149_41;
  TNode<IntPtrT> phi_bb149_42;
  TNode<Int32T> tmp244;
  TNode<IntPtrT> tmp245;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_17, &phi_bb149_18, &phi_bb149_19, &phi_bb149_23, &phi_bb149_24, &phi_bb149_25, &phi_bb149_28, &phi_bb149_29, &phi_bb149_30, &phi_bb149_31, &phi_bb149_34, &phi_bb149_35, &phi_bb149_36, &phi_bb149_37, &phi_bb149_38, &phi_bb149_41, &phi_bb149_42);
    tmp244 = CodeStubAssembler(state_).SmiToInt32(TNode<Smi>{tmp240});
    tmp245 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp244});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb149_41, phi_bb149_42}, tmp245);
    ca_.Goto(&block147, phi_bb149_17, phi_bb149_18, phi_bb149_19, phi_bb149_23, phi_bb149_24, phi_bb149_25, phi_bb149_28, phi_bb149_29, phi_bb149_30, phi_bb149_31, phi_bb149_34, phi_bb149_35, phi_bb149_36, phi_bb149_37, phi_bb149_38, phi_bb149_41, phi_bb149_42);
  }

  TNode<JSAny> phi_bb147_17;
  TNode<IntPtrT> phi_bb147_18;
  TNode<BoolT> phi_bb147_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb147_23;
  TNode<IntPtrT> phi_bb147_24;
  TNode<IntPtrT> phi_bb147_25;
  TNode<IntPtrT> phi_bb147_28;
  TNode<IntPtrT> phi_bb147_29;
  TNode<IntPtrT> phi_bb147_30;
  TNode<IntPtrT> phi_bb147_31;
  TNode<IntPtrT> phi_bb147_34;
  TNode<BoolT> phi_bb147_35;
  TNode<BoolT> phi_bb147_36;
  TNode<Union<FixedArray, Smi>> phi_bb147_37;
  TNode<IntPtrT> phi_bb147_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb147_41;
  TNode<IntPtrT> phi_bb147_42;
  if (block147.is_used()) {
    ca_.Bind(&block147, &phi_bb147_17, &phi_bb147_18, &phi_bb147_19, &phi_bb147_23, &phi_bb147_24, &phi_bb147_25, &phi_bb147_28, &phi_bb147_29, &phi_bb147_30, &phi_bb147_31, &phi_bb147_34, &phi_bb147_35, &phi_bb147_36, &phi_bb147_37, &phi_bb147_38, &phi_bb147_41, &phi_bb147_42);
    ca_.Goto(&block137, phi_bb147_17, phi_bb147_18, phi_bb147_19, phi_bb147_23, phi_bb147_24, phi_bb147_25, tmp216, phi_bb147_28, phi_bb147_29, phi_bb147_30, phi_bb147_31, phi_bb147_34, phi_bb147_35, phi_bb147_36, phi_bb147_37, phi_bb147_38);
  }

  TNode<JSAny> phi_bb136_17;
  TNode<IntPtrT> phi_bb136_18;
  TNode<BoolT> phi_bb136_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb136_23;
  TNode<IntPtrT> phi_bb136_24;
  TNode<IntPtrT> phi_bb136_25;
  TNode<IntPtrT> phi_bb136_27;
  TNode<IntPtrT> phi_bb136_28;
  TNode<IntPtrT> phi_bb136_29;
  TNode<IntPtrT> phi_bb136_30;
  TNode<IntPtrT> phi_bb136_31;
  TNode<IntPtrT> phi_bb136_34;
  TNode<BoolT> phi_bb136_35;
  TNode<BoolT> phi_bb136_36;
  TNode<Union<FixedArray, Smi>> phi_bb136_37;
  TNode<IntPtrT> phi_bb136_38;
  TNode<Uint32T> tmp246;
  TNode<BoolT> tmp247;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_17, &phi_bb136_18, &phi_bb136_19, &phi_bb136_23, &phi_bb136_24, &phi_bb136_25, &phi_bb136_27, &phi_bb136_28, &phi_bb136_29, &phi_bb136_30, &phi_bb136_31, &phi_bb136_34, &phi_bb136_35, &phi_bb136_36, &phi_bb136_37, &phi_bb136_38);
    tmp246 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp247 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp212}, TNode<Uint32T>{tmp246});
    ca_.Branch(tmp247, &block151, std::vector<compiler::Node*>{phi_bb136_17, phi_bb136_18, phi_bb136_19, phi_bb136_23, phi_bb136_24, phi_bb136_25, phi_bb136_27, phi_bb136_28, phi_bb136_29, phi_bb136_30, phi_bb136_31, phi_bb136_34, phi_bb136_35, phi_bb136_36, phi_bb136_37, phi_bb136_38}, &block152, std::vector<compiler::Node*>{phi_bb136_17, phi_bb136_18, phi_bb136_19, phi_bb136_23, phi_bb136_24, phi_bb136_25, phi_bb136_27, phi_bb136_28, phi_bb136_29, phi_bb136_30, phi_bb136_31, phi_bb136_34, phi_bb136_35, phi_bb136_36, phi_bb136_37, phi_bb136_38});
  }

  TNode<JSAny> phi_bb151_17;
  TNode<IntPtrT> phi_bb151_18;
  TNode<BoolT> phi_bb151_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb151_23;
  TNode<IntPtrT> phi_bb151_24;
  TNode<IntPtrT> phi_bb151_25;
  TNode<IntPtrT> phi_bb151_27;
  TNode<IntPtrT> phi_bb151_28;
  TNode<IntPtrT> phi_bb151_29;
  TNode<IntPtrT> phi_bb151_30;
  TNode<IntPtrT> phi_bb151_31;
  TNode<IntPtrT> phi_bb151_34;
  TNode<BoolT> phi_bb151_35;
  TNode<BoolT> phi_bb151_36;
  TNode<Union<FixedArray, Smi>> phi_bb151_37;
  TNode<IntPtrT> phi_bb151_38;
  TNode<IntPtrT> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<IntPtrT> tmp250;
  TNode<BoolT> tmp251;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_17, &phi_bb151_18, &phi_bb151_19, &phi_bb151_23, &phi_bb151_24, &phi_bb151_25, &phi_bb151_27, &phi_bb151_28, &phi_bb151_29, &phi_bb151_30, &phi_bb151_31, &phi_bb151_34, &phi_bb151_35, &phi_bb151_36, &phi_bb151_37, &phi_bb151_38);
    tmp248 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp249 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb151_28}, TNode<IntPtrT>{tmp248});
    tmp250 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp251 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb151_28}, TNode<IntPtrT>{tmp250});
    ca_.Branch(tmp251, &block155, std::vector<compiler::Node*>{phi_bb151_17, phi_bb151_18, phi_bb151_19, phi_bb151_23, phi_bb151_24, phi_bb151_25, phi_bb151_27, phi_bb151_29, phi_bb151_30, phi_bb151_31, phi_bb151_34, phi_bb151_35, phi_bb151_36, phi_bb151_37, phi_bb151_38}, &block156, std::vector<compiler::Node*>{phi_bb151_17, phi_bb151_18, phi_bb151_19, phi_bb151_23, phi_bb151_24, phi_bb151_25, phi_bb151_27, phi_bb151_29, phi_bb151_30, phi_bb151_31, phi_bb151_34, phi_bb151_35, phi_bb151_36, phi_bb151_37, phi_bb151_38});
  }

  TNode<JSAny> phi_bb155_17;
  TNode<IntPtrT> phi_bb155_18;
  TNode<BoolT> phi_bb155_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb155_23;
  TNode<IntPtrT> phi_bb155_24;
  TNode<IntPtrT> phi_bb155_25;
  TNode<IntPtrT> phi_bb155_27;
  TNode<IntPtrT> phi_bb155_29;
  TNode<IntPtrT> phi_bb155_30;
  TNode<IntPtrT> phi_bb155_31;
  TNode<IntPtrT> phi_bb155_34;
  TNode<BoolT> phi_bb155_35;
  TNode<BoolT> phi_bb155_36;
  TNode<Union<FixedArray, Smi>> phi_bb155_37;
  TNode<IntPtrT> phi_bb155_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp252;
  TNode<IntPtrT> tmp253;
  TNode<IntPtrT> tmp254;
  TNode<IntPtrT> tmp255;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_17, &phi_bb155_18, &phi_bb155_19, &phi_bb155_23, &phi_bb155_24, &phi_bb155_25, &phi_bb155_27, &phi_bb155_29, &phi_bb155_30, &phi_bb155_31, &phi_bb155_34, &phi_bb155_35, &phi_bb155_36, &phi_bb155_37, &phi_bb155_38);
    std::tie(tmp252, tmp253) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb155_30}).Flatten();
    tmp254 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp255 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb155_30}, TNode<IntPtrT>{tmp254});
    ca_.Goto(&block154, phi_bb155_17, phi_bb155_18, phi_bb155_19, phi_bb155_23, phi_bb155_24, phi_bb155_25, phi_bb155_27, phi_bb155_29, tmp255, phi_bb155_31, phi_bb155_34, phi_bb155_35, phi_bb155_36, phi_bb155_37, phi_bb155_38, tmp252, tmp253);
  }

  TNode<JSAny> phi_bb156_17;
  TNode<IntPtrT> phi_bb156_18;
  TNode<BoolT> phi_bb156_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb156_23;
  TNode<IntPtrT> phi_bb156_24;
  TNode<IntPtrT> phi_bb156_25;
  TNode<IntPtrT> phi_bb156_27;
  TNode<IntPtrT> phi_bb156_29;
  TNode<IntPtrT> phi_bb156_30;
  TNode<IntPtrT> phi_bb156_31;
  TNode<IntPtrT> phi_bb156_34;
  TNode<BoolT> phi_bb156_35;
  TNode<BoolT> phi_bb156_36;
  TNode<Union<FixedArray, Smi>> phi_bb156_37;
  TNode<IntPtrT> phi_bb156_38;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_17, &phi_bb156_18, &phi_bb156_19, &phi_bb156_23, &phi_bb156_24, &phi_bb156_25, &phi_bb156_27, &phi_bb156_29, &phi_bb156_30, &phi_bb156_31, &phi_bb156_34, &phi_bb156_35, &phi_bb156_36, &phi_bb156_37, &phi_bb156_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block158, phi_bb156_17, phi_bb156_18, phi_bb156_19, phi_bb156_23, phi_bb156_24, phi_bb156_25, phi_bb156_27, phi_bb156_29, phi_bb156_30, phi_bb156_31, phi_bb156_34, phi_bb156_35, phi_bb156_36, phi_bb156_37, phi_bb156_38);
    } else {
      ca_.Goto(&block159, phi_bb156_17, phi_bb156_18, phi_bb156_19, phi_bb156_23, phi_bb156_24, phi_bb156_25, phi_bb156_27, phi_bb156_29, phi_bb156_30, phi_bb156_31, phi_bb156_34, phi_bb156_35, phi_bb156_36, phi_bb156_37, phi_bb156_38);
    }
  }

  TNode<JSAny> phi_bb158_17;
  TNode<IntPtrT> phi_bb158_18;
  TNode<BoolT> phi_bb158_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb158_23;
  TNode<IntPtrT> phi_bb158_24;
  TNode<IntPtrT> phi_bb158_25;
  TNode<IntPtrT> phi_bb158_27;
  TNode<IntPtrT> phi_bb158_29;
  TNode<IntPtrT> phi_bb158_30;
  TNode<IntPtrT> phi_bb158_31;
  TNode<IntPtrT> phi_bb158_34;
  TNode<BoolT> phi_bb158_35;
  TNode<BoolT> phi_bb158_36;
  TNode<Union<FixedArray, Smi>> phi_bb158_37;
  TNode<IntPtrT> phi_bb158_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp256;
  TNode<IntPtrT> tmp257;
  TNode<IntPtrT> tmp258;
  TNode<IntPtrT> tmp259;
  if (block158.is_used()) {
    ca_.Bind(&block158, &phi_bb158_17, &phi_bb158_18, &phi_bb158_19, &phi_bb158_23, &phi_bb158_24, &phi_bb158_25, &phi_bb158_27, &phi_bb158_29, &phi_bb158_30, &phi_bb158_31, &phi_bb158_34, &phi_bb158_35, &phi_bb158_36, &phi_bb158_37, &phi_bb158_38);
    std::tie(tmp256, tmp257) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb158_31}).Flatten();
    tmp258 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp259 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb158_31}, TNode<IntPtrT>{tmp258});
    ca_.Goto(&block157, phi_bb158_17, phi_bb158_18, phi_bb158_19, phi_bb158_23, phi_bb158_24, phi_bb158_25, phi_bb158_27, phi_bb158_29, phi_bb158_30, tmp259, phi_bb158_34, phi_bb158_35, phi_bb158_36, phi_bb158_37, phi_bb158_38, tmp256, tmp257);
  }

  TNode<JSAny> phi_bb159_17;
  TNode<IntPtrT> phi_bb159_18;
  TNode<BoolT> phi_bb159_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb159_23;
  TNode<IntPtrT> phi_bb159_24;
  TNode<IntPtrT> phi_bb159_25;
  TNode<IntPtrT> phi_bb159_27;
  TNode<IntPtrT> phi_bb159_29;
  TNode<IntPtrT> phi_bb159_30;
  TNode<IntPtrT> phi_bb159_31;
  TNode<IntPtrT> phi_bb159_34;
  TNode<BoolT> phi_bb159_35;
  TNode<BoolT> phi_bb159_36;
  TNode<Union<FixedArray, Smi>> phi_bb159_37;
  TNode<IntPtrT> phi_bb159_38;
  TNode<IntPtrT> tmp260;
  TNode<BoolT> tmp261;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_17, &phi_bb159_18, &phi_bb159_19, &phi_bb159_23, &phi_bb159_24, &phi_bb159_25, &phi_bb159_27, &phi_bb159_29, &phi_bb159_30, &phi_bb159_31, &phi_bb159_34, &phi_bb159_35, &phi_bb159_36, &phi_bb159_37, &phi_bb159_38);
    tmp260 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp261 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb159_34}, TNode<IntPtrT>{tmp260});
    ca_.Branch(tmp261, &block161, std::vector<compiler::Node*>{phi_bb159_17, phi_bb159_18, phi_bb159_19, phi_bb159_23, phi_bb159_24, phi_bb159_25, phi_bb159_27, phi_bb159_29, phi_bb159_30, phi_bb159_31, phi_bb159_34, phi_bb159_35, phi_bb159_36, phi_bb159_37, phi_bb159_38}, &block162, std::vector<compiler::Node*>{phi_bb159_17, phi_bb159_18, phi_bb159_19, phi_bb159_23, phi_bb159_24, phi_bb159_25, phi_bb159_27, phi_bb159_29, phi_bb159_30, phi_bb159_31, phi_bb159_34, phi_bb159_35, phi_bb159_36, phi_bb159_37, phi_bb159_38});
  }

  TNode<JSAny> phi_bb161_17;
  TNode<IntPtrT> phi_bb161_18;
  TNode<BoolT> phi_bb161_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb161_23;
  TNode<IntPtrT> phi_bb161_24;
  TNode<IntPtrT> phi_bb161_25;
  TNode<IntPtrT> phi_bb161_27;
  TNode<IntPtrT> phi_bb161_29;
  TNode<IntPtrT> phi_bb161_30;
  TNode<IntPtrT> phi_bb161_31;
  TNode<IntPtrT> phi_bb161_34;
  TNode<BoolT> phi_bb161_35;
  TNode<BoolT> phi_bb161_36;
  TNode<Union<FixedArray, Smi>> phi_bb161_37;
  TNode<IntPtrT> phi_bb161_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp262;
  TNode<IntPtrT> tmp263;
  TNode<IntPtrT> tmp264;
  TNode<BoolT> tmp265;
  if (block161.is_used()) {
    ca_.Bind(&block161, &phi_bb161_17, &phi_bb161_18, &phi_bb161_19, &phi_bb161_23, &phi_bb161_24, &phi_bb161_25, &phi_bb161_27, &phi_bb161_29, &phi_bb161_30, &phi_bb161_31, &phi_bb161_34, &phi_bb161_35, &phi_bb161_36, &phi_bb161_37, &phi_bb161_38);
    std::tie(tmp262, tmp263) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb161_34}).Flatten();
    tmp264 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp265 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block157, phi_bb161_17, phi_bb161_18, phi_bb161_19, phi_bb161_23, phi_bb161_24, phi_bb161_25, phi_bb161_27, phi_bb161_29, phi_bb161_30, phi_bb161_31, tmp264, tmp265, phi_bb161_36, phi_bb161_37, phi_bb161_38, tmp262, tmp263);
  }

  TNode<JSAny> phi_bb162_17;
  TNode<IntPtrT> phi_bb162_18;
  TNode<BoolT> phi_bb162_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb162_23;
  TNode<IntPtrT> phi_bb162_24;
  TNode<IntPtrT> phi_bb162_25;
  TNode<IntPtrT> phi_bb162_27;
  TNode<IntPtrT> phi_bb162_29;
  TNode<IntPtrT> phi_bb162_30;
  TNode<IntPtrT> phi_bb162_31;
  TNode<IntPtrT> phi_bb162_34;
  TNode<BoolT> phi_bb162_35;
  TNode<BoolT> phi_bb162_36;
  TNode<Union<FixedArray, Smi>> phi_bb162_37;
  TNode<IntPtrT> phi_bb162_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp266;
  TNode<IntPtrT> tmp267;
  TNode<IntPtrT> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<IntPtrT> tmp270;
  TNode<IntPtrT> tmp271;
  TNode<BoolT> tmp272;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_17, &phi_bb162_18, &phi_bb162_19, &phi_bb162_23, &phi_bb162_24, &phi_bb162_25, &phi_bb162_27, &phi_bb162_29, &phi_bb162_30, &phi_bb162_31, &phi_bb162_34, &phi_bb162_35, &phi_bb162_36, &phi_bb162_37, &phi_bb162_38);
    std::tie(tmp266, tmp267) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb162_31}).Flatten();
    tmp268 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp269 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb162_31}, TNode<IntPtrT>{tmp268});
    tmp270 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp271 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp269}, TNode<IntPtrT>{tmp270});
    tmp272 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block157, phi_bb162_17, phi_bb162_18, phi_bb162_19, phi_bb162_23, phi_bb162_24, phi_bb162_25, phi_bb162_27, phi_bb162_29, phi_bb162_30, tmp271, tmp269, tmp272, phi_bb162_36, phi_bb162_37, phi_bb162_38, tmp266, tmp267);
  }

  TNode<JSAny> phi_bb157_17;
  TNode<IntPtrT> phi_bb157_18;
  TNode<BoolT> phi_bb157_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb157_23;
  TNode<IntPtrT> phi_bb157_24;
  TNode<IntPtrT> phi_bb157_25;
  TNode<IntPtrT> phi_bb157_27;
  TNode<IntPtrT> phi_bb157_29;
  TNode<IntPtrT> phi_bb157_30;
  TNode<IntPtrT> phi_bb157_31;
  TNode<IntPtrT> phi_bb157_34;
  TNode<BoolT> phi_bb157_35;
  TNode<BoolT> phi_bb157_36;
  TNode<Union<FixedArray, Smi>> phi_bb157_37;
  TNode<IntPtrT> phi_bb157_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb157_41;
  TNode<IntPtrT> phi_bb157_42;
  if (block157.is_used()) {
    ca_.Bind(&block157, &phi_bb157_17, &phi_bb157_18, &phi_bb157_19, &phi_bb157_23, &phi_bb157_24, &phi_bb157_25, &phi_bb157_27, &phi_bb157_29, &phi_bb157_30, &phi_bb157_31, &phi_bb157_34, &phi_bb157_35, &phi_bb157_36, &phi_bb157_37, &phi_bb157_38, &phi_bb157_41, &phi_bb157_42);
    ca_.Goto(&block154, phi_bb157_17, phi_bb157_18, phi_bb157_19, phi_bb157_23, phi_bb157_24, phi_bb157_25, phi_bb157_27, phi_bb157_29, phi_bb157_30, phi_bb157_31, phi_bb157_34, phi_bb157_35, phi_bb157_36, phi_bb157_37, phi_bb157_38, phi_bb157_41, phi_bb157_42);
  }

  TNode<JSAny> phi_bb154_17;
  TNode<IntPtrT> phi_bb154_18;
  TNode<BoolT> phi_bb154_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb154_23;
  TNode<IntPtrT> phi_bb154_24;
  TNode<IntPtrT> phi_bb154_25;
  TNode<IntPtrT> phi_bb154_27;
  TNode<IntPtrT> phi_bb154_29;
  TNode<IntPtrT> phi_bb154_30;
  TNode<IntPtrT> phi_bb154_31;
  TNode<IntPtrT> phi_bb154_34;
  TNode<BoolT> phi_bb154_35;
  TNode<BoolT> phi_bb154_36;
  TNode<Union<FixedArray, Smi>> phi_bb154_37;
  TNode<IntPtrT> phi_bb154_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb154_41;
  TNode<IntPtrT> phi_bb154_42;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_17, &phi_bb154_18, &phi_bb154_19, &phi_bb154_23, &phi_bb154_24, &phi_bb154_25, &phi_bb154_27, &phi_bb154_29, &phi_bb154_30, &phi_bb154_31, &phi_bb154_34, &phi_bb154_35, &phi_bb154_36, &phi_bb154_37, &phi_bb154_38, &phi_bb154_41, &phi_bb154_42);
    if ((((wasm::kIsFpAlwaysDouble || wasm::kIsBigEndian) || wasm::kIsBigEndianOnSim))) {
      ca_.Goto(&block163, phi_bb154_17, phi_bb154_18, phi_bb154_19, phi_bb154_23, phi_bb154_24, phi_bb154_25, phi_bb154_27, phi_bb154_29, phi_bb154_30, phi_bb154_31, phi_bb154_34, phi_bb154_35, phi_bb154_36, phi_bb154_37, phi_bb154_38, phi_bb154_41, phi_bb154_42);
    } else {
      ca_.Goto(&block164, phi_bb154_17, phi_bb154_18, phi_bb154_19, phi_bb154_23, phi_bb154_24, phi_bb154_25, phi_bb154_27, phi_bb154_29, phi_bb154_30, phi_bb154_31, phi_bb154_34, phi_bb154_35, phi_bb154_36, phi_bb154_37, phi_bb154_38, phi_bb154_41, phi_bb154_42);
    }
  }

  TNode<JSAny> phi_bb163_17;
  TNode<IntPtrT> phi_bb163_18;
  TNode<BoolT> phi_bb163_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb163_23;
  TNode<IntPtrT> phi_bb163_24;
  TNode<IntPtrT> phi_bb163_25;
  TNode<IntPtrT> phi_bb163_27;
  TNode<IntPtrT> phi_bb163_29;
  TNode<IntPtrT> phi_bb163_30;
  TNode<IntPtrT> phi_bb163_31;
  TNode<IntPtrT> phi_bb163_34;
  TNode<BoolT> phi_bb163_35;
  TNode<BoolT> phi_bb163_36;
  TNode<Union<FixedArray, Smi>> phi_bb163_37;
  TNode<IntPtrT> phi_bb163_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb163_41;
  TNode<IntPtrT> phi_bb163_42;
  if (block163.is_used()) {
    ca_.Bind(&block163, &phi_bb163_17, &phi_bb163_18, &phi_bb163_19, &phi_bb163_23, &phi_bb163_24, &phi_bb163_25, &phi_bb163_27, &phi_bb163_29, &phi_bb163_30, &phi_bb163_31, &phi_bb163_34, &phi_bb163_35, &phi_bb163_36, &phi_bb163_37, &phi_bb163_38, &phi_bb163_41, &phi_bb163_42);
    HandleF32Params_0(state_, TNode<NativeContext>{p_context}, TorqueStructLocationAllocator_0{TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb163_27}, TNode<IntPtrT>{tmp249}, TNode<IntPtrT>{phi_bb163_29}, TNode<IntPtrT>{phi_bb163_30}, TNode<IntPtrT>{phi_bb163_31}, TNode<IntPtrT>{tmp199}, TNode<IntPtrT>{tmp200}, TNode<IntPtrT>{phi_bb163_34}, TNode<BoolT>{phi_bb163_35}}, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb163_41}, TNode<IntPtrT>{phi_bb163_42}, TorqueStructUnsafe_0{}}, TNode<JSAny>{tmp207});
    ca_.Goto(&block165, phi_bb163_17, phi_bb163_18, phi_bb163_19, phi_bb163_23, phi_bb163_24, phi_bb163_25, phi_bb163_27, phi_bb163_29, phi_bb163_30, phi_bb163_31, phi_bb163_34, phi_bb163_35, phi_bb163_36, phi_bb163_37, phi_bb163_38, phi_bb163_41, phi_bb163_42);
  }

  TNode<JSAny> phi_bb164_17;
  TNode<IntPtrT> phi_bb164_18;
  TNode<BoolT> phi_bb164_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb164_23;
  TNode<IntPtrT> phi_bb164_24;
  TNode<IntPtrT> phi_bb164_25;
  TNode<IntPtrT> phi_bb164_27;
  TNode<IntPtrT> phi_bb164_29;
  TNode<IntPtrT> phi_bb164_30;
  TNode<IntPtrT> phi_bb164_31;
  TNode<IntPtrT> phi_bb164_34;
  TNode<BoolT> phi_bb164_35;
  TNode<BoolT> phi_bb164_36;
  TNode<Union<FixedArray, Smi>> phi_bb164_37;
  TNode<IntPtrT> phi_bb164_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb164_41;
  TNode<IntPtrT> phi_bb164_42;
  TNode<Float32T> tmp273;
  TNode<Uint32T> tmp274;
  TNode<IntPtrT> tmp275;
  TNode<Undefined> tmp276;
  TNode<BoolT> tmp277;
  if (block164.is_used()) {
    ca_.Bind(&block164, &phi_bb164_17, &phi_bb164_18, &phi_bb164_19, &phi_bb164_23, &phi_bb164_24, &phi_bb164_25, &phi_bb164_27, &phi_bb164_29, &phi_bb164_30, &phi_bb164_31, &phi_bb164_34, &phi_bb164_35, &phi_bb164_36, &phi_bb164_37, &phi_bb164_38, &phi_bb164_41, &phi_bb164_42);
    tmp273 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, tmp207);
    tmp274 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp273});
    tmp275 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp274});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb164_41, phi_bb164_42}, tmp275);
    tmp276 = Undefined_0(state_);
    tmp277 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp207}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp276});
    ca_.Branch(tmp277, &block166, std::vector<compiler::Node*>{phi_bb164_17, phi_bb164_18, phi_bb164_19, phi_bb164_23, phi_bb164_24, phi_bb164_25, phi_bb164_27, phi_bb164_29, phi_bb164_30, phi_bb164_31, phi_bb164_34, phi_bb164_35, phi_bb164_36, phi_bb164_37, phi_bb164_38, phi_bb164_41, phi_bb164_42}, &block167, std::vector<compiler::Node*>{phi_bb164_17, phi_bb164_18, phi_bb164_19, phi_bb164_23, phi_bb164_24, phi_bb164_25, phi_bb164_27, phi_bb164_29, phi_bb164_30, phi_bb164_31, phi_bb164_34, phi_bb164_35, phi_bb164_36, phi_bb164_37, phi_bb164_38, phi_bb164_41, phi_bb164_42});
  }

  TNode<JSAny> phi_bb166_17;
  TNode<IntPtrT> phi_bb166_18;
  TNode<BoolT> phi_bb166_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb166_23;
  TNode<IntPtrT> phi_bb166_24;
  TNode<IntPtrT> phi_bb166_25;
  TNode<IntPtrT> phi_bb166_27;
  TNode<IntPtrT> phi_bb166_29;
  TNode<IntPtrT> phi_bb166_30;
  TNode<IntPtrT> phi_bb166_31;
  TNode<IntPtrT> phi_bb166_34;
  TNode<BoolT> phi_bb166_35;
  TNode<BoolT> phi_bb166_36;
  TNode<Union<FixedArray, Smi>> phi_bb166_37;
  TNode<IntPtrT> phi_bb166_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb166_41;
  TNode<IntPtrT> phi_bb166_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp278;
  TNode<IntPtrT> tmp279;
  TNode<Float32T> tmp280;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_17, &phi_bb166_18, &phi_bb166_19, &phi_bb166_23, &phi_bb166_24, &phi_bb166_25, &phi_bb166_27, &phi_bb166_29, &phi_bb166_30, &phi_bb166_31, &phi_bb166_34, &phi_bb166_35, &phi_bb166_36, &phi_bb166_37, &phi_bb166_38, &phi_bb166_41, &phi_bb166_42);
    std::tie(tmp278, tmp279) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb166_41}, TNode<IntPtrT>{phi_bb166_42}, TorqueStructUnsafe_0{}}).Flatten();
    tmp280 = FromConstexpr_float32_constexpr_float32_0(state_, std::numeric_limits<float>::quiet_NaN());
    CodeStubAssembler(state_).StoreReference<Float32T>(CodeStubAssembler::Reference{tmp278, tmp279}, tmp280);
    ca_.Goto(&block167, phi_bb166_17, phi_bb166_18, phi_bb166_19, phi_bb166_23, phi_bb166_24, phi_bb166_25, phi_bb166_27, phi_bb166_29, phi_bb166_30, phi_bb166_31, phi_bb166_34, phi_bb166_35, phi_bb166_36, phi_bb166_37, phi_bb166_38, phi_bb166_41, phi_bb166_42);
  }

  TNode<JSAny> phi_bb167_17;
  TNode<IntPtrT> phi_bb167_18;
  TNode<BoolT> phi_bb167_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb167_23;
  TNode<IntPtrT> phi_bb167_24;
  TNode<IntPtrT> phi_bb167_25;
  TNode<IntPtrT> phi_bb167_27;
  TNode<IntPtrT> phi_bb167_29;
  TNode<IntPtrT> phi_bb167_30;
  TNode<IntPtrT> phi_bb167_31;
  TNode<IntPtrT> phi_bb167_34;
  TNode<BoolT> phi_bb167_35;
  TNode<BoolT> phi_bb167_36;
  TNode<Union<FixedArray, Smi>> phi_bb167_37;
  TNode<IntPtrT> phi_bb167_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb167_41;
  TNode<IntPtrT> phi_bb167_42;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_17, &phi_bb167_18, &phi_bb167_19, &phi_bb167_23, &phi_bb167_24, &phi_bb167_25, &phi_bb167_27, &phi_bb167_29, &phi_bb167_30, &phi_bb167_31, &phi_bb167_34, &phi_bb167_35, &phi_bb167_36, &phi_bb167_37, &phi_bb167_38, &phi_bb167_41, &phi_bb167_42);
    ca_.Goto(&block165, phi_bb167_17, phi_bb167_18, phi_bb167_19, phi_bb167_23, phi_bb167_24, phi_bb167_25, phi_bb167_27, phi_bb167_29, phi_bb167_30, phi_bb167_31, phi_bb167_34, phi_bb167_35, phi_bb167_36, phi_bb167_37, phi_bb167_38, phi_bb167_41, phi_bb167_42);
  }

  TNode<JSAny> phi_bb165_17;
  TNode<IntPtrT> phi_bb165_18;
  TNode<BoolT> phi_bb165_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb165_23;
  TNode<IntPtrT> phi_bb165_24;
  TNode<IntPtrT> phi_bb165_25;
  TNode<IntPtrT> phi_bb165_27;
  TNode<IntPtrT> phi_bb165_29;
  TNode<IntPtrT> phi_bb165_30;
  TNode<IntPtrT> phi_bb165_31;
  TNode<IntPtrT> phi_bb165_34;
  TNode<BoolT> phi_bb165_35;
  TNode<BoolT> phi_bb165_36;
  TNode<Union<FixedArray, Smi>> phi_bb165_37;
  TNode<IntPtrT> phi_bb165_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb165_41;
  TNode<IntPtrT> phi_bb165_42;
  if (block165.is_used()) {
    ca_.Bind(&block165, &phi_bb165_17, &phi_bb165_18, &phi_bb165_19, &phi_bb165_23, &phi_bb165_24, &phi_bb165_25, &phi_bb165_27, &phi_bb165_29, &phi_bb165_30, &phi_bb165_31, &phi_bb165_34, &phi_bb165_35, &phi_bb165_36, &phi_bb165_37, &phi_bb165_38, &phi_bb165_41, &phi_bb165_42);
    ca_.Goto(&block153, phi_bb165_17, phi_bb165_18, phi_bb165_19, phi_bb165_23, phi_bb165_24, phi_bb165_25, phi_bb165_27, tmp249, phi_bb165_29, phi_bb165_30, phi_bb165_31, phi_bb165_34, phi_bb165_35, phi_bb165_36, phi_bb165_37, phi_bb165_38);
  }

  TNode<JSAny> phi_bb152_17;
  TNode<IntPtrT> phi_bb152_18;
  TNode<BoolT> phi_bb152_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb152_23;
  TNode<IntPtrT> phi_bb152_24;
  TNode<IntPtrT> phi_bb152_25;
  TNode<IntPtrT> phi_bb152_27;
  TNode<IntPtrT> phi_bb152_28;
  TNode<IntPtrT> phi_bb152_29;
  TNode<IntPtrT> phi_bb152_30;
  TNode<IntPtrT> phi_bb152_31;
  TNode<IntPtrT> phi_bb152_34;
  TNode<BoolT> phi_bb152_35;
  TNode<BoolT> phi_bb152_36;
  TNode<Union<FixedArray, Smi>> phi_bb152_37;
  TNode<IntPtrT> phi_bb152_38;
  TNode<Uint32T> tmp281;
  TNode<BoolT> tmp282;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_17, &phi_bb152_18, &phi_bb152_19, &phi_bb152_23, &phi_bb152_24, &phi_bb152_25, &phi_bb152_27, &phi_bb152_28, &phi_bb152_29, &phi_bb152_30, &phi_bb152_31, &phi_bb152_34, &phi_bb152_35, &phi_bb152_36, &phi_bb152_37, &phi_bb152_38);
    tmp281 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp282 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp212}, TNode<Uint32T>{tmp281});
    ca_.Branch(tmp282, &block168, std::vector<compiler::Node*>{phi_bb152_17, phi_bb152_18, phi_bb152_19, phi_bb152_23, phi_bb152_24, phi_bb152_25, phi_bb152_27, phi_bb152_28, phi_bb152_29, phi_bb152_30, phi_bb152_31, phi_bb152_34, phi_bb152_35, phi_bb152_36, phi_bb152_37, phi_bb152_38}, &block169, std::vector<compiler::Node*>{phi_bb152_17, phi_bb152_18, phi_bb152_19, phi_bb152_23, phi_bb152_24, phi_bb152_25, phi_bb152_27, phi_bb152_28, phi_bb152_29, phi_bb152_30, phi_bb152_31, phi_bb152_34, phi_bb152_35, phi_bb152_36, phi_bb152_37, phi_bb152_38});
  }

  TNode<JSAny> phi_bb168_17;
  TNode<IntPtrT> phi_bb168_18;
  TNode<BoolT> phi_bb168_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb168_23;
  TNode<IntPtrT> phi_bb168_24;
  TNode<IntPtrT> phi_bb168_25;
  TNode<IntPtrT> phi_bb168_27;
  TNode<IntPtrT> phi_bb168_28;
  TNode<IntPtrT> phi_bb168_29;
  TNode<IntPtrT> phi_bb168_30;
  TNode<IntPtrT> phi_bb168_31;
  TNode<IntPtrT> phi_bb168_34;
  TNode<BoolT> phi_bb168_35;
  TNode<BoolT> phi_bb168_36;
  TNode<Union<FixedArray, Smi>> phi_bb168_37;
  TNode<IntPtrT> phi_bb168_38;
  TNode<IntPtrT> tmp283;
  TNode<IntPtrT> tmp284;
  TNode<IntPtrT> tmp285;
  TNode<BoolT> tmp286;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_17, &phi_bb168_18, &phi_bb168_19, &phi_bb168_23, &phi_bb168_24, &phi_bb168_25, &phi_bb168_27, &phi_bb168_28, &phi_bb168_29, &phi_bb168_30, &phi_bb168_31, &phi_bb168_34, &phi_bb168_35, &phi_bb168_36, &phi_bb168_37, &phi_bb168_38);
    tmp283 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp284 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb168_28}, TNode<IntPtrT>{tmp283});
    tmp285 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp286 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb168_28}, TNode<IntPtrT>{tmp285});
    ca_.Branch(tmp286, &block172, std::vector<compiler::Node*>{phi_bb168_17, phi_bb168_18, phi_bb168_19, phi_bb168_23, phi_bb168_24, phi_bb168_25, phi_bb168_27, phi_bb168_29, phi_bb168_30, phi_bb168_31, phi_bb168_34, phi_bb168_35, phi_bb168_36, phi_bb168_37, phi_bb168_38}, &block173, std::vector<compiler::Node*>{phi_bb168_17, phi_bb168_18, phi_bb168_19, phi_bb168_23, phi_bb168_24, phi_bb168_25, phi_bb168_27, phi_bb168_29, phi_bb168_30, phi_bb168_31, phi_bb168_34, phi_bb168_35, phi_bb168_36, phi_bb168_37, phi_bb168_38});
  }

  TNode<JSAny> phi_bb172_17;
  TNode<IntPtrT> phi_bb172_18;
  TNode<BoolT> phi_bb172_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb172_23;
  TNode<IntPtrT> phi_bb172_24;
  TNode<IntPtrT> phi_bb172_25;
  TNode<IntPtrT> phi_bb172_27;
  TNode<IntPtrT> phi_bb172_29;
  TNode<IntPtrT> phi_bb172_30;
  TNode<IntPtrT> phi_bb172_31;
  TNode<IntPtrT> phi_bb172_34;
  TNode<BoolT> phi_bb172_35;
  TNode<BoolT> phi_bb172_36;
  TNode<Union<FixedArray, Smi>> phi_bb172_37;
  TNode<IntPtrT> phi_bb172_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp287;
  TNode<IntPtrT> tmp288;
  TNode<IntPtrT> tmp289;
  TNode<IntPtrT> tmp290;
  if (block172.is_used()) {
    ca_.Bind(&block172, &phi_bb172_17, &phi_bb172_18, &phi_bb172_19, &phi_bb172_23, &phi_bb172_24, &phi_bb172_25, &phi_bb172_27, &phi_bb172_29, &phi_bb172_30, &phi_bb172_31, &phi_bb172_34, &phi_bb172_35, &phi_bb172_36, &phi_bb172_37, &phi_bb172_38);
    std::tie(tmp287, tmp288) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb172_30}).Flatten();
    tmp289 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp290 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb172_30}, TNode<IntPtrT>{tmp289});
    ca_.Goto(&block171, phi_bb172_17, phi_bb172_18, phi_bb172_19, phi_bb172_23, phi_bb172_24, phi_bb172_25, phi_bb172_27, phi_bb172_29, tmp290, phi_bb172_31, phi_bb172_34, phi_bb172_35, phi_bb172_36, phi_bb172_37, phi_bb172_38, tmp287, tmp288);
  }

  TNode<JSAny> phi_bb173_17;
  TNode<IntPtrT> phi_bb173_18;
  TNode<BoolT> phi_bb173_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb173_23;
  TNode<IntPtrT> phi_bb173_24;
  TNode<IntPtrT> phi_bb173_25;
  TNode<IntPtrT> phi_bb173_27;
  TNode<IntPtrT> phi_bb173_29;
  TNode<IntPtrT> phi_bb173_30;
  TNode<IntPtrT> phi_bb173_31;
  TNode<IntPtrT> phi_bb173_34;
  TNode<BoolT> phi_bb173_35;
  TNode<BoolT> phi_bb173_36;
  TNode<Union<FixedArray, Smi>> phi_bb173_37;
  TNode<IntPtrT> phi_bb173_38;
  if (block173.is_used()) {
    ca_.Bind(&block173, &phi_bb173_17, &phi_bb173_18, &phi_bb173_19, &phi_bb173_23, &phi_bb173_24, &phi_bb173_25, &phi_bb173_27, &phi_bb173_29, &phi_bb173_30, &phi_bb173_31, &phi_bb173_34, &phi_bb173_35, &phi_bb173_36, &phi_bb173_37, &phi_bb173_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block174, phi_bb173_17, phi_bb173_18, phi_bb173_19, phi_bb173_23, phi_bb173_24, phi_bb173_25, phi_bb173_27, phi_bb173_29, phi_bb173_30, phi_bb173_31, phi_bb173_34, phi_bb173_35, phi_bb173_36, phi_bb173_37, phi_bb173_38);
    } else {
      ca_.Goto(&block175, phi_bb173_17, phi_bb173_18, phi_bb173_19, phi_bb173_23, phi_bb173_24, phi_bb173_25, phi_bb173_27, phi_bb173_29, phi_bb173_30, phi_bb173_31, phi_bb173_34, phi_bb173_35, phi_bb173_36, phi_bb173_37, phi_bb173_38);
    }
  }

  TNode<JSAny> phi_bb174_17;
  TNode<IntPtrT> phi_bb174_18;
  TNode<BoolT> phi_bb174_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb174_23;
  TNode<IntPtrT> phi_bb174_24;
  TNode<IntPtrT> phi_bb174_25;
  TNode<IntPtrT> phi_bb174_27;
  TNode<IntPtrT> phi_bb174_29;
  TNode<IntPtrT> phi_bb174_30;
  TNode<IntPtrT> phi_bb174_31;
  TNode<IntPtrT> phi_bb174_34;
  TNode<BoolT> phi_bb174_35;
  TNode<BoolT> phi_bb174_36;
  TNode<Union<FixedArray, Smi>> phi_bb174_37;
  TNode<IntPtrT> phi_bb174_38;
  if (block174.is_used()) {
    ca_.Bind(&block174, &phi_bb174_17, &phi_bb174_18, &phi_bb174_19, &phi_bb174_23, &phi_bb174_24, &phi_bb174_25, &phi_bb174_27, &phi_bb174_29, &phi_bb174_30, &phi_bb174_31, &phi_bb174_34, &phi_bb174_35, &phi_bb174_36, &phi_bb174_37, &phi_bb174_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block178, phi_bb174_17, phi_bb174_18, phi_bb174_19, phi_bb174_23, phi_bb174_24, phi_bb174_25, phi_bb174_27, phi_bb174_29, phi_bb174_30, phi_bb174_31, phi_bb174_34, phi_bb174_35, phi_bb174_36, phi_bb174_37, phi_bb174_38);
    } else {
      ca_.Goto(&block179, phi_bb174_17, phi_bb174_18, phi_bb174_19, phi_bb174_23, phi_bb174_24, phi_bb174_25, phi_bb174_27, phi_bb174_29, phi_bb174_30, phi_bb174_31, phi_bb174_34, phi_bb174_35, phi_bb174_36, phi_bb174_37, phi_bb174_38);
    }
  }

  TNode<JSAny> phi_bb178_17;
  TNode<IntPtrT> phi_bb178_18;
  TNode<BoolT> phi_bb178_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb178_23;
  TNode<IntPtrT> phi_bb178_24;
  TNode<IntPtrT> phi_bb178_25;
  TNode<IntPtrT> phi_bb178_27;
  TNode<IntPtrT> phi_bb178_29;
  TNode<IntPtrT> phi_bb178_30;
  TNode<IntPtrT> phi_bb178_31;
  TNode<IntPtrT> phi_bb178_34;
  TNode<BoolT> phi_bb178_35;
  TNode<BoolT> phi_bb178_36;
  TNode<Union<FixedArray, Smi>> phi_bb178_37;
  TNode<IntPtrT> phi_bb178_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp291;
  TNode<IntPtrT> tmp292;
  TNode<IntPtrT> tmp293;
  TNode<IntPtrT> tmp294;
  if (block178.is_used()) {
    ca_.Bind(&block178, &phi_bb178_17, &phi_bb178_18, &phi_bb178_19, &phi_bb178_23, &phi_bb178_24, &phi_bb178_25, &phi_bb178_27, &phi_bb178_29, &phi_bb178_30, &phi_bb178_31, &phi_bb178_34, &phi_bb178_35, &phi_bb178_36, &phi_bb178_37, &phi_bb178_38);
    std::tie(tmp291, tmp292) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb178_31}).Flatten();
    tmp293 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp294 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb178_31}, TNode<IntPtrT>{tmp293});
    ca_.Goto(&block177, phi_bb178_17, phi_bb178_18, phi_bb178_19, phi_bb178_23, phi_bb178_24, phi_bb178_25, phi_bb178_27, phi_bb178_29, phi_bb178_30, tmp294, phi_bb178_34, phi_bb178_35, phi_bb178_36, phi_bb178_37, phi_bb178_38, tmp291, tmp292);
  }

  TNode<JSAny> phi_bb179_17;
  TNode<IntPtrT> phi_bb179_18;
  TNode<BoolT> phi_bb179_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb179_23;
  TNode<IntPtrT> phi_bb179_24;
  TNode<IntPtrT> phi_bb179_25;
  TNode<IntPtrT> phi_bb179_27;
  TNode<IntPtrT> phi_bb179_29;
  TNode<IntPtrT> phi_bb179_30;
  TNode<IntPtrT> phi_bb179_31;
  TNode<IntPtrT> phi_bb179_34;
  TNode<BoolT> phi_bb179_35;
  TNode<BoolT> phi_bb179_36;
  TNode<Union<FixedArray, Smi>> phi_bb179_37;
  TNode<IntPtrT> phi_bb179_38;
  TNode<IntPtrT> tmp295;
  TNode<BoolT> tmp296;
  if (block179.is_used()) {
    ca_.Bind(&block179, &phi_bb179_17, &phi_bb179_18, &phi_bb179_19, &phi_bb179_23, &phi_bb179_24, &phi_bb179_25, &phi_bb179_27, &phi_bb179_29, &phi_bb179_30, &phi_bb179_31, &phi_bb179_34, &phi_bb179_35, &phi_bb179_36, &phi_bb179_37, &phi_bb179_38);
    tmp295 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp296 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb179_34}, TNode<IntPtrT>{tmp295});
    ca_.Branch(tmp296, &block181, std::vector<compiler::Node*>{phi_bb179_17, phi_bb179_18, phi_bb179_19, phi_bb179_23, phi_bb179_24, phi_bb179_25, phi_bb179_27, phi_bb179_29, phi_bb179_30, phi_bb179_31, phi_bb179_34, phi_bb179_35, phi_bb179_36, phi_bb179_37, phi_bb179_38}, &block182, std::vector<compiler::Node*>{phi_bb179_17, phi_bb179_18, phi_bb179_19, phi_bb179_23, phi_bb179_24, phi_bb179_25, phi_bb179_27, phi_bb179_29, phi_bb179_30, phi_bb179_31, phi_bb179_34, phi_bb179_35, phi_bb179_36, phi_bb179_37, phi_bb179_38});
  }

  TNode<JSAny> phi_bb181_17;
  TNode<IntPtrT> phi_bb181_18;
  TNode<BoolT> phi_bb181_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb181_23;
  TNode<IntPtrT> phi_bb181_24;
  TNode<IntPtrT> phi_bb181_25;
  TNode<IntPtrT> phi_bb181_27;
  TNode<IntPtrT> phi_bb181_29;
  TNode<IntPtrT> phi_bb181_30;
  TNode<IntPtrT> phi_bb181_31;
  TNode<IntPtrT> phi_bb181_34;
  TNode<BoolT> phi_bb181_35;
  TNode<BoolT> phi_bb181_36;
  TNode<Union<FixedArray, Smi>> phi_bb181_37;
  TNode<IntPtrT> phi_bb181_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<IntPtrT> tmp299;
  TNode<BoolT> tmp300;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_17, &phi_bb181_18, &phi_bb181_19, &phi_bb181_23, &phi_bb181_24, &phi_bb181_25, &phi_bb181_27, &phi_bb181_29, &phi_bb181_30, &phi_bb181_31, &phi_bb181_34, &phi_bb181_35, &phi_bb181_36, &phi_bb181_37, &phi_bb181_38);
    std::tie(tmp297, tmp298) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb181_34}).Flatten();
    tmp299 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp300 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block177, phi_bb181_17, phi_bb181_18, phi_bb181_19, phi_bb181_23, phi_bb181_24, phi_bb181_25, phi_bb181_27, phi_bb181_29, phi_bb181_30, phi_bb181_31, tmp299, tmp300, phi_bb181_36, phi_bb181_37, phi_bb181_38, tmp297, tmp298);
  }

  TNode<JSAny> phi_bb182_17;
  TNode<IntPtrT> phi_bb182_18;
  TNode<BoolT> phi_bb182_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb182_23;
  TNode<IntPtrT> phi_bb182_24;
  TNode<IntPtrT> phi_bb182_25;
  TNode<IntPtrT> phi_bb182_27;
  TNode<IntPtrT> phi_bb182_29;
  TNode<IntPtrT> phi_bb182_30;
  TNode<IntPtrT> phi_bb182_31;
  TNode<IntPtrT> phi_bb182_34;
  TNode<BoolT> phi_bb182_35;
  TNode<BoolT> phi_bb182_36;
  TNode<Union<FixedArray, Smi>> phi_bb182_37;
  TNode<IntPtrT> phi_bb182_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp301;
  TNode<IntPtrT> tmp302;
  TNode<IntPtrT> tmp303;
  TNode<IntPtrT> tmp304;
  TNode<IntPtrT> tmp305;
  TNode<IntPtrT> tmp306;
  TNode<BoolT> tmp307;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_17, &phi_bb182_18, &phi_bb182_19, &phi_bb182_23, &phi_bb182_24, &phi_bb182_25, &phi_bb182_27, &phi_bb182_29, &phi_bb182_30, &phi_bb182_31, &phi_bb182_34, &phi_bb182_35, &phi_bb182_36, &phi_bb182_37, &phi_bb182_38);
    std::tie(tmp301, tmp302) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb182_31}).Flatten();
    tmp303 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp304 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb182_31}, TNode<IntPtrT>{tmp303});
    tmp305 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp306 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp304}, TNode<IntPtrT>{tmp305});
    tmp307 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block177, phi_bb182_17, phi_bb182_18, phi_bb182_19, phi_bb182_23, phi_bb182_24, phi_bb182_25, phi_bb182_27, phi_bb182_29, phi_bb182_30, tmp306, tmp304, tmp307, phi_bb182_36, phi_bb182_37, phi_bb182_38, tmp301, tmp302);
  }

  TNode<JSAny> phi_bb177_17;
  TNode<IntPtrT> phi_bb177_18;
  TNode<BoolT> phi_bb177_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb177_23;
  TNode<IntPtrT> phi_bb177_24;
  TNode<IntPtrT> phi_bb177_25;
  TNode<IntPtrT> phi_bb177_27;
  TNode<IntPtrT> phi_bb177_29;
  TNode<IntPtrT> phi_bb177_30;
  TNode<IntPtrT> phi_bb177_31;
  TNode<IntPtrT> phi_bb177_34;
  TNode<BoolT> phi_bb177_35;
  TNode<BoolT> phi_bb177_36;
  TNode<Union<FixedArray, Smi>> phi_bb177_37;
  TNode<IntPtrT> phi_bb177_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb177_41;
  TNode<IntPtrT> phi_bb177_42;
  if (block177.is_used()) {
    ca_.Bind(&block177, &phi_bb177_17, &phi_bb177_18, &phi_bb177_19, &phi_bb177_23, &phi_bb177_24, &phi_bb177_25, &phi_bb177_27, &phi_bb177_29, &phi_bb177_30, &phi_bb177_31, &phi_bb177_34, &phi_bb177_35, &phi_bb177_36, &phi_bb177_37, &phi_bb177_38, &phi_bb177_41, &phi_bb177_42);
    ca_.Goto(&block171, phi_bb177_17, phi_bb177_18, phi_bb177_19, phi_bb177_23, phi_bb177_24, phi_bb177_25, phi_bb177_27, phi_bb177_29, phi_bb177_30, phi_bb177_31, phi_bb177_34, phi_bb177_35, phi_bb177_36, phi_bb177_37, phi_bb177_38, phi_bb177_41, phi_bb177_42);
  }

  TNode<JSAny> phi_bb175_17;
  TNode<IntPtrT> phi_bb175_18;
  TNode<BoolT> phi_bb175_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb175_23;
  TNode<IntPtrT> phi_bb175_24;
  TNode<IntPtrT> phi_bb175_25;
  TNode<IntPtrT> phi_bb175_27;
  TNode<IntPtrT> phi_bb175_29;
  TNode<IntPtrT> phi_bb175_30;
  TNode<IntPtrT> phi_bb175_31;
  TNode<IntPtrT> phi_bb175_34;
  TNode<BoolT> phi_bb175_35;
  TNode<BoolT> phi_bb175_36;
  TNode<Union<FixedArray, Smi>> phi_bb175_37;
  TNode<IntPtrT> phi_bb175_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<IntPtrT> tmp310;
  TNode<IntPtrT> tmp311;
  TNode<BoolT> tmp312;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_17, &phi_bb175_18, &phi_bb175_19, &phi_bb175_23, &phi_bb175_24, &phi_bb175_25, &phi_bb175_27, &phi_bb175_29, &phi_bb175_30, &phi_bb175_31, &phi_bb175_34, &phi_bb175_35, &phi_bb175_36, &phi_bb175_37, &phi_bb175_38);
    std::tie(tmp308, tmp309) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb175_31}).Flatten();
    tmp310 = FromConstexpr_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_)))));
    tmp311 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb175_31}, TNode<IntPtrT>{tmp310});
    tmp312 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block171, phi_bb175_17, phi_bb175_18, phi_bb175_19, phi_bb175_23, phi_bb175_24, phi_bb175_25, phi_bb175_27, phi_bb175_29, phi_bb175_30, tmp311, phi_bb175_34, tmp312, phi_bb175_36, phi_bb175_37, phi_bb175_38, tmp308, tmp309);
  }

  TNode<JSAny> phi_bb171_17;
  TNode<IntPtrT> phi_bb171_18;
  TNode<BoolT> phi_bb171_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb171_23;
  TNode<IntPtrT> phi_bb171_24;
  TNode<IntPtrT> phi_bb171_25;
  TNode<IntPtrT> phi_bb171_27;
  TNode<IntPtrT> phi_bb171_29;
  TNode<IntPtrT> phi_bb171_30;
  TNode<IntPtrT> phi_bb171_31;
  TNode<IntPtrT> phi_bb171_34;
  TNode<BoolT> phi_bb171_35;
  TNode<BoolT> phi_bb171_36;
  TNode<Union<FixedArray, Smi>> phi_bb171_37;
  TNode<IntPtrT> phi_bb171_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb171_41;
  TNode<IntPtrT> phi_bb171_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp313;
  TNode<IntPtrT> tmp314;
  TNode<Float64T> tmp315;
  TNode<Float64T> tmp316;
  TNode<Undefined> tmp317;
  TNode<BoolT> tmp318;
  if (block171.is_used()) {
    ca_.Bind(&block171, &phi_bb171_17, &phi_bb171_18, &phi_bb171_19, &phi_bb171_23, &phi_bb171_24, &phi_bb171_25, &phi_bb171_27, &phi_bb171_29, &phi_bb171_30, &phi_bb171_31, &phi_bb171_34, &phi_bb171_35, &phi_bb171_36, &phi_bb171_37, &phi_bb171_38, &phi_bb171_41, &phi_bb171_42);
    std::tie(tmp313, tmp314) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb171_41}, TNode<IntPtrT>{phi_bb171_42}, TorqueStructUnsafe_0{}}).Flatten();
    tmp315 = CodeStubAssembler(state_).ChangeTaggedToFloat64(TNode<Context>{p_context}, TNode<JSAny>{tmp207});
    tmp316 = CodeStubAssembler(state_).Float64SilenceNaN(TNode<Float64T>{tmp315});
    CodeStubAssembler(state_).StoreReference<Float64T>(CodeStubAssembler::Reference{tmp313, tmp314}, tmp316);
    tmp317 = Undefined_0(state_);
    tmp318 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp207}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp317});
    ca_.Branch(tmp318, &block183, std::vector<compiler::Node*>{phi_bb171_17, phi_bb171_18, phi_bb171_19, phi_bb171_23, phi_bb171_24, phi_bb171_25, phi_bb171_27, phi_bb171_29, phi_bb171_30, phi_bb171_31, phi_bb171_34, phi_bb171_35, phi_bb171_36, phi_bb171_37, phi_bb171_38, phi_bb171_41, phi_bb171_42}, &block184, std::vector<compiler::Node*>{phi_bb171_17, phi_bb171_18, phi_bb171_19, phi_bb171_23, phi_bb171_24, phi_bb171_25, phi_bb171_27, phi_bb171_29, phi_bb171_30, phi_bb171_31, phi_bb171_34, phi_bb171_35, phi_bb171_36, phi_bb171_37, phi_bb171_38, phi_bb171_41, phi_bb171_42});
  }

  TNode<JSAny> phi_bb183_17;
  TNode<IntPtrT> phi_bb183_18;
  TNode<BoolT> phi_bb183_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb183_23;
  TNode<IntPtrT> phi_bb183_24;
  TNode<IntPtrT> phi_bb183_25;
  TNode<IntPtrT> phi_bb183_27;
  TNode<IntPtrT> phi_bb183_29;
  TNode<IntPtrT> phi_bb183_30;
  TNode<IntPtrT> phi_bb183_31;
  TNode<IntPtrT> phi_bb183_34;
  TNode<BoolT> phi_bb183_35;
  TNode<BoolT> phi_bb183_36;
  TNode<Union<FixedArray, Smi>> phi_bb183_37;
  TNode<IntPtrT> phi_bb183_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb183_41;
  TNode<IntPtrT> phi_bb183_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<Float64T> tmp321;
  TNode<Float64T> tmp322;
  TNode<Float64T> tmp323;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_17, &phi_bb183_18, &phi_bb183_19, &phi_bb183_23, &phi_bb183_24, &phi_bb183_25, &phi_bb183_27, &phi_bb183_29, &phi_bb183_30, &phi_bb183_31, &phi_bb183_34, &phi_bb183_35, &phi_bb183_36, &phi_bb183_37, &phi_bb183_38, &phi_bb183_41, &phi_bb183_42);
    std::tie(tmp319, tmp320) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb183_41}, TNode<IntPtrT>{phi_bb183_42}, TorqueStructUnsafe_0{}}).Flatten();
    tmp321 = FromConstexpr_float64_constexpr_float64_0(state_, std::numeric_limits<double>::quiet_NaN());
    tmp322 = FromConstexpr_float64_constexpr_float64_0(state_, std::numeric_limits<double>::quiet_NaN());
    tmp323 = CodeStubAssembler(state_).Float64SilenceNaN(TNode<Float64T>{tmp322});
    CodeStubAssembler(state_).StoreReference<Float64T>(CodeStubAssembler::Reference{tmp319, tmp320}, tmp323);
    ca_.Goto(&block184, phi_bb183_17, phi_bb183_18, phi_bb183_19, phi_bb183_23, phi_bb183_24, phi_bb183_25, phi_bb183_27, phi_bb183_29, phi_bb183_30, phi_bb183_31, phi_bb183_34, phi_bb183_35, phi_bb183_36, phi_bb183_37, phi_bb183_38, phi_bb183_41, phi_bb183_42);
  }

  TNode<JSAny> phi_bb184_17;
  TNode<IntPtrT> phi_bb184_18;
  TNode<BoolT> phi_bb184_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb184_23;
  TNode<IntPtrT> phi_bb184_24;
  TNode<IntPtrT> phi_bb184_25;
  TNode<IntPtrT> phi_bb184_27;
  TNode<IntPtrT> phi_bb184_29;
  TNode<IntPtrT> phi_bb184_30;
  TNode<IntPtrT> phi_bb184_31;
  TNode<IntPtrT> phi_bb184_34;
  TNode<BoolT> phi_bb184_35;
  TNode<BoolT> phi_bb184_36;
  TNode<Union<FixedArray, Smi>> phi_bb184_37;
  TNode<IntPtrT> phi_bb184_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb184_41;
  TNode<IntPtrT> phi_bb184_42;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_17, &phi_bb184_18, &phi_bb184_19, &phi_bb184_23, &phi_bb184_24, &phi_bb184_25, &phi_bb184_27, &phi_bb184_29, &phi_bb184_30, &phi_bb184_31, &phi_bb184_34, &phi_bb184_35, &phi_bb184_36, &phi_bb184_37, &phi_bb184_38, &phi_bb184_41, &phi_bb184_42);
    ca_.Goto(&block170, phi_bb184_17, phi_bb184_18, phi_bb184_19, phi_bb184_23, phi_bb184_24, phi_bb184_25, phi_bb184_27, tmp284, phi_bb184_29, phi_bb184_30, phi_bb184_31, phi_bb184_34, phi_bb184_35, phi_bb184_36, phi_bb184_37, phi_bb184_38);
  }

  TNode<JSAny> phi_bb169_17;
  TNode<IntPtrT> phi_bb169_18;
  TNode<BoolT> phi_bb169_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb169_23;
  TNode<IntPtrT> phi_bb169_24;
  TNode<IntPtrT> phi_bb169_25;
  TNode<IntPtrT> phi_bb169_27;
  TNode<IntPtrT> phi_bb169_28;
  TNode<IntPtrT> phi_bb169_29;
  TNode<IntPtrT> phi_bb169_30;
  TNode<IntPtrT> phi_bb169_31;
  TNode<IntPtrT> phi_bb169_34;
  TNode<BoolT> phi_bb169_35;
  TNode<BoolT> phi_bb169_36;
  TNode<Union<FixedArray, Smi>> phi_bb169_37;
  TNode<IntPtrT> phi_bb169_38;
  TNode<Uint32T> tmp324;
  TNode<BoolT> tmp325;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_17, &phi_bb169_18, &phi_bb169_19, &phi_bb169_23, &phi_bb169_24, &phi_bb169_25, &phi_bb169_27, &phi_bb169_28, &phi_bb169_29, &phi_bb169_30, &phi_bb169_31, &phi_bb169_34, &phi_bb169_35, &phi_bb169_36, &phi_bb169_37, &phi_bb169_38);
    tmp324 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp325 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp212}, TNode<Uint32T>{tmp324});
    ca_.Branch(tmp325, &block185, std::vector<compiler::Node*>{phi_bb169_17, phi_bb169_18, phi_bb169_19, phi_bb169_23, phi_bb169_24, phi_bb169_25, phi_bb169_27, phi_bb169_28, phi_bb169_29, phi_bb169_30, phi_bb169_31, phi_bb169_34, phi_bb169_35, phi_bb169_36, phi_bb169_37, phi_bb169_38}, &block186, std::vector<compiler::Node*>{phi_bb169_17, phi_bb169_18, phi_bb169_19, phi_bb169_23, phi_bb169_24, phi_bb169_25, phi_bb169_27, phi_bb169_28, phi_bb169_29, phi_bb169_30, phi_bb169_31, phi_bb169_34, phi_bb169_35, phi_bb169_36, phi_bb169_37, phi_bb169_38});
  }

  TNode<JSAny> phi_bb185_17;
  TNode<IntPtrT> phi_bb185_18;
  TNode<BoolT> phi_bb185_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb185_23;
  TNode<IntPtrT> phi_bb185_24;
  TNode<IntPtrT> phi_bb185_25;
  TNode<IntPtrT> phi_bb185_27;
  TNode<IntPtrT> phi_bb185_28;
  TNode<IntPtrT> phi_bb185_29;
  TNode<IntPtrT> phi_bb185_30;
  TNode<IntPtrT> phi_bb185_31;
  TNode<IntPtrT> phi_bb185_34;
  TNode<BoolT> phi_bb185_35;
  TNode<BoolT> phi_bb185_36;
  TNode<Union<FixedArray, Smi>> phi_bb185_37;
  TNode<IntPtrT> phi_bb185_38;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_17, &phi_bb185_18, &phi_bb185_19, &phi_bb185_23, &phi_bb185_24, &phi_bb185_25, &phi_bb185_27, &phi_bb185_28, &phi_bb185_29, &phi_bb185_30, &phi_bb185_31, &phi_bb185_34, &phi_bb185_35, &phi_bb185_36, &phi_bb185_37, &phi_bb185_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block188, phi_bb185_17, phi_bb185_18, phi_bb185_19, phi_bb185_23, phi_bb185_24, phi_bb185_25, phi_bb185_27, phi_bb185_28, phi_bb185_29, phi_bb185_30, phi_bb185_31, phi_bb185_34, phi_bb185_35, phi_bb185_36, phi_bb185_37, phi_bb185_38);
    } else {
      ca_.Goto(&block189, phi_bb185_17, phi_bb185_18, phi_bb185_19, phi_bb185_23, phi_bb185_24, phi_bb185_25, phi_bb185_27, phi_bb185_28, phi_bb185_29, phi_bb185_30, phi_bb185_31, phi_bb185_34, phi_bb185_35, phi_bb185_36, phi_bb185_37, phi_bb185_38);
    }
  }

  TNode<JSAny> phi_bb188_17;
  TNode<IntPtrT> phi_bb188_18;
  TNode<BoolT> phi_bb188_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb188_23;
  TNode<IntPtrT> phi_bb188_24;
  TNode<IntPtrT> phi_bb188_25;
  TNode<IntPtrT> phi_bb188_27;
  TNode<IntPtrT> phi_bb188_28;
  TNode<IntPtrT> phi_bb188_29;
  TNode<IntPtrT> phi_bb188_30;
  TNode<IntPtrT> phi_bb188_31;
  TNode<IntPtrT> phi_bb188_34;
  TNode<BoolT> phi_bb188_35;
  TNode<BoolT> phi_bb188_36;
  TNode<Union<FixedArray, Smi>> phi_bb188_37;
  TNode<IntPtrT> phi_bb188_38;
  TNode<IntPtrT> tmp326;
  TNode<IntPtrT> tmp327;
  TNode<IntPtrT> tmp328;
  TNode<BoolT> tmp329;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_17, &phi_bb188_18, &phi_bb188_19, &phi_bb188_23, &phi_bb188_24, &phi_bb188_25, &phi_bb188_27, &phi_bb188_28, &phi_bb188_29, &phi_bb188_30, &phi_bb188_31, &phi_bb188_34, &phi_bb188_35, &phi_bb188_36, &phi_bb188_37, &phi_bb188_38);
    tmp326 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp327 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb188_27}, TNode<IntPtrT>{tmp326});
    tmp328 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp329 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb188_27}, TNode<IntPtrT>{tmp328});
    ca_.Branch(tmp329, &block192, std::vector<compiler::Node*>{phi_bb188_17, phi_bb188_18, phi_bb188_19, phi_bb188_23, phi_bb188_24, phi_bb188_25, phi_bb188_28, phi_bb188_29, phi_bb188_30, phi_bb188_31, phi_bb188_34, phi_bb188_35, phi_bb188_36, phi_bb188_37, phi_bb188_38}, &block193, std::vector<compiler::Node*>{phi_bb188_17, phi_bb188_18, phi_bb188_19, phi_bb188_23, phi_bb188_24, phi_bb188_25, phi_bb188_28, phi_bb188_29, phi_bb188_30, phi_bb188_31, phi_bb188_34, phi_bb188_35, phi_bb188_36, phi_bb188_37, phi_bb188_38});
  }

  TNode<JSAny> phi_bb192_17;
  TNode<IntPtrT> phi_bb192_18;
  TNode<BoolT> phi_bb192_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb192_23;
  TNode<IntPtrT> phi_bb192_24;
  TNode<IntPtrT> phi_bb192_25;
  TNode<IntPtrT> phi_bb192_28;
  TNode<IntPtrT> phi_bb192_29;
  TNode<IntPtrT> phi_bb192_30;
  TNode<IntPtrT> phi_bb192_31;
  TNode<IntPtrT> phi_bb192_34;
  TNode<BoolT> phi_bb192_35;
  TNode<BoolT> phi_bb192_36;
  TNode<Union<FixedArray, Smi>> phi_bb192_37;
  TNode<IntPtrT> phi_bb192_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp330;
  TNode<IntPtrT> tmp331;
  TNode<IntPtrT> tmp332;
  TNode<IntPtrT> tmp333;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_17, &phi_bb192_18, &phi_bb192_19, &phi_bb192_23, &phi_bb192_24, &phi_bb192_25, &phi_bb192_28, &phi_bb192_29, &phi_bb192_30, &phi_bb192_31, &phi_bb192_34, &phi_bb192_35, &phi_bb192_36, &phi_bb192_37, &phi_bb192_38);
    std::tie(tmp330, tmp331) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb192_29}).Flatten();
    tmp332 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp333 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb192_29}, TNode<IntPtrT>{tmp332});
    ca_.Goto(&block191, phi_bb192_17, phi_bb192_18, phi_bb192_19, phi_bb192_23, phi_bb192_24, phi_bb192_25, phi_bb192_28, tmp333, phi_bb192_30, phi_bb192_31, phi_bb192_34, phi_bb192_35, phi_bb192_36, phi_bb192_37, phi_bb192_38, tmp330, tmp331);
  }

  TNode<JSAny> phi_bb193_17;
  TNode<IntPtrT> phi_bb193_18;
  TNode<BoolT> phi_bb193_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb193_23;
  TNode<IntPtrT> phi_bb193_24;
  TNode<IntPtrT> phi_bb193_25;
  TNode<IntPtrT> phi_bb193_28;
  TNode<IntPtrT> phi_bb193_29;
  TNode<IntPtrT> phi_bb193_30;
  TNode<IntPtrT> phi_bb193_31;
  TNode<IntPtrT> phi_bb193_34;
  TNode<BoolT> phi_bb193_35;
  TNode<BoolT> phi_bb193_36;
  TNode<Union<FixedArray, Smi>> phi_bb193_37;
  TNode<IntPtrT> phi_bb193_38;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_17, &phi_bb193_18, &phi_bb193_19, &phi_bb193_23, &phi_bb193_24, &phi_bb193_25, &phi_bb193_28, &phi_bb193_29, &phi_bb193_30, &phi_bb193_31, &phi_bb193_34, &phi_bb193_35, &phi_bb193_36, &phi_bb193_37, &phi_bb193_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block195, phi_bb193_17, phi_bb193_18, phi_bb193_19, phi_bb193_23, phi_bb193_24, phi_bb193_25, phi_bb193_28, phi_bb193_29, phi_bb193_30, phi_bb193_31, phi_bb193_34, phi_bb193_35, phi_bb193_36, phi_bb193_37, phi_bb193_38);
    } else {
      ca_.Goto(&block196, phi_bb193_17, phi_bb193_18, phi_bb193_19, phi_bb193_23, phi_bb193_24, phi_bb193_25, phi_bb193_28, phi_bb193_29, phi_bb193_30, phi_bb193_31, phi_bb193_34, phi_bb193_35, phi_bb193_36, phi_bb193_37, phi_bb193_38);
    }
  }

  TNode<JSAny> phi_bb195_17;
  TNode<IntPtrT> phi_bb195_18;
  TNode<BoolT> phi_bb195_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb195_23;
  TNode<IntPtrT> phi_bb195_24;
  TNode<IntPtrT> phi_bb195_25;
  TNode<IntPtrT> phi_bb195_28;
  TNode<IntPtrT> phi_bb195_29;
  TNode<IntPtrT> phi_bb195_30;
  TNode<IntPtrT> phi_bb195_31;
  TNode<IntPtrT> phi_bb195_34;
  TNode<BoolT> phi_bb195_35;
  TNode<BoolT> phi_bb195_36;
  TNode<Union<FixedArray, Smi>> phi_bb195_37;
  TNode<IntPtrT> phi_bb195_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp334;
  TNode<IntPtrT> tmp335;
  TNode<IntPtrT> tmp336;
  TNode<IntPtrT> tmp337;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_17, &phi_bb195_18, &phi_bb195_19, &phi_bb195_23, &phi_bb195_24, &phi_bb195_25, &phi_bb195_28, &phi_bb195_29, &phi_bb195_30, &phi_bb195_31, &phi_bb195_34, &phi_bb195_35, &phi_bb195_36, &phi_bb195_37, &phi_bb195_38);
    std::tie(tmp334, tmp335) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb195_31}).Flatten();
    tmp336 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp337 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb195_31}, TNode<IntPtrT>{tmp336});
    ca_.Goto(&block194, phi_bb195_17, phi_bb195_18, phi_bb195_19, phi_bb195_23, phi_bb195_24, phi_bb195_25, phi_bb195_28, phi_bb195_29, phi_bb195_30, tmp337, phi_bb195_34, phi_bb195_35, phi_bb195_36, phi_bb195_37, phi_bb195_38, tmp334, tmp335);
  }

  TNode<JSAny> phi_bb196_17;
  TNode<IntPtrT> phi_bb196_18;
  TNode<BoolT> phi_bb196_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb196_23;
  TNode<IntPtrT> phi_bb196_24;
  TNode<IntPtrT> phi_bb196_25;
  TNode<IntPtrT> phi_bb196_28;
  TNode<IntPtrT> phi_bb196_29;
  TNode<IntPtrT> phi_bb196_30;
  TNode<IntPtrT> phi_bb196_31;
  TNode<IntPtrT> phi_bb196_34;
  TNode<BoolT> phi_bb196_35;
  TNode<BoolT> phi_bb196_36;
  TNode<Union<FixedArray, Smi>> phi_bb196_37;
  TNode<IntPtrT> phi_bb196_38;
  TNode<IntPtrT> tmp338;
  TNode<BoolT> tmp339;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_17, &phi_bb196_18, &phi_bb196_19, &phi_bb196_23, &phi_bb196_24, &phi_bb196_25, &phi_bb196_28, &phi_bb196_29, &phi_bb196_30, &phi_bb196_31, &phi_bb196_34, &phi_bb196_35, &phi_bb196_36, &phi_bb196_37, &phi_bb196_38);
    tmp338 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp339 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb196_34}, TNode<IntPtrT>{tmp338});
    ca_.Branch(tmp339, &block198, std::vector<compiler::Node*>{phi_bb196_17, phi_bb196_18, phi_bb196_19, phi_bb196_23, phi_bb196_24, phi_bb196_25, phi_bb196_28, phi_bb196_29, phi_bb196_30, phi_bb196_31, phi_bb196_34, phi_bb196_35, phi_bb196_36, phi_bb196_37, phi_bb196_38}, &block199, std::vector<compiler::Node*>{phi_bb196_17, phi_bb196_18, phi_bb196_19, phi_bb196_23, phi_bb196_24, phi_bb196_25, phi_bb196_28, phi_bb196_29, phi_bb196_30, phi_bb196_31, phi_bb196_34, phi_bb196_35, phi_bb196_36, phi_bb196_37, phi_bb196_38});
  }

  TNode<JSAny> phi_bb198_17;
  TNode<IntPtrT> phi_bb198_18;
  TNode<BoolT> phi_bb198_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb198_23;
  TNode<IntPtrT> phi_bb198_24;
  TNode<IntPtrT> phi_bb198_25;
  TNode<IntPtrT> phi_bb198_28;
  TNode<IntPtrT> phi_bb198_29;
  TNode<IntPtrT> phi_bb198_30;
  TNode<IntPtrT> phi_bb198_31;
  TNode<IntPtrT> phi_bb198_34;
  TNode<BoolT> phi_bb198_35;
  TNode<BoolT> phi_bb198_36;
  TNode<Union<FixedArray, Smi>> phi_bb198_37;
  TNode<IntPtrT> phi_bb198_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp340;
  TNode<IntPtrT> tmp341;
  TNode<IntPtrT> tmp342;
  TNode<BoolT> tmp343;
  if (block198.is_used()) {
    ca_.Bind(&block198, &phi_bb198_17, &phi_bb198_18, &phi_bb198_19, &phi_bb198_23, &phi_bb198_24, &phi_bb198_25, &phi_bb198_28, &phi_bb198_29, &phi_bb198_30, &phi_bb198_31, &phi_bb198_34, &phi_bb198_35, &phi_bb198_36, &phi_bb198_37, &phi_bb198_38);
    std::tie(tmp340, tmp341) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb198_34}).Flatten();
    tmp342 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp343 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block194, phi_bb198_17, phi_bb198_18, phi_bb198_19, phi_bb198_23, phi_bb198_24, phi_bb198_25, phi_bb198_28, phi_bb198_29, phi_bb198_30, phi_bb198_31, tmp342, tmp343, phi_bb198_36, phi_bb198_37, phi_bb198_38, tmp340, tmp341);
  }

  TNode<JSAny> phi_bb199_17;
  TNode<IntPtrT> phi_bb199_18;
  TNode<BoolT> phi_bb199_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb199_23;
  TNode<IntPtrT> phi_bb199_24;
  TNode<IntPtrT> phi_bb199_25;
  TNode<IntPtrT> phi_bb199_28;
  TNode<IntPtrT> phi_bb199_29;
  TNode<IntPtrT> phi_bb199_30;
  TNode<IntPtrT> phi_bb199_31;
  TNode<IntPtrT> phi_bb199_34;
  TNode<BoolT> phi_bb199_35;
  TNode<BoolT> phi_bb199_36;
  TNode<Union<FixedArray, Smi>> phi_bb199_37;
  TNode<IntPtrT> phi_bb199_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp344;
  TNode<IntPtrT> tmp345;
  TNode<IntPtrT> tmp346;
  TNode<IntPtrT> tmp347;
  TNode<IntPtrT> tmp348;
  TNode<IntPtrT> tmp349;
  TNode<BoolT> tmp350;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_17, &phi_bb199_18, &phi_bb199_19, &phi_bb199_23, &phi_bb199_24, &phi_bb199_25, &phi_bb199_28, &phi_bb199_29, &phi_bb199_30, &phi_bb199_31, &phi_bb199_34, &phi_bb199_35, &phi_bb199_36, &phi_bb199_37, &phi_bb199_38);
    std::tie(tmp344, tmp345) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb199_31}).Flatten();
    tmp346 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp347 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb199_31}, TNode<IntPtrT>{tmp346});
    tmp348 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp349 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp347}, TNode<IntPtrT>{tmp348});
    tmp350 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block194, phi_bb199_17, phi_bb199_18, phi_bb199_19, phi_bb199_23, phi_bb199_24, phi_bb199_25, phi_bb199_28, phi_bb199_29, phi_bb199_30, tmp349, tmp347, tmp350, phi_bb199_36, phi_bb199_37, phi_bb199_38, tmp344, tmp345);
  }

  TNode<JSAny> phi_bb194_17;
  TNode<IntPtrT> phi_bb194_18;
  TNode<BoolT> phi_bb194_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb194_23;
  TNode<IntPtrT> phi_bb194_24;
  TNode<IntPtrT> phi_bb194_25;
  TNode<IntPtrT> phi_bb194_28;
  TNode<IntPtrT> phi_bb194_29;
  TNode<IntPtrT> phi_bb194_30;
  TNode<IntPtrT> phi_bb194_31;
  TNode<IntPtrT> phi_bb194_34;
  TNode<BoolT> phi_bb194_35;
  TNode<BoolT> phi_bb194_36;
  TNode<Union<FixedArray, Smi>> phi_bb194_37;
  TNode<IntPtrT> phi_bb194_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb194_41;
  TNode<IntPtrT> phi_bb194_42;
  if (block194.is_used()) {
    ca_.Bind(&block194, &phi_bb194_17, &phi_bb194_18, &phi_bb194_19, &phi_bb194_23, &phi_bb194_24, &phi_bb194_25, &phi_bb194_28, &phi_bb194_29, &phi_bb194_30, &phi_bb194_31, &phi_bb194_34, &phi_bb194_35, &phi_bb194_36, &phi_bb194_37, &phi_bb194_38, &phi_bb194_41, &phi_bb194_42);
    ca_.Goto(&block191, phi_bb194_17, phi_bb194_18, phi_bb194_19, phi_bb194_23, phi_bb194_24, phi_bb194_25, phi_bb194_28, phi_bb194_29, phi_bb194_30, phi_bb194_31, phi_bb194_34, phi_bb194_35, phi_bb194_36, phi_bb194_37, phi_bb194_38, phi_bb194_41, phi_bb194_42);
  }

  TNode<JSAny> phi_bb191_17;
  TNode<IntPtrT> phi_bb191_18;
  TNode<BoolT> phi_bb191_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb191_23;
  TNode<IntPtrT> phi_bb191_24;
  TNode<IntPtrT> phi_bb191_25;
  TNode<IntPtrT> phi_bb191_28;
  TNode<IntPtrT> phi_bb191_29;
  TNode<IntPtrT> phi_bb191_30;
  TNode<IntPtrT> phi_bb191_31;
  TNode<IntPtrT> phi_bb191_34;
  TNode<BoolT> phi_bb191_35;
  TNode<BoolT> phi_bb191_36;
  TNode<Union<FixedArray, Smi>> phi_bb191_37;
  TNode<IntPtrT> phi_bb191_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb191_41;
  TNode<IntPtrT> phi_bb191_42;
  TNode<IntPtrT> tmp351;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_17, &phi_bb191_18, &phi_bb191_19, &phi_bb191_23, &phi_bb191_24, &phi_bb191_25, &phi_bb191_28, &phi_bb191_29, &phi_bb191_30, &phi_bb191_31, &phi_bb191_34, &phi_bb191_35, &phi_bb191_36, &phi_bb191_37, &phi_bb191_38, &phi_bb191_41, &phi_bb191_42);
    tmp351 = TruncateBigIntToI64_0(state_, TNode<Context>{p_context}, TNode<JSAny>{tmp207});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb191_41, phi_bb191_42}, tmp351);
    ca_.Goto(&block190, phi_bb191_17, phi_bb191_18, phi_bb191_19, phi_bb191_23, phi_bb191_24, phi_bb191_25, tmp327, phi_bb191_28, phi_bb191_29, phi_bb191_30, phi_bb191_31, phi_bb191_34, phi_bb191_35, phi_bb191_36, phi_bb191_37, phi_bb191_38);
  }

  TNode<JSAny> phi_bb189_17;
  TNode<IntPtrT> phi_bb189_18;
  TNode<BoolT> phi_bb189_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb189_23;
  TNode<IntPtrT> phi_bb189_24;
  TNode<IntPtrT> phi_bb189_25;
  TNode<IntPtrT> phi_bb189_27;
  TNode<IntPtrT> phi_bb189_28;
  TNode<IntPtrT> phi_bb189_29;
  TNode<IntPtrT> phi_bb189_30;
  TNode<IntPtrT> phi_bb189_31;
  TNode<IntPtrT> phi_bb189_34;
  TNode<BoolT> phi_bb189_35;
  TNode<BoolT> phi_bb189_36;
  TNode<Union<FixedArray, Smi>> phi_bb189_37;
  TNode<IntPtrT> phi_bb189_38;
  TNode<IntPtrT> tmp352;
  TNode<IntPtrT> tmp353;
  TNode<IntPtrT> tmp354;
  TNode<BoolT> tmp355;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_17, &phi_bb189_18, &phi_bb189_19, &phi_bb189_23, &phi_bb189_24, &phi_bb189_25, &phi_bb189_27, &phi_bb189_28, &phi_bb189_29, &phi_bb189_30, &phi_bb189_31, &phi_bb189_34, &phi_bb189_35, &phi_bb189_36, &phi_bb189_37, &phi_bb189_38);
    tmp352 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp353 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb189_27}, TNode<IntPtrT>{tmp352});
    tmp354 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp355 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb189_27}, TNode<IntPtrT>{tmp354});
    ca_.Branch(tmp355, &block201, std::vector<compiler::Node*>{phi_bb189_17, phi_bb189_18, phi_bb189_19, phi_bb189_23, phi_bb189_24, phi_bb189_25, phi_bb189_28, phi_bb189_29, phi_bb189_30, phi_bb189_31, phi_bb189_34, phi_bb189_35, phi_bb189_36, phi_bb189_37, phi_bb189_38}, &block202, std::vector<compiler::Node*>{phi_bb189_17, phi_bb189_18, phi_bb189_19, phi_bb189_23, phi_bb189_24, phi_bb189_25, phi_bb189_28, phi_bb189_29, phi_bb189_30, phi_bb189_31, phi_bb189_34, phi_bb189_35, phi_bb189_36, phi_bb189_37, phi_bb189_38});
  }

  TNode<JSAny> phi_bb201_17;
  TNode<IntPtrT> phi_bb201_18;
  TNode<BoolT> phi_bb201_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb201_23;
  TNode<IntPtrT> phi_bb201_24;
  TNode<IntPtrT> phi_bb201_25;
  TNode<IntPtrT> phi_bb201_28;
  TNode<IntPtrT> phi_bb201_29;
  TNode<IntPtrT> phi_bb201_30;
  TNode<IntPtrT> phi_bb201_31;
  TNode<IntPtrT> phi_bb201_34;
  TNode<BoolT> phi_bb201_35;
  TNode<BoolT> phi_bb201_36;
  TNode<Union<FixedArray, Smi>> phi_bb201_37;
  TNode<IntPtrT> phi_bb201_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp356;
  TNode<IntPtrT> tmp357;
  TNode<IntPtrT> tmp358;
  TNode<IntPtrT> tmp359;
  if (block201.is_used()) {
    ca_.Bind(&block201, &phi_bb201_17, &phi_bb201_18, &phi_bb201_19, &phi_bb201_23, &phi_bb201_24, &phi_bb201_25, &phi_bb201_28, &phi_bb201_29, &phi_bb201_30, &phi_bb201_31, &phi_bb201_34, &phi_bb201_35, &phi_bb201_36, &phi_bb201_37, &phi_bb201_38);
    std::tie(tmp356, tmp357) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb201_29}).Flatten();
    tmp358 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp359 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb201_29}, TNode<IntPtrT>{tmp358});
    ca_.Goto(&block200, phi_bb201_17, phi_bb201_18, phi_bb201_19, phi_bb201_23, phi_bb201_24, phi_bb201_25, phi_bb201_28, tmp359, phi_bb201_30, phi_bb201_31, phi_bb201_34, phi_bb201_35, phi_bb201_36, phi_bb201_37, phi_bb201_38, tmp356, tmp357);
  }

  TNode<JSAny> phi_bb202_17;
  TNode<IntPtrT> phi_bb202_18;
  TNode<BoolT> phi_bb202_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb202_23;
  TNode<IntPtrT> phi_bb202_24;
  TNode<IntPtrT> phi_bb202_25;
  TNode<IntPtrT> phi_bb202_28;
  TNode<IntPtrT> phi_bb202_29;
  TNode<IntPtrT> phi_bb202_30;
  TNode<IntPtrT> phi_bb202_31;
  TNode<IntPtrT> phi_bb202_34;
  TNode<BoolT> phi_bb202_35;
  TNode<BoolT> phi_bb202_36;
  TNode<Union<FixedArray, Smi>> phi_bb202_37;
  TNode<IntPtrT> phi_bb202_38;
  if (block202.is_used()) {
    ca_.Bind(&block202, &phi_bb202_17, &phi_bb202_18, &phi_bb202_19, &phi_bb202_23, &phi_bb202_24, &phi_bb202_25, &phi_bb202_28, &phi_bb202_29, &phi_bb202_30, &phi_bb202_31, &phi_bb202_34, &phi_bb202_35, &phi_bb202_36, &phi_bb202_37, &phi_bb202_38);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block204, phi_bb202_17, phi_bb202_18, phi_bb202_19, phi_bb202_23, phi_bb202_24, phi_bb202_25, phi_bb202_28, phi_bb202_29, phi_bb202_30, phi_bb202_31, phi_bb202_34, phi_bb202_35, phi_bb202_36, phi_bb202_37, phi_bb202_38);
    } else {
      ca_.Goto(&block205, phi_bb202_17, phi_bb202_18, phi_bb202_19, phi_bb202_23, phi_bb202_24, phi_bb202_25, phi_bb202_28, phi_bb202_29, phi_bb202_30, phi_bb202_31, phi_bb202_34, phi_bb202_35, phi_bb202_36, phi_bb202_37, phi_bb202_38);
    }
  }

  TNode<JSAny> phi_bb204_17;
  TNode<IntPtrT> phi_bb204_18;
  TNode<BoolT> phi_bb204_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb204_23;
  TNode<IntPtrT> phi_bb204_24;
  TNode<IntPtrT> phi_bb204_25;
  TNode<IntPtrT> phi_bb204_28;
  TNode<IntPtrT> phi_bb204_29;
  TNode<IntPtrT> phi_bb204_30;
  TNode<IntPtrT> phi_bb204_31;
  TNode<IntPtrT> phi_bb204_34;
  TNode<BoolT> phi_bb204_35;
  TNode<BoolT> phi_bb204_36;
  TNode<Union<FixedArray, Smi>> phi_bb204_37;
  TNode<IntPtrT> phi_bb204_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp360;
  TNode<IntPtrT> tmp361;
  TNode<IntPtrT> tmp362;
  TNode<IntPtrT> tmp363;
  if (block204.is_used()) {
    ca_.Bind(&block204, &phi_bb204_17, &phi_bb204_18, &phi_bb204_19, &phi_bb204_23, &phi_bb204_24, &phi_bb204_25, &phi_bb204_28, &phi_bb204_29, &phi_bb204_30, &phi_bb204_31, &phi_bb204_34, &phi_bb204_35, &phi_bb204_36, &phi_bb204_37, &phi_bb204_38);
    std::tie(tmp360, tmp361) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb204_31}).Flatten();
    tmp362 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp363 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb204_31}, TNode<IntPtrT>{tmp362});
    ca_.Goto(&block203, phi_bb204_17, phi_bb204_18, phi_bb204_19, phi_bb204_23, phi_bb204_24, phi_bb204_25, phi_bb204_28, phi_bb204_29, phi_bb204_30, tmp363, phi_bb204_34, phi_bb204_35, phi_bb204_36, phi_bb204_37, phi_bb204_38, tmp360, tmp361);
  }

  TNode<JSAny> phi_bb205_17;
  TNode<IntPtrT> phi_bb205_18;
  TNode<BoolT> phi_bb205_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb205_23;
  TNode<IntPtrT> phi_bb205_24;
  TNode<IntPtrT> phi_bb205_25;
  TNode<IntPtrT> phi_bb205_28;
  TNode<IntPtrT> phi_bb205_29;
  TNode<IntPtrT> phi_bb205_30;
  TNode<IntPtrT> phi_bb205_31;
  TNode<IntPtrT> phi_bb205_34;
  TNode<BoolT> phi_bb205_35;
  TNode<BoolT> phi_bb205_36;
  TNode<Union<FixedArray, Smi>> phi_bb205_37;
  TNode<IntPtrT> phi_bb205_38;
  TNode<IntPtrT> tmp364;
  TNode<BoolT> tmp365;
  if (block205.is_used()) {
    ca_.Bind(&block205, &phi_bb205_17, &phi_bb205_18, &phi_bb205_19, &phi_bb205_23, &phi_bb205_24, &phi_bb205_25, &phi_bb205_28, &phi_bb205_29, &phi_bb205_30, &phi_bb205_31, &phi_bb205_34, &phi_bb205_35, &phi_bb205_36, &phi_bb205_37, &phi_bb205_38);
    tmp364 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp365 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb205_34}, TNode<IntPtrT>{tmp364});
    ca_.Branch(tmp365, &block207, std::vector<compiler::Node*>{phi_bb205_17, phi_bb205_18, phi_bb205_19, phi_bb205_23, phi_bb205_24, phi_bb205_25, phi_bb205_28, phi_bb205_29, phi_bb205_30, phi_bb205_31, phi_bb205_34, phi_bb205_35, phi_bb205_36, phi_bb205_37, phi_bb205_38}, &block208, std::vector<compiler::Node*>{phi_bb205_17, phi_bb205_18, phi_bb205_19, phi_bb205_23, phi_bb205_24, phi_bb205_25, phi_bb205_28, phi_bb205_29, phi_bb205_30, phi_bb205_31, phi_bb205_34, phi_bb205_35, phi_bb205_36, phi_bb205_37, phi_bb205_38});
  }

  TNode<JSAny> phi_bb207_17;
  TNode<IntPtrT> phi_bb207_18;
  TNode<BoolT> phi_bb207_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb207_23;
  TNode<IntPtrT> phi_bb207_24;
  TNode<IntPtrT> phi_bb207_25;
  TNode<IntPtrT> phi_bb207_28;
  TNode<IntPtrT> phi_bb207_29;
  TNode<IntPtrT> phi_bb207_30;
  TNode<IntPtrT> phi_bb207_31;
  TNode<IntPtrT> phi_bb207_34;
  TNode<BoolT> phi_bb207_35;
  TNode<BoolT> phi_bb207_36;
  TNode<Union<FixedArray, Smi>> phi_bb207_37;
  TNode<IntPtrT> phi_bb207_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp366;
  TNode<IntPtrT> tmp367;
  TNode<IntPtrT> tmp368;
  TNode<BoolT> tmp369;
  if (block207.is_used()) {
    ca_.Bind(&block207, &phi_bb207_17, &phi_bb207_18, &phi_bb207_19, &phi_bb207_23, &phi_bb207_24, &phi_bb207_25, &phi_bb207_28, &phi_bb207_29, &phi_bb207_30, &phi_bb207_31, &phi_bb207_34, &phi_bb207_35, &phi_bb207_36, &phi_bb207_37, &phi_bb207_38);
    std::tie(tmp366, tmp367) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb207_34}).Flatten();
    tmp368 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp369 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block203, phi_bb207_17, phi_bb207_18, phi_bb207_19, phi_bb207_23, phi_bb207_24, phi_bb207_25, phi_bb207_28, phi_bb207_29, phi_bb207_30, phi_bb207_31, tmp368, tmp369, phi_bb207_36, phi_bb207_37, phi_bb207_38, tmp366, tmp367);
  }

  TNode<JSAny> phi_bb208_17;
  TNode<IntPtrT> phi_bb208_18;
  TNode<BoolT> phi_bb208_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb208_23;
  TNode<IntPtrT> phi_bb208_24;
  TNode<IntPtrT> phi_bb208_25;
  TNode<IntPtrT> phi_bb208_28;
  TNode<IntPtrT> phi_bb208_29;
  TNode<IntPtrT> phi_bb208_30;
  TNode<IntPtrT> phi_bb208_31;
  TNode<IntPtrT> phi_bb208_34;
  TNode<BoolT> phi_bb208_35;
  TNode<BoolT> phi_bb208_36;
  TNode<Union<FixedArray, Smi>> phi_bb208_37;
  TNode<IntPtrT> phi_bb208_38;
  TNode<Union<HeapObject, TaggedIndex>> tmp370;
  TNode<IntPtrT> tmp371;
  TNode<IntPtrT> tmp372;
  TNode<IntPtrT> tmp373;
  TNode<IntPtrT> tmp374;
  TNode<IntPtrT> tmp375;
  TNode<BoolT> tmp376;
  if (block208.is_used()) {
    ca_.Bind(&block208, &phi_bb208_17, &phi_bb208_18, &phi_bb208_19, &phi_bb208_23, &phi_bb208_24, &phi_bb208_25, &phi_bb208_28, &phi_bb208_29, &phi_bb208_30, &phi_bb208_31, &phi_bb208_34, &phi_bb208_35, &phi_bb208_36, &phi_bb208_37, &phi_bb208_38);
    std::tie(tmp370, tmp371) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb208_31}).Flatten();
    tmp372 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp373 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb208_31}, TNode<IntPtrT>{tmp372});
    tmp374 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp375 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp373}, TNode<IntPtrT>{tmp374});
    tmp376 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block203, phi_bb208_17, phi_bb208_18, phi_bb208_19, phi_bb208_23, phi_bb208_24, phi_bb208_25, phi_bb208_28, phi_bb208_29, phi_bb208_30, tmp375, tmp373, tmp376, phi_bb208_36, phi_bb208_37, phi_bb208_38, tmp370, tmp371);
  }

  TNode<JSAny> phi_bb203_17;
  TNode<IntPtrT> phi_bb203_18;
  TNode<BoolT> phi_bb203_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb203_23;
  TNode<IntPtrT> phi_bb203_24;
  TNode<IntPtrT> phi_bb203_25;
  TNode<IntPtrT> phi_bb203_28;
  TNode<IntPtrT> phi_bb203_29;
  TNode<IntPtrT> phi_bb203_30;
  TNode<IntPtrT> phi_bb203_31;
  TNode<IntPtrT> phi_bb203_34;
  TNode<BoolT> phi_bb203_35;
  TNode<BoolT> phi_bb203_36;
  TNode<Union<FixedArray, Smi>> phi_bb203_37;
  TNode<IntPtrT> phi_bb203_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb203_41;
  TNode<IntPtrT> phi_bb203_42;
  if (block203.is_used()) {
    ca_.Bind(&block203, &phi_bb203_17, &phi_bb203_18, &phi_bb203_19, &phi_bb203_23, &phi_bb203_24, &phi_bb203_25, &phi_bb203_28, &phi_bb203_29, &phi_bb203_30, &phi_bb203_31, &phi_bb203_34, &phi_bb203_35, &phi_bb203_36, &phi_bb203_37, &phi_bb203_38, &phi_bb203_41, &phi_bb203_42);
    ca_.Goto(&block200, phi_bb203_17, phi_bb203_18, phi_bb203_19, phi_bb203_23, phi_bb203_24, phi_bb203_25, phi_bb203_28, phi_bb203_29, phi_bb203_30, phi_bb203_31, phi_bb203_34, phi_bb203_35, phi_bb203_36, phi_bb203_37, phi_bb203_38, phi_bb203_41, phi_bb203_42);
  }

  TNode<JSAny> phi_bb200_17;
  TNode<IntPtrT> phi_bb200_18;
  TNode<BoolT> phi_bb200_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb200_23;
  TNode<IntPtrT> phi_bb200_24;
  TNode<IntPtrT> phi_bb200_25;
  TNode<IntPtrT> phi_bb200_28;
  TNode<IntPtrT> phi_bb200_29;
  TNode<IntPtrT> phi_bb200_30;
  TNode<IntPtrT> phi_bb200_31;
  TNode<IntPtrT> phi_bb200_34;
  TNode<BoolT> phi_bb200_35;
  TNode<BoolT> phi_bb200_36;
  TNode<Union<FixedArray, Smi>> phi_bb200_37;
  TNode<IntPtrT> phi_bb200_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb200_41;
  TNode<IntPtrT> phi_bb200_42;
  TNode<IntPtrT> tmp377;
  TNode<IntPtrT> tmp378;
  TNode<IntPtrT> tmp379;
  TNode<BoolT> tmp380;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_17, &phi_bb200_18, &phi_bb200_19, &phi_bb200_23, &phi_bb200_24, &phi_bb200_25, &phi_bb200_28, &phi_bb200_29, &phi_bb200_30, &phi_bb200_31, &phi_bb200_34, &phi_bb200_35, &phi_bb200_36, &phi_bb200_37, &phi_bb200_38, &phi_bb200_41, &phi_bb200_42);
    tmp377 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp378 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp353}, TNode<IntPtrT>{tmp377});
    tmp379 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp380 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp353}, TNode<IntPtrT>{tmp379});
    ca_.Branch(tmp380, &block210, std::vector<compiler::Node*>{phi_bb200_17, phi_bb200_18, phi_bb200_19, phi_bb200_23, phi_bb200_24, phi_bb200_25, phi_bb200_28, phi_bb200_29, phi_bb200_30, phi_bb200_31, phi_bb200_34, phi_bb200_35, phi_bb200_36, phi_bb200_37, phi_bb200_38, phi_bb200_41, phi_bb200_42}, &block211, std::vector<compiler::Node*>{phi_bb200_17, phi_bb200_18, phi_bb200_19, phi_bb200_23, phi_bb200_24, phi_bb200_25, phi_bb200_28, phi_bb200_29, phi_bb200_30, phi_bb200_31, phi_bb200_34, phi_bb200_35, phi_bb200_36, phi_bb200_37, phi_bb200_38, phi_bb200_41, phi_bb200_42});
  }

  TNode<JSAny> phi_bb210_17;
  TNode<IntPtrT> phi_bb210_18;
  TNode<BoolT> phi_bb210_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb210_23;
  TNode<IntPtrT> phi_bb210_24;
  TNode<IntPtrT> phi_bb210_25;
  TNode<IntPtrT> phi_bb210_28;
  TNode<IntPtrT> phi_bb210_29;
  TNode<IntPtrT> phi_bb210_30;
  TNode<IntPtrT> phi_bb210_31;
  TNode<IntPtrT> phi_bb210_34;
  TNode<BoolT> phi_bb210_35;
  TNode<BoolT> phi_bb210_36;
  TNode<Union<FixedArray, Smi>> phi_bb210_37;
  TNode<IntPtrT> phi_bb210_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb210_41;
  TNode<IntPtrT> phi_bb210_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp381;
  TNode<IntPtrT> tmp382;
  TNode<IntPtrT> tmp383;
  TNode<IntPtrT> tmp384;
  if (block210.is_used()) {
    ca_.Bind(&block210, &phi_bb210_17, &phi_bb210_18, &phi_bb210_19, &phi_bb210_23, &phi_bb210_24, &phi_bb210_25, &phi_bb210_28, &phi_bb210_29, &phi_bb210_30, &phi_bb210_31, &phi_bb210_34, &phi_bb210_35, &phi_bb210_36, &phi_bb210_37, &phi_bb210_38, &phi_bb210_41, &phi_bb210_42);
    std::tie(tmp381, tmp382) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb210_29}).Flatten();
    tmp383 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp384 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb210_29}, TNode<IntPtrT>{tmp383});
    ca_.Goto(&block209, phi_bb210_17, phi_bb210_18, phi_bb210_19, phi_bb210_23, phi_bb210_24, phi_bb210_25, phi_bb210_28, tmp384, phi_bb210_30, phi_bb210_31, phi_bb210_34, phi_bb210_35, phi_bb210_36, phi_bb210_37, phi_bb210_38, phi_bb210_41, phi_bb210_42, tmp381, tmp382);
  }

  TNode<JSAny> phi_bb211_17;
  TNode<IntPtrT> phi_bb211_18;
  TNode<BoolT> phi_bb211_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb211_23;
  TNode<IntPtrT> phi_bb211_24;
  TNode<IntPtrT> phi_bb211_25;
  TNode<IntPtrT> phi_bb211_28;
  TNode<IntPtrT> phi_bb211_29;
  TNode<IntPtrT> phi_bb211_30;
  TNode<IntPtrT> phi_bb211_31;
  TNode<IntPtrT> phi_bb211_34;
  TNode<BoolT> phi_bb211_35;
  TNode<BoolT> phi_bb211_36;
  TNode<Union<FixedArray, Smi>> phi_bb211_37;
  TNode<IntPtrT> phi_bb211_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb211_41;
  TNode<IntPtrT> phi_bb211_42;
  if (block211.is_used()) {
    ca_.Bind(&block211, &phi_bb211_17, &phi_bb211_18, &phi_bb211_19, &phi_bb211_23, &phi_bb211_24, &phi_bb211_25, &phi_bb211_28, &phi_bb211_29, &phi_bb211_30, &phi_bb211_31, &phi_bb211_34, &phi_bb211_35, &phi_bb211_36, &phi_bb211_37, &phi_bb211_38, &phi_bb211_41, &phi_bb211_42);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block213, phi_bb211_17, phi_bb211_18, phi_bb211_19, phi_bb211_23, phi_bb211_24, phi_bb211_25, phi_bb211_28, phi_bb211_29, phi_bb211_30, phi_bb211_31, phi_bb211_34, phi_bb211_35, phi_bb211_36, phi_bb211_37, phi_bb211_38, phi_bb211_41, phi_bb211_42);
    } else {
      ca_.Goto(&block214, phi_bb211_17, phi_bb211_18, phi_bb211_19, phi_bb211_23, phi_bb211_24, phi_bb211_25, phi_bb211_28, phi_bb211_29, phi_bb211_30, phi_bb211_31, phi_bb211_34, phi_bb211_35, phi_bb211_36, phi_bb211_37, phi_bb211_38, phi_bb211_41, phi_bb211_42);
    }
  }

  TNode<JSAny> phi_bb213_17;
  TNode<IntPtrT> phi_bb213_18;
  TNode<BoolT> phi_bb213_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb213_23;
  TNode<IntPtrT> phi_bb213_24;
  TNode<IntPtrT> phi_bb213_25;
  TNode<IntPtrT> phi_bb213_28;
  TNode<IntPtrT> phi_bb213_29;
  TNode<IntPtrT> phi_bb213_30;
  TNode<IntPtrT> phi_bb213_31;
  TNode<IntPtrT> phi_bb213_34;
  TNode<BoolT> phi_bb213_35;
  TNode<BoolT> phi_bb213_36;
  TNode<Union<FixedArray, Smi>> phi_bb213_37;
  TNode<IntPtrT> phi_bb213_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb213_41;
  TNode<IntPtrT> phi_bb213_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp385;
  TNode<IntPtrT> tmp386;
  TNode<IntPtrT> tmp387;
  TNode<IntPtrT> tmp388;
  if (block213.is_used()) {
    ca_.Bind(&block213, &phi_bb213_17, &phi_bb213_18, &phi_bb213_19, &phi_bb213_23, &phi_bb213_24, &phi_bb213_25, &phi_bb213_28, &phi_bb213_29, &phi_bb213_30, &phi_bb213_31, &phi_bb213_34, &phi_bb213_35, &phi_bb213_36, &phi_bb213_37, &phi_bb213_38, &phi_bb213_41, &phi_bb213_42);
    std::tie(tmp385, tmp386) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb213_31}).Flatten();
    tmp387 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp388 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb213_31}, TNode<IntPtrT>{tmp387});
    ca_.Goto(&block212, phi_bb213_17, phi_bb213_18, phi_bb213_19, phi_bb213_23, phi_bb213_24, phi_bb213_25, phi_bb213_28, phi_bb213_29, phi_bb213_30, tmp388, phi_bb213_34, phi_bb213_35, phi_bb213_36, phi_bb213_37, phi_bb213_38, phi_bb213_41, phi_bb213_42, tmp385, tmp386);
  }

  TNode<JSAny> phi_bb214_17;
  TNode<IntPtrT> phi_bb214_18;
  TNode<BoolT> phi_bb214_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb214_23;
  TNode<IntPtrT> phi_bb214_24;
  TNode<IntPtrT> phi_bb214_25;
  TNode<IntPtrT> phi_bb214_28;
  TNode<IntPtrT> phi_bb214_29;
  TNode<IntPtrT> phi_bb214_30;
  TNode<IntPtrT> phi_bb214_31;
  TNode<IntPtrT> phi_bb214_34;
  TNode<BoolT> phi_bb214_35;
  TNode<BoolT> phi_bb214_36;
  TNode<Union<FixedArray, Smi>> phi_bb214_37;
  TNode<IntPtrT> phi_bb214_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb214_41;
  TNode<IntPtrT> phi_bb214_42;
  TNode<IntPtrT> tmp389;
  TNode<BoolT> tmp390;
  if (block214.is_used()) {
    ca_.Bind(&block214, &phi_bb214_17, &phi_bb214_18, &phi_bb214_19, &phi_bb214_23, &phi_bb214_24, &phi_bb214_25, &phi_bb214_28, &phi_bb214_29, &phi_bb214_30, &phi_bb214_31, &phi_bb214_34, &phi_bb214_35, &phi_bb214_36, &phi_bb214_37, &phi_bb214_38, &phi_bb214_41, &phi_bb214_42);
    tmp389 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp390 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb214_34}, TNode<IntPtrT>{tmp389});
    ca_.Branch(tmp390, &block216, std::vector<compiler::Node*>{phi_bb214_17, phi_bb214_18, phi_bb214_19, phi_bb214_23, phi_bb214_24, phi_bb214_25, phi_bb214_28, phi_bb214_29, phi_bb214_30, phi_bb214_31, phi_bb214_34, phi_bb214_35, phi_bb214_36, phi_bb214_37, phi_bb214_38, phi_bb214_41, phi_bb214_42}, &block217, std::vector<compiler::Node*>{phi_bb214_17, phi_bb214_18, phi_bb214_19, phi_bb214_23, phi_bb214_24, phi_bb214_25, phi_bb214_28, phi_bb214_29, phi_bb214_30, phi_bb214_31, phi_bb214_34, phi_bb214_35, phi_bb214_36, phi_bb214_37, phi_bb214_38, phi_bb214_41, phi_bb214_42});
  }

  TNode<JSAny> phi_bb216_17;
  TNode<IntPtrT> phi_bb216_18;
  TNode<BoolT> phi_bb216_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb216_23;
  TNode<IntPtrT> phi_bb216_24;
  TNode<IntPtrT> phi_bb216_25;
  TNode<IntPtrT> phi_bb216_28;
  TNode<IntPtrT> phi_bb216_29;
  TNode<IntPtrT> phi_bb216_30;
  TNode<IntPtrT> phi_bb216_31;
  TNode<IntPtrT> phi_bb216_34;
  TNode<BoolT> phi_bb216_35;
  TNode<BoolT> phi_bb216_36;
  TNode<Union<FixedArray, Smi>> phi_bb216_37;
  TNode<IntPtrT> phi_bb216_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb216_41;
  TNode<IntPtrT> phi_bb216_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp391;
  TNode<IntPtrT> tmp392;
  TNode<IntPtrT> tmp393;
  TNode<BoolT> tmp394;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_17, &phi_bb216_18, &phi_bb216_19, &phi_bb216_23, &phi_bb216_24, &phi_bb216_25, &phi_bb216_28, &phi_bb216_29, &phi_bb216_30, &phi_bb216_31, &phi_bb216_34, &phi_bb216_35, &phi_bb216_36, &phi_bb216_37, &phi_bb216_38, &phi_bb216_41, &phi_bb216_42);
    std::tie(tmp391, tmp392) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb216_34}).Flatten();
    tmp393 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp394 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block212, phi_bb216_17, phi_bb216_18, phi_bb216_19, phi_bb216_23, phi_bb216_24, phi_bb216_25, phi_bb216_28, phi_bb216_29, phi_bb216_30, phi_bb216_31, tmp393, tmp394, phi_bb216_36, phi_bb216_37, phi_bb216_38, phi_bb216_41, phi_bb216_42, tmp391, tmp392);
  }

  TNode<JSAny> phi_bb217_17;
  TNode<IntPtrT> phi_bb217_18;
  TNode<BoolT> phi_bb217_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb217_23;
  TNode<IntPtrT> phi_bb217_24;
  TNode<IntPtrT> phi_bb217_25;
  TNode<IntPtrT> phi_bb217_28;
  TNode<IntPtrT> phi_bb217_29;
  TNode<IntPtrT> phi_bb217_30;
  TNode<IntPtrT> phi_bb217_31;
  TNode<IntPtrT> phi_bb217_34;
  TNode<BoolT> phi_bb217_35;
  TNode<BoolT> phi_bb217_36;
  TNode<Union<FixedArray, Smi>> phi_bb217_37;
  TNode<IntPtrT> phi_bb217_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb217_41;
  TNode<IntPtrT> phi_bb217_42;
  TNode<Union<HeapObject, TaggedIndex>> tmp395;
  TNode<IntPtrT> tmp396;
  TNode<IntPtrT> tmp397;
  TNode<IntPtrT> tmp398;
  TNode<IntPtrT> tmp399;
  TNode<IntPtrT> tmp400;
  TNode<BoolT> tmp401;
  if (block217.is_used()) {
    ca_.Bind(&block217, &phi_bb217_17, &phi_bb217_18, &phi_bb217_19, &phi_bb217_23, &phi_bb217_24, &phi_bb217_25, &phi_bb217_28, &phi_bb217_29, &phi_bb217_30, &phi_bb217_31, &phi_bb217_34, &phi_bb217_35, &phi_bb217_36, &phi_bb217_37, &phi_bb217_38, &phi_bb217_41, &phi_bb217_42);
    std::tie(tmp395, tmp396) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb217_31}).Flatten();
    tmp397 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp398 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb217_31}, TNode<IntPtrT>{tmp397});
    tmp399 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp400 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp398}, TNode<IntPtrT>{tmp399});
    tmp401 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block212, phi_bb217_17, phi_bb217_18, phi_bb217_19, phi_bb217_23, phi_bb217_24, phi_bb217_25, phi_bb217_28, phi_bb217_29, phi_bb217_30, tmp400, tmp398, tmp401, phi_bb217_36, phi_bb217_37, phi_bb217_38, phi_bb217_41, phi_bb217_42, tmp395, tmp396);
  }

  TNode<JSAny> phi_bb212_17;
  TNode<IntPtrT> phi_bb212_18;
  TNode<BoolT> phi_bb212_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb212_23;
  TNode<IntPtrT> phi_bb212_24;
  TNode<IntPtrT> phi_bb212_25;
  TNode<IntPtrT> phi_bb212_28;
  TNode<IntPtrT> phi_bb212_29;
  TNode<IntPtrT> phi_bb212_30;
  TNode<IntPtrT> phi_bb212_31;
  TNode<IntPtrT> phi_bb212_34;
  TNode<BoolT> phi_bb212_35;
  TNode<BoolT> phi_bb212_36;
  TNode<Union<FixedArray, Smi>> phi_bb212_37;
  TNode<IntPtrT> phi_bb212_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb212_41;
  TNode<IntPtrT> phi_bb212_42;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb212_43;
  TNode<IntPtrT> phi_bb212_44;
  if (block212.is_used()) {
    ca_.Bind(&block212, &phi_bb212_17, &phi_bb212_18, &phi_bb212_19, &phi_bb212_23, &phi_bb212_24, &phi_bb212_25, &phi_bb212_28, &phi_bb212_29, &phi_bb212_30, &phi_bb212_31, &phi_bb212_34, &phi_bb212_35, &phi_bb212_36, &phi_bb212_37, &phi_bb212_38, &phi_bb212_41, &phi_bb212_42, &phi_bb212_43, &phi_bb212_44);
    ca_.Goto(&block209, phi_bb212_17, phi_bb212_18, phi_bb212_19, phi_bb212_23, phi_bb212_24, phi_bb212_25, phi_bb212_28, phi_bb212_29, phi_bb212_30, phi_bb212_31, phi_bb212_34, phi_bb212_35, phi_bb212_36, phi_bb212_37, phi_bb212_38, phi_bb212_41, phi_bb212_42, phi_bb212_43, phi_bb212_44);
  }

  TNode<JSAny> phi_bb209_17;
  TNode<IntPtrT> phi_bb209_18;
  TNode<BoolT> phi_bb209_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb209_23;
  TNode<IntPtrT> phi_bb209_24;
  TNode<IntPtrT> phi_bb209_25;
  TNode<IntPtrT> phi_bb209_28;
  TNode<IntPtrT> phi_bb209_29;
  TNode<IntPtrT> phi_bb209_30;
  TNode<IntPtrT> phi_bb209_31;
  TNode<IntPtrT> phi_bb209_34;
  TNode<BoolT> phi_bb209_35;
  TNode<BoolT> phi_bb209_36;
  TNode<Union<FixedArray, Smi>> phi_bb209_37;
  TNode<IntPtrT> phi_bb209_38;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb209_41;
  TNode<IntPtrT> phi_bb209_42;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb209_43;
  TNode<IntPtrT> phi_bb209_44;
  TNode<BigInt> tmp402;
  TNode<UintPtrT> tmp403;
  TNode<UintPtrT> tmp404;
  TNode<IntPtrT> tmp405;
  TNode<IntPtrT> tmp406;
  if (block209.is_used()) {
    ca_.Bind(&block209, &phi_bb209_17, &phi_bb209_18, &phi_bb209_19, &phi_bb209_23, &phi_bb209_24, &phi_bb209_25, &phi_bb209_28, &phi_bb209_29, &phi_bb209_30, &phi_bb209_31, &phi_bb209_34, &phi_bb209_35, &phi_bb209_36, &phi_bb209_37, &phi_bb209_38, &phi_bb209_41, &phi_bb209_42, &phi_bb209_43, &phi_bb209_44);
    tmp402 = CodeStubAssembler(state_).ToBigInt(TNode<Context>{p_context}, TNode<JSAny>{tmp207});
    std::tie(tmp403, tmp404) = CodeStubAssembler(state_).BigIntToRawBytes(TNode<BigInt>{tmp402}).Flatten();
    tmp405 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp403});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb209_41, phi_bb209_42}, tmp405);
    tmp406 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp404});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb209_43, phi_bb209_44}, tmp406);
    ca_.Goto(&block190, phi_bb209_17, phi_bb209_18, phi_bb209_19, phi_bb209_23, phi_bb209_24, phi_bb209_25, tmp378, phi_bb209_28, phi_bb209_29, phi_bb209_30, phi_bb209_31, phi_bb209_34, phi_bb209_35, phi_bb209_36, phi_bb209_37, phi_bb209_38);
  }

  TNode<JSAny> phi_bb190_17;
  TNode<IntPtrT> phi_bb190_18;
  TNode<BoolT> phi_bb190_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb190_23;
  TNode<IntPtrT> phi_bb190_24;
  TNode<IntPtrT> phi_bb190_25;
  TNode<IntPtrT> phi_bb190_27;
  TNode<IntPtrT> phi_bb190_28;
  TNode<IntPtrT> phi_bb190_29;
  TNode<IntPtrT> phi_bb190_30;
  TNode<IntPtrT> phi_bb190_31;
  TNode<IntPtrT> phi_bb190_34;
  TNode<BoolT> phi_bb190_35;
  TNode<BoolT> phi_bb190_36;
  TNode<Union<FixedArray, Smi>> phi_bb190_37;
  TNode<IntPtrT> phi_bb190_38;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_17, &phi_bb190_18, &phi_bb190_19, &phi_bb190_23, &phi_bb190_24, &phi_bb190_25, &phi_bb190_27, &phi_bb190_28, &phi_bb190_29, &phi_bb190_30, &phi_bb190_31, &phi_bb190_34, &phi_bb190_35, &phi_bb190_36, &phi_bb190_37, &phi_bb190_38);
    ca_.Goto(&block187, phi_bb190_17, phi_bb190_18, phi_bb190_19, phi_bb190_23, phi_bb190_24, phi_bb190_25, phi_bb190_27, phi_bb190_28, phi_bb190_29, phi_bb190_30, phi_bb190_31, phi_bb190_34, phi_bb190_35, phi_bb190_36, phi_bb190_37, phi_bb190_38);
  }

  TNode<JSAny> phi_bb186_17;
  TNode<IntPtrT> phi_bb186_18;
  TNode<BoolT> phi_bb186_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb186_23;
  TNode<IntPtrT> phi_bb186_24;
  TNode<IntPtrT> phi_bb186_25;
  TNode<IntPtrT> phi_bb186_27;
  TNode<IntPtrT> phi_bb186_28;
  TNode<IntPtrT> phi_bb186_29;
  TNode<IntPtrT> phi_bb186_30;
  TNode<IntPtrT> phi_bb186_31;
  TNode<IntPtrT> phi_bb186_34;
  TNode<BoolT> phi_bb186_35;
  TNode<BoolT> phi_bb186_36;
  TNode<Union<FixedArray, Smi>> phi_bb186_37;
  TNode<IntPtrT> phi_bb186_38;
  TNode<Uint32T> tmp407;
  TNode<Uint32T> tmp408;
  TNode<Uint32T> tmp409;
  TNode<BoolT> tmp410;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_17, &phi_bb186_18, &phi_bb186_19, &phi_bb186_23, &phi_bb186_24, &phi_bb186_25, &phi_bb186_27, &phi_bb186_28, &phi_bb186_29, &phi_bb186_30, &phi_bb186_31, &phi_bb186_34, &phi_bb186_35, &phi_bb186_36, &phi_bb186_37, &phi_bb186_38);
    tmp407 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp408 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp212}, TNode<Uint32T>{tmp407});
    tmp409 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp410 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp408}, TNode<Uint32T>{tmp409});
    ca_.Branch(tmp410, &block218, std::vector<compiler::Node*>{phi_bb186_17, phi_bb186_18, phi_bb186_19, phi_bb186_23, phi_bb186_24, phi_bb186_25, phi_bb186_27, phi_bb186_28, phi_bb186_29, phi_bb186_30, phi_bb186_31, phi_bb186_34, phi_bb186_35, phi_bb186_36, phi_bb186_37, phi_bb186_38}, &block219, std::vector<compiler::Node*>{phi_bb186_17, phi_bb186_18, phi_bb186_19, phi_bb186_23, phi_bb186_24, phi_bb186_25, phi_bb186_27, phi_bb186_28, phi_bb186_29, phi_bb186_30, phi_bb186_31, phi_bb186_34, phi_bb186_35, phi_bb186_36, phi_bb186_37, phi_bb186_38});
  }

  TNode<JSAny> phi_bb219_17;
  TNode<IntPtrT> phi_bb219_18;
  TNode<BoolT> phi_bb219_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb219_23;
  TNode<IntPtrT> phi_bb219_24;
  TNode<IntPtrT> phi_bb219_25;
  TNode<IntPtrT> phi_bb219_27;
  TNode<IntPtrT> phi_bb219_28;
  TNode<IntPtrT> phi_bb219_29;
  TNode<IntPtrT> phi_bb219_30;
  TNode<IntPtrT> phi_bb219_31;
  TNode<IntPtrT> phi_bb219_34;
  TNode<BoolT> phi_bb219_35;
  TNode<BoolT> phi_bb219_36;
  TNode<Union<FixedArray, Smi>> phi_bb219_37;
  TNode<IntPtrT> phi_bb219_38;
  if (block219.is_used()) {
    ca_.Bind(&block219, &phi_bb219_17, &phi_bb219_18, &phi_bb219_19, &phi_bb219_23, &phi_bb219_24, &phi_bb219_25, &phi_bb219_27, &phi_bb219_28, &phi_bb219_29, &phi_bb219_30, &phi_bb219_31, &phi_bb219_34, &phi_bb219_35, &phi_bb219_36, &phi_bb219_37, &phi_bb219_38);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 740});
      CodeStubAssembler(state_).FailAssert("Torque assert '(paramType & kValueTypeIsRefBit) != 0' failed", pos_stack);
    }
  }

  TNode<JSAny> phi_bb218_17;
  TNode<IntPtrT> phi_bb218_18;
  TNode<BoolT> phi_bb218_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb218_23;
  TNode<IntPtrT> phi_bb218_24;
  TNode<IntPtrT> phi_bb218_25;
  TNode<IntPtrT> phi_bb218_27;
  TNode<IntPtrT> phi_bb218_28;
  TNode<IntPtrT> phi_bb218_29;
  TNode<IntPtrT> phi_bb218_30;
  TNode<IntPtrT> phi_bb218_31;
  TNode<IntPtrT> phi_bb218_34;
  TNode<BoolT> phi_bb218_35;
  TNode<BoolT> phi_bb218_36;
  TNode<Union<FixedArray, Smi>> phi_bb218_37;
  TNode<IntPtrT> phi_bb218_38;
  TNode<BoolT> tmp411;
  TNode<BoolT> tmp412;
  if (block218.is_used()) {
    ca_.Bind(&block218, &phi_bb218_17, &phi_bb218_18, &phi_bb218_19, &phi_bb218_23, &phi_bb218_24, &phi_bb218_25, &phi_bb218_27, &phi_bb218_28, &phi_bb218_29, &phi_bb218_30, &phi_bb218_31, &phi_bb218_34, &phi_bb218_35, &phi_bb218_36, &phi_bb218_37, &phi_bb218_38);
    tmp411 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp412 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{phi_bb218_37});
    ca_.Branch(tmp412, &block220, std::vector<compiler::Node*>{phi_bb218_17, phi_bb218_18, phi_bb218_19, phi_bb218_23, phi_bb218_24, phi_bb218_25, phi_bb218_27, phi_bb218_28, phi_bb218_29, phi_bb218_30, phi_bb218_31, phi_bb218_34, phi_bb218_35, phi_bb218_37, phi_bb218_38}, &block221, std::vector<compiler::Node*>{phi_bb218_17, phi_bb218_18, phi_bb218_19, phi_bb218_23, phi_bb218_24, phi_bb218_25, phi_bb218_27, phi_bb218_28, phi_bb218_29, phi_bb218_30, phi_bb218_31, phi_bb218_34, phi_bb218_35, phi_bb218_37, phi_bb218_38});
  }

  TNode<JSAny> phi_bb220_17;
  TNode<IntPtrT> phi_bb220_18;
  TNode<BoolT> phi_bb220_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb220_23;
  TNode<IntPtrT> phi_bb220_24;
  TNode<IntPtrT> phi_bb220_25;
  TNode<IntPtrT> phi_bb220_27;
  TNode<IntPtrT> phi_bb220_28;
  TNode<IntPtrT> phi_bb220_29;
  TNode<IntPtrT> phi_bb220_30;
  TNode<IntPtrT> phi_bb220_31;
  TNode<IntPtrT> phi_bb220_34;
  TNode<BoolT> phi_bb220_35;
  TNode<Union<FixedArray, Smi>> phi_bb220_37;
  TNode<IntPtrT> phi_bb220_38;
  TNode<FixedArray> tmp413;
  if (block220.is_used()) {
    ca_.Bind(&block220, &phi_bb220_17, &phi_bb220_18, &phi_bb220_19, &phi_bb220_23, &phi_bb220_24, &phi_bb220_25, &phi_bb220_27, &phi_bb220_28, &phi_bb220_29, &phi_bb220_30, &phi_bb220_31, &phi_bb220_34, &phi_bb220_35, &phi_bb220_37, &phi_bb220_38);
    tmp413 = ca_.CallBuiltin<FixedArray>(Builtin::kWasmAllocateZeroedFixedArray, TNode<Object>(), tmp24);
    ca_.Goto(&block221, phi_bb220_17, phi_bb220_18, phi_bb220_19, phi_bb220_23, phi_bb220_24, phi_bb220_25, phi_bb220_27, phi_bb220_28, phi_bb220_29, phi_bb220_30, phi_bb220_31, phi_bb220_34, phi_bb220_35, tmp413, phi_bb220_38);
  }

  TNode<JSAny> phi_bb221_17;
  TNode<IntPtrT> phi_bb221_18;
  TNode<BoolT> phi_bb221_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb221_23;
  TNode<IntPtrT> phi_bb221_24;
  TNode<IntPtrT> phi_bb221_25;
  TNode<IntPtrT> phi_bb221_27;
  TNode<IntPtrT> phi_bb221_28;
  TNode<IntPtrT> phi_bb221_29;
  TNode<IntPtrT> phi_bb221_30;
  TNode<IntPtrT> phi_bb221_31;
  TNode<IntPtrT> phi_bb221_34;
  TNode<BoolT> phi_bb221_35;
  TNode<Union<FixedArray, Smi>> phi_bb221_37;
  TNode<IntPtrT> phi_bb221_38;
  TNode<FixedArray> tmp414;
  TNode<Union<HeapObject, TaggedIndex>> tmp415;
  TNode<IntPtrT> tmp416;
  TNode<IntPtrT> tmp417;
  TNode<UintPtrT> tmp418;
  TNode<UintPtrT> tmp419;
  TNode<BoolT> tmp420;
  if (block221.is_used()) {
    ca_.Bind(&block221, &phi_bb221_17, &phi_bb221_18, &phi_bb221_19, &phi_bb221_23, &phi_bb221_24, &phi_bb221_25, &phi_bb221_27, &phi_bb221_28, &phi_bb221_29, &phi_bb221_30, &phi_bb221_31, &phi_bb221_34, &phi_bb221_35, &phi_bb221_37, &phi_bb221_38);
    tmp414 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{phi_bb221_37});
    std::tie(tmp415, tmp416, tmp417) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp414}).Flatten();
    tmp418 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb221_38});
    tmp419 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp417});
    tmp420 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp418}, TNode<UintPtrT>{tmp419});
    ca_.Branch(tmp420, &block226, std::vector<compiler::Node*>{phi_bb221_17, phi_bb221_18, phi_bb221_19, phi_bb221_23, phi_bb221_24, phi_bb221_25, phi_bb221_27, phi_bb221_28, phi_bb221_29, phi_bb221_30, phi_bb221_31, phi_bb221_34, phi_bb221_35, phi_bb221_38, phi_bb221_38, phi_bb221_38, phi_bb221_38, phi_bb221_38}, &block227, std::vector<compiler::Node*>{phi_bb221_17, phi_bb221_18, phi_bb221_19, phi_bb221_23, phi_bb221_24, phi_bb221_25, phi_bb221_27, phi_bb221_28, phi_bb221_29, phi_bb221_30, phi_bb221_31, phi_bb221_34, phi_bb221_35, phi_bb221_38, phi_bb221_38, phi_bb221_38, phi_bb221_38, phi_bb221_38});
  }

  TNode<JSAny> phi_bb226_17;
  TNode<IntPtrT> phi_bb226_18;
  TNode<BoolT> phi_bb226_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb226_23;
  TNode<IntPtrT> phi_bb226_24;
  TNode<IntPtrT> phi_bb226_25;
  TNode<IntPtrT> phi_bb226_27;
  TNode<IntPtrT> phi_bb226_28;
  TNode<IntPtrT> phi_bb226_29;
  TNode<IntPtrT> phi_bb226_30;
  TNode<IntPtrT> phi_bb226_31;
  TNode<IntPtrT> phi_bb226_34;
  TNode<BoolT> phi_bb226_35;
  TNode<IntPtrT> phi_bb226_38;
  TNode<IntPtrT> phi_bb226_46;
  TNode<IntPtrT> phi_bb226_47;
  TNode<IntPtrT> phi_bb226_51;
  TNode<IntPtrT> phi_bb226_52;
  TNode<IntPtrT> tmp421;
  TNode<IntPtrT> tmp422;
  TNode<Union<HeapObject, TaggedIndex>> tmp423;
  TNode<IntPtrT> tmp424;
  TNode<Object> tmp425;
  if (block226.is_used()) {
    ca_.Bind(&block226, &phi_bb226_17, &phi_bb226_18, &phi_bb226_19, &phi_bb226_23, &phi_bb226_24, &phi_bb226_25, &phi_bb226_27, &phi_bb226_28, &phi_bb226_29, &phi_bb226_30, &phi_bb226_31, &phi_bb226_34, &phi_bb226_35, &phi_bb226_38, &phi_bb226_46, &phi_bb226_47, &phi_bb226_51, &phi_bb226_52);
    tmp421 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb226_52});
    tmp422 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp416}, TNode<IntPtrT>{tmp421});
    std::tie(tmp423, tmp424) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp415}, TNode<IntPtrT>{tmp422}).Flatten();
    tmp425 = JSToWasmObject_0(state_, TNode<NativeContext>{p_context}, TNode<Uint32T>{tmp212}, TNode<JSAny>{tmp207});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp423, tmp424}, tmp425);
    ca_.Goto(&block187, phi_bb226_17, phi_bb226_18, phi_bb226_19, phi_bb226_23, phi_bb226_24, phi_bb226_25, phi_bb226_27, phi_bb226_28, phi_bb226_29, phi_bb226_30, phi_bb226_31, phi_bb226_34, phi_bb226_35, tmp411, phi_bb221_37, phi_bb226_38);
  }

  TNode<JSAny> phi_bb227_17;
  TNode<IntPtrT> phi_bb227_18;
  TNode<BoolT> phi_bb227_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb227_23;
  TNode<IntPtrT> phi_bb227_24;
  TNode<IntPtrT> phi_bb227_25;
  TNode<IntPtrT> phi_bb227_27;
  TNode<IntPtrT> phi_bb227_28;
  TNode<IntPtrT> phi_bb227_29;
  TNode<IntPtrT> phi_bb227_30;
  TNode<IntPtrT> phi_bb227_31;
  TNode<IntPtrT> phi_bb227_34;
  TNode<BoolT> phi_bb227_35;
  TNode<IntPtrT> phi_bb227_38;
  TNode<IntPtrT> phi_bb227_46;
  TNode<IntPtrT> phi_bb227_47;
  TNode<IntPtrT> phi_bb227_51;
  TNode<IntPtrT> phi_bb227_52;
  if (block227.is_used()) {
    ca_.Bind(&block227, &phi_bb227_17, &phi_bb227_18, &phi_bb227_19, &phi_bb227_23, &phi_bb227_24, &phi_bb227_25, &phi_bb227_27, &phi_bb227_28, &phi_bb227_29, &phi_bb227_30, &phi_bb227_31, &phi_bb227_34, &phi_bb227_35, &phi_bb227_38, &phi_bb227_46, &phi_bb227_47, &phi_bb227_51, &phi_bb227_52);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb187_17;
  TNode<IntPtrT> phi_bb187_18;
  TNode<BoolT> phi_bb187_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb187_23;
  TNode<IntPtrT> phi_bb187_24;
  TNode<IntPtrT> phi_bb187_25;
  TNode<IntPtrT> phi_bb187_27;
  TNode<IntPtrT> phi_bb187_28;
  TNode<IntPtrT> phi_bb187_29;
  TNode<IntPtrT> phi_bb187_30;
  TNode<IntPtrT> phi_bb187_31;
  TNode<IntPtrT> phi_bb187_34;
  TNode<BoolT> phi_bb187_35;
  TNode<BoolT> phi_bb187_36;
  TNode<Union<FixedArray, Smi>> phi_bb187_37;
  TNode<IntPtrT> phi_bb187_38;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_17, &phi_bb187_18, &phi_bb187_19, &phi_bb187_23, &phi_bb187_24, &phi_bb187_25, &phi_bb187_27, &phi_bb187_28, &phi_bb187_29, &phi_bb187_30, &phi_bb187_31, &phi_bb187_34, &phi_bb187_35, &phi_bb187_36, &phi_bb187_37, &phi_bb187_38);
    ca_.Goto(&block170, phi_bb187_17, phi_bb187_18, phi_bb187_19, phi_bb187_23, phi_bb187_24, phi_bb187_25, phi_bb187_27, phi_bb187_28, phi_bb187_29, phi_bb187_30, phi_bb187_31, phi_bb187_34, phi_bb187_35, phi_bb187_36, phi_bb187_37, phi_bb187_38);
  }

  TNode<JSAny> phi_bb170_17;
  TNode<IntPtrT> phi_bb170_18;
  TNode<BoolT> phi_bb170_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb170_23;
  TNode<IntPtrT> phi_bb170_24;
  TNode<IntPtrT> phi_bb170_25;
  TNode<IntPtrT> phi_bb170_27;
  TNode<IntPtrT> phi_bb170_28;
  TNode<IntPtrT> phi_bb170_29;
  TNode<IntPtrT> phi_bb170_30;
  TNode<IntPtrT> phi_bb170_31;
  TNode<IntPtrT> phi_bb170_34;
  TNode<BoolT> phi_bb170_35;
  TNode<BoolT> phi_bb170_36;
  TNode<Union<FixedArray, Smi>> phi_bb170_37;
  TNode<IntPtrT> phi_bb170_38;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_17, &phi_bb170_18, &phi_bb170_19, &phi_bb170_23, &phi_bb170_24, &phi_bb170_25, &phi_bb170_27, &phi_bb170_28, &phi_bb170_29, &phi_bb170_30, &phi_bb170_31, &phi_bb170_34, &phi_bb170_35, &phi_bb170_36, &phi_bb170_37, &phi_bb170_38);
    ca_.Goto(&block153, phi_bb170_17, phi_bb170_18, phi_bb170_19, phi_bb170_23, phi_bb170_24, phi_bb170_25, phi_bb170_27, phi_bb170_28, phi_bb170_29, phi_bb170_30, phi_bb170_31, phi_bb170_34, phi_bb170_35, phi_bb170_36, phi_bb170_37, phi_bb170_38);
  }

  TNode<JSAny> phi_bb153_17;
  TNode<IntPtrT> phi_bb153_18;
  TNode<BoolT> phi_bb153_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb153_23;
  TNode<IntPtrT> phi_bb153_24;
  TNode<IntPtrT> phi_bb153_25;
  TNode<IntPtrT> phi_bb153_27;
  TNode<IntPtrT> phi_bb153_28;
  TNode<IntPtrT> phi_bb153_29;
  TNode<IntPtrT> phi_bb153_30;
  TNode<IntPtrT> phi_bb153_31;
  TNode<IntPtrT> phi_bb153_34;
  TNode<BoolT> phi_bb153_35;
  TNode<BoolT> phi_bb153_36;
  TNode<Union<FixedArray, Smi>> phi_bb153_37;
  TNode<IntPtrT> phi_bb153_38;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_17, &phi_bb153_18, &phi_bb153_19, &phi_bb153_23, &phi_bb153_24, &phi_bb153_25, &phi_bb153_27, &phi_bb153_28, &phi_bb153_29, &phi_bb153_30, &phi_bb153_31, &phi_bb153_34, &phi_bb153_35, &phi_bb153_36, &phi_bb153_37, &phi_bb153_38);
    ca_.Goto(&block137, phi_bb153_17, phi_bb153_18, phi_bb153_19, phi_bb153_23, phi_bb153_24, phi_bb153_25, phi_bb153_27, phi_bb153_28, phi_bb153_29, phi_bb153_30, phi_bb153_31, phi_bb153_34, phi_bb153_35, phi_bb153_36, phi_bb153_37, phi_bb153_38);
  }

  TNode<JSAny> phi_bb137_17;
  TNode<IntPtrT> phi_bb137_18;
  TNode<BoolT> phi_bb137_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb137_23;
  TNode<IntPtrT> phi_bb137_24;
  TNode<IntPtrT> phi_bb137_25;
  TNode<IntPtrT> phi_bb137_27;
  TNode<IntPtrT> phi_bb137_28;
  TNode<IntPtrT> phi_bb137_29;
  TNode<IntPtrT> phi_bb137_30;
  TNode<IntPtrT> phi_bb137_31;
  TNode<IntPtrT> phi_bb137_34;
  TNode<BoolT> phi_bb137_35;
  TNode<BoolT> phi_bb137_36;
  TNode<Union<FixedArray, Smi>> phi_bb137_37;
  TNode<IntPtrT> phi_bb137_38;
  TNode<IntPtrT> tmp426;
  TNode<IntPtrT> tmp427;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_17, &phi_bb137_18, &phi_bb137_19, &phi_bb137_23, &phi_bb137_24, &phi_bb137_25, &phi_bb137_27, &phi_bb137_28, &phi_bb137_29, &phi_bb137_30, &phi_bb137_31, &phi_bb137_34, &phi_bb137_35, &phi_bb137_36, &phi_bb137_37, &phi_bb137_38);
    tmp426 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp427 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb137_38}, TNode<IntPtrT>{tmp426});
    ca_.Goto(&block132, phi_bb137_17, phi_bb137_18, phi_bb137_19, phi_bb137_23, phi_bb137_24, phi_bb137_25, phi_bb137_27, phi_bb137_28, phi_bb137_29, phi_bb137_30, phi_bb137_31, phi_bb137_34, phi_bb137_35, phi_bb137_36, phi_bb137_37, tmp427);
  }

  TNode<JSAny> phi_bb131_17;
  TNode<IntPtrT> phi_bb131_18;
  TNode<BoolT> phi_bb131_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb131_23;
  TNode<IntPtrT> phi_bb131_24;
  TNode<IntPtrT> phi_bb131_25;
  TNode<IntPtrT> phi_bb131_27;
  TNode<IntPtrT> phi_bb131_28;
  TNode<IntPtrT> phi_bb131_29;
  TNode<IntPtrT> phi_bb131_30;
  TNode<IntPtrT> phi_bb131_31;
  TNode<IntPtrT> phi_bb131_34;
  TNode<BoolT> phi_bb131_35;
  TNode<BoolT> phi_bb131_36;
  TNode<Union<FixedArray, Smi>> phi_bb131_37;
  TNode<IntPtrT> phi_bb131_38;
  TNode<Undefined> tmp428;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_17, &phi_bb131_18, &phi_bb131_19, &phi_bb131_23, &phi_bb131_24, &phi_bb131_25, &phi_bb131_27, &phi_bb131_28, &phi_bb131_29, &phi_bb131_30, &phi_bb131_31, &phi_bb131_34, &phi_bb131_35, &phi_bb131_36, &phi_bb131_37, &phi_bb131_38);
    tmp428 = Undefined_0(state_);
    if ((((CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kPromise))) || (CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kStressSwitch)))))) {
      ca_.Goto(&block230, phi_bb131_17, phi_bb131_18, phi_bb131_19, phi_bb131_23, phi_bb131_24, phi_bb131_25, phi_bb131_27, phi_bb131_28, phi_bb131_29, phi_bb131_30, phi_bb131_31, phi_bb131_34, phi_bb131_35, phi_bb131_36, phi_bb131_37);
    } else {
      ca_.Goto(&block231, phi_bb131_17, phi_bb131_18, phi_bb131_19, phi_bb131_23, phi_bb131_24, phi_bb131_25, phi_bb131_27, phi_bb131_28, phi_bb131_29, phi_bb131_30, phi_bb131_31, phi_bb131_34, phi_bb131_35, phi_bb131_36, phi_bb131_37);
    }
  }

  TNode<JSAny> phi_bb230_17;
  TNode<IntPtrT> phi_bb230_18;
  TNode<BoolT> phi_bb230_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb230_23;
  TNode<IntPtrT> phi_bb230_24;
  TNode<IntPtrT> phi_bb230_25;
  TNode<IntPtrT> phi_bb230_27;
  TNode<IntPtrT> phi_bb230_28;
  TNode<IntPtrT> phi_bb230_29;
  TNode<IntPtrT> phi_bb230_30;
  TNode<IntPtrT> phi_bb230_31;
  TNode<IntPtrT> phi_bb230_34;
  TNode<BoolT> phi_bb230_35;
  TNode<BoolT> phi_bb230_36;
  TNode<Union<FixedArray, Smi>> phi_bb230_37;
  TNode<JSAny> tmp429;
  TNode<BoolT> tmp430;
  if (block230.is_used()) {
    ca_.Bind(&block230, &phi_bb230_17, &phi_bb230_18, &phi_bb230_19, &phi_bb230_23, &phi_bb230_24, &phi_bb230_25, &phi_bb230_27, &phi_bb230_28, &phi_bb230_29, &phi_bb230_30, &phi_bb230_31, &phi_bb230_34, &phi_bb230_35, &phi_bb230_36, &phi_bb230_37);
    tmp429 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kWasmAllocateSuspender, p_context)); 
    tmp430 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kStressSwitch))));
    ca_.Branch(tmp430, &block233, std::vector<compiler::Node*>{phi_bb230_17, phi_bb230_18, phi_bb230_19, phi_bb230_23, phi_bb230_24, phi_bb230_25, phi_bb230_27, phi_bb230_28, phi_bb230_29, phi_bb230_30, phi_bb230_31, phi_bb230_34, phi_bb230_35, phi_bb230_36, phi_bb230_37}, &block234, std::vector<compiler::Node*>{phi_bb230_17, phi_bb230_18, phi_bb230_19, phi_bb230_23, phi_bb230_24, phi_bb230_25, phi_bb230_27, phi_bb230_28, phi_bb230_29, phi_bb230_30, phi_bb230_31, phi_bb230_34, phi_bb230_35, phi_bb230_36, phi_bb230_37});
  }

  TNode<JSAny> phi_bb233_17;
  TNode<IntPtrT> phi_bb233_18;
  TNode<BoolT> phi_bb233_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb233_23;
  TNode<IntPtrT> phi_bb233_24;
  TNode<IntPtrT> phi_bb233_25;
  TNode<IntPtrT> phi_bb233_27;
  TNode<IntPtrT> phi_bb233_28;
  TNode<IntPtrT> phi_bb233_29;
  TNode<IntPtrT> phi_bb233_30;
  TNode<IntPtrT> phi_bb233_31;
  TNode<IntPtrT> phi_bb233_34;
  TNode<BoolT> phi_bb233_35;
  TNode<BoolT> phi_bb233_36;
  TNode<Union<FixedArray, Smi>> phi_bb233_37;
  TNode<JSAny> tmp431;
  if (block233.is_used()) {
    ca_.Bind(&block233, &phi_bb233_17, &phi_bb233_18, &phi_bb233_19, &phi_bb233_23, &phi_bb233_24, &phi_bb233_25, &phi_bb233_27, &phi_bb233_28, &phi_bb233_29, &phi_bb233_30, &phi_bb233_31, &phi_bb233_34, &phi_bb233_35, &phi_bb233_36, &phi_bb233_37);
    tmp431 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kClearWasmSuspenderResumeField, p_context, tmp429)); 
    ca_.Goto(&block234, phi_bb233_17, phi_bb233_18, phi_bb233_19, phi_bb233_23, phi_bb233_24, phi_bb233_25, phi_bb233_27, phi_bb233_28, phi_bb233_29, phi_bb233_30, phi_bb233_31, phi_bb233_34, phi_bb233_35, phi_bb233_36, phi_bb233_37);
  }

  TNode<JSAny> phi_bb234_17;
  TNode<IntPtrT> phi_bb234_18;
  TNode<BoolT> phi_bb234_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb234_23;
  TNode<IntPtrT> phi_bb234_24;
  TNode<IntPtrT> phi_bb234_25;
  TNode<IntPtrT> phi_bb234_27;
  TNode<IntPtrT> phi_bb234_28;
  TNode<IntPtrT> phi_bb234_29;
  TNode<IntPtrT> phi_bb234_30;
  TNode<IntPtrT> phi_bb234_31;
  TNode<IntPtrT> phi_bb234_34;
  TNode<BoolT> phi_bb234_35;
  TNode<BoolT> phi_bb234_36;
  TNode<Union<FixedArray, Smi>> phi_bb234_37;
  if (block234.is_used()) {
    ca_.Bind(&block234, &phi_bb234_17, &phi_bb234_18, &phi_bb234_19, &phi_bb234_23, &phi_bb234_24, &phi_bb234_25, &phi_bb234_27, &phi_bb234_28, &phi_bb234_29, &phi_bb234_30, &phi_bb234_31, &phi_bb234_34, &phi_bb234_35, &phi_bb234_36, &phi_bb234_37);
    ca_.Goto(&block232, phi_bb234_17, phi_bb234_18, phi_bb234_19, phi_bb234_23, phi_bb234_24, phi_bb234_25, phi_bb234_27, phi_bb234_28, phi_bb234_29, phi_bb234_30, phi_bb234_31, phi_bb234_34, phi_bb234_35, phi_bb234_36, phi_bb234_37, tmp429);
  }

  TNode<JSAny> phi_bb231_17;
  TNode<IntPtrT> phi_bb231_18;
  TNode<BoolT> phi_bb231_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb231_23;
  TNode<IntPtrT> phi_bb231_24;
  TNode<IntPtrT> phi_bb231_25;
  TNode<IntPtrT> phi_bb231_27;
  TNode<IntPtrT> phi_bb231_28;
  TNode<IntPtrT> phi_bb231_29;
  TNode<IntPtrT> phi_bb231_30;
  TNode<IntPtrT> phi_bb231_31;
  TNode<IntPtrT> phi_bb231_34;
  TNode<BoolT> phi_bb231_35;
  TNode<BoolT> phi_bb231_36;
  TNode<Union<FixedArray, Smi>> phi_bb231_37;
  if (block231.is_used()) {
    ca_.Bind(&block231, &phi_bb231_17, &phi_bb231_18, &phi_bb231_19, &phi_bb231_23, &phi_bb231_24, &phi_bb231_25, &phi_bb231_27, &phi_bb231_28, &phi_bb231_29, &phi_bb231_30, &phi_bb231_31, &phi_bb231_34, &phi_bb231_35, &phi_bb231_36, &phi_bb231_37);
    ca_.Goto(&block232, phi_bb231_17, phi_bb231_18, phi_bb231_19, phi_bb231_23, phi_bb231_24, phi_bb231_25, phi_bb231_27, phi_bb231_28, phi_bb231_29, phi_bb231_30, phi_bb231_31, phi_bb231_34, phi_bb231_35, phi_bb231_36, phi_bb231_37, tmp428);
  }

  TNode<JSAny> phi_bb232_17;
  TNode<IntPtrT> phi_bb232_18;
  TNode<BoolT> phi_bb232_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb232_23;
  TNode<IntPtrT> phi_bb232_24;
  TNode<IntPtrT> phi_bb232_25;
  TNode<IntPtrT> phi_bb232_27;
  TNode<IntPtrT> phi_bb232_28;
  TNode<IntPtrT> phi_bb232_29;
  TNode<IntPtrT> phi_bb232_30;
  TNode<IntPtrT> phi_bb232_31;
  TNode<IntPtrT> phi_bb232_34;
  TNode<BoolT> phi_bb232_35;
  TNode<BoolT> phi_bb232_36;
  TNode<Union<FixedArray, Smi>> phi_bb232_37;
  TNode<JSAny> phi_bb232_38;
  if (block232.is_used()) {
    ca_.Bind(&block232, &phi_bb232_17, &phi_bb232_18, &phi_bb232_19, &phi_bb232_23, &phi_bb232_24, &phi_bb232_25, &phi_bb232_27, &phi_bb232_28, &phi_bb232_29, &phi_bb232_30, &phi_bb232_31, &phi_bb232_34, &phi_bb232_35, &phi_bb232_36, &phi_bb232_37, &phi_bb232_38);
    ca_.Branch(phi_bb232_36, &block235, std::vector<compiler::Node*>{phi_bb232_17, phi_bb232_18, phi_bb232_19, phi_bb232_23, phi_bb232_24, phi_bb232_25, phi_bb232_27, phi_bb232_28, phi_bb232_29, phi_bb232_30, phi_bb232_31, phi_bb232_34, phi_bb232_35, phi_bb232_36, phi_bb232_37}, &block236, std::vector<compiler::Node*>{phi_bb232_17, phi_bb232_18, phi_bb232_19, phi_bb232_23, phi_bb232_24, phi_bb232_25, phi_bb232_27, phi_bb232_28, phi_bb232_29, phi_bb232_30, phi_bb232_31, phi_bb232_34, phi_bb232_35, phi_bb232_36, phi_bb232_37});
  }

  TNode<JSAny> phi_bb235_17;
  TNode<IntPtrT> phi_bb235_18;
  TNode<BoolT> phi_bb235_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb235_23;
  TNode<IntPtrT> phi_bb235_24;
  TNode<IntPtrT> phi_bb235_25;
  TNode<IntPtrT> phi_bb235_27;
  TNode<IntPtrT> phi_bb235_28;
  TNode<IntPtrT> phi_bb235_29;
  TNode<IntPtrT> phi_bb235_30;
  TNode<IntPtrT> phi_bb235_31;
  TNode<IntPtrT> phi_bb235_34;
  TNode<BoolT> phi_bb235_35;
  TNode<BoolT> phi_bb235_36;
  TNode<Union<FixedArray, Smi>> phi_bb235_37;
  TNode<BoolT> tmp432;
  if (block235.is_used()) {
    ca_.Bind(&block235, &phi_bb235_17, &phi_bb235_18, &phi_bb235_19, &phi_bb235_23, &phi_bb235_24, &phi_bb235_25, &phi_bb235_27, &phi_bb235_28, &phi_bb235_29, &phi_bb235_30, &phi_bb235_31, &phi_bb235_34, &phi_bb235_35, &phi_bb235_36, &phi_bb235_37);
    tmp432 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb235_35});
    ca_.Branch(tmp432, &block238, std::vector<compiler::Node*>{phi_bb235_17, phi_bb235_18, phi_bb235_19, phi_bb235_23, phi_bb235_24, phi_bb235_25, phi_bb235_27, phi_bb235_28, phi_bb235_29, phi_bb235_30, phi_bb235_31, phi_bb235_34, phi_bb235_35, phi_bb235_36, phi_bb235_37}, &block239, std::vector<compiler::Node*>{phi_bb235_17, phi_bb235_18, phi_bb235_19, phi_bb235_23, phi_bb235_24, phi_bb235_25, phi_bb235_27, phi_bb235_28, phi_bb235_29, phi_bb235_30, phi_bb235_31, phi_bb235_34, phi_bb235_35, phi_bb235_36, phi_bb235_37});
  }

  TNode<JSAny> phi_bb238_17;
  TNode<IntPtrT> phi_bb238_18;
  TNode<BoolT> phi_bb238_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb238_23;
  TNode<IntPtrT> phi_bb238_24;
  TNode<IntPtrT> phi_bb238_25;
  TNode<IntPtrT> phi_bb238_27;
  TNode<IntPtrT> phi_bb238_28;
  TNode<IntPtrT> phi_bb238_29;
  TNode<IntPtrT> phi_bb238_30;
  TNode<IntPtrT> phi_bb238_31;
  TNode<IntPtrT> phi_bb238_34;
  TNode<BoolT> phi_bb238_35;
  TNode<BoolT> phi_bb238_36;
  TNode<Union<FixedArray, Smi>> phi_bb238_37;
  TNode<IntPtrT> tmp433;
  if (block238.is_used()) {
    ca_.Bind(&block238, &phi_bb238_17, &phi_bb238_18, &phi_bb238_19, &phi_bb238_23, &phi_bb238_24, &phi_bb238_25, &phi_bb238_27, &phi_bb238_28, &phi_bb238_29, &phi_bb238_30, &phi_bb238_31, &phi_bb238_34, &phi_bb238_35, &phi_bb238_36, &phi_bb238_37);
    tmp433 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block239, phi_bb238_17, phi_bb238_18, phi_bb238_19, phi_bb238_23, phi_bb238_24, phi_bb238_25, phi_bb238_27, phi_bb238_28, phi_bb238_29, phi_bb238_30, phi_bb238_31, tmp433, phi_bb238_35, phi_bb238_36, phi_bb238_37);
  }

  TNode<JSAny> phi_bb239_17;
  TNode<IntPtrT> phi_bb239_18;
  TNode<BoolT> phi_bb239_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb239_23;
  TNode<IntPtrT> phi_bb239_24;
  TNode<IntPtrT> phi_bb239_25;
  TNode<IntPtrT> phi_bb239_27;
  TNode<IntPtrT> phi_bb239_28;
  TNode<IntPtrT> phi_bb239_29;
  TNode<IntPtrT> phi_bb239_30;
  TNode<IntPtrT> phi_bb239_31;
  TNode<IntPtrT> phi_bb239_34;
  TNode<BoolT> phi_bb239_35;
  TNode<BoolT> phi_bb239_36;
  TNode<Union<FixedArray, Smi>> phi_bb239_37;
  TNode<IntPtrT> tmp434;
  if (block239.is_used()) {
    ca_.Bind(&block239, &phi_bb239_17, &phi_bb239_18, &phi_bb239_19, &phi_bb239_23, &phi_bb239_24, &phi_bb239_25, &phi_bb239_27, &phi_bb239_28, &phi_bb239_29, &phi_bb239_30, &phi_bb239_31, &phi_bb239_34, &phi_bb239_35, &phi_bb239_36, &phi_bb239_37);
    tmp434 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block242, phi_bb239_17, phi_bb239_18, phi_bb239_19, phi_bb239_23, phi_bb239_24, phi_bb239_25, phi_bb239_27, phi_bb239_28, phi_bb239_29, phi_bb239_30, phi_bb239_31, phi_bb239_34, phi_bb239_35, phi_bb239_36, phi_bb239_37, tmp434);
  }

  TNode<JSAny> phi_bb242_17;
  TNode<IntPtrT> phi_bb242_18;
  TNode<BoolT> phi_bb242_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb242_23;
  TNode<IntPtrT> phi_bb242_24;
  TNode<IntPtrT> phi_bb242_25;
  TNode<IntPtrT> phi_bb242_27;
  TNode<IntPtrT> phi_bb242_28;
  TNode<IntPtrT> phi_bb242_29;
  TNode<IntPtrT> phi_bb242_30;
  TNode<IntPtrT> phi_bb242_31;
  TNode<IntPtrT> phi_bb242_34;
  TNode<BoolT> phi_bb242_35;
  TNode<BoolT> phi_bb242_36;
  TNode<Union<FixedArray, Smi>> phi_bb242_37;
  TNode<IntPtrT> phi_bb242_39;
  TNode<BoolT> tmp435;
  if (block242.is_used()) {
    ca_.Bind(&block242, &phi_bb242_17, &phi_bb242_18, &phi_bb242_19, &phi_bb242_23, &phi_bb242_24, &phi_bb242_25, &phi_bb242_27, &phi_bb242_28, &phi_bb242_29, &phi_bb242_30, &phi_bb242_31, &phi_bb242_34, &phi_bb242_35, &phi_bb242_36, &phi_bb242_37, &phi_bb242_39);
    tmp435 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb242_39}, TNode<IntPtrT>{tmp24});
    ca_.Branch(tmp435, &block240, std::vector<compiler::Node*>{phi_bb242_17, phi_bb242_18, phi_bb242_19, phi_bb242_23, phi_bb242_24, phi_bb242_25, phi_bb242_27, phi_bb242_28, phi_bb242_29, phi_bb242_30, phi_bb242_31, phi_bb242_34, phi_bb242_35, phi_bb242_36, phi_bb242_37, phi_bb242_39}, &block241, std::vector<compiler::Node*>{phi_bb242_17, phi_bb242_18, phi_bb242_19, phi_bb242_23, phi_bb242_24, phi_bb242_25, phi_bb242_27, phi_bb242_28, phi_bb242_29, phi_bb242_30, phi_bb242_31, phi_bb242_34, phi_bb242_35, phi_bb242_36, phi_bb242_37, phi_bb242_39});
  }

  TNode<JSAny> phi_bb240_17;
  TNode<IntPtrT> phi_bb240_18;
  TNode<BoolT> phi_bb240_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb240_23;
  TNode<IntPtrT> phi_bb240_24;
  TNode<IntPtrT> phi_bb240_25;
  TNode<IntPtrT> phi_bb240_27;
  TNode<IntPtrT> phi_bb240_28;
  TNode<IntPtrT> phi_bb240_29;
  TNode<IntPtrT> phi_bb240_30;
  TNode<IntPtrT> phi_bb240_31;
  TNode<IntPtrT> phi_bb240_34;
  TNode<BoolT> phi_bb240_35;
  TNode<BoolT> phi_bb240_36;
  TNode<Union<FixedArray, Smi>> phi_bb240_37;
  TNode<IntPtrT> phi_bb240_39;
  TNode<IntPtrT> tmp436;
  TNode<IntPtrT> tmp437;
  TNode<Union<HeapObject, TaggedIndex>> tmp438;
  TNode<IntPtrT> tmp439;
  TNode<Uint32T> tmp440;
  TNode<Uint32T> tmp441;
  TNode<Uint32T> tmp442;
  TNode<Uint32T> tmp443;
  TNode<BoolT> tmp444;
  if (block240.is_used()) {
    ca_.Bind(&block240, &phi_bb240_17, &phi_bb240_18, &phi_bb240_19, &phi_bb240_23, &phi_bb240_24, &phi_bb240_25, &phi_bb240_27, &phi_bb240_28, &phi_bb240_29, &phi_bb240_30, &phi_bb240_31, &phi_bb240_34, &phi_bb240_35, &phi_bb240_36, &phi_bb240_37, &phi_bb240_39);
    tmp436 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{phi_bb240_39});
    tmp437 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp168}, TNode<IntPtrT>{tmp436});
    std::tie(tmp438, tmp439) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp167}, TNode<IntPtrT>{tmp437}).Flatten();
    tmp440 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp438, tmp439});
    tmp441 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp442 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp440}, TNode<Uint32T>{tmp441});
    tmp443 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp444 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp442}, TNode<Uint32T>{tmp443});
    ca_.Branch(tmp444, &block245, std::vector<compiler::Node*>{phi_bb240_17, phi_bb240_18, phi_bb240_19, phi_bb240_23, phi_bb240_24, phi_bb240_25, phi_bb240_27, phi_bb240_28, phi_bb240_29, phi_bb240_30, phi_bb240_31, phi_bb240_34, phi_bb240_35, phi_bb240_36, phi_bb240_37, phi_bb240_39}, &block246, std::vector<compiler::Node*>{phi_bb240_17, phi_bb240_18, phi_bb240_19, phi_bb240_23, phi_bb240_24, phi_bb240_25, phi_bb240_27, phi_bb240_28, phi_bb240_29, phi_bb240_30, phi_bb240_31, phi_bb240_34, phi_bb240_35, phi_bb240_36, phi_bb240_37, phi_bb240_39});
  }

  TNode<JSAny> phi_bb245_17;
  TNode<IntPtrT> phi_bb245_18;
  TNode<BoolT> phi_bb245_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb245_23;
  TNode<IntPtrT> phi_bb245_24;
  TNode<IntPtrT> phi_bb245_25;
  TNode<IntPtrT> phi_bb245_27;
  TNode<IntPtrT> phi_bb245_28;
  TNode<IntPtrT> phi_bb245_29;
  TNode<IntPtrT> phi_bb245_30;
  TNode<IntPtrT> phi_bb245_31;
  TNode<IntPtrT> phi_bb245_34;
  TNode<BoolT> phi_bb245_35;
  TNode<BoolT> phi_bb245_36;
  TNode<Union<FixedArray, Smi>> phi_bb245_37;
  TNode<IntPtrT> phi_bb245_39;
  TNode<FixedArray> tmp445;
  TNode<Union<HeapObject, TaggedIndex>> tmp446;
  TNode<IntPtrT> tmp447;
  TNode<IntPtrT> tmp448;
  TNode<UintPtrT> tmp449;
  TNode<UintPtrT> tmp450;
  TNode<BoolT> tmp451;
  if (block245.is_used()) {
    ca_.Bind(&block245, &phi_bb245_17, &phi_bb245_18, &phi_bb245_19, &phi_bb245_23, &phi_bb245_24, &phi_bb245_25, &phi_bb245_27, &phi_bb245_28, &phi_bb245_29, &phi_bb245_30, &phi_bb245_31, &phi_bb245_34, &phi_bb245_35, &phi_bb245_36, &phi_bb245_37, &phi_bb245_39);
    tmp445 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{phi_bb245_37});
    std::tie(tmp446, tmp447, tmp448) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp445}).Flatten();
    tmp449 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb245_39});
    tmp450 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp448});
    tmp451 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp449}, TNode<UintPtrT>{tmp450});
    ca_.Branch(tmp451, &block251, std::vector<compiler::Node*>{phi_bb245_17, phi_bb245_18, phi_bb245_19, phi_bb245_23, phi_bb245_24, phi_bb245_25, phi_bb245_27, phi_bb245_28, phi_bb245_29, phi_bb245_30, phi_bb245_31, phi_bb245_34, phi_bb245_35, phi_bb245_36, phi_bb245_37, phi_bb245_39, phi_bb245_39, phi_bb245_39, phi_bb245_39, phi_bb245_39}, &block252, std::vector<compiler::Node*>{phi_bb245_17, phi_bb245_18, phi_bb245_19, phi_bb245_23, phi_bb245_24, phi_bb245_25, phi_bb245_27, phi_bb245_28, phi_bb245_29, phi_bb245_30, phi_bb245_31, phi_bb245_34, phi_bb245_35, phi_bb245_36, phi_bb245_37, phi_bb245_39, phi_bb245_39, phi_bb245_39, phi_bb245_39, phi_bb245_39});
  }

  TNode<JSAny> phi_bb251_17;
  TNode<IntPtrT> phi_bb251_18;
  TNode<BoolT> phi_bb251_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb251_23;
  TNode<IntPtrT> phi_bb251_24;
  TNode<IntPtrT> phi_bb251_25;
  TNode<IntPtrT> phi_bb251_27;
  TNode<IntPtrT> phi_bb251_28;
  TNode<IntPtrT> phi_bb251_29;
  TNode<IntPtrT> phi_bb251_30;
  TNode<IntPtrT> phi_bb251_31;
  TNode<IntPtrT> phi_bb251_34;
  TNode<BoolT> phi_bb251_35;
  TNode<BoolT> phi_bb251_36;
  TNode<Union<FixedArray, Smi>> phi_bb251_37;
  TNode<IntPtrT> phi_bb251_39;
  TNode<IntPtrT> phi_bb251_46;
  TNode<IntPtrT> phi_bb251_47;
  TNode<IntPtrT> phi_bb251_51;
  TNode<IntPtrT> phi_bb251_52;
  TNode<IntPtrT> tmp452;
  TNode<IntPtrT> tmp453;
  TNode<Union<HeapObject, TaggedIndex>> tmp454;
  TNode<IntPtrT> tmp455;
  TNode<Object> tmp456;
  TNode<IntPtrT> tmp457;
  TNode<IntPtrT> tmp458;
  TNode<IntPtrT> tmp459;
  TNode<BoolT> tmp460;
  if (block251.is_used()) {
    ca_.Bind(&block251, &phi_bb251_17, &phi_bb251_18, &phi_bb251_19, &phi_bb251_23, &phi_bb251_24, &phi_bb251_25, &phi_bb251_27, &phi_bb251_28, &phi_bb251_29, &phi_bb251_30, &phi_bb251_31, &phi_bb251_34, &phi_bb251_35, &phi_bb251_36, &phi_bb251_37, &phi_bb251_39, &phi_bb251_46, &phi_bb251_47, &phi_bb251_51, &phi_bb251_52);
    tmp452 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb251_52});
    tmp453 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp447}, TNode<IntPtrT>{tmp452});
    std::tie(tmp454, tmp455) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp446}, TNode<IntPtrT>{tmp453}).Flatten();
    tmp456 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp454, tmp455});
    tmp457 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp458 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb251_27}, TNode<IntPtrT>{tmp457});
    tmp459 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp460 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb251_27}, TNode<IntPtrT>{tmp459});
    ca_.Branch(tmp460, &block256, std::vector<compiler::Node*>{phi_bb251_17, phi_bb251_18, phi_bb251_19, phi_bb251_23, phi_bb251_24, phi_bb251_25, phi_bb251_28, phi_bb251_29, phi_bb251_30, phi_bb251_31, phi_bb251_34, phi_bb251_35, phi_bb251_36, phi_bb251_37, phi_bb251_39}, &block257, std::vector<compiler::Node*>{phi_bb251_17, phi_bb251_18, phi_bb251_19, phi_bb251_23, phi_bb251_24, phi_bb251_25, phi_bb251_28, phi_bb251_29, phi_bb251_30, phi_bb251_31, phi_bb251_34, phi_bb251_35, phi_bb251_36, phi_bb251_37, phi_bb251_39});
  }

  TNode<JSAny> phi_bb252_17;
  TNode<IntPtrT> phi_bb252_18;
  TNode<BoolT> phi_bb252_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb252_23;
  TNode<IntPtrT> phi_bb252_24;
  TNode<IntPtrT> phi_bb252_25;
  TNode<IntPtrT> phi_bb252_27;
  TNode<IntPtrT> phi_bb252_28;
  TNode<IntPtrT> phi_bb252_29;
  TNode<IntPtrT> phi_bb252_30;
  TNode<IntPtrT> phi_bb252_31;
  TNode<IntPtrT> phi_bb252_34;
  TNode<BoolT> phi_bb252_35;
  TNode<BoolT> phi_bb252_36;
  TNode<Union<FixedArray, Smi>> phi_bb252_37;
  TNode<IntPtrT> phi_bb252_39;
  TNode<IntPtrT> phi_bb252_46;
  TNode<IntPtrT> phi_bb252_47;
  TNode<IntPtrT> phi_bb252_51;
  TNode<IntPtrT> phi_bb252_52;
  if (block252.is_used()) {
    ca_.Bind(&block252, &phi_bb252_17, &phi_bb252_18, &phi_bb252_19, &phi_bb252_23, &phi_bb252_24, &phi_bb252_25, &phi_bb252_27, &phi_bb252_28, &phi_bb252_29, &phi_bb252_30, &phi_bb252_31, &phi_bb252_34, &phi_bb252_35, &phi_bb252_36, &phi_bb252_37, &phi_bb252_39, &phi_bb252_46, &phi_bb252_47, &phi_bb252_51, &phi_bb252_52);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb256_17;
  TNode<IntPtrT> phi_bb256_18;
  TNode<BoolT> phi_bb256_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb256_23;
  TNode<IntPtrT> phi_bb256_24;
  TNode<IntPtrT> phi_bb256_25;
  TNode<IntPtrT> phi_bb256_28;
  TNode<IntPtrT> phi_bb256_29;
  TNode<IntPtrT> phi_bb256_30;
  TNode<IntPtrT> phi_bb256_31;
  TNode<IntPtrT> phi_bb256_34;
  TNode<BoolT> phi_bb256_35;
  TNode<BoolT> phi_bb256_36;
  TNode<Union<FixedArray, Smi>> phi_bb256_37;
  TNode<IntPtrT> phi_bb256_39;
  TNode<Union<HeapObject, TaggedIndex>> tmp461;
  TNode<IntPtrT> tmp462;
  TNode<IntPtrT> tmp463;
  TNode<IntPtrT> tmp464;
  if (block256.is_used()) {
    ca_.Bind(&block256, &phi_bb256_17, &phi_bb256_18, &phi_bb256_19, &phi_bb256_23, &phi_bb256_24, &phi_bb256_25, &phi_bb256_28, &phi_bb256_29, &phi_bb256_30, &phi_bb256_31, &phi_bb256_34, &phi_bb256_35, &phi_bb256_36, &phi_bb256_37, &phi_bb256_39);
    std::tie(tmp461, tmp462) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb256_29}).Flatten();
    tmp463 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp464 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb256_29}, TNode<IntPtrT>{tmp463});
    ca_.Goto(&block255, phi_bb256_17, phi_bb256_18, phi_bb256_19, phi_bb256_23, phi_bb256_24, phi_bb256_25, phi_bb256_28, tmp464, phi_bb256_30, phi_bb256_31, phi_bb256_34, phi_bb256_35, phi_bb256_36, phi_bb256_37, phi_bb256_39, tmp461, tmp462);
  }

  TNode<JSAny> phi_bb257_17;
  TNode<IntPtrT> phi_bb257_18;
  TNode<BoolT> phi_bb257_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb257_23;
  TNode<IntPtrT> phi_bb257_24;
  TNode<IntPtrT> phi_bb257_25;
  TNode<IntPtrT> phi_bb257_28;
  TNode<IntPtrT> phi_bb257_29;
  TNode<IntPtrT> phi_bb257_30;
  TNode<IntPtrT> phi_bb257_31;
  TNode<IntPtrT> phi_bb257_34;
  TNode<BoolT> phi_bb257_35;
  TNode<BoolT> phi_bb257_36;
  TNode<Union<FixedArray, Smi>> phi_bb257_37;
  TNode<IntPtrT> phi_bb257_39;
  if (block257.is_used()) {
    ca_.Bind(&block257, &phi_bb257_17, &phi_bb257_18, &phi_bb257_19, &phi_bb257_23, &phi_bb257_24, &phi_bb257_25, &phi_bb257_28, &phi_bb257_29, &phi_bb257_30, &phi_bb257_31, &phi_bb257_34, &phi_bb257_35, &phi_bb257_36, &phi_bb257_37, &phi_bb257_39);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block259, phi_bb257_17, phi_bb257_18, phi_bb257_19, phi_bb257_23, phi_bb257_24, phi_bb257_25, phi_bb257_28, phi_bb257_29, phi_bb257_30, phi_bb257_31, phi_bb257_34, phi_bb257_35, phi_bb257_36, phi_bb257_37, phi_bb257_39);
    } else {
      ca_.Goto(&block260, phi_bb257_17, phi_bb257_18, phi_bb257_19, phi_bb257_23, phi_bb257_24, phi_bb257_25, phi_bb257_28, phi_bb257_29, phi_bb257_30, phi_bb257_31, phi_bb257_34, phi_bb257_35, phi_bb257_36, phi_bb257_37, phi_bb257_39);
    }
  }

  TNode<JSAny> phi_bb259_17;
  TNode<IntPtrT> phi_bb259_18;
  TNode<BoolT> phi_bb259_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb259_23;
  TNode<IntPtrT> phi_bb259_24;
  TNode<IntPtrT> phi_bb259_25;
  TNode<IntPtrT> phi_bb259_28;
  TNode<IntPtrT> phi_bb259_29;
  TNode<IntPtrT> phi_bb259_30;
  TNode<IntPtrT> phi_bb259_31;
  TNode<IntPtrT> phi_bb259_34;
  TNode<BoolT> phi_bb259_35;
  TNode<BoolT> phi_bb259_36;
  TNode<Union<FixedArray, Smi>> phi_bb259_37;
  TNode<IntPtrT> phi_bb259_39;
  TNode<Union<HeapObject, TaggedIndex>> tmp465;
  TNode<IntPtrT> tmp466;
  TNode<IntPtrT> tmp467;
  TNode<IntPtrT> tmp468;
  if (block259.is_used()) {
    ca_.Bind(&block259, &phi_bb259_17, &phi_bb259_18, &phi_bb259_19, &phi_bb259_23, &phi_bb259_24, &phi_bb259_25, &phi_bb259_28, &phi_bb259_29, &phi_bb259_30, &phi_bb259_31, &phi_bb259_34, &phi_bb259_35, &phi_bb259_36, &phi_bb259_37, &phi_bb259_39);
    std::tie(tmp465, tmp466) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb259_31}).Flatten();
    tmp467 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp468 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb259_31}, TNode<IntPtrT>{tmp467});
    ca_.Goto(&block258, phi_bb259_17, phi_bb259_18, phi_bb259_19, phi_bb259_23, phi_bb259_24, phi_bb259_25, phi_bb259_28, phi_bb259_29, phi_bb259_30, tmp468, phi_bb259_34, phi_bb259_35, phi_bb259_36, phi_bb259_37, phi_bb259_39, tmp465, tmp466);
  }

  TNode<JSAny> phi_bb260_17;
  TNode<IntPtrT> phi_bb260_18;
  TNode<BoolT> phi_bb260_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb260_23;
  TNode<IntPtrT> phi_bb260_24;
  TNode<IntPtrT> phi_bb260_25;
  TNode<IntPtrT> phi_bb260_28;
  TNode<IntPtrT> phi_bb260_29;
  TNode<IntPtrT> phi_bb260_30;
  TNode<IntPtrT> phi_bb260_31;
  TNode<IntPtrT> phi_bb260_34;
  TNode<BoolT> phi_bb260_35;
  TNode<BoolT> phi_bb260_36;
  TNode<Union<FixedArray, Smi>> phi_bb260_37;
  TNode<IntPtrT> phi_bb260_39;
  TNode<IntPtrT> tmp469;
  TNode<BoolT> tmp470;
  if (block260.is_used()) {
    ca_.Bind(&block260, &phi_bb260_17, &phi_bb260_18, &phi_bb260_19, &phi_bb260_23, &phi_bb260_24, &phi_bb260_25, &phi_bb260_28, &phi_bb260_29, &phi_bb260_30, &phi_bb260_31, &phi_bb260_34, &phi_bb260_35, &phi_bb260_36, &phi_bb260_37, &phi_bb260_39);
    tmp469 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp470 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb260_34}, TNode<IntPtrT>{tmp469});
    ca_.Branch(tmp470, &block262, std::vector<compiler::Node*>{phi_bb260_17, phi_bb260_18, phi_bb260_19, phi_bb260_23, phi_bb260_24, phi_bb260_25, phi_bb260_28, phi_bb260_29, phi_bb260_30, phi_bb260_31, phi_bb260_34, phi_bb260_35, phi_bb260_36, phi_bb260_37, phi_bb260_39}, &block263, std::vector<compiler::Node*>{phi_bb260_17, phi_bb260_18, phi_bb260_19, phi_bb260_23, phi_bb260_24, phi_bb260_25, phi_bb260_28, phi_bb260_29, phi_bb260_30, phi_bb260_31, phi_bb260_34, phi_bb260_35, phi_bb260_36, phi_bb260_37, phi_bb260_39});
  }

  TNode<JSAny> phi_bb262_17;
  TNode<IntPtrT> phi_bb262_18;
  TNode<BoolT> phi_bb262_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb262_23;
  TNode<IntPtrT> phi_bb262_24;
  TNode<IntPtrT> phi_bb262_25;
  TNode<IntPtrT> phi_bb262_28;
  TNode<IntPtrT> phi_bb262_29;
  TNode<IntPtrT> phi_bb262_30;
  TNode<IntPtrT> phi_bb262_31;
  TNode<IntPtrT> phi_bb262_34;
  TNode<BoolT> phi_bb262_35;
  TNode<BoolT> phi_bb262_36;
  TNode<Union<FixedArray, Smi>> phi_bb262_37;
  TNode<IntPtrT> phi_bb262_39;
  TNode<Union<HeapObject, TaggedIndex>> tmp471;
  TNode<IntPtrT> tmp472;
  TNode<IntPtrT> tmp473;
  TNode<BoolT> tmp474;
  if (block262.is_used()) {
    ca_.Bind(&block262, &phi_bb262_17, &phi_bb262_18, &phi_bb262_19, &phi_bb262_23, &phi_bb262_24, &phi_bb262_25, &phi_bb262_28, &phi_bb262_29, &phi_bb262_30, &phi_bb262_31, &phi_bb262_34, &phi_bb262_35, &phi_bb262_36, &phi_bb262_37, &phi_bb262_39);
    std::tie(tmp471, tmp472) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb262_34}).Flatten();
    tmp473 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp474 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block258, phi_bb262_17, phi_bb262_18, phi_bb262_19, phi_bb262_23, phi_bb262_24, phi_bb262_25, phi_bb262_28, phi_bb262_29, phi_bb262_30, phi_bb262_31, tmp473, tmp474, phi_bb262_36, phi_bb262_37, phi_bb262_39, tmp471, tmp472);
  }

  TNode<JSAny> phi_bb263_17;
  TNode<IntPtrT> phi_bb263_18;
  TNode<BoolT> phi_bb263_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb263_23;
  TNode<IntPtrT> phi_bb263_24;
  TNode<IntPtrT> phi_bb263_25;
  TNode<IntPtrT> phi_bb263_28;
  TNode<IntPtrT> phi_bb263_29;
  TNode<IntPtrT> phi_bb263_30;
  TNode<IntPtrT> phi_bb263_31;
  TNode<IntPtrT> phi_bb263_34;
  TNode<BoolT> phi_bb263_35;
  TNode<BoolT> phi_bb263_36;
  TNode<Union<FixedArray, Smi>> phi_bb263_37;
  TNode<IntPtrT> phi_bb263_39;
  TNode<Union<HeapObject, TaggedIndex>> tmp475;
  TNode<IntPtrT> tmp476;
  TNode<IntPtrT> tmp477;
  TNode<IntPtrT> tmp478;
  TNode<IntPtrT> tmp479;
  TNode<IntPtrT> tmp480;
  TNode<BoolT> tmp481;
  if (block263.is_used()) {
    ca_.Bind(&block263, &phi_bb263_17, &phi_bb263_18, &phi_bb263_19, &phi_bb263_23, &phi_bb263_24, &phi_bb263_25, &phi_bb263_28, &phi_bb263_29, &phi_bb263_30, &phi_bb263_31, &phi_bb263_34, &phi_bb263_35, &phi_bb263_36, &phi_bb263_37, &phi_bb263_39);
    std::tie(tmp475, tmp476) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb263_31}).Flatten();
    tmp477 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp478 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb263_31}, TNode<IntPtrT>{tmp477});
    tmp479 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp480 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp478}, TNode<IntPtrT>{tmp479});
    tmp481 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block258, phi_bb263_17, phi_bb263_18, phi_bb263_19, phi_bb263_23, phi_bb263_24, phi_bb263_25, phi_bb263_28, phi_bb263_29, phi_bb263_30, tmp480, tmp478, tmp481, phi_bb263_36, phi_bb263_37, phi_bb263_39, tmp475, tmp476);
  }

  TNode<JSAny> phi_bb258_17;
  TNode<IntPtrT> phi_bb258_18;
  TNode<BoolT> phi_bb258_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb258_23;
  TNode<IntPtrT> phi_bb258_24;
  TNode<IntPtrT> phi_bb258_25;
  TNode<IntPtrT> phi_bb258_28;
  TNode<IntPtrT> phi_bb258_29;
  TNode<IntPtrT> phi_bb258_30;
  TNode<IntPtrT> phi_bb258_31;
  TNode<IntPtrT> phi_bb258_34;
  TNode<BoolT> phi_bb258_35;
  TNode<BoolT> phi_bb258_36;
  TNode<Union<FixedArray, Smi>> phi_bb258_37;
  TNode<IntPtrT> phi_bb258_39;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb258_42;
  TNode<IntPtrT> phi_bb258_43;
  if (block258.is_used()) {
    ca_.Bind(&block258, &phi_bb258_17, &phi_bb258_18, &phi_bb258_19, &phi_bb258_23, &phi_bb258_24, &phi_bb258_25, &phi_bb258_28, &phi_bb258_29, &phi_bb258_30, &phi_bb258_31, &phi_bb258_34, &phi_bb258_35, &phi_bb258_36, &phi_bb258_37, &phi_bb258_39, &phi_bb258_42, &phi_bb258_43);
    ca_.Goto(&block255, phi_bb258_17, phi_bb258_18, phi_bb258_19, phi_bb258_23, phi_bb258_24, phi_bb258_25, phi_bb258_28, phi_bb258_29, phi_bb258_30, phi_bb258_31, phi_bb258_34, phi_bb258_35, phi_bb258_36, phi_bb258_37, phi_bb258_39, phi_bb258_42, phi_bb258_43);
  }

  TNode<JSAny> phi_bb255_17;
  TNode<IntPtrT> phi_bb255_18;
  TNode<BoolT> phi_bb255_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb255_23;
  TNode<IntPtrT> phi_bb255_24;
  TNode<IntPtrT> phi_bb255_25;
  TNode<IntPtrT> phi_bb255_28;
  TNode<IntPtrT> phi_bb255_29;
  TNode<IntPtrT> phi_bb255_30;
  TNode<IntPtrT> phi_bb255_31;
  TNode<IntPtrT> phi_bb255_34;
  TNode<BoolT> phi_bb255_35;
  TNode<BoolT> phi_bb255_36;
  TNode<Union<FixedArray, Smi>> phi_bb255_37;
  TNode<IntPtrT> phi_bb255_39;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb255_42;
  TNode<IntPtrT> phi_bb255_43;
  TNode<IntPtrT> tmp482;
  if (block255.is_used()) {
    ca_.Bind(&block255, &phi_bb255_17, &phi_bb255_18, &phi_bb255_19, &phi_bb255_23, &phi_bb255_24, &phi_bb255_25, &phi_bb255_28, &phi_bb255_29, &phi_bb255_30, &phi_bb255_31, &phi_bb255_34, &phi_bb255_35, &phi_bb255_36, &phi_bb255_37, &phi_bb255_39, &phi_bb255_42, &phi_bb255_43);
    tmp482 = CodeStubAssembler(state_).BitcastTaggedToWord(TNode<Object>{tmp456});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb255_42, phi_bb255_43}, tmp482);
    ca_.Goto(&block246, phi_bb255_17, phi_bb255_18, phi_bb255_19, phi_bb255_23, phi_bb255_24, phi_bb255_25, tmp458, phi_bb255_28, phi_bb255_29, phi_bb255_30, phi_bb255_31, phi_bb255_34, phi_bb255_35, phi_bb255_36, phi_bb255_37, phi_bb255_39);
  }

  TNode<JSAny> phi_bb246_17;
  TNode<IntPtrT> phi_bb246_18;
  TNode<BoolT> phi_bb246_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb246_23;
  TNode<IntPtrT> phi_bb246_24;
  TNode<IntPtrT> phi_bb246_25;
  TNode<IntPtrT> phi_bb246_27;
  TNode<IntPtrT> phi_bb246_28;
  TNode<IntPtrT> phi_bb246_29;
  TNode<IntPtrT> phi_bb246_30;
  TNode<IntPtrT> phi_bb246_31;
  TNode<IntPtrT> phi_bb246_34;
  TNode<BoolT> phi_bb246_35;
  TNode<BoolT> phi_bb246_36;
  TNode<Union<FixedArray, Smi>> phi_bb246_37;
  TNode<IntPtrT> phi_bb246_39;
  TNode<IntPtrT> tmp483;
  TNode<IntPtrT> tmp484;
  if (block246.is_used()) {
    ca_.Bind(&block246, &phi_bb246_17, &phi_bb246_18, &phi_bb246_19, &phi_bb246_23, &phi_bb246_24, &phi_bb246_25, &phi_bb246_27, &phi_bb246_28, &phi_bb246_29, &phi_bb246_30, &phi_bb246_31, &phi_bb246_34, &phi_bb246_35, &phi_bb246_36, &phi_bb246_37, &phi_bb246_39);
    tmp483 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp484 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb246_39}, TNode<IntPtrT>{tmp483});
    ca_.Goto(&block242, phi_bb246_17, phi_bb246_18, phi_bb246_19, phi_bb246_23, phi_bb246_24, phi_bb246_25, phi_bb246_27, phi_bb246_28, phi_bb246_29, phi_bb246_30, phi_bb246_31, phi_bb246_34, phi_bb246_35, phi_bb246_36, phi_bb246_37, tmp484);
  }

  TNode<JSAny> phi_bb241_17;
  TNode<IntPtrT> phi_bb241_18;
  TNode<BoolT> phi_bb241_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb241_23;
  TNode<IntPtrT> phi_bb241_24;
  TNode<IntPtrT> phi_bb241_25;
  TNode<IntPtrT> phi_bb241_27;
  TNode<IntPtrT> phi_bb241_28;
  TNode<IntPtrT> phi_bb241_29;
  TNode<IntPtrT> phi_bb241_30;
  TNode<IntPtrT> phi_bb241_31;
  TNode<IntPtrT> phi_bb241_34;
  TNode<BoolT> phi_bb241_35;
  TNode<BoolT> phi_bb241_36;
  TNode<Union<FixedArray, Smi>> phi_bb241_37;
  TNode<IntPtrT> phi_bb241_39;
  if (block241.is_used()) {
    ca_.Bind(&block241, &phi_bb241_17, &phi_bb241_18, &phi_bb241_19, &phi_bb241_23, &phi_bb241_24, &phi_bb241_25, &phi_bb241_27, &phi_bb241_28, &phi_bb241_29, &phi_bb241_30, &phi_bb241_31, &phi_bb241_34, &phi_bb241_35, &phi_bb241_36, &phi_bb241_37, &phi_bb241_39);
    ca_.Goto(&block236, phi_bb241_17, phi_bb241_18, phi_bb241_19, phi_bb241_23, phi_bb241_24, phi_bb241_25, phi_bb241_27, phi_bb241_28, phi_bb241_29, phi_bb241_30, phi_bb241_31, phi_bb241_34, phi_bb241_35, phi_bb241_36, phi_bb241_37);
  }

  TNode<JSAny> phi_bb236_17;
  TNode<IntPtrT> phi_bb236_18;
  TNode<BoolT> phi_bb236_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb236_23;
  TNode<IntPtrT> phi_bb236_24;
  TNode<IntPtrT> phi_bb236_25;
  TNode<IntPtrT> phi_bb236_27;
  TNode<IntPtrT> phi_bb236_28;
  TNode<IntPtrT> phi_bb236_29;
  TNode<IntPtrT> phi_bb236_30;
  TNode<IntPtrT> phi_bb236_31;
  TNode<IntPtrT> phi_bb236_34;
  TNode<BoolT> phi_bb236_35;
  TNode<BoolT> phi_bb236_36;
  TNode<Union<FixedArray, Smi>> phi_bb236_37;
  TNode<RawPtrT> tmp485;
  TNode<RawPtrT> tmp486;
  if (block236.is_used()) {
    ca_.Bind(&block236, &phi_bb236_17, &phi_bb236_18, &phi_bb236_19, &phi_bb236_23, &phi_bb236_24, &phi_bb236_25, &phi_bb236_27, &phi_bb236_28, &phi_bb236_29, &phi_bb236_30, &phi_bb236_31, &phi_bb236_34, &phi_bb236_35, &phi_bb236_36, &phi_bb236_37);
    tmp485 = CodeStubAssembler(state_).GCUnsafeReferenceToRawPtr(TNode<Union<HeapObject, TaggedIndex>>{phi_bb236_23}, TNode<IntPtrT>{phi_bb236_24});
    tmp486 = (TNode<RawPtrT>{tmp485});
    ca_.Branch(phi_bb236_35, &block266, std::vector<compiler::Node*>{phi_bb236_17, phi_bb236_18, phi_bb236_19, phi_bb236_23, phi_bb236_24, phi_bb236_25, phi_bb236_27, phi_bb236_28, phi_bb236_29, phi_bb236_30, phi_bb236_31, phi_bb236_34, phi_bb236_35, phi_bb236_36, phi_bb236_37, phi_bb236_31}, &block267, std::vector<compiler::Node*>{phi_bb236_17, phi_bb236_18, phi_bb236_19, phi_bb236_23, phi_bb236_24, phi_bb236_25, phi_bb236_27, phi_bb236_28, phi_bb236_29, phi_bb236_30, phi_bb236_31, phi_bb236_34, phi_bb236_35, phi_bb236_36, phi_bb236_37, phi_bb236_31});
  }

  TNode<JSAny> phi_bb266_17;
  TNode<IntPtrT> phi_bb266_18;
  TNode<BoolT> phi_bb266_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb266_23;
  TNode<IntPtrT> phi_bb266_24;
  TNode<IntPtrT> phi_bb266_25;
  TNode<IntPtrT> phi_bb266_27;
  TNode<IntPtrT> phi_bb266_28;
  TNode<IntPtrT> phi_bb266_29;
  TNode<IntPtrT> phi_bb266_30;
  TNode<IntPtrT> phi_bb266_31;
  TNode<IntPtrT> phi_bb266_34;
  TNode<BoolT> phi_bb266_35;
  TNode<BoolT> phi_bb266_36;
  TNode<Union<FixedArray, Smi>> phi_bb266_37;
  TNode<IntPtrT> phi_bb266_40;
  TNode<IntPtrT> tmp487;
  TNode<IntPtrT> tmp488;
  if (block266.is_used()) {
    ca_.Bind(&block266, &phi_bb266_17, &phi_bb266_18, &phi_bb266_19, &phi_bb266_23, &phi_bb266_24, &phi_bb266_25, &phi_bb266_27, &phi_bb266_28, &phi_bb266_29, &phi_bb266_30, &phi_bb266_31, &phi_bb266_34, &phi_bb266_35, &phi_bb266_36, &phi_bb266_37, &phi_bb266_40);
    tmp487 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp488 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb266_40}, TNode<IntPtrT>{tmp487});
    ca_.Goto(&block267, phi_bb266_17, phi_bb266_18, phi_bb266_19, phi_bb266_23, phi_bb266_24, phi_bb266_25, phi_bb266_27, phi_bb266_28, phi_bb266_29, phi_bb266_30, phi_bb266_31, phi_bb266_34, phi_bb266_35, phi_bb266_36, phi_bb266_37, tmp488);
  }

  TNode<JSAny> phi_bb267_17;
  TNode<IntPtrT> phi_bb267_18;
  TNode<BoolT> phi_bb267_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb267_23;
  TNode<IntPtrT> phi_bb267_24;
  TNode<IntPtrT> phi_bb267_25;
  TNode<IntPtrT> phi_bb267_27;
  TNode<IntPtrT> phi_bb267_28;
  TNode<IntPtrT> phi_bb267_29;
  TNode<IntPtrT> phi_bb267_30;
  TNode<IntPtrT> phi_bb267_31;
  TNode<IntPtrT> phi_bb267_34;
  TNode<BoolT> phi_bb267_35;
  TNode<BoolT> phi_bb267_36;
  TNode<Union<FixedArray, Smi>> phi_bb267_37;
  TNode<IntPtrT> phi_bb267_40;
  TNode<RawPtrT> tmp489;
  TNode<IntPtrT> tmp490;
  TNode<BoolT> tmp491;
  if (block267.is_used()) {
    ca_.Bind(&block267, &phi_bb267_17, &phi_bb267_18, &phi_bb267_19, &phi_bb267_23, &phi_bb267_24, &phi_bb267_25, &phi_bb267_27, &phi_bb267_28, &phi_bb267_29, &phi_bb267_30, &phi_bb267_31, &phi_bb267_34, &phi_bb267_35, &phi_bb267_36, &phi_bb267_37, &phi_bb267_40);
    tmp489 = CodeStubAssembler(state_).GCUnsafeReferenceToRawPtr(TNode<Union<HeapObject, TaggedIndex>>{tmp193}, TNode<IntPtrT>{phi_bb267_40});
    tmp490 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp491 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp200}, TNode<IntPtrT>{tmp490});
    ca_.Branch(tmp491, &block271, std::vector<compiler::Node*>{phi_bb267_17, phi_bb267_18, phi_bb267_19, phi_bb267_23, phi_bb267_24, phi_bb267_25, phi_bb267_27, phi_bb267_28, phi_bb267_29, phi_bb267_30, phi_bb267_31, phi_bb267_34, phi_bb267_35, phi_bb267_36, phi_bb267_37}, &block272, std::vector<compiler::Node*>{phi_bb267_17, phi_bb267_18, phi_bb267_19, phi_bb267_23, phi_bb267_24, phi_bb267_25, phi_bb267_27, phi_bb267_28, phi_bb267_29, phi_bb267_30, phi_bb267_31, phi_bb267_34, phi_bb267_35, phi_bb267_36, phi_bb267_37});
  }

  TNode<JSAny> phi_bb271_17;
  TNode<IntPtrT> phi_bb271_18;
  TNode<BoolT> phi_bb271_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb271_23;
  TNode<IntPtrT> phi_bb271_24;
  TNode<IntPtrT> phi_bb271_25;
  TNode<IntPtrT> phi_bb271_27;
  TNode<IntPtrT> phi_bb271_28;
  TNode<IntPtrT> phi_bb271_29;
  TNode<IntPtrT> phi_bb271_30;
  TNode<IntPtrT> phi_bb271_31;
  TNode<IntPtrT> phi_bb271_34;
  TNode<BoolT> phi_bb271_35;
  TNode<BoolT> phi_bb271_36;
  TNode<Union<FixedArray, Smi>> phi_bb271_37;
  TNode<BoolT> tmp492;
  if (block271.is_used()) {
    ca_.Bind(&block271, &phi_bb271_17, &phi_bb271_18, &phi_bb271_19, &phi_bb271_23, &phi_bb271_24, &phi_bb271_25, &phi_bb271_27, &phi_bb271_28, &phi_bb271_29, &phi_bb271_30, &phi_bb271_31, &phi_bb271_34, &phi_bb271_35, &phi_bb271_36, &phi_bb271_37);
    tmp492 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block273, phi_bb271_17, phi_bb271_18, phi_bb271_19, phi_bb271_23, phi_bb271_24, phi_bb271_25, phi_bb271_27, phi_bb271_28, phi_bb271_29, phi_bb271_30, phi_bb271_31, phi_bb271_34, phi_bb271_35, phi_bb271_36, phi_bb271_37, tmp492);
  }

  TNode<JSAny> phi_bb272_17;
  TNode<IntPtrT> phi_bb272_18;
  TNode<BoolT> phi_bb272_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb272_23;
  TNode<IntPtrT> phi_bb272_24;
  TNode<IntPtrT> phi_bb272_25;
  TNode<IntPtrT> phi_bb272_27;
  TNode<IntPtrT> phi_bb272_28;
  TNode<IntPtrT> phi_bb272_29;
  TNode<IntPtrT> phi_bb272_30;
  TNode<IntPtrT> phi_bb272_31;
  TNode<IntPtrT> phi_bb272_34;
  TNode<BoolT> phi_bb272_35;
  TNode<BoolT> phi_bb272_36;
  TNode<Union<FixedArray, Smi>> phi_bb272_37;
  TNode<BoolT> tmp493;
  if (block272.is_used()) {
    ca_.Bind(&block272, &phi_bb272_17, &phi_bb272_18, &phi_bb272_19, &phi_bb272_23, &phi_bb272_24, &phi_bb272_25, &phi_bb272_27, &phi_bb272_28, &phi_bb272_29, &phi_bb272_30, &phi_bb272_31, &phi_bb272_34, &phi_bb272_35, &phi_bb272_36, &phi_bb272_37);
    tmp493 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb272_31}, TNode<IntPtrT>{tmp200});
    ca_.Goto(&block273, phi_bb272_17, phi_bb272_18, phi_bb272_19, phi_bb272_23, phi_bb272_24, phi_bb272_25, phi_bb272_27, phi_bb272_28, phi_bb272_29, phi_bb272_30, phi_bb272_31, phi_bb272_34, phi_bb272_35, phi_bb272_36, phi_bb272_37, tmp493);
  }

  TNode<JSAny> phi_bb273_17;
  TNode<IntPtrT> phi_bb273_18;
  TNode<BoolT> phi_bb273_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb273_23;
  TNode<IntPtrT> phi_bb273_24;
  TNode<IntPtrT> phi_bb273_25;
  TNode<IntPtrT> phi_bb273_27;
  TNode<IntPtrT> phi_bb273_28;
  TNode<IntPtrT> phi_bb273_29;
  TNode<IntPtrT> phi_bb273_30;
  TNode<IntPtrT> phi_bb273_31;
  TNode<IntPtrT> phi_bb273_34;
  TNode<BoolT> phi_bb273_35;
  TNode<BoolT> phi_bb273_36;
  TNode<Union<FixedArray, Smi>> phi_bb273_37;
  TNode<BoolT> phi_bb273_42;
  if (block273.is_used()) {
    ca_.Bind(&block273, &phi_bb273_17, &phi_bb273_18, &phi_bb273_19, &phi_bb273_23, &phi_bb273_24, &phi_bb273_25, &phi_bb273_27, &phi_bb273_28, &phi_bb273_29, &phi_bb273_30, &phi_bb273_31, &phi_bb273_34, &phi_bb273_35, &phi_bb273_36, &phi_bb273_37, &phi_bb273_42);
    ca_.Branch(phi_bb273_42, &block269, std::vector<compiler::Node*>{phi_bb273_17, phi_bb273_18, phi_bb273_19, phi_bb273_23, phi_bb273_24, phi_bb273_25, phi_bb273_27, phi_bb273_28, phi_bb273_29, phi_bb273_30, phi_bb273_31, phi_bb273_34, phi_bb273_35, phi_bb273_36, phi_bb273_37}, &block270, std::vector<compiler::Node*>{phi_bb273_17, phi_bb273_18, phi_bb273_19, phi_bb273_23, phi_bb273_24, phi_bb273_25, phi_bb273_27, phi_bb273_28, phi_bb273_29, phi_bb273_30, phi_bb273_31, phi_bb273_34, phi_bb273_35, phi_bb273_36, phi_bb273_37});
  }

  TNode<JSAny> phi_bb270_17;
  TNode<IntPtrT> phi_bb270_18;
  TNode<BoolT> phi_bb270_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb270_23;
  TNode<IntPtrT> phi_bb270_24;
  TNode<IntPtrT> phi_bb270_25;
  TNode<IntPtrT> phi_bb270_27;
  TNode<IntPtrT> phi_bb270_28;
  TNode<IntPtrT> phi_bb270_29;
  TNode<IntPtrT> phi_bb270_30;
  TNode<IntPtrT> phi_bb270_31;
  TNode<IntPtrT> phi_bb270_34;
  TNode<BoolT> phi_bb270_35;
  TNode<BoolT> phi_bb270_36;
  TNode<Union<FixedArray, Smi>> phi_bb270_37;
  if (block270.is_used()) {
    ca_.Bind(&block270, &phi_bb270_17, &phi_bb270_18, &phi_bb270_19, &phi_bb270_23, &phi_bb270_24, &phi_bb270_25, &phi_bb270_27, &phi_bb270_28, &phi_bb270_29, &phi_bb270_30, &phi_bb270_31, &phi_bb270_34, &phi_bb270_35, &phi_bb270_36, &phi_bb270_37);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 379});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.paramBufferEnd == 0 || this.nextStack <= this.paramBufferEnd' failed", pos_stack);
    }
  }

  TNode<JSAny> phi_bb269_17;
  TNode<IntPtrT> phi_bb269_18;
  TNode<BoolT> phi_bb269_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb269_23;
  TNode<IntPtrT> phi_bb269_24;
  TNode<IntPtrT> phi_bb269_25;
  TNode<IntPtrT> phi_bb269_27;
  TNode<IntPtrT> phi_bb269_28;
  TNode<IntPtrT> phi_bb269_29;
  TNode<IntPtrT> phi_bb269_30;
  TNode<IntPtrT> phi_bb269_31;
  TNode<IntPtrT> phi_bb269_34;
  TNode<BoolT> phi_bb269_35;
  TNode<BoolT> phi_bb269_36;
  TNode<Union<FixedArray, Smi>> phi_bb269_37;
  TNode<WasmInternalFunction> tmp494;
  TNode<IntPtrT> tmp495;
  TNode<Uint32T> tmp496;
  TNode<RawPtrT> tmp497;
  TNode<RawPtrT> tmp498;
  TNode<IntPtrT> tmp499;
  TNode<Union<HeapObject, TaggedIndex>> tmp500;
  TNode<IntPtrT> tmp501;
  TNode<Int32T> tmp502;
  TNode<IntPtrT> tmp503;
  TNode<Union<HeapObject, TaggedIndex>> tmp504;
  TNode<IntPtrT> tmp505;
  TNode<IntPtrT> tmp506;
  TNode<Union<HeapObject, TaggedIndex>> tmp507;
  TNode<IntPtrT> tmp508;
  TNode<IntPtrT> tmp509;
  TNode<Union<HeapObject, TaggedIndex>> tmp510;
  TNode<IntPtrT> tmp511;
  TNode<IntPtrT> tmp512;
  TNode<Union<HeapObject, TaggedIndex>> tmp513;
  TNode<IntPtrT> tmp514;
  TNode<IntPtrT> tmp515;
  TNode<Union<HeapObject, TaggedIndex>> tmp516;
  TNode<IntPtrT> tmp517;
  TNode<IntPtrT> tmp518;
  TNode<Union<HeapObject, TaggedIndex>> tmp519;
  TNode<IntPtrT> tmp520;
  if (block269.is_used()) {
    ca_.Bind(&block269, &phi_bb269_17, &phi_bb269_18, &phi_bb269_19, &phi_bb269_23, &phi_bb269_24, &phi_bb269_25, &phi_bb269_27, &phi_bb269_28, &phi_bb269_29, &phi_bb269_30, &phi_bb269_31, &phi_bb269_34, &phi_bb269_35, &phi_bb269_36, &phi_bb269_37);
    tmp494 = CodeStubAssembler(state_).LoadWasmInternalFunctionFromFunctionData(TNode<WasmFunctionData>{tmp2});
    tmp495 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp496 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp494, tmp495});
    tmp497 = CodeStubAssembler(state_).StackSlotPtr(JSToWasmWrapperFrameConstants::kWrapperBufferSize, CastIfEnumClass<int32_t>((SizeOf_intptr_0(state_))));
    tmp498 = (TNode<RawPtrT>{tmp497});
    tmp499 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferReturnCount);
    std::tie(tmp500, tmp501) = GetRefAt_int32_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp499}).Flatten();
    tmp502 = CodeStubAssembler(state_).TruncateIntPtrToInt32(TNode<IntPtrT>{tmp28});
    CodeStubAssembler(state_).StoreReference<Int32T>(CodeStubAssembler::Reference{tmp500, tmp501}, tmp502);
    tmp503 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferRefReturnCount);
    std::tie(tmp504, tmp505) = GetRefAt_bool_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp503}).Flatten();
    CodeStubAssembler(state_).StoreReference<BoolT>(CodeStubAssembler::Reference{tmp504, tmp505}, phi_bb269_19);
    tmp506 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferSigRepresentationArray);
    std::tie(tmp507, tmp508) = GetRefAt_RawPtr_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp506}).Flatten();
    CodeStubAssembler(state_).StoreReference<RawPtrT>(CodeStubAssembler::Reference{tmp507, tmp508}, tmp32);
    tmp509 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferStackReturnBufferSize);
    std::tie(tmp510, tmp511) = GetRefAt_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp509}).Flatten();
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{tmp510, tmp511}, phi_bb269_18);
    tmp512 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferCallTarget);
    std::tie(tmp513, tmp514) = GetRefAt_WasmCodePointer_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp512}).Flatten();
    CodeStubAssembler(state_).StoreReference<Uint32T>(CodeStubAssembler::Reference{tmp513, tmp514}, tmp496);
    tmp515 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferParamStart);
    std::tie(tmp516, tmp517) = GetRefAt_RawPtr_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp515}).Flatten();
    CodeStubAssembler(state_).StoreReference<RawPtrT>(CodeStubAssembler::Reference{tmp516, tmp517}, tmp486);
    tmp518 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferParamEnd);
    std::tie(tmp519, tmp520) = GetRefAt_RawPtr_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp498}, TNode<IntPtrT>{tmp518}).Flatten();
    CodeStubAssembler(state_).StoreReference<RawPtrT>(CodeStubAssembler::Reference{tmp519, tmp520}, tmp489);
    if (((CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kPromise))))) {
      ca_.Goto(&block274, phi_bb269_17, phi_bb269_18, phi_bb269_19, phi_bb269_23, phi_bb269_24, phi_bb269_25, phi_bb269_27, phi_bb269_28, phi_bb269_29, phi_bb269_30, phi_bb269_31, phi_bb269_34, phi_bb269_35, phi_bb269_36, phi_bb269_37);
    } else {
      ca_.Goto(&block275, phi_bb269_17, phi_bb269_18, phi_bb269_19, phi_bb269_23, phi_bb269_24, phi_bb269_25, phi_bb269_27, phi_bb269_28, phi_bb269_29, phi_bb269_30, phi_bb269_31, phi_bb269_34, phi_bb269_35, phi_bb269_36, phi_bb269_37);
    }
  }

  TNode<JSAny> phi_bb274_17;
  TNode<IntPtrT> phi_bb274_18;
  TNode<BoolT> phi_bb274_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb274_23;
  TNode<IntPtrT> phi_bb274_24;
  TNode<IntPtrT> phi_bb274_25;
  TNode<IntPtrT> phi_bb274_27;
  TNode<IntPtrT> phi_bb274_28;
  TNode<IntPtrT> phi_bb274_29;
  TNode<IntPtrT> phi_bb274_30;
  TNode<IntPtrT> phi_bb274_31;
  TNode<IntPtrT> phi_bb274_34;
  TNode<BoolT> phi_bb274_35;
  TNode<BoolT> phi_bb274_36;
  TNode<Union<FixedArray, Smi>> phi_bb274_37;
  TNode<JSAny> tmp521;
  if (block274.is_used()) {
    ca_.Bind(&block274, &phi_bb274_17, &phi_bb274_18, &phi_bb274_19, &phi_bb274_23, &phi_bb274_24, &phi_bb274_25, &phi_bb274_27, &phi_bb274_28, &phi_bb274_29, &phi_bb274_30, &phi_bb274_31, &phi_bb274_34, &phi_bb274_35, &phi_bb274_36, &phi_bb274_37);
    tmp521 = ca_.CallBuiltin<JSAny>(Builtin::kWasmReturnPromiseOnSuspendAsm, TNode<Object>(), tmp498, tmp20, phi_bb274_17);
    ca_.Goto(&block276, phi_bb274_17, phi_bb274_18, phi_bb274_19, phi_bb274_23, phi_bb274_24, phi_bb274_25, phi_bb274_27, phi_bb274_28, phi_bb274_29, phi_bb274_30, phi_bb274_31, phi_bb274_34, phi_bb274_35, phi_bb274_36, phi_bb274_37, tmp521);
  }

  TNode<JSAny> phi_bb275_17;
  TNode<IntPtrT> phi_bb275_18;
  TNode<BoolT> phi_bb275_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb275_23;
  TNode<IntPtrT> phi_bb275_24;
  TNode<IntPtrT> phi_bb275_25;
  TNode<IntPtrT> phi_bb275_27;
  TNode<IntPtrT> phi_bb275_28;
  TNode<IntPtrT> phi_bb275_29;
  TNode<IntPtrT> phi_bb275_30;
  TNode<IntPtrT> phi_bb275_31;
  TNode<IntPtrT> phi_bb275_34;
  TNode<BoolT> phi_bb275_35;
  TNode<BoolT> phi_bb275_36;
  TNode<Union<FixedArray, Smi>> phi_bb275_37;
  TNode<BoolT> tmp522;
  if (block275.is_used()) {
    ca_.Bind(&block275, &phi_bb275_17, &phi_bb275_18, &phi_bb275_19, &phi_bb275_23, &phi_bb275_24, &phi_bb275_25, &phi_bb275_27, &phi_bb275_28, &phi_bb275_29, &phi_bb275_30, &phi_bb275_31, &phi_bb275_34, &phi_bb275_35, &phi_bb275_36, &phi_bb275_37);
    tmp522 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kNoPromise))));
    ca_.Branch(tmp522, &block277, std::vector<compiler::Node*>{phi_bb275_17, phi_bb275_18, phi_bb275_19, phi_bb275_23, phi_bb275_24, phi_bb275_25, phi_bb275_27, phi_bb275_28, phi_bb275_29, phi_bb275_30, phi_bb275_31, phi_bb275_34, phi_bb275_35, phi_bb275_36, phi_bb275_37}, &block278, std::vector<compiler::Node*>{phi_bb275_17, phi_bb275_18, phi_bb275_19, phi_bb275_23, phi_bb275_24, phi_bb275_25, phi_bb275_27, phi_bb275_28, phi_bb275_29, phi_bb275_30, phi_bb275_31, phi_bb275_34, phi_bb275_35, phi_bb275_36, phi_bb275_37});
  }

  TNode<JSAny> phi_bb277_17;
  TNode<IntPtrT> phi_bb277_18;
  TNode<BoolT> phi_bb277_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb277_23;
  TNode<IntPtrT> phi_bb277_24;
  TNode<IntPtrT> phi_bb277_25;
  TNode<IntPtrT> phi_bb277_27;
  TNode<IntPtrT> phi_bb277_28;
  TNode<IntPtrT> phi_bb277_29;
  TNode<IntPtrT> phi_bb277_30;
  TNode<IntPtrT> phi_bb277_31;
  TNode<IntPtrT> phi_bb277_34;
  TNode<BoolT> phi_bb277_35;
  TNode<BoolT> phi_bb277_36;
  TNode<Union<FixedArray, Smi>> phi_bb277_37;
  TNode<JSAny> tmp523;
  if (block277.is_used()) {
    ca_.Bind(&block277, &phi_bb277_17, &phi_bb277_18, &phi_bb277_19, &phi_bb277_23, &phi_bb277_24, &phi_bb277_25, &phi_bb277_27, &phi_bb277_28, &phi_bb277_29, &phi_bb277_30, &phi_bb277_31, &phi_bb277_34, &phi_bb277_35, &phi_bb277_36, &phi_bb277_37);
    tmp523 = ca_.CallBuiltin<JSAny>(Builtin::kJSToWasmWrapperAsm, TNode<Object>(), tmp498, tmp20, phi_bb277_17);
    ca_.Goto(&block279, phi_bb277_17, phi_bb277_18, phi_bb277_19, phi_bb277_23, phi_bb277_24, phi_bb277_25, phi_bb277_27, phi_bb277_28, phi_bb277_29, phi_bb277_30, phi_bb277_31, phi_bb277_34, phi_bb277_35, phi_bb277_36, phi_bb277_37, tmp523);
  }

  TNode<JSAny> phi_bb278_17;
  TNode<IntPtrT> phi_bb278_18;
  TNode<BoolT> phi_bb278_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb278_23;
  TNode<IntPtrT> phi_bb278_24;
  TNode<IntPtrT> phi_bb278_25;
  TNode<IntPtrT> phi_bb278_27;
  TNode<IntPtrT> phi_bb278_28;
  TNode<IntPtrT> phi_bb278_29;
  TNode<IntPtrT> phi_bb278_30;
  TNode<IntPtrT> phi_bb278_31;
  TNode<IntPtrT> phi_bb278_34;
  TNode<BoolT> phi_bb278_35;
  TNode<BoolT> phi_bb278_36;
  TNode<Union<FixedArray, Smi>> phi_bb278_37;
  TNode<BoolT> tmp524;
  if (block278.is_used()) {
    ca_.Bind(&block278, &phi_bb278_17, &phi_bb278_18, &phi_bb278_19, &phi_bb278_23, &phi_bb278_24, &phi_bb278_25, &phi_bb278_27, &phi_bb278_28, &phi_bb278_29, &phi_bb278_30, &phi_bb278_31, &phi_bb278_34, &phi_bb278_35, &phi_bb278_36, &phi_bb278_37);
    tmp524 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt32Equal(CastIfEnumClass<int32_t>(p_promise), CastIfEnumClass<int32_t>(wasm::Promise::kStressSwitch))));
    ca_.Branch(tmp524, &block280, std::vector<compiler::Node*>{phi_bb278_17, phi_bb278_18, phi_bb278_19, phi_bb278_23, phi_bb278_24, phi_bb278_25, phi_bb278_27, phi_bb278_28, phi_bb278_29, phi_bb278_30, phi_bb278_31, phi_bb278_34, phi_bb278_35, phi_bb278_36, phi_bb278_37}, &block281, std::vector<compiler::Node*>{phi_bb278_17, phi_bb278_18, phi_bb278_19, phi_bb278_23, phi_bb278_24, phi_bb278_25, phi_bb278_27, phi_bb278_28, phi_bb278_29, phi_bb278_30, phi_bb278_31, phi_bb278_34, phi_bb278_35, phi_bb278_36, phi_bb278_37});
  }

  TNode<JSAny> phi_bb280_17;
  TNode<IntPtrT> phi_bb280_18;
  TNode<BoolT> phi_bb280_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb280_23;
  TNode<IntPtrT> phi_bb280_24;
  TNode<IntPtrT> phi_bb280_25;
  TNode<IntPtrT> phi_bb280_27;
  TNode<IntPtrT> phi_bb280_28;
  TNode<IntPtrT> phi_bb280_29;
  TNode<IntPtrT> phi_bb280_30;
  TNode<IntPtrT> phi_bb280_31;
  TNode<IntPtrT> phi_bb280_34;
  TNode<BoolT> phi_bb280_35;
  TNode<BoolT> phi_bb280_36;
  TNode<Union<FixedArray, Smi>> phi_bb280_37;
  TNode<JSAny> tmp525;
  if (block280.is_used()) {
    ca_.Bind(&block280, &phi_bb280_17, &phi_bb280_18, &phi_bb280_19, &phi_bb280_23, &phi_bb280_24, &phi_bb280_25, &phi_bb280_27, &phi_bb280_28, &phi_bb280_29, &phi_bb280_30, &phi_bb280_31, &phi_bb280_34, &phi_bb280_35, &phi_bb280_36, &phi_bb280_37);
    tmp525 = ca_.CallBuiltin<JSAny>(Builtin::kJSToWasmStressSwitchStacksAsm, TNode<Object>(), tmp498, tmp20, phi_bb280_17);
    ca_.Goto(&block279, phi_bb280_17, phi_bb280_18, phi_bb280_19, phi_bb280_23, phi_bb280_24, phi_bb280_25, phi_bb280_27, phi_bb280_28, phi_bb280_29, phi_bb280_30, phi_bb280_31, phi_bb280_34, phi_bb280_35, phi_bb280_36, phi_bb280_37, tmp525);
  }

  TNode<JSAny> phi_bb281_17;
  TNode<IntPtrT> phi_bb281_18;
  TNode<BoolT> phi_bb281_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb281_23;
  TNode<IntPtrT> phi_bb281_24;
  TNode<IntPtrT> phi_bb281_25;
  TNode<IntPtrT> phi_bb281_27;
  TNode<IntPtrT> phi_bb281_28;
  TNode<IntPtrT> phi_bb281_29;
  TNode<IntPtrT> phi_bb281_30;
  TNode<IntPtrT> phi_bb281_31;
  TNode<IntPtrT> phi_bb281_34;
  TNode<BoolT> phi_bb281_35;
  TNode<BoolT> phi_bb281_36;
  TNode<Union<FixedArray, Smi>> phi_bb281_37;
  if (block281.is_used()) {
    ca_.Bind(&block281, &phi_bb281_17, &phi_bb281_18, &phi_bb281_19, &phi_bb281_23, &phi_bb281_24, &phi_bb281_25, &phi_bb281_27, &phi_bb281_28, &phi_bb281_29, &phi_bb281_30, &phi_bb281_31, &phi_bb281_34, &phi_bb281_35, &phi_bb281_36, &phi_bb281_37);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/js-to-wasm.tq:821:5");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> phi_bb279_17;
  TNode<IntPtrT> phi_bb279_18;
  TNode<BoolT> phi_bb279_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb279_23;
  TNode<IntPtrT> phi_bb279_24;
  TNode<IntPtrT> phi_bb279_25;
  TNode<IntPtrT> phi_bb279_27;
  TNode<IntPtrT> phi_bb279_28;
  TNode<IntPtrT> phi_bb279_29;
  TNode<IntPtrT> phi_bb279_30;
  TNode<IntPtrT> phi_bb279_31;
  TNode<IntPtrT> phi_bb279_34;
  TNode<BoolT> phi_bb279_35;
  TNode<BoolT> phi_bb279_36;
  TNode<Union<FixedArray, Smi>> phi_bb279_37;
  TNode<JSAny> phi_bb279_43;
  if (block279.is_used()) {
    ca_.Bind(&block279, &phi_bb279_17, &phi_bb279_18, &phi_bb279_19, &phi_bb279_23, &phi_bb279_24, &phi_bb279_25, &phi_bb279_27, &phi_bb279_28, &phi_bb279_29, &phi_bb279_30, &phi_bb279_31, &phi_bb279_34, &phi_bb279_35, &phi_bb279_36, &phi_bb279_37, &phi_bb279_43);
    ca_.Goto(&block276, phi_bb279_17, phi_bb279_18, phi_bb279_19, phi_bb279_23, phi_bb279_24, phi_bb279_25, phi_bb279_27, phi_bb279_28, phi_bb279_29, phi_bb279_30, phi_bb279_31, phi_bb279_34, phi_bb279_35, phi_bb279_36, phi_bb279_37, phi_bb279_43);
  }

  TNode<JSAny> phi_bb276_17;
  TNode<IntPtrT> phi_bb276_18;
  TNode<BoolT> phi_bb276_19;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb276_23;
  TNode<IntPtrT> phi_bb276_24;
  TNode<IntPtrT> phi_bb276_25;
  TNode<IntPtrT> phi_bb276_27;
  TNode<IntPtrT> phi_bb276_28;
  TNode<IntPtrT> phi_bb276_29;
  TNode<IntPtrT> phi_bb276_30;
  TNode<IntPtrT> phi_bb276_31;
  TNode<IntPtrT> phi_bb276_34;
  TNode<BoolT> phi_bb276_35;
  TNode<BoolT> phi_bb276_36;
  TNode<Union<FixedArray, Smi>> phi_bb276_37;
  TNode<JSAny> phi_bb276_43;
  if (block276.is_used()) {
    ca_.Bind(&block276, &phi_bb276_17, &phi_bb276_18, &phi_bb276_19, &phi_bb276_23, &phi_bb276_24, &phi_bb276_25, &phi_bb276_27, &phi_bb276_28, &phi_bb276_29, &phi_bb276_30, &phi_bb276_31, &phi_bb276_34, &phi_bb276_35, &phi_bb276_36, &phi_bb276_37, &phi_bb276_43);
    ca_.Goto(&block283, phi_bb276_43);
  }

  TNode<JSAny> phi_bb283_7;
    ca_.Bind(&block283, &phi_bb283_7);
  return TNode<JSAny>{phi_bb283_7};
}

TF_BUILTIN(JSToWasmWrapper, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSDispatchHandleT> parameter3 = UncheckedParameter<JSDispatchHandleT>(Descriptor::kJSDispatchHandle);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).SetSupportsDynamicParameterCount(TNode<JSFunction>{parameter2}, TNode<JSDispatchHandleT>{parameter3});
    tmp0 = JSToWasmWrapperHelper_0(state_, TNode<NativeContext>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSFunction>{parameter2}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, CastIfEnumClass<wasm::Promise>(wasm::Promise::kNoPromise));
    arguments.PopAndReturn(tmp0);
  }
}

TF_BUILTIN(WasmPromising, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSDispatchHandleT> parameter3 = UncheckedParameter<JSDispatchHandleT>(Descriptor::kJSDispatchHandle);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).SetSupportsDynamicParameterCount(TNode<JSFunction>{parameter2}, TNode<JSDispatchHandleT>{parameter3});
    tmp0 = JSToWasmWrapperHelper_0(state_, TNode<NativeContext>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSFunction>{parameter2}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, CastIfEnumClass<wasm::Promise>(wasm::Promise::kPromise));
    arguments.PopAndReturn(tmp0);
  }
}

TF_BUILTIN(WasmStressSwitch, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Word32T> argc = UncheckedParameter<Word32T>(Descriptor::kJSActualArgumentsCount);
  TNode<IntPtrT> arguments_length(ChangeInt32ToIntPtr(UncheckedCast<Int32T>(argc)));
  TNode<RawPtrT> arguments_frame = UncheckedCast<RawPtrT>(LoadFramePointer());
  TorqueStructArguments torque_arguments(GetFrameArguments(arguments_frame, arguments_length, FrameArgumentsArgcType::kCountIncludesReceiver));
  CodeStubArguments arguments(this, torque_arguments);
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = arguments.GetReceiver();
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSDispatchHandleT> parameter3 = UncheckedParameter<JSDispatchHandleT>(Descriptor::kJSDispatchHandle);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    CodeStubAssembler(state_).SetSupportsDynamicParameterCount(TNode<JSFunction>{parameter2}, TNode<JSDispatchHandleT>{parameter3});
    tmp0 = JSToWasmWrapperHelper_0(state_, TNode<NativeContext>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSFunction>{parameter2}, TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, CastIfEnumClass<wasm::Promise>(wasm::Promise::kStressSwitch));
    arguments.PopAndReturn(tmp0);
  }
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=860&c=1
TNode<JSAny> WasmToJSObject_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<Object> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<WasmNull> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kWasmNull_0(state_);
    tmp1 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{p_value}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<Null> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = Null_0(state_);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = Is_WasmFuncRef_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_value});
    ca_.Branch(tmp3, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<WasmFuncRef> tmp4;
  TNode<WasmInternalFunction> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Union<JSFunction, Undefined>> tmp7;
  TNode<BoolT> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = UnsafeCast_WasmFuncRef_0(state_, TNode<Context>{p_context}, TNode<Object>{p_value});
    tmp5 = CodeStubAssembler(state_).LoadWasmInternalFunctionFromFuncRef(TNode<WasmFuncRef>{tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp7 = CodeStubAssembler(state_).LoadReference<Union<JSFunction, Undefined>>(CodeStubAssembler::Reference{tmp5, tmp6});
    tmp8 = Is_JSFunction_Undefined_OR_JSFunction_0(state_, TNode<Context>{p_context}, TNode<Union<JSFunction, Undefined>>{tmp7});
    ca_.Branch(tmp8, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<JSFunction> tmp9;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp9 = UnsafeCast_JSFunction_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp7});
    ca_.Goto(&block1, tmp9);
  }

  TNode<JSAny> tmp10;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kWasmWasmToJSObject, p_context, p_value)); 
    ca_.Goto(&block1, tmp10);
  }

  TNode<BoolT> tmp11;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp11 = Is_String_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_value});
    ca_.Branch(tmp11, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp12;
  TNode<BoolT> tmp13;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp12 = UnsafeCast_String_0(state_, TNode<Context>{p_context}, TNode<Object>{p_value});
    tmp13 = WasmBuiltinsAssembler(state_).InSharedSpace(TNode<HeapObject>{tmp12});
    ca_.Goto(&block13, tmp13);
  }

  TNode<BoolT> tmp14;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp14 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block13, tmp14);
  }

  TNode<BoolT> phi_bb13_3;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_3);
    ca_.Branch(phi_bb13_3, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kWasmWasmToJSObject, p_context, p_value)); 
    ca_.Goto(&block1, tmp15);
  }

  TNode<JSAny> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp16 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{p_value});
    ca_.Goto(&block1, tmp16);
  }

  TNode<JSAny> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block14, phi_bb1_2);
  }

  TNode<JSAny> phi_bb14_2;
    ca_.Bind(&block14, &phi_bb14_2);
  return TNode<JSAny>{phi_bb14_2};
}

TF_BUILTIN(JSToWasmHandleReturns, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kJsContext);
  USE(parameter0);
  TNode<JSArray> parameter1 = UncheckedParameter<JSArray>(Descriptor::kResultArray);
  USE(parameter1);
  TNode<RawPtrT> parameter2 = UncheckedParameter<RawPtrT>(Descriptor::kWrapperBuffer);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Int32T> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block96(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block91(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block97(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block100(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block99(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block98(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block122(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block123(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block125(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block124(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block140(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block139(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block146(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block144(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block154(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block156(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block157(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block161(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Int32T> block163(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block168(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block172(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block177(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block179(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block180(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block178(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block187(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block185(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block191(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block194(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block197(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block193(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block202(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block203(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block173(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block206(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block209(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block213(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block214(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block217(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block219(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block220(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block215(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block212(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block225(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block226(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block210(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block230(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block231(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block233(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block234(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block236(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block237(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block232(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block229(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block239(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block240(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block242(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block243(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block245(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block246(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block241(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block238(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block251(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block252(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block211(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block207(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block255(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block259(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block260(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block261(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block265(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block266(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block268(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block269(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block264(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block262(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block258(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block274(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block275(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block256(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block279(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block278(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block284(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block285(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block292(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block293(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block257(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block208(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block174(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT> block145(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block299(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block300(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block301(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block298(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT> block297(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Int32T> tmp3;
  TNode<Int32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferReturnCount);
    std::tie(tmp1, tmp2) = GetRefAt_int32_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Int32T>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = FromConstexpr_int32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).Word32Equal(TNode<Int32T>{tmp3}, TNode<Int32T>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp6;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp6 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp6);
  }

  TNode<Int32T> tmp7;
  TNode<BoolT> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp7 = FromConstexpr_int32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp8 = CodeStubAssembler(state_).Word32Equal(TNode<Int32T>{tmp3}, TNode<Int32T>{tmp7});
    ca_.Branch(tmp8, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp9;
  TNode<Union<HeapObject, TaggedIndex>> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<RawPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Union<HeapObject, TaggedIndex>> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<Uint32T> tmp16;
  TNode<Uint32T> tmp17;
  TNode<BoolT> tmp18;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp9 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferSigRepresentationArray);
    std::tie(tmp10, tmp11) = GetRefAt_RawPtr_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp9}).Flatten();
    tmp12 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{tmp10, tmp11});
    tmp13 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp14, tmp15) = GetRefAt_uint32_RawPtr_0(state_, TNode<RawPtrT>{tmp12}, TNode<IntPtrT>{tmp13}).Flatten();
    tmp16 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp14, tmp15});
    tmp17 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp18 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp16}, TNode<Uint32T>{tmp17});
    ca_.Branch(tmp18, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    if ((wasm::kIsBigEndian)) {
      ca_.Goto(&block8);
    } else {
      ca_.Goto(&block9);
    }
  }

  TNode<IntPtrT> tmp19;
  TNode<Union<HeapObject, TaggedIndex>> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Int64T> tmp22;
  TNode<Int32T> tmp23;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp19 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    std::tie(tmp20, tmp21) = GetRefAt_int64_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp19}).Flatten();
    tmp22 = CodeStubAssembler(state_).LoadReference<Int64T>(CodeStubAssembler::Reference{tmp20, tmp21});
    tmp23 = CodeStubAssembler(state_).TruncateInt64ToInt32(TNode<Int64T>{tmp22});
    ca_.Goto(&block10, tmp23);
  }

  TNode<IntPtrT> tmp24;
  TNode<Union<HeapObject, TaggedIndex>> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<Int32T> tmp27;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp24 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    std::tie(tmp25, tmp26) = GetRefAt_int32_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp24}).Flatten();
    tmp27 = CodeStubAssembler(state_).LoadReference<Int32T>(CodeStubAssembler::Reference{tmp25, tmp26});
    ca_.Goto(&block10, tmp27);
  }

  TNode<Int32T> phi_bb10_6;
  TNode<Number> tmp28;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_6);
    tmp28 = Convert_Number_int32_0(state_, TNode<Int32T>{phi_bb10_6});
    CodeStubAssembler(state_).Return(tmp28);
  }

  TNode<Uint32T> tmp29;
  TNode<BoolT> tmp30;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp29 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp30 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp16}, TNode<Uint32T>{tmp29});
    ca_.Branch(tmp30, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    if ((wasm::kIsFpAlwaysDouble)) {
      ca_.Goto(&block14);
    } else {
      ca_.Goto(&block15);
    }
  }

  TNode<IntPtrT> tmp31;
  TNode<Union<HeapObject, TaggedIndex>> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<Float64T> tmp34;
  TNode<Float32T> tmp35;
  TNode<Number> tmp36;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp31 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferFPReturnRegister1);
    std::tie(tmp32, tmp33) = GetRefAt_float64_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp31}).Flatten();
    tmp34 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp32, tmp33});
    tmp35 = CodeStubAssembler(state_).TruncateFloat64ToFloat32(TNode<Float64T>{tmp34});
    tmp36 = Convert_Number_float32_0(state_, TNode<Float32T>{tmp35});
    CodeStubAssembler(state_).Return(tmp36);
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    if ((wasm::kIsBigEndianOnSim)) {
      ca_.Goto(&block17);
    } else {
      ca_.Goto(&block18);
    }
  }

  TNode<IntPtrT> tmp37;
  TNode<Union<HeapObject, TaggedIndex>> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Int64T> tmp40;
  TNode<Int64T> tmp41;
  TNode<Int64T> tmp42;
  TNode<Int32T> tmp43;
  TNode<Float32T> tmp44;
  TNode<Number> tmp45;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp37 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferFPReturnRegister1);
    std::tie(tmp38, tmp39) = GetRefAt_int64_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp37}).Flatten();
    tmp40 = CodeStubAssembler(state_).LoadReference<Int64T>(CodeStubAssembler::Reference{tmp38, tmp39});
    tmp41 = FromConstexpr_int64_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp42 = CodeStubAssembler(state_).Word64Sar(TNode<Int64T>{tmp40}, TNode<Int64T>{tmp41});
    tmp43 = CodeStubAssembler(state_).TruncateInt64ToInt32(TNode<Int64T>{tmp42});
    tmp44 = CodeStubAssembler(state_).BitcastInt32ToFloat32(TNode<Int32T>{tmp43});
    tmp45 = Convert_Number_float32_0(state_, TNode<Float32T>{tmp44});
    CodeStubAssembler(state_).Return(tmp45);
  }

  TNode<IntPtrT> tmp46;
  TNode<Union<HeapObject, TaggedIndex>> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<Float32T> tmp49;
  TNode<Number> tmp50;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp46 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferFPReturnRegister1);
    std::tie(tmp47, tmp48) = GetRefAt_float32_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp46}).Flatten();
    tmp49 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp47, tmp48});
    tmp50 = Convert_Number_float32_0(state_, TNode<Float32T>{tmp49});
    CodeStubAssembler(state_).Return(tmp50);
  }

  TNode<Uint32T> tmp51;
  TNode<BoolT> tmp52;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp51 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp52 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp16}, TNode<Uint32T>{tmp51});
    ca_.Branch(tmp52, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp53;
  TNode<Union<HeapObject, TaggedIndex>> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<Float64T> tmp56;
  TNode<Number> tmp57;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp53 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferFPReturnRegister1);
    std::tie(tmp54, tmp55) = GetRefAt_float64_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp53}).Flatten();
    tmp56 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp54, tmp55});
    tmp57 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp56});
    CodeStubAssembler(state_).Return(tmp57);
  }

  TNode<Uint32T> tmp58;
  TNode<BoolT> tmp59;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp58 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp59 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp16}, TNode<Uint32T>{tmp58});
    ca_.Branch(tmp59, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block26);
    } else {
      ca_.Goto(&block27);
    }
  }

  TNode<IntPtrT> tmp60;
  TNode<Union<HeapObject, TaggedIndex>> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<BigInt> tmp64;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp60 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    std::tie(tmp61, tmp62) = GetRefAt_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp60}).Flatten();
    tmp63 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp61, tmp62});
    tmp64 = ca_.CallBuiltin<BigInt>(Builtin::kI64ToBigInt, TNode<Object>(), tmp63);
    CodeStubAssembler(state_).Return(tmp64);
  }

  TNode<IntPtrT> tmp65;
  TNode<Union<HeapObject, TaggedIndex>> tmp66;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<Union<HeapObject, TaggedIndex>> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<BigInt> tmp73;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp65 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    std::tie(tmp66, tmp67) = GetRefAt_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp65}).Flatten();
    tmp68 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp66, tmp67});
    tmp69 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister2);
    std::tie(tmp70, tmp71) = GetRefAt_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp69}).Flatten();
    tmp72 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp70, tmp71});
    tmp73 = ca_.CallBuiltin<BigInt>(Builtin::kI32PairToBigInt, TNode<Object>(), tmp68, tmp72);
    CodeStubAssembler(state_).Return(tmp73);
  }

  TNode<Uint32T> tmp74;
  TNode<Uint32T> tmp75;
  TNode<Uint32T> tmp76;
  TNode<BoolT> tmp77;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp74 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp75 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp16}, TNode<Uint32T>{tmp74});
    tmp76 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp77 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp75}, TNode<Uint32T>{tmp76});
    ca_.Branch(tmp77, &block29, std::vector<compiler::Node*>{}, &block30, std::vector<compiler::Node*>{});
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 935});
      CodeStubAssembler(state_).FailAssert("Torque assert '(retType & kValueTypeIsRefBit) != 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp78;
  TNode<RawPtrT> tmp79;
  TNode<RawPtrT> tmp80;
  TNode<IntPtrT> tmp81;
  TNode<Union<HeapObject, TaggedIndex>> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<UintPtrT> tmp84;
  TNode<Object> tmp85;
  TNode<JSAny> tmp86;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp78 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    tmp79 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp78});
    tmp80 = (TNode<RawPtrT>{tmp79});
    tmp81 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp82, tmp83) = GetRefAt_uintptr_RawPtr_uintptr_0(state_, TNode<RawPtrT>{tmp80}, TNode<IntPtrT>{tmp81}).Flatten();
    tmp84 = CodeStubAssembler(state_).LoadReference<UintPtrT>(CodeStubAssembler::Reference{tmp82, tmp83});
    tmp85 = CodeStubAssembler(state_).BitcastWordToTagged(TNode<UintPtrT>{tmp84});
    tmp86 = WasmToJSObject_0(state_, TNode<NativeContext>{parameter0}, TNode<Object>{tmp85});
    CodeStubAssembler(state_).Return(tmp86);
  }

  TNode<IntPtrT> tmp87;
  TNode<FixedArrayBase> tmp88;
  TNode<HeapObject> tmp89;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp87 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp88 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{parameter1, tmp87});
    compiler::CodeAssemblerLabel label90(&ca_);
    tmp89 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{tmp88}, &label90);
    ca_.Goto(&block38);
    if (label90.is_used()) {
      ca_.Bind(&label90);
      ca_.Goto(&block39);
    }
  }

  if (block39.is_used()) {
    ca_.Bind(&block39);
    ca_.Goto(&block36);
  }

  TNode<FixedArray> tmp91;
  if (block38.is_used()) {
    ca_.Bind(&block38);
    compiler::CodeAssemblerLabel label92(&ca_);
    tmp91 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp89}, &label92);
    ca_.Goto(&block40);
    if (label92.is_used()) {
      ca_.Bind(&label92);
      ca_.Goto(&block41);
    }
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    ca_.Goto(&block36);
  }

  TNode<BoolT> tmp93;
  if (block40.is_used()) {
    ca_.Bind(&block40);
    tmp93 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block34, tmp93);
  }

  TNode<BoolT> tmp94;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp94 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block34, tmp94);
  }

  TNode<BoolT> phi_bb34_8;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_8);
    ca_.Branch(phi_bb34_8, &block32, std::vector<compiler::Node*>{}, &block33, std::vector<compiler::Node*>{});
  }

  if (block33.is_used()) {
    ca_.Bind(&block33);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<FixedArray> tmp95;
  TNode<IntPtrT> tmp96;
  TNode<Union<HeapObject, TaggedIndex>> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<RawPtrT> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<RawPtrT> tmp101;
  TNode<IntPtrT> tmp102;
  TNode<RawPtrT> tmp103;
  TNode<Union<HeapObject, TaggedIndex>> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<IntPtrT> tmp110;
  TNode<IntPtrT> tmp111;
  TNode<IntPtrT> tmp112;
  TNode<BoolT> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<Union<HeapObject, TaggedIndex>> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<RawPtrT> tmp117;
  TNode<RawPtrT> tmp118;
  TNode<IntPtrT> tmp119;
  TNode<Union<HeapObject, TaggedIndex>> tmp120;
  TNode<IntPtrT> tmp121;
  TNode<IntPtrT> tmp122;
  TNode<IntPtrT> tmp123;
  TNode<Union<HeapObject, TaggedIndex>> tmp124;
  TNode<IntPtrT> tmp125;
  TNode<BoolT> tmp126;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp95 = TORQUE_CAST(TNode<Object>{tmp88});
    tmp96 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferStackReturnBufferStart);
    std::tie(tmp97, tmp98) = GetRefAt_RawPtr_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp96}).Flatten();
    tmp99 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{tmp97, tmp98});
    tmp100 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    tmp101 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp100});
    tmp102 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferFPReturnRegister1);
    tmp103 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp102});
    std::tie(tmp104, tmp105, tmp106, tmp107, tmp108, tmp109, tmp110, tmp111, tmp112, tmp113) = LocationAllocatorForReturns_0(state_, TNode<RawPtrT>{tmp101}, TNode<RawPtrT>{tmp103}, TNode<RawPtrT>{tmp99}).Flatten();
    tmp114 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferSigRepresentationArray);
    std::tie(tmp115, tmp116) = GetRefAt_RawPtr_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp114}).Flatten();
    tmp117 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{tmp115, tmp116});
    tmp118 = (TNode<RawPtrT>{tmp117});
    tmp119 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp3});
    std::tie(tmp120, tmp121, tmp122) = NewOffHeapConstSlice_uint32_0(state_, TNode<RawPtrT>{tmp118}, TNode<IntPtrT>{tmp119}).Flatten();
    tmp123 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferRefReturnCount);
    std::tie(tmp124, tmp125) = GetRefAt_bool_RawPtr_intptr_0(state_, TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp123}).Flatten();
    tmp126 = CodeStubAssembler(state_).LoadReference<BoolT>(CodeStubAssembler::Reference{tmp124, tmp125});
    ca_.Branch(tmp126, &block42, std::vector<compiler::Node*>{}, &block43, std::vector<compiler::Node*>{tmp105, tmp106, tmp107, tmp108, tmp109, tmp112, tmp113});
  }

  TNode<IntPtrT> tmp127;
  if (block42.is_used()) {
    ca_.Bind(&block42);
    tmp127 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block46, tmp105, tmp106, tmp107, tmp108, tmp109, tmp112, tmp113, tmp127);
  }

  TNode<IntPtrT> phi_bb46_7;
  TNode<IntPtrT> phi_bb46_8;
  TNode<IntPtrT> phi_bb46_9;
  TNode<IntPtrT> phi_bb46_10;
  TNode<IntPtrT> phi_bb46_11;
  TNode<IntPtrT> phi_bb46_14;
  TNode<BoolT> phi_bb46_15;
  TNode<IntPtrT> phi_bb46_21;
  TNode<IntPtrT> tmp128;
  TNode<BoolT> tmp129;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_7, &phi_bb46_8, &phi_bb46_9, &phi_bb46_10, &phi_bb46_11, &phi_bb46_14, &phi_bb46_15, &phi_bb46_21);
    tmp128 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp3});
    tmp129 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb46_21}, TNode<IntPtrT>{tmp128});
    ca_.Branch(tmp129, &block44, std::vector<compiler::Node*>{phi_bb46_7, phi_bb46_8, phi_bb46_9, phi_bb46_10, phi_bb46_11, phi_bb46_14, phi_bb46_15, phi_bb46_21}, &block45, std::vector<compiler::Node*>{phi_bb46_7, phi_bb46_8, phi_bb46_9, phi_bb46_10, phi_bb46_11, phi_bb46_14, phi_bb46_15, phi_bb46_21});
  }

  TNode<IntPtrT> phi_bb44_7;
  TNode<IntPtrT> phi_bb44_8;
  TNode<IntPtrT> phi_bb44_9;
  TNode<IntPtrT> phi_bb44_10;
  TNode<IntPtrT> phi_bb44_11;
  TNode<IntPtrT> phi_bb44_14;
  TNode<BoolT> phi_bb44_15;
  TNode<IntPtrT> phi_bb44_21;
  TNode<IntPtrT> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<Union<HeapObject, TaggedIndex>> tmp132;
  TNode<IntPtrT> tmp133;
  TNode<Uint32T> tmp134;
  TNode<Uint32T> tmp135;
  TNode<BoolT> tmp136;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_7, &phi_bb44_8, &phi_bb44_9, &phi_bb44_10, &phi_bb44_11, &phi_bb44_14, &phi_bb44_15, &phi_bb44_21);
    tmp130 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{phi_bb44_21});
    tmp131 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp121}, TNode<IntPtrT>{tmp130});
    std::tie(tmp132, tmp133) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp120}, TNode<IntPtrT>{tmp131}).Flatten();
    tmp134 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp132, tmp133});
    tmp135 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp136 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp134}, TNode<Uint32T>{tmp135});
    ca_.Branch(tmp136, &block49, std::vector<compiler::Node*>{phi_bb44_7, phi_bb44_8, phi_bb44_9, phi_bb44_10, phi_bb44_11, phi_bb44_14, phi_bb44_15, phi_bb44_21}, &block50, std::vector<compiler::Node*>{phi_bb44_7, phi_bb44_8, phi_bb44_9, phi_bb44_10, phi_bb44_11, phi_bb44_14, phi_bb44_15, phi_bb44_21});
  }

  TNode<IntPtrT> phi_bb49_7;
  TNode<IntPtrT> phi_bb49_8;
  TNode<IntPtrT> phi_bb49_9;
  TNode<IntPtrT> phi_bb49_10;
  TNode<IntPtrT> phi_bb49_11;
  TNode<IntPtrT> phi_bb49_14;
  TNode<BoolT> phi_bb49_15;
  TNode<IntPtrT> phi_bb49_21;
  TNode<IntPtrT> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<IntPtrT> tmp139;
  TNode<BoolT> tmp140;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_7, &phi_bb49_8, &phi_bb49_9, &phi_bb49_10, &phi_bb49_11, &phi_bb49_14, &phi_bb49_15, &phi_bb49_21);
    tmp137 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp138 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb49_7}, TNode<IntPtrT>{tmp137});
    tmp139 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp140 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb49_7}, TNode<IntPtrT>{tmp139});
    ca_.Branch(tmp140, &block53, std::vector<compiler::Node*>{phi_bb49_8, phi_bb49_9, phi_bb49_10, phi_bb49_11, phi_bb49_14, phi_bb49_15, phi_bb49_21}, &block54, std::vector<compiler::Node*>{phi_bb49_8, phi_bb49_9, phi_bb49_10, phi_bb49_11, phi_bb49_14, phi_bb49_15, phi_bb49_21});
  }

  TNode<IntPtrT> phi_bb53_8;
  TNode<IntPtrT> phi_bb53_9;
  TNode<IntPtrT> phi_bb53_10;
  TNode<IntPtrT> phi_bb53_11;
  TNode<IntPtrT> phi_bb53_14;
  TNode<BoolT> phi_bb53_15;
  TNode<IntPtrT> phi_bb53_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp141;
  TNode<IntPtrT> tmp142;
  TNode<IntPtrT> tmp143;
  TNode<IntPtrT> tmp144;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_8, &phi_bb53_9, &phi_bb53_10, &phi_bb53_11, &phi_bb53_14, &phi_bb53_15, &phi_bb53_21);
    std::tie(tmp141, tmp142) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb53_9}).Flatten();
    tmp143 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp144 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb53_9}, TNode<IntPtrT>{tmp143});
    ca_.Goto(&block52, phi_bb53_8, tmp144, phi_bb53_10, phi_bb53_11, phi_bb53_14, phi_bb53_15, phi_bb53_21, tmp141, tmp142);
  }

  TNode<IntPtrT> phi_bb54_8;
  TNode<IntPtrT> phi_bb54_9;
  TNode<IntPtrT> phi_bb54_10;
  TNode<IntPtrT> phi_bb54_11;
  TNode<IntPtrT> phi_bb54_14;
  TNode<BoolT> phi_bb54_15;
  TNode<IntPtrT> phi_bb54_21;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_8, &phi_bb54_9, &phi_bb54_10, &phi_bb54_11, &phi_bb54_14, &phi_bb54_15, &phi_bb54_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block56, phi_bb54_8, phi_bb54_9, phi_bb54_10, phi_bb54_11, phi_bb54_14, phi_bb54_15, phi_bb54_21);
    } else {
      ca_.Goto(&block57, phi_bb54_8, phi_bb54_9, phi_bb54_10, phi_bb54_11, phi_bb54_14, phi_bb54_15, phi_bb54_21);
    }
  }

  TNode<IntPtrT> phi_bb56_8;
  TNode<IntPtrT> phi_bb56_9;
  TNode<IntPtrT> phi_bb56_10;
  TNode<IntPtrT> phi_bb56_11;
  TNode<IntPtrT> phi_bb56_14;
  TNode<BoolT> phi_bb56_15;
  TNode<IntPtrT> phi_bb56_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp145;
  TNode<IntPtrT> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<IntPtrT> tmp148;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_8, &phi_bb56_9, &phi_bb56_10, &phi_bb56_11, &phi_bb56_14, &phi_bb56_15, &phi_bb56_21);
    std::tie(tmp145, tmp146) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb56_11}).Flatten();
    tmp147 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp148 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb56_11}, TNode<IntPtrT>{tmp147});
    ca_.Goto(&block55, phi_bb56_8, phi_bb56_9, phi_bb56_10, tmp148, phi_bb56_14, phi_bb56_15, phi_bb56_21, tmp145, tmp146);
  }

  TNode<IntPtrT> phi_bb57_8;
  TNode<IntPtrT> phi_bb57_9;
  TNode<IntPtrT> phi_bb57_10;
  TNode<IntPtrT> phi_bb57_11;
  TNode<IntPtrT> phi_bb57_14;
  TNode<BoolT> phi_bb57_15;
  TNode<IntPtrT> phi_bb57_21;
  TNode<IntPtrT> tmp149;
  TNode<BoolT> tmp150;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_8, &phi_bb57_9, &phi_bb57_10, &phi_bb57_11, &phi_bb57_14, &phi_bb57_15, &phi_bb57_21);
    tmp149 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp150 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb57_14}, TNode<IntPtrT>{tmp149});
    ca_.Branch(tmp150, &block59, std::vector<compiler::Node*>{phi_bb57_8, phi_bb57_9, phi_bb57_10, phi_bb57_11, phi_bb57_14, phi_bb57_15, phi_bb57_21}, &block60, std::vector<compiler::Node*>{phi_bb57_8, phi_bb57_9, phi_bb57_10, phi_bb57_11, phi_bb57_14, phi_bb57_15, phi_bb57_21});
  }

  TNode<IntPtrT> phi_bb59_8;
  TNode<IntPtrT> phi_bb59_9;
  TNode<IntPtrT> phi_bb59_10;
  TNode<IntPtrT> phi_bb59_11;
  TNode<IntPtrT> phi_bb59_14;
  TNode<BoolT> phi_bb59_15;
  TNode<IntPtrT> phi_bb59_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp151;
  TNode<IntPtrT> tmp152;
  TNode<IntPtrT> tmp153;
  TNode<BoolT> tmp154;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_8, &phi_bb59_9, &phi_bb59_10, &phi_bb59_11, &phi_bb59_14, &phi_bb59_15, &phi_bb59_21);
    std::tie(tmp151, tmp152) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb59_14}).Flatten();
    tmp153 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp154 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block55, phi_bb59_8, phi_bb59_9, phi_bb59_10, phi_bb59_11, tmp153, tmp154, phi_bb59_21, tmp151, tmp152);
  }

  TNode<IntPtrT> phi_bb60_8;
  TNode<IntPtrT> phi_bb60_9;
  TNode<IntPtrT> phi_bb60_10;
  TNode<IntPtrT> phi_bb60_11;
  TNode<IntPtrT> phi_bb60_14;
  TNode<BoolT> phi_bb60_15;
  TNode<IntPtrT> phi_bb60_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp155;
  TNode<IntPtrT> tmp156;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<IntPtrT> tmp159;
  TNode<IntPtrT> tmp160;
  TNode<BoolT> tmp161;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_8, &phi_bb60_9, &phi_bb60_10, &phi_bb60_11, &phi_bb60_14, &phi_bb60_15, &phi_bb60_21);
    std::tie(tmp155, tmp156) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb60_11}).Flatten();
    tmp157 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp158 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb60_11}, TNode<IntPtrT>{tmp157});
    tmp159 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp160 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp158}, TNode<IntPtrT>{tmp159});
    tmp161 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block55, phi_bb60_8, phi_bb60_9, phi_bb60_10, tmp160, tmp158, tmp161, phi_bb60_21, tmp155, tmp156);
  }

  TNode<IntPtrT> phi_bb55_8;
  TNode<IntPtrT> phi_bb55_9;
  TNode<IntPtrT> phi_bb55_10;
  TNode<IntPtrT> phi_bb55_11;
  TNode<IntPtrT> phi_bb55_14;
  TNode<BoolT> phi_bb55_15;
  TNode<IntPtrT> phi_bb55_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb55_23;
  TNode<IntPtrT> phi_bb55_24;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_8, &phi_bb55_9, &phi_bb55_10, &phi_bb55_11, &phi_bb55_14, &phi_bb55_15, &phi_bb55_21, &phi_bb55_23, &phi_bb55_24);
    ca_.Goto(&block52, phi_bb55_8, phi_bb55_9, phi_bb55_10, phi_bb55_11, phi_bb55_14, phi_bb55_15, phi_bb55_21, phi_bb55_23, phi_bb55_24);
  }

  TNode<IntPtrT> phi_bb52_8;
  TNode<IntPtrT> phi_bb52_9;
  TNode<IntPtrT> phi_bb52_10;
  TNode<IntPtrT> phi_bb52_11;
  TNode<IntPtrT> phi_bb52_14;
  TNode<BoolT> phi_bb52_15;
  TNode<IntPtrT> phi_bb52_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb52_23;
  TNode<IntPtrT> phi_bb52_24;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_8, &phi_bb52_9, &phi_bb52_10, &phi_bb52_11, &phi_bb52_14, &phi_bb52_15, &phi_bb52_21, &phi_bb52_23, &phi_bb52_24);
    ca_.Goto(&block51, tmp138, phi_bb52_8, phi_bb52_9, phi_bb52_10, phi_bb52_11, phi_bb52_14, phi_bb52_15, phi_bb52_21);
  }

  TNode<IntPtrT> phi_bb50_7;
  TNode<IntPtrT> phi_bb50_8;
  TNode<IntPtrT> phi_bb50_9;
  TNode<IntPtrT> phi_bb50_10;
  TNode<IntPtrT> phi_bb50_11;
  TNode<IntPtrT> phi_bb50_14;
  TNode<BoolT> phi_bb50_15;
  TNode<IntPtrT> phi_bb50_21;
  TNode<Uint32T> tmp162;
  TNode<BoolT> tmp163;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_7, &phi_bb50_8, &phi_bb50_9, &phi_bb50_10, &phi_bb50_11, &phi_bb50_14, &phi_bb50_15, &phi_bb50_21);
    tmp162 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp163 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp134}, TNode<Uint32T>{tmp162});
    ca_.Branch(tmp163, &block61, std::vector<compiler::Node*>{phi_bb50_7, phi_bb50_8, phi_bb50_9, phi_bb50_10, phi_bb50_11, phi_bb50_14, phi_bb50_15, phi_bb50_21}, &block62, std::vector<compiler::Node*>{phi_bb50_7, phi_bb50_8, phi_bb50_9, phi_bb50_10, phi_bb50_11, phi_bb50_14, phi_bb50_15, phi_bb50_21});
  }

  TNode<IntPtrT> phi_bb61_7;
  TNode<IntPtrT> phi_bb61_8;
  TNode<IntPtrT> phi_bb61_9;
  TNode<IntPtrT> phi_bb61_10;
  TNode<IntPtrT> phi_bb61_11;
  TNode<IntPtrT> phi_bb61_14;
  TNode<BoolT> phi_bb61_15;
  TNode<IntPtrT> phi_bb61_21;
  TNode<IntPtrT> tmp164;
  TNode<IntPtrT> tmp165;
  TNode<IntPtrT> tmp166;
  TNode<BoolT> tmp167;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_7, &phi_bb61_8, &phi_bb61_9, &phi_bb61_10, &phi_bb61_11, &phi_bb61_14, &phi_bb61_15, &phi_bb61_21);
    tmp164 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp165 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb61_8}, TNode<IntPtrT>{tmp164});
    tmp166 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp167 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb61_8}, TNode<IntPtrT>{tmp166});
    ca_.Branch(tmp167, &block65, std::vector<compiler::Node*>{phi_bb61_7, phi_bb61_9, phi_bb61_10, phi_bb61_11, phi_bb61_14, phi_bb61_15, phi_bb61_21}, &block66, std::vector<compiler::Node*>{phi_bb61_7, phi_bb61_9, phi_bb61_10, phi_bb61_11, phi_bb61_14, phi_bb61_15, phi_bb61_21});
  }

  TNode<IntPtrT> phi_bb65_7;
  TNode<IntPtrT> phi_bb65_9;
  TNode<IntPtrT> phi_bb65_10;
  TNode<IntPtrT> phi_bb65_11;
  TNode<IntPtrT> phi_bb65_14;
  TNode<BoolT> phi_bb65_15;
  TNode<IntPtrT> phi_bb65_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp168;
  TNode<IntPtrT> tmp169;
  TNode<IntPtrT> tmp170;
  TNode<IntPtrT> tmp171;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_7, &phi_bb65_9, &phi_bb65_10, &phi_bb65_11, &phi_bb65_14, &phi_bb65_15, &phi_bb65_21);
    std::tie(tmp168, tmp169) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb65_10}).Flatten();
    tmp170 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp171 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb65_10}, TNode<IntPtrT>{tmp170});
    ca_.Goto(&block64, phi_bb65_7, phi_bb65_9, tmp171, phi_bb65_11, phi_bb65_14, phi_bb65_15, phi_bb65_21, tmp168, tmp169);
  }

  TNode<IntPtrT> phi_bb66_7;
  TNode<IntPtrT> phi_bb66_9;
  TNode<IntPtrT> phi_bb66_10;
  TNode<IntPtrT> phi_bb66_11;
  TNode<IntPtrT> phi_bb66_14;
  TNode<BoolT> phi_bb66_15;
  TNode<IntPtrT> phi_bb66_21;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_7, &phi_bb66_9, &phi_bb66_10, &phi_bb66_11, &phi_bb66_14, &phi_bb66_15, &phi_bb66_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block68, phi_bb66_7, phi_bb66_9, phi_bb66_10, phi_bb66_11, phi_bb66_14, phi_bb66_15, phi_bb66_21);
    } else {
      ca_.Goto(&block69, phi_bb66_7, phi_bb66_9, phi_bb66_10, phi_bb66_11, phi_bb66_14, phi_bb66_15, phi_bb66_21);
    }
  }

  TNode<IntPtrT> phi_bb68_7;
  TNode<IntPtrT> phi_bb68_9;
  TNode<IntPtrT> phi_bb68_10;
  TNode<IntPtrT> phi_bb68_11;
  TNode<IntPtrT> phi_bb68_14;
  TNode<BoolT> phi_bb68_15;
  TNode<IntPtrT> phi_bb68_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp172;
  TNode<IntPtrT> tmp173;
  TNode<IntPtrT> tmp174;
  TNode<IntPtrT> tmp175;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_7, &phi_bb68_9, &phi_bb68_10, &phi_bb68_11, &phi_bb68_14, &phi_bb68_15, &phi_bb68_21);
    std::tie(tmp172, tmp173) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb68_11}).Flatten();
    tmp174 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp175 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb68_11}, TNode<IntPtrT>{tmp174});
    ca_.Goto(&block67, phi_bb68_7, phi_bb68_9, phi_bb68_10, tmp175, phi_bb68_14, phi_bb68_15, phi_bb68_21, tmp172, tmp173);
  }

  TNode<IntPtrT> phi_bb69_7;
  TNode<IntPtrT> phi_bb69_9;
  TNode<IntPtrT> phi_bb69_10;
  TNode<IntPtrT> phi_bb69_11;
  TNode<IntPtrT> phi_bb69_14;
  TNode<BoolT> phi_bb69_15;
  TNode<IntPtrT> phi_bb69_21;
  TNode<IntPtrT> tmp176;
  TNode<BoolT> tmp177;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_7, &phi_bb69_9, &phi_bb69_10, &phi_bb69_11, &phi_bb69_14, &phi_bb69_15, &phi_bb69_21);
    tmp176 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp177 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb69_14}, TNode<IntPtrT>{tmp176});
    ca_.Branch(tmp177, &block71, std::vector<compiler::Node*>{phi_bb69_7, phi_bb69_9, phi_bb69_10, phi_bb69_11, phi_bb69_14, phi_bb69_15, phi_bb69_21}, &block72, std::vector<compiler::Node*>{phi_bb69_7, phi_bb69_9, phi_bb69_10, phi_bb69_11, phi_bb69_14, phi_bb69_15, phi_bb69_21});
  }

  TNode<IntPtrT> phi_bb71_7;
  TNode<IntPtrT> phi_bb71_9;
  TNode<IntPtrT> phi_bb71_10;
  TNode<IntPtrT> phi_bb71_11;
  TNode<IntPtrT> phi_bb71_14;
  TNode<BoolT> phi_bb71_15;
  TNode<IntPtrT> phi_bb71_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp178;
  TNode<IntPtrT> tmp179;
  TNode<IntPtrT> tmp180;
  TNode<BoolT> tmp181;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_7, &phi_bb71_9, &phi_bb71_10, &phi_bb71_11, &phi_bb71_14, &phi_bb71_15, &phi_bb71_21);
    std::tie(tmp178, tmp179) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb71_14}).Flatten();
    tmp180 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp181 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block67, phi_bb71_7, phi_bb71_9, phi_bb71_10, phi_bb71_11, tmp180, tmp181, phi_bb71_21, tmp178, tmp179);
  }

  TNode<IntPtrT> phi_bb72_7;
  TNode<IntPtrT> phi_bb72_9;
  TNode<IntPtrT> phi_bb72_10;
  TNode<IntPtrT> phi_bb72_11;
  TNode<IntPtrT> phi_bb72_14;
  TNode<BoolT> phi_bb72_15;
  TNode<IntPtrT> phi_bb72_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp182;
  TNode<IntPtrT> tmp183;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<IntPtrT> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<BoolT> tmp188;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_7, &phi_bb72_9, &phi_bb72_10, &phi_bb72_11, &phi_bb72_14, &phi_bb72_15, &phi_bb72_21);
    std::tie(tmp182, tmp183) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb72_11}).Flatten();
    tmp184 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp185 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb72_11}, TNode<IntPtrT>{tmp184});
    tmp186 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp187 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp185}, TNode<IntPtrT>{tmp186});
    tmp188 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block67, phi_bb72_7, phi_bb72_9, phi_bb72_10, tmp187, tmp185, tmp188, phi_bb72_21, tmp182, tmp183);
  }

  TNode<IntPtrT> phi_bb67_7;
  TNode<IntPtrT> phi_bb67_9;
  TNode<IntPtrT> phi_bb67_10;
  TNode<IntPtrT> phi_bb67_11;
  TNode<IntPtrT> phi_bb67_14;
  TNode<BoolT> phi_bb67_15;
  TNode<IntPtrT> phi_bb67_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb67_23;
  TNode<IntPtrT> phi_bb67_24;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_7, &phi_bb67_9, &phi_bb67_10, &phi_bb67_11, &phi_bb67_14, &phi_bb67_15, &phi_bb67_21, &phi_bb67_23, &phi_bb67_24);
    ca_.Goto(&block64, phi_bb67_7, phi_bb67_9, phi_bb67_10, phi_bb67_11, phi_bb67_14, phi_bb67_15, phi_bb67_21, phi_bb67_23, phi_bb67_24);
  }

  TNode<IntPtrT> phi_bb64_7;
  TNode<IntPtrT> phi_bb64_9;
  TNode<IntPtrT> phi_bb64_10;
  TNode<IntPtrT> phi_bb64_11;
  TNode<IntPtrT> phi_bb64_14;
  TNode<BoolT> phi_bb64_15;
  TNode<IntPtrT> phi_bb64_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb64_23;
  TNode<IntPtrT> phi_bb64_24;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_7, &phi_bb64_9, &phi_bb64_10, &phi_bb64_11, &phi_bb64_14, &phi_bb64_15, &phi_bb64_21, &phi_bb64_23, &phi_bb64_24);
    ca_.Goto(&block63, phi_bb64_7, tmp165, phi_bb64_9, phi_bb64_10, phi_bb64_11, phi_bb64_14, phi_bb64_15, phi_bb64_21);
  }

  TNode<IntPtrT> phi_bb62_7;
  TNode<IntPtrT> phi_bb62_8;
  TNode<IntPtrT> phi_bb62_9;
  TNode<IntPtrT> phi_bb62_10;
  TNode<IntPtrT> phi_bb62_11;
  TNode<IntPtrT> phi_bb62_14;
  TNode<BoolT> phi_bb62_15;
  TNode<IntPtrT> phi_bb62_21;
  TNode<Uint32T> tmp189;
  TNode<BoolT> tmp190;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_7, &phi_bb62_8, &phi_bb62_9, &phi_bb62_10, &phi_bb62_11, &phi_bb62_14, &phi_bb62_15, &phi_bb62_21);
    tmp189 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp190 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp134}, TNode<Uint32T>{tmp189});
    ca_.Branch(tmp190, &block73, std::vector<compiler::Node*>{phi_bb62_7, phi_bb62_8, phi_bb62_9, phi_bb62_10, phi_bb62_11, phi_bb62_14, phi_bb62_15, phi_bb62_21}, &block74, std::vector<compiler::Node*>{phi_bb62_7, phi_bb62_8, phi_bb62_9, phi_bb62_10, phi_bb62_11, phi_bb62_14, phi_bb62_15, phi_bb62_21});
  }

  TNode<IntPtrT> phi_bb73_7;
  TNode<IntPtrT> phi_bb73_8;
  TNode<IntPtrT> phi_bb73_9;
  TNode<IntPtrT> phi_bb73_10;
  TNode<IntPtrT> phi_bb73_11;
  TNode<IntPtrT> phi_bb73_14;
  TNode<BoolT> phi_bb73_15;
  TNode<IntPtrT> phi_bb73_21;
  TNode<IntPtrT> tmp191;
  TNode<IntPtrT> tmp192;
  TNode<IntPtrT> tmp193;
  TNode<BoolT> tmp194;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_7, &phi_bb73_8, &phi_bb73_9, &phi_bb73_10, &phi_bb73_11, &phi_bb73_14, &phi_bb73_15, &phi_bb73_21);
    tmp191 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp192 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb73_7}, TNode<IntPtrT>{tmp191});
    tmp193 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp194 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb73_7}, TNode<IntPtrT>{tmp193});
    ca_.Branch(tmp194, &block77, std::vector<compiler::Node*>{phi_bb73_8, phi_bb73_9, phi_bb73_10, phi_bb73_11, phi_bb73_14, phi_bb73_15, phi_bb73_21}, &block78, std::vector<compiler::Node*>{phi_bb73_8, phi_bb73_9, phi_bb73_10, phi_bb73_11, phi_bb73_14, phi_bb73_15, phi_bb73_21});
  }

  TNode<IntPtrT> phi_bb77_8;
  TNode<IntPtrT> phi_bb77_9;
  TNode<IntPtrT> phi_bb77_10;
  TNode<IntPtrT> phi_bb77_11;
  TNode<IntPtrT> phi_bb77_14;
  TNode<BoolT> phi_bb77_15;
  TNode<IntPtrT> phi_bb77_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp195;
  TNode<IntPtrT> tmp196;
  TNode<IntPtrT> tmp197;
  TNode<IntPtrT> tmp198;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_8, &phi_bb77_9, &phi_bb77_10, &phi_bb77_11, &phi_bb77_14, &phi_bb77_15, &phi_bb77_21);
    std::tie(tmp195, tmp196) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb77_9}).Flatten();
    tmp197 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp198 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb77_9}, TNode<IntPtrT>{tmp197});
    ca_.Goto(&block76, phi_bb77_8, tmp198, phi_bb77_10, phi_bb77_11, phi_bb77_14, phi_bb77_15, phi_bb77_21, tmp195, tmp196);
  }

  TNode<IntPtrT> phi_bb78_8;
  TNode<IntPtrT> phi_bb78_9;
  TNode<IntPtrT> phi_bb78_10;
  TNode<IntPtrT> phi_bb78_11;
  TNode<IntPtrT> phi_bb78_14;
  TNode<BoolT> phi_bb78_15;
  TNode<IntPtrT> phi_bb78_21;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_8, &phi_bb78_9, &phi_bb78_10, &phi_bb78_11, &phi_bb78_14, &phi_bb78_15, &phi_bb78_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block80, phi_bb78_8, phi_bb78_9, phi_bb78_10, phi_bb78_11, phi_bb78_14, phi_bb78_15, phi_bb78_21);
    } else {
      ca_.Goto(&block81, phi_bb78_8, phi_bb78_9, phi_bb78_10, phi_bb78_11, phi_bb78_14, phi_bb78_15, phi_bb78_21);
    }
  }

  TNode<IntPtrT> phi_bb80_8;
  TNode<IntPtrT> phi_bb80_9;
  TNode<IntPtrT> phi_bb80_10;
  TNode<IntPtrT> phi_bb80_11;
  TNode<IntPtrT> phi_bb80_14;
  TNode<BoolT> phi_bb80_15;
  TNode<IntPtrT> phi_bb80_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<IntPtrT> tmp201;
  TNode<IntPtrT> tmp202;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_8, &phi_bb80_9, &phi_bb80_10, &phi_bb80_11, &phi_bb80_14, &phi_bb80_15, &phi_bb80_21);
    std::tie(tmp199, tmp200) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb80_11}).Flatten();
    tmp201 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp202 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb80_11}, TNode<IntPtrT>{tmp201});
    ca_.Goto(&block79, phi_bb80_8, phi_bb80_9, phi_bb80_10, tmp202, phi_bb80_14, phi_bb80_15, phi_bb80_21, tmp199, tmp200);
  }

  TNode<IntPtrT> phi_bb81_8;
  TNode<IntPtrT> phi_bb81_9;
  TNode<IntPtrT> phi_bb81_10;
  TNode<IntPtrT> phi_bb81_11;
  TNode<IntPtrT> phi_bb81_14;
  TNode<BoolT> phi_bb81_15;
  TNode<IntPtrT> phi_bb81_21;
  TNode<IntPtrT> tmp203;
  TNode<BoolT> tmp204;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_8, &phi_bb81_9, &phi_bb81_10, &phi_bb81_11, &phi_bb81_14, &phi_bb81_15, &phi_bb81_21);
    tmp203 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp204 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb81_14}, TNode<IntPtrT>{tmp203});
    ca_.Branch(tmp204, &block83, std::vector<compiler::Node*>{phi_bb81_8, phi_bb81_9, phi_bb81_10, phi_bb81_11, phi_bb81_14, phi_bb81_15, phi_bb81_21}, &block84, std::vector<compiler::Node*>{phi_bb81_8, phi_bb81_9, phi_bb81_10, phi_bb81_11, phi_bb81_14, phi_bb81_15, phi_bb81_21});
  }

  TNode<IntPtrT> phi_bb83_8;
  TNode<IntPtrT> phi_bb83_9;
  TNode<IntPtrT> phi_bb83_10;
  TNode<IntPtrT> phi_bb83_11;
  TNode<IntPtrT> phi_bb83_14;
  TNode<BoolT> phi_bb83_15;
  TNode<IntPtrT> phi_bb83_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp205;
  TNode<IntPtrT> tmp206;
  TNode<IntPtrT> tmp207;
  TNode<BoolT> tmp208;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_8, &phi_bb83_9, &phi_bb83_10, &phi_bb83_11, &phi_bb83_14, &phi_bb83_15, &phi_bb83_21);
    std::tie(tmp205, tmp206) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb83_14}).Flatten();
    tmp207 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp208 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block79, phi_bb83_8, phi_bb83_9, phi_bb83_10, phi_bb83_11, tmp207, tmp208, phi_bb83_21, tmp205, tmp206);
  }

  TNode<IntPtrT> phi_bb84_8;
  TNode<IntPtrT> phi_bb84_9;
  TNode<IntPtrT> phi_bb84_10;
  TNode<IntPtrT> phi_bb84_11;
  TNode<IntPtrT> phi_bb84_14;
  TNode<BoolT> phi_bb84_15;
  TNode<IntPtrT> phi_bb84_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp209;
  TNode<IntPtrT> tmp210;
  TNode<IntPtrT> tmp211;
  TNode<IntPtrT> tmp212;
  TNode<IntPtrT> tmp213;
  TNode<IntPtrT> tmp214;
  TNode<BoolT> tmp215;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_8, &phi_bb84_9, &phi_bb84_10, &phi_bb84_11, &phi_bb84_14, &phi_bb84_15, &phi_bb84_21);
    std::tie(tmp209, tmp210) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb84_11}).Flatten();
    tmp211 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp212 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb84_11}, TNode<IntPtrT>{tmp211});
    tmp213 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp214 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp212}, TNode<IntPtrT>{tmp213});
    tmp215 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block79, phi_bb84_8, phi_bb84_9, phi_bb84_10, tmp214, tmp212, tmp215, phi_bb84_21, tmp209, tmp210);
  }

  TNode<IntPtrT> phi_bb79_8;
  TNode<IntPtrT> phi_bb79_9;
  TNode<IntPtrT> phi_bb79_10;
  TNode<IntPtrT> phi_bb79_11;
  TNode<IntPtrT> phi_bb79_14;
  TNode<BoolT> phi_bb79_15;
  TNode<IntPtrT> phi_bb79_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb79_23;
  TNode<IntPtrT> phi_bb79_24;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_8, &phi_bb79_9, &phi_bb79_10, &phi_bb79_11, &phi_bb79_14, &phi_bb79_15, &phi_bb79_21, &phi_bb79_23, &phi_bb79_24);
    ca_.Goto(&block76, phi_bb79_8, phi_bb79_9, phi_bb79_10, phi_bb79_11, phi_bb79_14, phi_bb79_15, phi_bb79_21, phi_bb79_23, phi_bb79_24);
  }

  TNode<IntPtrT> phi_bb76_8;
  TNode<IntPtrT> phi_bb76_9;
  TNode<IntPtrT> phi_bb76_10;
  TNode<IntPtrT> phi_bb76_11;
  TNode<IntPtrT> phi_bb76_14;
  TNode<BoolT> phi_bb76_15;
  TNode<IntPtrT> phi_bb76_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb76_23;
  TNode<IntPtrT> phi_bb76_24;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_8, &phi_bb76_9, &phi_bb76_10, &phi_bb76_11, &phi_bb76_14, &phi_bb76_15, &phi_bb76_21, &phi_bb76_23, &phi_bb76_24);
    if (((CodeStubAssembler(state_).ConstexprBoolNot((CodeStubAssembler(state_).Is64()))))) {
      ca_.Goto(&block85, phi_bb76_8, phi_bb76_9, phi_bb76_10, phi_bb76_11, phi_bb76_14, phi_bb76_15, phi_bb76_21);
    } else {
      ca_.Goto(&block86, phi_bb76_8, phi_bb76_9, phi_bb76_10, phi_bb76_11, phi_bb76_14, phi_bb76_15, phi_bb76_21);
    }
  }

  TNode<IntPtrT> phi_bb85_8;
  TNode<IntPtrT> phi_bb85_9;
  TNode<IntPtrT> phi_bb85_10;
  TNode<IntPtrT> phi_bb85_11;
  TNode<IntPtrT> phi_bb85_14;
  TNode<BoolT> phi_bb85_15;
  TNode<IntPtrT> phi_bb85_21;
  TNode<IntPtrT> tmp216;
  TNode<IntPtrT> tmp217;
  TNode<IntPtrT> tmp218;
  TNode<BoolT> tmp219;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_8, &phi_bb85_9, &phi_bb85_10, &phi_bb85_11, &phi_bb85_14, &phi_bb85_15, &phi_bb85_21);
    tmp216 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp217 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp192}, TNode<IntPtrT>{tmp216});
    tmp218 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp219 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp192}, TNode<IntPtrT>{tmp218});
    ca_.Branch(tmp219, &block89, std::vector<compiler::Node*>{phi_bb85_8, phi_bb85_9, phi_bb85_10, phi_bb85_11, phi_bb85_14, phi_bb85_15, phi_bb85_21}, &block90, std::vector<compiler::Node*>{phi_bb85_8, phi_bb85_9, phi_bb85_10, phi_bb85_11, phi_bb85_14, phi_bb85_15, phi_bb85_21});
  }

  TNode<IntPtrT> phi_bb89_8;
  TNode<IntPtrT> phi_bb89_9;
  TNode<IntPtrT> phi_bb89_10;
  TNode<IntPtrT> phi_bb89_11;
  TNode<IntPtrT> phi_bb89_14;
  TNode<BoolT> phi_bb89_15;
  TNode<IntPtrT> phi_bb89_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<IntPtrT> tmp222;
  TNode<IntPtrT> tmp223;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_8, &phi_bb89_9, &phi_bb89_10, &phi_bb89_11, &phi_bb89_14, &phi_bb89_15, &phi_bb89_21);
    std::tie(tmp220, tmp221) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb89_9}).Flatten();
    tmp222 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp223 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb89_9}, TNode<IntPtrT>{tmp222});
    ca_.Goto(&block88, phi_bb89_8, tmp223, phi_bb89_10, phi_bb89_11, phi_bb89_14, phi_bb89_15, phi_bb89_21, tmp220, tmp221);
  }

  TNode<IntPtrT> phi_bb90_8;
  TNode<IntPtrT> phi_bb90_9;
  TNode<IntPtrT> phi_bb90_10;
  TNode<IntPtrT> phi_bb90_11;
  TNode<IntPtrT> phi_bb90_14;
  TNode<BoolT> phi_bb90_15;
  TNode<IntPtrT> phi_bb90_21;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_8, &phi_bb90_9, &phi_bb90_10, &phi_bb90_11, &phi_bb90_14, &phi_bb90_15, &phi_bb90_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block92, phi_bb90_8, phi_bb90_9, phi_bb90_10, phi_bb90_11, phi_bb90_14, phi_bb90_15, phi_bb90_21);
    } else {
      ca_.Goto(&block93, phi_bb90_8, phi_bb90_9, phi_bb90_10, phi_bb90_11, phi_bb90_14, phi_bb90_15, phi_bb90_21);
    }
  }

  TNode<IntPtrT> phi_bb92_8;
  TNode<IntPtrT> phi_bb92_9;
  TNode<IntPtrT> phi_bb92_10;
  TNode<IntPtrT> phi_bb92_11;
  TNode<IntPtrT> phi_bb92_14;
  TNode<BoolT> phi_bb92_15;
  TNode<IntPtrT> phi_bb92_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp224;
  TNode<IntPtrT> tmp225;
  TNode<IntPtrT> tmp226;
  TNode<IntPtrT> tmp227;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_8, &phi_bb92_9, &phi_bb92_10, &phi_bb92_11, &phi_bb92_14, &phi_bb92_15, &phi_bb92_21);
    std::tie(tmp224, tmp225) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb92_11}).Flatten();
    tmp226 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp227 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb92_11}, TNode<IntPtrT>{tmp226});
    ca_.Goto(&block91, phi_bb92_8, phi_bb92_9, phi_bb92_10, tmp227, phi_bb92_14, phi_bb92_15, phi_bb92_21, tmp224, tmp225);
  }

  TNode<IntPtrT> phi_bb93_8;
  TNode<IntPtrT> phi_bb93_9;
  TNode<IntPtrT> phi_bb93_10;
  TNode<IntPtrT> phi_bb93_11;
  TNode<IntPtrT> phi_bb93_14;
  TNode<BoolT> phi_bb93_15;
  TNode<IntPtrT> phi_bb93_21;
  TNode<IntPtrT> tmp228;
  TNode<BoolT> tmp229;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_8, &phi_bb93_9, &phi_bb93_10, &phi_bb93_11, &phi_bb93_14, &phi_bb93_15, &phi_bb93_21);
    tmp228 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp229 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb93_14}, TNode<IntPtrT>{tmp228});
    ca_.Branch(tmp229, &block95, std::vector<compiler::Node*>{phi_bb93_8, phi_bb93_9, phi_bb93_10, phi_bb93_11, phi_bb93_14, phi_bb93_15, phi_bb93_21}, &block96, std::vector<compiler::Node*>{phi_bb93_8, phi_bb93_9, phi_bb93_10, phi_bb93_11, phi_bb93_14, phi_bb93_15, phi_bb93_21});
  }

  TNode<IntPtrT> phi_bb95_8;
  TNode<IntPtrT> phi_bb95_9;
  TNode<IntPtrT> phi_bb95_10;
  TNode<IntPtrT> phi_bb95_11;
  TNode<IntPtrT> phi_bb95_14;
  TNode<BoolT> phi_bb95_15;
  TNode<IntPtrT> phi_bb95_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<IntPtrT> tmp232;
  TNode<BoolT> tmp233;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_8, &phi_bb95_9, &phi_bb95_10, &phi_bb95_11, &phi_bb95_14, &phi_bb95_15, &phi_bb95_21);
    std::tie(tmp230, tmp231) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb95_14}).Flatten();
    tmp232 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp233 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block91, phi_bb95_8, phi_bb95_9, phi_bb95_10, phi_bb95_11, tmp232, tmp233, phi_bb95_21, tmp230, tmp231);
  }

  TNode<IntPtrT> phi_bb96_8;
  TNode<IntPtrT> phi_bb96_9;
  TNode<IntPtrT> phi_bb96_10;
  TNode<IntPtrT> phi_bb96_11;
  TNode<IntPtrT> phi_bb96_14;
  TNode<BoolT> phi_bb96_15;
  TNode<IntPtrT> phi_bb96_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp234;
  TNode<IntPtrT> tmp235;
  TNode<IntPtrT> tmp236;
  TNode<IntPtrT> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<IntPtrT> tmp239;
  TNode<BoolT> tmp240;
  if (block96.is_used()) {
    ca_.Bind(&block96, &phi_bb96_8, &phi_bb96_9, &phi_bb96_10, &phi_bb96_11, &phi_bb96_14, &phi_bb96_15, &phi_bb96_21);
    std::tie(tmp234, tmp235) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb96_11}).Flatten();
    tmp236 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp237 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb96_11}, TNode<IntPtrT>{tmp236});
    tmp238 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp239 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp237}, TNode<IntPtrT>{tmp238});
    tmp240 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block91, phi_bb96_8, phi_bb96_9, phi_bb96_10, tmp239, tmp237, tmp240, phi_bb96_21, tmp234, tmp235);
  }

  TNode<IntPtrT> phi_bb91_8;
  TNode<IntPtrT> phi_bb91_9;
  TNode<IntPtrT> phi_bb91_10;
  TNode<IntPtrT> phi_bb91_11;
  TNode<IntPtrT> phi_bb91_14;
  TNode<BoolT> phi_bb91_15;
  TNode<IntPtrT> phi_bb91_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb91_23;
  TNode<IntPtrT> phi_bb91_24;
  if (block91.is_used()) {
    ca_.Bind(&block91, &phi_bb91_8, &phi_bb91_9, &phi_bb91_10, &phi_bb91_11, &phi_bb91_14, &phi_bb91_15, &phi_bb91_21, &phi_bb91_23, &phi_bb91_24);
    ca_.Goto(&block88, phi_bb91_8, phi_bb91_9, phi_bb91_10, phi_bb91_11, phi_bb91_14, phi_bb91_15, phi_bb91_21, phi_bb91_23, phi_bb91_24);
  }

  TNode<IntPtrT> phi_bb88_8;
  TNode<IntPtrT> phi_bb88_9;
  TNode<IntPtrT> phi_bb88_10;
  TNode<IntPtrT> phi_bb88_11;
  TNode<IntPtrT> phi_bb88_14;
  TNode<BoolT> phi_bb88_15;
  TNode<IntPtrT> phi_bb88_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb88_23;
  TNode<IntPtrT> phi_bb88_24;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_8, &phi_bb88_9, &phi_bb88_10, &phi_bb88_11, &phi_bb88_14, &phi_bb88_15, &phi_bb88_21, &phi_bb88_23, &phi_bb88_24);
    ca_.Goto(&block87, tmp217, phi_bb88_8, phi_bb88_9, phi_bb88_10, phi_bb88_11, phi_bb88_14, phi_bb88_15, phi_bb88_21);
  }

  TNode<IntPtrT> phi_bb86_8;
  TNode<IntPtrT> phi_bb86_9;
  TNode<IntPtrT> phi_bb86_10;
  TNode<IntPtrT> phi_bb86_11;
  TNode<IntPtrT> phi_bb86_14;
  TNode<BoolT> phi_bb86_15;
  TNode<IntPtrT> phi_bb86_21;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_8, &phi_bb86_9, &phi_bb86_10, &phi_bb86_11, &phi_bb86_14, &phi_bb86_15, &phi_bb86_21);
    ca_.Goto(&block87, tmp192, phi_bb86_8, phi_bb86_9, phi_bb86_10, phi_bb86_11, phi_bb86_14, phi_bb86_15, phi_bb86_21);
  }

  TNode<IntPtrT> phi_bb87_7;
  TNode<IntPtrT> phi_bb87_8;
  TNode<IntPtrT> phi_bb87_9;
  TNode<IntPtrT> phi_bb87_10;
  TNode<IntPtrT> phi_bb87_11;
  TNode<IntPtrT> phi_bb87_14;
  TNode<BoolT> phi_bb87_15;
  TNode<IntPtrT> phi_bb87_21;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_7, &phi_bb87_8, &phi_bb87_9, &phi_bb87_10, &phi_bb87_11, &phi_bb87_14, &phi_bb87_15, &phi_bb87_21);
    ca_.Goto(&block75, phi_bb87_7, phi_bb87_8, phi_bb87_9, phi_bb87_10, phi_bb87_11, phi_bb87_14, phi_bb87_15, phi_bb87_21);
  }

  TNode<IntPtrT> phi_bb74_7;
  TNode<IntPtrT> phi_bb74_8;
  TNode<IntPtrT> phi_bb74_9;
  TNode<IntPtrT> phi_bb74_10;
  TNode<IntPtrT> phi_bb74_11;
  TNode<IntPtrT> phi_bb74_14;
  TNode<BoolT> phi_bb74_15;
  TNode<IntPtrT> phi_bb74_21;
  TNode<Uint32T> tmp241;
  TNode<BoolT> tmp242;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_7, &phi_bb74_8, &phi_bb74_9, &phi_bb74_10, &phi_bb74_11, &phi_bb74_14, &phi_bb74_15, &phi_bb74_21);
    tmp241 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp242 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp134}, TNode<Uint32T>{tmp241});
    ca_.Branch(tmp242, &block97, std::vector<compiler::Node*>{phi_bb74_7, phi_bb74_8, phi_bb74_9, phi_bb74_10, phi_bb74_11, phi_bb74_14, phi_bb74_15, phi_bb74_21}, &block98, std::vector<compiler::Node*>{phi_bb74_7, phi_bb74_8, phi_bb74_9, phi_bb74_10, phi_bb74_11, phi_bb74_14, phi_bb74_15, phi_bb74_21});
  }

  TNode<IntPtrT> phi_bb97_7;
  TNode<IntPtrT> phi_bb97_8;
  TNode<IntPtrT> phi_bb97_9;
  TNode<IntPtrT> phi_bb97_10;
  TNode<IntPtrT> phi_bb97_11;
  TNode<IntPtrT> phi_bb97_14;
  TNode<BoolT> phi_bb97_15;
  TNode<IntPtrT> phi_bb97_21;
  TNode<IntPtrT> tmp243;
  TNode<IntPtrT> tmp244;
  TNode<IntPtrT> tmp245;
  TNode<BoolT> tmp246;
  if (block97.is_used()) {
    ca_.Bind(&block97, &phi_bb97_7, &phi_bb97_8, &phi_bb97_9, &phi_bb97_10, &phi_bb97_11, &phi_bb97_14, &phi_bb97_15, &phi_bb97_21);
    tmp243 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp244 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb97_8}, TNode<IntPtrT>{tmp243});
    tmp245 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp246 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb97_8}, TNode<IntPtrT>{tmp245});
    ca_.Branch(tmp246, &block100, std::vector<compiler::Node*>{phi_bb97_7, phi_bb97_9, phi_bb97_10, phi_bb97_11, phi_bb97_14, phi_bb97_15, phi_bb97_21}, &block101, std::vector<compiler::Node*>{phi_bb97_7, phi_bb97_9, phi_bb97_10, phi_bb97_11, phi_bb97_14, phi_bb97_15, phi_bb97_21});
  }

  TNode<IntPtrT> phi_bb100_7;
  TNode<IntPtrT> phi_bb100_9;
  TNode<IntPtrT> phi_bb100_10;
  TNode<IntPtrT> phi_bb100_11;
  TNode<IntPtrT> phi_bb100_14;
  TNode<BoolT> phi_bb100_15;
  TNode<IntPtrT> phi_bb100_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp247;
  TNode<IntPtrT> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<IntPtrT> tmp250;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_7, &phi_bb100_9, &phi_bb100_10, &phi_bb100_11, &phi_bb100_14, &phi_bb100_15, &phi_bb100_21);
    std::tie(tmp247, tmp248) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb100_10}).Flatten();
    tmp249 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp250 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb100_10}, TNode<IntPtrT>{tmp249});
    ca_.Goto(&block99, phi_bb100_7, phi_bb100_9, tmp250, phi_bb100_11, phi_bb100_14, phi_bb100_15, phi_bb100_21, tmp247, tmp248);
  }

  TNode<IntPtrT> phi_bb101_7;
  TNode<IntPtrT> phi_bb101_9;
  TNode<IntPtrT> phi_bb101_10;
  TNode<IntPtrT> phi_bb101_11;
  TNode<IntPtrT> phi_bb101_14;
  TNode<BoolT> phi_bb101_15;
  TNode<IntPtrT> phi_bb101_21;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_7, &phi_bb101_9, &phi_bb101_10, &phi_bb101_11, &phi_bb101_14, &phi_bb101_15, &phi_bb101_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block102, phi_bb101_7, phi_bb101_9, phi_bb101_10, phi_bb101_11, phi_bb101_14, phi_bb101_15, phi_bb101_21);
    } else {
      ca_.Goto(&block103, phi_bb101_7, phi_bb101_9, phi_bb101_10, phi_bb101_11, phi_bb101_14, phi_bb101_15, phi_bb101_21);
    }
  }

  TNode<IntPtrT> phi_bb102_7;
  TNode<IntPtrT> phi_bb102_9;
  TNode<IntPtrT> phi_bb102_10;
  TNode<IntPtrT> phi_bb102_11;
  TNode<IntPtrT> phi_bb102_14;
  TNode<BoolT> phi_bb102_15;
  TNode<IntPtrT> phi_bb102_21;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_7, &phi_bb102_9, &phi_bb102_10, &phi_bb102_11, &phi_bb102_14, &phi_bb102_15, &phi_bb102_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block106, phi_bb102_7, phi_bb102_9, phi_bb102_10, phi_bb102_11, phi_bb102_14, phi_bb102_15, phi_bb102_21);
    } else {
      ca_.Goto(&block107, phi_bb102_7, phi_bb102_9, phi_bb102_10, phi_bb102_11, phi_bb102_14, phi_bb102_15, phi_bb102_21);
    }
  }

  TNode<IntPtrT> phi_bb106_7;
  TNode<IntPtrT> phi_bb106_9;
  TNode<IntPtrT> phi_bb106_10;
  TNode<IntPtrT> phi_bb106_11;
  TNode<IntPtrT> phi_bb106_14;
  TNode<BoolT> phi_bb106_15;
  TNode<IntPtrT> phi_bb106_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<IntPtrT> tmp253;
  TNode<IntPtrT> tmp254;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_7, &phi_bb106_9, &phi_bb106_10, &phi_bb106_11, &phi_bb106_14, &phi_bb106_15, &phi_bb106_21);
    std::tie(tmp251, tmp252) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb106_11}).Flatten();
    tmp253 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp254 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb106_11}, TNode<IntPtrT>{tmp253});
    ca_.Goto(&block105, phi_bb106_7, phi_bb106_9, phi_bb106_10, tmp254, phi_bb106_14, phi_bb106_15, phi_bb106_21, tmp251, tmp252);
  }

  TNode<IntPtrT> phi_bb107_7;
  TNode<IntPtrT> phi_bb107_9;
  TNode<IntPtrT> phi_bb107_10;
  TNode<IntPtrT> phi_bb107_11;
  TNode<IntPtrT> phi_bb107_14;
  TNode<BoolT> phi_bb107_15;
  TNode<IntPtrT> phi_bb107_21;
  TNode<IntPtrT> tmp255;
  TNode<BoolT> tmp256;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_7, &phi_bb107_9, &phi_bb107_10, &phi_bb107_11, &phi_bb107_14, &phi_bb107_15, &phi_bb107_21);
    tmp255 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp256 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb107_14}, TNode<IntPtrT>{tmp255});
    ca_.Branch(tmp256, &block109, std::vector<compiler::Node*>{phi_bb107_7, phi_bb107_9, phi_bb107_10, phi_bb107_11, phi_bb107_14, phi_bb107_15, phi_bb107_21}, &block110, std::vector<compiler::Node*>{phi_bb107_7, phi_bb107_9, phi_bb107_10, phi_bb107_11, phi_bb107_14, phi_bb107_15, phi_bb107_21});
  }

  TNode<IntPtrT> phi_bb109_7;
  TNode<IntPtrT> phi_bb109_9;
  TNode<IntPtrT> phi_bb109_10;
  TNode<IntPtrT> phi_bb109_11;
  TNode<IntPtrT> phi_bb109_14;
  TNode<BoolT> phi_bb109_15;
  TNode<IntPtrT> phi_bb109_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp257;
  TNode<IntPtrT> tmp258;
  TNode<IntPtrT> tmp259;
  TNode<BoolT> tmp260;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_7, &phi_bb109_9, &phi_bb109_10, &phi_bb109_11, &phi_bb109_14, &phi_bb109_15, &phi_bb109_21);
    std::tie(tmp257, tmp258) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb109_14}).Flatten();
    tmp259 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp260 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block105, phi_bb109_7, phi_bb109_9, phi_bb109_10, phi_bb109_11, tmp259, tmp260, phi_bb109_21, tmp257, tmp258);
  }

  TNode<IntPtrT> phi_bb110_7;
  TNode<IntPtrT> phi_bb110_9;
  TNode<IntPtrT> phi_bb110_10;
  TNode<IntPtrT> phi_bb110_11;
  TNode<IntPtrT> phi_bb110_14;
  TNode<BoolT> phi_bb110_15;
  TNode<IntPtrT> phi_bb110_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp261;
  TNode<IntPtrT> tmp262;
  TNode<IntPtrT> tmp263;
  TNode<IntPtrT> tmp264;
  TNode<IntPtrT> tmp265;
  TNode<IntPtrT> tmp266;
  TNode<BoolT> tmp267;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_7, &phi_bb110_9, &phi_bb110_10, &phi_bb110_11, &phi_bb110_14, &phi_bb110_15, &phi_bb110_21);
    std::tie(tmp261, tmp262) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb110_11}).Flatten();
    tmp263 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp264 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb110_11}, TNode<IntPtrT>{tmp263});
    tmp265 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp266 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp264}, TNode<IntPtrT>{tmp265});
    tmp267 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block105, phi_bb110_7, phi_bb110_9, phi_bb110_10, tmp266, tmp264, tmp267, phi_bb110_21, tmp261, tmp262);
  }

  TNode<IntPtrT> phi_bb105_7;
  TNode<IntPtrT> phi_bb105_9;
  TNode<IntPtrT> phi_bb105_10;
  TNode<IntPtrT> phi_bb105_11;
  TNode<IntPtrT> phi_bb105_14;
  TNode<BoolT> phi_bb105_15;
  TNode<IntPtrT> phi_bb105_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb105_23;
  TNode<IntPtrT> phi_bb105_24;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_7, &phi_bb105_9, &phi_bb105_10, &phi_bb105_11, &phi_bb105_14, &phi_bb105_15, &phi_bb105_21, &phi_bb105_23, &phi_bb105_24);
    ca_.Goto(&block99, phi_bb105_7, phi_bb105_9, phi_bb105_10, phi_bb105_11, phi_bb105_14, phi_bb105_15, phi_bb105_21, phi_bb105_23, phi_bb105_24);
  }

  TNode<IntPtrT> phi_bb103_7;
  TNode<IntPtrT> phi_bb103_9;
  TNode<IntPtrT> phi_bb103_10;
  TNode<IntPtrT> phi_bb103_11;
  TNode<IntPtrT> phi_bb103_14;
  TNode<BoolT> phi_bb103_15;
  TNode<IntPtrT> phi_bb103_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<IntPtrT> tmp270;
  TNode<IntPtrT> tmp271;
  TNode<BoolT> tmp272;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_7, &phi_bb103_9, &phi_bb103_10, &phi_bb103_11, &phi_bb103_14, &phi_bb103_15, &phi_bb103_21);
    std::tie(tmp268, tmp269) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb103_11}).Flatten();
    tmp270 = FromConstexpr_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_)))));
    tmp271 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb103_11}, TNode<IntPtrT>{tmp270});
    tmp272 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block99, phi_bb103_7, phi_bb103_9, phi_bb103_10, tmp271, phi_bb103_14, tmp272, phi_bb103_21, tmp268, tmp269);
  }

  TNode<IntPtrT> phi_bb99_7;
  TNode<IntPtrT> phi_bb99_9;
  TNode<IntPtrT> phi_bb99_10;
  TNode<IntPtrT> phi_bb99_11;
  TNode<IntPtrT> phi_bb99_14;
  TNode<BoolT> phi_bb99_15;
  TNode<IntPtrT> phi_bb99_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb99_23;
  TNode<IntPtrT> phi_bb99_24;
  if (block99.is_used()) {
    ca_.Bind(&block99, &phi_bb99_7, &phi_bb99_9, &phi_bb99_10, &phi_bb99_11, &phi_bb99_14, &phi_bb99_15, &phi_bb99_21, &phi_bb99_23, &phi_bb99_24);
    ca_.Goto(&block98, phi_bb99_7, tmp244, phi_bb99_9, phi_bb99_10, phi_bb99_11, phi_bb99_14, phi_bb99_15, phi_bb99_21);
  }

  TNode<IntPtrT> phi_bb98_7;
  TNode<IntPtrT> phi_bb98_8;
  TNode<IntPtrT> phi_bb98_9;
  TNode<IntPtrT> phi_bb98_10;
  TNode<IntPtrT> phi_bb98_11;
  TNode<IntPtrT> phi_bb98_14;
  TNode<BoolT> phi_bb98_15;
  TNode<IntPtrT> phi_bb98_21;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_7, &phi_bb98_8, &phi_bb98_9, &phi_bb98_10, &phi_bb98_11, &phi_bb98_14, &phi_bb98_15, &phi_bb98_21);
    ca_.Goto(&block75, phi_bb98_7, phi_bb98_8, phi_bb98_9, phi_bb98_10, phi_bb98_11, phi_bb98_14, phi_bb98_15, phi_bb98_21);
  }

  TNode<IntPtrT> phi_bb75_7;
  TNode<IntPtrT> phi_bb75_8;
  TNode<IntPtrT> phi_bb75_9;
  TNode<IntPtrT> phi_bb75_10;
  TNode<IntPtrT> phi_bb75_11;
  TNode<IntPtrT> phi_bb75_14;
  TNode<BoolT> phi_bb75_15;
  TNode<IntPtrT> phi_bb75_21;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_7, &phi_bb75_8, &phi_bb75_9, &phi_bb75_10, &phi_bb75_11, &phi_bb75_14, &phi_bb75_15, &phi_bb75_21);
    ca_.Goto(&block63, phi_bb75_7, phi_bb75_8, phi_bb75_9, phi_bb75_10, phi_bb75_11, phi_bb75_14, phi_bb75_15, phi_bb75_21);
  }

  TNode<IntPtrT> phi_bb63_7;
  TNode<IntPtrT> phi_bb63_8;
  TNode<IntPtrT> phi_bb63_9;
  TNode<IntPtrT> phi_bb63_10;
  TNode<IntPtrT> phi_bb63_11;
  TNode<IntPtrT> phi_bb63_14;
  TNode<BoolT> phi_bb63_15;
  TNode<IntPtrT> phi_bb63_21;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_7, &phi_bb63_8, &phi_bb63_9, &phi_bb63_10, &phi_bb63_11, &phi_bb63_14, &phi_bb63_15, &phi_bb63_21);
    ca_.Goto(&block51, phi_bb63_7, phi_bb63_8, phi_bb63_9, phi_bb63_10, phi_bb63_11, phi_bb63_14, phi_bb63_15, phi_bb63_21);
  }

  TNode<IntPtrT> phi_bb51_7;
  TNode<IntPtrT> phi_bb51_8;
  TNode<IntPtrT> phi_bb51_9;
  TNode<IntPtrT> phi_bb51_10;
  TNode<IntPtrT> phi_bb51_11;
  TNode<IntPtrT> phi_bb51_14;
  TNode<BoolT> phi_bb51_15;
  TNode<IntPtrT> phi_bb51_21;
  TNode<IntPtrT> tmp273;
  TNode<IntPtrT> tmp274;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_7, &phi_bb51_8, &phi_bb51_9, &phi_bb51_10, &phi_bb51_11, &phi_bb51_14, &phi_bb51_15, &phi_bb51_21);
    tmp273 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp274 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb51_21}, TNode<IntPtrT>{tmp273});
    ca_.Goto(&block46, phi_bb51_7, phi_bb51_8, phi_bb51_9, phi_bb51_10, phi_bb51_11, phi_bb51_14, phi_bb51_15, tmp274);
  }

  TNode<IntPtrT> phi_bb45_7;
  TNode<IntPtrT> phi_bb45_8;
  TNode<IntPtrT> phi_bb45_9;
  TNode<IntPtrT> phi_bb45_10;
  TNode<IntPtrT> phi_bb45_11;
  TNode<IntPtrT> phi_bb45_14;
  TNode<BoolT> phi_bb45_15;
  TNode<IntPtrT> phi_bb45_21;
  TNode<BoolT> tmp275;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_7, &phi_bb45_8, &phi_bb45_9, &phi_bb45_10, &phi_bb45_11, &phi_bb45_14, &phi_bb45_15, &phi_bb45_21);
    tmp275 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb45_15});
    ca_.Branch(tmp275, &block112, std::vector<compiler::Node*>{phi_bb45_7, phi_bb45_8, phi_bb45_9, phi_bb45_10, phi_bb45_11, phi_bb45_14, phi_bb45_15}, &block113, std::vector<compiler::Node*>{phi_bb45_7, phi_bb45_8, phi_bb45_9, phi_bb45_10, phi_bb45_11, phi_bb45_14, phi_bb45_15});
  }

  TNode<IntPtrT> phi_bb112_7;
  TNode<IntPtrT> phi_bb112_8;
  TNode<IntPtrT> phi_bb112_9;
  TNode<IntPtrT> phi_bb112_10;
  TNode<IntPtrT> phi_bb112_11;
  TNode<IntPtrT> phi_bb112_14;
  TNode<BoolT> phi_bb112_15;
  TNode<IntPtrT> tmp276;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_7, &phi_bb112_8, &phi_bb112_9, &phi_bb112_10, &phi_bb112_11, &phi_bb112_14, &phi_bb112_15);
    tmp276 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block113, phi_bb112_7, phi_bb112_8, phi_bb112_9, phi_bb112_10, phi_bb112_11, tmp276, phi_bb112_15);
  }

  TNode<IntPtrT> phi_bb113_7;
  TNode<IntPtrT> phi_bb113_8;
  TNode<IntPtrT> phi_bb113_9;
  TNode<IntPtrT> phi_bb113_10;
  TNode<IntPtrT> phi_bb113_11;
  TNode<IntPtrT> phi_bb113_14;
  TNode<BoolT> phi_bb113_15;
  TNode<IntPtrT> tmp277;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_7, &phi_bb113_8, &phi_bb113_9, &phi_bb113_10, &phi_bb113_11, &phi_bb113_14, &phi_bb113_15);
    tmp277 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block116, phi_bb113_7, phi_bb113_8, phi_bb113_9, phi_bb113_10, phi_bb113_11, phi_bb113_14, phi_bb113_15, tmp277);
  }

  TNode<IntPtrT> phi_bb116_7;
  TNode<IntPtrT> phi_bb116_8;
  TNode<IntPtrT> phi_bb116_9;
  TNode<IntPtrT> phi_bb116_10;
  TNode<IntPtrT> phi_bb116_11;
  TNode<IntPtrT> phi_bb116_14;
  TNode<BoolT> phi_bb116_15;
  TNode<IntPtrT> phi_bb116_21;
  TNode<IntPtrT> tmp278;
  TNode<BoolT> tmp279;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_7, &phi_bb116_8, &phi_bb116_9, &phi_bb116_10, &phi_bb116_11, &phi_bb116_14, &phi_bb116_15, &phi_bb116_21);
    tmp278 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp3});
    tmp279 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb116_21}, TNode<IntPtrT>{tmp278});
    ca_.Branch(tmp279, &block114, std::vector<compiler::Node*>{phi_bb116_7, phi_bb116_8, phi_bb116_9, phi_bb116_10, phi_bb116_11, phi_bb116_14, phi_bb116_15, phi_bb116_21}, &block115, std::vector<compiler::Node*>{phi_bb116_7, phi_bb116_8, phi_bb116_9, phi_bb116_10, phi_bb116_11, phi_bb116_14, phi_bb116_15, phi_bb116_21});
  }

  TNode<IntPtrT> phi_bb114_7;
  TNode<IntPtrT> phi_bb114_8;
  TNode<IntPtrT> phi_bb114_9;
  TNode<IntPtrT> phi_bb114_10;
  TNode<IntPtrT> phi_bb114_11;
  TNode<IntPtrT> phi_bb114_14;
  TNode<BoolT> phi_bb114_15;
  TNode<IntPtrT> phi_bb114_21;
  TNode<IntPtrT> tmp280;
  TNode<IntPtrT> tmp281;
  TNode<Union<HeapObject, TaggedIndex>> tmp282;
  TNode<IntPtrT> tmp283;
  TNode<Uint32T> tmp284;
  TNode<Uint32T> tmp285;
  TNode<Uint32T> tmp286;
  TNode<Uint32T> tmp287;
  TNode<BoolT> tmp288;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_7, &phi_bb114_8, &phi_bb114_9, &phi_bb114_10, &phi_bb114_11, &phi_bb114_14, &phi_bb114_15, &phi_bb114_21);
    tmp280 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{phi_bb114_21});
    tmp281 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp121}, TNode<IntPtrT>{tmp280});
    std::tie(tmp282, tmp283) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp120}, TNode<IntPtrT>{tmp281}).Flatten();
    tmp284 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp282, tmp283});
    tmp285 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp286 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp284}, TNode<Uint32T>{tmp285});
    tmp287 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp288 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp286}, TNode<Uint32T>{tmp287});
    ca_.Branch(tmp288, &block119, std::vector<compiler::Node*>{phi_bb114_7, phi_bb114_8, phi_bb114_9, phi_bb114_10, phi_bb114_11, phi_bb114_14, phi_bb114_15, phi_bb114_21}, &block120, std::vector<compiler::Node*>{phi_bb114_7, phi_bb114_8, phi_bb114_9, phi_bb114_10, phi_bb114_11, phi_bb114_14, phi_bb114_15, phi_bb114_21});
  }

  TNode<IntPtrT> phi_bb119_7;
  TNode<IntPtrT> phi_bb119_8;
  TNode<IntPtrT> phi_bb119_9;
  TNode<IntPtrT> phi_bb119_10;
  TNode<IntPtrT> phi_bb119_11;
  TNode<IntPtrT> phi_bb119_14;
  TNode<BoolT> phi_bb119_15;
  TNode<IntPtrT> phi_bb119_21;
  TNode<IntPtrT> tmp289;
  TNode<IntPtrT> tmp290;
  TNode<IntPtrT> tmp291;
  TNode<BoolT> tmp292;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_7, &phi_bb119_8, &phi_bb119_9, &phi_bb119_10, &phi_bb119_11, &phi_bb119_14, &phi_bb119_15, &phi_bb119_21);
    tmp289 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp290 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb119_7}, TNode<IntPtrT>{tmp289});
    tmp291 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp292 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb119_7}, TNode<IntPtrT>{tmp291});
    ca_.Branch(tmp292, &block122, std::vector<compiler::Node*>{phi_bb119_8, phi_bb119_9, phi_bb119_10, phi_bb119_11, phi_bb119_14, phi_bb119_15, phi_bb119_21}, &block123, std::vector<compiler::Node*>{phi_bb119_8, phi_bb119_9, phi_bb119_10, phi_bb119_11, phi_bb119_14, phi_bb119_15, phi_bb119_21});
  }

  TNode<IntPtrT> phi_bb122_8;
  TNode<IntPtrT> phi_bb122_9;
  TNode<IntPtrT> phi_bb122_10;
  TNode<IntPtrT> phi_bb122_11;
  TNode<IntPtrT> phi_bb122_14;
  TNode<BoolT> phi_bb122_15;
  TNode<IntPtrT> phi_bb122_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp293;
  TNode<IntPtrT> tmp294;
  TNode<IntPtrT> tmp295;
  TNode<IntPtrT> tmp296;
  if (block122.is_used()) {
    ca_.Bind(&block122, &phi_bb122_8, &phi_bb122_9, &phi_bb122_10, &phi_bb122_11, &phi_bb122_14, &phi_bb122_15, &phi_bb122_21);
    std::tie(tmp293, tmp294) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb122_9}).Flatten();
    tmp295 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp296 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb122_9}, TNode<IntPtrT>{tmp295});
    ca_.Goto(&block121, phi_bb122_8, tmp296, phi_bb122_10, phi_bb122_11, phi_bb122_14, phi_bb122_15, phi_bb122_21, tmp293, tmp294);
  }

  TNode<IntPtrT> phi_bb123_8;
  TNode<IntPtrT> phi_bb123_9;
  TNode<IntPtrT> phi_bb123_10;
  TNode<IntPtrT> phi_bb123_11;
  TNode<IntPtrT> phi_bb123_14;
  TNode<BoolT> phi_bb123_15;
  TNode<IntPtrT> phi_bb123_21;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_8, &phi_bb123_9, &phi_bb123_10, &phi_bb123_11, &phi_bb123_14, &phi_bb123_15, &phi_bb123_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block125, phi_bb123_8, phi_bb123_9, phi_bb123_10, phi_bb123_11, phi_bb123_14, phi_bb123_15, phi_bb123_21);
    } else {
      ca_.Goto(&block126, phi_bb123_8, phi_bb123_9, phi_bb123_10, phi_bb123_11, phi_bb123_14, phi_bb123_15, phi_bb123_21);
    }
  }

  TNode<IntPtrT> phi_bb125_8;
  TNode<IntPtrT> phi_bb125_9;
  TNode<IntPtrT> phi_bb125_10;
  TNode<IntPtrT> phi_bb125_11;
  TNode<IntPtrT> phi_bb125_14;
  TNode<BoolT> phi_bb125_15;
  TNode<IntPtrT> phi_bb125_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<IntPtrT> tmp299;
  TNode<IntPtrT> tmp300;
  if (block125.is_used()) {
    ca_.Bind(&block125, &phi_bb125_8, &phi_bb125_9, &phi_bb125_10, &phi_bb125_11, &phi_bb125_14, &phi_bb125_15, &phi_bb125_21);
    std::tie(tmp297, tmp298) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb125_11}).Flatten();
    tmp299 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp300 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb125_11}, TNode<IntPtrT>{tmp299});
    ca_.Goto(&block124, phi_bb125_8, phi_bb125_9, phi_bb125_10, tmp300, phi_bb125_14, phi_bb125_15, phi_bb125_21, tmp297, tmp298);
  }

  TNode<IntPtrT> phi_bb126_8;
  TNode<IntPtrT> phi_bb126_9;
  TNode<IntPtrT> phi_bb126_10;
  TNode<IntPtrT> phi_bb126_11;
  TNode<IntPtrT> phi_bb126_14;
  TNode<BoolT> phi_bb126_15;
  TNode<IntPtrT> phi_bb126_21;
  TNode<IntPtrT> tmp301;
  TNode<BoolT> tmp302;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_8, &phi_bb126_9, &phi_bb126_10, &phi_bb126_11, &phi_bb126_14, &phi_bb126_15, &phi_bb126_21);
    tmp301 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp302 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb126_14}, TNode<IntPtrT>{tmp301});
    ca_.Branch(tmp302, &block128, std::vector<compiler::Node*>{phi_bb126_8, phi_bb126_9, phi_bb126_10, phi_bb126_11, phi_bb126_14, phi_bb126_15, phi_bb126_21}, &block129, std::vector<compiler::Node*>{phi_bb126_8, phi_bb126_9, phi_bb126_10, phi_bb126_11, phi_bb126_14, phi_bb126_15, phi_bb126_21});
  }

  TNode<IntPtrT> phi_bb128_8;
  TNode<IntPtrT> phi_bb128_9;
  TNode<IntPtrT> phi_bb128_10;
  TNode<IntPtrT> phi_bb128_11;
  TNode<IntPtrT> phi_bb128_14;
  TNode<BoolT> phi_bb128_15;
  TNode<IntPtrT> phi_bb128_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp303;
  TNode<IntPtrT> tmp304;
  TNode<IntPtrT> tmp305;
  TNode<BoolT> tmp306;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_8, &phi_bb128_9, &phi_bb128_10, &phi_bb128_11, &phi_bb128_14, &phi_bb128_15, &phi_bb128_21);
    std::tie(tmp303, tmp304) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb128_14}).Flatten();
    tmp305 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp306 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block124, phi_bb128_8, phi_bb128_9, phi_bb128_10, phi_bb128_11, tmp305, tmp306, phi_bb128_21, tmp303, tmp304);
  }

  TNode<IntPtrT> phi_bb129_8;
  TNode<IntPtrT> phi_bb129_9;
  TNode<IntPtrT> phi_bb129_10;
  TNode<IntPtrT> phi_bb129_11;
  TNode<IntPtrT> phi_bb129_14;
  TNode<BoolT> phi_bb129_15;
  TNode<IntPtrT> phi_bb129_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp307;
  TNode<IntPtrT> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<IntPtrT> tmp310;
  TNode<IntPtrT> tmp311;
  TNode<IntPtrT> tmp312;
  TNode<BoolT> tmp313;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_8, &phi_bb129_9, &phi_bb129_10, &phi_bb129_11, &phi_bb129_14, &phi_bb129_15, &phi_bb129_21);
    std::tie(tmp307, tmp308) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{phi_bb129_11}).Flatten();
    tmp309 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp310 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb129_11}, TNode<IntPtrT>{tmp309});
    tmp311 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp312 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp310}, TNode<IntPtrT>{tmp311});
    tmp313 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block124, phi_bb129_8, phi_bb129_9, phi_bb129_10, tmp312, tmp310, tmp313, phi_bb129_21, tmp307, tmp308);
  }

  TNode<IntPtrT> phi_bb124_8;
  TNode<IntPtrT> phi_bb124_9;
  TNode<IntPtrT> phi_bb124_10;
  TNode<IntPtrT> phi_bb124_11;
  TNode<IntPtrT> phi_bb124_14;
  TNode<BoolT> phi_bb124_15;
  TNode<IntPtrT> phi_bb124_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb124_23;
  TNode<IntPtrT> phi_bb124_24;
  if (block124.is_used()) {
    ca_.Bind(&block124, &phi_bb124_8, &phi_bb124_9, &phi_bb124_10, &phi_bb124_11, &phi_bb124_14, &phi_bb124_15, &phi_bb124_21, &phi_bb124_23, &phi_bb124_24);
    ca_.Goto(&block121, phi_bb124_8, phi_bb124_9, phi_bb124_10, phi_bb124_11, phi_bb124_14, phi_bb124_15, phi_bb124_21, phi_bb124_23, phi_bb124_24);
  }

  TNode<IntPtrT> phi_bb121_8;
  TNode<IntPtrT> phi_bb121_9;
  TNode<IntPtrT> phi_bb121_10;
  TNode<IntPtrT> phi_bb121_11;
  TNode<IntPtrT> phi_bb121_14;
  TNode<BoolT> phi_bb121_15;
  TNode<IntPtrT> phi_bb121_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb121_23;
  TNode<IntPtrT> phi_bb121_24;
  TNode<IntPtrT> tmp314;
  TNode<Object> tmp315;
  TNode<Union<HeapObject, TaggedIndex>> tmp316;
  TNode<IntPtrT> tmp317;
  TNode<IntPtrT> tmp318;
  TNode<UintPtrT> tmp319;
  TNode<UintPtrT> tmp320;
  TNode<BoolT> tmp321;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_8, &phi_bb121_9, &phi_bb121_10, &phi_bb121_11, &phi_bb121_14, &phi_bb121_15, &phi_bb121_21, &phi_bb121_23, &phi_bb121_24);
    tmp314 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb121_23, phi_bb121_24});
    tmp315 = CodeStubAssembler(state_).BitcastWordToTagged(TNode<IntPtrT>{tmp314});
    std::tie(tmp316, tmp317, tmp318) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp319 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb121_21});
    tmp320 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp318});
    tmp321 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp319}, TNode<UintPtrT>{tmp320});
    ca_.Branch(tmp321, &block134, std::vector<compiler::Node*>{phi_bb121_8, phi_bb121_9, phi_bb121_10, phi_bb121_11, phi_bb121_14, phi_bb121_15, phi_bb121_21, phi_bb121_23, phi_bb121_24, phi_bb121_21, phi_bb121_21, phi_bb121_21, phi_bb121_21}, &block135, std::vector<compiler::Node*>{phi_bb121_8, phi_bb121_9, phi_bb121_10, phi_bb121_11, phi_bb121_14, phi_bb121_15, phi_bb121_21, phi_bb121_23, phi_bb121_24, phi_bb121_21, phi_bb121_21, phi_bb121_21, phi_bb121_21});
  }

  TNode<IntPtrT> phi_bb134_8;
  TNode<IntPtrT> phi_bb134_9;
  TNode<IntPtrT> phi_bb134_10;
  TNode<IntPtrT> phi_bb134_11;
  TNode<IntPtrT> phi_bb134_14;
  TNode<BoolT> phi_bb134_15;
  TNode<IntPtrT> phi_bb134_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb134_23;
  TNode<IntPtrT> phi_bb134_24;
  TNode<IntPtrT> phi_bb134_31;
  TNode<IntPtrT> phi_bb134_32;
  TNode<IntPtrT> phi_bb134_36;
  TNode<IntPtrT> phi_bb134_37;
  TNode<IntPtrT> tmp322;
  TNode<IntPtrT> tmp323;
  TNode<Union<HeapObject, TaggedIndex>> tmp324;
  TNode<IntPtrT> tmp325;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_8, &phi_bb134_9, &phi_bb134_10, &phi_bb134_11, &phi_bb134_14, &phi_bb134_15, &phi_bb134_21, &phi_bb134_23, &phi_bb134_24, &phi_bb134_31, &phi_bb134_32, &phi_bb134_36, &phi_bb134_37);
    tmp322 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb134_37});
    tmp323 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp317}, TNode<IntPtrT>{tmp322});
    std::tie(tmp324, tmp325) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp316}, TNode<IntPtrT>{tmp323}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp324, tmp325}, tmp315);
    ca_.Goto(&block120, tmp290, phi_bb134_8, phi_bb134_9, phi_bb134_10, phi_bb134_11, phi_bb134_14, phi_bb134_15, phi_bb134_21);
  }

  TNode<IntPtrT> phi_bb135_8;
  TNode<IntPtrT> phi_bb135_9;
  TNode<IntPtrT> phi_bb135_10;
  TNode<IntPtrT> phi_bb135_11;
  TNode<IntPtrT> phi_bb135_14;
  TNode<BoolT> phi_bb135_15;
  TNode<IntPtrT> phi_bb135_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb135_23;
  TNode<IntPtrT> phi_bb135_24;
  TNode<IntPtrT> phi_bb135_31;
  TNode<IntPtrT> phi_bb135_32;
  TNode<IntPtrT> phi_bb135_36;
  TNode<IntPtrT> phi_bb135_37;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_8, &phi_bb135_9, &phi_bb135_10, &phi_bb135_11, &phi_bb135_14, &phi_bb135_15, &phi_bb135_21, &phi_bb135_23, &phi_bb135_24, &phi_bb135_31, &phi_bb135_32, &phi_bb135_36, &phi_bb135_37);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb120_7;
  TNode<IntPtrT> phi_bb120_8;
  TNode<IntPtrT> phi_bb120_9;
  TNode<IntPtrT> phi_bb120_10;
  TNode<IntPtrT> phi_bb120_11;
  TNode<IntPtrT> phi_bb120_14;
  TNode<BoolT> phi_bb120_15;
  TNode<IntPtrT> phi_bb120_21;
  TNode<IntPtrT> tmp326;
  TNode<IntPtrT> tmp327;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_7, &phi_bb120_8, &phi_bb120_9, &phi_bb120_10, &phi_bb120_11, &phi_bb120_14, &phi_bb120_15, &phi_bb120_21);
    tmp326 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp327 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb120_21}, TNode<IntPtrT>{tmp326});
    ca_.Goto(&block116, phi_bb120_7, phi_bb120_8, phi_bb120_9, phi_bb120_10, phi_bb120_11, phi_bb120_14, phi_bb120_15, tmp327);
  }

  TNode<IntPtrT> phi_bb115_7;
  TNode<IntPtrT> phi_bb115_8;
  TNode<IntPtrT> phi_bb115_9;
  TNode<IntPtrT> phi_bb115_10;
  TNode<IntPtrT> phi_bb115_11;
  TNode<IntPtrT> phi_bb115_14;
  TNode<BoolT> phi_bb115_15;
  TNode<IntPtrT> phi_bb115_21;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_7, &phi_bb115_8, &phi_bb115_9, &phi_bb115_10, &phi_bb115_11, &phi_bb115_14, &phi_bb115_15, &phi_bb115_21);
    ca_.Goto(&block43, phi_bb115_7, phi_bb115_8, phi_bb115_9, phi_bb115_10, phi_bb115_11, phi_bb115_14, phi_bb115_15);
  }

  TNode<IntPtrT> phi_bb43_7;
  TNode<IntPtrT> phi_bb43_8;
  TNode<IntPtrT> phi_bb43_9;
  TNode<IntPtrT> phi_bb43_10;
  TNode<IntPtrT> phi_bb43_11;
  TNode<IntPtrT> phi_bb43_14;
  TNode<BoolT> phi_bb43_15;
  TNode<IntPtrT> tmp328;
  TNode<BoolT> tmp329;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_7, &phi_bb43_8, &phi_bb43_9, &phi_bb43_10, &phi_bb43_11, &phi_bb43_14, &phi_bb43_15);
    tmp328 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp329 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp111}, TNode<IntPtrT>{tmp328});
    ca_.Branch(tmp329, &block141, std::vector<compiler::Node*>{phi_bb43_7, phi_bb43_8, phi_bb43_9, phi_bb43_10, phi_bb43_11, phi_bb43_14, phi_bb43_15}, &block142, std::vector<compiler::Node*>{phi_bb43_7, phi_bb43_8, phi_bb43_9, phi_bb43_10, phi_bb43_11, phi_bb43_14, phi_bb43_15});
  }

  TNode<IntPtrT> phi_bb141_7;
  TNode<IntPtrT> phi_bb141_8;
  TNode<IntPtrT> phi_bb141_9;
  TNode<IntPtrT> phi_bb141_10;
  TNode<IntPtrT> phi_bb141_11;
  TNode<IntPtrT> phi_bb141_14;
  TNode<BoolT> phi_bb141_15;
  TNode<BoolT> tmp330;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_7, &phi_bb141_8, &phi_bb141_9, &phi_bb141_10, &phi_bb141_11, &phi_bb141_14, &phi_bb141_15);
    tmp330 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block143, phi_bb141_7, phi_bb141_8, phi_bb141_9, phi_bb141_10, phi_bb141_11, phi_bb141_14, phi_bb141_15, tmp330);
  }

  TNode<IntPtrT> phi_bb142_7;
  TNode<IntPtrT> phi_bb142_8;
  TNode<IntPtrT> phi_bb142_9;
  TNode<IntPtrT> phi_bb142_10;
  TNode<IntPtrT> phi_bb142_11;
  TNode<IntPtrT> phi_bb142_14;
  TNode<BoolT> phi_bb142_15;
  TNode<BoolT> tmp331;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_7, &phi_bb142_8, &phi_bb142_9, &phi_bb142_10, &phi_bb142_11, &phi_bb142_14, &phi_bb142_15);
    tmp331 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb142_11}, TNode<IntPtrT>{tmp111});
    ca_.Goto(&block143, phi_bb142_7, phi_bb142_8, phi_bb142_9, phi_bb142_10, phi_bb142_11, phi_bb142_14, phi_bb142_15, tmp331);
  }

  TNode<IntPtrT> phi_bb143_7;
  TNode<IntPtrT> phi_bb143_8;
  TNode<IntPtrT> phi_bb143_9;
  TNode<IntPtrT> phi_bb143_10;
  TNode<IntPtrT> phi_bb143_11;
  TNode<IntPtrT> phi_bb143_14;
  TNode<BoolT> phi_bb143_15;
  TNode<BoolT> phi_bb143_22;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_7, &phi_bb143_8, &phi_bb143_9, &phi_bb143_10, &phi_bb143_11, &phi_bb143_14, &phi_bb143_15, &phi_bb143_22);
    ca_.Branch(phi_bb143_22, &block139, std::vector<compiler::Node*>{phi_bb143_7, phi_bb143_8, phi_bb143_9, phi_bb143_10, phi_bb143_11, phi_bb143_14, phi_bb143_15}, &block140, std::vector<compiler::Node*>{phi_bb143_7, phi_bb143_8, phi_bb143_9, phi_bb143_10, phi_bb143_11, phi_bb143_14, phi_bb143_15});
  }

  TNode<IntPtrT> phi_bb140_7;
  TNode<IntPtrT> phi_bb140_8;
  TNode<IntPtrT> phi_bb140_9;
  TNode<IntPtrT> phi_bb140_10;
  TNode<IntPtrT> phi_bb140_11;
  TNode<IntPtrT> phi_bb140_14;
  TNode<BoolT> phi_bb140_15;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_7, &phi_bb140_8, &phi_bb140_9, &phi_bb140_10, &phi_bb140_11, &phi_bb140_14, &phi_bb140_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 379});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.paramBufferEnd == 0 || this.nextStack <= this.paramBufferEnd' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb139_7;
  TNode<IntPtrT> phi_bb139_8;
  TNode<IntPtrT> phi_bb139_9;
  TNode<IntPtrT> phi_bb139_10;
  TNode<IntPtrT> phi_bb139_11;
  TNode<IntPtrT> phi_bb139_14;
  TNode<BoolT> phi_bb139_15;
  TNode<IntPtrT> tmp332;
  TNode<RawPtrT> tmp333;
  TNode<IntPtrT> tmp334;
  TNode<RawPtrT> tmp335;
  TNode<Union<HeapObject, TaggedIndex>> tmp336;
  TNode<IntPtrT> tmp337;
  TNode<IntPtrT> tmp338;
  TNode<IntPtrT> tmp339;
  TNode<IntPtrT> tmp340;
  TNode<IntPtrT> tmp341;
  TNode<IntPtrT> tmp342;
  TNode<IntPtrT> tmp343;
  TNode<IntPtrT> tmp344;
  TNode<BoolT> tmp345;
  TNode<IntPtrT> tmp346;
  if (block139.is_used()) {
    ca_.Bind(&block139, &phi_bb139_7, &phi_bb139_8, &phi_bb139_9, &phi_bb139_10, &phi_bb139_11, &phi_bb139_14, &phi_bb139_15);
    tmp332 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferGPReturnRegister1);
    tmp333 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp332});
    tmp334 = FromConstexpr_intptr_constexpr_intptr_0(state_, JSToWasmWrapperFrameConstants::kWrapperBufferFPReturnRegister1);
    tmp335 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{parameter2}, TNode<IntPtrT>{tmp334});
    std::tie(tmp336, tmp337, tmp338, tmp339, tmp340, tmp341, tmp342, tmp343, tmp344, tmp345) = LocationAllocatorForReturns_0(state_, TNode<RawPtrT>{tmp333}, TNode<RawPtrT>{tmp335}, TNode<RawPtrT>{tmp99}).Flatten();
    tmp346 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block146, tmp337, tmp338, tmp339, tmp340, tmp341, tmp344, tmp345, tmp346);
  }

  TNode<IntPtrT> phi_bb146_7;
  TNode<IntPtrT> phi_bb146_8;
  TNode<IntPtrT> phi_bb146_9;
  TNode<IntPtrT> phi_bb146_10;
  TNode<IntPtrT> phi_bb146_11;
  TNode<IntPtrT> phi_bb146_14;
  TNode<BoolT> phi_bb146_15;
  TNode<IntPtrT> phi_bb146_21;
  TNode<IntPtrT> tmp347;
  TNode<BoolT> tmp348;
  if (block146.is_used()) {
    ca_.Bind(&block146, &phi_bb146_7, &phi_bb146_8, &phi_bb146_9, &phi_bb146_10, &phi_bb146_11, &phi_bb146_14, &phi_bb146_15, &phi_bb146_21);
    tmp347 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp3});
    tmp348 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb146_21}, TNode<IntPtrT>{tmp347});
    ca_.Branch(tmp348, &block144, std::vector<compiler::Node*>{phi_bb146_7, phi_bb146_8, phi_bb146_9, phi_bb146_10, phi_bb146_11, phi_bb146_14, phi_bb146_15, phi_bb146_21}, &block145, std::vector<compiler::Node*>{phi_bb146_7, phi_bb146_8, phi_bb146_9, phi_bb146_10, phi_bb146_11, phi_bb146_14, phi_bb146_15, phi_bb146_21});
  }

  TNode<IntPtrT> phi_bb144_7;
  TNode<IntPtrT> phi_bb144_8;
  TNode<IntPtrT> phi_bb144_9;
  TNode<IntPtrT> phi_bb144_10;
  TNode<IntPtrT> phi_bb144_11;
  TNode<IntPtrT> phi_bb144_14;
  TNode<BoolT> phi_bb144_15;
  TNode<IntPtrT> phi_bb144_21;
  TNode<IntPtrT> tmp349;
  TNode<IntPtrT> tmp350;
  TNode<Union<HeapObject, TaggedIndex>> tmp351;
  TNode<IntPtrT> tmp352;
  TNode<Uint32T> tmp353;
  TNode<Uint32T> tmp354;
  TNode<BoolT> tmp355;
  if (block144.is_used()) {
    ca_.Bind(&block144, &phi_bb144_7, &phi_bb144_8, &phi_bb144_9, &phi_bb144_10, &phi_bb144_11, &phi_bb144_14, &phi_bb144_15, &phi_bb144_21);
    tmp349 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{phi_bb144_21});
    tmp350 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp121}, TNode<IntPtrT>{tmp349});
    std::tie(tmp351, tmp352) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp120}, TNode<IntPtrT>{tmp350}).Flatten();
    tmp353 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp351, tmp352});
    tmp354 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp355 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp353}, TNode<Uint32T>{tmp354});
    ca_.Branch(tmp355, &block149, std::vector<compiler::Node*>{phi_bb144_7, phi_bb144_8, phi_bb144_9, phi_bb144_10, phi_bb144_11, phi_bb144_14, phi_bb144_15, phi_bb144_21}, &block150, std::vector<compiler::Node*>{phi_bb144_7, phi_bb144_8, phi_bb144_9, phi_bb144_10, phi_bb144_11, phi_bb144_14, phi_bb144_15, phi_bb144_21});
  }

  TNode<IntPtrT> phi_bb149_7;
  TNode<IntPtrT> phi_bb149_8;
  TNode<IntPtrT> phi_bb149_9;
  TNode<IntPtrT> phi_bb149_10;
  TNode<IntPtrT> phi_bb149_11;
  TNode<IntPtrT> phi_bb149_14;
  TNode<BoolT> phi_bb149_15;
  TNode<IntPtrT> phi_bb149_21;
  TNode<IntPtrT> tmp356;
  TNode<IntPtrT> tmp357;
  TNode<IntPtrT> tmp358;
  TNode<BoolT> tmp359;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_7, &phi_bb149_8, &phi_bb149_9, &phi_bb149_10, &phi_bb149_11, &phi_bb149_14, &phi_bb149_15, &phi_bb149_21);
    tmp356 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp357 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb149_7}, TNode<IntPtrT>{tmp356});
    tmp358 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp359 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb149_7}, TNode<IntPtrT>{tmp358});
    ca_.Branch(tmp359, &block153, std::vector<compiler::Node*>{phi_bb149_8, phi_bb149_9, phi_bb149_10, phi_bb149_11, phi_bb149_14, phi_bb149_15, phi_bb149_21}, &block154, std::vector<compiler::Node*>{phi_bb149_8, phi_bb149_9, phi_bb149_10, phi_bb149_11, phi_bb149_14, phi_bb149_15, phi_bb149_21});
  }

  TNode<IntPtrT> phi_bb153_8;
  TNode<IntPtrT> phi_bb153_9;
  TNode<IntPtrT> phi_bb153_10;
  TNode<IntPtrT> phi_bb153_11;
  TNode<IntPtrT> phi_bb153_14;
  TNode<BoolT> phi_bb153_15;
  TNode<IntPtrT> phi_bb153_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp360;
  TNode<IntPtrT> tmp361;
  TNode<IntPtrT> tmp362;
  TNode<IntPtrT> tmp363;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_8, &phi_bb153_9, &phi_bb153_10, &phi_bb153_11, &phi_bb153_14, &phi_bb153_15, &phi_bb153_21);
    std::tie(tmp360, tmp361) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb153_9}).Flatten();
    tmp362 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp363 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb153_9}, TNode<IntPtrT>{tmp362});
    ca_.Goto(&block152, phi_bb153_8, tmp363, phi_bb153_10, phi_bb153_11, phi_bb153_14, phi_bb153_15, phi_bb153_21, tmp360, tmp361);
  }

  TNode<IntPtrT> phi_bb154_8;
  TNode<IntPtrT> phi_bb154_9;
  TNode<IntPtrT> phi_bb154_10;
  TNode<IntPtrT> phi_bb154_11;
  TNode<IntPtrT> phi_bb154_14;
  TNode<BoolT> phi_bb154_15;
  TNode<IntPtrT> phi_bb154_21;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_8, &phi_bb154_9, &phi_bb154_10, &phi_bb154_11, &phi_bb154_14, &phi_bb154_15, &phi_bb154_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block156, phi_bb154_8, phi_bb154_9, phi_bb154_10, phi_bb154_11, phi_bb154_14, phi_bb154_15, phi_bb154_21);
    } else {
      ca_.Goto(&block157, phi_bb154_8, phi_bb154_9, phi_bb154_10, phi_bb154_11, phi_bb154_14, phi_bb154_15, phi_bb154_21);
    }
  }

  TNode<IntPtrT> phi_bb156_8;
  TNode<IntPtrT> phi_bb156_9;
  TNode<IntPtrT> phi_bb156_10;
  TNode<IntPtrT> phi_bb156_11;
  TNode<IntPtrT> phi_bb156_14;
  TNode<BoolT> phi_bb156_15;
  TNode<IntPtrT> phi_bb156_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp364;
  TNode<IntPtrT> tmp365;
  TNode<IntPtrT> tmp366;
  TNode<IntPtrT> tmp367;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_8, &phi_bb156_9, &phi_bb156_10, &phi_bb156_11, &phi_bb156_14, &phi_bb156_15, &phi_bb156_21);
    std::tie(tmp364, tmp365) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb156_11}).Flatten();
    tmp366 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp367 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb156_11}, TNode<IntPtrT>{tmp366});
    ca_.Goto(&block155, phi_bb156_8, phi_bb156_9, phi_bb156_10, tmp367, phi_bb156_14, phi_bb156_15, phi_bb156_21, tmp364, tmp365);
  }

  TNode<IntPtrT> phi_bb157_8;
  TNode<IntPtrT> phi_bb157_9;
  TNode<IntPtrT> phi_bb157_10;
  TNode<IntPtrT> phi_bb157_11;
  TNode<IntPtrT> phi_bb157_14;
  TNode<BoolT> phi_bb157_15;
  TNode<IntPtrT> phi_bb157_21;
  TNode<IntPtrT> tmp368;
  TNode<BoolT> tmp369;
  if (block157.is_used()) {
    ca_.Bind(&block157, &phi_bb157_8, &phi_bb157_9, &phi_bb157_10, &phi_bb157_11, &phi_bb157_14, &phi_bb157_15, &phi_bb157_21);
    tmp368 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp369 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb157_14}, TNode<IntPtrT>{tmp368});
    ca_.Branch(tmp369, &block159, std::vector<compiler::Node*>{phi_bb157_8, phi_bb157_9, phi_bb157_10, phi_bb157_11, phi_bb157_14, phi_bb157_15, phi_bb157_21}, &block160, std::vector<compiler::Node*>{phi_bb157_8, phi_bb157_9, phi_bb157_10, phi_bb157_11, phi_bb157_14, phi_bb157_15, phi_bb157_21});
  }

  TNode<IntPtrT> phi_bb159_8;
  TNode<IntPtrT> phi_bb159_9;
  TNode<IntPtrT> phi_bb159_10;
  TNode<IntPtrT> phi_bb159_11;
  TNode<IntPtrT> phi_bb159_14;
  TNode<BoolT> phi_bb159_15;
  TNode<IntPtrT> phi_bb159_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp370;
  TNode<IntPtrT> tmp371;
  TNode<IntPtrT> tmp372;
  TNode<BoolT> tmp373;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_8, &phi_bb159_9, &phi_bb159_10, &phi_bb159_11, &phi_bb159_14, &phi_bb159_15, &phi_bb159_21);
    std::tie(tmp370, tmp371) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb159_14}).Flatten();
    tmp372 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp373 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block155, phi_bb159_8, phi_bb159_9, phi_bb159_10, phi_bb159_11, tmp372, tmp373, phi_bb159_21, tmp370, tmp371);
  }

  TNode<IntPtrT> phi_bb160_8;
  TNode<IntPtrT> phi_bb160_9;
  TNode<IntPtrT> phi_bb160_10;
  TNode<IntPtrT> phi_bb160_11;
  TNode<IntPtrT> phi_bb160_14;
  TNode<BoolT> phi_bb160_15;
  TNode<IntPtrT> phi_bb160_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp374;
  TNode<IntPtrT> tmp375;
  TNode<IntPtrT> tmp376;
  TNode<IntPtrT> tmp377;
  TNode<IntPtrT> tmp378;
  TNode<IntPtrT> tmp379;
  TNode<BoolT> tmp380;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_8, &phi_bb160_9, &phi_bb160_10, &phi_bb160_11, &phi_bb160_14, &phi_bb160_15, &phi_bb160_21);
    std::tie(tmp374, tmp375) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb160_11}).Flatten();
    tmp376 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp377 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb160_11}, TNode<IntPtrT>{tmp376});
    tmp378 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp379 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp377}, TNode<IntPtrT>{tmp378});
    tmp380 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block155, phi_bb160_8, phi_bb160_9, phi_bb160_10, tmp379, tmp377, tmp380, phi_bb160_21, tmp374, tmp375);
  }

  TNode<IntPtrT> phi_bb155_8;
  TNode<IntPtrT> phi_bb155_9;
  TNode<IntPtrT> phi_bb155_10;
  TNode<IntPtrT> phi_bb155_11;
  TNode<IntPtrT> phi_bb155_14;
  TNode<BoolT> phi_bb155_15;
  TNode<IntPtrT> phi_bb155_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb155_23;
  TNode<IntPtrT> phi_bb155_24;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_8, &phi_bb155_9, &phi_bb155_10, &phi_bb155_11, &phi_bb155_14, &phi_bb155_15, &phi_bb155_21, &phi_bb155_23, &phi_bb155_24);
    ca_.Goto(&block152, phi_bb155_8, phi_bb155_9, phi_bb155_10, phi_bb155_11, phi_bb155_14, phi_bb155_15, phi_bb155_21, phi_bb155_23, phi_bb155_24);
  }

  TNode<IntPtrT> phi_bb152_8;
  TNode<IntPtrT> phi_bb152_9;
  TNode<IntPtrT> phi_bb152_10;
  TNode<IntPtrT> phi_bb152_11;
  TNode<IntPtrT> phi_bb152_14;
  TNode<BoolT> phi_bb152_15;
  TNode<IntPtrT> phi_bb152_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb152_23;
  TNode<IntPtrT> phi_bb152_24;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_8, &phi_bb152_9, &phi_bb152_10, &phi_bb152_11, &phi_bb152_14, &phi_bb152_15, &phi_bb152_21, &phi_bb152_23, &phi_bb152_24);
    if ((wasm::kIsBigEndian)) {
      ca_.Goto(&block161, phi_bb152_8, phi_bb152_9, phi_bb152_10, phi_bb152_11, phi_bb152_14, phi_bb152_15, phi_bb152_21, phi_bb152_23, phi_bb152_24);
    } else {
      ca_.Goto(&block162, phi_bb152_8, phi_bb152_9, phi_bb152_10, phi_bb152_11, phi_bb152_14, phi_bb152_15, phi_bb152_21, phi_bb152_23, phi_bb152_24);
    }
  }

  TNode<IntPtrT> phi_bb161_8;
  TNode<IntPtrT> phi_bb161_9;
  TNode<IntPtrT> phi_bb161_10;
  TNode<IntPtrT> phi_bb161_11;
  TNode<IntPtrT> phi_bb161_14;
  TNode<BoolT> phi_bb161_15;
  TNode<IntPtrT> phi_bb161_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb161_23;
  TNode<IntPtrT> phi_bb161_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp381;
  TNode<IntPtrT> tmp382;
  TNode<Int64T> tmp383;
  TNode<Int32T> tmp384;
  if (block161.is_used()) {
    ca_.Bind(&block161, &phi_bb161_8, &phi_bb161_9, &phi_bb161_10, &phi_bb161_11, &phi_bb161_14, &phi_bb161_15, &phi_bb161_21, &phi_bb161_23, &phi_bb161_24);
    std::tie(tmp381, tmp382) = RefCast_int64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb161_23}, TNode<IntPtrT>{phi_bb161_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp383 = CodeStubAssembler(state_).LoadReference<Int64T>(CodeStubAssembler::Reference{tmp381, tmp382});
    tmp384 = CodeStubAssembler(state_).TruncateInt64ToInt32(TNode<Int64T>{tmp383});
    ca_.Goto(&block163, phi_bb161_8, phi_bb161_9, phi_bb161_10, phi_bb161_11, phi_bb161_14, phi_bb161_15, phi_bb161_21, phi_bb161_23, phi_bb161_24, tmp384);
  }

  TNode<IntPtrT> phi_bb162_8;
  TNode<IntPtrT> phi_bb162_9;
  TNode<IntPtrT> phi_bb162_10;
  TNode<IntPtrT> phi_bb162_11;
  TNode<IntPtrT> phi_bb162_14;
  TNode<BoolT> phi_bb162_15;
  TNode<IntPtrT> phi_bb162_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb162_23;
  TNode<IntPtrT> phi_bb162_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp385;
  TNode<IntPtrT> tmp386;
  TNode<Int32T> tmp387;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_8, &phi_bb162_9, &phi_bb162_10, &phi_bb162_11, &phi_bb162_14, &phi_bb162_15, &phi_bb162_21, &phi_bb162_23, &phi_bb162_24);
    std::tie(tmp385, tmp386) = RefCast_int32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb162_23}, TNode<IntPtrT>{phi_bb162_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp387 = CodeStubAssembler(state_).LoadReference<Int32T>(CodeStubAssembler::Reference{tmp385, tmp386});
    ca_.Goto(&block163, phi_bb162_8, phi_bb162_9, phi_bb162_10, phi_bb162_11, phi_bb162_14, phi_bb162_15, phi_bb162_21, phi_bb162_23, phi_bb162_24, tmp387);
  }

  TNode<IntPtrT> phi_bb163_8;
  TNode<IntPtrT> phi_bb163_9;
  TNode<IntPtrT> phi_bb163_10;
  TNode<IntPtrT> phi_bb163_11;
  TNode<IntPtrT> phi_bb163_14;
  TNode<BoolT> phi_bb163_15;
  TNode<IntPtrT> phi_bb163_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb163_23;
  TNode<IntPtrT> phi_bb163_24;
  TNode<Int32T> phi_bb163_25;
  TNode<Union<HeapObject, TaggedIndex>> tmp388;
  TNode<IntPtrT> tmp389;
  TNode<IntPtrT> tmp390;
  TNode<UintPtrT> tmp391;
  TNode<UintPtrT> tmp392;
  TNode<BoolT> tmp393;
  if (block163.is_used()) {
    ca_.Bind(&block163, &phi_bb163_8, &phi_bb163_9, &phi_bb163_10, &phi_bb163_11, &phi_bb163_14, &phi_bb163_15, &phi_bb163_21, &phi_bb163_23, &phi_bb163_24, &phi_bb163_25);
    std::tie(tmp388, tmp389, tmp390) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp391 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb163_21});
    tmp392 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp390});
    tmp393 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp391}, TNode<UintPtrT>{tmp392});
    ca_.Branch(tmp393, &block168, std::vector<compiler::Node*>{phi_bb163_8, phi_bb163_9, phi_bb163_10, phi_bb163_11, phi_bb163_14, phi_bb163_15, phi_bb163_21, phi_bb163_23, phi_bb163_24, phi_bb163_21, phi_bb163_21, phi_bb163_21, phi_bb163_21}, &block169, std::vector<compiler::Node*>{phi_bb163_8, phi_bb163_9, phi_bb163_10, phi_bb163_11, phi_bb163_14, phi_bb163_15, phi_bb163_21, phi_bb163_23, phi_bb163_24, phi_bb163_21, phi_bb163_21, phi_bb163_21, phi_bb163_21});
  }

  TNode<IntPtrT> phi_bb168_8;
  TNode<IntPtrT> phi_bb168_9;
  TNode<IntPtrT> phi_bb168_10;
  TNode<IntPtrT> phi_bb168_11;
  TNode<IntPtrT> phi_bb168_14;
  TNode<BoolT> phi_bb168_15;
  TNode<IntPtrT> phi_bb168_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb168_23;
  TNode<IntPtrT> phi_bb168_24;
  TNode<IntPtrT> phi_bb168_30;
  TNode<IntPtrT> phi_bb168_31;
  TNode<IntPtrT> phi_bb168_35;
  TNode<IntPtrT> phi_bb168_36;
  TNode<IntPtrT> tmp394;
  TNode<IntPtrT> tmp395;
  TNode<Union<HeapObject, TaggedIndex>> tmp396;
  TNode<IntPtrT> tmp397;
  TNode<Number> tmp398;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_8, &phi_bb168_9, &phi_bb168_10, &phi_bb168_11, &phi_bb168_14, &phi_bb168_15, &phi_bb168_21, &phi_bb168_23, &phi_bb168_24, &phi_bb168_30, &phi_bb168_31, &phi_bb168_35, &phi_bb168_36);
    tmp394 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb168_36});
    tmp395 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp389}, TNode<IntPtrT>{tmp394});
    std::tie(tmp396, tmp397) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp388}, TNode<IntPtrT>{tmp395}).Flatten();
    tmp398 = Convert_Number_int32_0(state_, TNode<Int32T>{phi_bb163_25});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp396, tmp397}, tmp398);
    ca_.Goto(&block151, tmp357, phi_bb168_8, phi_bb168_9, phi_bb168_10, phi_bb168_11, phi_bb168_14, phi_bb168_15, phi_bb168_21);
  }

  TNode<IntPtrT> phi_bb169_8;
  TNode<IntPtrT> phi_bb169_9;
  TNode<IntPtrT> phi_bb169_10;
  TNode<IntPtrT> phi_bb169_11;
  TNode<IntPtrT> phi_bb169_14;
  TNode<BoolT> phi_bb169_15;
  TNode<IntPtrT> phi_bb169_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb169_23;
  TNode<IntPtrT> phi_bb169_24;
  TNode<IntPtrT> phi_bb169_30;
  TNode<IntPtrT> phi_bb169_31;
  TNode<IntPtrT> phi_bb169_35;
  TNode<IntPtrT> phi_bb169_36;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_8, &phi_bb169_9, &phi_bb169_10, &phi_bb169_11, &phi_bb169_14, &phi_bb169_15, &phi_bb169_21, &phi_bb169_23, &phi_bb169_24, &phi_bb169_30, &phi_bb169_31, &phi_bb169_35, &phi_bb169_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb150_7;
  TNode<IntPtrT> phi_bb150_8;
  TNode<IntPtrT> phi_bb150_9;
  TNode<IntPtrT> phi_bb150_10;
  TNode<IntPtrT> phi_bb150_11;
  TNode<IntPtrT> phi_bb150_14;
  TNode<BoolT> phi_bb150_15;
  TNode<IntPtrT> phi_bb150_21;
  TNode<Uint32T> tmp399;
  TNode<BoolT> tmp400;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_7, &phi_bb150_8, &phi_bb150_9, &phi_bb150_10, &phi_bb150_11, &phi_bb150_14, &phi_bb150_15, &phi_bb150_21);
    tmp399 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp400 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp353}, TNode<Uint32T>{tmp399});
    ca_.Branch(tmp400, &block172, std::vector<compiler::Node*>{phi_bb150_7, phi_bb150_8, phi_bb150_9, phi_bb150_10, phi_bb150_11, phi_bb150_14, phi_bb150_15, phi_bb150_21}, &block173, std::vector<compiler::Node*>{phi_bb150_7, phi_bb150_8, phi_bb150_9, phi_bb150_10, phi_bb150_11, phi_bb150_14, phi_bb150_15, phi_bb150_21});
  }

  TNode<IntPtrT> phi_bb172_7;
  TNode<IntPtrT> phi_bb172_8;
  TNode<IntPtrT> phi_bb172_9;
  TNode<IntPtrT> phi_bb172_10;
  TNode<IntPtrT> phi_bb172_11;
  TNode<IntPtrT> phi_bb172_14;
  TNode<BoolT> phi_bb172_15;
  TNode<IntPtrT> phi_bb172_21;
  TNode<IntPtrT> tmp401;
  TNode<IntPtrT> tmp402;
  TNode<IntPtrT> tmp403;
  TNode<BoolT> tmp404;
  if (block172.is_used()) {
    ca_.Bind(&block172, &phi_bb172_7, &phi_bb172_8, &phi_bb172_9, &phi_bb172_10, &phi_bb172_11, &phi_bb172_14, &phi_bb172_15, &phi_bb172_21);
    tmp401 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp402 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb172_8}, TNode<IntPtrT>{tmp401});
    tmp403 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp404 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb172_8}, TNode<IntPtrT>{tmp403});
    ca_.Branch(tmp404, &block176, std::vector<compiler::Node*>{phi_bb172_7, phi_bb172_9, phi_bb172_10, phi_bb172_11, phi_bb172_14, phi_bb172_15, phi_bb172_21}, &block177, std::vector<compiler::Node*>{phi_bb172_7, phi_bb172_9, phi_bb172_10, phi_bb172_11, phi_bb172_14, phi_bb172_15, phi_bb172_21});
  }

  TNode<IntPtrT> phi_bb176_7;
  TNode<IntPtrT> phi_bb176_9;
  TNode<IntPtrT> phi_bb176_10;
  TNode<IntPtrT> phi_bb176_11;
  TNode<IntPtrT> phi_bb176_14;
  TNode<BoolT> phi_bb176_15;
  TNode<IntPtrT> phi_bb176_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp405;
  TNode<IntPtrT> tmp406;
  TNode<IntPtrT> tmp407;
  TNode<IntPtrT> tmp408;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_7, &phi_bb176_9, &phi_bb176_10, &phi_bb176_11, &phi_bb176_14, &phi_bb176_15, &phi_bb176_21);
    std::tie(tmp405, tmp406) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb176_10}).Flatten();
    tmp407 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp408 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb176_10}, TNode<IntPtrT>{tmp407});
    ca_.Goto(&block175, phi_bb176_7, phi_bb176_9, tmp408, phi_bb176_11, phi_bb176_14, phi_bb176_15, phi_bb176_21, tmp405, tmp406);
  }

  TNode<IntPtrT> phi_bb177_7;
  TNode<IntPtrT> phi_bb177_9;
  TNode<IntPtrT> phi_bb177_10;
  TNode<IntPtrT> phi_bb177_11;
  TNode<IntPtrT> phi_bb177_14;
  TNode<BoolT> phi_bb177_15;
  TNode<IntPtrT> phi_bb177_21;
  if (block177.is_used()) {
    ca_.Bind(&block177, &phi_bb177_7, &phi_bb177_9, &phi_bb177_10, &phi_bb177_11, &phi_bb177_14, &phi_bb177_15, &phi_bb177_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block179, phi_bb177_7, phi_bb177_9, phi_bb177_10, phi_bb177_11, phi_bb177_14, phi_bb177_15, phi_bb177_21);
    } else {
      ca_.Goto(&block180, phi_bb177_7, phi_bb177_9, phi_bb177_10, phi_bb177_11, phi_bb177_14, phi_bb177_15, phi_bb177_21);
    }
  }

  TNode<IntPtrT> phi_bb179_7;
  TNode<IntPtrT> phi_bb179_9;
  TNode<IntPtrT> phi_bb179_10;
  TNode<IntPtrT> phi_bb179_11;
  TNode<IntPtrT> phi_bb179_14;
  TNode<BoolT> phi_bb179_15;
  TNode<IntPtrT> phi_bb179_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp409;
  TNode<IntPtrT> tmp410;
  TNode<IntPtrT> tmp411;
  TNode<IntPtrT> tmp412;
  if (block179.is_used()) {
    ca_.Bind(&block179, &phi_bb179_7, &phi_bb179_9, &phi_bb179_10, &phi_bb179_11, &phi_bb179_14, &phi_bb179_15, &phi_bb179_21);
    std::tie(tmp409, tmp410) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb179_11}).Flatten();
    tmp411 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp412 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb179_11}, TNode<IntPtrT>{tmp411});
    ca_.Goto(&block178, phi_bb179_7, phi_bb179_9, phi_bb179_10, tmp412, phi_bb179_14, phi_bb179_15, phi_bb179_21, tmp409, tmp410);
  }

  TNode<IntPtrT> phi_bb180_7;
  TNode<IntPtrT> phi_bb180_9;
  TNode<IntPtrT> phi_bb180_10;
  TNode<IntPtrT> phi_bb180_11;
  TNode<IntPtrT> phi_bb180_14;
  TNode<BoolT> phi_bb180_15;
  TNode<IntPtrT> phi_bb180_21;
  TNode<IntPtrT> tmp413;
  TNode<BoolT> tmp414;
  if (block180.is_used()) {
    ca_.Bind(&block180, &phi_bb180_7, &phi_bb180_9, &phi_bb180_10, &phi_bb180_11, &phi_bb180_14, &phi_bb180_15, &phi_bb180_21);
    tmp413 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp414 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb180_14}, TNode<IntPtrT>{tmp413});
    ca_.Branch(tmp414, &block182, std::vector<compiler::Node*>{phi_bb180_7, phi_bb180_9, phi_bb180_10, phi_bb180_11, phi_bb180_14, phi_bb180_15, phi_bb180_21}, &block183, std::vector<compiler::Node*>{phi_bb180_7, phi_bb180_9, phi_bb180_10, phi_bb180_11, phi_bb180_14, phi_bb180_15, phi_bb180_21});
  }

  TNode<IntPtrT> phi_bb182_7;
  TNode<IntPtrT> phi_bb182_9;
  TNode<IntPtrT> phi_bb182_10;
  TNode<IntPtrT> phi_bb182_11;
  TNode<IntPtrT> phi_bb182_14;
  TNode<BoolT> phi_bb182_15;
  TNode<IntPtrT> phi_bb182_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp415;
  TNode<IntPtrT> tmp416;
  TNode<IntPtrT> tmp417;
  TNode<BoolT> tmp418;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_7, &phi_bb182_9, &phi_bb182_10, &phi_bb182_11, &phi_bb182_14, &phi_bb182_15, &phi_bb182_21);
    std::tie(tmp415, tmp416) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb182_14}).Flatten();
    tmp417 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp418 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block178, phi_bb182_7, phi_bb182_9, phi_bb182_10, phi_bb182_11, tmp417, tmp418, phi_bb182_21, tmp415, tmp416);
  }

  TNode<IntPtrT> phi_bb183_7;
  TNode<IntPtrT> phi_bb183_9;
  TNode<IntPtrT> phi_bb183_10;
  TNode<IntPtrT> phi_bb183_11;
  TNode<IntPtrT> phi_bb183_14;
  TNode<BoolT> phi_bb183_15;
  TNode<IntPtrT> phi_bb183_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp419;
  TNode<IntPtrT> tmp420;
  TNode<IntPtrT> tmp421;
  TNode<IntPtrT> tmp422;
  TNode<IntPtrT> tmp423;
  TNode<IntPtrT> tmp424;
  TNode<BoolT> tmp425;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_7, &phi_bb183_9, &phi_bb183_10, &phi_bb183_11, &phi_bb183_14, &phi_bb183_15, &phi_bb183_21);
    std::tie(tmp419, tmp420) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb183_11}).Flatten();
    tmp421 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp422 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb183_11}, TNode<IntPtrT>{tmp421});
    tmp423 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp424 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp422}, TNode<IntPtrT>{tmp423});
    tmp425 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block178, phi_bb183_7, phi_bb183_9, phi_bb183_10, tmp424, tmp422, tmp425, phi_bb183_21, tmp419, tmp420);
  }

  TNode<IntPtrT> phi_bb178_7;
  TNode<IntPtrT> phi_bb178_9;
  TNode<IntPtrT> phi_bb178_10;
  TNode<IntPtrT> phi_bb178_11;
  TNode<IntPtrT> phi_bb178_14;
  TNode<BoolT> phi_bb178_15;
  TNode<IntPtrT> phi_bb178_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb178_23;
  TNode<IntPtrT> phi_bb178_24;
  if (block178.is_used()) {
    ca_.Bind(&block178, &phi_bb178_7, &phi_bb178_9, &phi_bb178_10, &phi_bb178_11, &phi_bb178_14, &phi_bb178_15, &phi_bb178_21, &phi_bb178_23, &phi_bb178_24);
    ca_.Goto(&block175, phi_bb178_7, phi_bb178_9, phi_bb178_10, phi_bb178_11, phi_bb178_14, phi_bb178_15, phi_bb178_21, phi_bb178_23, phi_bb178_24);
  }

  TNode<IntPtrT> phi_bb175_7;
  TNode<IntPtrT> phi_bb175_9;
  TNode<IntPtrT> phi_bb175_10;
  TNode<IntPtrT> phi_bb175_11;
  TNode<IntPtrT> phi_bb175_14;
  TNode<BoolT> phi_bb175_15;
  TNode<IntPtrT> phi_bb175_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb175_23;
  TNode<IntPtrT> phi_bb175_24;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_7, &phi_bb175_9, &phi_bb175_10, &phi_bb175_11, &phi_bb175_14, &phi_bb175_15, &phi_bb175_21, &phi_bb175_23, &phi_bb175_24);
    if ((wasm::kIsFpAlwaysDouble)) {
      ca_.Goto(&block184, phi_bb175_7, phi_bb175_9, phi_bb175_10, phi_bb175_11, phi_bb175_14, phi_bb175_15, phi_bb175_21, phi_bb175_23, phi_bb175_24);
    } else {
      ca_.Goto(&block185, phi_bb175_7, phi_bb175_9, phi_bb175_10, phi_bb175_11, phi_bb175_14, phi_bb175_15, phi_bb175_21, phi_bb175_23, phi_bb175_24);
    }
  }

  TNode<IntPtrT> phi_bb184_7;
  TNode<IntPtrT> phi_bb184_9;
  TNode<IntPtrT> phi_bb184_10;
  TNode<IntPtrT> phi_bb184_11;
  TNode<IntPtrT> phi_bb184_14;
  TNode<BoolT> phi_bb184_15;
  TNode<IntPtrT> phi_bb184_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb184_23;
  TNode<IntPtrT> phi_bb184_24;
  TNode<IntPtrT> tmp426;
  TNode<BoolT> tmp427;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_7, &phi_bb184_9, &phi_bb184_10, &phi_bb184_11, &phi_bb184_14, &phi_bb184_15, &phi_bb184_21, &phi_bb184_23, &phi_bb184_24);
    tmp426 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp427 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp402}, TNode<IntPtrT>{tmp426});
    ca_.Branch(tmp427, &block187, std::vector<compiler::Node*>{phi_bb184_7, phi_bb184_9, phi_bb184_10, phi_bb184_11, phi_bb184_14, phi_bb184_15, phi_bb184_21, phi_bb184_23, phi_bb184_24}, &block188, std::vector<compiler::Node*>{phi_bb184_7, phi_bb184_9, phi_bb184_10, phi_bb184_11, phi_bb184_14, phi_bb184_15, phi_bb184_21, phi_bb184_23, phi_bb184_24});
  }

  TNode<IntPtrT> phi_bb187_7;
  TNode<IntPtrT> phi_bb187_9;
  TNode<IntPtrT> phi_bb187_10;
  TNode<IntPtrT> phi_bb187_11;
  TNode<IntPtrT> phi_bb187_14;
  TNode<BoolT> phi_bb187_15;
  TNode<IntPtrT> phi_bb187_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb187_23;
  TNode<IntPtrT> phi_bb187_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp428;
  TNode<IntPtrT> tmp429;
  TNode<Float64T> tmp430;
  TNode<Float32T> tmp431;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_7, &phi_bb187_9, &phi_bb187_10, &phi_bb187_11, &phi_bb187_14, &phi_bb187_15, &phi_bb187_21, &phi_bb187_23, &phi_bb187_24);
    std::tie(tmp428, tmp429) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb187_23}, TNode<IntPtrT>{phi_bb187_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp430 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp428, tmp429});
    tmp431 = CodeStubAssembler(state_).TruncateFloat64ToFloat32(TNode<Float64T>{tmp430});
    ca_.Goto(&block190, phi_bb187_7, phi_bb187_9, phi_bb187_10, phi_bb187_11, phi_bb187_14, phi_bb187_15, phi_bb187_21, phi_bb187_23, phi_bb187_24, tmp431);
  }

  TNode<IntPtrT> phi_bb188_7;
  TNode<IntPtrT> phi_bb188_9;
  TNode<IntPtrT> phi_bb188_10;
  TNode<IntPtrT> phi_bb188_11;
  TNode<IntPtrT> phi_bb188_14;
  TNode<BoolT> phi_bb188_15;
  TNode<IntPtrT> phi_bb188_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb188_23;
  TNode<IntPtrT> phi_bb188_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp432;
  TNode<IntPtrT> tmp433;
  TNode<Float32T> tmp434;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_7, &phi_bb188_9, &phi_bb188_10, &phi_bb188_11, &phi_bb188_14, &phi_bb188_15, &phi_bb188_21, &phi_bb188_23, &phi_bb188_24);
    std::tie(tmp432, tmp433) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb188_23}, TNode<IntPtrT>{phi_bb188_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp434 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp432, tmp433});
    ca_.Goto(&block190, phi_bb188_7, phi_bb188_9, phi_bb188_10, phi_bb188_11, phi_bb188_14, phi_bb188_15, phi_bb188_21, phi_bb188_23, phi_bb188_24, tmp434);
  }

  TNode<IntPtrT> phi_bb190_7;
  TNode<IntPtrT> phi_bb190_9;
  TNode<IntPtrT> phi_bb190_10;
  TNode<IntPtrT> phi_bb190_11;
  TNode<IntPtrT> phi_bb190_14;
  TNode<BoolT> phi_bb190_15;
  TNode<IntPtrT> phi_bb190_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb190_23;
  TNode<IntPtrT> phi_bb190_24;
  TNode<Float32T> phi_bb190_25;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_7, &phi_bb190_9, &phi_bb190_10, &phi_bb190_11, &phi_bb190_14, &phi_bb190_15, &phi_bb190_21, &phi_bb190_23, &phi_bb190_24, &phi_bb190_25);
    ca_.Goto(&block186, phi_bb190_7, phi_bb190_9, phi_bb190_10, phi_bb190_11, phi_bb190_14, phi_bb190_15, phi_bb190_21, phi_bb190_23, phi_bb190_24, phi_bb190_25);
  }

  TNode<IntPtrT> phi_bb185_7;
  TNode<IntPtrT> phi_bb185_9;
  TNode<IntPtrT> phi_bb185_10;
  TNode<IntPtrT> phi_bb185_11;
  TNode<IntPtrT> phi_bb185_14;
  TNode<BoolT> phi_bb185_15;
  TNode<IntPtrT> phi_bb185_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb185_23;
  TNode<IntPtrT> phi_bb185_24;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_7, &phi_bb185_9, &phi_bb185_10, &phi_bb185_11, &phi_bb185_14, &phi_bb185_15, &phi_bb185_21, &phi_bb185_23, &phi_bb185_24);
    if ((wasm::kIsBigEndianOnSim)) {
      ca_.Goto(&block191, phi_bb185_7, phi_bb185_9, phi_bb185_10, phi_bb185_11, phi_bb185_14, phi_bb185_15, phi_bb185_21, phi_bb185_23, phi_bb185_24);
    } else {
      ca_.Goto(&block192, phi_bb185_7, phi_bb185_9, phi_bb185_10, phi_bb185_11, phi_bb185_14, phi_bb185_15, phi_bb185_21, phi_bb185_23, phi_bb185_24);
    }
  }

  TNode<IntPtrT> phi_bb191_7;
  TNode<IntPtrT> phi_bb191_9;
  TNode<IntPtrT> phi_bb191_10;
  TNode<IntPtrT> phi_bb191_11;
  TNode<IntPtrT> phi_bb191_14;
  TNode<BoolT> phi_bb191_15;
  TNode<IntPtrT> phi_bb191_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb191_23;
  TNode<IntPtrT> phi_bb191_24;
  TNode<IntPtrT> tmp435;
  TNode<BoolT> tmp436;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_7, &phi_bb191_9, &phi_bb191_10, &phi_bb191_11, &phi_bb191_14, &phi_bb191_15, &phi_bb191_21, &phi_bb191_23, &phi_bb191_24);
    tmp435 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp436 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp402}, TNode<IntPtrT>{tmp435});
    ca_.Branch(tmp436, &block194, std::vector<compiler::Node*>{phi_bb191_7, phi_bb191_9, phi_bb191_10, phi_bb191_11, phi_bb191_14, phi_bb191_15, phi_bb191_21, phi_bb191_23, phi_bb191_24}, &block195, std::vector<compiler::Node*>{phi_bb191_7, phi_bb191_9, phi_bb191_10, phi_bb191_11, phi_bb191_14, phi_bb191_15, phi_bb191_21, phi_bb191_23, phi_bb191_24});
  }

  TNode<IntPtrT> phi_bb194_7;
  TNode<IntPtrT> phi_bb194_9;
  TNode<IntPtrT> phi_bb194_10;
  TNode<IntPtrT> phi_bb194_11;
  TNode<IntPtrT> phi_bb194_14;
  TNode<BoolT> phi_bb194_15;
  TNode<IntPtrT> phi_bb194_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb194_23;
  TNode<IntPtrT> phi_bb194_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp437;
  TNode<IntPtrT> tmp438;
  TNode<Int64T> tmp439;
  TNode<Int64T> tmp440;
  TNode<Int64T> tmp441;
  TNode<Int32T> tmp442;
  TNode<Float32T> tmp443;
  if (block194.is_used()) {
    ca_.Bind(&block194, &phi_bb194_7, &phi_bb194_9, &phi_bb194_10, &phi_bb194_11, &phi_bb194_14, &phi_bb194_15, &phi_bb194_21, &phi_bb194_23, &phi_bb194_24);
    std::tie(tmp437, tmp438) = RefCast_int64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb194_23}, TNode<IntPtrT>{phi_bb194_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp439 = CodeStubAssembler(state_).LoadReference<Int64T>(CodeStubAssembler::Reference{tmp437, tmp438});
    tmp440 = FromConstexpr_int64_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp441 = CodeStubAssembler(state_).Word64Sar(TNode<Int64T>{tmp439}, TNode<Int64T>{tmp440});
    tmp442 = CodeStubAssembler(state_).TruncateInt64ToInt32(TNode<Int64T>{tmp441});
    tmp443 = CodeStubAssembler(state_).BitcastInt32ToFloat32(TNode<Int32T>{tmp442});
    ca_.Goto(&block197, phi_bb194_7, phi_bb194_9, phi_bb194_10, phi_bb194_11, phi_bb194_14, phi_bb194_15, phi_bb194_21, phi_bb194_23, phi_bb194_24, tmp443);
  }

  TNode<IntPtrT> phi_bb195_7;
  TNode<IntPtrT> phi_bb195_9;
  TNode<IntPtrT> phi_bb195_10;
  TNode<IntPtrT> phi_bb195_11;
  TNode<IntPtrT> phi_bb195_14;
  TNode<BoolT> phi_bb195_15;
  TNode<IntPtrT> phi_bb195_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb195_23;
  TNode<IntPtrT> phi_bb195_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp444;
  TNode<IntPtrT> tmp445;
  TNode<Float32T> tmp446;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_7, &phi_bb195_9, &phi_bb195_10, &phi_bb195_11, &phi_bb195_14, &phi_bb195_15, &phi_bb195_21, &phi_bb195_23, &phi_bb195_24);
    std::tie(tmp444, tmp445) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb195_23}, TNode<IntPtrT>{phi_bb195_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp446 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp444, tmp445});
    ca_.Goto(&block197, phi_bb195_7, phi_bb195_9, phi_bb195_10, phi_bb195_11, phi_bb195_14, phi_bb195_15, phi_bb195_21, phi_bb195_23, phi_bb195_24, tmp446);
  }

  TNode<IntPtrT> phi_bb197_7;
  TNode<IntPtrT> phi_bb197_9;
  TNode<IntPtrT> phi_bb197_10;
  TNode<IntPtrT> phi_bb197_11;
  TNode<IntPtrT> phi_bb197_14;
  TNode<BoolT> phi_bb197_15;
  TNode<IntPtrT> phi_bb197_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb197_23;
  TNode<IntPtrT> phi_bb197_24;
  TNode<Float32T> phi_bb197_25;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_7, &phi_bb197_9, &phi_bb197_10, &phi_bb197_11, &phi_bb197_14, &phi_bb197_15, &phi_bb197_21, &phi_bb197_23, &phi_bb197_24, &phi_bb197_25);
    ca_.Goto(&block193, phi_bb197_7, phi_bb197_9, phi_bb197_10, phi_bb197_11, phi_bb197_14, phi_bb197_15, phi_bb197_21, phi_bb197_23, phi_bb197_24, phi_bb197_25);
  }

  TNode<IntPtrT> phi_bb192_7;
  TNode<IntPtrT> phi_bb192_9;
  TNode<IntPtrT> phi_bb192_10;
  TNode<IntPtrT> phi_bb192_11;
  TNode<IntPtrT> phi_bb192_14;
  TNode<BoolT> phi_bb192_15;
  TNode<IntPtrT> phi_bb192_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb192_23;
  TNode<IntPtrT> phi_bb192_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp447;
  TNode<IntPtrT> tmp448;
  TNode<Float32T> tmp449;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_7, &phi_bb192_9, &phi_bb192_10, &phi_bb192_11, &phi_bb192_14, &phi_bb192_15, &phi_bb192_21, &phi_bb192_23, &phi_bb192_24);
    std::tie(tmp447, tmp448) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb192_23}, TNode<IntPtrT>{phi_bb192_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp449 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp447, tmp448});
    ca_.Goto(&block193, phi_bb192_7, phi_bb192_9, phi_bb192_10, phi_bb192_11, phi_bb192_14, phi_bb192_15, phi_bb192_21, phi_bb192_23, phi_bb192_24, tmp449);
  }

  TNode<IntPtrT> phi_bb193_7;
  TNode<IntPtrT> phi_bb193_9;
  TNode<IntPtrT> phi_bb193_10;
  TNode<IntPtrT> phi_bb193_11;
  TNode<IntPtrT> phi_bb193_14;
  TNode<BoolT> phi_bb193_15;
  TNode<IntPtrT> phi_bb193_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb193_23;
  TNode<IntPtrT> phi_bb193_24;
  TNode<Float32T> phi_bb193_25;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_7, &phi_bb193_9, &phi_bb193_10, &phi_bb193_11, &phi_bb193_14, &phi_bb193_15, &phi_bb193_21, &phi_bb193_23, &phi_bb193_24, &phi_bb193_25);
    ca_.Goto(&block186, phi_bb193_7, phi_bb193_9, phi_bb193_10, phi_bb193_11, phi_bb193_14, phi_bb193_15, phi_bb193_21, phi_bb193_23, phi_bb193_24, phi_bb193_25);
  }

  TNode<IntPtrT> phi_bb186_7;
  TNode<IntPtrT> phi_bb186_9;
  TNode<IntPtrT> phi_bb186_10;
  TNode<IntPtrT> phi_bb186_11;
  TNode<IntPtrT> phi_bb186_14;
  TNode<BoolT> phi_bb186_15;
  TNode<IntPtrT> phi_bb186_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb186_23;
  TNode<IntPtrT> phi_bb186_24;
  TNode<Float32T> phi_bb186_25;
  TNode<Union<HeapObject, TaggedIndex>> tmp450;
  TNode<IntPtrT> tmp451;
  TNode<IntPtrT> tmp452;
  TNode<UintPtrT> tmp453;
  TNode<UintPtrT> tmp454;
  TNode<BoolT> tmp455;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_7, &phi_bb186_9, &phi_bb186_10, &phi_bb186_11, &phi_bb186_14, &phi_bb186_15, &phi_bb186_21, &phi_bb186_23, &phi_bb186_24, &phi_bb186_25);
    std::tie(tmp450, tmp451, tmp452) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp453 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb186_21});
    tmp454 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp452});
    tmp455 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp453}, TNode<UintPtrT>{tmp454});
    ca_.Branch(tmp455, &block202, std::vector<compiler::Node*>{phi_bb186_7, phi_bb186_9, phi_bb186_10, phi_bb186_11, phi_bb186_14, phi_bb186_15, phi_bb186_21, phi_bb186_23, phi_bb186_24, phi_bb186_21, phi_bb186_21, phi_bb186_21, phi_bb186_21}, &block203, std::vector<compiler::Node*>{phi_bb186_7, phi_bb186_9, phi_bb186_10, phi_bb186_11, phi_bb186_14, phi_bb186_15, phi_bb186_21, phi_bb186_23, phi_bb186_24, phi_bb186_21, phi_bb186_21, phi_bb186_21, phi_bb186_21});
  }

  TNode<IntPtrT> phi_bb202_7;
  TNode<IntPtrT> phi_bb202_9;
  TNode<IntPtrT> phi_bb202_10;
  TNode<IntPtrT> phi_bb202_11;
  TNode<IntPtrT> phi_bb202_14;
  TNode<BoolT> phi_bb202_15;
  TNode<IntPtrT> phi_bb202_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb202_23;
  TNode<IntPtrT> phi_bb202_24;
  TNode<IntPtrT> phi_bb202_30;
  TNode<IntPtrT> phi_bb202_31;
  TNode<IntPtrT> phi_bb202_35;
  TNode<IntPtrT> phi_bb202_36;
  TNode<IntPtrT> tmp456;
  TNode<IntPtrT> tmp457;
  TNode<Union<HeapObject, TaggedIndex>> tmp458;
  TNode<IntPtrT> tmp459;
  TNode<Number> tmp460;
  if (block202.is_used()) {
    ca_.Bind(&block202, &phi_bb202_7, &phi_bb202_9, &phi_bb202_10, &phi_bb202_11, &phi_bb202_14, &phi_bb202_15, &phi_bb202_21, &phi_bb202_23, &phi_bb202_24, &phi_bb202_30, &phi_bb202_31, &phi_bb202_35, &phi_bb202_36);
    tmp456 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb202_36});
    tmp457 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp451}, TNode<IntPtrT>{tmp456});
    std::tie(tmp458, tmp459) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp450}, TNode<IntPtrT>{tmp457}).Flatten();
    tmp460 = Convert_Number_float32_0(state_, TNode<Float32T>{phi_bb186_25});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp458, tmp459}, tmp460);
    ca_.Goto(&block174, phi_bb202_7, tmp402, phi_bb202_9, phi_bb202_10, phi_bb202_11, phi_bb202_14, phi_bb202_15, phi_bb202_21);
  }

  TNode<IntPtrT> phi_bb203_7;
  TNode<IntPtrT> phi_bb203_9;
  TNode<IntPtrT> phi_bb203_10;
  TNode<IntPtrT> phi_bb203_11;
  TNode<IntPtrT> phi_bb203_14;
  TNode<BoolT> phi_bb203_15;
  TNode<IntPtrT> phi_bb203_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb203_23;
  TNode<IntPtrT> phi_bb203_24;
  TNode<IntPtrT> phi_bb203_30;
  TNode<IntPtrT> phi_bb203_31;
  TNode<IntPtrT> phi_bb203_35;
  TNode<IntPtrT> phi_bb203_36;
  if (block203.is_used()) {
    ca_.Bind(&block203, &phi_bb203_7, &phi_bb203_9, &phi_bb203_10, &phi_bb203_11, &phi_bb203_14, &phi_bb203_15, &phi_bb203_21, &phi_bb203_23, &phi_bb203_24, &phi_bb203_30, &phi_bb203_31, &phi_bb203_35, &phi_bb203_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb173_7;
  TNode<IntPtrT> phi_bb173_8;
  TNode<IntPtrT> phi_bb173_9;
  TNode<IntPtrT> phi_bb173_10;
  TNode<IntPtrT> phi_bb173_11;
  TNode<IntPtrT> phi_bb173_14;
  TNode<BoolT> phi_bb173_15;
  TNode<IntPtrT> phi_bb173_21;
  TNode<Uint32T> tmp461;
  TNode<BoolT> tmp462;
  if (block173.is_used()) {
    ca_.Bind(&block173, &phi_bb173_7, &phi_bb173_8, &phi_bb173_9, &phi_bb173_10, &phi_bb173_11, &phi_bb173_14, &phi_bb173_15, &phi_bb173_21);
    tmp461 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp462 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp353}, TNode<Uint32T>{tmp461});
    ca_.Branch(tmp462, &block206, std::vector<compiler::Node*>{phi_bb173_7, phi_bb173_8, phi_bb173_9, phi_bb173_10, phi_bb173_11, phi_bb173_14, phi_bb173_15, phi_bb173_21}, &block207, std::vector<compiler::Node*>{phi_bb173_7, phi_bb173_8, phi_bb173_9, phi_bb173_10, phi_bb173_11, phi_bb173_14, phi_bb173_15, phi_bb173_21});
  }

  TNode<IntPtrT> phi_bb206_7;
  TNode<IntPtrT> phi_bb206_8;
  TNode<IntPtrT> phi_bb206_9;
  TNode<IntPtrT> phi_bb206_10;
  TNode<IntPtrT> phi_bb206_11;
  TNode<IntPtrT> phi_bb206_14;
  TNode<BoolT> phi_bb206_15;
  TNode<IntPtrT> phi_bb206_21;
  if (block206.is_used()) {
    ca_.Bind(&block206, &phi_bb206_7, &phi_bb206_8, &phi_bb206_9, &phi_bb206_10, &phi_bb206_11, &phi_bb206_14, &phi_bb206_15, &phi_bb206_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block209, phi_bb206_7, phi_bb206_8, phi_bb206_9, phi_bb206_10, phi_bb206_11, phi_bb206_14, phi_bb206_15, phi_bb206_21);
    } else {
      ca_.Goto(&block210, phi_bb206_7, phi_bb206_8, phi_bb206_9, phi_bb206_10, phi_bb206_11, phi_bb206_14, phi_bb206_15, phi_bb206_21);
    }
  }

  TNode<IntPtrT> phi_bb209_7;
  TNode<IntPtrT> phi_bb209_8;
  TNode<IntPtrT> phi_bb209_9;
  TNode<IntPtrT> phi_bb209_10;
  TNode<IntPtrT> phi_bb209_11;
  TNode<IntPtrT> phi_bb209_14;
  TNode<BoolT> phi_bb209_15;
  TNode<IntPtrT> phi_bb209_21;
  TNode<IntPtrT> tmp463;
  TNode<IntPtrT> tmp464;
  TNode<IntPtrT> tmp465;
  TNode<BoolT> tmp466;
  if (block209.is_used()) {
    ca_.Bind(&block209, &phi_bb209_7, &phi_bb209_8, &phi_bb209_9, &phi_bb209_10, &phi_bb209_11, &phi_bb209_14, &phi_bb209_15, &phi_bb209_21);
    tmp463 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp464 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb209_7}, TNode<IntPtrT>{tmp463});
    tmp465 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp466 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb209_7}, TNode<IntPtrT>{tmp465});
    ca_.Branch(tmp466, &block213, std::vector<compiler::Node*>{phi_bb209_8, phi_bb209_9, phi_bb209_10, phi_bb209_11, phi_bb209_14, phi_bb209_15, phi_bb209_21}, &block214, std::vector<compiler::Node*>{phi_bb209_8, phi_bb209_9, phi_bb209_10, phi_bb209_11, phi_bb209_14, phi_bb209_15, phi_bb209_21});
  }

  TNode<IntPtrT> phi_bb213_8;
  TNode<IntPtrT> phi_bb213_9;
  TNode<IntPtrT> phi_bb213_10;
  TNode<IntPtrT> phi_bb213_11;
  TNode<IntPtrT> phi_bb213_14;
  TNode<BoolT> phi_bb213_15;
  TNode<IntPtrT> phi_bb213_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp467;
  TNode<IntPtrT> tmp468;
  TNode<IntPtrT> tmp469;
  TNode<IntPtrT> tmp470;
  if (block213.is_used()) {
    ca_.Bind(&block213, &phi_bb213_8, &phi_bb213_9, &phi_bb213_10, &phi_bb213_11, &phi_bb213_14, &phi_bb213_15, &phi_bb213_21);
    std::tie(tmp467, tmp468) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb213_9}).Flatten();
    tmp469 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp470 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb213_9}, TNode<IntPtrT>{tmp469});
    ca_.Goto(&block212, phi_bb213_8, tmp470, phi_bb213_10, phi_bb213_11, phi_bb213_14, phi_bb213_15, phi_bb213_21, tmp467, tmp468);
  }

  TNode<IntPtrT> phi_bb214_8;
  TNode<IntPtrT> phi_bb214_9;
  TNode<IntPtrT> phi_bb214_10;
  TNode<IntPtrT> phi_bb214_11;
  TNode<IntPtrT> phi_bb214_14;
  TNode<BoolT> phi_bb214_15;
  TNode<IntPtrT> phi_bb214_21;
  if (block214.is_used()) {
    ca_.Bind(&block214, &phi_bb214_8, &phi_bb214_9, &phi_bb214_10, &phi_bb214_11, &phi_bb214_14, &phi_bb214_15, &phi_bb214_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block216, phi_bb214_8, phi_bb214_9, phi_bb214_10, phi_bb214_11, phi_bb214_14, phi_bb214_15, phi_bb214_21);
    } else {
      ca_.Goto(&block217, phi_bb214_8, phi_bb214_9, phi_bb214_10, phi_bb214_11, phi_bb214_14, phi_bb214_15, phi_bb214_21);
    }
  }

  TNode<IntPtrT> phi_bb216_8;
  TNode<IntPtrT> phi_bb216_9;
  TNode<IntPtrT> phi_bb216_10;
  TNode<IntPtrT> phi_bb216_11;
  TNode<IntPtrT> phi_bb216_14;
  TNode<BoolT> phi_bb216_15;
  TNode<IntPtrT> phi_bb216_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp471;
  TNode<IntPtrT> tmp472;
  TNode<IntPtrT> tmp473;
  TNode<IntPtrT> tmp474;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_8, &phi_bb216_9, &phi_bb216_10, &phi_bb216_11, &phi_bb216_14, &phi_bb216_15, &phi_bb216_21);
    std::tie(tmp471, tmp472) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb216_11}).Flatten();
    tmp473 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp474 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb216_11}, TNode<IntPtrT>{tmp473});
    ca_.Goto(&block215, phi_bb216_8, phi_bb216_9, phi_bb216_10, tmp474, phi_bb216_14, phi_bb216_15, phi_bb216_21, tmp471, tmp472);
  }

  TNode<IntPtrT> phi_bb217_8;
  TNode<IntPtrT> phi_bb217_9;
  TNode<IntPtrT> phi_bb217_10;
  TNode<IntPtrT> phi_bb217_11;
  TNode<IntPtrT> phi_bb217_14;
  TNode<BoolT> phi_bb217_15;
  TNode<IntPtrT> phi_bb217_21;
  TNode<IntPtrT> tmp475;
  TNode<BoolT> tmp476;
  if (block217.is_used()) {
    ca_.Bind(&block217, &phi_bb217_8, &phi_bb217_9, &phi_bb217_10, &phi_bb217_11, &phi_bb217_14, &phi_bb217_15, &phi_bb217_21);
    tmp475 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp476 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb217_14}, TNode<IntPtrT>{tmp475});
    ca_.Branch(tmp476, &block219, std::vector<compiler::Node*>{phi_bb217_8, phi_bb217_9, phi_bb217_10, phi_bb217_11, phi_bb217_14, phi_bb217_15, phi_bb217_21}, &block220, std::vector<compiler::Node*>{phi_bb217_8, phi_bb217_9, phi_bb217_10, phi_bb217_11, phi_bb217_14, phi_bb217_15, phi_bb217_21});
  }

  TNode<IntPtrT> phi_bb219_8;
  TNode<IntPtrT> phi_bb219_9;
  TNode<IntPtrT> phi_bb219_10;
  TNode<IntPtrT> phi_bb219_11;
  TNode<IntPtrT> phi_bb219_14;
  TNode<BoolT> phi_bb219_15;
  TNode<IntPtrT> phi_bb219_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp477;
  TNode<IntPtrT> tmp478;
  TNode<IntPtrT> tmp479;
  TNode<BoolT> tmp480;
  if (block219.is_used()) {
    ca_.Bind(&block219, &phi_bb219_8, &phi_bb219_9, &phi_bb219_10, &phi_bb219_11, &phi_bb219_14, &phi_bb219_15, &phi_bb219_21);
    std::tie(tmp477, tmp478) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb219_14}).Flatten();
    tmp479 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp480 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block215, phi_bb219_8, phi_bb219_9, phi_bb219_10, phi_bb219_11, tmp479, tmp480, phi_bb219_21, tmp477, tmp478);
  }

  TNode<IntPtrT> phi_bb220_8;
  TNode<IntPtrT> phi_bb220_9;
  TNode<IntPtrT> phi_bb220_10;
  TNode<IntPtrT> phi_bb220_11;
  TNode<IntPtrT> phi_bb220_14;
  TNode<BoolT> phi_bb220_15;
  TNode<IntPtrT> phi_bb220_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp481;
  TNode<IntPtrT> tmp482;
  TNode<IntPtrT> tmp483;
  TNode<IntPtrT> tmp484;
  TNode<IntPtrT> tmp485;
  TNode<IntPtrT> tmp486;
  TNode<BoolT> tmp487;
  if (block220.is_used()) {
    ca_.Bind(&block220, &phi_bb220_8, &phi_bb220_9, &phi_bb220_10, &phi_bb220_11, &phi_bb220_14, &phi_bb220_15, &phi_bb220_21);
    std::tie(tmp481, tmp482) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb220_11}).Flatten();
    tmp483 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp484 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb220_11}, TNode<IntPtrT>{tmp483});
    tmp485 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp486 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp484}, TNode<IntPtrT>{tmp485});
    tmp487 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block215, phi_bb220_8, phi_bb220_9, phi_bb220_10, tmp486, tmp484, tmp487, phi_bb220_21, tmp481, tmp482);
  }

  TNode<IntPtrT> phi_bb215_8;
  TNode<IntPtrT> phi_bb215_9;
  TNode<IntPtrT> phi_bb215_10;
  TNode<IntPtrT> phi_bb215_11;
  TNode<IntPtrT> phi_bb215_14;
  TNode<BoolT> phi_bb215_15;
  TNode<IntPtrT> phi_bb215_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb215_23;
  TNode<IntPtrT> phi_bb215_24;
  if (block215.is_used()) {
    ca_.Bind(&block215, &phi_bb215_8, &phi_bb215_9, &phi_bb215_10, &phi_bb215_11, &phi_bb215_14, &phi_bb215_15, &phi_bb215_21, &phi_bb215_23, &phi_bb215_24);
    ca_.Goto(&block212, phi_bb215_8, phi_bb215_9, phi_bb215_10, phi_bb215_11, phi_bb215_14, phi_bb215_15, phi_bb215_21, phi_bb215_23, phi_bb215_24);
  }

  TNode<IntPtrT> phi_bb212_8;
  TNode<IntPtrT> phi_bb212_9;
  TNode<IntPtrT> phi_bb212_10;
  TNode<IntPtrT> phi_bb212_11;
  TNode<IntPtrT> phi_bb212_14;
  TNode<BoolT> phi_bb212_15;
  TNode<IntPtrT> phi_bb212_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb212_23;
  TNode<IntPtrT> phi_bb212_24;
  TNode<IntPtrT> tmp488;
  TNode<Union<HeapObject, TaggedIndex>> tmp489;
  TNode<IntPtrT> tmp490;
  TNode<IntPtrT> tmp491;
  TNode<UintPtrT> tmp492;
  TNode<UintPtrT> tmp493;
  TNode<BoolT> tmp494;
  if (block212.is_used()) {
    ca_.Bind(&block212, &phi_bb212_8, &phi_bb212_9, &phi_bb212_10, &phi_bb212_11, &phi_bb212_14, &phi_bb212_15, &phi_bb212_21, &phi_bb212_23, &phi_bb212_24);
    tmp488 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb212_23, phi_bb212_24});
    std::tie(tmp489, tmp490, tmp491) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp492 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb212_21});
    tmp493 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp491});
    tmp494 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp492}, TNode<UintPtrT>{tmp493});
    ca_.Branch(tmp494, &block225, std::vector<compiler::Node*>{phi_bb212_8, phi_bb212_9, phi_bb212_10, phi_bb212_11, phi_bb212_14, phi_bb212_15, phi_bb212_21, phi_bb212_23, phi_bb212_24, phi_bb212_21, phi_bb212_21, phi_bb212_21, phi_bb212_21}, &block226, std::vector<compiler::Node*>{phi_bb212_8, phi_bb212_9, phi_bb212_10, phi_bb212_11, phi_bb212_14, phi_bb212_15, phi_bb212_21, phi_bb212_23, phi_bb212_24, phi_bb212_21, phi_bb212_21, phi_bb212_21, phi_bb212_21});
  }

  TNode<IntPtrT> phi_bb225_8;
  TNode<IntPtrT> phi_bb225_9;
  TNode<IntPtrT> phi_bb225_10;
  TNode<IntPtrT> phi_bb225_11;
  TNode<IntPtrT> phi_bb225_14;
  TNode<BoolT> phi_bb225_15;
  TNode<IntPtrT> phi_bb225_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb225_23;
  TNode<IntPtrT> phi_bb225_24;
  TNode<IntPtrT> phi_bb225_30;
  TNode<IntPtrT> phi_bb225_31;
  TNode<IntPtrT> phi_bb225_35;
  TNode<IntPtrT> phi_bb225_36;
  TNode<IntPtrT> tmp495;
  TNode<IntPtrT> tmp496;
  TNode<Union<HeapObject, TaggedIndex>> tmp497;
  TNode<IntPtrT> tmp498;
  TNode<BigInt> tmp499;
  if (block225.is_used()) {
    ca_.Bind(&block225, &phi_bb225_8, &phi_bb225_9, &phi_bb225_10, &phi_bb225_11, &phi_bb225_14, &phi_bb225_15, &phi_bb225_21, &phi_bb225_23, &phi_bb225_24, &phi_bb225_30, &phi_bb225_31, &phi_bb225_35, &phi_bb225_36);
    tmp495 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb225_36});
    tmp496 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp490}, TNode<IntPtrT>{tmp495});
    std::tie(tmp497, tmp498) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp489}, TNode<IntPtrT>{tmp496}).Flatten();
    tmp499 = ca_.CallBuiltin<BigInt>(Builtin::kI64ToBigInt, TNode<Object>(), tmp488);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp497, tmp498}, tmp499);
    ca_.Goto(&block211, tmp464, phi_bb225_8, phi_bb225_9, phi_bb225_10, phi_bb225_11, phi_bb225_14, phi_bb225_15, phi_bb225_21);
  }

  TNode<IntPtrT> phi_bb226_8;
  TNode<IntPtrT> phi_bb226_9;
  TNode<IntPtrT> phi_bb226_10;
  TNode<IntPtrT> phi_bb226_11;
  TNode<IntPtrT> phi_bb226_14;
  TNode<BoolT> phi_bb226_15;
  TNode<IntPtrT> phi_bb226_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb226_23;
  TNode<IntPtrT> phi_bb226_24;
  TNode<IntPtrT> phi_bb226_30;
  TNode<IntPtrT> phi_bb226_31;
  TNode<IntPtrT> phi_bb226_35;
  TNode<IntPtrT> phi_bb226_36;
  if (block226.is_used()) {
    ca_.Bind(&block226, &phi_bb226_8, &phi_bb226_9, &phi_bb226_10, &phi_bb226_11, &phi_bb226_14, &phi_bb226_15, &phi_bb226_21, &phi_bb226_23, &phi_bb226_24, &phi_bb226_30, &phi_bb226_31, &phi_bb226_35, &phi_bb226_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb210_7;
  TNode<IntPtrT> phi_bb210_8;
  TNode<IntPtrT> phi_bb210_9;
  TNode<IntPtrT> phi_bb210_10;
  TNode<IntPtrT> phi_bb210_11;
  TNode<IntPtrT> phi_bb210_14;
  TNode<BoolT> phi_bb210_15;
  TNode<IntPtrT> phi_bb210_21;
  TNode<IntPtrT> tmp500;
  TNode<IntPtrT> tmp501;
  TNode<IntPtrT> tmp502;
  TNode<BoolT> tmp503;
  if (block210.is_used()) {
    ca_.Bind(&block210, &phi_bb210_7, &phi_bb210_8, &phi_bb210_9, &phi_bb210_10, &phi_bb210_11, &phi_bb210_14, &phi_bb210_15, &phi_bb210_21);
    tmp500 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp501 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb210_7}, TNode<IntPtrT>{tmp500});
    tmp502 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp503 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb210_7}, TNode<IntPtrT>{tmp502});
    ca_.Branch(tmp503, &block230, std::vector<compiler::Node*>{phi_bb210_8, phi_bb210_9, phi_bb210_10, phi_bb210_11, phi_bb210_14, phi_bb210_15, phi_bb210_21}, &block231, std::vector<compiler::Node*>{phi_bb210_8, phi_bb210_9, phi_bb210_10, phi_bb210_11, phi_bb210_14, phi_bb210_15, phi_bb210_21});
  }

  TNode<IntPtrT> phi_bb230_8;
  TNode<IntPtrT> phi_bb230_9;
  TNode<IntPtrT> phi_bb230_10;
  TNode<IntPtrT> phi_bb230_11;
  TNode<IntPtrT> phi_bb230_14;
  TNode<BoolT> phi_bb230_15;
  TNode<IntPtrT> phi_bb230_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp504;
  TNode<IntPtrT> tmp505;
  TNode<IntPtrT> tmp506;
  TNode<IntPtrT> tmp507;
  if (block230.is_used()) {
    ca_.Bind(&block230, &phi_bb230_8, &phi_bb230_9, &phi_bb230_10, &phi_bb230_11, &phi_bb230_14, &phi_bb230_15, &phi_bb230_21);
    std::tie(tmp504, tmp505) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb230_9}).Flatten();
    tmp506 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp507 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb230_9}, TNode<IntPtrT>{tmp506});
    ca_.Goto(&block229, phi_bb230_8, tmp507, phi_bb230_10, phi_bb230_11, phi_bb230_14, phi_bb230_15, phi_bb230_21, tmp504, tmp505);
  }

  TNode<IntPtrT> phi_bb231_8;
  TNode<IntPtrT> phi_bb231_9;
  TNode<IntPtrT> phi_bb231_10;
  TNode<IntPtrT> phi_bb231_11;
  TNode<IntPtrT> phi_bb231_14;
  TNode<BoolT> phi_bb231_15;
  TNode<IntPtrT> phi_bb231_21;
  if (block231.is_used()) {
    ca_.Bind(&block231, &phi_bb231_8, &phi_bb231_9, &phi_bb231_10, &phi_bb231_11, &phi_bb231_14, &phi_bb231_15, &phi_bb231_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block233, phi_bb231_8, phi_bb231_9, phi_bb231_10, phi_bb231_11, phi_bb231_14, phi_bb231_15, phi_bb231_21);
    } else {
      ca_.Goto(&block234, phi_bb231_8, phi_bb231_9, phi_bb231_10, phi_bb231_11, phi_bb231_14, phi_bb231_15, phi_bb231_21);
    }
  }

  TNode<IntPtrT> phi_bb233_8;
  TNode<IntPtrT> phi_bb233_9;
  TNode<IntPtrT> phi_bb233_10;
  TNode<IntPtrT> phi_bb233_11;
  TNode<IntPtrT> phi_bb233_14;
  TNode<BoolT> phi_bb233_15;
  TNode<IntPtrT> phi_bb233_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp508;
  TNode<IntPtrT> tmp509;
  TNode<IntPtrT> tmp510;
  TNode<IntPtrT> tmp511;
  if (block233.is_used()) {
    ca_.Bind(&block233, &phi_bb233_8, &phi_bb233_9, &phi_bb233_10, &phi_bb233_11, &phi_bb233_14, &phi_bb233_15, &phi_bb233_21);
    std::tie(tmp508, tmp509) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb233_11}).Flatten();
    tmp510 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp511 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb233_11}, TNode<IntPtrT>{tmp510});
    ca_.Goto(&block232, phi_bb233_8, phi_bb233_9, phi_bb233_10, tmp511, phi_bb233_14, phi_bb233_15, phi_bb233_21, tmp508, tmp509);
  }

  TNode<IntPtrT> phi_bb234_8;
  TNode<IntPtrT> phi_bb234_9;
  TNode<IntPtrT> phi_bb234_10;
  TNode<IntPtrT> phi_bb234_11;
  TNode<IntPtrT> phi_bb234_14;
  TNode<BoolT> phi_bb234_15;
  TNode<IntPtrT> phi_bb234_21;
  TNode<IntPtrT> tmp512;
  TNode<BoolT> tmp513;
  if (block234.is_used()) {
    ca_.Bind(&block234, &phi_bb234_8, &phi_bb234_9, &phi_bb234_10, &phi_bb234_11, &phi_bb234_14, &phi_bb234_15, &phi_bb234_21);
    tmp512 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp513 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb234_14}, TNode<IntPtrT>{tmp512});
    ca_.Branch(tmp513, &block236, std::vector<compiler::Node*>{phi_bb234_8, phi_bb234_9, phi_bb234_10, phi_bb234_11, phi_bb234_14, phi_bb234_15, phi_bb234_21}, &block237, std::vector<compiler::Node*>{phi_bb234_8, phi_bb234_9, phi_bb234_10, phi_bb234_11, phi_bb234_14, phi_bb234_15, phi_bb234_21});
  }

  TNode<IntPtrT> phi_bb236_8;
  TNode<IntPtrT> phi_bb236_9;
  TNode<IntPtrT> phi_bb236_10;
  TNode<IntPtrT> phi_bb236_11;
  TNode<IntPtrT> phi_bb236_14;
  TNode<BoolT> phi_bb236_15;
  TNode<IntPtrT> phi_bb236_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp514;
  TNode<IntPtrT> tmp515;
  TNode<IntPtrT> tmp516;
  TNode<BoolT> tmp517;
  if (block236.is_used()) {
    ca_.Bind(&block236, &phi_bb236_8, &phi_bb236_9, &phi_bb236_10, &phi_bb236_11, &phi_bb236_14, &phi_bb236_15, &phi_bb236_21);
    std::tie(tmp514, tmp515) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb236_14}).Flatten();
    tmp516 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp517 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block232, phi_bb236_8, phi_bb236_9, phi_bb236_10, phi_bb236_11, tmp516, tmp517, phi_bb236_21, tmp514, tmp515);
  }

  TNode<IntPtrT> phi_bb237_8;
  TNode<IntPtrT> phi_bb237_9;
  TNode<IntPtrT> phi_bb237_10;
  TNode<IntPtrT> phi_bb237_11;
  TNode<IntPtrT> phi_bb237_14;
  TNode<BoolT> phi_bb237_15;
  TNode<IntPtrT> phi_bb237_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp518;
  TNode<IntPtrT> tmp519;
  TNode<IntPtrT> tmp520;
  TNode<IntPtrT> tmp521;
  TNode<IntPtrT> tmp522;
  TNode<IntPtrT> tmp523;
  TNode<BoolT> tmp524;
  if (block237.is_used()) {
    ca_.Bind(&block237, &phi_bb237_8, &phi_bb237_9, &phi_bb237_10, &phi_bb237_11, &phi_bb237_14, &phi_bb237_15, &phi_bb237_21);
    std::tie(tmp518, tmp519) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb237_11}).Flatten();
    tmp520 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp521 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb237_11}, TNode<IntPtrT>{tmp520});
    tmp522 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp523 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp521}, TNode<IntPtrT>{tmp522});
    tmp524 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block232, phi_bb237_8, phi_bb237_9, phi_bb237_10, tmp523, tmp521, tmp524, phi_bb237_21, tmp518, tmp519);
  }

  TNode<IntPtrT> phi_bb232_8;
  TNode<IntPtrT> phi_bb232_9;
  TNode<IntPtrT> phi_bb232_10;
  TNode<IntPtrT> phi_bb232_11;
  TNode<IntPtrT> phi_bb232_14;
  TNode<BoolT> phi_bb232_15;
  TNode<IntPtrT> phi_bb232_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb232_23;
  TNode<IntPtrT> phi_bb232_24;
  if (block232.is_used()) {
    ca_.Bind(&block232, &phi_bb232_8, &phi_bb232_9, &phi_bb232_10, &phi_bb232_11, &phi_bb232_14, &phi_bb232_15, &phi_bb232_21, &phi_bb232_23, &phi_bb232_24);
    ca_.Goto(&block229, phi_bb232_8, phi_bb232_9, phi_bb232_10, phi_bb232_11, phi_bb232_14, phi_bb232_15, phi_bb232_21, phi_bb232_23, phi_bb232_24);
  }

  TNode<IntPtrT> phi_bb229_8;
  TNode<IntPtrT> phi_bb229_9;
  TNode<IntPtrT> phi_bb229_10;
  TNode<IntPtrT> phi_bb229_11;
  TNode<IntPtrT> phi_bb229_14;
  TNode<BoolT> phi_bb229_15;
  TNode<IntPtrT> phi_bb229_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb229_23;
  TNode<IntPtrT> phi_bb229_24;
  TNode<IntPtrT> tmp525;
  TNode<IntPtrT> tmp526;
  TNode<IntPtrT> tmp527;
  TNode<BoolT> tmp528;
  if (block229.is_used()) {
    ca_.Bind(&block229, &phi_bb229_8, &phi_bb229_9, &phi_bb229_10, &phi_bb229_11, &phi_bb229_14, &phi_bb229_15, &phi_bb229_21, &phi_bb229_23, &phi_bb229_24);
    tmp525 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp526 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp501}, TNode<IntPtrT>{tmp525});
    tmp527 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp528 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp501}, TNode<IntPtrT>{tmp527});
    ca_.Branch(tmp528, &block239, std::vector<compiler::Node*>{phi_bb229_8, phi_bb229_9, phi_bb229_10, phi_bb229_11, phi_bb229_14, phi_bb229_15, phi_bb229_21, phi_bb229_23, phi_bb229_24}, &block240, std::vector<compiler::Node*>{phi_bb229_8, phi_bb229_9, phi_bb229_10, phi_bb229_11, phi_bb229_14, phi_bb229_15, phi_bb229_21, phi_bb229_23, phi_bb229_24});
  }

  TNode<IntPtrT> phi_bb239_8;
  TNode<IntPtrT> phi_bb239_9;
  TNode<IntPtrT> phi_bb239_10;
  TNode<IntPtrT> phi_bb239_11;
  TNode<IntPtrT> phi_bb239_14;
  TNode<BoolT> phi_bb239_15;
  TNode<IntPtrT> phi_bb239_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb239_23;
  TNode<IntPtrT> phi_bb239_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp529;
  TNode<IntPtrT> tmp530;
  TNode<IntPtrT> tmp531;
  TNode<IntPtrT> tmp532;
  if (block239.is_used()) {
    ca_.Bind(&block239, &phi_bb239_8, &phi_bb239_9, &phi_bb239_10, &phi_bb239_11, &phi_bb239_14, &phi_bb239_15, &phi_bb239_21, &phi_bb239_23, &phi_bb239_24);
    std::tie(tmp529, tmp530) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb239_9}).Flatten();
    tmp531 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp532 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb239_9}, TNode<IntPtrT>{tmp531});
    ca_.Goto(&block238, phi_bb239_8, tmp532, phi_bb239_10, phi_bb239_11, phi_bb239_14, phi_bb239_15, phi_bb239_21, phi_bb239_23, phi_bb239_24, tmp529, tmp530);
  }

  TNode<IntPtrT> phi_bb240_8;
  TNode<IntPtrT> phi_bb240_9;
  TNode<IntPtrT> phi_bb240_10;
  TNode<IntPtrT> phi_bb240_11;
  TNode<IntPtrT> phi_bb240_14;
  TNode<BoolT> phi_bb240_15;
  TNode<IntPtrT> phi_bb240_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb240_23;
  TNode<IntPtrT> phi_bb240_24;
  if (block240.is_used()) {
    ca_.Bind(&block240, &phi_bb240_8, &phi_bb240_9, &phi_bb240_10, &phi_bb240_11, &phi_bb240_14, &phi_bb240_15, &phi_bb240_21, &phi_bb240_23, &phi_bb240_24);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block242, phi_bb240_8, phi_bb240_9, phi_bb240_10, phi_bb240_11, phi_bb240_14, phi_bb240_15, phi_bb240_21, phi_bb240_23, phi_bb240_24);
    } else {
      ca_.Goto(&block243, phi_bb240_8, phi_bb240_9, phi_bb240_10, phi_bb240_11, phi_bb240_14, phi_bb240_15, phi_bb240_21, phi_bb240_23, phi_bb240_24);
    }
  }

  TNode<IntPtrT> phi_bb242_8;
  TNode<IntPtrT> phi_bb242_9;
  TNode<IntPtrT> phi_bb242_10;
  TNode<IntPtrT> phi_bb242_11;
  TNode<IntPtrT> phi_bb242_14;
  TNode<BoolT> phi_bb242_15;
  TNode<IntPtrT> phi_bb242_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb242_23;
  TNode<IntPtrT> phi_bb242_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp533;
  TNode<IntPtrT> tmp534;
  TNode<IntPtrT> tmp535;
  TNode<IntPtrT> tmp536;
  if (block242.is_used()) {
    ca_.Bind(&block242, &phi_bb242_8, &phi_bb242_9, &phi_bb242_10, &phi_bb242_11, &phi_bb242_14, &phi_bb242_15, &phi_bb242_21, &phi_bb242_23, &phi_bb242_24);
    std::tie(tmp533, tmp534) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb242_11}).Flatten();
    tmp535 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp536 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb242_11}, TNode<IntPtrT>{tmp535});
    ca_.Goto(&block241, phi_bb242_8, phi_bb242_9, phi_bb242_10, tmp536, phi_bb242_14, phi_bb242_15, phi_bb242_21, phi_bb242_23, phi_bb242_24, tmp533, tmp534);
  }

  TNode<IntPtrT> phi_bb243_8;
  TNode<IntPtrT> phi_bb243_9;
  TNode<IntPtrT> phi_bb243_10;
  TNode<IntPtrT> phi_bb243_11;
  TNode<IntPtrT> phi_bb243_14;
  TNode<BoolT> phi_bb243_15;
  TNode<IntPtrT> phi_bb243_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb243_23;
  TNode<IntPtrT> phi_bb243_24;
  TNode<IntPtrT> tmp537;
  TNode<BoolT> tmp538;
  if (block243.is_used()) {
    ca_.Bind(&block243, &phi_bb243_8, &phi_bb243_9, &phi_bb243_10, &phi_bb243_11, &phi_bb243_14, &phi_bb243_15, &phi_bb243_21, &phi_bb243_23, &phi_bb243_24);
    tmp537 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp538 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb243_14}, TNode<IntPtrT>{tmp537});
    ca_.Branch(tmp538, &block245, std::vector<compiler::Node*>{phi_bb243_8, phi_bb243_9, phi_bb243_10, phi_bb243_11, phi_bb243_14, phi_bb243_15, phi_bb243_21, phi_bb243_23, phi_bb243_24}, &block246, std::vector<compiler::Node*>{phi_bb243_8, phi_bb243_9, phi_bb243_10, phi_bb243_11, phi_bb243_14, phi_bb243_15, phi_bb243_21, phi_bb243_23, phi_bb243_24});
  }

  TNode<IntPtrT> phi_bb245_8;
  TNode<IntPtrT> phi_bb245_9;
  TNode<IntPtrT> phi_bb245_10;
  TNode<IntPtrT> phi_bb245_11;
  TNode<IntPtrT> phi_bb245_14;
  TNode<BoolT> phi_bb245_15;
  TNode<IntPtrT> phi_bb245_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb245_23;
  TNode<IntPtrT> phi_bb245_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp539;
  TNode<IntPtrT> tmp540;
  TNode<IntPtrT> tmp541;
  TNode<BoolT> tmp542;
  if (block245.is_used()) {
    ca_.Bind(&block245, &phi_bb245_8, &phi_bb245_9, &phi_bb245_10, &phi_bb245_11, &phi_bb245_14, &phi_bb245_15, &phi_bb245_21, &phi_bb245_23, &phi_bb245_24);
    std::tie(tmp539, tmp540) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb245_14}).Flatten();
    tmp541 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp542 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block241, phi_bb245_8, phi_bb245_9, phi_bb245_10, phi_bb245_11, tmp541, tmp542, phi_bb245_21, phi_bb245_23, phi_bb245_24, tmp539, tmp540);
  }

  TNode<IntPtrT> phi_bb246_8;
  TNode<IntPtrT> phi_bb246_9;
  TNode<IntPtrT> phi_bb246_10;
  TNode<IntPtrT> phi_bb246_11;
  TNode<IntPtrT> phi_bb246_14;
  TNode<BoolT> phi_bb246_15;
  TNode<IntPtrT> phi_bb246_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb246_23;
  TNode<IntPtrT> phi_bb246_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp543;
  TNode<IntPtrT> tmp544;
  TNode<IntPtrT> tmp545;
  TNode<IntPtrT> tmp546;
  TNode<IntPtrT> tmp547;
  TNode<IntPtrT> tmp548;
  TNode<BoolT> tmp549;
  if (block246.is_used()) {
    ca_.Bind(&block246, &phi_bb246_8, &phi_bb246_9, &phi_bb246_10, &phi_bb246_11, &phi_bb246_14, &phi_bb246_15, &phi_bb246_21, &phi_bb246_23, &phi_bb246_24);
    std::tie(tmp543, tmp544) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb246_11}).Flatten();
    tmp545 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp546 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb246_11}, TNode<IntPtrT>{tmp545});
    tmp547 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp548 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp546}, TNode<IntPtrT>{tmp547});
    tmp549 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block241, phi_bb246_8, phi_bb246_9, phi_bb246_10, tmp548, tmp546, tmp549, phi_bb246_21, phi_bb246_23, phi_bb246_24, tmp543, tmp544);
  }

  TNode<IntPtrT> phi_bb241_8;
  TNode<IntPtrT> phi_bb241_9;
  TNode<IntPtrT> phi_bb241_10;
  TNode<IntPtrT> phi_bb241_11;
  TNode<IntPtrT> phi_bb241_14;
  TNode<BoolT> phi_bb241_15;
  TNode<IntPtrT> phi_bb241_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb241_23;
  TNode<IntPtrT> phi_bb241_24;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb241_25;
  TNode<IntPtrT> phi_bb241_26;
  if (block241.is_used()) {
    ca_.Bind(&block241, &phi_bb241_8, &phi_bb241_9, &phi_bb241_10, &phi_bb241_11, &phi_bb241_14, &phi_bb241_15, &phi_bb241_21, &phi_bb241_23, &phi_bb241_24, &phi_bb241_25, &phi_bb241_26);
    ca_.Goto(&block238, phi_bb241_8, phi_bb241_9, phi_bb241_10, phi_bb241_11, phi_bb241_14, phi_bb241_15, phi_bb241_21, phi_bb241_23, phi_bb241_24, phi_bb241_25, phi_bb241_26);
  }

  TNode<IntPtrT> phi_bb238_8;
  TNode<IntPtrT> phi_bb238_9;
  TNode<IntPtrT> phi_bb238_10;
  TNode<IntPtrT> phi_bb238_11;
  TNode<IntPtrT> phi_bb238_14;
  TNode<BoolT> phi_bb238_15;
  TNode<IntPtrT> phi_bb238_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb238_23;
  TNode<IntPtrT> phi_bb238_24;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb238_25;
  TNode<IntPtrT> phi_bb238_26;
  TNode<IntPtrT> tmp550;
  TNode<IntPtrT> tmp551;
  TNode<Union<HeapObject, TaggedIndex>> tmp552;
  TNode<IntPtrT> tmp553;
  TNode<IntPtrT> tmp554;
  TNode<UintPtrT> tmp555;
  TNode<UintPtrT> tmp556;
  TNode<BoolT> tmp557;
  if (block238.is_used()) {
    ca_.Bind(&block238, &phi_bb238_8, &phi_bb238_9, &phi_bb238_10, &phi_bb238_11, &phi_bb238_14, &phi_bb238_15, &phi_bb238_21, &phi_bb238_23, &phi_bb238_24, &phi_bb238_25, &phi_bb238_26);
    tmp550 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb238_23, phi_bb238_24});
    tmp551 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb238_25, phi_bb238_26});
    std::tie(tmp552, tmp553, tmp554) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp555 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb238_21});
    tmp556 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp554});
    tmp557 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp555}, TNode<UintPtrT>{tmp556});
    ca_.Branch(tmp557, &block251, std::vector<compiler::Node*>{phi_bb238_8, phi_bb238_9, phi_bb238_10, phi_bb238_11, phi_bb238_14, phi_bb238_15, phi_bb238_21, phi_bb238_23, phi_bb238_24, phi_bb238_25, phi_bb238_26, phi_bb238_21, phi_bb238_21, phi_bb238_21, phi_bb238_21}, &block252, std::vector<compiler::Node*>{phi_bb238_8, phi_bb238_9, phi_bb238_10, phi_bb238_11, phi_bb238_14, phi_bb238_15, phi_bb238_21, phi_bb238_23, phi_bb238_24, phi_bb238_25, phi_bb238_26, phi_bb238_21, phi_bb238_21, phi_bb238_21, phi_bb238_21});
  }

  TNode<IntPtrT> phi_bb251_8;
  TNode<IntPtrT> phi_bb251_9;
  TNode<IntPtrT> phi_bb251_10;
  TNode<IntPtrT> phi_bb251_11;
  TNode<IntPtrT> phi_bb251_14;
  TNode<BoolT> phi_bb251_15;
  TNode<IntPtrT> phi_bb251_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb251_23;
  TNode<IntPtrT> phi_bb251_24;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb251_25;
  TNode<IntPtrT> phi_bb251_26;
  TNode<IntPtrT> phi_bb251_33;
  TNode<IntPtrT> phi_bb251_34;
  TNode<IntPtrT> phi_bb251_38;
  TNode<IntPtrT> phi_bb251_39;
  TNode<IntPtrT> tmp558;
  TNode<IntPtrT> tmp559;
  TNode<Union<HeapObject, TaggedIndex>> tmp560;
  TNode<IntPtrT> tmp561;
  TNode<BigInt> tmp562;
  if (block251.is_used()) {
    ca_.Bind(&block251, &phi_bb251_8, &phi_bb251_9, &phi_bb251_10, &phi_bb251_11, &phi_bb251_14, &phi_bb251_15, &phi_bb251_21, &phi_bb251_23, &phi_bb251_24, &phi_bb251_25, &phi_bb251_26, &phi_bb251_33, &phi_bb251_34, &phi_bb251_38, &phi_bb251_39);
    tmp558 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb251_39});
    tmp559 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp553}, TNode<IntPtrT>{tmp558});
    std::tie(tmp560, tmp561) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp552}, TNode<IntPtrT>{tmp559}).Flatten();
    tmp562 = ca_.CallBuiltin<BigInt>(Builtin::kI32PairToBigInt, TNode<Object>(), tmp550, tmp551);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp560, tmp561}, tmp562);
    ca_.Goto(&block211, tmp526, phi_bb251_8, phi_bb251_9, phi_bb251_10, phi_bb251_11, phi_bb251_14, phi_bb251_15, phi_bb251_21);
  }

  TNode<IntPtrT> phi_bb252_8;
  TNode<IntPtrT> phi_bb252_9;
  TNode<IntPtrT> phi_bb252_10;
  TNode<IntPtrT> phi_bb252_11;
  TNode<IntPtrT> phi_bb252_14;
  TNode<BoolT> phi_bb252_15;
  TNode<IntPtrT> phi_bb252_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb252_23;
  TNode<IntPtrT> phi_bb252_24;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb252_25;
  TNode<IntPtrT> phi_bb252_26;
  TNode<IntPtrT> phi_bb252_33;
  TNode<IntPtrT> phi_bb252_34;
  TNode<IntPtrT> phi_bb252_38;
  TNode<IntPtrT> phi_bb252_39;
  if (block252.is_used()) {
    ca_.Bind(&block252, &phi_bb252_8, &phi_bb252_9, &phi_bb252_10, &phi_bb252_11, &phi_bb252_14, &phi_bb252_15, &phi_bb252_21, &phi_bb252_23, &phi_bb252_24, &phi_bb252_25, &phi_bb252_26, &phi_bb252_33, &phi_bb252_34, &phi_bb252_38, &phi_bb252_39);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb211_7;
  TNode<IntPtrT> phi_bb211_8;
  TNode<IntPtrT> phi_bb211_9;
  TNode<IntPtrT> phi_bb211_10;
  TNode<IntPtrT> phi_bb211_11;
  TNode<IntPtrT> phi_bb211_14;
  TNode<BoolT> phi_bb211_15;
  TNode<IntPtrT> phi_bb211_21;
  if (block211.is_used()) {
    ca_.Bind(&block211, &phi_bb211_7, &phi_bb211_8, &phi_bb211_9, &phi_bb211_10, &phi_bb211_11, &phi_bb211_14, &phi_bb211_15, &phi_bb211_21);
    ca_.Goto(&block208, phi_bb211_7, phi_bb211_8, phi_bb211_9, phi_bb211_10, phi_bb211_11, phi_bb211_14, phi_bb211_15, phi_bb211_21);
  }

  TNode<IntPtrT> phi_bb207_7;
  TNode<IntPtrT> phi_bb207_8;
  TNode<IntPtrT> phi_bb207_9;
  TNode<IntPtrT> phi_bb207_10;
  TNode<IntPtrT> phi_bb207_11;
  TNode<IntPtrT> phi_bb207_14;
  TNode<BoolT> phi_bb207_15;
  TNode<IntPtrT> phi_bb207_21;
  TNode<Uint32T> tmp563;
  TNode<BoolT> tmp564;
  if (block207.is_used()) {
    ca_.Bind(&block207, &phi_bb207_7, &phi_bb207_8, &phi_bb207_9, &phi_bb207_10, &phi_bb207_11, &phi_bb207_14, &phi_bb207_15, &phi_bb207_21);
    tmp563 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp564 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp353}, TNode<Uint32T>{tmp563});
    ca_.Branch(tmp564, &block255, std::vector<compiler::Node*>{phi_bb207_7, phi_bb207_8, phi_bb207_9, phi_bb207_10, phi_bb207_11, phi_bb207_14, phi_bb207_15, phi_bb207_21}, &block256, std::vector<compiler::Node*>{phi_bb207_7, phi_bb207_8, phi_bb207_9, phi_bb207_10, phi_bb207_11, phi_bb207_14, phi_bb207_15, phi_bb207_21});
  }

  TNode<IntPtrT> phi_bb255_7;
  TNode<IntPtrT> phi_bb255_8;
  TNode<IntPtrT> phi_bb255_9;
  TNode<IntPtrT> phi_bb255_10;
  TNode<IntPtrT> phi_bb255_11;
  TNode<IntPtrT> phi_bb255_14;
  TNode<BoolT> phi_bb255_15;
  TNode<IntPtrT> phi_bb255_21;
  TNode<IntPtrT> tmp565;
  TNode<IntPtrT> tmp566;
  TNode<IntPtrT> tmp567;
  TNode<BoolT> tmp568;
  if (block255.is_used()) {
    ca_.Bind(&block255, &phi_bb255_7, &phi_bb255_8, &phi_bb255_9, &phi_bb255_10, &phi_bb255_11, &phi_bb255_14, &phi_bb255_15, &phi_bb255_21);
    tmp565 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp566 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb255_8}, TNode<IntPtrT>{tmp565});
    tmp567 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp568 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb255_8}, TNode<IntPtrT>{tmp567});
    ca_.Branch(tmp568, &block259, std::vector<compiler::Node*>{phi_bb255_7, phi_bb255_9, phi_bb255_10, phi_bb255_11, phi_bb255_14, phi_bb255_15, phi_bb255_21}, &block260, std::vector<compiler::Node*>{phi_bb255_7, phi_bb255_9, phi_bb255_10, phi_bb255_11, phi_bb255_14, phi_bb255_15, phi_bb255_21});
  }

  TNode<IntPtrT> phi_bb259_7;
  TNode<IntPtrT> phi_bb259_9;
  TNode<IntPtrT> phi_bb259_10;
  TNode<IntPtrT> phi_bb259_11;
  TNode<IntPtrT> phi_bb259_14;
  TNode<BoolT> phi_bb259_15;
  TNode<IntPtrT> phi_bb259_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp569;
  TNode<IntPtrT> tmp570;
  TNode<IntPtrT> tmp571;
  TNode<IntPtrT> tmp572;
  if (block259.is_used()) {
    ca_.Bind(&block259, &phi_bb259_7, &phi_bb259_9, &phi_bb259_10, &phi_bb259_11, &phi_bb259_14, &phi_bb259_15, &phi_bb259_21);
    std::tie(tmp569, tmp570) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb259_10}).Flatten();
    tmp571 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp572 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb259_10}, TNode<IntPtrT>{tmp571});
    ca_.Goto(&block258, phi_bb259_7, phi_bb259_9, tmp572, phi_bb259_11, phi_bb259_14, phi_bb259_15, phi_bb259_21, tmp569, tmp570);
  }

  TNode<IntPtrT> phi_bb260_7;
  TNode<IntPtrT> phi_bb260_9;
  TNode<IntPtrT> phi_bb260_10;
  TNode<IntPtrT> phi_bb260_11;
  TNode<IntPtrT> phi_bb260_14;
  TNode<BoolT> phi_bb260_15;
  TNode<IntPtrT> phi_bb260_21;
  if (block260.is_used()) {
    ca_.Bind(&block260, &phi_bb260_7, &phi_bb260_9, &phi_bb260_10, &phi_bb260_11, &phi_bb260_14, &phi_bb260_15, &phi_bb260_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block261, phi_bb260_7, phi_bb260_9, phi_bb260_10, phi_bb260_11, phi_bb260_14, phi_bb260_15, phi_bb260_21);
    } else {
      ca_.Goto(&block262, phi_bb260_7, phi_bb260_9, phi_bb260_10, phi_bb260_11, phi_bb260_14, phi_bb260_15, phi_bb260_21);
    }
  }

  TNode<IntPtrT> phi_bb261_7;
  TNode<IntPtrT> phi_bb261_9;
  TNode<IntPtrT> phi_bb261_10;
  TNode<IntPtrT> phi_bb261_11;
  TNode<IntPtrT> phi_bb261_14;
  TNode<BoolT> phi_bb261_15;
  TNode<IntPtrT> phi_bb261_21;
  if (block261.is_used()) {
    ca_.Bind(&block261, &phi_bb261_7, &phi_bb261_9, &phi_bb261_10, &phi_bb261_11, &phi_bb261_14, &phi_bb261_15, &phi_bb261_21);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block265, phi_bb261_7, phi_bb261_9, phi_bb261_10, phi_bb261_11, phi_bb261_14, phi_bb261_15, phi_bb261_21);
    } else {
      ca_.Goto(&block266, phi_bb261_7, phi_bb261_9, phi_bb261_10, phi_bb261_11, phi_bb261_14, phi_bb261_15, phi_bb261_21);
    }
  }

  TNode<IntPtrT> phi_bb265_7;
  TNode<IntPtrT> phi_bb265_9;
  TNode<IntPtrT> phi_bb265_10;
  TNode<IntPtrT> phi_bb265_11;
  TNode<IntPtrT> phi_bb265_14;
  TNode<BoolT> phi_bb265_15;
  TNode<IntPtrT> phi_bb265_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp573;
  TNode<IntPtrT> tmp574;
  TNode<IntPtrT> tmp575;
  TNode<IntPtrT> tmp576;
  if (block265.is_used()) {
    ca_.Bind(&block265, &phi_bb265_7, &phi_bb265_9, &phi_bb265_10, &phi_bb265_11, &phi_bb265_14, &phi_bb265_15, &phi_bb265_21);
    std::tie(tmp573, tmp574) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb265_11}).Flatten();
    tmp575 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp576 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb265_11}, TNode<IntPtrT>{tmp575});
    ca_.Goto(&block264, phi_bb265_7, phi_bb265_9, phi_bb265_10, tmp576, phi_bb265_14, phi_bb265_15, phi_bb265_21, tmp573, tmp574);
  }

  TNode<IntPtrT> phi_bb266_7;
  TNode<IntPtrT> phi_bb266_9;
  TNode<IntPtrT> phi_bb266_10;
  TNode<IntPtrT> phi_bb266_11;
  TNode<IntPtrT> phi_bb266_14;
  TNode<BoolT> phi_bb266_15;
  TNode<IntPtrT> phi_bb266_21;
  TNode<IntPtrT> tmp577;
  TNode<BoolT> tmp578;
  if (block266.is_used()) {
    ca_.Bind(&block266, &phi_bb266_7, &phi_bb266_9, &phi_bb266_10, &phi_bb266_11, &phi_bb266_14, &phi_bb266_15, &phi_bb266_21);
    tmp577 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp578 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb266_14}, TNode<IntPtrT>{tmp577});
    ca_.Branch(tmp578, &block268, std::vector<compiler::Node*>{phi_bb266_7, phi_bb266_9, phi_bb266_10, phi_bb266_11, phi_bb266_14, phi_bb266_15, phi_bb266_21}, &block269, std::vector<compiler::Node*>{phi_bb266_7, phi_bb266_9, phi_bb266_10, phi_bb266_11, phi_bb266_14, phi_bb266_15, phi_bb266_21});
  }

  TNode<IntPtrT> phi_bb268_7;
  TNode<IntPtrT> phi_bb268_9;
  TNode<IntPtrT> phi_bb268_10;
  TNode<IntPtrT> phi_bb268_11;
  TNode<IntPtrT> phi_bb268_14;
  TNode<BoolT> phi_bb268_15;
  TNode<IntPtrT> phi_bb268_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp579;
  TNode<IntPtrT> tmp580;
  TNode<IntPtrT> tmp581;
  TNode<BoolT> tmp582;
  if (block268.is_used()) {
    ca_.Bind(&block268, &phi_bb268_7, &phi_bb268_9, &phi_bb268_10, &phi_bb268_11, &phi_bb268_14, &phi_bb268_15, &phi_bb268_21);
    std::tie(tmp579, tmp580) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb268_14}).Flatten();
    tmp581 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp582 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block264, phi_bb268_7, phi_bb268_9, phi_bb268_10, phi_bb268_11, tmp581, tmp582, phi_bb268_21, tmp579, tmp580);
  }

  TNode<IntPtrT> phi_bb269_7;
  TNode<IntPtrT> phi_bb269_9;
  TNode<IntPtrT> phi_bb269_10;
  TNode<IntPtrT> phi_bb269_11;
  TNode<IntPtrT> phi_bb269_14;
  TNode<BoolT> phi_bb269_15;
  TNode<IntPtrT> phi_bb269_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp583;
  TNode<IntPtrT> tmp584;
  TNode<IntPtrT> tmp585;
  TNode<IntPtrT> tmp586;
  TNode<IntPtrT> tmp587;
  TNode<IntPtrT> tmp588;
  TNode<BoolT> tmp589;
  if (block269.is_used()) {
    ca_.Bind(&block269, &phi_bb269_7, &phi_bb269_9, &phi_bb269_10, &phi_bb269_11, &phi_bb269_14, &phi_bb269_15, &phi_bb269_21);
    std::tie(tmp583, tmp584) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb269_11}).Flatten();
    tmp585 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp586 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb269_11}, TNode<IntPtrT>{tmp585});
    tmp587 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp588 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp586}, TNode<IntPtrT>{tmp587});
    tmp589 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block264, phi_bb269_7, phi_bb269_9, phi_bb269_10, tmp588, tmp586, tmp589, phi_bb269_21, tmp583, tmp584);
  }

  TNode<IntPtrT> phi_bb264_7;
  TNode<IntPtrT> phi_bb264_9;
  TNode<IntPtrT> phi_bb264_10;
  TNode<IntPtrT> phi_bb264_11;
  TNode<IntPtrT> phi_bb264_14;
  TNode<BoolT> phi_bb264_15;
  TNode<IntPtrT> phi_bb264_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb264_23;
  TNode<IntPtrT> phi_bb264_24;
  if (block264.is_used()) {
    ca_.Bind(&block264, &phi_bb264_7, &phi_bb264_9, &phi_bb264_10, &phi_bb264_11, &phi_bb264_14, &phi_bb264_15, &phi_bb264_21, &phi_bb264_23, &phi_bb264_24);
    ca_.Goto(&block258, phi_bb264_7, phi_bb264_9, phi_bb264_10, phi_bb264_11, phi_bb264_14, phi_bb264_15, phi_bb264_21, phi_bb264_23, phi_bb264_24);
  }

  TNode<IntPtrT> phi_bb262_7;
  TNode<IntPtrT> phi_bb262_9;
  TNode<IntPtrT> phi_bb262_10;
  TNode<IntPtrT> phi_bb262_11;
  TNode<IntPtrT> phi_bb262_14;
  TNode<BoolT> phi_bb262_15;
  TNode<IntPtrT> phi_bb262_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp590;
  TNode<IntPtrT> tmp591;
  TNode<IntPtrT> tmp592;
  TNode<IntPtrT> tmp593;
  TNode<BoolT> tmp594;
  if (block262.is_used()) {
    ca_.Bind(&block262, &phi_bb262_7, &phi_bb262_9, &phi_bb262_10, &phi_bb262_11, &phi_bb262_14, &phi_bb262_15, &phi_bb262_21);
    std::tie(tmp590, tmp591) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp336}, TNode<IntPtrT>{phi_bb262_11}).Flatten();
    tmp592 = FromConstexpr_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_)))));
    tmp593 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb262_11}, TNode<IntPtrT>{tmp592});
    tmp594 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block258, phi_bb262_7, phi_bb262_9, phi_bb262_10, tmp593, phi_bb262_14, tmp594, phi_bb262_21, tmp590, tmp591);
  }

  TNode<IntPtrT> phi_bb258_7;
  TNode<IntPtrT> phi_bb258_9;
  TNode<IntPtrT> phi_bb258_10;
  TNode<IntPtrT> phi_bb258_11;
  TNode<IntPtrT> phi_bb258_14;
  TNode<BoolT> phi_bb258_15;
  TNode<IntPtrT> phi_bb258_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb258_23;
  TNode<IntPtrT> phi_bb258_24;
  TNode<Union<HeapObject, TaggedIndex>> tmp595;
  TNode<IntPtrT> tmp596;
  TNode<Float64T> tmp597;
  TNode<Union<HeapObject, TaggedIndex>> tmp598;
  TNode<IntPtrT> tmp599;
  TNode<IntPtrT> tmp600;
  TNode<UintPtrT> tmp601;
  TNode<UintPtrT> tmp602;
  TNode<BoolT> tmp603;
  if (block258.is_used()) {
    ca_.Bind(&block258, &phi_bb258_7, &phi_bb258_9, &phi_bb258_10, &phi_bb258_11, &phi_bb258_14, &phi_bb258_15, &phi_bb258_21, &phi_bb258_23, &phi_bb258_24);
    std::tie(tmp595, tmp596) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb258_23}, TNode<IntPtrT>{phi_bb258_24}, TorqueStructUnsafe_0{}}).Flatten();
    tmp597 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp595, tmp596});
    std::tie(tmp598, tmp599, tmp600) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp601 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb258_21});
    tmp602 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp600});
    tmp603 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp601}, TNode<UintPtrT>{tmp602});
    ca_.Branch(tmp603, &block274, std::vector<compiler::Node*>{phi_bb258_7, phi_bb258_9, phi_bb258_10, phi_bb258_11, phi_bb258_14, phi_bb258_15, phi_bb258_21, phi_bb258_23, phi_bb258_24, phi_bb258_21, phi_bb258_21, phi_bb258_21, phi_bb258_21}, &block275, std::vector<compiler::Node*>{phi_bb258_7, phi_bb258_9, phi_bb258_10, phi_bb258_11, phi_bb258_14, phi_bb258_15, phi_bb258_21, phi_bb258_23, phi_bb258_24, phi_bb258_21, phi_bb258_21, phi_bb258_21, phi_bb258_21});
  }

  TNode<IntPtrT> phi_bb274_7;
  TNode<IntPtrT> phi_bb274_9;
  TNode<IntPtrT> phi_bb274_10;
  TNode<IntPtrT> phi_bb274_11;
  TNode<IntPtrT> phi_bb274_14;
  TNode<BoolT> phi_bb274_15;
  TNode<IntPtrT> phi_bb274_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb274_23;
  TNode<IntPtrT> phi_bb274_24;
  TNode<IntPtrT> phi_bb274_30;
  TNode<IntPtrT> phi_bb274_31;
  TNode<IntPtrT> phi_bb274_35;
  TNode<IntPtrT> phi_bb274_36;
  TNode<IntPtrT> tmp604;
  TNode<IntPtrT> tmp605;
  TNode<Union<HeapObject, TaggedIndex>> tmp606;
  TNode<IntPtrT> tmp607;
  TNode<Number> tmp608;
  if (block274.is_used()) {
    ca_.Bind(&block274, &phi_bb274_7, &phi_bb274_9, &phi_bb274_10, &phi_bb274_11, &phi_bb274_14, &phi_bb274_15, &phi_bb274_21, &phi_bb274_23, &phi_bb274_24, &phi_bb274_30, &phi_bb274_31, &phi_bb274_35, &phi_bb274_36);
    tmp604 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb274_36});
    tmp605 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp599}, TNode<IntPtrT>{tmp604});
    std::tie(tmp606, tmp607) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp598}, TNode<IntPtrT>{tmp605}).Flatten();
    tmp608 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp597});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp606, tmp607}, tmp608);
    ca_.Goto(&block257, phi_bb274_7, tmp566, phi_bb274_9, phi_bb274_10, phi_bb274_11, phi_bb274_14, phi_bb274_15, phi_bb274_21);
  }

  TNode<IntPtrT> phi_bb275_7;
  TNode<IntPtrT> phi_bb275_9;
  TNode<IntPtrT> phi_bb275_10;
  TNode<IntPtrT> phi_bb275_11;
  TNode<IntPtrT> phi_bb275_14;
  TNode<BoolT> phi_bb275_15;
  TNode<IntPtrT> phi_bb275_21;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb275_23;
  TNode<IntPtrT> phi_bb275_24;
  TNode<IntPtrT> phi_bb275_30;
  TNode<IntPtrT> phi_bb275_31;
  TNode<IntPtrT> phi_bb275_35;
  TNode<IntPtrT> phi_bb275_36;
  if (block275.is_used()) {
    ca_.Bind(&block275, &phi_bb275_7, &phi_bb275_9, &phi_bb275_10, &phi_bb275_11, &phi_bb275_14, &phi_bb275_15, &phi_bb275_21, &phi_bb275_23, &phi_bb275_24, &phi_bb275_30, &phi_bb275_31, &phi_bb275_35, &phi_bb275_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb256_7;
  TNode<IntPtrT> phi_bb256_8;
  TNode<IntPtrT> phi_bb256_9;
  TNode<IntPtrT> phi_bb256_10;
  TNode<IntPtrT> phi_bb256_11;
  TNode<IntPtrT> phi_bb256_14;
  TNode<BoolT> phi_bb256_15;
  TNode<IntPtrT> phi_bb256_21;
  TNode<Uint32T> tmp609;
  TNode<Uint32T> tmp610;
  TNode<Uint32T> tmp611;
  TNode<BoolT> tmp612;
  if (block256.is_used()) {
    ca_.Bind(&block256, &phi_bb256_7, &phi_bb256_8, &phi_bb256_9, &phi_bb256_10, &phi_bb256_11, &phi_bb256_14, &phi_bb256_15, &phi_bb256_21);
    tmp609 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp610 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp353}, TNode<Uint32T>{tmp609});
    tmp611 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp612 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp610}, TNode<Uint32T>{tmp611});
    ca_.Branch(tmp612, &block278, std::vector<compiler::Node*>{phi_bb256_7, phi_bb256_8, phi_bb256_9, phi_bb256_10, phi_bb256_11, phi_bb256_14, phi_bb256_15, phi_bb256_21}, &block279, std::vector<compiler::Node*>{phi_bb256_7, phi_bb256_8, phi_bb256_9, phi_bb256_10, phi_bb256_11, phi_bb256_14, phi_bb256_15, phi_bb256_21});
  }

  TNode<IntPtrT> phi_bb279_7;
  TNode<IntPtrT> phi_bb279_8;
  TNode<IntPtrT> phi_bb279_9;
  TNode<IntPtrT> phi_bb279_10;
  TNode<IntPtrT> phi_bb279_11;
  TNode<IntPtrT> phi_bb279_14;
  TNode<BoolT> phi_bb279_15;
  TNode<IntPtrT> phi_bb279_21;
  if (block279.is_used()) {
    ca_.Bind(&block279, &phi_bb279_7, &phi_bb279_8, &phi_bb279_9, &phi_bb279_10, &phi_bb279_11, &phi_bb279_14, &phi_bb279_15, &phi_bb279_21);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 1051});
      CodeStubAssembler(state_).FailAssert("Torque assert '(retType & kValueTypeIsRefBit) != 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb278_7;
  TNode<IntPtrT> phi_bb278_8;
  TNode<IntPtrT> phi_bb278_9;
  TNode<IntPtrT> phi_bb278_10;
  TNode<IntPtrT> phi_bb278_11;
  TNode<IntPtrT> phi_bb278_14;
  TNode<BoolT> phi_bb278_15;
  TNode<IntPtrT> phi_bb278_21;
  TNode<Union<HeapObject, TaggedIndex>> tmp613;
  TNode<IntPtrT> tmp614;
  TNode<IntPtrT> tmp615;
  TNode<UintPtrT> tmp616;
  TNode<UintPtrT> tmp617;
  TNode<BoolT> tmp618;
  if (block278.is_used()) {
    ca_.Bind(&block278, &phi_bb278_7, &phi_bb278_8, &phi_bb278_9, &phi_bb278_10, &phi_bb278_11, &phi_bb278_14, &phi_bb278_15, &phi_bb278_21);
    std::tie(tmp613, tmp614, tmp615) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp616 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb278_21});
    tmp617 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp615});
    tmp618 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp616}, TNode<UintPtrT>{tmp617});
    ca_.Branch(tmp618, &block284, std::vector<compiler::Node*>{phi_bb278_7, phi_bb278_8, phi_bb278_9, phi_bb278_10, phi_bb278_11, phi_bb278_14, phi_bb278_15, phi_bb278_21, phi_bb278_21, phi_bb278_21, phi_bb278_21, phi_bb278_21}, &block285, std::vector<compiler::Node*>{phi_bb278_7, phi_bb278_8, phi_bb278_9, phi_bb278_10, phi_bb278_11, phi_bb278_14, phi_bb278_15, phi_bb278_21, phi_bb278_21, phi_bb278_21, phi_bb278_21, phi_bb278_21});
  }

  TNode<IntPtrT> phi_bb284_7;
  TNode<IntPtrT> phi_bb284_8;
  TNode<IntPtrT> phi_bb284_9;
  TNode<IntPtrT> phi_bb284_10;
  TNode<IntPtrT> phi_bb284_11;
  TNode<IntPtrT> phi_bb284_14;
  TNode<BoolT> phi_bb284_15;
  TNode<IntPtrT> phi_bb284_21;
  TNode<IntPtrT> phi_bb284_27;
  TNode<IntPtrT> phi_bb284_28;
  TNode<IntPtrT> phi_bb284_32;
  TNode<IntPtrT> phi_bb284_33;
  TNode<IntPtrT> tmp619;
  TNode<IntPtrT> tmp620;
  TNode<Union<HeapObject, TaggedIndex>> tmp621;
  TNode<IntPtrT> tmp622;
  TNode<Object> tmp623;
  TNode<Union<HeapObject, TaggedIndex>> tmp624;
  TNode<IntPtrT> tmp625;
  TNode<IntPtrT> tmp626;
  TNode<UintPtrT> tmp627;
  TNode<UintPtrT> tmp628;
  TNode<BoolT> tmp629;
  if (block284.is_used()) {
    ca_.Bind(&block284, &phi_bb284_7, &phi_bb284_8, &phi_bb284_9, &phi_bb284_10, &phi_bb284_11, &phi_bb284_14, &phi_bb284_15, &phi_bb284_21, &phi_bb284_27, &phi_bb284_28, &phi_bb284_32, &phi_bb284_33);
    tmp619 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb284_33});
    tmp620 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp614}, TNode<IntPtrT>{tmp619});
    std::tie(tmp621, tmp622) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp613}, TNode<IntPtrT>{tmp620}).Flatten();
    tmp623 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp621, tmp622});
    std::tie(tmp624, tmp625, tmp626) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp95}).Flatten();
    tmp627 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb284_21});
    tmp628 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp626});
    tmp629 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp627}, TNode<UintPtrT>{tmp628});
    ca_.Branch(tmp629, &block292, std::vector<compiler::Node*>{phi_bb284_7, phi_bb284_8, phi_bb284_9, phi_bb284_10, phi_bb284_11, phi_bb284_14, phi_bb284_15, phi_bb284_21, phi_bb284_21, phi_bb284_21, phi_bb284_21, phi_bb284_21}, &block293, std::vector<compiler::Node*>{phi_bb284_7, phi_bb284_8, phi_bb284_9, phi_bb284_10, phi_bb284_11, phi_bb284_14, phi_bb284_15, phi_bb284_21, phi_bb284_21, phi_bb284_21, phi_bb284_21, phi_bb284_21});
  }

  TNode<IntPtrT> phi_bb285_7;
  TNode<IntPtrT> phi_bb285_8;
  TNode<IntPtrT> phi_bb285_9;
  TNode<IntPtrT> phi_bb285_10;
  TNode<IntPtrT> phi_bb285_11;
  TNode<IntPtrT> phi_bb285_14;
  TNode<BoolT> phi_bb285_15;
  TNode<IntPtrT> phi_bb285_21;
  TNode<IntPtrT> phi_bb285_27;
  TNode<IntPtrT> phi_bb285_28;
  TNode<IntPtrT> phi_bb285_32;
  TNode<IntPtrT> phi_bb285_33;
  if (block285.is_used()) {
    ca_.Bind(&block285, &phi_bb285_7, &phi_bb285_8, &phi_bb285_9, &phi_bb285_10, &phi_bb285_11, &phi_bb285_14, &phi_bb285_15, &phi_bb285_21, &phi_bb285_27, &phi_bb285_28, &phi_bb285_32, &phi_bb285_33);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb292_7;
  TNode<IntPtrT> phi_bb292_8;
  TNode<IntPtrT> phi_bb292_9;
  TNode<IntPtrT> phi_bb292_10;
  TNode<IntPtrT> phi_bb292_11;
  TNode<IntPtrT> phi_bb292_14;
  TNode<BoolT> phi_bb292_15;
  TNode<IntPtrT> phi_bb292_21;
  TNode<IntPtrT> phi_bb292_28;
  TNode<IntPtrT> phi_bb292_29;
  TNode<IntPtrT> phi_bb292_33;
  TNode<IntPtrT> phi_bb292_34;
  TNode<IntPtrT> tmp630;
  TNode<IntPtrT> tmp631;
  TNode<Union<HeapObject, TaggedIndex>> tmp632;
  TNode<IntPtrT> tmp633;
  TNode<JSAny> tmp634;
  if (block292.is_used()) {
    ca_.Bind(&block292, &phi_bb292_7, &phi_bb292_8, &phi_bb292_9, &phi_bb292_10, &phi_bb292_11, &phi_bb292_14, &phi_bb292_15, &phi_bb292_21, &phi_bb292_28, &phi_bb292_29, &phi_bb292_33, &phi_bb292_34);
    tmp630 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb292_34});
    tmp631 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp625}, TNode<IntPtrT>{tmp630});
    std::tie(tmp632, tmp633) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp624}, TNode<IntPtrT>{tmp631}).Flatten();
    tmp634 = WasmToJSObject_0(state_, TNode<NativeContext>{parameter0}, TNode<Object>{tmp623});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp632, tmp633}, tmp634);
    ca_.Goto(&block257, phi_bb292_7, phi_bb292_8, phi_bb292_9, phi_bb292_10, phi_bb292_11, phi_bb292_14, phi_bb292_15, phi_bb292_21);
  }

  TNode<IntPtrT> phi_bb293_7;
  TNode<IntPtrT> phi_bb293_8;
  TNode<IntPtrT> phi_bb293_9;
  TNode<IntPtrT> phi_bb293_10;
  TNode<IntPtrT> phi_bb293_11;
  TNode<IntPtrT> phi_bb293_14;
  TNode<BoolT> phi_bb293_15;
  TNode<IntPtrT> phi_bb293_21;
  TNode<IntPtrT> phi_bb293_28;
  TNode<IntPtrT> phi_bb293_29;
  TNode<IntPtrT> phi_bb293_33;
  TNode<IntPtrT> phi_bb293_34;
  if (block293.is_used()) {
    ca_.Bind(&block293, &phi_bb293_7, &phi_bb293_8, &phi_bb293_9, &phi_bb293_10, &phi_bb293_11, &phi_bb293_14, &phi_bb293_15, &phi_bb293_21, &phi_bb293_28, &phi_bb293_29, &phi_bb293_33, &phi_bb293_34);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb257_7;
  TNode<IntPtrT> phi_bb257_8;
  TNode<IntPtrT> phi_bb257_9;
  TNode<IntPtrT> phi_bb257_10;
  TNode<IntPtrT> phi_bb257_11;
  TNode<IntPtrT> phi_bb257_14;
  TNode<BoolT> phi_bb257_15;
  TNode<IntPtrT> phi_bb257_21;
  if (block257.is_used()) {
    ca_.Bind(&block257, &phi_bb257_7, &phi_bb257_8, &phi_bb257_9, &phi_bb257_10, &phi_bb257_11, &phi_bb257_14, &phi_bb257_15, &phi_bb257_21);
    ca_.Goto(&block208, phi_bb257_7, phi_bb257_8, phi_bb257_9, phi_bb257_10, phi_bb257_11, phi_bb257_14, phi_bb257_15, phi_bb257_21);
  }

  TNode<IntPtrT> phi_bb208_7;
  TNode<IntPtrT> phi_bb208_8;
  TNode<IntPtrT> phi_bb208_9;
  TNode<IntPtrT> phi_bb208_10;
  TNode<IntPtrT> phi_bb208_11;
  TNode<IntPtrT> phi_bb208_14;
  TNode<BoolT> phi_bb208_15;
  TNode<IntPtrT> phi_bb208_21;
  if (block208.is_used()) {
    ca_.Bind(&block208, &phi_bb208_7, &phi_bb208_8, &phi_bb208_9, &phi_bb208_10, &phi_bb208_11, &phi_bb208_14, &phi_bb208_15, &phi_bb208_21);
    ca_.Goto(&block174, phi_bb208_7, phi_bb208_8, phi_bb208_9, phi_bb208_10, phi_bb208_11, phi_bb208_14, phi_bb208_15, phi_bb208_21);
  }

  TNode<IntPtrT> phi_bb174_7;
  TNode<IntPtrT> phi_bb174_8;
  TNode<IntPtrT> phi_bb174_9;
  TNode<IntPtrT> phi_bb174_10;
  TNode<IntPtrT> phi_bb174_11;
  TNode<IntPtrT> phi_bb174_14;
  TNode<BoolT> phi_bb174_15;
  TNode<IntPtrT> phi_bb174_21;
  if (block174.is_used()) {
    ca_.Bind(&block174, &phi_bb174_7, &phi_bb174_8, &phi_bb174_9, &phi_bb174_10, &phi_bb174_11, &phi_bb174_14, &phi_bb174_15, &phi_bb174_21);
    ca_.Goto(&block151, phi_bb174_7, phi_bb174_8, phi_bb174_9, phi_bb174_10, phi_bb174_11, phi_bb174_14, phi_bb174_15, phi_bb174_21);
  }

  TNode<IntPtrT> phi_bb151_7;
  TNode<IntPtrT> phi_bb151_8;
  TNode<IntPtrT> phi_bb151_9;
  TNode<IntPtrT> phi_bb151_10;
  TNode<IntPtrT> phi_bb151_11;
  TNode<IntPtrT> phi_bb151_14;
  TNode<BoolT> phi_bb151_15;
  TNode<IntPtrT> phi_bb151_21;
  TNode<IntPtrT> tmp635;
  TNode<IntPtrT> tmp636;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_7, &phi_bb151_8, &phi_bb151_9, &phi_bb151_10, &phi_bb151_11, &phi_bb151_14, &phi_bb151_15, &phi_bb151_21);
    tmp635 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp636 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb151_21}, TNode<IntPtrT>{tmp635});
    ca_.Goto(&block146, phi_bb151_7, phi_bb151_8, phi_bb151_9, phi_bb151_10, phi_bb151_11, phi_bb151_14, phi_bb151_15, tmp636);
  }

  TNode<IntPtrT> phi_bb145_7;
  TNode<IntPtrT> phi_bb145_8;
  TNode<IntPtrT> phi_bb145_9;
  TNode<IntPtrT> phi_bb145_10;
  TNode<IntPtrT> phi_bb145_11;
  TNode<IntPtrT> phi_bb145_14;
  TNode<BoolT> phi_bb145_15;
  TNode<IntPtrT> phi_bb145_21;
  TNode<IntPtrT> tmp637;
  TNode<BoolT> tmp638;
  if (block145.is_used()) {
    ca_.Bind(&block145, &phi_bb145_7, &phi_bb145_8, &phi_bb145_9, &phi_bb145_10, &phi_bb145_11, &phi_bb145_14, &phi_bb145_15, &phi_bb145_21);
    tmp637 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp638 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp343}, TNode<IntPtrT>{tmp637});
    ca_.Branch(tmp638, &block299, std::vector<compiler::Node*>{phi_bb145_7, phi_bb145_8, phi_bb145_9, phi_bb145_10, phi_bb145_11, phi_bb145_14, phi_bb145_15}, &block300, std::vector<compiler::Node*>{phi_bb145_7, phi_bb145_8, phi_bb145_9, phi_bb145_10, phi_bb145_11, phi_bb145_14, phi_bb145_15});
  }

  TNode<IntPtrT> phi_bb299_7;
  TNode<IntPtrT> phi_bb299_8;
  TNode<IntPtrT> phi_bb299_9;
  TNode<IntPtrT> phi_bb299_10;
  TNode<IntPtrT> phi_bb299_11;
  TNode<IntPtrT> phi_bb299_14;
  TNode<BoolT> phi_bb299_15;
  TNode<BoolT> tmp639;
  if (block299.is_used()) {
    ca_.Bind(&block299, &phi_bb299_7, &phi_bb299_8, &phi_bb299_9, &phi_bb299_10, &phi_bb299_11, &phi_bb299_14, &phi_bb299_15);
    tmp639 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block301, phi_bb299_7, phi_bb299_8, phi_bb299_9, phi_bb299_10, phi_bb299_11, phi_bb299_14, phi_bb299_15, tmp639);
  }

  TNode<IntPtrT> phi_bb300_7;
  TNode<IntPtrT> phi_bb300_8;
  TNode<IntPtrT> phi_bb300_9;
  TNode<IntPtrT> phi_bb300_10;
  TNode<IntPtrT> phi_bb300_11;
  TNode<IntPtrT> phi_bb300_14;
  TNode<BoolT> phi_bb300_15;
  TNode<BoolT> tmp640;
  if (block300.is_used()) {
    ca_.Bind(&block300, &phi_bb300_7, &phi_bb300_8, &phi_bb300_9, &phi_bb300_10, &phi_bb300_11, &phi_bb300_14, &phi_bb300_15);
    tmp640 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb300_11}, TNode<IntPtrT>{tmp343});
    ca_.Goto(&block301, phi_bb300_7, phi_bb300_8, phi_bb300_9, phi_bb300_10, phi_bb300_11, phi_bb300_14, phi_bb300_15, tmp640);
  }

  TNode<IntPtrT> phi_bb301_7;
  TNode<IntPtrT> phi_bb301_8;
  TNode<IntPtrT> phi_bb301_9;
  TNode<IntPtrT> phi_bb301_10;
  TNode<IntPtrT> phi_bb301_11;
  TNode<IntPtrT> phi_bb301_14;
  TNode<BoolT> phi_bb301_15;
  TNode<BoolT> phi_bb301_22;
  if (block301.is_used()) {
    ca_.Bind(&block301, &phi_bb301_7, &phi_bb301_8, &phi_bb301_9, &phi_bb301_10, &phi_bb301_11, &phi_bb301_14, &phi_bb301_15, &phi_bb301_22);
    ca_.Branch(phi_bb301_22, &block297, std::vector<compiler::Node*>{phi_bb301_7, phi_bb301_8, phi_bb301_9, phi_bb301_10, phi_bb301_11, phi_bb301_14, phi_bb301_15}, &block298, std::vector<compiler::Node*>{phi_bb301_7, phi_bb301_8, phi_bb301_9, phi_bb301_10, phi_bb301_11, phi_bb301_14, phi_bb301_15});
  }

  TNode<IntPtrT> phi_bb298_7;
  TNode<IntPtrT> phi_bb298_8;
  TNode<IntPtrT> phi_bb298_9;
  TNode<IntPtrT> phi_bb298_10;
  TNode<IntPtrT> phi_bb298_11;
  TNode<IntPtrT> phi_bb298_14;
  TNode<BoolT> phi_bb298_15;
  if (block298.is_used()) {
    ca_.Bind(&block298, &phi_bb298_7, &phi_bb298_8, &phi_bb298_9, &phi_bb298_10, &phi_bb298_11, &phi_bb298_14, &phi_bb298_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/js-to-wasm.tq", 379});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.paramBufferEnd == 0 || this.nextStack <= this.paramBufferEnd' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb297_7;
  TNode<IntPtrT> phi_bb297_8;
  TNode<IntPtrT> phi_bb297_9;
  TNode<IntPtrT> phi_bb297_10;
  TNode<IntPtrT> phi_bb297_11;
  TNode<IntPtrT> phi_bb297_14;
  TNode<BoolT> phi_bb297_15;
  if (block297.is_used()) {
    ca_.Bind(&block297, &phi_bb297_7, &phi_bb297_8, &phi_bb297_9, &phi_bb297_10, &phi_bb297_11, &phi_bb297_14, &phi_bb297_15);
    CodeStubAssembler(state_).Return(parameter1);
  }
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=412&c=47
int31_t SizeOf_intptr_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return kIntptrSize;
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=420&c=32
int31_t SizeOf_float64_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return kDoubleSize;
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=483&c=8
TorqueStructReference_float64_0 RefCast_float64_0(compiler::CodeAssemblerState* state_, TorqueStructReference_intptr_0 p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NewReference_float64_0(state_, TNode<Union<HeapObject, TaggedIndex>>{p_i.object}, TNode<IntPtrT>{p_i.offset}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_float64_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=486&c=8
TorqueStructReference_float32_0 RefCast_float32_0(compiler::CodeAssemblerState* state_, TorqueStructReference_intptr_0 p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NewReference_float32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{p_i.object}, TNode<IntPtrT>{p_i.offset}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_float32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=528&c=23
TorqueStructReference_intptr_0 GetRefAt_intptr_RawFunctionSigPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=532&c=17
TorqueStructReference_RawPtr_0 GetRefAt_RawPtr_RawFunctionSigPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_RawPtr_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_RawPtr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=534&c=20
TorqueStructSlice_uint32_ConstReference_uint32_0 NewOffHeapConstSlice_uint32_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_startPointer, TNode<IntPtrT> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<TaggedIndex> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Union<HeapObject, TaggedIndex>> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kZeroBitPattern_0(state_);
    tmp1 = Convert_RawPtr_RawPtr_uint32_0(state_, TNode<RawPtrT>{p_startPointer});
    tmp2 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, kHeapObjectTag);
    tmp4 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp3});
    std::tie(tmp5, tmp6, tmp7) = (TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{p_length}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp5}, TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp7}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=550&c=25
TorqueStructSlice_uint32_ConstReference_uint32_0 Subslice_uint32_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_uint32_ConstReference_uint32_0 p_slice, TNode<IntPtrT> p_start, TNode<IntPtrT> p_length, compiler::CodeAssemblerLabel* label_OutOfBounds) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  TNode<UintPtrT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{p_length});
    tmp1 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{p_slice.length});
    tmp2 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{tmp1});
    ca_.Branch(tmp2, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<UintPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{p_start});
    tmp4 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{p_slice.length}, TNode<IntPtrT>{p_length});
    tmp5 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{tmp4});
    tmp6 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{p_start});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{p_slice.offset}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10, tmp11) = NewConstSlice_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{p_slice.object}, TNode<IntPtrT>{tmp8}, TNode<IntPtrT>{p_length}).Flatten();
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_OutOfBounds);
  }

    ca_.Bind(&block7);
  return TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp9}, TNode<IntPtrT>{tmp10}, TNode<IntPtrT>{tmp11}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=637&c=19
TorqueStructReference_intptr_0 NewOffHeapReference_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_ptr) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<TaggedIndex> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Union<HeapObject, TaggedIndex>> tmp5;
  TNode<IntPtrT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kZeroBitPattern_0(state_);
    tmp1 = Convert_RawPtr_RawPtr_intptr_0(state_, TNode<RawPtrT>{p_ptr});
    tmp2 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, kHeapObjectTag);
    tmp4 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp3});
    std::tie(tmp5, tmp6) = (TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp4}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp5}, TNode<IntPtrT>{tmp6}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=308&c=22
TorqueStructReference_intptr_0 NewReference_intptr_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = (TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{p_object}, TNode<IntPtrT>{p_offset}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=796&c=4
TorqueStructReference_int32_0 GetRefAt_int32_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_int32_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_int32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=798&c=4
TorqueStructReference_bool_0 GetRefAt_bool_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_bool_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_bool_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=799&c=4
TorqueStructReference_RawPtr_0 GetRefAt_RawPtr_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_RawPtr_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_RawPtr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=800&c=4
TorqueStructReference_intptr_0 GetRefAt_intptr_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=802&c=4
TorqueStructReference_WasmCodePointer_0 GetRefAt_WasmCodePointer_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_WasmCodePointer_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_WasmCodePointer_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=804&c=4
TorqueStructReference_RawPtr_intptr_0 GetRefAt_RawPtr_intptr_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_RawPtr_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=864&c=7
TNode<BoolT> Is_WasmFuncRef_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<WasmFuncRef> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_WasmFuncRef_1(state_, TNode<Context>{p_context}, TNode<Object>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=865&c=22
TNode<WasmFuncRef> UnsafeCast_WasmFuncRef_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Is_WasmFuncRef_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<WasmFuncRef> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<WasmFuncRef>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=867&c=9
TNode<BoolT> Is_JSFunction_Undefined_OR_JSFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Union<JSFunction, Undefined>> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSFunction> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSFunction_0(state_, TNode<HeapObject>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=868&c=14
TNode<JSFunction> UnsafeCast_JSFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Is_JSFunction_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<JSFunction> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSFunction>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=874&c=7
TNode<BoolT> Is_String_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<String> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_String_1(state_, TNode<Context>{p_context}, TNode<Object>{p_o}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp3);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block6);
  }

    ca_.Bind(&block6);
  return TNode<BoolT>{phi_bb1_2};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=892&c=22
TorqueStructReference_uint32_0 GetRefAt_uint32_RawPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_uint32_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=896&c=37
TorqueStructReference_int64_0 GetRefAt_int64_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_int64_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_int64_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=905&c=58
TorqueStructReference_float64_0 GetRefAt_float64_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_float64_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_float64_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=915&c=13
TorqueStructReference_float32_0 GetRefAt_float32_RawPtr_intptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_float32_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_float32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=938&c=23
TorqueStructReference_uintptr_0 GetRefAt_uintptr_RawPtr_uintptr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<RawPtrT> tmp1;
  TNode<Union<HeapObject, TaggedIndex>> tmp2;
  TNode<IntPtrT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{p_base}, TNode<IntPtrT>{p_offset});
    tmp1 = (TNode<RawPtrT>{tmp0});
    std::tie(tmp2, tmp3) = NewOffHeapReference_uintptr_0(state_, TNode<RawPtrT>{tmp1}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_uintptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp2}, TNode<IntPtrT>{tmp3}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=1009&c=37
TorqueStructReference_int64_0 RefCast_int64_0(compiler::CodeAssemblerState* state_, TorqueStructReference_intptr_0 p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NewReference_int64_0(state_, TNode<Union<HeapObject, TaggedIndex>>{p_i.object}, TNode<IntPtrT>{p_i.offset}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_int64_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=1011&c=16
TorqueStructReference_int32_0 RefCast_int32_0(compiler::CodeAssemblerState* state_, TorqueStructReference_intptr_0 p_i) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NewReference_int32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{p_i.object}, TNode<IntPtrT>{p_i.offset}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_int32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=155&c=10
TorqueStructReference_float32_0 NewReference_float32_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = (TorqueStructReference_float32_0{TNode<Union<HeapObject, TaggedIndex>>{p_object}, TNode<IntPtrT>{p_offset}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_float32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=155&c=10
TorqueStructReference_int64_0 NewReference_int64_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = (TorqueStructReference_int64_0{TNode<Union<HeapObject, TaggedIndex>>{p_object}, TNode<IntPtrT>{p_offset}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_int64_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/js-to-wasm.tq?l=155&c=10
TorqueStructReference_int32_0 NewReference_int32_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = (TorqueStructReference_int32_0{TNode<Union<HeapObject, TaggedIndex>>{p_object}, TNode<IntPtrT>{p_offset}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_int32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

} // namespace internal
} // namespace v8
