#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_FIXED_ARRAY_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_FIXED_ARRAY_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=5&c=1
TNode<FixedArrayBase> Cast_FixedArrayBase_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=13&c=1
TNode<FixedArray> Cast_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=20&c=1
TNode<TrustedFixedArray> Cast_TrustedFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=28&c=1
TNode<ProtectedFixedArray> Cast_ProtectedFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=36&c=1
TNode<FixedDoubleArray> Cast_FixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=41&c=1
TNode<WeakFixedArray> Cast_WeakFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=49&c=1
TNode<WeakHomomorphicFixedArray> Cast_WeakHomomorphicFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=55&c=1
TNode<TrustedWeakFixedArray> Cast_TrustedWeakFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=63&c=1
TNode<ProtectedWeakFixedArray> Cast_ProtectedWeakFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=73&c=1
TNode<ByteArray> Cast_ByteArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=78&c=1
TNode<TrustedByteArray> Cast_TrustedByteArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=88&c=1
TNode<ArrayList> Cast_ArrayList_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=95&c=1
TNode<WeakArrayList> Cast_WeakArrayList_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=102&c=1
TNode<IntPtrT> LoadFixedArrayBaseLengthIntptr_0(compiler::CodeAssemblerState* state_, TNode<FixedArrayBase> p_array);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=147&c=1
void StoreFixedDoubleArrayDirect_0(compiler::CodeAssemblerState* state_, TNode<FixedDoubleArray> p_a, TNode<Smi> p_i, TNode<Number> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=151&c=1
void StoreFixedArrayDirect_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_a, TNode<Smi> p_i, TNode<Object> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=186&c=1
TNode<FixedArray> ExtractFixedArray_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_source, TNode<IntPtrT> p_first, TNode<IntPtrT> p_count, TNode<IntPtrT> p_capacity, TNode<Hole> p_initialElement);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=196&c=1
TNode<Union<FixedArray, FixedDoubleArray>> ExtractFixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<FixedDoubleArray> p_source, TNode<IntPtrT> p_first, TNode<IntPtrT> p_count, TNode<IntPtrT> p_capacity);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=8&c=9
TNode<Uint32T> LoadFixedArrayBaseLength_0(compiler::CodeAssemblerState* state_, TNode<FixedArrayBase> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=15&c=3
TorqueStructSlice_Object_MutableReference_Object_0 FieldSliceFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=15&c=3
TNode<Object> LoadFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=15&c=3
void StoreFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_o, TNode<IntPtrT> p_i, TNode<Object> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=43&c=9
TNode<Uint32T> LoadWeakFixedArrayLength_0(compiler::CodeAssemblerState* state_, TNode<WeakFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=46&c=3
TorqueStructSlice_MaybeObject_MutableReference_MaybeObject_0 FieldSliceWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=46&c=3
TNode<Union<HeapObject, Smi, Weak<HeapObject>>> LoadWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakFixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=46&c=3
void StoreWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakFixedArray> p_o, TNode<IntPtrT> p_i, TNode<Union<HeapObject, Smi, Weak<HeapObject>>> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=97&c=9
TNode<Uint32T> LoadWeakArrayListCapacity_0(compiler::CodeAssemblerState* state_, TNode<WeakArrayList> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=98&c=3
TNode<Uint32T> LoadWeakArrayListLength_0(compiler::CodeAssemblerState* state_, TNode<WeakArrayList> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=98&c=3
void StoreWeakArrayListLength_0(compiler::CodeAssemblerState* state_, TNode<WeakArrayList> p_o, TNode<Uint32T> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=99&c=3
TorqueStructSlice_MaybeObject_MutableReference_MaybeObject_0 FieldSliceWeakArrayListObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakArrayList> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=99&c=3
TNode<Union<HeapObject, Smi, Weak<HeapObject>>> LoadWeakArrayListObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakArrayList> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=99&c=3
void StoreWeakArrayListObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakArrayList> p_o, TNode<IntPtrT> p_i, TNode<Union<HeapObject, Smi, Weak<HeapObject>>> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=38&c=3
TorqueStructSlice_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_0 FieldSliceFixedDoubleArrayValues_0(compiler::CodeAssemblerState* state_, TNode<FixedDoubleArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=22&c=9
TNode<Uint32T> LoadTrustedFixedArrayLength_0(compiler::CodeAssemblerState* state_, TNode<TrustedFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=25&c=3
TorqueStructSlice_Object_MutableReference_Object_0 FieldSliceTrustedFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<TrustedFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=25&c=3
TNode<Object> LoadTrustedFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<TrustedFixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=25&c=3
void StoreTrustedFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<TrustedFixedArray> p_o, TNode<IntPtrT> p_i, TNode<Object> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=30&c=9
TNode<Uint32T> LoadProtectedFixedArrayLength_0(compiler::CodeAssemblerState* state_, TNode<ProtectedFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=33&c=3
TorqueStructSlice_Smi_OR_TrustedObject_MutableReference_Smi_OR_TrustedObject_0 FieldSliceProtectedFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<ProtectedFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=33&c=3
TNode<Union<Smi, TrustedObject>> LoadProtectedFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<ProtectedFixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=33&c=3
void StoreProtectedFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<ProtectedFixedArray> p_o, TNode<IntPtrT> p_i, TNode<Union<Smi, TrustedObject>> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=51&c=9
TNode<Smi> LoadWeakHomomorphicFixedArrayLength_0(compiler::CodeAssemblerState* state_, TNode<WeakHomomorphicFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=52&c=3
TorqueStructSlice_MaybeObject_MutableReference_MaybeObject_0 FieldSliceWeakHomomorphicFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakHomomorphicFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=52&c=3
TNode<Union<HeapObject, Smi, Weak<HeapObject>>> LoadWeakHomomorphicFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakHomomorphicFixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=52&c=3
void StoreWeakHomomorphicFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<WeakHomomorphicFixedArray> p_o, TNode<IntPtrT> p_i, TNode<Union<HeapObject, Smi, Weak<HeapObject>>> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=57&c=9
TNode<Uint32T> LoadTrustedWeakFixedArrayLength_0(compiler::CodeAssemblerState* state_, TNode<TrustedWeakFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=60&c=3
TorqueStructSlice_MaybeObject_MutableReference_MaybeObject_0 FieldSliceTrustedWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<TrustedWeakFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=60&c=3
TNode<Union<HeapObject, Smi, Weak<HeapObject>>> LoadTrustedWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<TrustedWeakFixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=60&c=3
void StoreTrustedWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<TrustedWeakFixedArray> p_o, TNode<IntPtrT> p_i, TNode<Union<HeapObject, Smi, Weak<HeapObject>>> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=65&c=9
TNode<Uint32T> LoadProtectedWeakFixedArrayLength_0(compiler::CodeAssemblerState* state_, TNode<ProtectedWeakFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=70&c=3
TorqueStructSlice_Smi_OR_TrustedObject_MutableReference_Smi_OR_TrustedObject_0 FieldSliceProtectedWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<ProtectedWeakFixedArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=70&c=3
TNode<Union<Smi, TrustedObject>> LoadProtectedWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<ProtectedWeakFixedArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=70&c=3
void StoreProtectedWeakFixedArrayObjects_0(compiler::CodeAssemblerState* state_, TNode<ProtectedWeakFixedArray> p_o, TNode<IntPtrT> p_i, TNode<Union<Smi, TrustedObject>> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=75&c=3
TorqueStructSlice_uint8_MutableReference_uint8_0 FieldSliceByteArrayValues_0(compiler::CodeAssemblerState* state_, TNode<ByteArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=75&c=3
TNode<Uint8T> LoadByteArrayValues_0(compiler::CodeAssemblerState* state_, TNode<ByteArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=75&c=3
void StoreByteArrayValues_0(compiler::CodeAssemblerState* state_, TNode<ByteArray> p_o, TNode<IntPtrT> p_i, TNode<Uint8T> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=80&c=9
TNode<Uint32T> LoadTrustedByteArrayLength_0(compiler::CodeAssemblerState* state_, TNode<TrustedByteArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=83&c=3
TorqueStructSlice_uint8_MutableReference_uint8_0 FieldSliceTrustedByteArrayValues_0(compiler::CodeAssemblerState* state_, TNode<TrustedByteArray> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=83&c=3
TNode<Uint8T> LoadTrustedByteArrayValues_0(compiler::CodeAssemblerState* state_, TNode<TrustedByteArray> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=83&c=3
void StoreTrustedByteArrayValues_0(compiler::CodeAssemblerState* state_, TNode<TrustedByteArray> p_o, TNode<IntPtrT> p_i, TNode<Uint8T> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=90&c=9
TNode<Uint32T> LoadArrayListCapacity_0(compiler::CodeAssemblerState* state_, TNode<ArrayList> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=91&c=3
TNode<Uint32T> LoadArrayListLength_0(compiler::CodeAssemblerState* state_, TNode<ArrayList> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=91&c=3
void StoreArrayListLength_0(compiler::CodeAssemblerState* state_, TNode<ArrayList> p_o, TNode<Uint32T> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=92&c=3
TorqueStructSlice_Object_MutableReference_Object_0 FieldSliceArrayListObjects_0(compiler::CodeAssemblerState* state_, TNode<ArrayList> p_o);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=92&c=3
TNode<Object> LoadArrayListObjects_0(compiler::CodeAssemblerState* state_, TNode<ArrayList> p_o, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=92&c=3
void StoreArrayListObjects_0(compiler::CodeAssemblerState* state_, TNode<ArrayList> p_o, TNode<IntPtrT> p_i, TNode<Object> p_v);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=5&c=1
TNode<FixedArrayBase> DownCastForTorqueClass_FixedArrayBase_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=13&c=1
TNode<FixedArray> DownCastForTorqueClass_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=20&c=1
TNode<TrustedFixedArray> DownCastForTorqueClass_TrustedFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=28&c=1
TNode<ProtectedFixedArray> DownCastForTorqueClass_ProtectedFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=36&c=1
TNode<FixedDoubleArray> DownCastForTorqueClass_FixedDoubleArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=41&c=1
TNode<WeakFixedArray> DownCastForTorqueClass_WeakFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=49&c=1
TNode<WeakHomomorphicFixedArray> DownCastForTorqueClass_WeakHomomorphicFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=55&c=1
TNode<TrustedWeakFixedArray> DownCastForTorqueClass_TrustedWeakFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=63&c=1
TNode<ProtectedWeakFixedArray> DownCastForTorqueClass_ProtectedWeakFixedArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=73&c=1
TNode<ByteArray> DownCastForTorqueClass_ByteArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=78&c=1
TNode<TrustedByteArray> DownCastForTorqueClass_TrustedByteArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=88&c=1
TNode<ArrayList> DownCastForTorqueClass_ArrayList_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=95&c=1
TNode<WeakArrayList> DownCastForTorqueClass_WeakArrayList_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=194&c=11
TorqueStructConstantIterator_Hole_0 ConstantIterator_Hole_0(compiler::CodeAssemblerState* state_, TNode<Hole> p_value);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=192&c=7
TorqueStructIteratorSequence_Object_SliceIterator_Object_MutableReference_Object_ConstantIterator_Hole_0 IteratorSequence_Object_SliceIterator_Object_MutableReference_Object_ConstantIterator_Hole_0(compiler::CodeAssemblerState* state_, TorqueStructSliceIterator_Object_MutableReference_Object_0 p_first, TorqueStructConstantIterator_Hole_0 p_second);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=190&c=10
TNode<FixedArray> NewFixedArray_IteratorSequence_Object_SliceIterator_Object_MutableReference_Object_ConstantIterator_Hole_0(compiler::CodeAssemblerState* state_, TNode<IntPtrT> p_length, TorqueStructIteratorSequence_Object_SliceIterator_Object_MutableReference_Object_ConstantIterator_Hole_0 p_it);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=204&c=11
TorqueStructConstantIterator_float64_or_undefined_or_hole_0 ConstantIterator_float64_or_undefined_or_hole_0(compiler::CodeAssemblerState* state_, TorqueStructfloat64_or_undefined_or_hole_0 p_value);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=202&c=7
TorqueStructIteratorSequence_float64_or_undefined_or_hole_SliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_ConstantIterator_float64_or_undefined_or_hole_0 IteratorSequence_float64_or_undefined_or_hole_SliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_ConstantIterator_float64_or_undefined_or_hole_0(compiler::CodeAssemblerState* state_, TorqueStructSliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_0 p_first, TorqueStructConstantIterator_float64_or_undefined_or_hole_0 p_second);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=200&c=10
TNode<Union<FixedArray, FixedDoubleArray>> NewFixedDoubleArray_IteratorSequence_float64_or_undefined_or_hole_SliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_ConstantIterator_float64_or_undefined_or_hole_0(compiler::CodeAssemblerState* state_, TNode<IntPtrT> p_length, TorqueStructIteratorSequence_float64_or_undefined_or_hole_SliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_ConstantIterator_float64_or_undefined_or_hole_0 p_it);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=15&c=3
TorqueStructSlice_Object_MutableReference_Object_0 NewMutableSlice_Object_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset, TNode<IntPtrT> p_length);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=46&c=3
TorqueStructSlice_MaybeObject_MutableReference_MaybeObject_0 NewMutableSlice_MaybeObject_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset, TNode<IntPtrT> p_length);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=38&c=3
TorqueStructSlice_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_0 NewMutableSlice_float64_or_undefined_or_hole_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset, TNode<IntPtrT> p_length);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=33&c=3
TorqueStructSlice_Smi_OR_TrustedObject_MutableReference_Smi_OR_TrustedObject_0 NewMutableSlice_Smi_OR_TrustedObject_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, TaggedIndex>> p_object, TNode<IntPtrT> p_offset, TNode<IntPtrT> p_length);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=218&c=10
void InitializeFieldsFromIterator_Object_ArgumentsIterator_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_Object_MutableReference_Object_0 p_target, TorqueStructArgumentsIterator_0 p_originIterator);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=218&c=10
void InitializeFieldsFromIterator_Object_ConstantIterator_Undefined_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_Object_MutableReference_Object_0 p_target, TorqueStructConstantIterator_Undefined_0 p_originIterator);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=218&c=10
void InitializeFieldsFromIterator_Object_ParameterValueIterator_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_Object_MutableReference_Object_0 p_target, TorqueStructParameterValueIterator_0 p_originIterator);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=218&c=10
void InitializeFieldsFromIterator_Object_IteratorSequence_Object_SliceIterator_Object_MutableReference_Object_ConstantIterator_Hole_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_Object_MutableReference_Object_0 p_target, TorqueStructIteratorSequence_Object_SliceIterator_Object_MutableReference_Object_ConstantIterator_Hole_0 p_originIterator);

// https://crsrc.org/c/v8/src/objects/fixed-array.tq?l=229&c=10
void InitializeFieldsFromIterator_float64_or_undefined_or_hole_IteratorSequence_float64_or_undefined_or_hole_SliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_ConstantIterator_float64_or_undefined_or_hole_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_0 p_target, TorqueStructIteratorSequence_float64_or_undefined_or_hole_SliceIterator_float64_or_undefined_or_hole_MutableReference_float64_or_undefined_or_hole_ConstantIterator_float64_or_undefined_or_hole_0 p_originIterator);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_FIXED_ARRAY_TQ_CSA_H_
