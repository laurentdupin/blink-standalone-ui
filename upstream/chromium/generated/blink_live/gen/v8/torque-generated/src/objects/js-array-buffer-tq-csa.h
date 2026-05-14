#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_JS_ARRAY_BUFFER_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_JS_ARRAY_BUFFER_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=15&c=1
TNode<Smi> kNoView_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=16&c=1
TNode<Smi> kManyViews_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=18&c=1
TNode<JSArrayBuffer> Cast_JSArrayBuffer_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=41&c=1
TNode<BoolT> IsDetachedBuffer_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_buffer);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=46&c=1
TNode<BoolT> IsSharedArrayBuffer_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_buffer);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=51&c=1
TNode<BoolT> IsResizableArrayBuffer_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_buffer);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=56&c=1
TNode<BoolT> IsImmutableArrayBuffer_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_buffer);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=72&c=1
TNode<JSArrayBufferView> Cast_JSArrayBufferView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=93&c=1
TNode<BoolT> IsVariableLengthJSArrayBufferView_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_array);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=98&c=1
TNode<BoolT> IsLengthTrackingJSArrayBufferView_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_array);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=107&c=1
TNode<UintPtrT> LoadJSArrayBufferViewByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_view, TNode<JSArrayBuffer> p_buffer, compiler::CodeAssemblerLabel* label_DetachedOrOutOfBounds);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=119&c=1
TNode<JSTypedArray> Cast_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=131&c=1
TNode<JSDetachedTypedArray> Cast_JSDetachedTypedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=136&c=1
TNode<BoolT> IsOnHeapTypedArray_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_array);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=142&c=1
TNode<JSDataViewOrRabGsabDataView> Cast_JSDataViewOrRabGsabDataView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=149&c=1
TNode<JSDataView> Cast_JSDataView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=152&c=1
TNode<JSRabGsabDataView> Cast_JSRabGsabDataView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=75&c=3
TNode<JSArrayBuffer> LoadJSArrayBufferViewBuffer_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=75&c=3
void StoreJSArrayBufferViewBuffer_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o, TNode<JSArrayBuffer> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=76&c=3
TNode<Uint32T> LoadJSArrayBufferViewBitField_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=76&c=3
void StoreJSArrayBufferViewBitField_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o, TNode<Uint32T> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=79&c=3
TNode<UintPtrT> LoadJSArrayBufferViewRawByteOffset_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=79&c=3
void StoreJSArrayBufferViewRawByteOffset_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o, TNode<UintPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=81&c=3
TNode<UintPtrT> LoadJSArrayBufferViewRawByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=81&c=3
void StoreJSArrayBufferViewRawByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBufferView> p_o, TNode<UintPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=122&c=3
TNode<UintPtrT> LoadJSTypedArrayRawLength_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=122&c=3
void StoreJSTypedArrayRawLength_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_o, TNode<UintPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=124&c=3
TNode<RawPtrT> LoadJSTypedArrayExternalPointer_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=124&c=3
void StoreJSTypedArrayExternalPointer_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_o, TNode<RawPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=125&c=3
TNode<Union<ByteArray, Smi>> LoadJSTypedArrayBasePointer_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=125&c=3
void StoreJSTypedArrayBasePointer_0(compiler::CodeAssemblerState* state_, TNode<JSTypedArray> p_o, TNode<Union<ByteArray, Smi>> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=20&c=3
TNode<Union<Cell, Smi, Weak<HeapObject>>> LoadJSArrayBufferViewsOrDetachKey_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=20&c=3
void StoreJSArrayBufferViewsOrDetachKey_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o, TNode<Union<Cell, Smi, Weak<HeapObject>>> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=22&c=3
TNode<UintPtrT> LoadJSArrayBufferRawByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=22&c=3
void StoreJSArrayBufferRawByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o, TNode<UintPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=24&c=3
TNode<UintPtrT> LoadJSArrayBufferRawMaxByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=24&c=3
void StoreJSArrayBufferRawMaxByteLength_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o, TNode<UintPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=26&c=3
TNode<RawPtrT> LoadJSArrayBufferBackingStore_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=26&c=3
void StoreJSArrayBufferBackingStore_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o, TNode<RawPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=27&c=3
TNode<ExternalPointerT> LoadJSArrayBufferExtension_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=27&c=3
void StoreJSArrayBufferExtension_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o, TNode<ExternalPointerT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=28&c=3
TNode<Uint32T> LoadJSArrayBufferBitField_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=28&c=3
void StoreJSArrayBufferBitField_0(compiler::CodeAssemblerState* state_, TNode<JSArrayBuffer> p_o, TNode<Uint32T> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=146&c=3
TNode<RawPtrT> LoadJSDataViewOrRabGsabDataViewDataPointer_0(compiler::CodeAssemblerState* state_, TNode<JSDataViewOrRabGsabDataView> p_o);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=146&c=3
void StoreJSDataViewOrRabGsabDataViewDataPointer_0(compiler::CodeAssemblerState* state_, TNode<JSDataViewOrRabGsabDataView> p_o, TNode<RawPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=18&c=1
TNode<JSArrayBuffer> DownCastForTorqueClass_JSArrayBuffer_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=72&c=1
TNode<JSArrayBufferView> DownCastForTorqueClass_JSArrayBufferView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=119&c=1
TNode<JSTypedArray> DownCastForTorqueClass_JSTypedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=131&c=1
TNode<JSDetachedTypedArray> DownCastForTorqueClass_JSDetachedTypedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=142&c=1
TNode<JSDataViewOrRabGsabDataView> DownCastForTorqueClass_JSDataViewOrRabGsabDataView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=149&c=1
TNode<JSDataView> DownCastForTorqueClass_JSDataView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=152&c=1
TNode<JSRabGsabDataView> DownCastForTorqueClass_JSRabGsabDataView_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_JS_ARRAY_BUFFER_TQ_CSA_H_
