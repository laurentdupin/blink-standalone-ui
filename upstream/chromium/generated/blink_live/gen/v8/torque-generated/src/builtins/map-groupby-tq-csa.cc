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
#include "torque-generated/src/builtins/map-groupby-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/collections-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/function-tq-csa.h"
#include "torque-generated/src/builtins/map-groupby-tq-csa.h"
#include "torque-generated/src/builtins/object-groupby-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(MapGroupBy, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kItems);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kCallback);
  USE(parameter3);
  CodeStubAssembler(state_).CallRuntime(Runtime::kIncrementUseCounter, parameter0, CodeStubAssembler(state_).SmiConstant(v8::Isolate::kArrayGroup));
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, JSAny, IntPtrT> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, JSAny, IntPtrT> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, JSAny, IntPtrT, IntPtrT> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, JSAny, IntPtrT, IntPtrT> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny, JSAny, IntPtrT> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<False> tmp0;
  TNode<OrderedHashMap> tmp1;
  TNode<OrderedHashMap> tmp2;
  TNode<Int32T> tmp3;
  TNode<Int32T> tmp4;
  TNode<JSAny> tmp5;
  TNode<JSAny> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Map> tmp8;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = False_0(state_);
    tmp1 = GroupByImpl_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter3}, TNode<Boolean>{tmp0}, "Map.groupBy");
    std::tie(tmp2, tmp3, tmp4, tmp5, tmp6, tmp7) = NewUnmodifiedOrderedHashMapIterator_0(state_, TNode<OrderedHashMap>{tmp1}).Flatten();
    tmp8 = GetFastPackedElementsJSArrayMap_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block5, tmp5, tmp6, tmp7);
  }

  TNode<JSAny> phi_bb5_8;
  TNode<JSAny> phi_bb5_9;
  TNode<IntPtrT> phi_bb5_10;
  TNode<BoolT> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_8, &phi_bb5_9, &phi_bb5_10);
    tmp9 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp9, &block3, std::vector<compiler::Node*>{phi_bb5_8, phi_bb5_9, phi_bb5_10}, &block4, std::vector<compiler::Node*>{phi_bb5_8, phi_bb5_9, phi_bb5_10});
  }

  TNode<JSAny> phi_bb3_8;
  TNode<JSAny> phi_bb3_9;
  TNode<IntPtrT> phi_bb3_10;
  TNode<JSAny> tmp10;
  TNode<JSAny> tmp11;
  TNode<IntPtrT> tmp12;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_8, &phi_bb3_9, &phi_bb3_10);
    compiler::CodeAssemblerLabel label13(&ca_);
    std::tie(tmp10, tmp11, tmp12) = CollectionsBuiltinsAssembler(state_).NextKeyValueIndexTupleUnmodifiedTable(TNode<OrderedHashMap>{tmp2}, TNode<Int32T>{tmp3}, TNode<Int32T>{tmp4}, TNode<IntPtrT>{phi_bb3_10}, &label13).Flatten();
    ca_.Goto(&block7, phi_bb3_8, phi_bb3_9, phi_bb3_10, phi_bb3_10);
    if (label13.is_used()) {
      ca_.Bind(&label13);
      ca_.Goto(&block8, phi_bb3_8, phi_bb3_9, phi_bb3_10, phi_bb3_10);
    }
  }

  TNode<JSAny> phi_bb8_8;
  TNode<JSAny> phi_bb8_9;
  TNode<IntPtrT> phi_bb8_10;
  TNode<IntPtrT> phi_bb8_15;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_8, &phi_bb8_9, &phi_bb8_10, &phi_bb8_15);
    ca_.Goto(&block1);
  }

  TNode<JSAny> phi_bb7_8;
  TNode<JSAny> phi_bb7_9;
  TNode<IntPtrT> phi_bb7_10;
  TNode<IntPtrT> phi_bb7_15;
  TNode<ArrayList> tmp14;
  TNode<FixedArray> tmp15;
  TNode<JSArray> tmp16;
  TNode<IntPtrT> tmp17;
  TNode<BoolT> tmp18;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_8, &phi_bb7_9, &phi_bb7_10, &phi_bb7_15);
    tmp14 = UnsafeCast_ArrayList_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp11});
    tmp15 = CodeStubAssembler(state_).ArrayListElements(TNode<ArrayList>{tmp14});
    tmp16 = NewJSArray_0(state_, TNode<Context>{parameter0}, TNode<Map>{tmp8}, TNode<FixedArrayBase>{tmp15});
    tmp17 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp18 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp12}, TNode<IntPtrT>{tmp17});
    ca_.Branch(tmp18, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/collections.tq", 177});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.current.index > 0' failed", pos_stack);
    }
  }

  TNode<Int32T> tmp19;
  TNode<Int32T> tmp20;
  TNode<Int32T> tmp21;
  TNode<Int32T> tmp22;
  TNode<Int32T> tmp23;
  TNode<Int32T> tmp24;
  TNode<IntPtrT> tmp25;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp19 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{tmp12});
    tmp20 = FromConstexpr_int32_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp21 = CodeStubAssembler(state_).Int32Sub(TNode<Int32T>{tmp19}, TNode<Int32T>{tmp20});
    tmp22 = FromConstexpr_int32_constexpr_int32_0(state_, OrderedHashMap::kEntrySize);
    tmp23 = CodeStubAssembler(state_).Int32Mul(TNode<Int32T>{tmp21}, TNode<Int32T>{tmp22});
    tmp24 = CodeStubAssembler(state_).Int32Add(TNode<Int32T>{tmp23}, TNode<Int32T>{tmp3});
    tmp25 = Convert_intptr_int32_0(state_, TNode<Int32T>{tmp24});
    CollectionsBuiltinsAssembler(state_).UnsafeStoreValueInOrderedHashMapEntry(TNode<OrderedHashMap>{tmp2}, TNode<Object>{tmp16}, TNode<IntPtrT>{tmp25});
    ca_.Goto(&block5, tmp10, tmp11, tmp12);
  }

  TNode<JSAny> phi_bb4_8;
  TNode<JSAny> phi_bb4_9;
  TNode<IntPtrT> phi_bb4_10;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_8, &phi_bb4_9, &phi_bb4_10);
    ca_.Goto(&block1);
  }

  TNode<IntPtrT> tmp26;
  TNode<Union<HeapObject, TaggedIndex>> tmp27;
  TNode<IntPtrT> tmp28;
  TNode<Map> tmp29;
  TNode<FixedArray> tmp30;
  TNode<FixedArray> tmp31;
  TNode<BoolT> tmp32;
  TNode<BoolT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<HeapObject> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<JSMap> tmp40;
  if (block1.is_used()) {
    ca_.Bind(&block1);
    tmp26 = JS_MAP_MAP_INDEX_0(state_);
    std::tie(tmp27, tmp28) = NativeContextSlot_NativeContext_Map_0(state_, TNode<NativeContext>{parameter0}, TNode<IntPtrT>{tmp26}).Flatten();
    tmp29 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp27, tmp28});
    tmp30 = kEmptyFixedArray_0(state_);
    tmp31 = kEmptyFixedArray_0(state_);
    tmp32 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp33 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    tmp34 = FromConstexpr_intptr_constexpr_int31_0(state_, 16);
    tmp35 = AllocateFromNew_0(state_, TNode<IntPtrT>{tmp34}, TNode<Map>{tmp29}, TNode<BoolT>{tmp32}, TNode<BoolT>{tmp33});
    tmp36 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    CodeStubAssembler(state_).StoreReference<Map>(CodeStubAssembler::Reference{tmp35, tmp36}, tmp29);
    tmp37 = FromConstexpr_intptr_constexpr_int31_0(state_, 4);
    CodeStubAssembler(state_).StoreReference<Union<FixedArrayBase, PropertyArray, Smi, SwissNameDictionary>>(CodeStubAssembler::Reference{tmp35, tmp37}, tmp30);
    tmp38 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    CodeStubAssembler(state_).StoreReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp35, tmp38}, tmp31);
    tmp39 = FromConstexpr_intptr_constexpr_int31_0(state_, 12);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp35, tmp39}, tmp1);
    tmp40 = TORQUE_CAST(TNode<HeapObject>{tmp35});
    CodeStubAssembler(state_).Return(tmp40);
  }
}

// https://crsrc.org/c/v8/src/builtins/map-groupby.tq?l=25&c=42
TNode<ArrayList> UnsafeCast_ArrayList_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o) {
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
    tmp0 = Is_ArrayList_Object_0(state_, TNode<Context>{p_context}, TNode<Object>{p_o});
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

  TNode<ArrayList> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = TORQUE_CAST(TNode<Object>{p_o});
    ca_.Goto(&block4);
  }

    ca_.Bind(&block4);
  return TNode<ArrayList>{tmp1};
}

} // namespace internal
} // namespace v8
