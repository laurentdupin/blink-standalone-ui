// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <openssl/mem.h>

#include <stddef.h>

void OPENSSL_cleanse(void* ptr, size_t len) {
  volatile unsigned char* cursor = static_cast<volatile unsigned char*>(ptr);
  while (len-- > 0) {
    *cursor++ = 0;
  }
}

int CRYPTO_memcmp(const void* a, const void* b, size_t len) {
  const auto* lhs = static_cast<const unsigned char*>(a);
  const auto* rhs = static_cast<const unsigned char*>(b);
  unsigned char diff = 0;
  for (size_t i = 0; i < len; ++i) {
    diff |= lhs[i] ^ rhs[i];
  }
  return diff;
}
