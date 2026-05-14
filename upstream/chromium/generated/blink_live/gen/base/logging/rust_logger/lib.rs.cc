#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace logging {
namespace internal {
extern "C" {
void logging$internal$cxxbridge1$194$init_rust_logging() noexcept;
} // extern "C"

void init_rust_logging() noexcept {
  logging$internal$cxxbridge1$194$init_rust_logging();
}
} // namespace internal
} // namespace logging
