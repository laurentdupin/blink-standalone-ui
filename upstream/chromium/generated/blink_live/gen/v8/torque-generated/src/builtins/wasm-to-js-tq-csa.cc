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
#include "torque-generated/src/builtins/wasm-to-js-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frames-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/cell-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/builtins/js-to-wasm-tq-csa.h"
#include "torque-generated/src/builtins/wasm-tq-csa.h"
#include "torque-generated/src/builtins/wasm-to-js-tq-csa.h"
#include "torque-generated/src/wasm/wasm-objects-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=36&c=1
void HandleF32Returns_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TorqueStructLocationAllocator_0 p_locationAllocator, TorqueStructReference_intptr_0 p_toRef, TNode<JSAny> p_retVal) {
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
  TNode<Float64T> tmp4;
  TNode<Float64T> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    std::tie(tmp2, tmp3) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{p_toRef.object}, TNode<IntPtrT>{p_toRef.offset}, TorqueStructUnsafe_0{}}).Flatten();
    tmp4 = CodeStubAssembler(state_).ChangeTaggedToFloat64(TNode<Context>{p_context}, TNode<JSAny>{p_retVal});
    tmp5 = CodeStubAssembler(state_).Float64SilenceNaN(TNode<Float64T>{tmp4});
    CodeStubAssembler(state_).StoreReference<Float64T>(CodeStubAssembler::Reference{tmp2, tmp3}, tmp5);
    ca_.Goto(&block8);
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Float32T> tmp8;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    std::tie(tmp6, tmp7) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{p_toRef.object}, TNode<IntPtrT>{p_toRef.offset}, TorqueStructUnsafe_0{}}).Flatten();
    tmp8 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_retVal);
    CodeStubAssembler(state_).StoreReference<Float32T>(CodeStubAssembler::Reference{tmp6, tmp7}, tmp8);
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

  TNode<Float32T> tmp9;
  TNode<Uint32T> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp9 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_retVal);
    tmp10 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp9});
    tmp11 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp10});
    tmp12 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp13 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{tmp11}, TNode<IntPtrT>{tmp12});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{p_toRef.object, p_toRef.offset}, tmp13);
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

  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp14 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{p_locationAllocator.remainingFPRegs}, TNode<IntPtrT>{tmp14});
    ca_.Branch(tmp15, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<Float32T> tmp16;
  TNode<Uint32T> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp16 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_retVal);
    tmp17 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp16});
    tmp18 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp17});
    tmp19 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp20 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{tmp18}, TNode<IntPtrT>{tmp19});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{p_toRef.object, p_toRef.offset}, tmp20);
    ca_.Goto(&block18);
  }

  TNode<Float32T> tmp21;
  TNode<Uint32T> tmp22;
  TNode<IntPtrT> tmp23;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp21 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, p_context, p_retVal);
    tmp22 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp21});
    tmp23 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp22});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{p_toRef.object, p_toRef.offset}, tmp23);
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

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=58&c=1
TorqueStructWasmToJSResult WasmToJSWrapper_0(compiler::CodeAssemblerState* state_, TNode<WasmImportData> p_data) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Int32T> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block91(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Float32T> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block100(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block118(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block123(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block124(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block131(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block140(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block144(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block139(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block157(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block158(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block163(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block164(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block156(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block172(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block173(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block154(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block177(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block178(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block181(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block191(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block193(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block196(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block197(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block200(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block202(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block203(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block198(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block208(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block209(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, BoolT> block194(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block185(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT> block179(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT> block212(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT> block213(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, FixedArray> block214(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT> block217(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT> block218(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT> block219(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block223(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block221(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block225(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block226(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block232(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block233(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT, JSAny> block227(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT, JSAny> block239(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT, JSAny> block238(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block241(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block245(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block246(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block248(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block249(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block251(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block252(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block247(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block244(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT, JSAny, JSAny> block256(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT, JSAny, JSAny> block255(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT, JSAny> block253(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block242(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block257(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block261(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block262(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block264(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block265(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block267(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block268(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block263(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block260(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block269(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block270(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block271(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block258(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block272(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block276(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block277(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block278(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block282(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block283(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block285(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block286(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block281(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block279(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block275(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block273(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block287(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block290(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block294(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block295(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block297(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block298(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block300(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block301(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block296(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block293(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block291(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block303(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block304(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block306(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block307(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block309(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block310(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block305(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block302(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block312(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block313(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block315(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block316(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block318(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block319(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block314(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT, Union<HeapObject, TaggedIndex>, IntPtrT> block311(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block292(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block288(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block321(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block320(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block322(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block326(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block327(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block329(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block330(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block332(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block333(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block328(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny, Union<HeapObject, TaggedIndex>, IntPtrT> block325(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block323(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, JSAny, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block338(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, JSAny, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block339(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block324(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block289(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block274(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block259(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, JSAny> block243(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block222(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block342(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block345(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block346(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block350(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block348(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block355(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block354(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block357(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block360(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block361(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block363(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block364(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block366(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block367(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block362(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT> block359(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block372(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT, Union<HeapObject, TaggedIndex>, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block373(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, BoolT> block358(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, BoolT> block349(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT, IntPtrT, IntPtrT, BoolT> block343(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block376(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<RawPtrT> tmp0;
  TNode<WasmImportData> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SwitchToTheCentralStackIfNeeded();
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = Cast_WasmImportData_0(state_, TNode<HeapObject>{p_data}, &label2);
    ca_.Goto(&block7);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block8);
    }
  }

  TNode<BoolT> tmp3;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block4, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block4, tmp4);
  }

  TNode<BoolT> phi_bb4_4;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4);
    ca_.Branch(phi_bb4_4, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/wasm-to-js.tq", 61});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<WasmImportData>(data)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<RawPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<RawPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Cell> tmp17;
  TNode<Object> tmp18;
  TNode<Smi> tmp19;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = CodeStubAssembler(state_).LoadFramePointer();
    tmp6 = FromConstexpr_intptr_constexpr_intptr_0(state_, WasmToJSWrapperConstants::kSignatureOffset);
    tmp7 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{tmp5}, TNode<IntPtrT>{tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp9, tmp10) = GetRefAt_RawPtr_RawPtr_0(state_, TNode<RawPtrT>{tmp7}, TNode<IntPtrT>{tmp8}).Flatten();
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp12 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{p_data, tmp11});
    CodeStubAssembler(state_).StoreReference<RawPtrT>(CodeStubAssembler::Reference{tmp9, tmp10}, tmp12);
    tmp13 = CodeStubAssembler(state_).StackAlignmentInBytes();
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp15 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp14});
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp17 = CodeStubAssembler(state_).LoadReference<Cell>(CodeStubAssembler::Reference{p_data, tmp16});
    tmp18 = LoadCellValue_0(state_, TNode<Cell>{tmp17});
    compiler::CodeAssemblerLabel label20(&ca_);
    tmp19 = Cast_Smi_0(state_, TNode<Object>{tmp18}, &label20);
    ca_.Goto(&block15);
    if (label20.is_used()) {
      ca_.Bind(&label20);
      ca_.Goto(&block16);
    }
  }

  TNode<BoolT> tmp21;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp21 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block12, tmp21);
  }

  TNode<BoolT> tmp22;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp22 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block12, tmp22);
  }

  TNode<BoolT> phi_bb12_9;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_9);
    ca_.Branch(phi_bb12_9, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<BoolT> tmp25;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp23 = TORQUE_CAST(TNode<Object>{tmp18});
    tmp24 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp25 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp23}, TNode<Smi>{tmp24});
    ca_.Branch(tmp25, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/wasm-to-js.tq", 74});
      CodeStubAssembler(state_).FailAssert("Torque assert 'budget > 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp26;
  TNode<Smi> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Cell> tmp29;
  TNode<Smi> tmp30;
  TNode<BoolT> tmp31;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp26 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp27 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp23}, TNode<Smi>{tmp26});
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp29 = CodeStubAssembler(state_).LoadReference<Cell>(CodeStubAssembler::Reference{p_data, tmp28});
    StoreCellValue_0(state_, TNode<Cell>{tmp29}, TNode<Object>{tmp27});
    tmp30 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp31 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp27}, TNode<Smi>{tmp30});
    ca_.Branch(tmp31, &block19, std::vector<compiler::Node*>{}, &block20, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp32;
  TNode<JSAny> tmp33;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp32 = kNoContext_0(state_);
    tmp33 = TORQUE_CAST(CodeStubAssembler(state_).CallRuntime(Runtime::kTierUpWasmToJSWrapper, tmp32, p_data)); 
    ca_.Goto(&block20);
  }

  TNode<IntPtrT> tmp34;
  TNode<RawPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<RawPtrT> tmp37;
  TNode<RawPtrT> tmp38;
  TNode<Union<HeapObject, TaggedIndex>> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<RawPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<RawPtrT> tmp45;
  TNode<RawPtrT> tmp46;
  TNode<Union<HeapObject, TaggedIndex>> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<RawPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<RawPtrT> tmp53;
  TNode<RawPtrT> tmp54;
  TNode<Union<HeapObject, TaggedIndex>> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<RawPtrT> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<Union<HeapObject, TaggedIndex>> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<IntPtrT> tmp65;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp35 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{p_data, tmp34});
    tmp36 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp37 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{tmp35}, TNode<IntPtrT>{tmp36});
    tmp38 = (TNode<RawPtrT>{tmp37});
    std::tie(tmp39, tmp40) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp38}).Flatten();
    tmp41 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp39, tmp40});
    tmp42 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp43 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{p_data, tmp42});
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp45 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{tmp43}, TNode<IntPtrT>{tmp44});
    tmp46 = (TNode<RawPtrT>{tmp45});
    std::tie(tmp47, tmp48) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp46}).Flatten();
    tmp49 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp47, tmp48});
    tmp50 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp51 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{p_data, tmp50});
    tmp52 = FromConstexpr_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_)))));
    tmp53 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{tmp51}, TNode<IntPtrT>{tmp52});
    tmp54 = (TNode<RawPtrT>{tmp53});
    std::tie(tmp55, tmp56) = NewOffHeapReference_RawPtr_uint32_0(state_, TNode<RawPtrT>{tmp54}).Flatten();
    tmp57 = CodeStubAssembler(state_).LoadReference<RawPtrT>(CodeStubAssembler::Reference{tmp55, tmp56});
    tmp58 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp41});
    std::tie(tmp59, tmp60, tmp61) = NewOffHeapConstSlice_uint32_0(state_, TNode<RawPtrT>{tmp57}, TNode<IntPtrT>{tmp58}).Flatten();
    tmp62 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    compiler::CodeAssemblerLabel label66(&ca_);
    std::tie(tmp63, tmp64, tmp65) = Subslice_uint32_0(state_, TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp61}, TorqueStructUnsafe_0{}}, TNode<IntPtrT>{tmp62}, TNode<IntPtrT>{tmp41}, &label66).Flatten();
    ca_.Goto(&block23);
    if (label66.is_used()) {
      ca_.Bind(&label66);
      ca_.Goto(&block24);
    }
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/wasm-to-js.tq:93:63");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    compiler::CodeAssemblerLabel label70(&ca_);
    std::tie(tmp67, tmp68, tmp69) = Subslice_uint32_0(state_, TorqueStructSlice_uint32_ConstReference_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp61}, TorqueStructUnsafe_0{}}, TNode<IntPtrT>{tmp41}, TNode<IntPtrT>{tmp49}, &label70).Flatten();
    ca_.Goto(&block27);
    if (label70.is_used()) {
      ca_.Bind(&label70);
      ca_.Goto(&block28);
    }
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/wasm-to-js.tq:95:17");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<FixedArray> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<Union<HeapObject, TaggedIndex>> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<UintPtrT> tmp80;
  TNode<UintPtrT> tmp81;
  TNode<BoolT> tmp82;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp71 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp72 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp71});
    tmp73 = ca_.CallBuiltin<FixedArray>(Builtin::kWasmAllocateZeroedFixedArray, TNode<Object>(), tmp72);
    tmp74 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp75, tmp76, tmp77) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp78 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp79 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp74}, TNode<IntPtrT>{tmp78});
    tmp80 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp74});
    tmp81 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp77});
    tmp82 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp80}, TNode<UintPtrT>{tmp81});
    ca_.Branch(tmp82, &block33, std::vector<compiler::Node*>{}, &block34, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<Union<HeapObject, TaggedIndex>> tmp85;
  TNode<IntPtrT> tmp86;
  TNode<Undefined> tmp87;
  TNode<RawPtrT> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<IntPtrT> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<RawPtrT> tmp93;
  TNode<RawPtrT> tmp94;
  TNode<Union<HeapObject, TaggedIndex>> tmp95;
  TNode<IntPtrT> tmp96;
  TNode<IntPtrT> tmp97;
  TNode<Union<HeapObject, TaggedIndex>> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<IntPtrT> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<IntPtrT> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<BoolT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<BoolT> tmp110;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp83 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp74});
    tmp84 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp76}, TNode<IntPtrT>{tmp83});
    std::tie(tmp85, tmp86) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp75}, TNode<IntPtrT>{tmp84}).Flatten();
    tmp87 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp85, tmp86}, tmp87);
    tmp88 = CodeStubAssembler(state_).LoadFramePointer();
    tmp89 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp90 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp89}, TNode<IntPtrT>{tmp15});
    tmp91 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp92 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp90}, TNode<IntPtrT>{tmp91});
    tmp93 = CodeStubAssembler(state_).RawPtrAdd(TNode<RawPtrT>{tmp88}, TNode<IntPtrT>{tmp92});
    tmp94 = (TNode<RawPtrT>{tmp93});
    std::tie(tmp95, tmp96) = NewOffHeapReference_intptr_0(state_, TNode<RawPtrT>{tmp94}).Flatten();
    tmp97 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp98, tmp99, tmp100, tmp101, tmp102, tmp103, tmp104, tmp105, tmp106, tmp107) = LocationAllocatorForParams_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{tmp95}, TNode<IntPtrT>{tmp96}, TorqueStructUnsafe_0{}}, TNode<IntPtrT>{tmp97}).Flatten();
    tmp108 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{tmp69});
    tmp109 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp68}, TNode<IntPtrT>{tmp108});
    tmp110 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block40, tmp79, tmp99, tmp100, tmp101, tmp102, tmp103, tmp106, tmp107, tmp68, tmp110);
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb40_20;
  TNode<IntPtrT> phi_bb40_25;
  TNode<IntPtrT> phi_bb40_26;
  TNode<IntPtrT> phi_bb40_27;
  TNode<IntPtrT> phi_bb40_28;
  TNode<IntPtrT> phi_bb40_29;
  TNode<IntPtrT> phi_bb40_32;
  TNode<BoolT> phi_bb40_33;
  TNode<IntPtrT> phi_bb40_35;
  TNode<BoolT> phi_bb40_37;
  TNode<BoolT> tmp111;
  TNode<BoolT> tmp112;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_20, &phi_bb40_25, &phi_bb40_26, &phi_bb40_27, &phi_bb40_28, &phi_bb40_29, &phi_bb40_32, &phi_bb40_33, &phi_bb40_35, &phi_bb40_37);
    tmp111 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb40_35}, TNode<IntPtrT>{tmp109});
    tmp112 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp111});
    ca_.Branch(tmp112, &block38, std::vector<compiler::Node*>{phi_bb40_20, phi_bb40_25, phi_bb40_26, phi_bb40_27, phi_bb40_28, phi_bb40_29, phi_bb40_32, phi_bb40_33, phi_bb40_35, phi_bb40_37}, &block39, std::vector<compiler::Node*>{phi_bb40_20, phi_bb40_25, phi_bb40_26, phi_bb40_27, phi_bb40_28, phi_bb40_29, phi_bb40_32, phi_bb40_33, phi_bb40_35, phi_bb40_37});
  }

  TNode<IntPtrT> phi_bb38_20;
  TNode<IntPtrT> phi_bb38_25;
  TNode<IntPtrT> phi_bb38_26;
  TNode<IntPtrT> phi_bb38_27;
  TNode<IntPtrT> phi_bb38_28;
  TNode<IntPtrT> phi_bb38_29;
  TNode<IntPtrT> phi_bb38_32;
  TNode<BoolT> phi_bb38_33;
  TNode<IntPtrT> phi_bb38_35;
  TNode<BoolT> phi_bb38_37;
  TNode<BoolT> tmp113;
  TNode<BoolT> tmp114;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_20, &phi_bb38_25, &phi_bb38_26, &phi_bb38_27, &phi_bb38_28, &phi_bb38_29, &phi_bb38_32, &phi_bb38_33, &phi_bb38_35, &phi_bb38_37);
    tmp113 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb38_35}, TNode<IntPtrT>{tmp109});
    tmp114 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp113});
    ca_.Branch(tmp114, &block44, std::vector<compiler::Node*>{phi_bb38_20, phi_bb38_25, phi_bb38_26, phi_bb38_27, phi_bb38_28, phi_bb38_29, phi_bb38_32, phi_bb38_33, phi_bb38_35, phi_bb38_37}, &block45, std::vector<compiler::Node*>{phi_bb38_20, phi_bb38_25, phi_bb38_26, phi_bb38_27, phi_bb38_28, phi_bb38_29, phi_bb38_32, phi_bb38_33, phi_bb38_35, phi_bb38_37});
  }

  TNode<IntPtrT> phi_bb45_20;
  TNode<IntPtrT> phi_bb45_25;
  TNode<IntPtrT> phi_bb45_26;
  TNode<IntPtrT> phi_bb45_27;
  TNode<IntPtrT> phi_bb45_28;
  TNode<IntPtrT> phi_bb45_29;
  TNode<IntPtrT> phi_bb45_32;
  TNode<BoolT> phi_bb45_33;
  TNode<IntPtrT> phi_bb45_35;
  TNode<BoolT> phi_bb45_37;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_20, &phi_bb45_25, &phi_bb45_26, &phi_bb45_27, &phi_bb45_28, &phi_bb45_29, &phi_bb45_32, &phi_bb45_33, &phi_bb45_35, &phi_bb45_37);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/torque-internal.tq", 245});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.Empty()' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb44_20;
  TNode<IntPtrT> phi_bb44_25;
  TNode<IntPtrT> phi_bb44_26;
  TNode<IntPtrT> phi_bb44_27;
  TNode<IntPtrT> phi_bb44_28;
  TNode<IntPtrT> phi_bb44_29;
  TNode<IntPtrT> phi_bb44_32;
  TNode<BoolT> phi_bb44_33;
  TNode<IntPtrT> phi_bb44_35;
  TNode<BoolT> phi_bb44_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<IntPtrT> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<Uint32T> tmp119;
  TNode<Uint32T> tmp120;
  TNode<BoolT> tmp121;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_20, &phi_bb44_25, &phi_bb44_26, &phi_bb44_27, &phi_bb44_28, &phi_bb44_29, &phi_bb44_32, &phi_bb44_33, &phi_bb44_35, &phi_bb44_37);
    std::tie(tmp115, tmp116) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp67}, TNode<IntPtrT>{phi_bb44_35}).Flatten();
    tmp117 = FromConstexpr_intptr_constexpr_int31_0(state_, kInt32Size);
    tmp118 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb44_35}, TNode<IntPtrT>{tmp117});
    tmp119 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp115, tmp116});
    tmp120 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp121 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp119}, TNode<Uint32T>{tmp120});
    ca_.Branch(tmp121, &block47, std::vector<compiler::Node*>{phi_bb44_20, phi_bb44_25, phi_bb44_26, phi_bb44_27, phi_bb44_28, phi_bb44_29, phi_bb44_32, phi_bb44_33, phi_bb44_37}, &block48, std::vector<compiler::Node*>{phi_bb44_20, phi_bb44_25, phi_bb44_26, phi_bb44_27, phi_bb44_28, phi_bb44_29, phi_bb44_32, phi_bb44_33, phi_bb44_37});
  }

  TNode<IntPtrT> phi_bb47_20;
  TNode<IntPtrT> phi_bb47_25;
  TNode<IntPtrT> phi_bb47_26;
  TNode<IntPtrT> phi_bb47_27;
  TNode<IntPtrT> phi_bb47_28;
  TNode<IntPtrT> phi_bb47_29;
  TNode<IntPtrT> phi_bb47_32;
  TNode<BoolT> phi_bb47_33;
  TNode<BoolT> phi_bb47_37;
  TNode<IntPtrT> tmp122;
  TNode<IntPtrT> tmp123;
  TNode<IntPtrT> tmp124;
  TNode<BoolT> tmp125;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_20, &phi_bb47_25, &phi_bb47_26, &phi_bb47_27, &phi_bb47_28, &phi_bb47_29, &phi_bb47_32, &phi_bb47_33, &phi_bb47_37);
    tmp122 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp123 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb47_25}, TNode<IntPtrT>{tmp122});
    tmp124 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp125 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb47_25}, TNode<IntPtrT>{tmp124});
    ca_.Branch(tmp125, &block51, std::vector<compiler::Node*>{phi_bb47_20, phi_bb47_26, phi_bb47_27, phi_bb47_28, phi_bb47_29, phi_bb47_32, phi_bb47_33, phi_bb47_37}, &block52, std::vector<compiler::Node*>{phi_bb47_20, phi_bb47_26, phi_bb47_27, phi_bb47_28, phi_bb47_29, phi_bb47_32, phi_bb47_33, phi_bb47_37});
  }

  TNode<IntPtrT> phi_bb51_20;
  TNode<IntPtrT> phi_bb51_26;
  TNode<IntPtrT> phi_bb51_27;
  TNode<IntPtrT> phi_bb51_28;
  TNode<IntPtrT> phi_bb51_29;
  TNode<IntPtrT> phi_bb51_32;
  TNode<BoolT> phi_bb51_33;
  TNode<BoolT> phi_bb51_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp126;
  TNode<IntPtrT> tmp127;
  TNode<IntPtrT> tmp128;
  TNode<IntPtrT> tmp129;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_20, &phi_bb51_26, &phi_bb51_27, &phi_bb51_28, &phi_bb51_29, &phi_bb51_32, &phi_bb51_33, &phi_bb51_37);
    std::tie(tmp126, tmp127) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb51_27}).Flatten();
    tmp128 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp129 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb51_27}, TNode<IntPtrT>{tmp128});
    ca_.Goto(&block50, phi_bb51_20, phi_bb51_26, tmp129, phi_bb51_28, phi_bb51_29, phi_bb51_32, phi_bb51_33, phi_bb51_37, tmp126, tmp127);
  }

  TNode<IntPtrT> phi_bb52_20;
  TNode<IntPtrT> phi_bb52_26;
  TNode<IntPtrT> phi_bb52_27;
  TNode<IntPtrT> phi_bb52_28;
  TNode<IntPtrT> phi_bb52_29;
  TNode<IntPtrT> phi_bb52_32;
  TNode<BoolT> phi_bb52_33;
  TNode<BoolT> phi_bb52_37;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_20, &phi_bb52_26, &phi_bb52_27, &phi_bb52_28, &phi_bb52_29, &phi_bb52_32, &phi_bb52_33, &phi_bb52_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block54, phi_bb52_20, phi_bb52_26, phi_bb52_27, phi_bb52_28, phi_bb52_29, phi_bb52_32, phi_bb52_33, phi_bb52_37);
    } else {
      ca_.Goto(&block55, phi_bb52_20, phi_bb52_26, phi_bb52_27, phi_bb52_28, phi_bb52_29, phi_bb52_32, phi_bb52_33, phi_bb52_37);
    }
  }

  TNode<IntPtrT> phi_bb54_20;
  TNode<IntPtrT> phi_bb54_26;
  TNode<IntPtrT> phi_bb54_27;
  TNode<IntPtrT> phi_bb54_28;
  TNode<IntPtrT> phi_bb54_29;
  TNode<IntPtrT> phi_bb54_32;
  TNode<BoolT> phi_bb54_33;
  TNode<BoolT> phi_bb54_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<IntPtrT> tmp132;
  TNode<IntPtrT> tmp133;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_20, &phi_bb54_26, &phi_bb54_27, &phi_bb54_28, &phi_bb54_29, &phi_bb54_32, &phi_bb54_33, &phi_bb54_37);
    std::tie(tmp130, tmp131) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb54_29}).Flatten();
    tmp132 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp133 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb54_29}, TNode<IntPtrT>{tmp132});
    ca_.Goto(&block53, phi_bb54_20, phi_bb54_26, phi_bb54_27, phi_bb54_28, tmp133, phi_bb54_32, phi_bb54_33, phi_bb54_37, tmp130, tmp131);
  }

  TNode<IntPtrT> phi_bb55_20;
  TNode<IntPtrT> phi_bb55_26;
  TNode<IntPtrT> phi_bb55_27;
  TNode<IntPtrT> phi_bb55_28;
  TNode<IntPtrT> phi_bb55_29;
  TNode<IntPtrT> phi_bb55_32;
  TNode<BoolT> phi_bb55_33;
  TNode<BoolT> phi_bb55_37;
  TNode<IntPtrT> tmp134;
  TNode<BoolT> tmp135;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_20, &phi_bb55_26, &phi_bb55_27, &phi_bb55_28, &phi_bb55_29, &phi_bb55_32, &phi_bb55_33, &phi_bb55_37);
    tmp134 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp135 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb55_32}, TNode<IntPtrT>{tmp134});
    ca_.Branch(tmp135, &block57, std::vector<compiler::Node*>{phi_bb55_20, phi_bb55_26, phi_bb55_27, phi_bb55_28, phi_bb55_29, phi_bb55_32, phi_bb55_33, phi_bb55_37}, &block58, std::vector<compiler::Node*>{phi_bb55_20, phi_bb55_26, phi_bb55_27, phi_bb55_28, phi_bb55_29, phi_bb55_32, phi_bb55_33, phi_bb55_37});
  }

  TNode<IntPtrT> phi_bb57_20;
  TNode<IntPtrT> phi_bb57_26;
  TNode<IntPtrT> phi_bb57_27;
  TNode<IntPtrT> phi_bb57_28;
  TNode<IntPtrT> phi_bb57_29;
  TNode<IntPtrT> phi_bb57_32;
  TNode<BoolT> phi_bb57_33;
  TNode<BoolT> phi_bb57_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp136;
  TNode<IntPtrT> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<BoolT> tmp139;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_20, &phi_bb57_26, &phi_bb57_27, &phi_bb57_28, &phi_bb57_29, &phi_bb57_32, &phi_bb57_33, &phi_bb57_37);
    std::tie(tmp136, tmp137) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb57_32}).Flatten();
    tmp138 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp139 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block53, phi_bb57_20, phi_bb57_26, phi_bb57_27, phi_bb57_28, phi_bb57_29, tmp138, tmp139, phi_bb57_37, tmp136, tmp137);
  }

  TNode<IntPtrT> phi_bb58_20;
  TNode<IntPtrT> phi_bb58_26;
  TNode<IntPtrT> phi_bb58_27;
  TNode<IntPtrT> phi_bb58_28;
  TNode<IntPtrT> phi_bb58_29;
  TNode<IntPtrT> phi_bb58_32;
  TNode<BoolT> phi_bb58_33;
  TNode<BoolT> phi_bb58_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp140;
  TNode<IntPtrT> tmp141;
  TNode<IntPtrT> tmp142;
  TNode<IntPtrT> tmp143;
  TNode<IntPtrT> tmp144;
  TNode<IntPtrT> tmp145;
  TNode<BoolT> tmp146;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_20, &phi_bb58_26, &phi_bb58_27, &phi_bb58_28, &phi_bb58_29, &phi_bb58_32, &phi_bb58_33, &phi_bb58_37);
    std::tie(tmp140, tmp141) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb58_29}).Flatten();
    tmp142 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp143 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb58_29}, TNode<IntPtrT>{tmp142});
    tmp144 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp145 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp143}, TNode<IntPtrT>{tmp144});
    tmp146 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block53, phi_bb58_20, phi_bb58_26, phi_bb58_27, phi_bb58_28, tmp145, tmp143, tmp146, phi_bb58_37, tmp140, tmp141);
  }

  TNode<IntPtrT> phi_bb53_20;
  TNode<IntPtrT> phi_bb53_26;
  TNode<IntPtrT> phi_bb53_27;
  TNode<IntPtrT> phi_bb53_28;
  TNode<IntPtrT> phi_bb53_29;
  TNode<IntPtrT> phi_bb53_32;
  TNode<BoolT> phi_bb53_33;
  TNode<BoolT> phi_bb53_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb53_39;
  TNode<IntPtrT> phi_bb53_40;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_20, &phi_bb53_26, &phi_bb53_27, &phi_bb53_28, &phi_bb53_29, &phi_bb53_32, &phi_bb53_33, &phi_bb53_37, &phi_bb53_39, &phi_bb53_40);
    ca_.Goto(&block50, phi_bb53_20, phi_bb53_26, phi_bb53_27, phi_bb53_28, phi_bb53_29, phi_bb53_32, phi_bb53_33, phi_bb53_37, phi_bb53_39, phi_bb53_40);
  }

  TNode<IntPtrT> phi_bb50_20;
  TNode<IntPtrT> phi_bb50_26;
  TNode<IntPtrT> phi_bb50_27;
  TNode<IntPtrT> phi_bb50_28;
  TNode<IntPtrT> phi_bb50_29;
  TNode<IntPtrT> phi_bb50_32;
  TNode<BoolT> phi_bb50_33;
  TNode<BoolT> phi_bb50_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb50_39;
  TNode<IntPtrT> phi_bb50_40;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_20, &phi_bb50_26, &phi_bb50_27, &phi_bb50_28, &phi_bb50_29, &phi_bb50_32, &phi_bb50_33, &phi_bb50_37, &phi_bb50_39, &phi_bb50_40);
    if ((wasm::kIsBigEndian)) {
      ca_.Goto(&block59, phi_bb50_20, phi_bb50_26, phi_bb50_27, phi_bb50_28, phi_bb50_29, phi_bb50_32, phi_bb50_33, phi_bb50_37, phi_bb50_39, phi_bb50_40);
    } else {
      ca_.Goto(&block60, phi_bb50_20, phi_bb50_26, phi_bb50_27, phi_bb50_28, phi_bb50_29, phi_bb50_32, phi_bb50_33, phi_bb50_37, phi_bb50_39, phi_bb50_40);
    }
  }

  TNode<IntPtrT> phi_bb59_20;
  TNode<IntPtrT> phi_bb59_26;
  TNode<IntPtrT> phi_bb59_27;
  TNode<IntPtrT> phi_bb59_28;
  TNode<IntPtrT> phi_bb59_29;
  TNode<IntPtrT> phi_bb59_32;
  TNode<BoolT> phi_bb59_33;
  TNode<BoolT> phi_bb59_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb59_39;
  TNode<IntPtrT> phi_bb59_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp147;
  TNode<IntPtrT> tmp148;
  TNode<Int64T> tmp149;
  TNode<Int32T> tmp150;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_20, &phi_bb59_26, &phi_bb59_27, &phi_bb59_28, &phi_bb59_29, &phi_bb59_32, &phi_bb59_33, &phi_bb59_37, &phi_bb59_39, &phi_bb59_40);
    std::tie(tmp147, tmp148) = RefCast_int64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb59_39}, TNode<IntPtrT>{phi_bb59_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp149 = CodeStubAssembler(state_).LoadReference<Int64T>(CodeStubAssembler::Reference{tmp147, tmp148});
    tmp150 = CodeStubAssembler(state_).TruncateInt64ToInt32(TNode<Int64T>{tmp149});
    ca_.Goto(&block61, phi_bb59_20, phi_bb59_26, phi_bb59_27, phi_bb59_28, phi_bb59_29, phi_bb59_32, phi_bb59_33, phi_bb59_37, phi_bb59_39, phi_bb59_40, tmp150);
  }

  TNode<IntPtrT> phi_bb60_20;
  TNode<IntPtrT> phi_bb60_26;
  TNode<IntPtrT> phi_bb60_27;
  TNode<IntPtrT> phi_bb60_28;
  TNode<IntPtrT> phi_bb60_29;
  TNode<IntPtrT> phi_bb60_32;
  TNode<BoolT> phi_bb60_33;
  TNode<BoolT> phi_bb60_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb60_39;
  TNode<IntPtrT> phi_bb60_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp151;
  TNode<IntPtrT> tmp152;
  TNode<Int32T> tmp153;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_20, &phi_bb60_26, &phi_bb60_27, &phi_bb60_28, &phi_bb60_29, &phi_bb60_32, &phi_bb60_33, &phi_bb60_37, &phi_bb60_39, &phi_bb60_40);
    std::tie(tmp151, tmp152) = RefCast_int32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb60_39}, TNode<IntPtrT>{phi_bb60_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp153 = CodeStubAssembler(state_).LoadReference<Int32T>(CodeStubAssembler::Reference{tmp151, tmp152});
    ca_.Goto(&block61, phi_bb60_20, phi_bb60_26, phi_bb60_27, phi_bb60_28, phi_bb60_29, phi_bb60_32, phi_bb60_33, phi_bb60_37, phi_bb60_39, phi_bb60_40, tmp153);
  }

  TNode<IntPtrT> phi_bb61_20;
  TNode<IntPtrT> phi_bb61_26;
  TNode<IntPtrT> phi_bb61_27;
  TNode<IntPtrT> phi_bb61_28;
  TNode<IntPtrT> phi_bb61_29;
  TNode<IntPtrT> phi_bb61_32;
  TNode<BoolT> phi_bb61_33;
  TNode<BoolT> phi_bb61_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb61_39;
  TNode<IntPtrT> phi_bb61_40;
  TNode<Int32T> phi_bb61_41;
  TNode<Union<HeapObject, TaggedIndex>> tmp154;
  TNode<IntPtrT> tmp155;
  TNode<IntPtrT> tmp156;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<UintPtrT> tmp159;
  TNode<UintPtrT> tmp160;
  TNode<BoolT> tmp161;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_20, &phi_bb61_26, &phi_bb61_27, &phi_bb61_28, &phi_bb61_29, &phi_bb61_32, &phi_bb61_33, &phi_bb61_37, &phi_bb61_39, &phi_bb61_40, &phi_bb61_41);
    std::tie(tmp154, tmp155, tmp156) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp157 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp158 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb61_20}, TNode<IntPtrT>{tmp157});
    tmp159 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb61_20});
    tmp160 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp156});
    tmp161 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp159}, TNode<UintPtrT>{tmp160});
    ca_.Branch(tmp161, &block66, std::vector<compiler::Node*>{phi_bb61_26, phi_bb61_27, phi_bb61_28, phi_bb61_29, phi_bb61_32, phi_bb61_33, phi_bb61_37, phi_bb61_39, phi_bb61_40, phi_bb61_20, phi_bb61_20, phi_bb61_20, phi_bb61_20}, &block67, std::vector<compiler::Node*>{phi_bb61_26, phi_bb61_27, phi_bb61_28, phi_bb61_29, phi_bb61_32, phi_bb61_33, phi_bb61_37, phi_bb61_39, phi_bb61_40, phi_bb61_20, phi_bb61_20, phi_bb61_20, phi_bb61_20});
  }

  TNode<IntPtrT> phi_bb66_26;
  TNode<IntPtrT> phi_bb66_27;
  TNode<IntPtrT> phi_bb66_28;
  TNode<IntPtrT> phi_bb66_29;
  TNode<IntPtrT> phi_bb66_32;
  TNode<BoolT> phi_bb66_33;
  TNode<BoolT> phi_bb66_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb66_39;
  TNode<IntPtrT> phi_bb66_40;
  TNode<IntPtrT> phi_bb66_46;
  TNode<IntPtrT> phi_bb66_47;
  TNode<IntPtrT> phi_bb66_51;
  TNode<IntPtrT> phi_bb66_52;
  TNode<IntPtrT> tmp162;
  TNode<IntPtrT> tmp163;
  TNode<Union<HeapObject, TaggedIndex>> tmp164;
  TNode<IntPtrT> tmp165;
  TNode<Number> tmp166;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_26, &phi_bb66_27, &phi_bb66_28, &phi_bb66_29, &phi_bb66_32, &phi_bb66_33, &phi_bb66_37, &phi_bb66_39, &phi_bb66_40, &phi_bb66_46, &phi_bb66_47, &phi_bb66_51, &phi_bb66_52);
    tmp162 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb66_52});
    tmp163 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp155}, TNode<IntPtrT>{tmp162});
    std::tie(tmp164, tmp165) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp154}, TNode<IntPtrT>{tmp163}).Flatten();
    tmp166 = Convert_Number_int32_0(state_, TNode<Int32T>{phi_bb61_41});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp164, tmp165}, tmp166);
    ca_.Goto(&block49, tmp158, tmp123, phi_bb66_26, phi_bb66_27, phi_bb66_28, phi_bb66_29, phi_bb66_32, phi_bb66_33, phi_bb66_37);
  }

  TNode<IntPtrT> phi_bb67_26;
  TNode<IntPtrT> phi_bb67_27;
  TNode<IntPtrT> phi_bb67_28;
  TNode<IntPtrT> phi_bb67_29;
  TNode<IntPtrT> phi_bb67_32;
  TNode<BoolT> phi_bb67_33;
  TNode<BoolT> phi_bb67_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb67_39;
  TNode<IntPtrT> phi_bb67_40;
  TNode<IntPtrT> phi_bb67_46;
  TNode<IntPtrT> phi_bb67_47;
  TNode<IntPtrT> phi_bb67_51;
  TNode<IntPtrT> phi_bb67_52;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_26, &phi_bb67_27, &phi_bb67_28, &phi_bb67_29, &phi_bb67_32, &phi_bb67_33, &phi_bb67_37, &phi_bb67_39, &phi_bb67_40, &phi_bb67_46, &phi_bb67_47, &phi_bb67_51, &phi_bb67_52);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb48_20;
  TNode<IntPtrT> phi_bb48_25;
  TNode<IntPtrT> phi_bb48_26;
  TNode<IntPtrT> phi_bb48_27;
  TNode<IntPtrT> phi_bb48_28;
  TNode<IntPtrT> phi_bb48_29;
  TNode<IntPtrT> phi_bb48_32;
  TNode<BoolT> phi_bb48_33;
  TNode<BoolT> phi_bb48_37;
  TNode<Uint32T> tmp167;
  TNode<BoolT> tmp168;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_20, &phi_bb48_25, &phi_bb48_26, &phi_bb48_27, &phi_bb48_28, &phi_bb48_29, &phi_bb48_32, &phi_bb48_33, &phi_bb48_37);
    tmp167 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp168 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp119}, TNode<Uint32T>{tmp167});
    ca_.Branch(tmp168, &block70, std::vector<compiler::Node*>{phi_bb48_20, phi_bb48_25, phi_bb48_26, phi_bb48_27, phi_bb48_28, phi_bb48_29, phi_bb48_32, phi_bb48_33, phi_bb48_37}, &block71, std::vector<compiler::Node*>{phi_bb48_20, phi_bb48_25, phi_bb48_26, phi_bb48_27, phi_bb48_28, phi_bb48_29, phi_bb48_32, phi_bb48_33, phi_bb48_37});
  }

  TNode<IntPtrT> phi_bb70_20;
  TNode<IntPtrT> phi_bb70_25;
  TNode<IntPtrT> phi_bb70_26;
  TNode<IntPtrT> phi_bb70_27;
  TNode<IntPtrT> phi_bb70_28;
  TNode<IntPtrT> phi_bb70_29;
  TNode<IntPtrT> phi_bb70_32;
  TNode<BoolT> phi_bb70_33;
  TNode<BoolT> phi_bb70_37;
  TNode<IntPtrT> tmp169;
  TNode<IntPtrT> tmp170;
  TNode<IntPtrT> tmp171;
  TNode<BoolT> tmp172;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_20, &phi_bb70_25, &phi_bb70_26, &phi_bb70_27, &phi_bb70_28, &phi_bb70_29, &phi_bb70_32, &phi_bb70_33, &phi_bb70_37);
    tmp169 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp170 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb70_26}, TNode<IntPtrT>{tmp169});
    tmp171 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp172 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb70_26}, TNode<IntPtrT>{tmp171});
    ca_.Branch(tmp172, &block74, std::vector<compiler::Node*>{phi_bb70_20, phi_bb70_25, phi_bb70_27, phi_bb70_28, phi_bb70_29, phi_bb70_32, phi_bb70_33, phi_bb70_37}, &block75, std::vector<compiler::Node*>{phi_bb70_20, phi_bb70_25, phi_bb70_27, phi_bb70_28, phi_bb70_29, phi_bb70_32, phi_bb70_33, phi_bb70_37});
  }

  TNode<IntPtrT> phi_bb74_20;
  TNode<IntPtrT> phi_bb74_25;
  TNode<IntPtrT> phi_bb74_27;
  TNode<IntPtrT> phi_bb74_28;
  TNode<IntPtrT> phi_bb74_29;
  TNode<IntPtrT> phi_bb74_32;
  TNode<BoolT> phi_bb74_33;
  TNode<BoolT> phi_bb74_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp173;
  TNode<IntPtrT> tmp174;
  TNode<IntPtrT> tmp175;
  TNode<IntPtrT> tmp176;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_20, &phi_bb74_25, &phi_bb74_27, &phi_bb74_28, &phi_bb74_29, &phi_bb74_32, &phi_bb74_33, &phi_bb74_37);
    std::tie(tmp173, tmp174) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb74_28}).Flatten();
    tmp175 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp176 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb74_28}, TNode<IntPtrT>{tmp175});
    ca_.Goto(&block73, phi_bb74_20, phi_bb74_25, phi_bb74_27, tmp176, phi_bb74_29, phi_bb74_32, phi_bb74_33, phi_bb74_37, tmp173, tmp174);
  }

  TNode<IntPtrT> phi_bb75_20;
  TNode<IntPtrT> phi_bb75_25;
  TNode<IntPtrT> phi_bb75_27;
  TNode<IntPtrT> phi_bb75_28;
  TNode<IntPtrT> phi_bb75_29;
  TNode<IntPtrT> phi_bb75_32;
  TNode<BoolT> phi_bb75_33;
  TNode<BoolT> phi_bb75_37;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_20, &phi_bb75_25, &phi_bb75_27, &phi_bb75_28, &phi_bb75_29, &phi_bb75_32, &phi_bb75_33, &phi_bb75_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block77, phi_bb75_20, phi_bb75_25, phi_bb75_27, phi_bb75_28, phi_bb75_29, phi_bb75_32, phi_bb75_33, phi_bb75_37);
    } else {
      ca_.Goto(&block78, phi_bb75_20, phi_bb75_25, phi_bb75_27, phi_bb75_28, phi_bb75_29, phi_bb75_32, phi_bb75_33, phi_bb75_37);
    }
  }

  TNode<IntPtrT> phi_bb77_20;
  TNode<IntPtrT> phi_bb77_25;
  TNode<IntPtrT> phi_bb77_27;
  TNode<IntPtrT> phi_bb77_28;
  TNode<IntPtrT> phi_bb77_29;
  TNode<IntPtrT> phi_bb77_32;
  TNode<BoolT> phi_bb77_33;
  TNode<BoolT> phi_bb77_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp177;
  TNode<IntPtrT> tmp178;
  TNode<IntPtrT> tmp179;
  TNode<IntPtrT> tmp180;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_20, &phi_bb77_25, &phi_bb77_27, &phi_bb77_28, &phi_bb77_29, &phi_bb77_32, &phi_bb77_33, &phi_bb77_37);
    std::tie(tmp177, tmp178) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb77_29}).Flatten();
    tmp179 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp180 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb77_29}, TNode<IntPtrT>{tmp179});
    ca_.Goto(&block76, phi_bb77_20, phi_bb77_25, phi_bb77_27, phi_bb77_28, tmp180, phi_bb77_32, phi_bb77_33, phi_bb77_37, tmp177, tmp178);
  }

  TNode<IntPtrT> phi_bb78_20;
  TNode<IntPtrT> phi_bb78_25;
  TNode<IntPtrT> phi_bb78_27;
  TNode<IntPtrT> phi_bb78_28;
  TNode<IntPtrT> phi_bb78_29;
  TNode<IntPtrT> phi_bb78_32;
  TNode<BoolT> phi_bb78_33;
  TNode<BoolT> phi_bb78_37;
  TNode<IntPtrT> tmp181;
  TNode<BoolT> tmp182;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_20, &phi_bb78_25, &phi_bb78_27, &phi_bb78_28, &phi_bb78_29, &phi_bb78_32, &phi_bb78_33, &phi_bb78_37);
    tmp181 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp182 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb78_32}, TNode<IntPtrT>{tmp181});
    ca_.Branch(tmp182, &block80, std::vector<compiler::Node*>{phi_bb78_20, phi_bb78_25, phi_bb78_27, phi_bb78_28, phi_bb78_29, phi_bb78_32, phi_bb78_33, phi_bb78_37}, &block81, std::vector<compiler::Node*>{phi_bb78_20, phi_bb78_25, phi_bb78_27, phi_bb78_28, phi_bb78_29, phi_bb78_32, phi_bb78_33, phi_bb78_37});
  }

  TNode<IntPtrT> phi_bb80_20;
  TNode<IntPtrT> phi_bb80_25;
  TNode<IntPtrT> phi_bb80_27;
  TNode<IntPtrT> phi_bb80_28;
  TNode<IntPtrT> phi_bb80_29;
  TNode<IntPtrT> phi_bb80_32;
  TNode<BoolT> phi_bb80_33;
  TNode<BoolT> phi_bb80_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp183;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<BoolT> tmp186;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_20, &phi_bb80_25, &phi_bb80_27, &phi_bb80_28, &phi_bb80_29, &phi_bb80_32, &phi_bb80_33, &phi_bb80_37);
    std::tie(tmp183, tmp184) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb80_32}).Flatten();
    tmp185 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp186 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block76, phi_bb80_20, phi_bb80_25, phi_bb80_27, phi_bb80_28, phi_bb80_29, tmp185, tmp186, phi_bb80_37, tmp183, tmp184);
  }

  TNode<IntPtrT> phi_bb81_20;
  TNode<IntPtrT> phi_bb81_25;
  TNode<IntPtrT> phi_bb81_27;
  TNode<IntPtrT> phi_bb81_28;
  TNode<IntPtrT> phi_bb81_29;
  TNode<IntPtrT> phi_bb81_32;
  TNode<BoolT> phi_bb81_33;
  TNode<BoolT> phi_bb81_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp187;
  TNode<IntPtrT> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<IntPtrT> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<IntPtrT> tmp192;
  TNode<BoolT> tmp193;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_20, &phi_bb81_25, &phi_bb81_27, &phi_bb81_28, &phi_bb81_29, &phi_bb81_32, &phi_bb81_33, &phi_bb81_37);
    std::tie(tmp187, tmp188) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb81_29}).Flatten();
    tmp189 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp190 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb81_29}, TNode<IntPtrT>{tmp189});
    tmp191 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp192 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp190}, TNode<IntPtrT>{tmp191});
    tmp193 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block76, phi_bb81_20, phi_bb81_25, phi_bb81_27, phi_bb81_28, tmp192, tmp190, tmp193, phi_bb81_37, tmp187, tmp188);
  }

  TNode<IntPtrT> phi_bb76_20;
  TNode<IntPtrT> phi_bb76_25;
  TNode<IntPtrT> phi_bb76_27;
  TNode<IntPtrT> phi_bb76_28;
  TNode<IntPtrT> phi_bb76_29;
  TNode<IntPtrT> phi_bb76_32;
  TNode<BoolT> phi_bb76_33;
  TNode<BoolT> phi_bb76_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb76_39;
  TNode<IntPtrT> phi_bb76_40;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_20, &phi_bb76_25, &phi_bb76_27, &phi_bb76_28, &phi_bb76_29, &phi_bb76_32, &phi_bb76_33, &phi_bb76_37, &phi_bb76_39, &phi_bb76_40);
    ca_.Goto(&block73, phi_bb76_20, phi_bb76_25, phi_bb76_27, phi_bb76_28, phi_bb76_29, phi_bb76_32, phi_bb76_33, phi_bb76_37, phi_bb76_39, phi_bb76_40);
  }

  TNode<IntPtrT> phi_bb73_20;
  TNode<IntPtrT> phi_bb73_25;
  TNode<IntPtrT> phi_bb73_27;
  TNode<IntPtrT> phi_bb73_28;
  TNode<IntPtrT> phi_bb73_29;
  TNode<IntPtrT> phi_bb73_32;
  TNode<BoolT> phi_bb73_33;
  TNode<BoolT> phi_bb73_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb73_39;
  TNode<IntPtrT> phi_bb73_40;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_20, &phi_bb73_25, &phi_bb73_27, &phi_bb73_28, &phi_bb73_29, &phi_bb73_32, &phi_bb73_33, &phi_bb73_37, &phi_bb73_39, &phi_bb73_40);
    if ((wasm::kIsFpAlwaysDouble)) {
      ca_.Goto(&block82, phi_bb73_20, phi_bb73_25, phi_bb73_27, phi_bb73_28, phi_bb73_29, phi_bb73_32, phi_bb73_33, phi_bb73_37, phi_bb73_39, phi_bb73_40);
    } else {
      ca_.Goto(&block83, phi_bb73_20, phi_bb73_25, phi_bb73_27, phi_bb73_28, phi_bb73_29, phi_bb73_32, phi_bb73_33, phi_bb73_37, phi_bb73_39, phi_bb73_40);
    }
  }

  TNode<IntPtrT> phi_bb82_20;
  TNode<IntPtrT> phi_bb82_25;
  TNode<IntPtrT> phi_bb82_27;
  TNode<IntPtrT> phi_bb82_28;
  TNode<IntPtrT> phi_bb82_29;
  TNode<IntPtrT> phi_bb82_32;
  TNode<BoolT> phi_bb82_33;
  TNode<BoolT> phi_bb82_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb82_39;
  TNode<IntPtrT> phi_bb82_40;
  TNode<IntPtrT> tmp194;
  TNode<BoolT> tmp195;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_20, &phi_bb82_25, &phi_bb82_27, &phi_bb82_28, &phi_bb82_29, &phi_bb82_32, &phi_bb82_33, &phi_bb82_37, &phi_bb82_39, &phi_bb82_40);
    tmp194 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp195 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp170}, TNode<IntPtrT>{tmp194});
    ca_.Branch(tmp195, &block85, std::vector<compiler::Node*>{phi_bb82_20, phi_bb82_25, phi_bb82_27, phi_bb82_28, phi_bb82_29, phi_bb82_32, phi_bb82_33, phi_bb82_37, phi_bb82_39, phi_bb82_40}, &block86, std::vector<compiler::Node*>{phi_bb82_20, phi_bb82_25, phi_bb82_27, phi_bb82_28, phi_bb82_29, phi_bb82_32, phi_bb82_33, phi_bb82_37, phi_bb82_39, phi_bb82_40});
  }

  TNode<IntPtrT> phi_bb85_20;
  TNode<IntPtrT> phi_bb85_25;
  TNode<IntPtrT> phi_bb85_27;
  TNode<IntPtrT> phi_bb85_28;
  TNode<IntPtrT> phi_bb85_29;
  TNode<IntPtrT> phi_bb85_32;
  TNode<BoolT> phi_bb85_33;
  TNode<BoolT> phi_bb85_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb85_39;
  TNode<IntPtrT> phi_bb85_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp196;
  TNode<IntPtrT> tmp197;
  TNode<Float64T> tmp198;
  TNode<Float32T> tmp199;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_20, &phi_bb85_25, &phi_bb85_27, &phi_bb85_28, &phi_bb85_29, &phi_bb85_32, &phi_bb85_33, &phi_bb85_37, &phi_bb85_39, &phi_bb85_40);
    std::tie(tmp196, tmp197) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb85_39}, TNode<IntPtrT>{phi_bb85_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp198 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp196, tmp197});
    tmp199 = CodeStubAssembler(state_).TruncateFloat64ToFloat32(TNode<Float64T>{tmp198});
    ca_.Goto(&block88, phi_bb85_20, phi_bb85_25, phi_bb85_27, phi_bb85_28, phi_bb85_29, phi_bb85_32, phi_bb85_33, phi_bb85_37, phi_bb85_39, phi_bb85_40, tmp199);
  }

  TNode<IntPtrT> phi_bb86_20;
  TNode<IntPtrT> phi_bb86_25;
  TNode<IntPtrT> phi_bb86_27;
  TNode<IntPtrT> phi_bb86_28;
  TNode<IntPtrT> phi_bb86_29;
  TNode<IntPtrT> phi_bb86_32;
  TNode<BoolT> phi_bb86_33;
  TNode<BoolT> phi_bb86_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb86_39;
  TNode<IntPtrT> phi_bb86_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp200;
  TNode<IntPtrT> tmp201;
  TNode<Float32T> tmp202;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_20, &phi_bb86_25, &phi_bb86_27, &phi_bb86_28, &phi_bb86_29, &phi_bb86_32, &phi_bb86_33, &phi_bb86_37, &phi_bb86_39, &phi_bb86_40);
    std::tie(tmp200, tmp201) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb86_39}, TNode<IntPtrT>{phi_bb86_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp202 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp200, tmp201});
    ca_.Goto(&block88, phi_bb86_20, phi_bb86_25, phi_bb86_27, phi_bb86_28, phi_bb86_29, phi_bb86_32, phi_bb86_33, phi_bb86_37, phi_bb86_39, phi_bb86_40, tmp202);
  }

  TNode<IntPtrT> phi_bb88_20;
  TNode<IntPtrT> phi_bb88_25;
  TNode<IntPtrT> phi_bb88_27;
  TNode<IntPtrT> phi_bb88_28;
  TNode<IntPtrT> phi_bb88_29;
  TNode<IntPtrT> phi_bb88_32;
  TNode<BoolT> phi_bb88_33;
  TNode<BoolT> phi_bb88_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb88_39;
  TNode<IntPtrT> phi_bb88_40;
  TNode<Float32T> phi_bb88_41;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_20, &phi_bb88_25, &phi_bb88_27, &phi_bb88_28, &phi_bb88_29, &phi_bb88_32, &phi_bb88_33, &phi_bb88_37, &phi_bb88_39, &phi_bb88_40, &phi_bb88_41);
    ca_.Goto(&block84, phi_bb88_20, phi_bb88_25, phi_bb88_27, phi_bb88_28, phi_bb88_29, phi_bb88_32, phi_bb88_33, phi_bb88_37, phi_bb88_39, phi_bb88_40, phi_bb88_41);
  }

  TNode<IntPtrT> phi_bb83_20;
  TNode<IntPtrT> phi_bb83_25;
  TNode<IntPtrT> phi_bb83_27;
  TNode<IntPtrT> phi_bb83_28;
  TNode<IntPtrT> phi_bb83_29;
  TNode<IntPtrT> phi_bb83_32;
  TNode<BoolT> phi_bb83_33;
  TNode<BoolT> phi_bb83_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb83_39;
  TNode<IntPtrT> phi_bb83_40;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_20, &phi_bb83_25, &phi_bb83_27, &phi_bb83_28, &phi_bb83_29, &phi_bb83_32, &phi_bb83_33, &phi_bb83_37, &phi_bb83_39, &phi_bb83_40);
    if ((wasm::kIsBigEndianOnSim)) {
      ca_.Goto(&block89, phi_bb83_20, phi_bb83_25, phi_bb83_27, phi_bb83_28, phi_bb83_29, phi_bb83_32, phi_bb83_33, phi_bb83_37, phi_bb83_39, phi_bb83_40);
    } else {
      ca_.Goto(&block90, phi_bb83_20, phi_bb83_25, phi_bb83_27, phi_bb83_28, phi_bb83_29, phi_bb83_32, phi_bb83_33, phi_bb83_37, phi_bb83_39, phi_bb83_40);
    }
  }

  TNode<IntPtrT> phi_bb89_20;
  TNode<IntPtrT> phi_bb89_25;
  TNode<IntPtrT> phi_bb89_27;
  TNode<IntPtrT> phi_bb89_28;
  TNode<IntPtrT> phi_bb89_29;
  TNode<IntPtrT> phi_bb89_32;
  TNode<BoolT> phi_bb89_33;
  TNode<BoolT> phi_bb89_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb89_39;
  TNode<IntPtrT> phi_bb89_40;
  TNode<IntPtrT> tmp203;
  TNode<BoolT> tmp204;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_20, &phi_bb89_25, &phi_bb89_27, &phi_bb89_28, &phi_bb89_29, &phi_bb89_32, &phi_bb89_33, &phi_bb89_37, &phi_bb89_39, &phi_bb89_40);
    tmp203 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp204 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp170}, TNode<IntPtrT>{tmp203});
    ca_.Branch(tmp204, &block92, std::vector<compiler::Node*>{phi_bb89_20, phi_bb89_25, phi_bb89_27, phi_bb89_28, phi_bb89_29, phi_bb89_32, phi_bb89_33, phi_bb89_37, phi_bb89_39, phi_bb89_40}, &block93, std::vector<compiler::Node*>{phi_bb89_20, phi_bb89_25, phi_bb89_27, phi_bb89_28, phi_bb89_29, phi_bb89_32, phi_bb89_33, phi_bb89_37, phi_bb89_39, phi_bb89_40});
  }

  TNode<IntPtrT> phi_bb92_20;
  TNode<IntPtrT> phi_bb92_25;
  TNode<IntPtrT> phi_bb92_27;
  TNode<IntPtrT> phi_bb92_28;
  TNode<IntPtrT> phi_bb92_29;
  TNode<IntPtrT> phi_bb92_32;
  TNode<BoolT> phi_bb92_33;
  TNode<BoolT> phi_bb92_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb92_39;
  TNode<IntPtrT> phi_bb92_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp205;
  TNode<IntPtrT> tmp206;
  TNode<Int64T> tmp207;
  TNode<Int64T> tmp208;
  TNode<Int64T> tmp209;
  TNode<Int32T> tmp210;
  TNode<Float32T> tmp211;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_20, &phi_bb92_25, &phi_bb92_27, &phi_bb92_28, &phi_bb92_29, &phi_bb92_32, &phi_bb92_33, &phi_bb92_37, &phi_bb92_39, &phi_bb92_40);
    std::tie(tmp205, tmp206) = RefCast_int64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb92_39}, TNode<IntPtrT>{phi_bb92_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp207 = CodeStubAssembler(state_).LoadReference<Int64T>(CodeStubAssembler::Reference{tmp205, tmp206});
    tmp208 = FromConstexpr_int64_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp209 = CodeStubAssembler(state_).Word64Sar(TNode<Int64T>{tmp207}, TNode<Int64T>{tmp208});
    tmp210 = CodeStubAssembler(state_).TruncateInt64ToInt32(TNode<Int64T>{tmp209});
    tmp211 = CodeStubAssembler(state_).BitcastInt32ToFloat32(TNode<Int32T>{tmp210});
    ca_.Goto(&block95, phi_bb92_20, phi_bb92_25, phi_bb92_27, phi_bb92_28, phi_bb92_29, phi_bb92_32, phi_bb92_33, phi_bb92_37, phi_bb92_39, phi_bb92_40, tmp211);
  }

  TNode<IntPtrT> phi_bb93_20;
  TNode<IntPtrT> phi_bb93_25;
  TNode<IntPtrT> phi_bb93_27;
  TNode<IntPtrT> phi_bb93_28;
  TNode<IntPtrT> phi_bb93_29;
  TNode<IntPtrT> phi_bb93_32;
  TNode<BoolT> phi_bb93_33;
  TNode<BoolT> phi_bb93_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb93_39;
  TNode<IntPtrT> phi_bb93_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp212;
  TNode<IntPtrT> tmp213;
  TNode<Float32T> tmp214;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_20, &phi_bb93_25, &phi_bb93_27, &phi_bb93_28, &phi_bb93_29, &phi_bb93_32, &phi_bb93_33, &phi_bb93_37, &phi_bb93_39, &phi_bb93_40);
    std::tie(tmp212, tmp213) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb93_39}, TNode<IntPtrT>{phi_bb93_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp214 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp212, tmp213});
    ca_.Goto(&block95, phi_bb93_20, phi_bb93_25, phi_bb93_27, phi_bb93_28, phi_bb93_29, phi_bb93_32, phi_bb93_33, phi_bb93_37, phi_bb93_39, phi_bb93_40, tmp214);
  }

  TNode<IntPtrT> phi_bb95_20;
  TNode<IntPtrT> phi_bb95_25;
  TNode<IntPtrT> phi_bb95_27;
  TNode<IntPtrT> phi_bb95_28;
  TNode<IntPtrT> phi_bb95_29;
  TNode<IntPtrT> phi_bb95_32;
  TNode<BoolT> phi_bb95_33;
  TNode<BoolT> phi_bb95_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb95_39;
  TNode<IntPtrT> phi_bb95_40;
  TNode<Float32T> phi_bb95_41;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_20, &phi_bb95_25, &phi_bb95_27, &phi_bb95_28, &phi_bb95_29, &phi_bb95_32, &phi_bb95_33, &phi_bb95_37, &phi_bb95_39, &phi_bb95_40, &phi_bb95_41);
    ca_.Goto(&block91, phi_bb95_20, phi_bb95_25, phi_bb95_27, phi_bb95_28, phi_bb95_29, phi_bb95_32, phi_bb95_33, phi_bb95_37, phi_bb95_39, phi_bb95_40, phi_bb95_41);
  }

  TNode<IntPtrT> phi_bb90_20;
  TNode<IntPtrT> phi_bb90_25;
  TNode<IntPtrT> phi_bb90_27;
  TNode<IntPtrT> phi_bb90_28;
  TNode<IntPtrT> phi_bb90_29;
  TNode<IntPtrT> phi_bb90_32;
  TNode<BoolT> phi_bb90_33;
  TNode<BoolT> phi_bb90_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb90_39;
  TNode<IntPtrT> phi_bb90_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp215;
  TNode<IntPtrT> tmp216;
  TNode<Float32T> tmp217;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_20, &phi_bb90_25, &phi_bb90_27, &phi_bb90_28, &phi_bb90_29, &phi_bb90_32, &phi_bb90_33, &phi_bb90_37, &phi_bb90_39, &phi_bb90_40);
    std::tie(tmp215, tmp216) = RefCast_float32_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb90_39}, TNode<IntPtrT>{phi_bb90_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp217 = CodeStubAssembler(state_).LoadReference<Float32T>(CodeStubAssembler::Reference{tmp215, tmp216});
    ca_.Goto(&block91, phi_bb90_20, phi_bb90_25, phi_bb90_27, phi_bb90_28, phi_bb90_29, phi_bb90_32, phi_bb90_33, phi_bb90_37, phi_bb90_39, phi_bb90_40, tmp217);
  }

  TNode<IntPtrT> phi_bb91_20;
  TNode<IntPtrT> phi_bb91_25;
  TNode<IntPtrT> phi_bb91_27;
  TNode<IntPtrT> phi_bb91_28;
  TNode<IntPtrT> phi_bb91_29;
  TNode<IntPtrT> phi_bb91_32;
  TNode<BoolT> phi_bb91_33;
  TNode<BoolT> phi_bb91_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb91_39;
  TNode<IntPtrT> phi_bb91_40;
  TNode<Float32T> phi_bb91_41;
  if (block91.is_used()) {
    ca_.Bind(&block91, &phi_bb91_20, &phi_bb91_25, &phi_bb91_27, &phi_bb91_28, &phi_bb91_29, &phi_bb91_32, &phi_bb91_33, &phi_bb91_37, &phi_bb91_39, &phi_bb91_40, &phi_bb91_41);
    ca_.Goto(&block84, phi_bb91_20, phi_bb91_25, phi_bb91_27, phi_bb91_28, phi_bb91_29, phi_bb91_32, phi_bb91_33, phi_bb91_37, phi_bb91_39, phi_bb91_40, phi_bb91_41);
  }

  TNode<IntPtrT> phi_bb84_20;
  TNode<IntPtrT> phi_bb84_25;
  TNode<IntPtrT> phi_bb84_27;
  TNode<IntPtrT> phi_bb84_28;
  TNode<IntPtrT> phi_bb84_29;
  TNode<IntPtrT> phi_bb84_32;
  TNode<BoolT> phi_bb84_33;
  TNode<BoolT> phi_bb84_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb84_39;
  TNode<IntPtrT> phi_bb84_40;
  TNode<Float32T> phi_bb84_41;
  TNode<Union<HeapObject, TaggedIndex>> tmp218;
  TNode<IntPtrT> tmp219;
  TNode<IntPtrT> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<IntPtrT> tmp222;
  TNode<UintPtrT> tmp223;
  TNode<UintPtrT> tmp224;
  TNode<BoolT> tmp225;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_20, &phi_bb84_25, &phi_bb84_27, &phi_bb84_28, &phi_bb84_29, &phi_bb84_32, &phi_bb84_33, &phi_bb84_37, &phi_bb84_39, &phi_bb84_40, &phi_bb84_41);
    std::tie(tmp218, tmp219, tmp220) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp221 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp222 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb84_20}, TNode<IntPtrT>{tmp221});
    tmp223 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb84_20});
    tmp224 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp220});
    tmp225 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp223}, TNode<UintPtrT>{tmp224});
    ca_.Branch(tmp225, &block100, std::vector<compiler::Node*>{phi_bb84_25, phi_bb84_27, phi_bb84_28, phi_bb84_29, phi_bb84_32, phi_bb84_33, phi_bb84_37, phi_bb84_39, phi_bb84_40, phi_bb84_20, phi_bb84_20, phi_bb84_20, phi_bb84_20}, &block101, std::vector<compiler::Node*>{phi_bb84_25, phi_bb84_27, phi_bb84_28, phi_bb84_29, phi_bb84_32, phi_bb84_33, phi_bb84_37, phi_bb84_39, phi_bb84_40, phi_bb84_20, phi_bb84_20, phi_bb84_20, phi_bb84_20});
  }

  TNode<IntPtrT> phi_bb100_25;
  TNode<IntPtrT> phi_bb100_27;
  TNode<IntPtrT> phi_bb100_28;
  TNode<IntPtrT> phi_bb100_29;
  TNode<IntPtrT> phi_bb100_32;
  TNode<BoolT> phi_bb100_33;
  TNode<BoolT> phi_bb100_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb100_39;
  TNode<IntPtrT> phi_bb100_40;
  TNode<IntPtrT> phi_bb100_46;
  TNode<IntPtrT> phi_bb100_47;
  TNode<IntPtrT> phi_bb100_51;
  TNode<IntPtrT> phi_bb100_52;
  TNode<IntPtrT> tmp226;
  TNode<IntPtrT> tmp227;
  TNode<Union<HeapObject, TaggedIndex>> tmp228;
  TNode<IntPtrT> tmp229;
  TNode<Number> tmp230;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_25, &phi_bb100_27, &phi_bb100_28, &phi_bb100_29, &phi_bb100_32, &phi_bb100_33, &phi_bb100_37, &phi_bb100_39, &phi_bb100_40, &phi_bb100_46, &phi_bb100_47, &phi_bb100_51, &phi_bb100_52);
    tmp226 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb100_52});
    tmp227 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp219}, TNode<IntPtrT>{tmp226});
    std::tie(tmp228, tmp229) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp218}, TNode<IntPtrT>{tmp227}).Flatten();
    tmp230 = Convert_Number_float32_0(state_, TNode<Float32T>{phi_bb84_41});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp228, tmp229}, tmp230);
    ca_.Goto(&block72, tmp222, phi_bb100_25, tmp170, phi_bb100_27, phi_bb100_28, phi_bb100_29, phi_bb100_32, phi_bb100_33, phi_bb100_37);
  }

  TNode<IntPtrT> phi_bb101_25;
  TNode<IntPtrT> phi_bb101_27;
  TNode<IntPtrT> phi_bb101_28;
  TNode<IntPtrT> phi_bb101_29;
  TNode<IntPtrT> phi_bb101_32;
  TNode<BoolT> phi_bb101_33;
  TNode<BoolT> phi_bb101_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb101_39;
  TNode<IntPtrT> phi_bb101_40;
  TNode<IntPtrT> phi_bb101_46;
  TNode<IntPtrT> phi_bb101_47;
  TNode<IntPtrT> phi_bb101_51;
  TNode<IntPtrT> phi_bb101_52;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_25, &phi_bb101_27, &phi_bb101_28, &phi_bb101_29, &phi_bb101_32, &phi_bb101_33, &phi_bb101_37, &phi_bb101_39, &phi_bb101_40, &phi_bb101_46, &phi_bb101_47, &phi_bb101_51, &phi_bb101_52);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb71_20;
  TNode<IntPtrT> phi_bb71_25;
  TNode<IntPtrT> phi_bb71_26;
  TNode<IntPtrT> phi_bb71_27;
  TNode<IntPtrT> phi_bb71_28;
  TNode<IntPtrT> phi_bb71_29;
  TNode<IntPtrT> phi_bb71_32;
  TNode<BoolT> phi_bb71_33;
  TNode<BoolT> phi_bb71_37;
  TNode<Uint32T> tmp231;
  TNode<BoolT> tmp232;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_20, &phi_bb71_25, &phi_bb71_26, &phi_bb71_27, &phi_bb71_28, &phi_bb71_29, &phi_bb71_32, &phi_bb71_33, &phi_bb71_37);
    tmp231 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp232 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp119}, TNode<Uint32T>{tmp231});
    ca_.Branch(tmp232, &block104, std::vector<compiler::Node*>{phi_bb71_20, phi_bb71_25, phi_bb71_26, phi_bb71_27, phi_bb71_28, phi_bb71_29, phi_bb71_32, phi_bb71_33, phi_bb71_37}, &block105, std::vector<compiler::Node*>{phi_bb71_20, phi_bb71_25, phi_bb71_26, phi_bb71_27, phi_bb71_28, phi_bb71_29, phi_bb71_32, phi_bb71_33, phi_bb71_37});
  }

  TNode<IntPtrT> phi_bb104_20;
  TNode<IntPtrT> phi_bb104_25;
  TNode<IntPtrT> phi_bb104_26;
  TNode<IntPtrT> phi_bb104_27;
  TNode<IntPtrT> phi_bb104_28;
  TNode<IntPtrT> phi_bb104_29;
  TNode<IntPtrT> phi_bb104_32;
  TNode<BoolT> phi_bb104_33;
  TNode<BoolT> phi_bb104_37;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_20, &phi_bb104_25, &phi_bb104_26, &phi_bb104_27, &phi_bb104_28, &phi_bb104_29, &phi_bb104_32, &phi_bb104_33, &phi_bb104_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block107, phi_bb104_20, phi_bb104_25, phi_bb104_26, phi_bb104_27, phi_bb104_28, phi_bb104_29, phi_bb104_32, phi_bb104_33, phi_bb104_37);
    } else {
      ca_.Goto(&block108, phi_bb104_20, phi_bb104_25, phi_bb104_26, phi_bb104_27, phi_bb104_28, phi_bb104_29, phi_bb104_32, phi_bb104_33, phi_bb104_37);
    }
  }

  TNode<IntPtrT> phi_bb107_20;
  TNode<IntPtrT> phi_bb107_25;
  TNode<IntPtrT> phi_bb107_26;
  TNode<IntPtrT> phi_bb107_27;
  TNode<IntPtrT> phi_bb107_28;
  TNode<IntPtrT> phi_bb107_29;
  TNode<IntPtrT> phi_bb107_32;
  TNode<BoolT> phi_bb107_33;
  TNode<BoolT> phi_bb107_37;
  TNode<IntPtrT> tmp233;
  TNode<IntPtrT> tmp234;
  TNode<IntPtrT> tmp235;
  TNode<BoolT> tmp236;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_20, &phi_bb107_25, &phi_bb107_26, &phi_bb107_27, &phi_bb107_28, &phi_bb107_29, &phi_bb107_32, &phi_bb107_33, &phi_bb107_37);
    tmp233 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp234 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb107_25}, TNode<IntPtrT>{tmp233});
    tmp235 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp236 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb107_25}, TNode<IntPtrT>{tmp235});
    ca_.Branch(tmp236, &block111, std::vector<compiler::Node*>{phi_bb107_20, phi_bb107_26, phi_bb107_27, phi_bb107_28, phi_bb107_29, phi_bb107_32, phi_bb107_33, phi_bb107_37}, &block112, std::vector<compiler::Node*>{phi_bb107_20, phi_bb107_26, phi_bb107_27, phi_bb107_28, phi_bb107_29, phi_bb107_32, phi_bb107_33, phi_bb107_37});
  }

  TNode<IntPtrT> phi_bb111_20;
  TNode<IntPtrT> phi_bb111_26;
  TNode<IntPtrT> phi_bb111_27;
  TNode<IntPtrT> phi_bb111_28;
  TNode<IntPtrT> phi_bb111_29;
  TNode<IntPtrT> phi_bb111_32;
  TNode<BoolT> phi_bb111_33;
  TNode<BoolT> phi_bb111_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<IntPtrT> tmp239;
  TNode<IntPtrT> tmp240;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_20, &phi_bb111_26, &phi_bb111_27, &phi_bb111_28, &phi_bb111_29, &phi_bb111_32, &phi_bb111_33, &phi_bb111_37);
    std::tie(tmp237, tmp238) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb111_27}).Flatten();
    tmp239 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp240 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb111_27}, TNode<IntPtrT>{tmp239});
    ca_.Goto(&block110, phi_bb111_20, phi_bb111_26, tmp240, phi_bb111_28, phi_bb111_29, phi_bb111_32, phi_bb111_33, phi_bb111_37, tmp237, tmp238);
  }

  TNode<IntPtrT> phi_bb112_20;
  TNode<IntPtrT> phi_bb112_26;
  TNode<IntPtrT> phi_bb112_27;
  TNode<IntPtrT> phi_bb112_28;
  TNode<IntPtrT> phi_bb112_29;
  TNode<IntPtrT> phi_bb112_32;
  TNode<BoolT> phi_bb112_33;
  TNode<BoolT> phi_bb112_37;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_20, &phi_bb112_26, &phi_bb112_27, &phi_bb112_28, &phi_bb112_29, &phi_bb112_32, &phi_bb112_33, &phi_bb112_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block114, phi_bb112_20, phi_bb112_26, phi_bb112_27, phi_bb112_28, phi_bb112_29, phi_bb112_32, phi_bb112_33, phi_bb112_37);
    } else {
      ca_.Goto(&block115, phi_bb112_20, phi_bb112_26, phi_bb112_27, phi_bb112_28, phi_bb112_29, phi_bb112_32, phi_bb112_33, phi_bb112_37);
    }
  }

  TNode<IntPtrT> phi_bb114_20;
  TNode<IntPtrT> phi_bb114_26;
  TNode<IntPtrT> phi_bb114_27;
  TNode<IntPtrT> phi_bb114_28;
  TNode<IntPtrT> phi_bb114_29;
  TNode<IntPtrT> phi_bb114_32;
  TNode<BoolT> phi_bb114_33;
  TNode<BoolT> phi_bb114_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<IntPtrT> tmp243;
  TNode<IntPtrT> tmp244;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_20, &phi_bb114_26, &phi_bb114_27, &phi_bb114_28, &phi_bb114_29, &phi_bb114_32, &phi_bb114_33, &phi_bb114_37);
    std::tie(tmp241, tmp242) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb114_29}).Flatten();
    tmp243 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp244 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb114_29}, TNode<IntPtrT>{tmp243});
    ca_.Goto(&block113, phi_bb114_20, phi_bb114_26, phi_bb114_27, phi_bb114_28, tmp244, phi_bb114_32, phi_bb114_33, phi_bb114_37, tmp241, tmp242);
  }

  TNode<IntPtrT> phi_bb115_20;
  TNode<IntPtrT> phi_bb115_26;
  TNode<IntPtrT> phi_bb115_27;
  TNode<IntPtrT> phi_bb115_28;
  TNode<IntPtrT> phi_bb115_29;
  TNode<IntPtrT> phi_bb115_32;
  TNode<BoolT> phi_bb115_33;
  TNode<BoolT> phi_bb115_37;
  TNode<IntPtrT> tmp245;
  TNode<BoolT> tmp246;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_20, &phi_bb115_26, &phi_bb115_27, &phi_bb115_28, &phi_bb115_29, &phi_bb115_32, &phi_bb115_33, &phi_bb115_37);
    tmp245 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp246 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb115_32}, TNode<IntPtrT>{tmp245});
    ca_.Branch(tmp246, &block117, std::vector<compiler::Node*>{phi_bb115_20, phi_bb115_26, phi_bb115_27, phi_bb115_28, phi_bb115_29, phi_bb115_32, phi_bb115_33, phi_bb115_37}, &block118, std::vector<compiler::Node*>{phi_bb115_20, phi_bb115_26, phi_bb115_27, phi_bb115_28, phi_bb115_29, phi_bb115_32, phi_bb115_33, phi_bb115_37});
  }

  TNode<IntPtrT> phi_bb117_20;
  TNode<IntPtrT> phi_bb117_26;
  TNode<IntPtrT> phi_bb117_27;
  TNode<IntPtrT> phi_bb117_28;
  TNode<IntPtrT> phi_bb117_29;
  TNode<IntPtrT> phi_bb117_32;
  TNode<BoolT> phi_bb117_33;
  TNode<BoolT> phi_bb117_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp247;
  TNode<IntPtrT> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<BoolT> tmp250;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_20, &phi_bb117_26, &phi_bb117_27, &phi_bb117_28, &phi_bb117_29, &phi_bb117_32, &phi_bb117_33, &phi_bb117_37);
    std::tie(tmp247, tmp248) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb117_32}).Flatten();
    tmp249 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp250 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block113, phi_bb117_20, phi_bb117_26, phi_bb117_27, phi_bb117_28, phi_bb117_29, tmp249, tmp250, phi_bb117_37, tmp247, tmp248);
  }

  TNode<IntPtrT> phi_bb118_20;
  TNode<IntPtrT> phi_bb118_26;
  TNode<IntPtrT> phi_bb118_27;
  TNode<IntPtrT> phi_bb118_28;
  TNode<IntPtrT> phi_bb118_29;
  TNode<IntPtrT> phi_bb118_32;
  TNode<BoolT> phi_bb118_33;
  TNode<BoolT> phi_bb118_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<IntPtrT> tmp253;
  TNode<IntPtrT> tmp254;
  TNode<IntPtrT> tmp255;
  TNode<IntPtrT> tmp256;
  TNode<BoolT> tmp257;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_20, &phi_bb118_26, &phi_bb118_27, &phi_bb118_28, &phi_bb118_29, &phi_bb118_32, &phi_bb118_33, &phi_bb118_37);
    std::tie(tmp251, tmp252) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb118_29}).Flatten();
    tmp253 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp254 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb118_29}, TNode<IntPtrT>{tmp253});
    tmp255 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp256 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp254}, TNode<IntPtrT>{tmp255});
    tmp257 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block113, phi_bb118_20, phi_bb118_26, phi_bb118_27, phi_bb118_28, tmp256, tmp254, tmp257, phi_bb118_37, tmp251, tmp252);
  }

  TNode<IntPtrT> phi_bb113_20;
  TNode<IntPtrT> phi_bb113_26;
  TNode<IntPtrT> phi_bb113_27;
  TNode<IntPtrT> phi_bb113_28;
  TNode<IntPtrT> phi_bb113_29;
  TNode<IntPtrT> phi_bb113_32;
  TNode<BoolT> phi_bb113_33;
  TNode<BoolT> phi_bb113_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb113_39;
  TNode<IntPtrT> phi_bb113_40;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_20, &phi_bb113_26, &phi_bb113_27, &phi_bb113_28, &phi_bb113_29, &phi_bb113_32, &phi_bb113_33, &phi_bb113_37, &phi_bb113_39, &phi_bb113_40);
    ca_.Goto(&block110, phi_bb113_20, phi_bb113_26, phi_bb113_27, phi_bb113_28, phi_bb113_29, phi_bb113_32, phi_bb113_33, phi_bb113_37, phi_bb113_39, phi_bb113_40);
  }

  TNode<IntPtrT> phi_bb110_20;
  TNode<IntPtrT> phi_bb110_26;
  TNode<IntPtrT> phi_bb110_27;
  TNode<IntPtrT> phi_bb110_28;
  TNode<IntPtrT> phi_bb110_29;
  TNode<IntPtrT> phi_bb110_32;
  TNode<BoolT> phi_bb110_33;
  TNode<BoolT> phi_bb110_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb110_39;
  TNode<IntPtrT> phi_bb110_40;
  TNode<IntPtrT> tmp258;
  TNode<Union<HeapObject, TaggedIndex>> tmp259;
  TNode<IntPtrT> tmp260;
  TNode<IntPtrT> tmp261;
  TNode<IntPtrT> tmp262;
  TNode<IntPtrT> tmp263;
  TNode<UintPtrT> tmp264;
  TNode<UintPtrT> tmp265;
  TNode<BoolT> tmp266;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_20, &phi_bb110_26, &phi_bb110_27, &phi_bb110_28, &phi_bb110_29, &phi_bb110_32, &phi_bb110_33, &phi_bb110_37, &phi_bb110_39, &phi_bb110_40);
    tmp258 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb110_39, phi_bb110_40});
    std::tie(tmp259, tmp260, tmp261) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp262 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp263 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb110_20}, TNode<IntPtrT>{tmp262});
    tmp264 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb110_20});
    tmp265 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp261});
    tmp266 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp264}, TNode<UintPtrT>{tmp265});
    ca_.Branch(tmp266, &block123, std::vector<compiler::Node*>{phi_bb110_26, phi_bb110_27, phi_bb110_28, phi_bb110_29, phi_bb110_32, phi_bb110_33, phi_bb110_37, phi_bb110_39, phi_bb110_40, phi_bb110_20, phi_bb110_20, phi_bb110_20, phi_bb110_20}, &block124, std::vector<compiler::Node*>{phi_bb110_26, phi_bb110_27, phi_bb110_28, phi_bb110_29, phi_bb110_32, phi_bb110_33, phi_bb110_37, phi_bb110_39, phi_bb110_40, phi_bb110_20, phi_bb110_20, phi_bb110_20, phi_bb110_20});
  }

  TNode<IntPtrT> phi_bb123_26;
  TNode<IntPtrT> phi_bb123_27;
  TNode<IntPtrT> phi_bb123_28;
  TNode<IntPtrT> phi_bb123_29;
  TNode<IntPtrT> phi_bb123_32;
  TNode<BoolT> phi_bb123_33;
  TNode<BoolT> phi_bb123_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb123_39;
  TNode<IntPtrT> phi_bb123_40;
  TNode<IntPtrT> phi_bb123_46;
  TNode<IntPtrT> phi_bb123_47;
  TNode<IntPtrT> phi_bb123_51;
  TNode<IntPtrT> phi_bb123_52;
  TNode<IntPtrT> tmp267;
  TNode<IntPtrT> tmp268;
  TNode<Union<HeapObject, TaggedIndex>> tmp269;
  TNode<IntPtrT> tmp270;
  TNode<BigInt> tmp271;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_26, &phi_bb123_27, &phi_bb123_28, &phi_bb123_29, &phi_bb123_32, &phi_bb123_33, &phi_bb123_37, &phi_bb123_39, &phi_bb123_40, &phi_bb123_46, &phi_bb123_47, &phi_bb123_51, &phi_bb123_52);
    tmp267 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb123_52});
    tmp268 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp260}, TNode<IntPtrT>{tmp267});
    std::tie(tmp269, tmp270) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp259}, TNode<IntPtrT>{tmp268}).Flatten();
    tmp271 = ca_.CallBuiltin<BigInt>(Builtin::kI64ToBigInt, TNode<Object>(), tmp258);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp269, tmp270}, tmp271);
    ca_.Goto(&block109, tmp263, tmp234, phi_bb123_26, phi_bb123_27, phi_bb123_28, phi_bb123_29, phi_bb123_32, phi_bb123_33, phi_bb123_37);
  }

  TNode<IntPtrT> phi_bb124_26;
  TNode<IntPtrT> phi_bb124_27;
  TNode<IntPtrT> phi_bb124_28;
  TNode<IntPtrT> phi_bb124_29;
  TNode<IntPtrT> phi_bb124_32;
  TNode<BoolT> phi_bb124_33;
  TNode<BoolT> phi_bb124_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb124_39;
  TNode<IntPtrT> phi_bb124_40;
  TNode<IntPtrT> phi_bb124_46;
  TNode<IntPtrT> phi_bb124_47;
  TNode<IntPtrT> phi_bb124_51;
  TNode<IntPtrT> phi_bb124_52;
  if (block124.is_used()) {
    ca_.Bind(&block124, &phi_bb124_26, &phi_bb124_27, &phi_bb124_28, &phi_bb124_29, &phi_bb124_32, &phi_bb124_33, &phi_bb124_37, &phi_bb124_39, &phi_bb124_40, &phi_bb124_46, &phi_bb124_47, &phi_bb124_51, &phi_bb124_52);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb108_20;
  TNode<IntPtrT> phi_bb108_25;
  TNode<IntPtrT> phi_bb108_26;
  TNode<IntPtrT> phi_bb108_27;
  TNode<IntPtrT> phi_bb108_28;
  TNode<IntPtrT> phi_bb108_29;
  TNode<IntPtrT> phi_bb108_32;
  TNode<BoolT> phi_bb108_33;
  TNode<BoolT> phi_bb108_37;
  TNode<IntPtrT> tmp272;
  TNode<IntPtrT> tmp273;
  TNode<IntPtrT> tmp274;
  TNode<BoolT> tmp275;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_20, &phi_bb108_25, &phi_bb108_26, &phi_bb108_27, &phi_bb108_28, &phi_bb108_29, &phi_bb108_32, &phi_bb108_33, &phi_bb108_37);
    tmp272 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp273 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb108_25}, TNode<IntPtrT>{tmp272});
    tmp274 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp275 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb108_25}, TNode<IntPtrT>{tmp274});
    ca_.Branch(tmp275, &block128, std::vector<compiler::Node*>{phi_bb108_20, phi_bb108_26, phi_bb108_27, phi_bb108_28, phi_bb108_29, phi_bb108_32, phi_bb108_33, phi_bb108_37}, &block129, std::vector<compiler::Node*>{phi_bb108_20, phi_bb108_26, phi_bb108_27, phi_bb108_28, phi_bb108_29, phi_bb108_32, phi_bb108_33, phi_bb108_37});
  }

  TNode<IntPtrT> phi_bb128_20;
  TNode<IntPtrT> phi_bb128_26;
  TNode<IntPtrT> phi_bb128_27;
  TNode<IntPtrT> phi_bb128_28;
  TNode<IntPtrT> phi_bb128_29;
  TNode<IntPtrT> phi_bb128_32;
  TNode<BoolT> phi_bb128_33;
  TNode<BoolT> phi_bb128_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp276;
  TNode<IntPtrT> tmp277;
  TNode<IntPtrT> tmp278;
  TNode<IntPtrT> tmp279;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_20, &phi_bb128_26, &phi_bb128_27, &phi_bb128_28, &phi_bb128_29, &phi_bb128_32, &phi_bb128_33, &phi_bb128_37);
    std::tie(tmp276, tmp277) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb128_27}).Flatten();
    tmp278 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp279 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb128_27}, TNode<IntPtrT>{tmp278});
    ca_.Goto(&block127, phi_bb128_20, phi_bb128_26, tmp279, phi_bb128_28, phi_bb128_29, phi_bb128_32, phi_bb128_33, phi_bb128_37, tmp276, tmp277);
  }

  TNode<IntPtrT> phi_bb129_20;
  TNode<IntPtrT> phi_bb129_26;
  TNode<IntPtrT> phi_bb129_27;
  TNode<IntPtrT> phi_bb129_28;
  TNode<IntPtrT> phi_bb129_29;
  TNode<IntPtrT> phi_bb129_32;
  TNode<BoolT> phi_bb129_33;
  TNode<BoolT> phi_bb129_37;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_20, &phi_bb129_26, &phi_bb129_27, &phi_bb129_28, &phi_bb129_29, &phi_bb129_32, &phi_bb129_33, &phi_bb129_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block131, phi_bb129_20, phi_bb129_26, phi_bb129_27, phi_bb129_28, phi_bb129_29, phi_bb129_32, phi_bb129_33, phi_bb129_37);
    } else {
      ca_.Goto(&block132, phi_bb129_20, phi_bb129_26, phi_bb129_27, phi_bb129_28, phi_bb129_29, phi_bb129_32, phi_bb129_33, phi_bb129_37);
    }
  }

  TNode<IntPtrT> phi_bb131_20;
  TNode<IntPtrT> phi_bb131_26;
  TNode<IntPtrT> phi_bb131_27;
  TNode<IntPtrT> phi_bb131_28;
  TNode<IntPtrT> phi_bb131_29;
  TNode<IntPtrT> phi_bb131_32;
  TNode<BoolT> phi_bb131_33;
  TNode<BoolT> phi_bb131_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp280;
  TNode<IntPtrT> tmp281;
  TNode<IntPtrT> tmp282;
  TNode<IntPtrT> tmp283;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_20, &phi_bb131_26, &phi_bb131_27, &phi_bb131_28, &phi_bb131_29, &phi_bb131_32, &phi_bb131_33, &phi_bb131_37);
    std::tie(tmp280, tmp281) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb131_29}).Flatten();
    tmp282 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp283 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb131_29}, TNode<IntPtrT>{tmp282});
    ca_.Goto(&block130, phi_bb131_20, phi_bb131_26, phi_bb131_27, phi_bb131_28, tmp283, phi_bb131_32, phi_bb131_33, phi_bb131_37, tmp280, tmp281);
  }

  TNode<IntPtrT> phi_bb132_20;
  TNode<IntPtrT> phi_bb132_26;
  TNode<IntPtrT> phi_bb132_27;
  TNode<IntPtrT> phi_bb132_28;
  TNode<IntPtrT> phi_bb132_29;
  TNode<IntPtrT> phi_bb132_32;
  TNode<BoolT> phi_bb132_33;
  TNode<BoolT> phi_bb132_37;
  TNode<IntPtrT> tmp284;
  TNode<BoolT> tmp285;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_20, &phi_bb132_26, &phi_bb132_27, &phi_bb132_28, &phi_bb132_29, &phi_bb132_32, &phi_bb132_33, &phi_bb132_37);
    tmp284 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp285 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb132_32}, TNode<IntPtrT>{tmp284});
    ca_.Branch(tmp285, &block134, std::vector<compiler::Node*>{phi_bb132_20, phi_bb132_26, phi_bb132_27, phi_bb132_28, phi_bb132_29, phi_bb132_32, phi_bb132_33, phi_bb132_37}, &block135, std::vector<compiler::Node*>{phi_bb132_20, phi_bb132_26, phi_bb132_27, phi_bb132_28, phi_bb132_29, phi_bb132_32, phi_bb132_33, phi_bb132_37});
  }

  TNode<IntPtrT> phi_bb134_20;
  TNode<IntPtrT> phi_bb134_26;
  TNode<IntPtrT> phi_bb134_27;
  TNode<IntPtrT> phi_bb134_28;
  TNode<IntPtrT> phi_bb134_29;
  TNode<IntPtrT> phi_bb134_32;
  TNode<BoolT> phi_bb134_33;
  TNode<BoolT> phi_bb134_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp286;
  TNode<IntPtrT> tmp287;
  TNode<IntPtrT> tmp288;
  TNode<BoolT> tmp289;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_20, &phi_bb134_26, &phi_bb134_27, &phi_bb134_28, &phi_bb134_29, &phi_bb134_32, &phi_bb134_33, &phi_bb134_37);
    std::tie(tmp286, tmp287) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb134_32}).Flatten();
    tmp288 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp289 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block130, phi_bb134_20, phi_bb134_26, phi_bb134_27, phi_bb134_28, phi_bb134_29, tmp288, tmp289, phi_bb134_37, tmp286, tmp287);
  }

  TNode<IntPtrT> phi_bb135_20;
  TNode<IntPtrT> phi_bb135_26;
  TNode<IntPtrT> phi_bb135_27;
  TNode<IntPtrT> phi_bb135_28;
  TNode<IntPtrT> phi_bb135_29;
  TNode<IntPtrT> phi_bb135_32;
  TNode<BoolT> phi_bb135_33;
  TNode<BoolT> phi_bb135_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp290;
  TNode<IntPtrT> tmp291;
  TNode<IntPtrT> tmp292;
  TNode<IntPtrT> tmp293;
  TNode<IntPtrT> tmp294;
  TNode<IntPtrT> tmp295;
  TNode<BoolT> tmp296;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_20, &phi_bb135_26, &phi_bb135_27, &phi_bb135_28, &phi_bb135_29, &phi_bb135_32, &phi_bb135_33, &phi_bb135_37);
    std::tie(tmp290, tmp291) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb135_29}).Flatten();
    tmp292 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp293 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb135_29}, TNode<IntPtrT>{tmp292});
    tmp294 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp295 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp293}, TNode<IntPtrT>{tmp294});
    tmp296 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block130, phi_bb135_20, phi_bb135_26, phi_bb135_27, phi_bb135_28, tmp295, tmp293, tmp296, phi_bb135_37, tmp290, tmp291);
  }

  TNode<IntPtrT> phi_bb130_20;
  TNode<IntPtrT> phi_bb130_26;
  TNode<IntPtrT> phi_bb130_27;
  TNode<IntPtrT> phi_bb130_28;
  TNode<IntPtrT> phi_bb130_29;
  TNode<IntPtrT> phi_bb130_32;
  TNode<BoolT> phi_bb130_33;
  TNode<BoolT> phi_bb130_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb130_39;
  TNode<IntPtrT> phi_bb130_40;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_20, &phi_bb130_26, &phi_bb130_27, &phi_bb130_28, &phi_bb130_29, &phi_bb130_32, &phi_bb130_33, &phi_bb130_37, &phi_bb130_39, &phi_bb130_40);
    ca_.Goto(&block127, phi_bb130_20, phi_bb130_26, phi_bb130_27, phi_bb130_28, phi_bb130_29, phi_bb130_32, phi_bb130_33, phi_bb130_37, phi_bb130_39, phi_bb130_40);
  }

  TNode<IntPtrT> phi_bb127_20;
  TNode<IntPtrT> phi_bb127_26;
  TNode<IntPtrT> phi_bb127_27;
  TNode<IntPtrT> phi_bb127_28;
  TNode<IntPtrT> phi_bb127_29;
  TNode<IntPtrT> phi_bb127_32;
  TNode<BoolT> phi_bb127_33;
  TNode<BoolT> phi_bb127_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb127_39;
  TNode<IntPtrT> phi_bb127_40;
  TNode<IntPtrT> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<IntPtrT> tmp299;
  TNode<BoolT> tmp300;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_20, &phi_bb127_26, &phi_bb127_27, &phi_bb127_28, &phi_bb127_29, &phi_bb127_32, &phi_bb127_33, &phi_bb127_37, &phi_bb127_39, &phi_bb127_40);
    tmp297 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp298 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp273}, TNode<IntPtrT>{tmp297});
    tmp299 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp300 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp273}, TNode<IntPtrT>{tmp299});
    ca_.Branch(tmp300, &block137, std::vector<compiler::Node*>{phi_bb127_20, phi_bb127_26, phi_bb127_27, phi_bb127_28, phi_bb127_29, phi_bb127_32, phi_bb127_33, phi_bb127_37, phi_bb127_39, phi_bb127_40}, &block138, std::vector<compiler::Node*>{phi_bb127_20, phi_bb127_26, phi_bb127_27, phi_bb127_28, phi_bb127_29, phi_bb127_32, phi_bb127_33, phi_bb127_37, phi_bb127_39, phi_bb127_40});
  }

  TNode<IntPtrT> phi_bb137_20;
  TNode<IntPtrT> phi_bb137_26;
  TNode<IntPtrT> phi_bb137_27;
  TNode<IntPtrT> phi_bb137_28;
  TNode<IntPtrT> phi_bb137_29;
  TNode<IntPtrT> phi_bb137_32;
  TNode<BoolT> phi_bb137_33;
  TNode<BoolT> phi_bb137_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb137_39;
  TNode<IntPtrT> phi_bb137_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp301;
  TNode<IntPtrT> tmp302;
  TNode<IntPtrT> tmp303;
  TNode<IntPtrT> tmp304;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_20, &phi_bb137_26, &phi_bb137_27, &phi_bb137_28, &phi_bb137_29, &phi_bb137_32, &phi_bb137_33, &phi_bb137_37, &phi_bb137_39, &phi_bb137_40);
    std::tie(tmp301, tmp302) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb137_27}).Flatten();
    tmp303 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp304 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb137_27}, TNode<IntPtrT>{tmp303});
    ca_.Goto(&block136, phi_bb137_20, phi_bb137_26, tmp304, phi_bb137_28, phi_bb137_29, phi_bb137_32, phi_bb137_33, phi_bb137_37, phi_bb137_39, phi_bb137_40, tmp301, tmp302);
  }

  TNode<IntPtrT> phi_bb138_20;
  TNode<IntPtrT> phi_bb138_26;
  TNode<IntPtrT> phi_bb138_27;
  TNode<IntPtrT> phi_bb138_28;
  TNode<IntPtrT> phi_bb138_29;
  TNode<IntPtrT> phi_bb138_32;
  TNode<BoolT> phi_bb138_33;
  TNode<BoolT> phi_bb138_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb138_39;
  TNode<IntPtrT> phi_bb138_40;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_20, &phi_bb138_26, &phi_bb138_27, &phi_bb138_28, &phi_bb138_29, &phi_bb138_32, &phi_bb138_33, &phi_bb138_37, &phi_bb138_39, &phi_bb138_40);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block140, phi_bb138_20, phi_bb138_26, phi_bb138_27, phi_bb138_28, phi_bb138_29, phi_bb138_32, phi_bb138_33, phi_bb138_37, phi_bb138_39, phi_bb138_40);
    } else {
      ca_.Goto(&block141, phi_bb138_20, phi_bb138_26, phi_bb138_27, phi_bb138_28, phi_bb138_29, phi_bb138_32, phi_bb138_33, phi_bb138_37, phi_bb138_39, phi_bb138_40);
    }
  }

  TNode<IntPtrT> phi_bb140_20;
  TNode<IntPtrT> phi_bb140_26;
  TNode<IntPtrT> phi_bb140_27;
  TNode<IntPtrT> phi_bb140_28;
  TNode<IntPtrT> phi_bb140_29;
  TNode<IntPtrT> phi_bb140_32;
  TNode<BoolT> phi_bb140_33;
  TNode<BoolT> phi_bb140_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb140_39;
  TNode<IntPtrT> phi_bb140_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp305;
  TNode<IntPtrT> tmp306;
  TNode<IntPtrT> tmp307;
  TNode<IntPtrT> tmp308;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_20, &phi_bb140_26, &phi_bb140_27, &phi_bb140_28, &phi_bb140_29, &phi_bb140_32, &phi_bb140_33, &phi_bb140_37, &phi_bb140_39, &phi_bb140_40);
    std::tie(tmp305, tmp306) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb140_29}).Flatten();
    tmp307 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp308 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb140_29}, TNode<IntPtrT>{tmp307});
    ca_.Goto(&block139, phi_bb140_20, phi_bb140_26, phi_bb140_27, phi_bb140_28, tmp308, phi_bb140_32, phi_bb140_33, phi_bb140_37, phi_bb140_39, phi_bb140_40, tmp305, tmp306);
  }

  TNode<IntPtrT> phi_bb141_20;
  TNode<IntPtrT> phi_bb141_26;
  TNode<IntPtrT> phi_bb141_27;
  TNode<IntPtrT> phi_bb141_28;
  TNode<IntPtrT> phi_bb141_29;
  TNode<IntPtrT> phi_bb141_32;
  TNode<BoolT> phi_bb141_33;
  TNode<BoolT> phi_bb141_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb141_39;
  TNode<IntPtrT> phi_bb141_40;
  TNode<IntPtrT> tmp309;
  TNode<BoolT> tmp310;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_20, &phi_bb141_26, &phi_bb141_27, &phi_bb141_28, &phi_bb141_29, &phi_bb141_32, &phi_bb141_33, &phi_bb141_37, &phi_bb141_39, &phi_bb141_40);
    tmp309 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp310 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb141_32}, TNode<IntPtrT>{tmp309});
    ca_.Branch(tmp310, &block143, std::vector<compiler::Node*>{phi_bb141_20, phi_bb141_26, phi_bb141_27, phi_bb141_28, phi_bb141_29, phi_bb141_32, phi_bb141_33, phi_bb141_37, phi_bb141_39, phi_bb141_40}, &block144, std::vector<compiler::Node*>{phi_bb141_20, phi_bb141_26, phi_bb141_27, phi_bb141_28, phi_bb141_29, phi_bb141_32, phi_bb141_33, phi_bb141_37, phi_bb141_39, phi_bb141_40});
  }

  TNode<IntPtrT> phi_bb143_20;
  TNode<IntPtrT> phi_bb143_26;
  TNode<IntPtrT> phi_bb143_27;
  TNode<IntPtrT> phi_bb143_28;
  TNode<IntPtrT> phi_bb143_29;
  TNode<IntPtrT> phi_bb143_32;
  TNode<BoolT> phi_bb143_33;
  TNode<BoolT> phi_bb143_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb143_39;
  TNode<IntPtrT> phi_bb143_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp311;
  TNode<IntPtrT> tmp312;
  TNode<IntPtrT> tmp313;
  TNode<BoolT> tmp314;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_20, &phi_bb143_26, &phi_bb143_27, &phi_bb143_28, &phi_bb143_29, &phi_bb143_32, &phi_bb143_33, &phi_bb143_37, &phi_bb143_39, &phi_bb143_40);
    std::tie(tmp311, tmp312) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb143_32}).Flatten();
    tmp313 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp314 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block139, phi_bb143_20, phi_bb143_26, phi_bb143_27, phi_bb143_28, phi_bb143_29, tmp313, tmp314, phi_bb143_37, phi_bb143_39, phi_bb143_40, tmp311, tmp312);
  }

  TNode<IntPtrT> phi_bb144_20;
  TNode<IntPtrT> phi_bb144_26;
  TNode<IntPtrT> phi_bb144_27;
  TNode<IntPtrT> phi_bb144_28;
  TNode<IntPtrT> phi_bb144_29;
  TNode<IntPtrT> phi_bb144_32;
  TNode<BoolT> phi_bb144_33;
  TNode<BoolT> phi_bb144_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb144_39;
  TNode<IntPtrT> phi_bb144_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp315;
  TNode<IntPtrT> tmp316;
  TNode<IntPtrT> tmp317;
  TNode<IntPtrT> tmp318;
  TNode<IntPtrT> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<BoolT> tmp321;
  if (block144.is_used()) {
    ca_.Bind(&block144, &phi_bb144_20, &phi_bb144_26, &phi_bb144_27, &phi_bb144_28, &phi_bb144_29, &phi_bb144_32, &phi_bb144_33, &phi_bb144_37, &phi_bb144_39, &phi_bb144_40);
    std::tie(tmp315, tmp316) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb144_29}).Flatten();
    tmp317 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp318 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb144_29}, TNode<IntPtrT>{tmp317});
    tmp319 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp320 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp318}, TNode<IntPtrT>{tmp319});
    tmp321 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block139, phi_bb144_20, phi_bb144_26, phi_bb144_27, phi_bb144_28, tmp320, tmp318, tmp321, phi_bb144_37, phi_bb144_39, phi_bb144_40, tmp315, tmp316);
  }

  TNode<IntPtrT> phi_bb139_20;
  TNode<IntPtrT> phi_bb139_26;
  TNode<IntPtrT> phi_bb139_27;
  TNode<IntPtrT> phi_bb139_28;
  TNode<IntPtrT> phi_bb139_29;
  TNode<IntPtrT> phi_bb139_32;
  TNode<BoolT> phi_bb139_33;
  TNode<BoolT> phi_bb139_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb139_39;
  TNode<IntPtrT> phi_bb139_40;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb139_41;
  TNode<IntPtrT> phi_bb139_42;
  if (block139.is_used()) {
    ca_.Bind(&block139, &phi_bb139_20, &phi_bb139_26, &phi_bb139_27, &phi_bb139_28, &phi_bb139_29, &phi_bb139_32, &phi_bb139_33, &phi_bb139_37, &phi_bb139_39, &phi_bb139_40, &phi_bb139_41, &phi_bb139_42);
    ca_.Goto(&block136, phi_bb139_20, phi_bb139_26, phi_bb139_27, phi_bb139_28, phi_bb139_29, phi_bb139_32, phi_bb139_33, phi_bb139_37, phi_bb139_39, phi_bb139_40, phi_bb139_41, phi_bb139_42);
  }

  TNode<IntPtrT> phi_bb136_20;
  TNode<IntPtrT> phi_bb136_26;
  TNode<IntPtrT> phi_bb136_27;
  TNode<IntPtrT> phi_bb136_28;
  TNode<IntPtrT> phi_bb136_29;
  TNode<IntPtrT> phi_bb136_32;
  TNode<BoolT> phi_bb136_33;
  TNode<BoolT> phi_bb136_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb136_39;
  TNode<IntPtrT> phi_bb136_40;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb136_41;
  TNode<IntPtrT> phi_bb136_42;
  TNode<IntPtrT> tmp322;
  TNode<IntPtrT> tmp323;
  TNode<Union<HeapObject, TaggedIndex>> tmp324;
  TNode<IntPtrT> tmp325;
  TNode<IntPtrT> tmp326;
  TNode<IntPtrT> tmp327;
  TNode<IntPtrT> tmp328;
  TNode<UintPtrT> tmp329;
  TNode<UintPtrT> tmp330;
  TNode<BoolT> tmp331;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_20, &phi_bb136_26, &phi_bb136_27, &phi_bb136_28, &phi_bb136_29, &phi_bb136_32, &phi_bb136_33, &phi_bb136_37, &phi_bb136_39, &phi_bb136_40, &phi_bb136_41, &phi_bb136_42);
    tmp322 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb136_39, phi_bb136_40});
    tmp323 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb136_41, phi_bb136_42});
    std::tie(tmp324, tmp325, tmp326) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp327 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp328 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb136_20}, TNode<IntPtrT>{tmp327});
    tmp329 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb136_20});
    tmp330 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp326});
    tmp331 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp329}, TNode<UintPtrT>{tmp330});
    ca_.Branch(tmp331, &block149, std::vector<compiler::Node*>{phi_bb136_26, phi_bb136_27, phi_bb136_28, phi_bb136_29, phi_bb136_32, phi_bb136_33, phi_bb136_37, phi_bb136_39, phi_bb136_40, phi_bb136_41, phi_bb136_42, phi_bb136_20, phi_bb136_20, phi_bb136_20, phi_bb136_20}, &block150, std::vector<compiler::Node*>{phi_bb136_26, phi_bb136_27, phi_bb136_28, phi_bb136_29, phi_bb136_32, phi_bb136_33, phi_bb136_37, phi_bb136_39, phi_bb136_40, phi_bb136_41, phi_bb136_42, phi_bb136_20, phi_bb136_20, phi_bb136_20, phi_bb136_20});
  }

  TNode<IntPtrT> phi_bb149_26;
  TNode<IntPtrT> phi_bb149_27;
  TNode<IntPtrT> phi_bb149_28;
  TNode<IntPtrT> phi_bb149_29;
  TNode<IntPtrT> phi_bb149_32;
  TNode<BoolT> phi_bb149_33;
  TNode<BoolT> phi_bb149_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb149_39;
  TNode<IntPtrT> phi_bb149_40;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb149_41;
  TNode<IntPtrT> phi_bb149_42;
  TNode<IntPtrT> phi_bb149_49;
  TNode<IntPtrT> phi_bb149_50;
  TNode<IntPtrT> phi_bb149_54;
  TNode<IntPtrT> phi_bb149_55;
  TNode<IntPtrT> tmp332;
  TNode<IntPtrT> tmp333;
  TNode<Union<HeapObject, TaggedIndex>> tmp334;
  TNode<IntPtrT> tmp335;
  TNode<BigInt> tmp336;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_26, &phi_bb149_27, &phi_bb149_28, &phi_bb149_29, &phi_bb149_32, &phi_bb149_33, &phi_bb149_37, &phi_bb149_39, &phi_bb149_40, &phi_bb149_41, &phi_bb149_42, &phi_bb149_49, &phi_bb149_50, &phi_bb149_54, &phi_bb149_55);
    tmp332 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb149_55});
    tmp333 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp325}, TNode<IntPtrT>{tmp332});
    std::tie(tmp334, tmp335) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp324}, TNode<IntPtrT>{tmp333}).Flatten();
    tmp336 = ca_.CallBuiltin<BigInt>(Builtin::kI32PairToBigInt, TNode<Object>(), tmp322, tmp323);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp334, tmp335}, tmp336);
    ca_.Goto(&block109, tmp328, tmp298, phi_bb149_26, phi_bb149_27, phi_bb149_28, phi_bb149_29, phi_bb149_32, phi_bb149_33, phi_bb149_37);
  }

  TNode<IntPtrT> phi_bb150_26;
  TNode<IntPtrT> phi_bb150_27;
  TNode<IntPtrT> phi_bb150_28;
  TNode<IntPtrT> phi_bb150_29;
  TNode<IntPtrT> phi_bb150_32;
  TNode<BoolT> phi_bb150_33;
  TNode<BoolT> phi_bb150_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb150_39;
  TNode<IntPtrT> phi_bb150_40;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb150_41;
  TNode<IntPtrT> phi_bb150_42;
  TNode<IntPtrT> phi_bb150_49;
  TNode<IntPtrT> phi_bb150_50;
  TNode<IntPtrT> phi_bb150_54;
  TNode<IntPtrT> phi_bb150_55;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_26, &phi_bb150_27, &phi_bb150_28, &phi_bb150_29, &phi_bb150_32, &phi_bb150_33, &phi_bb150_37, &phi_bb150_39, &phi_bb150_40, &phi_bb150_41, &phi_bb150_42, &phi_bb150_49, &phi_bb150_50, &phi_bb150_54, &phi_bb150_55);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb109_20;
  TNode<IntPtrT> phi_bb109_25;
  TNode<IntPtrT> phi_bb109_26;
  TNode<IntPtrT> phi_bb109_27;
  TNode<IntPtrT> phi_bb109_28;
  TNode<IntPtrT> phi_bb109_29;
  TNode<IntPtrT> phi_bb109_32;
  TNode<BoolT> phi_bb109_33;
  TNode<BoolT> phi_bb109_37;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_20, &phi_bb109_25, &phi_bb109_26, &phi_bb109_27, &phi_bb109_28, &phi_bb109_29, &phi_bb109_32, &phi_bb109_33, &phi_bb109_37);
    ca_.Goto(&block106, phi_bb109_20, phi_bb109_25, phi_bb109_26, phi_bb109_27, phi_bb109_28, phi_bb109_29, phi_bb109_32, phi_bb109_33, phi_bb109_37);
  }

  TNode<IntPtrT> phi_bb105_20;
  TNode<IntPtrT> phi_bb105_25;
  TNode<IntPtrT> phi_bb105_26;
  TNode<IntPtrT> phi_bb105_27;
  TNode<IntPtrT> phi_bb105_28;
  TNode<IntPtrT> phi_bb105_29;
  TNode<IntPtrT> phi_bb105_32;
  TNode<BoolT> phi_bb105_33;
  TNode<BoolT> phi_bb105_37;
  TNode<Uint32T> tmp337;
  TNode<BoolT> tmp338;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_20, &phi_bb105_25, &phi_bb105_26, &phi_bb105_27, &phi_bb105_28, &phi_bb105_29, &phi_bb105_32, &phi_bb105_33, &phi_bb105_37);
    tmp337 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp338 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp119}, TNode<Uint32T>{tmp337});
    ca_.Branch(tmp338, &block153, std::vector<compiler::Node*>{phi_bb105_20, phi_bb105_25, phi_bb105_26, phi_bb105_27, phi_bb105_28, phi_bb105_29, phi_bb105_32, phi_bb105_33, phi_bb105_37}, &block154, std::vector<compiler::Node*>{phi_bb105_20, phi_bb105_25, phi_bb105_26, phi_bb105_27, phi_bb105_28, phi_bb105_29, phi_bb105_32, phi_bb105_33, phi_bb105_37});
  }

  TNode<IntPtrT> phi_bb153_20;
  TNode<IntPtrT> phi_bb153_25;
  TNode<IntPtrT> phi_bb153_26;
  TNode<IntPtrT> phi_bb153_27;
  TNode<IntPtrT> phi_bb153_28;
  TNode<IntPtrT> phi_bb153_29;
  TNode<IntPtrT> phi_bb153_32;
  TNode<BoolT> phi_bb153_33;
  TNode<BoolT> phi_bb153_37;
  TNode<IntPtrT> tmp339;
  TNode<IntPtrT> tmp340;
  TNode<IntPtrT> tmp341;
  TNode<BoolT> tmp342;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_20, &phi_bb153_25, &phi_bb153_26, &phi_bb153_27, &phi_bb153_28, &phi_bb153_29, &phi_bb153_32, &phi_bb153_33, &phi_bb153_37);
    tmp339 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp340 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb153_26}, TNode<IntPtrT>{tmp339});
    tmp341 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp342 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb153_26}, TNode<IntPtrT>{tmp341});
    ca_.Branch(tmp342, &block157, std::vector<compiler::Node*>{phi_bb153_20, phi_bb153_25, phi_bb153_27, phi_bb153_28, phi_bb153_29, phi_bb153_32, phi_bb153_33, phi_bb153_37}, &block158, std::vector<compiler::Node*>{phi_bb153_20, phi_bb153_25, phi_bb153_27, phi_bb153_28, phi_bb153_29, phi_bb153_32, phi_bb153_33, phi_bb153_37});
  }

  TNode<IntPtrT> phi_bb157_20;
  TNode<IntPtrT> phi_bb157_25;
  TNode<IntPtrT> phi_bb157_27;
  TNode<IntPtrT> phi_bb157_28;
  TNode<IntPtrT> phi_bb157_29;
  TNode<IntPtrT> phi_bb157_32;
  TNode<BoolT> phi_bb157_33;
  TNode<BoolT> phi_bb157_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp343;
  TNode<IntPtrT> tmp344;
  TNode<IntPtrT> tmp345;
  TNode<IntPtrT> tmp346;
  if (block157.is_used()) {
    ca_.Bind(&block157, &phi_bb157_20, &phi_bb157_25, &phi_bb157_27, &phi_bb157_28, &phi_bb157_29, &phi_bb157_32, &phi_bb157_33, &phi_bb157_37);
    std::tie(tmp343, tmp344) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb157_28}).Flatten();
    tmp345 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp346 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb157_28}, TNode<IntPtrT>{tmp345});
    ca_.Goto(&block156, phi_bb157_20, phi_bb157_25, phi_bb157_27, tmp346, phi_bb157_29, phi_bb157_32, phi_bb157_33, phi_bb157_37, tmp343, tmp344);
  }

  TNode<IntPtrT> phi_bb158_20;
  TNode<IntPtrT> phi_bb158_25;
  TNode<IntPtrT> phi_bb158_27;
  TNode<IntPtrT> phi_bb158_28;
  TNode<IntPtrT> phi_bb158_29;
  TNode<IntPtrT> phi_bb158_32;
  TNode<BoolT> phi_bb158_33;
  TNode<BoolT> phi_bb158_37;
  if (block158.is_used()) {
    ca_.Bind(&block158, &phi_bb158_20, &phi_bb158_25, &phi_bb158_27, &phi_bb158_28, &phi_bb158_29, &phi_bb158_32, &phi_bb158_33, &phi_bb158_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block159, phi_bb158_20, phi_bb158_25, phi_bb158_27, phi_bb158_28, phi_bb158_29, phi_bb158_32, phi_bb158_33, phi_bb158_37);
    } else {
      ca_.Goto(&block160, phi_bb158_20, phi_bb158_25, phi_bb158_27, phi_bb158_28, phi_bb158_29, phi_bb158_32, phi_bb158_33, phi_bb158_37);
    }
  }

  TNode<IntPtrT> phi_bb159_20;
  TNode<IntPtrT> phi_bb159_25;
  TNode<IntPtrT> phi_bb159_27;
  TNode<IntPtrT> phi_bb159_28;
  TNode<IntPtrT> phi_bb159_29;
  TNode<IntPtrT> phi_bb159_32;
  TNode<BoolT> phi_bb159_33;
  TNode<BoolT> phi_bb159_37;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_20, &phi_bb159_25, &phi_bb159_27, &phi_bb159_28, &phi_bb159_29, &phi_bb159_32, &phi_bb159_33, &phi_bb159_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block163, phi_bb159_20, phi_bb159_25, phi_bb159_27, phi_bb159_28, phi_bb159_29, phi_bb159_32, phi_bb159_33, phi_bb159_37);
    } else {
      ca_.Goto(&block164, phi_bb159_20, phi_bb159_25, phi_bb159_27, phi_bb159_28, phi_bb159_29, phi_bb159_32, phi_bb159_33, phi_bb159_37);
    }
  }

  TNode<IntPtrT> phi_bb163_20;
  TNode<IntPtrT> phi_bb163_25;
  TNode<IntPtrT> phi_bb163_27;
  TNode<IntPtrT> phi_bb163_28;
  TNode<IntPtrT> phi_bb163_29;
  TNode<IntPtrT> phi_bb163_32;
  TNode<BoolT> phi_bb163_33;
  TNode<BoolT> phi_bb163_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp347;
  TNode<IntPtrT> tmp348;
  TNode<IntPtrT> tmp349;
  TNode<IntPtrT> tmp350;
  if (block163.is_used()) {
    ca_.Bind(&block163, &phi_bb163_20, &phi_bb163_25, &phi_bb163_27, &phi_bb163_28, &phi_bb163_29, &phi_bb163_32, &phi_bb163_33, &phi_bb163_37);
    std::tie(tmp347, tmp348) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb163_29}).Flatten();
    tmp349 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp350 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb163_29}, TNode<IntPtrT>{tmp349});
    ca_.Goto(&block162, phi_bb163_20, phi_bb163_25, phi_bb163_27, phi_bb163_28, tmp350, phi_bb163_32, phi_bb163_33, phi_bb163_37, tmp347, tmp348);
  }

  TNode<IntPtrT> phi_bb164_20;
  TNode<IntPtrT> phi_bb164_25;
  TNode<IntPtrT> phi_bb164_27;
  TNode<IntPtrT> phi_bb164_28;
  TNode<IntPtrT> phi_bb164_29;
  TNode<IntPtrT> phi_bb164_32;
  TNode<BoolT> phi_bb164_33;
  TNode<BoolT> phi_bb164_37;
  TNode<IntPtrT> tmp351;
  TNode<BoolT> tmp352;
  if (block164.is_used()) {
    ca_.Bind(&block164, &phi_bb164_20, &phi_bb164_25, &phi_bb164_27, &phi_bb164_28, &phi_bb164_29, &phi_bb164_32, &phi_bb164_33, &phi_bb164_37);
    tmp351 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp352 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb164_32}, TNode<IntPtrT>{tmp351});
    ca_.Branch(tmp352, &block166, std::vector<compiler::Node*>{phi_bb164_20, phi_bb164_25, phi_bb164_27, phi_bb164_28, phi_bb164_29, phi_bb164_32, phi_bb164_33, phi_bb164_37}, &block167, std::vector<compiler::Node*>{phi_bb164_20, phi_bb164_25, phi_bb164_27, phi_bb164_28, phi_bb164_29, phi_bb164_32, phi_bb164_33, phi_bb164_37});
  }

  TNode<IntPtrT> phi_bb166_20;
  TNode<IntPtrT> phi_bb166_25;
  TNode<IntPtrT> phi_bb166_27;
  TNode<IntPtrT> phi_bb166_28;
  TNode<IntPtrT> phi_bb166_29;
  TNode<IntPtrT> phi_bb166_32;
  TNode<BoolT> phi_bb166_33;
  TNode<BoolT> phi_bb166_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp353;
  TNode<IntPtrT> tmp354;
  TNode<IntPtrT> tmp355;
  TNode<BoolT> tmp356;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_20, &phi_bb166_25, &phi_bb166_27, &phi_bb166_28, &phi_bb166_29, &phi_bb166_32, &phi_bb166_33, &phi_bb166_37);
    std::tie(tmp353, tmp354) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb166_32}).Flatten();
    tmp355 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp356 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block162, phi_bb166_20, phi_bb166_25, phi_bb166_27, phi_bb166_28, phi_bb166_29, tmp355, tmp356, phi_bb166_37, tmp353, tmp354);
  }

  TNode<IntPtrT> phi_bb167_20;
  TNode<IntPtrT> phi_bb167_25;
  TNode<IntPtrT> phi_bb167_27;
  TNode<IntPtrT> phi_bb167_28;
  TNode<IntPtrT> phi_bb167_29;
  TNode<IntPtrT> phi_bb167_32;
  TNode<BoolT> phi_bb167_33;
  TNode<BoolT> phi_bb167_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp357;
  TNode<IntPtrT> tmp358;
  TNode<IntPtrT> tmp359;
  TNode<IntPtrT> tmp360;
  TNode<IntPtrT> tmp361;
  TNode<IntPtrT> tmp362;
  TNode<BoolT> tmp363;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_20, &phi_bb167_25, &phi_bb167_27, &phi_bb167_28, &phi_bb167_29, &phi_bb167_32, &phi_bb167_33, &phi_bb167_37);
    std::tie(tmp357, tmp358) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb167_29}).Flatten();
    tmp359 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp360 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb167_29}, TNode<IntPtrT>{tmp359});
    tmp361 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp362 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp360}, TNode<IntPtrT>{tmp361});
    tmp363 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block162, phi_bb167_20, phi_bb167_25, phi_bb167_27, phi_bb167_28, tmp362, tmp360, tmp363, phi_bb167_37, tmp357, tmp358);
  }

  TNode<IntPtrT> phi_bb162_20;
  TNode<IntPtrT> phi_bb162_25;
  TNode<IntPtrT> phi_bb162_27;
  TNode<IntPtrT> phi_bb162_28;
  TNode<IntPtrT> phi_bb162_29;
  TNode<IntPtrT> phi_bb162_32;
  TNode<BoolT> phi_bb162_33;
  TNode<BoolT> phi_bb162_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb162_39;
  TNode<IntPtrT> phi_bb162_40;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_20, &phi_bb162_25, &phi_bb162_27, &phi_bb162_28, &phi_bb162_29, &phi_bb162_32, &phi_bb162_33, &phi_bb162_37, &phi_bb162_39, &phi_bb162_40);
    ca_.Goto(&block156, phi_bb162_20, phi_bb162_25, phi_bb162_27, phi_bb162_28, phi_bb162_29, phi_bb162_32, phi_bb162_33, phi_bb162_37, phi_bb162_39, phi_bb162_40);
  }

  TNode<IntPtrT> phi_bb160_20;
  TNode<IntPtrT> phi_bb160_25;
  TNode<IntPtrT> phi_bb160_27;
  TNode<IntPtrT> phi_bb160_28;
  TNode<IntPtrT> phi_bb160_29;
  TNode<IntPtrT> phi_bb160_32;
  TNode<BoolT> phi_bb160_33;
  TNode<BoolT> phi_bb160_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp364;
  TNode<IntPtrT> tmp365;
  TNode<IntPtrT> tmp366;
  TNode<IntPtrT> tmp367;
  TNode<BoolT> tmp368;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_20, &phi_bb160_25, &phi_bb160_27, &phi_bb160_28, &phi_bb160_29, &phi_bb160_32, &phi_bb160_33, &phi_bb160_37);
    std::tie(tmp364, tmp365) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb160_29}).Flatten();
    tmp366 = FromConstexpr_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_)))));
    tmp367 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb160_29}, TNode<IntPtrT>{tmp366});
    tmp368 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block156, phi_bb160_20, phi_bb160_25, phi_bb160_27, phi_bb160_28, tmp367, phi_bb160_32, tmp368, phi_bb160_37, tmp364, tmp365);
  }

  TNode<IntPtrT> phi_bb156_20;
  TNode<IntPtrT> phi_bb156_25;
  TNode<IntPtrT> phi_bb156_27;
  TNode<IntPtrT> phi_bb156_28;
  TNode<IntPtrT> phi_bb156_29;
  TNode<IntPtrT> phi_bb156_32;
  TNode<BoolT> phi_bb156_33;
  TNode<BoolT> phi_bb156_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb156_39;
  TNode<IntPtrT> phi_bb156_40;
  TNode<Union<HeapObject, TaggedIndex>> tmp369;
  TNode<IntPtrT> tmp370;
  TNode<Float64T> tmp371;
  TNode<Union<HeapObject, TaggedIndex>> tmp372;
  TNode<IntPtrT> tmp373;
  TNode<IntPtrT> tmp374;
  TNode<IntPtrT> tmp375;
  TNode<IntPtrT> tmp376;
  TNode<UintPtrT> tmp377;
  TNode<UintPtrT> tmp378;
  TNode<BoolT> tmp379;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_20, &phi_bb156_25, &phi_bb156_27, &phi_bb156_28, &phi_bb156_29, &phi_bb156_32, &phi_bb156_33, &phi_bb156_37, &phi_bb156_39, &phi_bb156_40);
    std::tie(tmp369, tmp370) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb156_39}, TNode<IntPtrT>{phi_bb156_40}, TorqueStructUnsafe_0{}}).Flatten();
    tmp371 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp369, tmp370});
    std::tie(tmp372, tmp373, tmp374) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp375 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp376 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb156_20}, TNode<IntPtrT>{tmp375});
    tmp377 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb156_20});
    tmp378 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp374});
    tmp379 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp377}, TNode<UintPtrT>{tmp378});
    ca_.Branch(tmp379, &block172, std::vector<compiler::Node*>{phi_bb156_25, phi_bb156_27, phi_bb156_28, phi_bb156_29, phi_bb156_32, phi_bb156_33, phi_bb156_37, phi_bb156_39, phi_bb156_40, phi_bb156_20, phi_bb156_20, phi_bb156_20, phi_bb156_20}, &block173, std::vector<compiler::Node*>{phi_bb156_25, phi_bb156_27, phi_bb156_28, phi_bb156_29, phi_bb156_32, phi_bb156_33, phi_bb156_37, phi_bb156_39, phi_bb156_40, phi_bb156_20, phi_bb156_20, phi_bb156_20, phi_bb156_20});
  }

  TNode<IntPtrT> phi_bb172_25;
  TNode<IntPtrT> phi_bb172_27;
  TNode<IntPtrT> phi_bb172_28;
  TNode<IntPtrT> phi_bb172_29;
  TNode<IntPtrT> phi_bb172_32;
  TNode<BoolT> phi_bb172_33;
  TNode<BoolT> phi_bb172_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb172_39;
  TNode<IntPtrT> phi_bb172_40;
  TNode<IntPtrT> phi_bb172_46;
  TNode<IntPtrT> phi_bb172_47;
  TNode<IntPtrT> phi_bb172_51;
  TNode<IntPtrT> phi_bb172_52;
  TNode<IntPtrT> tmp380;
  TNode<IntPtrT> tmp381;
  TNode<Union<HeapObject, TaggedIndex>> tmp382;
  TNode<IntPtrT> tmp383;
  TNode<Number> tmp384;
  if (block172.is_used()) {
    ca_.Bind(&block172, &phi_bb172_25, &phi_bb172_27, &phi_bb172_28, &phi_bb172_29, &phi_bb172_32, &phi_bb172_33, &phi_bb172_37, &phi_bb172_39, &phi_bb172_40, &phi_bb172_46, &phi_bb172_47, &phi_bb172_51, &phi_bb172_52);
    tmp380 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb172_52});
    tmp381 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp373}, TNode<IntPtrT>{tmp380});
    std::tie(tmp382, tmp383) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp372}, TNode<IntPtrT>{tmp381}).Flatten();
    tmp384 = Convert_Number_float64_0(state_, TNode<Float64T>{tmp371});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp382, tmp383}, tmp384);
    ca_.Goto(&block155, tmp376, phi_bb172_25, tmp340, phi_bb172_27, phi_bb172_28, phi_bb172_29, phi_bb172_32, phi_bb172_33, phi_bb172_37);
  }

  TNode<IntPtrT> phi_bb173_25;
  TNode<IntPtrT> phi_bb173_27;
  TNode<IntPtrT> phi_bb173_28;
  TNode<IntPtrT> phi_bb173_29;
  TNode<IntPtrT> phi_bb173_32;
  TNode<BoolT> phi_bb173_33;
  TNode<BoolT> phi_bb173_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb173_39;
  TNode<IntPtrT> phi_bb173_40;
  TNode<IntPtrT> phi_bb173_46;
  TNode<IntPtrT> phi_bb173_47;
  TNode<IntPtrT> phi_bb173_51;
  TNode<IntPtrT> phi_bb173_52;
  if (block173.is_used()) {
    ca_.Bind(&block173, &phi_bb173_25, &phi_bb173_27, &phi_bb173_28, &phi_bb173_29, &phi_bb173_32, &phi_bb173_33, &phi_bb173_37, &phi_bb173_39, &phi_bb173_40, &phi_bb173_46, &phi_bb173_47, &phi_bb173_51, &phi_bb173_52);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb154_20;
  TNode<IntPtrT> phi_bb154_25;
  TNode<IntPtrT> phi_bb154_26;
  TNode<IntPtrT> phi_bb154_27;
  TNode<IntPtrT> phi_bb154_28;
  TNode<IntPtrT> phi_bb154_29;
  TNode<IntPtrT> phi_bb154_32;
  TNode<BoolT> phi_bb154_33;
  TNode<BoolT> phi_bb154_37;
  TNode<Uint32T> tmp385;
  TNode<Uint32T> tmp386;
  TNode<Uint32T> tmp387;
  TNode<BoolT> tmp388;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_20, &phi_bb154_25, &phi_bb154_26, &phi_bb154_27, &phi_bb154_28, &phi_bb154_29, &phi_bb154_32, &phi_bb154_33, &phi_bb154_37);
    tmp385 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp386 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp119}, TNode<Uint32T>{tmp385});
    tmp387 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp388 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp386}, TNode<Uint32T>{tmp387});
    ca_.Branch(tmp388, &block176, std::vector<compiler::Node*>{phi_bb154_20, phi_bb154_25, phi_bb154_26, phi_bb154_27, phi_bb154_28, phi_bb154_29, phi_bb154_32, phi_bb154_33, phi_bb154_37}, &block177, std::vector<compiler::Node*>{phi_bb154_20, phi_bb154_25, phi_bb154_26, phi_bb154_27, phi_bb154_28, phi_bb154_29, phi_bb154_32, phi_bb154_33, phi_bb154_37});
  }

  TNode<IntPtrT> phi_bb177_20;
  TNode<IntPtrT> phi_bb177_25;
  TNode<IntPtrT> phi_bb177_26;
  TNode<IntPtrT> phi_bb177_27;
  TNode<IntPtrT> phi_bb177_28;
  TNode<IntPtrT> phi_bb177_29;
  TNode<IntPtrT> phi_bb177_32;
  TNode<BoolT> phi_bb177_33;
  TNode<BoolT> phi_bb177_37;
  if (block177.is_used()) {
    ca_.Bind(&block177, &phi_bb177_20, &phi_bb177_25, &phi_bb177_26, &phi_bb177_27, &phi_bb177_28, &phi_bb177_29, &phi_bb177_32, &phi_bb177_33, &phi_bb177_37);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/wasm-to-js.tq", 166});
      CodeStubAssembler(state_).FailAssert("Torque assert '(paramType & kValueTypeIsRefBit) != 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb176_20;
  TNode<IntPtrT> phi_bb176_25;
  TNode<IntPtrT> phi_bb176_26;
  TNode<IntPtrT> phi_bb176_27;
  TNode<IntPtrT> phi_bb176_28;
  TNode<IntPtrT> phi_bb176_29;
  TNode<IntPtrT> phi_bb176_32;
  TNode<BoolT> phi_bb176_33;
  TNode<BoolT> phi_bb176_37;
  TNode<IntPtrT> tmp389;
  TNode<IntPtrT> tmp390;
  TNode<BoolT> tmp391;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_20, &phi_bb176_25, &phi_bb176_26, &phi_bb176_27, &phi_bb176_28, &phi_bb176_29, &phi_bb176_32, &phi_bb176_33, &phi_bb176_37);
    tmp389 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp390 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb176_20}, TNode<IntPtrT>{tmp389});
    tmp391 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block155, tmp390, phi_bb176_25, phi_bb176_26, phi_bb176_27, phi_bb176_28, phi_bb176_29, phi_bb176_32, phi_bb176_33, tmp391);
  }

  TNode<IntPtrT> phi_bb155_20;
  TNode<IntPtrT> phi_bb155_25;
  TNode<IntPtrT> phi_bb155_26;
  TNode<IntPtrT> phi_bb155_27;
  TNode<IntPtrT> phi_bb155_28;
  TNode<IntPtrT> phi_bb155_29;
  TNode<IntPtrT> phi_bb155_32;
  TNode<BoolT> phi_bb155_33;
  TNode<BoolT> phi_bb155_37;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_20, &phi_bb155_25, &phi_bb155_26, &phi_bb155_27, &phi_bb155_28, &phi_bb155_29, &phi_bb155_32, &phi_bb155_33, &phi_bb155_37);
    ca_.Goto(&block106, phi_bb155_20, phi_bb155_25, phi_bb155_26, phi_bb155_27, phi_bb155_28, phi_bb155_29, phi_bb155_32, phi_bb155_33, phi_bb155_37);
  }

  TNode<IntPtrT> phi_bb106_20;
  TNode<IntPtrT> phi_bb106_25;
  TNode<IntPtrT> phi_bb106_26;
  TNode<IntPtrT> phi_bb106_27;
  TNode<IntPtrT> phi_bb106_28;
  TNode<IntPtrT> phi_bb106_29;
  TNode<IntPtrT> phi_bb106_32;
  TNode<BoolT> phi_bb106_33;
  TNode<BoolT> phi_bb106_37;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_20, &phi_bb106_25, &phi_bb106_26, &phi_bb106_27, &phi_bb106_28, &phi_bb106_29, &phi_bb106_32, &phi_bb106_33, &phi_bb106_37);
    ca_.Goto(&block72, phi_bb106_20, phi_bb106_25, phi_bb106_26, phi_bb106_27, phi_bb106_28, phi_bb106_29, phi_bb106_32, phi_bb106_33, phi_bb106_37);
  }

  TNode<IntPtrT> phi_bb72_20;
  TNode<IntPtrT> phi_bb72_25;
  TNode<IntPtrT> phi_bb72_26;
  TNode<IntPtrT> phi_bb72_27;
  TNode<IntPtrT> phi_bb72_28;
  TNode<IntPtrT> phi_bb72_29;
  TNode<IntPtrT> phi_bb72_32;
  TNode<BoolT> phi_bb72_33;
  TNode<BoolT> phi_bb72_37;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_20, &phi_bb72_25, &phi_bb72_26, &phi_bb72_27, &phi_bb72_28, &phi_bb72_29, &phi_bb72_32, &phi_bb72_33, &phi_bb72_37);
    ca_.Goto(&block49, phi_bb72_20, phi_bb72_25, phi_bb72_26, phi_bb72_27, phi_bb72_28, phi_bb72_29, phi_bb72_32, phi_bb72_33, phi_bb72_37);
  }

  TNode<IntPtrT> phi_bb49_20;
  TNode<IntPtrT> phi_bb49_25;
  TNode<IntPtrT> phi_bb49_26;
  TNode<IntPtrT> phi_bb49_27;
  TNode<IntPtrT> phi_bb49_28;
  TNode<IntPtrT> phi_bb49_29;
  TNode<IntPtrT> phi_bb49_32;
  TNode<BoolT> phi_bb49_33;
  TNode<BoolT> phi_bb49_37;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_20, &phi_bb49_25, &phi_bb49_26, &phi_bb49_27, &phi_bb49_28, &phi_bb49_29, &phi_bb49_32, &phi_bb49_33, &phi_bb49_37);
    ca_.Goto(&block40, phi_bb49_20, phi_bb49_25, phi_bb49_26, phi_bb49_27, phi_bb49_28, phi_bb49_29, phi_bb49_32, phi_bb49_33, tmp118, phi_bb49_37);
  }

  TNode<IntPtrT> phi_bb39_20;
  TNode<IntPtrT> phi_bb39_25;
  TNode<IntPtrT> phi_bb39_26;
  TNode<IntPtrT> phi_bb39_27;
  TNode<IntPtrT> phi_bb39_28;
  TNode<IntPtrT> phi_bb39_29;
  TNode<IntPtrT> phi_bb39_32;
  TNode<BoolT> phi_bb39_33;
  TNode<IntPtrT> phi_bb39_35;
  TNode<BoolT> phi_bb39_37;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_20, &phi_bb39_25, &phi_bb39_26, &phi_bb39_27, &phi_bb39_28, &phi_bb39_29, &phi_bb39_32, &phi_bb39_33, &phi_bb39_35, &phi_bb39_37);
    ca_.Branch(phi_bb39_37, &block178, std::vector<compiler::Node*>{phi_bb39_20, phi_bb39_25, phi_bb39_26, phi_bb39_27, phi_bb39_28, phi_bb39_29, phi_bb39_32, phi_bb39_33, phi_bb39_35, phi_bb39_37}, &block179, std::vector<compiler::Node*>{phi_bb39_20, phi_bb39_25, phi_bb39_26, phi_bb39_27, phi_bb39_28, phi_bb39_29, phi_bb39_32, phi_bb39_33, phi_bb39_35, tmp109, phi_bb39_37});
  }

  TNode<IntPtrT> phi_bb178_20;
  TNode<IntPtrT> phi_bb178_25;
  TNode<IntPtrT> phi_bb178_26;
  TNode<IntPtrT> phi_bb178_27;
  TNode<IntPtrT> phi_bb178_28;
  TNode<IntPtrT> phi_bb178_29;
  TNode<IntPtrT> phi_bb178_32;
  TNode<BoolT> phi_bb178_33;
  TNode<IntPtrT> phi_bb178_35;
  TNode<BoolT> phi_bb178_37;
  TNode<BoolT> tmp392;
  if (block178.is_used()) {
    ca_.Bind(&block178, &phi_bb178_20, &phi_bb178_25, &phi_bb178_26, &phi_bb178_27, &phi_bb178_28, &phi_bb178_29, &phi_bb178_32, &phi_bb178_33, &phi_bb178_35, &phi_bb178_37);
    tmp392 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb178_33});
    ca_.Branch(tmp392, &block181, std::vector<compiler::Node*>{phi_bb178_20, phi_bb178_25, phi_bb178_26, phi_bb178_27, phi_bb178_28, phi_bb178_29, phi_bb178_32, phi_bb178_33, phi_bb178_35, phi_bb178_37}, &block182, std::vector<compiler::Node*>{phi_bb178_20, phi_bb178_25, phi_bb178_26, phi_bb178_27, phi_bb178_28, phi_bb178_29, phi_bb178_32, phi_bb178_33, phi_bb178_35, phi_bb178_37});
  }

  TNode<IntPtrT> phi_bb181_20;
  TNode<IntPtrT> phi_bb181_25;
  TNode<IntPtrT> phi_bb181_26;
  TNode<IntPtrT> phi_bb181_27;
  TNode<IntPtrT> phi_bb181_28;
  TNode<IntPtrT> phi_bb181_29;
  TNode<IntPtrT> phi_bb181_32;
  TNode<BoolT> phi_bb181_33;
  TNode<IntPtrT> phi_bb181_35;
  TNode<BoolT> phi_bb181_37;
  TNode<IntPtrT> tmp393;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_20, &phi_bb181_25, &phi_bb181_26, &phi_bb181_27, &phi_bb181_28, &phi_bb181_29, &phi_bb181_32, &phi_bb181_33, &phi_bb181_35, &phi_bb181_37);
    tmp393 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block182, phi_bb181_20, phi_bb181_25, phi_bb181_26, phi_bb181_27, phi_bb181_28, phi_bb181_29, tmp393, phi_bb181_33, phi_bb181_35, phi_bb181_37);
  }

  TNode<IntPtrT> phi_bb182_20;
  TNode<IntPtrT> phi_bb182_25;
  TNode<IntPtrT> phi_bb182_26;
  TNode<IntPtrT> phi_bb182_27;
  TNode<IntPtrT> phi_bb182_28;
  TNode<IntPtrT> phi_bb182_29;
  TNode<IntPtrT> phi_bb182_32;
  TNode<BoolT> phi_bb182_33;
  TNode<IntPtrT> phi_bb182_35;
  TNode<BoolT> phi_bb182_37;
  TNode<IntPtrT> tmp394;
  TNode<IntPtrT> tmp395;
  TNode<IntPtrT> tmp396;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_20, &phi_bb182_25, &phi_bb182_26, &phi_bb182_27, &phi_bb182_28, &phi_bb182_29, &phi_bb182_32, &phi_bb182_33, &phi_bb182_35, &phi_bb182_37);
    tmp394 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp395 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{tmp69});
    tmp396 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp68}, TNode<IntPtrT>{tmp395});
    ca_.Goto(&block186, tmp394, phi_bb182_25, phi_bb182_26, phi_bb182_27, phi_bb182_28, phi_bb182_29, phi_bb182_32, phi_bb182_33, tmp68, phi_bb182_37);
  }

  TNode<IntPtrT> phi_bb186_20;
  TNode<IntPtrT> phi_bb186_25;
  TNode<IntPtrT> phi_bb186_26;
  TNode<IntPtrT> phi_bb186_27;
  TNode<IntPtrT> phi_bb186_28;
  TNode<IntPtrT> phi_bb186_29;
  TNode<IntPtrT> phi_bb186_32;
  TNode<BoolT> phi_bb186_33;
  TNode<IntPtrT> phi_bb186_35;
  TNode<BoolT> phi_bb186_37;
  TNode<BoolT> tmp397;
  TNode<BoolT> tmp398;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_20, &phi_bb186_25, &phi_bb186_26, &phi_bb186_27, &phi_bb186_28, &phi_bb186_29, &phi_bb186_32, &phi_bb186_33, &phi_bb186_35, &phi_bb186_37);
    tmp397 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb186_35}, TNode<IntPtrT>{tmp396});
    tmp398 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp397});
    ca_.Branch(tmp398, &block184, std::vector<compiler::Node*>{phi_bb186_20, phi_bb186_25, phi_bb186_26, phi_bb186_27, phi_bb186_28, phi_bb186_29, phi_bb186_32, phi_bb186_33, phi_bb186_35, phi_bb186_37}, &block185, std::vector<compiler::Node*>{phi_bb186_20, phi_bb186_25, phi_bb186_26, phi_bb186_27, phi_bb186_28, phi_bb186_29, phi_bb186_32, phi_bb186_33, phi_bb186_35, phi_bb186_37});
  }

  TNode<IntPtrT> phi_bb184_20;
  TNode<IntPtrT> phi_bb184_25;
  TNode<IntPtrT> phi_bb184_26;
  TNode<IntPtrT> phi_bb184_27;
  TNode<IntPtrT> phi_bb184_28;
  TNode<IntPtrT> phi_bb184_29;
  TNode<IntPtrT> phi_bb184_32;
  TNode<BoolT> phi_bb184_33;
  TNode<IntPtrT> phi_bb184_35;
  TNode<BoolT> phi_bb184_37;
  TNode<BoolT> tmp399;
  TNode<BoolT> tmp400;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_20, &phi_bb184_25, &phi_bb184_26, &phi_bb184_27, &phi_bb184_28, &phi_bb184_29, &phi_bb184_32, &phi_bb184_33, &phi_bb184_35, &phi_bb184_37);
    tmp399 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb184_35}, TNode<IntPtrT>{tmp396});
    tmp400 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp399});
    ca_.Branch(tmp400, &block190, std::vector<compiler::Node*>{phi_bb184_20, phi_bb184_25, phi_bb184_26, phi_bb184_27, phi_bb184_28, phi_bb184_29, phi_bb184_32, phi_bb184_33, phi_bb184_35, phi_bb184_37}, &block191, std::vector<compiler::Node*>{phi_bb184_20, phi_bb184_25, phi_bb184_26, phi_bb184_27, phi_bb184_28, phi_bb184_29, phi_bb184_32, phi_bb184_33, phi_bb184_35, phi_bb184_37});
  }

  TNode<IntPtrT> phi_bb191_20;
  TNode<IntPtrT> phi_bb191_25;
  TNode<IntPtrT> phi_bb191_26;
  TNode<IntPtrT> phi_bb191_27;
  TNode<IntPtrT> phi_bb191_28;
  TNode<IntPtrT> phi_bb191_29;
  TNode<IntPtrT> phi_bb191_32;
  TNode<BoolT> phi_bb191_33;
  TNode<IntPtrT> phi_bb191_35;
  TNode<BoolT> phi_bb191_37;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_20, &phi_bb191_25, &phi_bb191_26, &phi_bb191_27, &phi_bb191_28, &phi_bb191_29, &phi_bb191_32, &phi_bb191_33, &phi_bb191_35, &phi_bb191_37);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/torque-internal.tq", 245});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.Empty()' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb190_20;
  TNode<IntPtrT> phi_bb190_25;
  TNode<IntPtrT> phi_bb190_26;
  TNode<IntPtrT> phi_bb190_27;
  TNode<IntPtrT> phi_bb190_28;
  TNode<IntPtrT> phi_bb190_29;
  TNode<IntPtrT> phi_bb190_32;
  TNode<BoolT> phi_bb190_33;
  TNode<IntPtrT> phi_bb190_35;
  TNode<BoolT> phi_bb190_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp401;
  TNode<IntPtrT> tmp402;
  TNode<IntPtrT> tmp403;
  TNode<IntPtrT> tmp404;
  TNode<Uint32T> tmp405;
  TNode<Uint32T> tmp406;
  TNode<Uint32T> tmp407;
  TNode<Uint32T> tmp408;
  TNode<BoolT> tmp409;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_20, &phi_bb190_25, &phi_bb190_26, &phi_bb190_27, &phi_bb190_28, &phi_bb190_29, &phi_bb190_32, &phi_bb190_33, &phi_bb190_35, &phi_bb190_37);
    std::tie(tmp401, tmp402) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp67}, TNode<IntPtrT>{phi_bb190_35}).Flatten();
    tmp403 = FromConstexpr_intptr_constexpr_int31_0(state_, kInt32Size);
    tmp404 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb190_35}, TNode<IntPtrT>{tmp403});
    tmp405 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp401, tmp402});
    tmp406 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp407 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp405}, TNode<Uint32T>{tmp406});
    tmp408 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp409 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp407}, TNode<Uint32T>{tmp408});
    ca_.Branch(tmp409, &block193, std::vector<compiler::Node*>{phi_bb190_20, phi_bb190_25, phi_bb190_26, phi_bb190_27, phi_bb190_28, phi_bb190_29, phi_bb190_32, phi_bb190_33, phi_bb190_37}, &block194, std::vector<compiler::Node*>{phi_bb190_20, phi_bb190_25, phi_bb190_26, phi_bb190_27, phi_bb190_28, phi_bb190_29, phi_bb190_32, phi_bb190_33, phi_bb190_37});
  }

  TNode<IntPtrT> phi_bb193_20;
  TNode<IntPtrT> phi_bb193_25;
  TNode<IntPtrT> phi_bb193_26;
  TNode<IntPtrT> phi_bb193_27;
  TNode<IntPtrT> phi_bb193_28;
  TNode<IntPtrT> phi_bb193_29;
  TNode<IntPtrT> phi_bb193_32;
  TNode<BoolT> phi_bb193_33;
  TNode<BoolT> phi_bb193_37;
  TNode<IntPtrT> tmp410;
  TNode<IntPtrT> tmp411;
  TNode<IntPtrT> tmp412;
  TNode<BoolT> tmp413;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_20, &phi_bb193_25, &phi_bb193_26, &phi_bb193_27, &phi_bb193_28, &phi_bb193_29, &phi_bb193_32, &phi_bb193_33, &phi_bb193_37);
    tmp410 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp411 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb193_25}, TNode<IntPtrT>{tmp410});
    tmp412 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp413 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb193_25}, TNode<IntPtrT>{tmp412});
    ca_.Branch(tmp413, &block196, std::vector<compiler::Node*>{phi_bb193_20, phi_bb193_26, phi_bb193_27, phi_bb193_28, phi_bb193_29, phi_bb193_32, phi_bb193_33, phi_bb193_37}, &block197, std::vector<compiler::Node*>{phi_bb193_20, phi_bb193_26, phi_bb193_27, phi_bb193_28, phi_bb193_29, phi_bb193_32, phi_bb193_33, phi_bb193_37});
  }

  TNode<IntPtrT> phi_bb196_20;
  TNode<IntPtrT> phi_bb196_26;
  TNode<IntPtrT> phi_bb196_27;
  TNode<IntPtrT> phi_bb196_28;
  TNode<IntPtrT> phi_bb196_29;
  TNode<IntPtrT> phi_bb196_32;
  TNode<BoolT> phi_bb196_33;
  TNode<BoolT> phi_bb196_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp414;
  TNode<IntPtrT> tmp415;
  TNode<IntPtrT> tmp416;
  TNode<IntPtrT> tmp417;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_20, &phi_bb196_26, &phi_bb196_27, &phi_bb196_28, &phi_bb196_29, &phi_bb196_32, &phi_bb196_33, &phi_bb196_37);
    std::tie(tmp414, tmp415) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb196_27}).Flatten();
    tmp416 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp417 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb196_27}, TNode<IntPtrT>{tmp416});
    ca_.Goto(&block195, phi_bb196_20, phi_bb196_26, tmp417, phi_bb196_28, phi_bb196_29, phi_bb196_32, phi_bb196_33, phi_bb196_37, tmp414, tmp415);
  }

  TNode<IntPtrT> phi_bb197_20;
  TNode<IntPtrT> phi_bb197_26;
  TNode<IntPtrT> phi_bb197_27;
  TNode<IntPtrT> phi_bb197_28;
  TNode<IntPtrT> phi_bb197_29;
  TNode<IntPtrT> phi_bb197_32;
  TNode<BoolT> phi_bb197_33;
  TNode<BoolT> phi_bb197_37;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_20, &phi_bb197_26, &phi_bb197_27, &phi_bb197_28, &phi_bb197_29, &phi_bb197_32, &phi_bb197_33, &phi_bb197_37);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block199, phi_bb197_20, phi_bb197_26, phi_bb197_27, phi_bb197_28, phi_bb197_29, phi_bb197_32, phi_bb197_33, phi_bb197_37);
    } else {
      ca_.Goto(&block200, phi_bb197_20, phi_bb197_26, phi_bb197_27, phi_bb197_28, phi_bb197_29, phi_bb197_32, phi_bb197_33, phi_bb197_37);
    }
  }

  TNode<IntPtrT> phi_bb199_20;
  TNode<IntPtrT> phi_bb199_26;
  TNode<IntPtrT> phi_bb199_27;
  TNode<IntPtrT> phi_bb199_28;
  TNode<IntPtrT> phi_bb199_29;
  TNode<IntPtrT> phi_bb199_32;
  TNode<BoolT> phi_bb199_33;
  TNode<BoolT> phi_bb199_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp418;
  TNode<IntPtrT> tmp419;
  TNode<IntPtrT> tmp420;
  TNode<IntPtrT> tmp421;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_20, &phi_bb199_26, &phi_bb199_27, &phi_bb199_28, &phi_bb199_29, &phi_bb199_32, &phi_bb199_33, &phi_bb199_37);
    std::tie(tmp418, tmp419) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb199_29}).Flatten();
    tmp420 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp421 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb199_29}, TNode<IntPtrT>{tmp420});
    ca_.Goto(&block198, phi_bb199_20, phi_bb199_26, phi_bb199_27, phi_bb199_28, tmp421, phi_bb199_32, phi_bb199_33, phi_bb199_37, tmp418, tmp419);
  }

  TNode<IntPtrT> phi_bb200_20;
  TNode<IntPtrT> phi_bb200_26;
  TNode<IntPtrT> phi_bb200_27;
  TNode<IntPtrT> phi_bb200_28;
  TNode<IntPtrT> phi_bb200_29;
  TNode<IntPtrT> phi_bb200_32;
  TNode<BoolT> phi_bb200_33;
  TNode<BoolT> phi_bb200_37;
  TNode<IntPtrT> tmp422;
  TNode<BoolT> tmp423;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_20, &phi_bb200_26, &phi_bb200_27, &phi_bb200_28, &phi_bb200_29, &phi_bb200_32, &phi_bb200_33, &phi_bb200_37);
    tmp422 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp423 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb200_32}, TNode<IntPtrT>{tmp422});
    ca_.Branch(tmp423, &block202, std::vector<compiler::Node*>{phi_bb200_20, phi_bb200_26, phi_bb200_27, phi_bb200_28, phi_bb200_29, phi_bb200_32, phi_bb200_33, phi_bb200_37}, &block203, std::vector<compiler::Node*>{phi_bb200_20, phi_bb200_26, phi_bb200_27, phi_bb200_28, phi_bb200_29, phi_bb200_32, phi_bb200_33, phi_bb200_37});
  }

  TNode<IntPtrT> phi_bb202_20;
  TNode<IntPtrT> phi_bb202_26;
  TNode<IntPtrT> phi_bb202_27;
  TNode<IntPtrT> phi_bb202_28;
  TNode<IntPtrT> phi_bb202_29;
  TNode<IntPtrT> phi_bb202_32;
  TNode<BoolT> phi_bb202_33;
  TNode<BoolT> phi_bb202_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp424;
  TNode<IntPtrT> tmp425;
  TNode<IntPtrT> tmp426;
  TNode<BoolT> tmp427;
  if (block202.is_used()) {
    ca_.Bind(&block202, &phi_bb202_20, &phi_bb202_26, &phi_bb202_27, &phi_bb202_28, &phi_bb202_29, &phi_bb202_32, &phi_bb202_33, &phi_bb202_37);
    std::tie(tmp424, tmp425) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb202_32}).Flatten();
    tmp426 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp427 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block198, phi_bb202_20, phi_bb202_26, phi_bb202_27, phi_bb202_28, phi_bb202_29, tmp426, tmp427, phi_bb202_37, tmp424, tmp425);
  }

  TNode<IntPtrT> phi_bb203_20;
  TNode<IntPtrT> phi_bb203_26;
  TNode<IntPtrT> phi_bb203_27;
  TNode<IntPtrT> phi_bb203_28;
  TNode<IntPtrT> phi_bb203_29;
  TNode<IntPtrT> phi_bb203_32;
  TNode<BoolT> phi_bb203_33;
  TNode<BoolT> phi_bb203_37;
  TNode<Union<HeapObject, TaggedIndex>> tmp428;
  TNode<IntPtrT> tmp429;
  TNode<IntPtrT> tmp430;
  TNode<IntPtrT> tmp431;
  TNode<IntPtrT> tmp432;
  TNode<IntPtrT> tmp433;
  TNode<BoolT> tmp434;
  if (block203.is_used()) {
    ca_.Bind(&block203, &phi_bb203_20, &phi_bb203_26, &phi_bb203_27, &phi_bb203_28, &phi_bb203_29, &phi_bb203_32, &phi_bb203_33, &phi_bb203_37);
    std::tie(tmp428, tmp429) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb203_29}).Flatten();
    tmp430 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp431 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb203_29}, TNode<IntPtrT>{tmp430});
    tmp432 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp433 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp431}, TNode<IntPtrT>{tmp432});
    tmp434 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block198, phi_bb203_20, phi_bb203_26, phi_bb203_27, phi_bb203_28, tmp433, tmp431, tmp434, phi_bb203_37, tmp428, tmp429);
  }

  TNode<IntPtrT> phi_bb198_20;
  TNode<IntPtrT> phi_bb198_26;
  TNode<IntPtrT> phi_bb198_27;
  TNode<IntPtrT> phi_bb198_28;
  TNode<IntPtrT> phi_bb198_29;
  TNode<IntPtrT> phi_bb198_32;
  TNode<BoolT> phi_bb198_33;
  TNode<BoolT> phi_bb198_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb198_39;
  TNode<IntPtrT> phi_bb198_40;
  if (block198.is_used()) {
    ca_.Bind(&block198, &phi_bb198_20, &phi_bb198_26, &phi_bb198_27, &phi_bb198_28, &phi_bb198_29, &phi_bb198_32, &phi_bb198_33, &phi_bb198_37, &phi_bb198_39, &phi_bb198_40);
    ca_.Goto(&block195, phi_bb198_20, phi_bb198_26, phi_bb198_27, phi_bb198_28, phi_bb198_29, phi_bb198_32, phi_bb198_33, phi_bb198_37, phi_bb198_39, phi_bb198_40);
  }

  TNode<IntPtrT> phi_bb195_20;
  TNode<IntPtrT> phi_bb195_26;
  TNode<IntPtrT> phi_bb195_27;
  TNode<IntPtrT> phi_bb195_28;
  TNode<IntPtrT> phi_bb195_29;
  TNode<IntPtrT> phi_bb195_32;
  TNode<BoolT> phi_bb195_33;
  TNode<BoolT> phi_bb195_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb195_39;
  TNode<IntPtrT> phi_bb195_40;
  TNode<IntPtrT> tmp435;
  TNode<Object> tmp436;
  TNode<Union<HeapObject, TaggedIndex>> tmp437;
  TNode<IntPtrT> tmp438;
  TNode<IntPtrT> tmp439;
  TNode<UintPtrT> tmp440;
  TNode<UintPtrT> tmp441;
  TNode<BoolT> tmp442;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_20, &phi_bb195_26, &phi_bb195_27, &phi_bb195_28, &phi_bb195_29, &phi_bb195_32, &phi_bb195_33, &phi_bb195_37, &phi_bb195_39, &phi_bb195_40);
    tmp435 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb195_39, phi_bb195_40});
    tmp436 = CodeStubAssembler(state_).BitcastWordToTagged(TNode<IntPtrT>{tmp435});
    std::tie(tmp437, tmp438, tmp439) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp73}).Flatten();
    tmp440 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb195_20});
    tmp441 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp439});
    tmp442 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp440}, TNode<UintPtrT>{tmp441});
    ca_.Branch(tmp442, &block208, std::vector<compiler::Node*>{phi_bb195_20, phi_bb195_26, phi_bb195_27, phi_bb195_28, phi_bb195_29, phi_bb195_32, phi_bb195_33, phi_bb195_37, phi_bb195_39, phi_bb195_40, phi_bb195_20, phi_bb195_20, phi_bb195_20, phi_bb195_20}, &block209, std::vector<compiler::Node*>{phi_bb195_20, phi_bb195_26, phi_bb195_27, phi_bb195_28, phi_bb195_29, phi_bb195_32, phi_bb195_33, phi_bb195_37, phi_bb195_39, phi_bb195_40, phi_bb195_20, phi_bb195_20, phi_bb195_20, phi_bb195_20});
  }

  TNode<IntPtrT> phi_bb208_20;
  TNode<IntPtrT> phi_bb208_26;
  TNode<IntPtrT> phi_bb208_27;
  TNode<IntPtrT> phi_bb208_28;
  TNode<IntPtrT> phi_bb208_29;
  TNode<IntPtrT> phi_bb208_32;
  TNode<BoolT> phi_bb208_33;
  TNode<BoolT> phi_bb208_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb208_39;
  TNode<IntPtrT> phi_bb208_40;
  TNode<IntPtrT> phi_bb208_47;
  TNode<IntPtrT> phi_bb208_48;
  TNode<IntPtrT> phi_bb208_52;
  TNode<IntPtrT> phi_bb208_53;
  TNode<IntPtrT> tmp443;
  TNode<IntPtrT> tmp444;
  TNode<Union<HeapObject, TaggedIndex>> tmp445;
  TNode<IntPtrT> tmp446;
  TNode<IntPtrT> tmp447;
  TNode<NativeContext> tmp448;
  TNode<JSAny> tmp449;
  if (block208.is_used()) {
    ca_.Bind(&block208, &phi_bb208_20, &phi_bb208_26, &phi_bb208_27, &phi_bb208_28, &phi_bb208_29, &phi_bb208_32, &phi_bb208_33, &phi_bb208_37, &phi_bb208_39, &phi_bb208_40, &phi_bb208_47, &phi_bb208_48, &phi_bb208_52, &phi_bb208_53);
    tmp443 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb208_53});
    tmp444 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp438}, TNode<IntPtrT>{tmp443});
    std::tie(tmp445, tmp446) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp437}, TNode<IntPtrT>{tmp444}).Flatten();
    tmp447 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp448 = CodeStubAssembler(state_).LoadReference<NativeContext>(CodeStubAssembler::Reference{p_data, tmp447});
    tmp449 = WasmToJSObject_0(state_, TNode<NativeContext>{tmp448}, TNode<Object>{tmp436});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp445, tmp446}, tmp449);
    ca_.Goto(&block194, phi_bb208_20, tmp411, phi_bb208_26, phi_bb208_27, phi_bb208_28, phi_bb208_29, phi_bb208_32, phi_bb208_33, phi_bb208_37);
  }

  TNode<IntPtrT> phi_bb209_20;
  TNode<IntPtrT> phi_bb209_26;
  TNode<IntPtrT> phi_bb209_27;
  TNode<IntPtrT> phi_bb209_28;
  TNode<IntPtrT> phi_bb209_29;
  TNode<IntPtrT> phi_bb209_32;
  TNode<BoolT> phi_bb209_33;
  TNode<BoolT> phi_bb209_37;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb209_39;
  TNode<IntPtrT> phi_bb209_40;
  TNode<IntPtrT> phi_bb209_47;
  TNode<IntPtrT> phi_bb209_48;
  TNode<IntPtrT> phi_bb209_52;
  TNode<IntPtrT> phi_bb209_53;
  if (block209.is_used()) {
    ca_.Bind(&block209, &phi_bb209_20, &phi_bb209_26, &phi_bb209_27, &phi_bb209_28, &phi_bb209_29, &phi_bb209_32, &phi_bb209_33, &phi_bb209_37, &phi_bb209_39, &phi_bb209_40, &phi_bb209_47, &phi_bb209_48, &phi_bb209_52, &phi_bb209_53);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb194_20;
  TNode<IntPtrT> phi_bb194_25;
  TNode<IntPtrT> phi_bb194_26;
  TNode<IntPtrT> phi_bb194_27;
  TNode<IntPtrT> phi_bb194_28;
  TNode<IntPtrT> phi_bb194_29;
  TNode<IntPtrT> phi_bb194_32;
  TNode<BoolT> phi_bb194_33;
  TNode<BoolT> phi_bb194_37;
  TNode<IntPtrT> tmp450;
  TNode<IntPtrT> tmp451;
  if (block194.is_used()) {
    ca_.Bind(&block194, &phi_bb194_20, &phi_bb194_25, &phi_bb194_26, &phi_bb194_27, &phi_bb194_28, &phi_bb194_29, &phi_bb194_32, &phi_bb194_33, &phi_bb194_37);
    tmp450 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp451 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb194_20}, TNode<IntPtrT>{tmp450});
    ca_.Goto(&block186, tmp451, phi_bb194_25, phi_bb194_26, phi_bb194_27, phi_bb194_28, phi_bb194_29, phi_bb194_32, phi_bb194_33, tmp404, phi_bb194_37);
  }

  TNode<IntPtrT> phi_bb185_20;
  TNode<IntPtrT> phi_bb185_25;
  TNode<IntPtrT> phi_bb185_26;
  TNode<IntPtrT> phi_bb185_27;
  TNode<IntPtrT> phi_bb185_28;
  TNode<IntPtrT> phi_bb185_29;
  TNode<IntPtrT> phi_bb185_32;
  TNode<BoolT> phi_bb185_33;
  TNode<IntPtrT> phi_bb185_35;
  TNode<BoolT> phi_bb185_37;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_20, &phi_bb185_25, &phi_bb185_26, &phi_bb185_27, &phi_bb185_28, &phi_bb185_29, &phi_bb185_32, &phi_bb185_33, &phi_bb185_35, &phi_bb185_37);
    ca_.Goto(&block179, phi_bb185_20, phi_bb185_25, phi_bb185_26, phi_bb185_27, phi_bb185_28, phi_bb185_29, phi_bb185_32, phi_bb185_33, phi_bb185_35, tmp396, phi_bb185_37);
  }

  TNode<IntPtrT> phi_bb179_20;
  TNode<IntPtrT> phi_bb179_25;
  TNode<IntPtrT> phi_bb179_26;
  TNode<IntPtrT> phi_bb179_27;
  TNode<IntPtrT> phi_bb179_28;
  TNode<IntPtrT> phi_bb179_29;
  TNode<IntPtrT> phi_bb179_32;
  TNode<BoolT> phi_bb179_33;
  TNode<IntPtrT> phi_bb179_35;
  TNode<IntPtrT> phi_bb179_36;
  TNode<BoolT> phi_bb179_37;
  TNode<IntPtrT> tmp452;
  TNode<Union<JSReceiver, Undefined>> tmp453;
  TNode<IntPtrT> tmp454;
  TNode<NativeContext> tmp455;
  TNode<IntPtrT> tmp456;
  TNode<Union<HeapObject, TaggedIndex>> tmp457;
  TNode<IntPtrT> tmp458;
  TNode<IntPtrT> tmp459;
  TNode<Int32T> tmp460;
  TNode<Int32T> tmp461;
  TNode<JSAny> tmp462;
  TNode<IntPtrT> tmp463;
  TNode<Union<HeapObject, TaggedIndex>> tmp464;
  TNode<IntPtrT> tmp465;
  TNode<IntPtrT> tmp466;
  TNode<IntPtrT> tmp467;
  TNode<BoolT> tmp468;
  if (block179.is_used()) {
    ca_.Bind(&block179, &phi_bb179_20, &phi_bb179_25, &phi_bb179_26, &phi_bb179_27, &phi_bb179_28, &phi_bb179_29, &phi_bb179_32, &phi_bb179_33, &phi_bb179_35, &phi_bb179_36, &phi_bb179_37);
    tmp452 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp453 = CodeStubAssembler(state_).LoadReference<Union<JSReceiver, Undefined>>(CodeStubAssembler::Reference{p_data, tmp452});
    tmp454 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp455 = CodeStubAssembler(state_).LoadReference<NativeContext>(CodeStubAssembler::Reference{p_data, tmp454});
    tmp456 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp457, tmp458) = GetRefAt_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp7}, TNode<IntPtrT>{tmp456}).Flatten();
    tmp459 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{tmp457, tmp458}, tmp459);
    tmp460 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{tmp72});
    tmp461 = FromConstexpr_int32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp462 = ca_.CallBuiltin<JSAny>(Builtin::kCallVarargs, tmp455, tmp453, tmp461, tmp460, tmp73);
    tmp463 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp464, tmp465) = GetRefAt_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp7}, TNode<IntPtrT>{tmp463}).Flatten();
    tmp466 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{tmp464, tmp465}, tmp466);
    tmp467 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp468 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp41}, TNode<IntPtrT>{tmp467});
    ca_.Branch(tmp468, &block212, std::vector<compiler::Node*>{phi_bb179_20, phi_bb179_25, phi_bb179_26, phi_bb179_27, phi_bb179_28, phi_bb179_29, phi_bb179_32, phi_bb179_33, phi_bb179_35, phi_bb179_36, phi_bb179_37}, &block213, std::vector<compiler::Node*>{phi_bb179_20, phi_bb179_25, phi_bb179_26, phi_bb179_27, phi_bb179_28, phi_bb179_29, phi_bb179_32, phi_bb179_33, phi_bb179_35, phi_bb179_36, phi_bb179_37});
  }

  TNode<IntPtrT> phi_bb212_20;
  TNode<IntPtrT> phi_bb212_25;
  TNode<IntPtrT> phi_bb212_26;
  TNode<IntPtrT> phi_bb212_27;
  TNode<IntPtrT> phi_bb212_28;
  TNode<IntPtrT> phi_bb212_29;
  TNode<IntPtrT> phi_bb212_32;
  TNode<BoolT> phi_bb212_33;
  TNode<IntPtrT> phi_bb212_35;
  TNode<IntPtrT> phi_bb212_36;
  TNode<BoolT> phi_bb212_37;
  TNode<Smi> tmp469;
  TNode<FixedArray> tmp470;
  if (block212.is_used()) {
    ca_.Bind(&block212, &phi_bb212_20, &phi_bb212_25, &phi_bb212_26, &phi_bb212_27, &phi_bb212_28, &phi_bb212_29, &phi_bb212_32, &phi_bb212_33, &phi_bb212_35, &phi_bb212_36, &phi_bb212_37);
    tmp469 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{tmp41});
    tmp470 = ca_.CallBuiltin<FixedArray>(Builtin::kIterableToFixedArrayForWasm, tmp455, tmp462, tmp469);
    ca_.Goto(&block214, phi_bb212_20, phi_bb212_25, phi_bb212_26, phi_bb212_27, phi_bb212_28, phi_bb212_29, phi_bb212_32, phi_bb212_33, phi_bb212_35, phi_bb212_36, phi_bb212_37, tmp470);
  }

  TNode<IntPtrT> phi_bb213_20;
  TNode<IntPtrT> phi_bb213_25;
  TNode<IntPtrT> phi_bb213_26;
  TNode<IntPtrT> phi_bb213_27;
  TNode<IntPtrT> phi_bb213_28;
  TNode<IntPtrT> phi_bb213_29;
  TNode<IntPtrT> phi_bb213_32;
  TNode<BoolT> phi_bb213_33;
  TNode<IntPtrT> phi_bb213_35;
  TNode<IntPtrT> phi_bb213_36;
  TNode<BoolT> phi_bb213_37;
  TNode<FixedArray> tmp471;
  if (block213.is_used()) {
    ca_.Bind(&block213, &phi_bb213_20, &phi_bb213_25, &phi_bb213_26, &phi_bb213_27, &phi_bb213_28, &phi_bb213_29, &phi_bb213_32, &phi_bb213_33, &phi_bb213_35, &phi_bb213_36, &phi_bb213_37);
    tmp471 = kEmptyFixedArray_0(state_);
    ca_.Goto(&block214, phi_bb213_20, phi_bb213_25, phi_bb213_26, phi_bb213_27, phi_bb213_28, phi_bb213_29, phi_bb213_32, phi_bb213_33, phi_bb213_35, phi_bb213_36, phi_bb213_37, tmp471);
  }

  TNode<IntPtrT> phi_bb214_20;
  TNode<IntPtrT> phi_bb214_25;
  TNode<IntPtrT> phi_bb214_26;
  TNode<IntPtrT> phi_bb214_27;
  TNode<IntPtrT> phi_bb214_28;
  TNode<IntPtrT> phi_bb214_29;
  TNode<IntPtrT> phi_bb214_32;
  TNode<BoolT> phi_bb214_33;
  TNode<IntPtrT> phi_bb214_35;
  TNode<IntPtrT> phi_bb214_36;
  TNode<BoolT> phi_bb214_37;
  TNode<FixedArray> phi_bb214_41;
  TNode<RawPtrT> tmp472;
  TNode<RawPtrT> tmp473;
  TNode<RawPtrT> tmp474;
  TNode<RawPtrT> tmp475;
  TNode<IntPtrT> tmp476;
  if (block214.is_used()) {
    ca_.Bind(&block214, &phi_bb214_20, &phi_bb214_25, &phi_bb214_26, &phi_bb214_27, &phi_bb214_28, &phi_bb214_29, &phi_bb214_32, &phi_bb214_33, &phi_bb214_35, &phi_bb214_36, &phi_bb214_37, &phi_bb214_41);
    tmp472 = CodeStubAssembler(state_).StackSlotPtr(CastIfEnumClass<int32_t>((CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_))))), CastIfEnumClass<int32_t>((SizeOf_intptr_0(state_))));
    tmp473 = (TNode<RawPtrT>{tmp472});
    tmp474 = CodeStubAssembler(state_).StackSlotPtr(CastIfEnumClass<int32_t>((CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_float64_0(state_))))), CastIfEnumClass<int32_t>((SizeOf_float64_0(state_))));
    tmp475 = (TNode<RawPtrT>{tmp474});
    tmp476 = CodeStubAssembler(state_).StackAlignmentInBytes();
    ca_.Branch(phi_bb214_33, &block216, std::vector<compiler::Node*>{phi_bb214_20, phi_bb214_25, phi_bb214_26, phi_bb214_27, phi_bb214_28, phi_bb214_29, phi_bb214_32, phi_bb214_33, phi_bb214_35, phi_bb214_36, phi_bb214_37, phi_bb214_29}, &block217, std::vector<compiler::Node*>{phi_bb214_20, phi_bb214_25, phi_bb214_26, phi_bb214_27, phi_bb214_28, phi_bb214_29, phi_bb214_32, phi_bb214_33, phi_bb214_35, phi_bb214_36, phi_bb214_37, phi_bb214_29});
  }

  TNode<IntPtrT> phi_bb216_20;
  TNode<IntPtrT> phi_bb216_25;
  TNode<IntPtrT> phi_bb216_26;
  TNode<IntPtrT> phi_bb216_27;
  TNode<IntPtrT> phi_bb216_28;
  TNode<IntPtrT> phi_bb216_29;
  TNode<IntPtrT> phi_bb216_32;
  TNode<BoolT> phi_bb216_33;
  TNode<IntPtrT> phi_bb216_35;
  TNode<IntPtrT> phi_bb216_36;
  TNode<BoolT> phi_bb216_37;
  TNode<IntPtrT> phi_bb216_46;
  TNode<IntPtrT> tmp477;
  TNode<IntPtrT> tmp478;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_20, &phi_bb216_25, &phi_bb216_26, &phi_bb216_27, &phi_bb216_28, &phi_bb216_29, &phi_bb216_32, &phi_bb216_33, &phi_bb216_35, &phi_bb216_36, &phi_bb216_37, &phi_bb216_46);
    tmp477 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp478 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb216_46}, TNode<IntPtrT>{tmp477});
    ca_.Goto(&block217, phi_bb216_20, phi_bb216_25, phi_bb216_26, phi_bb216_27, phi_bb216_28, phi_bb216_29, phi_bb216_32, phi_bb216_33, phi_bb216_35, phi_bb216_36, phi_bb216_37, tmp478);
  }

  TNode<IntPtrT> phi_bb217_20;
  TNode<IntPtrT> phi_bb217_25;
  TNode<IntPtrT> phi_bb217_26;
  TNode<IntPtrT> phi_bb217_27;
  TNode<IntPtrT> phi_bb217_28;
  TNode<IntPtrT> phi_bb217_29;
  TNode<IntPtrT> phi_bb217_32;
  TNode<BoolT> phi_bb217_33;
  TNode<IntPtrT> phi_bb217_35;
  TNode<IntPtrT> phi_bb217_36;
  TNode<BoolT> phi_bb217_37;
  TNode<IntPtrT> phi_bb217_46;
  TNode<IntPtrT> tmp479;
  TNode<IntPtrT> tmp480;
  TNode<IntPtrT> tmp481;
  TNode<BoolT> tmp482;
  if (block217.is_used()) {
    ca_.Bind(&block217, &phi_bb217_20, &phi_bb217_25, &phi_bb217_26, &phi_bb217_27, &phi_bb217_28, &phi_bb217_29, &phi_bb217_32, &phi_bb217_33, &phi_bb217_35, &phi_bb217_36, &phi_bb217_37, &phi_bb217_46);
    tmp479 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb217_46}, TNode<IntPtrT>{tmp104});
    tmp480 = CodeStubAssembler(state_).IntPtrMod(TNode<IntPtrT>{tmp479}, TNode<IntPtrT>{tmp476});
    tmp481 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp482 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp480}, TNode<IntPtrT>{tmp481});
    ca_.Branch(tmp482, &block218, std::vector<compiler::Node*>{phi_bb217_20, phi_bb217_25, phi_bb217_26, phi_bb217_27, phi_bb217_28, phi_bb217_29, phi_bb217_32, phi_bb217_33, phi_bb217_35, phi_bb217_36, phi_bb217_37}, &block219, std::vector<compiler::Node*>{phi_bb217_20, phi_bb217_25, phi_bb217_26, phi_bb217_27, phi_bb217_28, phi_bb217_29, phi_bb217_32, phi_bb217_33, phi_bb217_35, phi_bb217_36, phi_bb217_37, phi_bb217_46});
  }

  TNode<IntPtrT> phi_bb218_20;
  TNode<IntPtrT> phi_bb218_25;
  TNode<IntPtrT> phi_bb218_26;
  TNode<IntPtrT> phi_bb218_27;
  TNode<IntPtrT> phi_bb218_28;
  TNode<IntPtrT> phi_bb218_29;
  TNode<IntPtrT> phi_bb218_32;
  TNode<BoolT> phi_bb218_33;
  TNode<IntPtrT> phi_bb218_35;
  TNode<IntPtrT> phi_bb218_36;
  TNode<BoolT> phi_bb218_37;
  TNode<IntPtrT> tmp483;
  TNode<IntPtrT> tmp484;
  TNode<IntPtrT> tmp485;
  if (block218.is_used()) {
    ca_.Bind(&block218, &phi_bb218_20, &phi_bb218_25, &phi_bb218_26, &phi_bb218_27, &phi_bb218_28, &phi_bb218_29, &phi_bb218_32, &phi_bb218_33, &phi_bb218_35, &phi_bb218_36, &phi_bb218_37);
    tmp483 = CodeStubAssembler(state_).IntPtrMod(TNode<IntPtrT>{tmp479}, TNode<IntPtrT>{tmp476});
    tmp484 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp476}, TNode<IntPtrT>{tmp483});
    tmp485 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb217_46}, TNode<IntPtrT>{tmp484});
    ca_.Goto(&block219, phi_bb218_20, phi_bb218_25, phi_bb218_26, phi_bb218_27, phi_bb218_28, phi_bb218_29, phi_bb218_32, phi_bb218_33, phi_bb218_35, phi_bb218_36, phi_bb218_37, tmp485);
  }

  TNode<IntPtrT> phi_bb219_20;
  TNode<IntPtrT> phi_bb219_25;
  TNode<IntPtrT> phi_bb219_26;
  TNode<IntPtrT> phi_bb219_27;
  TNode<IntPtrT> phi_bb219_28;
  TNode<IntPtrT> phi_bb219_29;
  TNode<IntPtrT> phi_bb219_32;
  TNode<BoolT> phi_bb219_33;
  TNode<IntPtrT> phi_bb219_35;
  TNode<IntPtrT> phi_bb219_36;
  TNode<BoolT> phi_bb219_37;
  TNode<IntPtrT> phi_bb219_46;
  TNode<RawPtrT> tmp486;
  TNode<Union<HeapObject, TaggedIndex>> tmp487;
  TNode<IntPtrT> tmp488;
  TNode<IntPtrT> tmp489;
  TNode<IntPtrT> tmp490;
  TNode<IntPtrT> tmp491;
  TNode<IntPtrT> tmp492;
  TNode<IntPtrT> tmp493;
  TNode<IntPtrT> tmp494;
  TNode<IntPtrT> tmp495;
  TNode<BoolT> tmp496;
  TNode<IntPtrT> tmp497;
  TNode<IntPtrT> tmp498;
  TNode<IntPtrT> tmp499;
  TNode<BoolT> tmp500;
  if (block219.is_used()) {
    ca_.Bind(&block219, &phi_bb219_20, &phi_bb219_25, &phi_bb219_26, &phi_bb219_27, &phi_bb219_28, &phi_bb219_29, &phi_bb219_32, &phi_bb219_33, &phi_bb219_35, &phi_bb219_36, &phi_bb219_37, &phi_bb219_46);
    tmp486 = CodeStubAssembler(state_).GCUnsafeReferenceToRawPtr(TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{phi_bb219_46});
    std::tie(tmp487, tmp488, tmp489, tmp490, tmp491, tmp492, tmp493, tmp494, tmp495, tmp496) = LocationAllocatorForReturns_0(state_, TNode<RawPtrT>{tmp473}, TNode<RawPtrT>{tmp475}, TNode<RawPtrT>{tmp486}).Flatten();
    tmp497 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{tmp65});
    tmp498 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp64}, TNode<IntPtrT>{tmp497});
    tmp499 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp500 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block223, tmp499, tmp488, tmp489, tmp490, tmp491, tmp492, tmp495, tmp496, phi_bb219_35, phi_bb219_36, phi_bb219_37, tmp64, tmp500);
  }

  TNode<IntPtrT> phi_bb223_20;
  TNode<IntPtrT> phi_bb223_25;
  TNode<IntPtrT> phi_bb223_26;
  TNode<IntPtrT> phi_bb223_27;
  TNode<IntPtrT> phi_bb223_28;
  TNode<IntPtrT> phi_bb223_29;
  TNode<IntPtrT> phi_bb223_32;
  TNode<BoolT> phi_bb223_33;
  TNode<IntPtrT> phi_bb223_35;
  TNode<IntPtrT> phi_bb223_36;
  TNode<BoolT> phi_bb223_37;
  TNode<IntPtrT> phi_bb223_46;
  TNode<BoolT> phi_bb223_48;
  TNode<BoolT> tmp501;
  TNode<BoolT> tmp502;
  if (block223.is_used()) {
    ca_.Bind(&block223, &phi_bb223_20, &phi_bb223_25, &phi_bb223_26, &phi_bb223_27, &phi_bb223_28, &phi_bb223_29, &phi_bb223_32, &phi_bb223_33, &phi_bb223_35, &phi_bb223_36, &phi_bb223_37, &phi_bb223_46, &phi_bb223_48);
    tmp501 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb223_46}, TNode<IntPtrT>{tmp498});
    tmp502 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp501});
    ca_.Branch(tmp502, &block221, std::vector<compiler::Node*>{phi_bb223_20, phi_bb223_25, phi_bb223_26, phi_bb223_27, phi_bb223_28, phi_bb223_29, phi_bb223_32, phi_bb223_33, phi_bb223_35, phi_bb223_36, phi_bb223_37, phi_bb223_46, phi_bb223_48}, &block222, std::vector<compiler::Node*>{phi_bb223_20, phi_bb223_25, phi_bb223_26, phi_bb223_27, phi_bb223_28, phi_bb223_29, phi_bb223_32, phi_bb223_33, phi_bb223_35, phi_bb223_36, phi_bb223_37, phi_bb223_46, phi_bb223_48});
  }

  TNode<IntPtrT> phi_bb221_20;
  TNode<IntPtrT> phi_bb221_25;
  TNode<IntPtrT> phi_bb221_26;
  TNode<IntPtrT> phi_bb221_27;
  TNode<IntPtrT> phi_bb221_28;
  TNode<IntPtrT> phi_bb221_29;
  TNode<IntPtrT> phi_bb221_32;
  TNode<BoolT> phi_bb221_33;
  TNode<IntPtrT> phi_bb221_35;
  TNode<IntPtrT> phi_bb221_36;
  TNode<BoolT> phi_bb221_37;
  TNode<IntPtrT> phi_bb221_46;
  TNode<BoolT> phi_bb221_48;
  TNode<IntPtrT> tmp503;
  TNode<BoolT> tmp504;
  if (block221.is_used()) {
    ca_.Bind(&block221, &phi_bb221_20, &phi_bb221_25, &phi_bb221_26, &phi_bb221_27, &phi_bb221_28, &phi_bb221_29, &phi_bb221_32, &phi_bb221_33, &phi_bb221_35, &phi_bb221_36, &phi_bb221_37, &phi_bb221_46, &phi_bb221_48);
    tmp503 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp504 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp41}, TNode<IntPtrT>{tmp503});
    ca_.Branch(tmp504, &block225, std::vector<compiler::Node*>{phi_bb221_20, phi_bb221_25, phi_bb221_26, phi_bb221_27, phi_bb221_28, phi_bb221_29, phi_bb221_32, phi_bb221_33, phi_bb221_35, phi_bb221_36, phi_bb221_37, phi_bb221_46, phi_bb221_48}, &block226, std::vector<compiler::Node*>{phi_bb221_20, phi_bb221_25, phi_bb221_26, phi_bb221_27, phi_bb221_28, phi_bb221_29, phi_bb221_32, phi_bb221_33, phi_bb221_35, phi_bb221_36, phi_bb221_37, phi_bb221_46, phi_bb221_48});
  }

  TNode<IntPtrT> phi_bb225_20;
  TNode<IntPtrT> phi_bb225_25;
  TNode<IntPtrT> phi_bb225_26;
  TNode<IntPtrT> phi_bb225_27;
  TNode<IntPtrT> phi_bb225_28;
  TNode<IntPtrT> phi_bb225_29;
  TNode<IntPtrT> phi_bb225_32;
  TNode<BoolT> phi_bb225_33;
  TNode<IntPtrT> phi_bb225_35;
  TNode<IntPtrT> phi_bb225_36;
  TNode<BoolT> phi_bb225_37;
  TNode<IntPtrT> phi_bb225_46;
  TNode<BoolT> phi_bb225_48;
  if (block225.is_used()) {
    ca_.Bind(&block225, &phi_bb225_20, &phi_bb225_25, &phi_bb225_26, &phi_bb225_27, &phi_bb225_28, &phi_bb225_29, &phi_bb225_32, &phi_bb225_33, &phi_bb225_35, &phi_bb225_36, &phi_bb225_37, &phi_bb225_46, &phi_bb225_48);
    ca_.Goto(&block227, phi_bb225_20, phi_bb225_25, phi_bb225_26, phi_bb225_27, phi_bb225_28, phi_bb225_29, phi_bb225_32, phi_bb225_33, phi_bb225_35, phi_bb225_36, phi_bb225_37, phi_bb225_46, phi_bb225_48, tmp462);
  }

  TNode<IntPtrT> phi_bb226_20;
  TNode<IntPtrT> phi_bb226_25;
  TNode<IntPtrT> phi_bb226_26;
  TNode<IntPtrT> phi_bb226_27;
  TNode<IntPtrT> phi_bb226_28;
  TNode<IntPtrT> phi_bb226_29;
  TNode<IntPtrT> phi_bb226_32;
  TNode<BoolT> phi_bb226_33;
  TNode<IntPtrT> phi_bb226_35;
  TNode<IntPtrT> phi_bb226_36;
  TNode<BoolT> phi_bb226_37;
  TNode<IntPtrT> phi_bb226_46;
  TNode<BoolT> phi_bb226_48;
  TNode<Union<HeapObject, TaggedIndex>> tmp505;
  TNode<IntPtrT> tmp506;
  TNode<IntPtrT> tmp507;
  TNode<UintPtrT> tmp508;
  TNode<UintPtrT> tmp509;
  TNode<BoolT> tmp510;
  if (block226.is_used()) {
    ca_.Bind(&block226, &phi_bb226_20, &phi_bb226_25, &phi_bb226_26, &phi_bb226_27, &phi_bb226_28, &phi_bb226_29, &phi_bb226_32, &phi_bb226_33, &phi_bb226_35, &phi_bb226_36, &phi_bb226_37, &phi_bb226_46, &phi_bb226_48);
    std::tie(tmp505, tmp506, tmp507) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb214_41}).Flatten();
    tmp508 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb226_20});
    tmp509 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp507});
    tmp510 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp508}, TNode<UintPtrT>{tmp509});
    ca_.Branch(tmp510, &block232, std::vector<compiler::Node*>{phi_bb226_20, phi_bb226_25, phi_bb226_26, phi_bb226_27, phi_bb226_28, phi_bb226_29, phi_bb226_32, phi_bb226_33, phi_bb226_35, phi_bb226_36, phi_bb226_37, phi_bb226_46, phi_bb226_48, phi_bb226_20, phi_bb226_20, phi_bb226_20, phi_bb226_20}, &block233, std::vector<compiler::Node*>{phi_bb226_20, phi_bb226_25, phi_bb226_26, phi_bb226_27, phi_bb226_28, phi_bb226_29, phi_bb226_32, phi_bb226_33, phi_bb226_35, phi_bb226_36, phi_bb226_37, phi_bb226_46, phi_bb226_48, phi_bb226_20, phi_bb226_20, phi_bb226_20, phi_bb226_20});
  }

  TNode<IntPtrT> phi_bb232_20;
  TNode<IntPtrT> phi_bb232_25;
  TNode<IntPtrT> phi_bb232_26;
  TNode<IntPtrT> phi_bb232_27;
  TNode<IntPtrT> phi_bb232_28;
  TNode<IntPtrT> phi_bb232_29;
  TNode<IntPtrT> phi_bb232_32;
  TNode<BoolT> phi_bb232_33;
  TNode<IntPtrT> phi_bb232_35;
  TNode<IntPtrT> phi_bb232_36;
  TNode<BoolT> phi_bb232_37;
  TNode<IntPtrT> phi_bb232_46;
  TNode<BoolT> phi_bb232_48;
  TNode<IntPtrT> phi_bb232_54;
  TNode<IntPtrT> phi_bb232_55;
  TNode<IntPtrT> phi_bb232_59;
  TNode<IntPtrT> phi_bb232_60;
  TNode<IntPtrT> tmp511;
  TNode<IntPtrT> tmp512;
  TNode<Union<HeapObject, TaggedIndex>> tmp513;
  TNode<IntPtrT> tmp514;
  TNode<Object> tmp515;
  TNode<JSAny> tmp516;
  if (block232.is_used()) {
    ca_.Bind(&block232, &phi_bb232_20, &phi_bb232_25, &phi_bb232_26, &phi_bb232_27, &phi_bb232_28, &phi_bb232_29, &phi_bb232_32, &phi_bb232_33, &phi_bb232_35, &phi_bb232_36, &phi_bb232_37, &phi_bb232_46, &phi_bb232_48, &phi_bb232_54, &phi_bb232_55, &phi_bb232_59, &phi_bb232_60);
    tmp511 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb232_60});
    tmp512 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp506}, TNode<IntPtrT>{tmp511});
    std::tie(tmp513, tmp514) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp505}, TNode<IntPtrT>{tmp512}).Flatten();
    tmp515 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp513, tmp514});
    tmp516 = UnsafeCast_JSAny_0(state_, TNode<Context>{tmp455}, TNode<Object>{tmp515});
    ca_.Goto(&block227, phi_bb232_20, phi_bb232_25, phi_bb232_26, phi_bb232_27, phi_bb232_28, phi_bb232_29, phi_bb232_32, phi_bb232_33, phi_bb232_35, phi_bb232_36, phi_bb232_37, phi_bb232_46, phi_bb232_48, tmp516);
  }

  TNode<IntPtrT> phi_bb233_20;
  TNode<IntPtrT> phi_bb233_25;
  TNode<IntPtrT> phi_bb233_26;
  TNode<IntPtrT> phi_bb233_27;
  TNode<IntPtrT> phi_bb233_28;
  TNode<IntPtrT> phi_bb233_29;
  TNode<IntPtrT> phi_bb233_32;
  TNode<BoolT> phi_bb233_33;
  TNode<IntPtrT> phi_bb233_35;
  TNode<IntPtrT> phi_bb233_36;
  TNode<BoolT> phi_bb233_37;
  TNode<IntPtrT> phi_bb233_46;
  TNode<BoolT> phi_bb233_48;
  TNode<IntPtrT> phi_bb233_54;
  TNode<IntPtrT> phi_bb233_55;
  TNode<IntPtrT> phi_bb233_59;
  TNode<IntPtrT> phi_bb233_60;
  if (block233.is_used()) {
    ca_.Bind(&block233, &phi_bb233_20, &phi_bb233_25, &phi_bb233_26, &phi_bb233_27, &phi_bb233_28, &phi_bb233_29, &phi_bb233_32, &phi_bb233_33, &phi_bb233_35, &phi_bb233_36, &phi_bb233_37, &phi_bb233_46, &phi_bb233_48, &phi_bb233_54, &phi_bb233_55, &phi_bb233_59, &phi_bb233_60);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb227_20;
  TNode<IntPtrT> phi_bb227_25;
  TNode<IntPtrT> phi_bb227_26;
  TNode<IntPtrT> phi_bb227_27;
  TNode<IntPtrT> phi_bb227_28;
  TNode<IntPtrT> phi_bb227_29;
  TNode<IntPtrT> phi_bb227_32;
  TNode<BoolT> phi_bb227_33;
  TNode<IntPtrT> phi_bb227_35;
  TNode<IntPtrT> phi_bb227_36;
  TNode<BoolT> phi_bb227_37;
  TNode<IntPtrT> phi_bb227_46;
  TNode<BoolT> phi_bb227_48;
  TNode<JSAny> phi_bb227_49;
  TNode<BoolT> tmp517;
  TNode<BoolT> tmp518;
  if (block227.is_used()) {
    ca_.Bind(&block227, &phi_bb227_20, &phi_bb227_25, &phi_bb227_26, &phi_bb227_27, &phi_bb227_28, &phi_bb227_29, &phi_bb227_32, &phi_bb227_33, &phi_bb227_35, &phi_bb227_36, &phi_bb227_37, &phi_bb227_46, &phi_bb227_48, &phi_bb227_49);
    tmp517 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb227_46}, TNode<IntPtrT>{tmp498});
    tmp518 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp517});
    ca_.Branch(tmp518, &block238, std::vector<compiler::Node*>{phi_bb227_20, phi_bb227_25, phi_bb227_26, phi_bb227_27, phi_bb227_28, phi_bb227_29, phi_bb227_32, phi_bb227_33, phi_bb227_35, phi_bb227_36, phi_bb227_37, phi_bb227_46, phi_bb227_48, phi_bb227_49}, &block239, std::vector<compiler::Node*>{phi_bb227_20, phi_bb227_25, phi_bb227_26, phi_bb227_27, phi_bb227_28, phi_bb227_29, phi_bb227_32, phi_bb227_33, phi_bb227_35, phi_bb227_36, phi_bb227_37, phi_bb227_46, phi_bb227_48, phi_bb227_49});
  }

  TNode<IntPtrT> phi_bb239_20;
  TNode<IntPtrT> phi_bb239_25;
  TNode<IntPtrT> phi_bb239_26;
  TNode<IntPtrT> phi_bb239_27;
  TNode<IntPtrT> phi_bb239_28;
  TNode<IntPtrT> phi_bb239_29;
  TNode<IntPtrT> phi_bb239_32;
  TNode<BoolT> phi_bb239_33;
  TNode<IntPtrT> phi_bb239_35;
  TNode<IntPtrT> phi_bb239_36;
  TNode<BoolT> phi_bb239_37;
  TNode<IntPtrT> phi_bb239_46;
  TNode<BoolT> phi_bb239_48;
  TNode<JSAny> phi_bb239_49;
  if (block239.is_used()) {
    ca_.Bind(&block239, &phi_bb239_20, &phi_bb239_25, &phi_bb239_26, &phi_bb239_27, &phi_bb239_28, &phi_bb239_29, &phi_bb239_32, &phi_bb239_33, &phi_bb239_35, &phi_bb239_36, &phi_bb239_37, &phi_bb239_46, &phi_bb239_48, &phi_bb239_49);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/torque-internal.tq", 245});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.Empty()' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb238_20;
  TNode<IntPtrT> phi_bb238_25;
  TNode<IntPtrT> phi_bb238_26;
  TNode<IntPtrT> phi_bb238_27;
  TNode<IntPtrT> phi_bb238_28;
  TNode<IntPtrT> phi_bb238_29;
  TNode<IntPtrT> phi_bb238_32;
  TNode<BoolT> phi_bb238_33;
  TNode<IntPtrT> phi_bb238_35;
  TNode<IntPtrT> phi_bb238_36;
  TNode<BoolT> phi_bb238_37;
  TNode<IntPtrT> phi_bb238_46;
  TNode<BoolT> phi_bb238_48;
  TNode<JSAny> phi_bb238_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp519;
  TNode<IntPtrT> tmp520;
  TNode<IntPtrT> tmp521;
  TNode<IntPtrT> tmp522;
  TNode<Uint32T> tmp523;
  TNode<Uint32T> tmp524;
  TNode<BoolT> tmp525;
  if (block238.is_used()) {
    ca_.Bind(&block238, &phi_bb238_20, &phi_bb238_25, &phi_bb238_26, &phi_bb238_27, &phi_bb238_28, &phi_bb238_29, &phi_bb238_32, &phi_bb238_33, &phi_bb238_35, &phi_bb238_36, &phi_bb238_37, &phi_bb238_46, &phi_bb238_48, &phi_bb238_49);
    std::tie(tmp519, tmp520) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp63}, TNode<IntPtrT>{phi_bb238_46}).Flatten();
    tmp521 = FromConstexpr_intptr_constexpr_int31_0(state_, kInt32Size);
    tmp522 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb238_46}, TNode<IntPtrT>{tmp521});
    tmp523 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp519, tmp520});
    tmp524 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI32.raw_bit_field());
    tmp525 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp523}, TNode<Uint32T>{tmp524});
    ca_.Branch(tmp525, &block241, std::vector<compiler::Node*>{phi_bb238_20, phi_bb238_25, phi_bb238_26, phi_bb238_27, phi_bb238_28, phi_bb238_29, phi_bb238_32, phi_bb238_33, phi_bb238_35, phi_bb238_36, phi_bb238_37, phi_bb238_48, phi_bb238_49}, &block242, std::vector<compiler::Node*>{phi_bb238_20, phi_bb238_25, phi_bb238_26, phi_bb238_27, phi_bb238_28, phi_bb238_29, phi_bb238_32, phi_bb238_33, phi_bb238_35, phi_bb238_36, phi_bb238_37, phi_bb238_48, phi_bb238_49});
  }

  TNode<IntPtrT> phi_bb241_20;
  TNode<IntPtrT> phi_bb241_25;
  TNode<IntPtrT> phi_bb241_26;
  TNode<IntPtrT> phi_bb241_27;
  TNode<IntPtrT> phi_bb241_28;
  TNode<IntPtrT> phi_bb241_29;
  TNode<IntPtrT> phi_bb241_32;
  TNode<BoolT> phi_bb241_33;
  TNode<IntPtrT> phi_bb241_35;
  TNode<IntPtrT> phi_bb241_36;
  TNode<BoolT> phi_bb241_37;
  TNode<BoolT> phi_bb241_48;
  TNode<JSAny> phi_bb241_49;
  TNode<IntPtrT> tmp526;
  TNode<IntPtrT> tmp527;
  TNode<IntPtrT> tmp528;
  TNode<BoolT> tmp529;
  if (block241.is_used()) {
    ca_.Bind(&block241, &phi_bb241_20, &phi_bb241_25, &phi_bb241_26, &phi_bb241_27, &phi_bb241_28, &phi_bb241_29, &phi_bb241_32, &phi_bb241_33, &phi_bb241_35, &phi_bb241_36, &phi_bb241_37, &phi_bb241_48, &phi_bb241_49);
    tmp526 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp527 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb241_25}, TNode<IntPtrT>{tmp526});
    tmp528 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp529 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb241_25}, TNode<IntPtrT>{tmp528});
    ca_.Branch(tmp529, &block245, std::vector<compiler::Node*>{phi_bb241_20, phi_bb241_26, phi_bb241_27, phi_bb241_28, phi_bb241_29, phi_bb241_32, phi_bb241_33, phi_bb241_35, phi_bb241_36, phi_bb241_37, phi_bb241_48, phi_bb241_49}, &block246, std::vector<compiler::Node*>{phi_bb241_20, phi_bb241_26, phi_bb241_27, phi_bb241_28, phi_bb241_29, phi_bb241_32, phi_bb241_33, phi_bb241_35, phi_bb241_36, phi_bb241_37, phi_bb241_48, phi_bb241_49});
  }

  TNode<IntPtrT> phi_bb245_20;
  TNode<IntPtrT> phi_bb245_26;
  TNode<IntPtrT> phi_bb245_27;
  TNode<IntPtrT> phi_bb245_28;
  TNode<IntPtrT> phi_bb245_29;
  TNode<IntPtrT> phi_bb245_32;
  TNode<BoolT> phi_bb245_33;
  TNode<IntPtrT> phi_bb245_35;
  TNode<IntPtrT> phi_bb245_36;
  TNode<BoolT> phi_bb245_37;
  TNode<BoolT> phi_bb245_48;
  TNode<JSAny> phi_bb245_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp530;
  TNode<IntPtrT> tmp531;
  TNode<IntPtrT> tmp532;
  TNode<IntPtrT> tmp533;
  if (block245.is_used()) {
    ca_.Bind(&block245, &phi_bb245_20, &phi_bb245_26, &phi_bb245_27, &phi_bb245_28, &phi_bb245_29, &phi_bb245_32, &phi_bb245_33, &phi_bb245_35, &phi_bb245_36, &phi_bb245_37, &phi_bb245_48, &phi_bb245_49);
    std::tie(tmp530, tmp531) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb245_27}).Flatten();
    tmp532 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp533 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb245_27}, TNode<IntPtrT>{tmp532});
    ca_.Goto(&block244, phi_bb245_20, phi_bb245_26, tmp533, phi_bb245_28, phi_bb245_29, phi_bb245_32, phi_bb245_33, phi_bb245_35, phi_bb245_36, phi_bb245_37, phi_bb245_48, phi_bb245_49, tmp530, tmp531);
  }

  TNode<IntPtrT> phi_bb246_20;
  TNode<IntPtrT> phi_bb246_26;
  TNode<IntPtrT> phi_bb246_27;
  TNode<IntPtrT> phi_bb246_28;
  TNode<IntPtrT> phi_bb246_29;
  TNode<IntPtrT> phi_bb246_32;
  TNode<BoolT> phi_bb246_33;
  TNode<IntPtrT> phi_bb246_35;
  TNode<IntPtrT> phi_bb246_36;
  TNode<BoolT> phi_bb246_37;
  TNode<BoolT> phi_bb246_48;
  TNode<JSAny> phi_bb246_49;
  if (block246.is_used()) {
    ca_.Bind(&block246, &phi_bb246_20, &phi_bb246_26, &phi_bb246_27, &phi_bb246_28, &phi_bb246_29, &phi_bb246_32, &phi_bb246_33, &phi_bb246_35, &phi_bb246_36, &phi_bb246_37, &phi_bb246_48, &phi_bb246_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block248, phi_bb246_20, phi_bb246_26, phi_bb246_27, phi_bb246_28, phi_bb246_29, phi_bb246_32, phi_bb246_33, phi_bb246_35, phi_bb246_36, phi_bb246_37, phi_bb246_48, phi_bb246_49);
    } else {
      ca_.Goto(&block249, phi_bb246_20, phi_bb246_26, phi_bb246_27, phi_bb246_28, phi_bb246_29, phi_bb246_32, phi_bb246_33, phi_bb246_35, phi_bb246_36, phi_bb246_37, phi_bb246_48, phi_bb246_49);
    }
  }

  TNode<IntPtrT> phi_bb248_20;
  TNode<IntPtrT> phi_bb248_26;
  TNode<IntPtrT> phi_bb248_27;
  TNode<IntPtrT> phi_bb248_28;
  TNode<IntPtrT> phi_bb248_29;
  TNode<IntPtrT> phi_bb248_32;
  TNode<BoolT> phi_bb248_33;
  TNode<IntPtrT> phi_bb248_35;
  TNode<IntPtrT> phi_bb248_36;
  TNode<BoolT> phi_bb248_37;
  TNode<BoolT> phi_bb248_48;
  TNode<JSAny> phi_bb248_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp534;
  TNode<IntPtrT> tmp535;
  TNode<IntPtrT> tmp536;
  TNode<IntPtrT> tmp537;
  if (block248.is_used()) {
    ca_.Bind(&block248, &phi_bb248_20, &phi_bb248_26, &phi_bb248_27, &phi_bb248_28, &phi_bb248_29, &phi_bb248_32, &phi_bb248_33, &phi_bb248_35, &phi_bb248_36, &phi_bb248_37, &phi_bb248_48, &phi_bb248_49);
    std::tie(tmp534, tmp535) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb248_29}).Flatten();
    tmp536 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp537 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb248_29}, TNode<IntPtrT>{tmp536});
    ca_.Goto(&block247, phi_bb248_20, phi_bb248_26, phi_bb248_27, phi_bb248_28, tmp537, phi_bb248_32, phi_bb248_33, phi_bb248_35, phi_bb248_36, phi_bb248_37, phi_bb248_48, phi_bb248_49, tmp534, tmp535);
  }

  TNode<IntPtrT> phi_bb249_20;
  TNode<IntPtrT> phi_bb249_26;
  TNode<IntPtrT> phi_bb249_27;
  TNode<IntPtrT> phi_bb249_28;
  TNode<IntPtrT> phi_bb249_29;
  TNode<IntPtrT> phi_bb249_32;
  TNode<BoolT> phi_bb249_33;
  TNode<IntPtrT> phi_bb249_35;
  TNode<IntPtrT> phi_bb249_36;
  TNode<BoolT> phi_bb249_37;
  TNode<BoolT> phi_bb249_48;
  TNode<JSAny> phi_bb249_49;
  TNode<IntPtrT> tmp538;
  TNode<BoolT> tmp539;
  if (block249.is_used()) {
    ca_.Bind(&block249, &phi_bb249_20, &phi_bb249_26, &phi_bb249_27, &phi_bb249_28, &phi_bb249_29, &phi_bb249_32, &phi_bb249_33, &phi_bb249_35, &phi_bb249_36, &phi_bb249_37, &phi_bb249_48, &phi_bb249_49);
    tmp538 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp539 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb249_32}, TNode<IntPtrT>{tmp538});
    ca_.Branch(tmp539, &block251, std::vector<compiler::Node*>{phi_bb249_20, phi_bb249_26, phi_bb249_27, phi_bb249_28, phi_bb249_29, phi_bb249_32, phi_bb249_33, phi_bb249_35, phi_bb249_36, phi_bb249_37, phi_bb249_48, phi_bb249_49}, &block252, std::vector<compiler::Node*>{phi_bb249_20, phi_bb249_26, phi_bb249_27, phi_bb249_28, phi_bb249_29, phi_bb249_32, phi_bb249_33, phi_bb249_35, phi_bb249_36, phi_bb249_37, phi_bb249_48, phi_bb249_49});
  }

  TNode<IntPtrT> phi_bb251_20;
  TNode<IntPtrT> phi_bb251_26;
  TNode<IntPtrT> phi_bb251_27;
  TNode<IntPtrT> phi_bb251_28;
  TNode<IntPtrT> phi_bb251_29;
  TNode<IntPtrT> phi_bb251_32;
  TNode<BoolT> phi_bb251_33;
  TNode<IntPtrT> phi_bb251_35;
  TNode<IntPtrT> phi_bb251_36;
  TNode<BoolT> phi_bb251_37;
  TNode<BoolT> phi_bb251_48;
  TNode<JSAny> phi_bb251_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp540;
  TNode<IntPtrT> tmp541;
  TNode<IntPtrT> tmp542;
  TNode<BoolT> tmp543;
  if (block251.is_used()) {
    ca_.Bind(&block251, &phi_bb251_20, &phi_bb251_26, &phi_bb251_27, &phi_bb251_28, &phi_bb251_29, &phi_bb251_32, &phi_bb251_33, &phi_bb251_35, &phi_bb251_36, &phi_bb251_37, &phi_bb251_48, &phi_bb251_49);
    std::tie(tmp540, tmp541) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb251_32}).Flatten();
    tmp542 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp543 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block247, phi_bb251_20, phi_bb251_26, phi_bb251_27, phi_bb251_28, phi_bb251_29, tmp542, tmp543, phi_bb251_35, phi_bb251_36, phi_bb251_37, phi_bb251_48, phi_bb251_49, tmp540, tmp541);
  }

  TNode<IntPtrT> phi_bb252_20;
  TNode<IntPtrT> phi_bb252_26;
  TNode<IntPtrT> phi_bb252_27;
  TNode<IntPtrT> phi_bb252_28;
  TNode<IntPtrT> phi_bb252_29;
  TNode<IntPtrT> phi_bb252_32;
  TNode<BoolT> phi_bb252_33;
  TNode<IntPtrT> phi_bb252_35;
  TNode<IntPtrT> phi_bb252_36;
  TNode<BoolT> phi_bb252_37;
  TNode<BoolT> phi_bb252_48;
  TNode<JSAny> phi_bb252_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp544;
  TNode<IntPtrT> tmp545;
  TNode<IntPtrT> tmp546;
  TNode<IntPtrT> tmp547;
  TNode<IntPtrT> tmp548;
  TNode<IntPtrT> tmp549;
  TNode<BoolT> tmp550;
  if (block252.is_used()) {
    ca_.Bind(&block252, &phi_bb252_20, &phi_bb252_26, &phi_bb252_27, &phi_bb252_28, &phi_bb252_29, &phi_bb252_32, &phi_bb252_33, &phi_bb252_35, &phi_bb252_36, &phi_bb252_37, &phi_bb252_48, &phi_bb252_49);
    std::tie(tmp544, tmp545) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb252_29}).Flatten();
    tmp546 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp547 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb252_29}, TNode<IntPtrT>{tmp546});
    tmp548 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp549 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp547}, TNode<IntPtrT>{tmp548});
    tmp550 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block247, phi_bb252_20, phi_bb252_26, phi_bb252_27, phi_bb252_28, tmp549, tmp547, tmp550, phi_bb252_35, phi_bb252_36, phi_bb252_37, phi_bb252_48, phi_bb252_49, tmp544, tmp545);
  }

  TNode<IntPtrT> phi_bb247_20;
  TNode<IntPtrT> phi_bb247_26;
  TNode<IntPtrT> phi_bb247_27;
  TNode<IntPtrT> phi_bb247_28;
  TNode<IntPtrT> phi_bb247_29;
  TNode<IntPtrT> phi_bb247_32;
  TNode<BoolT> phi_bb247_33;
  TNode<IntPtrT> phi_bb247_35;
  TNode<IntPtrT> phi_bb247_36;
  TNode<BoolT> phi_bb247_37;
  TNode<BoolT> phi_bb247_48;
  TNode<JSAny> phi_bb247_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb247_51;
  TNode<IntPtrT> phi_bb247_52;
  if (block247.is_used()) {
    ca_.Bind(&block247, &phi_bb247_20, &phi_bb247_26, &phi_bb247_27, &phi_bb247_28, &phi_bb247_29, &phi_bb247_32, &phi_bb247_33, &phi_bb247_35, &phi_bb247_36, &phi_bb247_37, &phi_bb247_48, &phi_bb247_49, &phi_bb247_51, &phi_bb247_52);
    ca_.Goto(&block244, phi_bb247_20, phi_bb247_26, phi_bb247_27, phi_bb247_28, phi_bb247_29, phi_bb247_32, phi_bb247_33, phi_bb247_35, phi_bb247_36, phi_bb247_37, phi_bb247_48, phi_bb247_49, phi_bb247_51, phi_bb247_52);
  }

  TNode<IntPtrT> phi_bb244_20;
  TNode<IntPtrT> phi_bb244_26;
  TNode<IntPtrT> phi_bb244_27;
  TNode<IntPtrT> phi_bb244_28;
  TNode<IntPtrT> phi_bb244_29;
  TNode<IntPtrT> phi_bb244_32;
  TNode<BoolT> phi_bb244_33;
  TNode<IntPtrT> phi_bb244_35;
  TNode<IntPtrT> phi_bb244_36;
  TNode<BoolT> phi_bb244_37;
  TNode<BoolT> phi_bb244_48;
  TNode<JSAny> phi_bb244_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb244_51;
  TNode<IntPtrT> phi_bb244_52;
  TNode<Smi> tmp551;
  if (block244.is_used()) {
    ca_.Bind(&block244, &phi_bb244_20, &phi_bb244_26, &phi_bb244_27, &phi_bb244_28, &phi_bb244_29, &phi_bb244_32, &phi_bb244_33, &phi_bb244_35, &phi_bb244_36, &phi_bb244_37, &phi_bb244_48, &phi_bb244_49, &phi_bb244_51, &phi_bb244_52);
    compiler::CodeAssemblerLabel label552(&ca_);
    tmp551 = Cast_Smi_0(state_, TNode<Object>{phi_bb244_49}, &label552);
    ca_.Goto(&block255, phi_bb244_20, phi_bb244_26, phi_bb244_27, phi_bb244_28, phi_bb244_29, phi_bb244_32, phi_bb244_33, phi_bb244_35, phi_bb244_36, phi_bb244_37, phi_bb244_48, phi_bb244_49, phi_bb244_51, phi_bb244_52, phi_bb244_49, phi_bb244_49);
    if (label552.is_used()) {
      ca_.Bind(&label552);
      ca_.Goto(&block256, phi_bb244_20, phi_bb244_26, phi_bb244_27, phi_bb244_28, phi_bb244_29, phi_bb244_32, phi_bb244_33, phi_bb244_35, phi_bb244_36, phi_bb244_37, phi_bb244_48, phi_bb244_49, phi_bb244_51, phi_bb244_52, phi_bb244_49, phi_bb244_49);
    }
  }

  TNode<IntPtrT> phi_bb256_20;
  TNode<IntPtrT> phi_bb256_26;
  TNode<IntPtrT> phi_bb256_27;
  TNode<IntPtrT> phi_bb256_28;
  TNode<IntPtrT> phi_bb256_29;
  TNode<IntPtrT> phi_bb256_32;
  TNode<BoolT> phi_bb256_33;
  TNode<IntPtrT> phi_bb256_35;
  TNode<IntPtrT> phi_bb256_36;
  TNode<BoolT> phi_bb256_37;
  TNode<BoolT> phi_bb256_48;
  TNode<JSAny> phi_bb256_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb256_51;
  TNode<IntPtrT> phi_bb256_52;
  TNode<JSAny> phi_bb256_53;
  TNode<JSAny> phi_bb256_54;
  TNode<Int32T> tmp553;
  TNode<IntPtrT> tmp554;
  if (block256.is_used()) {
    ca_.Bind(&block256, &phi_bb256_20, &phi_bb256_26, &phi_bb256_27, &phi_bb256_28, &phi_bb256_29, &phi_bb256_32, &phi_bb256_33, &phi_bb256_35, &phi_bb256_36, &phi_bb256_37, &phi_bb256_48, &phi_bb256_49, &phi_bb256_51, &phi_bb256_52, &phi_bb256_53, &phi_bb256_54);
    tmp553 = ca_.CallBuiltin<Int32T>(Builtin::kWasmTaggedNonSmiToInt32, tmp455, ca_.UncheckedCast<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, String, Symbol, Undefined>>(phi_bb256_53));
    tmp554 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp553});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb256_51, phi_bb256_52}, tmp554);
    ca_.Goto(&block253, phi_bb256_20, phi_bb256_26, phi_bb256_27, phi_bb256_28, phi_bb256_29, phi_bb256_32, phi_bb256_33, phi_bb256_35, phi_bb256_36, phi_bb256_37, phi_bb256_48, phi_bb256_49, phi_bb256_51, phi_bb256_52, phi_bb256_53);
  }

  TNode<IntPtrT> phi_bb255_20;
  TNode<IntPtrT> phi_bb255_26;
  TNode<IntPtrT> phi_bb255_27;
  TNode<IntPtrT> phi_bb255_28;
  TNode<IntPtrT> phi_bb255_29;
  TNode<IntPtrT> phi_bb255_32;
  TNode<BoolT> phi_bb255_33;
  TNode<IntPtrT> phi_bb255_35;
  TNode<IntPtrT> phi_bb255_36;
  TNode<BoolT> phi_bb255_37;
  TNode<BoolT> phi_bb255_48;
  TNode<JSAny> phi_bb255_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb255_51;
  TNode<IntPtrT> phi_bb255_52;
  TNode<JSAny> phi_bb255_53;
  TNode<JSAny> phi_bb255_54;
  TNode<Int32T> tmp555;
  TNode<IntPtrT> tmp556;
  if (block255.is_used()) {
    ca_.Bind(&block255, &phi_bb255_20, &phi_bb255_26, &phi_bb255_27, &phi_bb255_28, &phi_bb255_29, &phi_bb255_32, &phi_bb255_33, &phi_bb255_35, &phi_bb255_36, &phi_bb255_37, &phi_bb255_48, &phi_bb255_49, &phi_bb255_51, &phi_bb255_52, &phi_bb255_53, &phi_bb255_54);
    tmp555 = CodeStubAssembler(state_).SmiToInt32(TNode<Smi>{tmp551});
    tmp556 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp555});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb255_51, phi_bb255_52}, tmp556);
    ca_.Goto(&block253, phi_bb255_20, phi_bb255_26, phi_bb255_27, phi_bb255_28, phi_bb255_29, phi_bb255_32, phi_bb255_33, phi_bb255_35, phi_bb255_36, phi_bb255_37, phi_bb255_48, phi_bb255_49, phi_bb255_51, phi_bb255_52, phi_bb255_53);
  }

  TNode<IntPtrT> phi_bb253_20;
  TNode<IntPtrT> phi_bb253_26;
  TNode<IntPtrT> phi_bb253_27;
  TNode<IntPtrT> phi_bb253_28;
  TNode<IntPtrT> phi_bb253_29;
  TNode<IntPtrT> phi_bb253_32;
  TNode<BoolT> phi_bb253_33;
  TNode<IntPtrT> phi_bb253_35;
  TNode<IntPtrT> phi_bb253_36;
  TNode<BoolT> phi_bb253_37;
  TNode<BoolT> phi_bb253_48;
  TNode<JSAny> phi_bb253_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb253_51;
  TNode<IntPtrT> phi_bb253_52;
  TNode<JSAny> phi_bb253_53;
  if (block253.is_used()) {
    ca_.Bind(&block253, &phi_bb253_20, &phi_bb253_26, &phi_bb253_27, &phi_bb253_28, &phi_bb253_29, &phi_bb253_32, &phi_bb253_33, &phi_bb253_35, &phi_bb253_36, &phi_bb253_37, &phi_bb253_48, &phi_bb253_49, &phi_bb253_51, &phi_bb253_52, &phi_bb253_53);
    ca_.Goto(&block243, phi_bb253_20, tmp527, phi_bb253_26, phi_bb253_27, phi_bb253_28, phi_bb253_29, phi_bb253_32, phi_bb253_33, phi_bb253_35, phi_bb253_36, phi_bb253_37, phi_bb253_48, phi_bb253_49);
  }

  TNode<IntPtrT> phi_bb242_20;
  TNode<IntPtrT> phi_bb242_25;
  TNode<IntPtrT> phi_bb242_26;
  TNode<IntPtrT> phi_bb242_27;
  TNode<IntPtrT> phi_bb242_28;
  TNode<IntPtrT> phi_bb242_29;
  TNode<IntPtrT> phi_bb242_32;
  TNode<BoolT> phi_bb242_33;
  TNode<IntPtrT> phi_bb242_35;
  TNode<IntPtrT> phi_bb242_36;
  TNode<BoolT> phi_bb242_37;
  TNode<BoolT> phi_bb242_48;
  TNode<JSAny> phi_bb242_49;
  TNode<Uint32T> tmp557;
  TNode<BoolT> tmp558;
  if (block242.is_used()) {
    ca_.Bind(&block242, &phi_bb242_20, &phi_bb242_25, &phi_bb242_26, &phi_bb242_27, &phi_bb242_28, &phi_bb242_29, &phi_bb242_32, &phi_bb242_33, &phi_bb242_35, &phi_bb242_36, &phi_bb242_37, &phi_bb242_48, &phi_bb242_49);
    tmp557 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF32.raw_bit_field());
    tmp558 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp523}, TNode<Uint32T>{tmp557});
    ca_.Branch(tmp558, &block257, std::vector<compiler::Node*>{phi_bb242_20, phi_bb242_25, phi_bb242_26, phi_bb242_27, phi_bb242_28, phi_bb242_29, phi_bb242_32, phi_bb242_33, phi_bb242_35, phi_bb242_36, phi_bb242_37, phi_bb242_48, phi_bb242_49}, &block258, std::vector<compiler::Node*>{phi_bb242_20, phi_bb242_25, phi_bb242_26, phi_bb242_27, phi_bb242_28, phi_bb242_29, phi_bb242_32, phi_bb242_33, phi_bb242_35, phi_bb242_36, phi_bb242_37, phi_bb242_48, phi_bb242_49});
  }

  TNode<IntPtrT> phi_bb257_20;
  TNode<IntPtrT> phi_bb257_25;
  TNode<IntPtrT> phi_bb257_26;
  TNode<IntPtrT> phi_bb257_27;
  TNode<IntPtrT> phi_bb257_28;
  TNode<IntPtrT> phi_bb257_29;
  TNode<IntPtrT> phi_bb257_32;
  TNode<BoolT> phi_bb257_33;
  TNode<IntPtrT> phi_bb257_35;
  TNode<IntPtrT> phi_bb257_36;
  TNode<BoolT> phi_bb257_37;
  TNode<BoolT> phi_bb257_48;
  TNode<JSAny> phi_bb257_49;
  TNode<IntPtrT> tmp559;
  TNode<IntPtrT> tmp560;
  TNode<IntPtrT> tmp561;
  TNode<BoolT> tmp562;
  if (block257.is_used()) {
    ca_.Bind(&block257, &phi_bb257_20, &phi_bb257_25, &phi_bb257_26, &phi_bb257_27, &phi_bb257_28, &phi_bb257_29, &phi_bb257_32, &phi_bb257_33, &phi_bb257_35, &phi_bb257_36, &phi_bb257_37, &phi_bb257_48, &phi_bb257_49);
    tmp559 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp560 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb257_26}, TNode<IntPtrT>{tmp559});
    tmp561 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp562 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb257_26}, TNode<IntPtrT>{tmp561});
    ca_.Branch(tmp562, &block261, std::vector<compiler::Node*>{phi_bb257_20, phi_bb257_25, phi_bb257_27, phi_bb257_28, phi_bb257_29, phi_bb257_32, phi_bb257_33, phi_bb257_35, phi_bb257_36, phi_bb257_37, phi_bb257_48, phi_bb257_49}, &block262, std::vector<compiler::Node*>{phi_bb257_20, phi_bb257_25, phi_bb257_27, phi_bb257_28, phi_bb257_29, phi_bb257_32, phi_bb257_33, phi_bb257_35, phi_bb257_36, phi_bb257_37, phi_bb257_48, phi_bb257_49});
  }

  TNode<IntPtrT> phi_bb261_20;
  TNode<IntPtrT> phi_bb261_25;
  TNode<IntPtrT> phi_bb261_27;
  TNode<IntPtrT> phi_bb261_28;
  TNode<IntPtrT> phi_bb261_29;
  TNode<IntPtrT> phi_bb261_32;
  TNode<BoolT> phi_bb261_33;
  TNode<IntPtrT> phi_bb261_35;
  TNode<IntPtrT> phi_bb261_36;
  TNode<BoolT> phi_bb261_37;
  TNode<BoolT> phi_bb261_48;
  TNode<JSAny> phi_bb261_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp563;
  TNode<IntPtrT> tmp564;
  TNode<IntPtrT> tmp565;
  TNode<IntPtrT> tmp566;
  if (block261.is_used()) {
    ca_.Bind(&block261, &phi_bb261_20, &phi_bb261_25, &phi_bb261_27, &phi_bb261_28, &phi_bb261_29, &phi_bb261_32, &phi_bb261_33, &phi_bb261_35, &phi_bb261_36, &phi_bb261_37, &phi_bb261_48, &phi_bb261_49);
    std::tie(tmp563, tmp564) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb261_28}).Flatten();
    tmp565 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp566 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb261_28}, TNode<IntPtrT>{tmp565});
    ca_.Goto(&block260, phi_bb261_20, phi_bb261_25, phi_bb261_27, tmp566, phi_bb261_29, phi_bb261_32, phi_bb261_33, phi_bb261_35, phi_bb261_36, phi_bb261_37, phi_bb261_48, phi_bb261_49, tmp563, tmp564);
  }

  TNode<IntPtrT> phi_bb262_20;
  TNode<IntPtrT> phi_bb262_25;
  TNode<IntPtrT> phi_bb262_27;
  TNode<IntPtrT> phi_bb262_28;
  TNode<IntPtrT> phi_bb262_29;
  TNode<IntPtrT> phi_bb262_32;
  TNode<BoolT> phi_bb262_33;
  TNode<IntPtrT> phi_bb262_35;
  TNode<IntPtrT> phi_bb262_36;
  TNode<BoolT> phi_bb262_37;
  TNode<BoolT> phi_bb262_48;
  TNode<JSAny> phi_bb262_49;
  if (block262.is_used()) {
    ca_.Bind(&block262, &phi_bb262_20, &phi_bb262_25, &phi_bb262_27, &phi_bb262_28, &phi_bb262_29, &phi_bb262_32, &phi_bb262_33, &phi_bb262_35, &phi_bb262_36, &phi_bb262_37, &phi_bb262_48, &phi_bb262_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block264, phi_bb262_20, phi_bb262_25, phi_bb262_27, phi_bb262_28, phi_bb262_29, phi_bb262_32, phi_bb262_33, phi_bb262_35, phi_bb262_36, phi_bb262_37, phi_bb262_48, phi_bb262_49);
    } else {
      ca_.Goto(&block265, phi_bb262_20, phi_bb262_25, phi_bb262_27, phi_bb262_28, phi_bb262_29, phi_bb262_32, phi_bb262_33, phi_bb262_35, phi_bb262_36, phi_bb262_37, phi_bb262_48, phi_bb262_49);
    }
  }

  TNode<IntPtrT> phi_bb264_20;
  TNode<IntPtrT> phi_bb264_25;
  TNode<IntPtrT> phi_bb264_27;
  TNode<IntPtrT> phi_bb264_28;
  TNode<IntPtrT> phi_bb264_29;
  TNode<IntPtrT> phi_bb264_32;
  TNode<BoolT> phi_bb264_33;
  TNode<IntPtrT> phi_bb264_35;
  TNode<IntPtrT> phi_bb264_36;
  TNode<BoolT> phi_bb264_37;
  TNode<BoolT> phi_bb264_48;
  TNode<JSAny> phi_bb264_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp567;
  TNode<IntPtrT> tmp568;
  TNode<IntPtrT> tmp569;
  TNode<IntPtrT> tmp570;
  if (block264.is_used()) {
    ca_.Bind(&block264, &phi_bb264_20, &phi_bb264_25, &phi_bb264_27, &phi_bb264_28, &phi_bb264_29, &phi_bb264_32, &phi_bb264_33, &phi_bb264_35, &phi_bb264_36, &phi_bb264_37, &phi_bb264_48, &phi_bb264_49);
    std::tie(tmp567, tmp568) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb264_29}).Flatten();
    tmp569 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp570 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb264_29}, TNode<IntPtrT>{tmp569});
    ca_.Goto(&block263, phi_bb264_20, phi_bb264_25, phi_bb264_27, phi_bb264_28, tmp570, phi_bb264_32, phi_bb264_33, phi_bb264_35, phi_bb264_36, phi_bb264_37, phi_bb264_48, phi_bb264_49, tmp567, tmp568);
  }

  TNode<IntPtrT> phi_bb265_20;
  TNode<IntPtrT> phi_bb265_25;
  TNode<IntPtrT> phi_bb265_27;
  TNode<IntPtrT> phi_bb265_28;
  TNode<IntPtrT> phi_bb265_29;
  TNode<IntPtrT> phi_bb265_32;
  TNode<BoolT> phi_bb265_33;
  TNode<IntPtrT> phi_bb265_35;
  TNode<IntPtrT> phi_bb265_36;
  TNode<BoolT> phi_bb265_37;
  TNode<BoolT> phi_bb265_48;
  TNode<JSAny> phi_bb265_49;
  TNode<IntPtrT> tmp571;
  TNode<BoolT> tmp572;
  if (block265.is_used()) {
    ca_.Bind(&block265, &phi_bb265_20, &phi_bb265_25, &phi_bb265_27, &phi_bb265_28, &phi_bb265_29, &phi_bb265_32, &phi_bb265_33, &phi_bb265_35, &phi_bb265_36, &phi_bb265_37, &phi_bb265_48, &phi_bb265_49);
    tmp571 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp572 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb265_32}, TNode<IntPtrT>{tmp571});
    ca_.Branch(tmp572, &block267, std::vector<compiler::Node*>{phi_bb265_20, phi_bb265_25, phi_bb265_27, phi_bb265_28, phi_bb265_29, phi_bb265_32, phi_bb265_33, phi_bb265_35, phi_bb265_36, phi_bb265_37, phi_bb265_48, phi_bb265_49}, &block268, std::vector<compiler::Node*>{phi_bb265_20, phi_bb265_25, phi_bb265_27, phi_bb265_28, phi_bb265_29, phi_bb265_32, phi_bb265_33, phi_bb265_35, phi_bb265_36, phi_bb265_37, phi_bb265_48, phi_bb265_49});
  }

  TNode<IntPtrT> phi_bb267_20;
  TNode<IntPtrT> phi_bb267_25;
  TNode<IntPtrT> phi_bb267_27;
  TNode<IntPtrT> phi_bb267_28;
  TNode<IntPtrT> phi_bb267_29;
  TNode<IntPtrT> phi_bb267_32;
  TNode<BoolT> phi_bb267_33;
  TNode<IntPtrT> phi_bb267_35;
  TNode<IntPtrT> phi_bb267_36;
  TNode<BoolT> phi_bb267_37;
  TNode<BoolT> phi_bb267_48;
  TNode<JSAny> phi_bb267_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp573;
  TNode<IntPtrT> tmp574;
  TNode<IntPtrT> tmp575;
  TNode<BoolT> tmp576;
  if (block267.is_used()) {
    ca_.Bind(&block267, &phi_bb267_20, &phi_bb267_25, &phi_bb267_27, &phi_bb267_28, &phi_bb267_29, &phi_bb267_32, &phi_bb267_33, &phi_bb267_35, &phi_bb267_36, &phi_bb267_37, &phi_bb267_48, &phi_bb267_49);
    std::tie(tmp573, tmp574) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb267_32}).Flatten();
    tmp575 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp576 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block263, phi_bb267_20, phi_bb267_25, phi_bb267_27, phi_bb267_28, phi_bb267_29, tmp575, tmp576, phi_bb267_35, phi_bb267_36, phi_bb267_37, phi_bb267_48, phi_bb267_49, tmp573, tmp574);
  }

  TNode<IntPtrT> phi_bb268_20;
  TNode<IntPtrT> phi_bb268_25;
  TNode<IntPtrT> phi_bb268_27;
  TNode<IntPtrT> phi_bb268_28;
  TNode<IntPtrT> phi_bb268_29;
  TNode<IntPtrT> phi_bb268_32;
  TNode<BoolT> phi_bb268_33;
  TNode<IntPtrT> phi_bb268_35;
  TNode<IntPtrT> phi_bb268_36;
  TNode<BoolT> phi_bb268_37;
  TNode<BoolT> phi_bb268_48;
  TNode<JSAny> phi_bb268_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp577;
  TNode<IntPtrT> tmp578;
  TNode<IntPtrT> tmp579;
  TNode<IntPtrT> tmp580;
  TNode<IntPtrT> tmp581;
  TNode<IntPtrT> tmp582;
  TNode<BoolT> tmp583;
  if (block268.is_used()) {
    ca_.Bind(&block268, &phi_bb268_20, &phi_bb268_25, &phi_bb268_27, &phi_bb268_28, &phi_bb268_29, &phi_bb268_32, &phi_bb268_33, &phi_bb268_35, &phi_bb268_36, &phi_bb268_37, &phi_bb268_48, &phi_bb268_49);
    std::tie(tmp577, tmp578) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb268_29}).Flatten();
    tmp579 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp580 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb268_29}, TNode<IntPtrT>{tmp579});
    tmp581 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp582 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp580}, TNode<IntPtrT>{tmp581});
    tmp583 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block263, phi_bb268_20, phi_bb268_25, phi_bb268_27, phi_bb268_28, tmp582, tmp580, tmp583, phi_bb268_35, phi_bb268_36, phi_bb268_37, phi_bb268_48, phi_bb268_49, tmp577, tmp578);
  }

  TNode<IntPtrT> phi_bb263_20;
  TNode<IntPtrT> phi_bb263_25;
  TNode<IntPtrT> phi_bb263_27;
  TNode<IntPtrT> phi_bb263_28;
  TNode<IntPtrT> phi_bb263_29;
  TNode<IntPtrT> phi_bb263_32;
  TNode<BoolT> phi_bb263_33;
  TNode<IntPtrT> phi_bb263_35;
  TNode<IntPtrT> phi_bb263_36;
  TNode<BoolT> phi_bb263_37;
  TNode<BoolT> phi_bb263_48;
  TNode<JSAny> phi_bb263_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb263_51;
  TNode<IntPtrT> phi_bb263_52;
  if (block263.is_used()) {
    ca_.Bind(&block263, &phi_bb263_20, &phi_bb263_25, &phi_bb263_27, &phi_bb263_28, &phi_bb263_29, &phi_bb263_32, &phi_bb263_33, &phi_bb263_35, &phi_bb263_36, &phi_bb263_37, &phi_bb263_48, &phi_bb263_49, &phi_bb263_51, &phi_bb263_52);
    ca_.Goto(&block260, phi_bb263_20, phi_bb263_25, phi_bb263_27, phi_bb263_28, phi_bb263_29, phi_bb263_32, phi_bb263_33, phi_bb263_35, phi_bb263_36, phi_bb263_37, phi_bb263_48, phi_bb263_49, phi_bb263_51, phi_bb263_52);
  }

  TNode<IntPtrT> phi_bb260_20;
  TNode<IntPtrT> phi_bb260_25;
  TNode<IntPtrT> phi_bb260_27;
  TNode<IntPtrT> phi_bb260_28;
  TNode<IntPtrT> phi_bb260_29;
  TNode<IntPtrT> phi_bb260_32;
  TNode<BoolT> phi_bb260_33;
  TNode<IntPtrT> phi_bb260_35;
  TNode<IntPtrT> phi_bb260_36;
  TNode<BoolT> phi_bb260_37;
  TNode<BoolT> phi_bb260_48;
  TNode<JSAny> phi_bb260_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb260_51;
  TNode<IntPtrT> phi_bb260_52;
  if (block260.is_used()) {
    ca_.Bind(&block260, &phi_bb260_20, &phi_bb260_25, &phi_bb260_27, &phi_bb260_28, &phi_bb260_29, &phi_bb260_32, &phi_bb260_33, &phi_bb260_35, &phi_bb260_36, &phi_bb260_37, &phi_bb260_48, &phi_bb260_49, &phi_bb260_51, &phi_bb260_52);
    if ((((wasm::kIsFpAlwaysDouble || wasm::kIsBigEndian) || wasm::kIsBigEndianOnSim))) {
      ca_.Goto(&block269, phi_bb260_20, phi_bb260_25, phi_bb260_27, phi_bb260_28, phi_bb260_29, phi_bb260_32, phi_bb260_33, phi_bb260_35, phi_bb260_36, phi_bb260_37, phi_bb260_48, phi_bb260_49, phi_bb260_51, phi_bb260_52);
    } else {
      ca_.Goto(&block270, phi_bb260_20, phi_bb260_25, phi_bb260_27, phi_bb260_28, phi_bb260_29, phi_bb260_32, phi_bb260_33, phi_bb260_35, phi_bb260_36, phi_bb260_37, phi_bb260_48, phi_bb260_49, phi_bb260_51, phi_bb260_52);
    }
  }

  TNode<IntPtrT> phi_bb269_20;
  TNode<IntPtrT> phi_bb269_25;
  TNode<IntPtrT> phi_bb269_27;
  TNode<IntPtrT> phi_bb269_28;
  TNode<IntPtrT> phi_bb269_29;
  TNode<IntPtrT> phi_bb269_32;
  TNode<BoolT> phi_bb269_33;
  TNode<IntPtrT> phi_bb269_35;
  TNode<IntPtrT> phi_bb269_36;
  TNode<BoolT> phi_bb269_37;
  TNode<BoolT> phi_bb269_48;
  TNode<JSAny> phi_bb269_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb269_51;
  TNode<IntPtrT> phi_bb269_52;
  if (block269.is_used()) {
    ca_.Bind(&block269, &phi_bb269_20, &phi_bb269_25, &phi_bb269_27, &phi_bb269_28, &phi_bb269_29, &phi_bb269_32, &phi_bb269_33, &phi_bb269_35, &phi_bb269_36, &phi_bb269_37, &phi_bb269_48, &phi_bb269_49, &phi_bb269_51, &phi_bb269_52);
    HandleF32Returns_0(state_, TNode<NativeContext>{tmp455}, TorqueStructLocationAllocator_0{TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb269_25}, TNode<IntPtrT>{tmp560}, TNode<IntPtrT>{phi_bb269_27}, TNode<IntPtrT>{phi_bb269_28}, TNode<IntPtrT>{phi_bb269_29}, TNode<IntPtrT>{tmp493}, TNode<IntPtrT>{tmp494}, TNode<IntPtrT>{phi_bb269_32}, TNode<BoolT>{phi_bb269_33}}, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb269_51}, TNode<IntPtrT>{phi_bb269_52}, TorqueStructUnsafe_0{}}, TNode<JSAny>{phi_bb269_49});
    ca_.Goto(&block271, phi_bb269_20, phi_bb269_25, phi_bb269_27, phi_bb269_28, phi_bb269_29, phi_bb269_32, phi_bb269_33, phi_bb269_35, phi_bb269_36, phi_bb269_37, phi_bb269_48, phi_bb269_49, phi_bb269_51, phi_bb269_52);
  }

  TNode<IntPtrT> phi_bb270_20;
  TNode<IntPtrT> phi_bb270_25;
  TNode<IntPtrT> phi_bb270_27;
  TNode<IntPtrT> phi_bb270_28;
  TNode<IntPtrT> phi_bb270_29;
  TNode<IntPtrT> phi_bb270_32;
  TNode<BoolT> phi_bb270_33;
  TNode<IntPtrT> phi_bb270_35;
  TNode<IntPtrT> phi_bb270_36;
  TNode<BoolT> phi_bb270_37;
  TNode<BoolT> phi_bb270_48;
  TNode<JSAny> phi_bb270_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb270_51;
  TNode<IntPtrT> phi_bb270_52;
  TNode<Float32T> tmp584;
  TNode<Uint32T> tmp585;
  TNode<IntPtrT> tmp586;
  if (block270.is_used()) {
    ca_.Bind(&block270, &phi_bb270_20, &phi_bb270_25, &phi_bb270_27, &phi_bb270_28, &phi_bb270_29, &phi_bb270_32, &phi_bb270_33, &phi_bb270_35, &phi_bb270_36, &phi_bb270_37, &phi_bb270_48, &phi_bb270_49, &phi_bb270_51, &phi_bb270_52);
    tmp584 = ca_.CallBuiltin<Float32T>(Builtin::kWasmTaggedToFloat32, tmp455, phi_bb270_49);
    tmp585 = Bitcast_uint32_float32_0(state_, TNode<Float32T>{tmp584});
    tmp586 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp585});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb270_51, phi_bb270_52}, tmp586);
    ca_.Goto(&block271, phi_bb270_20, phi_bb270_25, phi_bb270_27, phi_bb270_28, phi_bb270_29, phi_bb270_32, phi_bb270_33, phi_bb270_35, phi_bb270_36, phi_bb270_37, phi_bb270_48, phi_bb270_49, phi_bb270_51, phi_bb270_52);
  }

  TNode<IntPtrT> phi_bb271_20;
  TNode<IntPtrT> phi_bb271_25;
  TNode<IntPtrT> phi_bb271_27;
  TNode<IntPtrT> phi_bb271_28;
  TNode<IntPtrT> phi_bb271_29;
  TNode<IntPtrT> phi_bb271_32;
  TNode<BoolT> phi_bb271_33;
  TNode<IntPtrT> phi_bb271_35;
  TNode<IntPtrT> phi_bb271_36;
  TNode<BoolT> phi_bb271_37;
  TNode<BoolT> phi_bb271_48;
  TNode<JSAny> phi_bb271_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb271_51;
  TNode<IntPtrT> phi_bb271_52;
  if (block271.is_used()) {
    ca_.Bind(&block271, &phi_bb271_20, &phi_bb271_25, &phi_bb271_27, &phi_bb271_28, &phi_bb271_29, &phi_bb271_32, &phi_bb271_33, &phi_bb271_35, &phi_bb271_36, &phi_bb271_37, &phi_bb271_48, &phi_bb271_49, &phi_bb271_51, &phi_bb271_52);
    ca_.Goto(&block259, phi_bb271_20, phi_bb271_25, tmp560, phi_bb271_27, phi_bb271_28, phi_bb271_29, phi_bb271_32, phi_bb271_33, phi_bb271_35, phi_bb271_36, phi_bb271_37, phi_bb271_48, phi_bb271_49);
  }

  TNode<IntPtrT> phi_bb258_20;
  TNode<IntPtrT> phi_bb258_25;
  TNode<IntPtrT> phi_bb258_26;
  TNode<IntPtrT> phi_bb258_27;
  TNode<IntPtrT> phi_bb258_28;
  TNode<IntPtrT> phi_bb258_29;
  TNode<IntPtrT> phi_bb258_32;
  TNode<BoolT> phi_bb258_33;
  TNode<IntPtrT> phi_bb258_35;
  TNode<IntPtrT> phi_bb258_36;
  TNode<BoolT> phi_bb258_37;
  TNode<BoolT> phi_bb258_48;
  TNode<JSAny> phi_bb258_49;
  TNode<Uint32T> tmp587;
  TNode<BoolT> tmp588;
  if (block258.is_used()) {
    ca_.Bind(&block258, &phi_bb258_20, &phi_bb258_25, &phi_bb258_26, &phi_bb258_27, &phi_bb258_28, &phi_bb258_29, &phi_bb258_32, &phi_bb258_33, &phi_bb258_35, &phi_bb258_36, &phi_bb258_37, &phi_bb258_48, &phi_bb258_49);
    tmp587 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmF64.raw_bit_field());
    tmp588 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp523}, TNode<Uint32T>{tmp587});
    ca_.Branch(tmp588, &block272, std::vector<compiler::Node*>{phi_bb258_20, phi_bb258_25, phi_bb258_26, phi_bb258_27, phi_bb258_28, phi_bb258_29, phi_bb258_32, phi_bb258_33, phi_bb258_35, phi_bb258_36, phi_bb258_37, phi_bb258_48, phi_bb258_49}, &block273, std::vector<compiler::Node*>{phi_bb258_20, phi_bb258_25, phi_bb258_26, phi_bb258_27, phi_bb258_28, phi_bb258_29, phi_bb258_32, phi_bb258_33, phi_bb258_35, phi_bb258_36, phi_bb258_37, phi_bb258_48, phi_bb258_49});
  }

  TNode<IntPtrT> phi_bb272_20;
  TNode<IntPtrT> phi_bb272_25;
  TNode<IntPtrT> phi_bb272_26;
  TNode<IntPtrT> phi_bb272_27;
  TNode<IntPtrT> phi_bb272_28;
  TNode<IntPtrT> phi_bb272_29;
  TNode<IntPtrT> phi_bb272_32;
  TNode<BoolT> phi_bb272_33;
  TNode<IntPtrT> phi_bb272_35;
  TNode<IntPtrT> phi_bb272_36;
  TNode<BoolT> phi_bb272_37;
  TNode<BoolT> phi_bb272_48;
  TNode<JSAny> phi_bb272_49;
  TNode<IntPtrT> tmp589;
  TNode<IntPtrT> tmp590;
  TNode<IntPtrT> tmp591;
  TNode<BoolT> tmp592;
  if (block272.is_used()) {
    ca_.Bind(&block272, &phi_bb272_20, &phi_bb272_25, &phi_bb272_26, &phi_bb272_27, &phi_bb272_28, &phi_bb272_29, &phi_bb272_32, &phi_bb272_33, &phi_bb272_35, &phi_bb272_36, &phi_bb272_37, &phi_bb272_48, &phi_bb272_49);
    tmp589 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp590 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb272_26}, TNode<IntPtrT>{tmp589});
    tmp591 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp592 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb272_26}, TNode<IntPtrT>{tmp591});
    ca_.Branch(tmp592, &block276, std::vector<compiler::Node*>{phi_bb272_20, phi_bb272_25, phi_bb272_27, phi_bb272_28, phi_bb272_29, phi_bb272_32, phi_bb272_33, phi_bb272_35, phi_bb272_36, phi_bb272_37, phi_bb272_48, phi_bb272_49}, &block277, std::vector<compiler::Node*>{phi_bb272_20, phi_bb272_25, phi_bb272_27, phi_bb272_28, phi_bb272_29, phi_bb272_32, phi_bb272_33, phi_bb272_35, phi_bb272_36, phi_bb272_37, phi_bb272_48, phi_bb272_49});
  }

  TNode<IntPtrT> phi_bb276_20;
  TNode<IntPtrT> phi_bb276_25;
  TNode<IntPtrT> phi_bb276_27;
  TNode<IntPtrT> phi_bb276_28;
  TNode<IntPtrT> phi_bb276_29;
  TNode<IntPtrT> phi_bb276_32;
  TNode<BoolT> phi_bb276_33;
  TNode<IntPtrT> phi_bb276_35;
  TNode<IntPtrT> phi_bb276_36;
  TNode<BoolT> phi_bb276_37;
  TNode<BoolT> phi_bb276_48;
  TNode<JSAny> phi_bb276_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp593;
  TNode<IntPtrT> tmp594;
  TNode<IntPtrT> tmp595;
  TNode<IntPtrT> tmp596;
  if (block276.is_used()) {
    ca_.Bind(&block276, &phi_bb276_20, &phi_bb276_25, &phi_bb276_27, &phi_bb276_28, &phi_bb276_29, &phi_bb276_32, &phi_bb276_33, &phi_bb276_35, &phi_bb276_36, &phi_bb276_37, &phi_bb276_48, &phi_bb276_49);
    std::tie(tmp593, tmp594) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb276_28}).Flatten();
    tmp595 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    tmp596 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb276_28}, TNode<IntPtrT>{tmp595});
    ca_.Goto(&block275, phi_bb276_20, phi_bb276_25, phi_bb276_27, tmp596, phi_bb276_29, phi_bb276_32, phi_bb276_33, phi_bb276_35, phi_bb276_36, phi_bb276_37, phi_bb276_48, phi_bb276_49, tmp593, tmp594);
  }

  TNode<IntPtrT> phi_bb277_20;
  TNode<IntPtrT> phi_bb277_25;
  TNode<IntPtrT> phi_bb277_27;
  TNode<IntPtrT> phi_bb277_28;
  TNode<IntPtrT> phi_bb277_29;
  TNode<IntPtrT> phi_bb277_32;
  TNode<BoolT> phi_bb277_33;
  TNode<IntPtrT> phi_bb277_35;
  TNode<IntPtrT> phi_bb277_36;
  TNode<BoolT> phi_bb277_37;
  TNode<BoolT> phi_bb277_48;
  TNode<JSAny> phi_bb277_49;
  if (block277.is_used()) {
    ca_.Bind(&block277, &phi_bb277_20, &phi_bb277_25, &phi_bb277_27, &phi_bb277_28, &phi_bb277_29, &phi_bb277_32, &phi_bb277_33, &phi_bb277_35, &phi_bb277_36, &phi_bb277_37, &phi_bb277_48, &phi_bb277_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block278, phi_bb277_20, phi_bb277_25, phi_bb277_27, phi_bb277_28, phi_bb277_29, phi_bb277_32, phi_bb277_33, phi_bb277_35, phi_bb277_36, phi_bb277_37, phi_bb277_48, phi_bb277_49);
    } else {
      ca_.Goto(&block279, phi_bb277_20, phi_bb277_25, phi_bb277_27, phi_bb277_28, phi_bb277_29, phi_bb277_32, phi_bb277_33, phi_bb277_35, phi_bb277_36, phi_bb277_37, phi_bb277_48, phi_bb277_49);
    }
  }

  TNode<IntPtrT> phi_bb278_20;
  TNode<IntPtrT> phi_bb278_25;
  TNode<IntPtrT> phi_bb278_27;
  TNode<IntPtrT> phi_bb278_28;
  TNode<IntPtrT> phi_bb278_29;
  TNode<IntPtrT> phi_bb278_32;
  TNode<BoolT> phi_bb278_33;
  TNode<IntPtrT> phi_bb278_35;
  TNode<IntPtrT> phi_bb278_36;
  TNode<BoolT> phi_bb278_37;
  TNode<BoolT> phi_bb278_48;
  TNode<JSAny> phi_bb278_49;
  if (block278.is_used()) {
    ca_.Bind(&block278, &phi_bb278_20, &phi_bb278_25, &phi_bb278_27, &phi_bb278_28, &phi_bb278_29, &phi_bb278_32, &phi_bb278_33, &phi_bb278_35, &phi_bb278_36, &phi_bb278_37, &phi_bb278_48, &phi_bb278_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block282, phi_bb278_20, phi_bb278_25, phi_bb278_27, phi_bb278_28, phi_bb278_29, phi_bb278_32, phi_bb278_33, phi_bb278_35, phi_bb278_36, phi_bb278_37, phi_bb278_48, phi_bb278_49);
    } else {
      ca_.Goto(&block283, phi_bb278_20, phi_bb278_25, phi_bb278_27, phi_bb278_28, phi_bb278_29, phi_bb278_32, phi_bb278_33, phi_bb278_35, phi_bb278_36, phi_bb278_37, phi_bb278_48, phi_bb278_49);
    }
  }

  TNode<IntPtrT> phi_bb282_20;
  TNode<IntPtrT> phi_bb282_25;
  TNode<IntPtrT> phi_bb282_27;
  TNode<IntPtrT> phi_bb282_28;
  TNode<IntPtrT> phi_bb282_29;
  TNode<IntPtrT> phi_bb282_32;
  TNode<BoolT> phi_bb282_33;
  TNode<IntPtrT> phi_bb282_35;
  TNode<IntPtrT> phi_bb282_36;
  TNode<BoolT> phi_bb282_37;
  TNode<BoolT> phi_bb282_48;
  TNode<JSAny> phi_bb282_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp597;
  TNode<IntPtrT> tmp598;
  TNode<IntPtrT> tmp599;
  TNode<IntPtrT> tmp600;
  if (block282.is_used()) {
    ca_.Bind(&block282, &phi_bb282_20, &phi_bb282_25, &phi_bb282_27, &phi_bb282_28, &phi_bb282_29, &phi_bb282_32, &phi_bb282_33, &phi_bb282_35, &phi_bb282_36, &phi_bb282_37, &phi_bb282_48, &phi_bb282_49);
    std::tie(tmp597, tmp598) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb282_29}).Flatten();
    tmp599 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp600 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb282_29}, TNode<IntPtrT>{tmp599});
    ca_.Goto(&block281, phi_bb282_20, phi_bb282_25, phi_bb282_27, phi_bb282_28, tmp600, phi_bb282_32, phi_bb282_33, phi_bb282_35, phi_bb282_36, phi_bb282_37, phi_bb282_48, phi_bb282_49, tmp597, tmp598);
  }

  TNode<IntPtrT> phi_bb283_20;
  TNode<IntPtrT> phi_bb283_25;
  TNode<IntPtrT> phi_bb283_27;
  TNode<IntPtrT> phi_bb283_28;
  TNode<IntPtrT> phi_bb283_29;
  TNode<IntPtrT> phi_bb283_32;
  TNode<BoolT> phi_bb283_33;
  TNode<IntPtrT> phi_bb283_35;
  TNode<IntPtrT> phi_bb283_36;
  TNode<BoolT> phi_bb283_37;
  TNode<BoolT> phi_bb283_48;
  TNode<JSAny> phi_bb283_49;
  TNode<IntPtrT> tmp601;
  TNode<BoolT> tmp602;
  if (block283.is_used()) {
    ca_.Bind(&block283, &phi_bb283_20, &phi_bb283_25, &phi_bb283_27, &phi_bb283_28, &phi_bb283_29, &phi_bb283_32, &phi_bb283_33, &phi_bb283_35, &phi_bb283_36, &phi_bb283_37, &phi_bb283_48, &phi_bb283_49);
    tmp601 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp602 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb283_32}, TNode<IntPtrT>{tmp601});
    ca_.Branch(tmp602, &block285, std::vector<compiler::Node*>{phi_bb283_20, phi_bb283_25, phi_bb283_27, phi_bb283_28, phi_bb283_29, phi_bb283_32, phi_bb283_33, phi_bb283_35, phi_bb283_36, phi_bb283_37, phi_bb283_48, phi_bb283_49}, &block286, std::vector<compiler::Node*>{phi_bb283_20, phi_bb283_25, phi_bb283_27, phi_bb283_28, phi_bb283_29, phi_bb283_32, phi_bb283_33, phi_bb283_35, phi_bb283_36, phi_bb283_37, phi_bb283_48, phi_bb283_49});
  }

  TNode<IntPtrT> phi_bb285_20;
  TNode<IntPtrT> phi_bb285_25;
  TNode<IntPtrT> phi_bb285_27;
  TNode<IntPtrT> phi_bb285_28;
  TNode<IntPtrT> phi_bb285_29;
  TNode<IntPtrT> phi_bb285_32;
  TNode<BoolT> phi_bb285_33;
  TNode<IntPtrT> phi_bb285_35;
  TNode<IntPtrT> phi_bb285_36;
  TNode<BoolT> phi_bb285_37;
  TNode<BoolT> phi_bb285_48;
  TNode<JSAny> phi_bb285_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp603;
  TNode<IntPtrT> tmp604;
  TNode<IntPtrT> tmp605;
  TNode<BoolT> tmp606;
  if (block285.is_used()) {
    ca_.Bind(&block285, &phi_bb285_20, &phi_bb285_25, &phi_bb285_27, &phi_bb285_28, &phi_bb285_29, &phi_bb285_32, &phi_bb285_33, &phi_bb285_35, &phi_bb285_36, &phi_bb285_37, &phi_bb285_48, &phi_bb285_49);
    std::tie(tmp603, tmp604) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb285_32}).Flatten();
    tmp605 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp606 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block281, phi_bb285_20, phi_bb285_25, phi_bb285_27, phi_bb285_28, phi_bb285_29, tmp605, tmp606, phi_bb285_35, phi_bb285_36, phi_bb285_37, phi_bb285_48, phi_bb285_49, tmp603, tmp604);
  }

  TNode<IntPtrT> phi_bb286_20;
  TNode<IntPtrT> phi_bb286_25;
  TNode<IntPtrT> phi_bb286_27;
  TNode<IntPtrT> phi_bb286_28;
  TNode<IntPtrT> phi_bb286_29;
  TNode<IntPtrT> phi_bb286_32;
  TNode<BoolT> phi_bb286_33;
  TNode<IntPtrT> phi_bb286_35;
  TNode<IntPtrT> phi_bb286_36;
  TNode<BoolT> phi_bb286_37;
  TNode<BoolT> phi_bb286_48;
  TNode<JSAny> phi_bb286_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp607;
  TNode<IntPtrT> tmp608;
  TNode<IntPtrT> tmp609;
  TNode<IntPtrT> tmp610;
  TNode<IntPtrT> tmp611;
  TNode<IntPtrT> tmp612;
  TNode<BoolT> tmp613;
  if (block286.is_used()) {
    ca_.Bind(&block286, &phi_bb286_20, &phi_bb286_25, &phi_bb286_27, &phi_bb286_28, &phi_bb286_29, &phi_bb286_32, &phi_bb286_33, &phi_bb286_35, &phi_bb286_36, &phi_bb286_37, &phi_bb286_48, &phi_bb286_49);
    std::tie(tmp607, tmp608) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb286_29}).Flatten();
    tmp609 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp610 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb286_29}, TNode<IntPtrT>{tmp609});
    tmp611 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp612 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp610}, TNode<IntPtrT>{tmp611});
    tmp613 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block281, phi_bb286_20, phi_bb286_25, phi_bb286_27, phi_bb286_28, tmp612, tmp610, tmp613, phi_bb286_35, phi_bb286_36, phi_bb286_37, phi_bb286_48, phi_bb286_49, tmp607, tmp608);
  }

  TNode<IntPtrT> phi_bb281_20;
  TNode<IntPtrT> phi_bb281_25;
  TNode<IntPtrT> phi_bb281_27;
  TNode<IntPtrT> phi_bb281_28;
  TNode<IntPtrT> phi_bb281_29;
  TNode<IntPtrT> phi_bb281_32;
  TNode<BoolT> phi_bb281_33;
  TNode<IntPtrT> phi_bb281_35;
  TNode<IntPtrT> phi_bb281_36;
  TNode<BoolT> phi_bb281_37;
  TNode<BoolT> phi_bb281_48;
  TNode<JSAny> phi_bb281_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb281_51;
  TNode<IntPtrT> phi_bb281_52;
  if (block281.is_used()) {
    ca_.Bind(&block281, &phi_bb281_20, &phi_bb281_25, &phi_bb281_27, &phi_bb281_28, &phi_bb281_29, &phi_bb281_32, &phi_bb281_33, &phi_bb281_35, &phi_bb281_36, &phi_bb281_37, &phi_bb281_48, &phi_bb281_49, &phi_bb281_51, &phi_bb281_52);
    ca_.Goto(&block275, phi_bb281_20, phi_bb281_25, phi_bb281_27, phi_bb281_28, phi_bb281_29, phi_bb281_32, phi_bb281_33, phi_bb281_35, phi_bb281_36, phi_bb281_37, phi_bb281_48, phi_bb281_49, phi_bb281_51, phi_bb281_52);
  }

  TNode<IntPtrT> phi_bb279_20;
  TNode<IntPtrT> phi_bb279_25;
  TNode<IntPtrT> phi_bb279_27;
  TNode<IntPtrT> phi_bb279_28;
  TNode<IntPtrT> phi_bb279_29;
  TNode<IntPtrT> phi_bb279_32;
  TNode<BoolT> phi_bb279_33;
  TNode<IntPtrT> phi_bb279_35;
  TNode<IntPtrT> phi_bb279_36;
  TNode<BoolT> phi_bb279_37;
  TNode<BoolT> phi_bb279_48;
  TNode<JSAny> phi_bb279_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp614;
  TNode<IntPtrT> tmp615;
  TNode<IntPtrT> tmp616;
  TNode<IntPtrT> tmp617;
  TNode<BoolT> tmp618;
  if (block279.is_used()) {
    ca_.Bind(&block279, &phi_bb279_20, &phi_bb279_25, &phi_bb279_27, &phi_bb279_28, &phi_bb279_29, &phi_bb279_32, &phi_bb279_33, &phi_bb279_35, &phi_bb279_36, &phi_bb279_37, &phi_bb279_48, &phi_bb279_49);
    std::tie(tmp614, tmp615) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb279_29}).Flatten();
    tmp616 = FromConstexpr_intptr_constexpr_int31_0(state_, (CodeStubAssembler(state_).ConstexprInt31Mul((FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull))), (SizeOf_intptr_0(state_)))));
    tmp617 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb279_29}, TNode<IntPtrT>{tmp616});
    tmp618 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block275, phi_bb279_20, phi_bb279_25, phi_bb279_27, phi_bb279_28, tmp617, phi_bb279_32, tmp618, phi_bb279_35, phi_bb279_36, phi_bb279_37, phi_bb279_48, phi_bb279_49, tmp614, tmp615);
  }

  TNode<IntPtrT> phi_bb275_20;
  TNode<IntPtrT> phi_bb275_25;
  TNode<IntPtrT> phi_bb275_27;
  TNode<IntPtrT> phi_bb275_28;
  TNode<IntPtrT> phi_bb275_29;
  TNode<IntPtrT> phi_bb275_32;
  TNode<BoolT> phi_bb275_33;
  TNode<IntPtrT> phi_bb275_35;
  TNode<IntPtrT> phi_bb275_36;
  TNode<BoolT> phi_bb275_37;
  TNode<BoolT> phi_bb275_48;
  TNode<JSAny> phi_bb275_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb275_51;
  TNode<IntPtrT> phi_bb275_52;
  TNode<Union<HeapObject, TaggedIndex>> tmp619;
  TNode<IntPtrT> tmp620;
  TNode<Float64T> tmp621;
  TNode<Float64T> tmp622;
  if (block275.is_used()) {
    ca_.Bind(&block275, &phi_bb275_20, &phi_bb275_25, &phi_bb275_27, &phi_bb275_28, &phi_bb275_29, &phi_bb275_32, &phi_bb275_33, &phi_bb275_35, &phi_bb275_36, &phi_bb275_37, &phi_bb275_48, &phi_bb275_49, &phi_bb275_51, &phi_bb275_52);
    std::tie(tmp619, tmp620) = RefCast_float64_0(state_, TorqueStructReference_intptr_0{TNode<Union<HeapObject, TaggedIndex>>{phi_bb275_51}, TNode<IntPtrT>{phi_bb275_52}, TorqueStructUnsafe_0{}}).Flatten();
    tmp621 = CodeStubAssembler(state_).ChangeTaggedToFloat64(TNode<Context>{tmp455}, TNode<JSAny>{phi_bb275_49});
    tmp622 = CodeStubAssembler(state_).Float64SilenceNaN(TNode<Float64T>{tmp621});
    CodeStubAssembler(state_).StoreReference<Float64T>(CodeStubAssembler::Reference{tmp619, tmp620}, tmp622);
    ca_.Goto(&block274, phi_bb275_20, phi_bb275_25, tmp590, phi_bb275_27, phi_bb275_28, phi_bb275_29, phi_bb275_32, phi_bb275_33, phi_bb275_35, phi_bb275_36, phi_bb275_37, phi_bb275_48, phi_bb275_49);
  }

  TNode<IntPtrT> phi_bb273_20;
  TNode<IntPtrT> phi_bb273_25;
  TNode<IntPtrT> phi_bb273_26;
  TNode<IntPtrT> phi_bb273_27;
  TNode<IntPtrT> phi_bb273_28;
  TNode<IntPtrT> phi_bb273_29;
  TNode<IntPtrT> phi_bb273_32;
  TNode<BoolT> phi_bb273_33;
  TNode<IntPtrT> phi_bb273_35;
  TNode<IntPtrT> phi_bb273_36;
  TNode<BoolT> phi_bb273_37;
  TNode<BoolT> phi_bb273_48;
  TNode<JSAny> phi_bb273_49;
  TNode<Uint32T> tmp623;
  TNode<BoolT> tmp624;
  if (block273.is_used()) {
    ca_.Bind(&block273, &phi_bb273_20, &phi_bb273_25, &phi_bb273_26, &phi_bb273_27, &phi_bb273_28, &phi_bb273_29, &phi_bb273_32, &phi_bb273_33, &phi_bb273_35, &phi_bb273_36, &phi_bb273_37, &phi_bb273_48, &phi_bb273_49);
    tmp623 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::kWasmI64.raw_bit_field());
    tmp624 = CodeStubAssembler(state_).Word32Equal(TNode<Uint32T>{tmp523}, TNode<Uint32T>{tmp623});
    ca_.Branch(tmp624, &block287, std::vector<compiler::Node*>{phi_bb273_20, phi_bb273_25, phi_bb273_26, phi_bb273_27, phi_bb273_28, phi_bb273_29, phi_bb273_32, phi_bb273_33, phi_bb273_35, phi_bb273_36, phi_bb273_37, phi_bb273_48, phi_bb273_49}, &block288, std::vector<compiler::Node*>{phi_bb273_20, phi_bb273_25, phi_bb273_26, phi_bb273_27, phi_bb273_28, phi_bb273_29, phi_bb273_32, phi_bb273_33, phi_bb273_35, phi_bb273_36, phi_bb273_37, phi_bb273_48, phi_bb273_49});
  }

  TNode<IntPtrT> phi_bb287_20;
  TNode<IntPtrT> phi_bb287_25;
  TNode<IntPtrT> phi_bb287_26;
  TNode<IntPtrT> phi_bb287_27;
  TNode<IntPtrT> phi_bb287_28;
  TNode<IntPtrT> phi_bb287_29;
  TNode<IntPtrT> phi_bb287_32;
  TNode<BoolT> phi_bb287_33;
  TNode<IntPtrT> phi_bb287_35;
  TNode<IntPtrT> phi_bb287_36;
  TNode<BoolT> phi_bb287_37;
  TNode<BoolT> phi_bb287_48;
  TNode<JSAny> phi_bb287_49;
  if (block287.is_used()) {
    ca_.Bind(&block287, &phi_bb287_20, &phi_bb287_25, &phi_bb287_26, &phi_bb287_27, &phi_bb287_28, &phi_bb287_29, &phi_bb287_32, &phi_bb287_33, &phi_bb287_35, &phi_bb287_36, &phi_bb287_37, &phi_bb287_48, &phi_bb287_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block290, phi_bb287_20, phi_bb287_25, phi_bb287_26, phi_bb287_27, phi_bb287_28, phi_bb287_29, phi_bb287_32, phi_bb287_33, phi_bb287_35, phi_bb287_36, phi_bb287_37, phi_bb287_48, phi_bb287_49);
    } else {
      ca_.Goto(&block291, phi_bb287_20, phi_bb287_25, phi_bb287_26, phi_bb287_27, phi_bb287_28, phi_bb287_29, phi_bb287_32, phi_bb287_33, phi_bb287_35, phi_bb287_36, phi_bb287_37, phi_bb287_48, phi_bb287_49);
    }
  }

  TNode<IntPtrT> phi_bb290_20;
  TNode<IntPtrT> phi_bb290_25;
  TNode<IntPtrT> phi_bb290_26;
  TNode<IntPtrT> phi_bb290_27;
  TNode<IntPtrT> phi_bb290_28;
  TNode<IntPtrT> phi_bb290_29;
  TNode<IntPtrT> phi_bb290_32;
  TNode<BoolT> phi_bb290_33;
  TNode<IntPtrT> phi_bb290_35;
  TNode<IntPtrT> phi_bb290_36;
  TNode<BoolT> phi_bb290_37;
  TNode<BoolT> phi_bb290_48;
  TNode<JSAny> phi_bb290_49;
  TNode<IntPtrT> tmp625;
  TNode<IntPtrT> tmp626;
  TNode<IntPtrT> tmp627;
  TNode<BoolT> tmp628;
  if (block290.is_used()) {
    ca_.Bind(&block290, &phi_bb290_20, &phi_bb290_25, &phi_bb290_26, &phi_bb290_27, &phi_bb290_28, &phi_bb290_29, &phi_bb290_32, &phi_bb290_33, &phi_bb290_35, &phi_bb290_36, &phi_bb290_37, &phi_bb290_48, &phi_bb290_49);
    tmp625 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp626 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb290_25}, TNode<IntPtrT>{tmp625});
    tmp627 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp628 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb290_25}, TNode<IntPtrT>{tmp627});
    ca_.Branch(tmp628, &block294, std::vector<compiler::Node*>{phi_bb290_20, phi_bb290_26, phi_bb290_27, phi_bb290_28, phi_bb290_29, phi_bb290_32, phi_bb290_33, phi_bb290_35, phi_bb290_36, phi_bb290_37, phi_bb290_48, phi_bb290_49}, &block295, std::vector<compiler::Node*>{phi_bb290_20, phi_bb290_26, phi_bb290_27, phi_bb290_28, phi_bb290_29, phi_bb290_32, phi_bb290_33, phi_bb290_35, phi_bb290_36, phi_bb290_37, phi_bb290_48, phi_bb290_49});
  }

  TNode<IntPtrT> phi_bb294_20;
  TNode<IntPtrT> phi_bb294_26;
  TNode<IntPtrT> phi_bb294_27;
  TNode<IntPtrT> phi_bb294_28;
  TNode<IntPtrT> phi_bb294_29;
  TNode<IntPtrT> phi_bb294_32;
  TNode<BoolT> phi_bb294_33;
  TNode<IntPtrT> phi_bb294_35;
  TNode<IntPtrT> phi_bb294_36;
  TNode<BoolT> phi_bb294_37;
  TNode<BoolT> phi_bb294_48;
  TNode<JSAny> phi_bb294_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp629;
  TNode<IntPtrT> tmp630;
  TNode<IntPtrT> tmp631;
  TNode<IntPtrT> tmp632;
  if (block294.is_used()) {
    ca_.Bind(&block294, &phi_bb294_20, &phi_bb294_26, &phi_bb294_27, &phi_bb294_28, &phi_bb294_29, &phi_bb294_32, &phi_bb294_33, &phi_bb294_35, &phi_bb294_36, &phi_bb294_37, &phi_bb294_48, &phi_bb294_49);
    std::tie(tmp629, tmp630) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb294_27}).Flatten();
    tmp631 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp632 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb294_27}, TNode<IntPtrT>{tmp631});
    ca_.Goto(&block293, phi_bb294_20, phi_bb294_26, tmp632, phi_bb294_28, phi_bb294_29, phi_bb294_32, phi_bb294_33, phi_bb294_35, phi_bb294_36, phi_bb294_37, phi_bb294_48, phi_bb294_49, tmp629, tmp630);
  }

  TNode<IntPtrT> phi_bb295_20;
  TNode<IntPtrT> phi_bb295_26;
  TNode<IntPtrT> phi_bb295_27;
  TNode<IntPtrT> phi_bb295_28;
  TNode<IntPtrT> phi_bb295_29;
  TNode<IntPtrT> phi_bb295_32;
  TNode<BoolT> phi_bb295_33;
  TNode<IntPtrT> phi_bb295_35;
  TNode<IntPtrT> phi_bb295_36;
  TNode<BoolT> phi_bb295_37;
  TNode<BoolT> phi_bb295_48;
  TNode<JSAny> phi_bb295_49;
  if (block295.is_used()) {
    ca_.Bind(&block295, &phi_bb295_20, &phi_bb295_26, &phi_bb295_27, &phi_bb295_28, &phi_bb295_29, &phi_bb295_32, &phi_bb295_33, &phi_bb295_35, &phi_bb295_36, &phi_bb295_37, &phi_bb295_48, &phi_bb295_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block297, phi_bb295_20, phi_bb295_26, phi_bb295_27, phi_bb295_28, phi_bb295_29, phi_bb295_32, phi_bb295_33, phi_bb295_35, phi_bb295_36, phi_bb295_37, phi_bb295_48, phi_bb295_49);
    } else {
      ca_.Goto(&block298, phi_bb295_20, phi_bb295_26, phi_bb295_27, phi_bb295_28, phi_bb295_29, phi_bb295_32, phi_bb295_33, phi_bb295_35, phi_bb295_36, phi_bb295_37, phi_bb295_48, phi_bb295_49);
    }
  }

  TNode<IntPtrT> phi_bb297_20;
  TNode<IntPtrT> phi_bb297_26;
  TNode<IntPtrT> phi_bb297_27;
  TNode<IntPtrT> phi_bb297_28;
  TNode<IntPtrT> phi_bb297_29;
  TNode<IntPtrT> phi_bb297_32;
  TNode<BoolT> phi_bb297_33;
  TNode<IntPtrT> phi_bb297_35;
  TNode<IntPtrT> phi_bb297_36;
  TNode<BoolT> phi_bb297_37;
  TNode<BoolT> phi_bb297_48;
  TNode<JSAny> phi_bb297_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp633;
  TNode<IntPtrT> tmp634;
  TNode<IntPtrT> tmp635;
  TNode<IntPtrT> tmp636;
  if (block297.is_used()) {
    ca_.Bind(&block297, &phi_bb297_20, &phi_bb297_26, &phi_bb297_27, &phi_bb297_28, &phi_bb297_29, &phi_bb297_32, &phi_bb297_33, &phi_bb297_35, &phi_bb297_36, &phi_bb297_37, &phi_bb297_48, &phi_bb297_49);
    std::tie(tmp633, tmp634) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb297_29}).Flatten();
    tmp635 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp636 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb297_29}, TNode<IntPtrT>{tmp635});
    ca_.Goto(&block296, phi_bb297_20, phi_bb297_26, phi_bb297_27, phi_bb297_28, tmp636, phi_bb297_32, phi_bb297_33, phi_bb297_35, phi_bb297_36, phi_bb297_37, phi_bb297_48, phi_bb297_49, tmp633, tmp634);
  }

  TNode<IntPtrT> phi_bb298_20;
  TNode<IntPtrT> phi_bb298_26;
  TNode<IntPtrT> phi_bb298_27;
  TNode<IntPtrT> phi_bb298_28;
  TNode<IntPtrT> phi_bb298_29;
  TNode<IntPtrT> phi_bb298_32;
  TNode<BoolT> phi_bb298_33;
  TNode<IntPtrT> phi_bb298_35;
  TNode<IntPtrT> phi_bb298_36;
  TNode<BoolT> phi_bb298_37;
  TNode<BoolT> phi_bb298_48;
  TNode<JSAny> phi_bb298_49;
  TNode<IntPtrT> tmp637;
  TNode<BoolT> tmp638;
  if (block298.is_used()) {
    ca_.Bind(&block298, &phi_bb298_20, &phi_bb298_26, &phi_bb298_27, &phi_bb298_28, &phi_bb298_29, &phi_bb298_32, &phi_bb298_33, &phi_bb298_35, &phi_bb298_36, &phi_bb298_37, &phi_bb298_48, &phi_bb298_49);
    tmp637 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp638 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb298_32}, TNode<IntPtrT>{tmp637});
    ca_.Branch(tmp638, &block300, std::vector<compiler::Node*>{phi_bb298_20, phi_bb298_26, phi_bb298_27, phi_bb298_28, phi_bb298_29, phi_bb298_32, phi_bb298_33, phi_bb298_35, phi_bb298_36, phi_bb298_37, phi_bb298_48, phi_bb298_49}, &block301, std::vector<compiler::Node*>{phi_bb298_20, phi_bb298_26, phi_bb298_27, phi_bb298_28, phi_bb298_29, phi_bb298_32, phi_bb298_33, phi_bb298_35, phi_bb298_36, phi_bb298_37, phi_bb298_48, phi_bb298_49});
  }

  TNode<IntPtrT> phi_bb300_20;
  TNode<IntPtrT> phi_bb300_26;
  TNode<IntPtrT> phi_bb300_27;
  TNode<IntPtrT> phi_bb300_28;
  TNode<IntPtrT> phi_bb300_29;
  TNode<IntPtrT> phi_bb300_32;
  TNode<BoolT> phi_bb300_33;
  TNode<IntPtrT> phi_bb300_35;
  TNode<IntPtrT> phi_bb300_36;
  TNode<BoolT> phi_bb300_37;
  TNode<BoolT> phi_bb300_48;
  TNode<JSAny> phi_bb300_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp639;
  TNode<IntPtrT> tmp640;
  TNode<IntPtrT> tmp641;
  TNode<BoolT> tmp642;
  if (block300.is_used()) {
    ca_.Bind(&block300, &phi_bb300_20, &phi_bb300_26, &phi_bb300_27, &phi_bb300_28, &phi_bb300_29, &phi_bb300_32, &phi_bb300_33, &phi_bb300_35, &phi_bb300_36, &phi_bb300_37, &phi_bb300_48, &phi_bb300_49);
    std::tie(tmp639, tmp640) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb300_32}).Flatten();
    tmp641 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp642 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block296, phi_bb300_20, phi_bb300_26, phi_bb300_27, phi_bb300_28, phi_bb300_29, tmp641, tmp642, phi_bb300_35, phi_bb300_36, phi_bb300_37, phi_bb300_48, phi_bb300_49, tmp639, tmp640);
  }

  TNode<IntPtrT> phi_bb301_20;
  TNode<IntPtrT> phi_bb301_26;
  TNode<IntPtrT> phi_bb301_27;
  TNode<IntPtrT> phi_bb301_28;
  TNode<IntPtrT> phi_bb301_29;
  TNode<IntPtrT> phi_bb301_32;
  TNode<BoolT> phi_bb301_33;
  TNode<IntPtrT> phi_bb301_35;
  TNode<IntPtrT> phi_bb301_36;
  TNode<BoolT> phi_bb301_37;
  TNode<BoolT> phi_bb301_48;
  TNode<JSAny> phi_bb301_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp643;
  TNode<IntPtrT> tmp644;
  TNode<IntPtrT> tmp645;
  TNode<IntPtrT> tmp646;
  TNode<IntPtrT> tmp647;
  TNode<IntPtrT> tmp648;
  TNode<BoolT> tmp649;
  if (block301.is_used()) {
    ca_.Bind(&block301, &phi_bb301_20, &phi_bb301_26, &phi_bb301_27, &phi_bb301_28, &phi_bb301_29, &phi_bb301_32, &phi_bb301_33, &phi_bb301_35, &phi_bb301_36, &phi_bb301_37, &phi_bb301_48, &phi_bb301_49);
    std::tie(tmp643, tmp644) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb301_29}).Flatten();
    tmp645 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp646 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb301_29}, TNode<IntPtrT>{tmp645});
    tmp647 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp648 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp646}, TNode<IntPtrT>{tmp647});
    tmp649 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block296, phi_bb301_20, phi_bb301_26, phi_bb301_27, phi_bb301_28, tmp648, tmp646, tmp649, phi_bb301_35, phi_bb301_36, phi_bb301_37, phi_bb301_48, phi_bb301_49, tmp643, tmp644);
  }

  TNode<IntPtrT> phi_bb296_20;
  TNode<IntPtrT> phi_bb296_26;
  TNode<IntPtrT> phi_bb296_27;
  TNode<IntPtrT> phi_bb296_28;
  TNode<IntPtrT> phi_bb296_29;
  TNode<IntPtrT> phi_bb296_32;
  TNode<BoolT> phi_bb296_33;
  TNode<IntPtrT> phi_bb296_35;
  TNode<IntPtrT> phi_bb296_36;
  TNode<BoolT> phi_bb296_37;
  TNode<BoolT> phi_bb296_48;
  TNode<JSAny> phi_bb296_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb296_51;
  TNode<IntPtrT> phi_bb296_52;
  if (block296.is_used()) {
    ca_.Bind(&block296, &phi_bb296_20, &phi_bb296_26, &phi_bb296_27, &phi_bb296_28, &phi_bb296_29, &phi_bb296_32, &phi_bb296_33, &phi_bb296_35, &phi_bb296_36, &phi_bb296_37, &phi_bb296_48, &phi_bb296_49, &phi_bb296_51, &phi_bb296_52);
    ca_.Goto(&block293, phi_bb296_20, phi_bb296_26, phi_bb296_27, phi_bb296_28, phi_bb296_29, phi_bb296_32, phi_bb296_33, phi_bb296_35, phi_bb296_36, phi_bb296_37, phi_bb296_48, phi_bb296_49, phi_bb296_51, phi_bb296_52);
  }

  TNode<IntPtrT> phi_bb293_20;
  TNode<IntPtrT> phi_bb293_26;
  TNode<IntPtrT> phi_bb293_27;
  TNode<IntPtrT> phi_bb293_28;
  TNode<IntPtrT> phi_bb293_29;
  TNode<IntPtrT> phi_bb293_32;
  TNode<BoolT> phi_bb293_33;
  TNode<IntPtrT> phi_bb293_35;
  TNode<IntPtrT> phi_bb293_36;
  TNode<BoolT> phi_bb293_37;
  TNode<BoolT> phi_bb293_48;
  TNode<JSAny> phi_bb293_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb293_51;
  TNode<IntPtrT> phi_bb293_52;
  TNode<IntPtrT> tmp650;
  if (block293.is_used()) {
    ca_.Bind(&block293, &phi_bb293_20, &phi_bb293_26, &phi_bb293_27, &phi_bb293_28, &phi_bb293_29, &phi_bb293_32, &phi_bb293_33, &phi_bb293_35, &phi_bb293_36, &phi_bb293_37, &phi_bb293_48, &phi_bb293_49, &phi_bb293_51, &phi_bb293_52);
    tmp650 = TruncateBigIntToI64_0(state_, TNode<Context>{tmp455}, TNode<JSAny>{phi_bb293_49});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb293_51, phi_bb293_52}, tmp650);
    ca_.Goto(&block292, phi_bb293_20, tmp626, phi_bb293_26, phi_bb293_27, phi_bb293_28, phi_bb293_29, phi_bb293_32, phi_bb293_33, phi_bb293_35, phi_bb293_36, phi_bb293_37, phi_bb293_48, phi_bb293_49);
  }

  TNode<IntPtrT> phi_bb291_20;
  TNode<IntPtrT> phi_bb291_25;
  TNode<IntPtrT> phi_bb291_26;
  TNode<IntPtrT> phi_bb291_27;
  TNode<IntPtrT> phi_bb291_28;
  TNode<IntPtrT> phi_bb291_29;
  TNode<IntPtrT> phi_bb291_32;
  TNode<BoolT> phi_bb291_33;
  TNode<IntPtrT> phi_bb291_35;
  TNode<IntPtrT> phi_bb291_36;
  TNode<BoolT> phi_bb291_37;
  TNode<BoolT> phi_bb291_48;
  TNode<JSAny> phi_bb291_49;
  TNode<IntPtrT> tmp651;
  TNode<IntPtrT> tmp652;
  TNode<IntPtrT> tmp653;
  TNode<BoolT> tmp654;
  if (block291.is_used()) {
    ca_.Bind(&block291, &phi_bb291_20, &phi_bb291_25, &phi_bb291_26, &phi_bb291_27, &phi_bb291_28, &phi_bb291_29, &phi_bb291_32, &phi_bb291_33, &phi_bb291_35, &phi_bb291_36, &phi_bb291_37, &phi_bb291_48, &phi_bb291_49);
    tmp651 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp652 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb291_25}, TNode<IntPtrT>{tmp651});
    tmp653 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp654 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb291_25}, TNode<IntPtrT>{tmp653});
    ca_.Branch(tmp654, &block303, std::vector<compiler::Node*>{phi_bb291_20, phi_bb291_26, phi_bb291_27, phi_bb291_28, phi_bb291_29, phi_bb291_32, phi_bb291_33, phi_bb291_35, phi_bb291_36, phi_bb291_37, phi_bb291_48, phi_bb291_49}, &block304, std::vector<compiler::Node*>{phi_bb291_20, phi_bb291_26, phi_bb291_27, phi_bb291_28, phi_bb291_29, phi_bb291_32, phi_bb291_33, phi_bb291_35, phi_bb291_36, phi_bb291_37, phi_bb291_48, phi_bb291_49});
  }

  TNode<IntPtrT> phi_bb303_20;
  TNode<IntPtrT> phi_bb303_26;
  TNode<IntPtrT> phi_bb303_27;
  TNode<IntPtrT> phi_bb303_28;
  TNode<IntPtrT> phi_bb303_29;
  TNode<IntPtrT> phi_bb303_32;
  TNode<BoolT> phi_bb303_33;
  TNode<IntPtrT> phi_bb303_35;
  TNode<IntPtrT> phi_bb303_36;
  TNode<BoolT> phi_bb303_37;
  TNode<BoolT> phi_bb303_48;
  TNode<JSAny> phi_bb303_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp655;
  TNode<IntPtrT> tmp656;
  TNode<IntPtrT> tmp657;
  TNode<IntPtrT> tmp658;
  if (block303.is_used()) {
    ca_.Bind(&block303, &phi_bb303_20, &phi_bb303_26, &phi_bb303_27, &phi_bb303_28, &phi_bb303_29, &phi_bb303_32, &phi_bb303_33, &phi_bb303_35, &phi_bb303_36, &phi_bb303_37, &phi_bb303_48, &phi_bb303_49);
    std::tie(tmp655, tmp656) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb303_27}).Flatten();
    tmp657 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp658 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb303_27}, TNode<IntPtrT>{tmp657});
    ca_.Goto(&block302, phi_bb303_20, phi_bb303_26, tmp658, phi_bb303_28, phi_bb303_29, phi_bb303_32, phi_bb303_33, phi_bb303_35, phi_bb303_36, phi_bb303_37, phi_bb303_48, phi_bb303_49, tmp655, tmp656);
  }

  TNode<IntPtrT> phi_bb304_20;
  TNode<IntPtrT> phi_bb304_26;
  TNode<IntPtrT> phi_bb304_27;
  TNode<IntPtrT> phi_bb304_28;
  TNode<IntPtrT> phi_bb304_29;
  TNode<IntPtrT> phi_bb304_32;
  TNode<BoolT> phi_bb304_33;
  TNode<IntPtrT> phi_bb304_35;
  TNode<IntPtrT> phi_bb304_36;
  TNode<BoolT> phi_bb304_37;
  TNode<BoolT> phi_bb304_48;
  TNode<JSAny> phi_bb304_49;
  if (block304.is_used()) {
    ca_.Bind(&block304, &phi_bb304_20, &phi_bb304_26, &phi_bb304_27, &phi_bb304_28, &phi_bb304_29, &phi_bb304_32, &phi_bb304_33, &phi_bb304_35, &phi_bb304_36, &phi_bb304_37, &phi_bb304_48, &phi_bb304_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block306, phi_bb304_20, phi_bb304_26, phi_bb304_27, phi_bb304_28, phi_bb304_29, phi_bb304_32, phi_bb304_33, phi_bb304_35, phi_bb304_36, phi_bb304_37, phi_bb304_48, phi_bb304_49);
    } else {
      ca_.Goto(&block307, phi_bb304_20, phi_bb304_26, phi_bb304_27, phi_bb304_28, phi_bb304_29, phi_bb304_32, phi_bb304_33, phi_bb304_35, phi_bb304_36, phi_bb304_37, phi_bb304_48, phi_bb304_49);
    }
  }

  TNode<IntPtrT> phi_bb306_20;
  TNode<IntPtrT> phi_bb306_26;
  TNode<IntPtrT> phi_bb306_27;
  TNode<IntPtrT> phi_bb306_28;
  TNode<IntPtrT> phi_bb306_29;
  TNode<IntPtrT> phi_bb306_32;
  TNode<BoolT> phi_bb306_33;
  TNode<IntPtrT> phi_bb306_35;
  TNode<IntPtrT> phi_bb306_36;
  TNode<BoolT> phi_bb306_37;
  TNode<BoolT> phi_bb306_48;
  TNode<JSAny> phi_bb306_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp659;
  TNode<IntPtrT> tmp660;
  TNode<IntPtrT> tmp661;
  TNode<IntPtrT> tmp662;
  if (block306.is_used()) {
    ca_.Bind(&block306, &phi_bb306_20, &phi_bb306_26, &phi_bb306_27, &phi_bb306_28, &phi_bb306_29, &phi_bb306_32, &phi_bb306_33, &phi_bb306_35, &phi_bb306_36, &phi_bb306_37, &phi_bb306_48, &phi_bb306_49);
    std::tie(tmp659, tmp660) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb306_29}).Flatten();
    tmp661 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp662 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb306_29}, TNode<IntPtrT>{tmp661});
    ca_.Goto(&block305, phi_bb306_20, phi_bb306_26, phi_bb306_27, phi_bb306_28, tmp662, phi_bb306_32, phi_bb306_33, phi_bb306_35, phi_bb306_36, phi_bb306_37, phi_bb306_48, phi_bb306_49, tmp659, tmp660);
  }

  TNode<IntPtrT> phi_bb307_20;
  TNode<IntPtrT> phi_bb307_26;
  TNode<IntPtrT> phi_bb307_27;
  TNode<IntPtrT> phi_bb307_28;
  TNode<IntPtrT> phi_bb307_29;
  TNode<IntPtrT> phi_bb307_32;
  TNode<BoolT> phi_bb307_33;
  TNode<IntPtrT> phi_bb307_35;
  TNode<IntPtrT> phi_bb307_36;
  TNode<BoolT> phi_bb307_37;
  TNode<BoolT> phi_bb307_48;
  TNode<JSAny> phi_bb307_49;
  TNode<IntPtrT> tmp663;
  TNode<BoolT> tmp664;
  if (block307.is_used()) {
    ca_.Bind(&block307, &phi_bb307_20, &phi_bb307_26, &phi_bb307_27, &phi_bb307_28, &phi_bb307_29, &phi_bb307_32, &phi_bb307_33, &phi_bb307_35, &phi_bb307_36, &phi_bb307_37, &phi_bb307_48, &phi_bb307_49);
    tmp663 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp664 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb307_32}, TNode<IntPtrT>{tmp663});
    ca_.Branch(tmp664, &block309, std::vector<compiler::Node*>{phi_bb307_20, phi_bb307_26, phi_bb307_27, phi_bb307_28, phi_bb307_29, phi_bb307_32, phi_bb307_33, phi_bb307_35, phi_bb307_36, phi_bb307_37, phi_bb307_48, phi_bb307_49}, &block310, std::vector<compiler::Node*>{phi_bb307_20, phi_bb307_26, phi_bb307_27, phi_bb307_28, phi_bb307_29, phi_bb307_32, phi_bb307_33, phi_bb307_35, phi_bb307_36, phi_bb307_37, phi_bb307_48, phi_bb307_49});
  }

  TNode<IntPtrT> phi_bb309_20;
  TNode<IntPtrT> phi_bb309_26;
  TNode<IntPtrT> phi_bb309_27;
  TNode<IntPtrT> phi_bb309_28;
  TNode<IntPtrT> phi_bb309_29;
  TNode<IntPtrT> phi_bb309_32;
  TNode<BoolT> phi_bb309_33;
  TNode<IntPtrT> phi_bb309_35;
  TNode<IntPtrT> phi_bb309_36;
  TNode<BoolT> phi_bb309_37;
  TNode<BoolT> phi_bb309_48;
  TNode<JSAny> phi_bb309_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp665;
  TNode<IntPtrT> tmp666;
  TNode<IntPtrT> tmp667;
  TNode<BoolT> tmp668;
  if (block309.is_used()) {
    ca_.Bind(&block309, &phi_bb309_20, &phi_bb309_26, &phi_bb309_27, &phi_bb309_28, &phi_bb309_29, &phi_bb309_32, &phi_bb309_33, &phi_bb309_35, &phi_bb309_36, &phi_bb309_37, &phi_bb309_48, &phi_bb309_49);
    std::tie(tmp665, tmp666) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb309_32}).Flatten();
    tmp667 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp668 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block305, phi_bb309_20, phi_bb309_26, phi_bb309_27, phi_bb309_28, phi_bb309_29, tmp667, tmp668, phi_bb309_35, phi_bb309_36, phi_bb309_37, phi_bb309_48, phi_bb309_49, tmp665, tmp666);
  }

  TNode<IntPtrT> phi_bb310_20;
  TNode<IntPtrT> phi_bb310_26;
  TNode<IntPtrT> phi_bb310_27;
  TNode<IntPtrT> phi_bb310_28;
  TNode<IntPtrT> phi_bb310_29;
  TNode<IntPtrT> phi_bb310_32;
  TNode<BoolT> phi_bb310_33;
  TNode<IntPtrT> phi_bb310_35;
  TNode<IntPtrT> phi_bb310_36;
  TNode<BoolT> phi_bb310_37;
  TNode<BoolT> phi_bb310_48;
  TNode<JSAny> phi_bb310_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp669;
  TNode<IntPtrT> tmp670;
  TNode<IntPtrT> tmp671;
  TNode<IntPtrT> tmp672;
  TNode<IntPtrT> tmp673;
  TNode<IntPtrT> tmp674;
  TNode<BoolT> tmp675;
  if (block310.is_used()) {
    ca_.Bind(&block310, &phi_bb310_20, &phi_bb310_26, &phi_bb310_27, &phi_bb310_28, &phi_bb310_29, &phi_bb310_32, &phi_bb310_33, &phi_bb310_35, &phi_bb310_36, &phi_bb310_37, &phi_bb310_48, &phi_bb310_49);
    std::tie(tmp669, tmp670) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb310_29}).Flatten();
    tmp671 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp672 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb310_29}, TNode<IntPtrT>{tmp671});
    tmp673 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp674 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp672}, TNode<IntPtrT>{tmp673});
    tmp675 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block305, phi_bb310_20, phi_bb310_26, phi_bb310_27, phi_bb310_28, tmp674, tmp672, tmp675, phi_bb310_35, phi_bb310_36, phi_bb310_37, phi_bb310_48, phi_bb310_49, tmp669, tmp670);
  }

  TNode<IntPtrT> phi_bb305_20;
  TNode<IntPtrT> phi_bb305_26;
  TNode<IntPtrT> phi_bb305_27;
  TNode<IntPtrT> phi_bb305_28;
  TNode<IntPtrT> phi_bb305_29;
  TNode<IntPtrT> phi_bb305_32;
  TNode<BoolT> phi_bb305_33;
  TNode<IntPtrT> phi_bb305_35;
  TNode<IntPtrT> phi_bb305_36;
  TNode<BoolT> phi_bb305_37;
  TNode<BoolT> phi_bb305_48;
  TNode<JSAny> phi_bb305_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb305_51;
  TNode<IntPtrT> phi_bb305_52;
  if (block305.is_used()) {
    ca_.Bind(&block305, &phi_bb305_20, &phi_bb305_26, &phi_bb305_27, &phi_bb305_28, &phi_bb305_29, &phi_bb305_32, &phi_bb305_33, &phi_bb305_35, &phi_bb305_36, &phi_bb305_37, &phi_bb305_48, &phi_bb305_49, &phi_bb305_51, &phi_bb305_52);
    ca_.Goto(&block302, phi_bb305_20, phi_bb305_26, phi_bb305_27, phi_bb305_28, phi_bb305_29, phi_bb305_32, phi_bb305_33, phi_bb305_35, phi_bb305_36, phi_bb305_37, phi_bb305_48, phi_bb305_49, phi_bb305_51, phi_bb305_52);
  }

  TNode<IntPtrT> phi_bb302_20;
  TNode<IntPtrT> phi_bb302_26;
  TNode<IntPtrT> phi_bb302_27;
  TNode<IntPtrT> phi_bb302_28;
  TNode<IntPtrT> phi_bb302_29;
  TNode<IntPtrT> phi_bb302_32;
  TNode<BoolT> phi_bb302_33;
  TNode<IntPtrT> phi_bb302_35;
  TNode<IntPtrT> phi_bb302_36;
  TNode<BoolT> phi_bb302_37;
  TNode<BoolT> phi_bb302_48;
  TNode<JSAny> phi_bb302_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb302_51;
  TNode<IntPtrT> phi_bb302_52;
  TNode<IntPtrT> tmp676;
  TNode<IntPtrT> tmp677;
  TNode<IntPtrT> tmp678;
  TNode<BoolT> tmp679;
  if (block302.is_used()) {
    ca_.Bind(&block302, &phi_bb302_20, &phi_bb302_26, &phi_bb302_27, &phi_bb302_28, &phi_bb302_29, &phi_bb302_32, &phi_bb302_33, &phi_bb302_35, &phi_bb302_36, &phi_bb302_37, &phi_bb302_48, &phi_bb302_49, &phi_bb302_51, &phi_bb302_52);
    tmp676 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp677 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp652}, TNode<IntPtrT>{tmp676});
    tmp678 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp679 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp652}, TNode<IntPtrT>{tmp678});
    ca_.Branch(tmp679, &block312, std::vector<compiler::Node*>{phi_bb302_20, phi_bb302_26, phi_bb302_27, phi_bb302_28, phi_bb302_29, phi_bb302_32, phi_bb302_33, phi_bb302_35, phi_bb302_36, phi_bb302_37, phi_bb302_48, phi_bb302_49, phi_bb302_51, phi_bb302_52}, &block313, std::vector<compiler::Node*>{phi_bb302_20, phi_bb302_26, phi_bb302_27, phi_bb302_28, phi_bb302_29, phi_bb302_32, phi_bb302_33, phi_bb302_35, phi_bb302_36, phi_bb302_37, phi_bb302_48, phi_bb302_49, phi_bb302_51, phi_bb302_52});
  }

  TNode<IntPtrT> phi_bb312_20;
  TNode<IntPtrT> phi_bb312_26;
  TNode<IntPtrT> phi_bb312_27;
  TNode<IntPtrT> phi_bb312_28;
  TNode<IntPtrT> phi_bb312_29;
  TNode<IntPtrT> phi_bb312_32;
  TNode<BoolT> phi_bb312_33;
  TNode<IntPtrT> phi_bb312_35;
  TNode<IntPtrT> phi_bb312_36;
  TNode<BoolT> phi_bb312_37;
  TNode<BoolT> phi_bb312_48;
  TNode<JSAny> phi_bb312_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb312_51;
  TNode<IntPtrT> phi_bb312_52;
  TNode<Union<HeapObject, TaggedIndex>> tmp680;
  TNode<IntPtrT> tmp681;
  TNode<IntPtrT> tmp682;
  TNode<IntPtrT> tmp683;
  if (block312.is_used()) {
    ca_.Bind(&block312, &phi_bb312_20, &phi_bb312_26, &phi_bb312_27, &phi_bb312_28, &phi_bb312_29, &phi_bb312_32, &phi_bb312_33, &phi_bb312_35, &phi_bb312_36, &phi_bb312_37, &phi_bb312_48, &phi_bb312_49, &phi_bb312_51, &phi_bb312_52);
    std::tie(tmp680, tmp681) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb312_27}).Flatten();
    tmp682 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp683 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb312_27}, TNode<IntPtrT>{tmp682});
    ca_.Goto(&block311, phi_bb312_20, phi_bb312_26, tmp683, phi_bb312_28, phi_bb312_29, phi_bb312_32, phi_bb312_33, phi_bb312_35, phi_bb312_36, phi_bb312_37, phi_bb312_48, phi_bb312_49, phi_bb312_51, phi_bb312_52, tmp680, tmp681);
  }

  TNode<IntPtrT> phi_bb313_20;
  TNode<IntPtrT> phi_bb313_26;
  TNode<IntPtrT> phi_bb313_27;
  TNode<IntPtrT> phi_bb313_28;
  TNode<IntPtrT> phi_bb313_29;
  TNode<IntPtrT> phi_bb313_32;
  TNode<BoolT> phi_bb313_33;
  TNode<IntPtrT> phi_bb313_35;
  TNode<IntPtrT> phi_bb313_36;
  TNode<BoolT> phi_bb313_37;
  TNode<BoolT> phi_bb313_48;
  TNode<JSAny> phi_bb313_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb313_51;
  TNode<IntPtrT> phi_bb313_52;
  if (block313.is_used()) {
    ca_.Bind(&block313, &phi_bb313_20, &phi_bb313_26, &phi_bb313_27, &phi_bb313_28, &phi_bb313_29, &phi_bb313_32, &phi_bb313_33, &phi_bb313_35, &phi_bb313_36, &phi_bb313_37, &phi_bb313_48, &phi_bb313_49, &phi_bb313_51, &phi_bb313_52);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block315, phi_bb313_20, phi_bb313_26, phi_bb313_27, phi_bb313_28, phi_bb313_29, phi_bb313_32, phi_bb313_33, phi_bb313_35, phi_bb313_36, phi_bb313_37, phi_bb313_48, phi_bb313_49, phi_bb313_51, phi_bb313_52);
    } else {
      ca_.Goto(&block316, phi_bb313_20, phi_bb313_26, phi_bb313_27, phi_bb313_28, phi_bb313_29, phi_bb313_32, phi_bb313_33, phi_bb313_35, phi_bb313_36, phi_bb313_37, phi_bb313_48, phi_bb313_49, phi_bb313_51, phi_bb313_52);
    }
  }

  TNode<IntPtrT> phi_bb315_20;
  TNode<IntPtrT> phi_bb315_26;
  TNode<IntPtrT> phi_bb315_27;
  TNode<IntPtrT> phi_bb315_28;
  TNode<IntPtrT> phi_bb315_29;
  TNode<IntPtrT> phi_bb315_32;
  TNode<BoolT> phi_bb315_33;
  TNode<IntPtrT> phi_bb315_35;
  TNode<IntPtrT> phi_bb315_36;
  TNode<BoolT> phi_bb315_37;
  TNode<BoolT> phi_bb315_48;
  TNode<JSAny> phi_bb315_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb315_51;
  TNode<IntPtrT> phi_bb315_52;
  TNode<Union<HeapObject, TaggedIndex>> tmp684;
  TNode<IntPtrT> tmp685;
  TNode<IntPtrT> tmp686;
  TNode<IntPtrT> tmp687;
  if (block315.is_used()) {
    ca_.Bind(&block315, &phi_bb315_20, &phi_bb315_26, &phi_bb315_27, &phi_bb315_28, &phi_bb315_29, &phi_bb315_32, &phi_bb315_33, &phi_bb315_35, &phi_bb315_36, &phi_bb315_37, &phi_bb315_48, &phi_bb315_49, &phi_bb315_51, &phi_bb315_52);
    std::tie(tmp684, tmp685) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb315_29}).Flatten();
    tmp686 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp687 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb315_29}, TNode<IntPtrT>{tmp686});
    ca_.Goto(&block314, phi_bb315_20, phi_bb315_26, phi_bb315_27, phi_bb315_28, tmp687, phi_bb315_32, phi_bb315_33, phi_bb315_35, phi_bb315_36, phi_bb315_37, phi_bb315_48, phi_bb315_49, phi_bb315_51, phi_bb315_52, tmp684, tmp685);
  }

  TNode<IntPtrT> phi_bb316_20;
  TNode<IntPtrT> phi_bb316_26;
  TNode<IntPtrT> phi_bb316_27;
  TNode<IntPtrT> phi_bb316_28;
  TNode<IntPtrT> phi_bb316_29;
  TNode<IntPtrT> phi_bb316_32;
  TNode<BoolT> phi_bb316_33;
  TNode<IntPtrT> phi_bb316_35;
  TNode<IntPtrT> phi_bb316_36;
  TNode<BoolT> phi_bb316_37;
  TNode<BoolT> phi_bb316_48;
  TNode<JSAny> phi_bb316_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb316_51;
  TNode<IntPtrT> phi_bb316_52;
  TNode<IntPtrT> tmp688;
  TNode<BoolT> tmp689;
  if (block316.is_used()) {
    ca_.Bind(&block316, &phi_bb316_20, &phi_bb316_26, &phi_bb316_27, &phi_bb316_28, &phi_bb316_29, &phi_bb316_32, &phi_bb316_33, &phi_bb316_35, &phi_bb316_36, &phi_bb316_37, &phi_bb316_48, &phi_bb316_49, &phi_bb316_51, &phi_bb316_52);
    tmp688 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp689 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb316_32}, TNode<IntPtrT>{tmp688});
    ca_.Branch(tmp689, &block318, std::vector<compiler::Node*>{phi_bb316_20, phi_bb316_26, phi_bb316_27, phi_bb316_28, phi_bb316_29, phi_bb316_32, phi_bb316_33, phi_bb316_35, phi_bb316_36, phi_bb316_37, phi_bb316_48, phi_bb316_49, phi_bb316_51, phi_bb316_52}, &block319, std::vector<compiler::Node*>{phi_bb316_20, phi_bb316_26, phi_bb316_27, phi_bb316_28, phi_bb316_29, phi_bb316_32, phi_bb316_33, phi_bb316_35, phi_bb316_36, phi_bb316_37, phi_bb316_48, phi_bb316_49, phi_bb316_51, phi_bb316_52});
  }

  TNode<IntPtrT> phi_bb318_20;
  TNode<IntPtrT> phi_bb318_26;
  TNode<IntPtrT> phi_bb318_27;
  TNode<IntPtrT> phi_bb318_28;
  TNode<IntPtrT> phi_bb318_29;
  TNode<IntPtrT> phi_bb318_32;
  TNode<BoolT> phi_bb318_33;
  TNode<IntPtrT> phi_bb318_35;
  TNode<IntPtrT> phi_bb318_36;
  TNode<BoolT> phi_bb318_37;
  TNode<BoolT> phi_bb318_48;
  TNode<JSAny> phi_bb318_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb318_51;
  TNode<IntPtrT> phi_bb318_52;
  TNode<Union<HeapObject, TaggedIndex>> tmp690;
  TNode<IntPtrT> tmp691;
  TNode<IntPtrT> tmp692;
  TNode<BoolT> tmp693;
  if (block318.is_used()) {
    ca_.Bind(&block318, &phi_bb318_20, &phi_bb318_26, &phi_bb318_27, &phi_bb318_28, &phi_bb318_29, &phi_bb318_32, &phi_bb318_33, &phi_bb318_35, &phi_bb318_36, &phi_bb318_37, &phi_bb318_48, &phi_bb318_49, &phi_bb318_51, &phi_bb318_52);
    std::tie(tmp690, tmp691) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb318_32}).Flatten();
    tmp692 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp693 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block314, phi_bb318_20, phi_bb318_26, phi_bb318_27, phi_bb318_28, phi_bb318_29, tmp692, tmp693, phi_bb318_35, phi_bb318_36, phi_bb318_37, phi_bb318_48, phi_bb318_49, phi_bb318_51, phi_bb318_52, tmp690, tmp691);
  }

  TNode<IntPtrT> phi_bb319_20;
  TNode<IntPtrT> phi_bb319_26;
  TNode<IntPtrT> phi_bb319_27;
  TNode<IntPtrT> phi_bb319_28;
  TNode<IntPtrT> phi_bb319_29;
  TNode<IntPtrT> phi_bb319_32;
  TNode<BoolT> phi_bb319_33;
  TNode<IntPtrT> phi_bb319_35;
  TNode<IntPtrT> phi_bb319_36;
  TNode<BoolT> phi_bb319_37;
  TNode<BoolT> phi_bb319_48;
  TNode<JSAny> phi_bb319_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb319_51;
  TNode<IntPtrT> phi_bb319_52;
  TNode<Union<HeapObject, TaggedIndex>> tmp694;
  TNode<IntPtrT> tmp695;
  TNode<IntPtrT> tmp696;
  TNode<IntPtrT> tmp697;
  TNode<IntPtrT> tmp698;
  TNode<IntPtrT> tmp699;
  TNode<BoolT> tmp700;
  if (block319.is_used()) {
    ca_.Bind(&block319, &phi_bb319_20, &phi_bb319_26, &phi_bb319_27, &phi_bb319_28, &phi_bb319_29, &phi_bb319_32, &phi_bb319_33, &phi_bb319_35, &phi_bb319_36, &phi_bb319_37, &phi_bb319_48, &phi_bb319_49, &phi_bb319_51, &phi_bb319_52);
    std::tie(tmp694, tmp695) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb319_29}).Flatten();
    tmp696 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp697 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb319_29}, TNode<IntPtrT>{tmp696});
    tmp698 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp699 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp697}, TNode<IntPtrT>{tmp698});
    tmp700 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block314, phi_bb319_20, phi_bb319_26, phi_bb319_27, phi_bb319_28, tmp699, tmp697, tmp700, phi_bb319_35, phi_bb319_36, phi_bb319_37, phi_bb319_48, phi_bb319_49, phi_bb319_51, phi_bb319_52, tmp694, tmp695);
  }

  TNode<IntPtrT> phi_bb314_20;
  TNode<IntPtrT> phi_bb314_26;
  TNode<IntPtrT> phi_bb314_27;
  TNode<IntPtrT> phi_bb314_28;
  TNode<IntPtrT> phi_bb314_29;
  TNode<IntPtrT> phi_bb314_32;
  TNode<BoolT> phi_bb314_33;
  TNode<IntPtrT> phi_bb314_35;
  TNode<IntPtrT> phi_bb314_36;
  TNode<BoolT> phi_bb314_37;
  TNode<BoolT> phi_bb314_48;
  TNode<JSAny> phi_bb314_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb314_51;
  TNode<IntPtrT> phi_bb314_52;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb314_53;
  TNode<IntPtrT> phi_bb314_54;
  if (block314.is_used()) {
    ca_.Bind(&block314, &phi_bb314_20, &phi_bb314_26, &phi_bb314_27, &phi_bb314_28, &phi_bb314_29, &phi_bb314_32, &phi_bb314_33, &phi_bb314_35, &phi_bb314_36, &phi_bb314_37, &phi_bb314_48, &phi_bb314_49, &phi_bb314_51, &phi_bb314_52, &phi_bb314_53, &phi_bb314_54);
    ca_.Goto(&block311, phi_bb314_20, phi_bb314_26, phi_bb314_27, phi_bb314_28, phi_bb314_29, phi_bb314_32, phi_bb314_33, phi_bb314_35, phi_bb314_36, phi_bb314_37, phi_bb314_48, phi_bb314_49, phi_bb314_51, phi_bb314_52, phi_bb314_53, phi_bb314_54);
  }

  TNode<IntPtrT> phi_bb311_20;
  TNode<IntPtrT> phi_bb311_26;
  TNode<IntPtrT> phi_bb311_27;
  TNode<IntPtrT> phi_bb311_28;
  TNode<IntPtrT> phi_bb311_29;
  TNode<IntPtrT> phi_bb311_32;
  TNode<BoolT> phi_bb311_33;
  TNode<IntPtrT> phi_bb311_35;
  TNode<IntPtrT> phi_bb311_36;
  TNode<BoolT> phi_bb311_37;
  TNode<BoolT> phi_bb311_48;
  TNode<JSAny> phi_bb311_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb311_51;
  TNode<IntPtrT> phi_bb311_52;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb311_53;
  TNode<IntPtrT> phi_bb311_54;
  TNode<BigInt> tmp701;
  TNode<UintPtrT> tmp702;
  TNode<UintPtrT> tmp703;
  TNode<IntPtrT> tmp704;
  TNode<IntPtrT> tmp705;
  if (block311.is_used()) {
    ca_.Bind(&block311, &phi_bb311_20, &phi_bb311_26, &phi_bb311_27, &phi_bb311_28, &phi_bb311_29, &phi_bb311_32, &phi_bb311_33, &phi_bb311_35, &phi_bb311_36, &phi_bb311_37, &phi_bb311_48, &phi_bb311_49, &phi_bb311_51, &phi_bb311_52, &phi_bb311_53, &phi_bb311_54);
    tmp701 = CodeStubAssembler(state_).ToBigInt(TNode<Context>{tmp455}, TNode<JSAny>{phi_bb311_49});
    std::tie(tmp702, tmp703) = CodeStubAssembler(state_).BigIntToRawBytes(TNode<BigInt>{tmp701}).Flatten();
    tmp704 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp702});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb311_51, phi_bb311_52}, tmp704);
    tmp705 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp703});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb311_53, phi_bb311_54}, tmp705);
    ca_.Goto(&block292, phi_bb311_20, tmp677, phi_bb311_26, phi_bb311_27, phi_bb311_28, phi_bb311_29, phi_bb311_32, phi_bb311_33, phi_bb311_35, phi_bb311_36, phi_bb311_37, phi_bb311_48, phi_bb311_49);
  }

  TNode<IntPtrT> phi_bb292_20;
  TNode<IntPtrT> phi_bb292_25;
  TNode<IntPtrT> phi_bb292_26;
  TNode<IntPtrT> phi_bb292_27;
  TNode<IntPtrT> phi_bb292_28;
  TNode<IntPtrT> phi_bb292_29;
  TNode<IntPtrT> phi_bb292_32;
  TNode<BoolT> phi_bb292_33;
  TNode<IntPtrT> phi_bb292_35;
  TNode<IntPtrT> phi_bb292_36;
  TNode<BoolT> phi_bb292_37;
  TNode<BoolT> phi_bb292_48;
  TNode<JSAny> phi_bb292_49;
  if (block292.is_used()) {
    ca_.Bind(&block292, &phi_bb292_20, &phi_bb292_25, &phi_bb292_26, &phi_bb292_27, &phi_bb292_28, &phi_bb292_29, &phi_bb292_32, &phi_bb292_33, &phi_bb292_35, &phi_bb292_36, &phi_bb292_37, &phi_bb292_48, &phi_bb292_49);
    ca_.Goto(&block289, phi_bb292_20, phi_bb292_25, phi_bb292_26, phi_bb292_27, phi_bb292_28, phi_bb292_29, phi_bb292_32, phi_bb292_33, phi_bb292_35, phi_bb292_36, phi_bb292_37, phi_bb292_48, phi_bb292_49);
  }

  TNode<IntPtrT> phi_bb288_20;
  TNode<IntPtrT> phi_bb288_25;
  TNode<IntPtrT> phi_bb288_26;
  TNode<IntPtrT> phi_bb288_27;
  TNode<IntPtrT> phi_bb288_28;
  TNode<IntPtrT> phi_bb288_29;
  TNode<IntPtrT> phi_bb288_32;
  TNode<BoolT> phi_bb288_33;
  TNode<IntPtrT> phi_bb288_35;
  TNode<IntPtrT> phi_bb288_36;
  TNode<BoolT> phi_bb288_37;
  TNode<BoolT> phi_bb288_48;
  TNode<JSAny> phi_bb288_49;
  TNode<Uint32T> tmp706;
  TNode<Uint32T> tmp707;
  TNode<Uint32T> tmp708;
  TNode<BoolT> tmp709;
  if (block288.is_used()) {
    ca_.Bind(&block288, &phi_bb288_20, &phi_bb288_25, &phi_bb288_26, &phi_bb288_27, &phi_bb288_28, &phi_bb288_29, &phi_bb288_32, &phi_bb288_33, &phi_bb288_35, &phi_bb288_36, &phi_bb288_37, &phi_bb288_48, &phi_bb288_49);
    tmp706 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp707 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp523}, TNode<Uint32T>{tmp706});
    tmp708 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp709 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp707}, TNode<Uint32T>{tmp708});
    ca_.Branch(tmp709, &block320, std::vector<compiler::Node*>{phi_bb288_20, phi_bb288_25, phi_bb288_26, phi_bb288_27, phi_bb288_28, phi_bb288_29, phi_bb288_32, phi_bb288_33, phi_bb288_35, phi_bb288_36, phi_bb288_37, phi_bb288_48, phi_bb288_49}, &block321, std::vector<compiler::Node*>{phi_bb288_20, phi_bb288_25, phi_bb288_26, phi_bb288_27, phi_bb288_28, phi_bb288_29, phi_bb288_32, phi_bb288_33, phi_bb288_35, phi_bb288_36, phi_bb288_37, phi_bb288_48, phi_bb288_49});
  }

  TNode<IntPtrT> phi_bb321_20;
  TNode<IntPtrT> phi_bb321_25;
  TNode<IntPtrT> phi_bb321_26;
  TNode<IntPtrT> phi_bb321_27;
  TNode<IntPtrT> phi_bb321_28;
  TNode<IntPtrT> phi_bb321_29;
  TNode<IntPtrT> phi_bb321_32;
  TNode<BoolT> phi_bb321_33;
  TNode<IntPtrT> phi_bb321_35;
  TNode<IntPtrT> phi_bb321_36;
  TNode<BoolT> phi_bb321_37;
  TNode<BoolT> phi_bb321_48;
  TNode<JSAny> phi_bb321_49;
  if (block321.is_used()) {
    ca_.Bind(&block321, &phi_bb321_20, &phi_bb321_25, &phi_bb321_26, &phi_bb321_27, &phi_bb321_28, &phi_bb321_29, &phi_bb321_32, &phi_bb321_33, &phi_bb321_35, &phi_bb321_36, &phi_bb321_37, &phi_bb321_48, &phi_bb321_49);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/wasm-to-js.tq", 269});
      CodeStubAssembler(state_).FailAssert("Torque assert '(retType & kValueTypeIsRefBit) != 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb320_20;
  TNode<IntPtrT> phi_bb320_25;
  TNode<IntPtrT> phi_bb320_26;
  TNode<IntPtrT> phi_bb320_27;
  TNode<IntPtrT> phi_bb320_28;
  TNode<IntPtrT> phi_bb320_29;
  TNode<IntPtrT> phi_bb320_32;
  TNode<BoolT> phi_bb320_33;
  TNode<IntPtrT> phi_bb320_35;
  TNode<IntPtrT> phi_bb320_36;
  TNode<BoolT> phi_bb320_37;
  TNode<BoolT> phi_bb320_48;
  TNode<JSAny> phi_bb320_49;
  TNode<Object> tmp710;
  TNode<IntPtrT> tmp711;
  TNode<BoolT> tmp712;
  if (block320.is_used()) {
    ca_.Bind(&block320, &phi_bb320_20, &phi_bb320_25, &phi_bb320_26, &phi_bb320_27, &phi_bb320_28, &phi_bb320_29, &phi_bb320_32, &phi_bb320_33, &phi_bb320_35, &phi_bb320_36, &phi_bb320_37, &phi_bb320_48, &phi_bb320_49);
    tmp710 = JSToWasmObject_0(state_, TNode<NativeContext>{tmp455}, TNode<Uint32T>{tmp523}, TNode<JSAny>{phi_bb320_49});
    tmp711 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp712 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp41}, TNode<IntPtrT>{tmp711});
    ca_.Branch(tmp712, &block322, std::vector<compiler::Node*>{phi_bb320_20, phi_bb320_25, phi_bb320_26, phi_bb320_27, phi_bb320_28, phi_bb320_29, phi_bb320_32, phi_bb320_33, phi_bb320_35, phi_bb320_36, phi_bb320_37, phi_bb320_48, phi_bb320_49}, &block323, std::vector<compiler::Node*>{phi_bb320_20, phi_bb320_25, phi_bb320_26, phi_bb320_27, phi_bb320_28, phi_bb320_29, phi_bb320_32, phi_bb320_33, phi_bb320_35, phi_bb320_36, phi_bb320_37, phi_bb320_48, phi_bb320_49});
  }

  TNode<IntPtrT> phi_bb322_20;
  TNode<IntPtrT> phi_bb322_25;
  TNode<IntPtrT> phi_bb322_26;
  TNode<IntPtrT> phi_bb322_27;
  TNode<IntPtrT> phi_bb322_28;
  TNode<IntPtrT> phi_bb322_29;
  TNode<IntPtrT> phi_bb322_32;
  TNode<BoolT> phi_bb322_33;
  TNode<IntPtrT> phi_bb322_35;
  TNode<IntPtrT> phi_bb322_36;
  TNode<BoolT> phi_bb322_37;
  TNode<BoolT> phi_bb322_48;
  TNode<JSAny> phi_bb322_49;
  TNode<IntPtrT> tmp713;
  TNode<IntPtrT> tmp714;
  TNode<IntPtrT> tmp715;
  TNode<BoolT> tmp716;
  if (block322.is_used()) {
    ca_.Bind(&block322, &phi_bb322_20, &phi_bb322_25, &phi_bb322_26, &phi_bb322_27, &phi_bb322_28, &phi_bb322_29, &phi_bb322_32, &phi_bb322_33, &phi_bb322_35, &phi_bb322_36, &phi_bb322_37, &phi_bb322_48, &phi_bb322_49);
    tmp713 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp714 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb322_25}, TNode<IntPtrT>{tmp713});
    tmp715 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp716 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb322_25}, TNode<IntPtrT>{tmp715});
    ca_.Branch(tmp716, &block326, std::vector<compiler::Node*>{phi_bb322_20, phi_bb322_26, phi_bb322_27, phi_bb322_28, phi_bb322_29, phi_bb322_32, phi_bb322_33, phi_bb322_35, phi_bb322_36, phi_bb322_37, phi_bb322_48, phi_bb322_49}, &block327, std::vector<compiler::Node*>{phi_bb322_20, phi_bb322_26, phi_bb322_27, phi_bb322_28, phi_bb322_29, phi_bb322_32, phi_bb322_33, phi_bb322_35, phi_bb322_36, phi_bb322_37, phi_bb322_48, phi_bb322_49});
  }

  TNode<IntPtrT> phi_bb326_20;
  TNode<IntPtrT> phi_bb326_26;
  TNode<IntPtrT> phi_bb326_27;
  TNode<IntPtrT> phi_bb326_28;
  TNode<IntPtrT> phi_bb326_29;
  TNode<IntPtrT> phi_bb326_32;
  TNode<BoolT> phi_bb326_33;
  TNode<IntPtrT> phi_bb326_35;
  TNode<IntPtrT> phi_bb326_36;
  TNode<BoolT> phi_bb326_37;
  TNode<BoolT> phi_bb326_48;
  TNode<JSAny> phi_bb326_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp717;
  TNode<IntPtrT> tmp718;
  TNode<IntPtrT> tmp719;
  TNode<IntPtrT> tmp720;
  if (block326.is_used()) {
    ca_.Bind(&block326, &phi_bb326_20, &phi_bb326_26, &phi_bb326_27, &phi_bb326_28, &phi_bb326_29, &phi_bb326_32, &phi_bb326_33, &phi_bb326_35, &phi_bb326_36, &phi_bb326_37, &phi_bb326_48, &phi_bb326_49);
    std::tie(tmp717, tmp718) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb326_27}).Flatten();
    tmp719 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp720 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb326_27}, TNode<IntPtrT>{tmp719});
    ca_.Goto(&block325, phi_bb326_20, phi_bb326_26, tmp720, phi_bb326_28, phi_bb326_29, phi_bb326_32, phi_bb326_33, phi_bb326_35, phi_bb326_36, phi_bb326_37, phi_bb326_48, phi_bb326_49, tmp717, tmp718);
  }

  TNode<IntPtrT> phi_bb327_20;
  TNode<IntPtrT> phi_bb327_26;
  TNode<IntPtrT> phi_bb327_27;
  TNode<IntPtrT> phi_bb327_28;
  TNode<IntPtrT> phi_bb327_29;
  TNode<IntPtrT> phi_bb327_32;
  TNode<BoolT> phi_bb327_33;
  TNode<IntPtrT> phi_bb327_35;
  TNode<IntPtrT> phi_bb327_36;
  TNode<BoolT> phi_bb327_37;
  TNode<BoolT> phi_bb327_48;
  TNode<JSAny> phi_bb327_49;
  if (block327.is_used()) {
    ca_.Bind(&block327, &phi_bb327_20, &phi_bb327_26, &phi_bb327_27, &phi_bb327_28, &phi_bb327_29, &phi_bb327_32, &phi_bb327_33, &phi_bb327_35, &phi_bb327_36, &phi_bb327_37, &phi_bb327_48, &phi_bb327_49);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block329, phi_bb327_20, phi_bb327_26, phi_bb327_27, phi_bb327_28, phi_bb327_29, phi_bb327_32, phi_bb327_33, phi_bb327_35, phi_bb327_36, phi_bb327_37, phi_bb327_48, phi_bb327_49);
    } else {
      ca_.Goto(&block330, phi_bb327_20, phi_bb327_26, phi_bb327_27, phi_bb327_28, phi_bb327_29, phi_bb327_32, phi_bb327_33, phi_bb327_35, phi_bb327_36, phi_bb327_37, phi_bb327_48, phi_bb327_49);
    }
  }

  TNode<IntPtrT> phi_bb329_20;
  TNode<IntPtrT> phi_bb329_26;
  TNode<IntPtrT> phi_bb329_27;
  TNode<IntPtrT> phi_bb329_28;
  TNode<IntPtrT> phi_bb329_29;
  TNode<IntPtrT> phi_bb329_32;
  TNode<BoolT> phi_bb329_33;
  TNode<IntPtrT> phi_bb329_35;
  TNode<IntPtrT> phi_bb329_36;
  TNode<BoolT> phi_bb329_37;
  TNode<BoolT> phi_bb329_48;
  TNode<JSAny> phi_bb329_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp721;
  TNode<IntPtrT> tmp722;
  TNode<IntPtrT> tmp723;
  TNode<IntPtrT> tmp724;
  if (block329.is_used()) {
    ca_.Bind(&block329, &phi_bb329_20, &phi_bb329_26, &phi_bb329_27, &phi_bb329_28, &phi_bb329_29, &phi_bb329_32, &phi_bb329_33, &phi_bb329_35, &phi_bb329_36, &phi_bb329_37, &phi_bb329_48, &phi_bb329_49);
    std::tie(tmp721, tmp722) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb329_29}).Flatten();
    tmp723 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp724 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb329_29}, TNode<IntPtrT>{tmp723});
    ca_.Goto(&block328, phi_bb329_20, phi_bb329_26, phi_bb329_27, phi_bb329_28, tmp724, phi_bb329_32, phi_bb329_33, phi_bb329_35, phi_bb329_36, phi_bb329_37, phi_bb329_48, phi_bb329_49, tmp721, tmp722);
  }

  TNode<IntPtrT> phi_bb330_20;
  TNode<IntPtrT> phi_bb330_26;
  TNode<IntPtrT> phi_bb330_27;
  TNode<IntPtrT> phi_bb330_28;
  TNode<IntPtrT> phi_bb330_29;
  TNode<IntPtrT> phi_bb330_32;
  TNode<BoolT> phi_bb330_33;
  TNode<IntPtrT> phi_bb330_35;
  TNode<IntPtrT> phi_bb330_36;
  TNode<BoolT> phi_bb330_37;
  TNode<BoolT> phi_bb330_48;
  TNode<JSAny> phi_bb330_49;
  TNode<IntPtrT> tmp725;
  TNode<BoolT> tmp726;
  if (block330.is_used()) {
    ca_.Bind(&block330, &phi_bb330_20, &phi_bb330_26, &phi_bb330_27, &phi_bb330_28, &phi_bb330_29, &phi_bb330_32, &phi_bb330_33, &phi_bb330_35, &phi_bb330_36, &phi_bb330_37, &phi_bb330_48, &phi_bb330_49);
    tmp725 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp726 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb330_32}, TNode<IntPtrT>{tmp725});
    ca_.Branch(tmp726, &block332, std::vector<compiler::Node*>{phi_bb330_20, phi_bb330_26, phi_bb330_27, phi_bb330_28, phi_bb330_29, phi_bb330_32, phi_bb330_33, phi_bb330_35, phi_bb330_36, phi_bb330_37, phi_bb330_48, phi_bb330_49}, &block333, std::vector<compiler::Node*>{phi_bb330_20, phi_bb330_26, phi_bb330_27, phi_bb330_28, phi_bb330_29, phi_bb330_32, phi_bb330_33, phi_bb330_35, phi_bb330_36, phi_bb330_37, phi_bb330_48, phi_bb330_49});
  }

  TNode<IntPtrT> phi_bb332_20;
  TNode<IntPtrT> phi_bb332_26;
  TNode<IntPtrT> phi_bb332_27;
  TNode<IntPtrT> phi_bb332_28;
  TNode<IntPtrT> phi_bb332_29;
  TNode<IntPtrT> phi_bb332_32;
  TNode<BoolT> phi_bb332_33;
  TNode<IntPtrT> phi_bb332_35;
  TNode<IntPtrT> phi_bb332_36;
  TNode<BoolT> phi_bb332_37;
  TNode<BoolT> phi_bb332_48;
  TNode<JSAny> phi_bb332_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp727;
  TNode<IntPtrT> tmp728;
  TNode<IntPtrT> tmp729;
  TNode<BoolT> tmp730;
  if (block332.is_used()) {
    ca_.Bind(&block332, &phi_bb332_20, &phi_bb332_26, &phi_bb332_27, &phi_bb332_28, &phi_bb332_29, &phi_bb332_32, &phi_bb332_33, &phi_bb332_35, &phi_bb332_36, &phi_bb332_37, &phi_bb332_48, &phi_bb332_49);
    std::tie(tmp727, tmp728) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb332_32}).Flatten();
    tmp729 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp730 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block328, phi_bb332_20, phi_bb332_26, phi_bb332_27, phi_bb332_28, phi_bb332_29, tmp729, tmp730, phi_bb332_35, phi_bb332_36, phi_bb332_37, phi_bb332_48, phi_bb332_49, tmp727, tmp728);
  }

  TNode<IntPtrT> phi_bb333_20;
  TNode<IntPtrT> phi_bb333_26;
  TNode<IntPtrT> phi_bb333_27;
  TNode<IntPtrT> phi_bb333_28;
  TNode<IntPtrT> phi_bb333_29;
  TNode<IntPtrT> phi_bb333_32;
  TNode<BoolT> phi_bb333_33;
  TNode<IntPtrT> phi_bb333_35;
  TNode<IntPtrT> phi_bb333_36;
  TNode<BoolT> phi_bb333_37;
  TNode<BoolT> phi_bb333_48;
  TNode<JSAny> phi_bb333_49;
  TNode<Union<HeapObject, TaggedIndex>> tmp731;
  TNode<IntPtrT> tmp732;
  TNode<IntPtrT> tmp733;
  TNode<IntPtrT> tmp734;
  TNode<IntPtrT> tmp735;
  TNode<IntPtrT> tmp736;
  TNode<BoolT> tmp737;
  if (block333.is_used()) {
    ca_.Bind(&block333, &phi_bb333_20, &phi_bb333_26, &phi_bb333_27, &phi_bb333_28, &phi_bb333_29, &phi_bb333_32, &phi_bb333_33, &phi_bb333_35, &phi_bb333_36, &phi_bb333_37, &phi_bb333_48, &phi_bb333_49);
    std::tie(tmp731, tmp732) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb333_29}).Flatten();
    tmp733 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp734 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb333_29}, TNode<IntPtrT>{tmp733});
    tmp735 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp736 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp734}, TNode<IntPtrT>{tmp735});
    tmp737 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block328, phi_bb333_20, phi_bb333_26, phi_bb333_27, phi_bb333_28, tmp736, tmp734, tmp737, phi_bb333_35, phi_bb333_36, phi_bb333_37, phi_bb333_48, phi_bb333_49, tmp731, tmp732);
  }

  TNode<IntPtrT> phi_bb328_20;
  TNode<IntPtrT> phi_bb328_26;
  TNode<IntPtrT> phi_bb328_27;
  TNode<IntPtrT> phi_bb328_28;
  TNode<IntPtrT> phi_bb328_29;
  TNode<IntPtrT> phi_bb328_32;
  TNode<BoolT> phi_bb328_33;
  TNode<IntPtrT> phi_bb328_35;
  TNode<IntPtrT> phi_bb328_36;
  TNode<BoolT> phi_bb328_37;
  TNode<BoolT> phi_bb328_48;
  TNode<JSAny> phi_bb328_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb328_52;
  TNode<IntPtrT> phi_bb328_53;
  if (block328.is_used()) {
    ca_.Bind(&block328, &phi_bb328_20, &phi_bb328_26, &phi_bb328_27, &phi_bb328_28, &phi_bb328_29, &phi_bb328_32, &phi_bb328_33, &phi_bb328_35, &phi_bb328_36, &phi_bb328_37, &phi_bb328_48, &phi_bb328_49, &phi_bb328_52, &phi_bb328_53);
    ca_.Goto(&block325, phi_bb328_20, phi_bb328_26, phi_bb328_27, phi_bb328_28, phi_bb328_29, phi_bb328_32, phi_bb328_33, phi_bb328_35, phi_bb328_36, phi_bb328_37, phi_bb328_48, phi_bb328_49, phi_bb328_52, phi_bb328_53);
  }

  TNode<IntPtrT> phi_bb325_20;
  TNode<IntPtrT> phi_bb325_26;
  TNode<IntPtrT> phi_bb325_27;
  TNode<IntPtrT> phi_bb325_28;
  TNode<IntPtrT> phi_bb325_29;
  TNode<IntPtrT> phi_bb325_32;
  TNode<BoolT> phi_bb325_33;
  TNode<IntPtrT> phi_bb325_35;
  TNode<IntPtrT> phi_bb325_36;
  TNode<BoolT> phi_bb325_37;
  TNode<BoolT> phi_bb325_48;
  TNode<JSAny> phi_bb325_49;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb325_52;
  TNode<IntPtrT> phi_bb325_53;
  TNode<IntPtrT> tmp738;
  if (block325.is_used()) {
    ca_.Bind(&block325, &phi_bb325_20, &phi_bb325_26, &phi_bb325_27, &phi_bb325_28, &phi_bb325_29, &phi_bb325_32, &phi_bb325_33, &phi_bb325_35, &phi_bb325_36, &phi_bb325_37, &phi_bb325_48, &phi_bb325_49, &phi_bb325_52, &phi_bb325_53);
    tmp738 = CodeStubAssembler(state_).BitcastTaggedToWord(TNode<Object>{tmp710});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb325_52, phi_bb325_53}, tmp738);
    ca_.Goto(&block324, phi_bb325_20, tmp714, phi_bb325_26, phi_bb325_27, phi_bb325_28, phi_bb325_29, phi_bb325_32, phi_bb325_33, phi_bb325_35, phi_bb325_36, phi_bb325_37, phi_bb325_48, phi_bb325_49);
  }

  TNode<IntPtrT> phi_bb323_20;
  TNode<IntPtrT> phi_bb323_25;
  TNode<IntPtrT> phi_bb323_26;
  TNode<IntPtrT> phi_bb323_27;
  TNode<IntPtrT> phi_bb323_28;
  TNode<IntPtrT> phi_bb323_29;
  TNode<IntPtrT> phi_bb323_32;
  TNode<BoolT> phi_bb323_33;
  TNode<IntPtrT> phi_bb323_35;
  TNode<IntPtrT> phi_bb323_36;
  TNode<BoolT> phi_bb323_37;
  TNode<BoolT> phi_bb323_48;
  TNode<JSAny> phi_bb323_49;
  TNode<BoolT> tmp739;
  TNode<Union<HeapObject, TaggedIndex>> tmp740;
  TNode<IntPtrT> tmp741;
  TNode<IntPtrT> tmp742;
  TNode<UintPtrT> tmp743;
  TNode<UintPtrT> tmp744;
  TNode<BoolT> tmp745;
  if (block323.is_used()) {
    ca_.Bind(&block323, &phi_bb323_20, &phi_bb323_25, &phi_bb323_26, &phi_bb323_27, &phi_bb323_28, &phi_bb323_29, &phi_bb323_32, &phi_bb323_33, &phi_bb323_35, &phi_bb323_36, &phi_bb323_37, &phi_bb323_48, &phi_bb323_49);
    tmp739 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    std::tie(tmp740, tmp741, tmp742) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb214_41}).Flatten();
    tmp743 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb323_20});
    tmp744 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp742});
    tmp745 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp743}, TNode<UintPtrT>{tmp744});
    ca_.Branch(tmp745, &block338, std::vector<compiler::Node*>{phi_bb323_20, phi_bb323_25, phi_bb323_26, phi_bb323_27, phi_bb323_28, phi_bb323_29, phi_bb323_32, phi_bb323_33, phi_bb323_35, phi_bb323_36, phi_bb323_37, phi_bb323_49, phi_bb323_20, phi_bb323_20, phi_bb323_20, phi_bb323_20}, &block339, std::vector<compiler::Node*>{phi_bb323_20, phi_bb323_25, phi_bb323_26, phi_bb323_27, phi_bb323_28, phi_bb323_29, phi_bb323_32, phi_bb323_33, phi_bb323_35, phi_bb323_36, phi_bb323_37, phi_bb323_49, phi_bb323_20, phi_bb323_20, phi_bb323_20, phi_bb323_20});
  }

  TNode<IntPtrT> phi_bb338_20;
  TNode<IntPtrT> phi_bb338_25;
  TNode<IntPtrT> phi_bb338_26;
  TNode<IntPtrT> phi_bb338_27;
  TNode<IntPtrT> phi_bb338_28;
  TNode<IntPtrT> phi_bb338_29;
  TNode<IntPtrT> phi_bb338_32;
  TNode<BoolT> phi_bb338_33;
  TNode<IntPtrT> phi_bb338_35;
  TNode<IntPtrT> phi_bb338_36;
  TNode<BoolT> phi_bb338_37;
  TNode<JSAny> phi_bb338_49;
  TNode<IntPtrT> phi_bb338_56;
  TNode<IntPtrT> phi_bb338_57;
  TNode<IntPtrT> phi_bb338_61;
  TNode<IntPtrT> phi_bb338_62;
  TNode<IntPtrT> tmp746;
  TNode<IntPtrT> tmp747;
  TNode<Union<HeapObject, TaggedIndex>> tmp748;
  TNode<IntPtrT> tmp749;
  if (block338.is_used()) {
    ca_.Bind(&block338, &phi_bb338_20, &phi_bb338_25, &phi_bb338_26, &phi_bb338_27, &phi_bb338_28, &phi_bb338_29, &phi_bb338_32, &phi_bb338_33, &phi_bb338_35, &phi_bb338_36, &phi_bb338_37, &phi_bb338_49, &phi_bb338_56, &phi_bb338_57, &phi_bb338_61, &phi_bb338_62);
    tmp746 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb338_62});
    tmp747 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp741}, TNode<IntPtrT>{tmp746});
    std::tie(tmp748, tmp749) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp740}, TNode<IntPtrT>{tmp747}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp748, tmp749}, tmp710);
    ca_.Goto(&block324, phi_bb338_20, phi_bb338_25, phi_bb338_26, phi_bb338_27, phi_bb338_28, phi_bb338_29, phi_bb338_32, phi_bb338_33, phi_bb338_35, phi_bb338_36, phi_bb338_37, tmp739, phi_bb338_49);
  }

  TNode<IntPtrT> phi_bb339_20;
  TNode<IntPtrT> phi_bb339_25;
  TNode<IntPtrT> phi_bb339_26;
  TNode<IntPtrT> phi_bb339_27;
  TNode<IntPtrT> phi_bb339_28;
  TNode<IntPtrT> phi_bb339_29;
  TNode<IntPtrT> phi_bb339_32;
  TNode<BoolT> phi_bb339_33;
  TNode<IntPtrT> phi_bb339_35;
  TNode<IntPtrT> phi_bb339_36;
  TNode<BoolT> phi_bb339_37;
  TNode<JSAny> phi_bb339_49;
  TNode<IntPtrT> phi_bb339_56;
  TNode<IntPtrT> phi_bb339_57;
  TNode<IntPtrT> phi_bb339_61;
  TNode<IntPtrT> phi_bb339_62;
  if (block339.is_used()) {
    ca_.Bind(&block339, &phi_bb339_20, &phi_bb339_25, &phi_bb339_26, &phi_bb339_27, &phi_bb339_28, &phi_bb339_29, &phi_bb339_32, &phi_bb339_33, &phi_bb339_35, &phi_bb339_36, &phi_bb339_37, &phi_bb339_49, &phi_bb339_56, &phi_bb339_57, &phi_bb339_61, &phi_bb339_62);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb324_20;
  TNode<IntPtrT> phi_bb324_25;
  TNode<IntPtrT> phi_bb324_26;
  TNode<IntPtrT> phi_bb324_27;
  TNode<IntPtrT> phi_bb324_28;
  TNode<IntPtrT> phi_bb324_29;
  TNode<IntPtrT> phi_bb324_32;
  TNode<BoolT> phi_bb324_33;
  TNode<IntPtrT> phi_bb324_35;
  TNode<IntPtrT> phi_bb324_36;
  TNode<BoolT> phi_bb324_37;
  TNode<BoolT> phi_bb324_48;
  TNode<JSAny> phi_bb324_49;
  if (block324.is_used()) {
    ca_.Bind(&block324, &phi_bb324_20, &phi_bb324_25, &phi_bb324_26, &phi_bb324_27, &phi_bb324_28, &phi_bb324_29, &phi_bb324_32, &phi_bb324_33, &phi_bb324_35, &phi_bb324_36, &phi_bb324_37, &phi_bb324_48, &phi_bb324_49);
    ca_.Goto(&block289, phi_bb324_20, phi_bb324_25, phi_bb324_26, phi_bb324_27, phi_bb324_28, phi_bb324_29, phi_bb324_32, phi_bb324_33, phi_bb324_35, phi_bb324_36, phi_bb324_37, phi_bb324_48, phi_bb324_49);
  }

  TNode<IntPtrT> phi_bb289_20;
  TNode<IntPtrT> phi_bb289_25;
  TNode<IntPtrT> phi_bb289_26;
  TNode<IntPtrT> phi_bb289_27;
  TNode<IntPtrT> phi_bb289_28;
  TNode<IntPtrT> phi_bb289_29;
  TNode<IntPtrT> phi_bb289_32;
  TNode<BoolT> phi_bb289_33;
  TNode<IntPtrT> phi_bb289_35;
  TNode<IntPtrT> phi_bb289_36;
  TNode<BoolT> phi_bb289_37;
  TNode<BoolT> phi_bb289_48;
  TNode<JSAny> phi_bb289_49;
  if (block289.is_used()) {
    ca_.Bind(&block289, &phi_bb289_20, &phi_bb289_25, &phi_bb289_26, &phi_bb289_27, &phi_bb289_28, &phi_bb289_29, &phi_bb289_32, &phi_bb289_33, &phi_bb289_35, &phi_bb289_36, &phi_bb289_37, &phi_bb289_48, &phi_bb289_49);
    ca_.Goto(&block274, phi_bb289_20, phi_bb289_25, phi_bb289_26, phi_bb289_27, phi_bb289_28, phi_bb289_29, phi_bb289_32, phi_bb289_33, phi_bb289_35, phi_bb289_36, phi_bb289_37, phi_bb289_48, phi_bb289_49);
  }

  TNode<IntPtrT> phi_bb274_20;
  TNode<IntPtrT> phi_bb274_25;
  TNode<IntPtrT> phi_bb274_26;
  TNode<IntPtrT> phi_bb274_27;
  TNode<IntPtrT> phi_bb274_28;
  TNode<IntPtrT> phi_bb274_29;
  TNode<IntPtrT> phi_bb274_32;
  TNode<BoolT> phi_bb274_33;
  TNode<IntPtrT> phi_bb274_35;
  TNode<IntPtrT> phi_bb274_36;
  TNode<BoolT> phi_bb274_37;
  TNode<BoolT> phi_bb274_48;
  TNode<JSAny> phi_bb274_49;
  if (block274.is_used()) {
    ca_.Bind(&block274, &phi_bb274_20, &phi_bb274_25, &phi_bb274_26, &phi_bb274_27, &phi_bb274_28, &phi_bb274_29, &phi_bb274_32, &phi_bb274_33, &phi_bb274_35, &phi_bb274_36, &phi_bb274_37, &phi_bb274_48, &phi_bb274_49);
    ca_.Goto(&block259, phi_bb274_20, phi_bb274_25, phi_bb274_26, phi_bb274_27, phi_bb274_28, phi_bb274_29, phi_bb274_32, phi_bb274_33, phi_bb274_35, phi_bb274_36, phi_bb274_37, phi_bb274_48, phi_bb274_49);
  }

  TNode<IntPtrT> phi_bb259_20;
  TNode<IntPtrT> phi_bb259_25;
  TNode<IntPtrT> phi_bb259_26;
  TNode<IntPtrT> phi_bb259_27;
  TNode<IntPtrT> phi_bb259_28;
  TNode<IntPtrT> phi_bb259_29;
  TNode<IntPtrT> phi_bb259_32;
  TNode<BoolT> phi_bb259_33;
  TNode<IntPtrT> phi_bb259_35;
  TNode<IntPtrT> phi_bb259_36;
  TNode<BoolT> phi_bb259_37;
  TNode<BoolT> phi_bb259_48;
  TNode<JSAny> phi_bb259_49;
  if (block259.is_used()) {
    ca_.Bind(&block259, &phi_bb259_20, &phi_bb259_25, &phi_bb259_26, &phi_bb259_27, &phi_bb259_28, &phi_bb259_29, &phi_bb259_32, &phi_bb259_33, &phi_bb259_35, &phi_bb259_36, &phi_bb259_37, &phi_bb259_48, &phi_bb259_49);
    ca_.Goto(&block243, phi_bb259_20, phi_bb259_25, phi_bb259_26, phi_bb259_27, phi_bb259_28, phi_bb259_29, phi_bb259_32, phi_bb259_33, phi_bb259_35, phi_bb259_36, phi_bb259_37, phi_bb259_48, phi_bb259_49);
  }

  TNode<IntPtrT> phi_bb243_20;
  TNode<IntPtrT> phi_bb243_25;
  TNode<IntPtrT> phi_bb243_26;
  TNode<IntPtrT> phi_bb243_27;
  TNode<IntPtrT> phi_bb243_28;
  TNode<IntPtrT> phi_bb243_29;
  TNode<IntPtrT> phi_bb243_32;
  TNode<BoolT> phi_bb243_33;
  TNode<IntPtrT> phi_bb243_35;
  TNode<IntPtrT> phi_bb243_36;
  TNode<BoolT> phi_bb243_37;
  TNode<BoolT> phi_bb243_48;
  TNode<JSAny> phi_bb243_49;
  TNode<IntPtrT> tmp750;
  TNode<IntPtrT> tmp751;
  if (block243.is_used()) {
    ca_.Bind(&block243, &phi_bb243_20, &phi_bb243_25, &phi_bb243_26, &phi_bb243_27, &phi_bb243_28, &phi_bb243_29, &phi_bb243_32, &phi_bb243_33, &phi_bb243_35, &phi_bb243_36, &phi_bb243_37, &phi_bb243_48, &phi_bb243_49);
    tmp750 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp751 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb243_20}, TNode<IntPtrT>{tmp750});
    ca_.Goto(&block223, tmp751, phi_bb243_25, phi_bb243_26, phi_bb243_27, phi_bb243_28, phi_bb243_29, phi_bb243_32, phi_bb243_33, phi_bb243_35, phi_bb243_36, phi_bb243_37, tmp522, phi_bb243_48);
  }

  TNode<IntPtrT> phi_bb222_20;
  TNode<IntPtrT> phi_bb222_25;
  TNode<IntPtrT> phi_bb222_26;
  TNode<IntPtrT> phi_bb222_27;
  TNode<IntPtrT> phi_bb222_28;
  TNode<IntPtrT> phi_bb222_29;
  TNode<IntPtrT> phi_bb222_32;
  TNode<BoolT> phi_bb222_33;
  TNode<IntPtrT> phi_bb222_35;
  TNode<IntPtrT> phi_bb222_36;
  TNode<BoolT> phi_bb222_37;
  TNode<IntPtrT> phi_bb222_46;
  TNode<BoolT> phi_bb222_48;
  if (block222.is_used()) {
    ca_.Bind(&block222, &phi_bb222_20, &phi_bb222_25, &phi_bb222_26, &phi_bb222_27, &phi_bb222_28, &phi_bb222_29, &phi_bb222_32, &phi_bb222_33, &phi_bb222_35, &phi_bb222_36, &phi_bb222_37, &phi_bb222_46, &phi_bb222_48);
    ca_.Branch(phi_bb222_48, &block342, std::vector<compiler::Node*>{phi_bb222_20, phi_bb222_25, phi_bb222_26, phi_bb222_27, phi_bb222_28, phi_bb222_29, phi_bb222_32, phi_bb222_33, phi_bb222_35, phi_bb222_36, phi_bb222_37, phi_bb222_46, phi_bb222_48}, &block343, std::vector<compiler::Node*>{phi_bb222_20, phi_bb222_25, phi_bb222_26, phi_bb222_27, phi_bb222_28, phi_bb222_29, phi_bb222_32, phi_bb222_33, phi_bb222_35, phi_bb222_36, phi_bb222_37, phi_bb222_46, tmp498, phi_bb222_48});
  }

  TNode<IntPtrT> phi_bb342_20;
  TNode<IntPtrT> phi_bb342_25;
  TNode<IntPtrT> phi_bb342_26;
  TNode<IntPtrT> phi_bb342_27;
  TNode<IntPtrT> phi_bb342_28;
  TNode<IntPtrT> phi_bb342_29;
  TNode<IntPtrT> phi_bb342_32;
  TNode<BoolT> phi_bb342_33;
  TNode<IntPtrT> phi_bb342_35;
  TNode<IntPtrT> phi_bb342_36;
  TNode<BoolT> phi_bb342_37;
  TNode<IntPtrT> phi_bb342_46;
  TNode<BoolT> phi_bb342_48;
  TNode<BoolT> tmp752;
  if (block342.is_used()) {
    ca_.Bind(&block342, &phi_bb342_20, &phi_bb342_25, &phi_bb342_26, &phi_bb342_27, &phi_bb342_28, &phi_bb342_29, &phi_bb342_32, &phi_bb342_33, &phi_bb342_35, &phi_bb342_36, &phi_bb342_37, &phi_bb342_46, &phi_bb342_48);
    tmp752 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{phi_bb342_33});
    ca_.Branch(tmp752, &block345, std::vector<compiler::Node*>{phi_bb342_20, phi_bb342_25, phi_bb342_26, phi_bb342_27, phi_bb342_28, phi_bb342_29, phi_bb342_32, phi_bb342_33, phi_bb342_35, phi_bb342_36, phi_bb342_37, phi_bb342_46, phi_bb342_48}, &block346, std::vector<compiler::Node*>{phi_bb342_20, phi_bb342_25, phi_bb342_26, phi_bb342_27, phi_bb342_28, phi_bb342_29, phi_bb342_32, phi_bb342_33, phi_bb342_35, phi_bb342_36, phi_bb342_37, phi_bb342_46, phi_bb342_48});
  }

  TNode<IntPtrT> phi_bb345_20;
  TNode<IntPtrT> phi_bb345_25;
  TNode<IntPtrT> phi_bb345_26;
  TNode<IntPtrT> phi_bb345_27;
  TNode<IntPtrT> phi_bb345_28;
  TNode<IntPtrT> phi_bb345_29;
  TNode<IntPtrT> phi_bb345_32;
  TNode<BoolT> phi_bb345_33;
  TNode<IntPtrT> phi_bb345_35;
  TNode<IntPtrT> phi_bb345_36;
  TNode<BoolT> phi_bb345_37;
  TNode<IntPtrT> phi_bb345_46;
  TNode<BoolT> phi_bb345_48;
  TNode<IntPtrT> tmp753;
  if (block345.is_used()) {
    ca_.Bind(&block345, &phi_bb345_20, &phi_bb345_25, &phi_bb345_26, &phi_bb345_27, &phi_bb345_28, &phi_bb345_29, &phi_bb345_32, &phi_bb345_33, &phi_bb345_35, &phi_bb345_36, &phi_bb345_37, &phi_bb345_46, &phi_bb345_48);
    tmp753 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block346, phi_bb345_20, phi_bb345_25, phi_bb345_26, phi_bb345_27, phi_bb345_28, phi_bb345_29, tmp753, phi_bb345_33, phi_bb345_35, phi_bb345_36, phi_bb345_37, phi_bb345_46, phi_bb345_48);
  }

  TNode<IntPtrT> phi_bb346_20;
  TNode<IntPtrT> phi_bb346_25;
  TNode<IntPtrT> phi_bb346_26;
  TNode<IntPtrT> phi_bb346_27;
  TNode<IntPtrT> phi_bb346_28;
  TNode<IntPtrT> phi_bb346_29;
  TNode<IntPtrT> phi_bb346_32;
  TNode<BoolT> phi_bb346_33;
  TNode<IntPtrT> phi_bb346_35;
  TNode<IntPtrT> phi_bb346_36;
  TNode<BoolT> phi_bb346_37;
  TNode<IntPtrT> phi_bb346_46;
  TNode<BoolT> phi_bb346_48;
  TNode<IntPtrT> tmp754;
  TNode<IntPtrT> tmp755;
  TNode<IntPtrT> tmp756;
  if (block346.is_used()) {
    ca_.Bind(&block346, &phi_bb346_20, &phi_bb346_25, &phi_bb346_26, &phi_bb346_27, &phi_bb346_28, &phi_bb346_29, &phi_bb346_32, &phi_bb346_33, &phi_bb346_35, &phi_bb346_36, &phi_bb346_37, &phi_bb346_46, &phi_bb346_48);
    tmp754 = TimesSizeOf_uint32_0(state_, TNode<IntPtrT>{tmp65});
    tmp755 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp64}, TNode<IntPtrT>{tmp754});
    tmp756 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block350, tmp756, phi_bb346_25, phi_bb346_26, phi_bb346_27, phi_bb346_28, phi_bb346_29, phi_bb346_32, phi_bb346_33, phi_bb346_35, phi_bb346_36, phi_bb346_37, tmp64, phi_bb346_48);
  }

  TNode<IntPtrT> phi_bb350_20;
  TNode<IntPtrT> phi_bb350_25;
  TNode<IntPtrT> phi_bb350_26;
  TNode<IntPtrT> phi_bb350_27;
  TNode<IntPtrT> phi_bb350_28;
  TNode<IntPtrT> phi_bb350_29;
  TNode<IntPtrT> phi_bb350_32;
  TNode<BoolT> phi_bb350_33;
  TNode<IntPtrT> phi_bb350_35;
  TNode<IntPtrT> phi_bb350_36;
  TNode<BoolT> phi_bb350_37;
  TNode<IntPtrT> phi_bb350_46;
  TNode<BoolT> phi_bb350_48;
  TNode<BoolT> tmp757;
  TNode<BoolT> tmp758;
  if (block350.is_used()) {
    ca_.Bind(&block350, &phi_bb350_20, &phi_bb350_25, &phi_bb350_26, &phi_bb350_27, &phi_bb350_28, &phi_bb350_29, &phi_bb350_32, &phi_bb350_33, &phi_bb350_35, &phi_bb350_36, &phi_bb350_37, &phi_bb350_46, &phi_bb350_48);
    tmp757 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb350_46}, TNode<IntPtrT>{tmp755});
    tmp758 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp757});
    ca_.Branch(tmp758, &block348, std::vector<compiler::Node*>{phi_bb350_20, phi_bb350_25, phi_bb350_26, phi_bb350_27, phi_bb350_28, phi_bb350_29, phi_bb350_32, phi_bb350_33, phi_bb350_35, phi_bb350_36, phi_bb350_37, phi_bb350_46, phi_bb350_48}, &block349, std::vector<compiler::Node*>{phi_bb350_20, phi_bb350_25, phi_bb350_26, phi_bb350_27, phi_bb350_28, phi_bb350_29, phi_bb350_32, phi_bb350_33, phi_bb350_35, phi_bb350_36, phi_bb350_37, phi_bb350_46, phi_bb350_48});
  }

  TNode<IntPtrT> phi_bb348_20;
  TNode<IntPtrT> phi_bb348_25;
  TNode<IntPtrT> phi_bb348_26;
  TNode<IntPtrT> phi_bb348_27;
  TNode<IntPtrT> phi_bb348_28;
  TNode<IntPtrT> phi_bb348_29;
  TNode<IntPtrT> phi_bb348_32;
  TNode<BoolT> phi_bb348_33;
  TNode<IntPtrT> phi_bb348_35;
  TNode<IntPtrT> phi_bb348_36;
  TNode<BoolT> phi_bb348_37;
  TNode<IntPtrT> phi_bb348_46;
  TNode<BoolT> phi_bb348_48;
  TNode<BoolT> tmp759;
  TNode<BoolT> tmp760;
  if (block348.is_used()) {
    ca_.Bind(&block348, &phi_bb348_20, &phi_bb348_25, &phi_bb348_26, &phi_bb348_27, &phi_bb348_28, &phi_bb348_29, &phi_bb348_32, &phi_bb348_33, &phi_bb348_35, &phi_bb348_36, &phi_bb348_37, &phi_bb348_46, &phi_bb348_48);
    tmp759 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb348_46}, TNode<IntPtrT>{tmp755});
    tmp760 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp759});
    ca_.Branch(tmp760, &block354, std::vector<compiler::Node*>{phi_bb348_20, phi_bb348_25, phi_bb348_26, phi_bb348_27, phi_bb348_28, phi_bb348_29, phi_bb348_32, phi_bb348_33, phi_bb348_35, phi_bb348_36, phi_bb348_37, phi_bb348_46, phi_bb348_48}, &block355, std::vector<compiler::Node*>{phi_bb348_20, phi_bb348_25, phi_bb348_26, phi_bb348_27, phi_bb348_28, phi_bb348_29, phi_bb348_32, phi_bb348_33, phi_bb348_35, phi_bb348_36, phi_bb348_37, phi_bb348_46, phi_bb348_48});
  }

  TNode<IntPtrT> phi_bb355_20;
  TNode<IntPtrT> phi_bb355_25;
  TNode<IntPtrT> phi_bb355_26;
  TNode<IntPtrT> phi_bb355_27;
  TNode<IntPtrT> phi_bb355_28;
  TNode<IntPtrT> phi_bb355_29;
  TNode<IntPtrT> phi_bb355_32;
  TNode<BoolT> phi_bb355_33;
  TNode<IntPtrT> phi_bb355_35;
  TNode<IntPtrT> phi_bb355_36;
  TNode<BoolT> phi_bb355_37;
  TNode<IntPtrT> phi_bb355_46;
  TNode<BoolT> phi_bb355_48;
  if (block355.is_used()) {
    ca_.Bind(&block355, &phi_bb355_20, &phi_bb355_25, &phi_bb355_26, &phi_bb355_27, &phi_bb355_28, &phi_bb355_29, &phi_bb355_32, &phi_bb355_33, &phi_bb355_35, &phi_bb355_36, &phi_bb355_37, &phi_bb355_46, &phi_bb355_48);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/torque-internal.tq", 245});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.Empty()' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb354_20;
  TNode<IntPtrT> phi_bb354_25;
  TNode<IntPtrT> phi_bb354_26;
  TNode<IntPtrT> phi_bb354_27;
  TNode<IntPtrT> phi_bb354_28;
  TNode<IntPtrT> phi_bb354_29;
  TNode<IntPtrT> phi_bb354_32;
  TNode<BoolT> phi_bb354_33;
  TNode<IntPtrT> phi_bb354_35;
  TNode<IntPtrT> phi_bb354_36;
  TNode<BoolT> phi_bb354_37;
  TNode<IntPtrT> phi_bb354_46;
  TNode<BoolT> phi_bb354_48;
  TNode<Union<HeapObject, TaggedIndex>> tmp761;
  TNode<IntPtrT> tmp762;
  TNode<IntPtrT> tmp763;
  TNode<IntPtrT> tmp764;
  TNode<Uint32T> tmp765;
  TNode<Uint32T> tmp766;
  TNode<Uint32T> tmp767;
  TNode<Uint32T> tmp768;
  TNode<BoolT> tmp769;
  if (block354.is_used()) {
    ca_.Bind(&block354, &phi_bb354_20, &phi_bb354_25, &phi_bb354_26, &phi_bb354_27, &phi_bb354_28, &phi_bb354_29, &phi_bb354_32, &phi_bb354_33, &phi_bb354_35, &phi_bb354_36, &phi_bb354_37, &phi_bb354_46, &phi_bb354_48);
    std::tie(tmp761, tmp762) = NewReference_uint32_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp63}, TNode<IntPtrT>{phi_bb354_46}).Flatten();
    tmp763 = FromConstexpr_intptr_constexpr_int31_0(state_, kInt32Size);
    tmp764 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb354_46}, TNode<IntPtrT>{tmp763});
    tmp765 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp761, tmp762});
    tmp766 = FromConstexpr_uint32_constexpr_uint32_0(state_, wasm::ValueType::kIsRefBit);
    tmp767 = CodeStubAssembler(state_).Word32And(TNode<Uint32T>{tmp765}, TNode<Uint32T>{tmp766});
    tmp768 = FromConstexpr_uint32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp769 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp767}, TNode<Uint32T>{tmp768});
    ca_.Branch(tmp769, &block357, std::vector<compiler::Node*>{phi_bb354_20, phi_bb354_25, phi_bb354_26, phi_bb354_27, phi_bb354_28, phi_bb354_29, phi_bb354_32, phi_bb354_33, phi_bb354_35, phi_bb354_36, phi_bb354_37, phi_bb354_48}, &block358, std::vector<compiler::Node*>{phi_bb354_20, phi_bb354_25, phi_bb354_26, phi_bb354_27, phi_bb354_28, phi_bb354_29, phi_bb354_32, phi_bb354_33, phi_bb354_35, phi_bb354_36, phi_bb354_37, phi_bb354_48});
  }

  TNode<IntPtrT> phi_bb357_20;
  TNode<IntPtrT> phi_bb357_25;
  TNode<IntPtrT> phi_bb357_26;
  TNode<IntPtrT> phi_bb357_27;
  TNode<IntPtrT> phi_bb357_28;
  TNode<IntPtrT> phi_bb357_29;
  TNode<IntPtrT> phi_bb357_32;
  TNode<BoolT> phi_bb357_33;
  TNode<IntPtrT> phi_bb357_35;
  TNode<IntPtrT> phi_bb357_36;
  TNode<BoolT> phi_bb357_37;
  TNode<BoolT> phi_bb357_48;
  TNode<IntPtrT> tmp770;
  TNode<IntPtrT> tmp771;
  TNode<IntPtrT> tmp772;
  TNode<BoolT> tmp773;
  if (block357.is_used()) {
    ca_.Bind(&block357, &phi_bb357_20, &phi_bb357_25, &phi_bb357_26, &phi_bb357_27, &phi_bb357_28, &phi_bb357_29, &phi_bb357_32, &phi_bb357_33, &phi_bb357_35, &phi_bb357_36, &phi_bb357_37, &phi_bb357_48);
    tmp770 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp771 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb357_25}, TNode<IntPtrT>{tmp770});
    tmp772 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp773 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb357_25}, TNode<IntPtrT>{tmp772});
    ca_.Branch(tmp773, &block360, std::vector<compiler::Node*>{phi_bb357_20, phi_bb357_26, phi_bb357_27, phi_bb357_28, phi_bb357_29, phi_bb357_32, phi_bb357_33, phi_bb357_35, phi_bb357_36, phi_bb357_37, phi_bb357_48}, &block361, std::vector<compiler::Node*>{phi_bb357_20, phi_bb357_26, phi_bb357_27, phi_bb357_28, phi_bb357_29, phi_bb357_32, phi_bb357_33, phi_bb357_35, phi_bb357_36, phi_bb357_37, phi_bb357_48});
  }

  TNode<IntPtrT> phi_bb360_20;
  TNode<IntPtrT> phi_bb360_26;
  TNode<IntPtrT> phi_bb360_27;
  TNode<IntPtrT> phi_bb360_28;
  TNode<IntPtrT> phi_bb360_29;
  TNode<IntPtrT> phi_bb360_32;
  TNode<BoolT> phi_bb360_33;
  TNode<IntPtrT> phi_bb360_35;
  TNode<IntPtrT> phi_bb360_36;
  TNode<BoolT> phi_bb360_37;
  TNode<BoolT> phi_bb360_48;
  TNode<Union<HeapObject, TaggedIndex>> tmp774;
  TNode<IntPtrT> tmp775;
  TNode<IntPtrT> tmp776;
  TNode<IntPtrT> tmp777;
  if (block360.is_used()) {
    ca_.Bind(&block360, &phi_bb360_20, &phi_bb360_26, &phi_bb360_27, &phi_bb360_28, &phi_bb360_29, &phi_bb360_32, &phi_bb360_33, &phi_bb360_35, &phi_bb360_36, &phi_bb360_37, &phi_bb360_48);
    std::tie(tmp774, tmp775) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb360_27}).Flatten();
    tmp776 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp777 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb360_27}, TNode<IntPtrT>{tmp776});
    ca_.Goto(&block359, phi_bb360_20, phi_bb360_26, tmp777, phi_bb360_28, phi_bb360_29, phi_bb360_32, phi_bb360_33, phi_bb360_35, phi_bb360_36, phi_bb360_37, phi_bb360_48, tmp774, tmp775);
  }

  TNode<IntPtrT> phi_bb361_20;
  TNode<IntPtrT> phi_bb361_26;
  TNode<IntPtrT> phi_bb361_27;
  TNode<IntPtrT> phi_bb361_28;
  TNode<IntPtrT> phi_bb361_29;
  TNode<IntPtrT> phi_bb361_32;
  TNode<BoolT> phi_bb361_33;
  TNode<IntPtrT> phi_bb361_35;
  TNode<IntPtrT> phi_bb361_36;
  TNode<BoolT> phi_bb361_37;
  TNode<BoolT> phi_bb361_48;
  if (block361.is_used()) {
    ca_.Bind(&block361, &phi_bb361_20, &phi_bb361_26, &phi_bb361_27, &phi_bb361_28, &phi_bb361_29, &phi_bb361_32, &phi_bb361_33, &phi_bb361_35, &phi_bb361_36, &phi_bb361_37, &phi_bb361_48);
    if (((CodeStubAssembler(state_).Is64()))) {
      ca_.Goto(&block363, phi_bb361_20, phi_bb361_26, phi_bb361_27, phi_bb361_28, phi_bb361_29, phi_bb361_32, phi_bb361_33, phi_bb361_35, phi_bb361_36, phi_bb361_37, phi_bb361_48);
    } else {
      ca_.Goto(&block364, phi_bb361_20, phi_bb361_26, phi_bb361_27, phi_bb361_28, phi_bb361_29, phi_bb361_32, phi_bb361_33, phi_bb361_35, phi_bb361_36, phi_bb361_37, phi_bb361_48);
    }
  }

  TNode<IntPtrT> phi_bb363_20;
  TNode<IntPtrT> phi_bb363_26;
  TNode<IntPtrT> phi_bb363_27;
  TNode<IntPtrT> phi_bb363_28;
  TNode<IntPtrT> phi_bb363_29;
  TNode<IntPtrT> phi_bb363_32;
  TNode<BoolT> phi_bb363_33;
  TNode<IntPtrT> phi_bb363_35;
  TNode<IntPtrT> phi_bb363_36;
  TNode<BoolT> phi_bb363_37;
  TNode<BoolT> phi_bb363_48;
  TNode<Union<HeapObject, TaggedIndex>> tmp778;
  TNode<IntPtrT> tmp779;
  TNode<IntPtrT> tmp780;
  TNode<IntPtrT> tmp781;
  if (block363.is_used()) {
    ca_.Bind(&block363, &phi_bb363_20, &phi_bb363_26, &phi_bb363_27, &phi_bb363_28, &phi_bb363_29, &phi_bb363_32, &phi_bb363_33, &phi_bb363_35, &phi_bb363_36, &phi_bb363_37, &phi_bb363_48);
    std::tie(tmp778, tmp779) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb363_29}).Flatten();
    tmp780 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp781 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb363_29}, TNode<IntPtrT>{tmp780});
    ca_.Goto(&block362, phi_bb363_20, phi_bb363_26, phi_bb363_27, phi_bb363_28, tmp781, phi_bb363_32, phi_bb363_33, phi_bb363_35, phi_bb363_36, phi_bb363_37, phi_bb363_48, tmp778, tmp779);
  }

  TNode<IntPtrT> phi_bb364_20;
  TNode<IntPtrT> phi_bb364_26;
  TNode<IntPtrT> phi_bb364_27;
  TNode<IntPtrT> phi_bb364_28;
  TNode<IntPtrT> phi_bb364_29;
  TNode<IntPtrT> phi_bb364_32;
  TNode<BoolT> phi_bb364_33;
  TNode<IntPtrT> phi_bb364_35;
  TNode<IntPtrT> phi_bb364_36;
  TNode<BoolT> phi_bb364_37;
  TNode<BoolT> phi_bb364_48;
  TNode<IntPtrT> tmp782;
  TNode<BoolT> tmp783;
  if (block364.is_used()) {
    ca_.Bind(&block364, &phi_bb364_20, &phi_bb364_26, &phi_bb364_27, &phi_bb364_28, &phi_bb364_29, &phi_bb364_32, &phi_bb364_33, &phi_bb364_35, &phi_bb364_36, &phi_bb364_37, &phi_bb364_48);
    tmp782 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp783 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb364_32}, TNode<IntPtrT>{tmp782});
    ca_.Branch(tmp783, &block366, std::vector<compiler::Node*>{phi_bb364_20, phi_bb364_26, phi_bb364_27, phi_bb364_28, phi_bb364_29, phi_bb364_32, phi_bb364_33, phi_bb364_35, phi_bb364_36, phi_bb364_37, phi_bb364_48}, &block367, std::vector<compiler::Node*>{phi_bb364_20, phi_bb364_26, phi_bb364_27, phi_bb364_28, phi_bb364_29, phi_bb364_32, phi_bb364_33, phi_bb364_35, phi_bb364_36, phi_bb364_37, phi_bb364_48});
  }

  TNode<IntPtrT> phi_bb366_20;
  TNode<IntPtrT> phi_bb366_26;
  TNode<IntPtrT> phi_bb366_27;
  TNode<IntPtrT> phi_bb366_28;
  TNode<IntPtrT> phi_bb366_29;
  TNode<IntPtrT> phi_bb366_32;
  TNode<BoolT> phi_bb366_33;
  TNode<IntPtrT> phi_bb366_35;
  TNode<IntPtrT> phi_bb366_36;
  TNode<BoolT> phi_bb366_37;
  TNode<BoolT> phi_bb366_48;
  TNode<Union<HeapObject, TaggedIndex>> tmp784;
  TNode<IntPtrT> tmp785;
  TNode<IntPtrT> tmp786;
  TNode<BoolT> tmp787;
  if (block366.is_used()) {
    ca_.Bind(&block366, &phi_bb366_20, &phi_bb366_26, &phi_bb366_27, &phi_bb366_28, &phi_bb366_29, &phi_bb366_32, &phi_bb366_33, &phi_bb366_35, &phi_bb366_36, &phi_bb366_37, &phi_bb366_48);
    std::tie(tmp784, tmp785) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb366_32}).Flatten();
    tmp786 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp787 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block362, phi_bb366_20, phi_bb366_26, phi_bb366_27, phi_bb366_28, phi_bb366_29, tmp786, tmp787, phi_bb366_35, phi_bb366_36, phi_bb366_37, phi_bb366_48, tmp784, tmp785);
  }

  TNode<IntPtrT> phi_bb367_20;
  TNode<IntPtrT> phi_bb367_26;
  TNode<IntPtrT> phi_bb367_27;
  TNode<IntPtrT> phi_bb367_28;
  TNode<IntPtrT> phi_bb367_29;
  TNode<IntPtrT> phi_bb367_32;
  TNode<BoolT> phi_bb367_33;
  TNode<IntPtrT> phi_bb367_35;
  TNode<IntPtrT> phi_bb367_36;
  TNode<BoolT> phi_bb367_37;
  TNode<BoolT> phi_bb367_48;
  TNode<Union<HeapObject, TaggedIndex>> tmp788;
  TNode<IntPtrT> tmp789;
  TNode<IntPtrT> tmp790;
  TNode<IntPtrT> tmp791;
  TNode<IntPtrT> tmp792;
  TNode<IntPtrT> tmp793;
  TNode<BoolT> tmp794;
  if (block367.is_used()) {
    ca_.Bind(&block367, &phi_bb367_20, &phi_bb367_26, &phi_bb367_27, &phi_bb367_28, &phi_bb367_29, &phi_bb367_32, &phi_bb367_33, &phi_bb367_35, &phi_bb367_36, &phi_bb367_37, &phi_bb367_48);
    std::tie(tmp788, tmp789) = NewReference_intptr_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp487}, TNode<IntPtrT>{phi_bb367_29}).Flatten();
    tmp790 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp791 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb367_29}, TNode<IntPtrT>{tmp790});
    tmp792 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp793 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp791}, TNode<IntPtrT>{tmp792});
    tmp794 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block362, phi_bb367_20, phi_bb367_26, phi_bb367_27, phi_bb367_28, tmp793, tmp791, tmp794, phi_bb367_35, phi_bb367_36, phi_bb367_37, phi_bb367_48, tmp788, tmp789);
  }

  TNode<IntPtrT> phi_bb362_20;
  TNode<IntPtrT> phi_bb362_26;
  TNode<IntPtrT> phi_bb362_27;
  TNode<IntPtrT> phi_bb362_28;
  TNode<IntPtrT> phi_bb362_29;
  TNode<IntPtrT> phi_bb362_32;
  TNode<BoolT> phi_bb362_33;
  TNode<IntPtrT> phi_bb362_35;
  TNode<IntPtrT> phi_bb362_36;
  TNode<BoolT> phi_bb362_37;
  TNode<BoolT> phi_bb362_48;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb362_50;
  TNode<IntPtrT> phi_bb362_51;
  if (block362.is_used()) {
    ca_.Bind(&block362, &phi_bb362_20, &phi_bb362_26, &phi_bb362_27, &phi_bb362_28, &phi_bb362_29, &phi_bb362_32, &phi_bb362_33, &phi_bb362_35, &phi_bb362_36, &phi_bb362_37, &phi_bb362_48, &phi_bb362_50, &phi_bb362_51);
    ca_.Goto(&block359, phi_bb362_20, phi_bb362_26, phi_bb362_27, phi_bb362_28, phi_bb362_29, phi_bb362_32, phi_bb362_33, phi_bb362_35, phi_bb362_36, phi_bb362_37, phi_bb362_48, phi_bb362_50, phi_bb362_51);
  }

  TNode<IntPtrT> phi_bb359_20;
  TNode<IntPtrT> phi_bb359_26;
  TNode<IntPtrT> phi_bb359_27;
  TNode<IntPtrT> phi_bb359_28;
  TNode<IntPtrT> phi_bb359_29;
  TNode<IntPtrT> phi_bb359_32;
  TNode<BoolT> phi_bb359_33;
  TNode<IntPtrT> phi_bb359_35;
  TNode<IntPtrT> phi_bb359_36;
  TNode<BoolT> phi_bb359_37;
  TNode<BoolT> phi_bb359_48;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb359_50;
  TNode<IntPtrT> phi_bb359_51;
  TNode<Union<HeapObject, TaggedIndex>> tmp795;
  TNode<IntPtrT> tmp796;
  TNode<IntPtrT> tmp797;
  TNode<UintPtrT> tmp798;
  TNode<UintPtrT> tmp799;
  TNode<BoolT> tmp800;
  if (block359.is_used()) {
    ca_.Bind(&block359, &phi_bb359_20, &phi_bb359_26, &phi_bb359_27, &phi_bb359_28, &phi_bb359_29, &phi_bb359_32, &phi_bb359_33, &phi_bb359_35, &phi_bb359_36, &phi_bb359_37, &phi_bb359_48, &phi_bb359_50, &phi_bb359_51);
    std::tie(tmp795, tmp796, tmp797) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb214_41}).Flatten();
    tmp798 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb359_20});
    tmp799 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp797});
    tmp800 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp798}, TNode<UintPtrT>{tmp799});
    ca_.Branch(tmp800, &block372, std::vector<compiler::Node*>{phi_bb359_20, phi_bb359_26, phi_bb359_27, phi_bb359_28, phi_bb359_29, phi_bb359_32, phi_bb359_33, phi_bb359_35, phi_bb359_36, phi_bb359_37, phi_bb359_48, phi_bb359_50, phi_bb359_51, phi_bb359_20, phi_bb359_20, phi_bb359_20, phi_bb359_20}, &block373, std::vector<compiler::Node*>{phi_bb359_20, phi_bb359_26, phi_bb359_27, phi_bb359_28, phi_bb359_29, phi_bb359_32, phi_bb359_33, phi_bb359_35, phi_bb359_36, phi_bb359_37, phi_bb359_48, phi_bb359_50, phi_bb359_51, phi_bb359_20, phi_bb359_20, phi_bb359_20, phi_bb359_20});
  }

  TNode<IntPtrT> phi_bb372_20;
  TNode<IntPtrT> phi_bb372_26;
  TNode<IntPtrT> phi_bb372_27;
  TNode<IntPtrT> phi_bb372_28;
  TNode<IntPtrT> phi_bb372_29;
  TNode<IntPtrT> phi_bb372_32;
  TNode<BoolT> phi_bb372_33;
  TNode<IntPtrT> phi_bb372_35;
  TNode<IntPtrT> phi_bb372_36;
  TNode<BoolT> phi_bb372_37;
  TNode<BoolT> phi_bb372_48;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb372_50;
  TNode<IntPtrT> phi_bb372_51;
  TNode<IntPtrT> phi_bb372_56;
  TNode<IntPtrT> phi_bb372_57;
  TNode<IntPtrT> phi_bb372_61;
  TNode<IntPtrT> phi_bb372_62;
  TNode<IntPtrT> tmp801;
  TNode<IntPtrT> tmp802;
  TNode<Union<HeapObject, TaggedIndex>> tmp803;
  TNode<IntPtrT> tmp804;
  TNode<Object> tmp805;
  TNode<IntPtrT> tmp806;
  if (block372.is_used()) {
    ca_.Bind(&block372, &phi_bb372_20, &phi_bb372_26, &phi_bb372_27, &phi_bb372_28, &phi_bb372_29, &phi_bb372_32, &phi_bb372_33, &phi_bb372_35, &phi_bb372_36, &phi_bb372_37, &phi_bb372_48, &phi_bb372_50, &phi_bb372_51, &phi_bb372_56, &phi_bb372_57, &phi_bb372_61, &phi_bb372_62);
    tmp801 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb372_62});
    tmp802 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp796}, TNode<IntPtrT>{tmp801});
    std::tie(tmp803, tmp804) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp795}, TNode<IntPtrT>{tmp802}).Flatten();
    tmp805 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp803, tmp804});
    tmp806 = CodeStubAssembler(state_).BitcastTaggedToWord(TNode<Object>{tmp805});
    CodeStubAssembler(state_).StoreReference<IntPtrT>(CodeStubAssembler::Reference{phi_bb372_50, phi_bb372_51}, tmp806);
    ca_.Goto(&block358, phi_bb372_20, tmp771, phi_bb372_26, phi_bb372_27, phi_bb372_28, phi_bb372_29, phi_bb372_32, phi_bb372_33, phi_bb372_35, phi_bb372_36, phi_bb372_37, phi_bb372_48);
  }

  TNode<IntPtrT> phi_bb373_20;
  TNode<IntPtrT> phi_bb373_26;
  TNode<IntPtrT> phi_bb373_27;
  TNode<IntPtrT> phi_bb373_28;
  TNode<IntPtrT> phi_bb373_29;
  TNode<IntPtrT> phi_bb373_32;
  TNode<BoolT> phi_bb373_33;
  TNode<IntPtrT> phi_bb373_35;
  TNode<IntPtrT> phi_bb373_36;
  TNode<BoolT> phi_bb373_37;
  TNode<BoolT> phi_bb373_48;
  TNode<Union<HeapObject, TaggedIndex>> phi_bb373_50;
  TNode<IntPtrT> phi_bb373_51;
  TNode<IntPtrT> phi_bb373_56;
  TNode<IntPtrT> phi_bb373_57;
  TNode<IntPtrT> phi_bb373_61;
  TNode<IntPtrT> phi_bb373_62;
  if (block373.is_used()) {
    ca_.Bind(&block373, &phi_bb373_20, &phi_bb373_26, &phi_bb373_27, &phi_bb373_28, &phi_bb373_29, &phi_bb373_32, &phi_bb373_33, &phi_bb373_35, &phi_bb373_36, &phi_bb373_37, &phi_bb373_48, &phi_bb373_50, &phi_bb373_51, &phi_bb373_56, &phi_bb373_57, &phi_bb373_61, &phi_bb373_62);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb358_20;
  TNode<IntPtrT> phi_bb358_25;
  TNode<IntPtrT> phi_bb358_26;
  TNode<IntPtrT> phi_bb358_27;
  TNode<IntPtrT> phi_bb358_28;
  TNode<IntPtrT> phi_bb358_29;
  TNode<IntPtrT> phi_bb358_32;
  TNode<BoolT> phi_bb358_33;
  TNode<IntPtrT> phi_bb358_35;
  TNode<IntPtrT> phi_bb358_36;
  TNode<BoolT> phi_bb358_37;
  TNode<BoolT> phi_bb358_48;
  TNode<IntPtrT> tmp807;
  TNode<IntPtrT> tmp808;
  if (block358.is_used()) {
    ca_.Bind(&block358, &phi_bb358_20, &phi_bb358_25, &phi_bb358_26, &phi_bb358_27, &phi_bb358_28, &phi_bb358_29, &phi_bb358_32, &phi_bb358_33, &phi_bb358_35, &phi_bb358_36, &phi_bb358_37, &phi_bb358_48);
    tmp807 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp808 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb358_20}, TNode<IntPtrT>{tmp807});
    ca_.Goto(&block350, tmp808, phi_bb358_25, phi_bb358_26, phi_bb358_27, phi_bb358_28, phi_bb358_29, phi_bb358_32, phi_bb358_33, phi_bb358_35, phi_bb358_36, phi_bb358_37, tmp764, phi_bb358_48);
  }

  TNode<IntPtrT> phi_bb349_20;
  TNode<IntPtrT> phi_bb349_25;
  TNode<IntPtrT> phi_bb349_26;
  TNode<IntPtrT> phi_bb349_27;
  TNode<IntPtrT> phi_bb349_28;
  TNode<IntPtrT> phi_bb349_29;
  TNode<IntPtrT> phi_bb349_32;
  TNode<BoolT> phi_bb349_33;
  TNode<IntPtrT> phi_bb349_35;
  TNode<IntPtrT> phi_bb349_36;
  TNode<BoolT> phi_bb349_37;
  TNode<IntPtrT> phi_bb349_46;
  TNode<BoolT> phi_bb349_48;
  if (block349.is_used()) {
    ca_.Bind(&block349, &phi_bb349_20, &phi_bb349_25, &phi_bb349_26, &phi_bb349_27, &phi_bb349_28, &phi_bb349_29, &phi_bb349_32, &phi_bb349_33, &phi_bb349_35, &phi_bb349_36, &phi_bb349_37, &phi_bb349_46, &phi_bb349_48);
    ca_.Goto(&block343, phi_bb349_20, phi_bb349_25, phi_bb349_26, phi_bb349_27, phi_bb349_28, phi_bb349_29, phi_bb349_32, phi_bb349_33, phi_bb349_35, phi_bb349_36, phi_bb349_37, phi_bb349_46, tmp755, phi_bb349_48);
  }

  TNode<IntPtrT> phi_bb343_20;
  TNode<IntPtrT> phi_bb343_25;
  TNode<IntPtrT> phi_bb343_26;
  TNode<IntPtrT> phi_bb343_27;
  TNode<IntPtrT> phi_bb343_28;
  TNode<IntPtrT> phi_bb343_29;
  TNode<IntPtrT> phi_bb343_32;
  TNode<BoolT> phi_bb343_33;
  TNode<IntPtrT> phi_bb343_35;
  TNode<IntPtrT> phi_bb343_36;
  TNode<BoolT> phi_bb343_37;
  TNode<IntPtrT> phi_bb343_46;
  TNode<IntPtrT> phi_bb343_47;
  TNode<BoolT> phi_bb343_48;
  TNode<IntPtrT> tmp809;
  TNode<IntPtrT> tmp810;
  TNode<IntPtrT> tmp811;
  TNode<IntPtrT> tmp812;
  TNode<IntPtrT> tmp813;
  TNode<IntPtrT> tmp814;
  TNode<IntPtrT> tmp815;
  TNode<Union<HeapObject, TaggedIndex>> tmp816;
  TNode<IntPtrT> tmp817;
  TNode<IntPtrT> tmp818;
  TNode<IntPtrT> tmp819;
  TNode<Union<HeapObject, TaggedIndex>> tmp820;
  TNode<IntPtrT> tmp821;
  TNode<IntPtrT> tmp822;
  TNode<IntPtrT> tmp823;
  TNode<Union<HeapObject, TaggedIndex>> tmp824;
  TNode<IntPtrT> tmp825;
  TNode<Float64T> tmp826;
  TNode<IntPtrT> tmp827;
  TNode<Union<HeapObject, TaggedIndex>> tmp828;
  TNode<IntPtrT> tmp829;
  TNode<Float64T> tmp830;
  if (block343.is_used()) {
    ca_.Bind(&block343, &phi_bb343_20, &phi_bb343_25, &phi_bb343_26, &phi_bb343_27, &phi_bb343_28, &phi_bb343_29, &phi_bb343_32, &phi_bb343_33, &phi_bb343_35, &phi_bb343_36, &phi_bb343_37, &phi_bb343_46, &phi_bb343_47, &phi_bb343_48);
    tmp809 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp486});
    tmp810 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp93});
    tmp811 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp809}, TNode<IntPtrT>{tmp810});
    tmp812 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    tmp813 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp811}, TNode<IntPtrT>{tmp812});
    tmp814 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp813}, TNode<IntPtrT>{tmp15});
    tmp815 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp816, tmp817) = GetRefAt_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp473}, TNode<IntPtrT>{tmp815}).Flatten();
    tmp818 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp816, tmp817});
    tmp819 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_intptr_0(state_)));
    std::tie(tmp820, tmp821) = GetRefAt_intptr_RawPtr_intptr_0(state_, TNode<RawPtrT>{tmp473}, TNode<IntPtrT>{tmp819}).Flatten();
    tmp822 = CodeStubAssembler(state_).LoadReference<IntPtrT>(CodeStubAssembler::Reference{tmp820, tmp821});
    tmp823 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp824, tmp825) = GetRefAt_float64_RawPtr_float64_0(state_, TNode<RawPtrT>{tmp475}, TNode<IntPtrT>{tmp823}).Flatten();
    tmp826 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp824, tmp825});
    tmp827 = FromConstexpr_intptr_constexpr_int31_0(state_, (SizeOf_float64_0(state_)));
    std::tie(tmp828, tmp829) = GetRefAt_float64_RawPtr_float64_0(state_, TNode<RawPtrT>{tmp475}, TNode<IntPtrT>{tmp827}).Flatten();
    tmp830 = CodeStubAssembler(state_).LoadReference<Float64T>(CodeStubAssembler::Reference{tmp828, tmp829});
    CodeStubAssembler(state_).SwitchFromTheCentralStack(TNode<RawPtrT>{tmp0});
    ca_.Goto(&block376);
  }

    ca_.Bind(&block376);
  return TorqueStructWasmToJSResult{TNode<IntPtrT>{tmp814}, TNode<IntPtrT>{tmp818}, TNode<IntPtrT>{tmp822}, TNode<Float64T>{tmp826}, TNode<Float64T>{tmp830}};
}

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=61&c=10
TNode<BoolT> Is_WasmImportData_WasmImportData_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<WasmImportData> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<WasmImportData> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_WasmImportData_0(state_, TNode<HeapObject>{p_o}, &label1);
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

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=66&c=4
TorqueStructReference_RawPtr_0 GetRefAt_RawPtr_RawPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
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

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=86&c=30
TorqueStructReference_RawPtr_uint32_0 NewOffHeapReference_RawPtr_uint32_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_ptr) {
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
    tmp1 = Convert_RawPtr_RawPtr_RawPtr_uint32_0(state_, TNode<RawPtrT>{p_ptr});
    tmp2 = Convert_intptr_RawPtr_0(state_, TNode<RawPtrT>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, kHeapObjectTag);
    tmp4 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp3});
    std::tie(tmp5, tmp6) = (TorqueStructReference_RawPtr_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp4}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_RawPtr_uint32_0{TNode<Union<HeapObject, TaggedIndex>>{tmp5}, TNode<IntPtrT>{tmp6}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=194&c=4
TorqueStructReference_intptr_0 GetRefAt_intptr_RawPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
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

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=313&c=15
TorqueStructReference_float64_0 GetRefAt_float64_RawPtr_float64_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset) {
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

} // namespace internal
} // namespace v8
