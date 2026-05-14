#include "src/objects/module.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/module.tq?l=5&c=1
class TorqueGeneratedModuleAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/module.tq?l=9&c=3
  static constexpr int kExportsOffset = sizeof(HeapObjectLayout);
  static constexpr int kExportsOffsetEnd = kExportsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=11&c=3
  static constexpr int kHashOffset = kExportsOffsetEnd + 1;
  static constexpr int kHashOffsetEnd = kHashOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=12&c=3
  static constexpr int kStatusOffset = kHashOffsetEnd + 1;
  static constexpr int kStatusOffsetEnd = kStatusOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=13&c=3
  static constexpr int kModuleNamespaceOffset = kStatusOffsetEnd + 1;
  static constexpr int kModuleNamespaceOffsetEnd = kModuleNamespaceOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=14&c=3
  static constexpr int kDeferredModuleNamespaceOffset = kModuleNamespaceOffsetEnd + 1;
  static constexpr int kDeferredModuleNamespaceOffsetEnd = kDeferredModuleNamespaceOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=16&c=3
  static constexpr int kExceptionOffset = kDeferredModuleNamespaceOffsetEnd + 1;
  static constexpr int kExceptionOffsetEnd = kExceptionOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=19&c=3
  static constexpr int kTopLevelCapabilityOffset = kExceptionOffsetEnd + 1;
  static constexpr int kTopLevelCapabilityOffsetEnd = kTopLevelCapabilityOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kTopLevelCapabilityOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kTopLevelCapabilityOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kTopLevelCapabilityOffsetEnd + 1;
  static constexpr int kHeaderSize = kTopLevelCapabilityOffsetEnd + 1;

  static_assert(kExportsOffset == offsetof(Module, exports_),
                "Value of Module::kExportsOffset defined in Torque and offset of field Module::exports in C++ do not match");
  static_assert(kHashOffset == offsetof(Module, hash_),
                "Value of Module::kHashOffset defined in Torque and offset of field Module::hash in C++ do not match");
  static_assert(kStatusOffset == offsetof(Module, status_),
                "Value of Module::kStatusOffset defined in Torque and offset of field Module::status in C++ do not match");
  static_assert(kModuleNamespaceOffset == offsetof(Module, module_namespace_),
                "Value of Module::kModuleNamespaceOffset defined in Torque and offset of field Module::module_namespace in C++ do not match");
  static_assert(kDeferredModuleNamespaceOffset == offsetof(Module, deferred_module_namespace_),
                "Value of Module::kDeferredModuleNamespaceOffset defined in Torque and offset of field Module::deferred_module_namespace in C++ do not match");
  static_assert(kExceptionOffset == offsetof(Module, exception_),
                "Value of Module::kExceptionOffset defined in Torque and offset of field Module::exception in C++ do not match");
  static_assert(kTopLevelCapabilityOffset == offsetof(Module, top_level_capability_),
                "Value of Module::kTopLevelCapabilityOffset defined in Torque and offset of field Module::top_level_capability in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/module.tq?l=22&c=1
class TorqueGeneratedJSModuleNamespaceAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSSpecialObject);
  // https://crsrc.org/c/v8/src/objects/module.tq?l=24&c=3
  static constexpr int kModuleOffset = sizeof(JSSpecialObject);
  static constexpr int kModuleOffsetEnd = kModuleOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kModuleOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kModuleOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kModuleOffsetEnd + 1;
  static constexpr int kHeaderSize = kModuleOffsetEnd + 1;

  static_assert(kModuleOffset == offsetof(JSModuleNamespace, module_),
                "Value of JSModuleNamespace::kModuleOffset defined in Torque and offset of field JSModuleNamespace::module in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/module.tq?l=27&c=1
class TorqueGeneratedJSDeferredModuleNamespaceAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSModuleNamespace);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSModuleNamespace);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSModuleNamespace);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSModuleNamespace);
  static constexpr int kHeaderSize = sizeof(JSModuleNamespace);

};

// Definition https://crsrc.org/c/v8/src/objects/module.tq?l=30&c=1
class TorqueGeneratedScriptOrModuleAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(Struct);
  // https://crsrc.org/c/v8/src/objects/module.tq?l=32&c=3
  static constexpr int kResourceNameOffset = sizeof(Struct);
  static constexpr int kResourceNameOffsetEnd = kResourceNameOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/module.tq?l=33&c=3
  static constexpr int kHostDefinedOptionsOffset = kResourceNameOffsetEnd + 1;
  static constexpr int kHostDefinedOptionsOffsetEnd = kHostDefinedOptionsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kHostDefinedOptionsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kHostDefinedOptionsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kHostDefinedOptionsOffsetEnd + 1;
  static constexpr int kHeaderSize = kHostDefinedOptionsOffsetEnd + 1;
  static constexpr int kSize = kHostDefinedOptionsOffsetEnd + 1;

  static_assert(kResourceNameOffset == offsetof(ScriptOrModule, resource_name_),
                "Value of ScriptOrModule::kResourceNameOffset defined in Torque and offset of field ScriptOrModule::resource_name in C++ do not match");
  static_assert(kHostDefinedOptionsOffset == offsetof(ScriptOrModule, host_defined_options_),
                "Value of ScriptOrModule::kHostDefinedOptionsOffset defined in Torque and offset of field ScriptOrModule::host_defined_options in C++ do not match");
  static_assert(kSize == sizeof(ScriptOrModule));
};

} // namespace internal
} // namespace v8
