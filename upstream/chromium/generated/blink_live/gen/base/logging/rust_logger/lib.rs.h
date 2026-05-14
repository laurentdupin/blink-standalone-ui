#pragma once

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace logging {
namespace internal {
void init_rust_logging() noexcept;
} // namespace internal
} // namespace logging

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
