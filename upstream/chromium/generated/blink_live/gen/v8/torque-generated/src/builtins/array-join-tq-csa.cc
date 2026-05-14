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
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/array-flat-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/builtins-string-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/promise-misc-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/builtins/typed-array-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-buffer-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/src/objects/string-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=12&c=1
int31_t kMaxBufferChunkSize_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  return FixedArray::kMaxRegularLength;}

TF_BUILTIN(LoadJoinElement_DictionaryElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<FixedArrayBase> tmp2;
  TNode<NumberDictionary> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<JSAny> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp1});
    tmp3 = UnsafeCast_NumberDictionary_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp2});
    tmp4 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{parameter2});
    compiler::CodeAssemblerLabel label6(&ca_);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp5 = CodeStubAssembler(state_).BasicLoadNumberDictionaryElement(TNode<NumberDictionary>{tmp3}, TNode<IntPtrT>{tmp4}, &label6, &label7);
    ca_.Goto(&block5);
    if (label6.is_used()) {
      ca_.Bind(&label6);
      ca_.Goto(&block6);
    }
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block7);
    }
  }

  TNode<Number> tmp8;
  TNode<JSAny> tmp9;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{parameter2});
    tmp9 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSAny>{tmp8});
    CodeStubAssembler(state_).Return(tmp9);
  }

  TNode<String> tmp10;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp10 = kEmptyString_0(state_);
    CodeStubAssembler(state_).Return(tmp10);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).Return(tmp5);
  }
}

TF_BUILTIN(LoadJoinElement_FastSmiOrObjectElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<FixedArrayBase> tmp2;
  TNode<FixedArray> tmp3;
  TNode<Union<HeapObject, TaggedIndex>> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp1});
    tmp3 = UnsafeCast_FixedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp2});
    std::tie(tmp4, tmp5, tmp6) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp3}).Flatten();
    tmp7 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{parameter2});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp10 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp10, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Union<HeapObject, TaggedIndex>> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Object> tmp15;
  TNode<TheHole> tmp16;
  TNode<BoolT> tmp17;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp11 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp7});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp4}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = TheHole_0(state_);
    tmp17 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp15}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp16});
    ca_.Branch(tmp17, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> tmp18;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp18 = kEmptyString_0(state_);
    ca_.Goto(&block11, tmp18);
  }

  TNode<JSAny> tmp19;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp19 = UnsafeCast_JSAny_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp15});
    ca_.Goto(&block11, tmp19);
  }

  TNode<JSAny> phi_bb11_6;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_6);
    CodeStubAssembler(state_).Return(phi_bb11_6);
  }
}

TF_BUILTIN(LoadJoinElement_FastDoubleElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<FixedArrayBase> tmp2;
  TNode<FixedDoubleArray> tmp3;
  TNode<Union<HeapObject, TaggedIndex>> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp2 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp1});
    tmp3 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp2});
    std::tie(tmp4, tmp5, tmp6) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp3}).Flatten();
    tmp7 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{parameter2});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp10 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp10, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Union<HeapObject, TaggedIndex>> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<BoolT> tmp15;
  TNode<BoolT> tmp16;
  TNode<Float64T> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp11 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp7});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp4}, TNode<IntPtrT>{tmp12}).Flatten();
    std::tie(tmp15, tmp16, tmp17) = LoadFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp13}, TNode<IntPtrT>{tmp14}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp15, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Undefined> tmp18;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp18 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp18);
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Branch(tmp16, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp19;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp19 = kEmptyString_0(state_);
    CodeStubAssembler(state_).Return(tmp19);
  }

  TNode<HeapNumber> tmp20;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp20 = CodeStubAssembler(state_).AllocateHeapNumberWithValue(TNode<Float64T>{tmp17});
    CodeStubAssembler(state_).Return(tmp20);
  }
}

TF_BUILTIN(ConvertToLocaleString, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kElement);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kLocales);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kOptions);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).IsNullOrUndefined(TNode<Object>{parameter1});
    ca_.Branch(tmp0, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp1;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp1 = kEmptyString_0(state_);
    CodeStubAssembler(state_).Return(tmp1);
  }

  TNode<JSAny> tmp2;
  TNode<JSAny> tmp3;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_JSAny_constexpr_string_0(state_, "toLocaleString");
    tmp3 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSAny>{tmp2});
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp3}, &label5);
    ca_.Goto(&block5);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, tmp3);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> tmp6;
  TNode<String> tmp7;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp6 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp4}, TNode<JSAny>{parameter1}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter3});
    tmp7 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp6});
    CodeStubAssembler(state_).Return(tmp7);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=108&c=1
TNode<BoolT> CannotUseSameArrayAccessor_JSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<BuiltinPtr> p_loadFn, TNode<JSReceiver> p_receiver, TNode<Map> p_originalMap, TNode<Number> p_originalLen) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{p_loadFn}, TNode<Smi>{ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_GenericElementsAccessor_0))});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp1);
  }

  TNode<JSArray> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<Map> tmp4;
  TNode<BoolT> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp2 = UnsafeCast_JSArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver});
    tmp3 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp4 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp2, tmp3});
    tmp5 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{p_originalMap}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp4});
    ca_.Branch(tmp5, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp6);
  }

  TNode<IntPtrT> tmp7;
  TNode<Number> tmp8;
  TNode<BoolT> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp8 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp2, tmp7});
    tmp9 = IsNumberNotEqual_0(state_, TNode<Number>{p_originalLen}, TNode<Number>{tmp8});
    ca_.Branch(tmp9, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp10;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp10 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp10);
  }

  TNode<BoolT> tmp11;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp11 = CodeStubAssembler(state_).IsNoElementsProtectorCellInvalid();
    ca_.Branch(tmp11, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp12;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp12 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp12);
  }

  TNode<BoolT> tmp13;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp13 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp13);
  }

  TNode<BoolT> phi_bb1_5;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5);
    ca_.Goto(&block10, phi_bb1_5);
  }

  TNode<BoolT> phi_bb10_5;
    ca_.Bind(&block10, &phi_bb10_5);
  return TNode<BoolT>{phi_bb10_5};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=120&c=1
TNode<BoolT> CannotUseSameArrayAccessor_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<BuiltinPtr> p__loadFn, TNode<JSReceiver> p_receiver, TNode<Map> p__initialMap, TNode<Number> p__initialLen) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<JSArrayBuffer> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver});
    tmp1 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp2 = CodeStubAssembler(state_).LoadReference<JSArrayBuffer>(CodeStubAssembler::Reference{tmp0, tmp1});
    tmp3 = IsDetachedBuffer_0(state_, TNode<JSArrayBuffer>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp4);
  }

  TNode<BoolT> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = IsVariableLengthJSArrayBufferView_0(state_, TNode<JSArrayBufferView>{tmp0});
    ca_.Branch(tmp5, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp6;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp6);
  }

  TNode<BoolT> tmp7;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp7);
  }

  TNode<BoolT> phi_bb1_5;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_5);
    ca_.Goto(&block6, phi_bb1_5);
  }

  TNode<BoolT> phi_bb6_5;
    ca_.Bind(&block6, &phi_bb6_5);
  return TNode<BoolT>{phi_bb6_5};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=142&c=1
TNode<IntPtrT> AddStringLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_lenA, TNode<IntPtrT> p_lenB) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).TryIntPtrAdd(TNode<IntPtrT>{p_lenA}, TNode<IntPtrT>{p_lenB}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block3);
  }

  TNode<IntPtrT> tmp2;
  TNode<BoolT> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, String::kMaxLength);
    tmp3 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp2});
    ca_.Branch(tmp3, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block3);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block8);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block8);
  return TNode<IntPtrT>{tmp0};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=306&c=1
TorqueStructBuffer_0 NewBuffer_0(compiler::CodeAssemblerState* state_, TNode<UintPtrT> p_len, TNode<String> p_sep) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<UintPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_uintptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp1 = CodeStubAssembler(state_).UintPtrGreaterThanOrEqual(TNode<UintPtrT>{p_len}, TNode<UintPtrT>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block4, tmp2);
  }

  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp3 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp4 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{p_len}, TNode<UintPtrT>{tmp3});
    tmp5 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp4});
    ca_.Goto(&block4, tmp5);
  }

  TNode<IntPtrT> phi_bb4_2;
  TNode<IntPtrT> tmp6;
  TNode<BoolT> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_2);
    tmp6 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb4_2}, TNode<IntPtrT>{tmp6});
    ca_.Branch(tmp7, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 310});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedBufferSize > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> tmp8;
  TNode<Union<HeapObject, TaggedIndex>> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<UintPtrT> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<UintPtrT> tmp15;
  TNode<BoolT> tmp16;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp8 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb4_2});
    std::tie(tmp9, tmp10, tmp11) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp8}).Flatten();
    tmp12 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp13 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp12});
    tmp14 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp13});
    tmp15 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp11});
    tmp16 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp15});
    ca_.Branch(tmp16, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<Union<HeapObject, TaggedIndex>> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<Undefined> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<Map> tmp23;
  TNode<BoolT> tmp24;
  TNode<Null> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp17 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp13});
    tmp18 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp10}, TNode<IntPtrT>{tmp17});
    std::tie(tmp19, tmp20) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp9}, TNode<IntPtrT>{tmp18}).Flatten();
    tmp21 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp19, tmp20}, tmp21);
    tmp22 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp23 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_sep, tmp22});
    tmp24 = CodeStubAssembler(state_).IsOneByteStringMap(TNode<Map>{tmp23});
    tmp25 = Null_0(state_);
    tmp26 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp27 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block17);
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block17);
  return TorqueStructBuffer_0{TNode<FixedArray>{tmp8}, TNode<FixedArray>{tmp8}, TNode<IntPtrT>{tmp26}, TNode<IntPtrT>{tmp27}, TNode<BoolT>{tmp24}, TNode<PrimitiveHeapObject>{tmp25}};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=323&c=1
TNode<String> BufferJoin_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructBuffer_0 p_buffer, TNode<String> p_sep) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Union<SeqOneByteString, SeqTwoByteString, String>> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).IsValidPositiveSmi(TNode<IntPtrT>{p_buffer.totalStringLength});
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 325});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsValidPositiveSmi(buffer.totalStringLength)' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp1;
  TNode<BoolT> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp2 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{p_buffer.totalStringLength}, TNode<IntPtrT>{tmp1});
    ca_.Branch(tmp2, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp3;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp3 = kEmptyString_0(state_);
    ca_.Goto(&block1, tmp3);
  }

  TNode<IntPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp5 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{p_buffer.index}, TNode<IntPtrT>{tmp4});
    ca_.Branch(tmp5, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp6;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp6 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{p_buffer.head}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{p_buffer.chunk});
    ca_.Goto(&block10, tmp6);
  }

  TNode<BoolT> tmp7;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp7 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block10, tmp7);
  }

  TNode<BoolT> phi_bb10_9;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_9);
    ca_.Branch(phi_bb10_9, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<UintPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<UintPtrT> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    std::tie(tmp8, tmp9, tmp10) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_buffer.head}).Flatten();
    tmp11 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp12 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp11});
    tmp13 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp12});
    tmp14 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp10});
    tmp15 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp13}, TNode<UintPtrT>{tmp14});
    ca_.Branch(tmp15, &block16, std::vector<compiler::Node*>{}, &block17, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<Object> tmp20;
  TNode<String> tmp21;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp16 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp12});
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp16});
    std::tie(tmp18, tmp19) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp8}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp18, tmp19});
    compiler::CodeAssemblerLabel label22(&ca_);
    tmp21 = Cast_String_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp20}, &label22);
    ca_.Goto(&block22);
    if (label22.is_used()) {
      ca_.Bind(&label22);
      ca_.Goto(&block23);
    }
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp23;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    compiler::CodeAssemblerLabel label24(&ca_);
    tmp23 = Cast_Smi_0(state_, TNode<Object>{ca_.UncheckedCast<Object>(tmp20)}, &label24);
    ca_.Goto(&block26);
    if (label24.is_used()) {
      ca_.Bind(&label24);
      ca_.Goto(&block27);
    }
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block1, tmp21);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:345:9");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Smi> tmp25;
  TNode<BoolT> tmp26;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp25 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp26 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp23}, TNode<Smi>{tmp25});
    ca_.Branch(tmp26, &block28, std::vector<compiler::Node*>{}, &block29, std::vector<compiler::Node*>{});
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 341});
      CodeStubAssembler(state_).FailAssert("Torque assert 'nofSeparators > 0' failed", pos_stack);
    }
  }

  TNode<String> tmp27;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp27 = ca_.CallBuiltin<String>(Builtin::kStringRepeat, p_context, p_sep, tmp23);
    ca_.Goto(&block1, tmp27);
  }

  TNode<UintPtrT> tmp28;
  TNode<Uint32T> tmp29;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp28 = CodeStubAssembler(state_).Unsigned(TNode<IntPtrT>{p_buffer.totalStringLength});
    tmp29 = Convert_uint32_uintptr_0(state_, TNode<UintPtrT>{tmp28});
    ca_.Branch(p_buffer.isOneByte, &block30, std::vector<compiler::Node*>{}, &block31, std::vector<compiler::Node*>{});
  }

  TNode<Union<SeqOneByteString, String>> tmp30;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp30 = AllocateSeqOneByteString_0(state_, TNode<Uint32T>{tmp29});
    ca_.Goto(&block32, tmp30);
  }

  TNode<Union<SeqTwoByteString, String>> tmp31;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp31 = AllocateSeqTwoByteString_0(state_, TNode<Uint32T>{tmp29});
    ca_.Goto(&block32, tmp31);
  }

  TNode<Union<SeqOneByteString, SeqTwoByteString, String>> phi_bb32_9;
  TNode<String> tmp32;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_9);
    tmp32 = ArrayBuiltinsAssembler(state_).CallJSArrayArrayJoinConcatToSequentialString(TNode<FixedArray>{p_buffer.head}, TNode<IntPtrT>{p_buffer.index}, TNode<String>{p_sep}, TNode<String>{phi_bb32_9});
    ca_.Goto(&block1, tmp32);
  }

  TNode<String> phi_bb1_8;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_8);
    ca_.Goto(&block34, phi_bb1_8);
  }

  TNode<String> phi_bb34_8;
    ca_.Bind(&block34, &phi_bb34_8);
  return TNode<String>{phi_bb34_8};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=357&c=1
TNode<String> FastArrayJoin_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, ElementsKind p_kind, TNode<JSArray> p_array, TNode<String> p_sep, TNode<Number> p_lengthNumber) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<UintPtrT, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, String> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, UintPtrT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, String> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, BoolT> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block60(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, BoolT> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block70(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block72(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block76(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block78(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block79(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block86(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block87(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block80(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block91(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, IntPtrT> block92(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block95(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block101(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block102(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block120(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block123(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block128(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block133(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block140(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block143(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block146(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block145(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block148(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block147(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block149(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block156(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block157(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block150(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block161(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, IntPtrT> block162(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block165(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block164(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block171(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block172(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block180(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block181(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block189(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block190(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block138(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block196(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block198(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block197(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block200(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block205(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block206(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block137(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block124(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block211(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block210(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block213(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block212(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block214(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block221(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block222(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block215(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block225(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block226(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, IntPtrT> block227(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block230(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block229(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block236(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, FixedArray> block237(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block245(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block246(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block254(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block255(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject> block125(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block258(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block260(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block261(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block259(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block265(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block266(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, BoolT> block267(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block263(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block264(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block268(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block269(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block270(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block274(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block273(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block276(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block275(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block277(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block284(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block285(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block278(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block288(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block289(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block290(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block293(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block292(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray> block299(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray> block300(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block308(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block309(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block317(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block318(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block279(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block271(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block262(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block321(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<FixedArrayBase> tmp1;
  TNode<UintPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<FixedArray> tmp5;
  TNode<FixedArray> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<BoolT> tmp9;
  TNode<PrimitiveHeapObject> tmp10;
  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Number> tmp13;
  TNode<UintPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp1 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{p_array, tmp0});
    tmp2 = Convert_uintptr_Number_0(state_, TNode<Number>{p_lengthNumber});
    tmp3 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{p_sep});
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp5, tmp6, tmp7, tmp8, tmp9, tmp10) = NewBuffer_0(state_, TNode<UintPtrT>{tmp2}, TNode<String>{p_sep}).Flatten();
    tmp11 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp12 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp13 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_array, tmp12});
    tmp14 = Convert_uintptr_Number_0(state_, TNode<Number>{tmp13});
    tmp15 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp14}, TNode<UintPtrT>{tmp2});
    ca_.Branch(tmp15, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{tmp2, tmp11});
  }

  TNode<UintPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp16 = CodeStubAssembler(state_).UintPtrSub(TNode<UintPtrT>{tmp2}, TNode<UintPtrT>{tmp14});
    tmp17 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp16});
    ca_.Goto(&block3, tmp14, tmp17);
  }

  TNode<UintPtrT> phi_bb3_5;
  TNode<IntPtrT> phi_bb3_14;
  TNode<UintPtrT> tmp18;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_5, &phi_bb3_14);
    tmp18 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block6, tmp4, tmp6, tmp7, tmp8, tmp9, tmp10, tmp18);
  }

  TNode<IntPtrT> phi_bb6_7;
  TNode<FixedArray> phi_bb6_9;
  TNode<IntPtrT> phi_bb6_10;
  TNode<IntPtrT> phi_bb6_11;
  TNode<BoolT> phi_bb6_12;
  TNode<PrimitiveHeapObject> phi_bb6_13;
  TNode<UintPtrT> phi_bb6_15;
  TNode<BoolT> tmp19;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7, &phi_bb6_9, &phi_bb6_10, &phi_bb6_11, &phi_bb6_12, &phi_bb6_13, &phi_bb6_15);
    tmp19 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb6_15}, TNode<UintPtrT>{phi_bb3_5});
    ca_.Branch(tmp19, &block4, std::vector<compiler::Node*>{phi_bb6_7, phi_bb6_9, phi_bb6_10, phi_bb6_11, phi_bb6_12, phi_bb6_13, phi_bb6_15}, &block5, std::vector<compiler::Node*>{phi_bb6_7, phi_bb6_9, phi_bb6_10, phi_bb6_11, phi_bb6_12, phi_bb6_13, phi_bb6_15});
  }

  TNode<IntPtrT> phi_bb4_7;
  TNode<FixedArray> phi_bb4_9;
  TNode<IntPtrT> phi_bb4_10;
  TNode<IntPtrT> phi_bb4_11;
  TNode<BoolT> phi_bb4_12;
  TNode<PrimitiveHeapObject> phi_bb4_13;
  TNode<UintPtrT> phi_bb4_15;
  TNode<UintPtrT> tmp20;
  TNode<BoolT> tmp21;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_7, &phi_bb4_9, &phi_bb4_10, &phi_bb4_11, &phi_bb4_12, &phi_bb4_13, &phi_bb4_15);
    tmp20 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp21 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{phi_bb4_15}, TNode<UintPtrT>{tmp20});
    ca_.Branch(tmp21, &block7, std::vector<compiler::Node*>{phi_bb4_7, phi_bb4_9, phi_bb4_10, phi_bb4_11, phi_bb4_12, phi_bb4_13, phi_bb4_15}, &block8, std::vector<compiler::Node*>{phi_bb4_7, phi_bb4_9, phi_bb4_10, phi_bb4_11, phi_bb4_12, phi_bb4_13, phi_bb4_15});
  }

  TNode<IntPtrT> phi_bb7_7;
  TNode<FixedArray> phi_bb7_9;
  TNode<IntPtrT> phi_bb7_10;
  TNode<IntPtrT> phi_bb7_11;
  TNode<BoolT> phi_bb7_12;
  TNode<PrimitiveHeapObject> phi_bb7_13;
  TNode<UintPtrT> phi_bb7_15;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_7, &phi_bb7_9, &phi_bb7_10, &phi_bb7_11, &phi_bb7_12, &phi_bb7_13, &phi_bb7_15);
    tmp22 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp23 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb7_7}, TNode<IntPtrT>{tmp22});
    ca_.Goto(&block8, tmp23, phi_bb7_9, phi_bb7_10, phi_bb7_11, phi_bb7_12, phi_bb7_13, phi_bb7_15);
  }

  TNode<IntPtrT> phi_bb8_7;
  TNode<FixedArray> phi_bb8_9;
  TNode<IntPtrT> phi_bb8_10;
  TNode<IntPtrT> phi_bb8_11;
  TNode<BoolT> phi_bb8_12;
  TNode<PrimitiveHeapObject> phi_bb8_13;
  TNode<UintPtrT> phi_bb8_15;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_7, &phi_bb8_9, &phi_bb8_10, &phi_bb8_11, &phi_bb8_12, &phi_bb8_13, &phi_bb8_15);
    if (((CodeStubAssembler(state_).IsDoubleElementsKind(p_kind)))) {
      ca_.Goto(&block9, phi_bb8_9, phi_bb8_10, phi_bb8_11, phi_bb8_12, phi_bb8_13, phi_bb8_15);
    } else {
      ca_.Goto(&block10, phi_bb8_9, phi_bb8_10, phi_bb8_11, phi_bb8_12, phi_bb8_13, phi_bb8_15);
    }
  }

  TNode<FixedArray> phi_bb9_9;
  TNode<IntPtrT> phi_bb9_10;
  TNode<IntPtrT> phi_bb9_11;
  TNode<BoolT> phi_bb9_12;
  TNode<PrimitiveHeapObject> phi_bb9_13;
  TNode<UintPtrT> phi_bb9_15;
  TNode<FixedDoubleArray> tmp24;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_9, &phi_bb9_10, &phi_bb9_11, &phi_bb9_12, &phi_bb9_13, &phi_bb9_15);
    tmp24 = UnsafeCast_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp1});
    if (((CodeStubAssembler(state_).IsHoleyElementsKind(p_kind)))) {
      ca_.Goto(&block12, phi_bb9_9, phi_bb9_10, phi_bb9_11, phi_bb9_12, phi_bb9_13, phi_bb9_15);
    } else {
      ca_.Goto(&block13, phi_bb9_9, phi_bb9_10, phi_bb9_11, phi_bb9_12, phi_bb9_13, phi_bb9_15);
    }
  }

  TNode<FixedArray> phi_bb12_9;
  TNode<IntPtrT> phi_bb12_10;
  TNode<IntPtrT> phi_bb12_11;
  TNode<BoolT> phi_bb12_12;
  TNode<PrimitiveHeapObject> phi_bb12_13;
  TNode<UintPtrT> phi_bb12_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp25;
  TNode<IntPtrT> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<UintPtrT> tmp28;
  TNode<UintPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  TNode<UintPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<BoolT> tmp33;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_9, &phi_bb12_10, &phi_bb12_11, &phi_bb12_12, &phi_bb12_13, &phi_bb12_15);
    std::tie(tmp25, tmp26, tmp27) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp24}).Flatten();
    tmp28 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp29 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb12_15}, TNode<UintPtrT>{tmp28});
    tmp30 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb12_15});
    tmp31 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp30});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp27});
    tmp33 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp31}, TNode<UintPtrT>{tmp32});
    ca_.Branch(tmp33, &block21, std::vector<compiler::Node*>{phi_bb12_9, phi_bb12_10, phi_bb12_11, phi_bb12_12, phi_bb12_13, phi_bb12_15, phi_bb12_15}, &block22, std::vector<compiler::Node*>{phi_bb12_9, phi_bb12_10, phi_bb12_11, phi_bb12_12, phi_bb12_13, phi_bb12_15, phi_bb12_15});
  }

  TNode<FixedArray> phi_bb21_9;
  TNode<IntPtrT> phi_bb21_10;
  TNode<IntPtrT> phi_bb21_11;
  TNode<BoolT> phi_bb21_12;
  TNode<PrimitiveHeapObject> phi_bb21_13;
  TNode<UintPtrT> phi_bb21_22;
  TNode<UintPtrT> phi_bb21_23;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  TNode<Union<HeapObject, TaggedIndex>> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<BoolT> tmp38;
  TNode<BoolT> tmp39;
  TNode<Float64T> tmp40;
  if (block21.is_used()) {
    ca_.Bind(&block21, &phi_bb21_9, &phi_bb21_10, &phi_bb21_11, &phi_bb21_12, &phi_bb21_13, &phi_bb21_22, &phi_bb21_23);
    tmp34 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp30});
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp26}, TNode<IntPtrT>{tmp34});
    std::tie(tmp36, tmp37) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp25}, TNode<IntPtrT>{tmp35}).Flatten();
    std::tie(tmp38, tmp39, tmp40) = LoadFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp36}, TNode<IntPtrT>{tmp37}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Branch(tmp38, &block26, std::vector<compiler::Node*>{phi_bb21_9, phi_bb21_10, phi_bb21_11, phi_bb21_12, phi_bb21_13, phi_bb21_22, phi_bb21_23}, &block27, std::vector<compiler::Node*>{phi_bb21_9, phi_bb21_10, phi_bb21_11, phi_bb21_12, phi_bb21_13, phi_bb21_22, phi_bb21_23});
  }

  TNode<FixedArray> phi_bb22_9;
  TNode<IntPtrT> phi_bb22_10;
  TNode<IntPtrT> phi_bb22_11;
  TNode<BoolT> phi_bb22_12;
  TNode<PrimitiveHeapObject> phi_bb22_13;
  TNode<UintPtrT> phi_bb22_22;
  TNode<UintPtrT> phi_bb22_23;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_9, &phi_bb22_10, &phi_bb22_11, &phi_bb22_12, &phi_bb22_13, &phi_bb22_22, &phi_bb22_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb26_9;
  TNode<IntPtrT> phi_bb26_10;
  TNode<IntPtrT> phi_bb26_11;
  TNode<BoolT> phi_bb26_12;
  TNode<PrimitiveHeapObject> phi_bb26_13;
  TNode<UintPtrT> phi_bb26_22;
  TNode<UintPtrT> phi_bb26_23;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_9, &phi_bb26_10, &phi_bb26_11, &phi_bb26_12, &phi_bb26_13, &phi_bb26_22, &phi_bb26_23);
    ca_.Goto(&block16, phi_bb26_9, phi_bb26_10, phi_bb26_11, phi_bb26_12, phi_bb26_13);
  }

  TNode<FixedArray> phi_bb27_9;
  TNode<IntPtrT> phi_bb27_10;
  TNode<IntPtrT> phi_bb27_11;
  TNode<BoolT> phi_bb27_12;
  TNode<PrimitiveHeapObject> phi_bb27_13;
  TNode<UintPtrT> phi_bb27_22;
  TNode<UintPtrT> phi_bb27_23;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_9, &phi_bb27_10, &phi_bb27_11, &phi_bb27_12, &phi_bb27_13, &phi_bb27_22, &phi_bb27_23);
    ca_.Branch(tmp39, &block28, std::vector<compiler::Node*>{phi_bb27_9, phi_bb27_10, phi_bb27_11, phi_bb27_12, phi_bb27_13, phi_bb27_22, phi_bb27_23}, &block29, std::vector<compiler::Node*>{phi_bb27_9, phi_bb27_10, phi_bb27_11, phi_bb27_12, phi_bb27_13, phi_bb27_22, phi_bb27_23});
  }

  TNode<FixedArray> phi_bb28_9;
  TNode<IntPtrT> phi_bb28_10;
  TNode<IntPtrT> phi_bb28_11;
  TNode<BoolT> phi_bb28_12;
  TNode<PrimitiveHeapObject> phi_bb28_13;
  TNode<UintPtrT> phi_bb28_22;
  TNode<UintPtrT> phi_bb28_23;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_9, &phi_bb28_10, &phi_bb28_11, &phi_bb28_12, &phi_bb28_13, &phi_bb28_22, &phi_bb28_23);
    ca_.Goto(&block16, phi_bb28_9, phi_bb28_10, phi_bb28_11, phi_bb28_12, phi_bb28_13);
  }

  TNode<FixedArray> phi_bb29_9;
  TNode<IntPtrT> phi_bb29_10;
  TNode<IntPtrT> phi_bb29_11;
  TNode<BoolT> phi_bb29_12;
  TNode<PrimitiveHeapObject> phi_bb29_13;
  TNode<UintPtrT> phi_bb29_22;
  TNode<UintPtrT> phi_bb29_23;
  TNode<String> tmp41;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_9, &phi_bb29_10, &phi_bb29_11, &phi_bb29_12, &phi_bb29_13, &phi_bb29_22, &phi_bb29_23);
    tmp41 = CodeStubAssembler(state_).Float64ToString(TNode<Float64T>{tmp40});
    ca_.Goto(&block14, phi_bb29_9, phi_bb29_10, phi_bb29_11, phi_bb29_12, phi_bb29_13, tmp29, tmp41);
  }

  TNode<FixedArray> phi_bb16_9;
  TNode<IntPtrT> phi_bb16_10;
  TNode<IntPtrT> phi_bb16_11;
  TNode<BoolT> phi_bb16_12;
  TNode<PrimitiveHeapObject> phi_bb16_13;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_9, &phi_bb16_10, &phi_bb16_11, &phi_bb16_12, &phi_bb16_13);
    ca_.Goto(&block6, phi_bb8_7, phi_bb16_9, phi_bb16_10, phi_bb16_11, phi_bb16_12, phi_bb16_13, tmp29);
  }

  TNode<FixedArray> phi_bb13_9;
  TNode<IntPtrT> phi_bb13_10;
  TNode<IntPtrT> phi_bb13_11;
  TNode<BoolT> phi_bb13_12;
  TNode<PrimitiveHeapObject> phi_bb13_13;
  TNode<UintPtrT> phi_bb13_15;
  TNode<Union<HeapObject, TaggedIndex>> tmp42;
  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<UintPtrT> tmp45;
  TNode<UintPtrT> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<UintPtrT> tmp48;
  TNode<UintPtrT> tmp49;
  TNode<BoolT> tmp50;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_9, &phi_bb13_10, &phi_bb13_11, &phi_bb13_12, &phi_bb13_13, &phi_bb13_15);
    std::tie(tmp42, tmp43, tmp44) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp24}).Flatten();
    tmp45 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp46 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb13_15}, TNode<UintPtrT>{tmp45});
    tmp47 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb13_15});
    tmp48 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp47});
    tmp49 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp44});
    tmp50 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp48}, TNode<UintPtrT>{tmp49});
    ca_.Branch(tmp50, &block34, std::vector<compiler::Node*>{phi_bb13_9, phi_bb13_10, phi_bb13_11, phi_bb13_12, phi_bb13_13, phi_bb13_15, phi_bb13_15}, &block35, std::vector<compiler::Node*>{phi_bb13_9, phi_bb13_10, phi_bb13_11, phi_bb13_12, phi_bb13_13, phi_bb13_15, phi_bb13_15});
  }

  TNode<FixedArray> phi_bb34_9;
  TNode<IntPtrT> phi_bb34_10;
  TNode<IntPtrT> phi_bb34_11;
  TNode<BoolT> phi_bb34_12;
  TNode<PrimitiveHeapObject> phi_bb34_13;
  TNode<UintPtrT> phi_bb34_22;
  TNode<UintPtrT> phi_bb34_23;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<Union<HeapObject, TaggedIndex>> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<BoolT> tmp55;
  TNode<BoolT> tmp56;
  TNode<Float64T> tmp57;
  TNode<BoolT> tmp58;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_9, &phi_bb34_10, &phi_bb34_11, &phi_bb34_12, &phi_bb34_13, &phi_bb34_22, &phi_bb34_23);
    tmp51 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp47});
    tmp52 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp43}, TNode<IntPtrT>{tmp51});
    std::tie(tmp53, tmp54) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp42}, TNode<IntPtrT>{tmp52}).Flatten();
    std::tie(tmp55, tmp56, tmp57) = LoadFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp53}, TNode<IntPtrT>{tmp54}, TorqueStructUnsafe_0{}}).Flatten();
    tmp58 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp55});
    ca_.Branch(tmp58, &block39, std::vector<compiler::Node*>{phi_bb34_9, phi_bb34_10, phi_bb34_11, phi_bb34_12, phi_bb34_13, phi_bb34_22, phi_bb34_23}, &block40, std::vector<compiler::Node*>{phi_bb34_9, phi_bb34_10, phi_bb34_11, phi_bb34_12, phi_bb34_13, phi_bb34_22, phi_bb34_23});
  }

  TNode<FixedArray> phi_bb35_9;
  TNode<IntPtrT> phi_bb35_10;
  TNode<IntPtrT> phi_bb35_11;
  TNode<BoolT> phi_bb35_12;
  TNode<PrimitiveHeapObject> phi_bb35_13;
  TNode<UintPtrT> phi_bb35_22;
  TNode<UintPtrT> phi_bb35_23;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_9, &phi_bb35_10, &phi_bb35_11, &phi_bb35_12, &phi_bb35_13, &phi_bb35_22, &phi_bb35_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb40_9;
  TNode<IntPtrT> phi_bb40_10;
  TNode<IntPtrT> phi_bb40_11;
  TNode<BoolT> phi_bb40_12;
  TNode<PrimitiveHeapObject> phi_bb40_13;
  TNode<UintPtrT> phi_bb40_22;
  TNode<UintPtrT> phi_bb40_23;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_9, &phi_bb40_10, &phi_bb40_11, &phi_bb40_12, &phi_bb40_13, &phi_bb40_22, &phi_bb40_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/base.tq", 201});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.is_undefined' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb39_9;
  TNode<IntPtrT> phi_bb39_10;
  TNode<IntPtrT> phi_bb39_11;
  TNode<BoolT> phi_bb39_12;
  TNode<PrimitiveHeapObject> phi_bb39_13;
  TNode<UintPtrT> phi_bb39_22;
  TNode<UintPtrT> phi_bb39_23;
  TNode<BoolT> tmp59;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_9, &phi_bb39_10, &phi_bb39_11, &phi_bb39_12, &phi_bb39_13, &phi_bb39_22, &phi_bb39_23);
    tmp59 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp56});
    ca_.Branch(tmp59, &block41, std::vector<compiler::Node*>{phi_bb39_9, phi_bb39_10, phi_bb39_11, phi_bb39_12, phi_bb39_13, phi_bb39_22, phi_bb39_23}, &block42, std::vector<compiler::Node*>{phi_bb39_9, phi_bb39_10, phi_bb39_11, phi_bb39_12, phi_bb39_13, phi_bb39_22, phi_bb39_23});
  }

  TNode<FixedArray> phi_bb42_9;
  TNode<IntPtrT> phi_bb42_10;
  TNode<IntPtrT> phi_bb42_11;
  TNode<BoolT> phi_bb42_12;
  TNode<PrimitiveHeapObject> phi_bb42_13;
  TNode<UintPtrT> phi_bb42_22;
  TNode<UintPtrT> phi_bb42_23;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_9, &phi_bb42_10, &phi_bb42_11, &phi_bb42_12, &phi_bb42_13, &phi_bb42_22, &phi_bb42_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/base.tq", 203});
      CodeStubAssembler(state_).FailAssert("Torque assert '!this.is_hole' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb41_9;
  TNode<IntPtrT> phi_bb41_10;
  TNode<IntPtrT> phi_bb41_11;
  TNode<BoolT> phi_bb41_12;
  TNode<PrimitiveHeapObject> phi_bb41_13;
  TNode<UintPtrT> phi_bb41_22;
  TNode<UintPtrT> phi_bb41_23;
  TNode<String> tmp60;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_9, &phi_bb41_10, &phi_bb41_11, &phi_bb41_12, &phi_bb41_13, &phi_bb41_22, &phi_bb41_23);
    tmp60 = CodeStubAssembler(state_).Float64ToString(TNode<Float64T>{tmp57});
    ca_.Goto(&block14, phi_bb41_9, phi_bb41_10, phi_bb41_11, phi_bb41_12, phi_bb41_13, tmp46, tmp60);
  }

  TNode<FixedArray> phi_bb14_9;
  TNode<IntPtrT> phi_bb14_10;
  TNode<IntPtrT> phi_bb14_11;
  TNode<BoolT> phi_bb14_12;
  TNode<PrimitiveHeapObject> phi_bb14_13;
  TNode<UintPtrT> phi_bb14_15;
  TNode<String> phi_bb14_16;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_9, &phi_bb14_10, &phi_bb14_11, &phi_bb14_12, &phi_bb14_13, &phi_bb14_15, &phi_bb14_16);
    ca_.Goto(&block11, phi_bb14_9, phi_bb14_10, phi_bb14_11, phi_bb14_12, phi_bb14_13, phi_bb14_15, phi_bb14_16);
  }

  TNode<FixedArray> phi_bb10_9;
  TNode<IntPtrT> phi_bb10_10;
  TNode<IntPtrT> phi_bb10_11;
  TNode<BoolT> phi_bb10_12;
  TNode<PrimitiveHeapObject> phi_bb10_13;
  TNode<UintPtrT> phi_bb10_15;
  TNode<BoolT> tmp61;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_9, &phi_bb10_10, &phi_bb10_11, &phi_bb10_12, &phi_bb10_13, &phi_bb10_15);
    tmp61 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).IsSmiElementsKind(p_kind)));
    ca_.Branch(tmp61, &block43, std::vector<compiler::Node*>{phi_bb10_9, phi_bb10_10, phi_bb10_11, phi_bb10_12, phi_bb10_13, phi_bb10_15}, &block44, std::vector<compiler::Node*>{phi_bb10_9, phi_bb10_10, phi_bb10_11, phi_bb10_12, phi_bb10_13, phi_bb10_15});
  }

  TNode<FixedArray> phi_bb44_9;
  TNode<IntPtrT> phi_bb44_10;
  TNode<IntPtrT> phi_bb44_11;
  TNode<BoolT> phi_bb44_12;
  TNode<PrimitiveHeapObject> phi_bb44_13;
  TNode<UintPtrT> phi_bb44_15;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_9, &phi_bb44_10, &phi_bb44_11, &phi_bb44_12, &phi_bb44_13, &phi_bb44_15);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 414});
      CodeStubAssembler(state_).FailAssert("Torque assert 'IsSmiElementsKind(kind)' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb43_9;
  TNode<IntPtrT> phi_bb43_10;
  TNode<IntPtrT> phi_bb43_11;
  TNode<BoolT> phi_bb43_12;
  TNode<PrimitiveHeapObject> phi_bb43_13;
  TNode<UintPtrT> phi_bb43_15;
  TNode<FixedArray> tmp62;
  TNode<Union<HeapObject, TaggedIndex>> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<UintPtrT> tmp66;
  TNode<UintPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<UintPtrT> tmp69;
  TNode<UintPtrT> tmp70;
  TNode<BoolT> tmp71;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_9, &phi_bb43_10, &phi_bb43_11, &phi_bb43_12, &phi_bb43_13, &phi_bb43_15);
    tmp62 = UnsafeCast_FixedArray_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp1});
    std::tie(tmp63, tmp64, tmp65) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp62}).Flatten();
    tmp66 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp67 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb43_15}, TNode<UintPtrT>{tmp66});
    tmp68 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{phi_bb43_15});
    tmp69 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp68});
    tmp70 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp65});
    tmp71 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp69}, TNode<UintPtrT>{tmp70});
    ca_.Branch(tmp71, &block49, std::vector<compiler::Node*>{phi_bb43_9, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, phi_bb43_15, phi_bb43_15}, &block50, std::vector<compiler::Node*>{phi_bb43_9, phi_bb43_10, phi_bb43_11, phi_bb43_12, phi_bb43_13, phi_bb43_15, phi_bb43_15});
  }

  TNode<FixedArray> phi_bb49_9;
  TNode<IntPtrT> phi_bb49_10;
  TNode<IntPtrT> phi_bb49_11;
  TNode<BoolT> phi_bb49_12;
  TNode<PrimitiveHeapObject> phi_bb49_13;
  TNode<UintPtrT> phi_bb49_22;
  TNode<UintPtrT> phi_bb49_23;
  TNode<IntPtrT> tmp72;
  TNode<IntPtrT> tmp73;
  TNode<Union<HeapObject, TaggedIndex>> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<Object> tmp76;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_9, &phi_bb49_10, &phi_bb49_11, &phi_bb49_12, &phi_bb49_13, &phi_bb49_22, &phi_bb49_23);
    tmp72 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp68});
    tmp73 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp64}, TNode<IntPtrT>{tmp72});
    std::tie(tmp74, tmp75) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp63}, TNode<IntPtrT>{tmp73}).Flatten();
    tmp76 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp74, tmp75});
    if (((CodeStubAssembler(state_).IsHoleyElementsKind(p_kind)))) {
      ca_.Goto(&block53, phi_bb49_9, phi_bb49_10, phi_bb49_11, phi_bb49_12, phi_bb49_13);
    } else {
      ca_.Goto(&block54, phi_bb49_9, phi_bb49_10, phi_bb49_11, phi_bb49_12, phi_bb49_13);
    }
  }

  TNode<FixedArray> phi_bb50_9;
  TNode<IntPtrT> phi_bb50_10;
  TNode<IntPtrT> phi_bb50_11;
  TNode<BoolT> phi_bb50_12;
  TNode<PrimitiveHeapObject> phi_bb50_13;
  TNode<UintPtrT> phi_bb50_22;
  TNode<UintPtrT> phi_bb50_23;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_9, &phi_bb50_10, &phi_bb50_11, &phi_bb50_12, &phi_bb50_13, &phi_bb50_22, &phi_bb50_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb53_9;
  TNode<IntPtrT> phi_bb53_10;
  TNode<IntPtrT> phi_bb53_11;
  TNode<BoolT> phi_bb53_12;
  TNode<PrimitiveHeapObject> phi_bb53_13;
  TNode<TheHole> tmp77;
  TNode<BoolT> tmp78;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_9, &phi_bb53_10, &phi_bb53_11, &phi_bb53_12, &phi_bb53_13);
    tmp77 = TheHole_0(state_);
    tmp78 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp76}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp77});
    ca_.Branch(tmp78, &block56, std::vector<compiler::Node*>{phi_bb53_9, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13}, &block57, std::vector<compiler::Node*>{phi_bb53_9, phi_bb53_10, phi_bb53_11, phi_bb53_12, phi_bb53_13});
  }

  TNode<FixedArray> phi_bb56_9;
  TNode<IntPtrT> phi_bb56_10;
  TNode<IntPtrT> phi_bb56_11;
  TNode<BoolT> phi_bb56_12;
  TNode<PrimitiveHeapObject> phi_bb56_13;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_9, &phi_bb56_10, &phi_bb56_11, &phi_bb56_12, &phi_bb56_13);
    ca_.Goto(&block6, phi_bb8_7, phi_bb56_9, phi_bb56_10, phi_bb56_11, phi_bb56_12, phi_bb56_13, tmp67);
  }

  TNode<FixedArray> phi_bb57_9;
  TNode<IntPtrT> phi_bb57_10;
  TNode<IntPtrT> phi_bb57_11;
  TNode<BoolT> phi_bb57_12;
  TNode<PrimitiveHeapObject> phi_bb57_13;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_9, &phi_bb57_10, &phi_bb57_11, &phi_bb57_12, &phi_bb57_13);
    ca_.Goto(&block55, phi_bb57_9, phi_bb57_10, phi_bb57_11, phi_bb57_12, phi_bb57_13);
  }

  TNode<FixedArray> phi_bb54_9;
  TNode<IntPtrT> phi_bb54_10;
  TNode<IntPtrT> phi_bb54_11;
  TNode<BoolT> phi_bb54_12;
  TNode<PrimitiveHeapObject> phi_bb54_13;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_9, &phi_bb54_10, &phi_bb54_11, &phi_bb54_12, &phi_bb54_13);
    ca_.Goto(&block55, phi_bb54_9, phi_bb54_10, phi_bb54_11, phi_bb54_12, phi_bb54_13);
  }

  TNode<FixedArray> phi_bb55_9;
  TNode<IntPtrT> phi_bb55_10;
  TNode<IntPtrT> phi_bb55_11;
  TNode<BoolT> phi_bb55_12;
  TNode<PrimitiveHeapObject> phi_bb55_13;
  TNode<Smi> tmp79;
  TNode<String> tmp80;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_9, &phi_bb55_10, &phi_bb55_11, &phi_bb55_12, &phi_bb55_13);
    tmp79 = UnsafeCast_Smi_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp76});
    tmp80 = CodeStubAssembler(state_).SmiToString(TNode<Smi>{tmp79});
    ca_.Goto(&block11, phi_bb55_9, phi_bb55_10, phi_bb55_11, phi_bb55_12, phi_bb55_13, tmp67, tmp80);
  }

  TNode<FixedArray> phi_bb11_9;
  TNode<IntPtrT> phi_bb11_10;
  TNode<IntPtrT> phi_bb11_11;
  TNode<BoolT> phi_bb11_12;
  TNode<PrimitiveHeapObject> phi_bb11_13;
  TNode<UintPtrT> phi_bb11_15;
  TNode<String> phi_bb11_16;
  TNode<IntPtrT> tmp81;
  TNode<BoolT> tmp82;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_9, &phi_bb11_10, &phi_bb11_11, &phi_bb11_12, &phi_bb11_13, &phi_bb11_15, &phi_bb11_16);
    tmp81 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp82 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb11_10}, TNode<IntPtrT>{tmp81});
    ca_.Branch(tmp82, &block61, std::vector<compiler::Node*>{phi_bb11_9, phi_bb11_10, phi_bb11_11, phi_bb11_12, phi_bb11_13}, &block62, std::vector<compiler::Node*>{phi_bb11_9, phi_bb11_10, phi_bb11_11, phi_bb11_12, phi_bb11_13});
  }

  TNode<FixedArray> phi_bb61_9;
  TNode<IntPtrT> phi_bb61_10;
  TNode<IntPtrT> phi_bb61_11;
  TNode<BoolT> phi_bb61_12;
  TNode<PrimitiveHeapObject> phi_bb61_13;
  TNode<BoolT> tmp83;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_9, &phi_bb61_10, &phi_bb61_11, &phi_bb61_12, &phi_bb61_13);
    tmp83 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block63, phi_bb61_9, phi_bb61_10, phi_bb61_11, phi_bb61_12, phi_bb61_13, tmp83);
  }

  TNode<FixedArray> phi_bb62_9;
  TNode<IntPtrT> phi_bb62_10;
  TNode<IntPtrT> phi_bb62_11;
  TNode<BoolT> phi_bb62_12;
  TNode<PrimitiveHeapObject> phi_bb62_13;
  TNode<BoolT> tmp84;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_9, &phi_bb62_10, &phi_bb62_11, &phi_bb62_12, &phi_bb62_13);
    tmp84 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp5}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{phi_bb62_9});
    ca_.Goto(&block63, phi_bb62_9, phi_bb62_10, phi_bb62_11, phi_bb62_12, phi_bb62_13, tmp84);
  }

  TNode<FixedArray> phi_bb63_9;
  TNode<IntPtrT> phi_bb63_10;
  TNode<IntPtrT> phi_bb63_11;
  TNode<BoolT> phi_bb63_12;
  TNode<PrimitiveHeapObject> phi_bb63_13;
  TNode<BoolT> phi_bb63_26;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_9, &phi_bb63_10, &phi_bb63_11, &phi_bb63_12, &phi_bb63_13, &phi_bb63_26);
    ca_.Branch(phi_bb63_26, &block59, std::vector<compiler::Node*>{phi_bb63_9, phi_bb63_10, phi_bb63_11, phi_bb63_12, phi_bb63_13}, &block60, std::vector<compiler::Node*>{phi_bb63_9, phi_bb63_10, phi_bb63_11, phi_bb63_12, phi_bb63_13});
  }

  TNode<FixedArray> phi_bb60_9;
  TNode<IntPtrT> phi_bb60_10;
  TNode<IntPtrT> phi_bb60_11;
  TNode<BoolT> phi_bb60_12;
  TNode<PrimitiveHeapObject> phi_bb60_13;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_9, &phi_bb60_10, &phi_bb60_11, &phi_bb60_12, &phi_bb60_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 184});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index != 1 || this.head == this.chunk' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb59_9;
  TNode<IntPtrT> phi_bb59_10;
  TNode<IntPtrT> phi_bb59_11;
  TNode<BoolT> phi_bb59_12;
  TNode<PrimitiveHeapObject> phi_bb59_13;
  TNode<IntPtrT> tmp85;
  TNode<BoolT> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<BoolT> tmp88;
  TNode<BoolT> tmp89;
  TNode<IntPtrT> tmp90;
  TNode<BoolT> tmp91;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_9, &phi_bb59_10, &phi_bb59_11, &phi_bb59_12, &phi_bb59_13);
    tmp85 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp86 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb59_10}, TNode<IntPtrT>{tmp85});
    tmp87 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp88 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb8_7}, TNode<IntPtrT>{tmp87});
    tmp89 = CodeStubAssembler(state_).Word32Or(TNode<BoolT>{tmp86}, TNode<BoolT>{tmp88});
    tmp90 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp91 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb8_7}, TNode<IntPtrT>{tmp90});
    ca_.Branch(tmp91, &block67, std::vector<compiler::Node*>{phi_bb59_9, phi_bb59_10, phi_bb59_11, phi_bb59_12, phi_bb59_13}, &block68, std::vector<compiler::Node*>{phi_bb59_9, phi_bb59_10, phi_bb59_11, phi_bb59_12, phi_bb59_13});
  }

  TNode<FixedArray> phi_bb67_9;
  TNode<IntPtrT> phi_bb67_10;
  TNode<IntPtrT> phi_bb67_11;
  TNode<BoolT> phi_bb67_12;
  TNode<PrimitiveHeapObject> phi_bb67_13;
  TNode<BoolT> tmp92;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_9, &phi_bb67_10, &phi_bb67_11, &phi_bb67_12, &phi_bb67_13);
    tmp92 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block69, phi_bb67_9, phi_bb67_10, phi_bb67_11, phi_bb67_12, phi_bb67_13, tmp92);
  }

  TNode<FixedArray> phi_bb68_9;
  TNode<IntPtrT> phi_bb68_10;
  TNode<IntPtrT> phi_bb68_11;
  TNode<BoolT> phi_bb68_12;
  TNode<PrimitiveHeapObject> phi_bb68_13;
  TNode<IntPtrT> tmp93;
  TNode<BoolT> tmp94;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_9, &phi_bb68_10, &phi_bb68_11, &phi_bb68_12, &phi_bb68_13);
    tmp93 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp94 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp93});
    ca_.Goto(&block69, phi_bb68_9, phi_bb68_10, phi_bb68_11, phi_bb68_12, phi_bb68_13, tmp94);
  }

  TNode<FixedArray> phi_bb69_9;
  TNode<IntPtrT> phi_bb69_10;
  TNode<IntPtrT> phi_bb69_11;
  TNode<BoolT> phi_bb69_12;
  TNode<PrimitiveHeapObject> phi_bb69_13;
  TNode<BoolT> phi_bb69_35;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_9, &phi_bb69_10, &phi_bb69_11, &phi_bb69_12, &phi_bb69_13, &phi_bb69_35);
    ca_.Branch(phi_bb69_35, &block65, std::vector<compiler::Node*>{phi_bb69_9, phi_bb69_10, phi_bb69_11, phi_bb69_12, phi_bb69_13}, &block66, std::vector<compiler::Node*>{phi_bb69_9, phi_bb69_10, phi_bb69_11, phi_bb69_12, phi_bb69_13});
  }

  TNode<FixedArray> phi_bb65_9;
  TNode<IntPtrT> phi_bb65_10;
  TNode<IntPtrT> phi_bb65_11;
  TNode<BoolT> phi_bb65_12;
  TNode<PrimitiveHeapObject> phi_bb65_13;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_9, &phi_bb65_10, &phi_bb65_11, &phi_bb65_12, &phi_bb65_13);
    ca_.Goto(&block64, phi_bb65_9, phi_bb65_10, phi_bb65_11, phi_bb65_12, phi_bb65_13);
  }

  TNode<FixedArray> phi_bb66_9;
  TNode<IntPtrT> phi_bb66_10;
  TNode<IntPtrT> phi_bb66_11;
  TNode<BoolT> phi_bb66_12;
  TNode<PrimitiveHeapObject> phi_bb66_13;
  TNode<IntPtrT> tmp95;
  TNode<IntPtrT> tmp96;
  TNode<BoolT> tmp97;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_9, &phi_bb66_10, &phi_bb66_11, &phi_bb66_12, &phi_bb66_13);
    tmp95 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{phi_bb8_7});
    tmp96 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp95}, TNode<IntPtrT>{tmp3});
    tmp97 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp96}, TNode<IntPtrT>{phi_bb8_7});
    ca_.Branch(tmp97, &block70, std::vector<compiler::Node*>{phi_bb66_9, phi_bb66_10, phi_bb66_11, phi_bb66_12, phi_bb66_13}, &block71, std::vector<compiler::Node*>{phi_bb66_9, phi_bb66_10, phi_bb66_11, phi_bb66_12, phi_bb66_13});
  }

  TNode<FixedArray> phi_bb70_9;
  TNode<IntPtrT> phi_bb70_10;
  TNode<IntPtrT> phi_bb70_11;
  TNode<BoolT> phi_bb70_12;
  TNode<PrimitiveHeapObject> phi_bb70_13;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_9, &phi_bb70_10, &phi_bb70_11, &phi_bb70_12, &phi_bb70_13);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb71_9;
  TNode<IntPtrT> phi_bb71_10;
  TNode<IntPtrT> phi_bb71_11;
  TNode<BoolT> phi_bb71_12;
  TNode<PrimitiveHeapObject> phi_bb71_13;
  TNode<IntPtrT> tmp98;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_9, &phi_bb71_10, &phi_bb71_11, &phi_bb71_12, &phi_bb71_13);
    tmp98 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb71_11}, TNode<IntPtrT>{tmp95});
    ca_.Branch(tmp89, &block72, std::vector<compiler::Node*>{phi_bb71_9, phi_bb71_10, phi_bb71_12, phi_bb71_13}, &block73, std::vector<compiler::Node*>{phi_bb71_9, phi_bb71_10, phi_bb71_12, phi_bb71_13});
  }

  TNode<FixedArray> phi_bb72_9;
  TNode<IntPtrT> phi_bb72_10;
  TNode<BoolT> phi_bb72_12;
  TNode<PrimitiveHeapObject> phi_bb72_13;
  TNode<Smi> tmp99;
  TNode<IntPtrT> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<BoolT> tmp102;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_9, &phi_bb72_10, &phi_bb72_12, &phi_bb72_13);
    tmp99 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb8_7});
    tmp100 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb72_9});
    tmp101 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp102 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb72_10}, TNode<IntPtrT>{tmp101});
    ca_.Branch(tmp102, &block75, std::vector<compiler::Node*>{phi_bb72_9, phi_bb72_10, phi_bb72_12, phi_bb72_13}, &block76, std::vector<compiler::Node*>{phi_bb72_9, phi_bb72_10, phi_bb72_12, phi_bb72_13});
  }

  TNode<FixedArray> phi_bb76_9;
  TNode<IntPtrT> phi_bb76_10;
  TNode<BoolT> phi_bb76_12;
  TNode<PrimitiveHeapObject> phi_bb76_13;
  if (block76.is_used()) {
    ca_.Bind(&block76, &phi_bb76_9, &phi_bb76_10, &phi_bb76_12, &phi_bb76_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb75_9;
  TNode<IntPtrT> phi_bb75_10;
  TNode<BoolT> phi_bb75_12;
  TNode<PrimitiveHeapObject> phi_bb75_13;
  TNode<BoolT> tmp103;
  if (block75.is_used()) {
    ca_.Bind(&block75, &phi_bb75_9, &phi_bb75_10, &phi_bb75_12, &phi_bb75_13);
    tmp103 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb75_10}, TNode<IntPtrT>{tmp100});
    ca_.Branch(tmp103, &block77, std::vector<compiler::Node*>{phi_bb75_9, phi_bb75_10, phi_bb75_12, phi_bb75_13}, &block78, std::vector<compiler::Node*>{phi_bb75_9, phi_bb75_10, phi_bb75_12, phi_bb75_13});
  }

  TNode<FixedArray> phi_bb78_9;
  TNode<IntPtrT> phi_bb78_10;
  TNode<BoolT> phi_bb78_12;
  TNode<PrimitiveHeapObject> phi_bb78_13;
  if (block78.is_used()) {
    ca_.Bind(&block78, &phi_bb78_9, &phi_bb78_10, &phi_bb78_12, &phi_bb78_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb77_9;
  TNode<IntPtrT> phi_bb77_10;
  TNode<BoolT> phi_bb77_12;
  TNode<PrimitiveHeapObject> phi_bb77_13;
  TNode<BoolT> tmp104;
  if (block77.is_used()) {
    ca_.Bind(&block77, &phi_bb77_9, &phi_bb77_10, &phi_bb77_12, &phi_bb77_13);
    tmp104 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb77_10}, TNode<IntPtrT>{tmp100});
    ca_.Branch(tmp104, &block79, std::vector<compiler::Node*>{phi_bb77_9, phi_bb77_10, phi_bb77_12, phi_bb77_13}, &block80, std::vector<compiler::Node*>{phi_bb77_9, phi_bb77_10, phi_bb77_12, phi_bb77_13});
  }

  TNode<FixedArray> phi_bb79_9;
  TNode<IntPtrT> phi_bb79_10;
  TNode<BoolT> phi_bb79_12;
  TNode<PrimitiveHeapObject> phi_bb79_13;
  TNode<Union<HeapObject, TaggedIndex>> tmp105;
  TNode<IntPtrT> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<IntPtrT> tmp108;
  TNode<IntPtrT> tmp109;
  TNode<UintPtrT> tmp110;
  TNode<UintPtrT> tmp111;
  TNode<BoolT> tmp112;
  if (block79.is_used()) {
    ca_.Bind(&block79, &phi_bb79_9, &phi_bb79_10, &phi_bb79_12, &phi_bb79_13);
    std::tie(tmp105, tmp106, tmp107) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb79_9}).Flatten();
    tmp108 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp109 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb79_10}, TNode<IntPtrT>{tmp108});
    tmp110 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb79_10});
    tmp111 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp107});
    tmp112 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp110}, TNode<UintPtrT>{tmp111});
    ca_.Branch(tmp112, &block86, std::vector<compiler::Node*>{phi_bb79_9, phi_bb79_12, phi_bb79_13, phi_bb79_9, phi_bb79_10, phi_bb79_10, phi_bb79_10, phi_bb79_10}, &block87, std::vector<compiler::Node*>{phi_bb79_9, phi_bb79_12, phi_bb79_13, phi_bb79_9, phi_bb79_10, phi_bb79_10, phi_bb79_10, phi_bb79_10});
  }

  TNode<FixedArray> phi_bb86_9;
  TNode<BoolT> phi_bb86_12;
  TNode<PrimitiveHeapObject> phi_bb86_13;
  TNode<FixedArray> phi_bb86_39;
  TNode<IntPtrT> phi_bb86_43;
  TNode<IntPtrT> phi_bb86_44;
  TNode<IntPtrT> phi_bb86_48;
  TNode<IntPtrT> phi_bb86_49;
  TNode<IntPtrT> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<Union<HeapObject, TaggedIndex>> tmp115;
  TNode<IntPtrT> tmp116;
  if (block86.is_used()) {
    ca_.Bind(&block86, &phi_bb86_9, &phi_bb86_12, &phi_bb86_13, &phi_bb86_39, &phi_bb86_43, &phi_bb86_44, &phi_bb86_48, &phi_bb86_49);
    tmp113 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb86_49});
    tmp114 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp106}, TNode<IntPtrT>{tmp113});
    std::tie(tmp115, tmp116) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp105}, TNode<IntPtrT>{tmp114}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp115, tmp116}, tmp99);
    ca_.Goto(&block81, phi_bb86_9, tmp109, phi_bb86_12, phi_bb86_13);
  }

  TNode<FixedArray> phi_bb87_9;
  TNode<BoolT> phi_bb87_12;
  TNode<PrimitiveHeapObject> phi_bb87_13;
  TNode<FixedArray> phi_bb87_39;
  TNode<IntPtrT> phi_bb87_43;
  TNode<IntPtrT> phi_bb87_44;
  TNode<IntPtrT> phi_bb87_48;
  TNode<IntPtrT> phi_bb87_49;
  if (block87.is_used()) {
    ca_.Bind(&block87, &phi_bb87_9, &phi_bb87_12, &phi_bb87_13, &phi_bb87_39, &phi_bb87_43, &phi_bb87_44, &phi_bb87_48, &phi_bb87_49);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb80_9;
  TNode<IntPtrT> phi_bb80_10;
  TNode<BoolT> phi_bb80_12;
  TNode<PrimitiveHeapObject> phi_bb80_13;
  TNode<IntPtrT> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<BoolT> tmp119;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_9, &phi_bb80_10, &phi_bb80_12, &phi_bb80_13);
    tmp117 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp100});
    tmp118 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp119 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp117}, TNode<IntPtrT>{tmp118});
    ca_.Branch(tmp119, &block90, std::vector<compiler::Node*>{phi_bb80_9, phi_bb80_10, phi_bb80_12, phi_bb80_13}, &block91, std::vector<compiler::Node*>{phi_bb80_9, phi_bb80_10, phi_bb80_12, phi_bb80_13});
  }

  TNode<FixedArray> phi_bb90_9;
  TNode<IntPtrT> phi_bb90_10;
  TNode<BoolT> phi_bb90_12;
  TNode<PrimitiveHeapObject> phi_bb90_13;
  TNode<IntPtrT> tmp120;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_9, &phi_bb90_10, &phi_bb90_12, &phi_bb90_13);
    tmp120 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block92, phi_bb90_9, phi_bb90_10, phi_bb90_12, phi_bb90_13, tmp120);
  }

  TNode<FixedArray> phi_bb91_9;
  TNode<IntPtrT> phi_bb91_10;
  TNode<BoolT> phi_bb91_12;
  TNode<PrimitiveHeapObject> phi_bb91_13;
  if (block91.is_used()) {
    ca_.Bind(&block91, &phi_bb91_9, &phi_bb91_10, &phi_bb91_12, &phi_bb91_13);
    ca_.Goto(&block92, phi_bb91_9, phi_bb91_10, phi_bb91_12, phi_bb91_13, tmp117);
  }

  TNode<FixedArray> phi_bb92_9;
  TNode<IntPtrT> phi_bb92_10;
  TNode<BoolT> phi_bb92_12;
  TNode<PrimitiveHeapObject> phi_bb92_13;
  TNode<IntPtrT> phi_bb92_40;
  TNode<IntPtrT> tmp121;
  TNode<BoolT> tmp122;
  if (block92.is_used()) {
    ca_.Bind(&block92, &phi_bb92_9, &phi_bb92_10, &phi_bb92_12, &phi_bb92_13, &phi_bb92_40);
    tmp121 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp122 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb92_40}, TNode<IntPtrT>{tmp121});
    ca_.Branch(tmp122, &block94, std::vector<compiler::Node*>{phi_bb92_9, phi_bb92_10, phi_bb92_12, phi_bb92_13}, &block95, std::vector<compiler::Node*>{phi_bb92_9, phi_bb92_10, phi_bb92_12, phi_bb92_13});
  }

  TNode<FixedArray> phi_bb95_9;
  TNode<IntPtrT> phi_bb95_10;
  TNode<BoolT> phi_bb95_12;
  TNode<PrimitiveHeapObject> phi_bb95_13;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_9, &phi_bb95_10, &phi_bb95_12, &phi_bb95_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb94_9;
  TNode<IntPtrT> phi_bb94_10;
  TNode<BoolT> phi_bb94_12;
  TNode<PrimitiveHeapObject> phi_bb94_13;
  TNode<FixedArray> tmp123;
  TNode<Union<HeapObject, TaggedIndex>> tmp124;
  TNode<IntPtrT> tmp125;
  TNode<IntPtrT> tmp126;
  TNode<UintPtrT> tmp127;
  TNode<IntPtrT> tmp128;
  TNode<UintPtrT> tmp129;
  TNode<UintPtrT> tmp130;
  TNode<BoolT> tmp131;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_9, &phi_bb94_10, &phi_bb94_12, &phi_bb94_13);
    tmp123 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb92_40});
    std::tie(tmp124, tmp125, tmp126) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb94_9}).Flatten();
    tmp127 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp128 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp127});
    tmp129 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp128});
    tmp130 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp126});
    tmp131 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp129}, TNode<UintPtrT>{tmp130});
    ca_.Branch(tmp131, &block101, std::vector<compiler::Node*>{phi_bb94_9, phi_bb94_10, phi_bb94_12, phi_bb94_13, phi_bb94_9}, &block102, std::vector<compiler::Node*>{phi_bb94_9, phi_bb94_10, phi_bb94_12, phi_bb94_13, phi_bb94_9});
  }

  TNode<FixedArray> phi_bb101_9;
  TNode<IntPtrT> phi_bb101_10;
  TNode<BoolT> phi_bb101_12;
  TNode<PrimitiveHeapObject> phi_bb101_13;
  TNode<FixedArray> phi_bb101_42;
  TNode<IntPtrT> tmp132;
  TNode<IntPtrT> tmp133;
  TNode<Union<HeapObject, TaggedIndex>> tmp134;
  TNode<IntPtrT> tmp135;
  TNode<Union<HeapObject, TaggedIndex>> tmp136;
  TNode<IntPtrT> tmp137;
  TNode<IntPtrT> tmp138;
  TNode<UintPtrT> tmp139;
  TNode<IntPtrT> tmp140;
  TNode<UintPtrT> tmp141;
  TNode<UintPtrT> tmp142;
  TNode<BoolT> tmp143;
  if (block101.is_used()) {
    ca_.Bind(&block101, &phi_bb101_9, &phi_bb101_10, &phi_bb101_12, &phi_bb101_13, &phi_bb101_42);
    tmp132 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp128});
    tmp133 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp125}, TNode<IntPtrT>{tmp132});
    std::tie(tmp134, tmp135) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp124}, TNode<IntPtrT>{tmp133}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp134, tmp135}, tmp123);
    std::tie(tmp136, tmp137, tmp138) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp123}).Flatten();
    tmp139 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp140 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp139});
    tmp141 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp140});
    tmp142 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp138});
    tmp143 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp141}, TNode<UintPtrT>{tmp142});
    ca_.Branch(tmp143, &block110, std::vector<compiler::Node*>{phi_bb101_9, phi_bb101_10, phi_bb101_12, phi_bb101_13}, &block111, std::vector<compiler::Node*>{phi_bb101_9, phi_bb101_10, phi_bb101_12, phi_bb101_13});
  }

  TNode<FixedArray> phi_bb102_9;
  TNode<IntPtrT> phi_bb102_10;
  TNode<BoolT> phi_bb102_12;
  TNode<PrimitiveHeapObject> phi_bb102_13;
  TNode<FixedArray> phi_bb102_42;
  if (block102.is_used()) {
    ca_.Bind(&block102, &phi_bb102_9, &phi_bb102_10, &phi_bb102_12, &phi_bb102_13, &phi_bb102_42);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb110_9;
  TNode<IntPtrT> phi_bb110_10;
  TNode<BoolT> phi_bb110_12;
  TNode<PrimitiveHeapObject> phi_bb110_13;
  TNode<IntPtrT> tmp144;
  TNode<IntPtrT> tmp145;
  TNode<Union<HeapObject, TaggedIndex>> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<Undefined> tmp148;
  TNode<Union<HeapObject, TaggedIndex>> tmp149;
  TNode<IntPtrT> tmp150;
  TNode<IntPtrT> tmp151;
  TNode<UintPtrT> tmp152;
  TNode<IntPtrT> tmp153;
  TNode<UintPtrT> tmp154;
  TNode<UintPtrT> tmp155;
  TNode<BoolT> tmp156;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_9, &phi_bb110_10, &phi_bb110_12, &phi_bb110_13);
    tmp144 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp140});
    tmp145 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp137}, TNode<IntPtrT>{tmp144});
    std::tie(tmp146, tmp147) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp136}, TNode<IntPtrT>{tmp145}).Flatten();
    tmp148 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp146, tmp147}, tmp148);
    std::tie(tmp149, tmp150, tmp151) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp123}).Flatten();
    tmp152 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp153 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp152});
    tmp154 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp153});
    tmp155 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp151});
    tmp156 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp154}, TNode<UintPtrT>{tmp155});
    ca_.Branch(tmp156, &block119, std::vector<compiler::Node*>{phi_bb110_9, phi_bb110_10, phi_bb110_12, phi_bb110_13}, &block120, std::vector<compiler::Node*>{phi_bb110_9, phi_bb110_10, phi_bb110_12, phi_bb110_13});
  }

  TNode<FixedArray> phi_bb111_9;
  TNode<IntPtrT> phi_bb111_10;
  TNode<BoolT> phi_bb111_12;
  TNode<PrimitiveHeapObject> phi_bb111_13;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_9, &phi_bb111_10, &phi_bb111_12, &phi_bb111_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb119_9;
  TNode<IntPtrT> phi_bb119_10;
  TNode<BoolT> phi_bb119_12;
  TNode<PrimitiveHeapObject> phi_bb119_13;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<Union<HeapObject, TaggedIndex>> tmp159;
  TNode<IntPtrT> tmp160;
  TNode<IntPtrT> tmp161;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_9, &phi_bb119_10, &phi_bb119_12, &phi_bb119_13);
    tmp157 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp153});
    tmp158 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp150}, TNode<IntPtrT>{tmp157});
    std::tie(tmp159, tmp160) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp149}, TNode<IntPtrT>{tmp158}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp159, tmp160}, tmp99);
    tmp161 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block81, tmp123, tmp161, phi_bb119_12, phi_bb119_13);
  }

  TNode<FixedArray> phi_bb120_9;
  TNode<IntPtrT> phi_bb120_10;
  TNode<BoolT> phi_bb120_12;
  TNode<PrimitiveHeapObject> phi_bb120_13;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_9, &phi_bb120_10, &phi_bb120_12, &phi_bb120_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb81_9;
  TNode<IntPtrT> phi_bb81_10;
  TNode<BoolT> phi_bb81_12;
  TNode<PrimitiveHeapObject> phi_bb81_13;
  TNode<Null> tmp162;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_9, &phi_bb81_10, &phi_bb81_12, &phi_bb81_13);
    tmp162 = Null_0(state_);
    ca_.Goto(&block73, phi_bb81_9, phi_bb81_10, phi_bb81_12, tmp162);
  }

  TNode<FixedArray> phi_bb73_9;
  TNode<IntPtrT> phi_bb73_10;
  TNode<BoolT> phi_bb73_12;
  TNode<PrimitiveHeapObject> phi_bb73_13;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_9, &phi_bb73_10, &phi_bb73_12, &phi_bb73_13);
    ca_.Goto(&block64, phi_bb73_9, phi_bb73_10, tmp98, phi_bb73_12, phi_bb73_13);
  }

  TNode<FixedArray> phi_bb64_9;
  TNode<IntPtrT> phi_bb64_10;
  TNode<IntPtrT> phi_bb64_11;
  TNode<BoolT> phi_bb64_12;
  TNode<PrimitiveHeapObject> phi_bb64_13;
  TNode<IntPtrT> tmp163;
  TNode<IntPtrT> tmp164;
  TNode<BoolT> tmp165;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_9, &phi_bb64_10, &phi_bb64_11, &phi_bb64_12, &phi_bb64_13);
    tmp163 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{phi_bb11_16});
    tmp164 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb64_11}, TNode<IntPtrT>{tmp163});
    tmp165 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{phi_bb11_16}, TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{phi_bb64_13});
    ca_.Branch(tmp165, &block123, std::vector<compiler::Node*>{phi_bb64_9, phi_bb64_10, phi_bb64_12, phi_bb64_13}, &block124, std::vector<compiler::Node*>{phi_bb64_9, phi_bb64_10, phi_bb64_12, phi_bb64_13});
  }

  TNode<FixedArray> phi_bb123_9;
  TNode<IntPtrT> phi_bb123_10;
  TNode<BoolT> phi_bb123_12;
  TNode<PrimitiveHeapObject> phi_bb123_13;
  TNode<IntPtrT> tmp166;
  TNode<BoolT> tmp167;
  if (block123.is_used()) {
    ca_.Bind(&block123, &phi_bb123_9, &phi_bb123_10, &phi_bb123_12, &phi_bb123_13);
    tmp166 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp167 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb123_10}, TNode<IntPtrT>{tmp166});
    ca_.Branch(tmp167, &block127, std::vector<compiler::Node*>{phi_bb123_9, phi_bb123_10, phi_bb123_12, phi_bb123_13}, &block128, std::vector<compiler::Node*>{phi_bb123_9, phi_bb123_10, phi_bb123_12, phi_bb123_13});
  }

  TNode<FixedArray> phi_bb128_9;
  TNode<IntPtrT> phi_bb128_10;
  TNode<BoolT> phi_bb128_12;
  TNode<PrimitiveHeapObject> phi_bb128_13;
  if (block128.is_used()) {
    ca_.Bind(&block128, &phi_bb128_9, &phi_bb128_10, &phi_bb128_12, &phi_bb128_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 223});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index > 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb127_9;
  TNode<IntPtrT> phi_bb127_10;
  TNode<BoolT> phi_bb127_12;
  TNode<PrimitiveHeapObject> phi_bb127_13;
  TNode<Union<HeapObject, TaggedIndex>> tmp168;
  TNode<IntPtrT> tmp169;
  TNode<IntPtrT> tmp170;
  TNode<IntPtrT> tmp171;
  TNode<IntPtrT> tmp172;
  TNode<UintPtrT> tmp173;
  TNode<UintPtrT> tmp174;
  TNode<BoolT> tmp175;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_9, &phi_bb127_10, &phi_bb127_12, &phi_bb127_13);
    std::tie(tmp168, tmp169, tmp170) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb127_9}).Flatten();
    tmp171 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp172 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb127_10}, TNode<IntPtrT>{tmp171});
    tmp173 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp172});
    tmp174 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp170});
    tmp175 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp173}, TNode<UintPtrT>{tmp174});
    ca_.Branch(tmp175, &block133, std::vector<compiler::Node*>{phi_bb127_9, phi_bb127_10, phi_bb127_12, phi_bb127_13, phi_bb127_9}, &block134, std::vector<compiler::Node*>{phi_bb127_9, phi_bb127_10, phi_bb127_12, phi_bb127_13, phi_bb127_9});
  }

  TNode<FixedArray> phi_bb133_9;
  TNode<IntPtrT> phi_bb133_10;
  TNode<BoolT> phi_bb133_12;
  TNode<PrimitiveHeapObject> phi_bb133_13;
  TNode<FixedArray> phi_bb133_26;
  TNode<IntPtrT> tmp176;
  TNode<IntPtrT> tmp177;
  TNode<Union<HeapObject, TaggedIndex>> tmp178;
  TNode<IntPtrT> tmp179;
  TNode<Object> tmp180;
  TNode<HeapObject> tmp181;
  if (block133.is_used()) {
    ca_.Bind(&block133, &phi_bb133_9, &phi_bb133_10, &phi_bb133_12, &phi_bb133_13, &phi_bb133_26);
    tmp176 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp172});
    tmp177 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp169}, TNode<IntPtrT>{tmp176});
    std::tie(tmp178, tmp179) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp168}, TNode<IntPtrT>{tmp177}).Flatten();
    tmp180 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp178, tmp179});
    compiler::CodeAssemblerLabel label182(&ca_);
    tmp181 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{tmp180}, &label182);
    ca_.Goto(&block140, phi_bb133_9, phi_bb133_10, phi_bb133_12, phi_bb133_13);
    if (label182.is_used()) {
      ca_.Bind(&label182);
      ca_.Goto(&block141, phi_bb133_9, phi_bb133_10, phi_bb133_12, phi_bb133_13);
    }
  }

  TNode<FixedArray> phi_bb134_9;
  TNode<IntPtrT> phi_bb134_10;
  TNode<BoolT> phi_bb134_12;
  TNode<PrimitiveHeapObject> phi_bb134_13;
  TNode<FixedArray> phi_bb134_26;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_9, &phi_bb134_10, &phi_bb134_12, &phi_bb134_13, &phi_bb134_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb141_9;
  TNode<IntPtrT> phi_bb141_10;
  TNode<BoolT> phi_bb141_12;
  TNode<PrimitiveHeapObject> phi_bb141_13;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_9, &phi_bb141_10, &phi_bb141_12, &phi_bb141_13);
    ca_.Goto(&block138, phi_bb141_9, phi_bb141_10, phi_bb141_12, phi_bb141_13);
  }

  TNode<FixedArray> phi_bb140_9;
  TNode<IntPtrT> phi_bb140_10;
  TNode<BoolT> phi_bb140_12;
  TNode<PrimitiveHeapObject> phi_bb140_13;
  TNode<String> tmp183;
  if (block140.is_used()) {
    ca_.Bind(&block140, &phi_bb140_9, &phi_bb140_10, &phi_bb140_12, &phi_bb140_13);
    compiler::CodeAssemblerLabel label184(&ca_);
    tmp183 = Cast_String_0(state_, TNode<HeapObject>{tmp181}, &label184);
    ca_.Goto(&block142, phi_bb140_9, phi_bb140_10, phi_bb140_12, phi_bb140_13);
    if (label184.is_used()) {
      ca_.Bind(&label184);
      ca_.Goto(&block143, phi_bb140_9, phi_bb140_10, phi_bb140_12, phi_bb140_13);
    }
  }

  TNode<FixedArray> phi_bb143_9;
  TNode<IntPtrT> phi_bb143_10;
  TNode<BoolT> phi_bb143_12;
  TNode<PrimitiveHeapObject> phi_bb143_13;
  if (block143.is_used()) {
    ca_.Bind(&block143, &phi_bb143_9, &phi_bb143_10, &phi_bb143_12, &phi_bb143_13);
    ca_.Goto(&block138, phi_bb143_9, phi_bb143_10, phi_bb143_12, phi_bb143_13);
  }

  TNode<FixedArray> phi_bb142_9;
  TNode<IntPtrT> phi_bb142_10;
  TNode<BoolT> phi_bb142_12;
  TNode<PrimitiveHeapObject> phi_bb142_13;
  TNode<Smi> tmp185;
  TNode<IntPtrT> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<BoolT> tmp188;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_9, &phi_bb142_10, &phi_bb142_12, &phi_bb142_13);
    tmp185 = SmiConstant_0(state_, IntegerLiteral(true, 0x1ull));
    tmp186 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb142_9});
    tmp187 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp188 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb142_10}, TNode<IntPtrT>{tmp187});
    ca_.Branch(tmp188, &block145, std::vector<compiler::Node*>{phi_bb142_9, phi_bb142_10, phi_bb142_12, phi_bb142_13}, &block146, std::vector<compiler::Node*>{phi_bb142_9, phi_bb142_10, phi_bb142_12, phi_bb142_13});
  }

  TNode<FixedArray> phi_bb146_9;
  TNode<IntPtrT> phi_bb146_10;
  TNode<BoolT> phi_bb146_12;
  TNode<PrimitiveHeapObject> phi_bb146_13;
  if (block146.is_used()) {
    ca_.Bind(&block146, &phi_bb146_9, &phi_bb146_10, &phi_bb146_12, &phi_bb146_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb145_9;
  TNode<IntPtrT> phi_bb145_10;
  TNode<BoolT> phi_bb145_12;
  TNode<PrimitiveHeapObject> phi_bb145_13;
  TNode<BoolT> tmp189;
  if (block145.is_used()) {
    ca_.Bind(&block145, &phi_bb145_9, &phi_bb145_10, &phi_bb145_12, &phi_bb145_13);
    tmp189 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb145_10}, TNode<IntPtrT>{tmp186});
    ca_.Branch(tmp189, &block147, std::vector<compiler::Node*>{phi_bb145_9, phi_bb145_10, phi_bb145_12, phi_bb145_13}, &block148, std::vector<compiler::Node*>{phi_bb145_9, phi_bb145_10, phi_bb145_12, phi_bb145_13});
  }

  TNode<FixedArray> phi_bb148_9;
  TNode<IntPtrT> phi_bb148_10;
  TNode<BoolT> phi_bb148_12;
  TNode<PrimitiveHeapObject> phi_bb148_13;
  if (block148.is_used()) {
    ca_.Bind(&block148, &phi_bb148_9, &phi_bb148_10, &phi_bb148_12, &phi_bb148_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb147_9;
  TNode<IntPtrT> phi_bb147_10;
  TNode<BoolT> phi_bb147_12;
  TNode<PrimitiveHeapObject> phi_bb147_13;
  TNode<BoolT> tmp190;
  if (block147.is_used()) {
    ca_.Bind(&block147, &phi_bb147_9, &phi_bb147_10, &phi_bb147_12, &phi_bb147_13);
    tmp190 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb147_10}, TNode<IntPtrT>{tmp186});
    ca_.Branch(tmp190, &block149, std::vector<compiler::Node*>{phi_bb147_9, phi_bb147_10, phi_bb147_12, phi_bb147_13}, &block150, std::vector<compiler::Node*>{phi_bb147_9, phi_bb147_10, phi_bb147_12, phi_bb147_13});
  }

  TNode<FixedArray> phi_bb149_9;
  TNode<IntPtrT> phi_bb149_10;
  TNode<BoolT> phi_bb149_12;
  TNode<PrimitiveHeapObject> phi_bb149_13;
  TNode<Union<HeapObject, TaggedIndex>> tmp191;
  TNode<IntPtrT> tmp192;
  TNode<IntPtrT> tmp193;
  TNode<IntPtrT> tmp194;
  TNode<IntPtrT> tmp195;
  TNode<UintPtrT> tmp196;
  TNode<UintPtrT> tmp197;
  TNode<BoolT> tmp198;
  if (block149.is_used()) {
    ca_.Bind(&block149, &phi_bb149_9, &phi_bb149_10, &phi_bb149_12, &phi_bb149_13);
    std::tie(tmp191, tmp192, tmp193) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb149_9}).Flatten();
    tmp194 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp195 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb149_10}, TNode<IntPtrT>{tmp194});
    tmp196 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb149_10});
    tmp197 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp193});
    tmp198 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp196}, TNode<UintPtrT>{tmp197});
    ca_.Branch(tmp198, &block156, std::vector<compiler::Node*>{phi_bb149_9, phi_bb149_12, phi_bb149_13, phi_bb149_9, phi_bb149_10, phi_bb149_10, phi_bb149_10, phi_bb149_10}, &block157, std::vector<compiler::Node*>{phi_bb149_9, phi_bb149_12, phi_bb149_13, phi_bb149_9, phi_bb149_10, phi_bb149_10, phi_bb149_10, phi_bb149_10});
  }

  TNode<FixedArray> phi_bb156_9;
  TNode<BoolT> phi_bb156_12;
  TNode<PrimitiveHeapObject> phi_bb156_13;
  TNode<FixedArray> phi_bb156_31;
  TNode<IntPtrT> phi_bb156_35;
  TNode<IntPtrT> phi_bb156_36;
  TNode<IntPtrT> phi_bb156_40;
  TNode<IntPtrT> phi_bb156_41;
  TNode<IntPtrT> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<Union<HeapObject, TaggedIndex>> tmp201;
  TNode<IntPtrT> tmp202;
  if (block156.is_used()) {
    ca_.Bind(&block156, &phi_bb156_9, &phi_bb156_12, &phi_bb156_13, &phi_bb156_31, &phi_bb156_35, &phi_bb156_36, &phi_bb156_40, &phi_bb156_41);
    tmp199 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb156_41});
    tmp200 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp192}, TNode<IntPtrT>{tmp199});
    std::tie(tmp201, tmp202) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp191}, TNode<IntPtrT>{tmp200}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp201, tmp202}, tmp185);
    ca_.Goto(&block151, phi_bb156_9, tmp195, phi_bb156_12, phi_bb156_13);
  }

  TNode<FixedArray> phi_bb157_9;
  TNode<BoolT> phi_bb157_12;
  TNode<PrimitiveHeapObject> phi_bb157_13;
  TNode<FixedArray> phi_bb157_31;
  TNode<IntPtrT> phi_bb157_35;
  TNode<IntPtrT> phi_bb157_36;
  TNode<IntPtrT> phi_bb157_40;
  TNode<IntPtrT> phi_bb157_41;
  if (block157.is_used()) {
    ca_.Bind(&block157, &phi_bb157_9, &phi_bb157_12, &phi_bb157_13, &phi_bb157_31, &phi_bb157_35, &phi_bb157_36, &phi_bb157_40, &phi_bb157_41);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb150_9;
  TNode<IntPtrT> phi_bb150_10;
  TNode<BoolT> phi_bb150_12;
  TNode<PrimitiveHeapObject> phi_bb150_13;
  TNode<IntPtrT> tmp203;
  TNode<IntPtrT> tmp204;
  TNode<BoolT> tmp205;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_9, &phi_bb150_10, &phi_bb150_12, &phi_bb150_13);
    tmp203 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp186});
    tmp204 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp205 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp203}, TNode<IntPtrT>{tmp204});
    ca_.Branch(tmp205, &block160, std::vector<compiler::Node*>{phi_bb150_9, phi_bb150_10, phi_bb150_12, phi_bb150_13}, &block161, std::vector<compiler::Node*>{phi_bb150_9, phi_bb150_10, phi_bb150_12, phi_bb150_13});
  }

  TNode<FixedArray> phi_bb160_9;
  TNode<IntPtrT> phi_bb160_10;
  TNode<BoolT> phi_bb160_12;
  TNode<PrimitiveHeapObject> phi_bb160_13;
  TNode<IntPtrT> tmp206;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_9, &phi_bb160_10, &phi_bb160_12, &phi_bb160_13);
    tmp206 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block162, phi_bb160_9, phi_bb160_10, phi_bb160_12, phi_bb160_13, tmp206);
  }

  TNode<FixedArray> phi_bb161_9;
  TNode<IntPtrT> phi_bb161_10;
  TNode<BoolT> phi_bb161_12;
  TNode<PrimitiveHeapObject> phi_bb161_13;
  if (block161.is_used()) {
    ca_.Bind(&block161, &phi_bb161_9, &phi_bb161_10, &phi_bb161_12, &phi_bb161_13);
    ca_.Goto(&block162, phi_bb161_9, phi_bb161_10, phi_bb161_12, phi_bb161_13, tmp203);
  }

  TNode<FixedArray> phi_bb162_9;
  TNode<IntPtrT> phi_bb162_10;
  TNode<BoolT> phi_bb162_12;
  TNode<PrimitiveHeapObject> phi_bb162_13;
  TNode<IntPtrT> phi_bb162_32;
  TNode<IntPtrT> tmp207;
  TNode<BoolT> tmp208;
  if (block162.is_used()) {
    ca_.Bind(&block162, &phi_bb162_9, &phi_bb162_10, &phi_bb162_12, &phi_bb162_13, &phi_bb162_32);
    tmp207 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp208 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb162_32}, TNode<IntPtrT>{tmp207});
    ca_.Branch(tmp208, &block164, std::vector<compiler::Node*>{phi_bb162_9, phi_bb162_10, phi_bb162_12, phi_bb162_13}, &block165, std::vector<compiler::Node*>{phi_bb162_9, phi_bb162_10, phi_bb162_12, phi_bb162_13});
  }

  TNode<FixedArray> phi_bb165_9;
  TNode<IntPtrT> phi_bb165_10;
  TNode<BoolT> phi_bb165_12;
  TNode<PrimitiveHeapObject> phi_bb165_13;
  if (block165.is_used()) {
    ca_.Bind(&block165, &phi_bb165_9, &phi_bb165_10, &phi_bb165_12, &phi_bb165_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb164_9;
  TNode<IntPtrT> phi_bb164_10;
  TNode<BoolT> phi_bb164_12;
  TNode<PrimitiveHeapObject> phi_bb164_13;
  TNode<FixedArray> tmp209;
  TNode<Union<HeapObject, TaggedIndex>> tmp210;
  TNode<IntPtrT> tmp211;
  TNode<IntPtrT> tmp212;
  TNode<UintPtrT> tmp213;
  TNode<IntPtrT> tmp214;
  TNode<UintPtrT> tmp215;
  TNode<UintPtrT> tmp216;
  TNode<BoolT> tmp217;
  if (block164.is_used()) {
    ca_.Bind(&block164, &phi_bb164_9, &phi_bb164_10, &phi_bb164_12, &phi_bb164_13);
    tmp209 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb162_32});
    std::tie(tmp210, tmp211, tmp212) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb164_9}).Flatten();
    tmp213 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp214 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp213});
    tmp215 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp214});
    tmp216 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp212});
    tmp217 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp215}, TNode<UintPtrT>{tmp216});
    ca_.Branch(tmp217, &block171, std::vector<compiler::Node*>{phi_bb164_9, phi_bb164_10, phi_bb164_12, phi_bb164_13, phi_bb164_9}, &block172, std::vector<compiler::Node*>{phi_bb164_9, phi_bb164_10, phi_bb164_12, phi_bb164_13, phi_bb164_9});
  }

  TNode<FixedArray> phi_bb171_9;
  TNode<IntPtrT> phi_bb171_10;
  TNode<BoolT> phi_bb171_12;
  TNode<PrimitiveHeapObject> phi_bb171_13;
  TNode<FixedArray> phi_bb171_34;
  TNode<IntPtrT> tmp218;
  TNode<IntPtrT> tmp219;
  TNode<Union<HeapObject, TaggedIndex>> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<Union<HeapObject, TaggedIndex>> tmp222;
  TNode<IntPtrT> tmp223;
  TNode<IntPtrT> tmp224;
  TNode<UintPtrT> tmp225;
  TNode<IntPtrT> tmp226;
  TNode<UintPtrT> tmp227;
  TNode<UintPtrT> tmp228;
  TNode<BoolT> tmp229;
  if (block171.is_used()) {
    ca_.Bind(&block171, &phi_bb171_9, &phi_bb171_10, &phi_bb171_12, &phi_bb171_13, &phi_bb171_34);
    tmp218 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp214});
    tmp219 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp211}, TNode<IntPtrT>{tmp218});
    std::tie(tmp220, tmp221) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp210}, TNode<IntPtrT>{tmp219}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp220, tmp221}, tmp209);
    std::tie(tmp222, tmp223, tmp224) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp209}).Flatten();
    tmp225 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp226 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp225});
    tmp227 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp226});
    tmp228 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp224});
    tmp229 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp227}, TNode<UintPtrT>{tmp228});
    ca_.Branch(tmp229, &block180, std::vector<compiler::Node*>{phi_bb171_9, phi_bb171_10, phi_bb171_12, phi_bb171_13}, &block181, std::vector<compiler::Node*>{phi_bb171_9, phi_bb171_10, phi_bb171_12, phi_bb171_13});
  }

  TNode<FixedArray> phi_bb172_9;
  TNode<IntPtrT> phi_bb172_10;
  TNode<BoolT> phi_bb172_12;
  TNode<PrimitiveHeapObject> phi_bb172_13;
  TNode<FixedArray> phi_bb172_34;
  if (block172.is_used()) {
    ca_.Bind(&block172, &phi_bb172_9, &phi_bb172_10, &phi_bb172_12, &phi_bb172_13, &phi_bb172_34);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb180_9;
  TNode<IntPtrT> phi_bb180_10;
  TNode<BoolT> phi_bb180_12;
  TNode<PrimitiveHeapObject> phi_bb180_13;
  TNode<IntPtrT> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<Union<HeapObject, TaggedIndex>> tmp232;
  TNode<IntPtrT> tmp233;
  TNode<Undefined> tmp234;
  TNode<Union<HeapObject, TaggedIndex>> tmp235;
  TNode<IntPtrT> tmp236;
  TNode<IntPtrT> tmp237;
  TNode<UintPtrT> tmp238;
  TNode<IntPtrT> tmp239;
  TNode<UintPtrT> tmp240;
  TNode<UintPtrT> tmp241;
  TNode<BoolT> tmp242;
  if (block180.is_used()) {
    ca_.Bind(&block180, &phi_bb180_9, &phi_bb180_10, &phi_bb180_12, &phi_bb180_13);
    tmp230 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp226});
    tmp231 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp223}, TNode<IntPtrT>{tmp230});
    std::tie(tmp232, tmp233) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp222}, TNode<IntPtrT>{tmp231}).Flatten();
    tmp234 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp232, tmp233}, tmp234);
    std::tie(tmp235, tmp236, tmp237) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp209}).Flatten();
    tmp238 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp239 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp238});
    tmp240 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp239});
    tmp241 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp237});
    tmp242 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp240}, TNode<UintPtrT>{tmp241});
    ca_.Branch(tmp242, &block189, std::vector<compiler::Node*>{phi_bb180_9, phi_bb180_10, phi_bb180_12, phi_bb180_13}, &block190, std::vector<compiler::Node*>{phi_bb180_9, phi_bb180_10, phi_bb180_12, phi_bb180_13});
  }

  TNode<FixedArray> phi_bb181_9;
  TNode<IntPtrT> phi_bb181_10;
  TNode<BoolT> phi_bb181_12;
  TNode<PrimitiveHeapObject> phi_bb181_13;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_9, &phi_bb181_10, &phi_bb181_12, &phi_bb181_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb189_9;
  TNode<IntPtrT> phi_bb189_10;
  TNode<BoolT> phi_bb189_12;
  TNode<PrimitiveHeapObject> phi_bb189_13;
  TNode<IntPtrT> tmp243;
  TNode<IntPtrT> tmp244;
  TNode<Union<HeapObject, TaggedIndex>> tmp245;
  TNode<IntPtrT> tmp246;
  TNode<IntPtrT> tmp247;
  if (block189.is_used()) {
    ca_.Bind(&block189, &phi_bb189_9, &phi_bb189_10, &phi_bb189_12, &phi_bb189_13);
    tmp243 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp239});
    tmp244 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp236}, TNode<IntPtrT>{tmp243});
    std::tie(tmp245, tmp246) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp235}, TNode<IntPtrT>{tmp244}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp245, tmp246}, tmp185);
    tmp247 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block151, tmp209, tmp247, phi_bb189_12, phi_bb189_13);
  }

  TNode<FixedArray> phi_bb190_9;
  TNode<IntPtrT> phi_bb190_10;
  TNode<BoolT> phi_bb190_12;
  TNode<PrimitiveHeapObject> phi_bb190_13;
  if (block190.is_used()) {
    ca_.Bind(&block190, &phi_bb190_9, &phi_bb190_10, &phi_bb190_12, &phi_bb190_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb151_9;
  TNode<IntPtrT> phi_bb151_10;
  TNode<BoolT> phi_bb151_12;
  TNode<PrimitiveHeapObject> phi_bb151_13;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_9, &phi_bb151_10, &phi_bb151_12, &phi_bb151_13);
    ca_.Goto(&block137, phi_bb151_9, phi_bb151_10, phi_bb151_12, phi_bb151_13);
  }

  TNode<FixedArray> phi_bb138_9;
  TNode<IntPtrT> phi_bb138_10;
  TNode<BoolT> phi_bb138_12;
  TNode<PrimitiveHeapObject> phi_bb138_13;
  TNode<Smi> tmp248;
  if (block138.is_used()) {
    ca_.Bind(&block138, &phi_bb138_9, &phi_bb138_10, &phi_bb138_12, &phi_bb138_13);
    compiler::CodeAssemblerLabel label249(&ca_);
    tmp248 = Cast_Smi_0(state_, TNode<Object>{ca_.UncheckedCast<Object>(tmp180)}, &label249);
    ca_.Goto(&block195, phi_bb138_9, phi_bb138_10, phi_bb138_12, phi_bb138_13);
    if (label249.is_used()) {
      ca_.Bind(&label249);
      ca_.Goto(&block196, phi_bb138_9, phi_bb138_10, phi_bb138_12, phi_bb138_13);
    }
  }

  TNode<FixedArray> phi_bb196_9;
  TNode<IntPtrT> phi_bb196_10;
  TNode<BoolT> phi_bb196_12;
  TNode<PrimitiveHeapObject> phi_bb196_13;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_9, &phi_bb196_10, &phi_bb196_12, &phi_bb196_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:234:9");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb195_9;
  TNode<IntPtrT> phi_bb195_10;
  TNode<BoolT> phi_bb195_12;
  TNode<PrimitiveHeapObject> phi_bb195_13;
  TNode<Smi> tmp250;
  TNode<BoolT> tmp251;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_9, &phi_bb195_10, &phi_bb195_12, &phi_bb195_13);
    tmp250 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp251 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp248}, TNode<Smi>{tmp250});
    ca_.Branch(tmp251, &block197, std::vector<compiler::Node*>{phi_bb195_9, phi_bb195_10, phi_bb195_12, phi_bb195_13}, &block198, std::vector<compiler::Node*>{phi_bb195_9, phi_bb195_10, phi_bb195_12, phi_bb195_13});
  }

  TNode<FixedArray> phi_bb198_9;
  TNode<IntPtrT> phi_bb198_10;
  TNode<BoolT> phi_bb198_12;
  TNode<PrimitiveHeapObject> phi_bb198_13;
  if (block198.is_used()) {
    ca_.Bind(&block198, &phi_bb198_9, &phi_bb198_10, &phi_bb198_12, &phi_bb198_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 229});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count < 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb197_9;
  TNode<IntPtrT> phi_bb197_10;
  TNode<BoolT> phi_bb197_12;
  TNode<PrimitiveHeapObject> phi_bb197_13;
  TNode<Smi> tmp252;
  TNode<Smi> tmp253;
  TNode<Smi> tmp254;
  TNode<BoolT> tmp255;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_9, &phi_bb197_10, &phi_bb197_12, &phi_bb197_13);
    tmp252 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp253 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp248}, TNode<Smi>{tmp252});
    tmp254 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp255 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp253}, TNode<Smi>{tmp254});
    ca_.Branch(tmp255, &block199, std::vector<compiler::Node*>{phi_bb197_9, phi_bb197_10, phi_bb197_12, phi_bb197_13}, &block200, std::vector<compiler::Node*>{phi_bb197_9, phi_bb197_10, phi_bb197_12, phi_bb197_13});
  }

  TNode<FixedArray> phi_bb200_9;
  TNode<IntPtrT> phi_bb200_10;
  TNode<BoolT> phi_bb200_12;
  TNode<PrimitiveHeapObject> phi_bb200_13;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_9, &phi_bb200_10, &phi_bb200_12, &phi_bb200_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 230});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count - 1 < 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb199_9;
  TNode<IntPtrT> phi_bb199_10;
  TNode<BoolT> phi_bb199_12;
  TNode<PrimitiveHeapObject> phi_bb199_13;
  TNode<Union<HeapObject, TaggedIndex>> tmp256;
  TNode<IntPtrT> tmp257;
  TNode<IntPtrT> tmp258;
  TNode<IntPtrT> tmp259;
  TNode<IntPtrT> tmp260;
  TNode<UintPtrT> tmp261;
  TNode<UintPtrT> tmp262;
  TNode<BoolT> tmp263;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_9, &phi_bb199_10, &phi_bb199_12, &phi_bb199_13);
    std::tie(tmp256, tmp257, tmp258) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb199_9}).Flatten();
    tmp259 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp260 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb199_10}, TNode<IntPtrT>{tmp259});
    tmp261 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp260});
    tmp262 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp258});
    tmp263 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp261}, TNode<UintPtrT>{tmp262});
    ca_.Branch(tmp263, &block205, std::vector<compiler::Node*>{phi_bb199_9, phi_bb199_10, phi_bb199_12, phi_bb199_13, phi_bb199_9}, &block206, std::vector<compiler::Node*>{phi_bb199_9, phi_bb199_10, phi_bb199_12, phi_bb199_13, phi_bb199_9});
  }

  TNode<FixedArray> phi_bb205_9;
  TNode<IntPtrT> phi_bb205_10;
  TNode<BoolT> phi_bb205_12;
  TNode<PrimitiveHeapObject> phi_bb205_13;
  TNode<FixedArray> phi_bb205_28;
  TNode<IntPtrT> tmp264;
  TNode<IntPtrT> tmp265;
  TNode<Union<HeapObject, TaggedIndex>> tmp266;
  TNode<IntPtrT> tmp267;
  TNode<Smi> tmp268;
  TNode<Smi> tmp269;
  if (block205.is_used()) {
    ca_.Bind(&block205, &phi_bb205_9, &phi_bb205_10, &phi_bb205_12, &phi_bb205_13, &phi_bb205_28);
    tmp264 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp260});
    tmp265 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp257}, TNode<IntPtrT>{tmp264});
    std::tie(tmp266, tmp267) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp256}, TNode<IntPtrT>{tmp265}).Flatten();
    tmp268 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp269 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp248}, TNode<Smi>{tmp268});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp266, tmp267}, tmp269);
    ca_.Goto(&block137, phi_bb205_9, phi_bb205_10, phi_bb205_12, phi_bb205_13);
  }

  TNode<FixedArray> phi_bb206_9;
  TNode<IntPtrT> phi_bb206_10;
  TNode<BoolT> phi_bb206_12;
  TNode<PrimitiveHeapObject> phi_bb206_13;
  TNode<FixedArray> phi_bb206_28;
  if (block206.is_used()) {
    ca_.Bind(&block206, &phi_bb206_9, &phi_bb206_10, &phi_bb206_12, &phi_bb206_13, &phi_bb206_28);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb137_9;
  TNode<IntPtrT> phi_bb137_10;
  TNode<BoolT> phi_bb137_12;
  TNode<PrimitiveHeapObject> phi_bb137_13;
  if (block137.is_used()) {
    ca_.Bind(&block137, &phi_bb137_9, &phi_bb137_10, &phi_bb137_12, &phi_bb137_13);
    ca_.Goto(&block125, phi_bb137_9, phi_bb137_10, phi_bb137_12, phi_bb137_13);
  }

  TNode<FixedArray> phi_bb124_9;
  TNode<IntPtrT> phi_bb124_10;
  TNode<BoolT> phi_bb124_12;
  TNode<PrimitiveHeapObject> phi_bb124_13;
  TNode<IntPtrT> tmp270;
  TNode<IntPtrT> tmp271;
  TNode<BoolT> tmp272;
  if (block124.is_used()) {
    ca_.Bind(&block124, &phi_bb124_9, &phi_bb124_10, &phi_bb124_12, &phi_bb124_13);
    tmp270 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb124_9});
    tmp271 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp272 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb124_10}, TNode<IntPtrT>{tmp271});
    ca_.Branch(tmp272, &block210, std::vector<compiler::Node*>{phi_bb124_9, phi_bb124_10, phi_bb124_12, phi_bb124_13}, &block211, std::vector<compiler::Node*>{phi_bb124_9, phi_bb124_10, phi_bb124_12, phi_bb124_13});
  }

  TNode<FixedArray> phi_bb211_9;
  TNode<IntPtrT> phi_bb211_10;
  TNode<BoolT> phi_bb211_12;
  TNode<PrimitiveHeapObject> phi_bb211_13;
  if (block211.is_used()) {
    ca_.Bind(&block211, &phi_bb211_9, &phi_bb211_10, &phi_bb211_12, &phi_bb211_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb210_9;
  TNode<IntPtrT> phi_bb210_10;
  TNode<BoolT> phi_bb210_12;
  TNode<PrimitiveHeapObject> phi_bb210_13;
  TNode<BoolT> tmp273;
  if (block210.is_used()) {
    ca_.Bind(&block210, &phi_bb210_9, &phi_bb210_10, &phi_bb210_12, &phi_bb210_13);
    tmp273 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb210_10}, TNode<IntPtrT>{tmp270});
    ca_.Branch(tmp273, &block212, std::vector<compiler::Node*>{phi_bb210_9, phi_bb210_10, phi_bb210_12, phi_bb210_13}, &block213, std::vector<compiler::Node*>{phi_bb210_9, phi_bb210_10, phi_bb210_12, phi_bb210_13});
  }

  TNode<FixedArray> phi_bb213_9;
  TNode<IntPtrT> phi_bb213_10;
  TNode<BoolT> phi_bb213_12;
  TNode<PrimitiveHeapObject> phi_bb213_13;
  if (block213.is_used()) {
    ca_.Bind(&block213, &phi_bb213_9, &phi_bb213_10, &phi_bb213_12, &phi_bb213_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb212_9;
  TNode<IntPtrT> phi_bb212_10;
  TNode<BoolT> phi_bb212_12;
  TNode<PrimitiveHeapObject> phi_bb212_13;
  TNode<BoolT> tmp274;
  if (block212.is_used()) {
    ca_.Bind(&block212, &phi_bb212_9, &phi_bb212_10, &phi_bb212_12, &phi_bb212_13);
    tmp274 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb212_10}, TNode<IntPtrT>{tmp270});
    ca_.Branch(tmp274, &block214, std::vector<compiler::Node*>{phi_bb212_9, phi_bb212_10, phi_bb212_12, phi_bb212_13}, &block215, std::vector<compiler::Node*>{phi_bb212_9, phi_bb212_10, phi_bb212_12, phi_bb212_13});
  }

  TNode<FixedArray> phi_bb214_9;
  TNode<IntPtrT> phi_bb214_10;
  TNode<BoolT> phi_bb214_12;
  TNode<PrimitiveHeapObject> phi_bb214_13;
  TNode<Union<HeapObject, TaggedIndex>> tmp275;
  TNode<IntPtrT> tmp276;
  TNode<IntPtrT> tmp277;
  TNode<IntPtrT> tmp278;
  TNode<IntPtrT> tmp279;
  TNode<UintPtrT> tmp280;
  TNode<UintPtrT> tmp281;
  TNode<BoolT> tmp282;
  if (block214.is_used()) {
    ca_.Bind(&block214, &phi_bb214_9, &phi_bb214_10, &phi_bb214_12, &phi_bb214_13);
    std::tie(tmp275, tmp276, tmp277) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb214_9}).Flatten();
    tmp278 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp279 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb214_10}, TNode<IntPtrT>{tmp278});
    tmp280 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb214_10});
    tmp281 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp277});
    tmp282 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp280}, TNode<UintPtrT>{tmp281});
    ca_.Branch(tmp282, &block221, std::vector<compiler::Node*>{phi_bb214_9, phi_bb214_12, phi_bb214_13, phi_bb214_9, phi_bb214_10, phi_bb214_10, phi_bb214_10, phi_bb214_10}, &block222, std::vector<compiler::Node*>{phi_bb214_9, phi_bb214_12, phi_bb214_13, phi_bb214_9, phi_bb214_10, phi_bb214_10, phi_bb214_10, phi_bb214_10});
  }

  TNode<FixedArray> phi_bb221_9;
  TNode<BoolT> phi_bb221_12;
  TNode<PrimitiveHeapObject> phi_bb221_13;
  TNode<FixedArray> phi_bb221_29;
  TNode<IntPtrT> phi_bb221_33;
  TNode<IntPtrT> phi_bb221_34;
  TNode<IntPtrT> phi_bb221_38;
  TNode<IntPtrT> phi_bb221_39;
  TNode<IntPtrT> tmp283;
  TNode<IntPtrT> tmp284;
  TNode<Union<HeapObject, TaggedIndex>> tmp285;
  TNode<IntPtrT> tmp286;
  if (block221.is_used()) {
    ca_.Bind(&block221, &phi_bb221_9, &phi_bb221_12, &phi_bb221_13, &phi_bb221_29, &phi_bb221_33, &phi_bb221_34, &phi_bb221_38, &phi_bb221_39);
    tmp283 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb221_39});
    tmp284 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp276}, TNode<IntPtrT>{tmp283});
    std::tie(tmp285, tmp286) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp275}, TNode<IntPtrT>{tmp284}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp285, tmp286}, phi_bb11_16);
    ca_.Goto(&block216, phi_bb221_9, tmp279, phi_bb221_12, phi_bb221_13);
  }

  TNode<FixedArray> phi_bb222_9;
  TNode<BoolT> phi_bb222_12;
  TNode<PrimitiveHeapObject> phi_bb222_13;
  TNode<FixedArray> phi_bb222_29;
  TNode<IntPtrT> phi_bb222_33;
  TNode<IntPtrT> phi_bb222_34;
  TNode<IntPtrT> phi_bb222_38;
  TNode<IntPtrT> phi_bb222_39;
  if (block222.is_used()) {
    ca_.Bind(&block222, &phi_bb222_9, &phi_bb222_12, &phi_bb222_13, &phi_bb222_29, &phi_bb222_33, &phi_bb222_34, &phi_bb222_38, &phi_bb222_39);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb215_9;
  TNode<IntPtrT> phi_bb215_10;
  TNode<BoolT> phi_bb215_12;
  TNode<PrimitiveHeapObject> phi_bb215_13;
  TNode<IntPtrT> tmp287;
  TNode<IntPtrT> tmp288;
  TNode<BoolT> tmp289;
  if (block215.is_used()) {
    ca_.Bind(&block215, &phi_bb215_9, &phi_bb215_10, &phi_bb215_12, &phi_bb215_13);
    tmp287 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp270});
    tmp288 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp289 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp287}, TNode<IntPtrT>{tmp288});
    ca_.Branch(tmp289, &block225, std::vector<compiler::Node*>{phi_bb215_9, phi_bb215_10, phi_bb215_12, phi_bb215_13}, &block226, std::vector<compiler::Node*>{phi_bb215_9, phi_bb215_10, phi_bb215_12, phi_bb215_13});
  }

  TNode<FixedArray> phi_bb225_9;
  TNode<IntPtrT> phi_bb225_10;
  TNode<BoolT> phi_bb225_12;
  TNode<PrimitiveHeapObject> phi_bb225_13;
  TNode<IntPtrT> tmp290;
  if (block225.is_used()) {
    ca_.Bind(&block225, &phi_bb225_9, &phi_bb225_10, &phi_bb225_12, &phi_bb225_13);
    tmp290 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block227, phi_bb225_9, phi_bb225_10, phi_bb225_12, phi_bb225_13, tmp290);
  }

  TNode<FixedArray> phi_bb226_9;
  TNode<IntPtrT> phi_bb226_10;
  TNode<BoolT> phi_bb226_12;
  TNode<PrimitiveHeapObject> phi_bb226_13;
  if (block226.is_used()) {
    ca_.Bind(&block226, &phi_bb226_9, &phi_bb226_10, &phi_bb226_12, &phi_bb226_13);
    ca_.Goto(&block227, phi_bb226_9, phi_bb226_10, phi_bb226_12, phi_bb226_13, tmp287);
  }

  TNode<FixedArray> phi_bb227_9;
  TNode<IntPtrT> phi_bb227_10;
  TNode<BoolT> phi_bb227_12;
  TNode<PrimitiveHeapObject> phi_bb227_13;
  TNode<IntPtrT> phi_bb227_30;
  TNode<IntPtrT> tmp291;
  TNode<BoolT> tmp292;
  if (block227.is_used()) {
    ca_.Bind(&block227, &phi_bb227_9, &phi_bb227_10, &phi_bb227_12, &phi_bb227_13, &phi_bb227_30);
    tmp291 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp292 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb227_30}, TNode<IntPtrT>{tmp291});
    ca_.Branch(tmp292, &block229, std::vector<compiler::Node*>{phi_bb227_9, phi_bb227_10, phi_bb227_12, phi_bb227_13}, &block230, std::vector<compiler::Node*>{phi_bb227_9, phi_bb227_10, phi_bb227_12, phi_bb227_13});
  }

  TNode<FixedArray> phi_bb230_9;
  TNode<IntPtrT> phi_bb230_10;
  TNode<BoolT> phi_bb230_12;
  TNode<PrimitiveHeapObject> phi_bb230_13;
  if (block230.is_used()) {
    ca_.Bind(&block230, &phi_bb230_9, &phi_bb230_10, &phi_bb230_12, &phi_bb230_13);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb229_9;
  TNode<IntPtrT> phi_bb229_10;
  TNode<BoolT> phi_bb229_12;
  TNode<PrimitiveHeapObject> phi_bb229_13;
  TNode<FixedArray> tmp293;
  TNode<Union<HeapObject, TaggedIndex>> tmp294;
  TNode<IntPtrT> tmp295;
  TNode<IntPtrT> tmp296;
  TNode<UintPtrT> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<UintPtrT> tmp299;
  TNode<UintPtrT> tmp300;
  TNode<BoolT> tmp301;
  if (block229.is_used()) {
    ca_.Bind(&block229, &phi_bb229_9, &phi_bb229_10, &phi_bb229_12, &phi_bb229_13);
    tmp293 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb227_30});
    std::tie(tmp294, tmp295, tmp296) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb229_9}).Flatten();
    tmp297 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp298 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp297});
    tmp299 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp298});
    tmp300 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp296});
    tmp301 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp299}, TNode<UintPtrT>{tmp300});
    ca_.Branch(tmp301, &block236, std::vector<compiler::Node*>{phi_bb229_9, phi_bb229_10, phi_bb229_12, phi_bb229_13, phi_bb229_9}, &block237, std::vector<compiler::Node*>{phi_bb229_9, phi_bb229_10, phi_bb229_12, phi_bb229_13, phi_bb229_9});
  }

  TNode<FixedArray> phi_bb236_9;
  TNode<IntPtrT> phi_bb236_10;
  TNode<BoolT> phi_bb236_12;
  TNode<PrimitiveHeapObject> phi_bb236_13;
  TNode<FixedArray> phi_bb236_32;
  TNode<IntPtrT> tmp302;
  TNode<IntPtrT> tmp303;
  TNode<Union<HeapObject, TaggedIndex>> tmp304;
  TNode<IntPtrT> tmp305;
  TNode<Union<HeapObject, TaggedIndex>> tmp306;
  TNode<IntPtrT> tmp307;
  TNode<IntPtrT> tmp308;
  TNode<UintPtrT> tmp309;
  TNode<IntPtrT> tmp310;
  TNode<UintPtrT> tmp311;
  TNode<UintPtrT> tmp312;
  TNode<BoolT> tmp313;
  if (block236.is_used()) {
    ca_.Bind(&block236, &phi_bb236_9, &phi_bb236_10, &phi_bb236_12, &phi_bb236_13, &phi_bb236_32);
    tmp302 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp298});
    tmp303 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp295}, TNode<IntPtrT>{tmp302});
    std::tie(tmp304, tmp305) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp294}, TNode<IntPtrT>{tmp303}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp304, tmp305}, tmp293);
    std::tie(tmp306, tmp307, tmp308) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp293}).Flatten();
    tmp309 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp310 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp309});
    tmp311 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp310});
    tmp312 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp308});
    tmp313 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp311}, TNode<UintPtrT>{tmp312});
    ca_.Branch(tmp313, &block245, std::vector<compiler::Node*>{phi_bb236_9, phi_bb236_10, phi_bb236_12, phi_bb236_13}, &block246, std::vector<compiler::Node*>{phi_bb236_9, phi_bb236_10, phi_bb236_12, phi_bb236_13});
  }

  TNode<FixedArray> phi_bb237_9;
  TNode<IntPtrT> phi_bb237_10;
  TNode<BoolT> phi_bb237_12;
  TNode<PrimitiveHeapObject> phi_bb237_13;
  TNode<FixedArray> phi_bb237_32;
  if (block237.is_used()) {
    ca_.Bind(&block237, &phi_bb237_9, &phi_bb237_10, &phi_bb237_12, &phi_bb237_13, &phi_bb237_32);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb245_9;
  TNode<IntPtrT> phi_bb245_10;
  TNode<BoolT> phi_bb245_12;
  TNode<PrimitiveHeapObject> phi_bb245_13;
  TNode<IntPtrT> tmp314;
  TNode<IntPtrT> tmp315;
  TNode<Union<HeapObject, TaggedIndex>> tmp316;
  TNode<IntPtrT> tmp317;
  TNode<Undefined> tmp318;
  TNode<Union<HeapObject, TaggedIndex>> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<IntPtrT> tmp321;
  TNode<UintPtrT> tmp322;
  TNode<IntPtrT> tmp323;
  TNode<UintPtrT> tmp324;
  TNode<UintPtrT> tmp325;
  TNode<BoolT> tmp326;
  if (block245.is_used()) {
    ca_.Bind(&block245, &phi_bb245_9, &phi_bb245_10, &phi_bb245_12, &phi_bb245_13);
    tmp314 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp310});
    tmp315 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp307}, TNode<IntPtrT>{tmp314});
    std::tie(tmp316, tmp317) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp306}, TNode<IntPtrT>{tmp315}).Flatten();
    tmp318 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp316, tmp317}, tmp318);
    std::tie(tmp319, tmp320, tmp321) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp293}).Flatten();
    tmp322 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp323 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp322});
    tmp324 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp323});
    tmp325 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp321});
    tmp326 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp324}, TNode<UintPtrT>{tmp325});
    ca_.Branch(tmp326, &block254, std::vector<compiler::Node*>{phi_bb245_9, phi_bb245_10, phi_bb245_12, phi_bb245_13}, &block255, std::vector<compiler::Node*>{phi_bb245_9, phi_bb245_10, phi_bb245_12, phi_bb245_13});
  }

  TNode<FixedArray> phi_bb246_9;
  TNode<IntPtrT> phi_bb246_10;
  TNode<BoolT> phi_bb246_12;
  TNode<PrimitiveHeapObject> phi_bb246_13;
  if (block246.is_used()) {
    ca_.Bind(&block246, &phi_bb246_9, &phi_bb246_10, &phi_bb246_12, &phi_bb246_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb254_9;
  TNode<IntPtrT> phi_bb254_10;
  TNode<BoolT> phi_bb254_12;
  TNode<PrimitiveHeapObject> phi_bb254_13;
  TNode<IntPtrT> tmp327;
  TNode<IntPtrT> tmp328;
  TNode<Union<HeapObject, TaggedIndex>> tmp329;
  TNode<IntPtrT> tmp330;
  TNode<IntPtrT> tmp331;
  if (block254.is_used()) {
    ca_.Bind(&block254, &phi_bb254_9, &phi_bb254_10, &phi_bb254_12, &phi_bb254_13);
    tmp327 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp323});
    tmp328 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp320}, TNode<IntPtrT>{tmp327});
    std::tie(tmp329, tmp330) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp319}, TNode<IntPtrT>{tmp328}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp329, tmp330}, phi_bb11_16);
    tmp331 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block216, tmp293, tmp331, phi_bb254_12, phi_bb254_13);
  }

  TNode<FixedArray> phi_bb255_9;
  TNode<IntPtrT> phi_bb255_10;
  TNode<BoolT> phi_bb255_12;
  TNode<PrimitiveHeapObject> phi_bb255_13;
  if (block255.is_used()) {
    ca_.Bind(&block255, &phi_bb255_9, &phi_bb255_10, &phi_bb255_12, &phi_bb255_13);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb216_9;
  TNode<IntPtrT> phi_bb216_10;
  TNode<BoolT> phi_bb216_12;
  TNode<PrimitiveHeapObject> phi_bb216_13;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_9, &phi_bb216_10, &phi_bb216_12, &phi_bb216_13);
    ca_.Goto(&block125, phi_bb216_9, phi_bb216_10, phi_bb216_12, phi_bb11_16);
  }

  TNode<FixedArray> phi_bb125_9;
  TNode<IntPtrT> phi_bb125_10;
  TNode<BoolT> phi_bb125_12;
  TNode<PrimitiveHeapObject> phi_bb125_13;
  TNode<IntPtrT> tmp332;
  TNode<Map> tmp333;
  TNode<BoolT> tmp334;
  TNode<BoolT> tmp335;
  TNode<IntPtrT> tmp336;
  if (block125.is_used()) {
    ca_.Bind(&block125, &phi_bb125_9, &phi_bb125_10, &phi_bb125_12, &phi_bb125_13);
    tmp332 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp333 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{phi_bb11_16, tmp332});
    tmp334 = CodeStubAssembler(state_).IsOneByteStringMap(TNode<Map>{tmp333});
    tmp335 = CodeStubAssembler(state_).Word32And(TNode<BoolT>{tmp334}, TNode<BoolT>{phi_bb125_12});
    tmp336 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block6, tmp336, phi_bb125_9, phi_bb125_10, tmp164, tmp335, phi_bb125_13, phi_bb11_15);
  }

  TNode<IntPtrT> phi_bb5_7;
  TNode<FixedArray> phi_bb5_9;
  TNode<IntPtrT> phi_bb5_10;
  TNode<IntPtrT> phi_bb5_11;
  TNode<BoolT> phi_bb5_12;
  TNode<PrimitiveHeapObject> phi_bb5_13;
  TNode<UintPtrT> phi_bb5_15;
  TNode<IntPtrT> tmp337;
  TNode<BoolT> tmp338;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_7, &phi_bb5_9, &phi_bb5_10, &phi_bb5_11, &phi_bb5_12, &phi_bb5_13, &phi_bb5_15);
    tmp337 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp338 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb3_14}, TNode<IntPtrT>{tmp337});
    ca_.Branch(tmp338, &block258, std::vector<compiler::Node*>{phi_bb5_7, phi_bb5_9, phi_bb5_10, phi_bb5_11, phi_bb5_12, phi_bb5_13, phi_bb5_15}, &block259, std::vector<compiler::Node*>{phi_bb5_7, phi_bb5_9, phi_bb5_10, phi_bb5_11, phi_bb5_12, phi_bb5_13, phi_bb5_15});
  }

  TNode<IntPtrT> phi_bb258_7;
  TNode<FixedArray> phi_bb258_9;
  TNode<IntPtrT> phi_bb258_10;
  TNode<IntPtrT> phi_bb258_11;
  TNode<BoolT> phi_bb258_12;
  TNode<PrimitiveHeapObject> phi_bb258_13;
  TNode<UintPtrT> phi_bb258_15;
  TNode<UintPtrT> tmp339;
  TNode<BoolT> tmp340;
  if (block258.is_used()) {
    ca_.Bind(&block258, &phi_bb258_7, &phi_bb258_9, &phi_bb258_10, &phi_bb258_11, &phi_bb258_12, &phi_bb258_13, &phi_bb258_15);
    tmp339 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp340 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{phi_bb258_15}, TNode<UintPtrT>{tmp339});
    ca_.Branch(tmp340, &block260, std::vector<compiler::Node*>{phi_bb258_7, phi_bb258_9, phi_bb258_10, phi_bb258_11, phi_bb258_12, phi_bb258_13, phi_bb258_15}, &block261, std::vector<compiler::Node*>{phi_bb258_7, phi_bb258_9, phi_bb258_10, phi_bb258_11, phi_bb258_12, phi_bb258_13, phi_bb258_15});
  }

  TNode<IntPtrT> phi_bb260_7;
  TNode<FixedArray> phi_bb260_9;
  TNode<IntPtrT> phi_bb260_10;
  TNode<IntPtrT> phi_bb260_11;
  TNode<BoolT> phi_bb260_12;
  TNode<PrimitiveHeapObject> phi_bb260_13;
  TNode<UintPtrT> phi_bb260_15;
  TNode<IntPtrT> tmp341;
  TNode<IntPtrT> tmp342;
  if (block260.is_used()) {
    ca_.Bind(&block260, &phi_bb260_7, &phi_bb260_9, &phi_bb260_10, &phi_bb260_11, &phi_bb260_12, &phi_bb260_13, &phi_bb260_15);
    tmp341 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp342 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb260_7}, TNode<IntPtrT>{tmp341});
    ca_.Goto(&block261, tmp342, phi_bb260_9, phi_bb260_10, phi_bb260_11, phi_bb260_12, phi_bb260_13, phi_bb260_15);
  }

  TNode<IntPtrT> phi_bb261_7;
  TNode<FixedArray> phi_bb261_9;
  TNode<IntPtrT> phi_bb261_10;
  TNode<IntPtrT> phi_bb261_11;
  TNode<BoolT> phi_bb261_12;
  TNode<PrimitiveHeapObject> phi_bb261_13;
  TNode<UintPtrT> phi_bb261_15;
  TNode<IntPtrT> tmp343;
  TNode<IntPtrT> tmp344;
  TNode<IntPtrT> tmp345;
  if (block261.is_used()) {
    ca_.Bind(&block261, &phi_bb261_7, &phi_bb261_9, &phi_bb261_10, &phi_bb261_11, &phi_bb261_12, &phi_bb261_13, &phi_bb261_15);
    tmp343 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp344 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb3_14}, TNode<IntPtrT>{tmp343});
    tmp345 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb261_7}, TNode<IntPtrT>{tmp344});
    ca_.Goto(&block259, tmp345, phi_bb261_9, phi_bb261_10, phi_bb261_11, phi_bb261_12, phi_bb261_13, phi_bb261_15);
  }

  TNode<IntPtrT> phi_bb259_7;
  TNode<FixedArray> phi_bb259_9;
  TNode<IntPtrT> phi_bb259_10;
  TNode<IntPtrT> phi_bb259_11;
  TNode<BoolT> phi_bb259_12;
  TNode<PrimitiveHeapObject> phi_bb259_13;
  TNode<UintPtrT> phi_bb259_15;
  TNode<BoolT> tmp346;
  TNode<IntPtrT> tmp347;
  TNode<BoolT> tmp348;
  if (block259.is_used()) {
    ca_.Bind(&block259, &phi_bb259_7, &phi_bb259_9, &phi_bb259_10, &phi_bb259_11, &phi_bb259_12, &phi_bb259_13, &phi_bb259_15);
    tmp346 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp347 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp348 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb259_7}, TNode<IntPtrT>{tmp347});
    ca_.Branch(tmp348, &block265, std::vector<compiler::Node*>{phi_bb259_7, phi_bb259_9, phi_bb259_10, phi_bb259_11, phi_bb259_12, phi_bb259_13, phi_bb259_15, phi_bb259_7, phi_bb259_7}, &block266, std::vector<compiler::Node*>{phi_bb259_7, phi_bb259_9, phi_bb259_10, phi_bb259_11, phi_bb259_12, phi_bb259_13, phi_bb259_15, phi_bb259_7, phi_bb259_7});
  }

  TNode<IntPtrT> phi_bb265_7;
  TNode<FixedArray> phi_bb265_9;
  TNode<IntPtrT> phi_bb265_10;
  TNode<IntPtrT> phi_bb265_11;
  TNode<BoolT> phi_bb265_12;
  TNode<PrimitiveHeapObject> phi_bb265_13;
  TNode<UintPtrT> phi_bb265_15;
  TNode<IntPtrT> phi_bb265_16;
  TNode<IntPtrT> phi_bb265_20;
  TNode<BoolT> tmp349;
  if (block265.is_used()) {
    ca_.Bind(&block265, &phi_bb265_7, &phi_bb265_9, &phi_bb265_10, &phi_bb265_11, &phi_bb265_12, &phi_bb265_13, &phi_bb265_15, &phi_bb265_16, &phi_bb265_20);
    tmp349 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block267, phi_bb265_7, phi_bb265_9, phi_bb265_10, phi_bb265_11, phi_bb265_12, phi_bb265_13, phi_bb265_15, phi_bb265_16, phi_bb265_20, tmp349);
  }

  TNode<IntPtrT> phi_bb266_7;
  TNode<FixedArray> phi_bb266_9;
  TNode<IntPtrT> phi_bb266_10;
  TNode<IntPtrT> phi_bb266_11;
  TNode<BoolT> phi_bb266_12;
  TNode<PrimitiveHeapObject> phi_bb266_13;
  TNode<UintPtrT> phi_bb266_15;
  TNode<IntPtrT> phi_bb266_16;
  TNode<IntPtrT> phi_bb266_20;
  TNode<IntPtrT> tmp350;
  TNode<BoolT> tmp351;
  if (block266.is_used()) {
    ca_.Bind(&block266, &phi_bb266_7, &phi_bb266_9, &phi_bb266_10, &phi_bb266_11, &phi_bb266_12, &phi_bb266_13, &phi_bb266_15, &phi_bb266_16, &phi_bb266_20);
    tmp350 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp351 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp350});
    ca_.Goto(&block267, phi_bb266_7, phi_bb266_9, phi_bb266_10, phi_bb266_11, phi_bb266_12, phi_bb266_13, phi_bb266_15, phi_bb266_16, phi_bb266_20, tmp351);
  }

  TNode<IntPtrT> phi_bb267_7;
  TNode<FixedArray> phi_bb267_9;
  TNode<IntPtrT> phi_bb267_10;
  TNode<IntPtrT> phi_bb267_11;
  TNode<BoolT> phi_bb267_12;
  TNode<PrimitiveHeapObject> phi_bb267_13;
  TNode<UintPtrT> phi_bb267_15;
  TNode<IntPtrT> phi_bb267_16;
  TNode<IntPtrT> phi_bb267_20;
  TNode<BoolT> phi_bb267_24;
  if (block267.is_used()) {
    ca_.Bind(&block267, &phi_bb267_7, &phi_bb267_9, &phi_bb267_10, &phi_bb267_11, &phi_bb267_12, &phi_bb267_13, &phi_bb267_15, &phi_bb267_16, &phi_bb267_20, &phi_bb267_24);
    ca_.Branch(phi_bb267_24, &block263, std::vector<compiler::Node*>{phi_bb267_7, phi_bb267_9, phi_bb267_10, phi_bb267_11, phi_bb267_12, phi_bb267_13, phi_bb267_15, phi_bb267_16, phi_bb267_20}, &block264, std::vector<compiler::Node*>{phi_bb267_7, phi_bb267_9, phi_bb267_10, phi_bb267_11, phi_bb267_12, phi_bb267_13, phi_bb267_15, phi_bb267_16, phi_bb267_20});
  }

  TNode<IntPtrT> phi_bb263_7;
  TNode<FixedArray> phi_bb263_9;
  TNode<IntPtrT> phi_bb263_10;
  TNode<IntPtrT> phi_bb263_11;
  TNode<BoolT> phi_bb263_12;
  TNode<PrimitiveHeapObject> phi_bb263_13;
  TNode<UintPtrT> phi_bb263_15;
  TNode<IntPtrT> phi_bb263_16;
  TNode<IntPtrT> phi_bb263_20;
  if (block263.is_used()) {
    ca_.Bind(&block263, &phi_bb263_7, &phi_bb263_9, &phi_bb263_10, &phi_bb263_11, &phi_bb263_12, &phi_bb263_13, &phi_bb263_15, &phi_bb263_16, &phi_bb263_20);
    ca_.Goto(&block262, phi_bb263_7, phi_bb263_9, phi_bb263_10, phi_bb263_11, phi_bb263_12, phi_bb263_13, phi_bb263_15, phi_bb263_16, phi_bb263_20);
  }

  TNode<IntPtrT> phi_bb264_7;
  TNode<FixedArray> phi_bb264_9;
  TNode<IntPtrT> phi_bb264_10;
  TNode<IntPtrT> phi_bb264_11;
  TNode<BoolT> phi_bb264_12;
  TNode<PrimitiveHeapObject> phi_bb264_13;
  TNode<UintPtrT> phi_bb264_15;
  TNode<IntPtrT> phi_bb264_16;
  TNode<IntPtrT> phi_bb264_20;
  TNode<IntPtrT> tmp352;
  TNode<IntPtrT> tmp353;
  TNode<BoolT> tmp354;
  if (block264.is_used()) {
    ca_.Bind(&block264, &phi_bb264_7, &phi_bb264_9, &phi_bb264_10, &phi_bb264_11, &phi_bb264_12, &phi_bb264_13, &phi_bb264_15, &phi_bb264_16, &phi_bb264_20);
    tmp352 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{phi_bb264_20});
    tmp353 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp352}, TNode<IntPtrT>{tmp3});
    tmp354 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp353}, TNode<IntPtrT>{phi_bb264_20});
    ca_.Branch(tmp354, &block268, std::vector<compiler::Node*>{phi_bb264_7, phi_bb264_9, phi_bb264_10, phi_bb264_11, phi_bb264_12, phi_bb264_13, phi_bb264_15, phi_bb264_16, phi_bb264_20, phi_bb264_20}, &block269, std::vector<compiler::Node*>{phi_bb264_7, phi_bb264_9, phi_bb264_10, phi_bb264_11, phi_bb264_12, phi_bb264_13, phi_bb264_15, phi_bb264_16, phi_bb264_20, phi_bb264_20});
  }

  TNode<IntPtrT> phi_bb268_7;
  TNode<FixedArray> phi_bb268_9;
  TNode<IntPtrT> phi_bb268_10;
  TNode<IntPtrT> phi_bb268_11;
  TNode<BoolT> phi_bb268_12;
  TNode<PrimitiveHeapObject> phi_bb268_13;
  TNode<UintPtrT> phi_bb268_15;
  TNode<IntPtrT> phi_bb268_16;
  TNode<IntPtrT> phi_bb268_20;
  TNode<IntPtrT> phi_bb268_23;
  if (block268.is_used()) {
    ca_.Bind(&block268, &phi_bb268_7, &phi_bb268_9, &phi_bb268_10, &phi_bb268_11, &phi_bb268_12, &phi_bb268_13, &phi_bb268_15, &phi_bb268_16, &phi_bb268_20, &phi_bb268_23);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb269_7;
  TNode<FixedArray> phi_bb269_9;
  TNode<IntPtrT> phi_bb269_10;
  TNode<IntPtrT> phi_bb269_11;
  TNode<BoolT> phi_bb269_12;
  TNode<PrimitiveHeapObject> phi_bb269_13;
  TNode<UintPtrT> phi_bb269_15;
  TNode<IntPtrT> phi_bb269_16;
  TNode<IntPtrT> phi_bb269_20;
  TNode<IntPtrT> phi_bb269_23;
  TNode<IntPtrT> tmp355;
  if (block269.is_used()) {
    ca_.Bind(&block269, &phi_bb269_7, &phi_bb269_9, &phi_bb269_10, &phi_bb269_11, &phi_bb269_12, &phi_bb269_13, &phi_bb269_15, &phi_bb269_16, &phi_bb269_20, &phi_bb269_23);
    tmp355 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb269_11}, TNode<IntPtrT>{tmp352});
    ca_.Branch(tmp346, &block270, std::vector<compiler::Node*>{phi_bb269_7, phi_bb269_9, phi_bb269_10, phi_bb269_12, phi_bb269_13, phi_bb269_15, phi_bb269_16, phi_bb269_20, phi_bb269_23}, &block271, std::vector<compiler::Node*>{phi_bb269_7, phi_bb269_9, phi_bb269_10, phi_bb269_12, phi_bb269_13, phi_bb269_15, phi_bb269_16, phi_bb269_20, phi_bb269_23});
  }

  TNode<IntPtrT> phi_bb270_7;
  TNode<FixedArray> phi_bb270_9;
  TNode<IntPtrT> phi_bb270_10;
  TNode<BoolT> phi_bb270_12;
  TNode<PrimitiveHeapObject> phi_bb270_13;
  TNode<UintPtrT> phi_bb270_15;
  TNode<IntPtrT> phi_bb270_16;
  TNode<IntPtrT> phi_bb270_20;
  TNode<IntPtrT> phi_bb270_23;
  TNode<Smi> tmp356;
  TNode<IntPtrT> tmp357;
  TNode<IntPtrT> tmp358;
  TNode<BoolT> tmp359;
  if (block270.is_used()) {
    ca_.Bind(&block270, &phi_bb270_7, &phi_bb270_9, &phi_bb270_10, &phi_bb270_12, &phi_bb270_13, &phi_bb270_15, &phi_bb270_16, &phi_bb270_20, &phi_bb270_23);
    tmp356 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb270_23});
    tmp357 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb270_9});
    tmp358 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp359 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb270_10}, TNode<IntPtrT>{tmp358});
    ca_.Branch(tmp359, &block273, std::vector<compiler::Node*>{phi_bb270_7, phi_bb270_9, phi_bb270_10, phi_bb270_12, phi_bb270_13, phi_bb270_15, phi_bb270_16, phi_bb270_20, phi_bb270_23}, &block274, std::vector<compiler::Node*>{phi_bb270_7, phi_bb270_9, phi_bb270_10, phi_bb270_12, phi_bb270_13, phi_bb270_15, phi_bb270_16, phi_bb270_20, phi_bb270_23});
  }

  TNode<IntPtrT> phi_bb274_7;
  TNode<FixedArray> phi_bb274_9;
  TNode<IntPtrT> phi_bb274_10;
  TNode<BoolT> phi_bb274_12;
  TNode<PrimitiveHeapObject> phi_bb274_13;
  TNode<UintPtrT> phi_bb274_15;
  TNode<IntPtrT> phi_bb274_16;
  TNode<IntPtrT> phi_bb274_20;
  TNode<IntPtrT> phi_bb274_23;
  if (block274.is_used()) {
    ca_.Bind(&block274, &phi_bb274_7, &phi_bb274_9, &phi_bb274_10, &phi_bb274_12, &phi_bb274_13, &phi_bb274_15, &phi_bb274_16, &phi_bb274_20, &phi_bb274_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb273_7;
  TNode<FixedArray> phi_bb273_9;
  TNode<IntPtrT> phi_bb273_10;
  TNode<BoolT> phi_bb273_12;
  TNode<PrimitiveHeapObject> phi_bb273_13;
  TNode<UintPtrT> phi_bb273_15;
  TNode<IntPtrT> phi_bb273_16;
  TNode<IntPtrT> phi_bb273_20;
  TNode<IntPtrT> phi_bb273_23;
  TNode<BoolT> tmp360;
  if (block273.is_used()) {
    ca_.Bind(&block273, &phi_bb273_7, &phi_bb273_9, &phi_bb273_10, &phi_bb273_12, &phi_bb273_13, &phi_bb273_15, &phi_bb273_16, &phi_bb273_20, &phi_bb273_23);
    tmp360 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb273_10}, TNode<IntPtrT>{tmp357});
    ca_.Branch(tmp360, &block275, std::vector<compiler::Node*>{phi_bb273_7, phi_bb273_9, phi_bb273_10, phi_bb273_12, phi_bb273_13, phi_bb273_15, phi_bb273_16, phi_bb273_20, phi_bb273_23}, &block276, std::vector<compiler::Node*>{phi_bb273_7, phi_bb273_9, phi_bb273_10, phi_bb273_12, phi_bb273_13, phi_bb273_15, phi_bb273_16, phi_bb273_20, phi_bb273_23});
  }

  TNode<IntPtrT> phi_bb276_7;
  TNode<FixedArray> phi_bb276_9;
  TNode<IntPtrT> phi_bb276_10;
  TNode<BoolT> phi_bb276_12;
  TNode<PrimitiveHeapObject> phi_bb276_13;
  TNode<UintPtrT> phi_bb276_15;
  TNode<IntPtrT> phi_bb276_16;
  TNode<IntPtrT> phi_bb276_20;
  TNode<IntPtrT> phi_bb276_23;
  if (block276.is_used()) {
    ca_.Bind(&block276, &phi_bb276_7, &phi_bb276_9, &phi_bb276_10, &phi_bb276_12, &phi_bb276_13, &phi_bb276_15, &phi_bb276_16, &phi_bb276_20, &phi_bb276_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb275_7;
  TNode<FixedArray> phi_bb275_9;
  TNode<IntPtrT> phi_bb275_10;
  TNode<BoolT> phi_bb275_12;
  TNode<PrimitiveHeapObject> phi_bb275_13;
  TNode<UintPtrT> phi_bb275_15;
  TNode<IntPtrT> phi_bb275_16;
  TNode<IntPtrT> phi_bb275_20;
  TNode<IntPtrT> phi_bb275_23;
  TNode<BoolT> tmp361;
  if (block275.is_used()) {
    ca_.Bind(&block275, &phi_bb275_7, &phi_bb275_9, &phi_bb275_10, &phi_bb275_12, &phi_bb275_13, &phi_bb275_15, &phi_bb275_16, &phi_bb275_20, &phi_bb275_23);
    tmp361 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb275_10}, TNode<IntPtrT>{tmp357});
    ca_.Branch(tmp361, &block277, std::vector<compiler::Node*>{phi_bb275_7, phi_bb275_9, phi_bb275_10, phi_bb275_12, phi_bb275_13, phi_bb275_15, phi_bb275_16, phi_bb275_20, phi_bb275_23}, &block278, std::vector<compiler::Node*>{phi_bb275_7, phi_bb275_9, phi_bb275_10, phi_bb275_12, phi_bb275_13, phi_bb275_15, phi_bb275_16, phi_bb275_20, phi_bb275_23});
  }

  TNode<IntPtrT> phi_bb277_7;
  TNode<FixedArray> phi_bb277_9;
  TNode<IntPtrT> phi_bb277_10;
  TNode<BoolT> phi_bb277_12;
  TNode<PrimitiveHeapObject> phi_bb277_13;
  TNode<UintPtrT> phi_bb277_15;
  TNode<IntPtrT> phi_bb277_16;
  TNode<IntPtrT> phi_bb277_20;
  TNode<IntPtrT> phi_bb277_23;
  TNode<Union<HeapObject, TaggedIndex>> tmp362;
  TNode<IntPtrT> tmp363;
  TNode<IntPtrT> tmp364;
  TNode<IntPtrT> tmp365;
  TNode<IntPtrT> tmp366;
  TNode<UintPtrT> tmp367;
  TNode<UintPtrT> tmp368;
  TNode<BoolT> tmp369;
  if (block277.is_used()) {
    ca_.Bind(&block277, &phi_bb277_7, &phi_bb277_9, &phi_bb277_10, &phi_bb277_12, &phi_bb277_13, &phi_bb277_15, &phi_bb277_16, &phi_bb277_20, &phi_bb277_23);
    std::tie(tmp362, tmp363, tmp364) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb277_9}).Flatten();
    tmp365 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp366 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb277_10}, TNode<IntPtrT>{tmp365});
    tmp367 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb277_10});
    tmp368 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp364});
    tmp369 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp367}, TNode<UintPtrT>{tmp368});
    ca_.Branch(tmp369, &block284, std::vector<compiler::Node*>{phi_bb277_7, phi_bb277_9, phi_bb277_12, phi_bb277_13, phi_bb277_15, phi_bb277_16, phi_bb277_20, phi_bb277_23, phi_bb277_9, phi_bb277_10, phi_bb277_10, phi_bb277_10, phi_bb277_10}, &block285, std::vector<compiler::Node*>{phi_bb277_7, phi_bb277_9, phi_bb277_12, phi_bb277_13, phi_bb277_15, phi_bb277_16, phi_bb277_20, phi_bb277_23, phi_bb277_9, phi_bb277_10, phi_bb277_10, phi_bb277_10, phi_bb277_10});
  }

  TNode<IntPtrT> phi_bb284_7;
  TNode<FixedArray> phi_bb284_9;
  TNode<BoolT> phi_bb284_12;
  TNode<PrimitiveHeapObject> phi_bb284_13;
  TNode<UintPtrT> phi_bb284_15;
  TNode<IntPtrT> phi_bb284_16;
  TNode<IntPtrT> phi_bb284_20;
  TNode<IntPtrT> phi_bb284_23;
  TNode<FixedArray> phi_bb284_28;
  TNode<IntPtrT> phi_bb284_32;
  TNode<IntPtrT> phi_bb284_33;
  TNode<IntPtrT> phi_bb284_37;
  TNode<IntPtrT> phi_bb284_38;
  TNode<IntPtrT> tmp370;
  TNode<IntPtrT> tmp371;
  TNode<Union<HeapObject, TaggedIndex>> tmp372;
  TNode<IntPtrT> tmp373;
  if (block284.is_used()) {
    ca_.Bind(&block284, &phi_bb284_7, &phi_bb284_9, &phi_bb284_12, &phi_bb284_13, &phi_bb284_15, &phi_bb284_16, &phi_bb284_20, &phi_bb284_23, &phi_bb284_28, &phi_bb284_32, &phi_bb284_33, &phi_bb284_37, &phi_bb284_38);
    tmp370 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb284_38});
    tmp371 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp363}, TNode<IntPtrT>{tmp370});
    std::tie(tmp372, tmp373) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp362}, TNode<IntPtrT>{tmp371}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp372, tmp373}, tmp356);
    ca_.Goto(&block279, phi_bb284_7, phi_bb284_9, tmp366, phi_bb284_12, phi_bb284_13, phi_bb284_15, phi_bb284_16, phi_bb284_20, phi_bb284_23);
  }

  TNode<IntPtrT> phi_bb285_7;
  TNode<FixedArray> phi_bb285_9;
  TNode<BoolT> phi_bb285_12;
  TNode<PrimitiveHeapObject> phi_bb285_13;
  TNode<UintPtrT> phi_bb285_15;
  TNode<IntPtrT> phi_bb285_16;
  TNode<IntPtrT> phi_bb285_20;
  TNode<IntPtrT> phi_bb285_23;
  TNode<FixedArray> phi_bb285_28;
  TNode<IntPtrT> phi_bb285_32;
  TNode<IntPtrT> phi_bb285_33;
  TNode<IntPtrT> phi_bb285_37;
  TNode<IntPtrT> phi_bb285_38;
  if (block285.is_used()) {
    ca_.Bind(&block285, &phi_bb285_7, &phi_bb285_9, &phi_bb285_12, &phi_bb285_13, &phi_bb285_15, &phi_bb285_16, &phi_bb285_20, &phi_bb285_23, &phi_bb285_28, &phi_bb285_32, &phi_bb285_33, &phi_bb285_37, &phi_bb285_38);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb278_7;
  TNode<FixedArray> phi_bb278_9;
  TNode<IntPtrT> phi_bb278_10;
  TNode<BoolT> phi_bb278_12;
  TNode<PrimitiveHeapObject> phi_bb278_13;
  TNode<UintPtrT> phi_bb278_15;
  TNode<IntPtrT> phi_bb278_16;
  TNode<IntPtrT> phi_bb278_20;
  TNode<IntPtrT> phi_bb278_23;
  TNode<IntPtrT> tmp374;
  TNode<IntPtrT> tmp375;
  TNode<BoolT> tmp376;
  if (block278.is_used()) {
    ca_.Bind(&block278, &phi_bb278_7, &phi_bb278_9, &phi_bb278_10, &phi_bb278_12, &phi_bb278_13, &phi_bb278_15, &phi_bb278_16, &phi_bb278_20, &phi_bb278_23);
    tmp374 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp357});
    tmp375 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp376 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp374}, TNode<IntPtrT>{tmp375});
    ca_.Branch(tmp376, &block288, std::vector<compiler::Node*>{phi_bb278_7, phi_bb278_9, phi_bb278_10, phi_bb278_12, phi_bb278_13, phi_bb278_15, phi_bb278_16, phi_bb278_20, phi_bb278_23}, &block289, std::vector<compiler::Node*>{phi_bb278_7, phi_bb278_9, phi_bb278_10, phi_bb278_12, phi_bb278_13, phi_bb278_15, phi_bb278_16, phi_bb278_20, phi_bb278_23});
  }

  TNode<IntPtrT> phi_bb288_7;
  TNode<FixedArray> phi_bb288_9;
  TNode<IntPtrT> phi_bb288_10;
  TNode<BoolT> phi_bb288_12;
  TNode<PrimitiveHeapObject> phi_bb288_13;
  TNode<UintPtrT> phi_bb288_15;
  TNode<IntPtrT> phi_bb288_16;
  TNode<IntPtrT> phi_bb288_20;
  TNode<IntPtrT> phi_bb288_23;
  TNode<IntPtrT> tmp377;
  if (block288.is_used()) {
    ca_.Bind(&block288, &phi_bb288_7, &phi_bb288_9, &phi_bb288_10, &phi_bb288_12, &phi_bb288_13, &phi_bb288_15, &phi_bb288_16, &phi_bb288_20, &phi_bb288_23);
    tmp377 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block290, phi_bb288_7, phi_bb288_9, phi_bb288_10, phi_bb288_12, phi_bb288_13, phi_bb288_15, phi_bb288_16, phi_bb288_20, phi_bb288_23, tmp377);
  }

  TNode<IntPtrT> phi_bb289_7;
  TNode<FixedArray> phi_bb289_9;
  TNode<IntPtrT> phi_bb289_10;
  TNode<BoolT> phi_bb289_12;
  TNode<PrimitiveHeapObject> phi_bb289_13;
  TNode<UintPtrT> phi_bb289_15;
  TNode<IntPtrT> phi_bb289_16;
  TNode<IntPtrT> phi_bb289_20;
  TNode<IntPtrT> phi_bb289_23;
  if (block289.is_used()) {
    ca_.Bind(&block289, &phi_bb289_7, &phi_bb289_9, &phi_bb289_10, &phi_bb289_12, &phi_bb289_13, &phi_bb289_15, &phi_bb289_16, &phi_bb289_20, &phi_bb289_23);
    ca_.Goto(&block290, phi_bb289_7, phi_bb289_9, phi_bb289_10, phi_bb289_12, phi_bb289_13, phi_bb289_15, phi_bb289_16, phi_bb289_20, phi_bb289_23, tmp374);
  }

  TNode<IntPtrT> phi_bb290_7;
  TNode<FixedArray> phi_bb290_9;
  TNode<IntPtrT> phi_bb290_10;
  TNode<BoolT> phi_bb290_12;
  TNode<PrimitiveHeapObject> phi_bb290_13;
  TNode<UintPtrT> phi_bb290_15;
  TNode<IntPtrT> phi_bb290_16;
  TNode<IntPtrT> phi_bb290_20;
  TNode<IntPtrT> phi_bb290_23;
  TNode<IntPtrT> phi_bb290_29;
  TNode<IntPtrT> tmp378;
  TNode<BoolT> tmp379;
  if (block290.is_used()) {
    ca_.Bind(&block290, &phi_bb290_7, &phi_bb290_9, &phi_bb290_10, &phi_bb290_12, &phi_bb290_13, &phi_bb290_15, &phi_bb290_16, &phi_bb290_20, &phi_bb290_23, &phi_bb290_29);
    tmp378 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp379 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb290_29}, TNode<IntPtrT>{tmp378});
    ca_.Branch(tmp379, &block292, std::vector<compiler::Node*>{phi_bb290_7, phi_bb290_9, phi_bb290_10, phi_bb290_12, phi_bb290_13, phi_bb290_15, phi_bb290_16, phi_bb290_20, phi_bb290_23}, &block293, std::vector<compiler::Node*>{phi_bb290_7, phi_bb290_9, phi_bb290_10, phi_bb290_12, phi_bb290_13, phi_bb290_15, phi_bb290_16, phi_bb290_20, phi_bb290_23});
  }

  TNode<IntPtrT> phi_bb293_7;
  TNode<FixedArray> phi_bb293_9;
  TNode<IntPtrT> phi_bb293_10;
  TNode<BoolT> phi_bb293_12;
  TNode<PrimitiveHeapObject> phi_bb293_13;
  TNode<UintPtrT> phi_bb293_15;
  TNode<IntPtrT> phi_bb293_16;
  TNode<IntPtrT> phi_bb293_20;
  TNode<IntPtrT> phi_bb293_23;
  if (block293.is_used()) {
    ca_.Bind(&block293, &phi_bb293_7, &phi_bb293_9, &phi_bb293_10, &phi_bb293_12, &phi_bb293_13, &phi_bb293_15, &phi_bb293_16, &phi_bb293_20, &phi_bb293_23);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb292_7;
  TNode<FixedArray> phi_bb292_9;
  TNode<IntPtrT> phi_bb292_10;
  TNode<BoolT> phi_bb292_12;
  TNode<PrimitiveHeapObject> phi_bb292_13;
  TNode<UintPtrT> phi_bb292_15;
  TNode<IntPtrT> phi_bb292_16;
  TNode<IntPtrT> phi_bb292_20;
  TNode<IntPtrT> phi_bb292_23;
  TNode<FixedArray> tmp380;
  TNode<Union<HeapObject, TaggedIndex>> tmp381;
  TNode<IntPtrT> tmp382;
  TNode<IntPtrT> tmp383;
  TNode<UintPtrT> tmp384;
  TNode<IntPtrT> tmp385;
  TNode<UintPtrT> tmp386;
  TNode<UintPtrT> tmp387;
  TNode<BoolT> tmp388;
  if (block292.is_used()) {
    ca_.Bind(&block292, &phi_bb292_7, &phi_bb292_9, &phi_bb292_10, &phi_bb292_12, &phi_bb292_13, &phi_bb292_15, &phi_bb292_16, &phi_bb292_20, &phi_bb292_23);
    tmp380 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb290_29});
    std::tie(tmp381, tmp382, tmp383) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb292_9}).Flatten();
    tmp384 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp385 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp384});
    tmp386 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp385});
    tmp387 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp383});
    tmp388 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp386}, TNode<UintPtrT>{tmp387});
    ca_.Branch(tmp388, &block299, std::vector<compiler::Node*>{phi_bb292_7, phi_bb292_9, phi_bb292_10, phi_bb292_12, phi_bb292_13, phi_bb292_15, phi_bb292_16, phi_bb292_20, phi_bb292_23, phi_bb292_9}, &block300, std::vector<compiler::Node*>{phi_bb292_7, phi_bb292_9, phi_bb292_10, phi_bb292_12, phi_bb292_13, phi_bb292_15, phi_bb292_16, phi_bb292_20, phi_bb292_23, phi_bb292_9});
  }

  TNode<IntPtrT> phi_bb299_7;
  TNode<FixedArray> phi_bb299_9;
  TNode<IntPtrT> phi_bb299_10;
  TNode<BoolT> phi_bb299_12;
  TNode<PrimitiveHeapObject> phi_bb299_13;
  TNode<UintPtrT> phi_bb299_15;
  TNode<IntPtrT> phi_bb299_16;
  TNode<IntPtrT> phi_bb299_20;
  TNode<IntPtrT> phi_bb299_23;
  TNode<FixedArray> phi_bb299_31;
  TNode<IntPtrT> tmp389;
  TNode<IntPtrT> tmp390;
  TNode<Union<HeapObject, TaggedIndex>> tmp391;
  TNode<IntPtrT> tmp392;
  TNode<Union<HeapObject, TaggedIndex>> tmp393;
  TNode<IntPtrT> tmp394;
  TNode<IntPtrT> tmp395;
  TNode<UintPtrT> tmp396;
  TNode<IntPtrT> tmp397;
  TNode<UintPtrT> tmp398;
  TNode<UintPtrT> tmp399;
  TNode<BoolT> tmp400;
  if (block299.is_used()) {
    ca_.Bind(&block299, &phi_bb299_7, &phi_bb299_9, &phi_bb299_10, &phi_bb299_12, &phi_bb299_13, &phi_bb299_15, &phi_bb299_16, &phi_bb299_20, &phi_bb299_23, &phi_bb299_31);
    tmp389 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp385});
    tmp390 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp382}, TNode<IntPtrT>{tmp389});
    std::tie(tmp391, tmp392) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp381}, TNode<IntPtrT>{tmp390}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp391, tmp392}, tmp380);
    std::tie(tmp393, tmp394, tmp395) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp380}).Flatten();
    tmp396 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp397 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp396});
    tmp398 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp397});
    tmp399 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp395});
    tmp400 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp398}, TNode<UintPtrT>{tmp399});
    ca_.Branch(tmp400, &block308, std::vector<compiler::Node*>{phi_bb299_7, phi_bb299_9, phi_bb299_10, phi_bb299_12, phi_bb299_13, phi_bb299_15, phi_bb299_16, phi_bb299_20, phi_bb299_23}, &block309, std::vector<compiler::Node*>{phi_bb299_7, phi_bb299_9, phi_bb299_10, phi_bb299_12, phi_bb299_13, phi_bb299_15, phi_bb299_16, phi_bb299_20, phi_bb299_23});
  }

  TNode<IntPtrT> phi_bb300_7;
  TNode<FixedArray> phi_bb300_9;
  TNode<IntPtrT> phi_bb300_10;
  TNode<BoolT> phi_bb300_12;
  TNode<PrimitiveHeapObject> phi_bb300_13;
  TNode<UintPtrT> phi_bb300_15;
  TNode<IntPtrT> phi_bb300_16;
  TNode<IntPtrT> phi_bb300_20;
  TNode<IntPtrT> phi_bb300_23;
  TNode<FixedArray> phi_bb300_31;
  if (block300.is_used()) {
    ca_.Bind(&block300, &phi_bb300_7, &phi_bb300_9, &phi_bb300_10, &phi_bb300_12, &phi_bb300_13, &phi_bb300_15, &phi_bb300_16, &phi_bb300_20, &phi_bb300_23, &phi_bb300_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb308_7;
  TNode<FixedArray> phi_bb308_9;
  TNode<IntPtrT> phi_bb308_10;
  TNode<BoolT> phi_bb308_12;
  TNode<PrimitiveHeapObject> phi_bb308_13;
  TNode<UintPtrT> phi_bb308_15;
  TNode<IntPtrT> phi_bb308_16;
  TNode<IntPtrT> phi_bb308_20;
  TNode<IntPtrT> phi_bb308_23;
  TNode<IntPtrT> tmp401;
  TNode<IntPtrT> tmp402;
  TNode<Union<HeapObject, TaggedIndex>> tmp403;
  TNode<IntPtrT> tmp404;
  TNode<Undefined> tmp405;
  TNode<Union<HeapObject, TaggedIndex>> tmp406;
  TNode<IntPtrT> tmp407;
  TNode<IntPtrT> tmp408;
  TNode<UintPtrT> tmp409;
  TNode<IntPtrT> tmp410;
  TNode<UintPtrT> tmp411;
  TNode<UintPtrT> tmp412;
  TNode<BoolT> tmp413;
  if (block308.is_used()) {
    ca_.Bind(&block308, &phi_bb308_7, &phi_bb308_9, &phi_bb308_10, &phi_bb308_12, &phi_bb308_13, &phi_bb308_15, &phi_bb308_16, &phi_bb308_20, &phi_bb308_23);
    tmp401 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp397});
    tmp402 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp394}, TNode<IntPtrT>{tmp401});
    std::tie(tmp403, tmp404) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp393}, TNode<IntPtrT>{tmp402}).Flatten();
    tmp405 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp403, tmp404}, tmp405);
    std::tie(tmp406, tmp407, tmp408) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp380}).Flatten();
    tmp409 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp410 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp409});
    tmp411 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp410});
    tmp412 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp408});
    tmp413 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp411}, TNode<UintPtrT>{tmp412});
    ca_.Branch(tmp413, &block317, std::vector<compiler::Node*>{phi_bb308_7, phi_bb308_9, phi_bb308_10, phi_bb308_12, phi_bb308_13, phi_bb308_15, phi_bb308_16, phi_bb308_20, phi_bb308_23}, &block318, std::vector<compiler::Node*>{phi_bb308_7, phi_bb308_9, phi_bb308_10, phi_bb308_12, phi_bb308_13, phi_bb308_15, phi_bb308_16, phi_bb308_20, phi_bb308_23});
  }

  TNode<IntPtrT> phi_bb309_7;
  TNode<FixedArray> phi_bb309_9;
  TNode<IntPtrT> phi_bb309_10;
  TNode<BoolT> phi_bb309_12;
  TNode<PrimitiveHeapObject> phi_bb309_13;
  TNode<UintPtrT> phi_bb309_15;
  TNode<IntPtrT> phi_bb309_16;
  TNode<IntPtrT> phi_bb309_20;
  TNode<IntPtrT> phi_bb309_23;
  if (block309.is_used()) {
    ca_.Bind(&block309, &phi_bb309_7, &phi_bb309_9, &phi_bb309_10, &phi_bb309_12, &phi_bb309_13, &phi_bb309_15, &phi_bb309_16, &phi_bb309_20, &phi_bb309_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb317_7;
  TNode<FixedArray> phi_bb317_9;
  TNode<IntPtrT> phi_bb317_10;
  TNode<BoolT> phi_bb317_12;
  TNode<PrimitiveHeapObject> phi_bb317_13;
  TNode<UintPtrT> phi_bb317_15;
  TNode<IntPtrT> phi_bb317_16;
  TNode<IntPtrT> phi_bb317_20;
  TNode<IntPtrT> phi_bb317_23;
  TNode<IntPtrT> tmp414;
  TNode<IntPtrT> tmp415;
  TNode<Union<HeapObject, TaggedIndex>> tmp416;
  TNode<IntPtrT> tmp417;
  TNode<IntPtrT> tmp418;
  if (block317.is_used()) {
    ca_.Bind(&block317, &phi_bb317_7, &phi_bb317_9, &phi_bb317_10, &phi_bb317_12, &phi_bb317_13, &phi_bb317_15, &phi_bb317_16, &phi_bb317_20, &phi_bb317_23);
    tmp414 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp410});
    tmp415 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp407}, TNode<IntPtrT>{tmp414});
    std::tie(tmp416, tmp417) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp406}, TNode<IntPtrT>{tmp415}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp416, tmp417}, tmp356);
    tmp418 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block279, phi_bb317_7, tmp380, tmp418, phi_bb317_12, phi_bb317_13, phi_bb317_15, phi_bb317_16, phi_bb317_20, phi_bb317_23);
  }

  TNode<IntPtrT> phi_bb318_7;
  TNode<FixedArray> phi_bb318_9;
  TNode<IntPtrT> phi_bb318_10;
  TNode<BoolT> phi_bb318_12;
  TNode<PrimitiveHeapObject> phi_bb318_13;
  TNode<UintPtrT> phi_bb318_15;
  TNode<IntPtrT> phi_bb318_16;
  TNode<IntPtrT> phi_bb318_20;
  TNode<IntPtrT> phi_bb318_23;
  if (block318.is_used()) {
    ca_.Bind(&block318, &phi_bb318_7, &phi_bb318_9, &phi_bb318_10, &phi_bb318_12, &phi_bb318_13, &phi_bb318_15, &phi_bb318_16, &phi_bb318_20, &phi_bb318_23);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb279_7;
  TNode<FixedArray> phi_bb279_9;
  TNode<IntPtrT> phi_bb279_10;
  TNode<BoolT> phi_bb279_12;
  TNode<PrimitiveHeapObject> phi_bb279_13;
  TNode<UintPtrT> phi_bb279_15;
  TNode<IntPtrT> phi_bb279_16;
  TNode<IntPtrT> phi_bb279_20;
  TNode<IntPtrT> phi_bb279_23;
  TNode<Null> tmp419;
  if (block279.is_used()) {
    ca_.Bind(&block279, &phi_bb279_7, &phi_bb279_9, &phi_bb279_10, &phi_bb279_12, &phi_bb279_13, &phi_bb279_15, &phi_bb279_16, &phi_bb279_20, &phi_bb279_23);
    tmp419 = Null_0(state_);
    ca_.Goto(&block271, phi_bb279_7, phi_bb279_9, phi_bb279_10, phi_bb279_12, tmp419, phi_bb279_15, phi_bb279_16, phi_bb279_20, phi_bb279_23);
  }

  TNode<IntPtrT> phi_bb271_7;
  TNode<FixedArray> phi_bb271_9;
  TNode<IntPtrT> phi_bb271_10;
  TNode<BoolT> phi_bb271_12;
  TNode<PrimitiveHeapObject> phi_bb271_13;
  TNode<UintPtrT> phi_bb271_15;
  TNode<IntPtrT> phi_bb271_16;
  TNode<IntPtrT> phi_bb271_20;
  TNode<IntPtrT> phi_bb271_23;
  if (block271.is_used()) {
    ca_.Bind(&block271, &phi_bb271_7, &phi_bb271_9, &phi_bb271_10, &phi_bb271_12, &phi_bb271_13, &phi_bb271_15, &phi_bb271_16, &phi_bb271_20, &phi_bb271_23);
    ca_.Goto(&block262, phi_bb271_7, phi_bb271_9, phi_bb271_10, tmp355, phi_bb271_12, phi_bb271_13, phi_bb271_15, phi_bb271_16, phi_bb271_20);
  }

  TNode<IntPtrT> phi_bb262_7;
  TNode<FixedArray> phi_bb262_9;
  TNode<IntPtrT> phi_bb262_10;
  TNode<IntPtrT> phi_bb262_11;
  TNode<BoolT> phi_bb262_12;
  TNode<PrimitiveHeapObject> phi_bb262_13;
  TNode<UintPtrT> phi_bb262_15;
  TNode<IntPtrT> phi_bb262_16;
  TNode<IntPtrT> phi_bb262_20;
  TNode<String> tmp420;
  if (block262.is_used()) {
    ca_.Bind(&block262, &phi_bb262_7, &phi_bb262_9, &phi_bb262_10, &phi_bb262_11, &phi_bb262_12, &phi_bb262_13, &phi_bb262_15, &phi_bb262_16, &phi_bb262_20);
    tmp420 = BufferJoin_0(state_, TNode<Context>{p_context}, TorqueStructBuffer_0{TNode<FixedArray>{tmp5}, TNode<FixedArray>{phi_bb262_9}, TNode<IntPtrT>{phi_bb262_10}, TNode<IntPtrT>{phi_bb262_11}, TNode<BoolT>{phi_bb262_12}, TNode<PrimitiveHeapObject>{phi_bb262_13}}, TNode<String>{p_sep});
    ca_.Goto(&block321);
  }

    ca_.Bind(&block321);
  return TNode<String>{tmp420};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=516&c=1
TNode<JSAny> ArrayJoin_JSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, bool p_useToLocaleString, TNode<JSReceiver> p_receiver, TNode<String> p_sep, TNode<Number> p_lenNumber, TNode<JSAny> p_locales, TNode<JSAny> p_options) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<Int32T> tmp2;
  TNode<JSArray> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_receiver, tmp0});
    tmp2 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp1});
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_JSArray_0(state_, TNode<HeapObject>{p_receiver}, &label4);
    ca_.Goto(&block4);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block3);
  }

  TNode<IntPtrT> tmp5;
  TNode<Number> tmp6;
  TNode<BoolT> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp6 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{tmp3, tmp5});
    tmp7 = IsNumberNotEqual_0(state_, TNode<Number>{tmp6}, TNode<Number>{p_lenNumber});
    ca_.Branch(tmp7, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block3);
  }

  TNode<BoolT> tmp8;
  TNode<BoolT> tmp9;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp8 = CodeStubAssembler(state_).IsPrototypeInitialArrayPrototype(TNode<Context>{p_context}, TNode<Map>{tmp1});
    tmp9 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp8});
    ca_.Branch(tmp9, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block3);
  }

  TNode<BoolT> tmp10;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp10 = CodeStubAssembler(state_).IsNoElementsProtectorCellInvalid();
    ca_.Branch(tmp10, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block10.is_used()) {
    ca_.Bind(&block10);
    ca_.Goto(&block3);
  }

  TNode<BoolT> tmp11;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp11 = CodeStubAssembler(state_).IsElementsKindLessThanOrEqual(TNode<Int32T>{tmp2}, CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_ELEMENTS));
    ca_.Branch(tmp11, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    ca_.Goto(&block14, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_FastSmiOrObjectElements_0)));
  }

  TNode<BoolT> tmp12;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp12 = CodeStubAssembler(state_).IsElementsKindLessThanOrEqual(TNode<Int32T>{tmp2}, CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_DOUBLE_ELEMENTS));
    ca_.Branch(tmp12, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block15.is_used()) {
    ca_.Bind(&block15);
    ca_.Goto(&block17, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_FastDoubleElements_0)));
  }

  TNode<BoolT> tmp13;
  if (block16.is_used()) {
    ca_.Bind(&block16);
    tmp13 = CodeStubAssembler(state_).IsElementsKindLessThanOrEqual(TNode<Int32T>{tmp2}, CastIfEnumClass<ElementsKind>(ElementsKind::LAST_ANY_NONEXTENSIBLE_ELEMENTS_KIND));
    ca_.Branch(tmp13, &block18, std::vector<compiler::Node*>{}, &block19, std::vector<compiler::Node*>{});
  }

  if (block18.is_used()) {
    ca_.Bind(&block18);
    ca_.Goto(&block20, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_FastSmiOrObjectElements_0)));
  }

  TNode<Int32T> tmp14;
  TNode<BoolT> tmp15;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    tmp14 = FromConstexpr_ElementsKind_constexpr_DICTIONARY_ELEMENTS_0(state_, ElementsKind::DICTIONARY_ELEMENTS);
    tmp15 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp14});
    ca_.Branch(tmp15, &block21, std::vector<compiler::Node*>{}, &block22, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp16;
  TNode<FixedArrayBase> tmp17;
  TNode<NumberDictionary> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<BoolT> tmp21;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp16 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp17 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp16});
    tmp18 = UnsafeCast_NumberDictionary_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp17});
    tmp19 = CodeStubAssembler(state_).GetNumberDictionaryNumberOfElements(TNode<NumberDictionary>{tmp18});
    tmp20 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp21 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp19}, TNode<Smi>{tmp20});
    ca_.Branch(tmp21, &block24, std::vector<compiler::Node*>{}, &block25, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp22;
  TNode<BoolT> tmp23;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp22 = kEmptyString_0(state_);
    tmp23 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{p_sep}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp22});
    ca_.Branch(tmp23, &block27, std::vector<compiler::Node*>{}, &block28, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp24;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp24 = kEmptyString_0(state_);
    ca_.Goto(&block1, tmp24);
  }

  TNode<Number> tmp25;
  TNode<Number> tmp26;
  TNode<Smi> tmp27;
  if (block28.is_used()) {
    ca_.Bind(&block28);
    tmp25 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp26 = CodeStubAssembler(state_).NumberSub(TNode<Number>{p_lenNumber}, TNode<Number>{tmp25});
    compiler::CodeAssemblerLabel label28(&ca_);
    tmp27 = Cast_Smi_0(state_, TNode<Object>{tmp26}, &label28);
    ca_.Goto(&block31);
    if (label28.is_used()) {
      ca_.Bind(&label28);
      ca_.Goto(&block32);
    }
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> tmp29;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp29 = ca_.CallBuiltin<String>(Builtin::kStringRepeat, p_context, p_sep, tmp27);
    ca_.Goto(&block1, tmp29);
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    ca_.Goto(&block20, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_DictionaryElements_0)));
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block3);
  }

  TNode<BuiltinPtr> phi_bb20_8;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_8);
    ca_.Goto(&block17, phi_bb20_8);
  }

  TNode<BuiltinPtr> phi_bb17_8;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_8);
    ca_.Goto(&block14, phi_bb17_8);
  }

  TNode<BuiltinPtr> phi_bb14_8;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_8);
    ca_.Goto(&block2, phi_bb14_8);
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block2, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_GenericElementsAccessor_0)));
  }

  TNode<BuiltinPtr> phi_bb2_8;
  TNode<String> tmp30;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_8);
    tmp30 = ArrayJoinImpl_JSArray_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver}, TNode<String>{p_sep}, TNode<Number>{p_lenNumber}, p_useToLocaleString, TNode<JSAny>{p_locales}, TNode<JSAny>{p_options}, TNode<BuiltinPtr>{phi_bb2_8});
    ca_.Goto(&block1, tmp30);
  }

  TNode<JSAny> phi_bb1_6;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_6);
    ca_.Goto(&block33, phi_bb1_6);
  }

  TNode<JSAny> phi_bb33_6;
    ca_.Bind(&block33, &phi_bb33_6);
  return TNode<JSAny>{phi_bb33_6};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=566&c=1
TNode<JSAny> ArrayJoin_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, bool p_useToLocaleString, TNode<JSReceiver> p_receiver, TNode<String> p_sep, TNode<Number> p_lenNumber, TNode<JSAny> p_locales, TNode<JSAny> p_options) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block75(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block73(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BuiltinPtr> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block77(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<Int32T> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_receiver, tmp0});
    tmp2 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp1});
    tmp3 = CodeStubAssembler(state_).IsElementsKindGreaterThan(TNode<Int32T>{tmp2}, CastIfEnumClass<ElementsKind>(ElementsKind::UINT32_ELEMENTS));
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<Int32T> tmp4;
  TNode<BoolT> tmp5;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = FromConstexpr_ElementsKind_constexpr_INT32_ELEMENTS_0(state_, ElementsKind::INT32_ELEMENTS);
    tmp5 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp4});
    ca_.Branch(tmp5, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block7, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Int32Elements_0)));
  }

  TNode<Int32T> tmp6;
  TNode<BoolT> tmp7;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp6 = FromConstexpr_ElementsKind_constexpr_FLOAT16_ELEMENTS_0(state_, ElementsKind::FLOAT16_ELEMENTS);
    tmp7 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp6});
    ca_.Branch(tmp7, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block10, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Float16Elements_0)));
  }

  TNode<Int32T> tmp8;
  TNode<BoolT> tmp9;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp8 = FromConstexpr_ElementsKind_constexpr_FLOAT32_ELEMENTS_0(state_, ElementsKind::FLOAT32_ELEMENTS);
    tmp9 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp8});
    ca_.Branch(tmp9, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block13, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Float32Elements_0)));
  }

  TNode<Int32T> tmp10;
  TNode<BoolT> tmp11;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp10 = FromConstexpr_ElementsKind_constexpr_FLOAT64_ELEMENTS_0(state_, ElementsKind::FLOAT64_ELEMENTS);
    tmp11 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp10});
    ca_.Branch(tmp11, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    ca_.Goto(&block16, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Float64Elements_0)));
  }

  TNode<Int32T> tmp12;
  TNode<BoolT> tmp13;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp12 = FromConstexpr_ElementsKind_constexpr_UINT8_CLAMPED_ELEMENTS_0(state_, ElementsKind::UINT8_CLAMPED_ELEMENTS);
    tmp13 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp12});
    ca_.Branch(tmp13, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block19, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint8ClampedElements_0)));
  }

  TNode<Int32T> tmp14;
  TNode<BoolT> tmp15;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp14 = FromConstexpr_ElementsKind_constexpr_BIGUINT64_ELEMENTS_0(state_, ElementsKind::BIGUINT64_ELEMENTS);
    tmp15 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp14});
    ca_.Branch(tmp15, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block22, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_BigUint64Elements_0)));
  }

  TNode<Int32T> tmp16;
  TNode<BoolT> tmp17;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp16 = FromConstexpr_ElementsKind_constexpr_BIGINT64_ELEMENTS_0(state_, ElementsKind::BIGINT64_ELEMENTS);
    tmp17 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp16});
    ca_.Branch(tmp17, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block25, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_BigInt64Elements_0)));
  }

  TNode<Int32T> tmp18;
  TNode<BoolT> tmp19;
  if (block24.is_used()) {
    ca_.Bind(&block24);
    tmp18 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT8_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_UINT8_ELEMENTS);
    tmp19 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp18});
    ca_.Branch(tmp19, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block28, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint8Elements_0)));
  }

  TNode<Int32T> tmp20;
  TNode<BoolT> tmp21;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp20 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_INT8_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_INT8_ELEMENTS);
    tmp21 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp20});
    ca_.Branch(tmp21, &block29, std::vector<compiler::Node*>{}, &block30, std::vector<compiler::Node*>{});
  }

  if (block29.is_used()) {
    ca_.Bind(&block29);
    ca_.Goto(&block31, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Int8Elements_0)));
  }

  TNode<Int32T> tmp22;
  TNode<BoolT> tmp23;
  if (block30.is_used()) {
    ca_.Bind(&block30);
    tmp22 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT16_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_UINT16_ELEMENTS);
    tmp23 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp22});
    ca_.Branch(tmp23, &block32, std::vector<compiler::Node*>{}, &block33, std::vector<compiler::Node*>{});
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    ca_.Goto(&block34, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint16Elements_0)));
  }

  TNode<Int32T> tmp24;
  TNode<BoolT> tmp25;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp24 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_INT16_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_INT16_ELEMENTS);
    tmp25 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp24});
    ca_.Branch(tmp25, &block35, std::vector<compiler::Node*>{}, &block36, std::vector<compiler::Node*>{});
  }

  if (block35.is_used()) {
    ca_.Bind(&block35);
    ca_.Goto(&block37, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Int16Elements_0)));
  }

  TNode<Int32T> tmp26;
  TNode<BoolT> tmp27;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp26 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT32_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_UINT32_ELEMENTS);
    tmp27 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp26});
    ca_.Branch(tmp27, &block38, std::vector<compiler::Node*>{}, &block39, std::vector<compiler::Node*>{});
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    ca_.Goto(&block40, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint32Elements_0)));
  }

  TNode<Int32T> tmp28;
  TNode<BoolT> tmp29;
  if (block39.is_used()) {
    ca_.Bind(&block39);
    tmp28 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_INT32_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_INT32_ELEMENTS);
    tmp29 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp28});
    ca_.Branch(tmp29, &block41, std::vector<compiler::Node*>{}, &block42, std::vector<compiler::Node*>{});
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    ca_.Goto(&block43, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Int32Elements_0)));
  }

  TNode<Int32T> tmp30;
  TNode<BoolT> tmp31;
  if (block42.is_used()) {
    ca_.Bind(&block42);
    tmp30 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_FLOAT16_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_FLOAT16_ELEMENTS);
    tmp31 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp30});
    ca_.Branch(tmp31, &block44, std::vector<compiler::Node*>{}, &block45, std::vector<compiler::Node*>{});
  }

  if (block44.is_used()) {
    ca_.Bind(&block44);
    ca_.Goto(&block46, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Float16Elements_0)));
  }

  TNode<Int32T> tmp32;
  TNode<BoolT> tmp33;
  if (block45.is_used()) {
    ca_.Bind(&block45);
    tmp32 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_FLOAT32_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_FLOAT32_ELEMENTS);
    tmp33 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp32});
    ca_.Branch(tmp33, &block47, std::vector<compiler::Node*>{}, &block48, std::vector<compiler::Node*>{});
  }

  if (block47.is_used()) {
    ca_.Bind(&block47);
    ca_.Goto(&block49, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Float32Elements_0)));
  }

  TNode<Int32T> tmp34;
  TNode<BoolT> tmp35;
  if (block48.is_used()) {
    ca_.Bind(&block48);
    tmp34 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_FLOAT64_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_FLOAT64_ELEMENTS);
    tmp35 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp34});
    ca_.Branch(tmp35, &block50, std::vector<compiler::Node*>{}, &block51, std::vector<compiler::Node*>{});
  }

  if (block50.is_used()) {
    ca_.Bind(&block50);
    ca_.Goto(&block52, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Float64Elements_0)));
  }

  TNode<Int32T> tmp36;
  TNode<BoolT> tmp37;
  if (block51.is_used()) {
    ca_.Bind(&block51);
    tmp36 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT8_CLAMPED_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_UINT8_CLAMPED_ELEMENTS);
    tmp37 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp36});
    ca_.Branch(tmp37, &block53, std::vector<compiler::Node*>{}, &block54, std::vector<compiler::Node*>{});
  }

  if (block53.is_used()) {
    ca_.Bind(&block53);
    ca_.Goto(&block55, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint8ClampedElements_0)));
  }

  TNode<Int32T> tmp38;
  TNode<BoolT> tmp39;
  if (block54.is_used()) {
    ca_.Bind(&block54);
    tmp38 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_BIGUINT64_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_BIGUINT64_ELEMENTS);
    tmp39 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp38});
    ca_.Branch(tmp39, &block56, std::vector<compiler::Node*>{}, &block57, std::vector<compiler::Node*>{});
  }

  if (block56.is_used()) {
    ca_.Bind(&block56);
    ca_.Goto(&block58, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_BigUint64Elements_0)));
  }

  TNode<Int32T> tmp40;
  TNode<BoolT> tmp41;
  if (block57.is_used()) {
    ca_.Bind(&block57);
    tmp40 = FromConstexpr_ElementsKind_constexpr_RAB_GSAB_BIGINT64_ELEMENTS_0(state_, ElementsKind::RAB_GSAB_BIGINT64_ELEMENTS);
    tmp41 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp40});
    ca_.Branch(tmp41, &block59, std::vector<compiler::Node*>{}, &block60, std::vector<compiler::Node*>{});
  }

  if (block59.is_used()) {
    ca_.Bind(&block59);
    ca_.Goto(&block58, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_BigInt64Elements_0)));
  }

  if (block60.is_used()) {
    ca_.Bind(&block60);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:614:7");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BuiltinPtr> phi_bb58_8;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_8);
    ca_.Goto(&block55, phi_bb58_8);
  }

  TNode<BuiltinPtr> phi_bb55_8;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_8);
    ca_.Goto(&block52, phi_bb55_8);
  }

  TNode<BuiltinPtr> phi_bb52_8;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_8);
    ca_.Goto(&block49, phi_bb52_8);
  }

  TNode<BuiltinPtr> phi_bb49_8;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_8);
    ca_.Goto(&block46, phi_bb49_8);
  }

  TNode<BuiltinPtr> phi_bb46_8;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_8);
    ca_.Goto(&block43, phi_bb46_8);
  }

  TNode<BuiltinPtr> phi_bb43_8;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_8);
    ca_.Goto(&block40, phi_bb43_8);
  }

  TNode<BuiltinPtr> phi_bb40_8;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_8);
    ca_.Goto(&block37, phi_bb40_8);
  }

  TNode<BuiltinPtr> phi_bb37_8;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_8);
    ca_.Goto(&block34, phi_bb37_8);
  }

  TNode<BuiltinPtr> phi_bb34_8;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_8);
    ca_.Goto(&block31, phi_bb34_8);
  }

  TNode<BuiltinPtr> phi_bb31_8;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_8);
    ca_.Goto(&block28, phi_bb31_8);
  }

  TNode<BuiltinPtr> phi_bb28_8;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_8);
    ca_.Goto(&block25, phi_bb28_8);
  }

  TNode<BuiltinPtr> phi_bb25_8;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_8);
    ca_.Goto(&block22, phi_bb25_8);
  }

  TNode<BuiltinPtr> phi_bb22_8;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_8);
    ca_.Goto(&block19, phi_bb22_8);
  }

  TNode<BuiltinPtr> phi_bb19_8;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_8);
    ca_.Goto(&block16, phi_bb19_8);
  }

  TNode<BuiltinPtr> phi_bb16_8;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_8);
    ca_.Goto(&block13, phi_bb16_8);
  }

  TNode<BuiltinPtr> phi_bb13_8;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_8);
    ca_.Goto(&block10, phi_bb13_8);
  }

  TNode<BuiltinPtr> phi_bb10_8;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_8);
    ca_.Goto(&block7, phi_bb10_8);
  }

  TNode<BuiltinPtr> phi_bb7_8;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_8);
    ca_.Goto(&block4, phi_bb7_8);
  }

  TNode<Int32T> tmp42;
  TNode<BoolT> tmp43;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp42 = FromConstexpr_ElementsKind_constexpr_UINT8_ELEMENTS_0(state_, ElementsKind::UINT8_ELEMENTS);
    tmp43 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp42});
    ca_.Branch(tmp43, &block62, std::vector<compiler::Node*>{}, &block63, std::vector<compiler::Node*>{});
  }

  if (block62.is_used()) {
    ca_.Bind(&block62);
    ca_.Goto(&block64, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint8Elements_0)));
  }

  TNode<Int32T> tmp44;
  TNode<BoolT> tmp45;
  if (block63.is_used()) {
    ca_.Bind(&block63);
    tmp44 = FromConstexpr_ElementsKind_constexpr_INT8_ELEMENTS_0(state_, ElementsKind::INT8_ELEMENTS);
    tmp45 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp44});
    ca_.Branch(tmp45, &block65, std::vector<compiler::Node*>{}, &block66, std::vector<compiler::Node*>{});
  }

  if (block65.is_used()) {
    ca_.Bind(&block65);
    ca_.Goto(&block67, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Int8Elements_0)));
  }

  TNode<Int32T> tmp46;
  TNode<BoolT> tmp47;
  if (block66.is_used()) {
    ca_.Bind(&block66);
    tmp46 = FromConstexpr_ElementsKind_constexpr_UINT16_ELEMENTS_0(state_, ElementsKind::UINT16_ELEMENTS);
    tmp47 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp46});
    ca_.Branch(tmp47, &block68, std::vector<compiler::Node*>{}, &block69, std::vector<compiler::Node*>{});
  }

  if (block68.is_used()) {
    ca_.Bind(&block68);
    ca_.Goto(&block70, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint16Elements_0)));
  }

  TNode<Int32T> tmp48;
  TNode<BoolT> tmp49;
  if (block69.is_used()) {
    ca_.Bind(&block69);
    tmp48 = FromConstexpr_ElementsKind_constexpr_INT16_ELEMENTS_0(state_, ElementsKind::INT16_ELEMENTS);
    tmp49 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp48});
    ca_.Branch(tmp49, &block71, std::vector<compiler::Node*>{}, &block72, std::vector<compiler::Node*>{});
  }

  if (block71.is_used()) {
    ca_.Bind(&block71);
    ca_.Goto(&block73, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Int16Elements_0)));
  }

  TNode<Int32T> tmp50;
  TNode<BoolT> tmp51;
  if (block72.is_used()) {
    ca_.Bind(&block72);
    tmp50 = FromConstexpr_ElementsKind_constexpr_UINT32_ELEMENTS_0(state_, ElementsKind::UINT32_ELEMENTS);
    tmp51 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp2}, TNode<Int32T>{tmp50});
    ca_.Branch(tmp51, &block74, std::vector<compiler::Node*>{}, &block75, std::vector<compiler::Node*>{});
  }

  if (block74.is_used()) {
    ca_.Bind(&block74);
    ca_.Goto(&block73, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinTypedElement_Uint32Elements_0)));
  }

  if (block75.is_used()) {
    ca_.Bind(&block75);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:628:7");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BuiltinPtr> phi_bb73_8;
  if (block73.is_used()) {
    ca_.Bind(&block73, &phi_bb73_8);
    ca_.Goto(&block70, phi_bb73_8);
  }

  TNode<BuiltinPtr> phi_bb70_8;
  if (block70.is_used()) {
    ca_.Bind(&block70, &phi_bb70_8);
    ca_.Goto(&block67, phi_bb70_8);
  }

  TNode<BuiltinPtr> phi_bb67_8;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_8);
    ca_.Goto(&block64, phi_bb67_8);
  }

  TNode<BuiltinPtr> phi_bb64_8;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_8);
    ca_.Goto(&block4, phi_bb64_8);
  }

  TNode<BuiltinPtr> phi_bb4_8;
  TNode<String> tmp52;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_8);
    tmp52 = ArrayJoinImpl_JSTypedArray_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_receiver}, TNode<String>{p_sep}, TNode<Number>{p_lenNumber}, p_useToLocaleString, TNode<JSAny>{p_locales}, TNode<JSAny>{p_options}, TNode<BuiltinPtr>{phi_bb4_8});
    ca_.Goto(&block77);
  }

    ca_.Bind(&block77);
  return TNode<JSAny>{tmp52};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=642&c=1
TNode<FixedArray> LoadJoinStack_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, compiler::CodeAssemblerLabel* label_IfUninitialized) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<Union<FixedArray, Undefined>> tmp3;
  TNode<Undefined> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ARRAY_JOIN_STACK_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_FixedArray_OR_Undefined_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    tmp3 = CodeStubAssembler(state_).LoadReference<Union<FixedArray, Undefined>>(CodeStubAssembler::Reference{tmp1, tmp2});
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_Undefined_2(state_, TNode<HeapObject>{tmp3}, &label5);
    ca_.Goto(&block5);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block7);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(label_IfUninitialized);
  }

    ca_.Bind(&block7);
  return TNode<FixedArray>{ca_.UncheckedCast<FixedArray>(tmp3)};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=654&c=1
void SetJoinStack_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_stack) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Union<HeapObject, TaggedIndex>> tmp1;
  TNode<IntPtrT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ARRAY_JOIN_STACK_INDEX_0(state_);
    std::tie(tmp1, tmp2) = NativeContextSlot_Context_FixedArray_OR_Undefined_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp0}).Flatten();
    CodeStubAssembler(state_).StoreReference<Union<FixedArray, Undefined>>(CodeStubAssembler::Reference{tmp1, tmp2}, p_stack);
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
}

TF_BUILTIN(JoinStackPush, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<FixedArray> parameter1 = UncheckedParameter<FixedArray>(Descriptor::kStack);
  USE(parameter1);
  TNode<JSReceiver> parameter2 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block3, tmp1);
  }

  TNode<IntPtrT> phi_bb3_4;
  TNode<BoolT> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4);
    tmp2 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb3_4}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{phi_bb3_4}, &block2, std::vector<compiler::Node*>{phi_bb3_4});
  }

  TNode<IntPtrT> phi_bb1_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<BoolT> tmp8;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    std::tie(tmp3, tmp4, tmp5) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter1}).Flatten();
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb1_4});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp8 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp6}, TNode<UintPtrT>{tmp7});
    ca_.Branch(tmp8, &block9, std::vector<compiler::Node*>{phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4}, &block10, std::vector<compiler::Node*>{phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4});
  }

  TNode<IntPtrT> phi_bb9_4;
  TNode<IntPtrT> phi_bb9_9;
  TNode<IntPtrT> phi_bb9_10;
  TNode<IntPtrT> phi_bb9_14;
  TNode<IntPtrT> phi_bb9_15;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Object> tmp13;
  TNode<TheHole> tmp14;
  TNode<BoolT> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_4, &phi_bb9_9, &phi_bb9_10, &phi_bb9_14, &phi_bb9_15);
    tmp9 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb9_15});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp3}, TNode<IntPtrT>{tmp10}).Flatten();
    tmp13 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp11, tmp12});
    tmp14 = TheHole_0(state_);
    tmp15 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp13}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp14});
    ca_.Branch(tmp15, &block13, std::vector<compiler::Node*>{phi_bb9_4}, &block14, std::vector<compiler::Node*>{phi_bb9_4});
  }

  TNode<IntPtrT> phi_bb10_4;
  TNode<IntPtrT> phi_bb10_9;
  TNode<IntPtrT> phi_bb10_10;
  TNode<IntPtrT> phi_bb10_14;
  TNode<IntPtrT> phi_bb10_15;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_4, &phi_bb10_9, &phi_bb10_10, &phi_bb10_14, &phi_bb10_15);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb13_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<IntPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<UintPtrT> tmp20;
  TNode<BoolT> tmp21;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_4);
    std::tie(tmp16, tmp17, tmp18) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter1}).Flatten();
    tmp19 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb13_4});
    tmp20 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp18});
    tmp21 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp19}, TNode<UintPtrT>{tmp20});
    ca_.Branch(tmp21, &block19, std::vector<compiler::Node*>{phi_bb13_4, phi_bb13_4, phi_bb13_4, phi_bb13_4, phi_bb13_4}, &block20, std::vector<compiler::Node*>{phi_bb13_4, phi_bb13_4, phi_bb13_4, phi_bb13_4, phi_bb13_4});
  }

  TNode<IntPtrT> phi_bb19_4;
  TNode<IntPtrT> phi_bb19_10;
  TNode<IntPtrT> phi_bb19_11;
  TNode<IntPtrT> phi_bb19_15;
  TNode<IntPtrT> phi_bb19_16;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Union<HeapObject, TaggedIndex>> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<True> tmp26;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_4, &phi_bb19_10, &phi_bb19_11, &phi_bb19_15, &phi_bb19_16);
    tmp22 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb19_16});
    tmp23 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp17}, TNode<IntPtrT>{tmp22});
    std::tie(tmp24, tmp25) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp16}, TNode<IntPtrT>{tmp23}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp24, tmp25}, parameter2);
    tmp26 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp26);
  }

  TNode<IntPtrT> phi_bb20_4;
  TNode<IntPtrT> phi_bb20_10;
  TNode<IntPtrT> phi_bb20_11;
  TNode<IntPtrT> phi_bb20_15;
  TNode<IntPtrT> phi_bb20_16;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_4, &phi_bb20_10, &phi_bb20_11, &phi_bb20_15, &phi_bb20_16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb14_4;
  TNode<BoolT> tmp27;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_4);
    tmp27 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2}, TNode<Object>{tmp13});
    ca_.Branch(tmp27, &block23, std::vector<compiler::Node*>{phi_bb14_4}, &block24, std::vector<compiler::Node*>{phi_bb14_4});
  }

  TNode<IntPtrT> phi_bb23_4;
  TNode<False> tmp28;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_4);
    tmp28 = False_0(state_);
    CodeStubAssembler(state_).Return(tmp28);
  }

  TNode<IntPtrT> phi_bb24_4;
  TNode<IntPtrT> tmp29;
  TNode<IntPtrT> tmp30;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_4);
    tmp29 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp30 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb24_4}, TNode<IntPtrT>{tmp29});
    ca_.Goto(&block3, tmp30);
  }

  TNode<IntPtrT> phi_bb2_4;
  TNode<FixedArray> tmp31;
  TNode<True> tmp32;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4);
    tmp31 = StoreAndGrowFixedArray_JSReceiver_0(state_, TNode<FixedArray>{parameter1}, TNode<IntPtrT>{tmp0}, TNode<JSReceiver>{parameter2});
    SetJoinStack_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp31});
    tmp32 = True_0(state_);
    CodeStubAssembler(state_).Return(tmp32);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=687&c=1
TNode<BoolT> JoinStackPushInline_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = LoadJoinStack_0(state_, TNode<Context>{p_context}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  TNode<IntPtrT> tmp2;
  TNode<FixedArray> tmp3;
  TNode<Union<HeapObject, TaggedIndex>> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<IntPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<UintPtrT> tmp10;
  TNode<BoolT> tmp11;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp2 = FromConstexpr_intptr_constexpr_int31_0(state_, JSArray::kMinJoinStackSize);
    tmp3 = CodeStubAssembler(state_).AllocateFixedArrayWithHoles(TNode<IntPtrT>{tmp2}, CastIfEnumClass<CodeStubAssembler::AllocationFlag>(CodeStubAssembler::AllocationFlag::kNone));
    std::tie(tmp4, tmp5, tmp6) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp3}).Flatten();
    tmp7 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp8 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp8});
    tmp10 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp6});
    tmp11 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp9}, TNode<UintPtrT>{tmp10});
    ca_.Branch(tmp11, &block34, std::vector<compiler::Node*>{}, &block35, std::vector<compiler::Node*>{});
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<UintPtrT> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<UintPtrT> tmp17;
  TNode<UintPtrT> tmp18;
  TNode<BoolT> tmp19;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    std::tie(tmp12, tmp13, tmp14) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp0}).Flatten();
    tmp15 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp15});
    tmp17 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp16});
    tmp18 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp14});
    tmp19 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp17}, TNode<UintPtrT>{tmp18});
    ca_.Branch(tmp19, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<Union<HeapObject, TaggedIndex>> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<Object> tmp24;
  TNode<TheHole> tmp25;
  TNode<BoolT> tmp26;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp20 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp16});
    tmp21 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp13}, TNode<IntPtrT>{tmp20});
    std::tie(tmp22, tmp23) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp12}, TNode<IntPtrT>{tmp21}).Flatten();
    tmp24 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp22, tmp23});
    tmp25 = TheHole_0(state_);
    tmp26 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp24}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp25});
    ca_.Branch(tmp26, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<UintPtrT> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<UintPtrT> tmp32;
  TNode<UintPtrT> tmp33;
  TNode<BoolT> tmp34;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    std::tie(tmp27, tmp28, tmp29) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp0}).Flatten();
    tmp30 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp31 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp30});
    tmp32 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp31});
    tmp33 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp29});
    tmp34 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp32}, TNode<UintPtrT>{tmp33});
    ca_.Branch(tmp34, &block23, std::vector<compiler::Node*>{}, &block24, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<Union<HeapObject, TaggedIndex>> tmp37;
  TNode<IntPtrT> tmp38;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp35 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp31});
    tmp36 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp28}, TNode<IntPtrT>{tmp35});
    std::tie(tmp37, tmp38) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp27}, TNode<IntPtrT>{tmp36}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp37, tmp38}, p_receiver);
    ca_.Goto(&block17);
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Boolean> tmp39;
  TNode<False> tmp40;
  TNode<BoolT> tmp41;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp39 = ca_.CallBuiltin<Boolean>(Builtin::kJoinStackPush, p_context, tmp0, p_receiver);
    tmp40 = False_0(state_);
    tmp41 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp39}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp40});
    ca_.Branch(tmp41, &block27, std::vector<compiler::Node*>{}, &block28, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp42;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    tmp42 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block1, tmp42);
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    ca_.Goto(&block17);
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<Union<HeapObject, TaggedIndex>> tmp45;
  TNode<IntPtrT> tmp46;
  if (block34.is_used()) {
    ca_.Bind(&block34);
    tmp43 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp8});
    tmp44 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp5}, TNode<IntPtrT>{tmp43});
    std::tie(tmp45, tmp46) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp4}, TNode<IntPtrT>{tmp44}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp45, tmp46}, p_receiver);
    SetJoinStack_0(state_, TNode<Context>{p_context}, TNode<FixedArray>{tmp3});
    ca_.Goto(&block2);
  }

  if (block35.is_used()) {
    ca_.Bind(&block35);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp47;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp47 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block1, tmp47);
  }

  TNode<BoolT> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block38, phi_bb1_2);
  }

  TNode<BoolT> phi_bb38_2;
    ca_.Bind(&block38, &phi_bb38_2);
  return TNode<BoolT>{phi_bb38_2};
}

TF_BUILTIN(JoinStackPop, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<FixedArray> parameter1 = UncheckedParameter<FixedArray>(Descriptor::kStack);
  USE(parameter1);
  TNode<JSReceiver> parameter2 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block15(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{parameter1});
    tmp1 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block3, tmp1);
  }

  TNode<IntPtrT> phi_bb3_4;
  TNode<BoolT> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_4);
    tmp2 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb3_4}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{phi_bb3_4}, &block2, std::vector<compiler::Node*>{phi_bb3_4});
  }

  TNode<IntPtrT> phi_bb1_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<BoolT> tmp8;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_4);
    std::tie(tmp3, tmp4, tmp5) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter1}).Flatten();
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb1_4});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp8 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp6}, TNode<UintPtrT>{tmp7});
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4}, &block12, std::vector<compiler::Node*>{phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4, phi_bb1_4});
  }

  TNode<IntPtrT> phi_bb11_4;
  TNode<IntPtrT> phi_bb11_9;
  TNode<IntPtrT> phi_bb11_10;
  TNode<IntPtrT> phi_bb11_14;
  TNode<IntPtrT> phi_bb11_15;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Object> tmp13;
  TNode<BoolT> tmp14;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_4, &phi_bb11_9, &phi_bb11_10, &phi_bb11_14, &phi_bb11_15);
    tmp9 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb11_15});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp3}, TNode<IntPtrT>{tmp10}).Flatten();
    tmp13 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp11, tmp12});
    tmp14 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp13}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{parameter2});
    ca_.Branch(tmp14, &block5, std::vector<compiler::Node*>{phi_bb11_4}, &block6, std::vector<compiler::Node*>{phi_bb11_4});
  }

  TNode<IntPtrT> phi_bb12_4;
  TNode<IntPtrT> phi_bb12_9;
  TNode<IntPtrT> phi_bb12_10;
  TNode<IntPtrT> phi_bb12_14;
  TNode<IntPtrT> phi_bb12_15;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_4, &phi_bb12_9, &phi_bb12_10, &phi_bb12_14, &phi_bb12_15);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb5_4;
  TNode<IntPtrT> tmp15;
  TNode<BoolT> tmp16;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_4);
    tmp15 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb5_4}, TNode<IntPtrT>{tmp15});
    ca_.Branch(tmp16, &block17, std::vector<compiler::Node*>{phi_bb5_4}, &block18, std::vector<compiler::Node*>{phi_bb5_4});
  }

  TNode<IntPtrT> phi_bb17_4;
  TNode<IntPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_4);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, JSArray::kMinJoinStackSize);
    tmp18 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp17});
    ca_.Goto(&block19, phi_bb17_4, tmp18);
  }

  TNode<IntPtrT> phi_bb18_4;
  TNode<BoolT> tmp19;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_4);
    tmp19 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block19, phi_bb18_4, tmp19);
  }

  TNode<IntPtrT> phi_bb19_4;
  TNode<BoolT> phi_bb19_6;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_4, &phi_bb19_6);
    ca_.Branch(phi_bb19_6, &block15, std::vector<compiler::Node*>{phi_bb19_4}, &block16, std::vector<compiler::Node*>{phi_bb19_4});
  }

  TNode<IntPtrT> phi_bb15_4;
  TNode<IntPtrT> tmp20;
  TNode<FixedArray> tmp21;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_4);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, JSArray::kMinJoinStackSize);
    tmp21 = CodeStubAssembler(state_).AllocateFixedArrayWithHoles(TNode<IntPtrT>{tmp20}, CastIfEnumClass<CodeStubAssembler::AllocationFlag>(CodeStubAssembler::AllocationFlag::kNone));
    SetJoinStack_0(state_, TNode<Context>{parameter0}, TNode<FixedArray>{tmp21});
    ca_.Goto(&block20, phi_bb15_4);
  }

  TNode<IntPtrT> phi_bb16_4;
  TNode<Union<HeapObject, TaggedIndex>> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<UintPtrT> tmp25;
  TNode<UintPtrT> tmp26;
  TNode<BoolT> tmp27;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_4);
    std::tie(tmp22, tmp23, tmp24) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{parameter1}).Flatten();
    tmp25 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb16_4});
    tmp26 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp24});
    tmp27 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp25}, TNode<UintPtrT>{tmp26});
    ca_.Branch(tmp27, &block25, std::vector<compiler::Node*>{phi_bb16_4, phi_bb16_4, phi_bb16_4, phi_bb16_4, phi_bb16_4}, &block26, std::vector<compiler::Node*>{phi_bb16_4, phi_bb16_4, phi_bb16_4, phi_bb16_4, phi_bb16_4});
  }

  TNode<IntPtrT> phi_bb25_4;
  TNode<IntPtrT> phi_bb25_9;
  TNode<IntPtrT> phi_bb25_10;
  TNode<IntPtrT> phi_bb25_14;
  TNode<IntPtrT> phi_bb25_15;
  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<TheHole> tmp32;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_4, &phi_bb25_9, &phi_bb25_10, &phi_bb25_14, &phi_bb25_15);
    tmp28 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb25_15});
    tmp29 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp23}, TNode<IntPtrT>{tmp28});
    std::tie(tmp30, tmp31) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp22}, TNode<IntPtrT>{tmp29}).Flatten();
    tmp32 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp30, tmp31}, tmp32);
    ca_.Goto(&block20, phi_bb25_4);
  }

  TNode<IntPtrT> phi_bb26_4;
  TNode<IntPtrT> phi_bb26_9;
  TNode<IntPtrT> phi_bb26_10;
  TNode<IntPtrT> phi_bb26_14;
  TNode<IntPtrT> phi_bb26_15;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_4, &phi_bb26_9, &phi_bb26_10, &phi_bb26_14, &phi_bb26_15);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb20_4;
  TNode<Undefined> tmp33;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_4);
    tmp33 = Undefined_0(state_);
    CodeStubAssembler(state_).Return(tmp33);
  }

  TNode<IntPtrT> phi_bb6_4;
  TNode<IntPtrT> tmp34;
  TNode<IntPtrT> tmp35;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_4);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp35 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb6_4}, TNode<IntPtrT>{tmp34});
    ca_.Goto(&block3, tmp35);
  }

  TNode<IntPtrT> phi_bb2_4;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:728:3");
    CodeStubAssembler(state_).Unreachable();
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=732&c=1
void JoinStackPopInline_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<FixedArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = LoadJoinStack_0(state_, TNode<Context>{p_context}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:735:17");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp2;
  TNode<Union<HeapObject, TaggedIndex>> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<UintPtrT> tmp8;
  TNode<UintPtrT> tmp9;
  TNode<BoolT> tmp10;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp0});
    std::tie(tmp3, tmp4, tmp5) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp0}).Flatten();
    tmp6 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp7 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp6});
    tmp8 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp7});
    tmp9 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp10 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp8}, TNode<UintPtrT>{tmp9});
    ca_.Branch(tmp10, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Union<HeapObject, TaggedIndex>> tmp13;
  TNode<IntPtrT> tmp14;
  TNode<Object> tmp15;
  TNode<BoolT> tmp16;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp11 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp7});
    tmp12 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp11});
    std::tie(tmp13, tmp14) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp3}, TNode<IntPtrT>{tmp12}).Flatten();
    tmp15 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp13, tmp14});
    tmp16 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp15}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{p_receiver});
    ca_.Branch(tmp16, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  if (block14.is_used()) {
    ca_.Bind(&block14);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp17 = FromConstexpr_intptr_constexpr_int31_0(state_, JSArray::kMinJoinStackSize);
    tmp18 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp2}, TNode<IntPtrT>{tmp17});
    ca_.Goto(&block19, tmp18);
  }

  TNode<BoolT> tmp19;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp19 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block19, tmp19);
  }

  TNode<BoolT> phi_bb19_5;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_5);
    ca_.Branch(phi_bb19_5, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<UintPtrT> tmp23;
  TNode<IntPtrT> tmp24;
  TNode<UintPtrT> tmp25;
  TNode<UintPtrT> tmp26;
  TNode<BoolT> tmp27;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    std::tie(tmp20, tmp21, tmp22) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp0}).Flatten();
    tmp23 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp24 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp23});
    tmp25 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp24});
    tmp26 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp22});
    tmp27 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp25}, TNode<UintPtrT>{tmp26});
    ca_.Branch(tmp27, &block26, std::vector<compiler::Node*>{}, &block27, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  TNode<TheHole> tmp32;
  if (block26.is_used()) {
    ca_.Bind(&block26);
    tmp28 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp24});
    tmp29 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp21}, TNode<IntPtrT>{tmp28});
    std::tie(tmp30, tmp31) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp20}, TNode<IntPtrT>{tmp29}).Flatten();
    tmp32 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp30, tmp31}, tmp32);
    ca_.Goto(&block20);
  }

  if (block27.is_used()) {
    ca_.Bind(&block27);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> tmp33;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp33 = ca_.CallBuiltin<JSAny>(Builtin::kJoinStackPop, p_context, tmp0, p_receiver);
    ca_.Goto(&block20);
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block30);
  }

    ca_.Bind(&block30);
}

TF_BUILTIN(ArrayPrototypeJoin, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<JSReceiver> tmp2;
  TNode<Number> tmp3;
  TNode<Number> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    tmp2 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter1});
    tmp3 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp2});
    tmp4 = FromConstexpr_Number_constexpr_uint32_0(state_, JSArray::kMaxArrayLength);
    tmp5 = NumberIsGreaterThan_0(state_, TNode<Number>{tmp3}, TNode<Number>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidArrayLength));
  }

  TNode<Undefined> tmp6;
  TNode<BoolT> tmp7;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp6 = Undefined_0(state_);
    tmp7 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp6});
    ca_.Branch(tmp7, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp8;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp8 = FromConstexpr_String_constexpr_string_0(state_, ",");
    ca_.Goto(&block5, tmp8);
  }

  TNode<String> tmp9;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp9 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp1});
    ca_.Goto(&block5, tmp9);
  }

  TNode<String> phi_bb5_9;
  TNode<Number> tmp10;
  TNode<BoolT> tmp11;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_9);
    tmp10 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp11 = IsNumberEqual_0(state_, TNode<Number>{tmp3}, TNode<Number>{tmp10});
    ca_.Branch(tmp11, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp12;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp12 = kEmptyString_0(state_);
    arguments.PopAndReturn(tmp12);
  }

  TNode<JSAny> tmp13;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp13 = ca_.CallBuiltin<JSAny>(Builtin::kArrayPrototypeJoinImpl, parameter0, tmp2, tmp3, phi_bb5_9);
    arguments.PopAndReturn(tmp13);
  }
}

TF_BUILTIN(ArrayPrototypeJoinImpl, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kO);
  USE(parameter1);
  TNode<Number> parameter2 = UncheckedParameter<Number>(Descriptor::kLen);
  USE(parameter2);
  TNode<String> parameter3 = UncheckedParameter<String>(Descriptor::kSeparator);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = IsNumberNotEqual_0(state_, TNode<Number>{parameter2}, TNode<Number>{tmp0});
    ca_.Branch(tmp1, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 800});
      CodeStubAssembler(state_).FailAssert("Torque assert 'len != 0' failed", pos_stack);
    }
  }

  TNode<Number> tmp2;
  TNode<BoolT> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp2 = FromConstexpr_Number_constexpr_uint32_0(state_, JSArray::kMaxArrayLength);
    tmp3 = NumberIsLessThanOrEqual_0(state_, TNode<Number>{parameter2}, TNode<Number>{tmp2});
    ca_.Branch(tmp3, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 801});
      CodeStubAssembler(state_).FailAssert("Torque assert 'len <= kMaxArrayLength' failed", pos_stack);
    }
  }

  TNode<JSArray> tmp4;
  TNode<Int32T> tmp5;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label6(&ca_);
    std::tie(tmp4, tmp5) = CastFastJSArrayForRead_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{parameter1}, &label6).Flatten();
    ca_.Goto(&block7);
    if (label6.is_used()) {
      ca_.Bind(&label6);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block5);
  }

  TNode<BoolT> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp7 = CodeStubAssembler(state_).IsFastSmiElementsKind(TNode<Int32T>{tmp5});
    ca_.Branch(tmp7, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp8;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp8 = CodeStubAssembler(state_).IsHoleyFastElementsKind(TNode<Int32T>{tmp5});
    ca_.Branch(tmp8, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp9;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp9 = FastArrayJoin_0(state_, TNode<Context>{parameter0}, CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_SMI_ELEMENTS), TNode<JSArray>{tmp4}, TNode<String>{parameter3}, TNode<Number>{parameter2});
    CodeStubAssembler(state_).Return(tmp9);
  }

  TNode<String> tmp10;
  if (block13.is_used()) {
    ca_.Bind(&block13);
    tmp10 = FastArrayJoin_0(state_, TNode<Context>{parameter0}, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_SMI_ELEMENTS), TNode<JSArray>{tmp4}, TNode<String>{parameter3}, TNode<Number>{parameter2});
    CodeStubAssembler(state_).Return(tmp10);
  }

  TNode<BoolT> tmp11;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp11 = CodeStubAssembler(state_).IsDoubleElementsKind(TNode<Int32T>{tmp5});
    ca_.Branch(tmp11, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp12;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp12 = CodeStubAssembler(state_).IsHoleyFastElementsKind(TNode<Int32T>{tmp5});
    ca_.Branch(tmp12, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp13;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp13 = FastArrayJoin_0(state_, TNode<Context>{parameter0}, CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_DOUBLE_ELEMENTS), TNode<JSArray>{tmp4}, TNode<String>{parameter3}, TNode<Number>{parameter2});
    CodeStubAssembler(state_).Return(tmp13);
  }

  TNode<String> tmp14;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp14 = FastArrayJoin_0(state_, TNode<Context>{parameter0}, CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_DOUBLE_ELEMENTS), TNode<JSArray>{tmp4}, TNode<String>{parameter3}, TNode<Number>{parameter2});
    CodeStubAssembler(state_).Return(tmp14);
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block5);
  }

  TNode<Undefined> tmp15;
  TNode<Undefined> tmp16;
  TNode<JSAny> tmp17;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    CodeStubAssembler(state_).PerformStackCheck(TNode<Context>{parameter0});
    tmp15 = Undefined_0(state_);
    tmp16 = Undefined_0(state_);
    tmp17 = CycleProtectedArrayJoin_JSArray_0(state_, TNode<Context>{parameter0}, false, TNode<JSReceiver>{parameter1}, TNode<Number>{parameter2}, TNode<String>{parameter3}, TNode<JSAny>{tmp15}, TNode<JSAny>{tmp16});
    CodeStubAssembler(state_).Return(tmp17);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=839&c=1
TNode<String> ArrayPrototypeToString_Inline_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_array) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Number> tmp1;
  TNode<Number> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    tmp1 = CodeStubAssembler(state_).LoadReference<Number>(CodeStubAssembler::Reference{p_array, tmp0});
    tmp2 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = IsNumberEqual_0(state_, TNode<Number>{tmp1}, TNode<Number>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp4;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = kEmptyString_0(state_);
    ca_.Goto(&block1, tmp4);
  }

  TNode<Number> tmp5;
  TNode<BoolT> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp5 = FromConstexpr_Number_constexpr_uint32_0(state_, JSArray::kMaxArrayLength);
    tmp6 = NumberIsGreaterThan_0(state_, TNode<Number>{tmp1}, TNode<Number>{tmp5});
    ca_.Branch(tmp6, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{p_context}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidArrayLength));
  }

  TNode<String> tmp7;
  TNode<JSAny> tmp8;
  TNode<String> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = FromConstexpr_String_constexpr_string_0(state_, ",");
    tmp8 = ca_.CallBuiltin<JSAny>(Builtin::kArrayPrototypeJoinImpl, p_context, p_array, tmp1, tmp7);
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = Cast_String_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp8}, &label10);
    ca_.Goto(&block8);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block9);
    }
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:858:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1, tmp9);
  }

  TNode<String> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block10, phi_bb1_2);
  }

  TNode<String> phi_bb10_2;
    ca_.Bind(&block10, &phi_bb10_2);
  return TNode<String>{phi_bb10_2};
}

TF_BUILTIN(ArrayPrototypeToLocaleString, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<JSAny> tmp3;
  TNode<JSReceiver> tmp4;
  TNode<Number> tmp5;
  TNode<Number> tmp6;
  TNode<BoolT> tmp7;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp3 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp2});
    tmp4 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter1});
    tmp5 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp4});
    tmp6 = FromConstexpr_Number_constexpr_uint32_0(state_, JSArray::kMaxArrayLength);
    tmp7 = NumberIsGreaterThan_0(state_, TNode<Number>{tmp5}, TNode<Number>{tmp6});
    ca_.Branch(tmp7, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kInvalidArrayLength));
  }

  TNode<String> tmp8;
  TNode<JSAny> tmp9;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp8 = FromConstexpr_String_constexpr_string_0(state_, ",");
    tmp9 = CycleProtectedArrayJoin_JSArray_0(state_, TNode<Context>{parameter0}, true, TNode<JSReceiver>{tmp4}, TNode<Number>{tmp5}, TNode<String>{tmp8}, TNode<JSAny>{tmp1}, TNode<JSAny>{tmp3});
    arguments.PopAndReturn(tmp9);
  }
}

TF_BUILTIN(ArrayPrototypeToString, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<JSAny> tmp1;
  TNode<JSAny> tmp2;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter1});
    tmp1 = FromConstexpr_JSAny_constexpr_string_0(state_, "join");
    tmp2 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp0}, TNode<JSAny>{tmp1});
    compiler::CodeAssemblerLabel label4(&ca_);
    tmp3 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp2}, &label4);
    ca_.Goto(&block3);
    if (label4.is_used()) {
      ca_.Bind(&label4);
      ca_.Goto(&block4);
    }
  }

  TNode<String> tmp5;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = ca_.CallBuiltin<String>(Builtin::kObjectToString, parameter0, tmp0);
    arguments.PopAndReturn(tmp5);
  }

  TNode<JSAny> tmp6;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp6 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp3}, TNode<JSAny>{tmp0});
    arguments.PopAndReturn(tmp6);
  }
}

TF_BUILTIN(TypedArrayPrototypeJoin, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<String> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<UintPtrT> tmp2;
  TNode<JSTypedArray> tmp3;
  TNode<Undefined> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    tmp2 = TypedArrayBuiltinsAssembler(state_).ValidateTypedArrayAndGetLength(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, "%TypedArray%.prototype.join", CastIfEnumClass<TypedArrayAccessMode>(TypedArrayAccessMode::kRead));
    tmp3 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp4 = Undefined_0(state_);
    tmp5 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp4});
    ca_.Branch(tmp5, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp6;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp6 = FromConstexpr_String_constexpr_string_0(state_, ",");
    ca_.Goto(&block3, tmp6);
  }

  TNode<String> tmp7;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp7 = CodeStubAssembler(state_).ToString_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp1});
    ca_.Goto(&block3, tmp7);
  }

  TNode<String> phi_bb3_9;
  TNode<Number> tmp8;
  TNode<Undefined> tmp9;
  TNode<Undefined> tmp10;
  TNode<JSAny> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_9);
    tmp8 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{tmp2});
    tmp9 = Undefined_0(state_);
    tmp10 = Undefined_0(state_);
    tmp11 = CycleProtectedArrayJoin_JSTypedArray_0(state_, TNode<Context>{parameter0}, false, TNode<JSReceiver>{tmp3}, TNode<Number>{tmp8}, TNode<String>{phi_bb3_9}, TNode<JSAny>{tmp9}, TNode<JSAny>{tmp10});
    arguments.PopAndReturn(tmp11);
  }
}

TF_BUILTIN(TypedArrayPrototypeToLocaleString, CodeStubAssembler) {
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
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<JSAny> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<JSAny> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<JSTypedArray> tmp5;
  TNode<Number> tmp6;
  TNode<String> tmp7;
  TNode<JSAny> tmp8;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp0});
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp3 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp2});
    tmp4 = TypedArrayBuiltinsAssembler(state_).ValidateTypedArrayAndGetLength(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, "%TypedArray%.prototype.toLocaleString", CastIfEnumClass<TypedArrayAccessMode>(TypedArrayAccessMode::kRead));
    tmp5 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp6 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{tmp4});
    tmp7 = FromConstexpr_String_constexpr_string_0(state_, ",");
    tmp8 = CycleProtectedArrayJoin_JSTypedArray_0(state_, TNode<Context>{parameter0}, true, TNode<JSReceiver>{tmp5}, TNode<Number>{tmp6}, TNode<String>{tmp7}, TNode<JSAny>{tmp1}, TNode<JSAny>{tmp3});
    arguments.PopAndReturn(tmp8);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=27&c=26
TNode<JSArray> UnsafeCast_JSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSArray_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=28&c=34
TNode<NumberDictionary> UnsafeCast_NumberDictionary_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_NumberDictionary_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<NumberDictionary> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<NumberDictionary>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=42&c=34
TNode<FixedArray> UnsafeCast_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_FixedArray_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<FixedArray> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<FixedArray>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=44&c=46
TNode<JSAny> UnsafeCast_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSAny_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSAny> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSAny>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=51&c=7
TNode<FixedDoubleArray> UnsafeCast_FixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_FixedDoubleArray_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<FixedDoubleArray> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<FixedDoubleArray>{tmp1};
}

TF_BUILTIN(LoadJoinElement_GenericElementsAccessor_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<JSAny> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = Convert_Number_uintptr_0(state_, TNode<UintPtrT>{parameter2});
    tmp1 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TNode<JSAny>{tmp0});
    CodeStubAssembler(state_).Return(tmp1);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=123&c=36
TNode<JSTypedArray> UnsafeCast_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_JSTypedArray_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<JSTypedArray> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<JSTypedArray>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=334&c=7
TNode<String> Cast_String_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<HeapObject> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{p_o}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    ca_.Goto(&block1);
  }

  TNode<String> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_String_0(state_, TNode<HeapObject>{tmp0}, &label3);
    ca_.Goto(&block5);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block1);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_CastError);
  }

    ca_.Bind(&block7);
  return TNode<String>{tmp2};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=562&c=10
TNode<String> ArrayJoinImpl_JSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<String> p_sep, TNode<Number> p_lengthNumber, bool p_useToLocaleString, TNode<JSAny> p_locales, TNode<JSAny> p_options, TNode<BuiltinPtr> p_initialLoadFn) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, BoolT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, BoolT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block46(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block48(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, IntPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block65(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block98(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block97(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block116(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block118(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block120(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block131(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, IntPtrT> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block135(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block165(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block168(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block170(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block181(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block180(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block183(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block191(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block185(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block196(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object, IntPtrT> block197(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block200(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray> block206(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray> block207(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block215(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block224(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block225(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block231(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block232(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, BoolT> block233(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block229(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block230(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block234(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block235(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block236(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block240(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block239(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block242(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block241(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block243(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block250(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block251(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block244(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block254(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block255(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block256(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block259(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block258(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray> block265(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray> block266(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block274(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block275(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block283(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block284(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block245(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block237(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block228(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block287(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<UintPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<FixedArray> tmp5;
  TNode<FixedArray> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<BoolT> tmp9;
  TNode<PrimitiveHeapObject> tmp10;
  TNode<UintPtrT> tmp11;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_receiver, tmp0});
    tmp2 = Convert_uintptr_Number_0(state_, TNode<Number>{p_lengthNumber});
    tmp3 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{p_sep});
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp5, tmp6, tmp7, tmp8, tmp9, tmp10) = NewBuffer_0(state_, TNode<UintPtrT>{tmp2}, TNode<String>{p_sep}).Flatten();
    tmp11 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block4, tmp4, p_initialLoadFn, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11);
  }

  TNode<IntPtrT> phi_bb4_10;
  TNode<BuiltinPtr> phi_bb4_11;
  TNode<FixedArray> phi_bb4_13;
  TNode<IntPtrT> phi_bb4_14;
  TNode<IntPtrT> phi_bb4_15;
  TNode<BoolT> phi_bb4_16;
  TNode<PrimitiveHeapObject> phi_bb4_17;
  TNode<UintPtrT> phi_bb4_18;
  TNode<BoolT> tmp12;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_10, &phi_bb4_11, &phi_bb4_13, &phi_bb4_14, &phi_bb4_15, &phi_bb4_16, &phi_bb4_17, &phi_bb4_18);
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb4_18}, TNode<UintPtrT>{tmp2});
    ca_.Branch(tmp12, &block2, std::vector<compiler::Node*>{phi_bb4_10, phi_bb4_11, phi_bb4_13, phi_bb4_14, phi_bb4_15, phi_bb4_16, phi_bb4_17, phi_bb4_18}, &block3, std::vector<compiler::Node*>{phi_bb4_10, phi_bb4_11, phi_bb4_13, phi_bb4_14, phi_bb4_15, phi_bb4_16, phi_bb4_17, phi_bb4_18});
  }

  TNode<IntPtrT> phi_bb2_10;
  TNode<BuiltinPtr> phi_bb2_11;
  TNode<FixedArray> phi_bb2_13;
  TNode<IntPtrT> phi_bb2_14;
  TNode<IntPtrT> phi_bb2_15;
  TNode<BoolT> phi_bb2_16;
  TNode<PrimitiveHeapObject> phi_bb2_17;
  TNode<UintPtrT> phi_bb2_18;
  TNode<BoolT> tmp13;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_10, &phi_bb2_11, &phi_bb2_13, &phi_bb2_14, &phi_bb2_15, &phi_bb2_16, &phi_bb2_17, &phi_bb2_18);
    tmp13 = CannotUseSameArrayAccessor_JSArray_0(state_, TNode<Context>{p_context}, TNode<BuiltinPtr>{phi_bb2_11}, TNode<JSReceiver>{p_receiver}, TNode<Map>{tmp1}, TNode<Number>{p_lengthNumber});
    ca_.Branch(tmp13, &block5, std::vector<compiler::Node*>{phi_bb2_10, phi_bb2_11, phi_bb2_13, phi_bb2_14, phi_bb2_15, phi_bb2_16, phi_bb2_17, phi_bb2_18}, &block6, std::vector<compiler::Node*>{phi_bb2_10, phi_bb2_11, phi_bb2_13, phi_bb2_14, phi_bb2_15, phi_bb2_16, phi_bb2_17, phi_bb2_18});
  }

  TNode<IntPtrT> phi_bb5_10;
  TNode<BuiltinPtr> phi_bb5_11;
  TNode<FixedArray> phi_bb5_13;
  TNode<IntPtrT> phi_bb5_14;
  TNode<IntPtrT> phi_bb5_15;
  TNode<BoolT> phi_bb5_16;
  TNode<PrimitiveHeapObject> phi_bb5_17;
  TNode<UintPtrT> phi_bb5_18;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_10, &phi_bb5_11, &phi_bb5_13, &phi_bb5_14, &phi_bb5_15, &phi_bb5_16, &phi_bb5_17, &phi_bb5_18);
    ca_.Goto(&block6, phi_bb5_10, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_GenericElementsAccessor_0)), phi_bb5_13, phi_bb5_14, phi_bb5_15, phi_bb5_16, phi_bb5_17, phi_bb5_18);
  }

  TNode<IntPtrT> phi_bb6_10;
  TNode<BuiltinPtr> phi_bb6_11;
  TNode<FixedArray> phi_bb6_13;
  TNode<IntPtrT> phi_bb6_14;
  TNode<IntPtrT> phi_bb6_15;
  TNode<BoolT> phi_bb6_16;
  TNode<PrimitiveHeapObject> phi_bb6_17;
  TNode<UintPtrT> phi_bb6_18;
  TNode<UintPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_10, &phi_bb6_11, &phi_bb6_13, &phi_bb6_14, &phi_bb6_15, &phi_bb6_16, &phi_bb6_17, &phi_bb6_18);
    tmp14 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{phi_bb6_18}, TNode<UintPtrT>{tmp14});
    ca_.Branch(tmp15, &block7, std::vector<compiler::Node*>{phi_bb6_10, phi_bb6_13, phi_bb6_14, phi_bb6_15, phi_bb6_16, phi_bb6_17, phi_bb6_18}, &block8, std::vector<compiler::Node*>{phi_bb6_10, phi_bb6_13, phi_bb6_14, phi_bb6_15, phi_bb6_16, phi_bb6_17, phi_bb6_18});
  }

  TNode<IntPtrT> phi_bb7_10;
  TNode<FixedArray> phi_bb7_13;
  TNode<IntPtrT> phi_bb7_14;
  TNode<IntPtrT> phi_bb7_15;
  TNode<BoolT> phi_bb7_16;
  TNode<PrimitiveHeapObject> phi_bb7_17;
  TNode<UintPtrT> phi_bb7_18;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_10, &phi_bb7_13, &phi_bb7_14, &phi_bb7_15, &phi_bb7_16, &phi_bb7_17, &phi_bb7_18);
    tmp16 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb7_10}, TNode<IntPtrT>{tmp16});
    ca_.Goto(&block8, tmp17, phi_bb7_13, phi_bb7_14, phi_bb7_15, phi_bb7_16, phi_bb7_17, phi_bb7_18);
  }

  TNode<IntPtrT> phi_bb8_10;
  TNode<FixedArray> phi_bb8_13;
  TNode<IntPtrT> phi_bb8_14;
  TNode<IntPtrT> phi_bb8_15;
  TNode<BoolT> phi_bb8_16;
  TNode<PrimitiveHeapObject> phi_bb8_17;
  TNode<UintPtrT> phi_bb8_18;
  TNode<UintPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<JSAny> tmp20;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_10, &phi_bb8_13, &phi_bb8_14, &phi_bb8_15, &phi_bb8_16, &phi_bb8_17, &phi_bb8_18);
    tmp18 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp19 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb8_18}, TNode<UintPtrT>{tmp18});
tmp20 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallInterfaceDescriptorFor(ExampleBuiltinForTorqueFunctionPointerType(0)), phi_bb6_11, p_context, p_receiver, phi_bb8_18));
    if ((p_useToLocaleString)) {
      ca_.Goto(&block9, phi_bb8_13, phi_bb8_14, phi_bb8_15, phi_bb8_16, phi_bb8_17);
    } else {
      ca_.Goto(&block10, phi_bb8_13, phi_bb8_14, phi_bb8_15, phi_bb8_16, phi_bb8_17);
    }
  }

  TNode<FixedArray> phi_bb9_13;
  TNode<IntPtrT> phi_bb9_14;
  TNode<IntPtrT> phi_bb9_15;
  TNode<BoolT> phi_bb9_16;
  TNode<PrimitiveHeapObject> phi_bb9_17;
  TNode<String> tmp21;
  TNode<String> tmp22;
  TNode<BoolT> tmp23;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_13, &phi_bb9_14, &phi_bb9_15, &phi_bb9_16, &phi_bb9_17);
    tmp21 = ca_.CallBuiltin<String>(Builtin::kConvertToLocaleString, p_context, tmp20, p_locales, p_options);
    tmp22 = kEmptyString_0(state_);
    tmp23 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp21}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp22});
    ca_.Branch(tmp23, &block12, std::vector<compiler::Node*>{phi_bb9_13, phi_bb9_14, phi_bb9_15, phi_bb9_16, phi_bb9_17}, &block13, std::vector<compiler::Node*>{phi_bb9_13, phi_bb9_14, phi_bb9_15, phi_bb9_16, phi_bb9_17});
  }

  TNode<FixedArray> phi_bb12_13;
  TNode<IntPtrT> phi_bb12_14;
  TNode<IntPtrT> phi_bb12_15;
  TNode<BoolT> phi_bb12_16;
  TNode<PrimitiveHeapObject> phi_bb12_17;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_13, &phi_bb12_14, &phi_bb12_15, &phi_bb12_16, &phi_bb12_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb12_13, phi_bb12_14, phi_bb12_15, phi_bb12_16, phi_bb12_17, tmp19);
  }

  TNode<FixedArray> phi_bb13_13;
  TNode<IntPtrT> phi_bb13_14;
  TNode<IntPtrT> phi_bb13_15;
  TNode<BoolT> phi_bb13_16;
  TNode<PrimitiveHeapObject> phi_bb13_17;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_13, &phi_bb13_14, &phi_bb13_15, &phi_bb13_16, &phi_bb13_17);
    ca_.Goto(&block11, phi_bb13_13, phi_bb13_14, phi_bb13_15, phi_bb13_16, phi_bb13_17, tmp21);
  }

  TNode<FixedArray> phi_bb10_13;
  TNode<IntPtrT> phi_bb10_14;
  TNode<IntPtrT> phi_bb10_15;
  TNode<BoolT> phi_bb10_16;
  TNode<PrimitiveHeapObject> phi_bb10_17;
  TNode<String> tmp24;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_13, &phi_bb10_14, &phi_bb10_15, &phi_bb10_16, &phi_bb10_17);
    compiler::CodeAssemblerLabel label25(&ca_);
    tmp24 = Cast_String_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp20}, &label25);
    ca_.Goto(&block16, phi_bb10_13, phi_bb10_14, phi_bb10_15, phi_bb10_16, phi_bb10_17);
    if (label25.is_used()) {
      ca_.Bind(&label25);
      ca_.Goto(&block17, phi_bb10_13, phi_bb10_14, phi_bb10_15, phi_bb10_16, phi_bb10_17);
    }
  }

  TNode<FixedArray> phi_bb17_13;
  TNode<IntPtrT> phi_bb17_14;
  TNode<IntPtrT> phi_bb17_15;
  TNode<BoolT> phi_bb17_16;
  TNode<PrimitiveHeapObject> phi_bb17_17;
  TNode<Number> tmp26;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_13, &phi_bb17_14, &phi_bb17_15, &phi_bb17_16, &phi_bb17_17);
    compiler::CodeAssemblerLabel label27(&ca_);
    tmp26 = Cast_Number_0(state_, TNode<Object>{ca_.UncheckedCast<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, Symbol, Undefined>>(tmp20)}, &label27);
    ca_.Goto(&block22, phi_bb17_13, phi_bb17_14, phi_bb17_15, phi_bb17_16, phi_bb17_17);
    if (label27.is_used()) {
      ca_.Bind(&label27);
      ca_.Goto(&block23, phi_bb17_13, phi_bb17_14, phi_bb17_15, phi_bb17_16, phi_bb17_17);
    }
  }

  TNode<FixedArray> phi_bb16_13;
  TNode<IntPtrT> phi_bb16_14;
  TNode<IntPtrT> phi_bb16_15;
  TNode<BoolT> phi_bb16_16;
  TNode<PrimitiveHeapObject> phi_bb16_17;
  TNode<String> tmp28;
  TNode<BoolT> tmp29;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_13, &phi_bb16_14, &phi_bb16_15, &phi_bb16_16, &phi_bb16_17);
    tmp28 = kEmptyString_0(state_);
    tmp29 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp24}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp28});
    ca_.Branch(tmp29, &block18, std::vector<compiler::Node*>{phi_bb16_13, phi_bb16_14, phi_bb16_15, phi_bb16_16, phi_bb16_17}, &block19, std::vector<compiler::Node*>{phi_bb16_13, phi_bb16_14, phi_bb16_15, phi_bb16_16, phi_bb16_17});
  }

  TNode<FixedArray> phi_bb18_13;
  TNode<IntPtrT> phi_bb18_14;
  TNode<IntPtrT> phi_bb18_15;
  TNode<BoolT> phi_bb18_16;
  TNode<PrimitiveHeapObject> phi_bb18_17;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_13, &phi_bb18_14, &phi_bb18_15, &phi_bb18_16, &phi_bb18_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb18_13, phi_bb18_14, phi_bb18_15, phi_bb18_16, phi_bb18_17, tmp19);
  }

  TNode<FixedArray> phi_bb19_13;
  TNode<IntPtrT> phi_bb19_14;
  TNode<IntPtrT> phi_bb19_15;
  TNode<BoolT> phi_bb19_16;
  TNode<PrimitiveHeapObject> phi_bb19_17;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_13, &phi_bb19_14, &phi_bb19_15, &phi_bb19_16, &phi_bb19_17);
    ca_.Goto(&block14, phi_bb19_13, phi_bb19_14, phi_bb19_15, phi_bb19_16, phi_bb19_17, tmp24);
  }

  TNode<FixedArray> phi_bb23_13;
  TNode<IntPtrT> phi_bb23_14;
  TNode<IntPtrT> phi_bb23_15;
  TNode<BoolT> phi_bb23_16;
  TNode<PrimitiveHeapObject> phi_bb23_17;
  TNode<BoolT> tmp30;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_13, &phi_bb23_14, &phi_bb23_15, &phi_bb23_16, &phi_bb23_17);
    tmp30 = CodeStubAssembler(state_).IsNullOrUndefined(TNode<Object>{ca_.UncheckedCast<Union<BigInt, Boolean, JSReceiver, Null, Symbol, Undefined>>(tmp20)});
    ca_.Branch(tmp30, &block24, std::vector<compiler::Node*>{phi_bb23_13, phi_bb23_14, phi_bb23_15, phi_bb23_16, phi_bb23_17}, &block25, std::vector<compiler::Node*>{phi_bb23_13, phi_bb23_14, phi_bb23_15, phi_bb23_16, phi_bb23_17});
  }

  TNode<FixedArray> phi_bb22_13;
  TNode<IntPtrT> phi_bb22_14;
  TNode<IntPtrT> phi_bb22_15;
  TNode<BoolT> phi_bb22_16;
  TNode<PrimitiveHeapObject> phi_bb22_17;
  TNode<String> tmp31;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_13, &phi_bb22_14, &phi_bb22_15, &phi_bb22_16, &phi_bb22_17);
    tmp31 = CodeStubAssembler(state_).NumberToString(TNode<Number>{tmp26});
    ca_.Goto(&block20, phi_bb22_13, phi_bb22_14, phi_bb22_15, phi_bb22_16, phi_bb22_17, tmp31);
  }

  TNode<FixedArray> phi_bb24_13;
  TNode<IntPtrT> phi_bb24_14;
  TNode<IntPtrT> phi_bb24_15;
  TNode<BoolT> phi_bb24_16;
  TNode<PrimitiveHeapObject> phi_bb24_17;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_13, &phi_bb24_14, &phi_bb24_15, &phi_bb24_16, &phi_bb24_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb24_13, phi_bb24_14, phi_bb24_15, phi_bb24_16, phi_bb24_17, tmp19);
  }

  TNode<FixedArray> phi_bb25_13;
  TNode<IntPtrT> phi_bb25_14;
  TNode<IntPtrT> phi_bb25_15;
  TNode<BoolT> phi_bb25_16;
  TNode<PrimitiveHeapObject> phi_bb25_17;
  TNode<String> tmp32;
  TNode<String> tmp33;
  TNode<BoolT> tmp34;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_13, &phi_bb25_14, &phi_bb25_15, &phi_bb25_16, &phi_bb25_17);
    tmp32 = ToString_Inline_0(state_, TNode<Context>{p_context}, TNode<JSAny>{ca_.UncheckedCast<Union<BigInt, Boolean, JSReceiver, Null, Symbol, Undefined>>(tmp20)});
    tmp33 = kEmptyString_0(state_);
    tmp34 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp32}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp33});
    ca_.Branch(tmp34, &block26, std::vector<compiler::Node*>{phi_bb25_13, phi_bb25_14, phi_bb25_15, phi_bb25_16, phi_bb25_17}, &block27, std::vector<compiler::Node*>{phi_bb25_13, phi_bb25_14, phi_bb25_15, phi_bb25_16, phi_bb25_17});
  }

  TNode<FixedArray> phi_bb26_13;
  TNode<IntPtrT> phi_bb26_14;
  TNode<IntPtrT> phi_bb26_15;
  TNode<BoolT> phi_bb26_16;
  TNode<PrimitiveHeapObject> phi_bb26_17;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_13, &phi_bb26_14, &phi_bb26_15, &phi_bb26_16, &phi_bb26_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb26_13, phi_bb26_14, phi_bb26_15, phi_bb26_16, phi_bb26_17, tmp19);
  }

  TNode<FixedArray> phi_bb27_13;
  TNode<IntPtrT> phi_bb27_14;
  TNode<IntPtrT> phi_bb27_15;
  TNode<BoolT> phi_bb27_16;
  TNode<PrimitiveHeapObject> phi_bb27_17;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_13, &phi_bb27_14, &phi_bb27_15, &phi_bb27_16, &phi_bb27_17);
    ca_.Goto(&block20, phi_bb27_13, phi_bb27_14, phi_bb27_15, phi_bb27_16, phi_bb27_17, tmp32);
  }

  TNode<FixedArray> phi_bb20_13;
  TNode<IntPtrT> phi_bb20_14;
  TNode<IntPtrT> phi_bb20_15;
  TNode<BoolT> phi_bb20_16;
  TNode<PrimitiveHeapObject> phi_bb20_17;
  TNode<String> phi_bb20_20;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_13, &phi_bb20_14, &phi_bb20_15, &phi_bb20_16, &phi_bb20_17, &phi_bb20_20);
    ca_.Goto(&block14, phi_bb20_13, phi_bb20_14, phi_bb20_15, phi_bb20_16, phi_bb20_17, phi_bb20_20);
  }

  TNode<FixedArray> phi_bb14_13;
  TNode<IntPtrT> phi_bb14_14;
  TNode<IntPtrT> phi_bb14_15;
  TNode<BoolT> phi_bb14_16;
  TNode<PrimitiveHeapObject> phi_bb14_17;
  TNode<String> phi_bb14_20;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_13, &phi_bb14_14, &phi_bb14_15, &phi_bb14_16, &phi_bb14_17, &phi_bb14_20);
    ca_.Goto(&block11, phi_bb14_13, phi_bb14_14, phi_bb14_15, phi_bb14_16, phi_bb14_17, phi_bb14_20);
  }

  TNode<FixedArray> phi_bb11_13;
  TNode<IntPtrT> phi_bb11_14;
  TNode<IntPtrT> phi_bb11_15;
  TNode<BoolT> phi_bb11_16;
  TNode<PrimitiveHeapObject> phi_bb11_17;
  TNode<String> phi_bb11_20;
  TNode<IntPtrT> tmp35;
  TNode<BoolT> tmp36;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_13, &phi_bb11_14, &phi_bb11_15, &phi_bb11_16, &phi_bb11_17, &phi_bb11_20);
    tmp35 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp36 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb11_14}, TNode<IntPtrT>{tmp35});
    ca_.Branch(tmp36, &block31, std::vector<compiler::Node*>{phi_bb11_13, phi_bb11_14, phi_bb11_15, phi_bb11_16, phi_bb11_17, phi_bb11_20, phi_bb11_20, phi_bb11_20}, &block32, std::vector<compiler::Node*>{phi_bb11_13, phi_bb11_14, phi_bb11_15, phi_bb11_16, phi_bb11_17, phi_bb11_20, phi_bb11_20, phi_bb11_20});
  }

  TNode<FixedArray> phi_bb31_13;
  TNode<IntPtrT> phi_bb31_14;
  TNode<IntPtrT> phi_bb31_15;
  TNode<BoolT> phi_bb31_16;
  TNode<PrimitiveHeapObject> phi_bb31_17;
  TNode<String> phi_bb31_20;
  TNode<String> phi_bb31_21;
  TNode<String> phi_bb31_26;
  TNode<BoolT> tmp37;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_13, &phi_bb31_14, &phi_bb31_15, &phi_bb31_16, &phi_bb31_17, &phi_bb31_20, &phi_bb31_21, &phi_bb31_26);
    tmp37 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block33, phi_bb31_13, phi_bb31_14, phi_bb31_15, phi_bb31_16, phi_bb31_17, phi_bb31_20, phi_bb31_21, phi_bb31_26, tmp37);
  }

  TNode<FixedArray> phi_bb32_13;
  TNode<IntPtrT> phi_bb32_14;
  TNode<IntPtrT> phi_bb32_15;
  TNode<BoolT> phi_bb32_16;
  TNode<PrimitiveHeapObject> phi_bb32_17;
  TNode<String> phi_bb32_20;
  TNode<String> phi_bb32_21;
  TNode<String> phi_bb32_26;
  TNode<BoolT> tmp38;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_13, &phi_bb32_14, &phi_bb32_15, &phi_bb32_16, &phi_bb32_17, &phi_bb32_20, &phi_bb32_21, &phi_bb32_26);
    tmp38 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp5}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{phi_bb32_13});
    ca_.Goto(&block33, phi_bb32_13, phi_bb32_14, phi_bb32_15, phi_bb32_16, phi_bb32_17, phi_bb32_20, phi_bb32_21, phi_bb32_26, tmp38);
  }

  TNode<FixedArray> phi_bb33_13;
  TNode<IntPtrT> phi_bb33_14;
  TNode<IntPtrT> phi_bb33_15;
  TNode<BoolT> phi_bb33_16;
  TNode<PrimitiveHeapObject> phi_bb33_17;
  TNode<String> phi_bb33_20;
  TNode<String> phi_bb33_21;
  TNode<String> phi_bb33_26;
  TNode<BoolT> phi_bb33_30;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_13, &phi_bb33_14, &phi_bb33_15, &phi_bb33_16, &phi_bb33_17, &phi_bb33_20, &phi_bb33_21, &phi_bb33_26, &phi_bb33_30);
    ca_.Branch(phi_bb33_30, &block29, std::vector<compiler::Node*>{phi_bb33_13, phi_bb33_14, phi_bb33_15, phi_bb33_16, phi_bb33_17, phi_bb33_20, phi_bb33_21, phi_bb33_26}, &block30, std::vector<compiler::Node*>{phi_bb33_13, phi_bb33_14, phi_bb33_15, phi_bb33_16, phi_bb33_17, phi_bb33_20, phi_bb33_21, phi_bb33_26});
  }

  TNode<FixedArray> phi_bb30_13;
  TNode<IntPtrT> phi_bb30_14;
  TNode<IntPtrT> phi_bb30_15;
  TNode<BoolT> phi_bb30_16;
  TNode<PrimitiveHeapObject> phi_bb30_17;
  TNode<String> phi_bb30_20;
  TNode<String> phi_bb30_21;
  TNode<String> phi_bb30_26;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_13, &phi_bb30_14, &phi_bb30_15, &phi_bb30_16, &phi_bb30_17, &phi_bb30_20, &phi_bb30_21, &phi_bb30_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 184});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index != 1 || this.head == this.chunk' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb29_13;
  TNode<IntPtrT> phi_bb29_14;
  TNode<IntPtrT> phi_bb29_15;
  TNode<BoolT> phi_bb29_16;
  TNode<PrimitiveHeapObject> phi_bb29_17;
  TNode<String> phi_bb29_20;
  TNode<String> phi_bb29_21;
  TNode<String> phi_bb29_26;
  TNode<IntPtrT> tmp39;
  TNode<BoolT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<BoolT> tmp42;
  TNode<BoolT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<BoolT> tmp45;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_13, &phi_bb29_14, &phi_bb29_15, &phi_bb29_16, &phi_bb29_17, &phi_bb29_20, &phi_bb29_21, &phi_bb29_26);
    tmp39 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp40 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb29_14}, TNode<IntPtrT>{tmp39});
    tmp41 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp42 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb8_10}, TNode<IntPtrT>{tmp41});
    tmp43 = CodeStubAssembler(state_).Word32Or(TNode<BoolT>{tmp40}, TNode<BoolT>{tmp42});
    tmp44 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp45 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb8_10}, TNode<IntPtrT>{tmp44});
    ca_.Branch(tmp45, &block37, std::vector<compiler::Node*>{phi_bb29_13, phi_bb29_14, phi_bb29_15, phi_bb29_16, phi_bb29_17, phi_bb29_20, phi_bb29_21, phi_bb29_26}, &block38, std::vector<compiler::Node*>{phi_bb29_13, phi_bb29_14, phi_bb29_15, phi_bb29_16, phi_bb29_17, phi_bb29_20, phi_bb29_21, phi_bb29_26});
  }

  TNode<FixedArray> phi_bb37_13;
  TNode<IntPtrT> phi_bb37_14;
  TNode<IntPtrT> phi_bb37_15;
  TNode<BoolT> phi_bb37_16;
  TNode<PrimitiveHeapObject> phi_bb37_17;
  TNode<String> phi_bb37_20;
  TNode<String> phi_bb37_21;
  TNode<String> phi_bb37_26;
  TNode<BoolT> tmp46;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_13, &phi_bb37_14, &phi_bb37_15, &phi_bb37_16, &phi_bb37_17, &phi_bb37_20, &phi_bb37_21, &phi_bb37_26);
    tmp46 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block39, phi_bb37_13, phi_bb37_14, phi_bb37_15, phi_bb37_16, phi_bb37_17, phi_bb37_20, phi_bb37_21, phi_bb37_26, tmp46);
  }

  TNode<FixedArray> phi_bb38_13;
  TNode<IntPtrT> phi_bb38_14;
  TNode<IntPtrT> phi_bb38_15;
  TNode<BoolT> phi_bb38_16;
  TNode<PrimitiveHeapObject> phi_bb38_17;
  TNode<String> phi_bb38_20;
  TNode<String> phi_bb38_21;
  TNode<String> phi_bb38_26;
  TNode<IntPtrT> tmp47;
  TNode<BoolT> tmp48;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_13, &phi_bb38_14, &phi_bb38_15, &phi_bb38_16, &phi_bb38_17, &phi_bb38_20, &phi_bb38_21, &phi_bb38_26);
    tmp47 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp48 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp47});
    ca_.Goto(&block39, phi_bb38_13, phi_bb38_14, phi_bb38_15, phi_bb38_16, phi_bb38_17, phi_bb38_20, phi_bb38_21, phi_bb38_26, tmp48);
  }

  TNode<FixedArray> phi_bb39_13;
  TNode<IntPtrT> phi_bb39_14;
  TNode<IntPtrT> phi_bb39_15;
  TNode<BoolT> phi_bb39_16;
  TNode<PrimitiveHeapObject> phi_bb39_17;
  TNode<String> phi_bb39_20;
  TNode<String> phi_bb39_21;
  TNode<String> phi_bb39_26;
  TNode<BoolT> phi_bb39_39;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_13, &phi_bb39_14, &phi_bb39_15, &phi_bb39_16, &phi_bb39_17, &phi_bb39_20, &phi_bb39_21, &phi_bb39_26, &phi_bb39_39);
    ca_.Branch(phi_bb39_39, &block35, std::vector<compiler::Node*>{phi_bb39_13, phi_bb39_14, phi_bb39_15, phi_bb39_16, phi_bb39_17, phi_bb39_20, phi_bb39_21, phi_bb39_26}, &block36, std::vector<compiler::Node*>{phi_bb39_13, phi_bb39_14, phi_bb39_15, phi_bb39_16, phi_bb39_17, phi_bb39_20, phi_bb39_21, phi_bb39_26});
  }

  TNode<FixedArray> phi_bb35_13;
  TNode<IntPtrT> phi_bb35_14;
  TNode<IntPtrT> phi_bb35_15;
  TNode<BoolT> phi_bb35_16;
  TNode<PrimitiveHeapObject> phi_bb35_17;
  TNode<String> phi_bb35_20;
  TNode<String> phi_bb35_21;
  TNode<String> phi_bb35_26;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_13, &phi_bb35_14, &phi_bb35_15, &phi_bb35_16, &phi_bb35_17, &phi_bb35_20, &phi_bb35_21, &phi_bb35_26);
    ca_.Goto(&block34, phi_bb35_13, phi_bb35_14, phi_bb35_15, phi_bb35_16, phi_bb35_17, phi_bb35_20, phi_bb35_21, phi_bb35_26);
  }

  TNode<FixedArray> phi_bb36_13;
  TNode<IntPtrT> phi_bb36_14;
  TNode<IntPtrT> phi_bb36_15;
  TNode<BoolT> phi_bb36_16;
  TNode<PrimitiveHeapObject> phi_bb36_17;
  TNode<String> phi_bb36_20;
  TNode<String> phi_bb36_21;
  TNode<String> phi_bb36_26;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<BoolT> tmp51;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_13, &phi_bb36_14, &phi_bb36_15, &phi_bb36_16, &phi_bb36_17, &phi_bb36_20, &phi_bb36_21, &phi_bb36_26);
    tmp49 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{phi_bb8_10});
    tmp50 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp3});
    tmp51 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp50}, TNode<IntPtrT>{phi_bb8_10});
    ca_.Branch(tmp51, &block40, std::vector<compiler::Node*>{phi_bb36_13, phi_bb36_14, phi_bb36_15, phi_bb36_16, phi_bb36_17, phi_bb36_20, phi_bb36_21, phi_bb36_26}, &block41, std::vector<compiler::Node*>{phi_bb36_13, phi_bb36_14, phi_bb36_15, phi_bb36_16, phi_bb36_17, phi_bb36_20, phi_bb36_21, phi_bb36_26});
  }

  TNode<FixedArray> phi_bb40_13;
  TNode<IntPtrT> phi_bb40_14;
  TNode<IntPtrT> phi_bb40_15;
  TNode<BoolT> phi_bb40_16;
  TNode<PrimitiveHeapObject> phi_bb40_17;
  TNode<String> phi_bb40_20;
  TNode<String> phi_bb40_21;
  TNode<String> phi_bb40_26;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_13, &phi_bb40_14, &phi_bb40_15, &phi_bb40_16, &phi_bb40_17, &phi_bb40_20, &phi_bb40_21, &phi_bb40_26);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb41_13;
  TNode<IntPtrT> phi_bb41_14;
  TNode<IntPtrT> phi_bb41_15;
  TNode<BoolT> phi_bb41_16;
  TNode<PrimitiveHeapObject> phi_bb41_17;
  TNode<String> phi_bb41_20;
  TNode<String> phi_bb41_21;
  TNode<String> phi_bb41_26;
  TNode<IntPtrT> tmp52;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_13, &phi_bb41_14, &phi_bb41_15, &phi_bb41_16, &phi_bb41_17, &phi_bb41_20, &phi_bb41_21, &phi_bb41_26);
    tmp52 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb41_15}, TNode<IntPtrT>{tmp49});
    ca_.Branch(tmp43, &block42, std::vector<compiler::Node*>{phi_bb41_13, phi_bb41_14, phi_bb41_16, phi_bb41_17, phi_bb41_20, phi_bb41_21, phi_bb41_26}, &block43, std::vector<compiler::Node*>{phi_bb41_13, phi_bb41_14, phi_bb41_16, phi_bb41_17, phi_bb41_20, phi_bb41_21, phi_bb41_26});
  }

  TNode<FixedArray> phi_bb42_13;
  TNode<IntPtrT> phi_bb42_14;
  TNode<BoolT> phi_bb42_16;
  TNode<PrimitiveHeapObject> phi_bb42_17;
  TNode<String> phi_bb42_20;
  TNode<String> phi_bb42_21;
  TNode<String> phi_bb42_26;
  TNode<Smi> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<BoolT> tmp56;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_13, &phi_bb42_14, &phi_bb42_16, &phi_bb42_17, &phi_bb42_20, &phi_bb42_21, &phi_bb42_26);
    tmp53 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb8_10});
    tmp54 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb42_13});
    tmp55 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp56 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb42_14}, TNode<IntPtrT>{tmp55});
    ca_.Branch(tmp56, &block45, std::vector<compiler::Node*>{phi_bb42_13, phi_bb42_14, phi_bb42_16, phi_bb42_17, phi_bb42_20, phi_bb42_21, phi_bb42_26}, &block46, std::vector<compiler::Node*>{phi_bb42_13, phi_bb42_14, phi_bb42_16, phi_bb42_17, phi_bb42_20, phi_bb42_21, phi_bb42_26});
  }

  TNode<FixedArray> phi_bb46_13;
  TNode<IntPtrT> phi_bb46_14;
  TNode<BoolT> phi_bb46_16;
  TNode<PrimitiveHeapObject> phi_bb46_17;
  TNode<String> phi_bb46_20;
  TNode<String> phi_bb46_21;
  TNode<String> phi_bb46_26;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_13, &phi_bb46_14, &phi_bb46_16, &phi_bb46_17, &phi_bb46_20, &phi_bb46_21, &phi_bb46_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb45_13;
  TNode<IntPtrT> phi_bb45_14;
  TNode<BoolT> phi_bb45_16;
  TNode<PrimitiveHeapObject> phi_bb45_17;
  TNode<String> phi_bb45_20;
  TNode<String> phi_bb45_21;
  TNode<String> phi_bb45_26;
  TNode<BoolT> tmp57;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_13, &phi_bb45_14, &phi_bb45_16, &phi_bb45_17, &phi_bb45_20, &phi_bb45_21, &phi_bb45_26);
    tmp57 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb45_14}, TNode<IntPtrT>{tmp54});
    ca_.Branch(tmp57, &block47, std::vector<compiler::Node*>{phi_bb45_13, phi_bb45_14, phi_bb45_16, phi_bb45_17, phi_bb45_20, phi_bb45_21, phi_bb45_26}, &block48, std::vector<compiler::Node*>{phi_bb45_13, phi_bb45_14, phi_bb45_16, phi_bb45_17, phi_bb45_20, phi_bb45_21, phi_bb45_26});
  }

  TNode<FixedArray> phi_bb48_13;
  TNode<IntPtrT> phi_bb48_14;
  TNode<BoolT> phi_bb48_16;
  TNode<PrimitiveHeapObject> phi_bb48_17;
  TNode<String> phi_bb48_20;
  TNode<String> phi_bb48_21;
  TNode<String> phi_bb48_26;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_13, &phi_bb48_14, &phi_bb48_16, &phi_bb48_17, &phi_bb48_20, &phi_bb48_21, &phi_bb48_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb47_13;
  TNode<IntPtrT> phi_bb47_14;
  TNode<BoolT> phi_bb47_16;
  TNode<PrimitiveHeapObject> phi_bb47_17;
  TNode<String> phi_bb47_20;
  TNode<String> phi_bb47_21;
  TNode<String> phi_bb47_26;
  TNode<BoolT> tmp58;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_13, &phi_bb47_14, &phi_bb47_16, &phi_bb47_17, &phi_bb47_20, &phi_bb47_21, &phi_bb47_26);
    tmp58 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb47_14}, TNode<IntPtrT>{tmp54});
    ca_.Branch(tmp58, &block49, std::vector<compiler::Node*>{phi_bb47_13, phi_bb47_14, phi_bb47_16, phi_bb47_17, phi_bb47_20, phi_bb47_21, phi_bb47_26}, &block50, std::vector<compiler::Node*>{phi_bb47_13, phi_bb47_14, phi_bb47_16, phi_bb47_17, phi_bb47_20, phi_bb47_21, phi_bb47_26});
  }

  TNode<FixedArray> phi_bb49_13;
  TNode<IntPtrT> phi_bb49_14;
  TNode<BoolT> phi_bb49_16;
  TNode<PrimitiveHeapObject> phi_bb49_17;
  TNode<String> phi_bb49_20;
  TNode<String> phi_bb49_21;
  TNode<String> phi_bb49_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<BoolT> tmp66;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_13, &phi_bb49_14, &phi_bb49_16, &phi_bb49_17, &phi_bb49_20, &phi_bb49_21, &phi_bb49_26);
    std::tie(tmp59, tmp60, tmp61) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb49_13}).Flatten();
    tmp62 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp63 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb49_14}, TNode<IntPtrT>{tmp62});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb49_14});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp61});
    tmp66 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp64}, TNode<UintPtrT>{tmp65});
    ca_.Branch(tmp66, &block56, std::vector<compiler::Node*>{phi_bb49_13, phi_bb49_16, phi_bb49_17, phi_bb49_20, phi_bb49_21, phi_bb49_26, phi_bb49_13, phi_bb49_14, phi_bb49_14, phi_bb49_14, phi_bb49_14}, &block57, std::vector<compiler::Node*>{phi_bb49_13, phi_bb49_16, phi_bb49_17, phi_bb49_20, phi_bb49_21, phi_bb49_26, phi_bb49_13, phi_bb49_14, phi_bb49_14, phi_bb49_14, phi_bb49_14});
  }

  TNode<FixedArray> phi_bb56_13;
  TNode<BoolT> phi_bb56_16;
  TNode<PrimitiveHeapObject> phi_bb56_17;
  TNode<String> phi_bb56_20;
  TNode<String> phi_bb56_21;
  TNode<String> phi_bb56_26;
  TNode<FixedArray> phi_bb56_43;
  TNode<IntPtrT> phi_bb56_47;
  TNode<IntPtrT> phi_bb56_48;
  TNode<IntPtrT> phi_bb56_52;
  TNode<IntPtrT> phi_bb56_53;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<Union<HeapObject, TaggedIndex>> tmp69;
  TNode<IntPtrT> tmp70;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_13, &phi_bb56_16, &phi_bb56_17, &phi_bb56_20, &phi_bb56_21, &phi_bb56_26, &phi_bb56_43, &phi_bb56_47, &phi_bb56_48, &phi_bb56_52, &phi_bb56_53);
    tmp67 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb56_53});
    tmp68 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp67});
    std::tie(tmp69, tmp70) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp68}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp69, tmp70}, tmp53);
    ca_.Goto(&block51, phi_bb56_13, tmp63, phi_bb56_16, phi_bb56_17, phi_bb56_20, phi_bb56_21, phi_bb56_26);
  }

  TNode<FixedArray> phi_bb57_13;
  TNode<BoolT> phi_bb57_16;
  TNode<PrimitiveHeapObject> phi_bb57_17;
  TNode<String> phi_bb57_20;
  TNode<String> phi_bb57_21;
  TNode<String> phi_bb57_26;
  TNode<FixedArray> phi_bb57_43;
  TNode<IntPtrT> phi_bb57_47;
  TNode<IntPtrT> phi_bb57_48;
  TNode<IntPtrT> phi_bb57_52;
  TNode<IntPtrT> phi_bb57_53;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_13, &phi_bb57_16, &phi_bb57_17, &phi_bb57_20, &phi_bb57_21, &phi_bb57_26, &phi_bb57_43, &phi_bb57_47, &phi_bb57_48, &phi_bb57_52, &phi_bb57_53);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb50_13;
  TNode<IntPtrT> phi_bb50_14;
  TNode<BoolT> phi_bb50_16;
  TNode<PrimitiveHeapObject> phi_bb50_17;
  TNode<String> phi_bb50_20;
  TNode<String> phi_bb50_21;
  TNode<String> phi_bb50_26;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<BoolT> tmp73;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_13, &phi_bb50_14, &phi_bb50_16, &phi_bb50_17, &phi_bb50_20, &phi_bb50_21, &phi_bb50_26);
    tmp71 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp54});
    tmp72 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp73 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp71}, TNode<IntPtrT>{tmp72});
    ca_.Branch(tmp73, &block60, std::vector<compiler::Node*>{phi_bb50_13, phi_bb50_14, phi_bb50_16, phi_bb50_17, phi_bb50_20, phi_bb50_21, phi_bb50_26}, &block61, std::vector<compiler::Node*>{phi_bb50_13, phi_bb50_14, phi_bb50_16, phi_bb50_17, phi_bb50_20, phi_bb50_21, phi_bb50_26});
  }

  TNode<FixedArray> phi_bb60_13;
  TNode<IntPtrT> phi_bb60_14;
  TNode<BoolT> phi_bb60_16;
  TNode<PrimitiveHeapObject> phi_bb60_17;
  TNode<String> phi_bb60_20;
  TNode<String> phi_bb60_21;
  TNode<String> phi_bb60_26;
  TNode<IntPtrT> tmp74;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_13, &phi_bb60_14, &phi_bb60_16, &phi_bb60_17, &phi_bb60_20, &phi_bb60_21, &phi_bb60_26);
    tmp74 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block62, phi_bb60_13, phi_bb60_14, phi_bb60_16, phi_bb60_17, phi_bb60_20, phi_bb60_21, phi_bb60_26, tmp74);
  }

  TNode<FixedArray> phi_bb61_13;
  TNode<IntPtrT> phi_bb61_14;
  TNode<BoolT> phi_bb61_16;
  TNode<PrimitiveHeapObject> phi_bb61_17;
  TNode<String> phi_bb61_20;
  TNode<String> phi_bb61_21;
  TNode<String> phi_bb61_26;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_13, &phi_bb61_14, &phi_bb61_16, &phi_bb61_17, &phi_bb61_20, &phi_bb61_21, &phi_bb61_26);
    ca_.Goto(&block62, phi_bb61_13, phi_bb61_14, phi_bb61_16, phi_bb61_17, phi_bb61_20, phi_bb61_21, phi_bb61_26, tmp71);
  }

  TNode<FixedArray> phi_bb62_13;
  TNode<IntPtrT> phi_bb62_14;
  TNode<BoolT> phi_bb62_16;
  TNode<PrimitiveHeapObject> phi_bb62_17;
  TNode<String> phi_bb62_20;
  TNode<String> phi_bb62_21;
  TNode<String> phi_bb62_26;
  TNode<IntPtrT> phi_bb62_44;
  TNode<IntPtrT> tmp75;
  TNode<BoolT> tmp76;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_13, &phi_bb62_14, &phi_bb62_16, &phi_bb62_17, &phi_bb62_20, &phi_bb62_21, &phi_bb62_26, &phi_bb62_44);
    tmp75 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp76 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb62_44}, TNode<IntPtrT>{tmp75});
    ca_.Branch(tmp76, &block64, std::vector<compiler::Node*>{phi_bb62_13, phi_bb62_14, phi_bb62_16, phi_bb62_17, phi_bb62_20, phi_bb62_21, phi_bb62_26}, &block65, std::vector<compiler::Node*>{phi_bb62_13, phi_bb62_14, phi_bb62_16, phi_bb62_17, phi_bb62_20, phi_bb62_21, phi_bb62_26});
  }

  TNode<FixedArray> phi_bb65_13;
  TNode<IntPtrT> phi_bb65_14;
  TNode<BoolT> phi_bb65_16;
  TNode<PrimitiveHeapObject> phi_bb65_17;
  TNode<String> phi_bb65_20;
  TNode<String> phi_bb65_21;
  TNode<String> phi_bb65_26;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_13, &phi_bb65_14, &phi_bb65_16, &phi_bb65_17, &phi_bb65_20, &phi_bb65_21, &phi_bb65_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb64_13;
  TNode<IntPtrT> phi_bb64_14;
  TNode<BoolT> phi_bb64_16;
  TNode<PrimitiveHeapObject> phi_bb64_17;
  TNode<String> phi_bb64_20;
  TNode<String> phi_bb64_21;
  TNode<String> phi_bb64_26;
  TNode<FixedArray> tmp77;
  TNode<Union<HeapObject, TaggedIndex>> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<UintPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<UintPtrT> tmp83;
  TNode<UintPtrT> tmp84;
  TNode<BoolT> tmp85;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_13, &phi_bb64_14, &phi_bb64_16, &phi_bb64_17, &phi_bb64_20, &phi_bb64_21, &phi_bb64_26);
    tmp77 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb62_44});
    std::tie(tmp78, tmp79, tmp80) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb64_13}).Flatten();
    tmp81 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp82 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp81});
    tmp83 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp82});
    tmp84 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp80});
    tmp85 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp83}, TNode<UintPtrT>{tmp84});
    ca_.Branch(tmp85, &block71, std::vector<compiler::Node*>{phi_bb64_13, phi_bb64_14, phi_bb64_16, phi_bb64_17, phi_bb64_20, phi_bb64_21, phi_bb64_26, phi_bb64_13}, &block72, std::vector<compiler::Node*>{phi_bb64_13, phi_bb64_14, phi_bb64_16, phi_bb64_17, phi_bb64_20, phi_bb64_21, phi_bb64_26, phi_bb64_13});
  }

  TNode<FixedArray> phi_bb71_13;
  TNode<IntPtrT> phi_bb71_14;
  TNode<BoolT> phi_bb71_16;
  TNode<PrimitiveHeapObject> phi_bb71_17;
  TNode<String> phi_bb71_20;
  TNode<String> phi_bb71_21;
  TNode<String> phi_bb71_26;
  TNode<FixedArray> phi_bb71_46;
  TNode<IntPtrT> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<Union<HeapObject, TaggedIndex>> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Union<HeapObject, TaggedIndex>> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<UintPtrT> tmp93;
  TNode<IntPtrT> tmp94;
  TNode<UintPtrT> tmp95;
  TNode<UintPtrT> tmp96;
  TNode<BoolT> tmp97;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_13, &phi_bb71_14, &phi_bb71_16, &phi_bb71_17, &phi_bb71_20, &phi_bb71_21, &phi_bb71_26, &phi_bb71_46);
    tmp86 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp82});
    tmp87 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp79}, TNode<IntPtrT>{tmp86});
    std::tie(tmp88, tmp89) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp78}, TNode<IntPtrT>{tmp87}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp88, tmp89}, tmp77);
    std::tie(tmp90, tmp91, tmp92) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp77}).Flatten();
    tmp93 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp94 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp93});
    tmp95 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp94});
    tmp96 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp92});
    tmp97 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp95}, TNode<UintPtrT>{tmp96});
    ca_.Branch(tmp97, &block80, std::vector<compiler::Node*>{phi_bb71_13, phi_bb71_14, phi_bb71_16, phi_bb71_17, phi_bb71_20, phi_bb71_21, phi_bb71_26}, &block81, std::vector<compiler::Node*>{phi_bb71_13, phi_bb71_14, phi_bb71_16, phi_bb71_17, phi_bb71_20, phi_bb71_21, phi_bb71_26});
  }

  TNode<FixedArray> phi_bb72_13;
  TNode<IntPtrT> phi_bb72_14;
  TNode<BoolT> phi_bb72_16;
  TNode<PrimitiveHeapObject> phi_bb72_17;
  TNode<String> phi_bb72_20;
  TNode<String> phi_bb72_21;
  TNode<String> phi_bb72_26;
  TNode<FixedArray> phi_bb72_46;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_13, &phi_bb72_14, &phi_bb72_16, &phi_bb72_17, &phi_bb72_20, &phi_bb72_21, &phi_bb72_26, &phi_bb72_46);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb80_13;
  TNode<IntPtrT> phi_bb80_14;
  TNode<BoolT> phi_bb80_16;
  TNode<PrimitiveHeapObject> phi_bb80_17;
  TNode<String> phi_bb80_20;
  TNode<String> phi_bb80_21;
  TNode<String> phi_bb80_26;
  TNode<IntPtrT> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<Union<HeapObject, TaggedIndex>> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<Undefined> tmp102;
  TNode<Union<HeapObject, TaggedIndex>> tmp103;
  TNode<IntPtrT> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<UintPtrT> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<UintPtrT> tmp108;
  TNode<UintPtrT> tmp109;
  TNode<BoolT> tmp110;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_13, &phi_bb80_14, &phi_bb80_16, &phi_bb80_17, &phi_bb80_20, &phi_bb80_21, &phi_bb80_26);
    tmp98 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp94});
    tmp99 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp91}, TNode<IntPtrT>{tmp98});
    std::tie(tmp100, tmp101) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp90}, TNode<IntPtrT>{tmp99}).Flatten();
    tmp102 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp100, tmp101}, tmp102);
    std::tie(tmp103, tmp104, tmp105) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp77}).Flatten();
    tmp106 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp107 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp106});
    tmp108 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp107});
    tmp109 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp105});
    tmp110 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp108}, TNode<UintPtrT>{tmp109});
    ca_.Branch(tmp110, &block89, std::vector<compiler::Node*>{phi_bb80_13, phi_bb80_14, phi_bb80_16, phi_bb80_17, phi_bb80_20, phi_bb80_21, phi_bb80_26}, &block90, std::vector<compiler::Node*>{phi_bb80_13, phi_bb80_14, phi_bb80_16, phi_bb80_17, phi_bb80_20, phi_bb80_21, phi_bb80_26});
  }

  TNode<FixedArray> phi_bb81_13;
  TNode<IntPtrT> phi_bb81_14;
  TNode<BoolT> phi_bb81_16;
  TNode<PrimitiveHeapObject> phi_bb81_17;
  TNode<String> phi_bb81_20;
  TNode<String> phi_bb81_21;
  TNode<String> phi_bb81_26;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_13, &phi_bb81_14, &phi_bb81_16, &phi_bb81_17, &phi_bb81_20, &phi_bb81_21, &phi_bb81_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb89_13;
  TNode<IntPtrT> phi_bb89_14;
  TNode<BoolT> phi_bb89_16;
  TNode<PrimitiveHeapObject> phi_bb89_17;
  TNode<String> phi_bb89_20;
  TNode<String> phi_bb89_21;
  TNode<String> phi_bb89_26;
  TNode<IntPtrT> tmp111;
  TNode<IntPtrT> tmp112;
  TNode<Union<HeapObject, TaggedIndex>> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<IntPtrT> tmp115;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_13, &phi_bb89_14, &phi_bb89_16, &phi_bb89_17, &phi_bb89_20, &phi_bb89_21, &phi_bb89_26);
    tmp111 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp107});
    tmp112 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp104}, TNode<IntPtrT>{tmp111});
    std::tie(tmp113, tmp114) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp103}, TNode<IntPtrT>{tmp112}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp113, tmp114}, tmp53);
    tmp115 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block51, tmp77, tmp115, phi_bb89_16, phi_bb89_17, phi_bb89_20, phi_bb89_21, phi_bb89_26);
  }

  TNode<FixedArray> phi_bb90_13;
  TNode<IntPtrT> phi_bb90_14;
  TNode<BoolT> phi_bb90_16;
  TNode<PrimitiveHeapObject> phi_bb90_17;
  TNode<String> phi_bb90_20;
  TNode<String> phi_bb90_21;
  TNode<String> phi_bb90_26;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_13, &phi_bb90_14, &phi_bb90_16, &phi_bb90_17, &phi_bb90_20, &phi_bb90_21, &phi_bb90_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb51_13;
  TNode<IntPtrT> phi_bb51_14;
  TNode<BoolT> phi_bb51_16;
  TNode<PrimitiveHeapObject> phi_bb51_17;
  TNode<String> phi_bb51_20;
  TNode<String> phi_bb51_21;
  TNode<String> phi_bb51_26;
  TNode<Null> tmp116;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_13, &phi_bb51_14, &phi_bb51_16, &phi_bb51_17, &phi_bb51_20, &phi_bb51_21, &phi_bb51_26);
    tmp116 = Null_0(state_);
    ca_.Goto(&block43, phi_bb51_13, phi_bb51_14, phi_bb51_16, tmp116, phi_bb51_20, phi_bb51_21, phi_bb51_26);
  }

  TNode<FixedArray> phi_bb43_13;
  TNode<IntPtrT> phi_bb43_14;
  TNode<BoolT> phi_bb43_16;
  TNode<PrimitiveHeapObject> phi_bb43_17;
  TNode<String> phi_bb43_20;
  TNode<String> phi_bb43_21;
  TNode<String> phi_bb43_26;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_13, &phi_bb43_14, &phi_bb43_16, &phi_bb43_17, &phi_bb43_20, &phi_bb43_21, &phi_bb43_26);
    ca_.Goto(&block34, phi_bb43_13, phi_bb43_14, tmp52, phi_bb43_16, phi_bb43_17, phi_bb43_20, phi_bb43_21, phi_bb43_26);
  }

  TNode<FixedArray> phi_bb34_13;
  TNode<IntPtrT> phi_bb34_14;
  TNode<IntPtrT> phi_bb34_15;
  TNode<BoolT> phi_bb34_16;
  TNode<PrimitiveHeapObject> phi_bb34_17;
  TNode<String> phi_bb34_20;
  TNode<String> phi_bb34_21;
  TNode<String> phi_bb34_26;
  TNode<IntPtrT> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<BoolT> tmp119;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_13, &phi_bb34_14, &phi_bb34_15, &phi_bb34_16, &phi_bb34_17, &phi_bb34_20, &phi_bb34_21, &phi_bb34_26);
    tmp117 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{phi_bb34_26});
    tmp118 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb34_15}, TNode<IntPtrT>{tmp117});
    tmp119 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{phi_bb34_26}, TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{phi_bb34_17});
    ca_.Branch(tmp119, &block93, std::vector<compiler::Node*>{phi_bb34_13, phi_bb34_14, phi_bb34_16, phi_bb34_17, phi_bb34_20, phi_bb34_21, phi_bb34_26}, &block94, std::vector<compiler::Node*>{phi_bb34_13, phi_bb34_14, phi_bb34_16, phi_bb34_17, phi_bb34_20, phi_bb34_21, phi_bb34_26});
  }

  TNode<FixedArray> phi_bb93_13;
  TNode<IntPtrT> phi_bb93_14;
  TNode<BoolT> phi_bb93_16;
  TNode<PrimitiveHeapObject> phi_bb93_17;
  TNode<String> phi_bb93_20;
  TNode<String> phi_bb93_21;
  TNode<String> phi_bb93_26;
  TNode<IntPtrT> tmp120;
  TNode<BoolT> tmp121;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_13, &phi_bb93_14, &phi_bb93_16, &phi_bb93_17, &phi_bb93_20, &phi_bb93_21, &phi_bb93_26);
    tmp120 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp121 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb93_14}, TNode<IntPtrT>{tmp120});
    ca_.Branch(tmp121, &block97, std::vector<compiler::Node*>{phi_bb93_13, phi_bb93_14, phi_bb93_16, phi_bb93_17, phi_bb93_20, phi_bb93_21, phi_bb93_26}, &block98, std::vector<compiler::Node*>{phi_bb93_13, phi_bb93_14, phi_bb93_16, phi_bb93_17, phi_bb93_20, phi_bb93_21, phi_bb93_26});
  }

  TNode<FixedArray> phi_bb98_13;
  TNode<IntPtrT> phi_bb98_14;
  TNode<BoolT> phi_bb98_16;
  TNode<PrimitiveHeapObject> phi_bb98_17;
  TNode<String> phi_bb98_20;
  TNode<String> phi_bb98_21;
  TNode<String> phi_bb98_26;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_13, &phi_bb98_14, &phi_bb98_16, &phi_bb98_17, &phi_bb98_20, &phi_bb98_21, &phi_bb98_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 223});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index > 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb97_13;
  TNode<IntPtrT> phi_bb97_14;
  TNode<BoolT> phi_bb97_16;
  TNode<PrimitiveHeapObject> phi_bb97_17;
  TNode<String> phi_bb97_20;
  TNode<String> phi_bb97_21;
  TNode<String> phi_bb97_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp122;
  TNode<IntPtrT> tmp123;
  TNode<IntPtrT> tmp124;
  TNode<IntPtrT> tmp125;
  TNode<IntPtrT> tmp126;
  TNode<UintPtrT> tmp127;
  TNode<UintPtrT> tmp128;
  TNode<BoolT> tmp129;
  if (block97.is_used()) {
    ca_.Bind(&block97, &phi_bb97_13, &phi_bb97_14, &phi_bb97_16, &phi_bb97_17, &phi_bb97_20, &phi_bb97_21, &phi_bb97_26);
    std::tie(tmp122, tmp123, tmp124) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb97_13}).Flatten();
    tmp125 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp126 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb97_14}, TNode<IntPtrT>{tmp125});
    tmp127 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp126});
    tmp128 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp124});
    tmp129 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp127}, TNode<UintPtrT>{tmp128});
    ca_.Branch(tmp129, &block103, std::vector<compiler::Node*>{phi_bb97_13, phi_bb97_14, phi_bb97_16, phi_bb97_17, phi_bb97_20, phi_bb97_21, phi_bb97_26, phi_bb97_13}, &block104, std::vector<compiler::Node*>{phi_bb97_13, phi_bb97_14, phi_bb97_16, phi_bb97_17, phi_bb97_20, phi_bb97_21, phi_bb97_26, phi_bb97_13});
  }

  TNode<FixedArray> phi_bb103_13;
  TNode<IntPtrT> phi_bb103_14;
  TNode<BoolT> phi_bb103_16;
  TNode<PrimitiveHeapObject> phi_bb103_17;
  TNode<String> phi_bb103_20;
  TNode<String> phi_bb103_21;
  TNode<String> phi_bb103_26;
  TNode<FixedArray> phi_bb103_30;
  TNode<IntPtrT> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<Union<HeapObject, TaggedIndex>> tmp132;
  TNode<IntPtrT> tmp133;
  TNode<Object> tmp134;
  TNode<HeapObject> tmp135;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_13, &phi_bb103_14, &phi_bb103_16, &phi_bb103_17, &phi_bb103_20, &phi_bb103_21, &phi_bb103_26, &phi_bb103_30);
    tmp130 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp126});
    tmp131 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp123}, TNode<IntPtrT>{tmp130});
    std::tie(tmp132, tmp133) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp122}, TNode<IntPtrT>{tmp131}).Flatten();
    tmp134 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp132, tmp133});
    compiler::CodeAssemblerLabel label136(&ca_);
    tmp135 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{tmp134}, &label136);
    ca_.Goto(&block110, phi_bb103_13, phi_bb103_14, phi_bb103_16, phi_bb103_17, phi_bb103_20, phi_bb103_21, phi_bb103_26);
    if (label136.is_used()) {
      ca_.Bind(&label136);
      ca_.Goto(&block111, phi_bb103_13, phi_bb103_14, phi_bb103_16, phi_bb103_17, phi_bb103_20, phi_bb103_21, phi_bb103_26);
    }
  }

  TNode<FixedArray> phi_bb104_13;
  TNode<IntPtrT> phi_bb104_14;
  TNode<BoolT> phi_bb104_16;
  TNode<PrimitiveHeapObject> phi_bb104_17;
  TNode<String> phi_bb104_20;
  TNode<String> phi_bb104_21;
  TNode<String> phi_bb104_26;
  TNode<FixedArray> phi_bb104_30;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_13, &phi_bb104_14, &phi_bb104_16, &phi_bb104_17, &phi_bb104_20, &phi_bb104_21, &phi_bb104_26, &phi_bb104_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb111_13;
  TNode<IntPtrT> phi_bb111_14;
  TNode<BoolT> phi_bb111_16;
  TNode<PrimitiveHeapObject> phi_bb111_17;
  TNode<String> phi_bb111_20;
  TNode<String> phi_bb111_21;
  TNode<String> phi_bb111_26;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_13, &phi_bb111_14, &phi_bb111_16, &phi_bb111_17, &phi_bb111_20, &phi_bb111_21, &phi_bb111_26);
    ca_.Goto(&block108, phi_bb111_13, phi_bb111_14, phi_bb111_16, phi_bb111_17, phi_bb111_20, phi_bb111_21, phi_bb111_26);
  }

  TNode<FixedArray> phi_bb110_13;
  TNode<IntPtrT> phi_bb110_14;
  TNode<BoolT> phi_bb110_16;
  TNode<PrimitiveHeapObject> phi_bb110_17;
  TNode<String> phi_bb110_20;
  TNode<String> phi_bb110_21;
  TNode<String> phi_bb110_26;
  TNode<String> tmp137;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_13, &phi_bb110_14, &phi_bb110_16, &phi_bb110_17, &phi_bb110_20, &phi_bb110_21, &phi_bb110_26);
    compiler::CodeAssemblerLabel label138(&ca_);
    tmp137 = Cast_String_0(state_, TNode<HeapObject>{tmp135}, &label138);
    ca_.Goto(&block112, phi_bb110_13, phi_bb110_14, phi_bb110_16, phi_bb110_17, phi_bb110_20, phi_bb110_21, phi_bb110_26);
    if (label138.is_used()) {
      ca_.Bind(&label138);
      ca_.Goto(&block113, phi_bb110_13, phi_bb110_14, phi_bb110_16, phi_bb110_17, phi_bb110_20, phi_bb110_21, phi_bb110_26);
    }
  }

  TNode<FixedArray> phi_bb113_13;
  TNode<IntPtrT> phi_bb113_14;
  TNode<BoolT> phi_bb113_16;
  TNode<PrimitiveHeapObject> phi_bb113_17;
  TNode<String> phi_bb113_20;
  TNode<String> phi_bb113_21;
  TNode<String> phi_bb113_26;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_13, &phi_bb113_14, &phi_bb113_16, &phi_bb113_17, &phi_bb113_20, &phi_bb113_21, &phi_bb113_26);
    ca_.Goto(&block108, phi_bb113_13, phi_bb113_14, phi_bb113_16, phi_bb113_17, phi_bb113_20, phi_bb113_21, phi_bb113_26);
  }

  TNode<FixedArray> phi_bb112_13;
  TNode<IntPtrT> phi_bb112_14;
  TNode<BoolT> phi_bb112_16;
  TNode<PrimitiveHeapObject> phi_bb112_17;
  TNode<String> phi_bb112_20;
  TNode<String> phi_bb112_21;
  TNode<String> phi_bb112_26;
  TNode<Smi> tmp139;
  TNode<IntPtrT> tmp140;
  TNode<IntPtrT> tmp141;
  TNode<BoolT> tmp142;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_13, &phi_bb112_14, &phi_bb112_16, &phi_bb112_17, &phi_bb112_20, &phi_bb112_21, &phi_bb112_26);
    tmp139 = SmiConstant_0(state_, IntegerLiteral(true, 0x1ull));
    tmp140 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb112_13});
    tmp141 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp142 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb112_14}, TNode<IntPtrT>{tmp141});
    ca_.Branch(tmp142, &block115, std::vector<compiler::Node*>{phi_bb112_13, phi_bb112_14, phi_bb112_16, phi_bb112_17, phi_bb112_20, phi_bb112_21, phi_bb112_26}, &block116, std::vector<compiler::Node*>{phi_bb112_13, phi_bb112_14, phi_bb112_16, phi_bb112_17, phi_bb112_20, phi_bb112_21, phi_bb112_26});
  }

  TNode<FixedArray> phi_bb116_13;
  TNode<IntPtrT> phi_bb116_14;
  TNode<BoolT> phi_bb116_16;
  TNode<PrimitiveHeapObject> phi_bb116_17;
  TNode<String> phi_bb116_20;
  TNode<String> phi_bb116_21;
  TNode<String> phi_bb116_26;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_13, &phi_bb116_14, &phi_bb116_16, &phi_bb116_17, &phi_bb116_20, &phi_bb116_21, &phi_bb116_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb115_13;
  TNode<IntPtrT> phi_bb115_14;
  TNode<BoolT> phi_bb115_16;
  TNode<PrimitiveHeapObject> phi_bb115_17;
  TNode<String> phi_bb115_20;
  TNode<String> phi_bb115_21;
  TNode<String> phi_bb115_26;
  TNode<BoolT> tmp143;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_13, &phi_bb115_14, &phi_bb115_16, &phi_bb115_17, &phi_bb115_20, &phi_bb115_21, &phi_bb115_26);
    tmp143 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb115_14}, TNode<IntPtrT>{tmp140});
    ca_.Branch(tmp143, &block117, std::vector<compiler::Node*>{phi_bb115_13, phi_bb115_14, phi_bb115_16, phi_bb115_17, phi_bb115_20, phi_bb115_21, phi_bb115_26}, &block118, std::vector<compiler::Node*>{phi_bb115_13, phi_bb115_14, phi_bb115_16, phi_bb115_17, phi_bb115_20, phi_bb115_21, phi_bb115_26});
  }

  TNode<FixedArray> phi_bb118_13;
  TNode<IntPtrT> phi_bb118_14;
  TNode<BoolT> phi_bb118_16;
  TNode<PrimitiveHeapObject> phi_bb118_17;
  TNode<String> phi_bb118_20;
  TNode<String> phi_bb118_21;
  TNode<String> phi_bb118_26;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_13, &phi_bb118_14, &phi_bb118_16, &phi_bb118_17, &phi_bb118_20, &phi_bb118_21, &phi_bb118_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb117_13;
  TNode<IntPtrT> phi_bb117_14;
  TNode<BoolT> phi_bb117_16;
  TNode<PrimitiveHeapObject> phi_bb117_17;
  TNode<String> phi_bb117_20;
  TNode<String> phi_bb117_21;
  TNode<String> phi_bb117_26;
  TNode<BoolT> tmp144;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_13, &phi_bb117_14, &phi_bb117_16, &phi_bb117_17, &phi_bb117_20, &phi_bb117_21, &phi_bb117_26);
    tmp144 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb117_14}, TNode<IntPtrT>{tmp140});
    ca_.Branch(tmp144, &block119, std::vector<compiler::Node*>{phi_bb117_13, phi_bb117_14, phi_bb117_16, phi_bb117_17, phi_bb117_20, phi_bb117_21, phi_bb117_26}, &block120, std::vector<compiler::Node*>{phi_bb117_13, phi_bb117_14, phi_bb117_16, phi_bb117_17, phi_bb117_20, phi_bb117_21, phi_bb117_26});
  }

  TNode<FixedArray> phi_bb119_13;
  TNode<IntPtrT> phi_bb119_14;
  TNode<BoolT> phi_bb119_16;
  TNode<PrimitiveHeapObject> phi_bb119_17;
  TNode<String> phi_bb119_20;
  TNode<String> phi_bb119_21;
  TNode<String> phi_bb119_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp145;
  TNode<IntPtrT> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<IntPtrT> tmp148;
  TNode<IntPtrT> tmp149;
  TNode<UintPtrT> tmp150;
  TNode<UintPtrT> tmp151;
  TNode<BoolT> tmp152;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_13, &phi_bb119_14, &phi_bb119_16, &phi_bb119_17, &phi_bb119_20, &phi_bb119_21, &phi_bb119_26);
    std::tie(tmp145, tmp146, tmp147) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb119_13}).Flatten();
    tmp148 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp149 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb119_14}, TNode<IntPtrT>{tmp148});
    tmp150 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb119_14});
    tmp151 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp147});
    tmp152 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp150}, TNode<UintPtrT>{tmp151});
    ca_.Branch(tmp152, &block126, std::vector<compiler::Node*>{phi_bb119_13, phi_bb119_16, phi_bb119_17, phi_bb119_20, phi_bb119_21, phi_bb119_26, phi_bb119_13, phi_bb119_14, phi_bb119_14, phi_bb119_14, phi_bb119_14}, &block127, std::vector<compiler::Node*>{phi_bb119_13, phi_bb119_16, phi_bb119_17, phi_bb119_20, phi_bb119_21, phi_bb119_26, phi_bb119_13, phi_bb119_14, phi_bb119_14, phi_bb119_14, phi_bb119_14});
  }

  TNode<FixedArray> phi_bb126_13;
  TNode<BoolT> phi_bb126_16;
  TNode<PrimitiveHeapObject> phi_bb126_17;
  TNode<String> phi_bb126_20;
  TNode<String> phi_bb126_21;
  TNode<String> phi_bb126_26;
  TNode<FixedArray> phi_bb126_35;
  TNode<IntPtrT> phi_bb126_39;
  TNode<IntPtrT> phi_bb126_40;
  TNode<IntPtrT> phi_bb126_44;
  TNode<IntPtrT> phi_bb126_45;
  TNode<IntPtrT> tmp153;
  TNode<IntPtrT> tmp154;
  TNode<Union<HeapObject, TaggedIndex>> tmp155;
  TNode<IntPtrT> tmp156;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_13, &phi_bb126_16, &phi_bb126_17, &phi_bb126_20, &phi_bb126_21, &phi_bb126_26, &phi_bb126_35, &phi_bb126_39, &phi_bb126_40, &phi_bb126_44, &phi_bb126_45);
    tmp153 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb126_45});
    tmp154 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp146}, TNode<IntPtrT>{tmp153});
    std::tie(tmp155, tmp156) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp145}, TNode<IntPtrT>{tmp154}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp155, tmp156}, tmp139);
    ca_.Goto(&block121, phi_bb126_13, tmp149, phi_bb126_16, phi_bb126_17, phi_bb126_20, phi_bb126_21, phi_bb126_26);
  }

  TNode<FixedArray> phi_bb127_13;
  TNode<BoolT> phi_bb127_16;
  TNode<PrimitiveHeapObject> phi_bb127_17;
  TNode<String> phi_bb127_20;
  TNode<String> phi_bb127_21;
  TNode<String> phi_bb127_26;
  TNode<FixedArray> phi_bb127_35;
  TNode<IntPtrT> phi_bb127_39;
  TNode<IntPtrT> phi_bb127_40;
  TNode<IntPtrT> phi_bb127_44;
  TNode<IntPtrT> phi_bb127_45;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_13, &phi_bb127_16, &phi_bb127_17, &phi_bb127_20, &phi_bb127_21, &phi_bb127_26, &phi_bb127_35, &phi_bb127_39, &phi_bb127_40, &phi_bb127_44, &phi_bb127_45);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb120_13;
  TNode<IntPtrT> phi_bb120_14;
  TNode<BoolT> phi_bb120_16;
  TNode<PrimitiveHeapObject> phi_bb120_17;
  TNode<String> phi_bb120_20;
  TNode<String> phi_bb120_21;
  TNode<String> phi_bb120_26;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<BoolT> tmp159;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_13, &phi_bb120_14, &phi_bb120_16, &phi_bb120_17, &phi_bb120_20, &phi_bb120_21, &phi_bb120_26);
    tmp157 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp140});
    tmp158 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp159 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp157}, TNode<IntPtrT>{tmp158});
    ca_.Branch(tmp159, &block130, std::vector<compiler::Node*>{phi_bb120_13, phi_bb120_14, phi_bb120_16, phi_bb120_17, phi_bb120_20, phi_bb120_21, phi_bb120_26}, &block131, std::vector<compiler::Node*>{phi_bb120_13, phi_bb120_14, phi_bb120_16, phi_bb120_17, phi_bb120_20, phi_bb120_21, phi_bb120_26});
  }

  TNode<FixedArray> phi_bb130_13;
  TNode<IntPtrT> phi_bb130_14;
  TNode<BoolT> phi_bb130_16;
  TNode<PrimitiveHeapObject> phi_bb130_17;
  TNode<String> phi_bb130_20;
  TNode<String> phi_bb130_21;
  TNode<String> phi_bb130_26;
  TNode<IntPtrT> tmp160;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_13, &phi_bb130_14, &phi_bb130_16, &phi_bb130_17, &phi_bb130_20, &phi_bb130_21, &phi_bb130_26);
    tmp160 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block132, phi_bb130_13, phi_bb130_14, phi_bb130_16, phi_bb130_17, phi_bb130_20, phi_bb130_21, phi_bb130_26, tmp160);
  }

  TNode<FixedArray> phi_bb131_13;
  TNode<IntPtrT> phi_bb131_14;
  TNode<BoolT> phi_bb131_16;
  TNode<PrimitiveHeapObject> phi_bb131_17;
  TNode<String> phi_bb131_20;
  TNode<String> phi_bb131_21;
  TNode<String> phi_bb131_26;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_13, &phi_bb131_14, &phi_bb131_16, &phi_bb131_17, &phi_bb131_20, &phi_bb131_21, &phi_bb131_26);
    ca_.Goto(&block132, phi_bb131_13, phi_bb131_14, phi_bb131_16, phi_bb131_17, phi_bb131_20, phi_bb131_21, phi_bb131_26, tmp157);
  }

  TNode<FixedArray> phi_bb132_13;
  TNode<IntPtrT> phi_bb132_14;
  TNode<BoolT> phi_bb132_16;
  TNode<PrimitiveHeapObject> phi_bb132_17;
  TNode<String> phi_bb132_20;
  TNode<String> phi_bb132_21;
  TNode<String> phi_bb132_26;
  TNode<IntPtrT> phi_bb132_36;
  TNode<IntPtrT> tmp161;
  TNode<BoolT> tmp162;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_13, &phi_bb132_14, &phi_bb132_16, &phi_bb132_17, &phi_bb132_20, &phi_bb132_21, &phi_bb132_26, &phi_bb132_36);
    tmp161 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp162 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb132_36}, TNode<IntPtrT>{tmp161});
    ca_.Branch(tmp162, &block134, std::vector<compiler::Node*>{phi_bb132_13, phi_bb132_14, phi_bb132_16, phi_bb132_17, phi_bb132_20, phi_bb132_21, phi_bb132_26}, &block135, std::vector<compiler::Node*>{phi_bb132_13, phi_bb132_14, phi_bb132_16, phi_bb132_17, phi_bb132_20, phi_bb132_21, phi_bb132_26});
  }

  TNode<FixedArray> phi_bb135_13;
  TNode<IntPtrT> phi_bb135_14;
  TNode<BoolT> phi_bb135_16;
  TNode<PrimitiveHeapObject> phi_bb135_17;
  TNode<String> phi_bb135_20;
  TNode<String> phi_bb135_21;
  TNode<String> phi_bb135_26;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_13, &phi_bb135_14, &phi_bb135_16, &phi_bb135_17, &phi_bb135_20, &phi_bb135_21, &phi_bb135_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb134_13;
  TNode<IntPtrT> phi_bb134_14;
  TNode<BoolT> phi_bb134_16;
  TNode<PrimitiveHeapObject> phi_bb134_17;
  TNode<String> phi_bb134_20;
  TNode<String> phi_bb134_21;
  TNode<String> phi_bb134_26;
  TNode<FixedArray> tmp163;
  TNode<Union<HeapObject, TaggedIndex>> tmp164;
  TNode<IntPtrT> tmp165;
  TNode<IntPtrT> tmp166;
  TNode<UintPtrT> tmp167;
  TNode<IntPtrT> tmp168;
  TNode<UintPtrT> tmp169;
  TNode<UintPtrT> tmp170;
  TNode<BoolT> tmp171;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_13, &phi_bb134_14, &phi_bb134_16, &phi_bb134_17, &phi_bb134_20, &phi_bb134_21, &phi_bb134_26);
    tmp163 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb132_36});
    std::tie(tmp164, tmp165, tmp166) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb134_13}).Flatten();
    tmp167 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp168 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp167});
    tmp169 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp168});
    tmp170 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp166});
    tmp171 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp169}, TNode<UintPtrT>{tmp170});
    ca_.Branch(tmp171, &block141, std::vector<compiler::Node*>{phi_bb134_13, phi_bb134_14, phi_bb134_16, phi_bb134_17, phi_bb134_20, phi_bb134_21, phi_bb134_26, phi_bb134_13}, &block142, std::vector<compiler::Node*>{phi_bb134_13, phi_bb134_14, phi_bb134_16, phi_bb134_17, phi_bb134_20, phi_bb134_21, phi_bb134_26, phi_bb134_13});
  }

  TNode<FixedArray> phi_bb141_13;
  TNode<IntPtrT> phi_bb141_14;
  TNode<BoolT> phi_bb141_16;
  TNode<PrimitiveHeapObject> phi_bb141_17;
  TNode<String> phi_bb141_20;
  TNode<String> phi_bb141_21;
  TNode<String> phi_bb141_26;
  TNode<FixedArray> phi_bb141_38;
  TNode<IntPtrT> tmp172;
  TNode<IntPtrT> tmp173;
  TNode<Union<HeapObject, TaggedIndex>> tmp174;
  TNode<IntPtrT> tmp175;
  TNode<Union<HeapObject, TaggedIndex>> tmp176;
  TNode<IntPtrT> tmp177;
  TNode<IntPtrT> tmp178;
  TNode<UintPtrT> tmp179;
  TNode<IntPtrT> tmp180;
  TNode<UintPtrT> tmp181;
  TNode<UintPtrT> tmp182;
  TNode<BoolT> tmp183;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_13, &phi_bb141_14, &phi_bb141_16, &phi_bb141_17, &phi_bb141_20, &phi_bb141_21, &phi_bb141_26, &phi_bb141_38);
    tmp172 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp168});
    tmp173 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp165}, TNode<IntPtrT>{tmp172});
    std::tie(tmp174, tmp175) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp164}, TNode<IntPtrT>{tmp173}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp174, tmp175}, tmp163);
    std::tie(tmp176, tmp177, tmp178) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp163}).Flatten();
    tmp179 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp180 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp179});
    tmp181 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp180});
    tmp182 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp178});
    tmp183 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp181}, TNode<UintPtrT>{tmp182});
    ca_.Branch(tmp183, &block150, std::vector<compiler::Node*>{phi_bb141_13, phi_bb141_14, phi_bb141_16, phi_bb141_17, phi_bb141_20, phi_bb141_21, phi_bb141_26}, &block151, std::vector<compiler::Node*>{phi_bb141_13, phi_bb141_14, phi_bb141_16, phi_bb141_17, phi_bb141_20, phi_bb141_21, phi_bb141_26});
  }

  TNode<FixedArray> phi_bb142_13;
  TNode<IntPtrT> phi_bb142_14;
  TNode<BoolT> phi_bb142_16;
  TNode<PrimitiveHeapObject> phi_bb142_17;
  TNode<String> phi_bb142_20;
  TNode<String> phi_bb142_21;
  TNode<String> phi_bb142_26;
  TNode<FixedArray> phi_bb142_38;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_13, &phi_bb142_14, &phi_bb142_16, &phi_bb142_17, &phi_bb142_20, &phi_bb142_21, &phi_bb142_26, &phi_bb142_38);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb150_13;
  TNode<IntPtrT> phi_bb150_14;
  TNode<BoolT> phi_bb150_16;
  TNode<PrimitiveHeapObject> phi_bb150_17;
  TNode<String> phi_bb150_20;
  TNode<String> phi_bb150_21;
  TNode<String> phi_bb150_26;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<Union<HeapObject, TaggedIndex>> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<Undefined> tmp188;
  TNode<Union<HeapObject, TaggedIndex>> tmp189;
  TNode<IntPtrT> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<UintPtrT> tmp192;
  TNode<IntPtrT> tmp193;
  TNode<UintPtrT> tmp194;
  TNode<UintPtrT> tmp195;
  TNode<BoolT> tmp196;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_13, &phi_bb150_14, &phi_bb150_16, &phi_bb150_17, &phi_bb150_20, &phi_bb150_21, &phi_bb150_26);
    tmp184 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp180});
    tmp185 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp177}, TNode<IntPtrT>{tmp184});
    std::tie(tmp186, tmp187) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp176}, TNode<IntPtrT>{tmp185}).Flatten();
    tmp188 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp186, tmp187}, tmp188);
    std::tie(tmp189, tmp190, tmp191) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp163}).Flatten();
    tmp192 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp193 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp192});
    tmp194 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp193});
    tmp195 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp191});
    tmp196 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp194}, TNode<UintPtrT>{tmp195});
    ca_.Branch(tmp196, &block159, std::vector<compiler::Node*>{phi_bb150_13, phi_bb150_14, phi_bb150_16, phi_bb150_17, phi_bb150_20, phi_bb150_21, phi_bb150_26}, &block160, std::vector<compiler::Node*>{phi_bb150_13, phi_bb150_14, phi_bb150_16, phi_bb150_17, phi_bb150_20, phi_bb150_21, phi_bb150_26});
  }

  TNode<FixedArray> phi_bb151_13;
  TNode<IntPtrT> phi_bb151_14;
  TNode<BoolT> phi_bb151_16;
  TNode<PrimitiveHeapObject> phi_bb151_17;
  TNode<String> phi_bb151_20;
  TNode<String> phi_bb151_21;
  TNode<String> phi_bb151_26;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_13, &phi_bb151_14, &phi_bb151_16, &phi_bb151_17, &phi_bb151_20, &phi_bb151_21, &phi_bb151_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb159_13;
  TNode<IntPtrT> phi_bb159_14;
  TNode<BoolT> phi_bb159_16;
  TNode<PrimitiveHeapObject> phi_bb159_17;
  TNode<String> phi_bb159_20;
  TNode<String> phi_bb159_21;
  TNode<String> phi_bb159_26;
  TNode<IntPtrT> tmp197;
  TNode<IntPtrT> tmp198;
  TNode<Union<HeapObject, TaggedIndex>> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<IntPtrT> tmp201;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_13, &phi_bb159_14, &phi_bb159_16, &phi_bb159_17, &phi_bb159_20, &phi_bb159_21, &phi_bb159_26);
    tmp197 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp193});
    tmp198 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp190}, TNode<IntPtrT>{tmp197});
    std::tie(tmp199, tmp200) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp189}, TNode<IntPtrT>{tmp198}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp199, tmp200}, tmp139);
    tmp201 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block121, tmp163, tmp201, phi_bb159_16, phi_bb159_17, phi_bb159_20, phi_bb159_21, phi_bb159_26);
  }

  TNode<FixedArray> phi_bb160_13;
  TNode<IntPtrT> phi_bb160_14;
  TNode<BoolT> phi_bb160_16;
  TNode<PrimitiveHeapObject> phi_bb160_17;
  TNode<String> phi_bb160_20;
  TNode<String> phi_bb160_21;
  TNode<String> phi_bb160_26;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_13, &phi_bb160_14, &phi_bb160_16, &phi_bb160_17, &phi_bb160_20, &phi_bb160_21, &phi_bb160_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb121_13;
  TNode<IntPtrT> phi_bb121_14;
  TNode<BoolT> phi_bb121_16;
  TNode<PrimitiveHeapObject> phi_bb121_17;
  TNode<String> phi_bb121_20;
  TNode<String> phi_bb121_21;
  TNode<String> phi_bb121_26;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_13, &phi_bb121_14, &phi_bb121_16, &phi_bb121_17, &phi_bb121_20, &phi_bb121_21, &phi_bb121_26);
    ca_.Goto(&block107, phi_bb121_13, phi_bb121_14, phi_bb121_16, phi_bb121_17, phi_bb121_20, phi_bb121_21, phi_bb121_26);
  }

  TNode<FixedArray> phi_bb108_13;
  TNode<IntPtrT> phi_bb108_14;
  TNode<BoolT> phi_bb108_16;
  TNode<PrimitiveHeapObject> phi_bb108_17;
  TNode<String> phi_bb108_20;
  TNode<String> phi_bb108_21;
  TNode<String> phi_bb108_26;
  TNode<Smi> tmp202;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_13, &phi_bb108_14, &phi_bb108_16, &phi_bb108_17, &phi_bb108_20, &phi_bb108_21, &phi_bb108_26);
    compiler::CodeAssemblerLabel label203(&ca_);
    tmp202 = Cast_Smi_0(state_, TNode<Object>{ca_.UncheckedCast<Object>(tmp134)}, &label203);
    ca_.Goto(&block165, phi_bb108_13, phi_bb108_14, phi_bb108_16, phi_bb108_17, phi_bb108_20, phi_bb108_21, phi_bb108_26);
    if (label203.is_used()) {
      ca_.Bind(&label203);
      ca_.Goto(&block166, phi_bb108_13, phi_bb108_14, phi_bb108_16, phi_bb108_17, phi_bb108_20, phi_bb108_21, phi_bb108_26);
    }
  }

  TNode<FixedArray> phi_bb166_13;
  TNode<IntPtrT> phi_bb166_14;
  TNode<BoolT> phi_bb166_16;
  TNode<PrimitiveHeapObject> phi_bb166_17;
  TNode<String> phi_bb166_20;
  TNode<String> phi_bb166_21;
  TNode<String> phi_bb166_26;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_13, &phi_bb166_14, &phi_bb166_16, &phi_bb166_17, &phi_bb166_20, &phi_bb166_21, &phi_bb166_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:234:9");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb165_13;
  TNode<IntPtrT> phi_bb165_14;
  TNode<BoolT> phi_bb165_16;
  TNode<PrimitiveHeapObject> phi_bb165_17;
  TNode<String> phi_bb165_20;
  TNode<String> phi_bb165_21;
  TNode<String> phi_bb165_26;
  TNode<Smi> tmp204;
  TNode<BoolT> tmp205;
  if (block165.is_used()) {
    ca_.Bind(&block165, &phi_bb165_13, &phi_bb165_14, &phi_bb165_16, &phi_bb165_17, &phi_bb165_20, &phi_bb165_21, &phi_bb165_26);
    tmp204 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp205 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp202}, TNode<Smi>{tmp204});
    ca_.Branch(tmp205, &block167, std::vector<compiler::Node*>{phi_bb165_13, phi_bb165_14, phi_bb165_16, phi_bb165_17, phi_bb165_20, phi_bb165_21, phi_bb165_26}, &block168, std::vector<compiler::Node*>{phi_bb165_13, phi_bb165_14, phi_bb165_16, phi_bb165_17, phi_bb165_20, phi_bb165_21, phi_bb165_26});
  }

  TNode<FixedArray> phi_bb168_13;
  TNode<IntPtrT> phi_bb168_14;
  TNode<BoolT> phi_bb168_16;
  TNode<PrimitiveHeapObject> phi_bb168_17;
  TNode<String> phi_bb168_20;
  TNode<String> phi_bb168_21;
  TNode<String> phi_bb168_26;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_13, &phi_bb168_14, &phi_bb168_16, &phi_bb168_17, &phi_bb168_20, &phi_bb168_21, &phi_bb168_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 229});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count < 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb167_13;
  TNode<IntPtrT> phi_bb167_14;
  TNode<BoolT> phi_bb167_16;
  TNode<PrimitiveHeapObject> phi_bb167_17;
  TNode<String> phi_bb167_20;
  TNode<String> phi_bb167_21;
  TNode<String> phi_bb167_26;
  TNode<Smi> tmp206;
  TNode<Smi> tmp207;
  TNode<Smi> tmp208;
  TNode<BoolT> tmp209;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_13, &phi_bb167_14, &phi_bb167_16, &phi_bb167_17, &phi_bb167_20, &phi_bb167_21, &phi_bb167_26);
    tmp206 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp207 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp202}, TNode<Smi>{tmp206});
    tmp208 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp209 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp207}, TNode<Smi>{tmp208});
    ca_.Branch(tmp209, &block169, std::vector<compiler::Node*>{phi_bb167_13, phi_bb167_14, phi_bb167_16, phi_bb167_17, phi_bb167_20, phi_bb167_21, phi_bb167_26}, &block170, std::vector<compiler::Node*>{phi_bb167_13, phi_bb167_14, phi_bb167_16, phi_bb167_17, phi_bb167_20, phi_bb167_21, phi_bb167_26});
  }

  TNode<FixedArray> phi_bb170_13;
  TNode<IntPtrT> phi_bb170_14;
  TNode<BoolT> phi_bb170_16;
  TNode<PrimitiveHeapObject> phi_bb170_17;
  TNode<String> phi_bb170_20;
  TNode<String> phi_bb170_21;
  TNode<String> phi_bb170_26;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_13, &phi_bb170_14, &phi_bb170_16, &phi_bb170_17, &phi_bb170_20, &phi_bb170_21, &phi_bb170_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 230});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count - 1 < 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb169_13;
  TNode<IntPtrT> phi_bb169_14;
  TNode<BoolT> phi_bb169_16;
  TNode<PrimitiveHeapObject> phi_bb169_17;
  TNode<String> phi_bb169_20;
  TNode<String> phi_bb169_21;
  TNode<String> phi_bb169_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp210;
  TNode<IntPtrT> tmp211;
  TNode<IntPtrT> tmp212;
  TNode<IntPtrT> tmp213;
  TNode<IntPtrT> tmp214;
  TNode<UintPtrT> tmp215;
  TNode<UintPtrT> tmp216;
  TNode<BoolT> tmp217;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_13, &phi_bb169_14, &phi_bb169_16, &phi_bb169_17, &phi_bb169_20, &phi_bb169_21, &phi_bb169_26);
    std::tie(tmp210, tmp211, tmp212) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb169_13}).Flatten();
    tmp213 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp214 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb169_14}, TNode<IntPtrT>{tmp213});
    tmp215 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp214});
    tmp216 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp212});
    tmp217 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp215}, TNode<UintPtrT>{tmp216});
    ca_.Branch(tmp217, &block175, std::vector<compiler::Node*>{phi_bb169_13, phi_bb169_14, phi_bb169_16, phi_bb169_17, phi_bb169_20, phi_bb169_21, phi_bb169_26, phi_bb169_13}, &block176, std::vector<compiler::Node*>{phi_bb169_13, phi_bb169_14, phi_bb169_16, phi_bb169_17, phi_bb169_20, phi_bb169_21, phi_bb169_26, phi_bb169_13});
  }

  TNode<FixedArray> phi_bb175_13;
  TNode<IntPtrT> phi_bb175_14;
  TNode<BoolT> phi_bb175_16;
  TNode<PrimitiveHeapObject> phi_bb175_17;
  TNode<String> phi_bb175_20;
  TNode<String> phi_bb175_21;
  TNode<String> phi_bb175_26;
  TNode<FixedArray> phi_bb175_32;
  TNode<IntPtrT> tmp218;
  TNode<IntPtrT> tmp219;
  TNode<Union<HeapObject, TaggedIndex>> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<Smi> tmp222;
  TNode<Smi> tmp223;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_13, &phi_bb175_14, &phi_bb175_16, &phi_bb175_17, &phi_bb175_20, &phi_bb175_21, &phi_bb175_26, &phi_bb175_32);
    tmp218 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp214});
    tmp219 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp211}, TNode<IntPtrT>{tmp218});
    std::tie(tmp220, tmp221) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp210}, TNode<IntPtrT>{tmp219}).Flatten();
    tmp222 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp223 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp202}, TNode<Smi>{tmp222});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp220, tmp221}, tmp223);
    ca_.Goto(&block107, phi_bb175_13, phi_bb175_14, phi_bb175_16, phi_bb175_17, phi_bb175_20, phi_bb175_21, phi_bb175_26);
  }

  TNode<FixedArray> phi_bb176_13;
  TNode<IntPtrT> phi_bb176_14;
  TNode<BoolT> phi_bb176_16;
  TNode<PrimitiveHeapObject> phi_bb176_17;
  TNode<String> phi_bb176_20;
  TNode<String> phi_bb176_21;
  TNode<String> phi_bb176_26;
  TNode<FixedArray> phi_bb176_32;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_13, &phi_bb176_14, &phi_bb176_16, &phi_bb176_17, &phi_bb176_20, &phi_bb176_21, &phi_bb176_26, &phi_bb176_32);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb107_13;
  TNode<IntPtrT> phi_bb107_14;
  TNode<BoolT> phi_bb107_16;
  TNode<PrimitiveHeapObject> phi_bb107_17;
  TNode<String> phi_bb107_20;
  TNode<String> phi_bb107_21;
  TNode<String> phi_bb107_26;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_13, &phi_bb107_14, &phi_bb107_16, &phi_bb107_17, &phi_bb107_20, &phi_bb107_21, &phi_bb107_26);
    ca_.Goto(&block95, phi_bb107_13, phi_bb107_14, phi_bb107_16, phi_bb107_17, phi_bb107_20, phi_bb107_21, phi_bb107_26);
  }

  TNode<FixedArray> phi_bb94_13;
  TNode<IntPtrT> phi_bb94_14;
  TNode<BoolT> phi_bb94_16;
  TNode<PrimitiveHeapObject> phi_bb94_17;
  TNode<String> phi_bb94_20;
  TNode<String> phi_bb94_21;
  TNode<String> phi_bb94_26;
  TNode<IntPtrT> tmp224;
  TNode<IntPtrT> tmp225;
  TNode<BoolT> tmp226;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_13, &phi_bb94_14, &phi_bb94_16, &phi_bb94_17, &phi_bb94_20, &phi_bb94_21, &phi_bb94_26);
    tmp224 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb94_13});
    tmp225 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp226 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb94_14}, TNode<IntPtrT>{tmp225});
    ca_.Branch(tmp226, &block180, std::vector<compiler::Node*>{phi_bb94_13, phi_bb94_14, phi_bb94_16, phi_bb94_17, phi_bb94_20, phi_bb94_21, phi_bb94_26, phi_bb94_26, phi_bb94_26}, &block181, std::vector<compiler::Node*>{phi_bb94_13, phi_bb94_14, phi_bb94_16, phi_bb94_17, phi_bb94_20, phi_bb94_21, phi_bb94_26, phi_bb94_26, phi_bb94_26});
  }

  TNode<FixedArray> phi_bb181_13;
  TNode<IntPtrT> phi_bb181_14;
  TNode<BoolT> phi_bb181_16;
  TNode<PrimitiveHeapObject> phi_bb181_17;
  TNode<String> phi_bb181_20;
  TNode<String> phi_bb181_21;
  TNode<String> phi_bb181_26;
  TNode<String> phi_bb181_30;
  TNode<Object> phi_bb181_31;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_13, &phi_bb181_14, &phi_bb181_16, &phi_bb181_17, &phi_bb181_20, &phi_bb181_21, &phi_bb181_26, &phi_bb181_30, &phi_bb181_31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb180_13;
  TNode<IntPtrT> phi_bb180_14;
  TNode<BoolT> phi_bb180_16;
  TNode<PrimitiveHeapObject> phi_bb180_17;
  TNode<String> phi_bb180_20;
  TNode<String> phi_bb180_21;
  TNode<String> phi_bb180_26;
  TNode<String> phi_bb180_30;
  TNode<Object> phi_bb180_31;
  TNode<BoolT> tmp227;
  if (block180.is_used()) {
    ca_.Bind(&block180, &phi_bb180_13, &phi_bb180_14, &phi_bb180_16, &phi_bb180_17, &phi_bb180_20, &phi_bb180_21, &phi_bb180_26, &phi_bb180_30, &phi_bb180_31);
    tmp227 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb180_14}, TNode<IntPtrT>{tmp224});
    ca_.Branch(tmp227, &block182, std::vector<compiler::Node*>{phi_bb180_13, phi_bb180_14, phi_bb180_16, phi_bb180_17, phi_bb180_20, phi_bb180_21, phi_bb180_26, phi_bb180_30, phi_bb180_31}, &block183, std::vector<compiler::Node*>{phi_bb180_13, phi_bb180_14, phi_bb180_16, phi_bb180_17, phi_bb180_20, phi_bb180_21, phi_bb180_26, phi_bb180_30, phi_bb180_31});
  }

  TNode<FixedArray> phi_bb183_13;
  TNode<IntPtrT> phi_bb183_14;
  TNode<BoolT> phi_bb183_16;
  TNode<PrimitiveHeapObject> phi_bb183_17;
  TNode<String> phi_bb183_20;
  TNode<String> phi_bb183_21;
  TNode<String> phi_bb183_26;
  TNode<String> phi_bb183_30;
  TNode<Object> phi_bb183_31;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_13, &phi_bb183_14, &phi_bb183_16, &phi_bb183_17, &phi_bb183_20, &phi_bb183_21, &phi_bb183_26, &phi_bb183_30, &phi_bb183_31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb182_13;
  TNode<IntPtrT> phi_bb182_14;
  TNode<BoolT> phi_bb182_16;
  TNode<PrimitiveHeapObject> phi_bb182_17;
  TNode<String> phi_bb182_20;
  TNode<String> phi_bb182_21;
  TNode<String> phi_bb182_26;
  TNode<String> phi_bb182_30;
  TNode<Object> phi_bb182_31;
  TNode<BoolT> tmp228;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_13, &phi_bb182_14, &phi_bb182_16, &phi_bb182_17, &phi_bb182_20, &phi_bb182_21, &phi_bb182_26, &phi_bb182_30, &phi_bb182_31);
    tmp228 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb182_14}, TNode<IntPtrT>{tmp224});
    ca_.Branch(tmp228, &block184, std::vector<compiler::Node*>{phi_bb182_13, phi_bb182_14, phi_bb182_16, phi_bb182_17, phi_bb182_20, phi_bb182_21, phi_bb182_26, phi_bb182_30, phi_bb182_31}, &block185, std::vector<compiler::Node*>{phi_bb182_13, phi_bb182_14, phi_bb182_16, phi_bb182_17, phi_bb182_20, phi_bb182_21, phi_bb182_26, phi_bb182_30, phi_bb182_31});
  }

  TNode<FixedArray> phi_bb184_13;
  TNode<IntPtrT> phi_bb184_14;
  TNode<BoolT> phi_bb184_16;
  TNode<PrimitiveHeapObject> phi_bb184_17;
  TNode<String> phi_bb184_20;
  TNode<String> phi_bb184_21;
  TNode<String> phi_bb184_26;
  TNode<String> phi_bb184_30;
  TNode<Object> phi_bb184_31;
  TNode<Union<HeapObject, TaggedIndex>> tmp229;
  TNode<IntPtrT> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<IntPtrT> tmp232;
  TNode<IntPtrT> tmp233;
  TNode<UintPtrT> tmp234;
  TNode<UintPtrT> tmp235;
  TNode<BoolT> tmp236;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_13, &phi_bb184_14, &phi_bb184_16, &phi_bb184_17, &phi_bb184_20, &phi_bb184_21, &phi_bb184_26, &phi_bb184_30, &phi_bb184_31);
    std::tie(tmp229, tmp230, tmp231) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb184_13}).Flatten();
    tmp232 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp233 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb184_14}, TNode<IntPtrT>{tmp232});
    tmp234 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb184_14});
    tmp235 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp231});
    tmp236 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp234}, TNode<UintPtrT>{tmp235});
    ca_.Branch(tmp236, &block191, std::vector<compiler::Node*>{phi_bb184_13, phi_bb184_16, phi_bb184_17, phi_bb184_20, phi_bb184_21, phi_bb184_26, phi_bb184_30, phi_bb184_31, phi_bb184_13, phi_bb184_14, phi_bb184_14, phi_bb184_14, phi_bb184_14}, &block192, std::vector<compiler::Node*>{phi_bb184_13, phi_bb184_16, phi_bb184_17, phi_bb184_20, phi_bb184_21, phi_bb184_26, phi_bb184_30, phi_bb184_31, phi_bb184_13, phi_bb184_14, phi_bb184_14, phi_bb184_14, phi_bb184_14});
  }

  TNode<FixedArray> phi_bb191_13;
  TNode<BoolT> phi_bb191_16;
  TNode<PrimitiveHeapObject> phi_bb191_17;
  TNode<String> phi_bb191_20;
  TNode<String> phi_bb191_21;
  TNode<String> phi_bb191_26;
  TNode<String> phi_bb191_30;
  TNode<Object> phi_bb191_31;
  TNode<FixedArray> phi_bb191_33;
  TNode<IntPtrT> phi_bb191_37;
  TNode<IntPtrT> phi_bb191_38;
  TNode<IntPtrT> phi_bb191_42;
  TNode<IntPtrT> phi_bb191_43;
  TNode<IntPtrT> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<Union<HeapObject, TaggedIndex>> tmp239;
  TNode<IntPtrT> tmp240;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_13, &phi_bb191_16, &phi_bb191_17, &phi_bb191_20, &phi_bb191_21, &phi_bb191_26, &phi_bb191_30, &phi_bb191_31, &phi_bb191_33, &phi_bb191_37, &phi_bb191_38, &phi_bb191_42, &phi_bb191_43);
    tmp237 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb191_43});
    tmp238 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp230}, TNode<IntPtrT>{tmp237});
    std::tie(tmp239, tmp240) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp229}, TNode<IntPtrT>{tmp238}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp239, tmp240}, phi_bb191_31);
    ca_.Goto(&block186, phi_bb191_13, tmp233, phi_bb191_16, phi_bb191_17, phi_bb191_20, phi_bb191_21, phi_bb191_26, phi_bb191_30, phi_bb191_31);
  }

  TNode<FixedArray> phi_bb192_13;
  TNode<BoolT> phi_bb192_16;
  TNode<PrimitiveHeapObject> phi_bb192_17;
  TNode<String> phi_bb192_20;
  TNode<String> phi_bb192_21;
  TNode<String> phi_bb192_26;
  TNode<String> phi_bb192_30;
  TNode<Object> phi_bb192_31;
  TNode<FixedArray> phi_bb192_33;
  TNode<IntPtrT> phi_bb192_37;
  TNode<IntPtrT> phi_bb192_38;
  TNode<IntPtrT> phi_bb192_42;
  TNode<IntPtrT> phi_bb192_43;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_13, &phi_bb192_16, &phi_bb192_17, &phi_bb192_20, &phi_bb192_21, &phi_bb192_26, &phi_bb192_30, &phi_bb192_31, &phi_bb192_33, &phi_bb192_37, &phi_bb192_38, &phi_bb192_42, &phi_bb192_43);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb185_13;
  TNode<IntPtrT> phi_bb185_14;
  TNode<BoolT> phi_bb185_16;
  TNode<PrimitiveHeapObject> phi_bb185_17;
  TNode<String> phi_bb185_20;
  TNode<String> phi_bb185_21;
  TNode<String> phi_bb185_26;
  TNode<String> phi_bb185_30;
  TNode<Object> phi_bb185_31;
  TNode<IntPtrT> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<BoolT> tmp243;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_13, &phi_bb185_14, &phi_bb185_16, &phi_bb185_17, &phi_bb185_20, &phi_bb185_21, &phi_bb185_26, &phi_bb185_30, &phi_bb185_31);
    tmp241 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp224});
    tmp242 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp243 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp241}, TNode<IntPtrT>{tmp242});
    ca_.Branch(tmp243, &block195, std::vector<compiler::Node*>{phi_bb185_13, phi_bb185_14, phi_bb185_16, phi_bb185_17, phi_bb185_20, phi_bb185_21, phi_bb185_26, phi_bb185_30, phi_bb185_31}, &block196, std::vector<compiler::Node*>{phi_bb185_13, phi_bb185_14, phi_bb185_16, phi_bb185_17, phi_bb185_20, phi_bb185_21, phi_bb185_26, phi_bb185_30, phi_bb185_31});
  }

  TNode<FixedArray> phi_bb195_13;
  TNode<IntPtrT> phi_bb195_14;
  TNode<BoolT> phi_bb195_16;
  TNode<PrimitiveHeapObject> phi_bb195_17;
  TNode<String> phi_bb195_20;
  TNode<String> phi_bb195_21;
  TNode<String> phi_bb195_26;
  TNode<String> phi_bb195_30;
  TNode<Object> phi_bb195_31;
  TNode<IntPtrT> tmp244;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_13, &phi_bb195_14, &phi_bb195_16, &phi_bb195_17, &phi_bb195_20, &phi_bb195_21, &phi_bb195_26, &phi_bb195_30, &phi_bb195_31);
    tmp244 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block197, phi_bb195_13, phi_bb195_14, phi_bb195_16, phi_bb195_17, phi_bb195_20, phi_bb195_21, phi_bb195_26, phi_bb195_30, phi_bb195_31, tmp244);
  }

  TNode<FixedArray> phi_bb196_13;
  TNode<IntPtrT> phi_bb196_14;
  TNode<BoolT> phi_bb196_16;
  TNode<PrimitiveHeapObject> phi_bb196_17;
  TNode<String> phi_bb196_20;
  TNode<String> phi_bb196_21;
  TNode<String> phi_bb196_26;
  TNode<String> phi_bb196_30;
  TNode<Object> phi_bb196_31;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_13, &phi_bb196_14, &phi_bb196_16, &phi_bb196_17, &phi_bb196_20, &phi_bb196_21, &phi_bb196_26, &phi_bb196_30, &phi_bb196_31);
    ca_.Goto(&block197, phi_bb196_13, phi_bb196_14, phi_bb196_16, phi_bb196_17, phi_bb196_20, phi_bb196_21, phi_bb196_26, phi_bb196_30, phi_bb196_31, tmp241);
  }

  TNode<FixedArray> phi_bb197_13;
  TNode<IntPtrT> phi_bb197_14;
  TNode<BoolT> phi_bb197_16;
  TNode<PrimitiveHeapObject> phi_bb197_17;
  TNode<String> phi_bb197_20;
  TNode<String> phi_bb197_21;
  TNode<String> phi_bb197_26;
  TNode<String> phi_bb197_30;
  TNode<Object> phi_bb197_31;
  TNode<IntPtrT> phi_bb197_34;
  TNode<IntPtrT> tmp245;
  TNode<BoolT> tmp246;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_13, &phi_bb197_14, &phi_bb197_16, &phi_bb197_17, &phi_bb197_20, &phi_bb197_21, &phi_bb197_26, &phi_bb197_30, &phi_bb197_31, &phi_bb197_34);
    tmp245 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp246 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb197_34}, TNode<IntPtrT>{tmp245});
    ca_.Branch(tmp246, &block199, std::vector<compiler::Node*>{phi_bb197_13, phi_bb197_14, phi_bb197_16, phi_bb197_17, phi_bb197_20, phi_bb197_21, phi_bb197_26, phi_bb197_30, phi_bb197_31}, &block200, std::vector<compiler::Node*>{phi_bb197_13, phi_bb197_14, phi_bb197_16, phi_bb197_17, phi_bb197_20, phi_bb197_21, phi_bb197_26, phi_bb197_30, phi_bb197_31});
  }

  TNode<FixedArray> phi_bb200_13;
  TNode<IntPtrT> phi_bb200_14;
  TNode<BoolT> phi_bb200_16;
  TNode<PrimitiveHeapObject> phi_bb200_17;
  TNode<String> phi_bb200_20;
  TNode<String> phi_bb200_21;
  TNode<String> phi_bb200_26;
  TNode<String> phi_bb200_30;
  TNode<Object> phi_bb200_31;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_13, &phi_bb200_14, &phi_bb200_16, &phi_bb200_17, &phi_bb200_20, &phi_bb200_21, &phi_bb200_26, &phi_bb200_30, &phi_bb200_31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb199_13;
  TNode<IntPtrT> phi_bb199_14;
  TNode<BoolT> phi_bb199_16;
  TNode<PrimitiveHeapObject> phi_bb199_17;
  TNode<String> phi_bb199_20;
  TNode<String> phi_bb199_21;
  TNode<String> phi_bb199_26;
  TNode<String> phi_bb199_30;
  TNode<Object> phi_bb199_31;
  TNode<FixedArray> tmp247;
  TNode<Union<HeapObject, TaggedIndex>> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<IntPtrT> tmp250;
  TNode<UintPtrT> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<UintPtrT> tmp253;
  TNode<UintPtrT> tmp254;
  TNode<BoolT> tmp255;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_13, &phi_bb199_14, &phi_bb199_16, &phi_bb199_17, &phi_bb199_20, &phi_bb199_21, &phi_bb199_26, &phi_bb199_30, &phi_bb199_31);
    tmp247 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb197_34});
    std::tie(tmp248, tmp249, tmp250) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb199_13}).Flatten();
    tmp251 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp252 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp251});
    tmp253 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp252});
    tmp254 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp250});
    tmp255 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp253}, TNode<UintPtrT>{tmp254});
    ca_.Branch(tmp255, &block206, std::vector<compiler::Node*>{phi_bb199_13, phi_bb199_14, phi_bb199_16, phi_bb199_17, phi_bb199_20, phi_bb199_21, phi_bb199_26, phi_bb199_30, phi_bb199_31, phi_bb199_13}, &block207, std::vector<compiler::Node*>{phi_bb199_13, phi_bb199_14, phi_bb199_16, phi_bb199_17, phi_bb199_20, phi_bb199_21, phi_bb199_26, phi_bb199_30, phi_bb199_31, phi_bb199_13});
  }

  TNode<FixedArray> phi_bb206_13;
  TNode<IntPtrT> phi_bb206_14;
  TNode<BoolT> phi_bb206_16;
  TNode<PrimitiveHeapObject> phi_bb206_17;
  TNode<String> phi_bb206_20;
  TNode<String> phi_bb206_21;
  TNode<String> phi_bb206_26;
  TNode<String> phi_bb206_30;
  TNode<Object> phi_bb206_31;
  TNode<FixedArray> phi_bb206_36;
  TNode<IntPtrT> tmp256;
  TNode<IntPtrT> tmp257;
  TNode<Union<HeapObject, TaggedIndex>> tmp258;
  TNode<IntPtrT> tmp259;
  TNode<Union<HeapObject, TaggedIndex>> tmp260;
  TNode<IntPtrT> tmp261;
  TNode<IntPtrT> tmp262;
  TNode<UintPtrT> tmp263;
  TNode<IntPtrT> tmp264;
  TNode<UintPtrT> tmp265;
  TNode<UintPtrT> tmp266;
  TNode<BoolT> tmp267;
  if (block206.is_used()) {
    ca_.Bind(&block206, &phi_bb206_13, &phi_bb206_14, &phi_bb206_16, &phi_bb206_17, &phi_bb206_20, &phi_bb206_21, &phi_bb206_26, &phi_bb206_30, &phi_bb206_31, &phi_bb206_36);
    tmp256 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp252});
    tmp257 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp249}, TNode<IntPtrT>{tmp256});
    std::tie(tmp258, tmp259) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp248}, TNode<IntPtrT>{tmp257}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp258, tmp259}, tmp247);
    std::tie(tmp260, tmp261, tmp262) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp247}).Flatten();
    tmp263 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp264 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp263});
    tmp265 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp264});
    tmp266 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp262});
    tmp267 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp265}, TNode<UintPtrT>{tmp266});
    ca_.Branch(tmp267, &block215, std::vector<compiler::Node*>{phi_bb206_13, phi_bb206_14, phi_bb206_16, phi_bb206_17, phi_bb206_20, phi_bb206_21, phi_bb206_26, phi_bb206_30, phi_bb206_31}, &block216, std::vector<compiler::Node*>{phi_bb206_13, phi_bb206_14, phi_bb206_16, phi_bb206_17, phi_bb206_20, phi_bb206_21, phi_bb206_26, phi_bb206_30, phi_bb206_31});
  }

  TNode<FixedArray> phi_bb207_13;
  TNode<IntPtrT> phi_bb207_14;
  TNode<BoolT> phi_bb207_16;
  TNode<PrimitiveHeapObject> phi_bb207_17;
  TNode<String> phi_bb207_20;
  TNode<String> phi_bb207_21;
  TNode<String> phi_bb207_26;
  TNode<String> phi_bb207_30;
  TNode<Object> phi_bb207_31;
  TNode<FixedArray> phi_bb207_36;
  if (block207.is_used()) {
    ca_.Bind(&block207, &phi_bb207_13, &phi_bb207_14, &phi_bb207_16, &phi_bb207_17, &phi_bb207_20, &phi_bb207_21, &phi_bb207_26, &phi_bb207_30, &phi_bb207_31, &phi_bb207_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb215_13;
  TNode<IntPtrT> phi_bb215_14;
  TNode<BoolT> phi_bb215_16;
  TNode<PrimitiveHeapObject> phi_bb215_17;
  TNode<String> phi_bb215_20;
  TNode<String> phi_bb215_21;
  TNode<String> phi_bb215_26;
  TNode<String> phi_bb215_30;
  TNode<Object> phi_bb215_31;
  TNode<IntPtrT> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<Union<HeapObject, TaggedIndex>> tmp270;
  TNode<IntPtrT> tmp271;
  TNode<Undefined> tmp272;
  TNode<Union<HeapObject, TaggedIndex>> tmp273;
  TNode<IntPtrT> tmp274;
  TNode<IntPtrT> tmp275;
  TNode<UintPtrT> tmp276;
  TNode<IntPtrT> tmp277;
  TNode<UintPtrT> tmp278;
  TNode<UintPtrT> tmp279;
  TNode<BoolT> tmp280;
  if (block215.is_used()) {
    ca_.Bind(&block215, &phi_bb215_13, &phi_bb215_14, &phi_bb215_16, &phi_bb215_17, &phi_bb215_20, &phi_bb215_21, &phi_bb215_26, &phi_bb215_30, &phi_bb215_31);
    tmp268 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp264});
    tmp269 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp261}, TNode<IntPtrT>{tmp268});
    std::tie(tmp270, tmp271) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp260}, TNode<IntPtrT>{tmp269}).Flatten();
    tmp272 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp270, tmp271}, tmp272);
    std::tie(tmp273, tmp274, tmp275) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp247}).Flatten();
    tmp276 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp277 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp276});
    tmp278 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp277});
    tmp279 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp275});
    tmp280 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp278}, TNode<UintPtrT>{tmp279});
    ca_.Branch(tmp280, &block224, std::vector<compiler::Node*>{phi_bb215_13, phi_bb215_14, phi_bb215_16, phi_bb215_17, phi_bb215_20, phi_bb215_21, phi_bb215_26, phi_bb215_30, phi_bb215_31}, &block225, std::vector<compiler::Node*>{phi_bb215_13, phi_bb215_14, phi_bb215_16, phi_bb215_17, phi_bb215_20, phi_bb215_21, phi_bb215_26, phi_bb215_30, phi_bb215_31});
  }

  TNode<FixedArray> phi_bb216_13;
  TNode<IntPtrT> phi_bb216_14;
  TNode<BoolT> phi_bb216_16;
  TNode<PrimitiveHeapObject> phi_bb216_17;
  TNode<String> phi_bb216_20;
  TNode<String> phi_bb216_21;
  TNode<String> phi_bb216_26;
  TNode<String> phi_bb216_30;
  TNode<Object> phi_bb216_31;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_13, &phi_bb216_14, &phi_bb216_16, &phi_bb216_17, &phi_bb216_20, &phi_bb216_21, &phi_bb216_26, &phi_bb216_30, &phi_bb216_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb224_13;
  TNode<IntPtrT> phi_bb224_14;
  TNode<BoolT> phi_bb224_16;
  TNode<PrimitiveHeapObject> phi_bb224_17;
  TNode<String> phi_bb224_20;
  TNode<String> phi_bb224_21;
  TNode<String> phi_bb224_26;
  TNode<String> phi_bb224_30;
  TNode<Object> phi_bb224_31;
  TNode<IntPtrT> tmp281;
  TNode<IntPtrT> tmp282;
  TNode<Union<HeapObject, TaggedIndex>> tmp283;
  TNode<IntPtrT> tmp284;
  TNode<IntPtrT> tmp285;
  if (block224.is_used()) {
    ca_.Bind(&block224, &phi_bb224_13, &phi_bb224_14, &phi_bb224_16, &phi_bb224_17, &phi_bb224_20, &phi_bb224_21, &phi_bb224_26, &phi_bb224_30, &phi_bb224_31);
    tmp281 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp277});
    tmp282 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp274}, TNode<IntPtrT>{tmp281});
    std::tie(tmp283, tmp284) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp273}, TNode<IntPtrT>{tmp282}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp283, tmp284}, phi_bb224_31);
    tmp285 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block186, tmp247, tmp285, phi_bb224_16, phi_bb224_17, phi_bb224_20, phi_bb224_21, phi_bb224_26, phi_bb224_30, phi_bb224_31);
  }

  TNode<FixedArray> phi_bb225_13;
  TNode<IntPtrT> phi_bb225_14;
  TNode<BoolT> phi_bb225_16;
  TNode<PrimitiveHeapObject> phi_bb225_17;
  TNode<String> phi_bb225_20;
  TNode<String> phi_bb225_21;
  TNode<String> phi_bb225_26;
  TNode<String> phi_bb225_30;
  TNode<Object> phi_bb225_31;
  if (block225.is_used()) {
    ca_.Bind(&block225, &phi_bb225_13, &phi_bb225_14, &phi_bb225_16, &phi_bb225_17, &phi_bb225_20, &phi_bb225_21, &phi_bb225_26, &phi_bb225_30, &phi_bb225_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb186_13;
  TNode<IntPtrT> phi_bb186_14;
  TNode<BoolT> phi_bb186_16;
  TNode<PrimitiveHeapObject> phi_bb186_17;
  TNode<String> phi_bb186_20;
  TNode<String> phi_bb186_21;
  TNode<String> phi_bb186_26;
  TNode<String> phi_bb186_30;
  TNode<Object> phi_bb186_31;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_13, &phi_bb186_14, &phi_bb186_16, &phi_bb186_17, &phi_bb186_20, &phi_bb186_21, &phi_bb186_26, &phi_bb186_30, &phi_bb186_31);
    ca_.Goto(&block95, phi_bb186_13, phi_bb186_14, phi_bb186_16, phi_bb186_26, phi_bb186_20, phi_bb186_21, phi_bb186_26);
  }

  TNode<FixedArray> phi_bb95_13;
  TNode<IntPtrT> phi_bb95_14;
  TNode<BoolT> phi_bb95_16;
  TNode<PrimitiveHeapObject> phi_bb95_17;
  TNode<String> phi_bb95_20;
  TNode<String> phi_bb95_21;
  TNode<String> phi_bb95_26;
  TNode<IntPtrT> tmp286;
  TNode<Map> tmp287;
  TNode<BoolT> tmp288;
  TNode<BoolT> tmp289;
  TNode<IntPtrT> tmp290;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_13, &phi_bb95_14, &phi_bb95_16, &phi_bb95_17, &phi_bb95_20, &phi_bb95_21, &phi_bb95_26);
    tmp286 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp287 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{phi_bb95_26, tmp286});
    tmp288 = CodeStubAssembler(state_).IsOneByteStringMap(TNode<Map>{tmp287});
    tmp289 = CodeStubAssembler(state_).Word32And(TNode<BoolT>{tmp288}, TNode<BoolT>{phi_bb95_16});
    tmp290 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block4, tmp290, phi_bb6_11, phi_bb95_13, phi_bb95_14, tmp118, tmp289, phi_bb95_17, tmp19);
  }

  TNode<IntPtrT> phi_bb3_10;
  TNode<BuiltinPtr> phi_bb3_11;
  TNode<FixedArray> phi_bb3_13;
  TNode<IntPtrT> phi_bb3_14;
  TNode<IntPtrT> phi_bb3_15;
  TNode<BoolT> phi_bb3_16;
  TNode<PrimitiveHeapObject> phi_bb3_17;
  TNode<UintPtrT> phi_bb3_18;
  TNode<BoolT> tmp291;
  TNode<IntPtrT> tmp292;
  TNode<BoolT> tmp293;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_10, &phi_bb3_11, &phi_bb3_13, &phi_bb3_14, &phi_bb3_15, &phi_bb3_16, &phi_bb3_17, &phi_bb3_18);
    tmp291 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp292 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp293 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb3_10}, TNode<IntPtrT>{tmp292});
    ca_.Branch(tmp293, &block231, std::vector<compiler::Node*>{phi_bb3_10, phi_bb3_11, phi_bb3_13, phi_bb3_14, phi_bb3_15, phi_bb3_16, phi_bb3_17, phi_bb3_18, phi_bb3_10, phi_bb3_10}, &block232, std::vector<compiler::Node*>{phi_bb3_10, phi_bb3_11, phi_bb3_13, phi_bb3_14, phi_bb3_15, phi_bb3_16, phi_bb3_17, phi_bb3_18, phi_bb3_10, phi_bb3_10});
  }

  TNode<IntPtrT> phi_bb231_10;
  TNode<BuiltinPtr> phi_bb231_11;
  TNode<FixedArray> phi_bb231_13;
  TNode<IntPtrT> phi_bb231_14;
  TNode<IntPtrT> phi_bb231_15;
  TNode<BoolT> phi_bb231_16;
  TNode<PrimitiveHeapObject> phi_bb231_17;
  TNode<UintPtrT> phi_bb231_18;
  TNode<IntPtrT> phi_bb231_19;
  TNode<IntPtrT> phi_bb231_23;
  TNode<BoolT> tmp294;
  if (block231.is_used()) {
    ca_.Bind(&block231, &phi_bb231_10, &phi_bb231_11, &phi_bb231_13, &phi_bb231_14, &phi_bb231_15, &phi_bb231_16, &phi_bb231_17, &phi_bb231_18, &phi_bb231_19, &phi_bb231_23);
    tmp294 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block233, phi_bb231_10, phi_bb231_11, phi_bb231_13, phi_bb231_14, phi_bb231_15, phi_bb231_16, phi_bb231_17, phi_bb231_18, phi_bb231_19, phi_bb231_23, tmp294);
  }

  TNode<IntPtrT> phi_bb232_10;
  TNode<BuiltinPtr> phi_bb232_11;
  TNode<FixedArray> phi_bb232_13;
  TNode<IntPtrT> phi_bb232_14;
  TNode<IntPtrT> phi_bb232_15;
  TNode<BoolT> phi_bb232_16;
  TNode<PrimitiveHeapObject> phi_bb232_17;
  TNode<UintPtrT> phi_bb232_18;
  TNode<IntPtrT> phi_bb232_19;
  TNode<IntPtrT> phi_bb232_23;
  TNode<IntPtrT> tmp295;
  TNode<BoolT> tmp296;
  if (block232.is_used()) {
    ca_.Bind(&block232, &phi_bb232_10, &phi_bb232_11, &phi_bb232_13, &phi_bb232_14, &phi_bb232_15, &phi_bb232_16, &phi_bb232_17, &phi_bb232_18, &phi_bb232_19, &phi_bb232_23);
    tmp295 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp296 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp295});
    ca_.Goto(&block233, phi_bb232_10, phi_bb232_11, phi_bb232_13, phi_bb232_14, phi_bb232_15, phi_bb232_16, phi_bb232_17, phi_bb232_18, phi_bb232_19, phi_bb232_23, tmp296);
  }

  TNode<IntPtrT> phi_bb233_10;
  TNode<BuiltinPtr> phi_bb233_11;
  TNode<FixedArray> phi_bb233_13;
  TNode<IntPtrT> phi_bb233_14;
  TNode<IntPtrT> phi_bb233_15;
  TNode<BoolT> phi_bb233_16;
  TNode<PrimitiveHeapObject> phi_bb233_17;
  TNode<UintPtrT> phi_bb233_18;
  TNode<IntPtrT> phi_bb233_19;
  TNode<IntPtrT> phi_bb233_23;
  TNode<BoolT> phi_bb233_27;
  if (block233.is_used()) {
    ca_.Bind(&block233, &phi_bb233_10, &phi_bb233_11, &phi_bb233_13, &phi_bb233_14, &phi_bb233_15, &phi_bb233_16, &phi_bb233_17, &phi_bb233_18, &phi_bb233_19, &phi_bb233_23, &phi_bb233_27);
    ca_.Branch(phi_bb233_27, &block229, std::vector<compiler::Node*>{phi_bb233_10, phi_bb233_11, phi_bb233_13, phi_bb233_14, phi_bb233_15, phi_bb233_16, phi_bb233_17, phi_bb233_18, phi_bb233_19, phi_bb233_23}, &block230, std::vector<compiler::Node*>{phi_bb233_10, phi_bb233_11, phi_bb233_13, phi_bb233_14, phi_bb233_15, phi_bb233_16, phi_bb233_17, phi_bb233_18, phi_bb233_19, phi_bb233_23});
  }

  TNode<IntPtrT> phi_bb229_10;
  TNode<BuiltinPtr> phi_bb229_11;
  TNode<FixedArray> phi_bb229_13;
  TNode<IntPtrT> phi_bb229_14;
  TNode<IntPtrT> phi_bb229_15;
  TNode<BoolT> phi_bb229_16;
  TNode<PrimitiveHeapObject> phi_bb229_17;
  TNode<UintPtrT> phi_bb229_18;
  TNode<IntPtrT> phi_bb229_19;
  TNode<IntPtrT> phi_bb229_23;
  if (block229.is_used()) {
    ca_.Bind(&block229, &phi_bb229_10, &phi_bb229_11, &phi_bb229_13, &phi_bb229_14, &phi_bb229_15, &phi_bb229_16, &phi_bb229_17, &phi_bb229_18, &phi_bb229_19, &phi_bb229_23);
    ca_.Goto(&block228, phi_bb229_10, phi_bb229_11, phi_bb229_13, phi_bb229_14, phi_bb229_15, phi_bb229_16, phi_bb229_17, phi_bb229_18, phi_bb229_19, phi_bb229_23);
  }

  TNode<IntPtrT> phi_bb230_10;
  TNode<BuiltinPtr> phi_bb230_11;
  TNode<FixedArray> phi_bb230_13;
  TNode<IntPtrT> phi_bb230_14;
  TNode<IntPtrT> phi_bb230_15;
  TNode<BoolT> phi_bb230_16;
  TNode<PrimitiveHeapObject> phi_bb230_17;
  TNode<UintPtrT> phi_bb230_18;
  TNode<IntPtrT> phi_bb230_19;
  TNode<IntPtrT> phi_bb230_23;
  TNode<IntPtrT> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<BoolT> tmp299;
  if (block230.is_used()) {
    ca_.Bind(&block230, &phi_bb230_10, &phi_bb230_11, &phi_bb230_13, &phi_bb230_14, &phi_bb230_15, &phi_bb230_16, &phi_bb230_17, &phi_bb230_18, &phi_bb230_19, &phi_bb230_23);
    tmp297 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{phi_bb230_23});
    tmp298 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp297}, TNode<IntPtrT>{tmp3});
    tmp299 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp298}, TNode<IntPtrT>{phi_bb230_23});
    ca_.Branch(tmp299, &block234, std::vector<compiler::Node*>{phi_bb230_10, phi_bb230_11, phi_bb230_13, phi_bb230_14, phi_bb230_15, phi_bb230_16, phi_bb230_17, phi_bb230_18, phi_bb230_19, phi_bb230_23, phi_bb230_23}, &block235, std::vector<compiler::Node*>{phi_bb230_10, phi_bb230_11, phi_bb230_13, phi_bb230_14, phi_bb230_15, phi_bb230_16, phi_bb230_17, phi_bb230_18, phi_bb230_19, phi_bb230_23, phi_bb230_23});
  }

  TNode<IntPtrT> phi_bb234_10;
  TNode<BuiltinPtr> phi_bb234_11;
  TNode<FixedArray> phi_bb234_13;
  TNode<IntPtrT> phi_bb234_14;
  TNode<IntPtrT> phi_bb234_15;
  TNode<BoolT> phi_bb234_16;
  TNode<PrimitiveHeapObject> phi_bb234_17;
  TNode<UintPtrT> phi_bb234_18;
  TNode<IntPtrT> phi_bb234_19;
  TNode<IntPtrT> phi_bb234_23;
  TNode<IntPtrT> phi_bb234_26;
  if (block234.is_used()) {
    ca_.Bind(&block234, &phi_bb234_10, &phi_bb234_11, &phi_bb234_13, &phi_bb234_14, &phi_bb234_15, &phi_bb234_16, &phi_bb234_17, &phi_bb234_18, &phi_bb234_19, &phi_bb234_23, &phi_bb234_26);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb235_10;
  TNode<BuiltinPtr> phi_bb235_11;
  TNode<FixedArray> phi_bb235_13;
  TNode<IntPtrT> phi_bb235_14;
  TNode<IntPtrT> phi_bb235_15;
  TNode<BoolT> phi_bb235_16;
  TNode<PrimitiveHeapObject> phi_bb235_17;
  TNode<UintPtrT> phi_bb235_18;
  TNode<IntPtrT> phi_bb235_19;
  TNode<IntPtrT> phi_bb235_23;
  TNode<IntPtrT> phi_bb235_26;
  TNode<IntPtrT> tmp300;
  if (block235.is_used()) {
    ca_.Bind(&block235, &phi_bb235_10, &phi_bb235_11, &phi_bb235_13, &phi_bb235_14, &phi_bb235_15, &phi_bb235_16, &phi_bb235_17, &phi_bb235_18, &phi_bb235_19, &phi_bb235_23, &phi_bb235_26);
    tmp300 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb235_15}, TNode<IntPtrT>{tmp297});
    ca_.Branch(tmp291, &block236, std::vector<compiler::Node*>{phi_bb235_10, phi_bb235_11, phi_bb235_13, phi_bb235_14, phi_bb235_16, phi_bb235_17, phi_bb235_18, phi_bb235_19, phi_bb235_23, phi_bb235_26}, &block237, std::vector<compiler::Node*>{phi_bb235_10, phi_bb235_11, phi_bb235_13, phi_bb235_14, phi_bb235_16, phi_bb235_17, phi_bb235_18, phi_bb235_19, phi_bb235_23, phi_bb235_26});
  }

  TNode<IntPtrT> phi_bb236_10;
  TNode<BuiltinPtr> phi_bb236_11;
  TNode<FixedArray> phi_bb236_13;
  TNode<IntPtrT> phi_bb236_14;
  TNode<BoolT> phi_bb236_16;
  TNode<PrimitiveHeapObject> phi_bb236_17;
  TNode<UintPtrT> phi_bb236_18;
  TNode<IntPtrT> phi_bb236_19;
  TNode<IntPtrT> phi_bb236_23;
  TNode<IntPtrT> phi_bb236_26;
  TNode<Smi> tmp301;
  TNode<IntPtrT> tmp302;
  TNode<IntPtrT> tmp303;
  TNode<BoolT> tmp304;
  if (block236.is_used()) {
    ca_.Bind(&block236, &phi_bb236_10, &phi_bb236_11, &phi_bb236_13, &phi_bb236_14, &phi_bb236_16, &phi_bb236_17, &phi_bb236_18, &phi_bb236_19, &phi_bb236_23, &phi_bb236_26);
    tmp301 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb236_26});
    tmp302 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb236_13});
    tmp303 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp304 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb236_14}, TNode<IntPtrT>{tmp303});
    ca_.Branch(tmp304, &block239, std::vector<compiler::Node*>{phi_bb236_10, phi_bb236_11, phi_bb236_13, phi_bb236_14, phi_bb236_16, phi_bb236_17, phi_bb236_18, phi_bb236_19, phi_bb236_23, phi_bb236_26}, &block240, std::vector<compiler::Node*>{phi_bb236_10, phi_bb236_11, phi_bb236_13, phi_bb236_14, phi_bb236_16, phi_bb236_17, phi_bb236_18, phi_bb236_19, phi_bb236_23, phi_bb236_26});
  }

  TNode<IntPtrT> phi_bb240_10;
  TNode<BuiltinPtr> phi_bb240_11;
  TNode<FixedArray> phi_bb240_13;
  TNode<IntPtrT> phi_bb240_14;
  TNode<BoolT> phi_bb240_16;
  TNode<PrimitiveHeapObject> phi_bb240_17;
  TNode<UintPtrT> phi_bb240_18;
  TNode<IntPtrT> phi_bb240_19;
  TNode<IntPtrT> phi_bb240_23;
  TNode<IntPtrT> phi_bb240_26;
  if (block240.is_used()) {
    ca_.Bind(&block240, &phi_bb240_10, &phi_bb240_11, &phi_bb240_13, &phi_bb240_14, &phi_bb240_16, &phi_bb240_17, &phi_bb240_18, &phi_bb240_19, &phi_bb240_23, &phi_bb240_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb239_10;
  TNode<BuiltinPtr> phi_bb239_11;
  TNode<FixedArray> phi_bb239_13;
  TNode<IntPtrT> phi_bb239_14;
  TNode<BoolT> phi_bb239_16;
  TNode<PrimitiveHeapObject> phi_bb239_17;
  TNode<UintPtrT> phi_bb239_18;
  TNode<IntPtrT> phi_bb239_19;
  TNode<IntPtrT> phi_bb239_23;
  TNode<IntPtrT> phi_bb239_26;
  TNode<BoolT> tmp305;
  if (block239.is_used()) {
    ca_.Bind(&block239, &phi_bb239_10, &phi_bb239_11, &phi_bb239_13, &phi_bb239_14, &phi_bb239_16, &phi_bb239_17, &phi_bb239_18, &phi_bb239_19, &phi_bb239_23, &phi_bb239_26);
    tmp305 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb239_14}, TNode<IntPtrT>{tmp302});
    ca_.Branch(tmp305, &block241, std::vector<compiler::Node*>{phi_bb239_10, phi_bb239_11, phi_bb239_13, phi_bb239_14, phi_bb239_16, phi_bb239_17, phi_bb239_18, phi_bb239_19, phi_bb239_23, phi_bb239_26}, &block242, std::vector<compiler::Node*>{phi_bb239_10, phi_bb239_11, phi_bb239_13, phi_bb239_14, phi_bb239_16, phi_bb239_17, phi_bb239_18, phi_bb239_19, phi_bb239_23, phi_bb239_26});
  }

  TNode<IntPtrT> phi_bb242_10;
  TNode<BuiltinPtr> phi_bb242_11;
  TNode<FixedArray> phi_bb242_13;
  TNode<IntPtrT> phi_bb242_14;
  TNode<BoolT> phi_bb242_16;
  TNode<PrimitiveHeapObject> phi_bb242_17;
  TNode<UintPtrT> phi_bb242_18;
  TNode<IntPtrT> phi_bb242_19;
  TNode<IntPtrT> phi_bb242_23;
  TNode<IntPtrT> phi_bb242_26;
  if (block242.is_used()) {
    ca_.Bind(&block242, &phi_bb242_10, &phi_bb242_11, &phi_bb242_13, &phi_bb242_14, &phi_bb242_16, &phi_bb242_17, &phi_bb242_18, &phi_bb242_19, &phi_bb242_23, &phi_bb242_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb241_10;
  TNode<BuiltinPtr> phi_bb241_11;
  TNode<FixedArray> phi_bb241_13;
  TNode<IntPtrT> phi_bb241_14;
  TNode<BoolT> phi_bb241_16;
  TNode<PrimitiveHeapObject> phi_bb241_17;
  TNode<UintPtrT> phi_bb241_18;
  TNode<IntPtrT> phi_bb241_19;
  TNode<IntPtrT> phi_bb241_23;
  TNode<IntPtrT> phi_bb241_26;
  TNode<BoolT> tmp306;
  if (block241.is_used()) {
    ca_.Bind(&block241, &phi_bb241_10, &phi_bb241_11, &phi_bb241_13, &phi_bb241_14, &phi_bb241_16, &phi_bb241_17, &phi_bb241_18, &phi_bb241_19, &phi_bb241_23, &phi_bb241_26);
    tmp306 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb241_14}, TNode<IntPtrT>{tmp302});
    ca_.Branch(tmp306, &block243, std::vector<compiler::Node*>{phi_bb241_10, phi_bb241_11, phi_bb241_13, phi_bb241_14, phi_bb241_16, phi_bb241_17, phi_bb241_18, phi_bb241_19, phi_bb241_23, phi_bb241_26}, &block244, std::vector<compiler::Node*>{phi_bb241_10, phi_bb241_11, phi_bb241_13, phi_bb241_14, phi_bb241_16, phi_bb241_17, phi_bb241_18, phi_bb241_19, phi_bb241_23, phi_bb241_26});
  }

  TNode<IntPtrT> phi_bb243_10;
  TNode<BuiltinPtr> phi_bb243_11;
  TNode<FixedArray> phi_bb243_13;
  TNode<IntPtrT> phi_bb243_14;
  TNode<BoolT> phi_bb243_16;
  TNode<PrimitiveHeapObject> phi_bb243_17;
  TNode<UintPtrT> phi_bb243_18;
  TNode<IntPtrT> phi_bb243_19;
  TNode<IntPtrT> phi_bb243_23;
  TNode<IntPtrT> phi_bb243_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp307;
  TNode<IntPtrT> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<IntPtrT> tmp310;
  TNode<IntPtrT> tmp311;
  TNode<UintPtrT> tmp312;
  TNode<UintPtrT> tmp313;
  TNode<BoolT> tmp314;
  if (block243.is_used()) {
    ca_.Bind(&block243, &phi_bb243_10, &phi_bb243_11, &phi_bb243_13, &phi_bb243_14, &phi_bb243_16, &phi_bb243_17, &phi_bb243_18, &phi_bb243_19, &phi_bb243_23, &phi_bb243_26);
    std::tie(tmp307, tmp308, tmp309) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb243_13}).Flatten();
    tmp310 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp311 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb243_14}, TNode<IntPtrT>{tmp310});
    tmp312 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb243_14});
    tmp313 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp309});
    tmp314 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp312}, TNode<UintPtrT>{tmp313});
    ca_.Branch(tmp314, &block250, std::vector<compiler::Node*>{phi_bb243_10, phi_bb243_11, phi_bb243_13, phi_bb243_16, phi_bb243_17, phi_bb243_18, phi_bb243_19, phi_bb243_23, phi_bb243_26, phi_bb243_13, phi_bb243_14, phi_bb243_14, phi_bb243_14, phi_bb243_14}, &block251, std::vector<compiler::Node*>{phi_bb243_10, phi_bb243_11, phi_bb243_13, phi_bb243_16, phi_bb243_17, phi_bb243_18, phi_bb243_19, phi_bb243_23, phi_bb243_26, phi_bb243_13, phi_bb243_14, phi_bb243_14, phi_bb243_14, phi_bb243_14});
  }

  TNode<IntPtrT> phi_bb250_10;
  TNode<BuiltinPtr> phi_bb250_11;
  TNode<FixedArray> phi_bb250_13;
  TNode<BoolT> phi_bb250_16;
  TNode<PrimitiveHeapObject> phi_bb250_17;
  TNode<UintPtrT> phi_bb250_18;
  TNode<IntPtrT> phi_bb250_19;
  TNode<IntPtrT> phi_bb250_23;
  TNode<IntPtrT> phi_bb250_26;
  TNode<FixedArray> phi_bb250_31;
  TNode<IntPtrT> phi_bb250_35;
  TNode<IntPtrT> phi_bb250_36;
  TNode<IntPtrT> phi_bb250_40;
  TNode<IntPtrT> phi_bb250_41;
  TNode<IntPtrT> tmp315;
  TNode<IntPtrT> tmp316;
  TNode<Union<HeapObject, TaggedIndex>> tmp317;
  TNode<IntPtrT> tmp318;
  if (block250.is_used()) {
    ca_.Bind(&block250, &phi_bb250_10, &phi_bb250_11, &phi_bb250_13, &phi_bb250_16, &phi_bb250_17, &phi_bb250_18, &phi_bb250_19, &phi_bb250_23, &phi_bb250_26, &phi_bb250_31, &phi_bb250_35, &phi_bb250_36, &phi_bb250_40, &phi_bb250_41);
    tmp315 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb250_41});
    tmp316 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp308}, TNode<IntPtrT>{tmp315});
    std::tie(tmp317, tmp318) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp307}, TNode<IntPtrT>{tmp316}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp317, tmp318}, tmp301);
    ca_.Goto(&block245, phi_bb250_10, phi_bb250_11, phi_bb250_13, tmp311, phi_bb250_16, phi_bb250_17, phi_bb250_18, phi_bb250_19, phi_bb250_23, phi_bb250_26);
  }

  TNode<IntPtrT> phi_bb251_10;
  TNode<BuiltinPtr> phi_bb251_11;
  TNode<FixedArray> phi_bb251_13;
  TNode<BoolT> phi_bb251_16;
  TNode<PrimitiveHeapObject> phi_bb251_17;
  TNode<UintPtrT> phi_bb251_18;
  TNode<IntPtrT> phi_bb251_19;
  TNode<IntPtrT> phi_bb251_23;
  TNode<IntPtrT> phi_bb251_26;
  TNode<FixedArray> phi_bb251_31;
  TNode<IntPtrT> phi_bb251_35;
  TNode<IntPtrT> phi_bb251_36;
  TNode<IntPtrT> phi_bb251_40;
  TNode<IntPtrT> phi_bb251_41;
  if (block251.is_used()) {
    ca_.Bind(&block251, &phi_bb251_10, &phi_bb251_11, &phi_bb251_13, &phi_bb251_16, &phi_bb251_17, &phi_bb251_18, &phi_bb251_19, &phi_bb251_23, &phi_bb251_26, &phi_bb251_31, &phi_bb251_35, &phi_bb251_36, &phi_bb251_40, &phi_bb251_41);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb244_10;
  TNode<BuiltinPtr> phi_bb244_11;
  TNode<FixedArray> phi_bb244_13;
  TNode<IntPtrT> phi_bb244_14;
  TNode<BoolT> phi_bb244_16;
  TNode<PrimitiveHeapObject> phi_bb244_17;
  TNode<UintPtrT> phi_bb244_18;
  TNode<IntPtrT> phi_bb244_19;
  TNode<IntPtrT> phi_bb244_23;
  TNode<IntPtrT> phi_bb244_26;
  TNode<IntPtrT> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<BoolT> tmp321;
  if (block244.is_used()) {
    ca_.Bind(&block244, &phi_bb244_10, &phi_bb244_11, &phi_bb244_13, &phi_bb244_14, &phi_bb244_16, &phi_bb244_17, &phi_bb244_18, &phi_bb244_19, &phi_bb244_23, &phi_bb244_26);
    tmp319 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp302});
    tmp320 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp321 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp319}, TNode<IntPtrT>{tmp320});
    ca_.Branch(tmp321, &block254, std::vector<compiler::Node*>{phi_bb244_10, phi_bb244_11, phi_bb244_13, phi_bb244_14, phi_bb244_16, phi_bb244_17, phi_bb244_18, phi_bb244_19, phi_bb244_23, phi_bb244_26}, &block255, std::vector<compiler::Node*>{phi_bb244_10, phi_bb244_11, phi_bb244_13, phi_bb244_14, phi_bb244_16, phi_bb244_17, phi_bb244_18, phi_bb244_19, phi_bb244_23, phi_bb244_26});
  }

  TNode<IntPtrT> phi_bb254_10;
  TNode<BuiltinPtr> phi_bb254_11;
  TNode<FixedArray> phi_bb254_13;
  TNode<IntPtrT> phi_bb254_14;
  TNode<BoolT> phi_bb254_16;
  TNode<PrimitiveHeapObject> phi_bb254_17;
  TNode<UintPtrT> phi_bb254_18;
  TNode<IntPtrT> phi_bb254_19;
  TNode<IntPtrT> phi_bb254_23;
  TNode<IntPtrT> phi_bb254_26;
  TNode<IntPtrT> tmp322;
  if (block254.is_used()) {
    ca_.Bind(&block254, &phi_bb254_10, &phi_bb254_11, &phi_bb254_13, &phi_bb254_14, &phi_bb254_16, &phi_bb254_17, &phi_bb254_18, &phi_bb254_19, &phi_bb254_23, &phi_bb254_26);
    tmp322 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block256, phi_bb254_10, phi_bb254_11, phi_bb254_13, phi_bb254_14, phi_bb254_16, phi_bb254_17, phi_bb254_18, phi_bb254_19, phi_bb254_23, phi_bb254_26, tmp322);
  }

  TNode<IntPtrT> phi_bb255_10;
  TNode<BuiltinPtr> phi_bb255_11;
  TNode<FixedArray> phi_bb255_13;
  TNode<IntPtrT> phi_bb255_14;
  TNode<BoolT> phi_bb255_16;
  TNode<PrimitiveHeapObject> phi_bb255_17;
  TNode<UintPtrT> phi_bb255_18;
  TNode<IntPtrT> phi_bb255_19;
  TNode<IntPtrT> phi_bb255_23;
  TNode<IntPtrT> phi_bb255_26;
  if (block255.is_used()) {
    ca_.Bind(&block255, &phi_bb255_10, &phi_bb255_11, &phi_bb255_13, &phi_bb255_14, &phi_bb255_16, &phi_bb255_17, &phi_bb255_18, &phi_bb255_19, &phi_bb255_23, &phi_bb255_26);
    ca_.Goto(&block256, phi_bb255_10, phi_bb255_11, phi_bb255_13, phi_bb255_14, phi_bb255_16, phi_bb255_17, phi_bb255_18, phi_bb255_19, phi_bb255_23, phi_bb255_26, tmp319);
  }

  TNode<IntPtrT> phi_bb256_10;
  TNode<BuiltinPtr> phi_bb256_11;
  TNode<FixedArray> phi_bb256_13;
  TNode<IntPtrT> phi_bb256_14;
  TNode<BoolT> phi_bb256_16;
  TNode<PrimitiveHeapObject> phi_bb256_17;
  TNode<UintPtrT> phi_bb256_18;
  TNode<IntPtrT> phi_bb256_19;
  TNode<IntPtrT> phi_bb256_23;
  TNode<IntPtrT> phi_bb256_26;
  TNode<IntPtrT> phi_bb256_32;
  TNode<IntPtrT> tmp323;
  TNode<BoolT> tmp324;
  if (block256.is_used()) {
    ca_.Bind(&block256, &phi_bb256_10, &phi_bb256_11, &phi_bb256_13, &phi_bb256_14, &phi_bb256_16, &phi_bb256_17, &phi_bb256_18, &phi_bb256_19, &phi_bb256_23, &phi_bb256_26, &phi_bb256_32);
    tmp323 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp324 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb256_32}, TNode<IntPtrT>{tmp323});
    ca_.Branch(tmp324, &block258, std::vector<compiler::Node*>{phi_bb256_10, phi_bb256_11, phi_bb256_13, phi_bb256_14, phi_bb256_16, phi_bb256_17, phi_bb256_18, phi_bb256_19, phi_bb256_23, phi_bb256_26}, &block259, std::vector<compiler::Node*>{phi_bb256_10, phi_bb256_11, phi_bb256_13, phi_bb256_14, phi_bb256_16, phi_bb256_17, phi_bb256_18, phi_bb256_19, phi_bb256_23, phi_bb256_26});
  }

  TNode<IntPtrT> phi_bb259_10;
  TNode<BuiltinPtr> phi_bb259_11;
  TNode<FixedArray> phi_bb259_13;
  TNode<IntPtrT> phi_bb259_14;
  TNode<BoolT> phi_bb259_16;
  TNode<PrimitiveHeapObject> phi_bb259_17;
  TNode<UintPtrT> phi_bb259_18;
  TNode<IntPtrT> phi_bb259_19;
  TNode<IntPtrT> phi_bb259_23;
  TNode<IntPtrT> phi_bb259_26;
  if (block259.is_used()) {
    ca_.Bind(&block259, &phi_bb259_10, &phi_bb259_11, &phi_bb259_13, &phi_bb259_14, &phi_bb259_16, &phi_bb259_17, &phi_bb259_18, &phi_bb259_19, &phi_bb259_23, &phi_bb259_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb258_10;
  TNode<BuiltinPtr> phi_bb258_11;
  TNode<FixedArray> phi_bb258_13;
  TNode<IntPtrT> phi_bb258_14;
  TNode<BoolT> phi_bb258_16;
  TNode<PrimitiveHeapObject> phi_bb258_17;
  TNode<UintPtrT> phi_bb258_18;
  TNode<IntPtrT> phi_bb258_19;
  TNode<IntPtrT> phi_bb258_23;
  TNode<IntPtrT> phi_bb258_26;
  TNode<FixedArray> tmp325;
  TNode<Union<HeapObject, TaggedIndex>> tmp326;
  TNode<IntPtrT> tmp327;
  TNode<IntPtrT> tmp328;
  TNode<UintPtrT> tmp329;
  TNode<IntPtrT> tmp330;
  TNode<UintPtrT> tmp331;
  TNode<UintPtrT> tmp332;
  TNode<BoolT> tmp333;
  if (block258.is_used()) {
    ca_.Bind(&block258, &phi_bb258_10, &phi_bb258_11, &phi_bb258_13, &phi_bb258_14, &phi_bb258_16, &phi_bb258_17, &phi_bb258_18, &phi_bb258_19, &phi_bb258_23, &phi_bb258_26);
    tmp325 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb256_32});
    std::tie(tmp326, tmp327, tmp328) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb258_13}).Flatten();
    tmp329 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp330 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp329});
    tmp331 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp330});
    tmp332 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp328});
    tmp333 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp331}, TNode<UintPtrT>{tmp332});
    ca_.Branch(tmp333, &block265, std::vector<compiler::Node*>{phi_bb258_10, phi_bb258_11, phi_bb258_13, phi_bb258_14, phi_bb258_16, phi_bb258_17, phi_bb258_18, phi_bb258_19, phi_bb258_23, phi_bb258_26, phi_bb258_13}, &block266, std::vector<compiler::Node*>{phi_bb258_10, phi_bb258_11, phi_bb258_13, phi_bb258_14, phi_bb258_16, phi_bb258_17, phi_bb258_18, phi_bb258_19, phi_bb258_23, phi_bb258_26, phi_bb258_13});
  }

  TNode<IntPtrT> phi_bb265_10;
  TNode<BuiltinPtr> phi_bb265_11;
  TNode<FixedArray> phi_bb265_13;
  TNode<IntPtrT> phi_bb265_14;
  TNode<BoolT> phi_bb265_16;
  TNode<PrimitiveHeapObject> phi_bb265_17;
  TNode<UintPtrT> phi_bb265_18;
  TNode<IntPtrT> phi_bb265_19;
  TNode<IntPtrT> phi_bb265_23;
  TNode<IntPtrT> phi_bb265_26;
  TNode<FixedArray> phi_bb265_34;
  TNode<IntPtrT> tmp334;
  TNode<IntPtrT> tmp335;
  TNode<Union<HeapObject, TaggedIndex>> tmp336;
  TNode<IntPtrT> tmp337;
  TNode<Union<HeapObject, TaggedIndex>> tmp338;
  TNode<IntPtrT> tmp339;
  TNode<IntPtrT> tmp340;
  TNode<UintPtrT> tmp341;
  TNode<IntPtrT> tmp342;
  TNode<UintPtrT> tmp343;
  TNode<UintPtrT> tmp344;
  TNode<BoolT> tmp345;
  if (block265.is_used()) {
    ca_.Bind(&block265, &phi_bb265_10, &phi_bb265_11, &phi_bb265_13, &phi_bb265_14, &phi_bb265_16, &phi_bb265_17, &phi_bb265_18, &phi_bb265_19, &phi_bb265_23, &phi_bb265_26, &phi_bb265_34);
    tmp334 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp330});
    tmp335 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp327}, TNode<IntPtrT>{tmp334});
    std::tie(tmp336, tmp337) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp326}, TNode<IntPtrT>{tmp335}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp336, tmp337}, tmp325);
    std::tie(tmp338, tmp339, tmp340) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp325}).Flatten();
    tmp341 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp342 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp341});
    tmp343 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp342});
    tmp344 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp340});
    tmp345 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp343}, TNode<UintPtrT>{tmp344});
    ca_.Branch(tmp345, &block274, std::vector<compiler::Node*>{phi_bb265_10, phi_bb265_11, phi_bb265_13, phi_bb265_14, phi_bb265_16, phi_bb265_17, phi_bb265_18, phi_bb265_19, phi_bb265_23, phi_bb265_26}, &block275, std::vector<compiler::Node*>{phi_bb265_10, phi_bb265_11, phi_bb265_13, phi_bb265_14, phi_bb265_16, phi_bb265_17, phi_bb265_18, phi_bb265_19, phi_bb265_23, phi_bb265_26});
  }

  TNode<IntPtrT> phi_bb266_10;
  TNode<BuiltinPtr> phi_bb266_11;
  TNode<FixedArray> phi_bb266_13;
  TNode<IntPtrT> phi_bb266_14;
  TNode<BoolT> phi_bb266_16;
  TNode<PrimitiveHeapObject> phi_bb266_17;
  TNode<UintPtrT> phi_bb266_18;
  TNode<IntPtrT> phi_bb266_19;
  TNode<IntPtrT> phi_bb266_23;
  TNode<IntPtrT> phi_bb266_26;
  TNode<FixedArray> phi_bb266_34;
  if (block266.is_used()) {
    ca_.Bind(&block266, &phi_bb266_10, &phi_bb266_11, &phi_bb266_13, &phi_bb266_14, &phi_bb266_16, &phi_bb266_17, &phi_bb266_18, &phi_bb266_19, &phi_bb266_23, &phi_bb266_26, &phi_bb266_34);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb274_10;
  TNode<BuiltinPtr> phi_bb274_11;
  TNode<FixedArray> phi_bb274_13;
  TNode<IntPtrT> phi_bb274_14;
  TNode<BoolT> phi_bb274_16;
  TNode<PrimitiveHeapObject> phi_bb274_17;
  TNode<UintPtrT> phi_bb274_18;
  TNode<IntPtrT> phi_bb274_19;
  TNode<IntPtrT> phi_bb274_23;
  TNode<IntPtrT> phi_bb274_26;
  TNode<IntPtrT> tmp346;
  TNode<IntPtrT> tmp347;
  TNode<Union<HeapObject, TaggedIndex>> tmp348;
  TNode<IntPtrT> tmp349;
  TNode<Undefined> tmp350;
  TNode<Union<HeapObject, TaggedIndex>> tmp351;
  TNode<IntPtrT> tmp352;
  TNode<IntPtrT> tmp353;
  TNode<UintPtrT> tmp354;
  TNode<IntPtrT> tmp355;
  TNode<UintPtrT> tmp356;
  TNode<UintPtrT> tmp357;
  TNode<BoolT> tmp358;
  if (block274.is_used()) {
    ca_.Bind(&block274, &phi_bb274_10, &phi_bb274_11, &phi_bb274_13, &phi_bb274_14, &phi_bb274_16, &phi_bb274_17, &phi_bb274_18, &phi_bb274_19, &phi_bb274_23, &phi_bb274_26);
    tmp346 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp342});
    tmp347 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp339}, TNode<IntPtrT>{tmp346});
    std::tie(tmp348, tmp349) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp338}, TNode<IntPtrT>{tmp347}).Flatten();
    tmp350 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp348, tmp349}, tmp350);
    std::tie(tmp351, tmp352, tmp353) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp325}).Flatten();
    tmp354 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp355 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp354});
    tmp356 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp355});
    tmp357 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp353});
    tmp358 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp356}, TNode<UintPtrT>{tmp357});
    ca_.Branch(tmp358, &block283, std::vector<compiler::Node*>{phi_bb274_10, phi_bb274_11, phi_bb274_13, phi_bb274_14, phi_bb274_16, phi_bb274_17, phi_bb274_18, phi_bb274_19, phi_bb274_23, phi_bb274_26}, &block284, std::vector<compiler::Node*>{phi_bb274_10, phi_bb274_11, phi_bb274_13, phi_bb274_14, phi_bb274_16, phi_bb274_17, phi_bb274_18, phi_bb274_19, phi_bb274_23, phi_bb274_26});
  }

  TNode<IntPtrT> phi_bb275_10;
  TNode<BuiltinPtr> phi_bb275_11;
  TNode<FixedArray> phi_bb275_13;
  TNode<IntPtrT> phi_bb275_14;
  TNode<BoolT> phi_bb275_16;
  TNode<PrimitiveHeapObject> phi_bb275_17;
  TNode<UintPtrT> phi_bb275_18;
  TNode<IntPtrT> phi_bb275_19;
  TNode<IntPtrT> phi_bb275_23;
  TNode<IntPtrT> phi_bb275_26;
  if (block275.is_used()) {
    ca_.Bind(&block275, &phi_bb275_10, &phi_bb275_11, &phi_bb275_13, &phi_bb275_14, &phi_bb275_16, &phi_bb275_17, &phi_bb275_18, &phi_bb275_19, &phi_bb275_23, &phi_bb275_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb283_10;
  TNode<BuiltinPtr> phi_bb283_11;
  TNode<FixedArray> phi_bb283_13;
  TNode<IntPtrT> phi_bb283_14;
  TNode<BoolT> phi_bb283_16;
  TNode<PrimitiveHeapObject> phi_bb283_17;
  TNode<UintPtrT> phi_bb283_18;
  TNode<IntPtrT> phi_bb283_19;
  TNode<IntPtrT> phi_bb283_23;
  TNode<IntPtrT> phi_bb283_26;
  TNode<IntPtrT> tmp359;
  TNode<IntPtrT> tmp360;
  TNode<Union<HeapObject, TaggedIndex>> tmp361;
  TNode<IntPtrT> tmp362;
  TNode<IntPtrT> tmp363;
  if (block283.is_used()) {
    ca_.Bind(&block283, &phi_bb283_10, &phi_bb283_11, &phi_bb283_13, &phi_bb283_14, &phi_bb283_16, &phi_bb283_17, &phi_bb283_18, &phi_bb283_19, &phi_bb283_23, &phi_bb283_26);
    tmp359 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp355});
    tmp360 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp352}, TNode<IntPtrT>{tmp359});
    std::tie(tmp361, tmp362) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp351}, TNode<IntPtrT>{tmp360}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp361, tmp362}, tmp301);
    tmp363 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block245, phi_bb283_10, phi_bb283_11, tmp325, tmp363, phi_bb283_16, phi_bb283_17, phi_bb283_18, phi_bb283_19, phi_bb283_23, phi_bb283_26);
  }

  TNode<IntPtrT> phi_bb284_10;
  TNode<BuiltinPtr> phi_bb284_11;
  TNode<FixedArray> phi_bb284_13;
  TNode<IntPtrT> phi_bb284_14;
  TNode<BoolT> phi_bb284_16;
  TNode<PrimitiveHeapObject> phi_bb284_17;
  TNode<UintPtrT> phi_bb284_18;
  TNode<IntPtrT> phi_bb284_19;
  TNode<IntPtrT> phi_bb284_23;
  TNode<IntPtrT> phi_bb284_26;
  if (block284.is_used()) {
    ca_.Bind(&block284, &phi_bb284_10, &phi_bb284_11, &phi_bb284_13, &phi_bb284_14, &phi_bb284_16, &phi_bb284_17, &phi_bb284_18, &phi_bb284_19, &phi_bb284_23, &phi_bb284_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb245_10;
  TNode<BuiltinPtr> phi_bb245_11;
  TNode<FixedArray> phi_bb245_13;
  TNode<IntPtrT> phi_bb245_14;
  TNode<BoolT> phi_bb245_16;
  TNode<PrimitiveHeapObject> phi_bb245_17;
  TNode<UintPtrT> phi_bb245_18;
  TNode<IntPtrT> phi_bb245_19;
  TNode<IntPtrT> phi_bb245_23;
  TNode<IntPtrT> phi_bb245_26;
  TNode<Null> tmp364;
  if (block245.is_used()) {
    ca_.Bind(&block245, &phi_bb245_10, &phi_bb245_11, &phi_bb245_13, &phi_bb245_14, &phi_bb245_16, &phi_bb245_17, &phi_bb245_18, &phi_bb245_19, &phi_bb245_23, &phi_bb245_26);
    tmp364 = Null_0(state_);
    ca_.Goto(&block237, phi_bb245_10, phi_bb245_11, phi_bb245_13, phi_bb245_14, phi_bb245_16, tmp364, phi_bb245_18, phi_bb245_19, phi_bb245_23, phi_bb245_26);
  }

  TNode<IntPtrT> phi_bb237_10;
  TNode<BuiltinPtr> phi_bb237_11;
  TNode<FixedArray> phi_bb237_13;
  TNode<IntPtrT> phi_bb237_14;
  TNode<BoolT> phi_bb237_16;
  TNode<PrimitiveHeapObject> phi_bb237_17;
  TNode<UintPtrT> phi_bb237_18;
  TNode<IntPtrT> phi_bb237_19;
  TNode<IntPtrT> phi_bb237_23;
  TNode<IntPtrT> phi_bb237_26;
  if (block237.is_used()) {
    ca_.Bind(&block237, &phi_bb237_10, &phi_bb237_11, &phi_bb237_13, &phi_bb237_14, &phi_bb237_16, &phi_bb237_17, &phi_bb237_18, &phi_bb237_19, &phi_bb237_23, &phi_bb237_26);
    ca_.Goto(&block228, phi_bb237_10, phi_bb237_11, phi_bb237_13, phi_bb237_14, tmp300, phi_bb237_16, phi_bb237_17, phi_bb237_18, phi_bb237_19, phi_bb237_23);
  }

  TNode<IntPtrT> phi_bb228_10;
  TNode<BuiltinPtr> phi_bb228_11;
  TNode<FixedArray> phi_bb228_13;
  TNode<IntPtrT> phi_bb228_14;
  TNode<IntPtrT> phi_bb228_15;
  TNode<BoolT> phi_bb228_16;
  TNode<PrimitiveHeapObject> phi_bb228_17;
  TNode<UintPtrT> phi_bb228_18;
  TNode<IntPtrT> phi_bb228_19;
  TNode<IntPtrT> phi_bb228_23;
  TNode<String> tmp365;
  if (block228.is_used()) {
    ca_.Bind(&block228, &phi_bb228_10, &phi_bb228_11, &phi_bb228_13, &phi_bb228_14, &phi_bb228_15, &phi_bb228_16, &phi_bb228_17, &phi_bb228_18, &phi_bb228_19, &phi_bb228_23);
    tmp365 = BufferJoin_0(state_, TNode<Context>{p_context}, TorqueStructBuffer_0{TNode<FixedArray>{tmp5}, TNode<FixedArray>{phi_bb228_13}, TNode<IntPtrT>{phi_bb228_14}, TNode<IntPtrT>{phi_bb228_15}, TNode<BoolT>{phi_bb228_16}, TNode<PrimitiveHeapObject>{phi_bb228_17}}, TNode<String>{p_sep});
    ca_.Goto(&block287);
  }

    ca_.Bind(&block287);
  return TNode<String>{tmp365};
}

TF_BUILTIN(LoadJoinTypedElement_Int32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Int32Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Float16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Float16Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Float32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Float32Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Float64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Float64Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Uint8ClampedElements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Uint8ClampedElements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_BigUint64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_BigUint64Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_BigInt64Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_BigInt64Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Uint8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Uint8Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Int8Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Int8Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Uint16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Uint16Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Int16Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Int16Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

TF_BUILTIN(LoadJoinTypedElement_Uint32Elements_0, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<UintPtrT> parameter2 = UncheckedParameter<UintPtrT>(Descriptor::kK);
  USE(parameter2);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSTypedArray> tmp0;
  TNode<BoolT> tmp1;
  TNode<BoolT> tmp2;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = UnsafeCast_JSTypedArray_0(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1});
    tmp1 = CodeStubAssembler(state_).IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean(TNode<JSArrayBufferView>{tmp0});
    tmp2 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp1});
    ca_.Branch(tmp2, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 65});
      CodeStubAssembler(state_).FailAssert("Torque assert '!typed_array::IsJSArrayBufferViewDetachedOrOutOfBoundsBoolean( typedArray)' failed", pos_stack);
    }
  }

  TNode<RawPtrT> tmp3;
  TNode<Numeric> tmp4;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp3 = CodeStubAssembler(state_).LoadJSTypedArrayDataPtr(TNode<JSTypedArray>{tmp0});
    tmp4 = CodeStubAssembler(state_).LoadFixedTypedArrayElementAsTagged(TNode<RawPtrT>{tmp3}, TNode<UintPtrT>{parameter2}, (KindForArrayType_Uint32Elements_0(state_)));
    CodeStubAssembler(state_).Return(tmp4);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=631&c=10
TNode<String> ArrayJoinImpl_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<String> p_sep, TNode<Number> p_lengthNumber, bool p_useToLocaleString, TNode<JSAny> p_locales, TNode<JSAny> p_options, TNode<BuiltinPtr> p_initialLoadFn) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, BoolT> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block30(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, BoolT> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block40(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block42(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block46(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block48(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block50(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, IntPtrT> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block65(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block72(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block80(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block81(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block89(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block90(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block93(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block98(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block97(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block103(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block104(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block111(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block110(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block113(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block112(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block116(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block115(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block118(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block117(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block119(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block126(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block127(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block120(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block130(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block131(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, IntPtrT> block132(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block135(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block134(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block141(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block142(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block150(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block151(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block159(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block160(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block121(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block108(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block166(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block165(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block168(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block167(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block170(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block169(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block175(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, FixedArray> block176(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block107(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block94(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block181(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block180(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block183(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block182(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block184(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block191(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block192(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block185(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block195(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block196(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object, IntPtrT> block197(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block200(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block199(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray> block206(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object, FixedArray> block207(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block215(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block216(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block224(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block225(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String, String, Object> block186(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, String, String, String> block95(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block231(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block232(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, BoolT> block233(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block229(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block230(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block234(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block235(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block236(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block240(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block239(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block242(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block241(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block243(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block250(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block251(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block244(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block254(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block255(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, IntPtrT> block256(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block259(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block258(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray> block265(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT, FixedArray> block266(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block274(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block275(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block283(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block284(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block245(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT, IntPtrT> block237(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<IntPtrT, BuiltinPtr, FixedArray, IntPtrT, IntPtrT, BoolT, PrimitiveHeapObject, UintPtrT, IntPtrT, IntPtrT> block228(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block287(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<Map> tmp1;
  TNode<UintPtrT> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<FixedArray> tmp5;
  TNode<FixedArray> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<BoolT> tmp9;
  TNode<PrimitiveHeapObject> tmp10;
  TNode<UintPtrT> tmp11;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp1 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{p_receiver, tmp0});
    tmp2 = Convert_uintptr_Number_0(state_, TNode<Number>{p_lengthNumber});
    tmp3 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{p_sep});
    tmp4 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp5, tmp6, tmp7, tmp8, tmp9, tmp10) = NewBuffer_0(state_, TNode<UintPtrT>{tmp2}, TNode<String>{p_sep}).Flatten();
    tmp11 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block4, tmp4, p_initialLoadFn, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11);
  }

  TNode<IntPtrT> phi_bb4_10;
  TNode<BuiltinPtr> phi_bb4_11;
  TNode<FixedArray> phi_bb4_13;
  TNode<IntPtrT> phi_bb4_14;
  TNode<IntPtrT> phi_bb4_15;
  TNode<BoolT> phi_bb4_16;
  TNode<PrimitiveHeapObject> phi_bb4_17;
  TNode<UintPtrT> phi_bb4_18;
  TNode<BoolT> tmp12;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_10, &phi_bb4_11, &phi_bb4_13, &phi_bb4_14, &phi_bb4_15, &phi_bb4_16, &phi_bb4_17, &phi_bb4_18);
    tmp12 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{phi_bb4_18}, TNode<UintPtrT>{tmp2});
    ca_.Branch(tmp12, &block2, std::vector<compiler::Node*>{phi_bb4_10, phi_bb4_11, phi_bb4_13, phi_bb4_14, phi_bb4_15, phi_bb4_16, phi_bb4_17, phi_bb4_18}, &block3, std::vector<compiler::Node*>{phi_bb4_10, phi_bb4_11, phi_bb4_13, phi_bb4_14, phi_bb4_15, phi_bb4_16, phi_bb4_17, phi_bb4_18});
  }

  TNode<IntPtrT> phi_bb2_10;
  TNode<BuiltinPtr> phi_bb2_11;
  TNode<FixedArray> phi_bb2_13;
  TNode<IntPtrT> phi_bb2_14;
  TNode<IntPtrT> phi_bb2_15;
  TNode<BoolT> phi_bb2_16;
  TNode<PrimitiveHeapObject> phi_bb2_17;
  TNode<UintPtrT> phi_bb2_18;
  TNode<BoolT> tmp13;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_10, &phi_bb2_11, &phi_bb2_13, &phi_bb2_14, &phi_bb2_15, &phi_bb2_16, &phi_bb2_17, &phi_bb2_18);
    tmp13 = CannotUseSameArrayAccessor_JSTypedArray_0(state_, TNode<Context>{p_context}, TNode<BuiltinPtr>{phi_bb2_11}, TNode<JSReceiver>{p_receiver}, TNode<Map>{tmp1}, TNode<Number>{p_lengthNumber});
    ca_.Branch(tmp13, &block5, std::vector<compiler::Node*>{phi_bb2_10, phi_bb2_11, phi_bb2_13, phi_bb2_14, phi_bb2_15, phi_bb2_16, phi_bb2_17, phi_bb2_18}, &block6, std::vector<compiler::Node*>{phi_bb2_10, phi_bb2_11, phi_bb2_13, phi_bb2_14, phi_bb2_15, phi_bb2_16, phi_bb2_17, phi_bb2_18});
  }

  TNode<IntPtrT> phi_bb5_10;
  TNode<BuiltinPtr> phi_bb5_11;
  TNode<FixedArray> phi_bb5_13;
  TNode<IntPtrT> phi_bb5_14;
  TNode<IntPtrT> phi_bb5_15;
  TNode<BoolT> phi_bb5_16;
  TNode<PrimitiveHeapObject> phi_bb5_17;
  TNode<UintPtrT> phi_bb5_18;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_10, &phi_bb5_11, &phi_bb5_13, &phi_bb5_14, &phi_bb5_15, &phi_bb5_16, &phi_bb5_17, &phi_bb5_18);
    ca_.Goto(&block6, phi_bb5_10, ca_.UncheckedCast<BuiltinPtr>(ca_.SmiConstant(Builtin::kLoadJoinElement_GenericElementsAccessor_0)), phi_bb5_13, phi_bb5_14, phi_bb5_15, phi_bb5_16, phi_bb5_17, phi_bb5_18);
  }

  TNode<IntPtrT> phi_bb6_10;
  TNode<BuiltinPtr> phi_bb6_11;
  TNode<FixedArray> phi_bb6_13;
  TNode<IntPtrT> phi_bb6_14;
  TNode<IntPtrT> phi_bb6_15;
  TNode<BoolT> phi_bb6_16;
  TNode<PrimitiveHeapObject> phi_bb6_17;
  TNode<UintPtrT> phi_bb6_18;
  TNode<UintPtrT> tmp14;
  TNode<BoolT> tmp15;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_10, &phi_bb6_11, &phi_bb6_13, &phi_bb6_14, &phi_bb6_15, &phi_bb6_16, &phi_bb6_17, &phi_bb6_18);
    tmp14 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).UintPtrGreaterThan(TNode<UintPtrT>{phi_bb6_18}, TNode<UintPtrT>{tmp14});
    ca_.Branch(tmp15, &block7, std::vector<compiler::Node*>{phi_bb6_10, phi_bb6_13, phi_bb6_14, phi_bb6_15, phi_bb6_16, phi_bb6_17, phi_bb6_18}, &block8, std::vector<compiler::Node*>{phi_bb6_10, phi_bb6_13, phi_bb6_14, phi_bb6_15, phi_bb6_16, phi_bb6_17, phi_bb6_18});
  }

  TNode<IntPtrT> phi_bb7_10;
  TNode<FixedArray> phi_bb7_13;
  TNode<IntPtrT> phi_bb7_14;
  TNode<IntPtrT> phi_bb7_15;
  TNode<BoolT> phi_bb7_16;
  TNode<PrimitiveHeapObject> phi_bb7_17;
  TNode<UintPtrT> phi_bb7_18;
  TNode<IntPtrT> tmp16;
  TNode<IntPtrT> tmp17;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_10, &phi_bb7_13, &phi_bb7_14, &phi_bb7_15, &phi_bb7_16, &phi_bb7_17, &phi_bb7_18);
    tmp16 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp17 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb7_10}, TNode<IntPtrT>{tmp16});
    ca_.Goto(&block8, tmp17, phi_bb7_13, phi_bb7_14, phi_bb7_15, phi_bb7_16, phi_bb7_17, phi_bb7_18);
  }

  TNode<IntPtrT> phi_bb8_10;
  TNode<FixedArray> phi_bb8_13;
  TNode<IntPtrT> phi_bb8_14;
  TNode<IntPtrT> phi_bb8_15;
  TNode<BoolT> phi_bb8_16;
  TNode<PrimitiveHeapObject> phi_bb8_17;
  TNode<UintPtrT> phi_bb8_18;
  TNode<UintPtrT> tmp18;
  TNode<UintPtrT> tmp19;
  TNode<JSAny> tmp20;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_10, &phi_bb8_13, &phi_bb8_14, &phi_bb8_15, &phi_bb8_16, &phi_bb8_17, &phi_bb8_18);
    tmp18 = FromConstexpr_uintptr_constexpr_int31_0(state_, 1);
    tmp19 = CodeStubAssembler(state_).UintPtrAdd(TNode<UintPtrT>{phi_bb8_18}, TNode<UintPtrT>{tmp18});
tmp20 = TORQUE_CAST(CodeStubAssembler(state_).CallBuiltinPointer(Builtins::CallInterfaceDescriptorFor(ExampleBuiltinForTorqueFunctionPointerType(0)), phi_bb6_11, p_context, p_receiver, phi_bb8_18));
    if ((p_useToLocaleString)) {
      ca_.Goto(&block9, phi_bb8_13, phi_bb8_14, phi_bb8_15, phi_bb8_16, phi_bb8_17);
    } else {
      ca_.Goto(&block10, phi_bb8_13, phi_bb8_14, phi_bb8_15, phi_bb8_16, phi_bb8_17);
    }
  }

  TNode<FixedArray> phi_bb9_13;
  TNode<IntPtrT> phi_bb9_14;
  TNode<IntPtrT> phi_bb9_15;
  TNode<BoolT> phi_bb9_16;
  TNode<PrimitiveHeapObject> phi_bb9_17;
  TNode<String> tmp21;
  TNode<String> tmp22;
  TNode<BoolT> tmp23;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_13, &phi_bb9_14, &phi_bb9_15, &phi_bb9_16, &phi_bb9_17);
    tmp21 = ca_.CallBuiltin<String>(Builtin::kConvertToLocaleString, p_context, tmp20, p_locales, p_options);
    tmp22 = kEmptyString_0(state_);
    tmp23 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp21}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp22});
    ca_.Branch(tmp23, &block12, std::vector<compiler::Node*>{phi_bb9_13, phi_bb9_14, phi_bb9_15, phi_bb9_16, phi_bb9_17}, &block13, std::vector<compiler::Node*>{phi_bb9_13, phi_bb9_14, phi_bb9_15, phi_bb9_16, phi_bb9_17});
  }

  TNode<FixedArray> phi_bb12_13;
  TNode<IntPtrT> phi_bb12_14;
  TNode<IntPtrT> phi_bb12_15;
  TNode<BoolT> phi_bb12_16;
  TNode<PrimitiveHeapObject> phi_bb12_17;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_13, &phi_bb12_14, &phi_bb12_15, &phi_bb12_16, &phi_bb12_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb12_13, phi_bb12_14, phi_bb12_15, phi_bb12_16, phi_bb12_17, tmp19);
  }

  TNode<FixedArray> phi_bb13_13;
  TNode<IntPtrT> phi_bb13_14;
  TNode<IntPtrT> phi_bb13_15;
  TNode<BoolT> phi_bb13_16;
  TNode<PrimitiveHeapObject> phi_bb13_17;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_13, &phi_bb13_14, &phi_bb13_15, &phi_bb13_16, &phi_bb13_17);
    ca_.Goto(&block11, phi_bb13_13, phi_bb13_14, phi_bb13_15, phi_bb13_16, phi_bb13_17, tmp21);
  }

  TNode<FixedArray> phi_bb10_13;
  TNode<IntPtrT> phi_bb10_14;
  TNode<IntPtrT> phi_bb10_15;
  TNode<BoolT> phi_bb10_16;
  TNode<PrimitiveHeapObject> phi_bb10_17;
  TNode<String> tmp24;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_13, &phi_bb10_14, &phi_bb10_15, &phi_bb10_16, &phi_bb10_17);
    compiler::CodeAssemblerLabel label25(&ca_);
    tmp24 = Cast_String_1(state_, TNode<Context>{p_context}, TNode<Object>{tmp20}, &label25);
    ca_.Goto(&block16, phi_bb10_13, phi_bb10_14, phi_bb10_15, phi_bb10_16, phi_bb10_17);
    if (label25.is_used()) {
      ca_.Bind(&label25);
      ca_.Goto(&block17, phi_bb10_13, phi_bb10_14, phi_bb10_15, phi_bb10_16, phi_bb10_17);
    }
  }

  TNode<FixedArray> phi_bb17_13;
  TNode<IntPtrT> phi_bb17_14;
  TNode<IntPtrT> phi_bb17_15;
  TNode<BoolT> phi_bb17_16;
  TNode<PrimitiveHeapObject> phi_bb17_17;
  TNode<Number> tmp26;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_13, &phi_bb17_14, &phi_bb17_15, &phi_bb17_16, &phi_bb17_17);
    compiler::CodeAssemblerLabel label27(&ca_);
    tmp26 = Cast_Number_0(state_, TNode<Object>{ca_.UncheckedCast<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, Symbol, Undefined>>(tmp20)}, &label27);
    ca_.Goto(&block22, phi_bb17_13, phi_bb17_14, phi_bb17_15, phi_bb17_16, phi_bb17_17);
    if (label27.is_used()) {
      ca_.Bind(&label27);
      ca_.Goto(&block23, phi_bb17_13, phi_bb17_14, phi_bb17_15, phi_bb17_16, phi_bb17_17);
    }
  }

  TNode<FixedArray> phi_bb16_13;
  TNode<IntPtrT> phi_bb16_14;
  TNode<IntPtrT> phi_bb16_15;
  TNode<BoolT> phi_bb16_16;
  TNode<PrimitiveHeapObject> phi_bb16_17;
  TNode<String> tmp28;
  TNode<BoolT> tmp29;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_13, &phi_bb16_14, &phi_bb16_15, &phi_bb16_16, &phi_bb16_17);
    tmp28 = kEmptyString_0(state_);
    tmp29 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp24}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp28});
    ca_.Branch(tmp29, &block18, std::vector<compiler::Node*>{phi_bb16_13, phi_bb16_14, phi_bb16_15, phi_bb16_16, phi_bb16_17}, &block19, std::vector<compiler::Node*>{phi_bb16_13, phi_bb16_14, phi_bb16_15, phi_bb16_16, phi_bb16_17});
  }

  TNode<FixedArray> phi_bb18_13;
  TNode<IntPtrT> phi_bb18_14;
  TNode<IntPtrT> phi_bb18_15;
  TNode<BoolT> phi_bb18_16;
  TNode<PrimitiveHeapObject> phi_bb18_17;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_13, &phi_bb18_14, &phi_bb18_15, &phi_bb18_16, &phi_bb18_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb18_13, phi_bb18_14, phi_bb18_15, phi_bb18_16, phi_bb18_17, tmp19);
  }

  TNode<FixedArray> phi_bb19_13;
  TNode<IntPtrT> phi_bb19_14;
  TNode<IntPtrT> phi_bb19_15;
  TNode<BoolT> phi_bb19_16;
  TNode<PrimitiveHeapObject> phi_bb19_17;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_13, &phi_bb19_14, &phi_bb19_15, &phi_bb19_16, &phi_bb19_17);
    ca_.Goto(&block14, phi_bb19_13, phi_bb19_14, phi_bb19_15, phi_bb19_16, phi_bb19_17, tmp24);
  }

  TNode<FixedArray> phi_bb23_13;
  TNode<IntPtrT> phi_bb23_14;
  TNode<IntPtrT> phi_bb23_15;
  TNode<BoolT> phi_bb23_16;
  TNode<PrimitiveHeapObject> phi_bb23_17;
  TNode<BoolT> tmp30;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_13, &phi_bb23_14, &phi_bb23_15, &phi_bb23_16, &phi_bb23_17);
    tmp30 = CodeStubAssembler(state_).IsNullOrUndefined(TNode<Object>{ca_.UncheckedCast<Union<BigInt, Boolean, JSReceiver, Null, Symbol, Undefined>>(tmp20)});
    ca_.Branch(tmp30, &block24, std::vector<compiler::Node*>{phi_bb23_13, phi_bb23_14, phi_bb23_15, phi_bb23_16, phi_bb23_17}, &block25, std::vector<compiler::Node*>{phi_bb23_13, phi_bb23_14, phi_bb23_15, phi_bb23_16, phi_bb23_17});
  }

  TNode<FixedArray> phi_bb22_13;
  TNode<IntPtrT> phi_bb22_14;
  TNode<IntPtrT> phi_bb22_15;
  TNode<BoolT> phi_bb22_16;
  TNode<PrimitiveHeapObject> phi_bb22_17;
  TNode<String> tmp31;
  if (block22.is_used()) {
    ca_.Bind(&block22, &phi_bb22_13, &phi_bb22_14, &phi_bb22_15, &phi_bb22_16, &phi_bb22_17);
    tmp31 = CodeStubAssembler(state_).NumberToString(TNode<Number>{tmp26});
    ca_.Goto(&block20, phi_bb22_13, phi_bb22_14, phi_bb22_15, phi_bb22_16, phi_bb22_17, tmp31);
  }

  TNode<FixedArray> phi_bb24_13;
  TNode<IntPtrT> phi_bb24_14;
  TNode<IntPtrT> phi_bb24_15;
  TNode<BoolT> phi_bb24_16;
  TNode<PrimitiveHeapObject> phi_bb24_17;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_13, &phi_bb24_14, &phi_bb24_15, &phi_bb24_16, &phi_bb24_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb24_13, phi_bb24_14, phi_bb24_15, phi_bb24_16, phi_bb24_17, tmp19);
  }

  TNode<FixedArray> phi_bb25_13;
  TNode<IntPtrT> phi_bb25_14;
  TNode<IntPtrT> phi_bb25_15;
  TNode<BoolT> phi_bb25_16;
  TNode<PrimitiveHeapObject> phi_bb25_17;
  TNode<String> tmp32;
  TNode<String> tmp33;
  TNode<BoolT> tmp34;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_13, &phi_bb25_14, &phi_bb25_15, &phi_bb25_16, &phi_bb25_17);
    tmp32 = ToString_Inline_0(state_, TNode<Context>{p_context}, TNode<JSAny>{ca_.UncheckedCast<Union<BigInt, Boolean, JSReceiver, Null, Symbol, Undefined>>(tmp20)});
    tmp33 = kEmptyString_0(state_);
    tmp34 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp32}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp33});
    ca_.Branch(tmp34, &block26, std::vector<compiler::Node*>{phi_bb25_13, phi_bb25_14, phi_bb25_15, phi_bb25_16, phi_bb25_17}, &block27, std::vector<compiler::Node*>{phi_bb25_13, phi_bb25_14, phi_bb25_15, phi_bb25_16, phi_bb25_17});
  }

  TNode<FixedArray> phi_bb26_13;
  TNode<IntPtrT> phi_bb26_14;
  TNode<IntPtrT> phi_bb26_15;
  TNode<BoolT> phi_bb26_16;
  TNode<PrimitiveHeapObject> phi_bb26_17;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_13, &phi_bb26_14, &phi_bb26_15, &phi_bb26_16, &phi_bb26_17);
    ca_.Goto(&block4, phi_bb8_10, phi_bb6_11, phi_bb26_13, phi_bb26_14, phi_bb26_15, phi_bb26_16, phi_bb26_17, tmp19);
  }

  TNode<FixedArray> phi_bb27_13;
  TNode<IntPtrT> phi_bb27_14;
  TNode<IntPtrT> phi_bb27_15;
  TNode<BoolT> phi_bb27_16;
  TNode<PrimitiveHeapObject> phi_bb27_17;
  if (block27.is_used()) {
    ca_.Bind(&block27, &phi_bb27_13, &phi_bb27_14, &phi_bb27_15, &phi_bb27_16, &phi_bb27_17);
    ca_.Goto(&block20, phi_bb27_13, phi_bb27_14, phi_bb27_15, phi_bb27_16, phi_bb27_17, tmp32);
  }

  TNode<FixedArray> phi_bb20_13;
  TNode<IntPtrT> phi_bb20_14;
  TNode<IntPtrT> phi_bb20_15;
  TNode<BoolT> phi_bb20_16;
  TNode<PrimitiveHeapObject> phi_bb20_17;
  TNode<String> phi_bb20_20;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_13, &phi_bb20_14, &phi_bb20_15, &phi_bb20_16, &phi_bb20_17, &phi_bb20_20);
    ca_.Goto(&block14, phi_bb20_13, phi_bb20_14, phi_bb20_15, phi_bb20_16, phi_bb20_17, phi_bb20_20);
  }

  TNode<FixedArray> phi_bb14_13;
  TNode<IntPtrT> phi_bb14_14;
  TNode<IntPtrT> phi_bb14_15;
  TNode<BoolT> phi_bb14_16;
  TNode<PrimitiveHeapObject> phi_bb14_17;
  TNode<String> phi_bb14_20;
  if (block14.is_used()) {
    ca_.Bind(&block14, &phi_bb14_13, &phi_bb14_14, &phi_bb14_15, &phi_bb14_16, &phi_bb14_17, &phi_bb14_20);
    ca_.Goto(&block11, phi_bb14_13, phi_bb14_14, phi_bb14_15, phi_bb14_16, phi_bb14_17, phi_bb14_20);
  }

  TNode<FixedArray> phi_bb11_13;
  TNode<IntPtrT> phi_bb11_14;
  TNode<IntPtrT> phi_bb11_15;
  TNode<BoolT> phi_bb11_16;
  TNode<PrimitiveHeapObject> phi_bb11_17;
  TNode<String> phi_bb11_20;
  TNode<IntPtrT> tmp35;
  TNode<BoolT> tmp36;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_13, &phi_bb11_14, &phi_bb11_15, &phi_bb11_16, &phi_bb11_17, &phi_bb11_20);
    tmp35 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp36 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{phi_bb11_14}, TNode<IntPtrT>{tmp35});
    ca_.Branch(tmp36, &block31, std::vector<compiler::Node*>{phi_bb11_13, phi_bb11_14, phi_bb11_15, phi_bb11_16, phi_bb11_17, phi_bb11_20, phi_bb11_20, phi_bb11_20}, &block32, std::vector<compiler::Node*>{phi_bb11_13, phi_bb11_14, phi_bb11_15, phi_bb11_16, phi_bb11_17, phi_bb11_20, phi_bb11_20, phi_bb11_20});
  }

  TNode<FixedArray> phi_bb31_13;
  TNode<IntPtrT> phi_bb31_14;
  TNode<IntPtrT> phi_bb31_15;
  TNode<BoolT> phi_bb31_16;
  TNode<PrimitiveHeapObject> phi_bb31_17;
  TNode<String> phi_bb31_20;
  TNode<String> phi_bb31_21;
  TNode<String> phi_bb31_26;
  TNode<BoolT> tmp37;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_13, &phi_bb31_14, &phi_bb31_15, &phi_bb31_16, &phi_bb31_17, &phi_bb31_20, &phi_bb31_21, &phi_bb31_26);
    tmp37 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block33, phi_bb31_13, phi_bb31_14, phi_bb31_15, phi_bb31_16, phi_bb31_17, phi_bb31_20, phi_bb31_21, phi_bb31_26, tmp37);
  }

  TNode<FixedArray> phi_bb32_13;
  TNode<IntPtrT> phi_bb32_14;
  TNode<IntPtrT> phi_bb32_15;
  TNode<BoolT> phi_bb32_16;
  TNode<PrimitiveHeapObject> phi_bb32_17;
  TNode<String> phi_bb32_20;
  TNode<String> phi_bb32_21;
  TNode<String> phi_bb32_26;
  TNode<BoolT> tmp38;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_13, &phi_bb32_14, &phi_bb32_15, &phi_bb32_16, &phi_bb32_17, &phi_bb32_20, &phi_bb32_21, &phi_bb32_26);
    tmp38 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp5}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{phi_bb32_13});
    ca_.Goto(&block33, phi_bb32_13, phi_bb32_14, phi_bb32_15, phi_bb32_16, phi_bb32_17, phi_bb32_20, phi_bb32_21, phi_bb32_26, tmp38);
  }

  TNode<FixedArray> phi_bb33_13;
  TNode<IntPtrT> phi_bb33_14;
  TNode<IntPtrT> phi_bb33_15;
  TNode<BoolT> phi_bb33_16;
  TNode<PrimitiveHeapObject> phi_bb33_17;
  TNode<String> phi_bb33_20;
  TNode<String> phi_bb33_21;
  TNode<String> phi_bb33_26;
  TNode<BoolT> phi_bb33_30;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_13, &phi_bb33_14, &phi_bb33_15, &phi_bb33_16, &phi_bb33_17, &phi_bb33_20, &phi_bb33_21, &phi_bb33_26, &phi_bb33_30);
    ca_.Branch(phi_bb33_30, &block29, std::vector<compiler::Node*>{phi_bb33_13, phi_bb33_14, phi_bb33_15, phi_bb33_16, phi_bb33_17, phi_bb33_20, phi_bb33_21, phi_bb33_26}, &block30, std::vector<compiler::Node*>{phi_bb33_13, phi_bb33_14, phi_bb33_15, phi_bb33_16, phi_bb33_17, phi_bb33_20, phi_bb33_21, phi_bb33_26});
  }

  TNode<FixedArray> phi_bb30_13;
  TNode<IntPtrT> phi_bb30_14;
  TNode<IntPtrT> phi_bb30_15;
  TNode<BoolT> phi_bb30_16;
  TNode<PrimitiveHeapObject> phi_bb30_17;
  TNode<String> phi_bb30_20;
  TNode<String> phi_bb30_21;
  TNode<String> phi_bb30_26;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_13, &phi_bb30_14, &phi_bb30_15, &phi_bb30_16, &phi_bb30_17, &phi_bb30_20, &phi_bb30_21, &phi_bb30_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 184});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index != 1 || this.head == this.chunk' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb29_13;
  TNode<IntPtrT> phi_bb29_14;
  TNode<IntPtrT> phi_bb29_15;
  TNode<BoolT> phi_bb29_16;
  TNode<PrimitiveHeapObject> phi_bb29_17;
  TNode<String> phi_bb29_20;
  TNode<String> phi_bb29_21;
  TNode<String> phi_bb29_26;
  TNode<IntPtrT> tmp39;
  TNode<BoolT> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<BoolT> tmp42;
  TNode<BoolT> tmp43;
  TNode<IntPtrT> tmp44;
  TNode<BoolT> tmp45;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_13, &phi_bb29_14, &phi_bb29_15, &phi_bb29_16, &phi_bb29_17, &phi_bb29_20, &phi_bb29_21, &phi_bb29_26);
    tmp39 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp40 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb29_14}, TNode<IntPtrT>{tmp39});
    tmp41 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp42 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb8_10}, TNode<IntPtrT>{tmp41});
    tmp43 = CodeStubAssembler(state_).Word32Or(TNode<BoolT>{tmp40}, TNode<BoolT>{tmp42});
    tmp44 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp45 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb8_10}, TNode<IntPtrT>{tmp44});
    ca_.Branch(tmp45, &block37, std::vector<compiler::Node*>{phi_bb29_13, phi_bb29_14, phi_bb29_15, phi_bb29_16, phi_bb29_17, phi_bb29_20, phi_bb29_21, phi_bb29_26}, &block38, std::vector<compiler::Node*>{phi_bb29_13, phi_bb29_14, phi_bb29_15, phi_bb29_16, phi_bb29_17, phi_bb29_20, phi_bb29_21, phi_bb29_26});
  }

  TNode<FixedArray> phi_bb37_13;
  TNode<IntPtrT> phi_bb37_14;
  TNode<IntPtrT> phi_bb37_15;
  TNode<BoolT> phi_bb37_16;
  TNode<PrimitiveHeapObject> phi_bb37_17;
  TNode<String> phi_bb37_20;
  TNode<String> phi_bb37_21;
  TNode<String> phi_bb37_26;
  TNode<BoolT> tmp46;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_13, &phi_bb37_14, &phi_bb37_15, &phi_bb37_16, &phi_bb37_17, &phi_bb37_20, &phi_bb37_21, &phi_bb37_26);
    tmp46 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block39, phi_bb37_13, phi_bb37_14, phi_bb37_15, phi_bb37_16, phi_bb37_17, phi_bb37_20, phi_bb37_21, phi_bb37_26, tmp46);
  }

  TNode<FixedArray> phi_bb38_13;
  TNode<IntPtrT> phi_bb38_14;
  TNode<IntPtrT> phi_bb38_15;
  TNode<BoolT> phi_bb38_16;
  TNode<PrimitiveHeapObject> phi_bb38_17;
  TNode<String> phi_bb38_20;
  TNode<String> phi_bb38_21;
  TNode<String> phi_bb38_26;
  TNode<IntPtrT> tmp47;
  TNode<BoolT> tmp48;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_13, &phi_bb38_14, &phi_bb38_15, &phi_bb38_16, &phi_bb38_17, &phi_bb38_20, &phi_bb38_21, &phi_bb38_26);
    tmp47 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp48 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp47});
    ca_.Goto(&block39, phi_bb38_13, phi_bb38_14, phi_bb38_15, phi_bb38_16, phi_bb38_17, phi_bb38_20, phi_bb38_21, phi_bb38_26, tmp48);
  }

  TNode<FixedArray> phi_bb39_13;
  TNode<IntPtrT> phi_bb39_14;
  TNode<IntPtrT> phi_bb39_15;
  TNode<BoolT> phi_bb39_16;
  TNode<PrimitiveHeapObject> phi_bb39_17;
  TNode<String> phi_bb39_20;
  TNode<String> phi_bb39_21;
  TNode<String> phi_bb39_26;
  TNode<BoolT> phi_bb39_39;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_13, &phi_bb39_14, &phi_bb39_15, &phi_bb39_16, &phi_bb39_17, &phi_bb39_20, &phi_bb39_21, &phi_bb39_26, &phi_bb39_39);
    ca_.Branch(phi_bb39_39, &block35, std::vector<compiler::Node*>{phi_bb39_13, phi_bb39_14, phi_bb39_15, phi_bb39_16, phi_bb39_17, phi_bb39_20, phi_bb39_21, phi_bb39_26}, &block36, std::vector<compiler::Node*>{phi_bb39_13, phi_bb39_14, phi_bb39_15, phi_bb39_16, phi_bb39_17, phi_bb39_20, phi_bb39_21, phi_bb39_26});
  }

  TNode<FixedArray> phi_bb35_13;
  TNode<IntPtrT> phi_bb35_14;
  TNode<IntPtrT> phi_bb35_15;
  TNode<BoolT> phi_bb35_16;
  TNode<PrimitiveHeapObject> phi_bb35_17;
  TNode<String> phi_bb35_20;
  TNode<String> phi_bb35_21;
  TNode<String> phi_bb35_26;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_13, &phi_bb35_14, &phi_bb35_15, &phi_bb35_16, &phi_bb35_17, &phi_bb35_20, &phi_bb35_21, &phi_bb35_26);
    ca_.Goto(&block34, phi_bb35_13, phi_bb35_14, phi_bb35_15, phi_bb35_16, phi_bb35_17, phi_bb35_20, phi_bb35_21, phi_bb35_26);
  }

  TNode<FixedArray> phi_bb36_13;
  TNode<IntPtrT> phi_bb36_14;
  TNode<IntPtrT> phi_bb36_15;
  TNode<BoolT> phi_bb36_16;
  TNode<PrimitiveHeapObject> phi_bb36_17;
  TNode<String> phi_bb36_20;
  TNode<String> phi_bb36_21;
  TNode<String> phi_bb36_26;
  TNode<IntPtrT> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<BoolT> tmp51;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_13, &phi_bb36_14, &phi_bb36_15, &phi_bb36_16, &phi_bb36_17, &phi_bb36_20, &phi_bb36_21, &phi_bb36_26);
    tmp49 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{phi_bb8_10});
    tmp50 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp49}, TNode<IntPtrT>{tmp3});
    tmp51 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp50}, TNode<IntPtrT>{phi_bb8_10});
    ca_.Branch(tmp51, &block40, std::vector<compiler::Node*>{phi_bb36_13, phi_bb36_14, phi_bb36_15, phi_bb36_16, phi_bb36_17, phi_bb36_20, phi_bb36_21, phi_bb36_26}, &block41, std::vector<compiler::Node*>{phi_bb36_13, phi_bb36_14, phi_bb36_15, phi_bb36_16, phi_bb36_17, phi_bb36_20, phi_bb36_21, phi_bb36_26});
  }

  TNode<FixedArray> phi_bb40_13;
  TNode<IntPtrT> phi_bb40_14;
  TNode<IntPtrT> phi_bb40_15;
  TNode<BoolT> phi_bb40_16;
  TNode<PrimitiveHeapObject> phi_bb40_17;
  TNode<String> phi_bb40_20;
  TNode<String> phi_bb40_21;
  TNode<String> phi_bb40_26;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_13, &phi_bb40_14, &phi_bb40_15, &phi_bb40_16, &phi_bb40_17, &phi_bb40_20, &phi_bb40_21, &phi_bb40_26);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb41_13;
  TNode<IntPtrT> phi_bb41_14;
  TNode<IntPtrT> phi_bb41_15;
  TNode<BoolT> phi_bb41_16;
  TNode<PrimitiveHeapObject> phi_bb41_17;
  TNode<String> phi_bb41_20;
  TNode<String> phi_bb41_21;
  TNode<String> phi_bb41_26;
  TNode<IntPtrT> tmp52;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_13, &phi_bb41_14, &phi_bb41_15, &phi_bb41_16, &phi_bb41_17, &phi_bb41_20, &phi_bb41_21, &phi_bb41_26);
    tmp52 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb41_15}, TNode<IntPtrT>{tmp49});
    ca_.Branch(tmp43, &block42, std::vector<compiler::Node*>{phi_bb41_13, phi_bb41_14, phi_bb41_16, phi_bb41_17, phi_bb41_20, phi_bb41_21, phi_bb41_26}, &block43, std::vector<compiler::Node*>{phi_bb41_13, phi_bb41_14, phi_bb41_16, phi_bb41_17, phi_bb41_20, phi_bb41_21, phi_bb41_26});
  }

  TNode<FixedArray> phi_bb42_13;
  TNode<IntPtrT> phi_bb42_14;
  TNode<BoolT> phi_bb42_16;
  TNode<PrimitiveHeapObject> phi_bb42_17;
  TNode<String> phi_bb42_20;
  TNode<String> phi_bb42_21;
  TNode<String> phi_bb42_26;
  TNode<Smi> tmp53;
  TNode<IntPtrT> tmp54;
  TNode<IntPtrT> tmp55;
  TNode<BoolT> tmp56;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_13, &phi_bb42_14, &phi_bb42_16, &phi_bb42_17, &phi_bb42_20, &phi_bb42_21, &phi_bb42_26);
    tmp53 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb8_10});
    tmp54 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb42_13});
    tmp55 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp56 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb42_14}, TNode<IntPtrT>{tmp55});
    ca_.Branch(tmp56, &block45, std::vector<compiler::Node*>{phi_bb42_13, phi_bb42_14, phi_bb42_16, phi_bb42_17, phi_bb42_20, phi_bb42_21, phi_bb42_26}, &block46, std::vector<compiler::Node*>{phi_bb42_13, phi_bb42_14, phi_bb42_16, phi_bb42_17, phi_bb42_20, phi_bb42_21, phi_bb42_26});
  }

  TNode<FixedArray> phi_bb46_13;
  TNode<IntPtrT> phi_bb46_14;
  TNode<BoolT> phi_bb46_16;
  TNode<PrimitiveHeapObject> phi_bb46_17;
  TNode<String> phi_bb46_20;
  TNode<String> phi_bb46_21;
  TNode<String> phi_bb46_26;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_13, &phi_bb46_14, &phi_bb46_16, &phi_bb46_17, &phi_bb46_20, &phi_bb46_21, &phi_bb46_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb45_13;
  TNode<IntPtrT> phi_bb45_14;
  TNode<BoolT> phi_bb45_16;
  TNode<PrimitiveHeapObject> phi_bb45_17;
  TNode<String> phi_bb45_20;
  TNode<String> phi_bb45_21;
  TNode<String> phi_bb45_26;
  TNode<BoolT> tmp57;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_13, &phi_bb45_14, &phi_bb45_16, &phi_bb45_17, &phi_bb45_20, &phi_bb45_21, &phi_bb45_26);
    tmp57 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb45_14}, TNode<IntPtrT>{tmp54});
    ca_.Branch(tmp57, &block47, std::vector<compiler::Node*>{phi_bb45_13, phi_bb45_14, phi_bb45_16, phi_bb45_17, phi_bb45_20, phi_bb45_21, phi_bb45_26}, &block48, std::vector<compiler::Node*>{phi_bb45_13, phi_bb45_14, phi_bb45_16, phi_bb45_17, phi_bb45_20, phi_bb45_21, phi_bb45_26});
  }

  TNode<FixedArray> phi_bb48_13;
  TNode<IntPtrT> phi_bb48_14;
  TNode<BoolT> phi_bb48_16;
  TNode<PrimitiveHeapObject> phi_bb48_17;
  TNode<String> phi_bb48_20;
  TNode<String> phi_bb48_21;
  TNode<String> phi_bb48_26;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_13, &phi_bb48_14, &phi_bb48_16, &phi_bb48_17, &phi_bb48_20, &phi_bb48_21, &phi_bb48_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb47_13;
  TNode<IntPtrT> phi_bb47_14;
  TNode<BoolT> phi_bb47_16;
  TNode<PrimitiveHeapObject> phi_bb47_17;
  TNode<String> phi_bb47_20;
  TNode<String> phi_bb47_21;
  TNode<String> phi_bb47_26;
  TNode<BoolT> tmp58;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_13, &phi_bb47_14, &phi_bb47_16, &phi_bb47_17, &phi_bb47_20, &phi_bb47_21, &phi_bb47_26);
    tmp58 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb47_14}, TNode<IntPtrT>{tmp54});
    ca_.Branch(tmp58, &block49, std::vector<compiler::Node*>{phi_bb47_13, phi_bb47_14, phi_bb47_16, phi_bb47_17, phi_bb47_20, phi_bb47_21, phi_bb47_26}, &block50, std::vector<compiler::Node*>{phi_bb47_13, phi_bb47_14, phi_bb47_16, phi_bb47_17, phi_bb47_20, phi_bb47_21, phi_bb47_26});
  }

  TNode<FixedArray> phi_bb49_13;
  TNode<IntPtrT> phi_bb49_14;
  TNode<BoolT> phi_bb49_16;
  TNode<PrimitiveHeapObject> phi_bb49_17;
  TNode<String> phi_bb49_20;
  TNode<String> phi_bb49_21;
  TNode<String> phi_bb49_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<IntPtrT> tmp62;
  TNode<IntPtrT> tmp63;
  TNode<UintPtrT> tmp64;
  TNode<UintPtrT> tmp65;
  TNode<BoolT> tmp66;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_13, &phi_bb49_14, &phi_bb49_16, &phi_bb49_17, &phi_bb49_20, &phi_bb49_21, &phi_bb49_26);
    std::tie(tmp59, tmp60, tmp61) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb49_13}).Flatten();
    tmp62 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp63 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb49_14}, TNode<IntPtrT>{tmp62});
    tmp64 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb49_14});
    tmp65 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp61});
    tmp66 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp64}, TNode<UintPtrT>{tmp65});
    ca_.Branch(tmp66, &block56, std::vector<compiler::Node*>{phi_bb49_13, phi_bb49_16, phi_bb49_17, phi_bb49_20, phi_bb49_21, phi_bb49_26, phi_bb49_13, phi_bb49_14, phi_bb49_14, phi_bb49_14, phi_bb49_14}, &block57, std::vector<compiler::Node*>{phi_bb49_13, phi_bb49_16, phi_bb49_17, phi_bb49_20, phi_bb49_21, phi_bb49_26, phi_bb49_13, phi_bb49_14, phi_bb49_14, phi_bb49_14, phi_bb49_14});
  }

  TNode<FixedArray> phi_bb56_13;
  TNode<BoolT> phi_bb56_16;
  TNode<PrimitiveHeapObject> phi_bb56_17;
  TNode<String> phi_bb56_20;
  TNode<String> phi_bb56_21;
  TNode<String> phi_bb56_26;
  TNode<FixedArray> phi_bb56_43;
  TNode<IntPtrT> phi_bb56_47;
  TNode<IntPtrT> phi_bb56_48;
  TNode<IntPtrT> phi_bb56_52;
  TNode<IntPtrT> phi_bb56_53;
  TNode<IntPtrT> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<Union<HeapObject, TaggedIndex>> tmp69;
  TNode<IntPtrT> tmp70;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_13, &phi_bb56_16, &phi_bb56_17, &phi_bb56_20, &phi_bb56_21, &phi_bb56_26, &phi_bb56_43, &phi_bb56_47, &phi_bb56_48, &phi_bb56_52, &phi_bb56_53);
    tmp67 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb56_53});
    tmp68 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp67});
    std::tie(tmp69, tmp70) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp68}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp69, tmp70}, tmp53);
    ca_.Goto(&block51, phi_bb56_13, tmp63, phi_bb56_16, phi_bb56_17, phi_bb56_20, phi_bb56_21, phi_bb56_26);
  }

  TNode<FixedArray> phi_bb57_13;
  TNode<BoolT> phi_bb57_16;
  TNode<PrimitiveHeapObject> phi_bb57_17;
  TNode<String> phi_bb57_20;
  TNode<String> phi_bb57_21;
  TNode<String> phi_bb57_26;
  TNode<FixedArray> phi_bb57_43;
  TNode<IntPtrT> phi_bb57_47;
  TNode<IntPtrT> phi_bb57_48;
  TNode<IntPtrT> phi_bb57_52;
  TNode<IntPtrT> phi_bb57_53;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_13, &phi_bb57_16, &phi_bb57_17, &phi_bb57_20, &phi_bb57_21, &phi_bb57_26, &phi_bb57_43, &phi_bb57_47, &phi_bb57_48, &phi_bb57_52, &phi_bb57_53);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb50_13;
  TNode<IntPtrT> phi_bb50_14;
  TNode<BoolT> phi_bb50_16;
  TNode<PrimitiveHeapObject> phi_bb50_17;
  TNode<String> phi_bb50_20;
  TNode<String> phi_bb50_21;
  TNode<String> phi_bb50_26;
  TNode<IntPtrT> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<BoolT> tmp73;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_13, &phi_bb50_14, &phi_bb50_16, &phi_bb50_17, &phi_bb50_20, &phi_bb50_21, &phi_bb50_26);
    tmp71 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp54});
    tmp72 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp73 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp71}, TNode<IntPtrT>{tmp72});
    ca_.Branch(tmp73, &block60, std::vector<compiler::Node*>{phi_bb50_13, phi_bb50_14, phi_bb50_16, phi_bb50_17, phi_bb50_20, phi_bb50_21, phi_bb50_26}, &block61, std::vector<compiler::Node*>{phi_bb50_13, phi_bb50_14, phi_bb50_16, phi_bb50_17, phi_bb50_20, phi_bb50_21, phi_bb50_26});
  }

  TNode<FixedArray> phi_bb60_13;
  TNode<IntPtrT> phi_bb60_14;
  TNode<BoolT> phi_bb60_16;
  TNode<PrimitiveHeapObject> phi_bb60_17;
  TNode<String> phi_bb60_20;
  TNode<String> phi_bb60_21;
  TNode<String> phi_bb60_26;
  TNode<IntPtrT> tmp74;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_13, &phi_bb60_14, &phi_bb60_16, &phi_bb60_17, &phi_bb60_20, &phi_bb60_21, &phi_bb60_26);
    tmp74 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block62, phi_bb60_13, phi_bb60_14, phi_bb60_16, phi_bb60_17, phi_bb60_20, phi_bb60_21, phi_bb60_26, tmp74);
  }

  TNode<FixedArray> phi_bb61_13;
  TNode<IntPtrT> phi_bb61_14;
  TNode<BoolT> phi_bb61_16;
  TNode<PrimitiveHeapObject> phi_bb61_17;
  TNode<String> phi_bb61_20;
  TNode<String> phi_bb61_21;
  TNode<String> phi_bb61_26;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_13, &phi_bb61_14, &phi_bb61_16, &phi_bb61_17, &phi_bb61_20, &phi_bb61_21, &phi_bb61_26);
    ca_.Goto(&block62, phi_bb61_13, phi_bb61_14, phi_bb61_16, phi_bb61_17, phi_bb61_20, phi_bb61_21, phi_bb61_26, tmp71);
  }

  TNode<FixedArray> phi_bb62_13;
  TNode<IntPtrT> phi_bb62_14;
  TNode<BoolT> phi_bb62_16;
  TNode<PrimitiveHeapObject> phi_bb62_17;
  TNode<String> phi_bb62_20;
  TNode<String> phi_bb62_21;
  TNode<String> phi_bb62_26;
  TNode<IntPtrT> phi_bb62_44;
  TNode<IntPtrT> tmp75;
  TNode<BoolT> tmp76;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_13, &phi_bb62_14, &phi_bb62_16, &phi_bb62_17, &phi_bb62_20, &phi_bb62_21, &phi_bb62_26, &phi_bb62_44);
    tmp75 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp76 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb62_44}, TNode<IntPtrT>{tmp75});
    ca_.Branch(tmp76, &block64, std::vector<compiler::Node*>{phi_bb62_13, phi_bb62_14, phi_bb62_16, phi_bb62_17, phi_bb62_20, phi_bb62_21, phi_bb62_26}, &block65, std::vector<compiler::Node*>{phi_bb62_13, phi_bb62_14, phi_bb62_16, phi_bb62_17, phi_bb62_20, phi_bb62_21, phi_bb62_26});
  }

  TNode<FixedArray> phi_bb65_13;
  TNode<IntPtrT> phi_bb65_14;
  TNode<BoolT> phi_bb65_16;
  TNode<PrimitiveHeapObject> phi_bb65_17;
  TNode<String> phi_bb65_20;
  TNode<String> phi_bb65_21;
  TNode<String> phi_bb65_26;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_13, &phi_bb65_14, &phi_bb65_16, &phi_bb65_17, &phi_bb65_20, &phi_bb65_21, &phi_bb65_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb64_13;
  TNode<IntPtrT> phi_bb64_14;
  TNode<BoolT> phi_bb64_16;
  TNode<PrimitiveHeapObject> phi_bb64_17;
  TNode<String> phi_bb64_20;
  TNode<String> phi_bb64_21;
  TNode<String> phi_bb64_26;
  TNode<FixedArray> tmp77;
  TNode<Union<HeapObject, TaggedIndex>> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<UintPtrT> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<UintPtrT> tmp83;
  TNode<UintPtrT> tmp84;
  TNode<BoolT> tmp85;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_13, &phi_bb64_14, &phi_bb64_16, &phi_bb64_17, &phi_bb64_20, &phi_bb64_21, &phi_bb64_26);
    tmp77 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb62_44});
    std::tie(tmp78, tmp79, tmp80) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb64_13}).Flatten();
    tmp81 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp82 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp81});
    tmp83 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp82});
    tmp84 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp80});
    tmp85 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp83}, TNode<UintPtrT>{tmp84});
    ca_.Branch(tmp85, &block71, std::vector<compiler::Node*>{phi_bb64_13, phi_bb64_14, phi_bb64_16, phi_bb64_17, phi_bb64_20, phi_bb64_21, phi_bb64_26, phi_bb64_13}, &block72, std::vector<compiler::Node*>{phi_bb64_13, phi_bb64_14, phi_bb64_16, phi_bb64_17, phi_bb64_20, phi_bb64_21, phi_bb64_26, phi_bb64_13});
  }

  TNode<FixedArray> phi_bb71_13;
  TNode<IntPtrT> phi_bb71_14;
  TNode<BoolT> phi_bb71_16;
  TNode<PrimitiveHeapObject> phi_bb71_17;
  TNode<String> phi_bb71_20;
  TNode<String> phi_bb71_21;
  TNode<String> phi_bb71_26;
  TNode<FixedArray> phi_bb71_46;
  TNode<IntPtrT> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<Union<HeapObject, TaggedIndex>> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Union<HeapObject, TaggedIndex>> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<IntPtrT> tmp92;
  TNode<UintPtrT> tmp93;
  TNode<IntPtrT> tmp94;
  TNode<UintPtrT> tmp95;
  TNode<UintPtrT> tmp96;
  TNode<BoolT> tmp97;
  if (block71.is_used()) {
    ca_.Bind(&block71, &phi_bb71_13, &phi_bb71_14, &phi_bb71_16, &phi_bb71_17, &phi_bb71_20, &phi_bb71_21, &phi_bb71_26, &phi_bb71_46);
    tmp86 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp82});
    tmp87 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp79}, TNode<IntPtrT>{tmp86});
    std::tie(tmp88, tmp89) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp78}, TNode<IntPtrT>{tmp87}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp88, tmp89}, tmp77);
    std::tie(tmp90, tmp91, tmp92) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp77}).Flatten();
    tmp93 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp94 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp93});
    tmp95 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp94});
    tmp96 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp92});
    tmp97 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp95}, TNode<UintPtrT>{tmp96});
    ca_.Branch(tmp97, &block80, std::vector<compiler::Node*>{phi_bb71_13, phi_bb71_14, phi_bb71_16, phi_bb71_17, phi_bb71_20, phi_bb71_21, phi_bb71_26}, &block81, std::vector<compiler::Node*>{phi_bb71_13, phi_bb71_14, phi_bb71_16, phi_bb71_17, phi_bb71_20, phi_bb71_21, phi_bb71_26});
  }

  TNode<FixedArray> phi_bb72_13;
  TNode<IntPtrT> phi_bb72_14;
  TNode<BoolT> phi_bb72_16;
  TNode<PrimitiveHeapObject> phi_bb72_17;
  TNode<String> phi_bb72_20;
  TNode<String> phi_bb72_21;
  TNode<String> phi_bb72_26;
  TNode<FixedArray> phi_bb72_46;
  if (block72.is_used()) {
    ca_.Bind(&block72, &phi_bb72_13, &phi_bb72_14, &phi_bb72_16, &phi_bb72_17, &phi_bb72_20, &phi_bb72_21, &phi_bb72_26, &phi_bb72_46);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb80_13;
  TNode<IntPtrT> phi_bb80_14;
  TNode<BoolT> phi_bb80_16;
  TNode<PrimitiveHeapObject> phi_bb80_17;
  TNode<String> phi_bb80_20;
  TNode<String> phi_bb80_21;
  TNode<String> phi_bb80_26;
  TNode<IntPtrT> tmp98;
  TNode<IntPtrT> tmp99;
  TNode<Union<HeapObject, TaggedIndex>> tmp100;
  TNode<IntPtrT> tmp101;
  TNode<Undefined> tmp102;
  TNode<Union<HeapObject, TaggedIndex>> tmp103;
  TNode<IntPtrT> tmp104;
  TNode<IntPtrT> tmp105;
  TNode<UintPtrT> tmp106;
  TNode<IntPtrT> tmp107;
  TNode<UintPtrT> tmp108;
  TNode<UintPtrT> tmp109;
  TNode<BoolT> tmp110;
  if (block80.is_used()) {
    ca_.Bind(&block80, &phi_bb80_13, &phi_bb80_14, &phi_bb80_16, &phi_bb80_17, &phi_bb80_20, &phi_bb80_21, &phi_bb80_26);
    tmp98 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp94});
    tmp99 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp91}, TNode<IntPtrT>{tmp98});
    std::tie(tmp100, tmp101) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp90}, TNode<IntPtrT>{tmp99}).Flatten();
    tmp102 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp100, tmp101}, tmp102);
    std::tie(tmp103, tmp104, tmp105) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp77}).Flatten();
    tmp106 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp107 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp106});
    tmp108 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp107});
    tmp109 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp105});
    tmp110 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp108}, TNode<UintPtrT>{tmp109});
    ca_.Branch(tmp110, &block89, std::vector<compiler::Node*>{phi_bb80_13, phi_bb80_14, phi_bb80_16, phi_bb80_17, phi_bb80_20, phi_bb80_21, phi_bb80_26}, &block90, std::vector<compiler::Node*>{phi_bb80_13, phi_bb80_14, phi_bb80_16, phi_bb80_17, phi_bb80_20, phi_bb80_21, phi_bb80_26});
  }

  TNode<FixedArray> phi_bb81_13;
  TNode<IntPtrT> phi_bb81_14;
  TNode<BoolT> phi_bb81_16;
  TNode<PrimitiveHeapObject> phi_bb81_17;
  TNode<String> phi_bb81_20;
  TNode<String> phi_bb81_21;
  TNode<String> phi_bb81_26;
  if (block81.is_used()) {
    ca_.Bind(&block81, &phi_bb81_13, &phi_bb81_14, &phi_bb81_16, &phi_bb81_17, &phi_bb81_20, &phi_bb81_21, &phi_bb81_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb89_13;
  TNode<IntPtrT> phi_bb89_14;
  TNode<BoolT> phi_bb89_16;
  TNode<PrimitiveHeapObject> phi_bb89_17;
  TNode<String> phi_bb89_20;
  TNode<String> phi_bb89_21;
  TNode<String> phi_bb89_26;
  TNode<IntPtrT> tmp111;
  TNode<IntPtrT> tmp112;
  TNode<Union<HeapObject, TaggedIndex>> tmp113;
  TNode<IntPtrT> tmp114;
  TNode<IntPtrT> tmp115;
  if (block89.is_used()) {
    ca_.Bind(&block89, &phi_bb89_13, &phi_bb89_14, &phi_bb89_16, &phi_bb89_17, &phi_bb89_20, &phi_bb89_21, &phi_bb89_26);
    tmp111 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp107});
    tmp112 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp104}, TNode<IntPtrT>{tmp111});
    std::tie(tmp113, tmp114) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp103}, TNode<IntPtrT>{tmp112}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp113, tmp114}, tmp53);
    tmp115 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block51, tmp77, tmp115, phi_bb89_16, phi_bb89_17, phi_bb89_20, phi_bb89_21, phi_bb89_26);
  }

  TNode<FixedArray> phi_bb90_13;
  TNode<IntPtrT> phi_bb90_14;
  TNode<BoolT> phi_bb90_16;
  TNode<PrimitiveHeapObject> phi_bb90_17;
  TNode<String> phi_bb90_20;
  TNode<String> phi_bb90_21;
  TNode<String> phi_bb90_26;
  if (block90.is_used()) {
    ca_.Bind(&block90, &phi_bb90_13, &phi_bb90_14, &phi_bb90_16, &phi_bb90_17, &phi_bb90_20, &phi_bb90_21, &phi_bb90_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb51_13;
  TNode<IntPtrT> phi_bb51_14;
  TNode<BoolT> phi_bb51_16;
  TNode<PrimitiveHeapObject> phi_bb51_17;
  TNode<String> phi_bb51_20;
  TNode<String> phi_bb51_21;
  TNode<String> phi_bb51_26;
  TNode<Null> tmp116;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_13, &phi_bb51_14, &phi_bb51_16, &phi_bb51_17, &phi_bb51_20, &phi_bb51_21, &phi_bb51_26);
    tmp116 = Null_0(state_);
    ca_.Goto(&block43, phi_bb51_13, phi_bb51_14, phi_bb51_16, tmp116, phi_bb51_20, phi_bb51_21, phi_bb51_26);
  }

  TNode<FixedArray> phi_bb43_13;
  TNode<IntPtrT> phi_bb43_14;
  TNode<BoolT> phi_bb43_16;
  TNode<PrimitiveHeapObject> phi_bb43_17;
  TNode<String> phi_bb43_20;
  TNode<String> phi_bb43_21;
  TNode<String> phi_bb43_26;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_13, &phi_bb43_14, &phi_bb43_16, &phi_bb43_17, &phi_bb43_20, &phi_bb43_21, &phi_bb43_26);
    ca_.Goto(&block34, phi_bb43_13, phi_bb43_14, tmp52, phi_bb43_16, phi_bb43_17, phi_bb43_20, phi_bb43_21, phi_bb43_26);
  }

  TNode<FixedArray> phi_bb34_13;
  TNode<IntPtrT> phi_bb34_14;
  TNode<IntPtrT> phi_bb34_15;
  TNode<BoolT> phi_bb34_16;
  TNode<PrimitiveHeapObject> phi_bb34_17;
  TNode<String> phi_bb34_20;
  TNode<String> phi_bb34_21;
  TNode<String> phi_bb34_26;
  TNode<IntPtrT> tmp117;
  TNode<IntPtrT> tmp118;
  TNode<BoolT> tmp119;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_13, &phi_bb34_14, &phi_bb34_15, &phi_bb34_16, &phi_bb34_17, &phi_bb34_20, &phi_bb34_21, &phi_bb34_26);
    tmp117 = CodeStubAssembler(state_).LoadStringLengthAsWord(TNode<String>{phi_bb34_26});
    tmp118 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb34_15}, TNode<IntPtrT>{tmp117});
    tmp119 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{phi_bb34_26}, TNode<Union<HeapObject, Smi, Weak<HeapObject>>>{phi_bb34_17});
    ca_.Branch(tmp119, &block93, std::vector<compiler::Node*>{phi_bb34_13, phi_bb34_14, phi_bb34_16, phi_bb34_17, phi_bb34_20, phi_bb34_21, phi_bb34_26}, &block94, std::vector<compiler::Node*>{phi_bb34_13, phi_bb34_14, phi_bb34_16, phi_bb34_17, phi_bb34_20, phi_bb34_21, phi_bb34_26});
  }

  TNode<FixedArray> phi_bb93_13;
  TNode<IntPtrT> phi_bb93_14;
  TNode<BoolT> phi_bb93_16;
  TNode<PrimitiveHeapObject> phi_bb93_17;
  TNode<String> phi_bb93_20;
  TNode<String> phi_bb93_21;
  TNode<String> phi_bb93_26;
  TNode<IntPtrT> tmp120;
  TNode<BoolT> tmp121;
  if (block93.is_used()) {
    ca_.Bind(&block93, &phi_bb93_13, &phi_bb93_14, &phi_bb93_16, &phi_bb93_17, &phi_bb93_20, &phi_bb93_21, &phi_bb93_26);
    tmp120 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp121 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb93_14}, TNode<IntPtrT>{tmp120});
    ca_.Branch(tmp121, &block97, std::vector<compiler::Node*>{phi_bb93_13, phi_bb93_14, phi_bb93_16, phi_bb93_17, phi_bb93_20, phi_bb93_21, phi_bb93_26}, &block98, std::vector<compiler::Node*>{phi_bb93_13, phi_bb93_14, phi_bb93_16, phi_bb93_17, phi_bb93_20, phi_bb93_21, phi_bb93_26});
  }

  TNode<FixedArray> phi_bb98_13;
  TNode<IntPtrT> phi_bb98_14;
  TNode<BoolT> phi_bb98_16;
  TNode<PrimitiveHeapObject> phi_bb98_17;
  TNode<String> phi_bb98_20;
  TNode<String> phi_bb98_21;
  TNode<String> phi_bb98_26;
  if (block98.is_used()) {
    ca_.Bind(&block98, &phi_bb98_13, &phi_bb98_14, &phi_bb98_16, &phi_bb98_17, &phi_bb98_20, &phi_bb98_21, &phi_bb98_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 223});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index > 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb97_13;
  TNode<IntPtrT> phi_bb97_14;
  TNode<BoolT> phi_bb97_16;
  TNode<PrimitiveHeapObject> phi_bb97_17;
  TNode<String> phi_bb97_20;
  TNode<String> phi_bb97_21;
  TNode<String> phi_bb97_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp122;
  TNode<IntPtrT> tmp123;
  TNode<IntPtrT> tmp124;
  TNode<IntPtrT> tmp125;
  TNode<IntPtrT> tmp126;
  TNode<UintPtrT> tmp127;
  TNode<UintPtrT> tmp128;
  TNode<BoolT> tmp129;
  if (block97.is_used()) {
    ca_.Bind(&block97, &phi_bb97_13, &phi_bb97_14, &phi_bb97_16, &phi_bb97_17, &phi_bb97_20, &phi_bb97_21, &phi_bb97_26);
    std::tie(tmp122, tmp123, tmp124) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb97_13}).Flatten();
    tmp125 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp126 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb97_14}, TNode<IntPtrT>{tmp125});
    tmp127 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp126});
    tmp128 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp124});
    tmp129 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp127}, TNode<UintPtrT>{tmp128});
    ca_.Branch(tmp129, &block103, std::vector<compiler::Node*>{phi_bb97_13, phi_bb97_14, phi_bb97_16, phi_bb97_17, phi_bb97_20, phi_bb97_21, phi_bb97_26, phi_bb97_13}, &block104, std::vector<compiler::Node*>{phi_bb97_13, phi_bb97_14, phi_bb97_16, phi_bb97_17, phi_bb97_20, phi_bb97_21, phi_bb97_26, phi_bb97_13});
  }

  TNode<FixedArray> phi_bb103_13;
  TNode<IntPtrT> phi_bb103_14;
  TNode<BoolT> phi_bb103_16;
  TNode<PrimitiveHeapObject> phi_bb103_17;
  TNode<String> phi_bb103_20;
  TNode<String> phi_bb103_21;
  TNode<String> phi_bb103_26;
  TNode<FixedArray> phi_bb103_30;
  TNode<IntPtrT> tmp130;
  TNode<IntPtrT> tmp131;
  TNode<Union<HeapObject, TaggedIndex>> tmp132;
  TNode<IntPtrT> tmp133;
  TNode<Object> tmp134;
  TNode<HeapObject> tmp135;
  if (block103.is_used()) {
    ca_.Bind(&block103, &phi_bb103_13, &phi_bb103_14, &phi_bb103_16, &phi_bb103_17, &phi_bb103_20, &phi_bb103_21, &phi_bb103_26, &phi_bb103_30);
    tmp130 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp126});
    tmp131 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp123}, TNode<IntPtrT>{tmp130});
    std::tie(tmp132, tmp133) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp122}, TNode<IntPtrT>{tmp131}).Flatten();
    tmp134 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp132, tmp133});
    compiler::CodeAssemblerLabel label136(&ca_);
    tmp135 = CodeStubAssembler(state_).TaggedToHeapObject(TNode<Object>{tmp134}, &label136);
    ca_.Goto(&block110, phi_bb103_13, phi_bb103_14, phi_bb103_16, phi_bb103_17, phi_bb103_20, phi_bb103_21, phi_bb103_26);
    if (label136.is_used()) {
      ca_.Bind(&label136);
      ca_.Goto(&block111, phi_bb103_13, phi_bb103_14, phi_bb103_16, phi_bb103_17, phi_bb103_20, phi_bb103_21, phi_bb103_26);
    }
  }

  TNode<FixedArray> phi_bb104_13;
  TNode<IntPtrT> phi_bb104_14;
  TNode<BoolT> phi_bb104_16;
  TNode<PrimitiveHeapObject> phi_bb104_17;
  TNode<String> phi_bb104_20;
  TNode<String> phi_bb104_21;
  TNode<String> phi_bb104_26;
  TNode<FixedArray> phi_bb104_30;
  if (block104.is_used()) {
    ca_.Bind(&block104, &phi_bb104_13, &phi_bb104_14, &phi_bb104_16, &phi_bb104_17, &phi_bb104_20, &phi_bb104_21, &phi_bb104_26, &phi_bb104_30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb111_13;
  TNode<IntPtrT> phi_bb111_14;
  TNode<BoolT> phi_bb111_16;
  TNode<PrimitiveHeapObject> phi_bb111_17;
  TNode<String> phi_bb111_20;
  TNode<String> phi_bb111_21;
  TNode<String> phi_bb111_26;
  if (block111.is_used()) {
    ca_.Bind(&block111, &phi_bb111_13, &phi_bb111_14, &phi_bb111_16, &phi_bb111_17, &phi_bb111_20, &phi_bb111_21, &phi_bb111_26);
    ca_.Goto(&block108, phi_bb111_13, phi_bb111_14, phi_bb111_16, phi_bb111_17, phi_bb111_20, phi_bb111_21, phi_bb111_26);
  }

  TNode<FixedArray> phi_bb110_13;
  TNode<IntPtrT> phi_bb110_14;
  TNode<BoolT> phi_bb110_16;
  TNode<PrimitiveHeapObject> phi_bb110_17;
  TNode<String> phi_bb110_20;
  TNode<String> phi_bb110_21;
  TNode<String> phi_bb110_26;
  TNode<String> tmp137;
  if (block110.is_used()) {
    ca_.Bind(&block110, &phi_bb110_13, &phi_bb110_14, &phi_bb110_16, &phi_bb110_17, &phi_bb110_20, &phi_bb110_21, &phi_bb110_26);
    compiler::CodeAssemblerLabel label138(&ca_);
    tmp137 = Cast_String_0(state_, TNode<HeapObject>{tmp135}, &label138);
    ca_.Goto(&block112, phi_bb110_13, phi_bb110_14, phi_bb110_16, phi_bb110_17, phi_bb110_20, phi_bb110_21, phi_bb110_26);
    if (label138.is_used()) {
      ca_.Bind(&label138);
      ca_.Goto(&block113, phi_bb110_13, phi_bb110_14, phi_bb110_16, phi_bb110_17, phi_bb110_20, phi_bb110_21, phi_bb110_26);
    }
  }

  TNode<FixedArray> phi_bb113_13;
  TNode<IntPtrT> phi_bb113_14;
  TNode<BoolT> phi_bb113_16;
  TNode<PrimitiveHeapObject> phi_bb113_17;
  TNode<String> phi_bb113_20;
  TNode<String> phi_bb113_21;
  TNode<String> phi_bb113_26;
  if (block113.is_used()) {
    ca_.Bind(&block113, &phi_bb113_13, &phi_bb113_14, &phi_bb113_16, &phi_bb113_17, &phi_bb113_20, &phi_bb113_21, &phi_bb113_26);
    ca_.Goto(&block108, phi_bb113_13, phi_bb113_14, phi_bb113_16, phi_bb113_17, phi_bb113_20, phi_bb113_21, phi_bb113_26);
  }

  TNode<FixedArray> phi_bb112_13;
  TNode<IntPtrT> phi_bb112_14;
  TNode<BoolT> phi_bb112_16;
  TNode<PrimitiveHeapObject> phi_bb112_17;
  TNode<String> phi_bb112_20;
  TNode<String> phi_bb112_21;
  TNode<String> phi_bb112_26;
  TNode<Smi> tmp139;
  TNode<IntPtrT> tmp140;
  TNode<IntPtrT> tmp141;
  TNode<BoolT> tmp142;
  if (block112.is_used()) {
    ca_.Bind(&block112, &phi_bb112_13, &phi_bb112_14, &phi_bb112_16, &phi_bb112_17, &phi_bb112_20, &phi_bb112_21, &phi_bb112_26);
    tmp139 = SmiConstant_0(state_, IntegerLiteral(true, 0x1ull));
    tmp140 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb112_13});
    tmp141 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp142 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb112_14}, TNode<IntPtrT>{tmp141});
    ca_.Branch(tmp142, &block115, std::vector<compiler::Node*>{phi_bb112_13, phi_bb112_14, phi_bb112_16, phi_bb112_17, phi_bb112_20, phi_bb112_21, phi_bb112_26}, &block116, std::vector<compiler::Node*>{phi_bb112_13, phi_bb112_14, phi_bb112_16, phi_bb112_17, phi_bb112_20, phi_bb112_21, phi_bb112_26});
  }

  TNode<FixedArray> phi_bb116_13;
  TNode<IntPtrT> phi_bb116_14;
  TNode<BoolT> phi_bb116_16;
  TNode<PrimitiveHeapObject> phi_bb116_17;
  TNode<String> phi_bb116_20;
  TNode<String> phi_bb116_21;
  TNode<String> phi_bb116_26;
  if (block116.is_used()) {
    ca_.Bind(&block116, &phi_bb116_13, &phi_bb116_14, &phi_bb116_16, &phi_bb116_17, &phi_bb116_20, &phi_bb116_21, &phi_bb116_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb115_13;
  TNode<IntPtrT> phi_bb115_14;
  TNode<BoolT> phi_bb115_16;
  TNode<PrimitiveHeapObject> phi_bb115_17;
  TNode<String> phi_bb115_20;
  TNode<String> phi_bb115_21;
  TNode<String> phi_bb115_26;
  TNode<BoolT> tmp143;
  if (block115.is_used()) {
    ca_.Bind(&block115, &phi_bb115_13, &phi_bb115_14, &phi_bb115_16, &phi_bb115_17, &phi_bb115_20, &phi_bb115_21, &phi_bb115_26);
    tmp143 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb115_14}, TNode<IntPtrT>{tmp140});
    ca_.Branch(tmp143, &block117, std::vector<compiler::Node*>{phi_bb115_13, phi_bb115_14, phi_bb115_16, phi_bb115_17, phi_bb115_20, phi_bb115_21, phi_bb115_26}, &block118, std::vector<compiler::Node*>{phi_bb115_13, phi_bb115_14, phi_bb115_16, phi_bb115_17, phi_bb115_20, phi_bb115_21, phi_bb115_26});
  }

  TNode<FixedArray> phi_bb118_13;
  TNode<IntPtrT> phi_bb118_14;
  TNode<BoolT> phi_bb118_16;
  TNode<PrimitiveHeapObject> phi_bb118_17;
  TNode<String> phi_bb118_20;
  TNode<String> phi_bb118_21;
  TNode<String> phi_bb118_26;
  if (block118.is_used()) {
    ca_.Bind(&block118, &phi_bb118_13, &phi_bb118_14, &phi_bb118_16, &phi_bb118_17, &phi_bb118_20, &phi_bb118_21, &phi_bb118_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb117_13;
  TNode<IntPtrT> phi_bb117_14;
  TNode<BoolT> phi_bb117_16;
  TNode<PrimitiveHeapObject> phi_bb117_17;
  TNode<String> phi_bb117_20;
  TNode<String> phi_bb117_21;
  TNode<String> phi_bb117_26;
  TNode<BoolT> tmp144;
  if (block117.is_used()) {
    ca_.Bind(&block117, &phi_bb117_13, &phi_bb117_14, &phi_bb117_16, &phi_bb117_17, &phi_bb117_20, &phi_bb117_21, &phi_bb117_26);
    tmp144 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb117_14}, TNode<IntPtrT>{tmp140});
    ca_.Branch(tmp144, &block119, std::vector<compiler::Node*>{phi_bb117_13, phi_bb117_14, phi_bb117_16, phi_bb117_17, phi_bb117_20, phi_bb117_21, phi_bb117_26}, &block120, std::vector<compiler::Node*>{phi_bb117_13, phi_bb117_14, phi_bb117_16, phi_bb117_17, phi_bb117_20, phi_bb117_21, phi_bb117_26});
  }

  TNode<FixedArray> phi_bb119_13;
  TNode<IntPtrT> phi_bb119_14;
  TNode<BoolT> phi_bb119_16;
  TNode<PrimitiveHeapObject> phi_bb119_17;
  TNode<String> phi_bb119_20;
  TNode<String> phi_bb119_21;
  TNode<String> phi_bb119_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp145;
  TNode<IntPtrT> tmp146;
  TNode<IntPtrT> tmp147;
  TNode<IntPtrT> tmp148;
  TNode<IntPtrT> tmp149;
  TNode<UintPtrT> tmp150;
  TNode<UintPtrT> tmp151;
  TNode<BoolT> tmp152;
  if (block119.is_used()) {
    ca_.Bind(&block119, &phi_bb119_13, &phi_bb119_14, &phi_bb119_16, &phi_bb119_17, &phi_bb119_20, &phi_bb119_21, &phi_bb119_26);
    std::tie(tmp145, tmp146, tmp147) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb119_13}).Flatten();
    tmp148 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp149 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb119_14}, TNode<IntPtrT>{tmp148});
    tmp150 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb119_14});
    tmp151 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp147});
    tmp152 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp150}, TNode<UintPtrT>{tmp151});
    ca_.Branch(tmp152, &block126, std::vector<compiler::Node*>{phi_bb119_13, phi_bb119_16, phi_bb119_17, phi_bb119_20, phi_bb119_21, phi_bb119_26, phi_bb119_13, phi_bb119_14, phi_bb119_14, phi_bb119_14, phi_bb119_14}, &block127, std::vector<compiler::Node*>{phi_bb119_13, phi_bb119_16, phi_bb119_17, phi_bb119_20, phi_bb119_21, phi_bb119_26, phi_bb119_13, phi_bb119_14, phi_bb119_14, phi_bb119_14, phi_bb119_14});
  }

  TNode<FixedArray> phi_bb126_13;
  TNode<BoolT> phi_bb126_16;
  TNode<PrimitiveHeapObject> phi_bb126_17;
  TNode<String> phi_bb126_20;
  TNode<String> phi_bb126_21;
  TNode<String> phi_bb126_26;
  TNode<FixedArray> phi_bb126_35;
  TNode<IntPtrT> phi_bb126_39;
  TNode<IntPtrT> phi_bb126_40;
  TNode<IntPtrT> phi_bb126_44;
  TNode<IntPtrT> phi_bb126_45;
  TNode<IntPtrT> tmp153;
  TNode<IntPtrT> tmp154;
  TNode<Union<HeapObject, TaggedIndex>> tmp155;
  TNode<IntPtrT> tmp156;
  if (block126.is_used()) {
    ca_.Bind(&block126, &phi_bb126_13, &phi_bb126_16, &phi_bb126_17, &phi_bb126_20, &phi_bb126_21, &phi_bb126_26, &phi_bb126_35, &phi_bb126_39, &phi_bb126_40, &phi_bb126_44, &phi_bb126_45);
    tmp153 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb126_45});
    tmp154 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp146}, TNode<IntPtrT>{tmp153});
    std::tie(tmp155, tmp156) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp145}, TNode<IntPtrT>{tmp154}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp155, tmp156}, tmp139);
    ca_.Goto(&block121, phi_bb126_13, tmp149, phi_bb126_16, phi_bb126_17, phi_bb126_20, phi_bb126_21, phi_bb126_26);
  }

  TNode<FixedArray> phi_bb127_13;
  TNode<BoolT> phi_bb127_16;
  TNode<PrimitiveHeapObject> phi_bb127_17;
  TNode<String> phi_bb127_20;
  TNode<String> phi_bb127_21;
  TNode<String> phi_bb127_26;
  TNode<FixedArray> phi_bb127_35;
  TNode<IntPtrT> phi_bb127_39;
  TNode<IntPtrT> phi_bb127_40;
  TNode<IntPtrT> phi_bb127_44;
  TNode<IntPtrT> phi_bb127_45;
  if (block127.is_used()) {
    ca_.Bind(&block127, &phi_bb127_13, &phi_bb127_16, &phi_bb127_17, &phi_bb127_20, &phi_bb127_21, &phi_bb127_26, &phi_bb127_35, &phi_bb127_39, &phi_bb127_40, &phi_bb127_44, &phi_bb127_45);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb120_13;
  TNode<IntPtrT> phi_bb120_14;
  TNode<BoolT> phi_bb120_16;
  TNode<PrimitiveHeapObject> phi_bb120_17;
  TNode<String> phi_bb120_20;
  TNode<String> phi_bb120_21;
  TNode<String> phi_bb120_26;
  TNode<IntPtrT> tmp157;
  TNode<IntPtrT> tmp158;
  TNode<BoolT> tmp159;
  if (block120.is_used()) {
    ca_.Bind(&block120, &phi_bb120_13, &phi_bb120_14, &phi_bb120_16, &phi_bb120_17, &phi_bb120_20, &phi_bb120_21, &phi_bb120_26);
    tmp157 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp140});
    tmp158 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp159 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp157}, TNode<IntPtrT>{tmp158});
    ca_.Branch(tmp159, &block130, std::vector<compiler::Node*>{phi_bb120_13, phi_bb120_14, phi_bb120_16, phi_bb120_17, phi_bb120_20, phi_bb120_21, phi_bb120_26}, &block131, std::vector<compiler::Node*>{phi_bb120_13, phi_bb120_14, phi_bb120_16, phi_bb120_17, phi_bb120_20, phi_bb120_21, phi_bb120_26});
  }

  TNode<FixedArray> phi_bb130_13;
  TNode<IntPtrT> phi_bb130_14;
  TNode<BoolT> phi_bb130_16;
  TNode<PrimitiveHeapObject> phi_bb130_17;
  TNode<String> phi_bb130_20;
  TNode<String> phi_bb130_21;
  TNode<String> phi_bb130_26;
  TNode<IntPtrT> tmp160;
  if (block130.is_used()) {
    ca_.Bind(&block130, &phi_bb130_13, &phi_bb130_14, &phi_bb130_16, &phi_bb130_17, &phi_bb130_20, &phi_bb130_21, &phi_bb130_26);
    tmp160 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block132, phi_bb130_13, phi_bb130_14, phi_bb130_16, phi_bb130_17, phi_bb130_20, phi_bb130_21, phi_bb130_26, tmp160);
  }

  TNode<FixedArray> phi_bb131_13;
  TNode<IntPtrT> phi_bb131_14;
  TNode<BoolT> phi_bb131_16;
  TNode<PrimitiveHeapObject> phi_bb131_17;
  TNode<String> phi_bb131_20;
  TNode<String> phi_bb131_21;
  TNode<String> phi_bb131_26;
  if (block131.is_used()) {
    ca_.Bind(&block131, &phi_bb131_13, &phi_bb131_14, &phi_bb131_16, &phi_bb131_17, &phi_bb131_20, &phi_bb131_21, &phi_bb131_26);
    ca_.Goto(&block132, phi_bb131_13, phi_bb131_14, phi_bb131_16, phi_bb131_17, phi_bb131_20, phi_bb131_21, phi_bb131_26, tmp157);
  }

  TNode<FixedArray> phi_bb132_13;
  TNode<IntPtrT> phi_bb132_14;
  TNode<BoolT> phi_bb132_16;
  TNode<PrimitiveHeapObject> phi_bb132_17;
  TNode<String> phi_bb132_20;
  TNode<String> phi_bb132_21;
  TNode<String> phi_bb132_26;
  TNode<IntPtrT> phi_bb132_36;
  TNode<IntPtrT> tmp161;
  TNode<BoolT> tmp162;
  if (block132.is_used()) {
    ca_.Bind(&block132, &phi_bb132_13, &phi_bb132_14, &phi_bb132_16, &phi_bb132_17, &phi_bb132_20, &phi_bb132_21, &phi_bb132_26, &phi_bb132_36);
    tmp161 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp162 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb132_36}, TNode<IntPtrT>{tmp161});
    ca_.Branch(tmp162, &block134, std::vector<compiler::Node*>{phi_bb132_13, phi_bb132_14, phi_bb132_16, phi_bb132_17, phi_bb132_20, phi_bb132_21, phi_bb132_26}, &block135, std::vector<compiler::Node*>{phi_bb132_13, phi_bb132_14, phi_bb132_16, phi_bb132_17, phi_bb132_20, phi_bb132_21, phi_bb132_26});
  }

  TNode<FixedArray> phi_bb135_13;
  TNode<IntPtrT> phi_bb135_14;
  TNode<BoolT> phi_bb135_16;
  TNode<PrimitiveHeapObject> phi_bb135_17;
  TNode<String> phi_bb135_20;
  TNode<String> phi_bb135_21;
  TNode<String> phi_bb135_26;
  if (block135.is_used()) {
    ca_.Bind(&block135, &phi_bb135_13, &phi_bb135_14, &phi_bb135_16, &phi_bb135_17, &phi_bb135_20, &phi_bb135_21, &phi_bb135_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb134_13;
  TNode<IntPtrT> phi_bb134_14;
  TNode<BoolT> phi_bb134_16;
  TNode<PrimitiveHeapObject> phi_bb134_17;
  TNode<String> phi_bb134_20;
  TNode<String> phi_bb134_21;
  TNode<String> phi_bb134_26;
  TNode<FixedArray> tmp163;
  TNode<Union<HeapObject, TaggedIndex>> tmp164;
  TNode<IntPtrT> tmp165;
  TNode<IntPtrT> tmp166;
  TNode<UintPtrT> tmp167;
  TNode<IntPtrT> tmp168;
  TNode<UintPtrT> tmp169;
  TNode<UintPtrT> tmp170;
  TNode<BoolT> tmp171;
  if (block134.is_used()) {
    ca_.Bind(&block134, &phi_bb134_13, &phi_bb134_14, &phi_bb134_16, &phi_bb134_17, &phi_bb134_20, &phi_bb134_21, &phi_bb134_26);
    tmp163 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb132_36});
    std::tie(tmp164, tmp165, tmp166) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb134_13}).Flatten();
    tmp167 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp168 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp167});
    tmp169 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp168});
    tmp170 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp166});
    tmp171 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp169}, TNode<UintPtrT>{tmp170});
    ca_.Branch(tmp171, &block141, std::vector<compiler::Node*>{phi_bb134_13, phi_bb134_14, phi_bb134_16, phi_bb134_17, phi_bb134_20, phi_bb134_21, phi_bb134_26, phi_bb134_13}, &block142, std::vector<compiler::Node*>{phi_bb134_13, phi_bb134_14, phi_bb134_16, phi_bb134_17, phi_bb134_20, phi_bb134_21, phi_bb134_26, phi_bb134_13});
  }

  TNode<FixedArray> phi_bb141_13;
  TNode<IntPtrT> phi_bb141_14;
  TNode<BoolT> phi_bb141_16;
  TNode<PrimitiveHeapObject> phi_bb141_17;
  TNode<String> phi_bb141_20;
  TNode<String> phi_bb141_21;
  TNode<String> phi_bb141_26;
  TNode<FixedArray> phi_bb141_38;
  TNode<IntPtrT> tmp172;
  TNode<IntPtrT> tmp173;
  TNode<Union<HeapObject, TaggedIndex>> tmp174;
  TNode<IntPtrT> tmp175;
  TNode<Union<HeapObject, TaggedIndex>> tmp176;
  TNode<IntPtrT> tmp177;
  TNode<IntPtrT> tmp178;
  TNode<UintPtrT> tmp179;
  TNode<IntPtrT> tmp180;
  TNode<UintPtrT> tmp181;
  TNode<UintPtrT> tmp182;
  TNode<BoolT> tmp183;
  if (block141.is_used()) {
    ca_.Bind(&block141, &phi_bb141_13, &phi_bb141_14, &phi_bb141_16, &phi_bb141_17, &phi_bb141_20, &phi_bb141_21, &phi_bb141_26, &phi_bb141_38);
    tmp172 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp168});
    tmp173 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp165}, TNode<IntPtrT>{tmp172});
    std::tie(tmp174, tmp175) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp164}, TNode<IntPtrT>{tmp173}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp174, tmp175}, tmp163);
    std::tie(tmp176, tmp177, tmp178) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp163}).Flatten();
    tmp179 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp180 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp179});
    tmp181 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp180});
    tmp182 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp178});
    tmp183 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp181}, TNode<UintPtrT>{tmp182});
    ca_.Branch(tmp183, &block150, std::vector<compiler::Node*>{phi_bb141_13, phi_bb141_14, phi_bb141_16, phi_bb141_17, phi_bb141_20, phi_bb141_21, phi_bb141_26}, &block151, std::vector<compiler::Node*>{phi_bb141_13, phi_bb141_14, phi_bb141_16, phi_bb141_17, phi_bb141_20, phi_bb141_21, phi_bb141_26});
  }

  TNode<FixedArray> phi_bb142_13;
  TNode<IntPtrT> phi_bb142_14;
  TNode<BoolT> phi_bb142_16;
  TNode<PrimitiveHeapObject> phi_bb142_17;
  TNode<String> phi_bb142_20;
  TNode<String> phi_bb142_21;
  TNode<String> phi_bb142_26;
  TNode<FixedArray> phi_bb142_38;
  if (block142.is_used()) {
    ca_.Bind(&block142, &phi_bb142_13, &phi_bb142_14, &phi_bb142_16, &phi_bb142_17, &phi_bb142_20, &phi_bb142_21, &phi_bb142_26, &phi_bb142_38);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb150_13;
  TNode<IntPtrT> phi_bb150_14;
  TNode<BoolT> phi_bb150_16;
  TNode<PrimitiveHeapObject> phi_bb150_17;
  TNode<String> phi_bb150_20;
  TNode<String> phi_bb150_21;
  TNode<String> phi_bb150_26;
  TNode<IntPtrT> tmp184;
  TNode<IntPtrT> tmp185;
  TNode<Union<HeapObject, TaggedIndex>> tmp186;
  TNode<IntPtrT> tmp187;
  TNode<Undefined> tmp188;
  TNode<Union<HeapObject, TaggedIndex>> tmp189;
  TNode<IntPtrT> tmp190;
  TNode<IntPtrT> tmp191;
  TNode<UintPtrT> tmp192;
  TNode<IntPtrT> tmp193;
  TNode<UintPtrT> tmp194;
  TNode<UintPtrT> tmp195;
  TNode<BoolT> tmp196;
  if (block150.is_used()) {
    ca_.Bind(&block150, &phi_bb150_13, &phi_bb150_14, &phi_bb150_16, &phi_bb150_17, &phi_bb150_20, &phi_bb150_21, &phi_bb150_26);
    tmp184 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp180});
    tmp185 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp177}, TNode<IntPtrT>{tmp184});
    std::tie(tmp186, tmp187) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp176}, TNode<IntPtrT>{tmp185}).Flatten();
    tmp188 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp186, tmp187}, tmp188);
    std::tie(tmp189, tmp190, tmp191) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp163}).Flatten();
    tmp192 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp193 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp192});
    tmp194 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp193});
    tmp195 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp191});
    tmp196 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp194}, TNode<UintPtrT>{tmp195});
    ca_.Branch(tmp196, &block159, std::vector<compiler::Node*>{phi_bb150_13, phi_bb150_14, phi_bb150_16, phi_bb150_17, phi_bb150_20, phi_bb150_21, phi_bb150_26}, &block160, std::vector<compiler::Node*>{phi_bb150_13, phi_bb150_14, phi_bb150_16, phi_bb150_17, phi_bb150_20, phi_bb150_21, phi_bb150_26});
  }

  TNode<FixedArray> phi_bb151_13;
  TNode<IntPtrT> phi_bb151_14;
  TNode<BoolT> phi_bb151_16;
  TNode<PrimitiveHeapObject> phi_bb151_17;
  TNode<String> phi_bb151_20;
  TNode<String> phi_bb151_21;
  TNode<String> phi_bb151_26;
  if (block151.is_used()) {
    ca_.Bind(&block151, &phi_bb151_13, &phi_bb151_14, &phi_bb151_16, &phi_bb151_17, &phi_bb151_20, &phi_bb151_21, &phi_bb151_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb159_13;
  TNode<IntPtrT> phi_bb159_14;
  TNode<BoolT> phi_bb159_16;
  TNode<PrimitiveHeapObject> phi_bb159_17;
  TNode<String> phi_bb159_20;
  TNode<String> phi_bb159_21;
  TNode<String> phi_bb159_26;
  TNode<IntPtrT> tmp197;
  TNode<IntPtrT> tmp198;
  TNode<Union<HeapObject, TaggedIndex>> tmp199;
  TNode<IntPtrT> tmp200;
  TNode<IntPtrT> tmp201;
  if (block159.is_used()) {
    ca_.Bind(&block159, &phi_bb159_13, &phi_bb159_14, &phi_bb159_16, &phi_bb159_17, &phi_bb159_20, &phi_bb159_21, &phi_bb159_26);
    tmp197 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp193});
    tmp198 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp190}, TNode<IntPtrT>{tmp197});
    std::tie(tmp199, tmp200) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp189}, TNode<IntPtrT>{tmp198}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp199, tmp200}, tmp139);
    tmp201 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block121, tmp163, tmp201, phi_bb159_16, phi_bb159_17, phi_bb159_20, phi_bb159_21, phi_bb159_26);
  }

  TNode<FixedArray> phi_bb160_13;
  TNode<IntPtrT> phi_bb160_14;
  TNode<BoolT> phi_bb160_16;
  TNode<PrimitiveHeapObject> phi_bb160_17;
  TNode<String> phi_bb160_20;
  TNode<String> phi_bb160_21;
  TNode<String> phi_bb160_26;
  if (block160.is_used()) {
    ca_.Bind(&block160, &phi_bb160_13, &phi_bb160_14, &phi_bb160_16, &phi_bb160_17, &phi_bb160_20, &phi_bb160_21, &phi_bb160_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb121_13;
  TNode<IntPtrT> phi_bb121_14;
  TNode<BoolT> phi_bb121_16;
  TNode<PrimitiveHeapObject> phi_bb121_17;
  TNode<String> phi_bb121_20;
  TNode<String> phi_bb121_21;
  TNode<String> phi_bb121_26;
  if (block121.is_used()) {
    ca_.Bind(&block121, &phi_bb121_13, &phi_bb121_14, &phi_bb121_16, &phi_bb121_17, &phi_bb121_20, &phi_bb121_21, &phi_bb121_26);
    ca_.Goto(&block107, phi_bb121_13, phi_bb121_14, phi_bb121_16, phi_bb121_17, phi_bb121_20, phi_bb121_21, phi_bb121_26);
  }

  TNode<FixedArray> phi_bb108_13;
  TNode<IntPtrT> phi_bb108_14;
  TNode<BoolT> phi_bb108_16;
  TNode<PrimitiveHeapObject> phi_bb108_17;
  TNode<String> phi_bb108_20;
  TNode<String> phi_bb108_21;
  TNode<String> phi_bb108_26;
  TNode<Smi> tmp202;
  if (block108.is_used()) {
    ca_.Bind(&block108, &phi_bb108_13, &phi_bb108_14, &phi_bb108_16, &phi_bb108_17, &phi_bb108_20, &phi_bb108_21, &phi_bb108_26);
    compiler::CodeAssemblerLabel label203(&ca_);
    tmp202 = Cast_Smi_0(state_, TNode<Object>{ca_.UncheckedCast<Object>(tmp134)}, &label203);
    ca_.Goto(&block165, phi_bb108_13, phi_bb108_14, phi_bb108_16, phi_bb108_17, phi_bb108_20, phi_bb108_21, phi_bb108_26);
    if (label203.is_used()) {
      ca_.Bind(&label203);
      ca_.Goto(&block166, phi_bb108_13, phi_bb108_14, phi_bb108_16, phi_bb108_17, phi_bb108_20, phi_bb108_21, phi_bb108_26);
    }
  }

  TNode<FixedArray> phi_bb166_13;
  TNode<IntPtrT> phi_bb166_14;
  TNode<BoolT> phi_bb166_16;
  TNode<PrimitiveHeapObject> phi_bb166_17;
  TNode<String> phi_bb166_20;
  TNode<String> phi_bb166_21;
  TNode<String> phi_bb166_26;
  if (block166.is_used()) {
    ca_.Bind(&block166, &phi_bb166_13, &phi_bb166_14, &phi_bb166_16, &phi_bb166_17, &phi_bb166_20, &phi_bb166_21, &phi_bb166_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-join.tq:234:9");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb165_13;
  TNode<IntPtrT> phi_bb165_14;
  TNode<BoolT> phi_bb165_16;
  TNode<PrimitiveHeapObject> phi_bb165_17;
  TNode<String> phi_bb165_20;
  TNode<String> phi_bb165_21;
  TNode<String> phi_bb165_26;
  TNode<Smi> tmp204;
  TNode<BoolT> tmp205;
  if (block165.is_used()) {
    ca_.Bind(&block165, &phi_bb165_13, &phi_bb165_14, &phi_bb165_16, &phi_bb165_17, &phi_bb165_20, &phi_bb165_21, &phi_bb165_26);
    tmp204 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp205 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp202}, TNode<Smi>{tmp204});
    ca_.Branch(tmp205, &block167, std::vector<compiler::Node*>{phi_bb165_13, phi_bb165_14, phi_bb165_16, phi_bb165_17, phi_bb165_20, phi_bb165_21, phi_bb165_26}, &block168, std::vector<compiler::Node*>{phi_bb165_13, phi_bb165_14, phi_bb165_16, phi_bb165_17, phi_bb165_20, phi_bb165_21, phi_bb165_26});
  }

  TNode<FixedArray> phi_bb168_13;
  TNode<IntPtrT> phi_bb168_14;
  TNode<BoolT> phi_bb168_16;
  TNode<PrimitiveHeapObject> phi_bb168_17;
  TNode<String> phi_bb168_20;
  TNode<String> phi_bb168_21;
  TNode<String> phi_bb168_26;
  if (block168.is_used()) {
    ca_.Bind(&block168, &phi_bb168_13, &phi_bb168_14, &phi_bb168_16, &phi_bb168_17, &phi_bb168_20, &phi_bb168_21, &phi_bb168_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 229});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count < 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb167_13;
  TNode<IntPtrT> phi_bb167_14;
  TNode<BoolT> phi_bb167_16;
  TNode<PrimitiveHeapObject> phi_bb167_17;
  TNode<String> phi_bb167_20;
  TNode<String> phi_bb167_21;
  TNode<String> phi_bb167_26;
  TNode<Smi> tmp206;
  TNode<Smi> tmp207;
  TNode<Smi> tmp208;
  TNode<BoolT> tmp209;
  if (block167.is_used()) {
    ca_.Bind(&block167, &phi_bb167_13, &phi_bb167_14, &phi_bb167_16, &phi_bb167_17, &phi_bb167_20, &phi_bb167_21, &phi_bb167_26);
    tmp206 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp207 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp202}, TNode<Smi>{tmp206});
    tmp208 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp209 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{tmp207}, TNode<Smi>{tmp208});
    ca_.Branch(tmp209, &block169, std::vector<compiler::Node*>{phi_bb167_13, phi_bb167_14, phi_bb167_16, phi_bb167_17, phi_bb167_20, phi_bb167_21, phi_bb167_26}, &block170, std::vector<compiler::Node*>{phi_bb167_13, phi_bb167_14, phi_bb167_16, phi_bb167_17, phi_bb167_20, phi_bb167_21, phi_bb167_26});
  }

  TNode<FixedArray> phi_bb170_13;
  TNode<IntPtrT> phi_bb170_14;
  TNode<BoolT> phi_bb170_16;
  TNode<PrimitiveHeapObject> phi_bb170_17;
  TNode<String> phi_bb170_20;
  TNode<String> phi_bb170_21;
  TNode<String> phi_bb170_26;
  if (block170.is_used()) {
    ca_.Bind(&block170, &phi_bb170_13, &phi_bb170_14, &phi_bb170_16, &phi_bb170_17, &phi_bb170_20, &phi_bb170_21, &phi_bb170_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 230});
      CodeStubAssembler(state_).FailAssert("Torque assert 'count - 1 < 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb169_13;
  TNode<IntPtrT> phi_bb169_14;
  TNode<BoolT> phi_bb169_16;
  TNode<PrimitiveHeapObject> phi_bb169_17;
  TNode<String> phi_bb169_20;
  TNode<String> phi_bb169_21;
  TNode<String> phi_bb169_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp210;
  TNode<IntPtrT> tmp211;
  TNode<IntPtrT> tmp212;
  TNode<IntPtrT> tmp213;
  TNode<IntPtrT> tmp214;
  TNode<UintPtrT> tmp215;
  TNode<UintPtrT> tmp216;
  TNode<BoolT> tmp217;
  if (block169.is_used()) {
    ca_.Bind(&block169, &phi_bb169_13, &phi_bb169_14, &phi_bb169_16, &phi_bb169_17, &phi_bb169_20, &phi_bb169_21, &phi_bb169_26);
    std::tie(tmp210, tmp211, tmp212) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb169_13}).Flatten();
    tmp213 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp214 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{phi_bb169_14}, TNode<IntPtrT>{tmp213});
    tmp215 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp214});
    tmp216 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp212});
    tmp217 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp215}, TNode<UintPtrT>{tmp216});
    ca_.Branch(tmp217, &block175, std::vector<compiler::Node*>{phi_bb169_13, phi_bb169_14, phi_bb169_16, phi_bb169_17, phi_bb169_20, phi_bb169_21, phi_bb169_26, phi_bb169_13}, &block176, std::vector<compiler::Node*>{phi_bb169_13, phi_bb169_14, phi_bb169_16, phi_bb169_17, phi_bb169_20, phi_bb169_21, phi_bb169_26, phi_bb169_13});
  }

  TNode<FixedArray> phi_bb175_13;
  TNode<IntPtrT> phi_bb175_14;
  TNode<BoolT> phi_bb175_16;
  TNode<PrimitiveHeapObject> phi_bb175_17;
  TNode<String> phi_bb175_20;
  TNode<String> phi_bb175_21;
  TNode<String> phi_bb175_26;
  TNode<FixedArray> phi_bb175_32;
  TNode<IntPtrT> tmp218;
  TNode<IntPtrT> tmp219;
  TNode<Union<HeapObject, TaggedIndex>> tmp220;
  TNode<IntPtrT> tmp221;
  TNode<Smi> tmp222;
  TNode<Smi> tmp223;
  if (block175.is_used()) {
    ca_.Bind(&block175, &phi_bb175_13, &phi_bb175_14, &phi_bb175_16, &phi_bb175_17, &phi_bb175_20, &phi_bb175_21, &phi_bb175_26, &phi_bb175_32);
    tmp218 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp214});
    tmp219 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp211}, TNode<IntPtrT>{tmp218});
    std::tie(tmp220, tmp221) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp210}, TNode<IntPtrT>{tmp219}).Flatten();
    tmp222 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp223 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp202}, TNode<Smi>{tmp222});
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp220, tmp221}, tmp223);
    ca_.Goto(&block107, phi_bb175_13, phi_bb175_14, phi_bb175_16, phi_bb175_17, phi_bb175_20, phi_bb175_21, phi_bb175_26);
  }

  TNode<FixedArray> phi_bb176_13;
  TNode<IntPtrT> phi_bb176_14;
  TNode<BoolT> phi_bb176_16;
  TNode<PrimitiveHeapObject> phi_bb176_17;
  TNode<String> phi_bb176_20;
  TNode<String> phi_bb176_21;
  TNode<String> phi_bb176_26;
  TNode<FixedArray> phi_bb176_32;
  if (block176.is_used()) {
    ca_.Bind(&block176, &phi_bb176_13, &phi_bb176_14, &phi_bb176_16, &phi_bb176_17, &phi_bb176_20, &phi_bb176_21, &phi_bb176_26, &phi_bb176_32);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb107_13;
  TNode<IntPtrT> phi_bb107_14;
  TNode<BoolT> phi_bb107_16;
  TNode<PrimitiveHeapObject> phi_bb107_17;
  TNode<String> phi_bb107_20;
  TNode<String> phi_bb107_21;
  TNode<String> phi_bb107_26;
  if (block107.is_used()) {
    ca_.Bind(&block107, &phi_bb107_13, &phi_bb107_14, &phi_bb107_16, &phi_bb107_17, &phi_bb107_20, &phi_bb107_21, &phi_bb107_26);
    ca_.Goto(&block95, phi_bb107_13, phi_bb107_14, phi_bb107_16, phi_bb107_17, phi_bb107_20, phi_bb107_21, phi_bb107_26);
  }

  TNode<FixedArray> phi_bb94_13;
  TNode<IntPtrT> phi_bb94_14;
  TNode<BoolT> phi_bb94_16;
  TNode<PrimitiveHeapObject> phi_bb94_17;
  TNode<String> phi_bb94_20;
  TNode<String> phi_bb94_21;
  TNode<String> phi_bb94_26;
  TNode<IntPtrT> tmp224;
  TNode<IntPtrT> tmp225;
  TNode<BoolT> tmp226;
  if (block94.is_used()) {
    ca_.Bind(&block94, &phi_bb94_13, &phi_bb94_14, &phi_bb94_16, &phi_bb94_17, &phi_bb94_20, &phi_bb94_21, &phi_bb94_26);
    tmp224 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb94_13});
    tmp225 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp226 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb94_14}, TNode<IntPtrT>{tmp225});
    ca_.Branch(tmp226, &block180, std::vector<compiler::Node*>{phi_bb94_13, phi_bb94_14, phi_bb94_16, phi_bb94_17, phi_bb94_20, phi_bb94_21, phi_bb94_26, phi_bb94_26, phi_bb94_26}, &block181, std::vector<compiler::Node*>{phi_bb94_13, phi_bb94_14, phi_bb94_16, phi_bb94_17, phi_bb94_20, phi_bb94_21, phi_bb94_26, phi_bb94_26, phi_bb94_26});
  }

  TNode<FixedArray> phi_bb181_13;
  TNode<IntPtrT> phi_bb181_14;
  TNode<BoolT> phi_bb181_16;
  TNode<PrimitiveHeapObject> phi_bb181_17;
  TNode<String> phi_bb181_20;
  TNode<String> phi_bb181_21;
  TNode<String> phi_bb181_26;
  TNode<String> phi_bb181_30;
  TNode<Object> phi_bb181_31;
  if (block181.is_used()) {
    ca_.Bind(&block181, &phi_bb181_13, &phi_bb181_14, &phi_bb181_16, &phi_bb181_17, &phi_bb181_20, &phi_bb181_21, &phi_bb181_26, &phi_bb181_30, &phi_bb181_31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb180_13;
  TNode<IntPtrT> phi_bb180_14;
  TNode<BoolT> phi_bb180_16;
  TNode<PrimitiveHeapObject> phi_bb180_17;
  TNode<String> phi_bb180_20;
  TNode<String> phi_bb180_21;
  TNode<String> phi_bb180_26;
  TNode<String> phi_bb180_30;
  TNode<Object> phi_bb180_31;
  TNode<BoolT> tmp227;
  if (block180.is_used()) {
    ca_.Bind(&block180, &phi_bb180_13, &phi_bb180_14, &phi_bb180_16, &phi_bb180_17, &phi_bb180_20, &phi_bb180_21, &phi_bb180_26, &phi_bb180_30, &phi_bb180_31);
    tmp227 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb180_14}, TNode<IntPtrT>{tmp224});
    ca_.Branch(tmp227, &block182, std::vector<compiler::Node*>{phi_bb180_13, phi_bb180_14, phi_bb180_16, phi_bb180_17, phi_bb180_20, phi_bb180_21, phi_bb180_26, phi_bb180_30, phi_bb180_31}, &block183, std::vector<compiler::Node*>{phi_bb180_13, phi_bb180_14, phi_bb180_16, phi_bb180_17, phi_bb180_20, phi_bb180_21, phi_bb180_26, phi_bb180_30, phi_bb180_31});
  }

  TNode<FixedArray> phi_bb183_13;
  TNode<IntPtrT> phi_bb183_14;
  TNode<BoolT> phi_bb183_16;
  TNode<PrimitiveHeapObject> phi_bb183_17;
  TNode<String> phi_bb183_20;
  TNode<String> phi_bb183_21;
  TNode<String> phi_bb183_26;
  TNode<String> phi_bb183_30;
  TNode<Object> phi_bb183_31;
  if (block183.is_used()) {
    ca_.Bind(&block183, &phi_bb183_13, &phi_bb183_14, &phi_bb183_16, &phi_bb183_17, &phi_bb183_20, &phi_bb183_21, &phi_bb183_26, &phi_bb183_30, &phi_bb183_31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb182_13;
  TNode<IntPtrT> phi_bb182_14;
  TNode<BoolT> phi_bb182_16;
  TNode<PrimitiveHeapObject> phi_bb182_17;
  TNode<String> phi_bb182_20;
  TNode<String> phi_bb182_21;
  TNode<String> phi_bb182_26;
  TNode<String> phi_bb182_30;
  TNode<Object> phi_bb182_31;
  TNode<BoolT> tmp228;
  if (block182.is_used()) {
    ca_.Bind(&block182, &phi_bb182_13, &phi_bb182_14, &phi_bb182_16, &phi_bb182_17, &phi_bb182_20, &phi_bb182_21, &phi_bb182_26, &phi_bb182_30, &phi_bb182_31);
    tmp228 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb182_14}, TNode<IntPtrT>{tmp224});
    ca_.Branch(tmp228, &block184, std::vector<compiler::Node*>{phi_bb182_13, phi_bb182_14, phi_bb182_16, phi_bb182_17, phi_bb182_20, phi_bb182_21, phi_bb182_26, phi_bb182_30, phi_bb182_31}, &block185, std::vector<compiler::Node*>{phi_bb182_13, phi_bb182_14, phi_bb182_16, phi_bb182_17, phi_bb182_20, phi_bb182_21, phi_bb182_26, phi_bb182_30, phi_bb182_31});
  }

  TNode<FixedArray> phi_bb184_13;
  TNode<IntPtrT> phi_bb184_14;
  TNode<BoolT> phi_bb184_16;
  TNode<PrimitiveHeapObject> phi_bb184_17;
  TNode<String> phi_bb184_20;
  TNode<String> phi_bb184_21;
  TNode<String> phi_bb184_26;
  TNode<String> phi_bb184_30;
  TNode<Object> phi_bb184_31;
  TNode<Union<HeapObject, TaggedIndex>> tmp229;
  TNode<IntPtrT> tmp230;
  TNode<IntPtrT> tmp231;
  TNode<IntPtrT> tmp232;
  TNode<IntPtrT> tmp233;
  TNode<UintPtrT> tmp234;
  TNode<UintPtrT> tmp235;
  TNode<BoolT> tmp236;
  if (block184.is_used()) {
    ca_.Bind(&block184, &phi_bb184_13, &phi_bb184_14, &phi_bb184_16, &phi_bb184_17, &phi_bb184_20, &phi_bb184_21, &phi_bb184_26, &phi_bb184_30, &phi_bb184_31);
    std::tie(tmp229, tmp230, tmp231) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb184_13}).Flatten();
    tmp232 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp233 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb184_14}, TNode<IntPtrT>{tmp232});
    tmp234 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb184_14});
    tmp235 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp231});
    tmp236 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp234}, TNode<UintPtrT>{tmp235});
    ca_.Branch(tmp236, &block191, std::vector<compiler::Node*>{phi_bb184_13, phi_bb184_16, phi_bb184_17, phi_bb184_20, phi_bb184_21, phi_bb184_26, phi_bb184_30, phi_bb184_31, phi_bb184_13, phi_bb184_14, phi_bb184_14, phi_bb184_14, phi_bb184_14}, &block192, std::vector<compiler::Node*>{phi_bb184_13, phi_bb184_16, phi_bb184_17, phi_bb184_20, phi_bb184_21, phi_bb184_26, phi_bb184_30, phi_bb184_31, phi_bb184_13, phi_bb184_14, phi_bb184_14, phi_bb184_14, phi_bb184_14});
  }

  TNode<FixedArray> phi_bb191_13;
  TNode<BoolT> phi_bb191_16;
  TNode<PrimitiveHeapObject> phi_bb191_17;
  TNode<String> phi_bb191_20;
  TNode<String> phi_bb191_21;
  TNode<String> phi_bb191_26;
  TNode<String> phi_bb191_30;
  TNode<Object> phi_bb191_31;
  TNode<FixedArray> phi_bb191_33;
  TNode<IntPtrT> phi_bb191_37;
  TNode<IntPtrT> phi_bb191_38;
  TNode<IntPtrT> phi_bb191_42;
  TNode<IntPtrT> phi_bb191_43;
  TNode<IntPtrT> tmp237;
  TNode<IntPtrT> tmp238;
  TNode<Union<HeapObject, TaggedIndex>> tmp239;
  TNode<IntPtrT> tmp240;
  if (block191.is_used()) {
    ca_.Bind(&block191, &phi_bb191_13, &phi_bb191_16, &phi_bb191_17, &phi_bb191_20, &phi_bb191_21, &phi_bb191_26, &phi_bb191_30, &phi_bb191_31, &phi_bb191_33, &phi_bb191_37, &phi_bb191_38, &phi_bb191_42, &phi_bb191_43);
    tmp237 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb191_43});
    tmp238 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp230}, TNode<IntPtrT>{tmp237});
    std::tie(tmp239, tmp240) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp229}, TNode<IntPtrT>{tmp238}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp239, tmp240}, phi_bb191_31);
    ca_.Goto(&block186, phi_bb191_13, tmp233, phi_bb191_16, phi_bb191_17, phi_bb191_20, phi_bb191_21, phi_bb191_26, phi_bb191_30, phi_bb191_31);
  }

  TNode<FixedArray> phi_bb192_13;
  TNode<BoolT> phi_bb192_16;
  TNode<PrimitiveHeapObject> phi_bb192_17;
  TNode<String> phi_bb192_20;
  TNode<String> phi_bb192_21;
  TNode<String> phi_bb192_26;
  TNode<String> phi_bb192_30;
  TNode<Object> phi_bb192_31;
  TNode<FixedArray> phi_bb192_33;
  TNode<IntPtrT> phi_bb192_37;
  TNode<IntPtrT> phi_bb192_38;
  TNode<IntPtrT> phi_bb192_42;
  TNode<IntPtrT> phi_bb192_43;
  if (block192.is_used()) {
    ca_.Bind(&block192, &phi_bb192_13, &phi_bb192_16, &phi_bb192_17, &phi_bb192_20, &phi_bb192_21, &phi_bb192_26, &phi_bb192_30, &phi_bb192_31, &phi_bb192_33, &phi_bb192_37, &phi_bb192_38, &phi_bb192_42, &phi_bb192_43);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb185_13;
  TNode<IntPtrT> phi_bb185_14;
  TNode<BoolT> phi_bb185_16;
  TNode<PrimitiveHeapObject> phi_bb185_17;
  TNode<String> phi_bb185_20;
  TNode<String> phi_bb185_21;
  TNode<String> phi_bb185_26;
  TNode<String> phi_bb185_30;
  TNode<Object> phi_bb185_31;
  TNode<IntPtrT> tmp241;
  TNode<IntPtrT> tmp242;
  TNode<BoolT> tmp243;
  if (block185.is_used()) {
    ca_.Bind(&block185, &phi_bb185_13, &phi_bb185_14, &phi_bb185_16, &phi_bb185_17, &phi_bb185_20, &phi_bb185_21, &phi_bb185_26, &phi_bb185_30, &phi_bb185_31);
    tmp241 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp224});
    tmp242 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp243 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp241}, TNode<IntPtrT>{tmp242});
    ca_.Branch(tmp243, &block195, std::vector<compiler::Node*>{phi_bb185_13, phi_bb185_14, phi_bb185_16, phi_bb185_17, phi_bb185_20, phi_bb185_21, phi_bb185_26, phi_bb185_30, phi_bb185_31}, &block196, std::vector<compiler::Node*>{phi_bb185_13, phi_bb185_14, phi_bb185_16, phi_bb185_17, phi_bb185_20, phi_bb185_21, phi_bb185_26, phi_bb185_30, phi_bb185_31});
  }

  TNode<FixedArray> phi_bb195_13;
  TNode<IntPtrT> phi_bb195_14;
  TNode<BoolT> phi_bb195_16;
  TNode<PrimitiveHeapObject> phi_bb195_17;
  TNode<String> phi_bb195_20;
  TNode<String> phi_bb195_21;
  TNode<String> phi_bb195_26;
  TNode<String> phi_bb195_30;
  TNode<Object> phi_bb195_31;
  TNode<IntPtrT> tmp244;
  if (block195.is_used()) {
    ca_.Bind(&block195, &phi_bb195_13, &phi_bb195_14, &phi_bb195_16, &phi_bb195_17, &phi_bb195_20, &phi_bb195_21, &phi_bb195_26, &phi_bb195_30, &phi_bb195_31);
    tmp244 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block197, phi_bb195_13, phi_bb195_14, phi_bb195_16, phi_bb195_17, phi_bb195_20, phi_bb195_21, phi_bb195_26, phi_bb195_30, phi_bb195_31, tmp244);
  }

  TNode<FixedArray> phi_bb196_13;
  TNode<IntPtrT> phi_bb196_14;
  TNode<BoolT> phi_bb196_16;
  TNode<PrimitiveHeapObject> phi_bb196_17;
  TNode<String> phi_bb196_20;
  TNode<String> phi_bb196_21;
  TNode<String> phi_bb196_26;
  TNode<String> phi_bb196_30;
  TNode<Object> phi_bb196_31;
  if (block196.is_used()) {
    ca_.Bind(&block196, &phi_bb196_13, &phi_bb196_14, &phi_bb196_16, &phi_bb196_17, &phi_bb196_20, &phi_bb196_21, &phi_bb196_26, &phi_bb196_30, &phi_bb196_31);
    ca_.Goto(&block197, phi_bb196_13, phi_bb196_14, phi_bb196_16, phi_bb196_17, phi_bb196_20, phi_bb196_21, phi_bb196_26, phi_bb196_30, phi_bb196_31, tmp241);
  }

  TNode<FixedArray> phi_bb197_13;
  TNode<IntPtrT> phi_bb197_14;
  TNode<BoolT> phi_bb197_16;
  TNode<PrimitiveHeapObject> phi_bb197_17;
  TNode<String> phi_bb197_20;
  TNode<String> phi_bb197_21;
  TNode<String> phi_bb197_26;
  TNode<String> phi_bb197_30;
  TNode<Object> phi_bb197_31;
  TNode<IntPtrT> phi_bb197_34;
  TNode<IntPtrT> tmp245;
  TNode<BoolT> tmp246;
  if (block197.is_used()) {
    ca_.Bind(&block197, &phi_bb197_13, &phi_bb197_14, &phi_bb197_16, &phi_bb197_17, &phi_bb197_20, &phi_bb197_21, &phi_bb197_26, &phi_bb197_30, &phi_bb197_31, &phi_bb197_34);
    tmp245 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp246 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb197_34}, TNode<IntPtrT>{tmp245});
    ca_.Branch(tmp246, &block199, std::vector<compiler::Node*>{phi_bb197_13, phi_bb197_14, phi_bb197_16, phi_bb197_17, phi_bb197_20, phi_bb197_21, phi_bb197_26, phi_bb197_30, phi_bb197_31}, &block200, std::vector<compiler::Node*>{phi_bb197_13, phi_bb197_14, phi_bb197_16, phi_bb197_17, phi_bb197_20, phi_bb197_21, phi_bb197_26, phi_bb197_30, phi_bb197_31});
  }

  TNode<FixedArray> phi_bb200_13;
  TNode<IntPtrT> phi_bb200_14;
  TNode<BoolT> phi_bb200_16;
  TNode<PrimitiveHeapObject> phi_bb200_17;
  TNode<String> phi_bb200_20;
  TNode<String> phi_bb200_21;
  TNode<String> phi_bb200_26;
  TNode<String> phi_bb200_30;
  TNode<Object> phi_bb200_31;
  if (block200.is_used()) {
    ca_.Bind(&block200, &phi_bb200_13, &phi_bb200_14, &phi_bb200_16, &phi_bb200_17, &phi_bb200_20, &phi_bb200_21, &phi_bb200_26, &phi_bb200_30, &phi_bb200_31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<FixedArray> phi_bb199_13;
  TNode<IntPtrT> phi_bb199_14;
  TNode<BoolT> phi_bb199_16;
  TNode<PrimitiveHeapObject> phi_bb199_17;
  TNode<String> phi_bb199_20;
  TNode<String> phi_bb199_21;
  TNode<String> phi_bb199_26;
  TNode<String> phi_bb199_30;
  TNode<Object> phi_bb199_31;
  TNode<FixedArray> tmp247;
  TNode<Union<HeapObject, TaggedIndex>> tmp248;
  TNode<IntPtrT> tmp249;
  TNode<IntPtrT> tmp250;
  TNode<UintPtrT> tmp251;
  TNode<IntPtrT> tmp252;
  TNode<UintPtrT> tmp253;
  TNode<UintPtrT> tmp254;
  TNode<BoolT> tmp255;
  if (block199.is_used()) {
    ca_.Bind(&block199, &phi_bb199_13, &phi_bb199_14, &phi_bb199_16, &phi_bb199_17, &phi_bb199_20, &phi_bb199_21, &phi_bb199_26, &phi_bb199_30, &phi_bb199_31);
    tmp247 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb197_34});
    std::tie(tmp248, tmp249, tmp250) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb199_13}).Flatten();
    tmp251 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp252 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp251});
    tmp253 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp252});
    tmp254 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp250});
    tmp255 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp253}, TNode<UintPtrT>{tmp254});
    ca_.Branch(tmp255, &block206, std::vector<compiler::Node*>{phi_bb199_13, phi_bb199_14, phi_bb199_16, phi_bb199_17, phi_bb199_20, phi_bb199_21, phi_bb199_26, phi_bb199_30, phi_bb199_31, phi_bb199_13}, &block207, std::vector<compiler::Node*>{phi_bb199_13, phi_bb199_14, phi_bb199_16, phi_bb199_17, phi_bb199_20, phi_bb199_21, phi_bb199_26, phi_bb199_30, phi_bb199_31, phi_bb199_13});
  }

  TNode<FixedArray> phi_bb206_13;
  TNode<IntPtrT> phi_bb206_14;
  TNode<BoolT> phi_bb206_16;
  TNode<PrimitiveHeapObject> phi_bb206_17;
  TNode<String> phi_bb206_20;
  TNode<String> phi_bb206_21;
  TNode<String> phi_bb206_26;
  TNode<String> phi_bb206_30;
  TNode<Object> phi_bb206_31;
  TNode<FixedArray> phi_bb206_36;
  TNode<IntPtrT> tmp256;
  TNode<IntPtrT> tmp257;
  TNode<Union<HeapObject, TaggedIndex>> tmp258;
  TNode<IntPtrT> tmp259;
  TNode<Union<HeapObject, TaggedIndex>> tmp260;
  TNode<IntPtrT> tmp261;
  TNode<IntPtrT> tmp262;
  TNode<UintPtrT> tmp263;
  TNode<IntPtrT> tmp264;
  TNode<UintPtrT> tmp265;
  TNode<UintPtrT> tmp266;
  TNode<BoolT> tmp267;
  if (block206.is_used()) {
    ca_.Bind(&block206, &phi_bb206_13, &phi_bb206_14, &phi_bb206_16, &phi_bb206_17, &phi_bb206_20, &phi_bb206_21, &phi_bb206_26, &phi_bb206_30, &phi_bb206_31, &phi_bb206_36);
    tmp256 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp252});
    tmp257 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp249}, TNode<IntPtrT>{tmp256});
    std::tie(tmp258, tmp259) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp248}, TNode<IntPtrT>{tmp257}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp258, tmp259}, tmp247);
    std::tie(tmp260, tmp261, tmp262) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp247}).Flatten();
    tmp263 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp264 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp263});
    tmp265 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp264});
    tmp266 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp262});
    tmp267 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp265}, TNode<UintPtrT>{tmp266});
    ca_.Branch(tmp267, &block215, std::vector<compiler::Node*>{phi_bb206_13, phi_bb206_14, phi_bb206_16, phi_bb206_17, phi_bb206_20, phi_bb206_21, phi_bb206_26, phi_bb206_30, phi_bb206_31}, &block216, std::vector<compiler::Node*>{phi_bb206_13, phi_bb206_14, phi_bb206_16, phi_bb206_17, phi_bb206_20, phi_bb206_21, phi_bb206_26, phi_bb206_30, phi_bb206_31});
  }

  TNode<FixedArray> phi_bb207_13;
  TNode<IntPtrT> phi_bb207_14;
  TNode<BoolT> phi_bb207_16;
  TNode<PrimitiveHeapObject> phi_bb207_17;
  TNode<String> phi_bb207_20;
  TNode<String> phi_bb207_21;
  TNode<String> phi_bb207_26;
  TNode<String> phi_bb207_30;
  TNode<Object> phi_bb207_31;
  TNode<FixedArray> phi_bb207_36;
  if (block207.is_used()) {
    ca_.Bind(&block207, &phi_bb207_13, &phi_bb207_14, &phi_bb207_16, &phi_bb207_17, &phi_bb207_20, &phi_bb207_21, &phi_bb207_26, &phi_bb207_30, &phi_bb207_31, &phi_bb207_36);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb215_13;
  TNode<IntPtrT> phi_bb215_14;
  TNode<BoolT> phi_bb215_16;
  TNode<PrimitiveHeapObject> phi_bb215_17;
  TNode<String> phi_bb215_20;
  TNode<String> phi_bb215_21;
  TNode<String> phi_bb215_26;
  TNode<String> phi_bb215_30;
  TNode<Object> phi_bb215_31;
  TNode<IntPtrT> tmp268;
  TNode<IntPtrT> tmp269;
  TNode<Union<HeapObject, TaggedIndex>> tmp270;
  TNode<IntPtrT> tmp271;
  TNode<Undefined> tmp272;
  TNode<Union<HeapObject, TaggedIndex>> tmp273;
  TNode<IntPtrT> tmp274;
  TNode<IntPtrT> tmp275;
  TNode<UintPtrT> tmp276;
  TNode<IntPtrT> tmp277;
  TNode<UintPtrT> tmp278;
  TNode<UintPtrT> tmp279;
  TNode<BoolT> tmp280;
  if (block215.is_used()) {
    ca_.Bind(&block215, &phi_bb215_13, &phi_bb215_14, &phi_bb215_16, &phi_bb215_17, &phi_bb215_20, &phi_bb215_21, &phi_bb215_26, &phi_bb215_30, &phi_bb215_31);
    tmp268 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp264});
    tmp269 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp261}, TNode<IntPtrT>{tmp268});
    std::tie(tmp270, tmp271) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp260}, TNode<IntPtrT>{tmp269}).Flatten();
    tmp272 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp270, tmp271}, tmp272);
    std::tie(tmp273, tmp274, tmp275) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp247}).Flatten();
    tmp276 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp277 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp276});
    tmp278 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp277});
    tmp279 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp275});
    tmp280 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp278}, TNode<UintPtrT>{tmp279});
    ca_.Branch(tmp280, &block224, std::vector<compiler::Node*>{phi_bb215_13, phi_bb215_14, phi_bb215_16, phi_bb215_17, phi_bb215_20, phi_bb215_21, phi_bb215_26, phi_bb215_30, phi_bb215_31}, &block225, std::vector<compiler::Node*>{phi_bb215_13, phi_bb215_14, phi_bb215_16, phi_bb215_17, phi_bb215_20, phi_bb215_21, phi_bb215_26, phi_bb215_30, phi_bb215_31});
  }

  TNode<FixedArray> phi_bb216_13;
  TNode<IntPtrT> phi_bb216_14;
  TNode<BoolT> phi_bb216_16;
  TNode<PrimitiveHeapObject> phi_bb216_17;
  TNode<String> phi_bb216_20;
  TNode<String> phi_bb216_21;
  TNode<String> phi_bb216_26;
  TNode<String> phi_bb216_30;
  TNode<Object> phi_bb216_31;
  if (block216.is_used()) {
    ca_.Bind(&block216, &phi_bb216_13, &phi_bb216_14, &phi_bb216_16, &phi_bb216_17, &phi_bb216_20, &phi_bb216_21, &phi_bb216_26, &phi_bb216_30, &phi_bb216_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb224_13;
  TNode<IntPtrT> phi_bb224_14;
  TNode<BoolT> phi_bb224_16;
  TNode<PrimitiveHeapObject> phi_bb224_17;
  TNode<String> phi_bb224_20;
  TNode<String> phi_bb224_21;
  TNode<String> phi_bb224_26;
  TNode<String> phi_bb224_30;
  TNode<Object> phi_bb224_31;
  TNode<IntPtrT> tmp281;
  TNode<IntPtrT> tmp282;
  TNode<Union<HeapObject, TaggedIndex>> tmp283;
  TNode<IntPtrT> tmp284;
  TNode<IntPtrT> tmp285;
  if (block224.is_used()) {
    ca_.Bind(&block224, &phi_bb224_13, &phi_bb224_14, &phi_bb224_16, &phi_bb224_17, &phi_bb224_20, &phi_bb224_21, &phi_bb224_26, &phi_bb224_30, &phi_bb224_31);
    tmp281 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp277});
    tmp282 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp274}, TNode<IntPtrT>{tmp281});
    std::tie(tmp283, tmp284) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp273}, TNode<IntPtrT>{tmp282}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp283, tmp284}, phi_bb224_31);
    tmp285 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block186, tmp247, tmp285, phi_bb224_16, phi_bb224_17, phi_bb224_20, phi_bb224_21, phi_bb224_26, phi_bb224_30, phi_bb224_31);
  }

  TNode<FixedArray> phi_bb225_13;
  TNode<IntPtrT> phi_bb225_14;
  TNode<BoolT> phi_bb225_16;
  TNode<PrimitiveHeapObject> phi_bb225_17;
  TNode<String> phi_bb225_20;
  TNode<String> phi_bb225_21;
  TNode<String> phi_bb225_26;
  TNode<String> phi_bb225_30;
  TNode<Object> phi_bb225_31;
  if (block225.is_used()) {
    ca_.Bind(&block225, &phi_bb225_13, &phi_bb225_14, &phi_bb225_16, &phi_bb225_17, &phi_bb225_20, &phi_bb225_21, &phi_bb225_26, &phi_bb225_30, &phi_bb225_31);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb186_13;
  TNode<IntPtrT> phi_bb186_14;
  TNode<BoolT> phi_bb186_16;
  TNode<PrimitiveHeapObject> phi_bb186_17;
  TNode<String> phi_bb186_20;
  TNode<String> phi_bb186_21;
  TNode<String> phi_bb186_26;
  TNode<String> phi_bb186_30;
  TNode<Object> phi_bb186_31;
  if (block186.is_used()) {
    ca_.Bind(&block186, &phi_bb186_13, &phi_bb186_14, &phi_bb186_16, &phi_bb186_17, &phi_bb186_20, &phi_bb186_21, &phi_bb186_26, &phi_bb186_30, &phi_bb186_31);
    ca_.Goto(&block95, phi_bb186_13, phi_bb186_14, phi_bb186_16, phi_bb186_26, phi_bb186_20, phi_bb186_21, phi_bb186_26);
  }

  TNode<FixedArray> phi_bb95_13;
  TNode<IntPtrT> phi_bb95_14;
  TNode<BoolT> phi_bb95_16;
  TNode<PrimitiveHeapObject> phi_bb95_17;
  TNode<String> phi_bb95_20;
  TNode<String> phi_bb95_21;
  TNode<String> phi_bb95_26;
  TNode<IntPtrT> tmp286;
  TNode<Map> tmp287;
  TNode<BoolT> tmp288;
  TNode<BoolT> tmp289;
  TNode<IntPtrT> tmp290;
  if (block95.is_used()) {
    ca_.Bind(&block95, &phi_bb95_13, &phi_bb95_14, &phi_bb95_16, &phi_bb95_17, &phi_bb95_20, &phi_bb95_21, &phi_bb95_26);
    tmp286 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp287 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{phi_bb95_26, tmp286});
    tmp288 = CodeStubAssembler(state_).IsOneByteStringMap(TNode<Map>{tmp287});
    tmp289 = CodeStubAssembler(state_).Word32And(TNode<BoolT>{tmp288}, TNode<BoolT>{phi_bb95_16});
    tmp290 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block4, tmp290, phi_bb6_11, phi_bb95_13, phi_bb95_14, tmp118, tmp289, phi_bb95_17, tmp19);
  }

  TNode<IntPtrT> phi_bb3_10;
  TNode<BuiltinPtr> phi_bb3_11;
  TNode<FixedArray> phi_bb3_13;
  TNode<IntPtrT> phi_bb3_14;
  TNode<IntPtrT> phi_bb3_15;
  TNode<BoolT> phi_bb3_16;
  TNode<PrimitiveHeapObject> phi_bb3_17;
  TNode<UintPtrT> phi_bb3_18;
  TNode<BoolT> tmp291;
  TNode<IntPtrT> tmp292;
  TNode<BoolT> tmp293;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_10, &phi_bb3_11, &phi_bb3_13, &phi_bb3_14, &phi_bb3_15, &phi_bb3_16, &phi_bb3_17, &phi_bb3_18);
    tmp291 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp292 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp293 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{phi_bb3_10}, TNode<IntPtrT>{tmp292});
    ca_.Branch(tmp293, &block231, std::vector<compiler::Node*>{phi_bb3_10, phi_bb3_11, phi_bb3_13, phi_bb3_14, phi_bb3_15, phi_bb3_16, phi_bb3_17, phi_bb3_18, phi_bb3_10, phi_bb3_10}, &block232, std::vector<compiler::Node*>{phi_bb3_10, phi_bb3_11, phi_bb3_13, phi_bb3_14, phi_bb3_15, phi_bb3_16, phi_bb3_17, phi_bb3_18, phi_bb3_10, phi_bb3_10});
  }

  TNode<IntPtrT> phi_bb231_10;
  TNode<BuiltinPtr> phi_bb231_11;
  TNode<FixedArray> phi_bb231_13;
  TNode<IntPtrT> phi_bb231_14;
  TNode<IntPtrT> phi_bb231_15;
  TNode<BoolT> phi_bb231_16;
  TNode<PrimitiveHeapObject> phi_bb231_17;
  TNode<UintPtrT> phi_bb231_18;
  TNode<IntPtrT> phi_bb231_19;
  TNode<IntPtrT> phi_bb231_23;
  TNode<BoolT> tmp294;
  if (block231.is_used()) {
    ca_.Bind(&block231, &phi_bb231_10, &phi_bb231_11, &phi_bb231_13, &phi_bb231_14, &phi_bb231_15, &phi_bb231_16, &phi_bb231_17, &phi_bb231_18, &phi_bb231_19, &phi_bb231_23);
    tmp294 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block233, phi_bb231_10, phi_bb231_11, phi_bb231_13, phi_bb231_14, phi_bb231_15, phi_bb231_16, phi_bb231_17, phi_bb231_18, phi_bb231_19, phi_bb231_23, tmp294);
  }

  TNode<IntPtrT> phi_bb232_10;
  TNode<BuiltinPtr> phi_bb232_11;
  TNode<FixedArray> phi_bb232_13;
  TNode<IntPtrT> phi_bb232_14;
  TNode<IntPtrT> phi_bb232_15;
  TNode<BoolT> phi_bb232_16;
  TNode<PrimitiveHeapObject> phi_bb232_17;
  TNode<UintPtrT> phi_bb232_18;
  TNode<IntPtrT> phi_bb232_19;
  TNode<IntPtrT> phi_bb232_23;
  TNode<IntPtrT> tmp295;
  TNode<BoolT> tmp296;
  if (block232.is_used()) {
    ca_.Bind(&block232, &phi_bb232_10, &phi_bb232_11, &phi_bb232_13, &phi_bb232_14, &phi_bb232_15, &phi_bb232_16, &phi_bb232_17, &phi_bb232_18, &phi_bb232_19, &phi_bb232_23);
    tmp295 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp296 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{tmp295});
    ca_.Goto(&block233, phi_bb232_10, phi_bb232_11, phi_bb232_13, phi_bb232_14, phi_bb232_15, phi_bb232_16, phi_bb232_17, phi_bb232_18, phi_bb232_19, phi_bb232_23, tmp296);
  }

  TNode<IntPtrT> phi_bb233_10;
  TNode<BuiltinPtr> phi_bb233_11;
  TNode<FixedArray> phi_bb233_13;
  TNode<IntPtrT> phi_bb233_14;
  TNode<IntPtrT> phi_bb233_15;
  TNode<BoolT> phi_bb233_16;
  TNode<PrimitiveHeapObject> phi_bb233_17;
  TNode<UintPtrT> phi_bb233_18;
  TNode<IntPtrT> phi_bb233_19;
  TNode<IntPtrT> phi_bb233_23;
  TNode<BoolT> phi_bb233_27;
  if (block233.is_used()) {
    ca_.Bind(&block233, &phi_bb233_10, &phi_bb233_11, &phi_bb233_13, &phi_bb233_14, &phi_bb233_15, &phi_bb233_16, &phi_bb233_17, &phi_bb233_18, &phi_bb233_19, &phi_bb233_23, &phi_bb233_27);
    ca_.Branch(phi_bb233_27, &block229, std::vector<compiler::Node*>{phi_bb233_10, phi_bb233_11, phi_bb233_13, phi_bb233_14, phi_bb233_15, phi_bb233_16, phi_bb233_17, phi_bb233_18, phi_bb233_19, phi_bb233_23}, &block230, std::vector<compiler::Node*>{phi_bb233_10, phi_bb233_11, phi_bb233_13, phi_bb233_14, phi_bb233_15, phi_bb233_16, phi_bb233_17, phi_bb233_18, phi_bb233_19, phi_bb233_23});
  }

  TNode<IntPtrT> phi_bb229_10;
  TNode<BuiltinPtr> phi_bb229_11;
  TNode<FixedArray> phi_bb229_13;
  TNode<IntPtrT> phi_bb229_14;
  TNode<IntPtrT> phi_bb229_15;
  TNode<BoolT> phi_bb229_16;
  TNode<PrimitiveHeapObject> phi_bb229_17;
  TNode<UintPtrT> phi_bb229_18;
  TNode<IntPtrT> phi_bb229_19;
  TNode<IntPtrT> phi_bb229_23;
  if (block229.is_used()) {
    ca_.Bind(&block229, &phi_bb229_10, &phi_bb229_11, &phi_bb229_13, &phi_bb229_14, &phi_bb229_15, &phi_bb229_16, &phi_bb229_17, &phi_bb229_18, &phi_bb229_19, &phi_bb229_23);
    ca_.Goto(&block228, phi_bb229_10, phi_bb229_11, phi_bb229_13, phi_bb229_14, phi_bb229_15, phi_bb229_16, phi_bb229_17, phi_bb229_18, phi_bb229_19, phi_bb229_23);
  }

  TNode<IntPtrT> phi_bb230_10;
  TNode<BuiltinPtr> phi_bb230_11;
  TNode<FixedArray> phi_bb230_13;
  TNode<IntPtrT> phi_bb230_14;
  TNode<IntPtrT> phi_bb230_15;
  TNode<BoolT> phi_bb230_16;
  TNode<PrimitiveHeapObject> phi_bb230_17;
  TNode<UintPtrT> phi_bb230_18;
  TNode<IntPtrT> phi_bb230_19;
  TNode<IntPtrT> phi_bb230_23;
  TNode<IntPtrT> tmp297;
  TNode<IntPtrT> tmp298;
  TNode<BoolT> tmp299;
  if (block230.is_used()) {
    ca_.Bind(&block230, &phi_bb230_10, &phi_bb230_11, &phi_bb230_13, &phi_bb230_14, &phi_bb230_15, &phi_bb230_16, &phi_bb230_17, &phi_bb230_18, &phi_bb230_19, &phi_bb230_23);
    tmp297 = CodeStubAssembler(state_).IntPtrMul(TNode<IntPtrT>{tmp3}, TNode<IntPtrT>{phi_bb230_23});
    tmp298 = CodeStubAssembler(state_).IntPtrDiv(TNode<IntPtrT>{tmp297}, TNode<IntPtrT>{tmp3});
    tmp299 = CodeStubAssembler(state_).WordNotEqual(TNode<IntPtrT>{tmp298}, TNode<IntPtrT>{phi_bb230_23});
    ca_.Branch(tmp299, &block234, std::vector<compiler::Node*>{phi_bb230_10, phi_bb230_11, phi_bb230_13, phi_bb230_14, phi_bb230_15, phi_bb230_16, phi_bb230_17, phi_bb230_18, phi_bb230_19, phi_bb230_23, phi_bb230_23}, &block235, std::vector<compiler::Node*>{phi_bb230_10, phi_bb230_11, phi_bb230_13, phi_bb230_14, phi_bb230_15, phi_bb230_16, phi_bb230_17, phi_bb230_18, phi_bb230_19, phi_bb230_23, phi_bb230_23});
  }

  TNode<IntPtrT> phi_bb234_10;
  TNode<BuiltinPtr> phi_bb234_11;
  TNode<FixedArray> phi_bb234_13;
  TNode<IntPtrT> phi_bb234_14;
  TNode<IntPtrT> phi_bb234_15;
  TNode<BoolT> phi_bb234_16;
  TNode<PrimitiveHeapObject> phi_bb234_17;
  TNode<UintPtrT> phi_bb234_18;
  TNode<IntPtrT> phi_bb234_19;
  TNode<IntPtrT> phi_bb234_23;
  TNode<IntPtrT> phi_bb234_26;
  if (block234.is_used()) {
    ca_.Bind(&block234, &phi_bb234_10, &phi_bb234_11, &phi_bb234_13, &phi_bb234_14, &phi_bb234_15, &phi_bb234_16, &phi_bb234_17, &phi_bb234_18, &phi_bb234_19, &phi_bb234_23, &phi_bb234_26);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowInvalidStringLength, p_context);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb235_10;
  TNode<BuiltinPtr> phi_bb235_11;
  TNode<FixedArray> phi_bb235_13;
  TNode<IntPtrT> phi_bb235_14;
  TNode<IntPtrT> phi_bb235_15;
  TNode<BoolT> phi_bb235_16;
  TNode<PrimitiveHeapObject> phi_bb235_17;
  TNode<UintPtrT> phi_bb235_18;
  TNode<IntPtrT> phi_bb235_19;
  TNode<IntPtrT> phi_bb235_23;
  TNode<IntPtrT> phi_bb235_26;
  TNode<IntPtrT> tmp300;
  if (block235.is_used()) {
    ca_.Bind(&block235, &phi_bb235_10, &phi_bb235_11, &phi_bb235_13, &phi_bb235_14, &phi_bb235_15, &phi_bb235_16, &phi_bb235_17, &phi_bb235_18, &phi_bb235_19, &phi_bb235_23, &phi_bb235_26);
    tmp300 = AddStringLength_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{phi_bb235_15}, TNode<IntPtrT>{tmp297});
    ca_.Branch(tmp291, &block236, std::vector<compiler::Node*>{phi_bb235_10, phi_bb235_11, phi_bb235_13, phi_bb235_14, phi_bb235_16, phi_bb235_17, phi_bb235_18, phi_bb235_19, phi_bb235_23, phi_bb235_26}, &block237, std::vector<compiler::Node*>{phi_bb235_10, phi_bb235_11, phi_bb235_13, phi_bb235_14, phi_bb235_16, phi_bb235_17, phi_bb235_18, phi_bb235_19, phi_bb235_23, phi_bb235_26});
  }

  TNode<IntPtrT> phi_bb236_10;
  TNode<BuiltinPtr> phi_bb236_11;
  TNode<FixedArray> phi_bb236_13;
  TNode<IntPtrT> phi_bb236_14;
  TNode<BoolT> phi_bb236_16;
  TNode<PrimitiveHeapObject> phi_bb236_17;
  TNode<UintPtrT> phi_bb236_18;
  TNode<IntPtrT> phi_bb236_19;
  TNode<IntPtrT> phi_bb236_23;
  TNode<IntPtrT> phi_bb236_26;
  TNode<Smi> tmp301;
  TNode<IntPtrT> tmp302;
  TNode<IntPtrT> tmp303;
  TNode<BoolT> tmp304;
  if (block236.is_used()) {
    ca_.Bind(&block236, &phi_bb236_10, &phi_bb236_11, &phi_bb236_13, &phi_bb236_14, &phi_bb236_16, &phi_bb236_17, &phi_bb236_18, &phi_bb236_19, &phi_bb236_23, &phi_bb236_26);
    tmp301 = Convert_Smi_intptr_0(state_, TNode<IntPtrT>{phi_bb236_26});
    tmp302 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{phi_bb236_13});
    tmp303 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp304 = CodeStubAssembler(state_).IntPtrGreaterThanOrEqual(TNode<IntPtrT>{phi_bb236_14}, TNode<IntPtrT>{tmp303});
    ca_.Branch(tmp304, &block239, std::vector<compiler::Node*>{phi_bb236_10, phi_bb236_11, phi_bb236_13, phi_bb236_14, phi_bb236_16, phi_bb236_17, phi_bb236_18, phi_bb236_19, phi_bb236_23, phi_bb236_26}, &block240, std::vector<compiler::Node*>{phi_bb236_10, phi_bb236_11, phi_bb236_13, phi_bb236_14, phi_bb236_16, phi_bb236_17, phi_bb236_18, phi_bb236_19, phi_bb236_23, phi_bb236_26});
  }

  TNode<IntPtrT> phi_bb240_10;
  TNode<BuiltinPtr> phi_bb240_11;
  TNode<FixedArray> phi_bb240_13;
  TNode<IntPtrT> phi_bb240_14;
  TNode<BoolT> phi_bb240_16;
  TNode<PrimitiveHeapObject> phi_bb240_17;
  TNode<UintPtrT> phi_bb240_18;
  TNode<IntPtrT> phi_bb240_19;
  TNode<IntPtrT> phi_bb240_23;
  TNode<IntPtrT> phi_bb240_26;
  if (block240.is_used()) {
    ca_.Bind(&block240, &phi_bb240_10, &phi_bb240_11, &phi_bb240_13, &phi_bb240_14, &phi_bb240_16, &phi_bb240_17, &phi_bb240_18, &phi_bb240_19, &phi_bb240_23, &phi_bb240_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 243});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index >= 1' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb239_10;
  TNode<BuiltinPtr> phi_bb239_11;
  TNode<FixedArray> phi_bb239_13;
  TNode<IntPtrT> phi_bb239_14;
  TNode<BoolT> phi_bb239_16;
  TNode<PrimitiveHeapObject> phi_bb239_17;
  TNode<UintPtrT> phi_bb239_18;
  TNode<IntPtrT> phi_bb239_19;
  TNode<IntPtrT> phi_bb239_23;
  TNode<IntPtrT> phi_bb239_26;
  TNode<BoolT> tmp305;
  if (block239.is_used()) {
    ca_.Bind(&block239, &phi_bb239_10, &phi_bb239_11, &phi_bb239_13, &phi_bb239_14, &phi_bb239_16, &phi_bb239_17, &phi_bb239_18, &phi_bb239_19, &phi_bb239_23, &phi_bb239_26);
    tmp305 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{phi_bb239_14}, TNode<IntPtrT>{tmp302});
    ca_.Branch(tmp305, &block241, std::vector<compiler::Node*>{phi_bb239_10, phi_bb239_11, phi_bb239_13, phi_bb239_14, phi_bb239_16, phi_bb239_17, phi_bb239_18, phi_bb239_19, phi_bb239_23, phi_bb239_26}, &block242, std::vector<compiler::Node*>{phi_bb239_10, phi_bb239_11, phi_bb239_13, phi_bb239_14, phi_bb239_16, phi_bb239_17, phi_bb239_18, phi_bb239_19, phi_bb239_23, phi_bb239_26});
  }

  TNode<IntPtrT> phi_bb242_10;
  TNode<BuiltinPtr> phi_bb242_11;
  TNode<FixedArray> phi_bb242_13;
  TNode<IntPtrT> phi_bb242_14;
  TNode<BoolT> phi_bb242_16;
  TNode<PrimitiveHeapObject> phi_bb242_17;
  TNode<UintPtrT> phi_bb242_18;
  TNode<IntPtrT> phi_bb242_19;
  TNode<IntPtrT> phi_bb242_23;
  TNode<IntPtrT> phi_bb242_26;
  if (block242.is_used()) {
    ca_.Bind(&block242, &phi_bb242_10, &phi_bb242_11, &phi_bb242_13, &phi_bb242_14, &phi_bb242_16, &phi_bb242_17, &phi_bb242_18, &phi_bb242_19, &phi_bb242_23, &phi_bb242_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 244});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.index <= length' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb241_10;
  TNode<BuiltinPtr> phi_bb241_11;
  TNode<FixedArray> phi_bb241_13;
  TNode<IntPtrT> phi_bb241_14;
  TNode<BoolT> phi_bb241_16;
  TNode<PrimitiveHeapObject> phi_bb241_17;
  TNode<UintPtrT> phi_bb241_18;
  TNode<IntPtrT> phi_bb241_19;
  TNode<IntPtrT> phi_bb241_23;
  TNode<IntPtrT> phi_bb241_26;
  TNode<BoolT> tmp306;
  if (block241.is_used()) {
    ca_.Bind(&block241, &phi_bb241_10, &phi_bb241_11, &phi_bb241_13, &phi_bb241_14, &phi_bb241_16, &phi_bb241_17, &phi_bb241_18, &phi_bb241_19, &phi_bb241_23, &phi_bb241_26);
    tmp306 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{phi_bb241_14}, TNode<IntPtrT>{tmp302});
    ca_.Branch(tmp306, &block243, std::vector<compiler::Node*>{phi_bb241_10, phi_bb241_11, phi_bb241_13, phi_bb241_14, phi_bb241_16, phi_bb241_17, phi_bb241_18, phi_bb241_19, phi_bb241_23, phi_bb241_26}, &block244, std::vector<compiler::Node*>{phi_bb241_10, phi_bb241_11, phi_bb241_13, phi_bb241_14, phi_bb241_16, phi_bb241_17, phi_bb241_18, phi_bb241_19, phi_bb241_23, phi_bb241_26});
  }

  TNode<IntPtrT> phi_bb243_10;
  TNode<BuiltinPtr> phi_bb243_11;
  TNode<FixedArray> phi_bb243_13;
  TNode<IntPtrT> phi_bb243_14;
  TNode<BoolT> phi_bb243_16;
  TNode<PrimitiveHeapObject> phi_bb243_17;
  TNode<UintPtrT> phi_bb243_18;
  TNode<IntPtrT> phi_bb243_19;
  TNode<IntPtrT> phi_bb243_23;
  TNode<IntPtrT> phi_bb243_26;
  TNode<Union<HeapObject, TaggedIndex>> tmp307;
  TNode<IntPtrT> tmp308;
  TNode<IntPtrT> tmp309;
  TNode<IntPtrT> tmp310;
  TNode<IntPtrT> tmp311;
  TNode<UintPtrT> tmp312;
  TNode<UintPtrT> tmp313;
  TNode<BoolT> tmp314;
  if (block243.is_used()) {
    ca_.Bind(&block243, &phi_bb243_10, &phi_bb243_11, &phi_bb243_13, &phi_bb243_14, &phi_bb243_16, &phi_bb243_17, &phi_bb243_18, &phi_bb243_19, &phi_bb243_23, &phi_bb243_26);
    std::tie(tmp307, tmp308, tmp309) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb243_13}).Flatten();
    tmp310 = FromConstexpr_intptr_constexpr_int31_0(state_, 1);
    tmp311 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{phi_bb243_14}, TNode<IntPtrT>{tmp310});
    tmp312 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{phi_bb243_14});
    tmp313 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp309});
    tmp314 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp312}, TNode<UintPtrT>{tmp313});
    ca_.Branch(tmp314, &block250, std::vector<compiler::Node*>{phi_bb243_10, phi_bb243_11, phi_bb243_13, phi_bb243_16, phi_bb243_17, phi_bb243_18, phi_bb243_19, phi_bb243_23, phi_bb243_26, phi_bb243_13, phi_bb243_14, phi_bb243_14, phi_bb243_14, phi_bb243_14}, &block251, std::vector<compiler::Node*>{phi_bb243_10, phi_bb243_11, phi_bb243_13, phi_bb243_16, phi_bb243_17, phi_bb243_18, phi_bb243_19, phi_bb243_23, phi_bb243_26, phi_bb243_13, phi_bb243_14, phi_bb243_14, phi_bb243_14, phi_bb243_14});
  }

  TNode<IntPtrT> phi_bb250_10;
  TNode<BuiltinPtr> phi_bb250_11;
  TNode<FixedArray> phi_bb250_13;
  TNode<BoolT> phi_bb250_16;
  TNode<PrimitiveHeapObject> phi_bb250_17;
  TNode<UintPtrT> phi_bb250_18;
  TNode<IntPtrT> phi_bb250_19;
  TNode<IntPtrT> phi_bb250_23;
  TNode<IntPtrT> phi_bb250_26;
  TNode<FixedArray> phi_bb250_31;
  TNode<IntPtrT> phi_bb250_35;
  TNode<IntPtrT> phi_bb250_36;
  TNode<IntPtrT> phi_bb250_40;
  TNode<IntPtrT> phi_bb250_41;
  TNode<IntPtrT> tmp315;
  TNode<IntPtrT> tmp316;
  TNode<Union<HeapObject, TaggedIndex>> tmp317;
  TNode<IntPtrT> tmp318;
  if (block250.is_used()) {
    ca_.Bind(&block250, &phi_bb250_10, &phi_bb250_11, &phi_bb250_13, &phi_bb250_16, &phi_bb250_17, &phi_bb250_18, &phi_bb250_19, &phi_bb250_23, &phi_bb250_26, &phi_bb250_31, &phi_bb250_35, &phi_bb250_36, &phi_bb250_40, &phi_bb250_41);
    tmp315 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{phi_bb250_41});
    tmp316 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp308}, TNode<IntPtrT>{tmp315});
    std::tie(tmp317, tmp318) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp307}, TNode<IntPtrT>{tmp316}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp317, tmp318}, tmp301);
    ca_.Goto(&block245, phi_bb250_10, phi_bb250_11, phi_bb250_13, tmp311, phi_bb250_16, phi_bb250_17, phi_bb250_18, phi_bb250_19, phi_bb250_23, phi_bb250_26);
  }

  TNode<IntPtrT> phi_bb251_10;
  TNode<BuiltinPtr> phi_bb251_11;
  TNode<FixedArray> phi_bb251_13;
  TNode<BoolT> phi_bb251_16;
  TNode<PrimitiveHeapObject> phi_bb251_17;
  TNode<UintPtrT> phi_bb251_18;
  TNode<IntPtrT> phi_bb251_19;
  TNode<IntPtrT> phi_bb251_23;
  TNode<IntPtrT> phi_bb251_26;
  TNode<FixedArray> phi_bb251_31;
  TNode<IntPtrT> phi_bb251_35;
  TNode<IntPtrT> phi_bb251_36;
  TNode<IntPtrT> phi_bb251_40;
  TNode<IntPtrT> phi_bb251_41;
  if (block251.is_used()) {
    ca_.Bind(&block251, &phi_bb251_10, &phi_bb251_11, &phi_bb251_13, &phi_bb251_16, &phi_bb251_17, &phi_bb251_18, &phi_bb251_19, &phi_bb251_23, &phi_bb251_26, &phi_bb251_31, &phi_bb251_35, &phi_bb251_36, &phi_bb251_40, &phi_bb251_41);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb244_10;
  TNode<BuiltinPtr> phi_bb244_11;
  TNode<FixedArray> phi_bb244_13;
  TNode<IntPtrT> phi_bb244_14;
  TNode<BoolT> phi_bb244_16;
  TNode<PrimitiveHeapObject> phi_bb244_17;
  TNode<UintPtrT> phi_bb244_18;
  TNode<IntPtrT> phi_bb244_19;
  TNode<IntPtrT> phi_bb244_23;
  TNode<IntPtrT> phi_bb244_26;
  TNode<IntPtrT> tmp319;
  TNode<IntPtrT> tmp320;
  TNode<BoolT> tmp321;
  if (block244.is_used()) {
    ca_.Bind(&block244, &phi_bb244_10, &phi_bb244_11, &phi_bb244_13, &phi_bb244_14, &phi_bb244_16, &phi_bb244_17, &phi_bb244_18, &phi_bb244_19, &phi_bb244_23, &phi_bb244_26);
    tmp319 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp302});
    tmp320 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    tmp321 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp319}, TNode<IntPtrT>{tmp320});
    ca_.Branch(tmp321, &block254, std::vector<compiler::Node*>{phi_bb244_10, phi_bb244_11, phi_bb244_13, phi_bb244_14, phi_bb244_16, phi_bb244_17, phi_bb244_18, phi_bb244_19, phi_bb244_23, phi_bb244_26}, &block255, std::vector<compiler::Node*>{phi_bb244_10, phi_bb244_11, phi_bb244_13, phi_bb244_14, phi_bb244_16, phi_bb244_17, phi_bb244_18, phi_bb244_19, phi_bb244_23, phi_bb244_26});
  }

  TNode<IntPtrT> phi_bb254_10;
  TNode<BuiltinPtr> phi_bb254_11;
  TNode<FixedArray> phi_bb254_13;
  TNode<IntPtrT> phi_bb254_14;
  TNode<BoolT> phi_bb254_16;
  TNode<PrimitiveHeapObject> phi_bb254_17;
  TNode<UintPtrT> phi_bb254_18;
  TNode<IntPtrT> phi_bb254_19;
  TNode<IntPtrT> phi_bb254_23;
  TNode<IntPtrT> phi_bb254_26;
  TNode<IntPtrT> tmp322;
  if (block254.is_used()) {
    ca_.Bind(&block254, &phi_bb254_10, &phi_bb254_11, &phi_bb254_13, &phi_bb254_14, &phi_bb254_16, &phi_bb254_17, &phi_bb254_18, &phi_bb254_19, &phi_bb254_23, &phi_bb254_26);
    tmp322 = FromConstexpr_intptr_constexpr_int31_0(state_, kMaxBufferChunkSize_0(state_));
    ca_.Goto(&block256, phi_bb254_10, phi_bb254_11, phi_bb254_13, phi_bb254_14, phi_bb254_16, phi_bb254_17, phi_bb254_18, phi_bb254_19, phi_bb254_23, phi_bb254_26, tmp322);
  }

  TNode<IntPtrT> phi_bb255_10;
  TNode<BuiltinPtr> phi_bb255_11;
  TNode<FixedArray> phi_bb255_13;
  TNode<IntPtrT> phi_bb255_14;
  TNode<BoolT> phi_bb255_16;
  TNode<PrimitiveHeapObject> phi_bb255_17;
  TNode<UintPtrT> phi_bb255_18;
  TNode<IntPtrT> phi_bb255_19;
  TNode<IntPtrT> phi_bb255_23;
  TNode<IntPtrT> phi_bb255_26;
  if (block255.is_used()) {
    ca_.Bind(&block255, &phi_bb255_10, &phi_bb255_11, &phi_bb255_13, &phi_bb255_14, &phi_bb255_16, &phi_bb255_17, &phi_bb255_18, &phi_bb255_19, &phi_bb255_23, &phi_bb255_26);
    ca_.Goto(&block256, phi_bb255_10, phi_bb255_11, phi_bb255_13, phi_bb255_14, phi_bb255_16, phi_bb255_17, phi_bb255_18, phi_bb255_19, phi_bb255_23, phi_bb255_26, tmp319);
  }

  TNode<IntPtrT> phi_bb256_10;
  TNode<BuiltinPtr> phi_bb256_11;
  TNode<FixedArray> phi_bb256_13;
  TNode<IntPtrT> phi_bb256_14;
  TNode<BoolT> phi_bb256_16;
  TNode<PrimitiveHeapObject> phi_bb256_17;
  TNode<UintPtrT> phi_bb256_18;
  TNode<IntPtrT> phi_bb256_19;
  TNode<IntPtrT> phi_bb256_23;
  TNode<IntPtrT> phi_bb256_26;
  TNode<IntPtrT> phi_bb256_32;
  TNode<IntPtrT> tmp323;
  TNode<BoolT> tmp324;
  if (block256.is_used()) {
    ca_.Bind(&block256, &phi_bb256_10, &phi_bb256_11, &phi_bb256_13, &phi_bb256_14, &phi_bb256_16, &phi_bb256_17, &phi_bb256_18, &phi_bb256_19, &phi_bb256_23, &phi_bb256_26, &phi_bb256_32);
    tmp323 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp324 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{phi_bb256_32}, TNode<IntPtrT>{tmp323});
    ca_.Branch(tmp324, &block258, std::vector<compiler::Node*>{phi_bb256_10, phi_bb256_11, phi_bb256_13, phi_bb256_14, phi_bb256_16, phi_bb256_17, phi_bb256_18, phi_bb256_19, phi_bb256_23, phi_bb256_26}, &block259, std::vector<compiler::Node*>{phi_bb256_10, phi_bb256_11, phi_bb256_13, phi_bb256_14, phi_bb256_16, phi_bb256_17, phi_bb256_18, phi_bb256_19, phi_bb256_23, phi_bb256_26});
  }

  TNode<IntPtrT> phi_bb259_10;
  TNode<BuiltinPtr> phi_bb259_11;
  TNode<FixedArray> phi_bb259_13;
  TNode<IntPtrT> phi_bb259_14;
  TNode<BoolT> phi_bb259_16;
  TNode<PrimitiveHeapObject> phi_bb259_17;
  TNode<UintPtrT> phi_bb259_18;
  TNode<IntPtrT> phi_bb259_19;
  TNode<IntPtrT> phi_bb259_23;
  TNode<IntPtrT> phi_bb259_26;
  if (block259.is_used()) {
    ca_.Bind(&block259, &phi_bb259_10, &phi_bb259_11, &phi_bb259_13, &phi_bb259_14, &phi_bb259_16, &phi_bb259_17, &phi_bb259_18, &phi_bb259_19, &phi_bb259_23, &phi_bb259_26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 253});
      CodeStubAssembler(state_).FailAssert("Torque assert 'cappedNewChunkLength > 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> phi_bb258_10;
  TNode<BuiltinPtr> phi_bb258_11;
  TNode<FixedArray> phi_bb258_13;
  TNode<IntPtrT> phi_bb258_14;
  TNode<BoolT> phi_bb258_16;
  TNode<PrimitiveHeapObject> phi_bb258_17;
  TNode<UintPtrT> phi_bb258_18;
  TNode<IntPtrT> phi_bb258_19;
  TNode<IntPtrT> phi_bb258_23;
  TNode<IntPtrT> phi_bb258_26;
  TNode<FixedArray> tmp325;
  TNode<Union<HeapObject, TaggedIndex>> tmp326;
  TNode<IntPtrT> tmp327;
  TNode<IntPtrT> tmp328;
  TNode<UintPtrT> tmp329;
  TNode<IntPtrT> tmp330;
  TNode<UintPtrT> tmp331;
  TNode<UintPtrT> tmp332;
  TNode<BoolT> tmp333;
  if (block258.is_used()) {
    ca_.Bind(&block258, &phi_bb258_10, &phi_bb258_11, &phi_bb258_13, &phi_bb258_14, &phi_bb258_16, &phi_bb258_17, &phi_bb258_18, &phi_bb258_19, &phi_bb258_23, &phi_bb258_26);
    tmp325 = CodeStubAssembler(state_).AllocateZeroedFixedArray(TNode<IntPtrT>{phi_bb256_32});
    std::tie(tmp326, tmp327, tmp328) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb258_13}).Flatten();
    tmp329 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp330 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp329});
    tmp331 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp330});
    tmp332 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp328});
    tmp333 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp331}, TNode<UintPtrT>{tmp332});
    ca_.Branch(tmp333, &block265, std::vector<compiler::Node*>{phi_bb258_10, phi_bb258_11, phi_bb258_13, phi_bb258_14, phi_bb258_16, phi_bb258_17, phi_bb258_18, phi_bb258_19, phi_bb258_23, phi_bb258_26, phi_bb258_13}, &block266, std::vector<compiler::Node*>{phi_bb258_10, phi_bb258_11, phi_bb258_13, phi_bb258_14, phi_bb258_16, phi_bb258_17, phi_bb258_18, phi_bb258_19, phi_bb258_23, phi_bb258_26, phi_bb258_13});
  }

  TNode<IntPtrT> phi_bb265_10;
  TNode<BuiltinPtr> phi_bb265_11;
  TNode<FixedArray> phi_bb265_13;
  TNode<IntPtrT> phi_bb265_14;
  TNode<BoolT> phi_bb265_16;
  TNode<PrimitiveHeapObject> phi_bb265_17;
  TNode<UintPtrT> phi_bb265_18;
  TNode<IntPtrT> phi_bb265_19;
  TNode<IntPtrT> phi_bb265_23;
  TNode<IntPtrT> phi_bb265_26;
  TNode<FixedArray> phi_bb265_34;
  TNode<IntPtrT> tmp334;
  TNode<IntPtrT> tmp335;
  TNode<Union<HeapObject, TaggedIndex>> tmp336;
  TNode<IntPtrT> tmp337;
  TNode<Union<HeapObject, TaggedIndex>> tmp338;
  TNode<IntPtrT> tmp339;
  TNode<IntPtrT> tmp340;
  TNode<UintPtrT> tmp341;
  TNode<IntPtrT> tmp342;
  TNode<UintPtrT> tmp343;
  TNode<UintPtrT> tmp344;
  TNode<BoolT> tmp345;
  if (block265.is_used()) {
    ca_.Bind(&block265, &phi_bb265_10, &phi_bb265_11, &phi_bb265_13, &phi_bb265_14, &phi_bb265_16, &phi_bb265_17, &phi_bb265_18, &phi_bb265_19, &phi_bb265_23, &phi_bb265_26, &phi_bb265_34);
    tmp334 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp330});
    tmp335 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp327}, TNode<IntPtrT>{tmp334});
    std::tie(tmp336, tmp337) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp326}, TNode<IntPtrT>{tmp335}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp336, tmp337}, tmp325);
    std::tie(tmp338, tmp339, tmp340) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp325}).Flatten();
    tmp341 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp342 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp341});
    tmp343 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp342});
    tmp344 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp340});
    tmp345 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp343}, TNode<UintPtrT>{tmp344});
    ca_.Branch(tmp345, &block274, std::vector<compiler::Node*>{phi_bb265_10, phi_bb265_11, phi_bb265_13, phi_bb265_14, phi_bb265_16, phi_bb265_17, phi_bb265_18, phi_bb265_19, phi_bb265_23, phi_bb265_26}, &block275, std::vector<compiler::Node*>{phi_bb265_10, phi_bb265_11, phi_bb265_13, phi_bb265_14, phi_bb265_16, phi_bb265_17, phi_bb265_18, phi_bb265_19, phi_bb265_23, phi_bb265_26});
  }

  TNode<IntPtrT> phi_bb266_10;
  TNode<BuiltinPtr> phi_bb266_11;
  TNode<FixedArray> phi_bb266_13;
  TNode<IntPtrT> phi_bb266_14;
  TNode<BoolT> phi_bb266_16;
  TNode<PrimitiveHeapObject> phi_bb266_17;
  TNode<UintPtrT> phi_bb266_18;
  TNode<IntPtrT> phi_bb266_19;
  TNode<IntPtrT> phi_bb266_23;
  TNode<IntPtrT> phi_bb266_26;
  TNode<FixedArray> phi_bb266_34;
  if (block266.is_used()) {
    ca_.Bind(&block266, &phi_bb266_10, &phi_bb266_11, &phi_bb266_13, &phi_bb266_14, &phi_bb266_16, &phi_bb266_17, &phi_bb266_18, &phi_bb266_19, &phi_bb266_23, &phi_bb266_26, &phi_bb266_34);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb274_10;
  TNode<BuiltinPtr> phi_bb274_11;
  TNode<FixedArray> phi_bb274_13;
  TNode<IntPtrT> phi_bb274_14;
  TNode<BoolT> phi_bb274_16;
  TNode<PrimitiveHeapObject> phi_bb274_17;
  TNode<UintPtrT> phi_bb274_18;
  TNode<IntPtrT> phi_bb274_19;
  TNode<IntPtrT> phi_bb274_23;
  TNode<IntPtrT> phi_bb274_26;
  TNode<IntPtrT> tmp346;
  TNode<IntPtrT> tmp347;
  TNode<Union<HeapObject, TaggedIndex>> tmp348;
  TNode<IntPtrT> tmp349;
  TNode<Undefined> tmp350;
  TNode<Union<HeapObject, TaggedIndex>> tmp351;
  TNode<IntPtrT> tmp352;
  TNode<IntPtrT> tmp353;
  TNode<UintPtrT> tmp354;
  TNode<IntPtrT> tmp355;
  TNode<UintPtrT> tmp356;
  TNode<UintPtrT> tmp357;
  TNode<BoolT> tmp358;
  if (block274.is_used()) {
    ca_.Bind(&block274, &phi_bb274_10, &phi_bb274_11, &phi_bb274_13, &phi_bb274_14, &phi_bb274_16, &phi_bb274_17, &phi_bb274_18, &phi_bb274_19, &phi_bb274_23, &phi_bb274_26);
    tmp346 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp342});
    tmp347 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp339}, TNode<IntPtrT>{tmp346});
    std::tie(tmp348, tmp349) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp338}, TNode<IntPtrT>{tmp347}).Flatten();
    tmp350 = Undefined_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp348, tmp349}, tmp350);
    std::tie(tmp351, tmp352, tmp353) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp325}).Flatten();
    tmp354 = FromConstexpr_uintptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp355 = Convert_intptr_uintptr_0(state_, TNode<UintPtrT>{tmp354});
    tmp356 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp355});
    tmp357 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp353});
    tmp358 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp356}, TNode<UintPtrT>{tmp357});
    ca_.Branch(tmp358, &block283, std::vector<compiler::Node*>{phi_bb274_10, phi_bb274_11, phi_bb274_13, phi_bb274_14, phi_bb274_16, phi_bb274_17, phi_bb274_18, phi_bb274_19, phi_bb274_23, phi_bb274_26}, &block284, std::vector<compiler::Node*>{phi_bb274_10, phi_bb274_11, phi_bb274_13, phi_bb274_14, phi_bb274_16, phi_bb274_17, phi_bb274_18, phi_bb274_19, phi_bb274_23, phi_bb274_26});
  }

  TNode<IntPtrT> phi_bb275_10;
  TNode<BuiltinPtr> phi_bb275_11;
  TNode<FixedArray> phi_bb275_13;
  TNode<IntPtrT> phi_bb275_14;
  TNode<BoolT> phi_bb275_16;
  TNode<PrimitiveHeapObject> phi_bb275_17;
  TNode<UintPtrT> phi_bb275_18;
  TNode<IntPtrT> phi_bb275_19;
  TNode<IntPtrT> phi_bb275_23;
  TNode<IntPtrT> phi_bb275_26;
  if (block275.is_used()) {
    ca_.Bind(&block275, &phi_bb275_10, &phi_bb275_11, &phi_bb275_13, &phi_bb275_14, &phi_bb275_16, &phi_bb275_17, &phi_bb275_18, &phi_bb275_19, &phi_bb275_23, &phi_bb275_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb283_10;
  TNode<BuiltinPtr> phi_bb283_11;
  TNode<FixedArray> phi_bb283_13;
  TNode<IntPtrT> phi_bb283_14;
  TNode<BoolT> phi_bb283_16;
  TNode<PrimitiveHeapObject> phi_bb283_17;
  TNode<UintPtrT> phi_bb283_18;
  TNode<IntPtrT> phi_bb283_19;
  TNode<IntPtrT> phi_bb283_23;
  TNode<IntPtrT> phi_bb283_26;
  TNode<IntPtrT> tmp359;
  TNode<IntPtrT> tmp360;
  TNode<Union<HeapObject, TaggedIndex>> tmp361;
  TNode<IntPtrT> tmp362;
  TNode<IntPtrT> tmp363;
  if (block283.is_used()) {
    ca_.Bind(&block283, &phi_bb283_10, &phi_bb283_11, &phi_bb283_13, &phi_bb283_14, &phi_bb283_16, &phi_bb283_17, &phi_bb283_18, &phi_bb283_19, &phi_bb283_23, &phi_bb283_26);
    tmp359 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp355});
    tmp360 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp352}, TNode<IntPtrT>{tmp359});
    std::tie(tmp361, tmp362) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp351}, TNode<IntPtrT>{tmp360}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp361, tmp362}, tmp301);
    tmp363 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    ca_.Goto(&block245, phi_bb283_10, phi_bb283_11, tmp325, tmp363, phi_bb283_16, phi_bb283_17, phi_bb283_18, phi_bb283_19, phi_bb283_23, phi_bb283_26);
  }

  TNode<IntPtrT> phi_bb284_10;
  TNode<BuiltinPtr> phi_bb284_11;
  TNode<FixedArray> phi_bb284_13;
  TNode<IntPtrT> phi_bb284_14;
  TNode<BoolT> phi_bb284_16;
  TNode<PrimitiveHeapObject> phi_bb284_17;
  TNode<UintPtrT> phi_bb284_18;
  TNode<IntPtrT> phi_bb284_19;
  TNode<IntPtrT> phi_bb284_23;
  TNode<IntPtrT> phi_bb284_26;
  if (block284.is_used()) {
    ca_.Bind(&block284, &phi_bb284_10, &phi_bb284_11, &phi_bb284_13, &phi_bb284_14, &phi_bb284_16, &phi_bb284_17, &phi_bb284_18, &phi_bb284_19, &phi_bb284_23, &phi_bb284_26);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:117:62");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> phi_bb245_10;
  TNode<BuiltinPtr> phi_bb245_11;
  TNode<FixedArray> phi_bb245_13;
  TNode<IntPtrT> phi_bb245_14;
  TNode<BoolT> phi_bb245_16;
  TNode<PrimitiveHeapObject> phi_bb245_17;
  TNode<UintPtrT> phi_bb245_18;
  TNode<IntPtrT> phi_bb245_19;
  TNode<IntPtrT> phi_bb245_23;
  TNode<IntPtrT> phi_bb245_26;
  TNode<Null> tmp364;
  if (block245.is_used()) {
    ca_.Bind(&block245, &phi_bb245_10, &phi_bb245_11, &phi_bb245_13, &phi_bb245_14, &phi_bb245_16, &phi_bb245_17, &phi_bb245_18, &phi_bb245_19, &phi_bb245_23, &phi_bb245_26);
    tmp364 = Null_0(state_);
    ca_.Goto(&block237, phi_bb245_10, phi_bb245_11, phi_bb245_13, phi_bb245_14, phi_bb245_16, tmp364, phi_bb245_18, phi_bb245_19, phi_bb245_23, phi_bb245_26);
  }

  TNode<IntPtrT> phi_bb237_10;
  TNode<BuiltinPtr> phi_bb237_11;
  TNode<FixedArray> phi_bb237_13;
  TNode<IntPtrT> phi_bb237_14;
  TNode<BoolT> phi_bb237_16;
  TNode<PrimitiveHeapObject> phi_bb237_17;
  TNode<UintPtrT> phi_bb237_18;
  TNode<IntPtrT> phi_bb237_19;
  TNode<IntPtrT> phi_bb237_23;
  TNode<IntPtrT> phi_bb237_26;
  if (block237.is_used()) {
    ca_.Bind(&block237, &phi_bb237_10, &phi_bb237_11, &phi_bb237_13, &phi_bb237_14, &phi_bb237_16, &phi_bb237_17, &phi_bb237_18, &phi_bb237_19, &phi_bb237_23, &phi_bb237_26);
    ca_.Goto(&block228, phi_bb237_10, phi_bb237_11, phi_bb237_13, phi_bb237_14, tmp300, phi_bb237_16, phi_bb237_17, phi_bb237_18, phi_bb237_19, phi_bb237_23);
  }

  TNode<IntPtrT> phi_bb228_10;
  TNode<BuiltinPtr> phi_bb228_11;
  TNode<FixedArray> phi_bb228_13;
  TNode<IntPtrT> phi_bb228_14;
  TNode<IntPtrT> phi_bb228_15;
  TNode<BoolT> phi_bb228_16;
  TNode<PrimitiveHeapObject> phi_bb228_17;
  TNode<UintPtrT> phi_bb228_18;
  TNode<IntPtrT> phi_bb228_19;
  TNode<IntPtrT> phi_bb228_23;
  TNode<String> tmp365;
  if (block228.is_used()) {
    ca_.Bind(&block228, &phi_bb228_10, &phi_bb228_11, &phi_bb228_13, &phi_bb228_14, &phi_bb228_15, &phi_bb228_16, &phi_bb228_17, &phi_bb228_18, &phi_bb228_19, &phi_bb228_23);
    tmp365 = BufferJoin_0(state_, TNode<Context>{p_context}, TorqueStructBuffer_0{TNode<FixedArray>{tmp5}, TNode<FixedArray>{phi_bb228_13}, TNode<IntPtrT>{phi_bb228_14}, TNode<IntPtrT>{phi_bb228_15}, TNode<BoolT>{phi_bb228_16}, TNode<PrimitiveHeapObject>{phi_bb228_17}}, TNode<String>{p_sep});
    ca_.Goto(&block287);
  }

    ca_.Bind(&block287);
  return TNode<String>{tmp365};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=644&c=16
TorqueStructReference_FixedArray_OR_Undefined_0 NativeContextSlot_Context_FixedArray_OR_Undefined_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1) = NativeContextSlot_FixedArray_OR_Undefined_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{p_index}).Flatten();
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TorqueStructReference_FixedArray_OR_Undefined_0{TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp1}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=680&c=7
TNode<FixedArray> StoreAndGrowFixedArray_JSReceiver_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_fixedArray, TNode<IntPtrT> p_index, TNode<JSReceiver> p_element) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{p_fixedArray});
    tmp1 = CodeStubAssembler(state_).IntPtrLessThanOrEqual(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp1, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 159});
      CodeStubAssembler(state_).FailAssert("Torque assert 'index <= length' failed", pos_stack);
    }
  }

  TNode<BoolT> tmp2;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp2 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp0});
    ca_.Branch(tmp2, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp3;
  TNode<IntPtrT> tmp4;
  TNode<IntPtrT> tmp5;
  TNode<UintPtrT> tmp6;
  TNode<UintPtrT> tmp7;
  TNode<BoolT> tmp8;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    std::tie(tmp3, tmp4, tmp5) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{p_fixedArray}).Flatten();
    tmp6 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp7 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp5});
    tmp8 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp6}, TNode<UintPtrT>{tmp7});
    ca_.Branch(tmp8, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp9 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{p_index});
    tmp10 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp4}, TNode<IntPtrT>{tmp9});
    std::tie(tmp11, tmp12) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp3}, TNode<IntPtrT>{tmp10}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp11, tmp12}, p_element);
    ca_.Goto(&block1, p_fixedArray);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp13;
  TNode<BoolT> tmp14;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp13 = CodeStubAssembler(state_).CalculateNewElementsCapacity(TNode<IntPtrT>{tmp0});
    tmp14 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{p_index}, TNode<IntPtrT>{tmp13});
    ca_.Branch(tmp14, &block15, std::vector<compiler::Node*>{}, &block16, std::vector<compiler::Node*>{});
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-join.tq", 166});
      CodeStubAssembler(state_).FailAssert("Torque assert 'index < newLength' failed", pos_stack);
    }
  }

  TNode<TheHole> tmp15;
  TNode<IntPtrT> tmp16;
  TNode<FixedArray> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<IntPtrT> tmp20;
  TNode<UintPtrT> tmp21;
  TNode<UintPtrT> tmp22;
  TNode<BoolT> tmp23;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp15 = TheHole_0(state_);
    tmp16 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp17 = ExtractFixedArray_0(state_, TNode<FixedArray>{p_fixedArray}, TNode<IntPtrT>{tmp16}, TNode<IntPtrT>{tmp0}, TNode<IntPtrT>{tmp13}, TNode<Hole>{tmp15});
    std::tie(tmp18, tmp19, tmp20) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp17}).Flatten();
    tmp21 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp22 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp20});
    tmp23 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp21}, TNode<UintPtrT>{tmp22});
    ca_.Branch(tmp23, &block21, std::vector<compiler::Node*>{}, &block22, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<Union<HeapObject, TaggedIndex>> tmp26;
  TNode<IntPtrT> tmp27;
  if (block21.is_used()) {
    ca_.Bind(&block21);
    tmp24 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{p_index});
    tmp25 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp19}, TNode<IntPtrT>{tmp24});
    std::tie(tmp26, tmp27) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp18}, TNode<IntPtrT>{tmp25}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp26, tmp27}, p_element);
    ca_.Goto(&block1, tmp17);
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<FixedArray> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block25, phi_bb1_3);
  }

  TNode<FixedArray> phi_bb25_3;
    ca_.Bind(&block25, &phi_bb25_3);
  return TNode<FixedArray>{phi_bb25_3};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=832&c=10
TNode<JSAny> CycleProtectedArrayJoin_JSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, bool p_useToLocaleString, TNode<JSReceiver> p_o, TNode<Number> p_len, TNode<String> p_sep, TNode<JSAny> p_locales, TNode<JSAny> p_options) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = NumberIsGreaterThan_0(state_, TNode<Number>{p_len}, TNode<Number>{tmp0});
    ca_.Branch(tmp1, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = JoinStackPushInline_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_o});
    ca_.Goto(&block6, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block6, tmp3);
  }

  TNode<BoolT> phi_bb6_7;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7);
    ca_.Branch(phi_bb6_7, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp4;
      TNode<JSAny> tmp6;
      TNode<JSAny> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    compiler::CodeAssemblerExceptionHandlerLabel catch5__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch5__label);
    tmp4 = ArrayJoin_JSArray_0(state_, TNode<Context>{p_context}, p_useToLocaleString, TNode<JSReceiver>{p_o}, TNode<String>{p_sep}, TNode<Number>{p_len}, TNode<JSAny>{p_locales}, TNode<JSAny>{p_options});
    }
    if (catch5__label.is_used()) {
      compiler::CodeAssemblerLabel catch5_skip(&ca_);
      ca_.Goto(&catch5_skip);
      ca_.Bind(&catch5__label, &tmp6);
      ca_.Goto(&block10);
      ca_.Bind(&catch5_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch7__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch7__label);
    JoinStackPopInline_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_o});
    }
    if (catch7__label.is_used()) {
      compiler::CodeAssemblerLabel catch7_skip(&ca_);
      ca_.Goto(&catch7_skip);
      ca_.Bind(&catch7__label, &tmp8);
      ca_.Goto(&block11);
      ca_.Bind(&catch7_skip);
    }
    ca_.Goto(&block1, tmp4);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp9 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block9, tmp6, tmp9);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp10;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp10 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block9, tmp8, tmp10);
  }

  TNode<JSAny> phi_bb9_6;
  TNode<Union<JSMessageObject, TheHole>> phi_bb9_7;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_6, &phi_bb9_7);
    JoinStackPopInline_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_o});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, p_context, phi_bb9_6, phi_bb9_7);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp11 = kEmptyString_0(state_);
    ca_.Goto(&block1, tmp11);
  }

  TNode<JSAny> phi_bb1_6;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_6);
    ca_.Goto(&block12);
  }

    ca_.Bind(&block12);
  return TNode<JSAny>{phi_bb1_6};
}

// https://crsrc.org/c/v8/src/builtins/array-join.tq?l=919&c=10
TNode<JSAny> CycleProtectedArrayJoin_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, bool p_useToLocaleString, TNode<JSReceiver> p_o, TNode<Number> p_len, TNode<String> p_sep, TNode<JSAny> p_locales, TNode<JSAny> p_options) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, Union<JSMessageObject, TheHole>> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Number> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = NumberIsGreaterThan_0(state_, TNode<Number>{p_len}, TNode<Number>{tmp0});
    ca_.Branch(tmp1, &block4, std::vector<compiler::Node*>{}, &block5, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp2 = JoinStackPushInline_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_o});
    ca_.Goto(&block6, tmp2);
  }

  TNode<BoolT> tmp3;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp3 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block6, tmp3);
  }

  TNode<BoolT> phi_bb6_7;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_7);
    ca_.Branch(phi_bb6_7, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp4;
      TNode<JSAny> tmp6;
      TNode<JSAny> tmp8;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    compiler::CodeAssemblerExceptionHandlerLabel catch5__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch5__label);
    tmp4 = ArrayJoin_JSTypedArray_0(state_, TNode<Context>{p_context}, p_useToLocaleString, TNode<JSReceiver>{p_o}, TNode<String>{p_sep}, TNode<Number>{p_len}, TNode<JSAny>{p_locales}, TNode<JSAny>{p_options});
    }
    if (catch5__label.is_used()) {
      compiler::CodeAssemblerLabel catch5_skip(&ca_);
      ca_.Goto(&catch5_skip);
      ca_.Bind(&catch5__label, &tmp6);
      ca_.Goto(&block10);
      ca_.Bind(&catch5_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch7__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch7__label);
    JoinStackPopInline_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_o});
    }
    if (catch7__label.is_used()) {
      compiler::CodeAssemblerLabel catch7_skip(&ca_);
      ca_.Goto(&catch7_skip);
      ca_.Bind(&catch7__label, &tmp8);
      ca_.Goto(&block11);
      ca_.Bind(&catch7_skip);
    }
    ca_.Goto(&block1, tmp4);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp9;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp9 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block9, tmp6, tmp9);
  }

  TNode<Union<JSMessageObject, TheHole>> tmp10;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp10 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block9, tmp8, tmp10);
  }

  TNode<JSAny> phi_bb9_6;
  TNode<Union<JSMessageObject, TheHole>> phi_bb9_7;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_6, &phi_bb9_7);
    JoinStackPopInline_0(state_, TNode<Context>{p_context}, TNode<JSReceiver>{p_o});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, p_context, phi_bb9_6, phi_bb9_7);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<String> tmp11;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp11 = kEmptyString_0(state_);
    ca_.Goto(&block1, tmp11);
  }

  TNode<JSAny> phi_bb1_6;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_6);
    ca_.Goto(&block12);
  }

    ca_.Bind(&block12);
  return TNode<JSAny>{phi_bb1_6};
}

} // namespace internal
} // namespace v8
