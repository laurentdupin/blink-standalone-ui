// Copyright 2026 The Standalone Renderer Authors
// Minimal Crashpad annotation boundary shim.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_CRASHPAD_CRASHPAD_CLIENT_ANNOTATION_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_CRASHPAD_CRASHPAD_CLIENT_ANNOTATION_H_

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace crashpad {

class Annotation {
 public:
  static constexpr size_t kNameMaxLength = 256;
  static constexpr size_t kValueMaxSize = 5 * 4096;

  using ValueSizeType = uint32_t;

  enum class Type : uint16_t {
    kInvalid = 0,
    kString = 1,
    kUserDefinedStart = 0x8000,
  };

  constexpr Annotation(Type type, const char name[], void* value_ptr)
      : type_(type), name_(name), value_ptr_(value_ptr) {}

  Annotation(const Annotation&) = delete;
  Annotation& operator=(const Annotation&) = delete;

  void SetSize(ValueSizeType size);
  void Clear();

  bool is_set() const { return size_ > 0; }
  Type type() const { return type_; }
  ValueSizeType size() const { return size_; }
  const char* name() const { return name_; }
  const void* value() const { return value_ptr_; }

 protected:
  Type type_;
  const char* name_;
  void* value_ptr_;
  ValueSizeType size_ = 0;
};

template <Annotation::ValueSizeType MaxSize>
class StringAnnotation : public Annotation {
 public:
  enum class Tag { kArray };

  constexpr explicit StringAnnotation(const char name[])
      : Annotation(Type::kString, name, value_), value_() {}
  constexpr StringAnnotation(const char name[], Tag)
      : StringAnnotation(name) {}

  StringAnnotation(const StringAnnotation&) = delete;
  StringAnnotation& operator=(const StringAnnotation&) = delete;

  void Set(const char* value) {
    ValueSizeType size =
        static_cast<ValueSizeType>(std::min(strlen(value), size_t{MaxSize - 1}));
    memcpy(value_, value, size);
    value_[size] = '\0';
    SetSize(size + 1);
  }

 private:
  char value_[MaxSize];
};

}  // namespace crashpad

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_CRASHPAD_CRASHPAD_CLIENT_ANNOTATION_H_
