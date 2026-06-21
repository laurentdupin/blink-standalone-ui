#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_LCP_CRITICAL_PATH_PREDICTOR_ELEMENT_LOCATOR_PB_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_LCP_CRITICAL_PATH_PREDICTOR_ELEMENT_LOCATOR_PB_H_

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace blink {

class ElementLocator_Component_Id {
 public:
  void set_id_attr(std::string id_attr) { id_attr_ = std::move(id_attr); }
  const std::string& id_attr() const { return id_attr_; }

 private:
  std::string id_attr_;
};

class ElementLocator_Component_NthTagName {
 public:
  void set_tag_name(std::string tag_name) { tag_name_ = std::move(tag_name); }
  const std::string& tag_name() const { return tag_name_; }

  void set_index(int32_t index) { index_ = index; }
  int32_t index() const { return index_; }

 private:
  std::string tag_name_;
  int32_t index_ = 0;
};

class ElementLocator_Component {
 public:
  enum ComponentCase {
    COMPONENT_NOT_SET = 0,
    kId = 1,
    kNth = 2,
  };

  ElementLocator_Component_Id* mutable_id() {
    component_case_ = kId;
    return &id_;
  }

  ElementLocator_Component_NthTagName* mutable_nth() {
    component_case_ = kNth;
    return &nth_;
  }

  bool has_id() const { return component_case_ == kId; }
  bool has_nth() const { return component_case_ == kNth; }

  const ElementLocator_Component_Id& id() const { return id_; }
  const ElementLocator_Component_NthTagName& nth() const { return nth_; }

  ComponentCase component_case() const { return component_case_; }

 private:
  ComponentCase component_case_ = COMPONENT_NOT_SET;
  ElementLocator_Component_Id id_;
  ElementLocator_Component_NthTagName nth_;
};

class ElementLocator {
 public:
  ElementLocator_Component* add_components() {
    components_.emplace_back();
    return &components_.back();
  }

  const std::vector<ElementLocator_Component>& components() const {
    return components_;
  }

  int components_size() const { return static_cast<int>(components_.size()); }

  bool ParseFromString(const std::string&) { return false; }
  std::string SerializeAsString() const { return {}; }

 private:
  std::vector<ElementLocator_Component> components_;
};

}  // namespace blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_LCP_CRITICAL_PATH_PREDICTOR_ELEMENT_LOCATOR_PB_H_
