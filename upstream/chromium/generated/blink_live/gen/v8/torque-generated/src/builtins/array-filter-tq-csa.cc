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
#include "torque-generated/src/builtins/array-filter-tq-csa.h"
#include "torque-generated/src/builtins/array-every-tq-csa.h"
#include "torque-generated/src/builtins/array-filter-tq-csa.h"
#include "torque-generated/src/builtins/array-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/cast-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/frame-arguments-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"

namespace v8 {
namespace internal {

TF_BUILTIN(ArrayFilterLoopEagerDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kCallback);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kThisArg);
  USE(parameter3);
  TNode<JSAny> parameter4 = UncheckedParameter<JSAny>(Descriptor::kArray);
  USE(parameter4);
  TNode<JSAny> parameter5 = UncheckedParameter<JSAny>(Descriptor::kInitialK);
  USE(parameter5);
  TNode<JSAny> parameter6 = UncheckedParameter<JSAny>(Descriptor::kLength);
  USE(parameter6);
  TNode<JSAny> parameter7 = UncheckedParameter<JSAny>(Descriptor::kInitialTo);
  USE(parameter7);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:17:59");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:18:57");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter4}, &label5);
    ca_.Goto(&block11);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block12);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:19:57");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp6;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Number_0(state_, TNode<Object>{parameter5}, &label7);
    ca_.Goto(&block15);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:20:52");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp8;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Number_0(state_, TNode<Object>{parameter7}, &label9);
    ca_.Goto(&block19);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block20);
    }
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:21:54");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp10;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_Number_0(state_, TNode<Object>{parameter6}, &label11);
    ca_.Goto(&block23);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block24);
    }
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:22:55");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSAny> tmp12;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp12 = ca_.CallBuiltin<JSAny>(Builtin::kArrayFilterLoopContinuation, parameter0, tmp0, tmp2, parameter3, tmp4, tmp0, tmp6, tmp10, tmp8);
    CodeStubAssembler(state_).Return(tmp12);
  }
}

TF_BUILTIN(ArrayFilterLoopLazyDeoptContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSAny> parameter2 = UncheckedParameter<JSAny>(Descriptor::kCallback);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kThisArg);
  USE(parameter3);
  TNode<JSAny> parameter4 = UncheckedParameter<JSAny>(Descriptor::kArray);
  USE(parameter4);
  TNode<JSAny> parameter5 = UncheckedParameter<JSAny>(Descriptor::kInitialK);
  USE(parameter5);
  TNode<JSAny> parameter6 = UncheckedParameter<JSAny>(Descriptor::kLength);
  USE(parameter6);
  TNode<JSAny> parameter7 = UncheckedParameter<JSAny>(Descriptor::kValueK);
  USE(parameter7);
  TNode<JSAny> parameter8 = UncheckedParameter<JSAny>(Descriptor::kInitialTo);
  USE(parameter8);
  TNode<JSAny> parameter9 = UncheckedParameter<JSAny>(Descriptor::kResult);
  USE(parameter9);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<JSReceiver> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    compiler::CodeAssemblerLabel label1(&ca_);
    tmp0 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter1}, &label1);
    ca_.Goto(&block3);
    if (label1.is_used()) {
      ca_.Bind(&label1);
      ca_.Goto(&block4);
    }
  }

  if (block4.is_used()) {
    ca_.Bind(&block4);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:36:59");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp2;
  if (block3.is_used()) {
    ca_.Bind(&block3);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter2}, &label3);
    ca_.Goto(&block7);
    if (label3.is_used()) {
      ca_.Bind(&label3);
      ca_.Goto(&block8);
    }
  }

  if (block8.is_used()) {
    ca_.Bind(&block8);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:37:57");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<JSReceiver> tmp4;
  if (block7.is_used()) {
    ca_.Bind(&block7);
    compiler::CodeAssemblerLabel label5(&ca_);
    tmp4 = Cast_JSReceiver_1(state_, TNode<Context>{parameter0}, TNode<Object>{parameter4}, &label5);
    ca_.Goto(&block11);
    if (label5.is_used()) {
      ca_.Bind(&label5);
      ca_.Goto(&block12);
    }
  }

  if (block12.is_used()) {
    ca_.Bind(&block12);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:38:57");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp6;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    compiler::CodeAssemblerLabel label7(&ca_);
    tmp6 = Cast_Number_0(state_, TNode<Object>{parameter5}, &label7);
    ca_.Goto(&block15);
    if (label7.is_used()) {
      ca_.Bind(&label7);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:39:50");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp8;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label9(&ca_);
    tmp8 = Cast_Number_0(state_, TNode<Object>{parameter8}, &label9);
    ca_.Goto(&block19);
    if (label9.is_used()) {
      ca_.Bind(&label9);
      ca_.Goto(&block20);
    }
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:40:52");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Number> tmp10;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    compiler::CodeAssemblerLabel label11(&ca_);
    tmp10 = Cast_Number_0(state_, TNode<Object>{parameter6}, &label11);
    ca_.Goto(&block23);
    if (label11.is_used()) {
      ca_.Bind(&label11);
      ca_.Goto(&block24);
    }
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/array-filter.tq:41:55");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<BoolT> tmp12;
  if (block23.is_used()) {
    ca_.Bind(&block23);
    tmp12 = ToBoolean_0(state_, TNode<JSAny>{parameter9});
    ca_.Branch(tmp12, &block25, std::vector<compiler::Node*>{}, &block26, std::vector<compiler::Node*>{tmp8});
  }

  TNode<Object> tmp13;
  TNode<Number> tmp14;
  TNode<Number> tmp15;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    tmp13 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, parameter0, tmp4, tmp8, parameter7);
    tmp14 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp15 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp8}, TNode<Number>{tmp14});
    ca_.Goto(&block26, tmp15);
  }

  TNode<Number> phi_bb26_14;
  TNode<Number> tmp16;
  TNode<Number> tmp17;
  TNode<JSAny> tmp18;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_14);
    tmp16 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp17 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{tmp6}, TNode<Number>{tmp16});
    tmp18 = ca_.CallBuiltin<JSAny>(Builtin::kArrayFilterLoopContinuation, parameter0, tmp0, tmp2, parameter3, tmp4, tmp0, tmp17, tmp10, phi_bb26_14);
    CodeStubAssembler(state_).Return(tmp18);
  }
}

TF_BUILTIN(ArrayFilterLoopContinuation, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<Context> parameter0 = UncheckedParameter<Context>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSReceiver> parameter1 = UncheckedParameter<JSReceiver>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> parameter2 = UncheckedParameter<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>(Descriptor::kCallbackfn);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kThisArg);
  USE(parameter3);
  TNode<JSReceiver> parameter4 = UncheckedParameter<JSReceiver>(Descriptor::kArray);
  USE(parameter4);
  TNode<JSReceiver> parameter5 = UncheckedParameter<JSReceiver>(Descriptor::kO);
  USE(parameter5);
  TNode<Number> parameter6 = UncheckedParameter<Number>(Descriptor::kInitialK);
  USE(parameter6);
  TNode<Number> parameter7 = UncheckedParameter<Number>(Descriptor::kLength);
  USE(parameter7);
  TNode<Number> parameter8 = UncheckedParameter<Number>(Descriptor::kInitialTo);
  USE(parameter8);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  if (block0.is_used()) {
    ca_.Bind(&block0);
    ca_.Goto(&block3, parameter8, parameter6);
  }

  TNode<Number> phi_bb3_9;
  TNode<Number> phi_bb3_10;
  TNode<BoolT> tmp0;
  if (block3.is_used()) {
    ca_.Bind(&block3, &phi_bb3_9, &phi_bb3_10);
    tmp0 = NumberIsLessThan_0(state_, TNode<Number>{phi_bb3_10}, TNode<Number>{parameter7});
    ca_.Branch(tmp0, &block1, std::vector<compiler::Node*>{phi_bb3_9, phi_bb3_10}, &block2, std::vector<compiler::Node*>{phi_bb3_9, phi_bb3_10});
  }

  TNode<Number> phi_bb1_9;
  TNode<Number> phi_bb1_10;
  TNode<Boolean> tmp1;
  TNode<True> tmp2;
  TNode<BoolT> tmp3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_9, &phi_bb1_10);
    tmp1 = CodeStubAssembler(state_).HasProperty_Inline(TNode<Context>{parameter0}, TNode<JSReceiver>{parameter5}, TNode<JSAny>{phi_bb1_10});
    tmp2 = True_0(state_);
    tmp3 = CodeStubAssembler(state_).TaggedEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp1}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp2});
    ca_.Branch(tmp3, &block5, std::vector<compiler::Node*>{phi_bb1_9, phi_bb1_10}, &block6, std::vector<compiler::Node*>{phi_bb1_9, phi_bb1_10});
  }

  TNode<Number> phi_bb5_9;
  TNode<Number> phi_bb5_10;
  TNode<JSAny> tmp4;
  TNode<JSAny> tmp5;
  TNode<BoolT> tmp6;
  if (block5.is_used()) {
    ca_.Bind(&block5, &phi_bb5_9, &phi_bb5_10);
    tmp4 = CodeStubAssembler(state_).GetProperty(TNode<Context>{parameter0}, TNode<JSAny>{parameter5}, TNode<JSAny>{phi_bb5_10});
    tmp5 = CodeStubAssembler(state_).Call(TNode<Context>{parameter0}, TNode<JSAny>{parameter2}, TNode<JSAny>{parameter3}, TNode<JSAny>{tmp4}, TNode<JSAny>{phi_bb5_10}, TNode<JSAny>{parameter5});
    tmp6 = ToBoolean_0(state_, TNode<JSAny>{tmp5});
    ca_.Branch(tmp6, &block7, std::vector<compiler::Node*>{phi_bb5_9, phi_bb5_10}, &block8, std::vector<compiler::Node*>{phi_bb5_9, phi_bb5_10});
  }

  TNode<Number> phi_bb7_9;
  TNode<Number> phi_bb7_10;
  TNode<Object> tmp7;
  TNode<Number> tmp8;
  TNode<Number> tmp9;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_9, &phi_bb7_10);
    tmp7 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, parameter0, parameter4, phi_bb7_9, tmp4);
    tmp8 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp9 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb7_9}, TNode<Number>{tmp8});
    ca_.Goto(&block8, tmp9, phi_bb7_10);
  }

  TNode<Number> phi_bb8_9;
  TNode<Number> phi_bb8_10;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_9, &phi_bb8_10);
    ca_.Goto(&block6, phi_bb8_9, phi_bb8_10);
  }

  TNode<Number> phi_bb6_9;
  TNode<Number> phi_bb6_10;
  TNode<Number> tmp10;
  TNode<Number> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6, &phi_bb6_9, &phi_bb6_10);
    tmp10 = FromConstexpr_Number_constexpr_int31_0(state_, 1);
    tmp11 = CodeStubAssembler(state_).NumberAdd(TNode<Number>{phi_bb6_10}, TNode<Number>{tmp10});
    ca_.Goto(&block3, phi_bb6_9, tmp11);
  }

  TNode<Number> phi_bb2_9;
  TNode<Number> phi_bb2_10;
  if (block2.is_used()) {
    ca_.Bind(&block2, &phi_bb2_9, &phi_bb2_10);
    CodeStubAssembler(state_).Return(parameter4);
  }
}

// https://crsrc.org/c/v8/src/builtins/array-filter.tq?l=96&c=1
void FastArrayFilter_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSArray> p_fastO, TNode<Smi> p_len, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_callbackfn, TNode<JSAny> p_thisArg, TNode<JSArray> p_output, compiler::CodeAssemblerLabel* label_Bailout, compiler::TypedCodeAssemblerVariable<Number>* label_Bailout_parameter_0, compiler::TypedCodeAssemblerVariable<Number>* label_Bailout_parameter_1) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block17(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block18(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi, Smi> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi, Smi> block28(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi, Smi> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi, Smi> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, Smi, Smi, JSAny> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block40(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block41(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block42(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block43(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block47(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block46(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block48(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block51(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block55(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block54(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block52(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block57(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block56(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block53(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block49(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block58(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block62(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block61(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block59(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block65(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block66(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, BoolT> block67(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block64(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block63(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block69(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block68(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block60(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi> block50(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block34(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Smi, Smi, JSArray, JSArray> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block70(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<Smi> tmp1;
  TNode<JSArray> tmp2;
  TNode<JSArray> tmp3;
  TNode<Map> tmp4;
  TNode<BoolT> tmp5;
  TNode<BoolT> tmp6;
  TNode<BoolT> tmp7;
  TNode<BoolT> tmp8;
  TNode<JSArray> tmp9;
  TNode<JSArray> tmp10;
  TNode<Map> tmp11;
  TNode<BoolT> tmp12;
  TNode<BoolT> tmp13;
  TNode<BoolT> tmp14;
  TNode<BoolT> tmp15;
  TNode<Int32T> tmp16;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    std::tie(tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8) = NewFastJSArrayWitness_0(state_, TNode<JSArray>{p_fastO}).Flatten();
    std::tie(tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15) = NewFastJSArrayWitness_0(state_, TNode<JSArray>{p_output}).Flatten();
    compiler::CodeAssemblerLabel label17(&ca_);
    tmp16 = CodeStubAssembler(state_).EnsureArrayPushable(TNode<Context>{p_context}, TNode<Map>{tmp11}, &label17);
    ca_.Goto(&block6);
    if (label17.is_used()) {
      ca_.Bind(&label17);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    ca_.Goto(&block1, tmp0, tmp1);
  }

  TNode<BoolT> tmp18;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    EnsureWriteableFastElements_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp10});
    tmp18 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block10, tmp0, tmp1, tmp3, tmp10);
  }

  TNode<Smi> phi_bb10_6;
  TNode<Smi> phi_bb10_7;
  TNode<JSArray> phi_bb10_9;
  TNode<JSArray> phi_bb10_16;
  TNode<BoolT> tmp19;
  if (block10.is_used()) {
    ca_.Bind(&block10, &phi_bb10_6, &phi_bb10_7, &phi_bb10_9, &phi_bb10_16);
    tmp19 = CodeStubAssembler(state_).SmiLessThan(TNode<Smi>{phi_bb10_6}, TNode<Smi>{p_len});
    ca_.Branch(tmp19, &block8, std::vector<compiler::Node*>{phi_bb10_6, phi_bb10_7, phi_bb10_9, phi_bb10_16}, &block9, std::vector<compiler::Node*>{phi_bb10_6, phi_bb10_7, phi_bb10_9, phi_bb10_16});
  }

  TNode<Smi> phi_bb8_6;
  TNode<Smi> phi_bb8_7;
  TNode<JSArray> phi_bb8_9;
  TNode<JSArray> phi_bb8_16;
  TNode<IntPtrT> tmp20;
  TNode<Map> tmp21;
  TNode<BoolT> tmp22;
  if (block8.is_used()) {
    ca_.Bind(&block8, &phi_bb8_6, &phi_bb8_7, &phi_bb8_9, &phi_bb8_16);
    tmp20 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp21 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp2, tmp20});
    tmp22 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp21}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp4});
    ca_.Branch(tmp22, &block15, std::vector<compiler::Node*>{phi_bb8_6, phi_bb8_7, phi_bb8_9, phi_bb8_16}, &block16, std::vector<compiler::Node*>{phi_bb8_6, phi_bb8_7, phi_bb8_9, phi_bb8_16});
  }

  TNode<Smi> phi_bb15_6;
  TNode<Smi> phi_bb15_7;
  TNode<JSArray> phi_bb15_9;
  TNode<JSArray> phi_bb15_16;
  if (block15.is_used()) {
    ca_.Bind(&block15, &phi_bb15_6, &phi_bb15_7, &phi_bb15_9, &phi_bb15_16);
    ca_.Goto(&block13, phi_bb15_6, phi_bb15_7, phi_bb15_9, phi_bb15_16);
  }

  TNode<Smi> phi_bb16_6;
  TNode<Smi> phi_bb16_7;
  TNode<JSArray> phi_bb16_9;
  TNode<JSArray> phi_bb16_16;
  TNode<BoolT> tmp23;
  if (block16.is_used()) {
    ca_.Bind(&block16, &phi_bb16_6, &phi_bb16_7, &phi_bb16_9, &phi_bb16_16);
    tmp23 = CodeStubAssembler(state_).IsNoElementsProtectorCellInvalid();
    ca_.Branch(tmp23, &block17, std::vector<compiler::Node*>{phi_bb16_6, phi_bb16_7, phi_bb16_9, phi_bb16_16}, &block18, std::vector<compiler::Node*>{phi_bb16_6, phi_bb16_7, phi_bb16_9, phi_bb16_16});
  }

  TNode<Smi> phi_bb17_6;
  TNode<Smi> phi_bb17_7;
  TNode<JSArray> phi_bb17_9;
  TNode<JSArray> phi_bb17_16;
  if (block17.is_used()) {
    ca_.Bind(&block17, &phi_bb17_6, &phi_bb17_7, &phi_bb17_9, &phi_bb17_16);
    ca_.Goto(&block13, phi_bb17_6, phi_bb17_7, phi_bb17_9, phi_bb17_16);
  }

  TNode<Smi> phi_bb18_6;
  TNode<Smi> phi_bb18_7;
  TNode<JSArray> phi_bb18_9;
  TNode<JSArray> phi_bb18_16;
  TNode<JSArray> tmp24;
  TNode<Smi> tmp25;
  TNode<BoolT> tmp26;
  if (block18.is_used()) {
    ca_.Bind(&block18, &phi_bb18_6, &phi_bb18_7, &phi_bb18_9, &phi_bb18_16);
    tmp24 = (TNode<JSArray>{tmp2});
    tmp25 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp24});
    tmp26 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{phi_bb18_6}, TNode<Smi>{tmp25});
    ca_.Branch(tmp26, &block19, std::vector<compiler::Node*>{phi_bb18_6, phi_bb18_7, phi_bb18_16}, &block20, std::vector<compiler::Node*>{phi_bb18_6, phi_bb18_7, phi_bb18_16});
  }

  TNode<Smi> phi_bb13_6;
  TNode<Smi> phi_bb13_7;
  TNode<JSArray> phi_bb13_9;
  TNode<JSArray> phi_bb13_16;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6, &phi_bb13_7, &phi_bb13_9, &phi_bb13_16);
    ca_.Goto(&block1, phi_bb13_6, phi_bb13_7);
  }

  TNode<Smi> phi_bb19_6;
  TNode<Smi> phi_bb19_7;
  TNode<JSArray> phi_bb19_16;
  if (block19.is_used()) {
    ca_.Bind(&block19, &phi_bb19_6, &phi_bb19_7, &phi_bb19_16);
    ca_.Goto(&block1, phi_bb19_6, phi_bb19_7);
  }

  TNode<Smi> phi_bb20_6;
  TNode<Smi> phi_bb20_7;
  TNode<JSArray> phi_bb20_16;
  if (block20.is_used()) {
    ca_.Bind(&block20, &phi_bb20_6, &phi_bb20_7, &phi_bb20_16);
    ca_.Branch(tmp5, &block25, std::vector<compiler::Node*>{phi_bb20_6, phi_bb20_7, phi_bb20_16, phi_bb20_6, phi_bb20_6}, &block26, std::vector<compiler::Node*>{phi_bb20_6, phi_bb20_7, phi_bb20_16, phi_bb20_6, phi_bb20_6});
  }

  TNode<Smi> phi_bb25_6;
  TNode<Smi> phi_bb25_7;
  TNode<JSArray> phi_bb25_16;
  TNode<Smi> phi_bb25_22;
  TNode<Smi> phi_bb25_25;
  TNode<JSAny> tmp27;
  if (block25.is_used()) {
    ca_.Bind(&block25, &phi_bb25_6, &phi_bb25_7, &phi_bb25_16, &phi_bb25_22, &phi_bb25_25);
    compiler::CodeAssemblerLabel label28(&ca_);
    tmp27 = LoadElementNoHole_FixedDoubleArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp24}, TNode<Smi>{phi_bb25_25}, &label28);
    ca_.Goto(&block28, phi_bb25_6, phi_bb25_7, phi_bb25_16, phi_bb25_22, phi_bb25_25, phi_bb25_25);
    if (label28.is_used()) {
      ca_.Bind(&label28);
      ca_.Goto(&block29, phi_bb25_6, phi_bb25_7, phi_bb25_16, phi_bb25_22, phi_bb25_25, phi_bb25_25);
    }
  }

  TNode<Smi> phi_bb29_6;
  TNode<Smi> phi_bb29_7;
  TNode<JSArray> phi_bb29_16;
  TNode<Smi> phi_bb29_22;
  TNode<Smi> phi_bb29_25;
  TNode<Smi> phi_bb29_27;
  if (block29.is_used()) {
    ca_.Bind(&block29, &phi_bb29_6, &phi_bb29_7, &phi_bb29_16, &phi_bb29_22, &phi_bb29_25, &phi_bb29_27);
    ca_.Goto(&block23, phi_bb29_6, phi_bb29_7, phi_bb29_16);
  }

  TNode<Smi> phi_bb28_6;
  TNode<Smi> phi_bb28_7;
  TNode<JSArray> phi_bb28_16;
  TNode<Smi> phi_bb28_22;
  TNode<Smi> phi_bb28_25;
  TNode<Smi> phi_bb28_27;
  if (block28.is_used()) {
    ca_.Bind(&block28, &phi_bb28_6, &phi_bb28_7, &phi_bb28_16, &phi_bb28_22, &phi_bb28_25, &phi_bb28_27);
    ca_.Goto(&block24, phi_bb28_6, phi_bb28_7, phi_bb28_16, phi_bb28_22, phi_bb28_25, tmp27);
  }

  TNode<Smi> phi_bb26_6;
  TNode<Smi> phi_bb26_7;
  TNode<JSArray> phi_bb26_16;
  TNode<Smi> phi_bb26_22;
  TNode<Smi> phi_bb26_25;
  TNode<JSAny> tmp29;
  if (block26.is_used()) {
    ca_.Bind(&block26, &phi_bb26_6, &phi_bb26_7, &phi_bb26_16, &phi_bb26_22, &phi_bb26_25);
    compiler::CodeAssemblerLabel label30(&ca_);
    tmp29 = LoadElementNoHole_FixedArray_0(state_, TNode<Context>{p_context}, TNode<JSArray>{tmp24}, TNode<Smi>{phi_bb26_25}, &label30);
    ca_.Goto(&block30, phi_bb26_6, phi_bb26_7, phi_bb26_16, phi_bb26_22, phi_bb26_25, phi_bb26_25);
    if (label30.is_used()) {
      ca_.Bind(&label30);
      ca_.Goto(&block31, phi_bb26_6, phi_bb26_7, phi_bb26_16, phi_bb26_22, phi_bb26_25, phi_bb26_25);
    }
  }

  TNode<Smi> phi_bb31_6;
  TNode<Smi> phi_bb31_7;
  TNode<JSArray> phi_bb31_16;
  TNode<Smi> phi_bb31_22;
  TNode<Smi> phi_bb31_25;
  TNode<Smi> phi_bb31_27;
  if (block31.is_used()) {
    ca_.Bind(&block31, &phi_bb31_6, &phi_bb31_7, &phi_bb31_16, &phi_bb31_22, &phi_bb31_25, &phi_bb31_27);
    ca_.Goto(&block23, phi_bb31_6, phi_bb31_7, phi_bb31_16);
  }

  TNode<Smi> phi_bb30_6;
  TNode<Smi> phi_bb30_7;
  TNode<JSArray> phi_bb30_16;
  TNode<Smi> phi_bb30_22;
  TNode<Smi> phi_bb30_25;
  TNode<Smi> phi_bb30_27;
  if (block30.is_used()) {
    ca_.Bind(&block30, &phi_bb30_6, &phi_bb30_7, &phi_bb30_16, &phi_bb30_22, &phi_bb30_25, &phi_bb30_27);
    ca_.Goto(&block24, phi_bb30_6, phi_bb30_7, phi_bb30_16, phi_bb30_22, phi_bb30_25, tmp29);
  }

  TNode<Smi> phi_bb24_6;
  TNode<Smi> phi_bb24_7;
  TNode<JSArray> phi_bb24_16;
  TNode<Smi> phi_bb24_22;
  TNode<Smi> phi_bb24_25;
  TNode<JSAny> phi_bb24_26;
  TNode<JSAny> tmp31;
  TNode<BoolT> tmp32;
  if (block24.is_used()) {
    ca_.Bind(&block24, &phi_bb24_6, &phi_bb24_7, &phi_bb24_16, &phi_bb24_22, &phi_bb24_25, &phi_bb24_26);
    tmp31 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<JSAny>{p_callbackfn}, TNode<JSAny>{p_thisArg}, TNode<JSAny>{phi_bb24_26}, TNode<JSAny>{phi_bb24_6}, TNode<JSAny>{tmp24});
    tmp32 = ToBoolean_0(state_, TNode<JSAny>{tmp31});
    ca_.Branch(tmp32, &block33, std::vector<compiler::Node*>{phi_bb24_6, phi_bb24_7, phi_bb24_16}, &block34, std::vector<compiler::Node*>{phi_bb24_6, phi_bb24_7, phi_bb24_16});
  }

  TNode<Smi> phi_bb23_6;
  TNode<Smi> phi_bb23_7;
  TNode<JSArray> phi_bb23_16;
  if (block23.is_used()) {
    ca_.Bind(&block23, &phi_bb23_6, &phi_bb23_7, &phi_bb23_16);
    ca_.Goto(&block11, phi_bb23_6, phi_bb23_7, phi_bb23_16);
  }

  TNode<Smi> phi_bb33_6;
  TNode<Smi> phi_bb33_7;
  TNode<JSArray> phi_bb33_16;
  TNode<IntPtrT> tmp33;
  TNode<Map> tmp34;
  TNode<BoolT> tmp35;
  if (block33.is_used()) {
    ca_.Bind(&block33, &phi_bb33_6, &phi_bb33_7, &phi_bb33_16);
    tmp33 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp34 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp9, tmp33});
    tmp35 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp34}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp11});
    ca_.Branch(tmp35, &block38, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7, phi_bb33_16}, &block39, std::vector<compiler::Node*>{phi_bb33_6, phi_bb33_7, phi_bb33_16});
  }

  TNode<Smi> phi_bb38_6;
  TNode<Smi> phi_bb38_7;
  TNode<JSArray> phi_bb38_16;
  if (block38.is_used()) {
    ca_.Bind(&block38, &phi_bb38_6, &phi_bb38_7, &phi_bb38_16);
    ca_.Goto(&block36, phi_bb38_6, phi_bb38_7, phi_bb38_16);
  }

  TNode<Smi> phi_bb39_6;
  TNode<Smi> phi_bb39_7;
  TNode<JSArray> phi_bb39_16;
  TNode<BoolT> tmp36;
  if (block39.is_used()) {
    ca_.Bind(&block39, &phi_bb39_6, &phi_bb39_7, &phi_bb39_16);
    tmp36 = CodeStubAssembler(state_).IsNoElementsProtectorCellInvalid();
    ca_.Branch(tmp36, &block40, std::vector<compiler::Node*>{phi_bb39_6, phi_bb39_7, phi_bb39_16}, &block41, std::vector<compiler::Node*>{phi_bb39_6, phi_bb39_7, phi_bb39_16});
  }

  TNode<Smi> phi_bb40_6;
  TNode<Smi> phi_bb40_7;
  TNode<JSArray> phi_bb40_16;
  if (block40.is_used()) {
    ca_.Bind(&block40, &phi_bb40_6, &phi_bb40_7, &phi_bb40_16);
    ca_.Goto(&block36, phi_bb40_6, phi_bb40_7, phi_bb40_16);
  }

  TNode<Smi> phi_bb41_6;
  TNode<Smi> phi_bb41_7;
  TNode<JSArray> phi_bb41_16;
  TNode<JSArray> tmp37;
  TNode<Smi> tmp38;
  TNode<BoolT> tmp39;
  if (block41.is_used()) {
    ca_.Bind(&block41, &phi_bb41_6, &phi_bb41_7, &phi_bb41_16);
    tmp37 = (TNode<JSArray>{tmp9});
    tmp38 = CodeStubAssembler(state_).LoadFastJSArrayLength(TNode<JSArray>{tmp37});
    tmp39 = CodeStubAssembler(state_).SmiNotEqual(TNode<Smi>{tmp38}, TNode<Smi>{phi_bb41_7});
    ca_.Branch(tmp39, &block42, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7}, &block43, std::vector<compiler::Node*>{phi_bb41_6, phi_bb41_7});
  }

  TNode<Smi> phi_bb42_6;
  TNode<Smi> phi_bb42_7;
  if (block42.is_used()) {
    ca_.Bind(&block42, &phi_bb42_6, &phi_bb42_7);
    ca_.Goto(&block36, phi_bb42_6, phi_bb42_7, tmp37);
  }

  TNode<Smi> phi_bb43_6;
  TNode<Smi> phi_bb43_7;
  if (block43.is_used()) {
    ca_.Bind(&block43, &phi_bb43_6, &phi_bb43_7);
    ca_.Branch(tmp18, &block46, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7}, &block47, std::vector<compiler::Node*>{phi_bb43_6, phi_bb43_7});
  }

  TNode<Smi> phi_bb47_6;
  TNode<Smi> phi_bb47_7;
  if (block47.is_used()) {
    ca_.Bind(&block47, &phi_bb47_6, &phi_bb47_7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/objects/js-array.tq", 290});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.arrayIsPushable' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb46_6;
  TNode<Smi> phi_bb46_7;
  if (block46.is_used()) {
    ca_.Bind(&block46, &phi_bb46_6, &phi_bb46_7);
    ca_.Branch(tmp12, &block48, std::vector<compiler::Node*>{phi_bb46_6, phi_bb46_7}, &block49, std::vector<compiler::Node*>{phi_bb46_6, phi_bb46_7});
  }

  TNode<Smi> phi_bb48_6;
  TNode<Smi> phi_bb48_7;
  if (block48.is_used()) {
    ca_.Bind(&block48, &phi_bb48_6, &phi_bb48_7);
    ca_.Branch(tmp13, &block51, std::vector<compiler::Node*>{phi_bb48_6, phi_bb48_7}, &block52, std::vector<compiler::Node*>{phi_bb48_6, phi_bb48_7});
  }

  TNode<Smi> phi_bb51_6;
  TNode<Smi> phi_bb51_7;
  if (block51.is_used()) {
    ca_.Bind(&block51, &phi_bb51_6, &phi_bb51_7);
    compiler::CodeAssemblerLabel label40(&ca_);
    CodeStubAssembler(state_).BuildAppendJSArray(CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_DOUBLE_ELEMENTS), TNode<JSArray>{tmp37}, TNode<JSAny>{phi_bb24_26}, &label40);
    ca_.Goto(&block54, phi_bb51_6, phi_bb51_7);
    if (label40.is_used()) {
      ca_.Bind(&label40);
      ca_.Goto(&block55, phi_bb51_6, phi_bb51_7);
    }
  }

  TNode<Smi> phi_bb55_6;
  TNode<Smi> phi_bb55_7;
  if (block55.is_used()) {
    ca_.Bind(&block55, &phi_bb55_6, &phi_bb55_7);
    ca_.Goto(&block36, phi_bb55_6, phi_bb55_7, tmp37);
  }

  TNode<Smi> phi_bb54_6;
  TNode<Smi> phi_bb54_7;
  if (block54.is_used()) {
    ca_.Bind(&block54, &phi_bb54_6, &phi_bb54_7);
    ca_.Goto(&block53, phi_bb54_6, phi_bb54_7);
  }

  TNode<Smi> phi_bb52_6;
  TNode<Smi> phi_bb52_7;
  if (block52.is_used()) {
    ca_.Bind(&block52, &phi_bb52_6, &phi_bb52_7);
    compiler::CodeAssemblerLabel label41(&ca_);
    CodeStubAssembler(state_).BuildAppendJSArray(CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_DOUBLE_ELEMENTS), TNode<JSArray>{tmp37}, TNode<JSAny>{phi_bb24_26}, &label41);
    ca_.Goto(&block56, phi_bb52_6, phi_bb52_7);
    if (label41.is_used()) {
      ca_.Bind(&label41);
      ca_.Goto(&block57, phi_bb52_6, phi_bb52_7);
    }
  }

  TNode<Smi> phi_bb57_6;
  TNode<Smi> phi_bb57_7;
  if (block57.is_used()) {
    ca_.Bind(&block57, &phi_bb57_6, &phi_bb57_7);
    ca_.Goto(&block36, phi_bb57_6, phi_bb57_7, tmp37);
  }

  TNode<Smi> phi_bb56_6;
  TNode<Smi> phi_bb56_7;
  if (block56.is_used()) {
    ca_.Bind(&block56, &phi_bb56_6, &phi_bb56_7);
    ca_.Goto(&block53, phi_bb56_6, phi_bb56_7);
  }

  TNode<Smi> phi_bb53_6;
  TNode<Smi> phi_bb53_7;
  if (block53.is_used()) {
    ca_.Bind(&block53, &phi_bb53_6, &phi_bb53_7);
    ca_.Goto(&block50, phi_bb53_6, phi_bb53_7);
  }

  TNode<Smi> phi_bb49_6;
  TNode<Smi> phi_bb49_7;
  if (block49.is_used()) {
    ca_.Bind(&block49, &phi_bb49_6, &phi_bb49_7);
    ca_.Branch(tmp14, &block58, std::vector<compiler::Node*>{phi_bb49_6, phi_bb49_7}, &block59, std::vector<compiler::Node*>{phi_bb49_6, phi_bb49_7});
  }

  TNode<Smi> phi_bb58_6;
  TNode<Smi> phi_bb58_7;
  if (block58.is_used()) {
    ca_.Bind(&block58, &phi_bb58_6, &phi_bb58_7);
    compiler::CodeAssemblerLabel label42(&ca_);
    CodeStubAssembler(state_).BuildAppendJSArray(CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_SMI_ELEMENTS), TNode<JSArray>{tmp37}, TNode<JSAny>{phi_bb24_26}, &label42);
    ca_.Goto(&block61, phi_bb58_6, phi_bb58_7);
    if (label42.is_used()) {
      ca_.Bind(&label42);
      ca_.Goto(&block62, phi_bb58_6, phi_bb58_7);
    }
  }

  TNode<Smi> phi_bb62_6;
  TNode<Smi> phi_bb62_7;
  if (block62.is_used()) {
    ca_.Bind(&block62, &phi_bb62_6, &phi_bb62_7);
    ca_.Goto(&block36, phi_bb62_6, phi_bb62_7, tmp37);
  }

  TNode<Smi> phi_bb61_6;
  TNode<Smi> phi_bb61_7;
  if (block61.is_used()) {
    ca_.Bind(&block61, &phi_bb61_6, &phi_bb61_7);
    ca_.Goto(&block60, phi_bb61_6, phi_bb61_7);
  }

  TNode<Smi> phi_bb59_6;
  TNode<Smi> phi_bb59_7;
  TNode<Int32T> tmp43;
  TNode<Int32T> tmp44;
  TNode<BoolT> tmp45;
  if (block59.is_used()) {
    ca_.Bind(&block59, &phi_bb59_6, &phi_bb59_7);
    tmp43 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp11});
    tmp44 = FromConstexpr_ElementsKind_constexpr_HOLEY_ELEMENTS_0(state_, ElementsKind::HOLEY_ELEMENTS);
    tmp45 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp43}, TNode<Int32T>{tmp44});
    ca_.Branch(tmp45, &block65, std::vector<compiler::Node*>{phi_bb59_6, phi_bb59_7}, &block66, std::vector<compiler::Node*>{phi_bb59_6, phi_bb59_7});
  }

  TNode<Smi> phi_bb65_6;
  TNode<Smi> phi_bb65_7;
  TNode<BoolT> tmp46;
  if (block65.is_used()) {
    ca_.Bind(&block65, &phi_bb65_6, &phi_bb65_7);
    tmp46 = FromConstexpr_bool_constexpr_bool_0(state_, true);
    ca_.Goto(&block67, phi_bb65_6, phi_bb65_7, tmp46);
  }

  TNode<Smi> phi_bb66_6;
  TNode<Smi> phi_bb66_7;
  TNode<Int32T> tmp47;
  TNode<Int32T> tmp48;
  TNode<BoolT> tmp49;
  if (block66.is_used()) {
    ca_.Bind(&block66, &phi_bb66_6, &phi_bb66_7);
    tmp47 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp11});
    tmp48 = FromConstexpr_ElementsKind_constexpr_PACKED_ELEMENTS_0(state_, ElementsKind::PACKED_ELEMENTS);
    tmp49 = CodeStubAssembler(state_).ElementsKindEqual(TNode<Int32T>{tmp47}, TNode<Int32T>{tmp48});
    ca_.Goto(&block67, phi_bb66_6, phi_bb66_7, tmp49);
  }

  TNode<Smi> phi_bb67_6;
  TNode<Smi> phi_bb67_7;
  TNode<BoolT> phi_bb67_27;
  if (block67.is_used()) {
    ca_.Bind(&block67, &phi_bb67_6, &phi_bb67_7, &phi_bb67_27);
    ca_.Branch(phi_bb67_27, &block63, std::vector<compiler::Node*>{phi_bb67_6, phi_bb67_7}, &block64, std::vector<compiler::Node*>{phi_bb67_6, phi_bb67_7});
  }

  TNode<Smi> phi_bb64_6;
  TNode<Smi> phi_bb64_7;
  if (block64.is_used()) {
    ca_.Bind(&block64, &phi_bb64_6, &phi_bb64_7);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/objects/js-array.tq", 312});
      CodeStubAssembler(state_).FailAssert("Torque assert 'this.map.elements_kind == ElementsKind::HOLEY_ELEMENTS || this.map.elements_kind == ElementsKind::PACKED_ELEMENTS' failed", pos_stack);
    }
  }

  TNode<Smi> phi_bb63_6;
  TNode<Smi> phi_bb63_7;
  if (block63.is_used()) {
    ca_.Bind(&block63, &phi_bb63_6, &phi_bb63_7);
    compiler::CodeAssemblerLabel label50(&ca_);
    CodeStubAssembler(state_).BuildAppendJSArray(CastIfEnumClass<ElementsKind>(ElementsKind::HOLEY_ELEMENTS), TNode<JSArray>{tmp37}, TNode<JSAny>{phi_bb24_26}, &label50);
    ca_.Goto(&block68, phi_bb63_6, phi_bb63_7);
    if (label50.is_used()) {
      ca_.Bind(&label50);
      ca_.Goto(&block69, phi_bb63_6, phi_bb63_7);
    }
  }

  TNode<Smi> phi_bb69_6;
  TNode<Smi> phi_bb69_7;
  if (block69.is_used()) {
    ca_.Bind(&block69, &phi_bb69_6, &phi_bb69_7);
    ca_.Goto(&block36, phi_bb69_6, phi_bb69_7, tmp37);
  }

  TNode<Smi> phi_bb68_6;
  TNode<Smi> phi_bb68_7;
  if (block68.is_used()) {
    ca_.Bind(&block68, &phi_bb68_6, &phi_bb68_7);
    ca_.Goto(&block60, phi_bb68_6, phi_bb68_7);
  }

  TNode<Smi> phi_bb60_6;
  TNode<Smi> phi_bb60_7;
  if (block60.is_used()) {
    ca_.Bind(&block60, &phi_bb60_6, &phi_bb60_7);
    ca_.Goto(&block50, phi_bb60_6, phi_bb60_7);
  }

  TNode<Smi> phi_bb50_6;
  TNode<Smi> phi_bb50_7;
  if (block50.is_used()) {
    ca_.Bind(&block50, &phi_bb50_6, &phi_bb50_7);
    ca_.Goto(&block35, phi_bb50_6, phi_bb50_7, tmp37);
  }

  TNode<Smi> phi_bb36_6;
  TNode<Smi> phi_bb36_7;
  TNode<JSArray> phi_bb36_16;
  TNode<Object> tmp51;
  if (block36.is_used()) {
    ca_.Bind(&block36, &phi_bb36_6, &phi_bb36_7, &phi_bb36_16);
    tmp51 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, p_context, tmp9, phi_bb36_7, phi_bb24_26);
    ca_.Goto(&block35, phi_bb36_6, phi_bb36_7, phi_bb36_16);
  }

  TNode<Smi> phi_bb35_6;
  TNode<Smi> phi_bb35_7;
  TNode<JSArray> phi_bb35_16;
  TNode<Smi> tmp52;
  TNode<Smi> tmp53;
  if (block35.is_used()) {
    ca_.Bind(&block35, &phi_bb35_6, &phi_bb35_7, &phi_bb35_16);
    tmp52 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp53 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb35_7}, TNode<Smi>{tmp52});
    ca_.Goto(&block34, phi_bb35_6, tmp53, phi_bb35_16);
  }

  TNode<Smi> phi_bb34_6;
  TNode<Smi> phi_bb34_7;
  TNode<JSArray> phi_bb34_16;
  if (block34.is_used()) {
    ca_.Bind(&block34, &phi_bb34_6, &phi_bb34_7, &phi_bb34_16);
    ca_.Goto(&block11, phi_bb34_6, phi_bb34_7, phi_bb34_16);
  }

  TNode<Smi> phi_bb11_6;
  TNode<Smi> phi_bb11_7;
  TNode<JSArray> phi_bb11_16;
  TNode<Smi> tmp54;
  TNode<Smi> tmp55;
  if (block11.is_used()) {
    ca_.Bind(&block11, &phi_bb11_6, &phi_bb11_7, &phi_bb11_16);
    tmp54 = FromConstexpr_Smi_constexpr_int31_0(state_, 1);
    tmp55 = CodeStubAssembler(state_).SmiAdd(TNode<Smi>{phi_bb11_6}, TNode<Smi>{tmp54});
    ca_.Goto(&block10, tmp55, phi_bb11_7, tmp24, phi_bb11_16);
  }

  TNode<Smi> phi_bb9_6;
  TNode<Smi> phi_bb9_7;
  TNode<JSArray> phi_bb9_9;
  TNode<JSArray> phi_bb9_16;
  if (block9.is_used()) {
    ca_.Bind(&block9, &phi_bb9_6, &phi_bb9_7, &phi_bb9_9, &phi_bb9_16);
    ca_.Goto(&block70);
  }

  TNode<Number> phi_bb1_0;
  TNode<Number> phi_bb1_1;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_0, &phi_bb1_1);
    *label_Bailout_parameter_1 = phi_bb1_1;
    *label_Bailout_parameter_0 = phi_bb1_0;
    ca_.Goto(label_Bailout);
  }

    ca_.Bind(&block70);
}

// https://crsrc.org/c/v8/src/builtins/array-filter.tq?l=135&c=1
TNode<JSReceiver> FastFilterSpeciesCreate_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, compiler::CodeAssemblerLabel* label_Slow) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Smi> tmp0;
  TNode<BoolT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp1 = CodeStubAssembler(state_).IsArraySpeciesProtectorCellInvalid();
    ca_.Branch(tmp1, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block1);
  }

  TNode<JSArray> tmp2;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    compiler::CodeAssemblerLabel label3(&ca_);
    tmp2 = Cast_FastJSArray_0(state_, TNode<Context>{p_context}, TNode<HeapObject>{p_receiver}, &label3);
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

  TNode<IntPtrT> tmp4;
  TNode<Map> tmp5;
  TNode<Int32T> tmp6;
  TNode<NativeContext> tmp7;
  TNode<Map> tmp8;
  TNode<JSArray> tmp9;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp4 = FromConstexpr_intptr_constexpr_int31_0(state_, 0);
    tmp5 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp2, tmp4});
    tmp6 = CodeStubAssembler(state_).LoadMapElementsKind(TNode<Map>{tmp5});
    tmp7 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp8 = CodeStubAssembler(state_).LoadJSArrayElementsMap(TNode<Int32T>{tmp6}, TNode<NativeContext>{tmp7});
    tmp9 = CodeStubAssembler(state_).AllocateJSArray(CastIfEnumClass<ElementsKind>(ElementsKind::PACKED_SMI_ELEMENTS), TNode<Map>{tmp8}, TNode<Smi>{tmp0}, TNode<Smi>{tmp0});
    ca_.Goto(&block7);
  }

  if (block1.is_used()) {
    ca_.Bind(&block1);
    ca_.Goto(label_Slow);
  }

    ca_.Bind(&block7);
  return TNode<JSReceiver>{tmp9};
}

TF_BUILTIN(ArrayFilter, CodeStubAssembler) {
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
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block4(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block5(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block16(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block19(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block24(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block23(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<Number, Number> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSReceiver, Number, Number> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kDeferred);
    ca_.Goto(&block0);

  TNode<JSAny> tmp0;
  TNode<JSReceiver> tmp1;
  TNode<Number> tmp2;
  TNode<IntPtrT> tmp3;
  TNode<BoolT> tmp4;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = RequireObjectCoercible_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, "Array.prototype.filter");
    tmp1 = CodeStubAssembler(state_).ToObject_Inline(TNode<Context>{parameter0}, TNode<JSAny>{parameter1});
    tmp2 = GetLengthProperty_0(state_, TNode<Context>{parameter0}, TNode<JSAny>{tmp1});
    tmp3 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp4 = CodeStubAssembler(state_).WordEqual(TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{tmp3});
    ca_.Branch(tmp4, &block3, std::vector<compiler::Node*>{}, &block4, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp5;
  TNode<JSAny> tmp6;
  TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> tmp7;
  if (block4.is_used()) {
    ca_.Bind(&block4);
    tmp5 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp6 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp5});
    compiler::CodeAssemblerLabel label8(&ca_);
    tmp7 = Cast_Callable_1(state_, TNode<Context>{parameter0}, TNode<Object>{tmp6}, &label8);
    ca_.Goto(&block5);
    if (label8.is_used()) {
      ca_.Bind(&label8);
      ca_.Goto(&block6);
    }
  }

  if (block6.is_used()) {
    ca_.Bind(&block6);
    ca_.Goto(&block2);
  }

  TNode<IntPtrT> tmp9;
  TNode<JSAny> tmp10;
  TNode<Number> tmp11;
  TNode<Number> tmp12;
  TNode<JSReceiver> tmp13;
  if (block5.is_used()) {
    ca_.Bind(&block5);
    tmp9 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp10 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp9});
    tmp11 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp12 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    compiler::CodeAssemblerLabel label14(&ca_);
    tmp13 = FastFilterSpeciesCreate_0(state_, TNode<Context>{parameter0}, TNode<JSReceiver>{tmp1}, &label14);
    ca_.Goto(&block9);
    if (label14.is_used()) {
      ca_.Bind(&label14);
      ca_.Goto(&block10);
    }
  }

  TNode<Number> tmp15;
  TNode<JSReceiver> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp15 = FromConstexpr_Number_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp16 = CodeStubAssembler(state_).ArraySpeciesCreate(TNode<Context>{parameter0}, TNode<JSAny>{parameter1}, TNode<Number>{tmp15});
    ca_.Goto(&block7, tmp16, tmp11, tmp12);
  }

  TNode<Smi> tmp17;
  if (block9.is_used()) {
    ca_.Bind(&block9);
    compiler::CodeAssemblerLabel label18(&ca_);
    tmp17 = Cast_Smi_0(state_, TNode<Object>{tmp2}, &label18);
    ca_.Goto(&block15);
    if (label18.is_used()) {
      ca_.Bind(&label18);
      ca_.Goto(&block16);
    }
  }

  if (block16.is_used()) {
    ca_.Bind(&block16);
    ca_.Goto(&block12, tmp11, tmp12);
  }

  TNode<JSArray> tmp19;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    compiler::CodeAssemblerLabel label20(&ca_);
    tmp19 = Cast_FastJSArray_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{tmp13}, &label20);
    ca_.Goto(&block19);
    if (label20.is_used()) {
      ca_.Bind(&label20);
      ca_.Goto(&block20);
    }
  }

  if (block20.is_used()) {
    ca_.Bind(&block20);
    ca_.Goto(&block12, tmp11, tmp12);
  }

  TNode<JSArray> tmp21;
  if (block19.is_used()) {
    ca_.Bind(&block19);
    compiler::CodeAssemblerLabel label22(&ca_);
    tmp21 = Cast_FastJSArray_0(state_, TNode<Context>{parameter0}, TNode<HeapObject>{tmp1}, &label22);
    ca_.Goto(&block23);
    if (label22.is_used()) {
      ca_.Bind(&label22);
      ca_.Goto(&block24);
    }
  }

  if (block24.is_used()) {
    ca_.Bind(&block24);
    ca_.Goto(&block12, tmp11, tmp12);
  }

    compiler::TypedCodeAssemblerVariable<Number> tmp24(&ca_);
    compiler::TypedCodeAssemblerVariable<Number> tmp25(&ca_);
  if (block23.is_used()) {
    ca_.Bind(&block23);
    compiler::CodeAssemblerLabel label23(&ca_);
    FastArrayFilter_0(state_, TNode<Context>{parameter0}, TNode<JSArray>{tmp21}, TNode<Smi>{tmp17}, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>>{tmp7}, TNode<JSAny>{tmp10}, TNode<JSArray>{tmp19}, &label23, &tmp24, &tmp25);
    ca_.Goto(&block25);
    if (label23.is_used()) {
      ca_.Bind(&label23);
      ca_.Goto(&block26);
    }
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    ca_.Goto(&block12, tmp24.value(), tmp25.value());
  }

  if (block25.is_used()) {
    ca_.Bind(&block25);
    arguments.PopAndReturn(tmp13);
  }

  TNode<Number> phi_bb12_13;
  TNode<Number> phi_bb12_14;
  if (block12.is_used()) {
    ca_.Bind(&block12, &phi_bb12_13, &phi_bb12_14);
    ca_.Goto(&block7, tmp13, phi_bb12_13, phi_bb12_14);
  }

  TNode<JSReceiver> phi_bb7_10;
  TNode<Number> phi_bb7_11;
  TNode<Number> phi_bb7_12;
  TNode<JSAny> tmp26;
  if (block7.is_used()) {
    ca_.Bind(&block7, &phi_bb7_10, &phi_bb7_11, &phi_bb7_12);
    tmp26 = ca_.CallBuiltin<JSAny>(Builtin::kArrayFilterLoopContinuation, parameter0, tmp1, tmp7, tmp10, phi_bb7_10, tmp1, phi_bb7_11, tmp2, phi_bb7_12);
    arguments.PopAndReturn(tmp26);
  }

  TNode<IntPtrT> tmp27;
  TNode<JSAny> tmp28;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    tmp27 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp28 = CodeStubAssembler(state_).GetArgumentValue(TorqueStructArguments{TNode<RawPtrT>{torque_arguments.frame}, TNode<RawPtrT>{torque_arguments.base}, TNode<IntPtrT>{torque_arguments.length}, TNode<IntPtrT>{torque_arguments.actual_count}}, TNode<IntPtrT>{tmp27});
    CodeStubAssembler(state_).CallRuntime(Runtime::kThrowCalledNonCallable, parameter0, tmp28);
    CodeStubAssembler(state_).Unreachable();
  }
}

} // namespace internal
} // namespace v8
