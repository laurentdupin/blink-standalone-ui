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
#include "torque-generated/third_party/v8/builtins/array-sort-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/array-from-async-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-slice-tq-csa.h"
#include "torque-generated/src/builtins/array-to-sorted-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/growable-fixed-array-tq-csa.h"
#include "torque-generated/src/builtins/math-tq-csa.h"
#include "torque-generated/src/builtins/object-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"
#include "torque-generated/src/objects/string-tq-csa.h"
#include "torque-generated/third_party/v8/builtins/array-sort-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=24&c=1
TNode<SortState> Cast_SortState_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<SortState> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = DownCastForTorqueClass_SortState_0(state_, TNode<HeapObject>{p_obj}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(label_CastError);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<SortState>{tmp0};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=80&c=1
TNode<Number> Compare_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<JSAny> p_x, TNode<JSAny> p_y) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp1;
  TNode<Undefined> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp1 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = Undefined_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp4;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp5;
  TNode<Number> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp5 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>(CodeStubAssembler::Reference{p_sortState, tmp4});
    tmp6 = ca_.CallBuiltin<Number>(Builtin::kSortCompareUserFn, p_context, tmp5, p_x, p_y);
    ca_.Goto(&block1, tmp6);
  }

  TNode<IntPtrT> tmp7;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp8;
  TNode<Number> tmp9;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp8 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>(CodeStubAssembler::Reference{p_sortState, tmp7});
    tmp9 = ca_.CallBuiltin<Number>(Builtin::kSortCompareDefault, p_context, tmp8, p_x, p_y);
    ca_.Goto(&block1, tmp9);
  }

  TNode<Number> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block5);
  }

    ca_.Bind(&block5);
  return TNode<Number>{phi_bb1_4};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=90&c=1
void CheckAccessor_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, compiler::CodeAssemblerLabel* label_Bailout) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<BoolT> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = IsFastJSArray_0(state_, TNode<Object>{tmp1}, TNode<Context>{p_context});
    tmp3 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp4;
  TNode<JSReceiver> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Map> tmp7;
  TNode<Int32T> tmp8;
  TNode<BoolT> tmp9;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp4});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp7 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp5, tmp6});
    tmp8 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp7});
    tmp9 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{tmp8});
    ca_.Branch(tmp9, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<JSReceiver> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Map> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Number> tmp15;
  TNode<Boolean> tmp16;
  TNode<BoolT> tmp17;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp11 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp10});
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp13 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_sortState, tmp12});
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp15 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_sortState, tmp14});
    tmp16 = ca_.CallBuiltin<Boolean>(Builtin::kCanUseSameAccessor_FastDoubleElements_0, p_context, tmp11, tmp13, tmp15);
    tmp17 = CodeStubAssembler(state_).IsFalse(TNode<Boolean>{tmp16});
    ca_.Branch(tmp17, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1);
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block7);
  }

  TNode<BoolT> tmp18;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp18 = CodeStubAssembler(state_).IsFastSmiElementsKind(TNode<Int32T>{tmp8});
    ca_.Branch(tmp18, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  TNode<JSReceiver> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Map> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Number> tmp24;
  TNode<Boolean> tmp25;
  TNode<BoolT> tmp26;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp20 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp19});
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp22 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_sortState, tmp21});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp24 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_sortState, tmp23});
    tmp25 = ca_.CallBuiltin<Boolean>(Builtin::kCanUseSameAccessor_FastSmiElements_0, p_context, tmp20, tmp22, tmp24);
    tmp26 = CodeStubAssembler(state_).IsFalse(TNode<Boolean>{tmp25});
    ca_.Branch(tmp26, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block1);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block12);
  }

  TNode<IntPtrT> tmp27;
  TNode<JSReceiver> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Map> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<Number> tmp32;
  TNode<Boolean> tmp33;
  TNode<BoolT> tmp34;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp28 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp27});
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp30 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_sortState, tmp29});
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp32 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_sortState, tmp31});
    tmp33 = ca_.CallBuiltin<Boolean>(Builtin::kCanUseSameAccessor_FastObjectElements_0, p_context, tmp28, tmp30, tmp32);
    tmp34 = CodeStubAssembler(state_).IsFalse(TNode<Boolean>{tmp33});
    ca_.Branch(tmp34, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Goto(&block1);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block12);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block7);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block17);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Bailout);
  }

    ca_.Bind(&block17);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=116&c=1
void ResetToGenericAccessor_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_sortState, bool p__isToSorted) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<True> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp1 = True_0(state_);
    CodeStubAssembler(state_).StoreReference<Boolean>(CodeStubAssembler::Reference{p_sortState, tmp0}, tmp1);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=126&c=1
TNode<IntPtrT> CalculateWorkArrayLength_0(compiler::CodeAssemblerState* state_, TNode<JSReceiver> p_receiver, TNode<Number> p_initialReceiverLength) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = ChangeSafeIntegerNumberToUintPtr_0(state_, TNode<Number>{p_initialReceiverLength}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<UintPtrT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    ca_.Goto(&block2, tmp2);
  }

  TNode<UintPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    tmp4 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{tmp0}, TNode<UintPtrT>{tmp3});
    ca_.Branch(tmp4, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{tmp0});
  }

  TNode<UintPtrT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp5 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    ca_.Goto(&block7, tmp5);
  }

  TNode<UintPtrT> phi_bb7_2;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_2);
    ca_.Goto(&block2, phi_bb7_2);
  }

  TNode<UintPtrT> phi_bb2_2;
  TNode<IntPtrT> tmp6;
  TNode<JSObject> tmp7;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_2);
    tmp6 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb2_2});
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = Cast_JSObject_0(state_, TNode<HeapObject>{p_receiver}, &label8);
    ca_.Goto(&block10, phi_bb2_2);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block11, phi_bb2_2);
    }
  }

  TNode<UintPtrT> phi_bb11_2;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_2);
    ca_.Goto(&block8, phi_bb11_2, tmp6);
  }

  TNode<UintPtrT> phi_bb10_2;
  TNode<IntPtrT> tmp9;
  TNode<FixedArrayBase> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Uint32T> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_2);
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp7, tmp9});
    tmp11 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp12 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp10, tmp11});
    tmp13 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp12});
    tmp14 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp14});
    ca_.Branch(tmp15, &block12, std::vector<compiler::Node*>{phi_bb10_2}, &block13, std::vector<compiler::Node*>{phi_bb10_2, tmp6});
  }

  TNode<UintPtrT> phi_bb12_2;
  TNode<IntPtrT> tmp16;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_2);
    tmp16 = CodeStubAssembler(state_).IntPtrMin(TNode<IntPtrT>{tmp6}, TNode<IntPtrT>{tmp13});
    ca_.Goto(&block13, phi_bb12_2, tmp16);
  }

  TNode<UintPtrT> phi_bb13_2;
  TNode<IntPtrT> phi_bb13_3;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_2, &phi_bb13_3);
    ca_.Goto(&block8, phi_bb13_2, phi_bb13_3);
  }

  TNode<UintPtrT> phi_bb8_2;
  TNode<IntPtrT> phi_bb8_3;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_2, &phi_bb8_3);
    ca_.Goto(&block14, phi_bb8_3);
  }

  TNode<IntPtrT> phi_bb14_2;
    ca_.Bind(&block14, &phi_bb14_2);
  return TNode<IntPtrT>{phi_bb14_2};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=158&c=1
TNode<SortState> NewSortState_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> p_comparefn, TNode<Number> p_initialReceiverLength, bool p_isToSorted) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_receiver, tmp0});
    tmp2 = Is_FastJSArray_JSReceiver_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver});
    ca_.Branch(tmp2, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<JSArray> tmp3;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = UnsafeCast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver});
    if (((CodeStubAssembler(state_).ConstexprBoolNot(p_isToSorted)))) {
      ca_.Goto(&block4);
    } else {
      ca_.Goto(&block5);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3});
    ca_.Goto(&block6);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block6);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block3);
  }

  TNode<IntPtrT> tmp4;
  TNode<Map> tmp5;
  TNode<False> tmp6;
  TNode<FixedArray> tmp7;
  TNode<FixedArray> tmp8;
  TNode<FixedArray> tmp9;
  TNode<FixedArray> tmp10;
  TNode<BoolT> tmp11;
  TNode<BoolT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<HeapObject> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Smi> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Smi> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Smi> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<Smi> tmp32;
  TNode<SortState> tmp33;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = CalculateWorkArrayLength_0(state_, TNode<JSReceiver>{p_receiver}, TNode<Number>{p_initialReceiverLength});
    tmp5 = CodeStubAssembler(state_).SortStateMapConstant();
    tmp6 = False_0(state_);
    tmp7 = kEmptyFixedArray_0(state_);
    tmp8 = kEmptyFixedArray_0(state_);
    tmp9 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp4});
    tmp10 = kEmptyFixedArray_0(state_);
    tmp11 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp13 = FromConstexpr_intptr_constexpr_int31_0(state_, 56);
    tmp14 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp13}, TNode<Map>{tmp5}, TNode<BoolT>{tmp11}, TNode<BoolT>{tmp12});
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp14, tmp15}, tmp5);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{tmp14, tmp16}, p_receiver);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp14, tmp17}, tmp1);
    tmp18 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{tmp14, tmp18}, p_initialReceiverLength);
    tmp19 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>(CodeStubAssembler::Reference{tmp14, tmp19}, p_comparefn);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Boolean>(CodeStubAssembler::Reference{tmp14, tmp20}, tmp6);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp22 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp14, tmp21}, tmp22);
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp24 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp14, tmp23}, tmp24);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp25}, tmp7);
    tmp26 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp26}, tmp8);
    tmp27 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp27}, tmp9);
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp14, tmp28}, tmp10);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp30 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp14, tmp29}, tmp30);
    tmp31 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp32 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp14, tmp31}, tmp32);
    tmp33 = TORQUE_CAST(TNode<HeapObject>{tmp14});
    ca_.Goto(&block7);
  }

    ca_.Bind(&block7);
  return TNode<SortState>{tmp33};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=198&c=1
TNode<Smi> kSuccess_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Smi> tmp0;
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
  return TNode<Smi>{tmp0};}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=205&c=1
int31_t kMaxMergePending_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x55ull)));}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=209&c=1
int31_t kMinGallopWins_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x7ull)));}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=219&c=1
TNode<Smi> kSortStateTempSize_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<Smi> tmp0;
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
  return TNode<Smi>{tmp0};}

TF_BUILTIN(Load_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Union<HeapObject, TaggedIndex>> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<UintPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    std::tie(tmp6, tmp7, tmp8) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp5}).Flatten();
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp11 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp11});
    ca_.Branch(tmp12, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Union<HeapObject, TaggedIndex>> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp13 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp6}, TNode<IntPtrT>{tmp14}).Flatten();
    tmp17 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16});
    tmp18 = UnsafeCast_Smi_OR_JSReceiver_OR_Undefined_OR_Null_OR_Boolean_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_TheHole_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp17});
    CodeStubAssembler(state_).Return(tmp18);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Load_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Union<HeapObject, TaggedIndex>> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<UintPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    std::tie(tmp6, tmp7, tmp8) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp5}).Flatten();
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp11 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp11});
    ca_.Branch(tmp12, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Union<HeapObject, TaggedIndex>> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Object> tmp17;
  TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> tmp18;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp13 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp6}, TNode<IntPtrT>{tmp14}).Flatten();
    tmp17 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16});
    tmp18 = UnsafeCast_Smi_OR_JSReceiver_OR_Undefined_OR_Null_OR_Boolean_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_TheHole_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp17});
    CodeStubAssembler(state_).Return(tmp18);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Load_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedDoubleArray> tmp5;
  TNode<Union<HeapObject, TaggedIndex>> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<UintPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    std::tie(tmp6, tmp7, tmp8) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp5}).Flatten();
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp11 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp11});
    ca_.Branch(tmp12, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Union<HeapObject, TaggedIndex>> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<BoolT> tmp17;
  TNode<BoolT> tmp18;
  TNode<Float64T> tmp19;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp13 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp9});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp6}, TNode<IntPtrT>{tmp14}).Flatten();
    std::tie(tmp17, tmp18, tmp19) = LoadFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp15}, TNode<IntPtrT>{tmp16}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp17, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp20;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp20 = FromConstexpr_bool_constexpr_bool_0(state_, V8_UNDEFINED_DOUBLE_BOOL);
    ca_.Branch(tmp20, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Branch(tmp18, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  TNode<TheHole> tmp21;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp21 = TheHole_0(state_);
    CodeStubAssembler(state_).Return(tmp21);
  }

  TNode<HeapNumber> tmp22;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp22 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp19});
    CodeStubAssembler(state_).Return(tmp22);
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 263});
      CodeStubAssembler(state_).FailAssert("Torque assert 'kEnableUndefinedDouble' failed", pos_stack);
    }
  }

  TNode<Undefined> tmp23;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp23 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp23);
  }
}

TF_BUILTIN(Store_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    CodeStubAssembler(state_).StoreFixedArrayElement(TNode<FixedArray>{tmp5}, TNode<Smi>{parameter2}, TNode<Smi>{tmp6});
    tmp7 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp7);
  }
}

TF_BUILTIN(Store_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedArray> tmp5;
  TNode<Union<HeapObject, TaggedIndex>> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<UintPtrT> tmp11;
  TNode<BoolT> tmp12;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    std::tie(tmp6, tmp7, tmp8) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp5}).Flatten();
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp11 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp10}, TNode<UintPtrT>{tmp11});
    ca_.Branch(tmp12, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Union<HeapObject, TaggedIndex>> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Smi> tmp17;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp13 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp14 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp13});
    std::tie(tmp15, tmp16) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp6}, TNode<IntPtrT>{tmp14}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp15, tmp16}, parameter3);
    tmp17 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp17);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Store_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSObject> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArrayBase> tmp4;
  TNode<FixedDoubleArray> tmp5;
  TNode<HeapNumber> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp4});
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_HeapNumber_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3}, &label7);
    ca_.Goto(&block3);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block4);
    }
  }

  TNode<BoolT> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, V8_UNDEFINED_DOUBLE_BOOL);
    ca_.Branch(tmp8, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<Float64T> tmp9;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp9 = Convert_float64_HeapNumber_0(state_, TNode<HeapNumber>{tmp6});
    CodeStubAssembler(state_).StoreFixedDoubleArrayElement(TNode<FixedDoubleArray>{tmp5}, TNode<Smi>{parameter2}, TNode<Float64T>{tmp9});
    ca_.Goto(&block1);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 302});
      CodeStubAssembler(state_).FailAssert("Torque assert 'kEnableUndefinedDouble' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp10;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp10 = Is_Undefined_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter3});
    ca_.Branch(tmp10, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 304});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<Undefined>(value)' failed", pos_stack);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).StoreFixedDoubleArrayUndefined(TNode<FixedDoubleArray>{tmp5}, TNode<Smi>{parameter2});
    ca_.Goto(&block1);
  }

  TNode<Smi> tmp11;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp11 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp11);
  }
}

TF_BUILTIN(Delete_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<Int32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp3});
    tmp5 = CodeStubAssembler(state_).IsHoleyFastElementsKind(TNode<Int32T>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 320});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsHoleyFastElementsKind(sortState.receiver.map.elements_kind)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<JSObject> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<FixedArrayBase> tmp10;
  TNode<FixedArray> tmp11;
  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp7 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp6});
    tmp8 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp8, tmp9});
    tmp11 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp10});
    std::tie(tmp12, tmp13, tmp14) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp11}).Flatten();
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp14});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<TheHole> tmp23;
  TNode<Smi> tmp24;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp19 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp15});
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp19});
    std::tie(tmp21, tmp22) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp12}, TNode<IntPtrT>{tmp20}).Flatten();
    tmp23 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp21, tmp22}, tmp23);
    tmp24 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp24);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Delete_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<Int32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp3});
    tmp5 = CodeStubAssembler(state_).IsHoleyFastElementsKind(TNode<Int32T>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 330});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsHoleyFastElementsKind(sortState.receiver.map.elements_kind)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<JSObject> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<FixedArrayBase> tmp10;
  TNode<FixedArray> tmp11;
  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp7 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp6});
    tmp8 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp8, tmp9});
    tmp11 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp10});
    std::tie(tmp12, tmp13, tmp14) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp11}).Flatten();
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp14});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<TheHole> tmp23;
  TNode<Smi> tmp24;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp19 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp15});
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp19});
    std::tie(tmp21, tmp22) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp12}, TNode<IntPtrT>{tmp20}).Flatten();
    tmp23 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp21, tmp22}, tmp23);
    tmp24 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp24);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(Delete_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Map> tmp3;
  TNode<Int32T> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp3 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp1, tmp2});
    tmp4 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp3});
    tmp5 = CodeStubAssembler(state_).IsHoleyFastElementsKind(TNode<Int32T>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 340});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsHoleyFastElementsKind(sortState.receiver.map.elements_kind)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp6;
  TNode<JSReceiver> tmp7;
  TNode<JSObject> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<FixedArrayBase> tmp10;
  TNode<FixedDoubleArray> tmp11;
  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp7 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp6});
    tmp8 = UnsafeCast_JSObject_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp7});
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp8, tmp9});
    tmp11 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp10});
    std::tie(tmp12, tmp13, tmp14) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp11}).Flatten();
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp14});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<BoolT> tmp23;
  TNode<BoolT> tmp24;
  TNode<Float64T> tmp25;
  TNode<Smi> tmp26;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp19 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp15});
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp19});
    std::tie(tmp21, tmp22) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp12}, TNode<IntPtrT>{tmp20}).Flatten();
    std::tie(tmp23, tmp24, tmp25) = kDoubleHole_0(state_).Flatten();
    StoreFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp21}, TNode<IntPtrT>{tmp22}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_undefined_or_hole_0{TNode<BoolT>{tmp23}, TNode<BoolT>{tmp24}, TNode<Float64T>{tmp25}});
    tmp26 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp26);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }
}

TF_BUILTIN(SortCompareDefault, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kComparefn);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kX);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kY);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Undefined> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Undefined_0(state_);
    tmp1 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{parameter1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 350});
      CodeStubAssembler(state_).FailAssert("Torque assert 'comparefn == Undefined' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp2;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter2});
    ca_.Branch(tmp2, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp3;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp3 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter3});
    ca_.Goto(&block7, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block7, tmp4);
  }

  TNode<BoolT> phi_bb7_5;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5);
    ca_.Branch(phi_bb7_5, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp7 = CodeStubAssembler(state_).SmiLexicographicCompare(TNode<Smi>{tmp5}, TNode<Smi>{tmp6});
    CodeStubAssembler(state_).Return(tmp7);
  }

  TNode<String> tmp8;
  TNode<String> tmp9;
  TNode<Smi> tmp10;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp8 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter2});
    tmp9 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter3});
    tmp10 = ca_.CallBuiltin<Smi>(Builtin::kStringCompare, TNode<Object>(), tmp8, tmp9);
    CodeStubAssembler(state_).Return(tmp10);
  }
}

TF_BUILTIN(SortCompareUserFn, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kComparefn);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kX);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kY);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Undefined> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Undefined_0(state_);
    tmp1 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{parameter1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 374});
      CodeStubAssembler(state_).FailAssert("Torque assert 'comparefn != Undefined' failed", pos_stack);
    }
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  TNode<Undefined> tmp3;
  TNode<JSAny> tmp4;
  TNode<Number> tmp5;
  TNode<BoolT> tmp6;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp3 = Undefined_0(state_);
    tmp4 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp2}, TNode<JSAny>{tmp3}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter3});
    tmp5 = CodeStubAssembler(state_).ToNumber_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp4});
    tmp6 = NumberIsNaN_0(state_, TNode<Number>{tmp5});
    ca_.Branch(tmp6, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<Number> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp7 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    CodeStubAssembler(state_).Return(tmp7);
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(CanUseSameAccessor_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedParameter<Map>(Descriptor::kInitialReceiverMap);
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedParameter<Number>(Descriptor::kInitialReceiverLength);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<True> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp0);
  }
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=408&c=1
TNode<Smi> GetPendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_sortState) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp1}, TNode<Smi>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 410});
      CodeStubAssembler(state_).FailAssert("Torque assert 'stackSize >= 0' failed", pos_stack);
    }
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=414&c=1
TNode<Smi> GetPendingRunBase_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_pendingRuns}).Flatten();
    tmp3 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Union<HeapObject, TaggedIndex>> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Object> tmp12;
  TNode<Smi> tmp13;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp4});
    tmp9 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp8});
    std::tie(tmp10, tmp11) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp9}).Flatten();
    tmp12 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp10, tmp11});
    compiler::CodeAssemblerLabel label14(&ca_);
    tmp13 = Cast_Smi_0(state_, TNode<Object>{tmp12}, &label14);
    ca_.Goto(&block16);
    if (label14.is_used()) {
      ca_.Bind(&label14);
      ca_.Goto(&block17);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp15;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp15 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block13, tmp15);
  }

  TNode<BoolT> tmp16;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp16 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block13, tmp16);
  }

  TNode<BoolT> phi_bb13_6;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    ca_.Branch(phi_bb13_6, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/cast.tq", 963});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Is<A>(o)' failed", pos_stack);
    }
  }

  TNode<Smi> tmp17;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp17 = TORQUE_CAST(TNode<Object>{tmp12});
    ca_.Goto(&block18);
  }

    ca_.Bind(&block18);
  return TNode<Smi>{tmp17};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=418&c=1
void SetPendingRunBase_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_pendingRuns}).Flatten();
    tmp3 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp4});
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp7 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp5}, TNode<UintPtrT>{tmp6});
    ca_.Branch(tmp7, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Union<HeapObject, TaggedIndex>> tmp10;
  TNode<IntPtrT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp4});
    tmp9 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp8});
    std::tie(tmp10, tmp11) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp9}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp10, tmp11}, p_value);
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=423&c=1
TNode<Smi> GetPendingRunLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_pendingRuns}).Flatten();
    tmp3 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp4 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp5 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp3}, TNode<Smi>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Object> tmp14;
  TNode<Smi> tmp15;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp6});
    tmp11 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp10});
    std::tie(tmp12, tmp13) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp11}).Flatten();
    tmp14 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp12, tmp13});
    tmp15 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp14});
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
  return TNode<Smi>{tmp15};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=428&c=1
void SetPendingRunLength_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<Smi> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_pendingRuns}).Flatten();
    tmp3 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{p_run}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp4 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp5 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp3}, TNode<Smi>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp5});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp6});
    tmp11 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp10});
    std::tie(tmp12, tmp13) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp11}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp12, tmp13}, p_value);
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=433&c=1
TNode<Smi> GetPendingPower_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingPowers, TNode<Smi> p_run) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_pendingPowers}).Flatten();
    tmp3 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_run});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Object> tmp11;
  TNode<Smi> tmp12;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp3});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp8}).Flatten();
    tmp11 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp9, tmp10});
    tmp12 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp11});
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
  return TNode<Smi>{tmp12};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=438&c=1
void SetPendingPower_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingPowers, TNode<Smi> p_run, TNode<Smi> p_value) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<UintPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_pendingPowers}).Flatten();
    tmp3 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_run});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp3});
    tmp5 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp6 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp4}, TNode<UintPtrT>{tmp5});
    ca_.Branch(tmp6, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp7 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp3});
    tmp8 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp7});
    std::tie(tmp9, tmp10) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp8}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp9, tmp10}, p_value);
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=446&c=1
TNode<Smi> NodePower32_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Smi> p_s1, TNode<Smi> p_n1, TNode<Smi> p_n2, TNode<Smi> p_n) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, IntPtrT, IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, IntPtrT, IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, IntPtrT, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
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
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_s1});
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp3 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp1});
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n1});
    tmp5 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp4});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n1});
    tmp7 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n2});
    tmp9 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n});
    ca_.Goto(&block4, tmp0, tmp5, tmp9);
  }

  TNode<Smi> phi_bb4_5;
  TNode<IntPtrT> phi_bb4_6;
  TNode<IntPtrT> phi_bb4_7;
  TNode<BoolT> tmp11;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5, &phi_bb4_6, &phi_bb4_7);
    tmp11 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp11, &block2, std::vector<compiler::Node*>{phi_bb4_5, phi_bb4_6, phi_bb4_7}, &block3, std::vector<compiler::Node*>{phi_bb4_5, phi_bb4_6, phi_bb4_7});
  }

  TNode<Smi> phi_bb2_5;
  TNode<IntPtrT> phi_bb2_6;
  TNode<IntPtrT> phi_bb2_7;
  TNode<Smi> tmp12;
  TNode<Smi> tmp13;
  TNode<BoolT> tmp14;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_5, &phi_bb2_6, &phi_bb2_7);
    tmp12 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp13 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb2_5}, TNode<Smi>{tmp12});
    tmp14 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb2_6}, TNode<IntPtrT>{tmp10});
    ca_.Branch(tmp14, &block5, std::vector<compiler::Node*>{phi_bb2_6, phi_bb2_7}, &block6, std::vector<compiler::Node*>{phi_bb2_6, phi_bb2_7});
  }

  TNode<IntPtrT> phi_bb5_6;
  TNode<IntPtrT> phi_bb5_7;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_6, &phi_bb5_7);
    tmp15 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb5_6}, TNode<IntPtrT>{tmp10});
    tmp16 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb5_7}, TNode<IntPtrT>{tmp10});
    ca_.Goto(&block7, tmp15, tmp16);
  }

  TNode<IntPtrT> phi_bb6_6;
  TNode<IntPtrT> phi_bb6_7;
  TNode<BoolT> tmp17;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_6, &phi_bb6_7);
    tmp17 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb6_7}, TNode<IntPtrT>{tmp10});
    ca_.Branch(tmp17, &block8, std::vector<compiler::Node*>{phi_bb6_6, phi_bb6_7}, &block9, std::vector<compiler::Node*>{phi_bb6_6, phi_bb6_7});
  }

  TNode<IntPtrT> phi_bb8_6;
  TNode<IntPtrT> phi_bb8_7;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_6, &phi_bb8_7);
    ca_.Goto(&block3, tmp13, phi_bb8_6, phi_bb8_7);
  }

  TNode<IntPtrT> phi_bb9_6;
  TNode<IntPtrT> phi_bb9_7;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_6, &phi_bb9_7);
    ca_.Goto(&block7, phi_bb9_6, phi_bb9_7);
  }

  TNode<IntPtrT> phi_bb7_6;
  TNode<IntPtrT> phi_bb7_7;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_6, &phi_bb7_7);
    tmp18 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp19 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{phi_bb7_6}, TNode<IntPtrT>{tmp18});
    tmp20 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp21 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{phi_bb7_7}, TNode<IntPtrT>{tmp20});
    ca_.Goto(&block4, tmp13, tmp19, tmp21);
  }

  TNode<Smi> phi_bb3_5;
  TNode<IntPtrT> phi_bb3_6;
  TNode<IntPtrT> phi_bb3_7;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_5, &phi_bb3_6, &phi_bb3_7);
    ca_.Goto(&block10, phi_bb3_5);
  }

  TNode<Smi> phi_bb10_5;
    ca_.Bind(&block10, &phi_bb10_5);
  return TNode<Smi>{phi_bb10_5};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=474&c=1
TNode<Smi> NodePower_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Smi> p_s1, TNode<Smi> p_n1, TNode<Smi> p_n2, TNode<Smi> p_n) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{p_s1}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 477});
      CodeStubAssembler(state_).FailAssert("Torque assert 's1 >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{p_n1}, TNode<Smi>{tmp2});
    ca_.Branch(tmp3, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp4;
  TNode<BoolT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp4 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp5 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{p_n2}, TNode<Smi>{tmp4});
    ca_.Goto(&block8, tmp5);
  }

  TNode<BoolT> tmp6;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block8, tmp6);
  }

  TNode<BoolT> phi_bb8_6;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_6);
    ca_.Branch(phi_bb8_6, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 478});
      CodeStubAssembler(state_).FailAssert("Torque assert 'n1 > 0 && n2 > 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  TNode<BoolT> tmp9;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_s1}, TNode<Smi>{p_n1});
    tmp8 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp7}, TNode<Smi>{p_n2});
    tmp9 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp8}, TNode<Smi>{p_n});
    ca_.Branch(tmp9, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 479});
      CodeStubAssembler(state_).FailAssert("Torque assert 's1 + n1 + n2 <= n' failed", pos_stack);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    if (((CodeStubAssembler(state_).ConstexprBoolNot((CodeStubAssembler(state_).Is64()))))) {
      ca_.Goto(&block11);
    } else {
      ca_.Goto(&block12);
    }
  }

  TNode<Smi> tmp10;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp10 = NodePower32_0(state_, TNode<Context>{p_context}, TNode<Smi>{p_s1}, TNode<Smi>{p_n1}, TNode<Smi>{p_n2}, TNode<Smi>{p_n});
    ca_.Goto(&block1, tmp10);
  }

  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<Int32T> tmp27;
  TNode<Uint32T> tmp28;
  TNode<Int32T> tmp29;
  TNode<Uint32T> tmp30;
  TNode<Uint64T> tmp31;
  TNode<Uint64T> tmp32;
  TNode<Uint64T> tmp33;
  TNode<Uint32T> tmp34;
  TNode<Int32T> tmp35;
  TNode<Int32T> tmp36;
  TNode<Smi> tmp37;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_s1});
    tmp12 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp13 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp11});
    tmp14 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n1});
    tmp15 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp14});
    tmp16 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n1});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp16});
    tmp18 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n2});
    tmp19 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp17}, TNode<IntPtrT>{tmp18});
    tmp20 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_n});
    tmp21 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1eull));
    tmp22 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{tmp15}, TNode<IntPtrT>{tmp21});
    tmp23 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp20});
    tmp24 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1eull));
    tmp25 = CodeStubAssembler(state_).WordShl(TNode<IntPtrT>{tmp19}, TNode<IntPtrT>{tmp24});
    tmp26 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp20});
    tmp27 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{tmp23});
    tmp28 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp27});
    tmp29 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{tmp26});
    tmp30 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp29});
    tmp31 = Convert_uint64_uint32_0(state_, TNode<Uint32T>{tmp28});
    tmp32 = Convert_uint64_uint32_0(state_, TNode<Uint32T>{tmp30});
    tmp33 = CodeStubAssembler(state_).Word64Xor(TNode<Uint64T>{tmp31}, TNode<Uint64T>{tmp32});
    tmp34 = Convert_uint32_uint64_0(state_, TNode<Uint64T>{tmp33});
    tmp35 = CodeStubAssembler(state_).Signed(TNode<Uint32T>{tmp34});
    tmp36 = CodeStubAssembler(state_).Word32Clz(TNode<Int32T>{tmp35});
    tmp37 = Convert_Smi_int32_0(state_, TNode<Int32T>{tmp36});
    ca_.Goto(&block1, tmp37);
  }

  TNode<Smi> phi_bb1_5;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5);
    ca_.Goto(&block14);
  }

    ca_.Bind(&block14);
  return TNode<Smi>{phi_bb1_5};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=505&c=1
void PushRun_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_base, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, kMaxMergePending_0(state_));
    tmp2 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp0}, TNode<Smi>{tmp1});
    ca_.Branch(tmp2, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 508});
      CodeStubAssembler(state_).FailAssert("Torque assert 'GetPendingRunsSize(sortState) < kMaxMergePending' failed", pos_stack);
    }
  }

  TNode<Smi> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<FixedArray> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<Smi> tmp7;
  TNode<Smi> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp5 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp4});
    SetPendingRunBase_0(state_, TNode<FixedArray>{tmp5}, TNode<Smi>{tmp3}, TNode<Smi>{p_base});
    SetPendingRunLength_0(state_, TNode<FixedArray>{tmp5}, TNode<Smi>{tmp3}, TNode<Smi>{p_length});
    tmp6 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp7 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp8 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp3}, TNode<Smi>{tmp7});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp6}, tmp8);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=521&c=1
TNode<FixedArray> GetTempArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_requestedSize) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArray> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<BoolT> tmp6;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = kSortStateTempSize_0(state_);
    tmp1 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp0}, TNode<Smi>{p_requestedSize});
    tmp2 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp3});
    tmp5 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp4});
    tmp6 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp2});
    ca_.Branch(tmp6, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<FixedArray> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp8 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp7});
    ca_.Goto(&block1, tmp8);
  }

  TNode<FixedArray> tmp9;
  TNode<IntPtrT> tmp10;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp9 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp2});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp10}, tmp9);
    ca_.Goto(&block1, tmp9);
  }

  TNode<FixedArray> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<FixedArray>{phi_bb1_3};
}

TF_BUILTIN(Copy, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<FixedArray> parameter1 = UncheckedParameter<FixedArray>(Descriptor::kSource);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kSrcPos);
  USE(parameter2);
  TNode<FixedArray> parameter3 = UncheckedParameter<FixedArray>(Descriptor::kTarget);
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedParameter<Smi>(Descriptor::kDstPos);
  USE(parameter4);
  TNode<Smi> parameter5 = UncheckedParameter<Smi>(Descriptor::kLength);
  USE(parameter5);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 541});
      CodeStubAssembler(state_).FailAssert("Torque assert 'srcPos >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{parameter4}, TNode<Smi>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 542});
      CodeStubAssembler(state_).FailAssert("Torque assert 'dstPos >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<BoolT> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter2});
    tmp5 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{parameter1});
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter5});
    tmp7 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp6});
    tmp8 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp7});
    ca_.Branch(tmp8, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 543});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Convert<intptr>(srcPos) <= source.length_intptr - Convert<intptr>(length)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<BoolT> tmp13;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter4});
    tmp10 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{parameter3});
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{parameter5});
    tmp12 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp10}, TNode<IntPtrT>{tmp11});
    tmp13 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp12});
    ca_.Branch(tmp13, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 546});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Convert<intptr>(dstPos) <= target.length_intptr - Convert<intptr>(length)' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp14;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp14 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{parameter2}, TNode<Smi>{parameter4});
    ca_.Branch(tmp14, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp15;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{parameter5});
    tmp16 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp17 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp15}, TNode<Smi>{tmp16});
    tmp18 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter5});
    tmp19 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp20 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp18}, TNode<Smi>{tmp19});
    ca_.Goto(&block14, tmp17, tmp20);
  }

  TNode<Smi> phi_bb14_6;
  TNode<Smi> phi_bb14_7;
  TNode<BoolT> tmp21;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_6, &phi_bb14_7);
    tmp21 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb14_6}, TNode<Smi>{parameter2});
    ca_.Branch(tmp21, &block12, std::vector<compiler::Node*>{phi_bb14_6, phi_bb14_7}, &block13, std::vector<compiler::Node*>{phi_bb14_6, phi_bb14_7});
  }

  TNode<Smi> phi_bb12_6;
  TNode<Smi> phi_bb12_7;
  TNode<Union<HeapObject, TaggedIndex>> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<UintPtrT> tmp28;
  TNode<UintPtrT> tmp29;
  TNode<BoolT> tmp30;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_6, &phi_bb12_7);
    std::tie(tmp22, tmp23, tmp24) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter3}).Flatten();
    tmp25 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp26 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb12_7}, TNode<Smi>{tmp25});
    tmp27 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb12_7});
    tmp28 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp27});
    tmp29 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp24});
    tmp30 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp28}, TNode<UintPtrT>{tmp29});
    ca_.Branch(tmp30, &block19, std::vector<compiler::Node*>{phi_bb12_6, phi_bb12_7, phi_bb12_7}, &block20, std::vector<compiler::Node*>{phi_bb12_6, phi_bb12_7, phi_bb12_7});
  }

  TNode<Smi> phi_bb19_6;
  TNode<Smi> phi_bb19_12;
  TNode<Smi> phi_bb19_13;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<Union<HeapObject, TaggedIndex>> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<Union<HeapObject, TaggedIndex>> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Smi> tmp38;
  TNode<Smi> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<UintPtrT> tmp41;
  TNode<UintPtrT> tmp42;
  TNode<BoolT> tmp43;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_6, &phi_bb19_12, &phi_bb19_13);
    tmp31 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp27});
    tmp32 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp23}, TNode<IntPtrT>{tmp31});
    std::tie(tmp33, tmp34) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp22}, TNode<IntPtrT>{tmp32}).Flatten();
    std::tie(tmp35, tmp36, tmp37) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter1}).Flatten();
    tmp38 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp39 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb19_6}, TNode<Smi>{tmp38});
    tmp40 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb19_6});
    tmp41 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp40});
    tmp42 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp37});
    tmp43 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp41}, TNode<UintPtrT>{tmp42});
    ca_.Branch(tmp43, &block27, std::vector<compiler::Node*>{phi_bb19_12, phi_bb19_13, phi_bb19_6, phi_bb19_6}, &block28, std::vector<compiler::Node*>{phi_bb19_12, phi_bb19_13, phi_bb19_6, phi_bb19_6});
  }

  TNode<Smi> phi_bb20_6;
  TNode<Smi> phi_bb20_12;
  TNode<Smi> phi_bb20_13;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_6, &phi_bb20_12, &phi_bb20_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb27_12;
  TNode<Smi> phi_bb27_13;
  TNode<Smi> phi_bb27_20;
  TNode<Smi> phi_bb27_21;
  TNode<IntPtrT> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<Union<HeapObject, TaggedIndex>> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Object> tmp48;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_12, &phi_bb27_13, &phi_bb27_20, &phi_bb27_21);
    tmp44 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp40});
    tmp45 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp44});
    std::tie(tmp46, tmp47) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp35}, TNode<IntPtrT>{tmp45}).Flatten();
    tmp48 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp46, tmp47});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp33, tmp34}, tmp48);
    ca_.Goto(&block14, tmp39, tmp26);
  }

  TNode<Smi> phi_bb28_12;
  TNode<Smi> phi_bb28_13;
  TNode<Smi> phi_bb28_20;
  TNode<Smi> phi_bb28_21;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_12, &phi_bb28_13, &phi_bb28_20, &phi_bb28_21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb13_6;
  TNode<Smi> phi_bb13_7;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6, &phi_bb13_7);
    ca_.Goto(&block11);
  }

  TNode<Smi> tmp49;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp49 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{parameter5});
    ca_.Goto(&block33, parameter2, parameter4);
  }

  TNode<Smi> phi_bb33_6;
  TNode<Smi> phi_bb33_7;
  TNode<BoolT> tmp50;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_6, &phi_bb33_7);
    tmp50 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb33_6}, TNode<Smi>{tmp49});
    ca_.Branch(tmp50, &block31, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7}, &block32, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7});
  }

  TNode<Smi> phi_bb31_6;
  TNode<Smi> phi_bb31_7;
  TNode<Union<HeapObject, TaggedIndex>> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<Smi> tmp54;
  TNode<Smi> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<UintPtrT> tmp57;
  TNode<UintPtrT> tmp58;
  TNode<BoolT> tmp59;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_6, &phi_bb31_7);
    std::tie(tmp51, tmp52, tmp53) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter3}).Flatten();
    tmp54 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp55 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb31_7}, TNode<Smi>{tmp54});
    tmp56 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb31_7});
    tmp57 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp56});
    tmp58 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp53});
    tmp59 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp57}, TNode<UintPtrT>{tmp58});
    ca_.Branch(tmp59, &block38, std::vector<compiler::Node*>{phi_bb31_6, phi_bb31_7, phi_bb31_7}, &block39, std::vector<compiler::Node*>{phi_bb31_6, phi_bb31_7, phi_bb31_7});
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_13;
  TNode<Smi> phi_bb38_14;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<Union<HeapObject, TaggedIndex>> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<Union<HeapObject, TaggedIndex>> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<Smi> tmp67;
  TNode<Smi> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<UintPtrT> tmp70;
  TNode<UintPtrT> tmp71;
  TNode<BoolT> tmp72;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_13, &phi_bb38_14);
    tmp60 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp56});
    tmp61 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp52}, TNode<IntPtrT>{tmp60});
    std::tie(tmp62, tmp63) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp51}, TNode<IntPtrT>{tmp61}).Flatten();
    std::tie(tmp64, tmp65, tmp66) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter1}).Flatten();
    tmp67 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp68 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb38_6}, TNode<Smi>{tmp67});
    tmp69 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb38_6});
    tmp70 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp69});
    tmp71 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp66});
    tmp72 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp70}, TNode<UintPtrT>{tmp71});
    ca_.Branch(tmp72, &block46, std::vector<compiler::Node*>{phi_bb38_13, phi_bb38_14, phi_bb38_6, phi_bb38_6}, &block47, std::vector<compiler::Node*>{phi_bb38_13, phi_bb38_14, phi_bb38_6, phi_bb38_6});
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_13;
  TNode<Smi> phi_bb39_14;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_13, &phi_bb39_14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb46_13;
  TNode<Smi> phi_bb46_14;
  TNode<Smi> phi_bb46_21;
  TNode<Smi> phi_bb46_22;
  TNode<IntPtrT> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<Union<HeapObject, TaggedIndex>> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<Object> tmp77;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_13, &phi_bb46_14, &phi_bb46_21, &phi_bb46_22);
    tmp73 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp69});
    tmp74 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp65}, TNode<IntPtrT>{tmp73});
    std::tie(tmp75, tmp76) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp64}, TNode<IntPtrT>{tmp74}).Flatten();
    tmp77 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp75, tmp76});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp62, tmp63}, tmp77);
    ca_.Goto(&block33, tmp68, tmp55);
  }

  TNode<Smi> phi_bb47_13;
  TNode<Smi> phi_bb47_14;
  TNode<Smi> phi_bb47_21;
  TNode<Smi> phi_bb47_22;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_13, &phi_bb47_14, &phi_bb47_21, &phi_bb47_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb32_6;
  TNode<Smi> phi_bb32_7;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_6, &phi_bb32_7);
    ca_.Goto(&block11);
  }

  TNode<Smi> tmp78;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp78 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp78);
  }
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=584&c=1
void BinaryInsertionSort_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_low, TNode<Smi> p_startArg, TNode<Smi> p_high) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block24(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{p_low}, TNode<Smi>{p_startArg});
    ca_.Branch(tmp0, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp1;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp1 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{p_startArg}, TNode<Smi>{p_high});
    ca_.Goto(&block6, tmp1);
  }

  TNode<BoolT> tmp2;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block6, tmp2);
  }

  TNode<BoolT> phi_bb6_6;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_6);
    ca_.Branch(phi_bb6_6, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 587});
      CodeStubAssembler(state_).FailAssert("Torque assert 'low <= startArg && startArg <= high' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp3;
  TNode<FixedArray> tmp4;
  TNode<BoolT> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp4 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp3});
    tmp5 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_low}, TNode<Smi>{p_startArg});
    ca_.Branch(tmp5, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp6;
  TNode<Smi> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp6 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp7 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_startArg}, TNode<Smi>{tmp6});
    ca_.Goto(&block9, tmp7);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block9, p_startArg);
  }

  TNode<Smi> phi_bb9_6;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_6);
    ca_.Goto(&block13, phi_bb9_6);
  }

  TNode<Smi> phi_bb13_6;
  TNode<BoolT> tmp8;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    tmp8 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb13_6}, TNode<Smi>{p_high});
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{phi_bb13_6}, &block12, std::vector<compiler::Node*>{phi_bb13_6});
  }

  TNode<Smi> phi_bb11_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_6);
    std::tie(tmp9, tmp10, tmp11) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp4}).Flatten();
    tmp12 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb11_6});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp12});
    tmp14 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp15 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp13}, TNode<UintPtrT>{tmp14});
    ca_.Branch(tmp15, &block19, std::vector<compiler::Node*>{phi_bb11_6, phi_bb11_6, phi_bb11_6, phi_bb11_6}, &block20, std::vector<compiler::Node*>{phi_bb11_6, phi_bb11_6, phi_bb11_6, phi_bb11_6});
  }

  TNode<Smi> phi_bb19_6;
  TNode<Smi> phi_bb19_8;
  TNode<Smi> phi_bb19_13;
  TNode<Smi> phi_bb19_14;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Object> tmp20;
  TNode<JSAny> tmp21;
  TNode<BoolT> tmp22;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_6, &phi_bb19_8, &phi_bb19_13, &phi_bb19_14);
    tmp16 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp12});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp10}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp9}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp20});
    tmp22 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_low}, TNode<Smi>{phi_bb19_8});
    ca_.Branch(tmp22, &block23, std::vector<compiler::Node*>{phi_bb19_6, phi_bb19_8}, &block24, std::vector<compiler::Node*>{phi_bb19_6, phi_bb19_8});
  }

  TNode<Smi> phi_bb20_6;
  TNode<Smi> phi_bb20_8;
  TNode<Smi> phi_bb20_13;
  TNode<Smi> phi_bb20_14;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_6, &phi_bb20_8, &phi_bb20_13, &phi_bb20_14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb24_6;
  TNode<Smi> phi_bb24_8;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_6, &phi_bb24_8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 603});
      CodeStubAssembler(state_).FailAssert("Torque assert 'left < right' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb23_6;
  TNode<Smi> phi_bb23_8;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_6, &phi_bb23_8);
    ca_.Goto(&block27, phi_bb23_6, p_low, phi_bb23_8);
  }

  TNode<Smi> phi_bb27_6;
  TNode<Smi> phi_bb27_7;
  TNode<Smi> phi_bb27_8;
  TNode<BoolT> tmp23;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_6, &phi_bb27_7, &phi_bb27_8);
    tmp23 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb27_7}, TNode<Smi>{phi_bb27_8});
    ca_.Branch(tmp23, &block25, std::vector<compiler::Node*>{phi_bb27_6, phi_bb27_7, phi_bb27_8}, &block26, std::vector<compiler::Node*>{phi_bb27_6, phi_bb27_7, phi_bb27_8});
  }

  TNode<Smi> phi_bb25_6;
  TNode<Smi> phi_bb25_7;
  TNode<Smi> phi_bb25_8;
  TNode<Smi> tmp24;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  TNode<Union<HeapObject, TaggedIndex>> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<UintPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<BoolT> tmp33;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_6, &phi_bb25_7, &phi_bb25_8);
    tmp24 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb25_8}, TNode<Smi>{phi_bb25_7});
    tmp25 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{tmp24}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp26 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb25_7}, TNode<Smi>{tmp25});
    std::tie(tmp27, tmp28, tmp29) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp4}).Flatten();
    tmp30 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp26});
    tmp31 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp29});
    tmp33 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp31}, TNode<UintPtrT>{tmp32});
    ca_.Branch(tmp33, &block32, std::vector<compiler::Node*>{phi_bb25_6, phi_bb25_7, phi_bb25_8}, &block33, std::vector<compiler::Node*>{phi_bb25_6, phi_bb25_7, phi_bb25_8});
  }

  TNode<Smi> phi_bb32_6;
  TNode<Smi> phi_bb32_7;
  TNode<Smi> phi_bb32_8;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<Union<HeapObject, TaggedIndex>> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Object> tmp38;
  TNode<JSAny> tmp39;
  TNode<Number> tmp40;
  TNode<Number> tmp41;
  TNode<BoolT> tmp42;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_6, &phi_bb32_7, &phi_bb32_8);
    tmp34 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp30});
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp34});
    std::tie(tmp36, tmp37) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp27}, TNode<IntPtrT>{tmp35}).Flatten();
    tmp38 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp36, tmp37});
    tmp39 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp38});
    tmp40 = Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<JSAny>{tmp21}, TNode<JSAny>{tmp39});
    tmp41 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp42 = NumberIsLessThan_0(state_, TNode<Number>{tmp40}, TNode<Number>{tmp41});
    ca_.Branch(tmp42, &block36, std::vector<compiler::Node*>{phi_bb32_6, phi_bb32_7, phi_bb32_8}, &block37, std::vector<compiler::Node*>{phi_bb32_6, phi_bb32_7, phi_bb32_8});
  }

  TNode<Smi> phi_bb33_6;
  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_8;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_6, &phi_bb33_7, &phi_bb33_8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb36_6;
  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_8;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_6, &phi_bb36_7, &phi_bb36_8);
    ca_.Goto(&block38, phi_bb36_6, phi_bb36_7, tmp26);
  }

  TNode<Smi> phi_bb37_6;
  TNode<Smi> phi_bb37_7;
  TNode<Smi> phi_bb37_8;
  TNode<Smi> tmp43;
  TNode<Smi> tmp44;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_6, &phi_bb37_7, &phi_bb37_8);
    tmp43 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp44 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp26}, TNode<Smi>{tmp43});
    ca_.Goto(&block38, phi_bb37_6, tmp44, phi_bb37_8);
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_8;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_7, &phi_bb38_8);
    ca_.Goto(&block27, phi_bb38_6, phi_bb38_7, phi_bb38_8);
  }

  TNode<Smi> phi_bb26_6;
  TNode<Smi> phi_bb26_7;
  TNode<Smi> phi_bb26_8;
  TNode<BoolT> tmp45;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_6, &phi_bb26_7, &phi_bb26_8);
    tmp45 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb26_7}, TNode<Smi>{phi_bb26_8});
    ca_.Branch(tmp45, &block39, std::vector<compiler::Node*>{phi_bb26_6, phi_bb26_7, phi_bb26_8}, &block40, std::vector<compiler::Node*>{phi_bb26_6, phi_bb26_7, phi_bb26_8});
  }

  TNode<Smi> phi_bb40_6;
  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_8;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_7, &phi_bb40_8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 617});
      CodeStubAssembler(state_).FailAssert("Torque assert 'left == right' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_8;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_7, &phi_bb39_8);
    ca_.Goto(&block43, phi_bb39_6, phi_bb39_7, phi_bb39_8, phi_bb39_6);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_8;
  TNode<Smi> phi_bb43_10;
  TNode<BoolT> tmp46;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_7, &phi_bb43_8, &phi_bb43_10);
    tmp46 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb43_10}, TNode<Smi>{phi_bb43_7});
    ca_.Branch(tmp46, &block41, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7, phi_bb43_8, phi_bb43_10}, &block42, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7, phi_bb43_8, phi_bb43_10});
  }

  TNode<Smi> phi_bb41_6;
  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_8;
  TNode<Smi> phi_bb41_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<UintPtrT> tmp51;
  TNode<UintPtrT> tmp52;
  TNode<BoolT> tmp53;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_6, &phi_bb41_7, &phi_bb41_8, &phi_bb41_10);
    std::tie(tmp47, tmp48, tmp49) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp4}).Flatten();
    tmp50 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb41_10});
    tmp51 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp50});
    tmp52 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp49});
    tmp53 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp51}, TNode<UintPtrT>{tmp52});
    ca_.Branch(tmp53, &block49, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7, phi_bb41_8, phi_bb41_10, phi_bb41_10, phi_bb41_10}, &block50, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7, phi_bb41_8, phi_bb41_10, phi_bb41_10, phi_bb41_10});
  }

  TNode<Smi> phi_bb49_6;
  TNode<Smi> phi_bb49_7;
  TNode<Smi> phi_bb49_8;
  TNode<Smi> phi_bb49_10;
  TNode<Smi> phi_bb49_15;
  TNode<Smi> phi_bb49_16;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<Union<HeapObject, TaggedIndex>> tmp56;
  TNode<IntPtrT> tmp57;
  TNode<Union<HeapObject, TaggedIndex>> tmp58;
  TNode<IntPtrT> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<Smi> tmp61;
  TNode<Smi> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<BoolT> tmp66;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_6, &phi_bb49_7, &phi_bb49_8, &phi_bb49_10, &phi_bb49_15, &phi_bb49_16);
    tmp54 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp50});
    tmp55 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp48}, TNode<IntPtrT>{tmp54});
    std::tie(tmp56, tmp57) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp47}, TNode<IntPtrT>{tmp55}).Flatten();
    std::tie(tmp58, tmp59, tmp60) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp4}).Flatten();
    tmp61 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp62 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb49_10}, TNode<Smi>{tmp61});
    tmp63 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp62});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp60});
    tmp66 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp64}, TNode<UintPtrT>{tmp65});
    ca_.Branch(tmp66, &block57, std::vector<compiler::Node*>{phi_bb49_6, phi_bb49_7, phi_bb49_8, phi_bb49_10, phi_bb49_15, phi_bb49_16}, &block58, std::vector<compiler::Node*>{phi_bb49_6, phi_bb49_7, phi_bb49_8, phi_bb49_10, phi_bb49_15, phi_bb49_16});
  }

  TNode<Smi> phi_bb50_6;
  TNode<Smi> phi_bb50_7;
  TNode<Smi> phi_bb50_8;
  TNode<Smi> phi_bb50_10;
  TNode<Smi> phi_bb50_15;
  TNode<Smi> phi_bb50_16;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_6, &phi_bb50_7, &phi_bb50_8, &phi_bb50_10, &phi_bb50_15, &phi_bb50_16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb57_6;
  TNode<Smi> phi_bb57_7;
  TNode<Smi> phi_bb57_8;
  TNode<Smi> phi_bb57_10;
  TNode<Smi> phi_bb57_15;
  TNode<Smi> phi_bb57_16;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<Union<HeapObject, TaggedIndex>> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<Object> tmp71;
  TNode<Smi> tmp72;
  TNode<Smi> tmp73;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_6, &phi_bb57_7, &phi_bb57_8, &phi_bb57_10, &phi_bb57_15, &phi_bb57_16);
    tmp67 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp63});
    tmp68 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp59}, TNode<IntPtrT>{tmp67});
    std::tie(tmp69, tmp70) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp58}, TNode<IntPtrT>{tmp68}).Flatten();
    tmp71 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp69, tmp70});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp56, tmp57}, tmp71);
    tmp72 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp73 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb57_10}, TNode<Smi>{tmp72});
    ca_.Goto(&block43, phi_bb57_6, phi_bb57_7, phi_bb57_8, tmp73);
  }

  TNode<Smi> phi_bb58_6;
  TNode<Smi> phi_bb58_7;
  TNode<Smi> phi_bb58_8;
  TNode<Smi> phi_bb58_10;
  TNode<Smi> phi_bb58_15;
  TNode<Smi> phi_bb58_16;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_6, &phi_bb58_7, &phi_bb58_8, &phi_bb58_10, &phi_bb58_15, &phi_bb58_16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb42_6;
  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_8;
  TNode<Smi> phi_bb42_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<UintPtrT> tmp78;
  TNode<UintPtrT> tmp79;
  TNode<BoolT> tmp80;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_7, &phi_bb42_8, &phi_bb42_10);
    std::tie(tmp74, tmp75, tmp76) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp4}).Flatten();
    tmp77 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb42_7});
    tmp78 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp77});
    tmp79 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp76});
    tmp80 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp78}, TNode<UintPtrT>{tmp79});
    ca_.Branch(tmp80, &block65, std::vector<compiler::Node*>{phi_bb42_6, phi_bb42_7, phi_bb42_8, phi_bb42_7, phi_bb42_7}, &block66, std::vector<compiler::Node*>{phi_bb42_6, phi_bb42_7, phi_bb42_8, phi_bb42_7, phi_bb42_7});
  }

  TNode<Smi> phi_bb65_6;
  TNode<Smi> phi_bb65_7;
  TNode<Smi> phi_bb65_8;
  TNode<Smi> phi_bb65_14;
  TNode<Smi> phi_bb65_15;
  TNode<IntPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<Union<HeapObject, TaggedIndex>> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<Smi> tmp85;
  TNode<Smi> tmp86;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_6, &phi_bb65_7, &phi_bb65_8, &phi_bb65_14, &phi_bb65_15);
    tmp81 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp77});
    tmp82 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp75}, TNode<IntPtrT>{tmp81});
    std::tie(tmp83, tmp84) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp74}, TNode<IntPtrT>{tmp82}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp83, tmp84}, tmp21);
    tmp85 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp86 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb65_6}, TNode<Smi>{tmp85});
    ca_.Goto(&block13, tmp86);
  }

  TNode<Smi> phi_bb66_6;
  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_8;
  TNode<Smi> phi_bb66_14;
  TNode<Smi> phi_bb66_15;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_6, &phi_bb66_7, &phi_bb66_8, &phi_bb66_14, &phi_bb66_15);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb12_6;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_6);
    ca_.Goto(&block69);
  }

    ca_.Bind(&block69);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=650&c=1
TNode<Smi> CountAndMakeRun_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_lowArg, TNode<Smi> p_high) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, JSAny, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Number, JSAny> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_lowArg}, TNode<Smi>{p_high});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 653});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lowArg < high' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp1;
  TNode<FixedArray> tmp2;
  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  TNode<BoolT> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp2 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp1});
    tmp3 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp4 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_lowArg}, TNode<Smi>{tmp3});
    tmp5 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp4}, TNode<Smi>{p_high});
    ca_.Branch(tmp5, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    ca_.Goto(&block1, tmp6);
  }

  TNode<Smi> tmp7;
  TNode<Union<HeapObject, TaggedIndex>> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    std::tie(tmp8, tmp9, tmp10) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp2}).Flatten();
    tmp11 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp4});
    tmp12 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp14 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp12}, TNode<UintPtrT>{tmp13});
    ca_.Branch(tmp14, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<Union<HeapObject, TaggedIndex>> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<Object> tmp19;
  TNode<JSAny> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Smi> tmp24;
  TNode<Smi> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<UintPtrT> tmp27;
  TNode<UintPtrT> tmp28;
  TNode<BoolT> tmp29;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp15 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp11});
    tmp16 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp15});
    std::tie(tmp17, tmp18) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp8}, TNode<IntPtrT>{tmp16}).Flatten();
    tmp19 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp17, tmp18});
    tmp20 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp19});
    std::tie(tmp21, tmp22, tmp23) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp2}).Flatten();
    tmp24 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp25 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp4}, TNode<Smi>{tmp24});
    tmp26 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp25});
    tmp27 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp26});
    tmp28 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp23});
    tmp29 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp27}, TNode<UintPtrT>{tmp28});
    ca_.Branch(tmp29, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<Union<HeapObject, TaggedIndex>> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<Object> tmp34;
  TNode<JSAny> tmp35;
  TNode<Number> tmp36;
  TNode<Number> tmp37;
  TNode<BoolT> tmp38;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp30 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp26});
    tmp31 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp30});
    std::tie(tmp32, tmp33) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp21}, TNode<IntPtrT>{tmp31}).Flatten();
    tmp34 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp32, tmp33});
    tmp35 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp34});
    tmp36 = Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<JSAny>{tmp20}, TNode<JSAny>{tmp35});
    tmp37 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp38 = NumberIsLessThan_0(state_, TNode<Number>{tmp36}, TNode<Number>{tmp37});
    ca_.Branch(tmp38, &block22, std::vector<compiler::Node*>{}, &block23, std::vector<compiler::Node*>{});
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp39;
  if (block22.is_used()) {
    ca_.Bind(&block22);
    tmp39 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block24, tmp39);
  }

  TNode<BoolT> tmp40;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp40 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block24, tmp40);
  }

  TNode<BoolT> phi_bb24_10;
  TNode<Smi> tmp41;
  TNode<Smi> tmp42;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_10);
    tmp41 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp42 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp4}, TNode<Smi>{tmp41});
    ca_.Goto(&block28, tmp7, tmp36, tmp20, tmp42);
  }

  TNode<Smi> phi_bb28_6;
  TNode<Number> phi_bb28_9;
  TNode<JSAny> phi_bb28_11;
  TNode<Smi> phi_bb28_12;
  TNode<BoolT> tmp43;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_6, &phi_bb28_9, &phi_bb28_11, &phi_bb28_12);
    tmp43 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb28_12}, TNode<Smi>{p_high});
    ca_.Branch(tmp43, &block26, std::vector<compiler::Node*>{phi_bb28_6, phi_bb28_9, phi_bb28_11, phi_bb28_12}, &block27, std::vector<compiler::Node*>{phi_bb28_6, phi_bb28_9, phi_bb28_11, phi_bb28_12});
  }

  TNode<Smi> phi_bb26_6;
  TNode<Number> phi_bb26_9;
  TNode<JSAny> phi_bb26_11;
  TNode<Smi> phi_bb26_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<UintPtrT> tmp48;
  TNode<UintPtrT> tmp49;
  TNode<BoolT> tmp50;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_6, &phi_bb26_9, &phi_bb26_11, &phi_bb26_12);
    std::tie(tmp44, tmp45, tmp46) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp2}).Flatten();
    tmp47 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb26_12});
    tmp48 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp49 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp46});
    tmp50 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp48}, TNode<UintPtrT>{tmp49});
    ca_.Branch(tmp50, &block34, std::vector<compiler::Node*>{phi_bb26_6, phi_bb26_9, phi_bb26_11, phi_bb26_12, phi_bb26_12, phi_bb26_12}, &block35, std::vector<compiler::Node*>{phi_bb26_6, phi_bb26_9, phi_bb26_11, phi_bb26_12, phi_bb26_12, phi_bb26_12});
  }

  TNode<Smi> phi_bb34_6;
  TNode<Number> phi_bb34_9;
  TNode<JSAny> phi_bb34_11;
  TNode<Smi> phi_bb34_12;
  TNode<Smi> phi_bb34_17;
  TNode<Smi> phi_bb34_18;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<Union<HeapObject, TaggedIndex>> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<Object> tmp55;
  TNode<JSAny> tmp56;
  TNode<Number> tmp57;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_6, &phi_bb34_9, &phi_bb34_11, &phi_bb34_12, &phi_bb34_17, &phi_bb34_18);
    tmp51 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp47});
    tmp52 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp45}, TNode<IntPtrT>{tmp51});
    std::tie(tmp53, tmp54) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp44}, TNode<IntPtrT>{tmp52}).Flatten();
    tmp55 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp53, tmp54});
    tmp56 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp55});
    tmp57 = Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<JSAny>{tmp56}, TNode<JSAny>{phi_bb34_11});
    ca_.Branch(phi_bb24_10, &block38, std::vector<compiler::Node*>{phi_bb34_6, phi_bb34_11, phi_bb34_12}, &block39, std::vector<compiler::Node*>{phi_bb34_6, phi_bb34_11, phi_bb34_12});
  }

  TNode<Smi> phi_bb35_6;
  TNode<Number> phi_bb35_9;
  TNode<JSAny> phi_bb35_11;
  TNode<Smi> phi_bb35_12;
  TNode<Smi> phi_bb35_17;
  TNode<Smi> phi_bb35_18;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_9, &phi_bb35_11, &phi_bb35_12, &phi_bb35_17, &phi_bb35_18);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb38_6;
  TNode<JSAny> phi_bb38_11;
  TNode<Smi> phi_bb38_12;
  TNode<Number> tmp58;
  TNode<BoolT> tmp59;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_11, &phi_bb38_12);
    tmp58 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp59 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp57}, TNode<Number>{tmp58});
    ca_.Branch(tmp59, &block41, std::vector<compiler::Node*>{phi_bb38_6, phi_bb38_11, phi_bb38_12}, &block42, std::vector<compiler::Node*>{phi_bb38_6, phi_bb38_11, phi_bb38_12});
  }

  TNode<Smi> phi_bb41_6;
  TNode<JSAny> phi_bb41_11;
  TNode<Smi> phi_bb41_12;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_6, &phi_bb41_11, &phi_bb41_12);
    ca_.Goto(&block27, phi_bb41_6, tmp57, phi_bb41_11, phi_bb41_12);
  }

  TNode<Smi> phi_bb42_6;
  TNode<JSAny> phi_bb42_11;
  TNode<Smi> phi_bb42_12;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_11, &phi_bb42_12);
    ca_.Goto(&block40, phi_bb42_6, phi_bb42_11, phi_bb42_12);
  }

  TNode<Smi> phi_bb39_6;
  TNode<JSAny> phi_bb39_11;
  TNode<Smi> phi_bb39_12;
  TNode<Number> tmp60;
  TNode<BoolT> tmp61;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_11, &phi_bb39_12);
    tmp60 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp61 = NumberIsLessThan_0(state_, TNode<Number>{tmp57}, TNode<Number>{tmp60});
    ca_.Branch(tmp61, &block43, std::vector<compiler::Node*>{phi_bb39_6, phi_bb39_11, phi_bb39_12}, &block44, std::vector<compiler::Node*>{phi_bb39_6, phi_bb39_11, phi_bb39_12});
  }

  TNode<Smi> phi_bb43_6;
  TNode<JSAny> phi_bb43_11;
  TNode<Smi> phi_bb43_12;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_11, &phi_bb43_12);
    ca_.Goto(&block27, phi_bb43_6, tmp57, phi_bb43_11, phi_bb43_12);
  }

  TNode<Smi> phi_bb44_6;
  TNode<JSAny> phi_bb44_11;
  TNode<Smi> phi_bb44_12;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_11, &phi_bb44_12);
    ca_.Goto(&block40, phi_bb44_6, phi_bb44_11, phi_bb44_12);
  }

  TNode<Smi> phi_bb40_6;
  TNode<JSAny> phi_bb40_11;
  TNode<Smi> phi_bb40_12;
  TNode<Smi> tmp62;
  TNode<Smi> tmp63;
  TNode<Smi> tmp64;
  TNode<Smi> tmp65;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_11, &phi_bb40_12);
    tmp62 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp63 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb40_6}, TNode<Smi>{tmp62});
    tmp64 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp65 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb40_12}, TNode<Smi>{tmp64});
    ca_.Goto(&block28, tmp63, tmp57, tmp56, tmp65);
  }

  TNode<Smi> phi_bb27_6;
  TNode<Number> phi_bb27_9;
  TNode<JSAny> phi_bb27_11;
  TNode<Smi> phi_bb27_12;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_6, &phi_bb27_9, &phi_bb27_11, &phi_bb27_12);
    ca_.Branch(phi_bb24_10, &block45, std::vector<compiler::Node*>{phi_bb27_6, phi_bb27_9, phi_bb27_11}, &block46, std::vector<compiler::Node*>{phi_bb27_6, phi_bb27_9, phi_bb27_11});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Number> phi_bb45_9;
  TNode<JSAny> phi_bb45_11;
  TNode<Smi> tmp66;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_9, &phi_bb45_11);
    tmp66 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_lowArg}, TNode<Smi>{phi_bb45_6});
    ReverseRange_0(state_, TNode<FixedArray>{tmp2}, TNode<Smi>{p_lowArg}, TNode<Smi>{tmp66});
    ca_.Goto(&block46, phi_bb45_6, phi_bb45_9, phi_bb45_11);
  }

  TNode<Smi> phi_bb46_6;
  TNode<Number> phi_bb46_9;
  TNode<JSAny> phi_bb46_11;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_9, &phi_bb46_11);
    ca_.Goto(&block1, phi_bb46_6);
  }

  TNode<Smi> phi_bb1_4;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    ca_.Goto(&block47, phi_bb1_4);
  }

  TNode<Smi> phi_bb47_4;
    ca_.Bind(&block47, &phi_bb47_4);
  return TNode<Smi>{phi_bb47_4};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=693&c=1
void ReverseRange_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_array, TNode<Smi> p_from, TNode<Smi> p_to) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp1 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_to}, TNode<Smi>{tmp0});
    ca_.Goto(&block4, p_from, tmp1);
  }

  TNode<Smi> phi_bb4_3;
  TNode<Smi> phi_bb4_4;
  TNode<BoolT> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_3, &phi_bb4_4);
    tmp2 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb4_3}, TNode<Smi>{phi_bb4_4});
    ca_.Branch(tmp2, &block2, std::vector<compiler::Node*>{phi_bb4_3, phi_bb4_4}, &block3, std::vector<compiler::Node*>{phi_bb4_3, phi_bb4_4});
  }

  TNode<Smi> phi_bb2_3;
  TNode<Smi> phi_bb2_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<BoolT> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3, &phi_bb2_4);
    std::tie(tmp3, tmp4, tmp5) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_array}).Flatten();
    tmp6 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb2_3});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp9 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp7}, TNode<UintPtrT>{tmp8});
    ca_.Branch(tmp9, &block9, std::vector<compiler::Node*>{phi_bb2_3, phi_bb2_4, phi_bb2_3, phi_bb2_3}, &block10, std::vector<compiler::Node*>{phi_bb2_3, phi_bb2_4, phi_bb2_3, phi_bb2_3});
  }

  TNode<Smi> phi_bb9_3;
  TNode<Smi> phi_bb9_4;
  TNode<Smi> phi_bb9_9;
  TNode<Smi> phi_bb9_10;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Object> tmp14;
  TNode<Union<HeapObject, TaggedIndex>> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<UintPtrT> tmp20;
  TNode<BoolT> tmp21;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3, &phi_bb9_4, &phi_bb9_9, &phi_bb9_10);
    tmp10 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp6});
    tmp11 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp10});
    std::tie(tmp12, tmp13) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp3}, TNode<IntPtrT>{tmp11}).Flatten();
    tmp14 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp12, tmp13});
    std::tie(tmp15, tmp16, tmp17) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_array}).Flatten();
    tmp18 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb9_4});
    tmp19 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp18});
    tmp20 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp17});
    tmp21 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp19}, TNode<UintPtrT>{tmp20});
    ca_.Branch(tmp21, &block17, std::vector<compiler::Node*>{phi_bb9_3, phi_bb9_4, phi_bb9_4, phi_bb9_4}, &block18, std::vector<compiler::Node*>{phi_bb9_3, phi_bb9_4, phi_bb9_4, phi_bb9_4});
  }

  TNode<Smi> phi_bb10_3;
  TNode<Smi> phi_bb10_4;
  TNode<Smi> phi_bb10_9;
  TNode<Smi> phi_bb10_10;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3, &phi_bb10_4, &phi_bb10_9, &phi_bb10_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb17_3;
  TNode<Smi> phi_bb17_4;
  TNode<Smi> phi_bb17_10;
  TNode<Smi> phi_bb17_11;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Union<HeapObject, TaggedIndex>> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Object> tmp26;
  TNode<Union<HeapObject, TaggedIndex>> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Smi> tmp30;
  TNode<Smi> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<UintPtrT> tmp34;
  TNode<BoolT> tmp35;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_3, &phi_bb17_4, &phi_bb17_10, &phi_bb17_11);
    tmp22 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp18});
    tmp23 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp22});
    std::tie(tmp24, tmp25) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp15}, TNode<IntPtrT>{tmp23}).Flatten();
    tmp26 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp24, tmp25});
    std::tie(tmp27, tmp28, tmp29) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_array}).Flatten();
    tmp30 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp31 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb17_3}, TNode<Smi>{tmp30});
    tmp32 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb17_3});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp34 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp29});
    tmp35 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp33}, TNode<UintPtrT>{tmp34});
    ca_.Branch(tmp35, &block25, std::vector<compiler::Node*>{phi_bb17_4, phi_bb17_3, phi_bb17_3}, &block26, std::vector<compiler::Node*>{phi_bb17_4, phi_bb17_3, phi_bb17_3});
  }

  TNode<Smi> phi_bb18_3;
  TNode<Smi> phi_bb18_4;
  TNode<Smi> phi_bb18_10;
  TNode<Smi> phi_bb18_11;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_3, &phi_bb18_4, &phi_bb18_10, &phi_bb18_11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb25_4;
  TNode<Smi> phi_bb25_11;
  TNode<Smi> phi_bb25_12;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Union<HeapObject, TaggedIndex>> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Union<HeapObject, TaggedIndex>> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<Smi> tmp43;
  TNode<Smi> tmp44;
  TNode<IntPtrT> tmp45;
  TNode<UintPtrT> tmp46;
  TNode<UintPtrT> tmp47;
  TNode<BoolT> tmp48;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_4, &phi_bb25_11, &phi_bb25_12);
    tmp36 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp32});
    tmp37 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp36});
    std::tie(tmp38, tmp39) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp27}, TNode<IntPtrT>{tmp37}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp38, tmp39}, tmp26);
    std::tie(tmp40, tmp41, tmp42) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_array}).Flatten();
    tmp43 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp44 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb25_4}, TNode<Smi>{tmp43});
    tmp45 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb25_4});
    tmp46 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp45});
    tmp47 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp42});
    tmp48 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp46}, TNode<UintPtrT>{tmp47});
    ca_.Branch(tmp48, &block33, std::vector<compiler::Node*>{phi_bb25_4, phi_bb25_4}, &block34, std::vector<compiler::Node*>{phi_bb25_4, phi_bb25_4});
  }

  TNode<Smi> phi_bb26_4;
  TNode<Smi> phi_bb26_11;
  TNode<Smi> phi_bb26_12;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_4, &phi_bb26_11, &phi_bb26_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb33_11;
  TNode<Smi> phi_bb33_12;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<Union<HeapObject, TaggedIndex>> tmp51;
  TNode<IntPtrT> tmp52;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_11, &phi_bb33_12);
    tmp49 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp45});
    tmp50 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp41}, TNode<IntPtrT>{tmp49});
    std::tie(tmp51, tmp52) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp40}, TNode<IntPtrT>{tmp50}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp51, tmp52}, tmp14);
    ca_.Goto(&block4, tmp31, tmp44);
  }

  TNode<Smi> phi_bb34_11;
  TNode<Smi> phi_bb34_12;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_11, &phi_bb34_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb3_3;
  TNode<Smi> phi_bb3_4;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_3, &phi_bb3_4);
    ca_.Goto(&block37);
  }

    ca_.Bind(&block37);
}

TF_BUILTIN(MergeAt, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kI);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = GetPendingRunsSize_0(state_, TNode<SortState>{parameter1});
    tmp1 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp2 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp0}, TNode<Smi>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 713});
      CodeStubAssembler(state_).FailAssert("Torque assert 'stackSize >= 2' failed", pos_stack);
    }
  }

  TNode<Smi> tmp3;
  TNode<BoolT> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp3});
    ca_.Branch(tmp4, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 714});
      CodeStubAssembler(state_).FailAssert("Torque assert 'i >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp5;
  TNode<Smi> tmp6;
  TNode<BoolT> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp6 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp0}, TNode<Smi>{tmp5});
    tmp7 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp6});
    ca_.Branch(tmp7, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp8;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block9, tmp8);
  }

  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<BoolT> tmp11;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp9 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x3ull));
    tmp10 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp0}, TNode<Smi>{tmp9});
    tmp11 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp10});
    ca_.Goto(&block9, tmp11);
  }

  TNode<BoolT> phi_bb9_5;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5);
    ca_.Branch(phi_bb9_5, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 715});
      CodeStubAssembler(state_).FailAssert("Torque assert 'i == stackSize - 2 || i == stackSize - 3' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp12;
  TNode<FixedArray> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<FixedArray> tmp15;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<BoolT> tmp25;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp13 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp12});
    tmp14 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp15 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{parameter1, tmp14});
    tmp16 = GetPendingRunBase_0(state_, TNode<FixedArray>{tmp15}, TNode<Smi>{parameter2});
    tmp17 = GetPendingRunLength_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp15}, TNode<Smi>{parameter2});
    tmp18 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp19 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp18});
    tmp20 = GetPendingRunBase_0(state_, TNode<FixedArray>{tmp15}, TNode<Smi>{tmp19});
    tmp21 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp22 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp21});
    tmp23 = GetPendingRunLength_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp15}, TNode<Smi>{tmp22});
    tmp24 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp25 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp17}, TNode<Smi>{tmp24});
    ca_.Branch(tmp25, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp26;
  TNode<BoolT> tmp27;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp26 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp27 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp23}, TNode<Smi>{tmp26});
    ca_.Goto(&block14, tmp27);
  }

  TNode<BoolT> tmp28;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp28 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block14, tmp28);
  }

  TNode<BoolT> phi_bb14_11;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_11);
    ca_.Branch(phi_bb14_11, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 724});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA > 0 && lengthB > 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp29;
  TNode<BoolT> tmp30;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp29 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp16}, TNode<Smi>{tmp17});
    tmp30 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp29}, TNode<Smi>{tmp20});
    ca_.Branch(tmp30, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 725});
      CodeStubAssembler(state_).FailAssert("Torque assert 'baseA + lengthA == baseB' failed", pos_stack);
    }
  }

  TNode<Smi> tmp31;
  TNode<Smi> tmp32;
  TNode<Smi> tmp33;
  TNode<BoolT> tmp34;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp31 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp17}, TNode<Smi>{tmp23});
    SetPendingRunLength_0(state_, TNode<FixedArray>{tmp15}, TNode<Smi>{parameter2}, TNode<Smi>{tmp31});
    tmp32 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x3ull));
    tmp33 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp0}, TNode<Smi>{tmp32});
    tmp34 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{parameter2}, TNode<Smi>{tmp33});
    ca_.Branch(tmp34, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp35;
  TNode<Smi> tmp36;
  TNode<Smi> tmp37;
  TNode<Smi> tmp38;
  TNode<Smi> tmp39;
  TNode<Smi> tmp40;
  TNode<Smi> tmp41;
  TNode<Smi> tmp42;
  TNode<Smi> tmp43;
  TNode<Smi> tmp44;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp35 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp36 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp35});
    tmp37 = GetPendingRunBase_0(state_, TNode<FixedArray>{tmp15}, TNode<Smi>{tmp36});
    tmp38 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp39 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp38});
    tmp40 = GetPendingRunLength_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp15}, TNode<Smi>{tmp39});
    tmp41 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp42 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp41});
    SetPendingRunBase_0(state_, TNode<FixedArray>{tmp15}, TNode<Smi>{tmp42}, TNode<Smi>{tmp37});
    tmp43 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp44 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter2}, TNode<Smi>{tmp43});
    SetPendingRunLength_0(state_, TNode<FixedArray>{tmp15}, TNode<Smi>{tmp44}, TNode<Smi>{tmp40});
    ca_.Goto(&block18);
  }

  TNode<IntPtrT> tmp45;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  TNode<Union<HeapObject, TaggedIndex>> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<UintPtrT> tmp52;
  TNode<UintPtrT> tmp53;
  TNode<BoolT> tmp54;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp45 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp46 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp47 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp0}, TNode<Smi>{tmp46});
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{parameter1, tmp45}, tmp47);
    std::tie(tmp48, tmp49, tmp50) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp51 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp20});
    tmp52 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp51});
    tmp53 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp50});
    tmp54 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp52}, TNode<UintPtrT>{tmp53});
    ca_.Branch(tmp54, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<Union<HeapObject, TaggedIndex>> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<Object> tmp59;
  TNode<JSAny> tmp60;
  TNode<Smi> tmp61;
  TNode<Smi> tmp62;
  TNode<Smi> tmp63;
  TNode<BoolT> tmp64;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp55 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp51});
    tmp56 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp55});
    std::tie(tmp57, tmp58) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp48}, TNode<IntPtrT>{tmp56}).Flatten();
    tmp59 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp57, tmp58});
    tmp60 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp59});
    tmp61 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp62 = ca_.CallBuiltin<Smi>(Builtin::kGallopRight, parameter0, parameter1, tmp13, tmp60, tmp16, tmp17, tmp61);
    tmp63 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp64 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp62}, TNode<Smi>{tmp63});
    ca_.Branch(tmp64, &block27, std::vector<compiler::Node*>{}, &block28, std::vector<compiler::Node*>{});
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 743});
      CodeStubAssembler(state_).FailAssert("Torque assert 'k >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp65;
  TNode<Smi> tmp66;
  TNode<Smi> tmp67;
  TNode<BoolT> tmp68;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp65 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp16}, TNode<Smi>{tmp62});
    tmp66 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp17}, TNode<Smi>{tmp62});
    tmp67 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp68 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp66}, TNode<Smi>{tmp67});
    ca_.Branch(tmp68, &block29, std::vector<compiler::Node*>{}, &block30, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp69;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp69 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp69);
  }

  TNode<Smi> tmp70;
  TNode<BoolT> tmp71;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp70 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp71 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp66}, TNode<Smi>{tmp70});
    ca_.Branch(tmp71, &block31, std::vector<compiler::Node*>{}, &block32, std::vector<compiler::Node*>{});
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 748});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA > 0' failed", pos_stack);
    }
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<IntPtrT> tmp74;
  TNode<Smi> tmp75;
  TNode<Smi> tmp76;
  TNode<Smi> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<UintPtrT> tmp79;
  TNode<UintPtrT> tmp80;
  TNode<BoolT> tmp81;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    std::tie(tmp72, tmp73, tmp74) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp75 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp65}, TNode<Smi>{tmp66});
    tmp76 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp77 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp75}, TNode<Smi>{tmp76});
    tmp78 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp77});
    tmp79 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp78});
    tmp80 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp74});
    tmp81 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp79}, TNode<UintPtrT>{tmp80});
    ca_.Branch(tmp81, &block37, std::vector<compiler::Node*>{}, &block38, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<Union<HeapObject, TaggedIndex>> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<Object> tmp86;
  TNode<JSAny> tmp87;
  TNode<Smi> tmp88;
  TNode<Smi> tmp89;
  TNode<Smi> tmp90;
  TNode<Smi> tmp91;
  TNode<BoolT> tmp92;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp82 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp78});
    tmp83 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp73}, TNode<IntPtrT>{tmp82});
    std::tie(tmp84, tmp85) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp72}, TNode<IntPtrT>{tmp83}).Flatten();
    tmp86 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp84, tmp85});
    tmp87 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp86});
    tmp88 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp89 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp23}, TNode<Smi>{tmp88});
    tmp90 = ca_.CallBuiltin<Smi>(Builtin::kGallopLeft, parameter0, parameter1, tmp13, tmp87, tmp20, tmp23, tmp89);
    tmp91 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp92 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp90}, TNode<Smi>{tmp91});
    ca_.Branch(tmp92, &block41, std::vector<compiler::Node*>{}, &block42, std::vector<compiler::Node*>{});
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block42.is_used()) {
    ca_.Bind(&block42);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 754});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthB >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp93;
  TNode<BoolT> tmp94;
  if (block41.is_used()) {
    ca_.Bind(&block41);
    tmp93 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp94 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp90}, TNode<Smi>{tmp93});
    ca_.Branch(tmp94, &block43, std::vector<compiler::Node*>{}, &block44, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp95;
  if (block43.is_used()) {
    ca_.Bind(&block43);
    tmp95 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp95);
  }

  TNode<BoolT> tmp96;
  if (block44.is_used()) {
    ca_.Bind(&block44);
    tmp96 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp66}, TNode<Smi>{tmp90});
    ca_.Branch(tmp96, &block45, std::vector<compiler::Node*>{}, &block46, std::vector<compiler::Node*>{});
  }

  if (block45.is_used()) {
    ca_.Bind(&block45);
    MergeLow_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp65}, TNode<Smi>{tmp66}, TNode<Smi>{tmp20}, TNode<Smi>{tmp90});
    ca_.Goto(&block47);
  }

  if (block46.is_used()) {
    ca_.Bind(&block46);
    MergeHigh_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp65}, TNode<Smi>{tmp66}, TNode<Smi>{tmp20}, TNode<Smi>{tmp90});
    ca_.Goto(&block47);
  }

  TNode<Smi> tmp97;
  if (block47.is_used()) {
    ca_.Bind(&block47);
    tmp97 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp97);
  }
}

TF_BUILTIN(GallopLeft, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<FixedArray> parameter2 = UncheckedParameter<FixedArray>(Descriptor::kArray);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kKey);
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedParameter<Smi>(Descriptor::kBase);
  USE(parameter4);
  TNode<Smi> parameter5 = UncheckedParameter<Smi>(Descriptor::kLength);
  USE(parameter5);
  TNode<Smi> parameter6 = UncheckedParameter<Smi>(Descriptor::kHint);
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number, BoolT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number, BoolT> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block59(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block81(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number, BoolT> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block83(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{parameter5}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{parameter4}, TNode<Smi>{tmp2});
    ca_.Goto(&block5, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block5, tmp4);
  }

  TNode<BoolT> phi_bb5_8;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_8);
    ca_.Branch(phi_bb5_8, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 788});
      CodeStubAssembler(state_).FailAssert("Torque assert 'length > 0 && base >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp5;
  TNode<BoolT> tmp6;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp5 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp5}, TNode<Smi>{parameter6});
    ca_.Branch(tmp6, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp7;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp7 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{parameter6}, TNode<Smi>{parameter5});
    ca_.Goto(&block10, tmp7);
  }

  TNode<BoolT> tmp8;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block10, tmp8);
  }

  TNode<BoolT> phi_bb10_8;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_8);
    ca_.Branch(phi_bb10_8, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 789});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 <= hint && hint < length' failed", pos_stack);
    }
  }

  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Smi> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp9 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp10 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    std::tie(tmp11, tmp12, tmp13) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp14 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp14});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp13});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<Object> tmp23;
  TNode<JSAny> tmp24;
  TNode<Number> tmp25;
  TNode<Number> tmp26;
  TNode<BoolT> tmp27;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp19 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp15});
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp19});
    std::tie(tmp21, tmp22) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp11}, TNode<IntPtrT>{tmp20}).Flatten();
    tmp23 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp21, tmp22});
    tmp24 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp23});
    tmp25 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{tmp24}, TNode<JSAny>{parameter3});
    tmp26 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp27 = NumberIsLessThan_0(state_, TNode<Number>{tmp25}, TNode<Number>{tmp26});
    ca_.Branch(tmp27, &block19, std::vector<compiler::Node*>{}, &block20, std::vector<compiler::Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp28;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp28 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter5}, TNode<Smi>{parameter6});
    ca_.Goto(&block24, tmp9, tmp10, tmp25);
  }

  TNode<Smi> phi_bb24_7;
  TNode<Smi> phi_bb24_8;
  TNode<Number> phi_bb24_10;
  TNode<BoolT> tmp29;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_7, &phi_bb24_8, &phi_bb24_10);
    tmp29 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb24_8}, TNode<Smi>{tmp28});
    ca_.Branch(tmp29, &block22, std::vector<compiler::Node*>{phi_bb24_7, phi_bb24_8, phi_bb24_10}, &block23, std::vector<compiler::Node*>{phi_bb24_7, phi_bb24_8, phi_bb24_10});
  }

  TNode<Smi> phi_bb22_7;
  TNode<Smi> phi_bb22_8;
  TNode<Number> phi_bb22_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<Smi> tmp33;
  TNode<Smi> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<UintPtrT> tmp36;
  TNode<UintPtrT> tmp37;
  TNode<BoolT> tmp38;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7, &phi_bb22_8, &phi_bb22_10);
    std::tie(tmp30, tmp31, tmp32) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp33 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp34 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp33}, TNode<Smi>{phi_bb22_8});
    tmp35 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp34});
    tmp36 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp35});
    tmp37 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp32});
    tmp38 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp36}, TNode<UintPtrT>{tmp37});
    ca_.Branch(tmp38, &block29, std::vector<compiler::Node*>{phi_bb22_7, phi_bb22_8, phi_bb22_10}, &block30, std::vector<compiler::Node*>{phi_bb22_7, phi_bb22_8, phi_bb22_10});
  }

  TNode<Smi> phi_bb29_7;
  TNode<Smi> phi_bb29_8;
  TNode<Number> phi_bb29_10;
  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Union<HeapObject, TaggedIndex>> tmp41;
  TNode<IntPtrT> tmp42;
  TNode<Object> tmp43;
  TNode<JSAny> tmp44;
  TNode<Number> tmp45;
  TNode<Number> tmp46;
  TNode<BoolT> tmp47;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_7, &phi_bb29_8, &phi_bb29_10);
    tmp39 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp35});
    tmp40 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp31}, TNode<IntPtrT>{tmp39});
    std::tie(tmp41, tmp42) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp30}, TNode<IntPtrT>{tmp40}).Flatten();
    tmp43 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp41, tmp42});
    tmp44 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp43});
    tmp45 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{tmp44}, TNode<JSAny>{parameter3});
    tmp46 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp47 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp45}, TNode<Number>{tmp46});
    ca_.Branch(tmp47, &block33, std::vector<compiler::Node*>{phi_bb29_7, phi_bb29_8}, &block34, std::vector<compiler::Node*>{phi_bb29_7, phi_bb29_8});
  }

  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_8;
  TNode<Number> phi_bb30_10;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_7, &phi_bb30_8, &phi_bb30_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_8;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_7, &phi_bb33_8);
    ca_.Goto(&block23, phi_bb33_7, phi_bb33_8, tmp45);
  }

  TNode<Smi> phi_bb34_7;
  TNode<Smi> phi_bb34_8;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  TNode<Smi> tmp50;
  TNode<Smi> tmp51;
  TNode<BoolT> tmp52;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_7, &phi_bb34_8);
    tmp48 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb34_8}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp49 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp50 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp48}, TNode<Smi>{tmp49});
    tmp51 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp52 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp50}, TNode<Smi>{tmp51});
    ca_.Branch(tmp52, &block35, std::vector<compiler::Node*>{phi_bb34_8}, &block36, std::vector<compiler::Node*>{phi_bb34_8, tmp50});
  }

  TNode<Smi> phi_bb35_7;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_7);
    ca_.Goto(&block36, phi_bb35_7, tmp28);
  }

  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_8;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_7, &phi_bb36_8);
    ca_.Goto(&block24, phi_bb36_7, phi_bb36_8, tmp45);
  }

  TNode<Smi> phi_bb23_7;
  TNode<Smi> phi_bb23_8;
  TNode<Number> phi_bb23_10;
  TNode<BoolT> tmp53;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_7, &phi_bb23_8, &phi_bb23_10);
    tmp53 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb23_8}, TNode<Smi>{tmp28});
    ca_.Branch(tmp53, &block37, std::vector<compiler::Node*>{phi_bb23_7, phi_bb23_8, phi_bb23_10}, &block38, std::vector<compiler::Node*>{phi_bb23_7, phi_bb23_8, phi_bb23_10});
  }

  TNode<Smi> phi_bb37_7;
  TNode<Smi> phi_bb37_8;
  TNode<Number> phi_bb37_10;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_7, &phi_bb37_8, &phi_bb37_10);
    ca_.Goto(&block38, phi_bb37_7, tmp28, phi_bb37_10);
  }

  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_8;
  TNode<Number> phi_bb38_10;
  TNode<Smi> tmp54;
  TNode<Smi> tmp55;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_7, &phi_bb38_8, &phi_bb38_10);
    tmp54 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb38_7}, TNode<Smi>{parameter6});
    tmp55 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb38_8}, TNode<Smi>{parameter6});
    ca_.Goto(&block21, tmp54, tmp55, phi_bb38_10);
  }

  TNode<Number> tmp56;
  TNode<BoolT> tmp57;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp56 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp57 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp25}, TNode<Number>{tmp56});
    ca_.Branch(tmp57, &block39, std::vector<compiler::Node*>{}, &block40, std::vector<compiler::Node*>{});
  }

  if (block40.is_used()) {
    ca_.Bind(&block40);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 826});
      CodeStubAssembler(state_).FailAssert("Torque assert 'order >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp58;
  TNode<Smi> tmp59;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp58 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp59 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter6}, TNode<Smi>{tmp58});
    ca_.Goto(&block43, tmp9, tmp10, tmp25);
  }

  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_8;
  TNode<Number> phi_bb43_10;
  TNode<BoolT> tmp60;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_7, &phi_bb43_8, &phi_bb43_10);
    tmp60 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb43_8}, TNode<Smi>{tmp59});
    ca_.Branch(tmp60, &block41, std::vector<compiler::Node*>{phi_bb43_7, phi_bb43_8, phi_bb43_10}, &block42, std::vector<compiler::Node*>{phi_bb43_7, phi_bb43_8, phi_bb43_10});
  }

  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_8;
  TNode<Number> phi_bb41_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<Smi> tmp64;
  TNode<Smi> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<UintPtrT> tmp67;
  TNode<UintPtrT> tmp68;
  TNode<BoolT> tmp69;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_7, &phi_bb41_8, &phi_bb41_10);
    std::tie(tmp61, tmp62, tmp63) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp64 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp65 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp64}, TNode<Smi>{phi_bb41_8});
    tmp66 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp65});
    tmp67 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp66});
    tmp68 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp63});
    tmp69 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp67}, TNode<UintPtrT>{tmp68});
    ca_.Branch(tmp69, &block48, std::vector<compiler::Node*>{phi_bb41_7, phi_bb41_8, phi_bb41_10}, &block49, std::vector<compiler::Node*>{phi_bb41_7, phi_bb41_8, phi_bb41_10});
  }

  TNode<Smi> phi_bb48_7;
  TNode<Smi> phi_bb48_8;
  TNode<Number> phi_bb48_10;
  TNode<IntPtrT> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Union<HeapObject, TaggedIndex>> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<Object> tmp74;
  TNode<JSAny> tmp75;
  TNode<Number> tmp76;
  TNode<Number> tmp77;
  TNode<BoolT> tmp78;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_7, &phi_bb48_8, &phi_bb48_10);
    tmp70 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp66});
    tmp71 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp62}, TNode<IntPtrT>{tmp70});
    std::tie(tmp72, tmp73) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp61}, TNode<IntPtrT>{tmp71}).Flatten();
    tmp74 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp72, tmp73});
    tmp75 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp74});
    tmp76 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{tmp75}, TNode<JSAny>{parameter3});
    tmp77 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp78 = NumberIsLessThan_0(state_, TNode<Number>{tmp76}, TNode<Number>{tmp77});
    ca_.Branch(tmp78, &block52, std::vector<compiler::Node*>{phi_bb48_7, phi_bb48_8}, &block53, std::vector<compiler::Node*>{phi_bb48_7, phi_bb48_8});
  }

  TNode<Smi> phi_bb49_7;
  TNode<Smi> phi_bb49_8;
  TNode<Number> phi_bb49_10;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_7, &phi_bb49_8, &phi_bb49_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb52_7;
  TNode<Smi> phi_bb52_8;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_7, &phi_bb52_8);
    ca_.Goto(&block42, phi_bb52_7, phi_bb52_8, tmp76);
  }

  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_8;
  TNode<Smi> tmp79;
  TNode<Smi> tmp80;
  TNode<Smi> tmp81;
  TNode<Smi> tmp82;
  TNode<BoolT> tmp83;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_7, &phi_bb53_8);
    tmp79 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb53_8}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp80 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp81 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp79}, TNode<Smi>{tmp80});
    tmp82 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp83 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp81}, TNode<Smi>{tmp82});
    ca_.Branch(tmp83, &block54, std::vector<compiler::Node*>{phi_bb53_8}, &block55, std::vector<compiler::Node*>{phi_bb53_8, tmp81});
  }

  TNode<Smi> phi_bb54_7;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_7);
    ca_.Goto(&block55, phi_bb54_7, tmp59);
  }

  TNode<Smi> phi_bb55_7;
  TNode<Smi> phi_bb55_8;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_7, &phi_bb55_8);
    ca_.Goto(&block43, phi_bb55_7, phi_bb55_8, tmp76);
  }

  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_8;
  TNode<Number> phi_bb42_10;
  TNode<BoolT> tmp84;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_7, &phi_bb42_8, &phi_bb42_10);
    tmp84 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb42_8}, TNode<Smi>{tmp59});
    ca_.Branch(tmp84, &block56, std::vector<compiler::Node*>{phi_bb42_7, phi_bb42_8, phi_bb42_10}, &block57, std::vector<compiler::Node*>{phi_bb42_7, phi_bb42_8, phi_bb42_10});
  }

  TNode<Smi> phi_bb56_7;
  TNode<Smi> phi_bb56_8;
  TNode<Number> phi_bb56_10;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_7, &phi_bb56_8, &phi_bb56_10);
    ca_.Goto(&block57, phi_bb56_7, tmp59, phi_bb56_10);
  }

  TNode<Smi> phi_bb57_7;
  TNode<Smi> phi_bb57_8;
  TNode<Number> phi_bb57_10;
  TNode<Smi> tmp85;
  TNode<Smi> tmp86;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_7, &phi_bb57_8, &phi_bb57_10);
    tmp85 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb57_8});
    tmp86 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb57_7});
    ca_.Goto(&block21, tmp85, tmp86, phi_bb57_10);
  }

  TNode<Smi> phi_bb21_7;
  TNode<Smi> phi_bb21_8;
  TNode<Number> phi_bb21_10;
  TNode<Smi> tmp87;
  TNode<BoolT> tmp88;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7, &phi_bb21_8, &phi_bb21_10);
    tmp87 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp88 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp87}, TNode<Smi>{phi_bb21_7});
    ca_.Branch(tmp88, &block60, std::vector<compiler::Node*>{phi_bb21_7, phi_bb21_8, phi_bb21_10}, &block61, std::vector<compiler::Node*>{phi_bb21_7, phi_bb21_8, phi_bb21_10});
  }

  TNode<Smi> phi_bb60_7;
  TNode<Smi> phi_bb60_8;
  TNode<Number> phi_bb60_10;
  TNode<BoolT> tmp89;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_7, &phi_bb60_8, &phi_bb60_10);
    tmp89 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb60_7}, TNode<Smi>{phi_bb60_8});
    ca_.Goto(&block62, phi_bb60_7, phi_bb60_8, phi_bb60_10, tmp89);
  }

  TNode<Smi> phi_bb61_7;
  TNode<Smi> phi_bb61_8;
  TNode<Number> phi_bb61_10;
  TNode<BoolT> tmp90;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_7, &phi_bb61_8, &phi_bb61_10);
    tmp90 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block62, phi_bb61_7, phi_bb61_8, phi_bb61_10, tmp90);
  }

  TNode<Smi> phi_bb62_7;
  TNode<Smi> phi_bb62_8;
  TNode<Number> phi_bb62_10;
  TNode<BoolT> phi_bb62_12;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_7, &phi_bb62_8, &phi_bb62_10, &phi_bb62_12);
    ca_.Branch(phi_bb62_12, &block63, std::vector<compiler::Node*>{phi_bb62_7, phi_bb62_8, phi_bb62_10}, &block64, std::vector<compiler::Node*>{phi_bb62_7, phi_bb62_8, phi_bb62_10});
  }

  TNode<Smi> phi_bb63_7;
  TNode<Smi> phi_bb63_8;
  TNode<Number> phi_bb63_10;
  TNode<BoolT> tmp91;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_7, &phi_bb63_8, &phi_bb63_10);
    tmp91 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{phi_bb63_8}, TNode<Smi>{parameter5});
    ca_.Goto(&block65, phi_bb63_7, phi_bb63_8, phi_bb63_10, tmp91);
  }

  TNode<Smi> phi_bb64_7;
  TNode<Smi> phi_bb64_8;
  TNode<Number> phi_bb64_10;
  TNode<BoolT> tmp92;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_7, &phi_bb64_8, &phi_bb64_10);
    tmp92 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block65, phi_bb64_7, phi_bb64_8, phi_bb64_10, tmp92);
  }

  TNode<Smi> phi_bb65_7;
  TNode<Smi> phi_bb65_8;
  TNode<Number> phi_bb65_10;
  TNode<BoolT> phi_bb65_12;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_7, &phi_bb65_8, &phi_bb65_10, &phi_bb65_12);
    ca_.Branch(phi_bb65_12, &block58, std::vector<compiler::Node*>{phi_bb65_7, phi_bb65_8, phi_bb65_10}, &block59, std::vector<compiler::Node*>{phi_bb65_7, phi_bb65_8, phi_bb65_10});
  }

  TNode<Smi> phi_bb59_7;
  TNode<Smi> phi_bb59_8;
  TNode<Number> phi_bb59_10;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_7, &phi_bb59_8, &phi_bb59_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 852});
      CodeStubAssembler(state_).FailAssert("Torque assert '-1 <= lastOfs && lastOfs < offset && offset <= length' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb58_7;
  TNode<Smi> phi_bb58_8;
  TNode<Number> phi_bb58_10;
  TNode<Smi> tmp93;
  TNode<Smi> tmp94;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_7, &phi_bb58_8, &phi_bb58_10);
    tmp93 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp94 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb58_7}, TNode<Smi>{tmp93});
    ca_.Goto(&block68, tmp94, phi_bb58_8, phi_bb58_10);
  }

  TNode<Smi> phi_bb68_7;
  TNode<Smi> phi_bb68_8;
  TNode<Number> phi_bb68_10;
  TNode<BoolT> tmp95;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_7, &phi_bb68_8, &phi_bb68_10);
    tmp95 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb68_7}, TNode<Smi>{phi_bb68_8});
    ca_.Branch(tmp95, &block66, std::vector<compiler::Node*>{phi_bb68_7, phi_bb68_8, phi_bb68_10}, &block67, std::vector<compiler::Node*>{phi_bb68_7, phi_bb68_8, phi_bb68_10});
  }

  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_8;
  TNode<Number> phi_bb66_10;
  TNode<Smi> tmp96;
  TNode<Smi> tmp97;
  TNode<Smi> tmp98;
  TNode<Union<HeapObject, TaggedIndex>> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<Smi> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<UintPtrT> tmp104;
  TNode<UintPtrT> tmp105;
  TNode<BoolT> tmp106;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_7, &phi_bb66_8, &phi_bb66_10);
    tmp96 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb66_8}, TNode<Smi>{phi_bb66_7});
    tmp97 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{tmp96}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp98 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb66_7}, TNode<Smi>{tmp97});
    std::tie(tmp99, tmp100, tmp101) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp102 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{tmp98});
    tmp103 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp102});
    tmp104 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp103});
    tmp105 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp101});
    tmp106 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp104}, TNode<UintPtrT>{tmp105});
    ca_.Branch(tmp106, &block73, std::vector<compiler::Node*>{phi_bb66_7, phi_bb66_8, phi_bb66_10}, &block74, std::vector<compiler::Node*>{phi_bb66_7, phi_bb66_8, phi_bb66_10});
  }

  TNode<Smi> phi_bb73_7;
  TNode<Smi> phi_bb73_8;
  TNode<Number> phi_bb73_10;
  TNode<IntPtrT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<Union<HeapObject, TaggedIndex>> tmp109;
  TNode<IntPtrT> tmp110;
  TNode<Object> tmp111;
  TNode<JSAny> tmp112;
  TNode<Number> tmp113;
  TNode<Number> tmp114;
  TNode<BoolT> tmp115;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_7, &phi_bb73_8, &phi_bb73_10);
    tmp107 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp103});
    tmp108 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp100}, TNode<IntPtrT>{tmp107});
    std::tie(tmp109, tmp110) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp99}, TNode<IntPtrT>{tmp108}).Flatten();
    tmp111 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp109, tmp110});
    tmp112 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp111});
    tmp113 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{tmp112}, TNode<JSAny>{parameter3});
    tmp114 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp115 = NumberIsLessThan_0(state_, TNode<Number>{tmp113}, TNode<Number>{tmp114});
    ca_.Branch(tmp115, &block77, std::vector<compiler::Node*>{phi_bb73_7, phi_bb73_8}, &block78, std::vector<compiler::Node*>{phi_bb73_7, phi_bb73_8});
  }

  TNode<Smi> phi_bb74_7;
  TNode<Smi> phi_bb74_8;
  TNode<Number> phi_bb74_10;
  if (block74.is_used()) {
    ca_.Bind(&block74, &phi_bb74_7, &phi_bb74_8, &phi_bb74_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb77_7;
  TNode<Smi> phi_bb77_8;
  TNode<Smi> tmp116;
  TNode<Smi> tmp117;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_7, &phi_bb77_8);
    tmp116 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp117 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp98}, TNode<Smi>{tmp116});
    ca_.Goto(&block79, tmp117, phi_bb77_8);
  }

  TNode<Smi> phi_bb78_7;
  TNode<Smi> phi_bb78_8;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_7, &phi_bb78_8);
    ca_.Goto(&block79, phi_bb78_7, tmp98);
  }

  TNode<Smi> phi_bb79_7;
  TNode<Smi> phi_bb79_8;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_7, &phi_bb79_8);
    ca_.Goto(&block68, phi_bb79_7, phi_bb79_8, tmp113);
  }

  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_8;
  TNode<Number> phi_bb67_10;
  TNode<BoolT> tmp118;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_7, &phi_bb67_8, &phi_bb67_10);
    tmp118 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb67_7}, TNode<Smi>{phi_bb67_8});
    ca_.Branch(tmp118, &block80, std::vector<compiler::Node*>{phi_bb67_7, phi_bb67_8, phi_bb67_10}, &block81, std::vector<compiler::Node*>{phi_bb67_7, phi_bb67_8, phi_bb67_10});
  }

  TNode<Smi> phi_bb81_7;
  TNode<Smi> phi_bb81_8;
  TNode<Number> phi_bb81_10;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_7, &phi_bb81_8, &phi_bb81_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 871});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lastOfs == offset' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb80_7;
  TNode<Smi> phi_bb80_8;
  TNode<Number> phi_bb80_10;
  TNode<Smi> tmp119;
  TNode<BoolT> tmp120;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_7, &phi_bb80_8, &phi_bb80_10);
    tmp119 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp120 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp119}, TNode<Smi>{phi_bb80_8});
    ca_.Branch(tmp120, &block84, std::vector<compiler::Node*>{phi_bb80_7, phi_bb80_8, phi_bb80_10}, &block85, std::vector<compiler::Node*>{phi_bb80_7, phi_bb80_8, phi_bb80_10});
  }

  TNode<Smi> phi_bb84_7;
  TNode<Smi> phi_bb84_8;
  TNode<Number> phi_bb84_10;
  TNode<BoolT> tmp121;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_7, &phi_bb84_8, &phi_bb84_10);
    tmp121 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{phi_bb84_8}, TNode<Smi>{parameter5});
    ca_.Goto(&block86, phi_bb84_7, phi_bb84_8, phi_bb84_10, tmp121);
  }

  TNode<Smi> phi_bb85_7;
  TNode<Smi> phi_bb85_8;
  TNode<Number> phi_bb85_10;
  TNode<BoolT> tmp122;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_7, &phi_bb85_8, &phi_bb85_10);
    tmp122 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block86, phi_bb85_7, phi_bb85_8, phi_bb85_10, tmp122);
  }

  TNode<Smi> phi_bb86_7;
  TNode<Smi> phi_bb86_8;
  TNode<Number> phi_bb86_10;
  TNode<BoolT> phi_bb86_12;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_7, &phi_bb86_8, &phi_bb86_10, &phi_bb86_12);
    ca_.Branch(phi_bb86_12, &block82, std::vector<compiler::Node*>{phi_bb86_7, phi_bb86_8, phi_bb86_10}, &block83, std::vector<compiler::Node*>{phi_bb86_7, phi_bb86_8, phi_bb86_10});
  }

  TNode<Smi> phi_bb83_7;
  TNode<Smi> phi_bb83_8;
  TNode<Number> phi_bb83_10;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_7, &phi_bb83_8, &phi_bb83_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 872});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 <= offset && offset <= length' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb82_7;
  TNode<Smi> phi_bb82_8;
  TNode<Number> phi_bb82_10;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_7, &phi_bb82_8, &phi_bb82_10);
    CodeStubAssembler(state_).Return(phi_bb82_8);
  }
}

TF_BUILTIN(GallopRight, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<FixedArray> parameter2 = UncheckedParameter<FixedArray>(Descriptor::kArray);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kKey);
  USE(parameter3);
  TNode<Smi> parameter4 = UncheckedParameter<Smi>(Descriptor::kBase);
  USE(parameter4);
  TNode<Smi> parameter5 = UncheckedParameter<Smi>(Descriptor::kLength);
  USE(parameter5);
  TNode<Smi> parameter6 = UncheckedParameter<Smi>(Descriptor::kHint);
  USE(parameter6);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, BoolT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, BoolT> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block57(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block79(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block78(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number, BoolT> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block81(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Number> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{parameter5}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{parameter4}, TNode<Smi>{tmp2});
    ca_.Goto(&block5, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block5, tmp4);
  }

  TNode<BoolT> phi_bb5_8;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_8);
    ca_.Branch(phi_bb5_8, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 888});
      CodeStubAssembler(state_).FailAssert("Torque assert 'length > 0 && base >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> tmp5;
  TNode<BoolT> tmp6;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp5 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp5}, TNode<Smi>{parameter6});
    ca_.Branch(tmp6, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp7;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp7 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{parameter6}, TNode<Smi>{parameter5});
    ca_.Goto(&block10, tmp7);
  }

  TNode<BoolT> tmp8;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp8 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block10, tmp8);
  }

  TNode<BoolT> phi_bb10_8;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_8);
    ca_.Branch(phi_bb10_8, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 889});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 <= hint && hint < length' failed", pos_stack);
    }
  }

  TNode<Smi> tmp9;
  TNode<Smi> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<Smi> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<UintPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp9 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp10 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    std::tie(tmp11, tmp12, tmp13) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp14 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp15 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp14});
    tmp16 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp13});
    tmp18 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp16}, TNode<UintPtrT>{tmp17});
    ca_.Branch(tmp18, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Union<HeapObject, TaggedIndex>> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<Object> tmp23;
  TNode<JSAny> tmp24;
  TNode<Number> tmp25;
  TNode<Number> tmp26;
  TNode<BoolT> tmp27;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp19 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp15});
    tmp20 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp19});
    std::tie(tmp21, tmp22) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp11}, TNode<IntPtrT>{tmp20}).Flatten();
    tmp23 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp21, tmp22});
    tmp24 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp23});
    tmp25 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{parameter3}, TNode<JSAny>{tmp24});
    tmp26 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp27 = NumberIsLessThan_0(state_, TNode<Number>{tmp25}, TNode<Number>{tmp26});
    ca_.Branch(tmp27, &block19, std::vector<compiler::Node*>{}, &block20, std::vector<compiler::Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp28;
  TNode<Smi> tmp29;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp28 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp29 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter6}, TNode<Smi>{tmp28});
    ca_.Goto(&block24, tmp9, tmp10, tmp25);
  }

  TNode<Smi> phi_bb24_7;
  TNode<Smi> phi_bb24_8;
  TNode<Number> phi_bb24_10;
  TNode<BoolT> tmp30;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_7, &phi_bb24_8, &phi_bb24_10);
    tmp30 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb24_8}, TNode<Smi>{tmp29});
    ca_.Branch(tmp30, &block22, std::vector<compiler::Node*>{phi_bb24_7, phi_bb24_8, phi_bb24_10}, &block23, std::vector<compiler::Node*>{phi_bb24_7, phi_bb24_8, phi_bb24_10});
  }

  TNode<Smi> phi_bb22_7;
  TNode<Smi> phi_bb22_8;
  TNode<Number> phi_bb22_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<Smi> tmp34;
  TNode<Smi> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<UintPtrT> tmp37;
  TNode<UintPtrT> tmp38;
  TNode<BoolT> tmp39;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_7, &phi_bb22_8, &phi_bb22_10);
    std::tie(tmp31, tmp32, tmp33) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp34 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp35 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp34}, TNode<Smi>{phi_bb22_8});
    tmp36 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp35});
    tmp37 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp36});
    tmp38 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp33});
    tmp39 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp37}, TNode<UintPtrT>{tmp38});
    ca_.Branch(tmp39, &block29, std::vector<compiler::Node*>{phi_bb22_7, phi_bb22_8, phi_bb22_10}, &block30, std::vector<compiler::Node*>{phi_bb22_7, phi_bb22_8, phi_bb22_10});
  }

  TNode<Smi> phi_bb29_7;
  TNode<Smi> phi_bb29_8;
  TNode<Number> phi_bb29_10;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<Union<HeapObject, TaggedIndex>> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<Object> tmp44;
  TNode<JSAny> tmp45;
  TNode<Number> tmp46;
  TNode<Number> tmp47;
  TNode<BoolT> tmp48;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_7, &phi_bb29_8, &phi_bb29_10);
    tmp40 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp36});
    tmp41 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp32}, TNode<IntPtrT>{tmp40});
    std::tie(tmp42, tmp43) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp31}, TNode<IntPtrT>{tmp41}).Flatten();
    tmp44 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp42, tmp43});
    tmp45 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp44});
    tmp46 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{parameter3}, TNode<JSAny>{tmp45});
    tmp47 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp48 = NumberIsGreaterThanOrEqual_0(state_, TNode<Number>{tmp46}, TNode<Number>{tmp47});
    ca_.Branch(tmp48, &block33, std::vector<compiler::Node*>{phi_bb29_7, phi_bb29_8}, &block34, std::vector<compiler::Node*>{phi_bb29_7, phi_bb29_8});
  }

  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_8;
  TNode<Number> phi_bb30_10;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_7, &phi_bb30_8, &phi_bb30_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_8;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_7, &phi_bb33_8);
    ca_.Goto(&block23, phi_bb33_7, phi_bb33_8, tmp46);
  }

  TNode<Smi> phi_bb34_7;
  TNode<Smi> phi_bb34_8;
  TNode<Smi> tmp49;
  TNode<Smi> tmp50;
  TNode<Smi> tmp51;
  TNode<Smi> tmp52;
  TNode<BoolT> tmp53;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_7, &phi_bb34_8);
    tmp49 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb34_8}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp50 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp51 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp49}, TNode<Smi>{tmp50});
    tmp52 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp53 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp51}, TNode<Smi>{tmp52});
    ca_.Branch(tmp53, &block35, std::vector<compiler::Node*>{phi_bb34_8}, &block36, std::vector<compiler::Node*>{phi_bb34_8, tmp51});
  }

  TNode<Smi> phi_bb35_7;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_7);
    ca_.Goto(&block36, phi_bb35_7, tmp29);
  }

  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_8;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_7, &phi_bb36_8);
    ca_.Goto(&block24, phi_bb36_7, phi_bb36_8, tmp46);
  }

  TNode<Smi> phi_bb23_7;
  TNode<Smi> phi_bb23_8;
  TNode<Number> phi_bb23_10;
  TNode<BoolT> tmp54;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_7, &phi_bb23_8, &phi_bb23_10);
    tmp54 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb23_8}, TNode<Smi>{tmp29});
    ca_.Branch(tmp54, &block37, std::vector<compiler::Node*>{phi_bb23_7, phi_bb23_8, phi_bb23_10}, &block38, std::vector<compiler::Node*>{phi_bb23_7, phi_bb23_8, phi_bb23_10});
  }

  TNode<Smi> phi_bb37_7;
  TNode<Smi> phi_bb37_8;
  TNode<Number> phi_bb37_10;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_7, &phi_bb37_8, &phi_bb37_10);
    ca_.Goto(&block38, phi_bb37_7, tmp29, phi_bb37_10);
  }

  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_8;
  TNode<Number> phi_bb38_10;
  TNode<Smi> tmp55;
  TNode<Smi> tmp56;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_7, &phi_bb38_8, &phi_bb38_10);
    tmp55 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb38_8});
    tmp56 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter6}, TNode<Smi>{phi_bb38_7});
    ca_.Goto(&block21, tmp55, tmp56, phi_bb38_10);
  }

  TNode<Smi> tmp57;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp57 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{parameter5}, TNode<Smi>{parameter6});
    ca_.Goto(&block41, tmp9, tmp10, tmp25);
  }

  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_8;
  TNode<Number> phi_bb41_10;
  TNode<BoolT> tmp58;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_7, &phi_bb41_8, &phi_bb41_10);
    tmp58 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb41_8}, TNode<Smi>{tmp57});
    ca_.Branch(tmp58, &block39, std::vector<compiler::Node*>{phi_bb41_7, phi_bb41_8, phi_bb41_10}, &block40, std::vector<compiler::Node*>{phi_bb41_7, phi_bb41_8, phi_bb41_10});
  }

  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_8;
  TNode<Number> phi_bb39_10;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<Smi> tmp62;
  TNode<Smi> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<UintPtrT> tmp66;
  TNode<BoolT> tmp67;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_7, &phi_bb39_8, &phi_bb39_10);
    std::tie(tmp59, tmp60, tmp61) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp62 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{parameter6});
    tmp63 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp62}, TNode<Smi>{phi_bb39_8});
    tmp64 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp63});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp64});
    tmp66 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp61});
    tmp67 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp65}, TNode<UintPtrT>{tmp66});
    ca_.Branch(tmp67, &block46, std::vector<compiler::Node*>{phi_bb39_7, phi_bb39_8, phi_bb39_10}, &block47, std::vector<compiler::Node*>{phi_bb39_7, phi_bb39_8, phi_bb39_10});
  }

  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_8;
  TNode<Number> phi_bb46_10;
  TNode<IntPtrT> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<Union<HeapObject, TaggedIndex>> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<Object> tmp72;
  TNode<JSAny> tmp73;
  TNode<Number> tmp74;
  TNode<Number> tmp75;
  TNode<BoolT> tmp76;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_7, &phi_bb46_8, &phi_bb46_10);
    tmp68 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp64});
    tmp69 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp68});
    std::tie(tmp70, tmp71) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp69}).Flatten();
    tmp72 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp70, tmp71});
    tmp73 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp72});
    tmp74 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{parameter3}, TNode<JSAny>{tmp73});
    tmp75 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp76 = NumberIsLessThan_0(state_, TNode<Number>{tmp74}, TNode<Number>{tmp75});
    ca_.Branch(tmp76, &block50, std::vector<compiler::Node*>{phi_bb46_7, phi_bb46_8}, &block51, std::vector<compiler::Node*>{phi_bb46_7, phi_bb46_8});
  }

  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_8;
  TNode<Number> phi_bb47_10;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_7, &phi_bb47_8, &phi_bb47_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb50_7;
  TNode<Smi> phi_bb50_8;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_7, &phi_bb50_8);
    ca_.Goto(&block40, phi_bb50_7, phi_bb50_8, tmp74);
  }

  TNode<Smi> phi_bb51_7;
  TNode<Smi> phi_bb51_8;
  TNode<Smi> tmp77;
  TNode<Smi> tmp78;
  TNode<Smi> tmp79;
  TNode<Smi> tmp80;
  TNode<BoolT> tmp81;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_7, &phi_bb51_8);
    tmp77 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb51_8}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp78 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp79 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp77}, TNode<Smi>{tmp78});
    tmp80 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp81 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp79}, TNode<Smi>{tmp80});
    ca_.Branch(tmp81, &block52, std::vector<compiler::Node*>{phi_bb51_8}, &block53, std::vector<compiler::Node*>{phi_bb51_8, tmp79});
  }

  TNode<Smi> phi_bb52_7;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_7);
    ca_.Goto(&block53, phi_bb52_7, tmp57);
  }

  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_8;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_7, &phi_bb53_8);
    ca_.Goto(&block41, phi_bb53_7, phi_bb53_8, tmp74);
  }

  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_8;
  TNode<Number> phi_bb40_10;
  TNode<BoolT> tmp82;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_7, &phi_bb40_8, &phi_bb40_10);
    tmp82 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb40_8}, TNode<Smi>{tmp57});
    ca_.Branch(tmp82, &block54, std::vector<compiler::Node*>{phi_bb40_7, phi_bb40_8, phi_bb40_10}, &block55, std::vector<compiler::Node*>{phi_bb40_7, phi_bb40_8, phi_bb40_10});
  }

  TNode<Smi> phi_bb54_7;
  TNode<Smi> phi_bb54_8;
  TNode<Number> phi_bb54_10;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_7, &phi_bb54_8, &phi_bb54_10);
    ca_.Goto(&block55, phi_bb54_7, tmp57, phi_bb54_10);
  }

  TNode<Smi> phi_bb55_7;
  TNode<Smi> phi_bb55_8;
  TNode<Number> phi_bb55_10;
  TNode<Smi> tmp83;
  TNode<Smi> tmp84;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_7, &phi_bb55_8, &phi_bb55_10);
    tmp83 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb55_7}, TNode<Smi>{parameter6});
    tmp84 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb55_8}, TNode<Smi>{parameter6});
    ca_.Goto(&block21, tmp83, tmp84, phi_bb55_10);
  }

  TNode<Smi> phi_bb21_7;
  TNode<Smi> phi_bb21_8;
  TNode<Number> phi_bb21_10;
  TNode<Smi> tmp85;
  TNode<BoolT> tmp86;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_7, &phi_bb21_8, &phi_bb21_10);
    tmp85 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(true, 0x1ull));
    tmp86 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp85}, TNode<Smi>{phi_bb21_7});
    ca_.Branch(tmp86, &block58, std::vector<compiler::Node*>{phi_bb21_10}, &block59, std::vector<compiler::Node*>{phi_bb21_10});
  }

  TNode<Number> phi_bb58_10;
  TNode<BoolT> tmp87;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_10);
    tmp87 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb21_7}, TNode<Smi>{phi_bb21_8});
    ca_.Goto(&block60, phi_bb58_10, tmp87);
  }

  TNode<Number> phi_bb59_10;
  TNode<BoolT> tmp88;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_10);
    tmp88 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block60, phi_bb59_10, tmp88);
  }

  TNode<Number> phi_bb60_10;
  TNode<BoolT> phi_bb60_12;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_10, &phi_bb60_12);
    ca_.Branch(phi_bb60_12, &block61, std::vector<compiler::Node*>{phi_bb60_10}, &block62, std::vector<compiler::Node*>{phi_bb60_10});
  }

  TNode<Number> phi_bb61_10;
  TNode<BoolT> tmp89;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_10);
    tmp89 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{phi_bb21_8}, TNode<Smi>{parameter5});
    ca_.Goto(&block63, phi_bb61_10, tmp89);
  }

  TNode<Number> phi_bb62_10;
  TNode<BoolT> tmp90;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_10);
    tmp90 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block63, phi_bb62_10, tmp90);
  }

  TNode<Number> phi_bb63_10;
  TNode<BoolT> phi_bb63_12;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_10, &phi_bb63_12);
    ca_.Branch(phi_bb63_12, &block56, std::vector<compiler::Node*>{phi_bb63_10}, &block57, std::vector<compiler::Node*>{phi_bb63_10});
  }

  TNode<Number> phi_bb57_10;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 950});
      CodeStubAssembler(state_).FailAssert("Torque assert '-1 <= lastOfs && lastOfs < offset && offset <= length' failed", pos_stack);
    }
  }

  TNode<Number> phi_bb56_10;
  TNode<Smi> tmp91;
  TNode<Smi> tmp92;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_10);
    tmp91 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp92 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb21_7}, TNode<Smi>{tmp91});
    ca_.Goto(&block66, tmp92, phi_bb21_8, phi_bb56_10);
  }

  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_8;
  TNode<Number> phi_bb66_10;
  TNode<BoolT> tmp93;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_7, &phi_bb66_8, &phi_bb66_10);
    tmp93 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb66_7}, TNode<Smi>{phi_bb66_8});
    ca_.Branch(tmp93, &block64, std::vector<compiler::Node*>{phi_bb66_7, phi_bb66_8, phi_bb66_10}, &block65, std::vector<compiler::Node*>{phi_bb66_7, phi_bb66_8, phi_bb66_10});
  }

  TNode<Smi> phi_bb64_7;
  TNode<Smi> phi_bb64_8;
  TNode<Number> phi_bb64_10;
  TNode<Smi> tmp94;
  TNode<Smi> tmp95;
  TNode<Smi> tmp96;
  TNode<Union<HeapObject, TaggedIndex>> tmp97;
  TNode<IntPtrT> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<Smi> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<UintPtrT> tmp102;
  TNode<UintPtrT> tmp103;
  TNode<BoolT> tmp104;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_7, &phi_bb64_8, &phi_bb64_10);
    tmp94 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb64_8}, TNode<Smi>{phi_bb64_7});
    tmp95 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{tmp94}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp96 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb64_7}, TNode<Smi>{tmp95});
    std::tie(tmp97, tmp98, tmp99) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter2}).Flatten();
    tmp100 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{parameter4}, TNode<Smi>{tmp96});
    tmp101 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp100});
    tmp102 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp101});
    tmp103 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp99});
    tmp104 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp102}, TNode<UintPtrT>{tmp103});
    ca_.Branch(tmp104, &block71, std::vector<compiler::Node*>{phi_bb64_7, phi_bb64_8, phi_bb64_10}, &block72, std::vector<compiler::Node*>{phi_bb64_7, phi_bb64_8, phi_bb64_10});
  }

  TNode<Smi> phi_bb71_7;
  TNode<Smi> phi_bb71_8;
  TNode<Number> phi_bb71_10;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<Union<HeapObject, TaggedIndex>> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<Object> tmp109;
  TNode<JSAny> tmp110;
  TNode<Number> tmp111;
  TNode<Number> tmp112;
  TNode<BoolT> tmp113;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_7, &phi_bb71_8, &phi_bb71_10);
    tmp105 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp101});
    tmp106 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp98}, TNode<IntPtrT>{tmp105});
    std::tie(tmp107, tmp108) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp97}, TNode<IntPtrT>{tmp106}).Flatten();
    tmp109 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp107, tmp108});
    tmp110 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp109});
    tmp111 = Compare_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<JSAny>{parameter3}, TNode<JSAny>{tmp110});
    tmp112 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp113 = NumberIsLessThan_0(state_, TNode<Number>{tmp111}, TNode<Number>{tmp112});
    ca_.Branch(tmp113, &block75, std::vector<compiler::Node*>{phi_bb71_7, phi_bb71_8}, &block76, std::vector<compiler::Node*>{phi_bb71_7, phi_bb71_8});
  }

  TNode<Smi> phi_bb72_7;
  TNode<Smi> phi_bb72_8;
  TNode<Number> phi_bb72_10;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_7, &phi_bb72_8, &phi_bb72_10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb75_7;
  TNode<Smi> phi_bb75_8;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_7, &phi_bb75_8);
    ca_.Goto(&block77, phi_bb75_7, tmp96);
  }

  TNode<Smi> phi_bb76_7;
  TNode<Smi> phi_bb76_8;
  TNode<Smi> tmp114;
  TNode<Smi> tmp115;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_7, &phi_bb76_8);
    tmp114 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp115 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp96}, TNode<Smi>{tmp114});
    ca_.Goto(&block77, tmp115, phi_bb76_8);
  }

  TNode<Smi> phi_bb77_7;
  TNode<Smi> phi_bb77_8;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_7, &phi_bb77_8);
    ca_.Goto(&block66, phi_bb77_7, phi_bb77_8, tmp111);
  }

  TNode<Smi> phi_bb65_7;
  TNode<Smi> phi_bb65_8;
  TNode<Number> phi_bb65_10;
  TNode<BoolT> tmp116;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_7, &phi_bb65_8, &phi_bb65_10);
    tmp116 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb65_7}, TNode<Smi>{phi_bb65_8});
    ca_.Branch(tmp116, &block78, std::vector<compiler::Node*>{phi_bb65_7, phi_bb65_8, phi_bb65_10}, &block79, std::vector<compiler::Node*>{phi_bb65_7, phi_bb65_8, phi_bb65_10});
  }

  TNode<Smi> phi_bb79_7;
  TNode<Smi> phi_bb79_8;
  TNode<Number> phi_bb79_10;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_7, &phi_bb79_8, &phi_bb79_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 969});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lastOfs == offset' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb78_7;
  TNode<Smi> phi_bb78_8;
  TNode<Number> phi_bb78_10;
  TNode<Smi> tmp117;
  TNode<BoolT> tmp118;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_7, &phi_bb78_8, &phi_bb78_10);
    tmp117 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp118 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp117}, TNode<Smi>{phi_bb78_8});
    ca_.Branch(tmp118, &block82, std::vector<compiler::Node*>{phi_bb78_7, phi_bb78_8, phi_bb78_10}, &block83, std::vector<compiler::Node*>{phi_bb78_7, phi_bb78_8, phi_bb78_10});
  }

  TNode<Smi> phi_bb82_7;
  TNode<Smi> phi_bb82_8;
  TNode<Number> phi_bb82_10;
  TNode<BoolT> tmp119;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_7, &phi_bb82_8, &phi_bb82_10);
    tmp119 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{phi_bb82_8}, TNode<Smi>{parameter5});
    ca_.Goto(&block84, phi_bb82_7, phi_bb82_8, phi_bb82_10, tmp119);
  }

  TNode<Smi> phi_bb83_7;
  TNode<Smi> phi_bb83_8;
  TNode<Number> phi_bb83_10;
  TNode<BoolT> tmp120;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_7, &phi_bb83_8, &phi_bb83_10);
    tmp120 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block84, phi_bb83_7, phi_bb83_8, phi_bb83_10, tmp120);
  }

  TNode<Smi> phi_bb84_7;
  TNode<Smi> phi_bb84_8;
  TNode<Number> phi_bb84_10;
  TNode<BoolT> phi_bb84_12;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_7, &phi_bb84_8, &phi_bb84_10, &phi_bb84_12);
    ca_.Branch(phi_bb84_12, &block80, std::vector<compiler::Node*>{phi_bb84_7, phi_bb84_8, phi_bb84_10}, &block81, std::vector<compiler::Node*>{phi_bb84_7, phi_bb84_8, phi_bb84_10});
  }

  TNode<Smi> phi_bb81_7;
  TNode<Smi> phi_bb81_8;
  TNode<Number> phi_bb81_10;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_7, &phi_bb81_8, &phi_bb81_10);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 970});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 <= offset && offset <= length' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb80_7;
  TNode<Smi> phi_bb80_8;
  TNode<Number> phi_bb80_10;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_7, &phi_bb80_8, &phi_bb80_10);
    CodeStubAssembler(state_).Return(phi_bb80_8);
  }
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=980&c=1
void MergeLow_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_baseA, TNode<Smi> p_lengthAArg, TNode<Smi> p_baseB, TNode<Smi> p_lengthBArg) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block100(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block118(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block131(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block136(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block133(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block154(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block155(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block161(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block165(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block164(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block168(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block174(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block187(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block189(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block193(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, BoolT> block194(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block191(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block200(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block207(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block208(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block211(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp0}, TNode<Smi>{p_lengthAArg});
    ca_.Branch(tmp1, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp2}, TNode<Smi>{p_lengthBArg});
    ca_.Goto(&block6, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block6, tmp4);
  }

  TNode<BoolT> phi_bb6_7;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7);
    ca_.Branch(phi_bb6_7, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 983});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 < lengthAArg && 0 < lengthBArg' failed", pos_stack);
    }
  }

  TNode<Smi> tmp5;
  TNode<BoolT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp5}, TNode<Smi>{p_baseA});
    ca_.Branch(tmp6, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp7 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp8 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp7}, TNode<Smi>{p_baseB});
    ca_.Goto(&block11, tmp8);
  }

  TNode<BoolT> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block11, tmp9);
  }

  TNode<BoolT> phi_bb11_7;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    ca_.Branch(phi_bb11_7, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 984});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 <= baseA && 0 < baseB' failed", pos_stack);
    }
  }

  TNode<Smi> tmp10;
  TNode<BoolT> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseA}, TNode<Smi>{p_lengthAArg});
    tmp11 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp10}, TNode<Smi>{p_baseB});
    ca_.Branch(tmp11, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 985});
      CodeStubAssembler(state_).FailAssert("Torque assert 'baseA + lengthAArg == baseB' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp12;
  TNode<FixedArray> tmp13;
  TNode<FixedArray> tmp14;
  TNode<Smi> tmp15;
  TNode<JSAny> tmp16;
  TNode<Smi> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<UintPtrT> tmp24;
  TNode<UintPtrT> tmp25;
  TNode<BoolT> tmp26;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp13 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp12});
    tmp14 = GetTempArray_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{p_lengthAArg});
    tmp15 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp13, p_baseA, tmp14, tmp15, p_lengthAArg);
    tmp17 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp18, tmp19, tmp20) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp21 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp22 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseA}, TNode<Smi>{tmp21});
    tmp23 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_baseA});
    tmp24 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp23});
    tmp25 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp20});
    tmp26 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp24}, TNode<UintPtrT>{tmp25});
    ca_.Branch(tmp26, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Union<HeapObject, TaggedIndex>> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<Union<HeapObject, TaggedIndex>> tmp31;
  TNode<IntPtrT> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<Smi> tmp34;
  TNode<Smi> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<UintPtrT> tmp37;
  TNode<UintPtrT> tmp38;
  TNode<BoolT> tmp39;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp27 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp23});
    tmp28 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp19}, TNode<IntPtrT>{tmp27});
    std::tie(tmp29, tmp30) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp18}, TNode<IntPtrT>{tmp28}).Flatten();
    std::tie(tmp31, tmp32, tmp33) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp34 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp35 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseB}, TNode<Smi>{tmp34});
    tmp36 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_baseB});
    tmp37 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp36});
    tmp38 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp33});
    tmp39 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp37}, TNode<UintPtrT>{tmp38});
    ca_.Branch(tmp39, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<Union<HeapObject, TaggedIndex>> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<Object> tmp44;
  TNode<Smi> tmp45;
  TNode<Smi> tmp46;
  TNode<Smi> tmp47;
  TNode<BoolT> tmp48;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp40 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp36});
    tmp41 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp32}, TNode<IntPtrT>{tmp40});
    std::tie(tmp42, tmp43) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp31}, TNode<IntPtrT>{tmp41}).Flatten();
    tmp44 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp42, tmp43});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp29, tmp30}, tmp44);
    tmp45 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp46 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_lengthBArg}, TNode<Smi>{tmp45});
    tmp47 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp48 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp46}, TNode<Smi>{tmp47});
    ca_.Branch(tmp48, &block34, std::vector<compiler::Node*>{}, &block35, std::vector<compiler::Node*>{});
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    ca_.Goto(&block33, p_lengthAArg, tmp46, tmp22, tmp17, tmp35);
  }

  TNode<Smi> tmp49;
  TNode<BoolT> tmp50;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp49 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp50 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_lengthAArg}, TNode<Smi>{tmp49});
    ca_.Branch(tmp50, &block36, std::vector<compiler::Node*>{}, &block37, std::vector<compiler::Node*>{});
  }

  if (block36.is_used()) {
    ca_.Bind(&block36);
    ca_.Goto(&block31, p_lengthAArg, tmp46, tmp22, tmp17, tmp35);
  }

  TNode<IntPtrT> tmp51;
  TNode<Smi> tmp52;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp51 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp52 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp51});
    ca_.Goto(&block40, p_lengthAArg, tmp46, tmp22, tmp17, tmp35, tmp52);
  }

  TNode<Smi> phi_bb40_6;
  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_10;
  TNode<Smi> phi_bb40_11;
  TNode<Smi> phi_bb40_12;
  TNode<Smi> phi_bb40_13;
  TNode<BoolT> tmp53;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_7, &phi_bb40_10, &phi_bb40_11, &phi_bb40_12, &phi_bb40_13);
    tmp53 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp53, &block38, std::vector<compiler::Node*>{phi_bb40_6, phi_bb40_7, phi_bb40_10, phi_bb40_11, phi_bb40_12, phi_bb40_13}, &block39, std::vector<compiler::Node*>{phi_bb40_6, phi_bb40_7, phi_bb40_10, phi_bb40_11, phi_bb40_12, phi_bb40_13});
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_10;
  TNode<Smi> phi_bb38_11;
  TNode<Smi> phi_bb38_12;
  TNode<Smi> phi_bb38_13;
  TNode<Smi> tmp54;
  TNode<Smi> tmp55;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_7, &phi_bb38_10, &phi_bb38_11, &phi_bb38_12, &phi_bb38_13);
    tmp54 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp55 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block43, phi_bb38_6, phi_bb38_7, phi_bb38_10, phi_bb38_11, phi_bb38_12, phi_bb38_13, tmp54, tmp55);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_10;
  TNode<Smi> phi_bb43_11;
  TNode<Smi> phi_bb43_12;
  TNode<Smi> phi_bb43_13;
  TNode<Smi> phi_bb43_14;
  TNode<Smi> phi_bb43_15;
  TNode<BoolT> tmp56;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_7, &phi_bb43_10, &phi_bb43_11, &phi_bb43_12, &phi_bb43_13, &phi_bb43_14, &phi_bb43_15);
    tmp56 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp56, &block41, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, phi_bb43_14, phi_bb43_15}, &block42, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, phi_bb43_14, phi_bb43_15});
  }

  TNode<Smi> phi_bb41_6;
  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_10;
  TNode<Smi> phi_bb41_11;
  TNode<Smi> phi_bb41_12;
  TNode<Smi> phi_bb41_13;
  TNode<Smi> phi_bb41_14;
  TNode<Smi> phi_bb41_15;
  TNode<Smi> tmp57;
  TNode<BoolT> tmp58;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_6, &phi_bb41_7, &phi_bb41_10, &phi_bb41_11, &phi_bb41_12, &phi_bb41_13, &phi_bb41_14, &phi_bb41_15);
    tmp57 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp58 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb41_6}, TNode<Smi>{tmp57});
    ca_.Branch(tmp58, &block46, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7, phi_bb41_10, phi_bb41_11, phi_bb41_12, phi_bb41_13, phi_bb41_14, phi_bb41_15}, &block47, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7, phi_bb41_10, phi_bb41_11, phi_bb41_12, phi_bb41_13, phi_bb41_14, phi_bb41_15});
  }

  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_10;
  TNode<Smi> phi_bb46_11;
  TNode<Smi> phi_bb46_12;
  TNode<Smi> phi_bb46_13;
  TNode<Smi> phi_bb46_14;
  TNode<Smi> phi_bb46_15;
  TNode<Smi> tmp59;
  TNode<BoolT> tmp60;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_7, &phi_bb46_10, &phi_bb46_11, &phi_bb46_12, &phi_bb46_13, &phi_bb46_14, &phi_bb46_15);
    tmp59 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp60 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb46_7}, TNode<Smi>{tmp59});
    ca_.Goto(&block48, phi_bb46_6, phi_bb46_7, phi_bb46_10, phi_bb46_11, phi_bb46_12, phi_bb46_13, phi_bb46_14, phi_bb46_15, tmp60);
  }

  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_10;
  TNode<Smi> phi_bb47_11;
  TNode<Smi> phi_bb47_12;
  TNode<Smi> phi_bb47_13;
  TNode<Smi> phi_bb47_14;
  TNode<Smi> phi_bb47_15;
  TNode<BoolT> tmp61;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_6, &phi_bb47_7, &phi_bb47_10, &phi_bb47_11, &phi_bb47_12, &phi_bb47_13, &phi_bb47_14, &phi_bb47_15);
    tmp61 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block48, phi_bb47_6, phi_bb47_7, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_14, phi_bb47_15, tmp61);
  }

  TNode<Smi> phi_bb48_6;
  TNode<Smi> phi_bb48_7;
  TNode<Smi> phi_bb48_10;
  TNode<Smi> phi_bb48_11;
  TNode<Smi> phi_bb48_12;
  TNode<Smi> phi_bb48_13;
  TNode<Smi> phi_bb48_14;
  TNode<Smi> phi_bb48_15;
  TNode<BoolT> phi_bb48_17;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_6, &phi_bb48_7, &phi_bb48_10, &phi_bb48_11, &phi_bb48_12, &phi_bb48_13, &phi_bb48_14, &phi_bb48_15, &phi_bb48_17);
    ca_.Branch(phi_bb48_17, &block44, std::vector<compiler::Node*>{phi_bb48_6, phi_bb48_7, phi_bb48_10, phi_bb48_11, phi_bb48_12, phi_bb48_13, phi_bb48_14, phi_bb48_15}, &block45, std::vector<compiler::Node*>{phi_bb48_6, phi_bb48_7, phi_bb48_10, phi_bb48_11, phi_bb48_12, phi_bb48_13, phi_bb48_14, phi_bb48_15});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_10;
  TNode<Smi> phi_bb45_11;
  TNode<Smi> phi_bb45_12;
  TNode<Smi> phi_bb45_13;
  TNode<Smi> phi_bb45_14;
  TNode<Smi> phi_bb45_15;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_7, &phi_bb45_10, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_14, &phi_bb45_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1016});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA > 1 && lengthB > 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb44_6;
  TNode<Smi> phi_bb44_7;
  TNode<Smi> phi_bb44_10;
  TNode<Smi> phi_bb44_11;
  TNode<Smi> phi_bb44_12;
  TNode<Smi> phi_bb44_13;
  TNode<Smi> phi_bb44_14;
  TNode<Smi> phi_bb44_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<UintPtrT> tmp66;
  TNode<UintPtrT> tmp67;
  TNode<BoolT> tmp68;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_7, &phi_bb44_10, &phi_bb44_11, &phi_bb44_12, &phi_bb44_13, &phi_bb44_14, &phi_bb44_15);
    std::tie(tmp62, tmp63, tmp64) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp65 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb44_12});
    tmp66 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp65});
    tmp67 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp64});
    tmp68 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp66}, TNode<UintPtrT>{tmp67});
    ca_.Branch(tmp68, &block53, std::vector<compiler::Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13, phi_bb44_14, phi_bb44_15, phi_bb44_12, phi_bb44_12}, &block54, std::vector<compiler::Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13, phi_bb44_14, phi_bb44_15, phi_bb44_12, phi_bb44_12});
  }

  TNode<Smi> phi_bb53_6;
  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_10;
  TNode<Smi> phi_bb53_11;
  TNode<Smi> phi_bb53_12;
  TNode<Smi> phi_bb53_13;
  TNode<Smi> phi_bb53_14;
  TNode<Smi> phi_bb53_15;
  TNode<Smi> phi_bb53_21;
  TNode<Smi> phi_bb53_22;
  TNode<IntPtrT> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<Union<HeapObject, TaggedIndex>> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<Object> tmp73;
  TNode<JSAny> tmp74;
  TNode<Union<HeapObject, TaggedIndex>> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<UintPtrT> tmp79;
  TNode<UintPtrT> tmp80;
  TNode<BoolT> tmp81;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_6, &phi_bb53_7, &phi_bb53_10, &phi_bb53_11, &phi_bb53_12, &phi_bb53_13, &phi_bb53_14, &phi_bb53_15, &phi_bb53_21, &phi_bb53_22);
    tmp69 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp65});
    tmp70 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp63}, TNode<IntPtrT>{tmp69});
    std::tie(tmp71, tmp72) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp62}, TNode<IntPtrT>{tmp70}).Flatten();
    tmp73 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp71, tmp72});
    tmp74 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp73});
    std::tie(tmp75, tmp76, tmp77) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp78 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb53_11});
    tmp79 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp78});
    tmp80 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp77});
    tmp81 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp79}, TNode<UintPtrT>{tmp80});
    ca_.Branch(tmp81, &block61, std::vector<compiler::Node*>{phi_bb53_6, phi_bb53_7, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13, phi_bb53_14, phi_bb53_15, phi_bb53_11, phi_bb53_11}, &block62, std::vector<compiler::Node*>{phi_bb53_6, phi_bb53_7, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13, phi_bb53_14, phi_bb53_15, phi_bb53_11, phi_bb53_11});
  }

  TNode<Smi> phi_bb54_6;
  TNode<Smi> phi_bb54_7;
  TNode<Smi> phi_bb54_10;
  TNode<Smi> phi_bb54_11;
  TNode<Smi> phi_bb54_12;
  TNode<Smi> phi_bb54_13;
  TNode<Smi> phi_bb54_14;
  TNode<Smi> phi_bb54_15;
  TNode<Smi> phi_bb54_21;
  TNode<Smi> phi_bb54_22;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_6, &phi_bb54_7, &phi_bb54_10, &phi_bb54_11, &phi_bb54_12, &phi_bb54_13, &phi_bb54_14, &phi_bb54_15, &phi_bb54_21, &phi_bb54_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb61_6;
  TNode<Smi> phi_bb61_7;
  TNode<Smi> phi_bb61_10;
  TNode<Smi> phi_bb61_11;
  TNode<Smi> phi_bb61_12;
  TNode<Smi> phi_bb61_13;
  TNode<Smi> phi_bb61_14;
  TNode<Smi> phi_bb61_15;
  TNode<Smi> phi_bb61_22;
  TNode<Smi> phi_bb61_23;
  TNode<IntPtrT> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<Union<HeapObject, TaggedIndex>> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<Object> tmp86;
  TNode<JSAny> tmp87;
  TNode<Number> tmp88;
  TNode<Number> tmp89;
  TNode<BoolT> tmp90;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_6, &phi_bb61_7, &phi_bb61_10, &phi_bb61_11, &phi_bb61_12, &phi_bb61_13, &phi_bb61_14, &phi_bb61_15, &phi_bb61_22, &phi_bb61_23);
    tmp82 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp78});
    tmp83 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp76}, TNode<IntPtrT>{tmp82});
    std::tie(tmp84, tmp85) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp75}, TNode<IntPtrT>{tmp83}).Flatten();
    tmp86 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp84, tmp85});
    tmp87 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp86});
    tmp88 = Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<JSAny>{tmp74}, TNode<JSAny>{tmp87});
    tmp89 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp90 = NumberIsLessThan_0(state_, TNode<Number>{tmp88}, TNode<Number>{tmp89});
    ca_.Branch(tmp90, &block65, std::vector<compiler::Node*>{phi_bb61_6, phi_bb61_7, phi_bb61_10, phi_bb61_11, phi_bb61_12, phi_bb61_13, phi_bb61_14, phi_bb61_15}, &block66, std::vector<compiler::Node*>{phi_bb61_6, phi_bb61_7, phi_bb61_10, phi_bb61_11, phi_bb61_12, phi_bb61_13, phi_bb61_14, phi_bb61_15});
  }

  TNode<Smi> phi_bb62_6;
  TNode<Smi> phi_bb62_7;
  TNode<Smi> phi_bb62_10;
  TNode<Smi> phi_bb62_11;
  TNode<Smi> phi_bb62_12;
  TNode<Smi> phi_bb62_13;
  TNode<Smi> phi_bb62_14;
  TNode<Smi> phi_bb62_15;
  TNode<Smi> phi_bb62_22;
  TNode<Smi> phi_bb62_23;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_6, &phi_bb62_7, &phi_bb62_10, &phi_bb62_11, &phi_bb62_12, &phi_bb62_13, &phi_bb62_14, &phi_bb62_15, &phi_bb62_22, &phi_bb62_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb65_6;
  TNode<Smi> phi_bb65_7;
  TNode<Smi> phi_bb65_10;
  TNode<Smi> phi_bb65_11;
  TNode<Smi> phi_bb65_12;
  TNode<Smi> phi_bb65_13;
  TNode<Smi> phi_bb65_14;
  TNode<Smi> phi_bb65_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<IntPtrT> tmp93;
  TNode<Smi> tmp94;
  TNode<Smi> tmp95;
  TNode<IntPtrT> tmp96;
  TNode<UintPtrT> tmp97;
  TNode<UintPtrT> tmp98;
  TNode<BoolT> tmp99;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_6, &phi_bb65_7, &phi_bb65_10, &phi_bb65_11, &phi_bb65_12, &phi_bb65_13, &phi_bb65_14, &phi_bb65_15);
    std::tie(tmp91, tmp92, tmp93) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp94 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp95 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb65_10}, TNode<Smi>{tmp94});
    tmp96 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb65_10});
    tmp97 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp96});
    tmp98 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp93});
    tmp99 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp97}, TNode<UintPtrT>{tmp98});
    ca_.Branch(tmp99, &block72, std::vector<compiler::Node*>{phi_bb65_6, phi_bb65_7, phi_bb65_11, phi_bb65_12, phi_bb65_13, phi_bb65_14, phi_bb65_15, phi_bb65_10, phi_bb65_10}, &block73, std::vector<compiler::Node*>{phi_bb65_6, phi_bb65_7, phi_bb65_11, phi_bb65_12, phi_bb65_13, phi_bb65_14, phi_bb65_15, phi_bb65_10, phi_bb65_10});
  }

  TNode<Smi> phi_bb72_6;
  TNode<Smi> phi_bb72_7;
  TNode<Smi> phi_bb72_11;
  TNode<Smi> phi_bb72_12;
  TNode<Smi> phi_bb72_13;
  TNode<Smi> phi_bb72_14;
  TNode<Smi> phi_bb72_15;
  TNode<Smi> phi_bb72_21;
  TNode<Smi> phi_bb72_22;
  TNode<IntPtrT> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<Union<HeapObject, TaggedIndex>> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<Union<HeapObject, TaggedIndex>> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<Smi> tmp107;
  TNode<Smi> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<UintPtrT> tmp110;
  TNode<UintPtrT> tmp111;
  TNode<BoolT> tmp112;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_6, &phi_bb72_7, &phi_bb72_11, &phi_bb72_12, &phi_bb72_13, &phi_bb72_14, &phi_bb72_15, &phi_bb72_21, &phi_bb72_22);
    tmp100 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp96});
    tmp101 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp92}, TNode<IntPtrT>{tmp100});
    std::tie(tmp102, tmp103) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp91}, TNode<IntPtrT>{tmp101}).Flatten();
    std::tie(tmp104, tmp105, tmp106) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp107 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp108 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb72_12}, TNode<Smi>{tmp107});
    tmp109 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb72_12});
    tmp110 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp109});
    tmp111 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp106});
    tmp112 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp110}, TNode<UintPtrT>{tmp111});
    ca_.Branch(tmp112, &block80, std::vector<compiler::Node*>{phi_bb72_6, phi_bb72_7, phi_bb72_11, phi_bb72_13, phi_bb72_14, phi_bb72_15, phi_bb72_21, phi_bb72_22, phi_bb72_12, phi_bb72_12}, &block81, std::vector<compiler::Node*>{phi_bb72_6, phi_bb72_7, phi_bb72_11, phi_bb72_13, phi_bb72_14, phi_bb72_15, phi_bb72_21, phi_bb72_22, phi_bb72_12, phi_bb72_12});
  }

  TNode<Smi> phi_bb73_6;
  TNode<Smi> phi_bb73_7;
  TNode<Smi> phi_bb73_11;
  TNode<Smi> phi_bb73_12;
  TNode<Smi> phi_bb73_13;
  TNode<Smi> phi_bb73_14;
  TNode<Smi> phi_bb73_15;
  TNode<Smi> phi_bb73_21;
  TNode<Smi> phi_bb73_22;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_6, &phi_bb73_7, &phi_bb73_11, &phi_bb73_12, &phi_bb73_13, &phi_bb73_14, &phi_bb73_15, &phi_bb73_21, &phi_bb73_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb80_6;
  TNode<Smi> phi_bb80_7;
  TNode<Smi> phi_bb80_11;
  TNode<Smi> phi_bb80_13;
  TNode<Smi> phi_bb80_14;
  TNode<Smi> phi_bb80_15;
  TNode<Smi> phi_bb80_21;
  TNode<Smi> phi_bb80_22;
  TNode<Smi> phi_bb80_29;
  TNode<Smi> phi_bb80_30;
  TNode<IntPtrT> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<Union<HeapObject, TaggedIndex>> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<Object> tmp117;
  TNode<Smi> tmp118;
  TNode<Smi> tmp119;
  TNode<Smi> tmp120;
  TNode<Smi> tmp121;
  TNode<Smi> tmp122;
  TNode<Smi> tmp123;
  TNode<BoolT> tmp124;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_6, &phi_bb80_7, &phi_bb80_11, &phi_bb80_13, &phi_bb80_14, &phi_bb80_15, &phi_bb80_21, &phi_bb80_22, &phi_bb80_29, &phi_bb80_30);
    tmp113 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp109});
    tmp114 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp105}, TNode<IntPtrT>{tmp113});
    std::tie(tmp115, tmp116) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp104}, TNode<IntPtrT>{tmp114}).Flatten();
    tmp117 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp115, tmp116});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp102, tmp103}, tmp117);
    tmp118 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp119 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb80_15}, TNode<Smi>{tmp118});
    tmp120 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp121 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb80_7}, TNode<Smi>{tmp120});
    tmp122 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp123 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp124 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp121}, TNode<Smi>{tmp123});
    ca_.Branch(tmp124, &block84, std::vector<compiler::Node*>{phi_bb80_6, phi_bb80_11, phi_bb80_13}, &block85, std::vector<compiler::Node*>{phi_bb80_6, phi_bb80_11, phi_bb80_13});
  }

  TNode<Smi> phi_bb81_6;
  TNode<Smi> phi_bb81_7;
  TNode<Smi> phi_bb81_11;
  TNode<Smi> phi_bb81_13;
  TNode<Smi> phi_bb81_14;
  TNode<Smi> phi_bb81_15;
  TNode<Smi> phi_bb81_21;
  TNode<Smi> phi_bb81_22;
  TNode<Smi> phi_bb81_29;
  TNode<Smi> phi_bb81_30;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_6, &phi_bb81_7, &phi_bb81_11, &phi_bb81_13, &phi_bb81_14, &phi_bb81_15, &phi_bb81_21, &phi_bb81_22, &phi_bb81_29, &phi_bb81_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb84_6;
  TNode<Smi> phi_bb84_11;
  TNode<Smi> phi_bb84_13;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_6, &phi_bb84_11, &phi_bb84_13);
    ca_.Goto(&block33, phi_bb84_6, tmp121, tmp95, phi_bb84_11, tmp108);
  }

  TNode<Smi> phi_bb85_6;
  TNode<Smi> phi_bb85_11;
  TNode<Smi> phi_bb85_13;
  TNode<BoolT> tmp125;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_6, &phi_bb85_11, &phi_bb85_13);
    tmp125 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp119}, TNode<Smi>{phi_bb85_13});
    ca_.Branch(tmp125, &block86, std::vector<compiler::Node*>{phi_bb85_6, phi_bb85_11, phi_bb85_13}, &block87, std::vector<compiler::Node*>{phi_bb85_6, phi_bb85_11, phi_bb85_13});
  }

  TNode<Smi> phi_bb86_6;
  TNode<Smi> phi_bb86_11;
  TNode<Smi> phi_bb86_13;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_6, &phi_bb86_11, &phi_bb86_13);
    ca_.Goto(&block42, phi_bb86_6, tmp121, tmp95, phi_bb86_11, tmp108, phi_bb86_13, tmp122, tmp119);
  }

  TNode<Smi> phi_bb87_6;
  TNode<Smi> phi_bb87_11;
  TNode<Smi> phi_bb87_13;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_6, &phi_bb87_11, &phi_bb87_13);
    ca_.Goto(&block67, phi_bb87_6, tmp121, tmp95, phi_bb87_11, tmp108, phi_bb87_13, tmp122, tmp119);
  }

  TNode<Smi> phi_bb66_6;
  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_10;
  TNode<Smi> phi_bb66_11;
  TNode<Smi> phi_bb66_12;
  TNode<Smi> phi_bb66_13;
  TNode<Smi> phi_bb66_14;
  TNode<Smi> phi_bb66_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp126;
  TNode<IntPtrT> tmp127;
  TNode<IntPtrT> tmp128;
  TNode<Smi> tmp129;
  TNode<Smi> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<UintPtrT> tmp132;
  TNode<UintPtrT> tmp133;
  TNode<BoolT> tmp134;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_6, &phi_bb66_7, &phi_bb66_10, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13, &phi_bb66_14, &phi_bb66_15);
    std::tie(tmp126, tmp127, tmp128) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp129 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp130 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb66_10}, TNode<Smi>{tmp129});
    tmp131 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb66_10});
    tmp132 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp131});
    tmp133 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp128});
    tmp134 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp132}, TNode<UintPtrT>{tmp133});
    ca_.Branch(tmp134, &block92, std::vector<compiler::Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15, phi_bb66_10, phi_bb66_10}, &block93, std::vector<compiler::Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15, phi_bb66_10, phi_bb66_10});
  }

  TNode<Smi> phi_bb92_6;
  TNode<Smi> phi_bb92_7;
  TNode<Smi> phi_bb92_11;
  TNode<Smi> phi_bb92_12;
  TNode<Smi> phi_bb92_13;
  TNode<Smi> phi_bb92_14;
  TNode<Smi> phi_bb92_15;
  TNode<Smi> phi_bb92_21;
  TNode<Smi> phi_bb92_22;
  TNode<IntPtrT> tmp135;
  TNode<IntPtrT> tmp136;
  TNode<Union<HeapObject, TaggedIndex>> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<Union<HeapObject, TaggedIndex>> tmp139;
  TNode<IntPtrT> tmp140;
  TNode<IntPtrT> tmp141;
  TNode<Smi> tmp142;
  TNode<Smi> tmp143;
  TNode<IntPtrT> tmp144;
  TNode<UintPtrT> tmp145;
  TNode<UintPtrT> tmp146;
  TNode<BoolT> tmp147;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_6, &phi_bb92_7, &phi_bb92_11, &phi_bb92_12, &phi_bb92_13, &phi_bb92_14, &phi_bb92_15, &phi_bb92_21, &phi_bb92_22);
    tmp135 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp131});
    tmp136 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp127}, TNode<IntPtrT>{tmp135});
    std::tie(tmp137, tmp138) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp126}, TNode<IntPtrT>{tmp136}).Flatten();
    std::tie(tmp139, tmp140, tmp141) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp142 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp143 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb92_11}, TNode<Smi>{tmp142});
    tmp144 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb92_11});
    tmp145 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp144});
    tmp146 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp141});
    tmp147 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp145}, TNode<UintPtrT>{tmp146});
    ca_.Branch(tmp147, &block100, std::vector<compiler::Node*>{phi_bb92_6, phi_bb92_7, phi_bb92_12, phi_bb92_13, phi_bb92_14, phi_bb92_15, phi_bb92_21, phi_bb92_22, phi_bb92_11, phi_bb92_11}, &block101, std::vector<compiler::Node*>{phi_bb92_6, phi_bb92_7, phi_bb92_12, phi_bb92_13, phi_bb92_14, phi_bb92_15, phi_bb92_21, phi_bb92_22, phi_bb92_11, phi_bb92_11});
  }

  TNode<Smi> phi_bb93_6;
  TNode<Smi> phi_bb93_7;
  TNode<Smi> phi_bb93_11;
  TNode<Smi> phi_bb93_12;
  TNode<Smi> phi_bb93_13;
  TNode<Smi> phi_bb93_14;
  TNode<Smi> phi_bb93_15;
  TNode<Smi> phi_bb93_21;
  TNode<Smi> phi_bb93_22;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_6, &phi_bb93_7, &phi_bb93_11, &phi_bb93_12, &phi_bb93_13, &phi_bb93_14, &phi_bb93_15, &phi_bb93_21, &phi_bb93_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb100_6;
  TNode<Smi> phi_bb100_7;
  TNode<Smi> phi_bb100_12;
  TNode<Smi> phi_bb100_13;
  TNode<Smi> phi_bb100_14;
  TNode<Smi> phi_bb100_15;
  TNode<Smi> phi_bb100_21;
  TNode<Smi> phi_bb100_22;
  TNode<Smi> phi_bb100_29;
  TNode<Smi> phi_bb100_30;
  TNode<IntPtrT> tmp148;
  TNode<IntPtrT> tmp149;
  TNode<Union<HeapObject, TaggedIndex>> tmp150;
  TNode<IntPtrT> tmp151;
  TNode<Object> tmp152;
  TNode<Smi> tmp153;
  TNode<Smi> tmp154;
  TNode<Smi> tmp155;
  TNode<Smi> tmp156;
  TNode<Smi> tmp157;
  TNode<Smi> tmp158;
  TNode<BoolT> tmp159;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_6, &phi_bb100_7, &phi_bb100_12, &phi_bb100_13, &phi_bb100_14, &phi_bb100_15, &phi_bb100_21, &phi_bb100_22, &phi_bb100_29, &phi_bb100_30);
    tmp148 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp144});
    tmp149 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp140}, TNode<IntPtrT>{tmp148});
    std::tie(tmp150, tmp151) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp139}, TNode<IntPtrT>{tmp149}).Flatten();
    tmp152 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp150, tmp151});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp137, tmp138}, tmp152);
    tmp153 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp154 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb100_14}, TNode<Smi>{tmp153});
    tmp155 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp156 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb100_6}, TNode<Smi>{tmp155});
    tmp157 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp158 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp159 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp156}, TNode<Smi>{tmp158});
    ca_.Branch(tmp159, &block104, std::vector<compiler::Node*>{phi_bb100_7, phi_bb100_12, phi_bb100_13}, &block105, std::vector<compiler::Node*>{phi_bb100_7, phi_bb100_12, phi_bb100_13});
  }

  TNode<Smi> phi_bb101_6;
  TNode<Smi> phi_bb101_7;
  TNode<Smi> phi_bb101_12;
  TNode<Smi> phi_bb101_13;
  TNode<Smi> phi_bb101_14;
  TNode<Smi> phi_bb101_15;
  TNode<Smi> phi_bb101_21;
  TNode<Smi> phi_bb101_22;
  TNode<Smi> phi_bb101_29;
  TNode<Smi> phi_bb101_30;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_6, &phi_bb101_7, &phi_bb101_12, &phi_bb101_13, &phi_bb101_14, &phi_bb101_15, &phi_bb101_21, &phi_bb101_22, &phi_bb101_29, &phi_bb101_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb104_7;
  TNode<Smi> phi_bb104_12;
  TNode<Smi> phi_bb104_13;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_7, &phi_bb104_12, &phi_bb104_13);
    ca_.Goto(&block31, tmp156, phi_bb104_7, tmp130, tmp143, phi_bb104_12);
  }

  TNode<Smi> phi_bb105_7;
  TNode<Smi> phi_bb105_12;
  TNode<Smi> phi_bb105_13;
  TNode<BoolT> tmp160;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_7, &phi_bb105_12, &phi_bb105_13);
    tmp160 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp154}, TNode<Smi>{phi_bb105_13});
    ca_.Branch(tmp160, &block106, std::vector<compiler::Node*>{phi_bb105_7, phi_bb105_12, phi_bb105_13}, &block107, std::vector<compiler::Node*>{phi_bb105_7, phi_bb105_12, phi_bb105_13});
  }

  TNode<Smi> phi_bb106_7;
  TNode<Smi> phi_bb106_12;
  TNode<Smi> phi_bb106_13;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_7, &phi_bb106_12, &phi_bb106_13);
    ca_.Goto(&block42, tmp156, phi_bb106_7, tmp130, tmp143, phi_bb106_12, phi_bb106_13, tmp154, tmp157);
  }

  TNode<Smi> phi_bb107_7;
  TNode<Smi> phi_bb107_12;
  TNode<Smi> phi_bb107_13;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_7, &phi_bb107_12, &phi_bb107_13);
    ca_.Goto(&block67, tmp156, phi_bb107_7, tmp130, tmp143, phi_bb107_12, phi_bb107_13, tmp154, tmp157);
  }

  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_10;
  TNode<Smi> phi_bb67_11;
  TNode<Smi> phi_bb67_12;
  TNode<Smi> phi_bb67_13;
  TNode<Smi> phi_bb67_14;
  TNode<Smi> phi_bb67_15;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_7, &phi_bb67_10, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13, &phi_bb67_14, &phi_bb67_15);
    ca_.Goto(&block43, phi_bb67_6, phi_bb67_7, phi_bb67_10, phi_bb67_11, phi_bb67_12, phi_bb67_13, phi_bb67_14, phi_bb67_15);
  }

  TNode<Smi> phi_bb42_6;
  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_10;
  TNode<Smi> phi_bb42_11;
  TNode<Smi> phi_bb42_12;
  TNode<Smi> phi_bb42_13;
  TNode<Smi> phi_bb42_14;
  TNode<Smi> phi_bb42_15;
  TNode<Smi> tmp161;
  TNode<Smi> tmp162;
  TNode<BoolT> tmp163;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_7, &phi_bb42_10, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13, &phi_bb42_14, &phi_bb42_15);
    tmp161 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp162 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb42_13}, TNode<Smi>{tmp161});
    tmp163 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block110, phi_bb42_6, phi_bb42_7, phi_bb42_10, phi_bb42_11, phi_bb42_12, tmp162, phi_bb42_14, phi_bb42_15, tmp163);
  }

  TNode<Smi> phi_bb110_6;
  TNode<Smi> phi_bb110_7;
  TNode<Smi> phi_bb110_10;
  TNode<Smi> phi_bb110_11;
  TNode<Smi> phi_bb110_12;
  TNode<Smi> phi_bb110_13;
  TNode<Smi> phi_bb110_14;
  TNode<Smi> phi_bb110_15;
  TNode<BoolT> phi_bb110_16;
  TNode<Smi> tmp164;
  TNode<BoolT> tmp165;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_6, &phi_bb110_7, &phi_bb110_10, &phi_bb110_11, &phi_bb110_12, &phi_bb110_13, &phi_bb110_14, &phi_bb110_15, &phi_bb110_16);
    tmp164 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp165 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb110_14}, TNode<Smi>{tmp164});
    ca_.Branch(tmp165, &block111, std::vector<compiler::Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16}, &block112, std::vector<compiler::Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16});
  }

  TNode<Smi> phi_bb111_6;
  TNode<Smi> phi_bb111_7;
  TNode<Smi> phi_bb111_10;
  TNode<Smi> phi_bb111_11;
  TNode<Smi> phi_bb111_12;
  TNode<Smi> phi_bb111_13;
  TNode<Smi> phi_bb111_14;
  TNode<Smi> phi_bb111_15;
  TNode<BoolT> phi_bb111_16;
  TNode<BoolT> tmp166;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_6, &phi_bb111_7, &phi_bb111_10, &phi_bb111_11, &phi_bb111_12, &phi_bb111_13, &phi_bb111_14, &phi_bb111_15, &phi_bb111_16);
    tmp166 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block113, phi_bb111_6, phi_bb111_7, phi_bb111_10, phi_bb111_11, phi_bb111_12, phi_bb111_13, phi_bb111_14, phi_bb111_15, phi_bb111_16, tmp166);
  }

  TNode<Smi> phi_bb112_6;
  TNode<Smi> phi_bb112_7;
  TNode<Smi> phi_bb112_10;
  TNode<Smi> phi_bb112_11;
  TNode<Smi> phi_bb112_12;
  TNode<Smi> phi_bb112_13;
  TNode<Smi> phi_bb112_14;
  TNode<Smi> phi_bb112_15;
  TNode<BoolT> phi_bb112_16;
  TNode<Smi> tmp167;
  TNode<BoolT> tmp168;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_6, &phi_bb112_7, &phi_bb112_10, &phi_bb112_11, &phi_bb112_12, &phi_bb112_13, &phi_bb112_14, &phi_bb112_15, &phi_bb112_16);
    tmp167 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp168 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb112_15}, TNode<Smi>{tmp167});
    ca_.Goto(&block113, phi_bb112_6, phi_bb112_7, phi_bb112_10, phi_bb112_11, phi_bb112_12, phi_bb112_13, phi_bb112_14, phi_bb112_15, phi_bb112_16, tmp168);
  }

  TNode<Smi> phi_bb113_6;
  TNode<Smi> phi_bb113_7;
  TNode<Smi> phi_bb113_10;
  TNode<Smi> phi_bb113_11;
  TNode<Smi> phi_bb113_12;
  TNode<Smi> phi_bb113_13;
  TNode<Smi> phi_bb113_14;
  TNode<Smi> phi_bb113_15;
  TNode<BoolT> phi_bb113_16;
  TNode<BoolT> phi_bb113_18;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_6, &phi_bb113_7, &phi_bb113_10, &phi_bb113_11, &phi_bb113_12, &phi_bb113_13, &phi_bb113_14, &phi_bb113_15, &phi_bb113_16, &phi_bb113_18);
    ca_.Branch(phi_bb113_18, &block114, std::vector<compiler::Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16}, &block115, std::vector<compiler::Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16});
  }

  TNode<Smi> phi_bb114_6;
  TNode<Smi> phi_bb114_7;
  TNode<Smi> phi_bb114_10;
  TNode<Smi> phi_bb114_11;
  TNode<Smi> phi_bb114_12;
  TNode<Smi> phi_bb114_13;
  TNode<Smi> phi_bb114_14;
  TNode<Smi> phi_bb114_15;
  TNode<BoolT> phi_bb114_16;
  TNode<BoolT> tmp169;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_6, &phi_bb114_7, &phi_bb114_10, &phi_bb114_11, &phi_bb114_12, &phi_bb114_13, &phi_bb114_14, &phi_bb114_15, &phi_bb114_16);
    tmp169 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block116, phi_bb114_6, phi_bb114_7, phi_bb114_10, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_14, phi_bb114_15, phi_bb114_16, tmp169);
  }

  TNode<Smi> phi_bb115_6;
  TNode<Smi> phi_bb115_7;
  TNode<Smi> phi_bb115_10;
  TNode<Smi> phi_bb115_11;
  TNode<Smi> phi_bb115_12;
  TNode<Smi> phi_bb115_13;
  TNode<Smi> phi_bb115_14;
  TNode<Smi> phi_bb115_15;
  TNode<BoolT> phi_bb115_16;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_6, &phi_bb115_7, &phi_bb115_10, &phi_bb115_11, &phi_bb115_12, &phi_bb115_13, &phi_bb115_14, &phi_bb115_15, &phi_bb115_16);
    ca_.Goto(&block116, phi_bb115_6, phi_bb115_7, phi_bb115_10, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_14, phi_bb115_15, phi_bb115_16, phi_bb115_16);
  }

  TNode<Smi> phi_bb116_6;
  TNode<Smi> phi_bb116_7;
  TNode<Smi> phi_bb116_10;
  TNode<Smi> phi_bb116_11;
  TNode<Smi> phi_bb116_12;
  TNode<Smi> phi_bb116_13;
  TNode<Smi> phi_bb116_14;
  TNode<Smi> phi_bb116_15;
  TNode<BoolT> phi_bb116_16;
  TNode<BoolT> phi_bb116_18;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_6, &phi_bb116_7, &phi_bb116_10, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13, &phi_bb116_14, &phi_bb116_15, &phi_bb116_16, &phi_bb116_18);
    ca_.Branch(phi_bb116_18, &block108, std::vector<compiler::Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16}, &block109, std::vector<compiler::Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16});
  }

  TNode<Smi> phi_bb108_6;
  TNode<Smi> phi_bb108_7;
  TNode<Smi> phi_bb108_10;
  TNode<Smi> phi_bb108_11;
  TNode<Smi> phi_bb108_12;
  TNode<Smi> phi_bb108_13;
  TNode<Smi> phi_bb108_14;
  TNode<Smi> phi_bb108_15;
  TNode<BoolT> phi_bb108_16;
  TNode<BoolT> tmp170;
  TNode<Smi> tmp171;
  TNode<BoolT> tmp172;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_6, &phi_bb108_7, &phi_bb108_10, &phi_bb108_11, &phi_bb108_12, &phi_bb108_13, &phi_bb108_14, &phi_bb108_15, &phi_bb108_16);
    tmp170 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp171 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp172 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb108_6}, TNode<Smi>{tmp171});
    ca_.Branch(tmp172, &block119, std::vector<compiler::Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_13, phi_bb108_14, phi_bb108_15}, &block120, std::vector<compiler::Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_13, phi_bb108_14, phi_bb108_15});
  }

  TNode<Smi> phi_bb119_6;
  TNode<Smi> phi_bb119_7;
  TNode<Smi> phi_bb119_10;
  TNode<Smi> phi_bb119_11;
  TNode<Smi> phi_bb119_12;
  TNode<Smi> phi_bb119_13;
  TNode<Smi> phi_bb119_14;
  TNode<Smi> phi_bb119_15;
  TNode<Smi> tmp173;
  TNode<BoolT> tmp174;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_6, &phi_bb119_7, &phi_bb119_10, &phi_bb119_11, &phi_bb119_12, &phi_bb119_13, &phi_bb119_14, &phi_bb119_15);
    tmp173 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp174 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb119_7}, TNode<Smi>{tmp173});
    ca_.Goto(&block121, phi_bb119_6, phi_bb119_7, phi_bb119_10, phi_bb119_11, phi_bb119_12, phi_bb119_13, phi_bb119_14, phi_bb119_15, tmp174);
  }

  TNode<Smi> phi_bb120_6;
  TNode<Smi> phi_bb120_7;
  TNode<Smi> phi_bb120_10;
  TNode<Smi> phi_bb120_11;
  TNode<Smi> phi_bb120_12;
  TNode<Smi> phi_bb120_13;
  TNode<Smi> phi_bb120_14;
  TNode<Smi> phi_bb120_15;
  TNode<BoolT> tmp175;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_6, &phi_bb120_7, &phi_bb120_10, &phi_bb120_11, &phi_bb120_12, &phi_bb120_13, &phi_bb120_14, &phi_bb120_15);
    tmp175 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block121, phi_bb120_6, phi_bb120_7, phi_bb120_10, phi_bb120_11, phi_bb120_12, phi_bb120_13, phi_bb120_14, phi_bb120_15, tmp175);
  }

  TNode<Smi> phi_bb121_6;
  TNode<Smi> phi_bb121_7;
  TNode<Smi> phi_bb121_10;
  TNode<Smi> phi_bb121_11;
  TNode<Smi> phi_bb121_12;
  TNode<Smi> phi_bb121_13;
  TNode<Smi> phi_bb121_14;
  TNode<Smi> phi_bb121_15;
  TNode<BoolT> phi_bb121_18;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_6, &phi_bb121_7, &phi_bb121_10, &phi_bb121_11, &phi_bb121_12, &phi_bb121_13, &phi_bb121_14, &phi_bb121_15, &phi_bb121_18);
    ca_.Branch(phi_bb121_18, &block117, std::vector<compiler::Node*>{phi_bb121_6, phi_bb121_7, phi_bb121_10, phi_bb121_11, phi_bb121_12, phi_bb121_13, phi_bb121_14, phi_bb121_15}, &block118, std::vector<compiler::Node*>{phi_bb121_6, phi_bb121_7, phi_bb121_10, phi_bb121_11, phi_bb121_12, phi_bb121_13, phi_bb121_14, phi_bb121_15});
  }

  TNode<Smi> phi_bb118_6;
  TNode<Smi> phi_bb118_7;
  TNode<Smi> phi_bb118_10;
  TNode<Smi> phi_bb118_11;
  TNode<Smi> phi_bb118_12;
  TNode<Smi> phi_bb118_13;
  TNode<Smi> phi_bb118_14;
  TNode<Smi> phi_bb118_15;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_6, &phi_bb118_7, &phi_bb118_10, &phi_bb118_11, &phi_bb118_12, &phi_bb118_13, &phi_bb118_14, &phi_bb118_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1051});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA > 1 && lengthB > 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb117_6;
  TNode<Smi> phi_bb117_7;
  TNode<Smi> phi_bb117_10;
  TNode<Smi> phi_bb117_11;
  TNode<Smi> phi_bb117_12;
  TNode<Smi> phi_bb117_13;
  TNode<Smi> phi_bb117_14;
  TNode<Smi> phi_bb117_15;
  TNode<Smi> tmp176;
  TNode<Smi> tmp177;
  TNode<Smi> tmp178;
  TNode<Smi> tmp179;
  TNode<IntPtrT> tmp180;
  TNode<Union<HeapObject, TaggedIndex>> tmp181;
  TNode<IntPtrT> tmp182;
  TNode<IntPtrT> tmp183;
  TNode<IntPtrT> tmp184;
  TNode<UintPtrT> tmp185;
  TNode<UintPtrT> tmp186;
  TNode<BoolT> tmp187;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_6, &phi_bb117_7, &phi_bb117_10, &phi_bb117_11, &phi_bb117_12, &phi_bb117_13, &phi_bb117_14, &phi_bb117_15);
    tmp176 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp177 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb117_13}, TNode<Smi>{tmp176});
    tmp178 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp179 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp178}, TNode<Smi>{tmp177});
    tmp180 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp180}, tmp179);
    std::tie(tmp181, tmp182, tmp183) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp184 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb117_12});
    tmp185 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp184});
    tmp186 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp183});
    tmp187 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp185}, TNode<UintPtrT>{tmp186});
    ca_.Branch(tmp187, &block126, std::vector<compiler::Node*>{phi_bb117_6, phi_bb117_7, phi_bb117_10, phi_bb117_11, phi_bb117_12, phi_bb117_14, phi_bb117_15, phi_bb117_12, phi_bb117_12}, &block127, std::vector<compiler::Node*>{phi_bb117_6, phi_bb117_7, phi_bb117_10, phi_bb117_11, phi_bb117_12, phi_bb117_14, phi_bb117_15, phi_bb117_12, phi_bb117_12});
  }

  TNode<Smi> phi_bb126_6;
  TNode<Smi> phi_bb126_7;
  TNode<Smi> phi_bb126_10;
  TNode<Smi> phi_bb126_11;
  TNode<Smi> phi_bb126_12;
  TNode<Smi> phi_bb126_14;
  TNode<Smi> phi_bb126_15;
  TNode<Smi> phi_bb126_22;
  TNode<Smi> phi_bb126_23;
  TNode<IntPtrT> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<Union<HeapObject, TaggedIndex>> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<Object> tmp192;
  TNode<JSAny> tmp193;
  TNode<Smi> tmp194;
  TNode<Smi> tmp195;
  TNode<Smi> tmp196;
  TNode<BoolT> tmp197;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_6, &phi_bb126_7, &phi_bb126_10, &phi_bb126_11, &phi_bb126_12, &phi_bb126_14, &phi_bb126_15, &phi_bb126_22, &phi_bb126_23);
    tmp188 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp184});
    tmp189 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp182}, TNode<IntPtrT>{tmp188});
    std::tie(tmp190, tmp191) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp181}, TNode<IntPtrT>{tmp189}).Flatten();
    tmp192 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp190, tmp191});
    tmp193 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp192});
    tmp194 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp195 = ca_.CallBuiltin<Smi>(Builtin::kGallopRight, p_context, p_sortState, tmp14, tmp193, phi_bb126_11, phi_bb126_6, tmp194);
    tmp196 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp197 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp195}, TNode<Smi>{tmp196});
    ca_.Branch(tmp197, &block130, std::vector<compiler::Node*>{phi_bb126_6, phi_bb126_7, phi_bb126_10, phi_bb126_11, phi_bb126_12, phi_bb126_15}, &block131, std::vector<compiler::Node*>{phi_bb126_6, phi_bb126_7, phi_bb126_10, phi_bb126_11, phi_bb126_12, phi_bb126_15});
  }

  TNode<Smi> phi_bb127_6;
  TNode<Smi> phi_bb127_7;
  TNode<Smi> phi_bb127_10;
  TNode<Smi> phi_bb127_11;
  TNode<Smi> phi_bb127_12;
  TNode<Smi> phi_bb127_14;
  TNode<Smi> phi_bb127_15;
  TNode<Smi> phi_bb127_22;
  TNode<Smi> phi_bb127_23;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_6, &phi_bb127_7, &phi_bb127_10, &phi_bb127_11, &phi_bb127_12, &phi_bb127_14, &phi_bb127_15, &phi_bb127_22, &phi_bb127_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb131_6;
  TNode<Smi> phi_bb131_7;
  TNode<Smi> phi_bb131_10;
  TNode<Smi> phi_bb131_11;
  TNode<Smi> phi_bb131_12;
  TNode<Smi> phi_bb131_15;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_6, &phi_bb131_7, &phi_bb131_10, &phi_bb131_11, &phi_bb131_12, &phi_bb131_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1059});
      CodeStubAssembler(state_).FailAssert("Torque assert 'nofWinsA >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb130_6;
  TNode<Smi> phi_bb130_7;
  TNode<Smi> phi_bb130_10;
  TNode<Smi> phi_bb130_11;
  TNode<Smi> phi_bb130_12;
  TNode<Smi> phi_bb130_15;
  TNode<Smi> tmp198;
  TNode<BoolT> tmp199;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_6, &phi_bb130_7, &phi_bb130_10, &phi_bb130_11, &phi_bb130_12, &phi_bb130_15);
    tmp198 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp199 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp195}, TNode<Smi>{tmp198});
    ca_.Branch(tmp199, &block132, std::vector<compiler::Node*>{phi_bb130_6, phi_bb130_7, phi_bb130_10, phi_bb130_11, phi_bb130_12, phi_bb130_15}, &block133, std::vector<compiler::Node*>{phi_bb130_6, phi_bb130_7, phi_bb130_10, phi_bb130_11, phi_bb130_12, phi_bb130_15});
  }

  TNode<Smi> phi_bb132_6;
  TNode<Smi> phi_bb132_7;
  TNode<Smi> phi_bb132_10;
  TNode<Smi> phi_bb132_11;
  TNode<Smi> phi_bb132_12;
  TNode<Smi> phi_bb132_15;
  TNode<JSAny> tmp200;
  TNode<Smi> tmp201;
  TNode<Smi> tmp202;
  TNode<Smi> tmp203;
  TNode<Smi> tmp204;
  TNode<BoolT> tmp205;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_6, &phi_bb132_7, &phi_bb132_10, &phi_bb132_11, &phi_bb132_12, &phi_bb132_15);
    tmp200 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp14, phi_bb132_11, tmp13, phi_bb132_10, tmp195);
    tmp201 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb132_10}, TNode<Smi>{tmp195});
    tmp202 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb132_11}, TNode<Smi>{tmp195});
    tmp203 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb132_6}, TNode<Smi>{tmp195});
    tmp204 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp205 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp203}, TNode<Smi>{tmp204});
    ca_.Branch(tmp205, &block134, std::vector<compiler::Node*>{phi_bb132_7, phi_bb132_12, phi_bb132_15}, &block135, std::vector<compiler::Node*>{phi_bb132_7, phi_bb132_12, phi_bb132_15});
  }

  TNode<Smi> phi_bb134_7;
  TNode<Smi> phi_bb134_12;
  TNode<Smi> phi_bb134_15;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_7, &phi_bb134_12, &phi_bb134_15);
    ca_.Goto(&block31, tmp203, phi_bb134_7, tmp201, tmp202, phi_bb134_12);
  }

  TNode<Smi> phi_bb135_7;
  TNode<Smi> phi_bb135_12;
  TNode<Smi> phi_bb135_15;
  TNode<Smi> tmp206;
  TNode<BoolT> tmp207;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_7, &phi_bb135_12, &phi_bb135_15);
    tmp206 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp207 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp203}, TNode<Smi>{tmp206});
    ca_.Branch(tmp207, &block136, std::vector<compiler::Node*>{phi_bb135_7, phi_bb135_12, phi_bb135_15}, &block137, std::vector<compiler::Node*>{phi_bb135_7, phi_bb135_12, phi_bb135_15});
  }

  TNode<Smi> phi_bb136_7;
  TNode<Smi> phi_bb136_12;
  TNode<Smi> phi_bb136_15;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_7, &phi_bb136_12, &phi_bb136_15);
    ca_.Goto(&block33, tmp203, phi_bb136_7, tmp201, tmp202, phi_bb136_12);
  }

  TNode<Smi> phi_bb137_7;
  TNode<Smi> phi_bb137_12;
  TNode<Smi> phi_bb137_15;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_7, &phi_bb137_12, &phi_bb137_15);
    ca_.Goto(&block133, tmp203, phi_bb137_7, tmp201, tmp202, phi_bb137_12, phi_bb137_15);
  }

  TNode<Smi> phi_bb133_6;
  TNode<Smi> phi_bb133_7;
  TNode<Smi> phi_bb133_10;
  TNode<Smi> phi_bb133_11;
  TNode<Smi> phi_bb133_12;
  TNode<Smi> phi_bb133_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp208;
  TNode<IntPtrT> tmp209;
  TNode<IntPtrT> tmp210;
  TNode<Smi> tmp211;
  TNode<Smi> tmp212;
  TNode<IntPtrT> tmp213;
  TNode<UintPtrT> tmp214;
  TNode<UintPtrT> tmp215;
  TNode<BoolT> tmp216;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_6, &phi_bb133_7, &phi_bb133_10, &phi_bb133_11, &phi_bb133_12, &phi_bb133_15);
    std::tie(tmp208, tmp209, tmp210) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp211 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp212 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb133_10}, TNode<Smi>{tmp211});
    tmp213 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb133_10});
    tmp214 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp213});
    tmp215 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp210});
    tmp216 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp214}, TNode<UintPtrT>{tmp215});
    ca_.Branch(tmp216, &block142, std::vector<compiler::Node*>{phi_bb133_6, phi_bb133_7, phi_bb133_11, phi_bb133_12, phi_bb133_15, phi_bb133_10, phi_bb133_10}, &block143, std::vector<compiler::Node*>{phi_bb133_6, phi_bb133_7, phi_bb133_11, phi_bb133_12, phi_bb133_15, phi_bb133_10, phi_bb133_10});
  }

  TNode<Smi> phi_bb142_6;
  TNode<Smi> phi_bb142_7;
  TNode<Smi> phi_bb142_11;
  TNode<Smi> phi_bb142_12;
  TNode<Smi> phi_bb142_15;
  TNode<Smi> phi_bb142_21;
  TNode<Smi> phi_bb142_22;
  TNode<IntPtrT> tmp217;
  TNode<IntPtrT> tmp218;
  TNode<Union<HeapObject, TaggedIndex>> tmp219;
  TNode<IntPtrT> tmp220;
  TNode<Union<HeapObject, TaggedIndex>> tmp221;
  TNode<IntPtrT> tmp222;
  TNode<IntPtrT> tmp223;
  TNode<Smi> tmp224;
  TNode<Smi> tmp225;
  TNode<IntPtrT> tmp226;
  TNode<UintPtrT> tmp227;
  TNode<UintPtrT> tmp228;
  TNode<BoolT> tmp229;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_6, &phi_bb142_7, &phi_bb142_11, &phi_bb142_12, &phi_bb142_15, &phi_bb142_21, &phi_bb142_22);
    tmp217 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp213});
    tmp218 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp209}, TNode<IntPtrT>{tmp217});
    std::tie(tmp219, tmp220) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp208}, TNode<IntPtrT>{tmp218}).Flatten();
    std::tie(tmp221, tmp222, tmp223) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp224 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp225 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb142_12}, TNode<Smi>{tmp224});
    tmp226 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb142_12});
    tmp227 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp226});
    tmp228 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp223});
    tmp229 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp227}, TNode<UintPtrT>{tmp228});
    ca_.Branch(tmp229, &block150, std::vector<compiler::Node*>{phi_bb142_6, phi_bb142_7, phi_bb142_11, phi_bb142_15, phi_bb142_21, phi_bb142_22, phi_bb142_12, phi_bb142_12}, &block151, std::vector<compiler::Node*>{phi_bb142_6, phi_bb142_7, phi_bb142_11, phi_bb142_15, phi_bb142_21, phi_bb142_22, phi_bb142_12, phi_bb142_12});
  }

  TNode<Smi> phi_bb143_6;
  TNode<Smi> phi_bb143_7;
  TNode<Smi> phi_bb143_11;
  TNode<Smi> phi_bb143_12;
  TNode<Smi> phi_bb143_15;
  TNode<Smi> phi_bb143_21;
  TNode<Smi> phi_bb143_22;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_6, &phi_bb143_7, &phi_bb143_11, &phi_bb143_12, &phi_bb143_15, &phi_bb143_21, &phi_bb143_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb150_6;
  TNode<Smi> phi_bb150_7;
  TNode<Smi> phi_bb150_11;
  TNode<Smi> phi_bb150_15;
  TNode<Smi> phi_bb150_21;
  TNode<Smi> phi_bb150_22;
  TNode<Smi> phi_bb150_29;
  TNode<Smi> phi_bb150_30;
  TNode<IntPtrT> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<Union<HeapObject, TaggedIndex>> tmp232;
  TNode<IntPtrT> tmp233;
  TNode<Object> tmp234;
  TNode<Smi> tmp235;
  TNode<Smi> tmp236;
  TNode<Smi> tmp237;
  TNode<BoolT> tmp238;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_6, &phi_bb150_7, &phi_bb150_11, &phi_bb150_15, &phi_bb150_21, &phi_bb150_22, &phi_bb150_29, &phi_bb150_30);
    tmp230 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp226});
    tmp231 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp222}, TNode<IntPtrT>{tmp230});
    std::tie(tmp232, tmp233) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp221}, TNode<IntPtrT>{tmp231}).Flatten();
    tmp234 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp232, tmp233});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp219, tmp220}, tmp234);
    tmp235 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp236 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb150_7}, TNode<Smi>{tmp235});
    tmp237 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp238 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp236}, TNode<Smi>{tmp237});
    ca_.Branch(tmp238, &block154, std::vector<compiler::Node*>{phi_bb150_6, phi_bb150_11, phi_bb150_15}, &block155, std::vector<compiler::Node*>{phi_bb150_6, phi_bb150_11, phi_bb150_15});
  }

  TNode<Smi> phi_bb151_6;
  TNode<Smi> phi_bb151_7;
  TNode<Smi> phi_bb151_11;
  TNode<Smi> phi_bb151_15;
  TNode<Smi> phi_bb151_21;
  TNode<Smi> phi_bb151_22;
  TNode<Smi> phi_bb151_29;
  TNode<Smi> phi_bb151_30;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_6, &phi_bb151_7, &phi_bb151_11, &phi_bb151_15, &phi_bb151_21, &phi_bb151_22, &phi_bb151_29, &phi_bb151_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb154_6;
  TNode<Smi> phi_bb154_11;
  TNode<Smi> phi_bb154_15;
  if (block154.is_used()) {
    ca_.Bind(&block154, &phi_bb154_6, &phi_bb154_11, &phi_bb154_15);
    ca_.Goto(&block33, phi_bb154_6, tmp236, tmp212, phi_bb154_11, tmp225);
  }

  TNode<Smi> phi_bb155_6;
  TNode<Smi> phi_bb155_11;
  TNode<Smi> phi_bb155_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp239;
  TNode<IntPtrT> tmp240;
  TNode<IntPtrT> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<UintPtrT> tmp243;
  TNode<UintPtrT> tmp244;
  TNode<BoolT> tmp245;
  if (block155.is_used()) {
    ca_.Bind(&block155, &phi_bb155_6, &phi_bb155_11, &phi_bb155_15);
    std::tie(tmp239, tmp240, tmp241) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp242 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb155_11});
    tmp243 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp242});
    tmp244 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp241});
    tmp245 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp243}, TNode<UintPtrT>{tmp244});
    ca_.Branch(tmp245, &block160, std::vector<compiler::Node*>{phi_bb155_6, phi_bb155_11, phi_bb155_15, phi_bb155_11, phi_bb155_11}, &block161, std::vector<compiler::Node*>{phi_bb155_6, phi_bb155_11, phi_bb155_15, phi_bb155_11, phi_bb155_11});
  }

  TNode<Smi> phi_bb160_6;
  TNode<Smi> phi_bb160_11;
  TNode<Smi> phi_bb160_15;
  TNode<Smi> phi_bb160_22;
  TNode<Smi> phi_bb160_23;
  TNode<IntPtrT> tmp246;
  TNode<IntPtrT> tmp247;
  TNode<Union<HeapObject, TaggedIndex>> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<Object> tmp250;
  TNode<JSAny> tmp251;
  TNode<Smi> tmp252;
  TNode<Smi> tmp253;
  TNode<Smi> tmp254;
  TNode<BoolT> tmp255;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_6, &phi_bb160_11, &phi_bb160_15, &phi_bb160_22, &phi_bb160_23);
    tmp246 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp242});
    tmp247 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp240}, TNode<IntPtrT>{tmp246});
    std::tie(tmp248, tmp249) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp239}, TNode<IntPtrT>{tmp247}).Flatten();
    tmp250 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp248, tmp249});
    tmp251 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp250});
    tmp252 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp253 = ca_.CallBuiltin<Smi>(Builtin::kGallopLeft, p_context, p_sortState, tmp13, tmp251, tmp225, tmp236, tmp252);
    tmp254 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp255 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp253}, TNode<Smi>{tmp254});
    ca_.Branch(tmp255, &block164, std::vector<compiler::Node*>{phi_bb160_6, phi_bb160_11}, &block165, std::vector<compiler::Node*>{phi_bb160_6, phi_bb160_11});
  }

  TNode<Smi> phi_bb161_6;
  TNode<Smi> phi_bb161_11;
  TNode<Smi> phi_bb161_15;
  TNode<Smi> phi_bb161_22;
  TNode<Smi> phi_bb161_23;
  if (block161.is_used()) {
    ca_.Bind(&block161, &phi_bb161_6, &phi_bb161_11, &phi_bb161_15, &phi_bb161_22, &phi_bb161_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb165_6;
  TNode<Smi> phi_bb165_11;
  if (block165.is_used()) {
    ca_.Bind(&block165, &phi_bb165_6, &phi_bb165_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1079});
      CodeStubAssembler(state_).FailAssert("Torque assert 'nofWinsB >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb164_6;
  TNode<Smi> phi_bb164_11;
  TNode<Smi> tmp256;
  TNode<BoolT> tmp257;
  if (block164.is_used()) {
    ca_.Bind(&block164, &phi_bb164_6, &phi_bb164_11);
    tmp256 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp257 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp253}, TNode<Smi>{tmp256});
    ca_.Branch(tmp257, &block166, std::vector<compiler::Node*>{phi_bb164_6, phi_bb164_11}, &block167, std::vector<compiler::Node*>{phi_bb164_6, tmp236, tmp212, phi_bb164_11, tmp225});
  }

  TNode<Smi> phi_bb166_6;
  TNode<Smi> phi_bb166_11;
  TNode<JSAny> tmp258;
  TNode<Smi> tmp259;
  TNode<Smi> tmp260;
  TNode<Smi> tmp261;
  TNode<Smi> tmp262;
  TNode<BoolT> tmp263;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_6, &phi_bb166_11);
    tmp258 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp13, tmp225, tmp13, tmp212, tmp253);
    tmp259 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp212}, TNode<Smi>{tmp253});
    tmp260 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp225}, TNode<Smi>{tmp253});
    tmp261 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp236}, TNode<Smi>{tmp253});
    tmp262 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp263 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp261}, TNode<Smi>{tmp262});
    ca_.Branch(tmp263, &block168, std::vector<compiler::Node*>{phi_bb166_6, phi_bb166_11}, &block169, std::vector<compiler::Node*>{phi_bb166_6, phi_bb166_11});
  }

  TNode<Smi> phi_bb168_6;
  TNode<Smi> phi_bb168_11;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_6, &phi_bb168_11);
    ca_.Goto(&block33, phi_bb168_6, tmp261, tmp259, phi_bb168_11, tmp260);
  }

  TNode<Smi> phi_bb169_6;
  TNode<Smi> phi_bb169_11;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_6, &phi_bb169_11);
    ca_.Goto(&block167, phi_bb169_6, tmp261, tmp259, phi_bb169_11, tmp260);
  }

  TNode<Smi> phi_bb167_6;
  TNode<Smi> phi_bb167_7;
  TNode<Smi> phi_bb167_10;
  TNode<Smi> phi_bb167_11;
  TNode<Smi> phi_bb167_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp264;
  TNode<IntPtrT> tmp265;
  TNode<IntPtrT> tmp266;
  TNode<Smi> tmp267;
  TNode<Smi> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<UintPtrT> tmp270;
  TNode<UintPtrT> tmp271;
  TNode<BoolT> tmp272;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_6, &phi_bb167_7, &phi_bb167_10, &phi_bb167_11, &phi_bb167_12);
    std::tie(tmp264, tmp265, tmp266) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp267 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp268 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb167_10}, TNode<Smi>{tmp267});
    tmp269 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb167_10});
    tmp270 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp269});
    tmp271 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp266});
    tmp272 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp270}, TNode<UintPtrT>{tmp271});
    ca_.Branch(tmp272, &block174, std::vector<compiler::Node*>{phi_bb167_6, phi_bb167_7, phi_bb167_11, phi_bb167_12, phi_bb167_10, phi_bb167_10}, &block175, std::vector<compiler::Node*>{phi_bb167_6, phi_bb167_7, phi_bb167_11, phi_bb167_12, phi_bb167_10, phi_bb167_10});
  }

  TNode<Smi> phi_bb174_6;
  TNode<Smi> phi_bb174_7;
  TNode<Smi> phi_bb174_11;
  TNode<Smi> phi_bb174_12;
  TNode<Smi> phi_bb174_21;
  TNode<Smi> phi_bb174_22;
  TNode<IntPtrT> tmp273;
  TNode<IntPtrT> tmp274;
  TNode<Union<HeapObject, TaggedIndex>> tmp275;
  TNode<IntPtrT> tmp276;
  TNode<Union<HeapObject, TaggedIndex>> tmp277;
  TNode<IntPtrT> tmp278;
  TNode<IntPtrT> tmp279;
  TNode<Smi> tmp280;
  TNode<Smi> tmp281;
  TNode<IntPtrT> tmp282;
  TNode<UintPtrT> tmp283;
  TNode<UintPtrT> tmp284;
  TNode<BoolT> tmp285;
  if (block174.is_used()) {
    ca_.Bind(&block174, &phi_bb174_6, &phi_bb174_7, &phi_bb174_11, &phi_bb174_12, &phi_bb174_21, &phi_bb174_22);
    tmp273 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp269});
    tmp274 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp265}, TNode<IntPtrT>{tmp273});
    std::tie(tmp275, tmp276) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp264}, TNode<IntPtrT>{tmp274}).Flatten();
    std::tie(tmp277, tmp278, tmp279) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp280 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp281 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb174_11}, TNode<Smi>{tmp280});
    tmp282 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb174_11});
    tmp283 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp282});
    tmp284 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp279});
    tmp285 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp283}, TNode<UintPtrT>{tmp284});
    ca_.Branch(tmp285, &block182, std::vector<compiler::Node*>{phi_bb174_6, phi_bb174_7, phi_bb174_12, phi_bb174_21, phi_bb174_22, phi_bb174_11, phi_bb174_11}, &block183, std::vector<compiler::Node*>{phi_bb174_6, phi_bb174_7, phi_bb174_12, phi_bb174_21, phi_bb174_22, phi_bb174_11, phi_bb174_11});
  }

  TNode<Smi> phi_bb175_6;
  TNode<Smi> phi_bb175_7;
  TNode<Smi> phi_bb175_11;
  TNode<Smi> phi_bb175_12;
  TNode<Smi> phi_bb175_21;
  TNode<Smi> phi_bb175_22;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_6, &phi_bb175_7, &phi_bb175_11, &phi_bb175_12, &phi_bb175_21, &phi_bb175_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb182_6;
  TNode<Smi> phi_bb182_7;
  TNode<Smi> phi_bb182_12;
  TNode<Smi> phi_bb182_21;
  TNode<Smi> phi_bb182_22;
  TNode<Smi> phi_bb182_29;
  TNode<Smi> phi_bb182_30;
  TNode<IntPtrT> tmp286;
  TNode<IntPtrT> tmp287;
  TNode<Union<HeapObject, TaggedIndex>> tmp288;
  TNode<IntPtrT> tmp289;
  TNode<Object> tmp290;
  TNode<Smi> tmp291;
  TNode<Smi> tmp292;
  TNode<Smi> tmp293;
  TNode<BoolT> tmp294;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_6, &phi_bb182_7, &phi_bb182_12, &phi_bb182_21, &phi_bb182_22, &phi_bb182_29, &phi_bb182_30);
    tmp286 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp282});
    tmp287 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp278}, TNode<IntPtrT>{tmp286});
    std::tie(tmp288, tmp289) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp277}, TNode<IntPtrT>{tmp287}).Flatten();
    tmp290 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp288, tmp289});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp275, tmp276}, tmp290);
    tmp291 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp292 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb182_6}, TNode<Smi>{tmp291});
    tmp293 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp294 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp292}, TNode<Smi>{tmp293});
    ca_.Branch(tmp294, &block186, std::vector<compiler::Node*>{phi_bb182_7, phi_bb182_12}, &block187, std::vector<compiler::Node*>{phi_bb182_7, phi_bb182_12});
  }

  TNode<Smi> phi_bb183_6;
  TNode<Smi> phi_bb183_7;
  TNode<Smi> phi_bb183_12;
  TNode<Smi> phi_bb183_21;
  TNode<Smi> phi_bb183_22;
  TNode<Smi> phi_bb183_29;
  TNode<Smi> phi_bb183_30;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_6, &phi_bb183_7, &phi_bb183_12, &phi_bb183_21, &phi_bb183_22, &phi_bb183_29, &phi_bb183_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb186_7;
  TNode<Smi> phi_bb186_12;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_7, &phi_bb186_12);
    ca_.Goto(&block31, tmp292, phi_bb186_7, tmp268, tmp281, phi_bb186_12);
  }

  TNode<Smi> phi_bb187_7;
  TNode<Smi> phi_bb187_12;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_7, &phi_bb187_12);
    ca_.Goto(&block110, tmp292, phi_bb187_7, tmp268, tmp281, phi_bb187_12, tmp179, tmp195, tmp253, tmp170);
  }

  TNode<Smi> phi_bb109_6;
  TNode<Smi> phi_bb109_7;
  TNode<Smi> phi_bb109_10;
  TNode<Smi> phi_bb109_11;
  TNode<Smi> phi_bb109_12;
  TNode<Smi> phi_bb109_13;
  TNode<Smi> phi_bb109_14;
  TNode<Smi> phi_bb109_15;
  TNode<BoolT> phi_bb109_16;
  TNode<Smi> tmp295;
  TNode<Smi> tmp296;
  TNode<IntPtrT> tmp297;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_6, &phi_bb109_7, &phi_bb109_10, &phi_bb109_11, &phi_bb109_12, &phi_bb109_13, &phi_bb109_14, &phi_bb109_15, &phi_bb109_16);
    tmp295 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp296 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb109_13}, TNode<Smi>{tmp295});
    tmp297 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp297}, tmp296);
    ca_.Goto(&block40, phi_bb109_6, phi_bb109_7, phi_bb109_10, phi_bb109_11, phi_bb109_12, tmp296);
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_10;
  TNode<Smi> phi_bb39_11;
  TNode<Smi> phi_bb39_12;
  TNode<Smi> phi_bb39_13;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_7, &phi_bb39_10, &phi_bb39_11, &phi_bb39_12, &phi_bb39_13);
    ca_.Goto(&block32, phi_bb39_6, phi_bb39_7, phi_bb39_10, phi_bb39_11, phi_bb39_12);
  }

  TNode<Smi> phi_bb33_6;
  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_10;
  TNode<Smi> phi_bb33_11;
  TNode<Smi> phi_bb33_12;
  TNode<Smi> tmp298;
  TNode<BoolT> tmp299;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_6, &phi_bb33_7, &phi_bb33_10, &phi_bb33_11, &phi_bb33_12);
    tmp298 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp299 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb33_6}, TNode<Smi>{tmp298});
    ca_.Branch(tmp299, &block188, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7, phi_bb33_10, phi_bb33_11, phi_bb33_12}, &block189, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7, phi_bb33_10, phi_bb33_11, phi_bb33_12});
  }

  TNode<Smi> phi_bb188_6;
  TNode<Smi> phi_bb188_7;
  TNode<Smi> phi_bb188_10;
  TNode<Smi> phi_bb188_11;
  TNode<Smi> phi_bb188_12;
  TNode<JSAny> tmp300;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_6, &phi_bb188_7, &phi_bb188_10, &phi_bb188_11, &phi_bb188_12);
    tmp300 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp14, phi_bb188_11, tmp13, phi_bb188_10, phi_bb188_6);
    ca_.Goto(&block189, phi_bb188_6, phi_bb188_7, phi_bb188_10, phi_bb188_11, phi_bb188_12);
  }

  TNode<Smi> phi_bb189_6;
  TNode<Smi> phi_bb189_7;
  TNode<Smi> phi_bb189_10;
  TNode<Smi> phi_bb189_11;
  TNode<Smi> phi_bb189_12;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_6, &phi_bb189_7, &phi_bb189_10, &phi_bb189_11, &phi_bb189_12);
    ca_.Goto(&block32, phi_bb189_6, phi_bb189_7, phi_bb189_10, phi_bb189_11, phi_bb189_12);
  }

  TNode<Smi> phi_bb32_6;
  TNode<Smi> phi_bb32_7;
  TNode<Smi> phi_bb32_10;
  TNode<Smi> phi_bb32_11;
  TNode<Smi> phi_bb32_12;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_6, &phi_bb32_7, &phi_bb32_10, &phi_bb32_11, &phi_bb32_12);
    ca_.Goto(&block30, phi_bb32_6, phi_bb32_7, phi_bb32_10, phi_bb32_11, phi_bb32_12);
  }

  TNode<Smi> phi_bb31_6;
  TNode<Smi> phi_bb31_7;
  TNode<Smi> phi_bb31_10;
  TNode<Smi> phi_bb31_11;
  TNode<Smi> phi_bb31_12;
  TNode<Smi> tmp301;
  TNode<BoolT> tmp302;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_6, &phi_bb31_7, &phi_bb31_10, &phi_bb31_11, &phi_bb31_12);
    tmp301 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp302 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb31_6}, TNode<Smi>{tmp301});
    ca_.Branch(tmp302, &block192, std::vector<compiler::Node*>{phi_bb31_6, phi_bb31_7, phi_bb31_10, phi_bb31_11, phi_bb31_12}, &block193, std::vector<compiler::Node*>{phi_bb31_6, phi_bb31_7, phi_bb31_10, phi_bb31_11, phi_bb31_12});
  }

  TNode<Smi> phi_bb192_6;
  TNode<Smi> phi_bb192_7;
  TNode<Smi> phi_bb192_10;
  TNode<Smi> phi_bb192_11;
  TNode<Smi> phi_bb192_12;
  TNode<Smi> tmp303;
  TNode<BoolT> tmp304;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_6, &phi_bb192_7, &phi_bb192_10, &phi_bb192_11, &phi_bb192_12);
    tmp303 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp304 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb192_7}, TNode<Smi>{tmp303});
    ca_.Goto(&block194, phi_bb192_6, phi_bb192_7, phi_bb192_10, phi_bb192_11, phi_bb192_12, tmp304);
  }

  TNode<Smi> phi_bb193_6;
  TNode<Smi> phi_bb193_7;
  TNode<Smi> phi_bb193_10;
  TNode<Smi> phi_bb193_11;
  TNode<Smi> phi_bb193_12;
  TNode<BoolT> tmp305;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_6, &phi_bb193_7, &phi_bb193_10, &phi_bb193_11, &phi_bb193_12);
    tmp305 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block194, phi_bb193_6, phi_bb193_7, phi_bb193_10, phi_bb193_11, phi_bb193_12, tmp305);
  }

  TNode<Smi> phi_bb194_6;
  TNode<Smi> phi_bb194_7;
  TNode<Smi> phi_bb194_10;
  TNode<Smi> phi_bb194_11;
  TNode<Smi> phi_bb194_12;
  TNode<BoolT> phi_bb194_14;
  if (block194.is_used()) {
    ca_.Bind(&block194, &phi_bb194_6, &phi_bb194_7, &phi_bb194_10, &phi_bb194_11, &phi_bb194_12, &phi_bb194_14);
    ca_.Branch(phi_bb194_14, &block190, std::vector<compiler::Node*>{phi_bb194_6, phi_bb194_7, phi_bb194_10, phi_bb194_11, phi_bb194_12}, &block191, std::vector<compiler::Node*>{phi_bb194_6, phi_bb194_7, phi_bb194_10, phi_bb194_11, phi_bb194_12});
  }

  TNode<Smi> phi_bb191_6;
  TNode<Smi> phi_bb191_7;
  TNode<Smi> phi_bb191_10;
  TNode<Smi> phi_bb191_11;
  TNode<Smi> phi_bb191_12;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_6, &phi_bb191_7, &phi_bb191_10, &phi_bb191_11, &phi_bb191_12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1100});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA == 1 && lengthB > 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb190_6;
  TNode<Smi> phi_bb190_7;
  TNode<Smi> phi_bb190_10;
  TNode<Smi> phi_bb190_11;
  TNode<Smi> phi_bb190_12;
  TNode<JSAny> tmp306;
  TNode<Union<HeapObject, TaggedIndex>> tmp307;
  TNode<IntPtrT> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<Smi> tmp310;
  TNode<IntPtrT> tmp311;
  TNode<UintPtrT> tmp312;
  TNode<UintPtrT> tmp313;
  TNode<BoolT> tmp314;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_6, &phi_bb190_7, &phi_bb190_10, &phi_bb190_11, &phi_bb190_12);
    tmp306 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp13, phi_bb190_12, tmp13, phi_bb190_10, phi_bb190_7);
    std::tie(tmp307, tmp308, tmp309) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp310 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb190_10}, TNode<Smi>{phi_bb190_7});
    tmp311 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp310});
    tmp312 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp311});
    tmp313 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp309});
    tmp314 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp312}, TNode<UintPtrT>{tmp313});
    ca_.Branch(tmp314, &block199, std::vector<compiler::Node*>{phi_bb190_6, phi_bb190_7, phi_bb190_10, phi_bb190_11, phi_bb190_12}, &block200, std::vector<compiler::Node*>{phi_bb190_6, phi_bb190_7, phi_bb190_10, phi_bb190_11, phi_bb190_12});
  }

  TNode<Smi> phi_bb199_6;
  TNode<Smi> phi_bb199_7;
  TNode<Smi> phi_bb199_10;
  TNode<Smi> phi_bb199_11;
  TNode<Smi> phi_bb199_12;
  TNode<IntPtrT> tmp315;
  TNode<IntPtrT> tmp316;
  TNode<Union<HeapObject, TaggedIndex>> tmp317;
  TNode<IntPtrT> tmp318;
  TNode<Union<HeapObject, TaggedIndex>> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<IntPtrT> tmp321;
  TNode<IntPtrT> tmp322;
  TNode<UintPtrT> tmp323;
  TNode<UintPtrT> tmp324;
  TNode<BoolT> tmp325;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_6, &phi_bb199_7, &phi_bb199_10, &phi_bb199_11, &phi_bb199_12);
    tmp315 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp311});
    tmp316 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp308}, TNode<IntPtrT>{tmp315});
    std::tie(tmp317, tmp318) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp307}, TNode<IntPtrT>{tmp316}).Flatten();
    std::tie(tmp319, tmp320, tmp321) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp322 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb199_11});
    tmp323 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp322});
    tmp324 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp321});
    tmp325 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp323}, TNode<UintPtrT>{tmp324});
    ca_.Branch(tmp325, &block207, std::vector<compiler::Node*>{phi_bb199_6, phi_bb199_7, phi_bb199_10, phi_bb199_11, phi_bb199_12, phi_bb199_11, phi_bb199_11}, &block208, std::vector<compiler::Node*>{phi_bb199_6, phi_bb199_7, phi_bb199_10, phi_bb199_11, phi_bb199_12, phi_bb199_11, phi_bb199_11});
  }

  TNode<Smi> phi_bb200_6;
  TNode<Smi> phi_bb200_7;
  TNode<Smi> phi_bb200_10;
  TNode<Smi> phi_bb200_11;
  TNode<Smi> phi_bb200_12;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_6, &phi_bb200_7, &phi_bb200_10, &phi_bb200_11, &phi_bb200_12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb207_6;
  TNode<Smi> phi_bb207_7;
  TNode<Smi> phi_bb207_10;
  TNode<Smi> phi_bb207_11;
  TNode<Smi> phi_bb207_12;
  TNode<Smi> phi_bb207_25;
  TNode<Smi> phi_bb207_26;
  TNode<IntPtrT> tmp326;
  TNode<IntPtrT> tmp327;
  TNode<Union<HeapObject, TaggedIndex>> tmp328;
  TNode<IntPtrT> tmp329;
  TNode<Object> tmp330;
  if (block207.is_used()) {
    ca_.Bind(&block207, &phi_bb207_6, &phi_bb207_7, &phi_bb207_10, &phi_bb207_11, &phi_bb207_12, &phi_bb207_25, &phi_bb207_26);
    tmp326 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp322});
    tmp327 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp320}, TNode<IntPtrT>{tmp326});
    std::tie(tmp328, tmp329) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp319}, TNode<IntPtrT>{tmp327}).Flatten();
    tmp330 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp328, tmp329});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp317, tmp318}, tmp330);
    ca_.Goto(&block30, phi_bb207_6, phi_bb207_7, phi_bb207_10, phi_bb207_11, phi_bb207_12);
  }

  TNode<Smi> phi_bb208_6;
  TNode<Smi> phi_bb208_7;
  TNode<Smi> phi_bb208_10;
  TNode<Smi> phi_bb208_11;
  TNode<Smi> phi_bb208_12;
  TNode<Smi> phi_bb208_25;
  TNode<Smi> phi_bb208_26;
  if (block208.is_used()) {
    ca_.Bind(&block208, &phi_bb208_6, &phi_bb208_7, &phi_bb208_10, &phi_bb208_11, &phi_bb208_12, &phi_bb208_25, &phi_bb208_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb30_6;
  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_10;
  TNode<Smi> phi_bb30_11;
  TNode<Smi> phi_bb30_12;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_6, &phi_bb30_7, &phi_bb30_10, &phi_bb30_11, &phi_bb30_12);
    ca_.Goto(&block211);
  }

    ca_.Bind(&block211);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1111&c=1
void MergeHigh_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_baseA, TNode<Smi> p_lengthAArg, TNode<Smi> p_baseB, TNode<Smi> p_lengthBArg) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block84(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block85(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block100(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block114(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT, BoolT> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block118(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block131(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block133(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block140(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block148(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block152(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block153(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block158(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block163(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block164(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block168(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block165(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block174(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi> block183(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block187(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi, Smi, Smi, BoolT> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block188(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block191(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block189(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block194(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, BoolT> block196(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block193(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block201(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi> block202(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block209(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block210(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block213(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp0}, TNode<Smi>{p_lengthAArg});
    ca_.Branch(tmp1, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp2;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp2}, TNode<Smi>{p_lengthBArg});
    ca_.Goto(&block6, tmp3);
  }

  TNode<BoolT> tmp4;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block6, tmp4);
  }

  TNode<BoolT> phi_bb6_7;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7);
    ca_.Branch(phi_bb6_7, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1114});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 < lengthAArg && 0 < lengthBArg' failed", pos_stack);
    }
  }

  TNode<Smi> tmp5;
  TNode<BoolT> tmp6;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp5}, TNode<Smi>{p_baseA});
    ca_.Branch(tmp6, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp7;
  TNode<BoolT> tmp8;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp7 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp8 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp7}, TNode<Smi>{p_baseB});
    ca_.Goto(&block11, tmp8);
  }

  TNode<BoolT> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block11, tmp9);
  }

  TNode<BoolT> phi_bb11_7;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_7);
    ca_.Branch(phi_bb11_7, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1115});
      CodeStubAssembler(state_).FailAssert("Torque assert '0 <= baseA && 0 < baseB' failed", pos_stack);
    }
  }

  TNode<Smi> tmp10;
  TNode<BoolT> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseA}, TNode<Smi>{p_lengthAArg});
    tmp11 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp10}, TNode<Smi>{p_baseB});
    ca_.Branch(tmp11, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1116});
      CodeStubAssembler(state_).FailAssert("Torque assert 'baseA + lengthAArg == baseB' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp12;
  TNode<FixedArray> tmp13;
  TNode<FixedArray> tmp14;
  TNode<Smi> tmp15;
  TNode<JSAny> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<Smi> tmp23;
  TNode<Smi> tmp24;
  TNode<Union<HeapObject, TaggedIndex>> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<Smi> tmp28;
  TNode<Smi> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<UintPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<BoolT> tmp33;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp13 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp12});
    tmp14 = GetTempArray_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{p_lengthBArg});
    tmp15 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp13, p_baseB, tmp14, tmp15, p_lengthBArg);
    tmp17 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseB}, TNode<Smi>{p_lengthBArg});
    tmp18 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp19 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp17}, TNode<Smi>{tmp18});
    tmp20 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp21 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_lengthBArg}, TNode<Smi>{tmp20});
    tmp22 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_baseA}, TNode<Smi>{p_lengthAArg});
    tmp23 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp24 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp22}, TNode<Smi>{tmp23});
    std::tie(tmp25, tmp26, tmp27) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp28 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp29 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp19}, TNode<Smi>{tmp28});
    tmp30 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp19});
    tmp31 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp27});
    tmp33 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp31}, TNode<UintPtrT>{tmp32});
    ca_.Branch(tmp33, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<Union<HeapObject, TaggedIndex>> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<Union<HeapObject, TaggedIndex>> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<Smi> tmp41;
  TNode<Smi> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<UintPtrT> tmp44;
  TNode<UintPtrT> tmp45;
  TNode<BoolT> tmp46;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp34 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp30});
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp26}, TNode<IntPtrT>{tmp34});
    std::tie(tmp36, tmp37) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp25}, TNode<IntPtrT>{tmp35}).Flatten();
    std::tie(tmp38, tmp39, tmp40) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp41 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp42 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp24}, TNode<Smi>{tmp41});
    tmp43 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp24});
    tmp44 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp43});
    tmp45 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp40});
    tmp46 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp44}, TNode<UintPtrT>{tmp45});
    ca_.Branch(tmp46, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  if (block19.is_used()) {
    ca_.Bind(&block19);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<Union<HeapObject, TaggedIndex>> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<Object> tmp51;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  TNode<Smi> tmp54;
  TNode<BoolT> tmp55;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp47 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp43});
    tmp48 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp39}, TNode<IntPtrT>{tmp47});
    std::tie(tmp49, tmp50) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp38}, TNode<IntPtrT>{tmp48}).Flatten();
    tmp51 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp49, tmp50});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp36, tmp37}, tmp51);
    tmp52 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp53 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{p_lengthAArg}, TNode<Smi>{tmp52});
    tmp54 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp55 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp53}, TNode<Smi>{tmp54});
    ca_.Branch(tmp55, &block34, std::vector<compiler::Node*>{}, &block35, std::vector<compiler::Node*>{});
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    ca_.Goto(&block33, tmp53, p_lengthBArg, tmp29, tmp21, tmp42);
  }

  TNode<Smi> tmp56;
  TNode<BoolT> tmp57;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp56 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp57 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_lengthBArg}, TNode<Smi>{tmp56});
    ca_.Branch(tmp57, &block36, std::vector<compiler::Node*>{}, &block37, std::vector<compiler::Node*>{});
  }

  if (block36.is_used()) {
    ca_.Bind(&block36);
    ca_.Goto(&block31, tmp53, p_lengthBArg, tmp29, tmp21, tmp42);
  }

  TNode<IntPtrT> tmp58;
  TNode<Smi> tmp59;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp58 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp59 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp58});
    ca_.Goto(&block40, tmp53, p_lengthBArg, tmp29, tmp21, tmp42, tmp59);
  }

  TNode<Smi> phi_bb40_6;
  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_10;
  TNode<Smi> phi_bb40_11;
  TNode<Smi> phi_bb40_12;
  TNode<Smi> phi_bb40_13;
  TNode<BoolT> tmp60;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_7, &phi_bb40_10, &phi_bb40_11, &phi_bb40_12, &phi_bb40_13);
    tmp60 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp60, &block38, std::vector<compiler::Node*>{phi_bb40_6, phi_bb40_7, phi_bb40_10, phi_bb40_11, phi_bb40_12, phi_bb40_13}, &block39, std::vector<compiler::Node*>{phi_bb40_6, phi_bb40_7, phi_bb40_10, phi_bb40_11, phi_bb40_12, phi_bb40_13});
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_10;
  TNode<Smi> phi_bb38_11;
  TNode<Smi> phi_bb38_12;
  TNode<Smi> phi_bb38_13;
  TNode<Smi> tmp61;
  TNode<Smi> tmp62;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_7, &phi_bb38_10, &phi_bb38_11, &phi_bb38_12, &phi_bb38_13);
    tmp61 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp62 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block43, phi_bb38_6, phi_bb38_7, phi_bb38_10, phi_bb38_11, phi_bb38_12, phi_bb38_13, tmp61, tmp62);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Smi> phi_bb43_7;
  TNode<Smi> phi_bb43_10;
  TNode<Smi> phi_bb43_11;
  TNode<Smi> phi_bb43_12;
  TNode<Smi> phi_bb43_13;
  TNode<Smi> phi_bb43_14;
  TNode<Smi> phi_bb43_15;
  TNode<BoolT> tmp63;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_7, &phi_bb43_10, &phi_bb43_11, &phi_bb43_12, &phi_bb43_13, &phi_bb43_14, &phi_bb43_15);
    tmp63 = CodeStubAssembler(state_).Int32TrueConstant();
    ca_.Branch(tmp63, &block41, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, phi_bb43_14, phi_bb43_15}, &block42, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, phi_bb43_14, phi_bb43_15});
  }

  TNode<Smi> phi_bb41_6;
  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_10;
  TNode<Smi> phi_bb41_11;
  TNode<Smi> phi_bb41_12;
  TNode<Smi> phi_bb41_13;
  TNode<Smi> phi_bb41_14;
  TNode<Smi> phi_bb41_15;
  TNode<Smi> tmp64;
  TNode<BoolT> tmp65;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_6, &phi_bb41_7, &phi_bb41_10, &phi_bb41_11, &phi_bb41_12, &phi_bb41_13, &phi_bb41_14, &phi_bb41_15);
    tmp64 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp65 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb41_6}, TNode<Smi>{tmp64});
    ca_.Branch(tmp65, &block46, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7, phi_bb41_10, phi_bb41_11, phi_bb41_12, phi_bb41_13, phi_bb41_14, phi_bb41_15}, &block47, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7, phi_bb41_10, phi_bb41_11, phi_bb41_12, phi_bb41_13, phi_bb41_14, phi_bb41_15});
  }

  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_10;
  TNode<Smi> phi_bb46_11;
  TNode<Smi> phi_bb46_12;
  TNode<Smi> phi_bb46_13;
  TNode<Smi> phi_bb46_14;
  TNode<Smi> phi_bb46_15;
  TNode<Smi> tmp66;
  TNode<BoolT> tmp67;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_7, &phi_bb46_10, &phi_bb46_11, &phi_bb46_12, &phi_bb46_13, &phi_bb46_14, &phi_bb46_15);
    tmp66 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp67 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb46_7}, TNode<Smi>{tmp66});
    ca_.Goto(&block48, phi_bb46_6, phi_bb46_7, phi_bb46_10, phi_bb46_11, phi_bb46_12, phi_bb46_13, phi_bb46_14, phi_bb46_15, tmp67);
  }

  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_10;
  TNode<Smi> phi_bb47_11;
  TNode<Smi> phi_bb47_12;
  TNode<Smi> phi_bb47_13;
  TNode<Smi> phi_bb47_14;
  TNode<Smi> phi_bb47_15;
  TNode<BoolT> tmp68;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_6, &phi_bb47_7, &phi_bb47_10, &phi_bb47_11, &phi_bb47_12, &phi_bb47_13, &phi_bb47_14, &phi_bb47_15);
    tmp68 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block48, phi_bb47_6, phi_bb47_7, phi_bb47_10, phi_bb47_11, phi_bb47_12, phi_bb47_13, phi_bb47_14, phi_bb47_15, tmp68);
  }

  TNode<Smi> phi_bb48_6;
  TNode<Smi> phi_bb48_7;
  TNode<Smi> phi_bb48_10;
  TNode<Smi> phi_bb48_11;
  TNode<Smi> phi_bb48_12;
  TNode<Smi> phi_bb48_13;
  TNode<Smi> phi_bb48_14;
  TNode<Smi> phi_bb48_15;
  TNode<BoolT> phi_bb48_17;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_6, &phi_bb48_7, &phi_bb48_10, &phi_bb48_11, &phi_bb48_12, &phi_bb48_13, &phi_bb48_14, &phi_bb48_15, &phi_bb48_17);
    ca_.Branch(phi_bb48_17, &block44, std::vector<compiler::Node*>{phi_bb48_6, phi_bb48_7, phi_bb48_10, phi_bb48_11, phi_bb48_12, phi_bb48_13, phi_bb48_14, phi_bb48_15}, &block45, std::vector<compiler::Node*>{phi_bb48_6, phi_bb48_7, phi_bb48_10, phi_bb48_11, phi_bb48_12, phi_bb48_13, phi_bb48_14, phi_bb48_15});
  }

  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_10;
  TNode<Smi> phi_bb45_11;
  TNode<Smi> phi_bb45_12;
  TNode<Smi> phi_bb45_13;
  TNode<Smi> phi_bb45_14;
  TNode<Smi> phi_bb45_15;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_6, &phi_bb45_7, &phi_bb45_10, &phi_bb45_11, &phi_bb45_12, &phi_bb45_13, &phi_bb45_14, &phi_bb45_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1148});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA > 0 && lengthB > 1' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb44_6;
  TNode<Smi> phi_bb44_7;
  TNode<Smi> phi_bb44_10;
  TNode<Smi> phi_bb44_11;
  TNode<Smi> phi_bb44_12;
  TNode<Smi> phi_bb44_13;
  TNode<Smi> phi_bb44_14;
  TNode<Smi> phi_bb44_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<UintPtrT> tmp73;
  TNode<UintPtrT> tmp74;
  TNode<BoolT> tmp75;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_6, &phi_bb44_7, &phi_bb44_10, &phi_bb44_11, &phi_bb44_12, &phi_bb44_13, &phi_bb44_14, &phi_bb44_15);
    std::tie(tmp69, tmp70, tmp71) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp72 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb44_11});
    tmp73 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp72});
    tmp74 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp71});
    tmp75 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp73}, TNode<UintPtrT>{tmp74});
    ca_.Branch(tmp75, &block53, std::vector<compiler::Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13, phi_bb44_14, phi_bb44_15, phi_bb44_11, phi_bb44_11}, &block54, std::vector<compiler::Node*>{phi_bb44_6, phi_bb44_7, phi_bb44_10, phi_bb44_11, phi_bb44_12, phi_bb44_13, phi_bb44_14, phi_bb44_15, phi_bb44_11, phi_bb44_11});
  }

  TNode<Smi> phi_bb53_6;
  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_10;
  TNode<Smi> phi_bb53_11;
  TNode<Smi> phi_bb53_12;
  TNode<Smi> phi_bb53_13;
  TNode<Smi> phi_bb53_14;
  TNode<Smi> phi_bb53_15;
  TNode<Smi> phi_bb53_21;
  TNode<Smi> phi_bb53_22;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<Union<HeapObject, TaggedIndex>> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<Object> tmp80;
  TNode<JSAny> tmp81;
  TNode<Union<HeapObject, TaggedIndex>> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<IntPtrT> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<UintPtrT> tmp86;
  TNode<UintPtrT> tmp87;
  TNode<BoolT> tmp88;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_6, &phi_bb53_7, &phi_bb53_10, &phi_bb53_11, &phi_bb53_12, &phi_bb53_13, &phi_bb53_14, &phi_bb53_15, &phi_bb53_21, &phi_bb53_22);
    tmp76 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp72});
    tmp77 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp70}, TNode<IntPtrT>{tmp76});
    std::tie(tmp78, tmp79) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp69}, TNode<IntPtrT>{tmp77}).Flatten();
    tmp80 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp78, tmp79});
    tmp81 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp80});
    std::tie(tmp82, tmp83, tmp84) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp85 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb53_12});
    tmp86 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp85});
    tmp87 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp84});
    tmp88 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp86}, TNode<UintPtrT>{tmp87});
    ca_.Branch(tmp88, &block61, std::vector<compiler::Node*>{phi_bb53_6, phi_bb53_7, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13, phi_bb53_14, phi_bb53_15, phi_bb53_12, phi_bb53_12}, &block62, std::vector<compiler::Node*>{phi_bb53_6, phi_bb53_7, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13, phi_bb53_14, phi_bb53_15, phi_bb53_12, phi_bb53_12});
  }

  TNode<Smi> phi_bb54_6;
  TNode<Smi> phi_bb54_7;
  TNode<Smi> phi_bb54_10;
  TNode<Smi> phi_bb54_11;
  TNode<Smi> phi_bb54_12;
  TNode<Smi> phi_bb54_13;
  TNode<Smi> phi_bb54_14;
  TNode<Smi> phi_bb54_15;
  TNode<Smi> phi_bb54_21;
  TNode<Smi> phi_bb54_22;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_6, &phi_bb54_7, &phi_bb54_10, &phi_bb54_11, &phi_bb54_12, &phi_bb54_13, &phi_bb54_14, &phi_bb54_15, &phi_bb54_21, &phi_bb54_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb61_6;
  TNode<Smi> phi_bb61_7;
  TNode<Smi> phi_bb61_10;
  TNode<Smi> phi_bb61_11;
  TNode<Smi> phi_bb61_12;
  TNode<Smi> phi_bb61_13;
  TNode<Smi> phi_bb61_14;
  TNode<Smi> phi_bb61_15;
  TNode<Smi> phi_bb61_22;
  TNode<Smi> phi_bb61_23;
  TNode<IntPtrT> tmp89;
  TNode<IntPtrT> tmp90;
  TNode<Union<HeapObject, TaggedIndex>> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<Object> tmp93;
  TNode<JSAny> tmp94;
  TNode<Number> tmp95;
  TNode<Number> tmp96;
  TNode<BoolT> tmp97;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_6, &phi_bb61_7, &phi_bb61_10, &phi_bb61_11, &phi_bb61_12, &phi_bb61_13, &phi_bb61_14, &phi_bb61_15, &phi_bb61_22, &phi_bb61_23);
    tmp89 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp85});
    tmp90 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp83}, TNode<IntPtrT>{tmp89});
    std::tie(tmp91, tmp92) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp82}, TNode<IntPtrT>{tmp90}).Flatten();
    tmp93 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp91, tmp92});
    tmp94 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp93});
    tmp95 = Compare_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<JSAny>{tmp81}, TNode<JSAny>{tmp94});
    tmp96 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp97 = NumberIsLessThan_0(state_, TNode<Number>{tmp95}, TNode<Number>{tmp96});
    ca_.Branch(tmp97, &block65, std::vector<compiler::Node*>{phi_bb61_6, phi_bb61_7, phi_bb61_10, phi_bb61_11, phi_bb61_12, phi_bb61_13, phi_bb61_14, phi_bb61_15}, &block66, std::vector<compiler::Node*>{phi_bb61_6, phi_bb61_7, phi_bb61_10, phi_bb61_11, phi_bb61_12, phi_bb61_13, phi_bb61_14, phi_bb61_15});
  }

  TNode<Smi> phi_bb62_6;
  TNode<Smi> phi_bb62_7;
  TNode<Smi> phi_bb62_10;
  TNode<Smi> phi_bb62_11;
  TNode<Smi> phi_bb62_12;
  TNode<Smi> phi_bb62_13;
  TNode<Smi> phi_bb62_14;
  TNode<Smi> phi_bb62_15;
  TNode<Smi> phi_bb62_22;
  TNode<Smi> phi_bb62_23;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_6, &phi_bb62_7, &phi_bb62_10, &phi_bb62_11, &phi_bb62_12, &phi_bb62_13, &phi_bb62_14, &phi_bb62_15, &phi_bb62_22, &phi_bb62_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb65_6;
  TNode<Smi> phi_bb65_7;
  TNode<Smi> phi_bb65_10;
  TNode<Smi> phi_bb65_11;
  TNode<Smi> phi_bb65_12;
  TNode<Smi> phi_bb65_13;
  TNode<Smi> phi_bb65_14;
  TNode<Smi> phi_bb65_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<Smi> tmp101;
  TNode<Smi> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<UintPtrT> tmp104;
  TNode<UintPtrT> tmp105;
  TNode<BoolT> tmp106;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_6, &phi_bb65_7, &phi_bb65_10, &phi_bb65_11, &phi_bb65_12, &phi_bb65_13, &phi_bb65_14, &phi_bb65_15);
    std::tie(tmp98, tmp99, tmp100) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp101 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp102 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb65_10}, TNode<Smi>{tmp101});
    tmp103 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb65_10});
    tmp104 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp103});
    tmp105 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp100});
    tmp106 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp104}, TNode<UintPtrT>{tmp105});
    ca_.Branch(tmp106, &block72, std::vector<compiler::Node*>{phi_bb65_6, phi_bb65_7, phi_bb65_11, phi_bb65_12, phi_bb65_13, phi_bb65_14, phi_bb65_15, phi_bb65_10, phi_bb65_10}, &block73, std::vector<compiler::Node*>{phi_bb65_6, phi_bb65_7, phi_bb65_11, phi_bb65_12, phi_bb65_13, phi_bb65_14, phi_bb65_15, phi_bb65_10, phi_bb65_10});
  }

  TNode<Smi> phi_bb72_6;
  TNode<Smi> phi_bb72_7;
  TNode<Smi> phi_bb72_11;
  TNode<Smi> phi_bb72_12;
  TNode<Smi> phi_bb72_13;
  TNode<Smi> phi_bb72_14;
  TNode<Smi> phi_bb72_15;
  TNode<Smi> phi_bb72_21;
  TNode<Smi> phi_bb72_22;
  TNode<IntPtrT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<Union<HeapObject, TaggedIndex>> tmp109;
  TNode<IntPtrT> tmp110;
  TNode<Union<HeapObject, TaggedIndex>> tmp111;
  TNode<IntPtrT> tmp112;
  TNode<IntPtrT> tmp113;
  TNode<Smi> tmp114;
  TNode<Smi> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<UintPtrT> tmp117;
  TNode<UintPtrT> tmp118;
  TNode<BoolT> tmp119;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_6, &phi_bb72_7, &phi_bb72_11, &phi_bb72_12, &phi_bb72_13, &phi_bb72_14, &phi_bb72_15, &phi_bb72_21, &phi_bb72_22);
    tmp107 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp103});
    tmp108 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp99}, TNode<IntPtrT>{tmp107});
    std::tie(tmp109, tmp110) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp98}, TNode<IntPtrT>{tmp108}).Flatten();
    std::tie(tmp111, tmp112, tmp113) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp114 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp115 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb72_12}, TNode<Smi>{tmp114});
    tmp116 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb72_12});
    tmp117 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp116});
    tmp118 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp113});
    tmp119 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp117}, TNode<UintPtrT>{tmp118});
    ca_.Branch(tmp119, &block80, std::vector<compiler::Node*>{phi_bb72_6, phi_bb72_7, phi_bb72_11, phi_bb72_13, phi_bb72_14, phi_bb72_15, phi_bb72_21, phi_bb72_22, phi_bb72_12, phi_bb72_12}, &block81, std::vector<compiler::Node*>{phi_bb72_6, phi_bb72_7, phi_bb72_11, phi_bb72_13, phi_bb72_14, phi_bb72_15, phi_bb72_21, phi_bb72_22, phi_bb72_12, phi_bb72_12});
  }

  TNode<Smi> phi_bb73_6;
  TNode<Smi> phi_bb73_7;
  TNode<Smi> phi_bb73_11;
  TNode<Smi> phi_bb73_12;
  TNode<Smi> phi_bb73_13;
  TNode<Smi> phi_bb73_14;
  TNode<Smi> phi_bb73_15;
  TNode<Smi> phi_bb73_21;
  TNode<Smi> phi_bb73_22;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_6, &phi_bb73_7, &phi_bb73_11, &phi_bb73_12, &phi_bb73_13, &phi_bb73_14, &phi_bb73_15, &phi_bb73_21, &phi_bb73_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb80_6;
  TNode<Smi> phi_bb80_7;
  TNode<Smi> phi_bb80_11;
  TNode<Smi> phi_bb80_13;
  TNode<Smi> phi_bb80_14;
  TNode<Smi> phi_bb80_15;
  TNode<Smi> phi_bb80_21;
  TNode<Smi> phi_bb80_22;
  TNode<Smi> phi_bb80_29;
  TNode<Smi> phi_bb80_30;
  TNode<IntPtrT> tmp120;
  TNode<IntPtrT> tmp121;
  TNode<Union<HeapObject, TaggedIndex>> tmp122;
  TNode<IntPtrT> tmp123;
  TNode<Object> tmp124;
  TNode<Smi> tmp125;
  TNode<Smi> tmp126;
  TNode<Smi> tmp127;
  TNode<Smi> tmp128;
  TNode<Smi> tmp129;
  TNode<Smi> tmp130;
  TNode<BoolT> tmp131;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_6, &phi_bb80_7, &phi_bb80_11, &phi_bb80_13, &phi_bb80_14, &phi_bb80_15, &phi_bb80_21, &phi_bb80_22, &phi_bb80_29, &phi_bb80_30);
    tmp120 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp116});
    tmp121 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp112}, TNode<IntPtrT>{tmp120});
    std::tie(tmp122, tmp123) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp111}, TNode<IntPtrT>{tmp121}).Flatten();
    tmp124 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp122, tmp123});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp109, tmp110}, tmp124);
    tmp125 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp126 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb80_14}, TNode<Smi>{tmp125});
    tmp127 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp128 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb80_6}, TNode<Smi>{tmp127});
    tmp129 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp130 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp131 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp128}, TNode<Smi>{tmp130});
    ca_.Branch(tmp131, &block84, std::vector<compiler::Node*>{phi_bb80_7, phi_bb80_11, phi_bb80_13}, &block85, std::vector<compiler::Node*>{phi_bb80_7, phi_bb80_11, phi_bb80_13});
  }

  TNode<Smi> phi_bb81_6;
  TNode<Smi> phi_bb81_7;
  TNode<Smi> phi_bb81_11;
  TNode<Smi> phi_bb81_13;
  TNode<Smi> phi_bb81_14;
  TNode<Smi> phi_bb81_15;
  TNode<Smi> phi_bb81_21;
  TNode<Smi> phi_bb81_22;
  TNode<Smi> phi_bb81_29;
  TNode<Smi> phi_bb81_30;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_6, &phi_bb81_7, &phi_bb81_11, &phi_bb81_13, &phi_bb81_14, &phi_bb81_15, &phi_bb81_21, &phi_bb81_22, &phi_bb81_29, &phi_bb81_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb84_7;
  TNode<Smi> phi_bb84_11;
  TNode<Smi> phi_bb84_13;
  if (block84.is_used()) {
    ca_.Bind(&block84, &phi_bb84_7, &phi_bb84_11, &phi_bb84_13);
    ca_.Goto(&block33, tmp128, phi_bb84_7, tmp102, phi_bb84_11, tmp115);
  }

  TNode<Smi> phi_bb85_7;
  TNode<Smi> phi_bb85_11;
  TNode<Smi> phi_bb85_13;
  TNode<BoolT> tmp132;
  if (block85.is_used()) {
    ca_.Bind(&block85, &phi_bb85_7, &phi_bb85_11, &phi_bb85_13);
    tmp132 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp126}, TNode<Smi>{phi_bb85_13});
    ca_.Branch(tmp132, &block86, std::vector<compiler::Node*>{phi_bb85_7, phi_bb85_11, phi_bb85_13}, &block87, std::vector<compiler::Node*>{phi_bb85_7, phi_bb85_11, phi_bb85_13});
  }

  TNode<Smi> phi_bb86_7;
  TNode<Smi> phi_bb86_11;
  TNode<Smi> phi_bb86_13;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_7, &phi_bb86_11, &phi_bb86_13);
    ca_.Goto(&block42, tmp128, phi_bb86_7, tmp102, phi_bb86_11, tmp115, phi_bb86_13, tmp126, tmp129);
  }

  TNode<Smi> phi_bb87_7;
  TNode<Smi> phi_bb87_11;
  TNode<Smi> phi_bb87_13;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_7, &phi_bb87_11, &phi_bb87_13);
    ca_.Goto(&block67, tmp128, phi_bb87_7, tmp102, phi_bb87_11, tmp115, phi_bb87_13, tmp126, tmp129);
  }

  TNode<Smi> phi_bb66_6;
  TNode<Smi> phi_bb66_7;
  TNode<Smi> phi_bb66_10;
  TNode<Smi> phi_bb66_11;
  TNode<Smi> phi_bb66_12;
  TNode<Smi> phi_bb66_13;
  TNode<Smi> phi_bb66_14;
  TNode<Smi> phi_bb66_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp133;
  TNode<IntPtrT> tmp134;
  TNode<IntPtrT> tmp135;
  TNode<Smi> tmp136;
  TNode<Smi> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<UintPtrT> tmp139;
  TNode<UintPtrT> tmp140;
  TNode<BoolT> tmp141;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_6, &phi_bb66_7, &phi_bb66_10, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13, &phi_bb66_14, &phi_bb66_15);
    std::tie(tmp133, tmp134, tmp135) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp136 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp137 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb66_10}, TNode<Smi>{tmp136});
    tmp138 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb66_10});
    tmp139 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp138});
    tmp140 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp135});
    tmp141 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp139}, TNode<UintPtrT>{tmp140});
    ca_.Branch(tmp141, &block92, std::vector<compiler::Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15, phi_bb66_10, phi_bb66_10}, &block93, std::vector<compiler::Node*>{phi_bb66_6, phi_bb66_7, phi_bb66_11, phi_bb66_12, phi_bb66_13, phi_bb66_14, phi_bb66_15, phi_bb66_10, phi_bb66_10});
  }

  TNode<Smi> phi_bb92_6;
  TNode<Smi> phi_bb92_7;
  TNode<Smi> phi_bb92_11;
  TNode<Smi> phi_bb92_12;
  TNode<Smi> phi_bb92_13;
  TNode<Smi> phi_bb92_14;
  TNode<Smi> phi_bb92_15;
  TNode<Smi> phi_bb92_21;
  TNode<Smi> phi_bb92_22;
  TNode<IntPtrT> tmp142;
  TNode<IntPtrT> tmp143;
  TNode<Union<HeapObject, TaggedIndex>> tmp144;
  TNode<IntPtrT> tmp145;
  TNode<Union<HeapObject, TaggedIndex>> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<IntPtrT> tmp148;
  TNode<Smi> tmp149;
  TNode<Smi> tmp150;
  TNode<IntPtrT> tmp151;
  TNode<UintPtrT> tmp152;
  TNode<UintPtrT> tmp153;
  TNode<BoolT> tmp154;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_6, &phi_bb92_7, &phi_bb92_11, &phi_bb92_12, &phi_bb92_13, &phi_bb92_14, &phi_bb92_15, &phi_bb92_21, &phi_bb92_22);
    tmp142 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp138});
    tmp143 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp134}, TNode<IntPtrT>{tmp142});
    std::tie(tmp144, tmp145) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp133}, TNode<IntPtrT>{tmp143}).Flatten();
    std::tie(tmp146, tmp147, tmp148) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp149 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp150 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb92_11}, TNode<Smi>{tmp149});
    tmp151 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb92_11});
    tmp152 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp151});
    tmp153 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp148});
    tmp154 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp152}, TNode<UintPtrT>{tmp153});
    ca_.Branch(tmp154, &block100, std::vector<compiler::Node*>{phi_bb92_6, phi_bb92_7, phi_bb92_12, phi_bb92_13, phi_bb92_14, phi_bb92_15, phi_bb92_21, phi_bb92_22, phi_bb92_11, phi_bb92_11}, &block101, std::vector<compiler::Node*>{phi_bb92_6, phi_bb92_7, phi_bb92_12, phi_bb92_13, phi_bb92_14, phi_bb92_15, phi_bb92_21, phi_bb92_22, phi_bb92_11, phi_bb92_11});
  }

  TNode<Smi> phi_bb93_6;
  TNode<Smi> phi_bb93_7;
  TNode<Smi> phi_bb93_11;
  TNode<Smi> phi_bb93_12;
  TNode<Smi> phi_bb93_13;
  TNode<Smi> phi_bb93_14;
  TNode<Smi> phi_bb93_15;
  TNode<Smi> phi_bb93_21;
  TNode<Smi> phi_bb93_22;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_6, &phi_bb93_7, &phi_bb93_11, &phi_bb93_12, &phi_bb93_13, &phi_bb93_14, &phi_bb93_15, &phi_bb93_21, &phi_bb93_22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb100_6;
  TNode<Smi> phi_bb100_7;
  TNode<Smi> phi_bb100_12;
  TNode<Smi> phi_bb100_13;
  TNode<Smi> phi_bb100_14;
  TNode<Smi> phi_bb100_15;
  TNode<Smi> phi_bb100_21;
  TNode<Smi> phi_bb100_22;
  TNode<Smi> phi_bb100_29;
  TNode<Smi> phi_bb100_30;
  TNode<IntPtrT> tmp155;
  TNode<IntPtrT> tmp156;
  TNode<Union<HeapObject, TaggedIndex>> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<Object> tmp159;
  TNode<Smi> tmp160;
  TNode<Smi> tmp161;
  TNode<Smi> tmp162;
  TNode<Smi> tmp163;
  TNode<Smi> tmp164;
  TNode<Smi> tmp165;
  TNode<BoolT> tmp166;
  if (block100.is_used()) {
    ca_.Bind(&block100, &phi_bb100_6, &phi_bb100_7, &phi_bb100_12, &phi_bb100_13, &phi_bb100_14, &phi_bb100_15, &phi_bb100_21, &phi_bb100_22, &phi_bb100_29, &phi_bb100_30);
    tmp155 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp151});
    tmp156 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp147}, TNode<IntPtrT>{tmp155});
    std::tie(tmp157, tmp158) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp146}, TNode<IntPtrT>{tmp156}).Flatten();
    tmp159 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp157, tmp158});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp144, tmp145}, tmp159);
    tmp160 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp161 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb100_15}, TNode<Smi>{tmp160});
    tmp162 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp163 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb100_7}, TNode<Smi>{tmp162});
    tmp164 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp165 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp166 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp163}, TNode<Smi>{tmp165});
    ca_.Branch(tmp166, &block104, std::vector<compiler::Node*>{phi_bb100_6, phi_bb100_12, phi_bb100_13}, &block105, std::vector<compiler::Node*>{phi_bb100_6, phi_bb100_12, phi_bb100_13});
  }

  TNode<Smi> phi_bb101_6;
  TNode<Smi> phi_bb101_7;
  TNode<Smi> phi_bb101_12;
  TNode<Smi> phi_bb101_13;
  TNode<Smi> phi_bb101_14;
  TNode<Smi> phi_bb101_15;
  TNode<Smi> phi_bb101_21;
  TNode<Smi> phi_bb101_22;
  TNode<Smi> phi_bb101_29;
  TNode<Smi> phi_bb101_30;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_6, &phi_bb101_7, &phi_bb101_12, &phi_bb101_13, &phi_bb101_14, &phi_bb101_15, &phi_bb101_21, &phi_bb101_22, &phi_bb101_29, &phi_bb101_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb104_6;
  TNode<Smi> phi_bb104_12;
  TNode<Smi> phi_bb104_13;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_6, &phi_bb104_12, &phi_bb104_13);
    ca_.Goto(&block31, phi_bb104_6, tmp163, tmp137, tmp150, phi_bb104_12);
  }

  TNode<Smi> phi_bb105_6;
  TNode<Smi> phi_bb105_12;
  TNode<Smi> phi_bb105_13;
  TNode<BoolT> tmp167;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_6, &phi_bb105_12, &phi_bb105_13);
    tmp167 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp161}, TNode<Smi>{phi_bb105_13});
    ca_.Branch(tmp167, &block106, std::vector<compiler::Node*>{phi_bb105_6, phi_bb105_12, phi_bb105_13}, &block107, std::vector<compiler::Node*>{phi_bb105_6, phi_bb105_12, phi_bb105_13});
  }

  TNode<Smi> phi_bb106_6;
  TNode<Smi> phi_bb106_12;
  TNode<Smi> phi_bb106_13;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_6, &phi_bb106_12, &phi_bb106_13);
    ca_.Goto(&block42, phi_bb106_6, tmp163, tmp137, tmp150, phi_bb106_12, phi_bb106_13, tmp164, tmp161);
  }

  TNode<Smi> phi_bb107_6;
  TNode<Smi> phi_bb107_12;
  TNode<Smi> phi_bb107_13;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_6, &phi_bb107_12, &phi_bb107_13);
    ca_.Goto(&block67, phi_bb107_6, tmp163, tmp137, tmp150, phi_bb107_12, phi_bb107_13, tmp164, tmp161);
  }

  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_10;
  TNode<Smi> phi_bb67_11;
  TNode<Smi> phi_bb67_12;
  TNode<Smi> phi_bb67_13;
  TNode<Smi> phi_bb67_14;
  TNode<Smi> phi_bb67_15;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_7, &phi_bb67_10, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13, &phi_bb67_14, &phi_bb67_15);
    ca_.Goto(&block43, phi_bb67_6, phi_bb67_7, phi_bb67_10, phi_bb67_11, phi_bb67_12, phi_bb67_13, phi_bb67_14, phi_bb67_15);
  }

  TNode<Smi> phi_bb42_6;
  TNode<Smi> phi_bb42_7;
  TNode<Smi> phi_bb42_10;
  TNode<Smi> phi_bb42_11;
  TNode<Smi> phi_bb42_12;
  TNode<Smi> phi_bb42_13;
  TNode<Smi> phi_bb42_14;
  TNode<Smi> phi_bb42_15;
  TNode<Smi> tmp168;
  TNode<Smi> tmp169;
  TNode<BoolT> tmp170;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_7, &phi_bb42_10, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13, &phi_bb42_14, &phi_bb42_15);
    tmp168 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp169 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb42_13}, TNode<Smi>{tmp168});
    tmp170 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block110, phi_bb42_6, phi_bb42_7, phi_bb42_10, phi_bb42_11, phi_bb42_12, tmp169, phi_bb42_14, phi_bb42_15, tmp170);
  }

  TNode<Smi> phi_bb110_6;
  TNode<Smi> phi_bb110_7;
  TNode<Smi> phi_bb110_10;
  TNode<Smi> phi_bb110_11;
  TNode<Smi> phi_bb110_12;
  TNode<Smi> phi_bb110_13;
  TNode<Smi> phi_bb110_14;
  TNode<Smi> phi_bb110_15;
  TNode<BoolT> phi_bb110_16;
  TNode<Smi> tmp171;
  TNode<BoolT> tmp172;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_6, &phi_bb110_7, &phi_bb110_10, &phi_bb110_11, &phi_bb110_12, &phi_bb110_13, &phi_bb110_14, &phi_bb110_15, &phi_bb110_16);
    tmp171 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp172 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb110_14}, TNode<Smi>{tmp171});
    ca_.Branch(tmp172, &block111, std::vector<compiler::Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16}, &block112, std::vector<compiler::Node*>{phi_bb110_6, phi_bb110_7, phi_bb110_10, phi_bb110_11, phi_bb110_12, phi_bb110_13, phi_bb110_14, phi_bb110_15, phi_bb110_16});
  }

  TNode<Smi> phi_bb111_6;
  TNode<Smi> phi_bb111_7;
  TNode<Smi> phi_bb111_10;
  TNode<Smi> phi_bb111_11;
  TNode<Smi> phi_bb111_12;
  TNode<Smi> phi_bb111_13;
  TNode<Smi> phi_bb111_14;
  TNode<Smi> phi_bb111_15;
  TNode<BoolT> phi_bb111_16;
  TNode<BoolT> tmp173;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_6, &phi_bb111_7, &phi_bb111_10, &phi_bb111_11, &phi_bb111_12, &phi_bb111_13, &phi_bb111_14, &phi_bb111_15, &phi_bb111_16);
    tmp173 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block113, phi_bb111_6, phi_bb111_7, phi_bb111_10, phi_bb111_11, phi_bb111_12, phi_bb111_13, phi_bb111_14, phi_bb111_15, phi_bb111_16, tmp173);
  }

  TNode<Smi> phi_bb112_6;
  TNode<Smi> phi_bb112_7;
  TNode<Smi> phi_bb112_10;
  TNode<Smi> phi_bb112_11;
  TNode<Smi> phi_bb112_12;
  TNode<Smi> phi_bb112_13;
  TNode<Smi> phi_bb112_14;
  TNode<Smi> phi_bb112_15;
  TNode<BoolT> phi_bb112_16;
  TNode<Smi> tmp174;
  TNode<BoolT> tmp175;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_6, &phi_bb112_7, &phi_bb112_10, &phi_bb112_11, &phi_bb112_12, &phi_bb112_13, &phi_bb112_14, &phi_bb112_15, &phi_bb112_16);
    tmp174 = FromConstexpr_Smi_constexpr_int31_0(state_, kMinGallopWins_0(state_));
    tmp175 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb112_15}, TNode<Smi>{tmp174});
    ca_.Goto(&block113, phi_bb112_6, phi_bb112_7, phi_bb112_10, phi_bb112_11, phi_bb112_12, phi_bb112_13, phi_bb112_14, phi_bb112_15, phi_bb112_16, tmp175);
  }

  TNode<Smi> phi_bb113_6;
  TNode<Smi> phi_bb113_7;
  TNode<Smi> phi_bb113_10;
  TNode<Smi> phi_bb113_11;
  TNode<Smi> phi_bb113_12;
  TNode<Smi> phi_bb113_13;
  TNode<Smi> phi_bb113_14;
  TNode<Smi> phi_bb113_15;
  TNode<BoolT> phi_bb113_16;
  TNode<BoolT> phi_bb113_18;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_6, &phi_bb113_7, &phi_bb113_10, &phi_bb113_11, &phi_bb113_12, &phi_bb113_13, &phi_bb113_14, &phi_bb113_15, &phi_bb113_16, &phi_bb113_18);
    ca_.Branch(phi_bb113_18, &block114, std::vector<compiler::Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16}, &block115, std::vector<compiler::Node*>{phi_bb113_6, phi_bb113_7, phi_bb113_10, phi_bb113_11, phi_bb113_12, phi_bb113_13, phi_bb113_14, phi_bb113_15, phi_bb113_16});
  }

  TNode<Smi> phi_bb114_6;
  TNode<Smi> phi_bb114_7;
  TNode<Smi> phi_bb114_10;
  TNode<Smi> phi_bb114_11;
  TNode<Smi> phi_bb114_12;
  TNode<Smi> phi_bb114_13;
  TNode<Smi> phi_bb114_14;
  TNode<Smi> phi_bb114_15;
  TNode<BoolT> phi_bb114_16;
  TNode<BoolT> tmp176;
  if (block114.is_used()) {
    ca_.Bind(&block114, &phi_bb114_6, &phi_bb114_7, &phi_bb114_10, &phi_bb114_11, &phi_bb114_12, &phi_bb114_13, &phi_bb114_14, &phi_bb114_15, &phi_bb114_16);
    tmp176 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block116, phi_bb114_6, phi_bb114_7, phi_bb114_10, phi_bb114_11, phi_bb114_12, phi_bb114_13, phi_bb114_14, phi_bb114_15, phi_bb114_16, tmp176);
  }

  TNode<Smi> phi_bb115_6;
  TNode<Smi> phi_bb115_7;
  TNode<Smi> phi_bb115_10;
  TNode<Smi> phi_bb115_11;
  TNode<Smi> phi_bb115_12;
  TNode<Smi> phi_bb115_13;
  TNode<Smi> phi_bb115_14;
  TNode<Smi> phi_bb115_15;
  TNode<BoolT> phi_bb115_16;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_6, &phi_bb115_7, &phi_bb115_10, &phi_bb115_11, &phi_bb115_12, &phi_bb115_13, &phi_bb115_14, &phi_bb115_15, &phi_bb115_16);
    ca_.Goto(&block116, phi_bb115_6, phi_bb115_7, phi_bb115_10, phi_bb115_11, phi_bb115_12, phi_bb115_13, phi_bb115_14, phi_bb115_15, phi_bb115_16, phi_bb115_16);
  }

  TNode<Smi> phi_bb116_6;
  TNode<Smi> phi_bb116_7;
  TNode<Smi> phi_bb116_10;
  TNode<Smi> phi_bb116_11;
  TNode<Smi> phi_bb116_12;
  TNode<Smi> phi_bb116_13;
  TNode<Smi> phi_bb116_14;
  TNode<Smi> phi_bb116_15;
  TNode<BoolT> phi_bb116_16;
  TNode<BoolT> phi_bb116_18;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_6, &phi_bb116_7, &phi_bb116_10, &phi_bb116_11, &phi_bb116_12, &phi_bb116_13, &phi_bb116_14, &phi_bb116_15, &phi_bb116_16, &phi_bb116_18);
    ca_.Branch(phi_bb116_18, &block108, std::vector<compiler::Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16}, &block109, std::vector<compiler::Node*>{phi_bb116_6, phi_bb116_7, phi_bb116_10, phi_bb116_11, phi_bb116_12, phi_bb116_13, phi_bb116_14, phi_bb116_15, phi_bb116_16});
  }

  TNode<Smi> phi_bb108_6;
  TNode<Smi> phi_bb108_7;
  TNode<Smi> phi_bb108_10;
  TNode<Smi> phi_bb108_11;
  TNode<Smi> phi_bb108_12;
  TNode<Smi> phi_bb108_13;
  TNode<Smi> phi_bb108_14;
  TNode<Smi> phi_bb108_15;
  TNode<BoolT> phi_bb108_16;
  TNode<BoolT> tmp177;
  TNode<Smi> tmp178;
  TNode<BoolT> tmp179;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_6, &phi_bb108_7, &phi_bb108_10, &phi_bb108_11, &phi_bb108_12, &phi_bb108_13, &phi_bb108_14, &phi_bb108_15, &phi_bb108_16);
    tmp177 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp178 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp179 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb108_6}, TNode<Smi>{tmp178});
    ca_.Branch(tmp179, &block119, std::vector<compiler::Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_13, phi_bb108_14, phi_bb108_15}, &block120, std::vector<compiler::Node*>{phi_bb108_6, phi_bb108_7, phi_bb108_10, phi_bb108_11, phi_bb108_12, phi_bb108_13, phi_bb108_14, phi_bb108_15});
  }

  TNode<Smi> phi_bb119_6;
  TNode<Smi> phi_bb119_7;
  TNode<Smi> phi_bb119_10;
  TNode<Smi> phi_bb119_11;
  TNode<Smi> phi_bb119_12;
  TNode<Smi> phi_bb119_13;
  TNode<Smi> phi_bb119_14;
  TNode<Smi> phi_bb119_15;
  TNode<Smi> tmp180;
  TNode<BoolT> tmp181;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_6, &phi_bb119_7, &phi_bb119_10, &phi_bb119_11, &phi_bb119_12, &phi_bb119_13, &phi_bb119_14, &phi_bb119_15);
    tmp180 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp181 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb119_7}, TNode<Smi>{tmp180});
    ca_.Goto(&block121, phi_bb119_6, phi_bb119_7, phi_bb119_10, phi_bb119_11, phi_bb119_12, phi_bb119_13, phi_bb119_14, phi_bb119_15, tmp181);
  }

  TNode<Smi> phi_bb120_6;
  TNode<Smi> phi_bb120_7;
  TNode<Smi> phi_bb120_10;
  TNode<Smi> phi_bb120_11;
  TNode<Smi> phi_bb120_12;
  TNode<Smi> phi_bb120_13;
  TNode<Smi> phi_bb120_14;
  TNode<Smi> phi_bb120_15;
  TNode<BoolT> tmp182;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_6, &phi_bb120_7, &phi_bb120_10, &phi_bb120_11, &phi_bb120_12, &phi_bb120_13, &phi_bb120_14, &phi_bb120_15);
    tmp182 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block121, phi_bb120_6, phi_bb120_7, phi_bb120_10, phi_bb120_11, phi_bb120_12, phi_bb120_13, phi_bb120_14, phi_bb120_15, tmp182);
  }

  TNode<Smi> phi_bb121_6;
  TNode<Smi> phi_bb121_7;
  TNode<Smi> phi_bb121_10;
  TNode<Smi> phi_bb121_11;
  TNode<Smi> phi_bb121_12;
  TNode<Smi> phi_bb121_13;
  TNode<Smi> phi_bb121_14;
  TNode<Smi> phi_bb121_15;
  TNode<BoolT> phi_bb121_18;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_6, &phi_bb121_7, &phi_bb121_10, &phi_bb121_11, &phi_bb121_12, &phi_bb121_13, &phi_bb121_14, &phi_bb121_15, &phi_bb121_18);
    ca_.Branch(phi_bb121_18, &block117, std::vector<compiler::Node*>{phi_bb121_6, phi_bb121_7, phi_bb121_10, phi_bb121_11, phi_bb121_12, phi_bb121_13, phi_bb121_14, phi_bb121_15}, &block118, std::vector<compiler::Node*>{phi_bb121_6, phi_bb121_7, phi_bb121_10, phi_bb121_11, phi_bb121_12, phi_bb121_13, phi_bb121_14, phi_bb121_15});
  }

  TNode<Smi> phi_bb118_6;
  TNode<Smi> phi_bb118_7;
  TNode<Smi> phi_bb118_10;
  TNode<Smi> phi_bb118_11;
  TNode<Smi> phi_bb118_12;
  TNode<Smi> phi_bb118_13;
  TNode<Smi> phi_bb118_14;
  TNode<Smi> phi_bb118_15;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_6, &phi_bb118_7, &phi_bb118_10, &phi_bb118_11, &phi_bb118_12, &phi_bb118_13, &phi_bb118_14, &phi_bb118_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1184});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA > 0 && lengthB > 1' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb117_6;
  TNode<Smi> phi_bb117_7;
  TNode<Smi> phi_bb117_10;
  TNode<Smi> phi_bb117_11;
  TNode<Smi> phi_bb117_12;
  TNode<Smi> phi_bb117_13;
  TNode<Smi> phi_bb117_14;
  TNode<Smi> phi_bb117_15;
  TNode<Smi> tmp183;
  TNode<Smi> tmp184;
  TNode<Smi> tmp185;
  TNode<Smi> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<Union<HeapObject, TaggedIndex>> tmp188;
  TNode<IntPtrT> tmp189;
  TNode<IntPtrT> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<UintPtrT> tmp192;
  TNode<UintPtrT> tmp193;
  TNode<BoolT> tmp194;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_6, &phi_bb117_7, &phi_bb117_10, &phi_bb117_11, &phi_bb117_12, &phi_bb117_13, &phi_bb117_14, &phi_bb117_15);
    tmp183 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp184 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb117_13}, TNode<Smi>{tmp183});
    tmp185 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp186 = CodeStubAssembler(state_).SmiMax(TNode<Smi>{tmp185}, TNode<Smi>{tmp184});
    tmp187 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp187}, tmp186);
    std::tie(tmp188, tmp189, tmp190) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp191 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb117_11});
    tmp192 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp191});
    tmp193 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp190});
    tmp194 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp192}, TNode<UintPtrT>{tmp193});
    ca_.Branch(tmp194, &block126, std::vector<compiler::Node*>{phi_bb117_6, phi_bb117_7, phi_bb117_10, phi_bb117_11, phi_bb117_12, phi_bb117_14, phi_bb117_15, phi_bb117_11, phi_bb117_11}, &block127, std::vector<compiler::Node*>{phi_bb117_6, phi_bb117_7, phi_bb117_10, phi_bb117_11, phi_bb117_12, phi_bb117_14, phi_bb117_15, phi_bb117_11, phi_bb117_11});
  }

  TNode<Smi> phi_bb126_6;
  TNode<Smi> phi_bb126_7;
  TNode<Smi> phi_bb126_10;
  TNode<Smi> phi_bb126_11;
  TNode<Smi> phi_bb126_12;
  TNode<Smi> phi_bb126_14;
  TNode<Smi> phi_bb126_15;
  TNode<Smi> phi_bb126_22;
  TNode<Smi> phi_bb126_23;
  TNode<IntPtrT> tmp195;
  TNode<IntPtrT> tmp196;
  TNode<Union<HeapObject, TaggedIndex>> tmp197;
  TNode<IntPtrT> tmp198;
  TNode<Object> tmp199;
  TNode<JSAny> tmp200;
  TNode<Smi> tmp201;
  TNode<Smi> tmp202;
  TNode<Smi> tmp203;
  TNode<Smi> tmp204;
  TNode<BoolT> tmp205;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_6, &phi_bb126_7, &phi_bb126_10, &phi_bb126_11, &phi_bb126_12, &phi_bb126_14, &phi_bb126_15, &phi_bb126_22, &phi_bb126_23);
    tmp195 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp191});
    tmp196 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp189}, TNode<IntPtrT>{tmp195});
    std::tie(tmp197, tmp198) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp188}, TNode<IntPtrT>{tmp196}).Flatten();
    tmp199 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp197, tmp198});
    tmp200 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp199});
    tmp201 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp202 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb126_6}, TNode<Smi>{tmp201});
    tmp203 = ca_.CallBuiltin<Smi>(Builtin::kGallopRight, p_context, p_sortState, tmp13, tmp200, p_baseA, phi_bb126_6, tmp202);
    tmp204 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp205 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp203}, TNode<Smi>{tmp204});
    ca_.Branch(tmp205, &block130, std::vector<compiler::Node*>{phi_bb126_6, phi_bb126_7, phi_bb126_10, phi_bb126_11, phi_bb126_12, phi_bb126_14, phi_bb126_15}, &block131, std::vector<compiler::Node*>{phi_bb126_6, phi_bb126_7, phi_bb126_10, phi_bb126_11, phi_bb126_12, phi_bb126_14, phi_bb126_15});
  }

  TNode<Smi> phi_bb127_6;
  TNode<Smi> phi_bb127_7;
  TNode<Smi> phi_bb127_10;
  TNode<Smi> phi_bb127_11;
  TNode<Smi> phi_bb127_12;
  TNode<Smi> phi_bb127_14;
  TNode<Smi> phi_bb127_15;
  TNode<Smi> phi_bb127_22;
  TNode<Smi> phi_bb127_23;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_6, &phi_bb127_7, &phi_bb127_10, &phi_bb127_11, &phi_bb127_12, &phi_bb127_14, &phi_bb127_15, &phi_bb127_22, &phi_bb127_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb131_6;
  TNode<Smi> phi_bb131_7;
  TNode<Smi> phi_bb131_10;
  TNode<Smi> phi_bb131_11;
  TNode<Smi> phi_bb131_12;
  TNode<Smi> phi_bb131_14;
  TNode<Smi> phi_bb131_15;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_6, &phi_bb131_7, &phi_bb131_10, &phi_bb131_11, &phi_bb131_12, &phi_bb131_14, &phi_bb131_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1192});
      CodeStubAssembler(state_).FailAssert("Torque assert 'k >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb130_6;
  TNode<Smi> phi_bb130_7;
  TNode<Smi> phi_bb130_10;
  TNode<Smi> phi_bb130_11;
  TNode<Smi> phi_bb130_12;
  TNode<Smi> phi_bb130_14;
  TNode<Smi> phi_bb130_15;
  TNode<Smi> tmp206;
  TNode<Smi> tmp207;
  TNode<BoolT> tmp208;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_6, &phi_bb130_7, &phi_bb130_10, &phi_bb130_11, &phi_bb130_12, &phi_bb130_14, &phi_bb130_15);
    tmp206 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb130_6}, TNode<Smi>{tmp203});
    tmp207 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp208 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp206}, TNode<Smi>{tmp207});
    ca_.Branch(tmp208, &block132, std::vector<compiler::Node*>{phi_bb130_6, phi_bb130_7, phi_bb130_10, phi_bb130_11, phi_bb130_12, phi_bb130_15}, &block133, std::vector<compiler::Node*>{phi_bb130_6, phi_bb130_7, phi_bb130_10, phi_bb130_11, phi_bb130_12, phi_bb130_15});
  }

  TNode<Smi> phi_bb132_6;
  TNode<Smi> phi_bb132_7;
  TNode<Smi> phi_bb132_10;
  TNode<Smi> phi_bb132_11;
  TNode<Smi> phi_bb132_12;
  TNode<Smi> phi_bb132_15;
  TNode<Smi> tmp209;
  TNode<Smi> tmp210;
  TNode<Smi> tmp211;
  TNode<Smi> tmp212;
  TNode<Smi> tmp213;
  TNode<Smi> tmp214;
  TNode<JSAny> tmp215;
  TNode<Smi> tmp216;
  TNode<Smi> tmp217;
  TNode<BoolT> tmp218;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_6, &phi_bb132_7, &phi_bb132_10, &phi_bb132_11, &phi_bb132_12, &phi_bb132_15);
    tmp209 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb132_10}, TNode<Smi>{tmp206});
    tmp210 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb132_12}, TNode<Smi>{tmp206});
    tmp211 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp212 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp210}, TNode<Smi>{tmp211});
    tmp213 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp214 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp209}, TNode<Smi>{tmp213});
    tmp215 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp13, tmp212, tmp13, tmp214, tmp206);
    tmp216 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb132_6}, TNode<Smi>{tmp206});
    tmp217 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp218 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp216}, TNode<Smi>{tmp217});
    ca_.Branch(tmp218, &block134, std::vector<compiler::Node*>{phi_bb132_7, phi_bb132_11, phi_bb132_15}, &block135, std::vector<compiler::Node*>{phi_bb132_7, phi_bb132_11, phi_bb132_15});
  }

  TNode<Smi> phi_bb134_7;
  TNode<Smi> phi_bb134_11;
  TNode<Smi> phi_bb134_15;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_7, &phi_bb134_11, &phi_bb134_15);
    ca_.Goto(&block33, tmp216, phi_bb134_7, tmp209, phi_bb134_11, tmp210);
  }

  TNode<Smi> phi_bb135_7;
  TNode<Smi> phi_bb135_11;
  TNode<Smi> phi_bb135_15;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_7, &phi_bb135_11, &phi_bb135_15);
    ca_.Goto(&block133, tmp216, phi_bb135_7, tmp209, phi_bb135_11, tmp210, phi_bb135_15);
  }

  TNode<Smi> phi_bb133_6;
  TNode<Smi> phi_bb133_7;
  TNode<Smi> phi_bb133_10;
  TNode<Smi> phi_bb133_11;
  TNode<Smi> phi_bb133_12;
  TNode<Smi> phi_bb133_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp219;
  TNode<IntPtrT> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<Smi> tmp222;
  TNode<Smi> tmp223;
  TNode<IntPtrT> tmp224;
  TNode<UintPtrT> tmp225;
  TNode<UintPtrT> tmp226;
  TNode<BoolT> tmp227;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_6, &phi_bb133_7, &phi_bb133_10, &phi_bb133_11, &phi_bb133_12, &phi_bb133_15);
    std::tie(tmp219, tmp220, tmp221) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp222 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp223 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb133_10}, TNode<Smi>{tmp222});
    tmp224 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb133_10});
    tmp225 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp224});
    tmp226 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp221});
    tmp227 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp225}, TNode<UintPtrT>{tmp226});
    ca_.Branch(tmp227, &block140, std::vector<compiler::Node*>{phi_bb133_6, phi_bb133_7, phi_bb133_11, phi_bb133_12, phi_bb133_15, phi_bb133_10, phi_bb133_10}, &block141, std::vector<compiler::Node*>{phi_bb133_6, phi_bb133_7, phi_bb133_11, phi_bb133_12, phi_bb133_15, phi_bb133_10, phi_bb133_10});
  }

  TNode<Smi> phi_bb140_6;
  TNode<Smi> phi_bb140_7;
  TNode<Smi> phi_bb140_11;
  TNode<Smi> phi_bb140_12;
  TNode<Smi> phi_bb140_15;
  TNode<Smi> phi_bb140_22;
  TNode<Smi> phi_bb140_23;
  TNode<IntPtrT> tmp228;
  TNode<IntPtrT> tmp229;
  TNode<Union<HeapObject, TaggedIndex>> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<Union<HeapObject, TaggedIndex>> tmp232;
  TNode<IntPtrT> tmp233;
  TNode<IntPtrT> tmp234;
  TNode<Smi> tmp235;
  TNode<Smi> tmp236;
  TNode<IntPtrT> tmp237;
  TNode<UintPtrT> tmp238;
  TNode<UintPtrT> tmp239;
  TNode<BoolT> tmp240;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_6, &phi_bb140_7, &phi_bb140_11, &phi_bb140_12, &phi_bb140_15, &phi_bb140_22, &phi_bb140_23);
    tmp228 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp224});
    tmp229 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp220}, TNode<IntPtrT>{tmp228});
    std::tie(tmp230, tmp231) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp219}, TNode<IntPtrT>{tmp229}).Flatten();
    std::tie(tmp232, tmp233, tmp234) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp235 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp236 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb140_11}, TNode<Smi>{tmp235});
    tmp237 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb140_11});
    tmp238 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp237});
    tmp239 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp234});
    tmp240 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp238}, TNode<UintPtrT>{tmp239});
    ca_.Branch(tmp240, &block148, std::vector<compiler::Node*>{phi_bb140_6, phi_bb140_7, phi_bb140_12, phi_bb140_15, phi_bb140_22, phi_bb140_23, phi_bb140_11, phi_bb140_11}, &block149, std::vector<compiler::Node*>{phi_bb140_6, phi_bb140_7, phi_bb140_12, phi_bb140_15, phi_bb140_22, phi_bb140_23, phi_bb140_11, phi_bb140_11});
  }

  TNode<Smi> phi_bb141_6;
  TNode<Smi> phi_bb141_7;
  TNode<Smi> phi_bb141_11;
  TNode<Smi> phi_bb141_12;
  TNode<Smi> phi_bb141_15;
  TNode<Smi> phi_bb141_22;
  TNode<Smi> phi_bb141_23;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_6, &phi_bb141_7, &phi_bb141_11, &phi_bb141_12, &phi_bb141_15, &phi_bb141_22, &phi_bb141_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb148_6;
  TNode<Smi> phi_bb148_7;
  TNode<Smi> phi_bb148_12;
  TNode<Smi> phi_bb148_15;
  TNode<Smi> phi_bb148_22;
  TNode<Smi> phi_bb148_23;
  TNode<Smi> phi_bb148_30;
  TNode<Smi> phi_bb148_31;
  TNode<IntPtrT> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<Union<HeapObject, TaggedIndex>> tmp243;
  TNode<IntPtrT> tmp244;
  TNode<Object> tmp245;
  TNode<Smi> tmp246;
  TNode<Smi> tmp247;
  TNode<Smi> tmp248;
  TNode<BoolT> tmp249;
  if (block148.is_used()) {
    ca_.Bind(&block148, &phi_bb148_6, &phi_bb148_7, &phi_bb148_12, &phi_bb148_15, &phi_bb148_22, &phi_bb148_23, &phi_bb148_30, &phi_bb148_31);
    tmp241 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp237});
    tmp242 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp233}, TNode<IntPtrT>{tmp241});
    std::tie(tmp243, tmp244) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp232}, TNode<IntPtrT>{tmp242}).Flatten();
    tmp245 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp243, tmp244});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp230, tmp231}, tmp245);
    tmp246 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp247 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb148_7}, TNode<Smi>{tmp246});
    tmp248 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp249 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp247}, TNode<Smi>{tmp248});
    ca_.Branch(tmp249, &block152, std::vector<compiler::Node*>{phi_bb148_6, phi_bb148_12, phi_bb148_15}, &block153, std::vector<compiler::Node*>{phi_bb148_6, phi_bb148_12, phi_bb148_15});
  }

  TNode<Smi> phi_bb149_6;
  TNode<Smi> phi_bb149_7;
  TNode<Smi> phi_bb149_12;
  TNode<Smi> phi_bb149_15;
  TNode<Smi> phi_bb149_22;
  TNode<Smi> phi_bb149_23;
  TNode<Smi> phi_bb149_30;
  TNode<Smi> phi_bb149_31;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_6, &phi_bb149_7, &phi_bb149_12, &phi_bb149_15, &phi_bb149_22, &phi_bb149_23, &phi_bb149_30, &phi_bb149_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb152_6;
  TNode<Smi> phi_bb152_12;
  TNode<Smi> phi_bb152_15;
  if (block152.is_used()) {
    ca_.Bind(&block152, &phi_bb152_6, &phi_bb152_12, &phi_bb152_15);
    ca_.Goto(&block31, phi_bb152_6, tmp247, tmp223, tmp236, phi_bb152_12);
  }

  TNode<Smi> phi_bb153_6;
  TNode<Smi> phi_bb153_12;
  TNode<Smi> phi_bb153_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp250;
  TNode<IntPtrT> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<IntPtrT> tmp253;
  TNode<UintPtrT> tmp254;
  TNode<UintPtrT> tmp255;
  TNode<BoolT> tmp256;
  if (block153.is_used()) {
    ca_.Bind(&block153, &phi_bb153_6, &phi_bb153_12, &phi_bb153_15);
    std::tie(tmp250, tmp251, tmp252) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp253 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb153_12});
    tmp254 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp253});
    tmp255 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp252});
    tmp256 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp254}, TNode<UintPtrT>{tmp255});
    ca_.Branch(tmp256, &block158, std::vector<compiler::Node*>{phi_bb153_6, phi_bb153_12, phi_bb153_15, phi_bb153_12, phi_bb153_12}, &block159, std::vector<compiler::Node*>{phi_bb153_6, phi_bb153_12, phi_bb153_15, phi_bb153_12, phi_bb153_12});
  }

  TNode<Smi> phi_bb158_6;
  TNode<Smi> phi_bb158_12;
  TNode<Smi> phi_bb158_15;
  TNode<Smi> phi_bb158_23;
  TNode<Smi> phi_bb158_24;
  TNode<IntPtrT> tmp257;
  TNode<IntPtrT> tmp258;
  TNode<Union<HeapObject, TaggedIndex>> tmp259;
  TNode<IntPtrT> tmp260;
  TNode<Object> tmp261;
  TNode<JSAny> tmp262;
  TNode<Smi> tmp263;
  TNode<Smi> tmp264;
  TNode<Smi> tmp265;
  TNode<Smi> tmp266;
  TNode<Smi> tmp267;
  TNode<BoolT> tmp268;
  if (block158.is_used()) {
    ca_.Bind(&block158, &phi_bb158_6, &phi_bb158_12, &phi_bb158_15, &phi_bb158_23, &phi_bb158_24);
    tmp257 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp253});
    tmp258 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp251}, TNode<IntPtrT>{tmp257});
    std::tie(tmp259, tmp260) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp250}, TNode<IntPtrT>{tmp258}).Flatten();
    tmp261 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp259, tmp260});
    tmp262 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp261});
    tmp263 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp264 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp247}, TNode<Smi>{tmp263});
    tmp265 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp266 = ca_.CallBuiltin<Smi>(Builtin::kGallopLeft, p_context, p_sortState, tmp14, tmp262, tmp265, tmp247, tmp264);
    tmp267 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp268 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp266}, TNode<Smi>{tmp267});
    ca_.Branch(tmp268, &block162, std::vector<compiler::Node*>{phi_bb158_6, phi_bb158_12, phi_bb158_15}, &block163, std::vector<compiler::Node*>{phi_bb158_6, phi_bb158_12, phi_bb158_15});
  }

  TNode<Smi> phi_bb159_6;
  TNode<Smi> phi_bb159_12;
  TNode<Smi> phi_bb159_15;
  TNode<Smi> phi_bb159_23;
  TNode<Smi> phi_bb159_24;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_6, &phi_bb159_12, &phi_bb159_15, &phi_bb159_23, &phi_bb159_24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb163_6;
  TNode<Smi> phi_bb163_12;
  TNode<Smi> phi_bb163_15;
  if (block163.is_used()) {
    ca_.Bind(&block163, &phi_bb163_6, &phi_bb163_12, &phi_bb163_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1209});
      CodeStubAssembler(state_).FailAssert("Torque assert 'k >= 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb162_6;
  TNode<Smi> phi_bb162_12;
  TNode<Smi> phi_bb162_15;
  TNode<Smi> tmp269;
  TNode<Smi> tmp270;
  TNode<BoolT> tmp271;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_6, &phi_bb162_12, &phi_bb162_15);
    tmp269 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp247}, TNode<Smi>{tmp266});
    tmp270 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp271 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp269}, TNode<Smi>{tmp270});
    ca_.Branch(tmp271, &block164, std::vector<compiler::Node*>{phi_bb162_6, phi_bb162_12}, &block165, std::vector<compiler::Node*>{phi_bb162_6, tmp247, tmp223, tmp236, phi_bb162_12});
  }

  TNode<Smi> phi_bb164_6;
  TNode<Smi> phi_bb164_12;
  TNode<Smi> tmp272;
  TNode<Smi> tmp273;
  TNode<Smi> tmp274;
  TNode<Smi> tmp275;
  TNode<Smi> tmp276;
  TNode<Smi> tmp277;
  TNode<JSAny> tmp278;
  TNode<Smi> tmp279;
  TNode<Smi> tmp280;
  TNode<BoolT> tmp281;
  if (block164.is_used()) {
    ca_.Bind(&block164, &phi_bb164_6, &phi_bb164_12);
    tmp272 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp223}, TNode<Smi>{tmp269});
    tmp273 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp236}, TNode<Smi>{tmp269});
    tmp274 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp275 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp273}, TNode<Smi>{tmp274});
    tmp276 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp277 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp272}, TNode<Smi>{tmp276});
    tmp278 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp14, tmp275, tmp13, tmp277, tmp269);
    tmp279 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp247}, TNode<Smi>{tmp269});
    tmp280 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp281 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp279}, TNode<Smi>{tmp280});
    ca_.Branch(tmp281, &block166, std::vector<compiler::Node*>{phi_bb164_6, phi_bb164_12}, &block167, std::vector<compiler::Node*>{phi_bb164_6, phi_bb164_12});
  }

  TNode<Smi> phi_bb166_6;
  TNode<Smi> phi_bb166_12;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_6, &phi_bb166_12);
    ca_.Goto(&block31, phi_bb166_6, tmp279, tmp272, tmp273, phi_bb166_12);
  }

  TNode<Smi> phi_bb167_6;
  TNode<Smi> phi_bb167_12;
  TNode<Smi> tmp282;
  TNode<BoolT> tmp283;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_6, &phi_bb167_12);
    tmp282 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp283 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp279}, TNode<Smi>{tmp282});
    ca_.Branch(tmp283, &block168, std::vector<compiler::Node*>{phi_bb167_6, phi_bb167_12}, &block169, std::vector<compiler::Node*>{phi_bb167_6, phi_bb167_12});
  }

  TNode<Smi> phi_bb168_6;
  TNode<Smi> phi_bb168_12;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_6, &phi_bb168_12);
    ca_.Goto(&block33, phi_bb168_6, tmp279, tmp272, tmp273, phi_bb168_12);
  }

  TNode<Smi> phi_bb169_6;
  TNode<Smi> phi_bb169_12;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_6, &phi_bb169_12);
    ca_.Goto(&block165, phi_bb169_6, tmp279, tmp272, tmp273, phi_bb169_12);
  }

  TNode<Smi> phi_bb165_6;
  TNode<Smi> phi_bb165_7;
  TNode<Smi> phi_bb165_10;
  TNode<Smi> phi_bb165_11;
  TNode<Smi> phi_bb165_12;
  TNode<Union<HeapObject, TaggedIndex>> tmp284;
  TNode<IntPtrT> tmp285;
  TNode<IntPtrT> tmp286;
  TNode<Smi> tmp287;
  TNode<Smi> tmp288;
  TNode<IntPtrT> tmp289;
  TNode<UintPtrT> tmp290;
  TNode<UintPtrT> tmp291;
  TNode<BoolT> tmp292;
  if (block165.is_used()) {
    ca_.Bind(&block165, &phi_bb165_6, &phi_bb165_7, &phi_bb165_10, &phi_bb165_11, &phi_bb165_12);
    std::tie(tmp284, tmp285, tmp286) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp287 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp288 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb165_10}, TNode<Smi>{tmp287});
    tmp289 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb165_10});
    tmp290 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp289});
    tmp291 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp286});
    tmp292 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp290}, TNode<UintPtrT>{tmp291});
    ca_.Branch(tmp292, &block174, std::vector<compiler::Node*>{phi_bb165_6, phi_bb165_7, phi_bb165_11, phi_bb165_12, phi_bb165_10, phi_bb165_10}, &block175, std::vector<compiler::Node*>{phi_bb165_6, phi_bb165_7, phi_bb165_11, phi_bb165_12, phi_bb165_10, phi_bb165_10});
  }

  TNode<Smi> phi_bb174_6;
  TNode<Smi> phi_bb174_7;
  TNode<Smi> phi_bb174_11;
  TNode<Smi> phi_bb174_12;
  TNode<Smi> phi_bb174_22;
  TNode<Smi> phi_bb174_23;
  TNode<IntPtrT> tmp293;
  TNode<IntPtrT> tmp294;
  TNode<Union<HeapObject, TaggedIndex>> tmp295;
  TNode<IntPtrT> tmp296;
  TNode<Union<HeapObject, TaggedIndex>> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<IntPtrT> tmp299;
  TNode<Smi> tmp300;
  TNode<Smi> tmp301;
  TNode<IntPtrT> tmp302;
  TNode<UintPtrT> tmp303;
  TNode<UintPtrT> tmp304;
  TNode<BoolT> tmp305;
  if (block174.is_used()) {
    ca_.Bind(&block174, &phi_bb174_6, &phi_bb174_7, &phi_bb174_11, &phi_bb174_12, &phi_bb174_22, &phi_bb174_23);
    tmp293 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp289});
    tmp294 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp285}, TNode<IntPtrT>{tmp293});
    std::tie(tmp295, tmp296) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp284}, TNode<IntPtrT>{tmp294}).Flatten();
    std::tie(tmp297, tmp298, tmp299) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp300 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp301 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb174_12}, TNode<Smi>{tmp300});
    tmp302 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb174_12});
    tmp303 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp302});
    tmp304 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp299});
    tmp305 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp303}, TNode<UintPtrT>{tmp304});
    ca_.Branch(tmp305, &block182, std::vector<compiler::Node*>{phi_bb174_6, phi_bb174_7, phi_bb174_11, phi_bb174_22, phi_bb174_23, phi_bb174_12, phi_bb174_12}, &block183, std::vector<compiler::Node*>{phi_bb174_6, phi_bb174_7, phi_bb174_11, phi_bb174_22, phi_bb174_23, phi_bb174_12, phi_bb174_12});
  }

  TNode<Smi> phi_bb175_6;
  TNode<Smi> phi_bb175_7;
  TNode<Smi> phi_bb175_11;
  TNode<Smi> phi_bb175_12;
  TNode<Smi> phi_bb175_22;
  TNode<Smi> phi_bb175_23;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_6, &phi_bb175_7, &phi_bb175_11, &phi_bb175_12, &phi_bb175_22, &phi_bb175_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb182_6;
  TNode<Smi> phi_bb182_7;
  TNode<Smi> phi_bb182_11;
  TNode<Smi> phi_bb182_22;
  TNode<Smi> phi_bb182_23;
  TNode<Smi> phi_bb182_30;
  TNode<Smi> phi_bb182_31;
  TNode<IntPtrT> tmp306;
  TNode<IntPtrT> tmp307;
  TNode<Union<HeapObject, TaggedIndex>> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<Object> tmp310;
  TNode<Smi> tmp311;
  TNode<Smi> tmp312;
  TNode<Smi> tmp313;
  TNode<BoolT> tmp314;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_6, &phi_bb182_7, &phi_bb182_11, &phi_bb182_22, &phi_bb182_23, &phi_bb182_30, &phi_bb182_31);
    tmp306 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp302});
    tmp307 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp298}, TNode<IntPtrT>{tmp306});
    std::tie(tmp308, tmp309) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp297}, TNode<IntPtrT>{tmp307}).Flatten();
    tmp310 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp308, tmp309});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp295, tmp296}, tmp310);
    tmp311 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp312 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb182_6}, TNode<Smi>{tmp311});
    tmp313 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp314 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp312}, TNode<Smi>{tmp313});
    ca_.Branch(tmp314, &block186, std::vector<compiler::Node*>{phi_bb182_7, phi_bb182_11}, &block187, std::vector<compiler::Node*>{phi_bb182_7, phi_bb182_11});
  }

  TNode<Smi> phi_bb183_6;
  TNode<Smi> phi_bb183_7;
  TNode<Smi> phi_bb183_11;
  TNode<Smi> phi_bb183_22;
  TNode<Smi> phi_bb183_23;
  TNode<Smi> phi_bb183_30;
  TNode<Smi> phi_bb183_31;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_6, &phi_bb183_7, &phi_bb183_11, &phi_bb183_22, &phi_bb183_23, &phi_bb183_30, &phi_bb183_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb186_7;
  TNode<Smi> phi_bb186_11;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_7, &phi_bb186_11);
    ca_.Goto(&block33, tmp312, phi_bb186_7, tmp288, phi_bb186_11, tmp301);
  }

  TNode<Smi> phi_bb187_7;
  TNode<Smi> phi_bb187_11;
  if (block187.is_used()) {
    ca_.Bind(&block187, &phi_bb187_7, &phi_bb187_11);
    ca_.Goto(&block110, tmp312, phi_bb187_7, tmp288, phi_bb187_11, tmp301, tmp186, tmp206, tmp269, tmp177);
  }

  TNode<Smi> phi_bb109_6;
  TNode<Smi> phi_bb109_7;
  TNode<Smi> phi_bb109_10;
  TNode<Smi> phi_bb109_11;
  TNode<Smi> phi_bb109_12;
  TNode<Smi> phi_bb109_13;
  TNode<Smi> phi_bb109_14;
  TNode<Smi> phi_bb109_15;
  TNode<BoolT> phi_bb109_16;
  TNode<Smi> tmp315;
  TNode<Smi> tmp316;
  TNode<IntPtrT> tmp317;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_6, &phi_bb109_7, &phi_bb109_10, &phi_bb109_11, &phi_bb109_12, &phi_bb109_13, &phi_bb109_14, &phi_bb109_15, &phi_bb109_16);
    tmp315 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp316 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb109_13}, TNode<Smi>{tmp315});
    tmp317 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp317}, tmp316);
    ca_.Goto(&block40, phi_bb109_6, phi_bb109_7, phi_bb109_10, phi_bb109_11, phi_bb109_12, tmp316);
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_10;
  TNode<Smi> phi_bb39_11;
  TNode<Smi> phi_bb39_12;
  TNode<Smi> phi_bb39_13;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_7, &phi_bb39_10, &phi_bb39_11, &phi_bb39_12, &phi_bb39_13);
    ca_.Goto(&block32, phi_bb39_6, phi_bb39_7, phi_bb39_10, phi_bb39_11, phi_bb39_12);
  }

  TNode<Smi> phi_bb33_6;
  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_10;
  TNode<Smi> phi_bb33_11;
  TNode<Smi> phi_bb33_12;
  TNode<Smi> tmp318;
  TNode<BoolT> tmp319;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_6, &phi_bb33_7, &phi_bb33_10, &phi_bb33_11, &phi_bb33_12);
    tmp318 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp319 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb33_7}, TNode<Smi>{tmp318});
    ca_.Branch(tmp319, &block188, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7, phi_bb33_10, phi_bb33_11, phi_bb33_12}, &block189, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7, phi_bb33_10, phi_bb33_11, phi_bb33_12});
  }

  TNode<Smi> phi_bb188_6;
  TNode<Smi> phi_bb188_7;
  TNode<Smi> phi_bb188_10;
  TNode<Smi> phi_bb188_11;
  TNode<Smi> phi_bb188_12;
  TNode<Smi> tmp320;
  TNode<BoolT> tmp321;
  if (block188.is_used()) {
    ca_.Bind(&block188, &phi_bb188_6, &phi_bb188_7, &phi_bb188_10, &phi_bb188_11, &phi_bb188_12);
    tmp320 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp321 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb188_6}, TNode<Smi>{tmp320});
    ca_.Branch(tmp321, &block190, std::vector<compiler::Node*>{phi_bb188_6, phi_bb188_7, phi_bb188_10, phi_bb188_11, phi_bb188_12}, &block191, std::vector<compiler::Node*>{phi_bb188_6, phi_bb188_7, phi_bb188_10, phi_bb188_11, phi_bb188_12});
  }

  TNode<Smi> phi_bb191_6;
  TNode<Smi> phi_bb191_7;
  TNode<Smi> phi_bb191_10;
  TNode<Smi> phi_bb191_11;
  TNode<Smi> phi_bb191_12;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_6, &phi_bb191_7, &phi_bb191_10, &phi_bb191_11, &phi_bb191_12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1232});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthA == 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb190_6;
  TNode<Smi> phi_bb190_7;
  TNode<Smi> phi_bb190_10;
  TNode<Smi> phi_bb190_11;
  TNode<Smi> phi_bb190_12;
  TNode<Smi> tmp322;
  TNode<Smi> tmp323;
  TNode<Smi> tmp324;
  TNode<Smi> tmp325;
  TNode<JSAny> tmp326;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_6, &phi_bb190_7, &phi_bb190_10, &phi_bb190_11, &phi_bb190_12);
    tmp322 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp323 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb190_7}, TNode<Smi>{tmp322});
    tmp324 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb190_10}, TNode<Smi>{tmp323});
    tmp325 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp326 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp14, tmp325, tmp13, tmp324, phi_bb190_7);
    ca_.Goto(&block189, phi_bb190_6, phi_bb190_7, phi_bb190_10, phi_bb190_11, phi_bb190_12);
  }

  TNode<Smi> phi_bb189_6;
  TNode<Smi> phi_bb189_7;
  TNode<Smi> phi_bb189_10;
  TNode<Smi> phi_bb189_11;
  TNode<Smi> phi_bb189_12;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_6, &phi_bb189_7, &phi_bb189_10, &phi_bb189_11, &phi_bb189_12);
    ca_.Goto(&block32, phi_bb189_6, phi_bb189_7, phi_bb189_10, phi_bb189_11, phi_bb189_12);
  }

  TNode<Smi> phi_bb32_6;
  TNode<Smi> phi_bb32_7;
  TNode<Smi> phi_bb32_10;
  TNode<Smi> phi_bb32_11;
  TNode<Smi> phi_bb32_12;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_6, &phi_bb32_7, &phi_bb32_10, &phi_bb32_11, &phi_bb32_12);
    ca_.Goto(&block30, phi_bb32_6, phi_bb32_7, phi_bb32_10, phi_bb32_11, phi_bb32_12);
  }

  TNode<Smi> phi_bb31_6;
  TNode<Smi> phi_bb31_7;
  TNode<Smi> phi_bb31_10;
  TNode<Smi> phi_bb31_11;
  TNode<Smi> phi_bb31_12;
  TNode<Smi> tmp327;
  TNode<BoolT> tmp328;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_6, &phi_bb31_7, &phi_bb31_10, &phi_bb31_11, &phi_bb31_12);
    tmp327 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp328 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb31_7}, TNode<Smi>{tmp327});
    ca_.Branch(tmp328, &block194, std::vector<compiler::Node*>{phi_bb31_6, phi_bb31_7, phi_bb31_10, phi_bb31_11, phi_bb31_12}, &block195, std::vector<compiler::Node*>{phi_bb31_6, phi_bb31_7, phi_bb31_10, phi_bb31_11, phi_bb31_12});
  }

  TNode<Smi> phi_bb194_6;
  TNode<Smi> phi_bb194_7;
  TNode<Smi> phi_bb194_10;
  TNode<Smi> phi_bb194_11;
  TNode<Smi> phi_bb194_12;
  TNode<Smi> tmp329;
  TNode<BoolT> tmp330;
  if (block194.is_used()) {
    ca_.Bind(&block194, &phi_bb194_6, &phi_bb194_7, &phi_bb194_10, &phi_bb194_11, &phi_bb194_12);
    tmp329 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp330 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb194_6}, TNode<Smi>{tmp329});
    ca_.Goto(&block196, phi_bb194_6, phi_bb194_7, phi_bb194_10, phi_bb194_11, phi_bb194_12, tmp330);
  }

  TNode<Smi> phi_bb195_6;
  TNode<Smi> phi_bb195_7;
  TNode<Smi> phi_bb195_10;
  TNode<Smi> phi_bb195_11;
  TNode<Smi> phi_bb195_12;
  TNode<BoolT> tmp331;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_6, &phi_bb195_7, &phi_bb195_10, &phi_bb195_11, &phi_bb195_12);
    tmp331 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block196, phi_bb195_6, phi_bb195_7, phi_bb195_10, phi_bb195_11, phi_bb195_12, tmp331);
  }

  TNode<Smi> phi_bb196_6;
  TNode<Smi> phi_bb196_7;
  TNode<Smi> phi_bb196_10;
  TNode<Smi> phi_bb196_11;
  TNode<Smi> phi_bb196_12;
  TNode<BoolT> phi_bb196_14;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_6, &phi_bb196_7, &phi_bb196_10, &phi_bb196_11, &phi_bb196_12, &phi_bb196_14);
    ca_.Branch(phi_bb196_14, &block192, std::vector<compiler::Node*>{phi_bb196_6, phi_bb196_7, phi_bb196_10, phi_bb196_11, phi_bb196_12}, &block193, std::vector<compiler::Node*>{phi_bb196_6, phi_bb196_7, phi_bb196_10, phi_bb196_11, phi_bb196_12});
  }

  TNode<Smi> phi_bb193_6;
  TNode<Smi> phi_bb193_7;
  TNode<Smi> phi_bb193_10;
  TNode<Smi> phi_bb193_11;
  TNode<Smi> phi_bb193_12;
  if (block193.is_used()) {
    ca_.Bind(&block193, &phi_bb193_6, &phi_bb193_7, &phi_bb193_10, &phi_bb193_11, &phi_bb193_12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1236});
      CodeStubAssembler(state_).FailAssert("Torque assert 'lengthB == 1 && lengthA > 0' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb192_6;
  TNode<Smi> phi_bb192_7;
  TNode<Smi> phi_bb192_10;
  TNode<Smi> phi_bb192_11;
  TNode<Smi> phi_bb192_12;
  TNode<Smi> tmp332;
  TNode<Smi> tmp333;
  TNode<Smi> tmp334;
  TNode<Smi> tmp335;
  TNode<Smi> tmp336;
  TNode<Smi> tmp337;
  TNode<JSAny> tmp338;
  TNode<Union<HeapObject, TaggedIndex>> tmp339;
  TNode<IntPtrT> tmp340;
  TNode<IntPtrT> tmp341;
  TNode<IntPtrT> tmp342;
  TNode<UintPtrT> tmp343;
  TNode<UintPtrT> tmp344;
  TNode<BoolT> tmp345;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_6, &phi_bb192_7, &phi_bb192_10, &phi_bb192_11, &phi_bb192_12);
    tmp332 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb192_10}, TNode<Smi>{phi_bb192_6});
    tmp333 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb192_12}, TNode<Smi>{phi_bb192_6});
    tmp334 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp335 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp333}, TNode<Smi>{tmp334});
    tmp336 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp337 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp332}, TNode<Smi>{tmp336});
    tmp338 = ca_.CallBuiltin<JSAny>(Builtin::kCopy, p_context, tmp13, tmp335, tmp13, tmp337, phi_bb192_6);
    std::tie(tmp339, tmp340, tmp341) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp13}).Flatten();
    tmp342 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp332});
    tmp343 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp342});
    tmp344 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp341});
    tmp345 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp343}, TNode<UintPtrT>{tmp344});
    ca_.Branch(tmp345, &block201, std::vector<compiler::Node*>{phi_bb192_6, phi_bb192_7, phi_bb192_11}, &block202, std::vector<compiler::Node*>{phi_bb192_6, phi_bb192_7, phi_bb192_11});
  }

  TNode<Smi> phi_bb201_6;
  TNode<Smi> phi_bb201_7;
  TNode<Smi> phi_bb201_11;
  TNode<IntPtrT> tmp346;
  TNode<IntPtrT> tmp347;
  TNode<Union<HeapObject, TaggedIndex>> tmp348;
  TNode<IntPtrT> tmp349;
  TNode<Union<HeapObject, TaggedIndex>> tmp350;
  TNode<IntPtrT> tmp351;
  TNode<IntPtrT> tmp352;
  TNode<IntPtrT> tmp353;
  TNode<UintPtrT> tmp354;
  TNode<UintPtrT> tmp355;
  TNode<BoolT> tmp356;
  if (block201.is_used()) {
    ca_.Bind(&block201, &phi_bb201_6, &phi_bb201_7, &phi_bb201_11);
    tmp346 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp342});
    tmp347 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp340}, TNode<IntPtrT>{tmp346});
    std::tie(tmp348, tmp349) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp339}, TNode<IntPtrT>{tmp347}).Flatten();
    std::tie(tmp350, tmp351, tmp352) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp14}).Flatten();
    tmp353 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb201_11});
    tmp354 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp353});
    tmp355 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp352});
    tmp356 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp354}, TNode<UintPtrT>{tmp355});
    ca_.Branch(tmp356, &block209, std::vector<compiler::Node*>{phi_bb201_6, phi_bb201_7, phi_bb201_11, phi_bb201_11, phi_bb201_11}, &block210, std::vector<compiler::Node*>{phi_bb201_6, phi_bb201_7, phi_bb201_11, phi_bb201_11, phi_bb201_11});
  }

  TNode<Smi> phi_bb202_6;
  TNode<Smi> phi_bb202_7;
  TNode<Smi> phi_bb202_11;
  if (block202.is_used()) {
    ca_.Bind(&block202, &phi_bb202_6, &phi_bb202_7, &phi_bb202_11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb209_6;
  TNode<Smi> phi_bb209_7;
  TNode<Smi> phi_bb209_11;
  TNode<Smi> phi_bb209_25;
  TNode<Smi> phi_bb209_26;
  TNode<IntPtrT> tmp357;
  TNode<IntPtrT> tmp358;
  TNode<Union<HeapObject, TaggedIndex>> tmp359;
  TNode<IntPtrT> tmp360;
  TNode<Object> tmp361;
  if (block209.is_used()) {
    ca_.Bind(&block209, &phi_bb209_6, &phi_bb209_7, &phi_bb209_11, &phi_bb209_25, &phi_bb209_26);
    tmp357 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp353});
    tmp358 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp351}, TNode<IntPtrT>{tmp357});
    std::tie(tmp359, tmp360) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp350}, TNode<IntPtrT>{tmp358}).Flatten();
    tmp361 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp359, tmp360});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp348, tmp349}, tmp361);
    ca_.Goto(&block30, phi_bb209_6, phi_bb209_7, tmp332, phi_bb209_11, tmp333);
  }

  TNode<Smi> phi_bb210_6;
  TNode<Smi> phi_bb210_7;
  TNode<Smi> phi_bb210_11;
  TNode<Smi> phi_bb210_25;
  TNode<Smi> phi_bb210_26;
  if (block210.is_used()) {
    ca_.Bind(&block210, &phi_bb210_6, &phi_bb210_7, &phi_bb210_11, &phi_bb210_25, &phi_bb210_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> phi_bb30_6;
  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_10;
  TNode<Smi> phi_bb30_11;
  TNode<Smi> phi_bb30_12;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_6, &phi_bb30_7, &phi_bb30_10, &phi_bb30_11, &phi_bb30_12);
    ca_.Goto(&block213);
  }

    ca_.Bind(&block213);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1260&c=1
void ArrayPowerSortImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_length) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, BoolT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block13(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, BoolT> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, BoolT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, BoolT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp1 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_length}, TNode<Smi>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<FixedArray> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<FixedArray> tmp7;
  TNode<Smi> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp3 = Convert_intptr_constexpr_int31_0(state_, kMaxMergePending_0(state_));
    tmp4 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp3});
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp2}, tmp4);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp6 = Convert_intptr_constexpr_int31_0(state_, kMaxMergePending_0(state_));
    tmp7 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{tmp6});
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp5}, tmp7);
    tmp8 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block6, p_length, tmp8);
  }

  TNode<Smi> phi_bb6_4;
  TNode<Smi> phi_bb6_5;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_4, &phi_bb6_5);
    tmp9 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x40ull));
    tmp10 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb6_4}, TNode<Smi>{tmp9});
    ca_.Branch(tmp10, &block4, std::vector<compiler::Node*>{phi_bb6_4, phi_bb6_5}, &block5, std::vector<compiler::Node*>{phi_bb6_4, phi_bb6_5});
  }

  TNode<Smi> phi_bb4_4;
  TNode<Smi> phi_bb4_5;
  TNode<Smi> tmp11;
  TNode<Smi> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_4, &phi_bb4_5);
    tmp11 = CodeStubAssembler(state_).SmiSar(TNode<Smi>{phi_bb4_4}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp12 = CodeStubAssembler(state_).SmiShl(TNode<Smi>{phi_bb4_5}, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull))));
    tmp13 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp14 = CodeStubAssembler(state_).SmiOr(TNode<Smi>{tmp12}, TNode<Smi>{tmp13});
    ca_.Goto(&block6, tmp11, tmp14);
  }

  TNode<Smi> phi_bb5_4;
  TNode<Smi> phi_bb5_5;
  TNode<Smi> tmp15;
  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_4, &phi_bb5_5);
    tmp15 = CodeStubAssembler(state_).SmiAnd(TNode<Smi>{p_length}, TNode<Smi>{phi_bb5_5});
    tmp16 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp17 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb5_5}, TNode<Smi>{tmp16});
    tmp18 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp19 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block9, p_length, phi_bb5_4, phi_bb5_5, tmp18, tmp19);
  }

  TNode<Smi> phi_bb9_3;
  TNode<Smi> phi_bb9_4;
  TNode<Smi> phi_bb9_5;
  TNode<Smi> phi_bb9_8;
  TNode<Smi> phi_bb9_9;
  TNode<Smi> tmp20;
  TNode<BoolT> tmp21;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_3, &phi_bb9_4, &phi_bb9_5, &phi_bb9_8, &phi_bb9_9);
    tmp20 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp21 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{phi_bb9_3}, TNode<Smi>{tmp20});
    ca_.Branch(tmp21, &block7, std::vector<compiler::Node*>{phi_bb9_3, phi_bb9_4, phi_bb9_5, phi_bb9_8, phi_bb9_9}, &block8, std::vector<compiler::Node*>{phi_bb9_3, phi_bb9_4, phi_bb9_5, phi_bb9_8, phi_bb9_9});
  }

  TNode<Smi> phi_bb7_3;
  TNode<Smi> phi_bb7_4;
  TNode<Smi> phi_bb7_5;
  TNode<Smi> phi_bb7_8;
  TNode<Smi> phi_bb7_9;
  TNode<Smi> tmp22;
  TNode<BoolT> tmp23;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_3, &phi_bb7_4, &phi_bb7_5, &phi_bb7_8, &phi_bb7_9);
    tmp22 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb7_8}, TNode<Smi>{tmp15});
    tmp23 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp22}, TNode<Smi>{tmp17});
    ca_.Branch(tmp23, &block10, std::vector<compiler::Node*>{phi_bb7_3, phi_bb7_4, phi_bb7_5, phi_bb7_9, phi_bb7_4}, &block11, std::vector<compiler::Node*>{phi_bb7_3, phi_bb7_4, phi_bb7_5, tmp22, phi_bb7_9, phi_bb7_4});
  }

  TNode<Smi> phi_bb10_3;
  TNode<Smi> phi_bb10_4;
  TNode<Smi> phi_bb10_5;
  TNode<Smi> phi_bb10_9;
  TNode<Smi> phi_bb10_10;
  TNode<Smi> tmp24;
  TNode<Smi> tmp25;
  TNode<Smi> tmp26;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3, &phi_bb10_4, &phi_bb10_5, &phi_bb10_9, &phi_bb10_10);
    tmp24 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp22}, TNode<Smi>{tmp17});
    tmp25 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp26 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb10_10}, TNode<Smi>{tmp25});
    ca_.Goto(&block11, phi_bb10_3, phi_bb10_4, phi_bb10_5, tmp24, phi_bb10_9, tmp26);
  }

  TNode<Smi> phi_bb11_3;
  TNode<Smi> phi_bb11_4;
  TNode<Smi> phi_bb11_5;
  TNode<Smi> phi_bb11_8;
  TNode<Smi> phi_bb11_9;
  TNode<Smi> phi_bb11_10;
  TNode<Smi> tmp27;
  TNode<BoolT> tmp28;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_3, &phi_bb11_4, &phi_bb11_5, &phi_bb11_8, &phi_bb11_9, &phi_bb11_10);
    tmp27 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x40ull));
    tmp28 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{p_length}, TNode<Smi>{tmp27});
    ca_.Branch(tmp28, &block14, std::vector<compiler::Node*>{phi_bb11_3, phi_bb11_4, phi_bb11_5, phi_bb11_9}, &block15, std::vector<compiler::Node*>{phi_bb11_3, phi_bb11_4, phi_bb11_5, phi_bb11_9});
  }

  TNode<Smi> phi_bb14_3;
  TNode<Smi> phi_bb14_4;
  TNode<Smi> phi_bb14_5;
  TNode<Smi> phi_bb14_9;
  TNode<BoolT> tmp29;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_3, &phi_bb14_4, &phi_bb14_5, &phi_bb14_9);
    tmp29 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block16, phi_bb14_3, phi_bb14_4, phi_bb14_5, phi_bb14_9, tmp29);
  }

  TNode<Smi> phi_bb15_3;
  TNode<Smi> phi_bb15_4;
  TNode<Smi> phi_bb15_5;
  TNode<Smi> phi_bb15_9;
  TNode<Smi> tmp30;
  TNode<BoolT> tmp31;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_3, &phi_bb15_4, &phi_bb15_5, &phi_bb15_9);
    tmp30 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x20ull));
    tmp31 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp30}, TNode<Smi>{phi_bb11_10});
    ca_.Branch(tmp31, &block17, std::vector<compiler::Node*>{phi_bb15_3, phi_bb15_4, phi_bb15_5, phi_bb15_9}, &block18, std::vector<compiler::Node*>{phi_bb15_3, phi_bb15_4, phi_bb15_5, phi_bb15_9});
  }

  TNode<Smi> phi_bb17_3;
  TNode<Smi> phi_bb17_4;
  TNode<Smi> phi_bb17_5;
  TNode<Smi> phi_bb17_9;
  TNode<Smi> tmp32;
  TNode<BoolT> tmp33;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_3, &phi_bb17_4, &phi_bb17_5, &phi_bb17_9);
    tmp32 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x40ull));
    tmp33 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{phi_bb11_10}, TNode<Smi>{tmp32});
    ca_.Goto(&block19, phi_bb17_3, phi_bb17_4, phi_bb17_5, phi_bb17_9, tmp33);
  }

  TNode<Smi> phi_bb18_3;
  TNode<Smi> phi_bb18_4;
  TNode<Smi> phi_bb18_5;
  TNode<Smi> phi_bb18_9;
  TNode<BoolT> tmp34;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_3, &phi_bb18_4, &phi_bb18_5, &phi_bb18_9);
    tmp34 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block19, phi_bb18_3, phi_bb18_4, phi_bb18_5, phi_bb18_9, tmp34);
  }

  TNode<Smi> phi_bb19_3;
  TNode<Smi> phi_bb19_4;
  TNode<Smi> phi_bb19_5;
  TNode<Smi> phi_bb19_9;
  TNode<BoolT> phi_bb19_13;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_3, &phi_bb19_4, &phi_bb19_5, &phi_bb19_9, &phi_bb19_13);
    ca_.Goto(&block16, phi_bb19_3, phi_bb19_4, phi_bb19_5, phi_bb19_9, phi_bb19_13);
  }

  TNode<Smi> phi_bb16_3;
  TNode<Smi> phi_bb16_4;
  TNode<Smi> phi_bb16_5;
  TNode<Smi> phi_bb16_9;
  TNode<BoolT> phi_bb16_12;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_3, &phi_bb16_4, &phi_bb16_5, &phi_bb16_9, &phi_bb16_12);
    ca_.Branch(phi_bb16_12, &block12, std::vector<compiler::Node*>{phi_bb16_3, phi_bb16_4, phi_bb16_5, phi_bb16_9}, &block13, std::vector<compiler::Node*>{phi_bb16_3, phi_bb16_4, phi_bb16_5, phi_bb16_9});
  }

  TNode<Smi> phi_bb13_3;
  TNode<Smi> phi_bb13_4;
  TNode<Smi> phi_bb13_5;
  TNode<Smi> phi_bb13_9;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_3, &phi_bb13_4, &phi_bb13_5, &phi_bb13_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1296});
      CodeStubAssembler(state_).FailAssert("Torque assert 'length < 64 || (32 <= minRunLength && minRunLength <= 64)' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb12_3;
  TNode<Smi> phi_bb12_4;
  TNode<Smi> phi_bb12_5;
  TNode<Smi> phi_bb12_9;
  TNode<Smi> tmp35;
  TNode<Smi> tmp36;
  TNode<BoolT> tmp37;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_3, &phi_bb12_4, &phi_bb12_5, &phi_bb12_9);
    tmp35 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb12_9}, TNode<Smi>{phi_bb12_3});
    tmp36 = CountAndMakeRun_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb12_9}, TNode<Smi>{tmp35});
    tmp37 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp36}, TNode<Smi>{phi_bb11_10});
    ca_.Branch(tmp37, &block20, std::vector<compiler::Node*>{phi_bb12_3, phi_bb12_4, phi_bb12_5, phi_bb12_9}, &block21, std::vector<compiler::Node*>{phi_bb12_3, phi_bb12_4, phi_bb12_5, phi_bb12_9, tmp36});
  }

  TNode<Smi> phi_bb20_3;
  TNode<Smi> phi_bb20_4;
  TNode<Smi> phi_bb20_5;
  TNode<Smi> phi_bb20_9;
  TNode<Smi> tmp38;
  TNode<Smi> tmp39;
  TNode<Smi> tmp40;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_3, &phi_bb20_4, &phi_bb20_5, &phi_bb20_9);
    tmp38 = CodeStubAssembler(state_).SmiMin(TNode<Smi>{phi_bb11_10}, TNode<Smi>{phi_bb20_3});
    tmp39 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb20_9}, TNode<Smi>{tmp36});
    tmp40 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb20_9}, TNode<Smi>{tmp38});
    BinaryInsertionSort_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb20_9}, TNode<Smi>{tmp39}, TNode<Smi>{tmp40});
    ca_.Goto(&block21, phi_bb20_3, phi_bb20_4, phi_bb20_5, phi_bb20_9, tmp38);
  }

  TNode<Smi> phi_bb21_3;
  TNode<Smi> phi_bb21_4;
  TNode<Smi> phi_bb21_5;
  TNode<Smi> phi_bb21_9;
  TNode<Smi> phi_bb21_11;
  TNode<Smi> tmp41;
  TNode<Smi> tmp42;
  TNode<BoolT> tmp43;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_3, &phi_bb21_4, &phi_bb21_5, &phi_bb21_9, &phi_bb21_11);
    tmp41 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    tmp42 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp43 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp41}, TNode<Smi>{tmp42});
    ca_.Branch(tmp43, &block22, std::vector<compiler::Node*>{phi_bb21_3, phi_bb21_4, phi_bb21_5, phi_bb21_9}, &block23, std::vector<compiler::Node*>{phi_bb21_3, phi_bb21_4, phi_bb21_5, phi_bb21_9});
  }

  TNode<Smi> phi_bb22_3;
  TNode<Smi> phi_bb22_4;
  TNode<Smi> phi_bb22_5;
  TNode<Smi> phi_bb22_9;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_3, &phi_bb22_4, &phi_bb22_5, &phi_bb22_9);
    PushRun_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb22_9}, TNode<Smi>{phi_bb21_11});
    ca_.Goto(&block24, phi_bb22_3, phi_bb22_4, phi_bb22_5, phi_bb22_9, tmp41);
  }

  TNode<Smi> phi_bb23_3;
  TNode<Smi> phi_bb23_4;
  TNode<Smi> phi_bb23_5;
  TNode<Smi> phi_bb23_9;
  TNode<IntPtrT> tmp44;
  TNode<FixedArray> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<FixedArray> tmp47;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  TNode<Smi> tmp50;
  TNode<Smi> tmp51;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  TNode<Smi> tmp54;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_3, &phi_bb23_4, &phi_bb23_5, &phi_bb23_9);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp45 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp44});
    tmp46 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp47 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp46});
    tmp48 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp49 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp41}, TNode<Smi>{tmp48});
    tmp50 = GetPendingRunBase_0(state_, TNode<FixedArray>{tmp45}, TNode<Smi>{tmp49});
    tmp51 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp52 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp41}, TNode<Smi>{tmp51});
    tmp53 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp45}, TNode<Smi>{tmp52});
    tmp54 = NodePower_0(state_, TNode<Context>{p_context}, TNode<Smi>{tmp50}, TNode<Smi>{tmp53}, TNode<Smi>{phi_bb21_11}, TNode<Smi>{p_length});
    ca_.Goto(&block27, phi_bb23_3, phi_bb23_4, phi_bb23_5, phi_bb23_9, tmp41);
  }

  TNode<Smi> phi_bb27_3;
  TNode<Smi> phi_bb27_4;
  TNode<Smi> phi_bb27_5;
  TNode<Smi> phi_bb27_9;
  TNode<Smi> phi_bb27_12;
  TNode<Smi> tmp55;
  TNode<BoolT> tmp56;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_3, &phi_bb27_4, &phi_bb27_5, &phi_bb27_9, &phi_bb27_12);
    tmp55 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp56 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{phi_bb27_12}, TNode<Smi>{tmp55});
    ca_.Branch(tmp56, &block28, std::vector<compiler::Node*>{phi_bb27_3, phi_bb27_4, phi_bb27_5, phi_bb27_9, phi_bb27_12}, &block29, std::vector<compiler::Node*>{phi_bb27_3, phi_bb27_4, phi_bb27_5, phi_bb27_9, phi_bb27_12});
  }

  TNode<Smi> phi_bb28_3;
  TNode<Smi> phi_bb28_4;
  TNode<Smi> phi_bb28_5;
  TNode<Smi> phi_bb28_9;
  TNode<Smi> phi_bb28_12;
  TNode<Smi> tmp57;
  TNode<Smi> tmp58;
  TNode<Smi> tmp59;
  TNode<BoolT> tmp60;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_3, &phi_bb28_4, &phi_bb28_5, &phi_bb28_9, &phi_bb28_12);
    tmp57 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp58 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb28_12}, TNode<Smi>{tmp57});
    tmp59 = GetPendingPower_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp47}, TNode<Smi>{tmp58});
    tmp60 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp59}, TNode<Smi>{tmp54});
    ca_.Goto(&block30, phi_bb28_3, phi_bb28_4, phi_bb28_5, phi_bb28_9, phi_bb28_12, tmp60);
  }

  TNode<Smi> phi_bb29_3;
  TNode<Smi> phi_bb29_4;
  TNode<Smi> phi_bb29_5;
  TNode<Smi> phi_bb29_9;
  TNode<Smi> phi_bb29_12;
  TNode<BoolT> tmp61;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_3, &phi_bb29_4, &phi_bb29_5, &phi_bb29_9, &phi_bb29_12);
    tmp61 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block30, phi_bb29_3, phi_bb29_4, phi_bb29_5, phi_bb29_9, phi_bb29_12, tmp61);
  }

  TNode<Smi> phi_bb30_3;
  TNode<Smi> phi_bb30_4;
  TNode<Smi> phi_bb30_5;
  TNode<Smi> phi_bb30_9;
  TNode<Smi> phi_bb30_12;
  TNode<BoolT> phi_bb30_19;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_3, &phi_bb30_4, &phi_bb30_5, &phi_bb30_9, &phi_bb30_12, &phi_bb30_19);
    ca_.Branch(phi_bb30_19, &block25, std::vector<compiler::Node*>{phi_bb30_3, phi_bb30_4, phi_bb30_5, phi_bb30_9, phi_bb30_12}, &block26, std::vector<compiler::Node*>{phi_bb30_3, phi_bb30_4, phi_bb30_5, phi_bb30_9, phi_bb30_12});
  }

  TNode<Smi> phi_bb25_3;
  TNode<Smi> phi_bb25_4;
  TNode<Smi> phi_bb25_5;
  TNode<Smi> phi_bb25_9;
  TNode<Smi> phi_bb25_12;
  TNode<Smi> tmp62;
  TNode<Smi> tmp63;
  TNode<Smi> tmp64;
  TNode<Smi> tmp65;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_3, &phi_bb25_4, &phi_bb25_5, &phi_bb25_9, &phi_bb25_12);
    tmp62 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp63 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb25_12}, TNode<Smi>{tmp62});
    tmp64 = ca_.CallBuiltin<Smi>(Builtin::kMergeAt, p_context, p_sortState, tmp63);
    tmp65 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    ca_.Goto(&block27, phi_bb25_3, phi_bb25_4, phi_bb25_5, phi_bb25_9, tmp65);
  }

  TNode<Smi> phi_bb26_3;
  TNode<Smi> phi_bb26_4;
  TNode<Smi> phi_bb26_5;
  TNode<Smi> phi_bb26_9;
  TNode<Smi> phi_bb26_12;
  TNode<Smi> tmp66;
  TNode<BoolT> tmp67;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_3, &phi_bb26_4, &phi_bb26_5, &phi_bb26_9, &phi_bb26_12);
    tmp66 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp67 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb26_12}, TNode<Smi>{tmp66});
    ca_.Branch(tmp67, &block33, std::vector<compiler::Node*>{phi_bb26_3, phi_bb26_4, phi_bb26_5, phi_bb26_9, phi_bb26_12}, &block34, std::vector<compiler::Node*>{phi_bb26_3, phi_bb26_4, phi_bb26_5, phi_bb26_9, phi_bb26_12});
  }

  TNode<Smi> phi_bb33_3;
  TNode<Smi> phi_bb33_4;
  TNode<Smi> phi_bb33_5;
  TNode<Smi> phi_bb33_9;
  TNode<Smi> phi_bb33_12;
  TNode<BoolT> tmp68;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_3, &phi_bb33_4, &phi_bb33_5, &phi_bb33_9, &phi_bb33_12);
    tmp68 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block35, phi_bb33_3, phi_bb33_4, phi_bb33_5, phi_bb33_9, phi_bb33_12, tmp68);
  }

  TNode<Smi> phi_bb34_3;
  TNode<Smi> phi_bb34_4;
  TNode<Smi> phi_bb34_5;
  TNode<Smi> phi_bb34_9;
  TNode<Smi> phi_bb34_12;
  TNode<Smi> tmp69;
  TNode<Smi> tmp70;
  TNode<Smi> tmp71;
  TNode<BoolT> tmp72;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_3, &phi_bb34_4, &phi_bb34_5, &phi_bb34_9, &phi_bb34_12);
    tmp69 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp70 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb34_12}, TNode<Smi>{tmp69});
    tmp71 = GetPendingPower_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp47}, TNode<Smi>{tmp70});
    tmp72 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp71}, TNode<Smi>{tmp54});
    ca_.Goto(&block35, phi_bb34_3, phi_bb34_4, phi_bb34_5, phi_bb34_9, phi_bb34_12, tmp72);
  }

  TNode<Smi> phi_bb35_3;
  TNode<Smi> phi_bb35_4;
  TNode<Smi> phi_bb35_5;
  TNode<Smi> phi_bb35_9;
  TNode<Smi> phi_bb35_12;
  TNode<BoolT> phi_bb35_19;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_3, &phi_bb35_4, &phi_bb35_5, &phi_bb35_9, &phi_bb35_12, &phi_bb35_19);
    ca_.Branch(phi_bb35_19, &block31, std::vector<compiler::Node*>{phi_bb35_3, phi_bb35_4, phi_bb35_5, phi_bb35_9, phi_bb35_12}, &block32, std::vector<compiler::Node*>{phi_bb35_3, phi_bb35_4, phi_bb35_5, phi_bb35_9, phi_bb35_12});
  }

  TNode<Smi> phi_bb32_3;
  TNode<Smi> phi_bb32_4;
  TNode<Smi> phi_bb32_5;
  TNode<Smi> phi_bb32_9;
  TNode<Smi> phi_bb32_12;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_3, &phi_bb32_4, &phi_bb32_5, &phi_bb32_9, &phi_bb32_12);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1323});
      CodeStubAssembler(state_).FailAssert("Torque assert 'stackSize < 2 || GetPendingPower(pendingPowers, stackSize - 2) < p' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb31_3;
  TNode<Smi> phi_bb31_4;
  TNode<Smi> phi_bb31_5;
  TNode<Smi> phi_bb31_9;
  TNode<Smi> phi_bb31_12;
  TNode<Smi> tmp73;
  TNode<Smi> tmp74;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_3, &phi_bb31_4, &phi_bb31_5, &phi_bb31_9, &phi_bb31_12);
    tmp73 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp74 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb31_12}, TNode<Smi>{tmp73});
    SetPendingPower_0(state_, TNode<FixedArray>{tmp47}, TNode<Smi>{tmp74}, TNode<Smi>{tmp54});
    PushRun_0(state_, TNode<Context>{p_context}, TNode<SortState>{p_sortState}, TNode<Smi>{phi_bb31_9}, TNode<Smi>{phi_bb21_11});
    ca_.Goto(&block24, phi_bb31_3, phi_bb31_4, phi_bb31_5, phi_bb31_9, phi_bb31_12);
  }

  TNode<Smi> phi_bb24_3;
  TNode<Smi> phi_bb24_4;
  TNode<Smi> phi_bb24_5;
  TNode<Smi> phi_bb24_9;
  TNode<Smi> phi_bb24_12;
  TNode<Smi> tmp75;
  TNode<Smi> tmp76;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_3, &phi_bb24_4, &phi_bb24_5, &phi_bb24_9, &phi_bb24_12);
    tmp75 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb24_9}, TNode<Smi>{phi_bb21_11});
    tmp76 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{phi_bb24_3}, TNode<Smi>{phi_bb21_11});
    ca_.Goto(&block9, tmp76, phi_bb24_4, phi_bb24_5, phi_bb11_8, tmp75);
  }

  TNode<Smi> phi_bb8_3;
  TNode<Smi> phi_bb8_4;
  TNode<Smi> phi_bb8_5;
  TNode<Smi> phi_bb8_8;
  TNode<Smi> phi_bb8_9;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_3, &phi_bb8_4, &phi_bb8_5, &phi_bb8_8, &phi_bb8_9);
    ca_.Goto(&block38, phi_bb8_3, phi_bb8_4, phi_bb8_5, phi_bb8_8, phi_bb8_9);
  }

  TNode<Smi> phi_bb38_3;
  TNode<Smi> phi_bb38_4;
  TNode<Smi> phi_bb38_5;
  TNode<Smi> phi_bb38_8;
  TNode<Smi> phi_bb38_9;
  TNode<Smi> tmp77;
  TNode<Smi> tmp78;
  TNode<BoolT> tmp79;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_3, &phi_bb38_4, &phi_bb38_5, &phi_bb38_8, &phi_bb38_9);
    tmp77 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    tmp78 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp79 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp77}, TNode<Smi>{tmp78});
    ca_.Branch(tmp79, &block36, std::vector<compiler::Node*>{phi_bb38_3, phi_bb38_4, phi_bb38_5, phi_bb38_8, phi_bb38_9}, &block37, std::vector<compiler::Node*>{phi_bb38_3, phi_bb38_4, phi_bb38_5, phi_bb38_8, phi_bb38_9});
  }

  TNode<Smi> phi_bb36_3;
  TNode<Smi> phi_bb36_4;
  TNode<Smi> phi_bb36_5;
  TNode<Smi> phi_bb36_8;
  TNode<Smi> phi_bb36_9;
  TNode<Smi> tmp80;
  TNode<Smi> tmp81;
  TNode<Smi> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<FixedArray> tmp84;
  TNode<Smi> tmp85;
  TNode<BoolT> tmp86;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_3, &phi_bb36_4, &phi_bb36_5, &phi_bb36_8, &phi_bb36_9);
    tmp80 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    tmp81 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp82 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp80}, TNode<Smi>{tmp81});
    tmp83 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp84 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp83});
    tmp85 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp86 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp82}, TNode<Smi>{tmp85});
    ca_.Branch(tmp86, &block41, std::vector<compiler::Node*>{phi_bb36_3, phi_bb36_4, phi_bb36_5, phi_bb36_8, phi_bb36_9}, &block42, std::vector<compiler::Node*>{phi_bb36_3, phi_bb36_4, phi_bb36_5, phi_bb36_8, phi_bb36_9});
  }

  TNode<Smi> phi_bb41_3;
  TNode<Smi> phi_bb41_4;
  TNode<Smi> phi_bb41_5;
  TNode<Smi> phi_bb41_8;
  TNode<Smi> phi_bb41_9;
  TNode<Smi> tmp87;
  TNode<Smi> tmp88;
  TNode<Smi> tmp89;
  TNode<Smi> tmp90;
  TNode<Smi> tmp91;
  TNode<Smi> tmp92;
  TNode<BoolT> tmp93;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_3, &phi_bb41_4, &phi_bb41_5, &phi_bb41_8, &phi_bb41_9);
    tmp87 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp88 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp82}, TNode<Smi>{tmp87});
    tmp89 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp84}, TNode<Smi>{tmp88});
    tmp90 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp91 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp82}, TNode<Smi>{tmp90});
    tmp92 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp84}, TNode<Smi>{tmp91});
    tmp93 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp89}, TNode<Smi>{tmp92});
    ca_.Goto(&block43, phi_bb41_3, phi_bb41_4, phi_bb41_5, phi_bb41_8, phi_bb41_9, tmp93);
  }

  TNode<Smi> phi_bb42_3;
  TNode<Smi> phi_bb42_4;
  TNode<Smi> phi_bb42_5;
  TNode<Smi> phi_bb42_8;
  TNode<Smi> phi_bb42_9;
  TNode<BoolT> tmp94;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_3, &phi_bb42_4, &phi_bb42_5, &phi_bb42_8, &phi_bb42_9);
    tmp94 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block43, phi_bb42_3, phi_bb42_4, phi_bb42_5, phi_bb42_8, phi_bb42_9, tmp94);
  }

  TNode<Smi> phi_bb43_3;
  TNode<Smi> phi_bb43_4;
  TNode<Smi> phi_bb43_5;
  TNode<Smi> phi_bb43_8;
  TNode<Smi> phi_bb43_9;
  TNode<BoolT> phi_bb43_13;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_3, &phi_bb43_4, &phi_bb43_5, &phi_bb43_8, &phi_bb43_9, &phi_bb43_13);
    ca_.Branch(phi_bb43_13, &block39, std::vector<compiler::Node*>{phi_bb43_3, phi_bb43_4, phi_bb43_5, phi_bb43_8, phi_bb43_9}, &block40, std::vector<compiler::Node*>{phi_bb43_3, phi_bb43_4, phi_bb43_5, phi_bb43_8, phi_bb43_9, tmp82});
  }

  TNode<Smi> phi_bb39_3;
  TNode<Smi> phi_bb39_4;
  TNode<Smi> phi_bb39_5;
  TNode<Smi> phi_bb39_8;
  TNode<Smi> phi_bb39_9;
  TNode<Smi> tmp95;
  TNode<Smi> tmp96;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_3, &phi_bb39_4, &phi_bb39_5, &phi_bb39_8, &phi_bb39_9);
    tmp95 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp96 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp82}, TNode<Smi>{tmp95});
    ca_.Goto(&block40, phi_bb39_3, phi_bb39_4, phi_bb39_5, phi_bb39_8, phi_bb39_9, tmp96);
  }

  TNode<Smi> phi_bb40_3;
  TNode<Smi> phi_bb40_4;
  TNode<Smi> phi_bb40_5;
  TNode<Smi> phi_bb40_8;
  TNode<Smi> phi_bb40_9;
  TNode<Smi> phi_bb40_10;
  TNode<Smi> tmp97;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_3, &phi_bb40_4, &phi_bb40_5, &phi_bb40_8, &phi_bb40_9, &phi_bb40_10);
    tmp97 = ca_.CallBuiltin<Smi>(Builtin::kMergeAt, p_context, p_sortState, phi_bb40_10);
    ca_.Goto(&block38, phi_bb40_3, phi_bb40_4, phi_bb40_5, phi_bb40_8, phi_bb40_9);
  }

  TNode<Smi> phi_bb37_3;
  TNode<Smi> phi_bb37_4;
  TNode<Smi> phi_bb37_5;
  TNode<Smi> phi_bb37_8;
  TNode<Smi> phi_bb37_9;
  TNode<Smi> tmp98;
  TNode<Smi> tmp99;
  TNode<BoolT> tmp100;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_3, &phi_bb37_4, &phi_bb37_5, &phi_bb37_8, &phi_bb37_9);
    tmp98 = GetPendingRunsSize_0(state_, TNode<SortState>{p_sortState});
    tmp99 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp100 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp98}, TNode<Smi>{tmp99});
    ca_.Branch(tmp100, &block44, std::vector<compiler::Node*>{phi_bb37_3, phi_bb37_4, phi_bb37_5, phi_bb37_8, phi_bb37_9}, &block45, std::vector<compiler::Node*>{phi_bb37_3, phi_bb37_4, phi_bb37_5, phi_bb37_8, phi_bb37_9});
  }

  TNode<Smi> phi_bb45_3;
  TNode<Smi> phi_bb45_4;
  TNode<Smi> phi_bb45_5;
  TNode<Smi> phi_bb45_8;
  TNode<Smi> phi_bb45_9;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_3, &phi_bb45_4, &phi_bb45_5, &phi_bb45_8, &phi_bb45_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1348});
      CodeStubAssembler(state_).FailAssert("Torque assert 'GetPendingRunsSize(sortState) == 1' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb44_3;
  TNode<Smi> phi_bb44_4;
  TNode<Smi> phi_bb44_5;
  TNode<Smi> phi_bb44_8;
  TNode<Smi> phi_bb44_9;
  TNode<IntPtrT> tmp101;
  TNode<FixedArray> tmp102;
  TNode<Smi> tmp103;
  TNode<Smi> tmp104;
  TNode<BoolT> tmp105;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_3, &phi_bb44_4, &phi_bb44_5, &phi_bb44_8, &phi_bb44_9);
    tmp101 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp102 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp101});
    tmp103 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp104 = GetPendingRunLength_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp102}, TNode<Smi>{tmp103});
    tmp105 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp104}, TNode<Smi>{p_length});
    ca_.Branch(tmp105, &block46, std::vector<compiler::Node*>{phi_bb44_3, phi_bb44_4, phi_bb44_5, phi_bb44_8, phi_bb44_9}, &block47, std::vector<compiler::Node*>{phi_bb44_3, phi_bb44_4, phi_bb44_5, phi_bb44_8, phi_bb44_9});
  }

  TNode<Smi> phi_bb47_3;
  TNode<Smi> phi_bb47_4;
  TNode<Smi> phi_bb47_5;
  TNode<Smi> phi_bb47_8;
  TNode<Smi> phi_bb47_9;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_3, &phi_bb47_4, &phi_bb47_5, &phi_bb47_8, &phi_bb47_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1349});
      CodeStubAssembler(state_).FailAssert("Torque assert 'GetPendingRunLength(sortState.pending_runs, 0) == length' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb46_3;
  TNode<Smi> phi_bb46_4;
  TNode<Smi> phi_bb46_5;
  TNode<Smi> phi_bb46_8;
  TNode<Smi> phi_bb46_9;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_3, &phi_bb46_4, &phi_bb46_5, &phi_bb46_8, &phi_bb46_9);
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block48);
  }

    ca_.Bind(&block48);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1352&c=1
TNode<Smi> CompactReceiverElementsIntoWorkArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, bool p_isToSorted) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BoolT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block52(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block76(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block82(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi, Smi, Smi> block83(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block87(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block88(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block92(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block91(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block94(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block96(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block105(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block106(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi> block109(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, BuiltinPtr> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block118(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block116(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block122(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block127(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block128(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block132(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block131(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block134(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block133(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block136(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi> block135(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block129(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, Smi, Smi, Smi, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block123(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi, Smi> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, Smi, Smi> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block145(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<FixedArray> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<Uint32T> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<Number> tmp9;
  TNode<BoolT> tmp10;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp3 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp2});
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<Uint32T>(CodeStubAssembler::Reference{tmp3, tmp4});
    tmp6 = Convert_intptr_uint32_0(state_, TNode<Uint32T>{tmp5});
    tmp7 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp9 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_sortState, tmp8});
    tmp10 = CodeStubAssembler(state_).IsNumberNormalized(TNode<Number>{tmp9});
    ca_.Branch(tmp10, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1364});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsNumberNormalized(receiverLength)' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp11;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp11 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{tmp9});
    ca_.Branch(tmp11, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp12;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp12 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp9});
    ca_.Goto(&block6, tmp12);
  }

  TNode<UintPtrT> tmp13;
  TNode<Smi> tmp14;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp13 = kSmiMax_0(state_);
    compiler::CodeAssemblerLabel label15(&ca_);
    tmp14 = Convert_PositiveSmi_uintptr_0(state_, TNode<UintPtrT>{tmp13}, &label15);
    ca_.Goto(&block10);
    if (label15.is_used()) {
      ca_.Bind(&label15);
      ca_.Goto(&block11);
    }
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at third_party/v8/builtins/array-sort.tq:1368:47");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block6, tmp14);
  }

  TNode<Smi> phi_bb6_6;
  TNode<Smi> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Boolean> tmp18;
  TNode<False> tmp19;
  TNode<BoolT> tmp20;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_6);
    tmp16 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp18 = CodeStubAssembler(state_).LoadReference<Boolean>(CodeStubAssembler::Reference{p_sortState, tmp17});
    tmp19 = False_0(state_);
    tmp20 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp18}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp19});
    ca_.Branch(tmp20, &block14, std::vector<compiler::Node*>{phi_bb6_6}, &block15, std::vector<compiler::Node*>{phi_bb6_6});
  }

  TNode<Smi> phi_bb14_6;
  TNode<IntPtrT> tmp21;
  TNode<JSReceiver> tmp22;
  TNode<BoolT> tmp23;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_6);
    tmp21 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp22 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp21});
    tmp23 = Is_FastJSArray_JSReceiver_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{tmp22});
    ca_.Goto(&block16, phi_bb14_6, tmp23);
  }

  TNode<Smi> phi_bb15_6;
  TNode<BoolT> tmp24;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_6);
    tmp24 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block16, phi_bb15_6, tmp24);
  }

  TNode<Smi> phi_bb16_6;
  TNode<BoolT> phi_bb16_9;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_6, &phi_bb16_9);
    ca_.Branch(phi_bb16_9, &block12, std::vector<compiler::Node*>{phi_bb16_6}, &block13, std::vector<compiler::Node*>{phi_bb16_6});
  }

  TNode<Smi> phi_bb12_6;
  TNode<IntPtrT> tmp25;
  TNode<JSReceiver> tmp26;
  TNode<JSArray> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Map> tmp29;
  TNode<Int32T> tmp30;
  TNode<BoolT> tmp31;
  TNode<BoolT> tmp32;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_6);
    tmp25 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp26 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp25});
    tmp27 = UnsafeCast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp26});
    tmp28 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp29 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp27, tmp28});
    tmp30 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp29});
    tmp31 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{tmp30});
    tmp32 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp31});
    ca_.Branch(tmp32, &block18, std::vector<compiler::Node*>{phi_bb12_6}, &block19, std::vector<compiler::Node*>{phi_bb12_6});
  }

  TNode<Smi> phi_bb18_6;
  TNode<IntPtrT> tmp33;
  TNode<FixedArrayBase> tmp34;
  TNode<FixedArray> tmp35;
  TNode<Smi> tmp36;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_6);
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp34 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp27, tmp33});
    tmp35 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp34});
    tmp36 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block23, tmp1, tmp6, tmp7, phi_bb18_6, tmp16, tmp36);
  }

  TNode<FixedArray> phi_bb23_2;
  TNode<IntPtrT> phi_bb23_3;
  TNode<IntPtrT> phi_bb23_4;
  TNode<Smi> phi_bb23_6;
  TNode<Smi> phi_bb23_7;
  TNode<Smi> phi_bb23_11;
  TNode<BoolT> tmp37;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_2, &phi_bb23_3, &phi_bb23_4, &phi_bb23_6, &phi_bb23_7, &phi_bb23_11);
    tmp37 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb23_11}, TNode<Number>{tmp9});
    ca_.Branch(tmp37, &block21, std::vector<compiler::Node*>{phi_bb23_2, phi_bb23_3, phi_bb23_4, phi_bb23_6, phi_bb23_7, phi_bb23_11}, &block22, std::vector<compiler::Node*>{phi_bb23_2, phi_bb23_3, phi_bb23_4, phi_bb23_6, phi_bb23_7, phi_bb23_11});
  }

  TNode<FixedArray> phi_bb21_2;
  TNode<IntPtrT> phi_bb21_3;
  TNode<IntPtrT> phi_bb21_4;
  TNode<Smi> phi_bb21_6;
  TNode<Smi> phi_bb21_7;
  TNode<Smi> phi_bb21_11;
  TNode<Union<HeapObject, TaggedIndex>> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<IntPtrT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<UintPtrT> tmp42;
  TNode<UintPtrT> tmp43;
  TNode<BoolT> tmp44;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_2, &phi_bb21_3, &phi_bb21_4, &phi_bb21_6, &phi_bb21_7, &phi_bb21_11);
    std::tie(tmp38, tmp39, tmp40) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp35}).Flatten();
    tmp41 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb21_11});
    tmp42 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp41});
    tmp43 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp40});
    tmp44 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp42}, TNode<UintPtrT>{tmp43});
    ca_.Branch(tmp44, &block29, std::vector<compiler::Node*>{phi_bb21_2, phi_bb21_3, phi_bb21_4, phi_bb21_6, phi_bb21_7, phi_bb21_11, phi_bb21_11, phi_bb21_11}, &block30, std::vector<compiler::Node*>{phi_bb21_2, phi_bb21_3, phi_bb21_4, phi_bb21_6, phi_bb21_7, phi_bb21_11, phi_bb21_11, phi_bb21_11});
  }

  TNode<FixedArray> phi_bb29_2;
  TNode<IntPtrT> phi_bb29_3;
  TNode<IntPtrT> phi_bb29_4;
  TNode<Smi> phi_bb29_6;
  TNode<Smi> phi_bb29_7;
  TNode<Smi> phi_bb29_11;
  TNode<Smi> phi_bb29_16;
  TNode<Smi> phi_bb29_17;
  TNode<IntPtrT> tmp45;
  TNode<IntPtrT> tmp46;
  TNode<Union<HeapObject, TaggedIndex>> tmp47;
  TNode<IntPtrT> tmp48;
  TNode<Object> tmp49;
  TNode<TheHole> tmp50;
  TNode<BoolT> tmp51;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_2, &phi_bb29_3, &phi_bb29_4, &phi_bb29_6, &phi_bb29_7, &phi_bb29_11, &phi_bb29_16, &phi_bb29_17);
    tmp45 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp41});
    tmp46 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp39}, TNode<IntPtrT>{tmp45});
    std::tie(tmp47, tmp48) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp38}, TNode<IntPtrT>{tmp46}).Flatten();
    tmp49 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp47, tmp48});
    tmp50 = TheHole_0(state_);
    tmp51 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp49}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp50});
    ca_.Branch(tmp51, &block33, std::vector<compiler::Node*>{phi_bb29_2, phi_bb29_3, phi_bb29_4, phi_bb29_6, phi_bb29_7, phi_bb29_11}, &block34, std::vector<compiler::Node*>{phi_bb29_2, phi_bb29_3, phi_bb29_4, phi_bb29_6, phi_bb29_7, phi_bb29_11});
  }

  TNode<FixedArray> phi_bb30_2;
  TNode<IntPtrT> phi_bb30_3;
  TNode<IntPtrT> phi_bb30_4;
  TNode<Smi> phi_bb30_6;
  TNode<Smi> phi_bb30_7;
  TNode<Smi> phi_bb30_11;
  TNode<Smi> phi_bb30_16;
  TNode<Smi> phi_bb30_17;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_2, &phi_bb30_3, &phi_bb30_4, &phi_bb30_6, &phi_bb30_7, &phi_bb30_11, &phi_bb30_16, &phi_bb30_17);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb33_2;
  TNode<IntPtrT> phi_bb33_3;
  TNode<IntPtrT> phi_bb33_4;
  TNode<Smi> phi_bb33_6;
  TNode<Smi> phi_bb33_7;
  TNode<Smi> phi_bb33_11;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_2, &phi_bb33_3, &phi_bb33_4, &phi_bb33_6, &phi_bb33_7, &phi_bb33_11);
    if ((p_isToSorted)) {
      ca_.Goto(&block36, phi_bb33_2, phi_bb33_3, phi_bb33_4, phi_bb33_6, phi_bb33_7, phi_bb33_11);
    } else {
      ca_.Goto(&block37, phi_bb33_2, phi_bb33_3, phi_bb33_4, phi_bb33_6, phi_bb33_7, phi_bb33_11);
    }
  }

  TNode<FixedArray> phi_bb36_2;
  TNode<IntPtrT> phi_bb36_3;
  TNode<IntPtrT> phi_bb36_4;
  TNode<Smi> phi_bb36_6;
  TNode<Smi> phi_bb36_7;
  TNode<Smi> phi_bb36_11;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_2, &phi_bb36_3, &phi_bb36_4, &phi_bb36_6, &phi_bb36_7, &phi_bb36_11);
    tmp52 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp53 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb36_7}, TNode<Smi>{tmp52});
    ca_.Goto(&block38, phi_bb36_2, phi_bb36_3, phi_bb36_4, phi_bb36_6, tmp53, phi_bb36_11);
  }

  TNode<FixedArray> phi_bb37_2;
  TNode<IntPtrT> phi_bb37_3;
  TNode<IntPtrT> phi_bb37_4;
  TNode<Smi> phi_bb37_6;
  TNode<Smi> phi_bb37_7;
  TNode<Smi> phi_bb37_11;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_2, &phi_bb37_3, &phi_bb37_4, &phi_bb37_6, &phi_bb37_7, &phi_bb37_11);
    ca_.Goto(&block38, phi_bb37_2, phi_bb37_3, phi_bb37_4, phi_bb37_6, phi_bb37_7, phi_bb37_11);
  }

  TNode<FixedArray> phi_bb38_2;
  TNode<IntPtrT> phi_bb38_3;
  TNode<IntPtrT> phi_bb38_4;
  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  TNode<Smi> phi_bb38_11;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_2, &phi_bb38_3, &phi_bb38_4, &phi_bb38_6, &phi_bb38_7, &phi_bb38_11);
    ca_.Goto(&block35, phi_bb38_2, phi_bb38_3, phi_bb38_4, phi_bb38_6, phi_bb38_7, phi_bb38_11);
  }

  TNode<FixedArray> phi_bb34_2;
  TNode<IntPtrT> phi_bb34_3;
  TNode<IntPtrT> phi_bb34_4;
  TNode<Smi> phi_bb34_6;
  TNode<Smi> phi_bb34_7;
  TNode<Smi> phi_bb34_11;
  TNode<Undefined> tmp54;
  TNode<BoolT> tmp55;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_2, &phi_bb34_3, &phi_bb34_4, &phi_bb34_6, &phi_bb34_7, &phi_bb34_11);
    tmp54 = Undefined_0(state_);
    tmp55 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp49}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp54});
    ca_.Branch(tmp55, &block39, std::vector<compiler::Node*>{phi_bb34_2, phi_bb34_3, phi_bb34_4, phi_bb34_6, phi_bb34_7, phi_bb34_11}, &block40, std::vector<compiler::Node*>{phi_bb34_2, phi_bb34_3, phi_bb34_4, phi_bb34_6, phi_bb34_7, phi_bb34_11});
  }

  TNode<FixedArray> phi_bb39_2;
  TNode<IntPtrT> phi_bb39_3;
  TNode<IntPtrT> phi_bb39_4;
  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<Smi> phi_bb39_11;
  TNode<Smi> tmp56;
  TNode<Smi> tmp57;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_2, &phi_bb39_3, &phi_bb39_4, &phi_bb39_6, &phi_bb39_7, &phi_bb39_11);
    tmp56 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp57 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb39_7}, TNode<Smi>{tmp56});
    ca_.Goto(&block41, phi_bb39_2, phi_bb39_3, phi_bb39_4, phi_bb39_6, tmp57, phi_bb39_11);
  }

  TNode<FixedArray> phi_bb40_2;
  TNode<IntPtrT> phi_bb40_3;
  TNode<IntPtrT> phi_bb40_4;
  TNode<Smi> phi_bb40_6;
  TNode<Smi> phi_bb40_7;
  TNode<Smi> phi_bb40_11;
  TNode<JSAny> tmp58;
  TNode<BoolT> tmp59;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_2, &phi_bb40_3, &phi_bb40_4, &phi_bb40_6, &phi_bb40_7, &phi_bb40_11);
    tmp58 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp49});
    tmp59 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb40_4}, TNode<IntPtrT>{phi_bb40_3});
    ca_.Branch(tmp59, &block44, std::vector<compiler::Node*>{phi_bb40_2, phi_bb40_3, phi_bb40_4, phi_bb40_6, phi_bb40_7, phi_bb40_11}, &block45, std::vector<compiler::Node*>{phi_bb40_2, phi_bb40_3, phi_bb40_4, phi_bb40_6, phi_bb40_7, phi_bb40_11});
  }

  TNode<FixedArray> phi_bb45_2;
  TNode<IntPtrT> phi_bb45_3;
  TNode<IntPtrT> phi_bb45_4;
  TNode<Smi> phi_bb45_6;
  TNode<Smi> phi_bb45_7;
  TNode<Smi> phi_bb45_11;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_2, &phi_bb45_3, &phi_bb45_4, &phi_bb45_6, &phi_bb45_7, &phi_bb45_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb44_2;
  TNode<IntPtrT> phi_bb44_3;
  TNode<IntPtrT> phi_bb44_4;
  TNode<Smi> phi_bb44_6;
  TNode<Smi> phi_bb44_7;
  TNode<Smi> phi_bb44_11;
  TNode<BoolT> tmp60;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_2, &phi_bb44_3, &phi_bb44_4, &phi_bb44_6, &phi_bb44_7, &phi_bb44_11);
    tmp60 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb44_3}, TNode<IntPtrT>{phi_bb44_4});
    ca_.Branch(tmp60, &block46, std::vector<compiler::Node*>{phi_bb44_2, phi_bb44_3, phi_bb44_4, phi_bb44_6, phi_bb44_7, phi_bb44_11}, &block47, std::vector<compiler::Node*>{phi_bb44_2, phi_bb44_3, phi_bb44_4, phi_bb44_6, phi_bb44_7, phi_bb44_11});
  }

  TNode<FixedArray> phi_bb46_2;
  TNode<IntPtrT> phi_bb46_3;
  TNode<IntPtrT> phi_bb46_4;
  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  TNode<Smi> phi_bb46_11;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<BoolT> tmp67;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_2, &phi_bb46_3, &phi_bb46_4, &phi_bb46_6, &phi_bb46_7, &phi_bb46_11);
    tmp61 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp62 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb46_3}, TNode<IntPtrT>{tmp61});
    tmp63 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb46_3}, TNode<IntPtrT>{tmp62});
    tmp64 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp65 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp63}, TNode<IntPtrT>{tmp64});
    tmp66 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp67 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb46_4}, TNode<IntPtrT>{tmp66});
    ca_.Branch(tmp67, &block49, std::vector<compiler::Node*>{phi_bb46_2, phi_bb46_4, phi_bb46_6, phi_bb46_7, phi_bb46_11}, &block50, std::vector<compiler::Node*>{phi_bb46_2, phi_bb46_4, phi_bb46_6, phi_bb46_7, phi_bb46_11});
  }

  TNode<FixedArray> phi_bb50_2;
  TNode<IntPtrT> phi_bb50_4;
  TNode<Smi> phi_bb50_6;
  TNode<Smi> phi_bb50_7;
  TNode<Smi> phi_bb50_11;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_2, &phi_bb50_4, &phi_bb50_6, &phi_bb50_7, &phi_bb50_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb49_2;
  TNode<IntPtrT> phi_bb49_4;
  TNode<Smi> phi_bb49_6;
  TNode<Smi> phi_bb49_7;
  TNode<Smi> phi_bb49_11;
  TNode<IntPtrT> tmp68;
  TNode<BoolT> tmp69;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_2, &phi_bb49_4, &phi_bb49_6, &phi_bb49_7, &phi_bb49_11);
    tmp68 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp69 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp65}, TNode<IntPtrT>{tmp68});
    ca_.Branch(tmp69, &block51, std::vector<compiler::Node*>{phi_bb49_2, phi_bb49_4, phi_bb49_6, phi_bb49_7, phi_bb49_11}, &block52, std::vector<compiler::Node*>{phi_bb49_2, phi_bb49_4, phi_bb49_6, phi_bb49_7, phi_bb49_11});
  }

  TNode<FixedArray> phi_bb52_2;
  TNode<IntPtrT> phi_bb52_4;
  TNode<Smi> phi_bb52_6;
  TNode<Smi> phi_bb52_7;
  TNode<Smi> phi_bb52_11;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_2, &phi_bb52_4, &phi_bb52_6, &phi_bb52_7, &phi_bb52_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb51_2;
  TNode<IntPtrT> phi_bb51_4;
  TNode<Smi> phi_bb51_6;
  TNode<Smi> phi_bb51_7;
  TNode<Smi> phi_bb51_11;
  TNode<BoolT> tmp70;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_2, &phi_bb51_4, &phi_bb51_6, &phi_bb51_7, &phi_bb51_11);
    tmp70 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp65}, TNode<IntPtrT>{phi_bb51_4});
    ca_.Branch(tmp70, &block53, std::vector<compiler::Node*>{phi_bb51_2, phi_bb51_4, phi_bb51_6, phi_bb51_7, phi_bb51_11}, &block54, std::vector<compiler::Node*>{phi_bb51_2, phi_bb51_4, phi_bb51_6, phi_bb51_7, phi_bb51_11});
  }

  TNode<FixedArray> phi_bb54_2;
  TNode<IntPtrT> phi_bb54_4;
  TNode<Smi> phi_bb54_6;
  TNode<Smi> phi_bb54_7;
  TNode<Smi> phi_bb54_11;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_2, &phi_bb54_4, &phi_bb54_6, &phi_bb54_7, &phi_bb54_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb53_2;
  TNode<IntPtrT> phi_bb53_4;
  TNode<Smi> phi_bb53_6;
  TNode<Smi> phi_bb53_7;
  TNode<Smi> phi_bb53_11;
  TNode<IntPtrT> tmp71;
  TNode<TheHole> tmp72;
  TNode<FixedArray> tmp73;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_2, &phi_bb53_4, &phi_bb53_6, &phi_bb53_7, &phi_bb53_11);
    tmp71 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp72 = TheHole_0(state_);
    tmp73 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb53_2}, TNode<IntPtrT>{tmp71}, TNode<IntPtrT>{phi_bb53_4}, TNode<IntPtrT>{tmp65}, TNode<Hole>{tmp72});
    ca_.Goto(&block47, tmp73, tmp65, phi_bb53_4, phi_bb53_6, phi_bb53_7, phi_bb53_11);
  }

  TNode<FixedArray> phi_bb47_2;
  TNode<IntPtrT> phi_bb47_3;
  TNode<IntPtrT> phi_bb47_4;
  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  TNode<Smi> phi_bb47_11;
  TNode<Union<HeapObject, TaggedIndex>> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<UintPtrT> tmp79;
  TNode<UintPtrT> tmp80;
  TNode<BoolT> tmp81;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_2, &phi_bb47_3, &phi_bb47_4, &phi_bb47_6, &phi_bb47_7, &phi_bb47_11);
    std::tie(tmp74, tmp75, tmp76) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb47_2}).Flatten();
    tmp77 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp78 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb47_4}, TNode<IntPtrT>{tmp77});
    tmp79 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb47_4});
    tmp80 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp76});
    tmp81 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp79}, TNode<UintPtrT>{tmp80});
    ca_.Branch(tmp81, &block59, std::vector<compiler::Node*>{phi_bb47_2, phi_bb47_3, phi_bb47_6, phi_bb47_7, phi_bb47_11, phi_bb47_2, phi_bb47_4, phi_bb47_4, phi_bb47_4, phi_bb47_4}, &block60, std::vector<compiler::Node*>{phi_bb47_2, phi_bb47_3, phi_bb47_6, phi_bb47_7, phi_bb47_11, phi_bb47_2, phi_bb47_4, phi_bb47_4, phi_bb47_4, phi_bb47_4});
  }

  TNode<FixedArray> phi_bb59_2;
  TNode<IntPtrT> phi_bb59_3;
  TNode<Smi> phi_bb59_6;
  TNode<Smi> phi_bb59_7;
  TNode<Smi> phi_bb59_11;
  TNode<FixedArray> phi_bb59_15;
  TNode<IntPtrT> phi_bb59_19;
  TNode<IntPtrT> phi_bb59_20;
  TNode<IntPtrT> phi_bb59_24;
  TNode<IntPtrT> phi_bb59_25;
  TNode<IntPtrT> tmp82;
  TNode<IntPtrT> tmp83;
  TNode<Union<HeapObject, TaggedIndex>> tmp84;
  TNode<IntPtrT> tmp85;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_2, &phi_bb59_3, &phi_bb59_6, &phi_bb59_7, &phi_bb59_11, &phi_bb59_15, &phi_bb59_19, &phi_bb59_20, &phi_bb59_24, &phi_bb59_25);
    tmp82 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb59_25});
    tmp83 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp75}, TNode<IntPtrT>{tmp82});
    std::tie(tmp84, tmp85) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp74}, TNode<IntPtrT>{tmp83}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp84, tmp85}, tmp58);
    ca_.Goto(&block41, phi_bb59_2, phi_bb59_3, tmp78, phi_bb59_6, phi_bb59_7, phi_bb59_11);
  }

  TNode<FixedArray> phi_bb60_2;
  TNode<IntPtrT> phi_bb60_3;
  TNode<Smi> phi_bb60_6;
  TNode<Smi> phi_bb60_7;
  TNode<Smi> phi_bb60_11;
  TNode<FixedArray> phi_bb60_15;
  TNode<IntPtrT> phi_bb60_19;
  TNode<IntPtrT> phi_bb60_20;
  TNode<IntPtrT> phi_bb60_24;
  TNode<IntPtrT> phi_bb60_25;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_2, &phi_bb60_3, &phi_bb60_6, &phi_bb60_7, &phi_bb60_11, &phi_bb60_15, &phi_bb60_19, &phi_bb60_20, &phi_bb60_24, &phi_bb60_25);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb41_2;
  TNode<IntPtrT> phi_bb41_3;
  TNode<IntPtrT> phi_bb41_4;
  TNode<Smi> phi_bb41_6;
  TNode<Smi> phi_bb41_7;
  TNode<Smi> phi_bb41_11;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_2, &phi_bb41_3, &phi_bb41_4, &phi_bb41_6, &phi_bb41_7, &phi_bb41_11);
    ca_.Goto(&block35, phi_bb41_2, phi_bb41_3, phi_bb41_4, phi_bb41_6, phi_bb41_7, phi_bb41_11);
  }

  TNode<FixedArray> phi_bb35_2;
  TNode<IntPtrT> phi_bb35_3;
  TNode<IntPtrT> phi_bb35_4;
  TNode<Smi> phi_bb35_6;
  TNode<Smi> phi_bb35_7;
  TNode<Smi> phi_bb35_11;
  TNode<Smi> tmp86;
  TNode<Smi> tmp87;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_2, &phi_bb35_3, &phi_bb35_4, &phi_bb35_6, &phi_bb35_7, &phi_bb35_11);
    tmp86 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp87 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb35_11}, TNode<Smi>{tmp86});
    ca_.Goto(&block23, phi_bb35_2, phi_bb35_3, phi_bb35_4, phi_bb35_6, phi_bb35_7, tmp87);
  }

  TNode<FixedArray> phi_bb22_2;
  TNode<IntPtrT> phi_bb22_3;
  TNode<IntPtrT> phi_bb22_4;
  TNode<Smi> phi_bb22_6;
  TNode<Smi> phi_bb22_7;
  TNode<Smi> phi_bb22_11;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_2, &phi_bb22_3, &phi_bb22_4, &phi_bb22_6, &phi_bb22_7, &phi_bb22_11);
    ca_.Goto(&block20, phi_bb22_2, phi_bb22_3, phi_bb22_4, phi_bb22_6, phi_bb22_7);
  }

  TNode<Smi> phi_bb19_6;
  TNode<IntPtrT> tmp88;
  TNode<FixedArrayBase> tmp89;
  TNode<FixedDoubleArray> tmp90;
  TNode<Smi> tmp91;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_6);
    tmp88 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp89 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp27, tmp88});
    tmp90 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp89});
    tmp91 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block65, tmp1, tmp6, tmp7, phi_bb19_6, tmp16, tmp91);
  }

  TNode<FixedArray> phi_bb65_2;
  TNode<IntPtrT> phi_bb65_3;
  TNode<IntPtrT> phi_bb65_4;
  TNode<Smi> phi_bb65_6;
  TNode<Smi> phi_bb65_7;
  TNode<Smi> phi_bb65_11;
  TNode<BoolT> tmp92;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_2, &phi_bb65_3, &phi_bb65_4, &phi_bb65_6, &phi_bb65_7, &phi_bb65_11);
    tmp92 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb65_11}, TNode<Number>{tmp9});
    ca_.Branch(tmp92, &block63, std::vector<compiler::Node*>{phi_bb65_2, phi_bb65_3, phi_bb65_4, phi_bb65_6, phi_bb65_7, phi_bb65_11}, &block64, std::vector<compiler::Node*>{phi_bb65_2, phi_bb65_3, phi_bb65_4, phi_bb65_6, phi_bb65_7, phi_bb65_11});
  }

  TNode<FixedArray> phi_bb63_2;
  TNode<IntPtrT> phi_bb63_3;
  TNode<IntPtrT> phi_bb63_4;
  TNode<Smi> phi_bb63_6;
  TNode<Smi> phi_bb63_7;
  TNode<Smi> phi_bb63_11;
  TNode<Union<HeapObject, TaggedIndex>> tmp93;
  TNode<IntPtrT> tmp94;
  TNode<IntPtrT> tmp95;
  TNode<IntPtrT> tmp96;
  TNode<UintPtrT> tmp97;
  TNode<UintPtrT> tmp98;
  TNode<BoolT> tmp99;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_2, &phi_bb63_3, &phi_bb63_4, &phi_bb63_6, &phi_bb63_7, &phi_bb63_11);
    std::tie(tmp93, tmp94, tmp95) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp90}).Flatten();
    tmp96 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb63_11});
    tmp97 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp96});
    tmp98 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp95});
    tmp99 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp97}, TNode<UintPtrT>{tmp98});
    ca_.Branch(tmp99, &block75, std::vector<compiler::Node*>{phi_bb63_2, phi_bb63_3, phi_bb63_4, phi_bb63_6, phi_bb63_7, phi_bb63_11, phi_bb63_11, phi_bb63_11}, &block76, std::vector<compiler::Node*>{phi_bb63_2, phi_bb63_3, phi_bb63_4, phi_bb63_6, phi_bb63_7, phi_bb63_11, phi_bb63_11, phi_bb63_11});
  }

  TNode<FixedArray> phi_bb75_2;
  TNode<IntPtrT> phi_bb75_3;
  TNode<IntPtrT> phi_bb75_4;
  TNode<Smi> phi_bb75_6;
  TNode<Smi> phi_bb75_7;
  TNode<Smi> phi_bb75_11;
  TNode<Smi> phi_bb75_16;
  TNode<Smi> phi_bb75_17;
  TNode<IntPtrT> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<Union<HeapObject, TaggedIndex>> tmp102;
  TNode<IntPtrT> tmp103;
  TNode<BoolT> tmp104;
  TNode<BoolT> tmp105;
  TNode<Float64T> tmp106;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_2, &phi_bb75_3, &phi_bb75_4, &phi_bb75_6, &phi_bb75_7, &phi_bb75_11, &phi_bb75_16, &phi_bb75_17);
    tmp100 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp96});
    tmp101 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp94}, TNode<IntPtrT>{tmp100});
    std::tie(tmp102, tmp103) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp93}, TNode<IntPtrT>{tmp101}).Flatten();
    std::tie(tmp104, tmp105, tmp106) = LoadFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp102}, TNode<IntPtrT>{tmp103}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp104, &block80, std::vector<compiler::Node*>{phi_bb75_2, phi_bb75_3, phi_bb75_4, phi_bb75_6, phi_bb75_7, phi_bb75_11, phi_bb75_16, phi_bb75_17}, &block81, std::vector<compiler::Node*>{phi_bb75_2, phi_bb75_3, phi_bb75_4, phi_bb75_6, phi_bb75_7, phi_bb75_11, phi_bb75_16, phi_bb75_17});
  }

  TNode<FixedArray> phi_bb76_2;
  TNode<IntPtrT> phi_bb76_3;
  TNode<IntPtrT> phi_bb76_4;
  TNode<Smi> phi_bb76_6;
  TNode<Smi> phi_bb76_7;
  TNode<Smi> phi_bb76_11;
  TNode<Smi> phi_bb76_16;
  TNode<Smi> phi_bb76_17;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_2, &phi_bb76_3, &phi_bb76_4, &phi_bb76_6, &phi_bb76_7, &phi_bb76_11, &phi_bb76_16, &phi_bb76_17);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb80_2;
  TNode<IntPtrT> phi_bb80_3;
  TNode<IntPtrT> phi_bb80_4;
  TNode<Smi> phi_bb80_6;
  TNode<Smi> phi_bb80_7;
  TNode<Smi> phi_bb80_11;
  TNode<Smi> phi_bb80_16;
  TNode<Smi> phi_bb80_17;
  TNode<Smi> tmp107;
  TNode<Smi> tmp108;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_2, &phi_bb80_3, &phi_bb80_4, &phi_bb80_6, &phi_bb80_7, &phi_bb80_11, &phi_bb80_16, &phi_bb80_17);
    tmp107 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp108 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb80_7}, TNode<Smi>{tmp107});
    ca_.Goto(&block69, phi_bb80_2, phi_bb80_3, phi_bb80_4, phi_bb80_6, tmp108, phi_bb80_11);
  }

  TNode<FixedArray> phi_bb81_2;
  TNode<IntPtrT> phi_bb81_3;
  TNode<IntPtrT> phi_bb81_4;
  TNode<Smi> phi_bb81_6;
  TNode<Smi> phi_bb81_7;
  TNode<Smi> phi_bb81_11;
  TNode<Smi> phi_bb81_16;
  TNode<Smi> phi_bb81_17;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_2, &phi_bb81_3, &phi_bb81_4, &phi_bb81_6, &phi_bb81_7, &phi_bb81_11, &phi_bb81_16, &phi_bb81_17);
    ca_.Branch(tmp105, &block82, std::vector<compiler::Node*>{phi_bb81_2, phi_bb81_3, phi_bb81_4, phi_bb81_6, phi_bb81_7, phi_bb81_11, phi_bb81_16, phi_bb81_17}, &block83, std::vector<compiler::Node*>{phi_bb81_2, phi_bb81_3, phi_bb81_4, phi_bb81_6, phi_bb81_7, phi_bb81_11, phi_bb81_16, phi_bb81_17});
  }

  TNode<FixedArray> phi_bb82_2;
  TNode<IntPtrT> phi_bb82_3;
  TNode<IntPtrT> phi_bb82_4;
  TNode<Smi> phi_bb82_6;
  TNode<Smi> phi_bb82_7;
  TNode<Smi> phi_bb82_11;
  TNode<Smi> phi_bb82_16;
  TNode<Smi> phi_bb82_17;
  if (block82.is_used()) {
    ca_.Bind(&block82, &phi_bb82_2, &phi_bb82_3, &phi_bb82_4, &phi_bb82_6, &phi_bb82_7, &phi_bb82_11, &phi_bb82_16, &phi_bb82_17);
    if ((p_isToSorted)) {
      ca_.Goto(&block105, phi_bb82_2, phi_bb82_3, phi_bb82_4, phi_bb82_6, phi_bb82_7, phi_bb82_11);
    } else {
      ca_.Goto(&block106, phi_bb82_2, phi_bb82_3, phi_bb82_4, phi_bb82_6, phi_bb82_7, phi_bb82_11);
    }
  }

  TNode<FixedArray> phi_bb83_2;
  TNode<IntPtrT> phi_bb83_3;
  TNode<IntPtrT> phi_bb83_4;
  TNode<Smi> phi_bb83_6;
  TNode<Smi> phi_bb83_7;
  TNode<Smi> phi_bb83_11;
  TNode<Smi> phi_bb83_16;
  TNode<Smi> phi_bb83_17;
  TNode<HeapNumber> tmp109;
  TNode<BoolT> tmp110;
  if (block83.is_used()) {
    ca_.Bind(&block83, &phi_bb83_2, &phi_bb83_3, &phi_bb83_4, &phi_bb83_6, &phi_bb83_7, &phi_bb83_11, &phi_bb83_16, &phi_bb83_17);
    tmp109 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp106});
    tmp110 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb83_4}, TNode<IntPtrT>{phi_bb83_3});
    ca_.Branch(tmp110, &block86, std::vector<compiler::Node*>{phi_bb83_2, phi_bb83_3, phi_bb83_4, phi_bb83_6, phi_bb83_7, phi_bb83_11}, &block87, std::vector<compiler::Node*>{phi_bb83_2, phi_bb83_3, phi_bb83_4, phi_bb83_6, phi_bb83_7, phi_bb83_11});
  }

  TNode<FixedArray> phi_bb87_2;
  TNode<IntPtrT> phi_bb87_3;
  TNode<IntPtrT> phi_bb87_4;
  TNode<Smi> phi_bb87_6;
  TNode<Smi> phi_bb87_7;
  TNode<Smi> phi_bb87_11;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_2, &phi_bb87_3, &phi_bb87_4, &phi_bb87_6, &phi_bb87_7, &phi_bb87_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb86_2;
  TNode<IntPtrT> phi_bb86_3;
  TNode<IntPtrT> phi_bb86_4;
  TNode<Smi> phi_bb86_6;
  TNode<Smi> phi_bb86_7;
  TNode<Smi> phi_bb86_11;
  TNode<BoolT> tmp111;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_2, &phi_bb86_3, &phi_bb86_4, &phi_bb86_6, &phi_bb86_7, &phi_bb86_11);
    tmp111 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb86_3}, TNode<IntPtrT>{phi_bb86_4});
    ca_.Branch(tmp111, &block88, std::vector<compiler::Node*>{phi_bb86_2, phi_bb86_3, phi_bb86_4, phi_bb86_6, phi_bb86_7, phi_bb86_11}, &block89, std::vector<compiler::Node*>{phi_bb86_2, phi_bb86_3, phi_bb86_4, phi_bb86_6, phi_bb86_7, phi_bb86_11});
  }

  TNode<FixedArray> phi_bb88_2;
  TNode<IntPtrT> phi_bb88_3;
  TNode<IntPtrT> phi_bb88_4;
  TNode<Smi> phi_bb88_6;
  TNode<Smi> phi_bb88_7;
  TNode<Smi> phi_bb88_11;
  TNode<IntPtrT> tmp112;
  TNode<IntPtrT> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<IntPtrT> tmp115;
  TNode<IntPtrT> tmp116;
  TNode<IntPtrT> tmp117;
  TNode<BoolT> tmp118;
  if (block88.is_used()) {
    ca_.Bind(&block88, &phi_bb88_2, &phi_bb88_3, &phi_bb88_4, &phi_bb88_6, &phi_bb88_7, &phi_bb88_11);
    tmp112 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp113 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb88_3}, TNode<IntPtrT>{tmp112});
    tmp114 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb88_3}, TNode<IntPtrT>{tmp113});
    tmp115 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp116 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp114}, TNode<IntPtrT>{tmp115});
    tmp117 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp118 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb88_4}, TNode<IntPtrT>{tmp117});
    ca_.Branch(tmp118, &block91, std::vector<compiler::Node*>{phi_bb88_2, phi_bb88_4, phi_bb88_6, phi_bb88_7, phi_bb88_11}, &block92, std::vector<compiler::Node*>{phi_bb88_2, phi_bb88_4, phi_bb88_6, phi_bb88_7, phi_bb88_11});
  }

  TNode<FixedArray> phi_bb92_2;
  TNode<IntPtrT> phi_bb92_4;
  TNode<Smi> phi_bb92_6;
  TNode<Smi> phi_bb92_7;
  TNode<Smi> phi_bb92_11;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_2, &phi_bb92_4, &phi_bb92_6, &phi_bb92_7, &phi_bb92_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb91_2;
  TNode<IntPtrT> phi_bb91_4;
  TNode<Smi> phi_bb91_6;
  TNode<Smi> phi_bb91_7;
  TNode<Smi> phi_bb91_11;
  TNode<IntPtrT> tmp119;
  TNode<BoolT> tmp120;
  if (block91.is_used()) {
    ca_.Bind(&block91, &phi_bb91_2, &phi_bb91_4, &phi_bb91_6, &phi_bb91_7, &phi_bb91_11);
    tmp119 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp120 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp116}, TNode<IntPtrT>{tmp119});
    ca_.Branch(tmp120, &block93, std::vector<compiler::Node*>{phi_bb91_2, phi_bb91_4, phi_bb91_6, phi_bb91_7, phi_bb91_11}, &block94, std::vector<compiler::Node*>{phi_bb91_2, phi_bb91_4, phi_bb91_6, phi_bb91_7, phi_bb91_11});
  }

  TNode<FixedArray> phi_bb94_2;
  TNode<IntPtrT> phi_bb94_4;
  TNode<Smi> phi_bb94_6;
  TNode<Smi> phi_bb94_7;
  TNode<Smi> phi_bb94_11;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_2, &phi_bb94_4, &phi_bb94_6, &phi_bb94_7, &phi_bb94_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb93_2;
  TNode<IntPtrT> phi_bb93_4;
  TNode<Smi> phi_bb93_6;
  TNode<Smi> phi_bb93_7;
  TNode<Smi> phi_bb93_11;
  TNode<BoolT> tmp121;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_2, &phi_bb93_4, &phi_bb93_6, &phi_bb93_7, &phi_bb93_11);
    tmp121 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp116}, TNode<IntPtrT>{phi_bb93_4});
    ca_.Branch(tmp121, &block95, std::vector<compiler::Node*>{phi_bb93_2, phi_bb93_4, phi_bb93_6, phi_bb93_7, phi_bb93_11}, &block96, std::vector<compiler::Node*>{phi_bb93_2, phi_bb93_4, phi_bb93_6, phi_bb93_7, phi_bb93_11});
  }

  TNode<FixedArray> phi_bb96_2;
  TNode<IntPtrT> phi_bb96_4;
  TNode<Smi> phi_bb96_6;
  TNode<Smi> phi_bb96_7;
  TNode<Smi> phi_bb96_11;
  if (block96.is_used()) {
    ca_.Bind(&block96, &phi_bb96_2, &phi_bb96_4, &phi_bb96_6, &phi_bb96_7, &phi_bb96_11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb95_2;
  TNode<IntPtrT> phi_bb95_4;
  TNode<Smi> phi_bb95_6;
  TNode<Smi> phi_bb95_7;
  TNode<Smi> phi_bb95_11;
  TNode<IntPtrT> tmp122;
  TNode<TheHole> tmp123;
  TNode<FixedArray> tmp124;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_2, &phi_bb95_4, &phi_bb95_6, &phi_bb95_7, &phi_bb95_11);
    tmp122 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp123 = TheHole_0(state_);
    tmp124 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb95_2}, TNode<IntPtrT>{tmp122}, TNode<IntPtrT>{phi_bb95_4}, TNode<IntPtrT>{tmp116}, TNode<Hole>{tmp123});
    ca_.Goto(&block89, tmp124, tmp116, phi_bb95_4, phi_bb95_6, phi_bb95_7, phi_bb95_11);
  }

  TNode<FixedArray> phi_bb89_2;
  TNode<IntPtrT> phi_bb89_3;
  TNode<IntPtrT> phi_bb89_4;
  TNode<Smi> phi_bb89_6;
  TNode<Smi> phi_bb89_7;
  TNode<Smi> phi_bb89_11;
  TNode<Union<HeapObject, TaggedIndex>> tmp125;
  TNode<IntPtrT> tmp126;
  TNode<IntPtrT> tmp127;
  TNode<IntPtrT> tmp128;
  TNode<IntPtrT> tmp129;
  TNode<UintPtrT> tmp130;
  TNode<UintPtrT> tmp131;
  TNode<BoolT> tmp132;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_2, &phi_bb89_3, &phi_bb89_4, &phi_bb89_6, &phi_bb89_7, &phi_bb89_11);
    std::tie(tmp125, tmp126, tmp127) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb89_2}).Flatten();
    tmp128 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp129 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb89_4}, TNode<IntPtrT>{tmp128});
    tmp130 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb89_4});
    tmp131 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp127});
    tmp132 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp130}, TNode<UintPtrT>{tmp131});
    ca_.Branch(tmp132, &block101, std::vector<compiler::Node*>{phi_bb89_2, phi_bb89_3, phi_bb89_6, phi_bb89_7, phi_bb89_11, phi_bb89_2, phi_bb89_4, phi_bb89_4, phi_bb89_4, phi_bb89_4}, &block102, std::vector<compiler::Node*>{phi_bb89_2, phi_bb89_3, phi_bb89_6, phi_bb89_7, phi_bb89_11, phi_bb89_2, phi_bb89_4, phi_bb89_4, phi_bb89_4, phi_bb89_4});
  }

  TNode<FixedArray> phi_bb101_2;
  TNode<IntPtrT> phi_bb101_3;
  TNode<Smi> phi_bb101_6;
  TNode<Smi> phi_bb101_7;
  TNode<Smi> phi_bb101_11;
  TNode<FixedArray> phi_bb101_16;
  TNode<IntPtrT> phi_bb101_20;
  TNode<IntPtrT> phi_bb101_21;
  TNode<IntPtrT> phi_bb101_25;
  TNode<IntPtrT> phi_bb101_26;
  TNode<IntPtrT> tmp133;
  TNode<IntPtrT> tmp134;
  TNode<Union<HeapObject, TaggedIndex>> tmp135;
  TNode<IntPtrT> tmp136;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_2, &phi_bb101_3, &phi_bb101_6, &phi_bb101_7, &phi_bb101_11, &phi_bb101_16, &phi_bb101_20, &phi_bb101_21, &phi_bb101_25, &phi_bb101_26);
    tmp133 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb101_26});
    tmp134 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp126}, TNode<IntPtrT>{tmp133});
    std::tie(tmp135, tmp136) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp125}, TNode<IntPtrT>{tmp134}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp135, tmp136}, tmp109);
    ca_.Goto(&block69, phi_bb101_2, phi_bb101_3, tmp129, phi_bb101_6, phi_bb101_7, phi_bb101_11);
  }

  TNode<FixedArray> phi_bb102_2;
  TNode<IntPtrT> phi_bb102_3;
  TNode<Smi> phi_bb102_6;
  TNode<Smi> phi_bb102_7;
  TNode<Smi> phi_bb102_11;
  TNode<FixedArray> phi_bb102_16;
  TNode<IntPtrT> phi_bb102_20;
  TNode<IntPtrT> phi_bb102_21;
  TNode<IntPtrT> phi_bb102_25;
  TNode<IntPtrT> phi_bb102_26;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_2, &phi_bb102_3, &phi_bb102_6, &phi_bb102_7, &phi_bb102_11, &phi_bb102_16, &phi_bb102_20, &phi_bb102_21, &phi_bb102_25, &phi_bb102_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb69_2;
  TNode<IntPtrT> phi_bb69_3;
  TNode<IntPtrT> phi_bb69_4;
  TNode<Smi> phi_bb69_6;
  TNode<Smi> phi_bb69_7;
  TNode<Smi> phi_bb69_11;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_2, &phi_bb69_3, &phi_bb69_4, &phi_bb69_6, &phi_bb69_7, &phi_bb69_11);
    ca_.Goto(&block67, phi_bb69_2, phi_bb69_3, phi_bb69_4, phi_bb69_6, phi_bb69_7, phi_bb69_11);
  }

  TNode<FixedArray> phi_bb105_2;
  TNode<IntPtrT> phi_bb105_3;
  TNode<IntPtrT> phi_bb105_4;
  TNode<Smi> phi_bb105_6;
  TNode<Smi> phi_bb105_7;
  TNode<Smi> phi_bb105_11;
  TNode<Smi> tmp137;
  TNode<Smi> tmp138;
  if (block105.is_used()) {
    ca_.Bind(&block105, &phi_bb105_2, &phi_bb105_3, &phi_bb105_4, &phi_bb105_6, &phi_bb105_7, &phi_bb105_11);
    tmp137 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp138 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb105_7}, TNode<Smi>{tmp137});
    ca_.Goto(&block107, phi_bb105_2, phi_bb105_3, phi_bb105_4, phi_bb105_6, tmp138, phi_bb105_11);
  }

  TNode<FixedArray> phi_bb106_2;
  TNode<IntPtrT> phi_bb106_3;
  TNode<IntPtrT> phi_bb106_4;
  TNode<Smi> phi_bb106_6;
  TNode<Smi> phi_bb106_7;
  TNode<Smi> phi_bb106_11;
  if (block106.is_used()) {
    ca_.Bind(&block106, &phi_bb106_2, &phi_bb106_3, &phi_bb106_4, &phi_bb106_6, &phi_bb106_7, &phi_bb106_11);
    ca_.Goto(&block107, phi_bb106_2, phi_bb106_3, phi_bb106_4, phi_bb106_6, phi_bb106_7, phi_bb106_11);
  }

  TNode<FixedArray> phi_bb107_2;
  TNode<IntPtrT> phi_bb107_3;
  TNode<IntPtrT> phi_bb107_4;
  TNode<Smi> phi_bb107_6;
  TNode<Smi> phi_bb107_7;
  TNode<Smi> phi_bb107_11;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_2, &phi_bb107_3, &phi_bb107_4, &phi_bb107_6, &phi_bb107_7, &phi_bb107_11);
    ca_.Goto(&block67, phi_bb107_2, phi_bb107_3, phi_bb107_4, phi_bb107_6, phi_bb107_7, phi_bb107_11);
  }

  TNode<FixedArray> phi_bb67_2;
  TNode<IntPtrT> phi_bb67_3;
  TNode<IntPtrT> phi_bb67_4;
  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<Smi> phi_bb67_11;
  TNode<Smi> tmp139;
  TNode<Smi> tmp140;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_2, &phi_bb67_3, &phi_bb67_4, &phi_bb67_6, &phi_bb67_7, &phi_bb67_11);
    tmp139 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp140 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb67_11}, TNode<Smi>{tmp139});
    ca_.Goto(&block65, phi_bb67_2, phi_bb67_3, phi_bb67_4, phi_bb67_6, phi_bb67_7, tmp140);
  }

  TNode<FixedArray> phi_bb64_2;
  TNode<IntPtrT> phi_bb64_3;
  TNode<IntPtrT> phi_bb64_4;
  TNode<Smi> phi_bb64_6;
  TNode<Smi> phi_bb64_7;
  TNode<Smi> phi_bb64_11;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_2, &phi_bb64_3, &phi_bb64_4, &phi_bb64_6, &phi_bb64_7, &phi_bb64_11);
    ca_.Goto(&block20, phi_bb64_2, phi_bb64_3, phi_bb64_4, phi_bb64_6, phi_bb64_7);
  }

  TNode<FixedArray> phi_bb20_2;
  TNode<IntPtrT> phi_bb20_3;
  TNode<IntPtrT> phi_bb20_4;
  TNode<Smi> phi_bb20_6;
  TNode<Smi> phi_bb20_7;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_2, &phi_bb20_3, &phi_bb20_4, &phi_bb20_6, &phi_bb20_7);
    ca_.Goto(&block17, phi_bb20_2, phi_bb20_3, phi_bb20_4, phi_bb20_6, phi_bb20_7);
  }

  TNode<Smi> phi_bb13_6;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    if ((p_isToSorted)) {
      ca_.Goto(&block108, phi_bb13_6);
    } else {
      ca_.Goto(&block109, phi_bb13_6);
    }
  }

  TNode<Smi> phi_bb108_6;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_6);
    ca_.Goto(&block110, phi_bb108_6, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadNoHasPropertyCheck_GenericElementsAccessor_0)));
  }

  TNode<Smi> phi_bb109_6;
  if (block109.is_used()) {
    ca_.Bind(&block109, &phi_bb109_6);
    ca_.Goto(&block110, phi_bb109_6, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoad_GenericElementsAccessor_0)));
  }

  TNode<Smi> phi_bb110_6;
  TNode<BuiltinPtr> phi_bb110_8;
  TNode<Smi> tmp141;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_6, &phi_bb110_8);
    tmp141 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block113, tmp1, tmp6, tmp7, phi_bb110_6, tmp16, tmp141);
  }

  TNode<FixedArray> phi_bb113_2;
  TNode<IntPtrT> phi_bb113_3;
  TNode<IntPtrT> phi_bb113_4;
  TNode<Smi> phi_bb113_6;
  TNode<Smi> phi_bb113_7;
  TNode<Smi> phi_bb113_9;
  TNode<BoolT> tmp142;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_2, &phi_bb113_3, &phi_bb113_4, &phi_bb113_6, &phi_bb113_7, &phi_bb113_9);
    tmp142 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb113_9}, TNode<Number>{tmp9});
    ca_.Branch(tmp142, &block111, std::vector<compiler::Node*>{phi_bb113_2, phi_bb113_3, phi_bb113_4, phi_bb113_6, phi_bb113_7, phi_bb113_9}, &block112, std::vector<compiler::Node*>{phi_bb113_2, phi_bb113_3, phi_bb113_4, phi_bb113_6, phi_bb113_7, phi_bb113_9});
  }

  TNode<FixedArray> phi_bb111_2;
  TNode<IntPtrT> phi_bb111_3;
  TNode<IntPtrT> phi_bb111_4;
  TNode<Smi> phi_bb111_6;
  TNode<Smi> phi_bb111_7;
  TNode<Smi> phi_bb111_9;
  TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> tmp143;
  TNode<TheHole> tmp144;
  TNode<BoolT> tmp145;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_2, &phi_bb111_3, &phi_bb111_4, &phi_bb111_6, &phi_bb111_7, &phi_bb111_9);
tmp143 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallInterfaceDescriptorFor(ExampleBuiltinForTorqueFunctionPointerType(8)), phi_bb110_8, p_context, p_sortState, phi_bb111_9));
    tmp144 = TheHole_0(state_);
    tmp145 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp143}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp144});
    ca_.Branch(tmp145, &block115, std::vector<compiler::Node*>{phi_bb111_2, phi_bb111_3, phi_bb111_4, phi_bb111_6, phi_bb111_7, phi_bb111_9}, &block116, std::vector<compiler::Node*>{phi_bb111_2, phi_bb111_3, phi_bb111_4, phi_bb111_6, phi_bb111_7, phi_bb111_9});
  }

  TNode<FixedArray> phi_bb115_2;
  TNode<IntPtrT> phi_bb115_3;
  TNode<IntPtrT> phi_bb115_4;
  TNode<Smi> phi_bb115_6;
  TNode<Smi> phi_bb115_7;
  TNode<Smi> phi_bb115_9;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_2, &phi_bb115_3, &phi_bb115_4, &phi_bb115_6, &phi_bb115_7, &phi_bb115_9);
    if ((p_isToSorted)) {
      ca_.Goto(&block118, phi_bb115_2, phi_bb115_3, phi_bb115_4, phi_bb115_6, phi_bb115_7, phi_bb115_9);
    } else {
      ca_.Goto(&block119, phi_bb115_2, phi_bb115_3, phi_bb115_4, phi_bb115_6, phi_bb115_7, phi_bb115_9);
    }
  }

  TNode<FixedArray> phi_bb118_2;
  TNode<IntPtrT> phi_bb118_3;
  TNode<IntPtrT> phi_bb118_4;
  TNode<Smi> phi_bb118_6;
  TNode<Smi> phi_bb118_7;
  TNode<Smi> phi_bb118_9;
  TNode<Smi> tmp146;
  TNode<Smi> tmp147;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_2, &phi_bb118_3, &phi_bb118_4, &phi_bb118_6, &phi_bb118_7, &phi_bb118_9);
    tmp146 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp147 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb118_7}, TNode<Smi>{tmp146});
    ca_.Goto(&block120, phi_bb118_2, phi_bb118_3, phi_bb118_4, phi_bb118_6, tmp147, phi_bb118_9);
  }

  TNode<FixedArray> phi_bb119_2;
  TNode<IntPtrT> phi_bb119_3;
  TNode<IntPtrT> phi_bb119_4;
  TNode<Smi> phi_bb119_6;
  TNode<Smi> phi_bb119_7;
  TNode<Smi> phi_bb119_9;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_2, &phi_bb119_3, &phi_bb119_4, &phi_bb119_6, &phi_bb119_7, &phi_bb119_9);
    ca_.Goto(&block120, phi_bb119_2, phi_bb119_3, phi_bb119_4, phi_bb119_6, phi_bb119_7, phi_bb119_9);
  }

  TNode<FixedArray> phi_bb120_2;
  TNode<IntPtrT> phi_bb120_3;
  TNode<IntPtrT> phi_bb120_4;
  TNode<Smi> phi_bb120_6;
  TNode<Smi> phi_bb120_7;
  TNode<Smi> phi_bb120_9;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_2, &phi_bb120_3, &phi_bb120_4, &phi_bb120_6, &phi_bb120_7, &phi_bb120_9);
    ca_.Goto(&block117, phi_bb120_2, phi_bb120_3, phi_bb120_4, phi_bb120_6, phi_bb120_7, phi_bb120_9);
  }

  TNode<FixedArray> phi_bb116_2;
  TNode<IntPtrT> phi_bb116_3;
  TNode<IntPtrT> phi_bb116_4;
  TNode<Smi> phi_bb116_6;
  TNode<Smi> phi_bb116_7;
  TNode<Smi> phi_bb116_9;
  TNode<Undefined> tmp148;
  TNode<BoolT> tmp149;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_2, &phi_bb116_3, &phi_bb116_4, &phi_bb116_6, &phi_bb116_7, &phi_bb116_9);
    tmp148 = Undefined_0(state_);
    tmp149 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp143}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp148});
    ca_.Branch(tmp149, &block121, std::vector<compiler::Node*>{phi_bb116_2, phi_bb116_3, phi_bb116_4, phi_bb116_6, phi_bb116_7, phi_bb116_9}, &block122, std::vector<compiler::Node*>{phi_bb116_2, phi_bb116_3, phi_bb116_4, phi_bb116_6, phi_bb116_7, phi_bb116_9});
  }

  TNode<FixedArray> phi_bb121_2;
  TNode<IntPtrT> phi_bb121_3;
  TNode<IntPtrT> phi_bb121_4;
  TNode<Smi> phi_bb121_6;
  TNode<Smi> phi_bb121_7;
  TNode<Smi> phi_bb121_9;
  TNode<Smi> tmp150;
  TNode<Smi> tmp151;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_2, &phi_bb121_3, &phi_bb121_4, &phi_bb121_6, &phi_bb121_7, &phi_bb121_9);
    tmp150 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp151 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb121_7}, TNode<Smi>{tmp150});
    ca_.Goto(&block123, phi_bb121_2, phi_bb121_3, phi_bb121_4, phi_bb121_6, tmp151, phi_bb121_9);
  }

  TNode<FixedArray> phi_bb122_2;
  TNode<IntPtrT> phi_bb122_3;
  TNode<IntPtrT> phi_bb122_4;
  TNode<Smi> phi_bb122_6;
  TNode<Smi> phi_bb122_7;
  TNode<Smi> phi_bb122_9;
  TNode<BoolT> tmp152;
  if (block122.is_used()) {
    ca_.Bind(&block122, &phi_bb122_2, &phi_bb122_3, &phi_bb122_4, &phi_bb122_6, &phi_bb122_7, &phi_bb122_9);
    tmp152 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb122_4}, TNode<IntPtrT>{phi_bb122_3});
    ca_.Branch(tmp152, &block126, std::vector<compiler::Node*>{phi_bb122_2, phi_bb122_3, phi_bb122_4, phi_bb122_6, phi_bb122_7, phi_bb122_9}, &block127, std::vector<compiler::Node*>{phi_bb122_2, phi_bb122_3, phi_bb122_4, phi_bb122_6, phi_bb122_7, phi_bb122_9});
  }

  TNode<FixedArray> phi_bb127_2;
  TNode<IntPtrT> phi_bb127_3;
  TNode<IntPtrT> phi_bb127_4;
  TNode<Smi> phi_bb127_6;
  TNode<Smi> phi_bb127_7;
  TNode<Smi> phi_bb127_9;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_2, &phi_bb127_3, &phi_bb127_4, &phi_bb127_6, &phi_bb127_7, &phi_bb127_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 21});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length <= this.capacity' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb126_2;
  TNode<IntPtrT> phi_bb126_3;
  TNode<IntPtrT> phi_bb126_4;
  TNode<Smi> phi_bb126_6;
  TNode<Smi> phi_bb126_7;
  TNode<Smi> phi_bb126_9;
  TNode<BoolT> tmp153;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_2, &phi_bb126_3, &phi_bb126_4, &phi_bb126_6, &phi_bb126_7, &phi_bb126_9);
    tmp153 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb126_3}, TNode<IntPtrT>{phi_bb126_4});
    ca_.Branch(tmp153, &block128, std::vector<compiler::Node*>{phi_bb126_2, phi_bb126_3, phi_bb126_4, phi_bb126_6, phi_bb126_7, phi_bb126_9}, &block129, std::vector<compiler::Node*>{phi_bb126_2, phi_bb126_3, phi_bb126_4, phi_bb126_6, phi_bb126_7, phi_bb126_9});
  }

  TNode<FixedArray> phi_bb128_2;
  TNode<IntPtrT> phi_bb128_3;
  TNode<IntPtrT> phi_bb128_4;
  TNode<Smi> phi_bb128_6;
  TNode<Smi> phi_bb128_7;
  TNode<Smi> phi_bb128_9;
  TNode<IntPtrT> tmp154;
  TNode<IntPtrT> tmp155;
  TNode<IntPtrT> tmp156;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<IntPtrT> tmp159;
  TNode<BoolT> tmp160;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_2, &phi_bb128_3, &phi_bb128_4, &phi_bb128_6, &phi_bb128_7, &phi_bb128_9);
    tmp154 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp155 = CodeStubAssembler(state_).WordSar(TNode<IntPtrT>{phi_bb128_3}, TNode<IntPtrT>{tmp154});
    tmp156 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb128_3}, TNode<IntPtrT>{tmp155});
    tmp157 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x10ull));
    tmp158 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp156}, TNode<IntPtrT>{tmp157});
    tmp159 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp160 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb128_4}, TNode<IntPtrT>{tmp159});
    ca_.Branch(tmp160, &block131, std::vector<compiler::Node*>{phi_bb128_2, phi_bb128_4, phi_bb128_6, phi_bb128_7, phi_bb128_9}, &block132, std::vector<compiler::Node*>{phi_bb128_2, phi_bb128_4, phi_bb128_6, phi_bb128_7, phi_bb128_9});
  }

  TNode<FixedArray> phi_bb132_2;
  TNode<IntPtrT> phi_bb132_4;
  TNode<Smi> phi_bb132_6;
  TNode<Smi> phi_bb132_7;
  TNode<Smi> phi_bb132_9;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_2, &phi_bb132_4, &phi_bb132_6, &phi_bb132_7, &phi_bb132_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 13});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.length >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb131_2;
  TNode<IntPtrT> phi_bb131_4;
  TNode<Smi> phi_bb131_6;
  TNode<Smi> phi_bb131_7;
  TNode<Smi> phi_bb131_9;
  TNode<IntPtrT> tmp161;
  TNode<BoolT> tmp162;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_2, &phi_bb131_4, &phi_bb131_6, &phi_bb131_7, &phi_bb131_9);
    tmp161 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp162 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp158}, TNode<IntPtrT>{tmp161});
    ca_.Branch(tmp162, &block133, std::vector<compiler::Node*>{phi_bb131_2, phi_bb131_4, phi_bb131_6, phi_bb131_7, phi_bb131_9}, &block134, std::vector<compiler::Node*>{phi_bb131_2, phi_bb131_4, phi_bb131_6, phi_bb131_7, phi_bb131_9});
  }

  TNode<FixedArray> phi_bb134_2;
  TNode<IntPtrT> phi_bb134_4;
  TNode<Smi> phi_bb134_6;
  TNode<Smi> phi_bb134_7;
  TNode<Smi> phi_bb134_9;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_2, &phi_bb134_4, &phi_bb134_6, &phi_bb134_7, &phi_bb134_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 14});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb133_2;
  TNode<IntPtrT> phi_bb133_4;
  TNode<Smi> phi_bb133_6;
  TNode<Smi> phi_bb133_7;
  TNode<Smi> phi_bb133_9;
  TNode<BoolT> tmp163;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_2, &phi_bb133_4, &phi_bb133_6, &phi_bb133_7, &phi_bb133_9);
    tmp163 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{tmp158}, TNode<IntPtrT>{phi_bb133_4});
    ca_.Branch(tmp163, &block135, std::vector<compiler::Node*>{phi_bb133_2, phi_bb133_4, phi_bb133_6, phi_bb133_7, phi_bb133_9}, &block136, std::vector<compiler::Node*>{phi_bb133_2, phi_bb133_4, phi_bb133_6, phi_bb133_7, phi_bb133_9});
  }

  TNode<FixedArray> phi_bb136_2;
  TNode<IntPtrT> phi_bb136_4;
  TNode<Smi> phi_bb136_6;
  TNode<Smi> phi_bb136_7;
  TNode<Smi> phi_bb136_9;
  if (block136.is_used()) {
    ca_.Bind(&block136, &phi_bb136_2, &phi_bb136_4, &phi_bb136_6, &phi_bb136_7, &phi_bb136_9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/growable-fixed-array.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'newCapacity >= this.length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb135_2;
  TNode<IntPtrT> phi_bb135_4;
  TNode<Smi> phi_bb135_6;
  TNode<Smi> phi_bb135_7;
  TNode<Smi> phi_bb135_9;
  TNode<IntPtrT> tmp164;
  TNode<TheHole> tmp165;
  TNode<FixedArray> tmp166;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_2, &phi_bb135_4, &phi_bb135_6, &phi_bb135_7, &phi_bb135_9);
    tmp164 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp165 = TheHole_0(state_);
    tmp166 = ExtractFixedArray_0(state_, TNode<FixedArray>{phi_bb135_2}, TNode<IntPtrT>{tmp164}, TNode<IntPtrT>{phi_bb135_4}, TNode<IntPtrT>{tmp158}, TNode<Hole>{tmp165});
    ca_.Goto(&block129, tmp166, tmp158, phi_bb135_4, phi_bb135_6, phi_bb135_7, phi_bb135_9);
  }

  TNode<FixedArray> phi_bb129_2;
  TNode<IntPtrT> phi_bb129_3;
  TNode<IntPtrT> phi_bb129_4;
  TNode<Smi> phi_bb129_6;
  TNode<Smi> phi_bb129_7;
  TNode<Smi> phi_bb129_9;
  TNode<Union<HeapObject, TaggedIndex>> tmp167;
  TNode<IntPtrT> tmp168;
  TNode<IntPtrT> tmp169;
  TNode<IntPtrT> tmp170;
  TNode<IntPtrT> tmp171;
  TNode<UintPtrT> tmp172;
  TNode<UintPtrT> tmp173;
  TNode<BoolT> tmp174;
  if (block129.is_used()) {
    ca_.Bind(&block129, &phi_bb129_2, &phi_bb129_3, &phi_bb129_4, &phi_bb129_6, &phi_bb129_7, &phi_bb129_9);
    std::tie(tmp167, tmp168, tmp169) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb129_2}).Flatten();
    tmp170 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp171 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb129_4}, TNode<IntPtrT>{tmp170});
    tmp172 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb129_4});
    tmp173 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp169});
    tmp174 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp172}, TNode<UintPtrT>{tmp173});
    ca_.Branch(tmp174, &block141, std::vector<compiler::Node*>{phi_bb129_2, phi_bb129_3, phi_bb129_6, phi_bb129_7, phi_bb129_9, phi_bb129_2, phi_bb129_4, phi_bb129_4, phi_bb129_4, phi_bb129_4}, &block142, std::vector<compiler::Node*>{phi_bb129_2, phi_bb129_3, phi_bb129_6, phi_bb129_7, phi_bb129_9, phi_bb129_2, phi_bb129_4, phi_bb129_4, phi_bb129_4, phi_bb129_4});
  }

  TNode<FixedArray> phi_bb141_2;
  TNode<IntPtrT> phi_bb141_3;
  TNode<Smi> phi_bb141_6;
  TNode<Smi> phi_bb141_7;
  TNode<Smi> phi_bb141_9;
  TNode<FixedArray> phi_bb141_13;
  TNode<IntPtrT> phi_bb141_17;
  TNode<IntPtrT> phi_bb141_18;
  TNode<IntPtrT> phi_bb141_22;
  TNode<IntPtrT> phi_bb141_23;
  TNode<IntPtrT> tmp175;
  TNode<IntPtrT> tmp176;
  TNode<Union<HeapObject, TaggedIndex>> tmp177;
  TNode<IntPtrT> tmp178;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_2, &phi_bb141_3, &phi_bb141_6, &phi_bb141_7, &phi_bb141_9, &phi_bb141_13, &phi_bb141_17, &phi_bb141_18, &phi_bb141_22, &phi_bb141_23);
    tmp175 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb141_23});
    tmp176 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp168}, TNode<IntPtrT>{tmp175});
    std::tie(tmp177, tmp178) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp167}, TNode<IntPtrT>{tmp176}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp177, tmp178}, tmp143);
    ca_.Goto(&block123, phi_bb141_2, phi_bb141_3, tmp171, phi_bb141_6, phi_bb141_7, phi_bb141_9);
  }

  TNode<FixedArray> phi_bb142_2;
  TNode<IntPtrT> phi_bb142_3;
  TNode<Smi> phi_bb142_6;
  TNode<Smi> phi_bb142_7;
  TNode<Smi> phi_bb142_9;
  TNode<FixedArray> phi_bb142_13;
  TNode<IntPtrT> phi_bb142_17;
  TNode<IntPtrT> phi_bb142_18;
  TNode<IntPtrT> phi_bb142_22;
  TNode<IntPtrT> phi_bb142_23;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_2, &phi_bb142_3, &phi_bb142_6, &phi_bb142_7, &phi_bb142_9, &phi_bb142_13, &phi_bb142_17, &phi_bb142_18, &phi_bb142_22, &phi_bb142_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb123_2;
  TNode<IntPtrT> phi_bb123_3;
  TNode<IntPtrT> phi_bb123_4;
  TNode<Smi> phi_bb123_6;
  TNode<Smi> phi_bb123_7;
  TNode<Smi> phi_bb123_9;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_2, &phi_bb123_3, &phi_bb123_4, &phi_bb123_6, &phi_bb123_7, &phi_bb123_9);
    ca_.Goto(&block117, phi_bb123_2, phi_bb123_3, phi_bb123_4, phi_bb123_6, phi_bb123_7, phi_bb123_9);
  }

  TNode<FixedArray> phi_bb117_2;
  TNode<IntPtrT> phi_bb117_3;
  TNode<IntPtrT> phi_bb117_4;
  TNode<Smi> phi_bb117_6;
  TNode<Smi> phi_bb117_7;
  TNode<Smi> phi_bb117_9;
  TNode<Smi> tmp179;
  TNode<Smi> tmp180;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_2, &phi_bb117_3, &phi_bb117_4, &phi_bb117_6, &phi_bb117_7, &phi_bb117_9);
    tmp179 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp180 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb117_9}, TNode<Smi>{tmp179});
    ca_.Goto(&block113, phi_bb117_2, phi_bb117_3, phi_bb117_4, phi_bb117_6, phi_bb117_7, tmp180);
  }

  TNode<FixedArray> phi_bb112_2;
  TNode<IntPtrT> phi_bb112_3;
  TNode<IntPtrT> phi_bb112_4;
  TNode<Smi> phi_bb112_6;
  TNode<Smi> phi_bb112_7;
  TNode<Smi> phi_bb112_9;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_2, &phi_bb112_3, &phi_bb112_4, &phi_bb112_6, &phi_bb112_7, &phi_bb112_9);
    ca_.Goto(&block17, phi_bb112_2, phi_bb112_3, phi_bb112_4, phi_bb112_6, phi_bb112_7);
  }

  TNode<FixedArray> phi_bb17_2;
  TNode<IntPtrT> phi_bb17_3;
  TNode<IntPtrT> phi_bb17_4;
  TNode<Smi> phi_bb17_6;
  TNode<Smi> phi_bb17_7;
  TNode<IntPtrT> tmp181;
  TNode<IntPtrT> tmp182;
  TNode<IntPtrT> tmp183;
  TNode<Smi> tmp184;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_2, &phi_bb17_3, &phi_bb17_4, &phi_bb17_6, &phi_bb17_7);
    tmp181 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp181}, phi_bb17_2);
    tmp182 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp182}, phi_bb17_6);
    tmp183 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp183}, phi_bb17_7);
    tmp184 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb17_4});
    ca_.Goto(&block145);
  }

    ca_.Bind(&block145);
  return TNode<Smi>{tmp184};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1456&c=1
void CopyWorkArrayToReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_numberOfNonUndefined) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, Smi, Smi, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, Smi, Smi, Smi> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, BuiltinPtr> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, BuiltinPtr> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, BuiltinPtr> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, BuiltinPtr> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, BuiltinPtr> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr, Smi, BuiltinPtr> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Boolean> tmp1;
  TNode<True> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp1 = CodeStubAssembler(state_).LoadReference<Boolean>(CodeStubAssembler::Reference{p_sortState, tmp0});
    tmp2 = True_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block3);
  }

  TNode<IntPtrT> tmp4;
  TNode<JSReceiver> tmp5;
  TNode<JSArray> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp5 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp4});
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp5}, &label7);
    ca_.Goto(&block6);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block3);
  }

  TNode<IntPtrT> tmp8;
  TNode<JSReceiver> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Map> tmp11;
  TNode<Int32T> tmp12;
  TNode<BoolT> tmp13;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp9 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp8});
    tmp10 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp11 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp9, tmp10});
    tmp12 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp11});
    tmp13 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{tmp12});
    ca_.Branch(tmp13, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block10, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kStore_FastDoubleElements_0)));
  }

  TNode<BoolT> tmp14;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp14 = CodeStubAssembler(state_).IsFastSmiElementsKind(TNode<Int32T>{tmp12});
    ca_.Branch(tmp14, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block13, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kStore_FastSmiElements_0)));
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block13, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kStore_FastObjectElements_0)));
  }

  TNode<BuiltinPtr> phi_bb13_3;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_3);
    ca_.Goto(&block10, phi_bb13_3);
  }

  TNode<BuiltinPtr> phi_bb10_3;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_3);
    ca_.Goto(&block2, phi_bb10_3);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block2, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kStore_GenericElementsAccessor_0)));
  }

  TNode<BuiltinPtr> phi_bb2_3;
  TNode<IntPtrT> tmp15;
  TNode<FixedArray> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<BoolT> tmp19;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_3);
    tmp15 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp16 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_sortState, tmp15});
    tmp17 = Convert_intptr_Smi_0(state_, TNode<Smi>{p_numberOfNonUndefined});
    tmp18 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp16});
    tmp19 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{tmp17}, TNode<IntPtrT>{tmp18});
    ca_.Branch(tmp19, &block14, std::vector<compiler::Node*>{phi_bb2_3}, &block15, std::vector<compiler::Node*>{phi_bb2_3});
  }

  TNode<BuiltinPtr> phi_bb15_3;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1478});
      CodeStubAssembler(state_).FailAssert("Torque assert 'Convert<intptr>(numberOfNonUndefined) <= workArray.length_intptr' failed", pos_stack);
    }
  }

  TNode<BuiltinPtr> phi_bb14_3;
  TNode<IntPtrT> tmp20;
  TNode<Smi> tmp21;
  TNode<Smi> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Smi> tmp24;
  TNode<BoolT> tmp25;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_3);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp21 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp20});
    tmp22 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{p_numberOfNonUndefined}, TNode<Smi>{tmp21});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp24 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp23});
    tmp25 = CodeStubAssembler(state_).SmiLessThanOrEqual(TNode<Smi>{tmp22}, TNode<Smi>{tmp24});
    ca_.Branch(tmp25, &block16, std::vector<compiler::Node*>{phi_bb14_3}, &block17, std::vector<compiler::Node*>{phi_bb14_3});
  }

  TNode<BuiltinPtr> phi_bb17_3;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 1479});
      CodeStubAssembler(state_).FailAssert("Torque assert 'numberOfNonUndefined + sortState.number_of_undefined <= sortState.sort_length' failed", pos_stack);
    }
  }

  TNode<BuiltinPtr> phi_bb16_3;
  TNode<Smi> tmp26;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_3);
    tmp26 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block20, phi_bb16_3, tmp26);
  }

  TNode<BuiltinPtr> phi_bb20_3;
  TNode<Smi> phi_bb20_5;
  TNode<BoolT> tmp27;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_3, &phi_bb20_5);
    tmp27 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb20_5}, TNode<Smi>{p_numberOfNonUndefined});
    ca_.Branch(tmp27, &block18, std::vector<compiler::Node*>{phi_bb20_3, phi_bb20_5}, &block19, std::vector<compiler::Node*>{phi_bb20_3, phi_bb20_5});
  }

  TNode<BuiltinPtr> phi_bb18_3;
  TNode<Smi> phi_bb18_5;
  TNode<Union<HeapObject, TaggedIndex>> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_3, &phi_bb18_5);
    std::tie(tmp28, tmp29, tmp30) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp16}).Flatten();
    tmp31 = Convert_intptr_Smi_0(state_, TNode<Smi>{phi_bb18_5});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp34 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block26, std::vector<compiler::Node*>{phi_bb18_3, phi_bb18_5, phi_bb18_5, phi_bb18_5, phi_bb18_5}, &block27, std::vector<compiler::Node*>{phi_bb18_3, phi_bb18_5, phi_bb18_5, phi_bb18_5, phi_bb18_5});
  }

  TNode<BuiltinPtr> phi_bb26_3;
  TNode<Smi> phi_bb26_5;
  TNode<Smi> phi_bb26_8;
  TNode<Smi> phi_bb26_13;
  TNode<Smi> phi_bb26_14;
  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<Union<HeapObject, TaggedIndex>> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<Object> tmp39;
  TNode<JSAny> tmp40;
  TNode<Smi> tmp41;
  TNode<Smi> tmp42;
  TNode<Smi> tmp43;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_3, &phi_bb26_5, &phi_bb26_8, &phi_bb26_13, &phi_bb26_14);
    tmp35 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp31});
    tmp36 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp29}, TNode<IntPtrT>{tmp35});
    std::tie(tmp37, tmp38) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp28}, TNode<IntPtrT>{tmp36}).Flatten();
    tmp39 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp37, tmp38});
    tmp40 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp39});
tmp41 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallInterfaceDescriptorFor(ExampleBuiltinForTorqueFunctionPointerType(9)), phi_bb26_3, p_context, p_sortState, phi_bb26_8, tmp40));
    tmp42 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp43 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb26_5}, TNode<Smi>{tmp42});
    ca_.Goto(&block20, phi_bb26_3, tmp43);
  }

  TNode<BuiltinPtr> phi_bb27_3;
  TNode<Smi> phi_bb27_5;
  TNode<Smi> phi_bb27_8;
  TNode<Smi> phi_bb27_13;
  TNode<Smi> phi_bb27_14;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_3, &phi_bb27_5, &phi_bb27_8, &phi_bb27_13, &phi_bb27_14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BuiltinPtr> phi_bb19_3;
  TNode<Smi> phi_bb19_5;
  TNode<IntPtrT> tmp44;
  TNode<Smi> tmp45;
  TNode<BoolT> tmp46;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_3, &phi_bb19_5);
    tmp44 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp45 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp44});
    tmp46 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{phi_bb19_5}, TNode<Smi>{tmp45});
    ca_.Branch(tmp46, &block30, std::vector<compiler::Node*>{phi_bb19_3, phi_bb19_5}, &block31, std::vector<compiler::Node*>{phi_bb19_3, phi_bb19_5});
  }

  TNode<BuiltinPtr> phi_bb30_3;
  TNode<Smi> phi_bb30_5;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_3, &phi_bb30_5);
    ca_.Goto(&block1);
  }

  TNode<BuiltinPtr> phi_bb31_3;
  TNode<Smi> phi_bb31_5;
  TNode<IntPtrT> tmp47;
  TNode<Smi> tmp48;
  TNode<Smi> tmp49;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_3, &phi_bb31_5);
    tmp47 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp48 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_sortState, tmp47});
    tmp49 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp48}, TNode<Smi>{p_numberOfNonUndefined});
    ca_.Goto(&block34, phi_bb31_3, phi_bb31_5);
  }

  TNode<BuiltinPtr> phi_bb34_3;
  TNode<Smi> phi_bb34_5;
  TNode<BoolT> tmp50;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_3, &phi_bb34_5);
    tmp50 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb34_5}, TNode<Smi>{tmp49});
    ca_.Branch(tmp50, &block32, std::vector<compiler::Node*>{phi_bb34_3, phi_bb34_5}, &block33, std::vector<compiler::Node*>{phi_bb34_3, phi_bb34_5});
  }

  TNode<BuiltinPtr> phi_bb32_3;
  TNode<Smi> phi_bb32_5;
  TNode<Undefined> tmp51;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  TNode<Smi> tmp54;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_3, &phi_bb32_5);
    tmp51 = Undefined_0(state_);
tmp52 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallInterfaceDescriptorFor(ExampleBuiltinForTorqueFunctionPointerType(9)), phi_bb32_3, p_context, p_sortState, phi_bb32_5, tmp51));
    tmp53 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp54 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb32_5}, TNode<Smi>{tmp53});
    ca_.Goto(&block34, phi_bb32_3, tmp54);
  }

  TNode<BuiltinPtr> phi_bb33_3;
  TNode<Smi> phi_bb33_5;
  TNode<IntPtrT> tmp55;
  TNode<Boolean> tmp56;
  TNode<True> tmp57;
  TNode<BoolT> tmp58;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_3, &phi_bb33_5);
    tmp55 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp56 = CodeStubAssembler(state_).LoadReference<Boolean>(CodeStubAssembler::Reference{p_sortState, tmp55});
    tmp57 = True_0(state_);
    tmp58 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp56}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp57});
    ca_.Branch(tmp58, &block38, std::vector<compiler::Node*>{phi_bb33_3, phi_bb33_5}, &block39, std::vector<compiler::Node*>{phi_bb33_3, phi_bb33_5});
  }

  TNode<BuiltinPtr> phi_bb38_3;
  TNode<Smi> phi_bb38_5;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_3, &phi_bb38_5);
    ca_.Goto(&block37, phi_bb38_3, phi_bb38_5);
  }

  TNode<BuiltinPtr> phi_bb39_3;
  TNode<Smi> phi_bb39_5;
  TNode<IntPtrT> tmp59;
  TNode<JSReceiver> tmp60;
  TNode<JSArray> tmp61;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_3, &phi_bb39_5);
    tmp59 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp60 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp59});
    compiler::CodeAssemblerLabel label62(&ca_);
    tmp61 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{tmp60}, &label62);
    ca_.Goto(&block40, phi_bb39_3, phi_bb39_5);
    if (label62.is_used()) {
      ca_.Bind(&label62);
      ca_.Goto(&block41, phi_bb39_3, phi_bb39_5);
    }
  }

  TNode<BuiltinPtr> phi_bb41_3;
  TNode<Smi> phi_bb41_5;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_3, &phi_bb41_5);
    ca_.Goto(&block37, phi_bb41_3, phi_bb41_5);
  }

  TNode<BuiltinPtr> phi_bb40_3;
  TNode<Smi> phi_bb40_5;
  TNode<IntPtrT> tmp63;
  TNode<JSReceiver> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<Map> tmp66;
  TNode<Int32T> tmp67;
  TNode<BoolT> tmp68;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_3, &phi_bb40_5);
    tmp63 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp64 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_sortState, tmp63});
    tmp65 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp66 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp64, tmp65});
    tmp67 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp66});
    tmp68 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{tmp67});
    ca_.Branch(tmp68, &block42, std::vector<compiler::Node*>{phi_bb40_3, phi_bb40_5}, &block43, std::vector<compiler::Node*>{phi_bb40_3, phi_bb40_5});
  }

  TNode<BuiltinPtr> phi_bb42_3;
  TNode<Smi> phi_bb42_5;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_3, &phi_bb42_5);
    ca_.Goto(&block44, phi_bb42_3, phi_bb42_5, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kDelete_FastDoubleElements_0)));
  }

  TNode<BuiltinPtr> phi_bb43_3;
  TNode<Smi> phi_bb43_5;
  TNode<BoolT> tmp69;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_3, &phi_bb43_5);
    tmp69 = CodeStubAssembler(state_).IsFastSmiElementsKind(TNode<Int32T>{tmp67});
    ca_.Branch(tmp69, &block45, std::vector<compiler::Node*>{phi_bb43_3, phi_bb43_5}, &block46, std::vector<compiler::Node*>{phi_bb43_3, phi_bb43_5});
  }

  TNode<BuiltinPtr> phi_bb45_3;
  TNode<Smi> phi_bb45_5;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_3, &phi_bb45_5);
    ca_.Goto(&block47, phi_bb45_3, phi_bb45_5, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kDelete_FastSmiElements_0)));
  }

  TNode<BuiltinPtr> phi_bb46_3;
  TNode<Smi> phi_bb46_5;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_3, &phi_bb46_5);
    ca_.Goto(&block47, phi_bb46_3, phi_bb46_5, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kDelete_FastObjectElements_0)));
  }

  TNode<BuiltinPtr> phi_bb47_3;
  TNode<Smi> phi_bb47_5;
  TNode<BuiltinPtr> phi_bb47_8;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_3, &phi_bb47_5, &phi_bb47_8);
    ca_.Goto(&block44, phi_bb47_3, phi_bb47_5, phi_bb47_8);
  }

  TNode<BuiltinPtr> phi_bb44_3;
  TNode<Smi> phi_bb44_5;
  TNode<BuiltinPtr> phi_bb44_8;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_3, &phi_bb44_5, &phi_bb44_8);
    ca_.Goto(&block36, phi_bb44_3, phi_bb44_5, phi_bb44_8);
  }

  TNode<BuiltinPtr> phi_bb37_3;
  TNode<Smi> phi_bb37_5;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_3, &phi_bb37_5);
    ca_.Goto(&block36, phi_bb37_3, phi_bb37_5, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kDelete_GenericElementsAccessor_0)));
  }

  TNode<BuiltinPtr> phi_bb36_3;
  TNode<Smi> phi_bb36_5;
  TNode<BuiltinPtr> phi_bb36_8;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_3, &phi_bb36_5, &phi_bb36_8);
    ca_.Goto(&block50, phi_bb36_3, phi_bb36_5, phi_bb36_8);
  }

  TNode<BuiltinPtr> phi_bb50_3;
  TNode<Smi> phi_bb50_5;
  TNode<BuiltinPtr> phi_bb50_8;
  TNode<BoolT> tmp70;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_3, &phi_bb50_5, &phi_bb50_8);
    tmp70 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb50_5}, TNode<Smi>{tmp45});
    ca_.Branch(tmp70, &block48, std::vector<compiler::Node*>{phi_bb50_3, phi_bb50_5, phi_bb50_8}, &block49, std::vector<compiler::Node*>{phi_bb50_3, phi_bb50_5, phi_bb50_8});
  }

  TNode<BuiltinPtr> phi_bb48_3;
  TNode<Smi> phi_bb48_5;
  TNode<BuiltinPtr> phi_bb48_8;
  TNode<Smi> tmp71;
  TNode<Smi> tmp72;
  TNode<Smi> tmp73;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_3, &phi_bb48_5, &phi_bb48_8);
tmp71 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallInterfaceDescriptorFor(ExampleBuiltinForTorqueFunctionPointerType(10)), phi_bb48_8, p_context, p_sortState, phi_bb48_5));
    tmp72 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp73 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb48_5}, TNode<Smi>{tmp72});
    ca_.Goto(&block50, phi_bb48_3, tmp73, phi_bb48_8);
  }

  TNode<BuiltinPtr> phi_bb49_3;
  TNode<Smi> phi_bb49_5;
  TNode<BuiltinPtr> phi_bb49_8;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_3, &phi_bb49_5, &phi_bb49_8);
    ca_.Goto(&block1);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block52);
  }

    ca_.Bind(&block52);
}

TF_BUILTIN(ArrayPowerSort, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CompactReceiverElementsIntoWorkArray_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, false);
    tmp1 = FromConstexpr_Smi_constexpr_int31_0(state_, JSArray::kMaxInlineSortLength);
    tmp2 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp0}, TNode<Smi>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<Smi> tmp3;
  TNode<Smi> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    BinaryInsertionSort_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp3}, TNode<Smi>{tmp4}, TNode<Smi>{tmp0});
    ca_.Goto(&block3);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ArrayPowerSortImpl_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp0});
    ca_.Goto(&block3);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label5(&ca_);
    CheckAccessor_1(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, &label5);
    ca_.Goto(&block6);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ResetToGenericAccessor_0(state_, TNode<SortState>{parameter1}, false);
    ca_.Goto(&block4);
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block4);
  }

  TNode<Smi> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    CopyWorkArrayToReceiver_0(state_, TNode<Context>{parameter0}, TNode<SortState>{parameter1}, TNode<Smi>{tmp0});
    tmp6 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp6);
  }
}

TF_BUILTIN(ArrayPrototypeSort, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Undefined_OR_JSFunction_OR_CallableApiObject_OR_CallableJSProxy_OR_JSWrappedFunction_OR_JSBoundFunction_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp1}, &label3);
    ca_.Goto(&block3);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kBadSortComparisonFunction), TNode<Object>{tmp1});
  }

  TNode<JSReceiver> tmp4;
  TNode<Number> tmp5;
  TNode<Number> tmp6;
  TNode<BoolT> tmp7;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp4 = ca_.CallBuiltin<JSReceiver>(Builtin::kToObject, parameter0, parameter1);
    tmp5 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp4});
    tmp6 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp7 = NumberIsLessThan_0(state_, TNode<Number>{tmp5}, TNode<Number>{tmp6});
    ca_.Branch(tmp7, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    arguments.PopAndReturn(tmp4);
  }

  TNode<SortState> tmp8;
  TNode<JSAny> tmp9;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = NewSortState_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp4}, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>{tmp2}, TNode<Number>{tmp5}, false);
    tmp9 = ca_.CallBuiltin<JSAny>(Builtin::kArrayPowerSort, parameter0, tmp8);
    arguments.PopAndReturn(tmp4);
  }
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=27&c=3
TNode<JSReceiver> LoadSortStateReceiver_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<JSReceiver>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=27&c=3
void StoreSortStateReceiver_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<JSReceiver> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<JSReceiver>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=32&c=3
TNode<Map> LoadSortStateInitialReceiverMap_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Map>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=32&c=3
void StoreSortStateInitialReceiverMap_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Map> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=33&c=3
TNode<Number> LoadSortStateInitialReceiverLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Number> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Number>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=33&c=3
void StoreSortStateInitialReceiverLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Number> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Number>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=36&c=3
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> LoadSortStateUserCmpFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp1 = CodeStubAssembler(state_).LoadReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=36&c=3
void StoreSortStateUserCmpFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    CodeStubAssembler(state_).StoreReference<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=38&c=3
TNode<Boolean> LoadSortStateIsResetToGeneric_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Boolean> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    tmp1 = CodeStubAssembler(state_).LoadReference<Boolean>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Boolean>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=38&c=3
void StoreSortStateIsResetToGeneric_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Boolean> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 20);
    CodeStubAssembler(state_).StoreReference<Boolean>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=43&c=3
TNode<Smi> LoadSortStateMinGallop_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=43&c=3
void StoreSortStateMinGallop_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 24);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=55&c=3
TNode<Smi> LoadSortStatePendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=55&c=3
void StoreSortStatePendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 28);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=56&c=3
TNode<FixedArray> LoadSortStatePendingRuns_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=56&c=3
void StoreSortStatePendingRuns_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 32);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=57&c=3
TNode<FixedArray> LoadSortStatePendingPowers_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=57&c=3
void StoreSortStatePendingPowers_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 36);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=62&c=3
TNode<FixedArray> LoadSortStateWorkArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=62&c=3
void StoreSortStateWorkArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 40);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=65&c=3
TNode<FixedArray> LoadSortStateTempArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArray> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<FixedArray>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=65&c=3
void StoreSortStateTempArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 44);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=68&c=3
TNode<Smi> LoadSortStateSortLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=68&c=3
void StoreSortStateSortLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 48);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=72&c=3
TNode<Smi> LoadSortStateNumberOfUndefined_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Smi> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    tmp1 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<Smi>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=72&c=3
void StoreSortStateNumberOfUndefined_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 52);
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{p_o, tmp0}, p_v);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=24&c=1
TNode<SortState> DownCastForTorqueClass_SortState_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_o, tmp0});
    if (((CodeStubAssembler(state_).ConstexprInt31Equal(static_cast<InstanceType>(279), static_cast<InstanceType>(279))))) {
      ca_.Goto(&block3);
    } else {
      ca_.Goto(&block4);
    }
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    if ((CodeStubAssembler(state_).ClassHasMapConstant<SortState>())) {
      ca_.Goto(&block6);
    } else {
      ca_.Goto(&block7);
    }
  }

  TNode<Map> tmp2;
  TNode<BoolT> tmp3;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp2 = CodeStubAssembler(state_).GetClassMapConstant<SortState>();
    tmp3 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    ca_.Goto(&block1);
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block8);
  }

  TNode<IntPtrT> tmp4;
  TNode<Uint16T> tmp5;
  TNode<Uint32T> tmp6;
  TNode<BoolT> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp5 = CodeStubAssembler(state_).LoadReference<Uint16T>(CodeStubAssembler::Reference{tmp1, tmp4});
    tmp6 = FromConstexpr_uint32_constexpr_uint32_0(state_, CastIfEnumClass<uint32_t>(static_cast<InstanceType>(279)));
    tmp7 = CodeStubAssembler(state_).Word32NotEqual(TNode<Uint32T>{tmp5}, TNode<Uint32T>{tmp6});
    ca_.Branch(tmp7, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block1);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block8);
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block5);
  }

  TNode<Int32T> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Uint16T> tmp10;
  TNode<Uint16T> tmp11;
  TNode<Int32T> tmp12;
  TNode<Uint16T> tmp13;
  TNode<Uint16T> tmp14;
  TNode<Int32T> tmp15;
  TNode<Int32T> tmp16;
  TNode<Uint32T> tmp17;
  TNode<Uint32T> tmp18;
  TNode<BoolT> tmp19;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp8 = FromConstexpr_int32_constexpr_int32_0(state_, (CodeStubAssembler(state_).ConstexprUint32Sub(static_cast<InstanceType>(279), static_cast<InstanceType>(279))));
    tmp9 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp10 = CodeStubAssembler(state_).LoadReference<Uint16T>(CodeStubAssembler::Reference{tmp1, tmp9});
    tmp11 = Convert_uint16_InstanceType_0(state_, TNode<Uint16T>{tmp10});
    tmp12 = Convert_int32_uint16_0(state_, TNode<Uint16T>{tmp11});
    tmp13 = FromConstexpr_InstanceType_constexpr_InstanceType_0(state_, static_cast<InstanceType>(279));
    tmp14 = Convert_uint16_InstanceType_0(state_, TNode<Uint16T>{tmp13});
    tmp15 = Convert_int32_uint16_0(state_, TNode<Uint16T>{tmp14});
    tmp16 = CodeStubAssembler(state_).Int32Sub(TNode<Int32T>{tmp12}, TNode<Int32T>{tmp15});
    tmp17 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp16});
    tmp18 = CodeStubAssembler(state_).Unsigned(TNode<Int32T>{tmp8});
    tmp19 = CodeStubAssembler(state_).Uint32GreaterThan(TNode<Uint32T>{tmp17}, TNode<Uint32T>{tmp18});
    ca_.Branch(tmp19, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block1);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block5);
  }

  TNode<SortState> tmp20;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp20 = TORQUE_CAST(TNode<HeapObject>{p_o});
    ca_.Goto(&block15);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block15);
  return TNode<SortState>{tmp20};
}

TF_BUILTIN(CanUseSameAccessor_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedParameter<Map>(Descriptor::kInitialReceiverMap);
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedParameter<Number>(Descriptor::kInitialReceiverLength);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<False> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<BoolT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter3});
    ca_.Branch(tmp4, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 392});
      CodeStubAssembler(state_).FailAssert("Torque assert 'TaggedIsSmi(initialReceiverLength)' failed", pos_stack);
    }
  }

  TNode<JSArray> tmp5;
  TNode<Smi> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Number> tmp8;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  TNode<Boolean> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp8 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp5, tmp7});
    tmp9 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp8});
    tmp10 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp9}, TNode<Smi>{tmp6});
    tmp11 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp10});
    CodeStubAssembler(state_).Return(tmp11);
  }
}

TF_BUILTIN(CanUseSameAccessor_FastSmiElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedParameter<Map>(Descriptor::kInitialReceiverMap);
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedParameter<Number>(Descriptor::kInitialReceiverLength);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<False> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<BoolT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter3});
    ca_.Branch(tmp4, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 392});
      CodeStubAssembler(state_).FailAssert("Torque assert 'TaggedIsSmi(initialReceiverLength)' failed", pos_stack);
    }
  }

  TNode<JSArray> tmp5;
  TNode<Smi> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Number> tmp8;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  TNode<Boolean> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp8 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp5, tmp7});
    tmp9 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp8});
    tmp10 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp9}, TNode<Smi>{tmp6});
    tmp11 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp10});
    CodeStubAssembler(state_).Return(tmp11);
  }
}

TF_BUILTIN(CanUseSameAccessor_FastObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<Map> parameter2 = UncheckedParameter<Map>(Descriptor::kInitialReceiverMap);
  USE(parameter2);
  TNode<Number> parameter3 = UncheckedParameter<Number>(Descriptor::kInitialReceiverLength);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<False> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }

  TNode<BoolT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = CodeStubAssembler(state_).TaggedIsSmi(TNode<Object>{parameter3});
    ca_.Branch(tmp4, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"third_party/v8/builtins/array-sort.tq", 392});
      CodeStubAssembler(state_).FailAssert("Torque assert 'TaggedIsSmi(initialReceiverLength)' failed", pos_stack);
    }
  }

  TNode<JSArray> tmp5;
  TNode<Smi> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Number> tmp8;
  TNode<Smi> tmp9;
  TNode<BoolT> tmp10;
  TNode<Boolean> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp6 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter3});
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp8 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp5, tmp7});
    tmp9 = UnsafeCast_Smi_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp8});
    tmp10 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp9}, TNode<Smi>{tmp6});
    tmp11 = CodeStubAssembler(state_).SelectBooleanConstant(TNode<BoolT>{tmp10});
    CodeStubAssembler(state_).Return(tmp11);
  }
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=164&c=7
TNode<BoolT> Is_FastJSArray_JSReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_o}, &label1);
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

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=165&c=15
TNode<JSArray> UnsafeCast_FastJSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_FastJSArray_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSArray> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSArray>{tmp1};
}

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=243&c=18
TNode<JSObject> UnsafeCast_JSObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSObject_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSObject> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSObject>{tmp1};
}

TF_BUILTIN(LoadNoHasPropertyCheck_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSAny> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp1}, TNode<JSAny>{parameter2});
    CodeStubAssembler(state_).Return(tmp2);
  }
}

TF_BUILTIN(Load_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Boolean> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = CodeStubAssembler(state_).HasProperty_Inline(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp1}, TNode<JSAny>{parameter2});
    tmp3 = CodeStubAssembler(state_).IsFalse(TNode<Boolean>{tmp2});
    ca_.Branch(tmp3, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<TheHole> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp4 = TheHole_0(state_);
    CodeStubAssembler(state_).Return(tmp4);
  }

  TNode<JSAny> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp5 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp1}, TNode<JSAny>{parameter2});
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(Store_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<JSAny> tmp2;
  TNode<Smi> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, parameter0, tmp1, parameter2, parameter3);
    tmp3 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp3);
  }
}

TF_BUILTIN(Delete_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<SortState> parameter1 = UncheckedParameter<SortState>(Descriptor::kSortState);
  USE(parameter1);
  TNode<Smi> parameter2 = UncheckedParameter<Smi>(Descriptor::kIndex);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Smi> tmp2;
  TNode<Boolean> tmp3;
  TNode<Smi> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    tmp1 = CodeStubAssembler(state_).LoadReference<JSReceiver>(CodeStubAssembler::Reference{parameter1, tmp0});
    tmp2 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, CastIfEnumClass<LanguageMode>(LanguageMode::kStrict));
    tmp3 = ca_.CallBuiltin<Boolean>(Builtin::kDeleteProperty, parameter0, tmp1, parameter2, tmp2);
    tmp4 = kSuccess_0(state_);
    CodeStubAssembler(state_).Return(tmp4);
  }
}

} // namespace internal
} // namespace v8
