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
#include "torque-generated/src/builtins/array-from-tq-csa.h"
#include "torque-generated/src/builtins/array-from-async-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/builtins/iterator-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ArrayFrom, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<JSAny> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block17(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block44(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Smi> block45(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, JSAny, Union<JSMessageObject, TheHole>> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, JSAny> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi, Smi> block48(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver, Smi> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver, Smi> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver, Smi> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver, Smi> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver, Smi, JSAny> block64(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<BoolT, JSReceiver, Smi> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = CodeStubAssembler(state_).HasBuiltinSubclassingFlag();
    ca_.Branch(tmp0, &block1, std::vector<compiler::Node*>{}, &block2, std::vector<compiler::Node*>{});
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(&block3, parameter1);
  }

  TNode<JSFunction> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp1 = GetArrayFunction_0(state_, TNode<Context>{parameter0});
    ca_.Goto(&block3, tmp1);
  }

  TNode<JSAny> phi_bb3_6;
  TNode<IntPtrT> tmp2;
  TNode<BoolT> tmp3;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_6);
    tmp2 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp3 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp2});
    ca_.Branch(tmp3, &block7, std::vector<compiler::Node*>{}, &block8, std::vector<compiler::Node*>{});
  }

  TNode<JSFunction> tmp4;
  TNode<BoolT> tmp5;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    tmp4 = GetArrayFunction_0(state_, TNode<Context>{parameter0});
    tmp5 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{phi_bb3_6}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp4});
    ca_.Goto(&block9, tmp5);
  }

  TNode<BoolT> tmp6;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp6 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block9, tmp6);
  }

  TNode<BoolT> phi_bb9_8;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_8);
    ca_.Branch(phi_bb9_8, &block5, std::vector<compiler::Node*>{}, &block6, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp7;
  TNode<JSAny> tmp8;
  TNode<JSArray> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp7 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp8 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp7});
    compiler::CodeAssemblerLabel label10(&ca_);
    tmp9 = IteratorBuiltinsAssembler(state_).FastIterableToList(TNode<Context>{parameter0}, TNode<JSAny>{tmp8}, &label10);
    ca_.Goto(&block12);
    if (label10.is_used()) {
      ca_.Bind(&label10);
      ca_.Goto(&block13);
    }
  }

  if (block13.is_used()) {
    ca_.Bind(&block13);
    ca_.Goto(&block6);
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    arguments.PopAndReturn(tmp9);
  }

  TNode<IntPtrT> tmp11;
  TNode<JSAny> tmp12;
  TNode<IntPtrT> tmp13;
  TNode<JSAny> tmp14;
  TNode<IntPtrT> tmp15;
  TNode<JSAny> tmp16;
  TNode<Undefined> tmp17;
  TNode<BoolT> tmp18;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp11 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp12 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp11});
    tmp13 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp14 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp13});
    tmp15 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x2ull));
    tmp16 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp15});
    tmp17 = Undefined_0(state_);
    tmp18 = CodeStubAssembler(state_).TaggedEqual(TNode<Object>{tmp14}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp17});
    ca_.Branch(tmp18, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  TNode<BoolT> tmp19;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp19 = FromConstexpr_bool_constexpr_bool_0(state_, false);
    ca_.Goto(&block16, tmp19);
  }

  TNode<BoolT> tmp20;
  TNode<BoolT> tmp21;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp20 = Is_Callable_JSAny_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp14});
    tmp21 = CodeStubAssembler(state_).Word32BinaryNot(TNode<BoolT>{tmp20});
    ca_.Branch(tmp21, &block17, std::vector<compiler::Node*>{}, &block18, std::vector<compiler::Node*>{});
  }

  if (block17.is_used()) {
    ca_.Bind(&block17);
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, tmp14);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp22;
  if (block18.is_used()) {
    ca_.Bind(&block18);
    tmp22 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block16, tmp22);
  }

  TNode<BoolT> phi_bb16_10;
  TNode<Symbol> tmp23;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp24;
    compiler::TypedCodeAssemblerVariable<JSAny> tmp27(&ca_);
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_10);
    tmp23 = CodeStubAssembler(state_).IteratorSymbolConstant();
    compiler::CodeAssemblerLabel label25(&ca_);
    compiler::CodeAssemblerLabel label26(&ca_);
    tmp24 = GetMethod_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp12}, TNode<Union<String, Symbol>>{tmp23}, &label25, &label26, &tmp27);
    ca_.Goto(&block23, phi_bb16_10);
    if (label25.is_used()) {
      ca_.Bind(&label25);
      ca_.Goto(&block24, phi_bb16_10);
    }
    if (label26.is_used()) {
      ca_.Bind(&label26);
      ca_.Goto(&block25, phi_bb16_10);
    }
  }

  TNode<BoolT> phi_bb24_10;
  TNode<JSReceiver> tmp28;
  TNode<Number> tmp29;
  TNode<JSFunction> tmp30;
  TNode<BoolT> tmp31;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_10);
    tmp28 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<JSAny>{tmp12});
    tmp29 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp28});
    tmp30 = GetArrayFunction_0(state_, TNode<Context>{parameter0});
    tmp31 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{phi_bb3_6}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp30});
    ca_.Branch(tmp31, &block51, std::vector<compiler::Node*>{phi_bb24_10}, &block52, std::vector<compiler::Node*>{phi_bb24_10});
  }

  TNode<BoolT> phi_bb25_10;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_10);
    CodeStubAssembler(state_).ThrowTypeError(TNode<Context>{parameter0}, CastIfEnumClass<MessageTemplate>(MessageTemplate::kFirstArgumentIteratorSymbolNonCallable), "%Array%.from");
  }

  TNode<BoolT> phi_bb23_10;
  TNode<JSReceiver> tmp32;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_10);
    compiler::CodeAssemblerLabel label33(&ca_);
    tmp32 = Cast_Constructor_1(state_, TNode<Context>{parameter0}, TNode<Object>{phi_bb3_6}, &label33);
    ca_.Goto(&block28, phi_bb23_10);
    if (label33.is_used()) {
      ca_.Bind(&label33);
      ca_.Goto(&block29, phi_bb23_10);
    }
  }

  TNode<BoolT> phi_bb29_10;
  TNode<Number> tmp34;
  TNode<JSArray> tmp35;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_10);
    tmp34 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp35 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{parameter0}, TNode<Number>{tmp34});
    ca_.Goto(&block26, phi_bb29_10, tmp35);
  }

  TNode<BoolT> phi_bb28_10;
  TNode<JSReceiver> tmp36;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_10);
    tmp36 = CodeStubAssembler(state_).Construct(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp32});
    ca_.Goto(&block26, phi_bb28_10, tmp36);
  }

  TNode<BoolT> phi_bb26_10;
  TNode<JSReceiver> phi_bb26_12;
  TNode<JSReceiver> tmp37;
  TNode<JSAny> tmp38;
  TNode<Map> tmp39;
  TNode<Smi> tmp40;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_10, &phi_bb26_12);
    std::tie(tmp37, tmp38) = IteratorBuiltinsAssembler(state_).GetIterator(TNode<Context>{parameter0}, TNode<JSAny>{tmp12}, TNode<JSAny>{tmp24}).Flatten();
    tmp39 = GetIteratorResultMap_0(state_, TNode<Context>{parameter0});
    tmp40 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block32, phi_bb26_10, tmp40);
  }

  TNode<BoolT> phi_bb32_10;
  TNode<Smi> phi_bb32_16;
  TNode<BoolT> tmp41;
  if (block32.is_used()) {
    ca_.Bind(&block32, &phi_bb32_10, &phi_bb32_16);
    tmp41 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Branch(tmp41, &block30, std::vector<compiler::Node*>{phi_bb32_10, phi_bb32_16}, &block31, std::vector<compiler::Node*>{phi_bb32_10, phi_bb32_16});
  }

  TNode<BoolT> phi_bb30_10;
  TNode<Smi> phi_bb30_16;
  TNode<Number> tmp42;
  TNode<BoolT> tmp43;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_10, &phi_bb30_16);
    tmp42 = FromConstexpr_Number_constexpr_float64_0(state_, kMaxSafeInteger);
    tmp43 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb30_16}, TNode<Number>{tmp42});
    ca_.Branch(tmp43, &block33, std::vector<compiler::Node*>{phi_bb30_10, phi_bb30_16}, &block34, std::vector<compiler::Node*>{phi_bb30_10, phi_bb30_16});
  }

  TNode<BoolT> phi_bb34_10;
  TNode<Smi> phi_bb34_16;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_10, &phi_bb34_16);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/array-from.tq", 82});
      CodeStubAssembler(state_).FailAssert("Torque assert 'k < kMaxSafeInteger' failed", pos_stack);
    }
  }

  TNode<BoolT> phi_bb33_10;
  TNode<Smi> phi_bb33_16;
  TNode<JSReceiver> tmp44;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_10, &phi_bb33_16);
    compiler::CodeAssemblerLabel label45(&ca_);
    tmp44 = IteratorBuiltinsAssembler(state_).IteratorStep(TNode<Context>{parameter0}, TorqueStructIteratorRecord{TNode<JSReceiver>{tmp37}, TNode<JSAny>{tmp38}}, TNode<Map>{tmp39}, &label45);
    ca_.Goto(&block37, phi_bb33_10, phi_bb33_16);
    if (label45.is_used()) {
      ca_.Bind(&label45);
      ca_.Goto(&block38, phi_bb33_10, phi_bb33_16);
    }
  }

  TNode<BoolT> phi_bb38_10;
  TNode<Smi> phi_bb38_16;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_10, &phi_bb38_16);
    CodeStubAssembler(state_).SetPropertyLength(TNode<Context>{parameter0}, TNode<JSAny>{phi_bb26_12}, TNode<Number>{phi_bb38_16});
    arguments.PopAndReturn(phi_bb26_12);
  }

  TNode<BoolT> phi_bb37_10;
  TNode<Smi> phi_bb37_16;
  TNode<JSAny> tmp46;
  if (block37.is_used()) {
    ca_.Bind(&block37, &phi_bb37_10, &phi_bb37_16);
    tmp46 = IteratorBuiltinsAssembler(state_).IteratorValue(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp44}, TNode<Map>{tmp39});
    ca_.Branch(phi_bb37_10, &block39, std::vector<compiler::Node*>{phi_bb37_10, phi_bb37_16}, &block40, std::vector<compiler::Node*>{phi_bb37_10, phi_bb37_16});
  }

  TNode<BoolT> phi_bb39_10;
  TNode<Smi> phi_bb39_16;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp47;
      TNode<JSAny> tmp49;
  TNode<JSAny> tmp50;
      TNode<JSAny> tmp52;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_10, &phi_bb39_16);
    compiler::CodeAssemblerExceptionHandlerLabel catch48__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch48__label);
    tmp47 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp14});
    }
    if (catch48__label.is_used()) {
      compiler::CodeAssemblerLabel catch48_skip(&ca_);
      ca_.Goto(&catch48_skip);
      ca_.Bind(&catch48__label, &tmp49);
      ca_.Goto(&block44, phi_bb39_10, phi_bb39_16);
      ca_.Bind(&catch48_skip);
    }
    compiler::CodeAssemblerExceptionHandlerLabel catch51__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch51__label);
    tmp50 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp47}, TNode<JSAny>{tmp16}, TNode<JSAny>{tmp46}, TNode<JSAny>{phi_bb39_16});
    }
    if (catch51__label.is_used()) {
      compiler::CodeAssemblerLabel catch51_skip(&ca_);
      ca_.Goto(&catch51_skip);
      ca_.Bind(&catch51__label, &tmp52);
      ca_.Goto(&block45, phi_bb39_10, phi_bb39_16, phi_bb39_16);
      ca_.Bind(&catch51_skip);
    }
    ca_.Goto(&block41, phi_bb39_10, phi_bb39_16, tmp50);
  }

  TNode<BoolT> phi_bb44_10;
  TNode<Smi> phi_bb44_16;
  TNode<Union<JSMessageObject, TheHole>> tmp53;
  if (block44.is_used()) {
    ca_.Bind(&block44, &phi_bb44_10, &phi_bb44_16);
    tmp53 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block43, phi_bb44_10, phi_bb44_16, tmp49, tmp53);
  }

  TNode<BoolT> phi_bb45_10;
  TNode<Smi> phi_bb45_16;
  TNode<Smi> phi_bb45_24;
  TNode<Union<JSMessageObject, TheHole>> tmp54;
  if (block45.is_used()) {
    ca_.Bind(&block45, &phi_bb45_10, &phi_bb45_16, &phi_bb45_24);
    tmp54 = GetAndResetPendingMessage_0(state_);
    ca_.Goto(&block43, phi_bb45_10, phi_bb45_16, tmp52, tmp54);
  }

  TNode<BoolT> phi_bb43_10;
  TNode<Smi> phi_bb43_16;
  TNode<JSAny> phi_bb43_20;
  TNode<Union<JSMessageObject, TheHole>> phi_bb43_21;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_10, &phi_bb43_16, &phi_bb43_20, &phi_bb43_21);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp37});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, phi_bb43_20, phi_bb43_21);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb40_10;
  TNode<Smi> phi_bb40_16;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_10, &phi_bb40_16);
    ca_.Goto(&block41, phi_bb40_10, phi_bb40_16, tmp46);
  }

  TNode<BoolT> phi_bb41_10;
  TNode<Smi> phi_bb41_16;
  TNode<JSAny> phi_bb41_19;
  TNode<Object> tmp55;
      TNode<JSAny> tmp57;
  TNode<Smi> tmp58;
  TNode<Smi> tmp59;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_10, &phi_bb41_16, &phi_bb41_19);
    compiler::CodeAssemblerExceptionHandlerLabel catch56__label(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    { compiler::ScopedExceptionHandler s(&ca_, &catch56__label);
    tmp55 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, parameter0, phi_bb26_12, phi_bb41_16, phi_bb41_19);
    }
    if (catch56__label.is_used()) {
      compiler::CodeAssemblerLabel catch56_skip(&ca_);
      ca_.Goto(&catch56_skip);
      ca_.Bind(&catch56__label, &tmp57);
      ca_.Goto(&block48, phi_bb41_10, phi_bb41_16, phi_bb41_16);
      ca_.Bind(&catch56_skip);
    }
    tmp58 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp59 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb41_16}, TNode<Smi>{tmp58});
    ca_.Goto(&block32, phi_bb41_10, tmp59);
  }

  TNode<BoolT> phi_bb48_10;
  TNode<Smi> phi_bb48_16;
  TNode<Smi> phi_bb48_21;
  TNode<Union<JSMessageObject, TheHole>> tmp60;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_10, &phi_bb48_16, &phi_bb48_21);
    tmp60 = GetAndResetPendingMessage_0(state_);
    IteratorCloseOnException_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp37});
    CodeStubAssembler(state_).CallRuntime(Runtime::kReThrowWithMessage, parameter0, tmp57, tmp60);
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb31_10;
  TNode<Smi> phi_bb31_16;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_10, &phi_bb31_16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-from.tq:133:5");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> phi_bb51_10;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_10);
    ca_.Goto(&block50, phi_bb51_10);
  }

  TNode<BoolT> phi_bb52_10;
  TNode<Number> tmp61;
  TNode<BoolT> tmp62;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_10);
    tmp61 = FromConstexpr_Number_constexpr_int31_0(state_, JSArray::kMaxFastArrayLength);
    tmp62 = NumberIsGreaterThan_0(state_, TNode<Number>{tmp29}, TNode<Number>{tmp61});
    ca_.Branch(tmp62, &block53, std::vector<compiler::Node*>{phi_bb52_10}, &block54, std::vector<compiler::Node*>{phi_bb52_10});
  }

  TNode<BoolT> phi_bb53_10;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_10);
    ca_.Goto(&block50, phi_bb53_10);
  }

  TNode<BoolT> phi_bb54_10;
  TNode<Smi> tmp63;
  TNode<IntPtrT> tmp64;
  TNode<Map> tmp65;
  TNode<JSArray> tmp66;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_10);
    tmp63 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp64 = Convert_intptr_Number_0(state_, TNode<Number>{tmp29});
    tmp65 = GetFastPackedSmiElementsJSArrayMap_0(state_, TNode<Context>{parameter0});
    tmp66 = CodeStubAssembler(state_).AllocateJSArray(CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_SMI_ELEMENTS), TNode<Map>{tmp65}, TNode<IntPtrT>{tmp64}, TNode<Smi>{tmp63});
    ca_.Goto(&block49, phi_bb54_10, tmp66);
  }

  TNode<BoolT> phi_bb50_10;
  TNode<JSReceiver> tmp67;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_10);
    compiler::CodeAssemblerLabel label68(&ca_);
    tmp67 = Cast_Constructor_1(state_, TNode<Context>{parameter0}, TNode<Object>{phi_bb3_6}, &label68);
    ca_.Goto(&block57, phi_bb50_10);
    if (label68.is_used()) {
      ca_.Bind(&label68);
      ca_.Goto(&block58, phi_bb50_10);
    }
  }

  TNode<BoolT> phi_bb58_10;
  TNode<JSArray> tmp69;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_10);
    tmp69 = CodeStubAssembler(state_).ArrayCreate(TNode<Context>{parameter0}, TNode<Number>{tmp29});
    ca_.Goto(&block55, phi_bb58_10, tmp69);
  }

  TNode<BoolT> phi_bb57_10;
  TNode<JSReceiver> tmp70;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_10);
    tmp70 = CodeStubAssembler(state_).Construct(TNode<Context>{parameter0}, TNode<JSReceiver>{tmp67}, TNode<JSAny>{tmp29});
    ca_.Goto(&block55, phi_bb57_10, tmp70);
  }

  TNode<BoolT> phi_bb55_10;
  TNode<JSReceiver> phi_bb55_13;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_10, &phi_bb55_13);
    ca_.Goto(&block49, phi_bb55_10, phi_bb55_13);
  }

  TNode<BoolT> phi_bb49_10;
  TNode<JSReceiver> phi_bb49_13;
  TNode<Smi> tmp71;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_10, &phi_bb49_13);
    tmp71 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    ca_.Goto(&block61, phi_bb49_10, phi_bb49_13, tmp71);
  }

  TNode<BoolT> phi_bb61_10;
  TNode<JSReceiver> phi_bb61_13;
  TNode<Smi> phi_bb61_14;
  TNode<BoolT> tmp72;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_10, &phi_bb61_13, &phi_bb61_14);
    tmp72 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb61_14}, TNode<Number>{tmp29});
    ca_.Branch(tmp72, &block59, std::vector<compiler::Node*>{phi_bb61_10, phi_bb61_13, phi_bb61_14}, &block60, std::vector<compiler::Node*>{phi_bb61_10, phi_bb61_13, phi_bb61_14});
  }

  TNode<BoolT> phi_bb59_10;
  TNode<JSReceiver> phi_bb59_13;
  TNode<Smi> phi_bb59_14;
  TNode<JSAny> tmp73;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_10, &phi_bb59_13, &phi_bb59_14);
    tmp73 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{tmp28}, TNode<JSAny>{phi_bb59_14});
    ca_.Branch(phi_bb59_10, &block62, std::vector<compiler::Node*>{phi_bb59_10, phi_bb59_13, phi_bb59_14}, &block63, std::vector<compiler::Node*>{phi_bb59_10, phi_bb59_13, phi_bb59_14});
  }

  TNode<BoolT> phi_bb62_10;
  TNode<JSReceiver> phi_bb62_13;
  TNode<Smi> phi_bb62_14;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp74;
  TNode<JSAny> tmp75;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_10, &phi_bb62_13, &phi_bb62_14);
    tmp74 = UnsafeCast_Callable_0(state_, TNode<Context>{parameter0}, TNode<Object>{tmp14});
    tmp75 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{tmp74}, TNode<JSAny>{tmp16}, TNode<JSAny>{tmp73}, TNode<JSAny>{phi_bb62_14});
    ca_.Goto(&block64, phi_bb62_10, phi_bb62_13, phi_bb62_14, tmp75);
  }

  TNode<BoolT> phi_bb63_10;
  TNode<JSReceiver> phi_bb63_13;
  TNode<Smi> phi_bb63_14;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_10, &phi_bb63_13, &phi_bb63_14);
    ca_.Goto(&block64, phi_bb63_10, phi_bb63_13, phi_bb63_14, tmp73);
  }

  TNode<BoolT> phi_bb64_10;
  TNode<JSReceiver> phi_bb64_13;
  TNode<Smi> phi_bb64_14;
  TNode<JSAny> phi_bb64_16;
  TNode<Object> tmp76;
  TNode<Smi> tmp77;
  TNode<Smi> tmp78;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_10, &phi_bb64_13, &phi_bb64_14, &phi_bb64_16);
    tmp76 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, parameter0, phi_bb64_13, phi_bb64_14, phi_bb64_16);
    tmp77 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp78 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb64_14}, TNode<Smi>{tmp77});
    ca_.Goto(&block61, phi_bb64_10, phi_bb64_13, tmp78);
  }

  TNode<BoolT> phi_bb60_10;
  TNode<JSReceiver> phi_bb60_13;
  TNode<Smi> phi_bb60_14;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_10, &phi_bb60_13, &phi_bb60_14);
    CodeStubAssembler(state_).SetPropertyLength(TNode<Context>{parameter0}, TNode<JSAny>{phi_bb60_13}, TNode<Number>{tmp29});
    arguments.PopAndReturn(phi_bb60_13);
  }
}

} // namespace internal
} // namespace v8
