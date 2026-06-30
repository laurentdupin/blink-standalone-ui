// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/renderer_c_api.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#if __has_include("vulkan/vulkan.h")
#define BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS 1
#include "vulkan/vulkan.h"
#else
#define BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS 0
#endif
#endif

namespace {

bool Fail(const char* message) {
  std::fprintf(stderr, "static_gpu_external_target_smoke: failed %s\n",
               message);
  return false;
}

void DestroyRenderer(blink_standalone_renderer_t* renderer) {
  if (renderer) {
    blink_standalone_renderer_destroy(renderer);
  }
}

#if defined(_WIN32)

#if BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS

struct VulkanFunctions {
  HMODULE loader = nullptr;
  PFN_vkGetInstanceProcAddr GetInstanceProcAddr = nullptr;
  PFN_vkGetDeviceProcAddr GetDeviceProcAddr = nullptr;
  PFN_vkEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties = nullptr;
  PFN_vkCreateInstance CreateInstance = nullptr;
  PFN_vkDestroyInstance DestroyInstance = nullptr;
  PFN_vkEnumeratePhysicalDevices EnumeratePhysicalDevices = nullptr;
  PFN_vkGetPhysicalDeviceQueueFamilyProperties GetPhysicalDeviceQueueFamilyProperties = nullptr;
  PFN_vkGetPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties = nullptr;
  PFN_vkEnumerateDeviceExtensionProperties EnumerateDeviceExtensionProperties = nullptr;
  PFN_vkCreateDevice CreateDevice = nullptr;
  PFN_vkDestroyDevice DestroyDevice = nullptr;
  PFN_vkGetDeviceQueue GetDeviceQueue = nullptr;
  PFN_vkDeviceWaitIdle DeviceWaitIdle = nullptr;
  PFN_vkCreateImage CreateImage = nullptr;
  PFN_vkDestroyImage DestroyImage = nullptr;
  PFN_vkGetImageMemoryRequirements GetImageMemoryRequirements = nullptr;
  PFN_vkAllocateMemory AllocateMemory = nullptr;
  PFN_vkFreeMemory FreeMemory = nullptr;
  PFN_vkBindImageMemory BindImageMemory = nullptr;
  PFN_vkCreateBuffer CreateBuffer = nullptr;
  PFN_vkDestroyBuffer DestroyBuffer = nullptr;
  PFN_vkGetBufferMemoryRequirements GetBufferMemoryRequirements = nullptr;
  PFN_vkBindBufferMemory BindBufferMemory = nullptr;
  PFN_vkMapMemory MapMemory = nullptr;
  PFN_vkUnmapMemory UnmapMemory = nullptr;
  PFN_vkCreateCommandPool CreateCommandPool = nullptr;
  PFN_vkDestroyCommandPool DestroyCommandPool = nullptr;
  PFN_vkAllocateCommandBuffers AllocateCommandBuffers = nullptr;
  PFN_vkFreeCommandBuffers FreeCommandBuffers = nullptr;
  PFN_vkBeginCommandBuffer BeginCommandBuffer = nullptr;
  PFN_vkEndCommandBuffer EndCommandBuffer = nullptr;
  PFN_vkCmdPipelineBarrier CmdPipelineBarrier = nullptr;
  PFN_vkCmdCopyImageToBuffer CmdCopyImageToBuffer = nullptr;
  PFN_vkQueueSubmit QueueSubmit = nullptr;
  PFN_vkQueueWaitIdle QueueWaitIdle = nullptr;
};

template <typename T>
bool LoadGlobalVulkanFunction(VulkanFunctions* vk, const char* name, T* out) {
  *out = reinterpret_cast<T>(vk->GetInstanceProcAddr(VK_NULL_HANDLE, name));
  return *out != nullptr;
}

template <typename T>
bool LoadInstanceVulkanFunction(VulkanFunctions* vk,
                                VkInstance instance,
                                const char* name,
                                T* out) {
  *out = reinterpret_cast<T>(vk->GetInstanceProcAddr(instance, name));
  return *out != nullptr;
}

template <typename T>
bool LoadDeviceVulkanFunction(VulkanFunctions* vk,
                              VkDevice device,
                              const char* name,
                              T* out) {
  *out = reinterpret_cast<T>(vk->GetDeviceProcAddr(device, name));
  return *out != nullptr;
}

bool LoadVulkanLoader(VulkanFunctions* vk, std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    return false;
  };
  vk->loader = ::LoadLibraryA("vulkan-1.dll");
  if (!vk->loader) {
    return fail("vulkan-1.dll not found");
  }
  vk->GetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
      ::GetProcAddress(vk->loader, "vkGetInstanceProcAddr"));
  if (!vk->GetInstanceProcAddr) {
    return fail("vkGetInstanceProcAddr not found");
  }
  if (!LoadGlobalVulkanFunction(vk, "vkEnumerateInstanceExtensionProperties",
                                &vk->EnumerateInstanceExtensionProperties) ||
      !LoadGlobalVulkanFunction(vk, "vkCreateInstance", &vk->CreateInstance)) {
    return fail("global Vulkan functions missing");
  }
  return true;
}

bool FindVulkanMemoryType(VulkanFunctions* vk,
                          VkPhysicalDevice physical_device,
                          uint32_t memory_type_bits,
                          VkMemoryPropertyFlags required_flags,
                          uint32_t* memory_type_index) {
  VkPhysicalDeviceMemoryProperties properties = {};
  vk->GetPhysicalDeviceMemoryProperties(physical_device, &properties);
  for (uint32_t i = 0; i < properties.memoryTypeCount; ++i) {
    if (((1u << i) & memory_type_bits) == 0) {
      continue;
    }
    if ((properties.memoryTypes[i].propertyFlags & required_flags) ==
        required_flags) {
      *memory_type_index = i;
      return true;
    }
  }
  return false;
}

struct VulkanProbeContext {
  VulkanFunctions vk;
  VkInstance instance = VK_NULL_HANDLE;
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  VkQueue queue = VK_NULL_HANDLE;
  uint32_t queue_family_index = UINT32_MAX;
  VkImage image = VK_NULL_HANDLE;
  VkDeviceMemory image_memory = VK_NULL_HANDLE;
  VkDeviceSize image_allocation_size = 0;
  uint32_t image_memory_type_index = 0;
  VkImageLayout current_layout = VK_IMAGE_LAYOUT_UNDEFINED;
  std::vector<const char*> enabled_instance_extensions;
  std::vector<const char*> enabled_device_extensions;
};

void DestroyVulkanProbeContext(VulkanProbeContext* context) {
  if (!context) {
    return;
  }
  VulkanFunctions& vk = context->vk;
  if (context->device != VK_NULL_HANDLE) {
    if (vk.DeviceWaitIdle) {
      vk.DeviceWaitIdle(context->device);
    }
    if (context->image != VK_NULL_HANDLE) {
      if (vk.DestroyImage) {
        vk.DestroyImage(context->device, context->image, nullptr);
      }
    }
    if (context->image_memory != VK_NULL_HANDLE) {
      if (vk.FreeMemory) {
        vk.FreeMemory(context->device, context->image_memory, nullptr);
      }
    }
    if (vk.DestroyDevice) {
      vk.DestroyDevice(context->device, nullptr);
    }
  }
  if (context->instance != VK_NULL_HANDLE) {
    if (vk.DestroyInstance) {
      vk.DestroyInstance(context->instance, nullptr);
    }
  }
  if (vk.loader) {
    ::FreeLibrary(vk.loader);
  }
}

bool InitializeVulkanProbeContext(VulkanProbeContext* context,
                                  uint32_t width,
                                  uint32_t height,
                                  std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    DestroyVulkanProbeContext(context);
    return false;
  };
  VulkanFunctions& vk = context->vk;
  if (!LoadVulkanLoader(&vk, failure)) {
    return false;
  }

  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "blink_static_gpu_external_target_smoke";
  app_info.apiVersion = VK_API_VERSION_1_1;
  VkInstanceCreateInfo instance_info = {};
  instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pApplicationInfo = &app_info;
  if (vk.CreateInstance(&instance_info, nullptr, &context->instance) !=
      VK_SUCCESS) {
    return fail("vkCreateInstance failed");
  }
  if (!LoadInstanceVulkanFunction(&vk, context->instance, "vkDestroyInstance",
                                  &vk.DestroyInstance) ||
      !LoadInstanceVulkanFunction(&vk, context->instance,
                                  "vkEnumeratePhysicalDevices",
                                  &vk.EnumeratePhysicalDevices) ||
      !LoadInstanceVulkanFunction(
          &vk, context->instance, "vkGetPhysicalDeviceQueueFamilyProperties",
          &vk.GetPhysicalDeviceQueueFamilyProperties) ||
      !LoadInstanceVulkanFunction(
          &vk, context->instance, "vkGetPhysicalDeviceMemoryProperties",
          &vk.GetPhysicalDeviceMemoryProperties) ||
      !LoadInstanceVulkanFunction(
          &vk, context->instance, "vkEnumerateDeviceExtensionProperties",
          &vk.EnumerateDeviceExtensionProperties) ||
      !LoadInstanceVulkanFunction(&vk, context->instance, "vkCreateDevice",
                                  &vk.CreateDevice)) {
    return fail("instance Vulkan functions missing");
  }
  vk.GetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(
      vk.GetInstanceProcAddr(context->instance, "vkGetDeviceProcAddr"));
  if (!vk.GetDeviceProcAddr) {
    return fail("vkGetDeviceProcAddr missing");
  }

  uint32_t device_count = 0;
  if (vk.EnumeratePhysicalDevices(context->instance, &device_count, nullptr) !=
          VK_SUCCESS ||
      device_count == 0) {
    return fail("no Vulkan physical devices");
  }
  std::vector<VkPhysicalDevice> devices(device_count);
  if (vk.EnumeratePhysicalDevices(context->instance, &device_count,
                                  devices.data()) != VK_SUCCESS) {
    return fail("vkEnumeratePhysicalDevices failed");
  }

  for (VkPhysicalDevice candidate : devices) {
    uint32_t queue_family_count = 0;
    vk.GetPhysicalDeviceQueueFamilyProperties(candidate, &queue_family_count,
                                              nullptr);
    std::vector<VkQueueFamilyProperties> families(queue_family_count);
    vk.GetPhysicalDeviceQueueFamilyProperties(candidate, &queue_family_count,
                                              families.data());
    for (uint32_t i = 0; i < queue_family_count; ++i) {
      if ((families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
        context->physical_device = candidate;
        context->queue_family_index = i;
        break;
      }
    }
    if (context->physical_device != VK_NULL_HANDLE) {
      break;
    }
  }
  if (context->physical_device == VK_NULL_HANDLE ||
      context->queue_family_index == UINT32_MAX) {
    return fail("no Vulkan graphics queue");
  }

  float queue_priority = 1.0f;
  VkDeviceQueueCreateInfo queue_info = {};
  queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_info.queueFamilyIndex = context->queue_family_index;
  queue_info.queueCount = 1;
  queue_info.pQueuePriorities = &queue_priority;
  VkDeviceCreateInfo device_info = {};
  device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_info.queueCreateInfoCount = 1;
  device_info.pQueueCreateInfos = &queue_info;
  if (vk.CreateDevice(context->physical_device, &device_info, nullptr,
                      &context->device) != VK_SUCCESS) {
    return fail("vkCreateDevice failed");
  }
  if (!LoadDeviceVulkanFunction(&vk, context->device, "vkDestroyDevice",
                                &vk.DestroyDevice) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkGetDeviceQueue",
                                &vk.GetDeviceQueue) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkDeviceWaitIdle",
                                &vk.DeviceWaitIdle) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkCreateImage",
                                &vk.CreateImage) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkDestroyImage",
                                &vk.DestroyImage) ||
      !LoadDeviceVulkanFunction(&vk, context->device,
                                "vkGetImageMemoryRequirements",
                                &vk.GetImageMemoryRequirements) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkAllocateMemory",
                                &vk.AllocateMemory) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkFreeMemory",
                                &vk.FreeMemory) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkBindImageMemory",
                                &vk.BindImageMemory) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkCreateBuffer",
                                &vk.CreateBuffer) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkDestroyBuffer",
                                &vk.DestroyBuffer) ||
      !LoadDeviceVulkanFunction(&vk, context->device,
                                "vkGetBufferMemoryRequirements",
                                &vk.GetBufferMemoryRequirements) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkBindBufferMemory",
                                &vk.BindBufferMemory) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkMapMemory",
                                &vk.MapMemory) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkUnmapMemory",
                                &vk.UnmapMemory) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkCreateCommandPool",
                                &vk.CreateCommandPool) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkDestroyCommandPool",
                                &vk.DestroyCommandPool) ||
      !LoadDeviceVulkanFunction(&vk, context->device,
                                "vkAllocateCommandBuffers",
                                &vk.AllocateCommandBuffers) ||
      !LoadDeviceVulkanFunction(&vk, context->device,
                                "vkFreeCommandBuffers",
                                &vk.FreeCommandBuffers) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkBeginCommandBuffer",
                                &vk.BeginCommandBuffer) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkEndCommandBuffer",
                                &vk.EndCommandBuffer) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkCmdPipelineBarrier",
                                &vk.CmdPipelineBarrier) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkCmdCopyImageToBuffer",
                                &vk.CmdCopyImageToBuffer) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkQueueSubmit",
                                &vk.QueueSubmit) ||
      !LoadDeviceVulkanFunction(&vk, context->device, "vkQueueWaitIdle",
                                &vk.QueueWaitIdle)) {
    return fail("device Vulkan functions missing");
  }
  vk.GetDeviceQueue(context->device, context->queue_family_index, 0,
                    &context->queue);
  if (context->queue == VK_NULL_HANDLE) {
    return fail("vkGetDeviceQueue failed");
  }

  VkImageCreateInfo image_info = {};
  image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.format = VK_FORMAT_R8G8B8A8_UNORM;
  image_info.extent = {width, height, 1};
  image_info.mipLevels = 1;
  image_info.arrayLayers = 1;
  image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
  image_info.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                     VK_IMAGE_USAGE_SAMPLED_BIT |
                     VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                     VK_IMAGE_USAGE_TRANSFER_DST_BIT;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  if (vk.CreateImage(context->device, &image_info, nullptr, &context->image) !=
      VK_SUCCESS) {
    return fail("vkCreateImage failed");
  }
  VkMemoryRequirements requirements = {};
  vk.GetImageMemoryRequirements(context->device, context->image, &requirements);
  context->image_allocation_size = requirements.size;
  if (!FindVulkanMemoryType(&vk, context->physical_device,
                            requirements.memoryTypeBits,
                            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                            &context->image_memory_type_index)) {
    return fail("Vulkan image memory type not found");
  }
  VkMemoryAllocateInfo allocation_info = {};
  allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocation_info.allocationSize = requirements.size;
  allocation_info.memoryTypeIndex = context->image_memory_type_index;
  if (vk.AllocateMemory(context->device, &allocation_info, nullptr,
                        &context->image_memory) != VK_SUCCESS) {
    return fail("vkAllocateMemory image failed");
  }
  if (vk.BindImageMemory(context->device, context->image,
                         context->image_memory, 0) != VK_SUCCESS) {
    return fail("vkBindImageMemory failed");
  }
  context->current_layout = VK_IMAGE_LAYOUT_UNDEFINED;
  return true;
}

bool ReadbackVulkanImage(VulkanProbeContext* context,
                         uint32_t width,
                         uint32_t height,
                         VkImageLayout current_layout,
                         std::vector<uint32_t>* pixels,
                         std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    return false;
  };
  VulkanFunctions& vk = context->vk;
  const VkDeviceSize byte_count =
      static_cast<VkDeviceSize>(width) * height * sizeof(uint32_t);
  VkBuffer buffer = VK_NULL_HANDLE;
  VkDeviceMemory memory = VK_NULL_HANDLE;
  VkCommandPool command_pool = VK_NULL_HANDLE;
  VkCommandBuffer command_buffer = VK_NULL_HANDLE;
  auto cleanup = [&] {
    if (command_buffer != VK_NULL_HANDLE) {
      vk.FreeCommandBuffers(context->device, command_pool, 1, &command_buffer);
    }
    if (command_pool != VK_NULL_HANDLE) {
      vk.DestroyCommandPool(context->device, command_pool, nullptr);
    }
    if (memory != VK_NULL_HANDLE) {
      vk.FreeMemory(context->device, memory, nullptr);
    }
    if (buffer != VK_NULL_HANDLE) {
      vk.DestroyBuffer(context->device, buffer, nullptr);
    }
  };

  VkBufferCreateInfo buffer_info = {};
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = byte_count;
  buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (vk.CreateBuffer(context->device, &buffer_info, nullptr, &buffer) !=
      VK_SUCCESS) {
    return fail("vkCreateBuffer failed");
  }
  VkMemoryRequirements requirements = {};
  vk.GetBufferMemoryRequirements(context->device, buffer, &requirements);
  uint32_t memory_type_index = 0;
  if (!FindVulkanMemoryType(
          &vk, context->physical_device, requirements.memoryTypeBits,
          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
              VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
          &memory_type_index)) {
    cleanup();
    return fail("Vulkan readback memory type not found");
  }
  VkMemoryAllocateInfo allocation_info = {};
  allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocation_info.allocationSize = requirements.size;
  allocation_info.memoryTypeIndex = memory_type_index;
  if (vk.AllocateMemory(context->device, &allocation_info, nullptr, &memory) !=
      VK_SUCCESS) {
    cleanup();
    return fail("vkAllocateMemory readback failed");
  }
  if (vk.BindBufferMemory(context->device, buffer, memory, 0) != VK_SUCCESS) {
    cleanup();
    return fail("vkBindBufferMemory failed");
  }

  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.queueFamilyIndex = context->queue_family_index;
  if (vk.CreateCommandPool(context->device, &pool_info, nullptr,
                           &command_pool) != VK_SUCCESS) {
    cleanup();
    return fail("vkCreateCommandPool failed");
  }
  VkCommandBufferAllocateInfo command_info = {};
  command_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  command_info.commandPool = command_pool;
  command_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  command_info.commandBufferCount = 1;
  if (vk.AllocateCommandBuffers(context->device, &command_info,
                                &command_buffer) != VK_SUCCESS) {
    cleanup();
    return fail("vkAllocateCommandBuffers failed");
  }
  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  if (vk.BeginCommandBuffer(command_buffer, &begin_info) != VK_SUCCESS) {
    cleanup();
    return fail("vkBeginCommandBuffer failed");
  }
  VkImageMemoryBarrier to_transfer = {};
  to_transfer.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  to_transfer.oldLayout = current_layout;
  to_transfer.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
  to_transfer.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  to_transfer.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  to_transfer.image = context->image;
  to_transfer.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  to_transfer.subresourceRange.levelCount = 1;
  to_transfer.subresourceRange.layerCount = 1;
  to_transfer.srcAccessMask = VK_ACCESS_SHADER_READ_BIT |
                              VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                              VK_ACCESS_TRANSFER_WRITE_BIT;
  to_transfer.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
  vk.CmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                        VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0,
                        nullptr, 1, &to_transfer);
  VkBufferImageCopy copy_region = {};
  copy_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  copy_region.imageSubresource.layerCount = 1;
  copy_region.imageExtent = {width, height, 1};
  vk.CmdCopyImageToBuffer(command_buffer, context->image,
                          VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1,
                          &copy_region);
  VkImageMemoryBarrier restore = to_transfer;
  restore.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
  restore.newLayout = current_layout;
  restore.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
  restore.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
  vk.CmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0,
                        nullptr, 1, &restore);
  if (vk.EndCommandBuffer(command_buffer) != VK_SUCCESS) {
    cleanup();
    return fail("vkEndCommandBuffer failed");
  }
  VkSubmitInfo submit_info = {};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command_buffer;
  if (vk.QueueSubmit(context->queue, 1, &submit_info, VK_NULL_HANDLE) !=
      VK_SUCCESS) {
    cleanup();
    return fail("vkQueueSubmit failed");
  }
  vk.QueueWaitIdle(context->queue);

  void* mapped = nullptr;
  if (vk.MapMemory(context->device, memory, 0, byte_count, 0, &mapped) !=
          VK_SUCCESS ||
      !mapped) {
    cleanup();
    return fail("vkMapMemory failed");
  }
  pixels->resize(static_cast<size_t>(width) * height);
  std::memcpy(pixels->data(), mapped, static_cast<size_t>(byte_count));
  vk.UnmapMemory(context->device, memory);
  cleanup();
  return true;
}

bool RunVulkanExternalTargetSmoke() {
  constexpr uint32_t kWidth = 128;
  constexpr uint32_t kHeight = 64;
  constexpr uint32_t kExpectedBackground = 0xff123456u;
  constexpr uint32_t kExpectedBox = 0xffd06329u;
  VulkanProbeContext context;
  std::string failure;
  if (!InitializeVulkanProbeContext(&context, kWidth, kHeight, &failure)) {
    std::printf("static_gpu_external_target_smoke: blocked vulkan=0 "
                "failure=%s\n",
                failure.c_str());
    return true;
  }

  blink_standalone_renderer_config_t config = {};
  config.width = static_cast<int>(kWidth);
  config.height = static_cast<int>(kHeight);
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    DestroyVulkanProbeContext(&context);
    return Fail("vulkan create");
  }

  blink_standalone_vulkan_external_device_t external_device = {};
  external_device.vk_instance = context.instance;
  external_device.vk_physical_device = context.physical_device;
  external_device.vk_device = context.device;
  external_device.vk_queue = context.queue;
  external_device.queue_family_index = context.queue_family_index;
  external_device.api_version = VK_API_VERSION_1_1;
  external_device.enabled_instance_extensions =
      context.enabled_instance_extensions.data();
  external_device.enabled_instance_extension_count =
      context.enabled_instance_extensions.size();
  external_device.enabled_device_extensions =
      context.enabled_device_extensions.data();
  external_device.enabled_device_extension_count =
      context.enabled_device_extensions.size();
  status = blink_standalone_renderer_configure_vulkan_external_device(
      renderer, &external_device);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed configure_vulkan "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;width:100%;height:100%;"
      "background:#123456}#box{position:absolute;left:16px;top:12px;"
      "width:80px;height:32px;background:#d06329}</style><div id='box'></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed vulkan set_document "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(
          renderer, BLINK_STANDALONE_GPU_BACKEND_VULKAN);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0 ||
      (capabilities & BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET) == 0) {
    std::printf(
        "static_gpu_external_target_smoke: blocked vulkan=0 capabilities=%u\n",
        capabilities);
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return true;
  }

  blink_standalone_external_gpu_target_t target = {};
  target.common.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
  target.common.logical_width = kWidth;
  target.common.logical_height = kHeight;
  target.common.physical_width = kWidth;
  target.common.physical_height = kHeight;
  target.common.device_scale_factor = 1.0f;
  target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
  target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
  target.common.generation = 1;
  target.vulkan.vk_image = context.image;
  target.vulkan.vk_device = context.device;
  target.vulkan.vk_physical_device = context.physical_device;
  target.vulkan.vk_device_memory = context.image_memory;
  target.vulkan.vk_format = VK_FORMAT_R8G8B8A8_UNORM;
  target.vulkan.width = kWidth;
  target.vulkan.height = kHeight;
  target.vulkan.current_layout = VK_IMAGE_LAYOUT_UNDEFINED;
  target.vulkan.required_final_layout =
      VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  target.vulkan.queue_family_index = context.queue_family_index;
  target.vulkan.allocation_size = context.image_allocation_size;
  target.vulkan.memory_type_index = context.image_memory_type_index;
  target.vulkan.image_tiling = VK_IMAGE_TILING_OPTIMAL;
  target.vulkan.image_usage_flags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                                    VK_IMAGE_USAGE_SAMPLED_BIT |
                                    VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                                    VK_IMAGE_USAGE_TRANSFER_DST_BIT;
  target.vulkan.sample_count = VK_SAMPLE_COUNT_1_BIT;
  target.vulkan.level_count = 1;

  blink_standalone_gpu_render_result_t result = {};
  status =
      blink_standalone_renderer_render_to_gpu_target(renderer, &target, &result);
  for (int retry = 0;
       status == BLINK_STANDALONE_STATUS_PENDING && result.target_written == 0 &&
       retry < 32;
       ++retry) {
    blink_standalone_update_result_t update = {};
    status = blink_standalone_renderer_update(
        renderer, 0.016 * static_cast<double>(retry + 1), &update);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      break;
    }
    result = blink_standalone_gpu_render_result_t{};
    target.common.generation++;
    target.vulkan.current_layout = target.vulkan.required_final_layout;
    status = blink_standalone_renderer_render_to_gpu_target(renderer, &target,
                                                            &result);
  }
  if (status != BLINK_STANDALONE_STATUS_OK || result.target_written == 0 ||
      result.backend != BLINK_STANDALONE_GPU_BACKEND_VULKAN ||
      result.width != kWidth || result.height != kHeight) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed vulkan_render "
                 "status=%d result_status=%u backend=%u written=%u size=%ux%u "
                 "error=%s\n",
                 status, result.status, result.backend, result.target_written,
                 result.width, result.height,
                 blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  std::vector<uint32_t> pixels;
  if (!ReadbackVulkanImage(&context, kWidth, kHeight,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, &pixels,
                           &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed vulkan_readback "
                 "failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  auto pixel_at = [&](uint32_t x, uint32_t y) {
    const uint32_t rgba = pixels[static_cast<size_t>(y) * kWidth + x];
    return (rgba & 0xff000000u) | ((rgba & 0x000000ffu) << 16) |
           (rgba & 0x0000ff00u) | ((rgba & 0x00ff0000u) >> 16);
  };
  const uint32_t observed_background = pixel_at(4, 4);
  const uint32_t observed_box = pixel_at(20, 20);
  uint32_t background_pixels = 0;
  uint32_t box_pixels = 0;
  uint32_t nontransparent_pixels = 0;
  for (uint32_t rgba : pixels) {
    const uint32_t pixel = (rgba & 0xff000000u) |
                           ((rgba & 0x000000ffu) << 16) |
                           (rgba & 0x0000ff00u) |
                           ((rgba & 0x00ff0000u) >> 16);
    if ((pixel >> 24) != 0) {
      ++nontransparent_pixels;
    }
    if (pixel == kExpectedBackground) {
      ++background_pixels;
    }
    if (pixel == kExpectedBox) {
      ++box_pixels;
    }
  }

  DestroyRenderer(renderer);
  DestroyVulkanProbeContext(&context);

  if (observed_background != kExpectedBackground ||
      observed_box != kExpectedBox || background_pixels == 0 ||
      box_pixels == 0 || nontransparent_pixels == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed vulkan_pixels "
                 "observed_background=%08x observed_box=%08x "
                 "background_pixels=%u box_pixels=%u nontransparent=%u\n",
                 observed_background, observed_box, background_pixels,
                 box_pixels, nontransparent_pixels);
    return false;
  }
  std::printf(
      "static_gpu_external_target_smoke: ok vulkan=1 target_written=%u "
      "size=%ux%u observed_background=%08x observed_box=%08x "
      "background_pixels=%u box_pixels=%u nontransparent=%u\n",
      result.target_written, result.width, result.height, observed_background,
      observed_box, background_pixels, box_pixels, nontransparent_pixels);
  return true;
}

#endif  // BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS

bool ReadbackD3D12Texture(ID3D12Device* device,
                          ID3D12CommandQueue* queue,
                          ID3D12Resource* texture,
                          uint32_t width,
                          uint32_t height,
                          D3D12_RESOURCE_STATES current_state,
                          std::vector<uint32_t>* pixels,
                          std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    return false;
  };
  if (!device || !queue || !texture || !pixels || width == 0 || height == 0) {
    return fail("invalid D3D12 readback arguments");
  }

  const D3D12_RESOURCE_DESC texture_desc = texture->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
  UINT row_count = 0;
  UINT64 row_size_bytes = 0;
  UINT64 total_bytes = 0;
  device->GetCopyableFootprints(&texture_desc, 0, 1, 0, &footprint,
                                &row_count, &row_size_bytes, &total_bytes);
  if (row_count == 0 || row_size_bytes == 0 || total_bytes == 0) {
    return fail("D3D12 readback footprint is empty");
  }

  D3D12_HEAP_PROPERTIES readback_heap = {};
  readback_heap.Type = D3D12_HEAP_TYPE_READBACK;
  readback_heap.CreationNodeMask = 1;
  readback_heap.VisibleNodeMask = 1;
  D3D12_RESOURCE_DESC buffer_desc = {};
  buffer_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
  buffer_desc.Width = total_bytes;
  buffer_desc.Height = 1;
  buffer_desc.DepthOrArraySize = 1;
  buffer_desc.MipLevels = 1;
  buffer_desc.SampleDesc.Count = 1;
  buffer_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  Microsoft::WRL::ComPtr<ID3D12Resource> readback;
  if (FAILED(device->CreateCommittedResource(
          &readback_heap, D3D12_HEAP_FLAG_NONE, &buffer_desc,
          D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback))) ||
      !readback) {
    return fail("D3D12 readback buffer creation failed");
  }

  Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
  if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                            IID_PPV_ARGS(&allocator))) ||
      !allocator) {
    return fail("D3D12 readback command allocator creation failed");
  }
  Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
  if (FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                       allocator.Get(), nullptr,
                                       IID_PPV_ARGS(&command_list))) ||
      !command_list) {
    return fail("D3D12 readback command list creation failed");
  }

  D3D12_TEXTURE_COPY_LOCATION src = {};
  src.pResource = texture;
  src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
  src.SubresourceIndex = 0;
  D3D12_TEXTURE_COPY_LOCATION dst = {};
  dst.pResource = readback.Get();
  dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
  dst.PlacedFootprint = footprint;
  if (current_state != D3D12_RESOURCE_STATE_COPY_SOURCE) {
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = texture;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = current_state;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE;
    command_list->ResourceBarrier(1, &barrier);
  }
  command_list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
  if (FAILED(command_list->Close())) {
    return fail("D3D12 readback command list close failed");
  }
  ID3D12CommandList* command_lists[] = {command_list.Get()};
  queue->ExecuteCommandLists(1, command_lists);

  Microsoft::WRL::ComPtr<ID3D12Fence> fence;
  if (FAILED(device->CreateFence(0, D3D12_FENCE_FLAG_NONE,
                                 IID_PPV_ARGS(&fence))) ||
      !fence) {
    return fail("D3D12 readback fence creation failed");
  }
  HANDLE event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
  if (!event_handle) {
    return fail("D3D12 readback event creation failed");
  }
  constexpr UINT64 kFenceValue = 1;
  if (FAILED(queue->Signal(fence.Get(), kFenceValue))) {
    ::CloseHandle(event_handle);
    return fail("D3D12 readback fence signal failed");
  }
  if (fence->GetCompletedValue() < kFenceValue) {
    if (FAILED(fence->SetEventOnCompletion(kFenceValue, event_handle))) {
      ::CloseHandle(event_handle);
      return fail("D3D12 readback fence wait setup failed");
    }
    ::WaitForSingleObject(event_handle, 5000);
  }
  ::CloseHandle(event_handle);
  if (fence->GetCompletedValue() < kFenceValue) {
    return fail("D3D12 readback fence wait timed out");
  }

  void* mapped = nullptr;
  D3D12_RANGE read_range = {0, static_cast<SIZE_T>(total_bytes)};
  if (FAILED(readback->Map(0, &read_range, &mapped)) || !mapped) {
    return fail("D3D12 readback map failed");
  }
  const uint8_t* mapped_bytes = static_cast<const uint8_t*>(mapped);
  pixels->assign(static_cast<size_t>(width) * static_cast<size_t>(height), 0);
  for (uint32_t y = 0; y < height; ++y) {
    const uint8_t* row =
        mapped_bytes + footprint.Offset +
        static_cast<size_t>(y) * footprint.Footprint.RowPitch;
    for (uint32_t x = 0; x < width; ++x) {
      const uint8_t* p = row + static_cast<size_t>(x) * 4u;
      (*pixels)[static_cast<size_t>(y) * width + x] =
          (static_cast<uint32_t>(p[3]) << 24) |
          (static_cast<uint32_t>(p[0]) << 16) |
          (static_cast<uint32_t>(p[1]) << 8) | static_cast<uint32_t>(p[2]);
    }
  }
  D3D12_RANGE written_range = {0, 0};
  readback->Unmap(0, &written_range);
  return true;
}

bool RunD3D12ExternalTargetSmoke() {
  constexpr uint32_t kWidth = 128;
  constexpr uint32_t kHeight = 64;
  constexpr uint32_t kExpectedBackground = 0xff123456u;
  constexpr uint32_t kExpectedBox = 0xffd06329u;

  Microsoft::WRL::ComPtr<ID3D12Device> device;
  HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0,
                                 IID_PPV_ARGS(&device));
  if (FAILED(hr) || !device) {
    std::printf(
        "static_gpu_external_target_smoke: blocked d3d12=0 "
        "device_hr=0x%08lx\n",
        static_cast<unsigned long>(hr));
    return true;
  }

  D3D12_COMMAND_QUEUE_DESC queue_desc = {};
  queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue;
  hr = device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&queue));
  if (FAILED(hr) || !queue) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed d3d12_queue "
                 "hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  D3D12_HEAP_PROPERTIES heap_properties = {};
  heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
  heap_properties.CreationNodeMask = 1;
  heap_properties.VisibleNodeMask = 1;
  D3D12_RESOURCE_DESC resource_desc = {};
  resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Width = kWidth;
  resource_desc.Height = kHeight;
  resource_desc.DepthOrArraySize = 1;
  resource_desc.MipLevels = 1;
  resource_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  resource_desc.SampleDesc.Count = 1;
  resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET |
                        D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
  Microsoft::WRL::ComPtr<ID3D12Resource> target_resource;
  hr = device->CreateCommittedResource(
      &heap_properties, D3D12_HEAP_FLAG_SHARED, &resource_desc,
      D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&target_resource));
  if (FAILED(hr) || !target_resource) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed d3d12_target "
                 "hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  HANDLE shared_handle = nullptr;
  hr = device->CreateSharedHandle(target_resource.Get(), nullptr, GENERIC_ALL,
                                  nullptr, &shared_handle);
  if (FAILED(hr) || !shared_handle) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed d3d12_shared_handle "
                 "hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  blink_standalone_renderer_config_t config = {};
  config.width = static_cast<int>(kWidth);
  config.height = static_cast<int>(kHeight);
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    ::CloseHandle(shared_handle);
    return Fail("create");
  }

  blink_standalone_d3d12_external_device_t external_device = {};
  external_device.d3d12_device = device.Get();
  external_device.d3d12_command_queue = queue.Get();
  status = blink_standalone_renderer_configure_d3d12_external_device(
      renderer, &external_device);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed configure_d3d12 "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(shared_handle);
    return false;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;width:100%;height:100%;"
      "background:#123456}#box{position:absolute;left:16px;top:12px;"
      "width:80px;height:32px;background:#d06329}</style><div id='box'></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed set_document "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(shared_handle);
    return false;
  }

  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(
          renderer, BLINK_STANDALONE_GPU_BACKEND_D3D12);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0 ||
      (capabilities & BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET) == 0) {
    std::printf(
        "static_gpu_external_target_smoke: blocked d3d12=0 capabilities=%u\n",
        capabilities);
    DestroyRenderer(renderer);
    ::CloseHandle(shared_handle);
    return true;
  }

  blink_standalone_external_gpu_target_t target = {};
  target.common.backend = BLINK_STANDALONE_GPU_BACKEND_D3D12;
  target.common.logical_width = kWidth;
  target.common.logical_height = kHeight;
  target.common.physical_width = kWidth;
  target.common.physical_height = kHeight;
  target.common.device_scale_factor = 1.0f;
  target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
  target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
  target.common.generation = 1;
  target.d3d12.d3d12_device = device.Get();
  target.d3d12.d3d12_command_queue = queue.Get();
  target.d3d12.d3d12_resource = target_resource.Get();
  target.d3d12.shared_handle = shared_handle;
  target.d3d12.dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;
  target.d3d12.width = kWidth;
  target.d3d12.height = kHeight;
  target.d3d12.current_state = D3D12_RESOURCE_STATE_COMMON;
  target.d3d12.required_final_state =
      D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

  blink_standalone_gpu_render_result_t result = {};
  status =
      blink_standalone_renderer_render_to_gpu_target(renderer, &target, &result);
  for (int retry = 0;
       status == BLINK_STANDALONE_STATUS_PENDING && result.target_written == 0 &&
       retry < 32;
       ++retry) {
    blink_standalone_update_result_t update = {};
    status = blink_standalone_renderer_update(
        renderer, 0.016 * static_cast<double>(retry + 1), &update);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      break;
    }
    result = blink_standalone_gpu_render_result_t{};
    target.common.generation++;
    target.d3d12.current_state = target.d3d12.required_final_state;
    status = blink_standalone_renderer_render_to_gpu_target(renderer, &target,
                                                            &result);
  }
  if (status != BLINK_STANDALONE_STATUS_OK || result.target_written == 0 ||
      result.backend != BLINK_STANDALONE_GPU_BACKEND_D3D12 ||
      result.width != kWidth || result.height != kHeight) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed d3d12_render "
                 "status=%d result_status=%u backend=%u written=%u size=%ux%u "
                 "error=%s\n",
                 status, result.status, result.backend, result.target_written,
                 result.width, result.height,
                 blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(shared_handle);
    return false;
  }

  std::vector<uint32_t> pixels;
  std::string failure;
  if (!ReadbackD3D12Texture(
          device.Get(), queue.Get(), target_resource.Get(), kWidth, kHeight,
          static_cast<D3D12_RESOURCE_STATES>(target.d3d12.required_final_state),
          &pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed d3d12_readback "
                 "failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    ::CloseHandle(shared_handle);
    return false;
  }

  uint32_t background_pixels = 0;
  uint32_t box_pixels = 0;
  uint32_t nontransparent_pixels = 0;
  const uint32_t observed_background = pixels[4 * kWidth + 4];
  const uint32_t observed_box = pixels[20 * kWidth + 20];
  for (uint32_t pixel : pixels) {
    if ((pixel >> 24) != 0) {
      ++nontransparent_pixels;
    }
    if (pixel == kExpectedBackground) {
      ++background_pixels;
    }
    if (pixel == kExpectedBox) {
      ++box_pixels;
    }
  }

  DestroyRenderer(renderer);
  ::CloseHandle(shared_handle);

  if (observed_background != kExpectedBackground ||
      observed_box != kExpectedBox || background_pixels == 0 ||
      box_pixels == 0 || nontransparent_pixels != kWidth * kHeight) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed d3d12_pixels "
                 "observed_background=%08x observed_box=%08x "
                 "background_pixels=%u box_pixels=%u nontransparent=%u\n",
                 observed_background, observed_box, background_pixels,
                 box_pixels, nontransparent_pixels);
    return false;
  }

  std::printf(
      "static_gpu_external_target_smoke: ok d3d12=1 target_written=%u "
      "size=%ux%u observed_background=%08x observed_box=%08x "
      "background_pixels=%u box_pixels=%u nontransparent=%u\n",
      result.target_written, result.width, result.height, observed_background,
      observed_box, background_pixels, box_pixels, nontransparent_pixels);
  return true;
}

#endif  // defined(_WIN32)

}  // namespace

int main() {
#if defined(_WIN32)
  bool ok = true;
#if BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS
  ok = RunVulkanExternalTargetSmoke() && ok;
#else
  std::printf(
      "static_gpu_external_target_smoke: blocked vulkan=0 "
      "failure=static package lacks Vulkan headers\n");
#endif
  ok = RunD3D12ExternalTargetSmoke() && ok;
  return ok ? 0 : 1;
#else
  std::printf(
      "static_gpu_external_target_smoke: blocked platform=non_windows "
      "d3d12=0 vulkan=blocked_package_lacks_vulkan_headers_and_loader_metadata\n");
  return 0;
#endif
}
