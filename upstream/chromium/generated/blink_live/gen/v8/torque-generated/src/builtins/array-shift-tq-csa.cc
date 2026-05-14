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
#include "torque-generated/src/builtins/array-shift-tq-csa.h"
#include "torque-generated/src/builtins/array-findindex-tq-csa.h"
#include "torque-generated/src/builtins/array-reverse-tq-csa.h"
#include "torque-generated/src/builtins/array-shift-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frames-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/array-shift.tq?l=11&c=1
TNode<JSAny> TryFastArrayShift_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_receiver, compiler::CodeAssemblerLabel* label_Slow, compiler::CodeAssemblerLabel* label_Runtime) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block22(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block28(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block27(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block44(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block45(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block47(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block71(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block74(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSArray> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_FastJSArray_1(state_, TNode<Context>{p_context}, TNode<Object>{p_receiver}, &label1);
    ca_.Goto(&block4);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block5);
    }
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    ca_.Goto(&block1);
  }

  TNode<JSArray> tmp2;
  TNode<JSArray> tmp3;
  TNode<Map> tmp4;
  TNode<BoolT> tmp5;
  TNode<BoolT> tmp6;
  TNode<BoolT> tmp7;
  TNode<BoolT> tmp8;
  TNode<Int32T> tmp9;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    std::tie(tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8) = NewFastJSArrayWitness_0(state_, TNode<JSArray>{tmp0}).Flatten();
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = CodeStubAssembler(state_).EnsureArrayPushable(TNode<Context>{p_context}, TNode<Map>{tmp4}, &label10);
    ca_.Goto(&block7);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    ca_.Goto(&block1);
  }

  TNode<BoolT> tmp11;
  TNode<Smi> tmp12;
  TNode<Smi> tmp13;
  TNode<BoolT> tmp14;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3});
    tmp11 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    tmp12 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    tmp13 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp14 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp12}, TNode<Smi>{tmp13});
    ca_.Branch(tmp14, &block9, std::vector<compiler::Node*>{}, &block10, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp15;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    tmp15 = Undefined_0(state_);
    ca_.Goto(&block3, tmp15);
  }

  TNode<Smi> tmp16;
  TNode<Smi> tmp17;
  TNode<Smi> tmp18;
  TNode<Smi> tmp19;
  TNode<Smi> tmp20;
  TNode<Smi> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<FixedArrayBase> tmp24;
  TNode<IntPtrT> tmp25;
  TNode<BoolT> tmp26;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp16 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp0});
    tmp17 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp18 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp16}, TNode<Smi>{tmp17});
    tmp19 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp18}, TNode<Smi>{tmp18});
    tmp20 = FromConstexpr_Smi_constexpr_int31_0(state_, JSObject::kMinAddedElementsCapacity);
    tmp21 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{tmp19}, TNode<Smi>{tmp20});
    tmp22 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp21});
    tmp23 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp24 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp0, tmp23});
    tmp25 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp24});
    tmp26 = CodeStubAssembler(state_).IntPtrLessThan(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp25});
    ca_.Branch(tmp26, &block11, std::vector<compiler::Node*>{}, &block12, std::vector<compiler::Node*>{});
  }

  if (block11.is_used()) {
    ca_.Bind(&block11);
    ca_.Goto(&block2);
  }

  TNode<Smi> tmp27;
  TNode<BoolT> tmp28;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp27 = FromConstexpr_Smi_constexpr_int31_0(state_, JSArray::kMaxCopyElements);
    tmp28 = CodeStubAssembler(state_).SmiGreaterThan(TNode<Smi>{tmp18}, TNode<Smi>{tmp27});
    ca_.Branch(tmp28, &block13, std::vector<compiler::Node*>{}, &block14, std::vector<compiler::Node*>{});
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block2);
  }

  TNode<Smi> tmp29;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp29 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Branch(tmp5, &block19, std::vector<compiler::Node*>{}, &block20, std::vector<compiler::Node*>{});
  }

  TNode<JSAny> tmp30;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    compiler::CodeAssemblerLabel label31(&ca_);
    tmp30 = LoadElementNoHole_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3}, TNode<Smi>{tmp29}, &label31);
    ca_.Goto(&block22);
    if (label31.is_used()) {
      ca_.Bind(&label31);
      ca_.Goto(&block23);
    }
  }

  if (block23.is_used()) {
    ca_.Bind(&block23);
    ca_.Goto(&block17);
  }

  if (block22.is_used()) {
    ca_.Bind(&block22);
    ca_.Goto(&block18, tmp30);
  }

  TNode<JSAny> tmp32;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    compiler::CodeAssemblerLabel label33(&ca_);
    tmp32 = LoadElementNoHole_FixedArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp3}, TNode<Smi>{tmp29}, &label33);
    ca_.Goto(&block24);
    if (label33.is_used()) {
      ca_.Bind(&label33);
      ca_.Goto(&block25);
    }
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    ca_.Goto(&block17);
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    ca_.Goto(&block18, tmp32);
  }

  TNode<JSAny> phi_bb18_18;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_18);
    ca_.Goto(&block15, phi_bb18_18);
  }

  TNode<Undefined> tmp34;
  if (block17.is_used()) {
    ca_.Bind(&block17);
    tmp34 = Undefined_0(state_);
    ca_.Goto(&block15, tmp34);
  }

  TNode<JSAny> phi_bb15_14;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_14);
    ca_.Branch(tmp11, &block27, std::vector<compiler::Node*>{}, &block28, std::vector<compiler::Node*>{});
  }

  if (block28.is_used()) {
    ca_.Bind(&block28);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/objects/js-array.tq", 285});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.arrayIsPushable' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp35;
  TNode<IntPtrT> tmp36;
  TNode<IntPtrT> tmp37;
  if (block27.is_used()) {
    ca_.Bind(&block27);
    StoreFastJSArrayLength_0(state_, TNode<JSArray>{tmp3}, TNode<Smi>{tmp18});
    tmp35 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp18});
    tmp36 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp37 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    ca_.Branch(tmp11, &block30, std::vector<compiler::Node*>{}, &block31, std::vector<compiler::Node*>{});
  }

  if (block31.is_used()) {
    ca_.Bind(&block31);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/objects/js-array.tq", 321});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.arrayIsPushable' failed", pos_stack);
    }
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    ca_.Branch(tmp5, &block32, std::vector<compiler::Node*>{}, &block33, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp38;
  TNode<FixedArrayBase> tmp39;
  TNode<FixedDoubleArray> tmp40;
  if (block32.is_used()) {
    ca_.Bind(&block32);
    tmp38 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp39 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp38});
    compiler::CodeAssemblerLabel label41(&ca_);
    tmp40 = Cast_FixedDoubleArray_0(state_, TNode<HeapObject>{tmp39}, &label41);
    ca_.Goto(&block37);
    if (label41.is_used()) {
      ca_.Bind(&label41);
      ca_.Goto(&block38);
    }
  }

  if (block38.is_used()) {
    ca_.Bind(&block38);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/objects/js-array.tq:325:21");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block37.is_used()) {
    ca_.Bind(&block37);
    TorqueMoveElements_1(state_, TNode<FixedDoubleArray>{tmp40}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp37}, TNode<IntPtrT>{tmp35});
    ca_.Goto(&block34);
  }

  TNode<IntPtrT> tmp42;
  TNode<FixedArrayBase> tmp43;
  TNode<FixedArray> tmp44;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp42 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp43 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp42});
    compiler::CodeAssemblerLabel label45(&ca_);
    tmp44 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp43}, &label45);
    ca_.Goto(&block41);
    if (label45.is_used()) {
      ca_.Bind(&label45);
      ca_.Goto(&block42);
    }
  }

  if (block42.is_used()) {
    ca_.Bind(&block42);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/objects/js-array.tq:329:21");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block41.is_used()) {
    ca_.Bind(&block41);
    ca_.Branch(tmp7, &block43, std::vector<compiler::Node*>{}, &block44, std::vector<compiler::Node*>{});
  }

  if (block43.is_used()) {
    ca_.Bind(&block43);
    TorqueMoveElementsSmi_0(state_, TNode<FixedArray>{tmp44}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp37}, TNode<IntPtrT>{tmp35});
    ca_.Goto(&block45);
  }

  if (block44.is_used()) {
    ca_.Bind(&block44);
    TorqueMoveElements_0(state_, TNode<FixedArray>{tmp44}, TNode<IntPtrT>{tmp36}, TNode<IntPtrT>{tmp37}, TNode<IntPtrT>{tmp35});
    ca_.Goto(&block45);
  }

  if (block45.is_used()) {
    ca_.Bind(&block45);
    ca_.Goto(&block34);
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    ca_.Branch(tmp5, &block47, std::vector<compiler::Node*>{}, &block48, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp46;
  TNode<FixedArrayBase> tmp47;
  TNode<FixedDoubleArray> tmp48;
  if (block47.is_used()) {
    ca_.Bind(&block47);
    tmp46 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp47 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp46});
    compiler::CodeAssemblerLabel label49(&ca_);
    tmp48 = Cast_FixedDoubleArray_0(state_, TNode<HeapObject>{tmp47}, &label49);
    ca_.Goto(&block52);
    if (label49.is_used()) {
      ca_.Bind(&label49);
      ca_.Goto(&block53);
    }
  }

  if (block53.is_used()) {
    ca_.Bind(&block53);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/objects/js-array.tq:261:21");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<IntPtrT> tmp52;
  TNode<IntPtrT> tmp53;
  TNode<UintPtrT> tmp54;
  TNode<UintPtrT> tmp55;
  TNode<BoolT> tmp56;
  if (block52.is_used()) {
    ca_.Bind(&block52);
    std::tie(tmp50, tmp51, tmp52) = FieldSliceFixedDoubleArrayValues_0(state_, TNode<FixedDoubleArray>{tmp48}).Flatten();
    tmp53 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp18});
    tmp54 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp53});
    tmp55 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp52});
    tmp56 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp54}, TNode<UintPtrT>{tmp55});
    ca_.Branch(tmp56, &block58, std::vector<compiler::Node*>{}, &block59, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<BoolT> tmp61;
  TNode<BoolT> tmp62;
  TNode<Float64T> tmp63;
  if (block58.is_used()) {
    ca_.Bind(&block58);
    tmp57 = TimesSizeOf_float64_or_undefined_or_hole_0(state_, TNode<IntPtrT>{tmp53});
    tmp58 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp51}, TNode<IntPtrT>{tmp57});
    std::tie(tmp59, tmp60) = NewReference_float64_or_undefined_or_hole_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp50}, TNode<IntPtrT>{tmp58}).Flatten();
    std::tie(tmp61, tmp62, tmp63) = kDoubleHole_0(state_).Flatten();
    StoreFloat64OrUndefinedOrHole_0(state_, TorqueStructReference_float64_or_undefined_or_hole_0{TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp60}, TorqueStructUnsafe_0{}}, TorqueStructfloat64_or_undefined_or_hole_0{TNode<BoolT>{tmp61}, TNode<BoolT>{tmp62}, TNode<Float64T>{tmp63}});
    ca_.Goto(&block49);
  }

  if (block59.is_used()) {
    ca_.Bind(&block59);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<IntPtrT> tmp64;
  TNode<FixedArrayBase> tmp65;
  TNode<FixedArray> tmp66;
  if (block48.is_used()) {
    ca_.Bind(&block48);
    tmp64 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp65 = CodeStubAssembler(state_).LoadReference<FixedArrayBase>(CodeStubAssembler::Reference{tmp3, tmp64});
    compiler::CodeAssemblerLabel label67(&ca_);
    tmp66 = Cast_FixedArray_0(state_, TNode<HeapObject>{tmp65}, &label67);
    ca_.Goto(&block64);
    if (label67.is_used()) {
      ca_.Bind(&label67);
      ca_.Goto(&block65);
    }
  }

  if (block65.is_used()) {
    ca_.Bind(&block65);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/objects/js-array.tq:265:21");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp68;
  TNode<IntPtrT> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<IntPtrT> tmp71;
  TNode<UintPtrT> tmp72;
  TNode<UintPtrT> tmp73;
  TNode<BoolT> tmp74;
  if (block64.is_used()) {
    ca_.Bind(&block64);
    std::tie(tmp68, tmp69, tmp70) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{tmp66}).Flatten();
    tmp71 = Convert_intptr_Smi_0(state_, TNode<Smi>{tmp18});
    tmp72 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp71});
    tmp73 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp70});
    tmp74 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp72}, TNode<UintPtrT>{tmp73});
    ca_.Branch(tmp74, &block70, std::vector<compiler::Node*>{}, &block71, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp75;
  TNode<IntPtrT> tmp76;
  TNode<Union<HeapObject, TaggedIndex>> tmp77;
  TNode<IntPtrT> tmp78;
  TNode<TheHole> tmp79;
  if (block70.is_used()) {
    ca_.Bind(&block70);
    tmp75 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp71});
    tmp76 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp69}, TNode<IntPtrT>{tmp75});
    std::tie(tmp77, tmp78) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp68}, TNode<IntPtrT>{tmp76}).Flatten();
    tmp79 = TheHole_0(state_);
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp77, tmp78}, tmp79);
    ca_.Goto(&block49);
  }

  if (block71.is_used()) {
    ca_.Bind(&block71);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:131:41");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block49.is_used()) {
    ca_.Bind(&block49);
    ca_.Goto(&block3, phi_bb15_14);
  }

  TNode<JSAny> phi_bb3_2;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_2);
    ca_.Goto(&block74, phi_bb3_2);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Slow);
  }

  if (block2.is_used()) {
    ca_.Bind(&block2);
    ca_.Goto(label_Runtime);
  }

  TNode<JSAny> phi_bb74_2;
    ca_.Bind(&block74, &phi_bb74_2);
  return TNode<JSAny>{phi_bb74_2};
}

// https://crsrc.org/c/v8/src/builtins/array-shift.tq?l=42&c=1
TNode<JSAny> GenericArrayShift_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_receiver) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  TNode<Number> tmp1;
  TNode<Number> tmp2;
  TNode<BoolT> tmp3;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{p_context}, TNode<JSAny>{p_receiver});
    tmp1 = GetLengthProperty_0(state_, TNode<Context>{p_context}, TNode<JSAny>{tmp0});
    tmp2 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp3 = IsNumberEqual_0(state_, TNode<Number>{tmp1}, TNode<Number>{tmp2});
    ca_.Branch(tmp3, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  TNode<String> tmp4;
  TNode<Smi> tmp5;
  TNode<JSAny> tmp6;
  TNode<Undefined> tmp7;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp4 = kLengthString_0(state_);
    tmp5 = Convert_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, p_context, tmp0, tmp4, tmp5);
    tmp7 = Undefined_0(state_);
    ca_.Goto(&block1, tmp7);
  }

  TNode<Smi> tmp8;
  TNode<JSAny> tmp9;
  TNode<Number> tmp10;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    tmp8 = Convert_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp9 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<JSAny>{tmp0}, TNode<JSAny>{tmp8});
    tmp10 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    ca_.Goto(&block6, tmp10);
  }

  TNode<Number> phi_bb6_5;
  TNode<BoolT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_5);
    tmp11 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb6_5}, TNode<Number>{tmp1});
    ca_.Branch(tmp11, &block4, std::vector<compiler::Node*>{phi_bb6_5}, &block5, std::vector<compiler::Node*>{phi_bb6_5});
  }

  TNode<Number> phi_bb4_5;
  TNode<Number> tmp12;
  TNode<Number> tmp13;
  TNode<Boolean> tmp14;
  TNode<True> tmp15;
  TNode<BoolT> tmp16;
  if (block4.is_used()) {
    ca_.Bind(&block4, &phi_bb4_5);
    tmp12 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp13 = CodeStubAssembler(state_).NumberSub(TNode<Number>{phi_bb4_5}, TNode<Number>{tmp12});
    tmp14 = ca_.CallBuiltin<Boolean>(Builtin::kHasProperty, p_context, tmp0, phi_bb4_5);
    tmp15 = True_0(state_);
    tmp16 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp14}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp15});
    ca_.Branch(tmp16, &block7, std::vector<compiler::Node*>{phi_bb4_5, phi_bb4_5}, &block8, std::vector<compiler::Node*>{phi_bb4_5, phi_bb4_5});
  }

  TNode<Number> phi_bb7_5;
  TNode<Number> phi_bb7_6;
  TNode<JSAny> tmp17;
  TNode<JSAny> tmp18;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_5, &phi_bb7_6);
    tmp17 = CodeStubAssembler(state_).GetProperty(TNode<Context>{p_context}, TNode<JSAny>{tmp0}, TNode<JSAny>{phi_bb7_6});
    tmp18 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, p_context, tmp0, tmp13, tmp17);
    ca_.Goto(&block9, phi_bb7_5, phi_bb7_6);
  }

  TNode<Number> phi_bb8_5;
  TNode<Number> phi_bb8_6;
  TNode<Smi> tmp19;
  TNode<Boolean> tmp20;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_5, &phi_bb8_6);
    tmp19 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, CastIfEnumClass<LanguageMode>(LanguageMode::kStrict));
    tmp20 = ca_.CallBuiltin<Boolean>(Builtin::kDeleteProperty, p_context, tmp0, tmp13, tmp19);
    ca_.Goto(&block9, phi_bb8_5, phi_bb8_6);
  }

  TNode<Number> phi_bb9_5;
  TNode<Number> phi_bb9_6;
  TNode<Number> tmp21;
  TNode<Number> tmp22;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_5, &phi_bb9_6);
    tmp21 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp22 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb9_5}, TNode<Number>{tmp21});
    ca_.Goto(&block6, tmp22);
  }

  TNode<Number> phi_bb5_5;
  TNode<Number> tmp23;
  TNode<Number> tmp24;
  TNode<Smi> tmp25;
  TNode<Boolean> tmp26;
  TNode<String> tmp27;
  TNode<Number> tmp28;
  TNode<Number> tmp29;
  TNode<JSAny> tmp30;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_5);
    tmp23 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp24 = CodeStubAssembler(state_).NumberSub(TNode<Number>{tmp1}, TNode<Number>{tmp23});
    tmp25 = FromConstexpr_LanguageModeSmi_constexpr_LanguageMode_0(state_, CastIfEnumClass<LanguageMode>(LanguageMode::kStrict));
    tmp26 = ca_.CallBuiltin<Boolean>(Builtin::kDeleteProperty, p_context, tmp0, tmp24, tmp25);
    tmp27 = kLengthString_0(state_);
    tmp28 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp29 = CodeStubAssembler(state_).NumberSub(TNode<Number>{tmp1}, TNode<Number>{tmp28});
    tmp30 = ca_.CallBuiltin<JSAny>(Builtin::kSetProperty, p_context, tmp0, tmp27, tmp29);
    ca_.Goto(&block1, tmp9);
  }

  TNode<JSAny> phi_bb1_2;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_2);
    ca_.Goto(&block10, phi_bb1_2);
  }

  TNode<JSAny> phi_bb10_2;
    ca_.Bind(&block10, &phi_bb10_2);
  return TNode<JSAny>{phi_bb10_2};
}

TF_BUILTIN(ArrayPrototypeShift, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp0 = TryFastArrayShift_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, &label1, &label2);
    ca_.Goto(&block5);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block6);
    }
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  TNode<JSAny> tmp3;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp3 = GenericArrayShift_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter1});
    arguments.PopAndReturn(tmp3);
  }

  TNode<JSFunction> tmp4;
  TNode<Undefined> tmp5;
  TNode<Int32T> tmp6;
  TNode<JSDispatchHandleT> tmp7;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = LoadTargetFromFrame_0(state_);
    tmp5 = Undefined_0(state_);
    tmp6 = Convert_int32_intptr_0(state_, TNode<IntPtrT>{torque_arguments.actual_count});
    tmp7 = kInvalidDispatchHandle_0(state_);
   CodeStubAssembler(state_).TailCallJSBuiltin(Builtin::kArrayShift, parameter0, tmp4, tmp5, tmp6, tmp7);
  }

  if (block5.is_used()) {
    ca_.Bind(&block5);
    arguments.PopAndReturn(tmp0);
  }
}

} // namespace internal
} // namespace v8
