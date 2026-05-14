#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_BACKGROUND_HTML_SCANNER_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_BACKGROUND_HTML_SCANNER_H_

#include <memory>

#include "third_party/blink/renderer/platform/wtf/sequence_bound.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

class HTMLParserOptions;
class HTMLToken;
class ScriptableDocumentParser;

class BackgroundHTMLScanner {
 public:
  class ScriptTokenScanner {
   public:
    static std::unique_ptr<ScriptTokenScanner> Create(
        ScriptableDocumentParser*);
    void ScanToken(const HTMLToken&) {}
    void set_first_script_in_scan(bool) {}
  };

  static SequenceBound<BackgroundHTMLScanner> Create(
      const HTMLParserOptions&,
      ScriptableDocumentParser*);
  BackgroundHTMLScanner() = default;
  ~BackgroundHTMLScanner();
  void Scan(const String&);
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_BACKGROUND_HTML_SCANNER_H_
