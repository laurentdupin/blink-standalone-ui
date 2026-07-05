// Copyright 2026 The Standalone Renderer Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_SYNC_SYNC_H_
#define STANDALONE_RENDERER_STUBS_SYNC_SYNC_H_

#include <errno.h>
#include <linux/sync_file.h>
#include <poll.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

static inline int sync_wait(int fd, int timeout) {
  struct pollfd fds;
  int ret;

  memset(&fds, 0, sizeof(fds));
  fds.fd = fd;
  fds.events = POLLIN;

  do {
    ret = poll(&fds, 1, timeout);
    if (ret > 0) {
      if (fds.revents & (POLLERR | POLLNVAL)) {
        errno = EINVAL;
        return -1;
      }
      return 0;
    }
    if (ret == 0) {
      errno = ETIME;
      return -1;
    }
  } while (ret == -1 && (errno == EINTR || errno == EAGAIN));

  return ret;
}

static inline struct sync_file_info* sync_file_info(int fd) {
  struct sync_file_info probe;
  struct sync_file_info* info;
  size_t fences_size;

  memset(&probe, 0, sizeof(probe));
  if (ioctl(fd, SYNC_IOC_FILE_INFO, &probe) < 0) {
    return NULL;
  }

  fences_size = (size_t)probe.num_fences * sizeof(struct sync_fence_info);
  info = (struct sync_file_info*)calloc(1, sizeof(*info) + fences_size);
  if (!info) {
    return NULL;
  }

  *info = probe;
  if (fences_size > 0) {
    info->sync_fence_info =
        (uint64_t)(uintptr_t)((char*)info + sizeof(*info));
  }

  if (ioctl(fd, SYNC_IOC_FILE_INFO, info) < 0) {
    free(info);
    return NULL;
  }

  return info;
}

static inline void sync_file_info_free(struct sync_file_info* info) {
  free(info);
}

static inline struct sync_fence_info* sync_get_fence_info(
    struct sync_file_info* info) {
  if (!info || !info->sync_fence_info) {
    return NULL;
  }
  return (struct sync_fence_info*)(uintptr_t)info->sync_fence_info;
}

#endif  // STANDALONE_RENDERER_STUBS_SYNC_SYNC_H_
