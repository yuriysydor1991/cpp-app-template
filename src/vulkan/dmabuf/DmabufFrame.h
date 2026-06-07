#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DMABUFFRAME_STRUCT_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DMABUFFRAME_STRUCT_H

#include <cstdint>

namespace vulkani
{

/**
 * @brief Describes a single plane dma-buf exported from a Vulkan image.
 *
 * Everything the GTK side needs to wrap the exported buffer into a
 * Gdk::DmabufTexture (the DRM fourcc, the DRM format modifier, the file
 * descriptor, and the linear layout). The owning VulkanDmabufRenderer keeps the
 * file descriptor (and the backing Vulkan memory) valid for its whole lifetime.
 */
struct DmabufFrame
{
  /// @brief The exported dma-buf file descriptor (owned by the renderer).
  int fd{-1};
  /// @brief Image width in pixels.
  std::uint32_t width{0};
  /// @brief Image height in pixels.
  std::uint32_t height{0};
  /// @brief Row stride (bytes) of the single plane.
  std::uint32_t stride{0};
  /// @brief Byte offset of the single plane inside the dma-buf.
  std::uint32_t offset{0};
  /// @brief DRM fourcc pixel format (e.g. DRM_FORMAT_XRGB8888).
  std::uint32_t fourcc{0};
  /// @brief DRM format modifier reported by the driver for the image.
  std::uint64_t modifier{0};
};

}  // namespace vulkani

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DMABUFFRAME_STRUCT_H
