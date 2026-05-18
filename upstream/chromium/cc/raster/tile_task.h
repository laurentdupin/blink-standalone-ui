// Standalone CC tile-task declaration shim.
//
// Blink's Image::SharedCCDecodeCache includes the CC image decode cache API,
// which references TileTask. The optional PNG image experiment does not enable
// compositor tile scheduling.

#ifndef CC_RASTER_TILE_TASK_H_
#define CC_RASTER_TILE_TASK_H_

#include "base/memory/ref_counted.h"

namespace cc {

class TileTask : public base::RefCountedThreadSafe<TileTask> {
 public:
  TileTask() = default;

  TileTask(const TileTask&) = delete;
  TileTask& operator=(const TileTask&) = delete;

 protected:
  friend class base::RefCountedThreadSafe<TileTask>;
  virtual ~TileTask() = default;
};

}  // namespace cc

#endif  // CC_RASTER_TILE_TASK_H_
