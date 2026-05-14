#include "src/objects/bytecode-array.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=7&c=1
class TorqueGeneratedBytecodeArrayAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(ExposedTrustedObject);
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=9&c=9
  static constexpr int kLengthOffset = sizeof(ExposedTrustedObject);
  static constexpr int kLengthOffsetEnd = kLengthOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=10&c=3
  static constexpr int kWrapperOffset = kLengthOffsetEnd + 1;
  static constexpr int kWrapperOffsetEnd = kWrapperOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kWrapperOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kWrapperOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=11&c=3
  static constexpr int kSourcePositionTableOffset = kWrapperOffsetEnd + 1;
  static constexpr int kSourcePositionTableOffsetEnd = kSourcePositionTableOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=12&c=3
  static constexpr int kHandlerTableOffset = kSourcePositionTableOffsetEnd + 1;
  static constexpr int kHandlerTableOffsetEnd = kHandlerTableOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=13&c=3
  static constexpr int kConstantPoolOffset = kHandlerTableOffsetEnd + 1;
  static constexpr int kConstantPoolOffsetEnd = kConstantPoolOffset + kTaggedSize - 1;
  static constexpr int kEndOfWeakFieldsOffset = kConstantPoolOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=14&c=3
  static constexpr int kFrameSizeOffset = kConstantPoolOffsetEnd + 1;
  static constexpr int kFrameSizeOffsetEnd = kFrameSizeOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=15&c=3
  static constexpr int kParameterSizeOffset = kFrameSizeOffsetEnd + 1;
  static constexpr int kParameterSizeOffsetEnd = kParameterSizeOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=16&c=3
  static constexpr int kMaxArgumentsOffset = kParameterSizeOffsetEnd + 1;
  static constexpr int kMaxArgumentsOffsetEnd = kMaxArgumentsOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=17&c=3
  static constexpr int kIncomingNewTargetOrGeneratorRegisterOffset = kMaxArgumentsOffsetEnd + 1;
  static constexpr int kIncomingNewTargetOrGeneratorRegisterOffsetEnd = kIncomingNewTargetOrGeneratorRegisterOffset + kInt32Size - 1;
  static constexpr int kHeaderSize = kIncomingNewTargetOrGeneratorRegisterOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=19&c=3
  static constexpr int kBytesOffset = kIncomingNewTargetOrGeneratorRegisterOffsetEnd + 1;
  static constexpr int kBytesOffsetEnd = kBytesOffset + 0 - 1;

  static_assert(kLengthOffset == offsetof(BytecodeArray, length_),
                "Value of BytecodeArray::kLengthOffset defined in Torque and offset of field BytecodeArray::length in C++ do not match");
  static_assert(kWrapperOffset == offsetof(BytecodeArray, wrapper_),
                "Value of BytecodeArray::kWrapperOffset defined in Torque and offset of field BytecodeArray::wrapper in C++ do not match");
  static_assert(kSourcePositionTableOffset == offsetof(BytecodeArray, source_position_table_),
                "Value of BytecodeArray::kSourcePositionTableOffset defined in Torque and offset of field BytecodeArray::source_position_table in C++ do not match");
  static_assert(kHandlerTableOffset == offsetof(BytecodeArray, handler_table_),
                "Value of BytecodeArray::kHandlerTableOffset defined in Torque and offset of field BytecodeArray::handler_table in C++ do not match");
  static_assert(kConstantPoolOffset == offsetof(BytecodeArray, constant_pool_),
                "Value of BytecodeArray::kConstantPoolOffset defined in Torque and offset of field BytecodeArray::constant_pool in C++ do not match");
  static_assert(kFrameSizeOffset == offsetof(BytecodeArray, frame_size_),
                "Value of BytecodeArray::kFrameSizeOffset defined in Torque and offset of field BytecodeArray::frame_size in C++ do not match");
  static_assert(kParameterSizeOffset == offsetof(BytecodeArray, parameter_size_),
                "Value of BytecodeArray::kParameterSizeOffset defined in Torque and offset of field BytecodeArray::parameter_size in C++ do not match");
  static_assert(kMaxArgumentsOffset == offsetof(BytecodeArray, max_arguments_),
                "Value of BytecodeArray::kMaxArgumentsOffset defined in Torque and offset of field BytecodeArray::max_arguments in C++ do not match");
  static_assert(kIncomingNewTargetOrGeneratorRegisterOffset == offsetof(BytecodeArray, incoming_new_target_or_generator_register_),
                "Value of BytecodeArray::kIncomingNewTargetOrGeneratorRegisterOffset defined in Torque and offset of field BytecodeArray::incoming_new_target_or_generator_register in C++ do not match");
  static_assert(kBytesOffset == OFFSET_OF_DATA_START(BytecodeArray),
                "Value of BytecodeArray::kBytesOffset defined in Torque and offset of field BytecodeArray::bytes in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=25&c=1
class TorqueGeneratedBytecodeWrapperAsserts {
  // https://crsrc.org/c/v8/src/objects/bytecode-array.tq?l=27&c=3
  static constexpr int kBytecodeOffset = sizeof(Struct);
  static constexpr int kBytecodeOffsetEnd = kBytecodeOffset + kTrustedPointerSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kBytecodeOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBytecodeOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kBytecodeOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kBytecodeOffsetEnd + 1;
  static constexpr int kHeaderSize = kBytecodeOffsetEnd + 1;
  static constexpr int kSize = kBytecodeOffsetEnd + 1;

  static_assert(kBytecodeOffset == offsetof(BytecodeWrapper, bytecode_),
                "Value of BytecodeWrapper::kBytecodeOffset defined in Torque and offset of field BytecodeWrapper::bytecode in C++ do not match");
  static_assert(kSize == sizeof(BytecodeWrapper));
};

} // namespace internal
} // namespace v8
