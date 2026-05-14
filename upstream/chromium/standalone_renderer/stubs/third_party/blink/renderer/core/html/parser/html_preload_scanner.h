#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_HTML_PRELOAD_SCANNER_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_HTML_PRELOAD_SCANNER_H_

#include <memory>
#include <optional>

#include "base/memory/weak_ptr.h"
#include "base/task/sequenced_task_runner.h"
#include "services/network/public/cpp/client_hints.h"
#include "third_party/blink/renderer/core/html/parser/preload_request.h"
#include "third_party/blink/renderer/core/page/viewport_description.h"
#include "third_party/blink/renderer/platform/text/segmented_string.h"
#include "third_party/blink/renderer/platform/wtf/functional.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace blink {

class Document;
class HTMLDocumentParser;
class HTMLParserOptions;

struct MetaCHValue {
  AtomicString value;
  network::MetaCHType type = network::MetaCHType::HttpEquivAcceptCH;
  bool is_doc_preloader = false;
};
using MetaCHValues = Vector<MetaCHValue>;

struct PendingPreloadData {
  MetaCHValues meta_ch_values;
  std::optional<ViewportDescription> viewport;
  int csp_meta_tag_count = 0;
  bool has_located_potential_lcp_element = false;
  PreloadRequestStream requests;
};

class TokenPreloadScanner {
 public:
  enum class ScannerType { kMainDocument, kInsertion };
};

class HTMLPreloadScanner final {
 public:
  static std::unique_ptr<HTMLPreloadScanner> Create(
      Document&,
      HTMLParserOptions,
      TokenPreloadScanner::ScannerType);

  using TakePreloadFn =
      CrossThreadRepeatingFunction<void(std::unique_ptr<PendingPreloadData>)>;

  struct Deleter {
    void operator()(const HTMLPreloadScanner* ptr) {
      delete ptr;
    }
    scoped_refptr<base::SequencedTaskRunner> task_runner_;
  };
  using BackgroundPtr = std::unique_ptr<HTMLPreloadScanner, Deleter>;

  static BackgroundPtr CreateBackground(
      HTMLDocumentParser*,
      HTMLParserOptions,
      scoped_refptr<base::SequencedTaskRunner>,
      TakePreloadFn);

  ~HTMLPreloadScanner();
  void AppendToEnd(const SegmentedString&);
  std::unique_ptr<PendingPreloadData> Scan(const KURL&);
  void ScanInBackground(const String&, const KURL&);
  base::WeakPtr<HTMLPreloadScanner> AsWeakPtr();

 private:
  HTMLPreloadScanner() = default;
  base::WeakPtrFactory<HTMLPreloadScanner> weak_ptr_factory_{this};
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_PARSER_HTML_PRELOAD_SCANNER_H_
