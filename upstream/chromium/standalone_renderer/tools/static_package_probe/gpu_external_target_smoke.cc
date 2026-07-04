// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/renderer_c_api.h"

#include <chrono>
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

bool ValidatePublicGpuBackdropEffectTable(blink_standalone_renderer_t* renderer,
                                          uint32_t expected_effects,
                                          const char* label) {
  const size_t api_effects =
      blink_standalone_renderer_gpu_backdrop_effect_count(renderer);
  if (expected_effects == 0 || api_effects != expected_effects) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed %s_effect_table "
                 "expected=%u api_effects=%zu\n",
                 label, expected_effects, api_effects);
    return false;
  }
  blink_standalone_gpu_backdrop_effect_t effect = {};
  const blink_standalone_status_code_t status =
      blink_standalone_renderer_get_gpu_backdrop_effect(renderer, 0, &effect);
  if (status != BLINK_STANDALONE_STATUS_OK || effect.id == 0 ||
      effect.filter_op_count == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed %s_effect_record "
                 "status=%d id=%u generation=%llu ops=%u bounds=%.1fx%.1f "
                 "element=%s error=%s\n",
                 label, status, effect.id,
                 static_cast<unsigned long long>(effect.generation),
                 effect.filter_op_count, effect.bounds.width,
                 effect.bounds.height,
                 effect.element_id ? effect.element_id : "",
                 blink_standalone_renderer_last_error(renderer));
    return false;
  }
  return true;
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

bool CreateVulkanProbeImage(VulkanProbeContext* context,
                            uint32_t width,
                            uint32_t height,
                            VkImage* image,
                            VkDeviceMemory* memory,
                            VkDeviceSize* allocation_size,
                            uint32_t* memory_type_index,
                            std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    if (image && *image != VK_NULL_HANDLE) {
      context->vk.DestroyImage(context->device, *image, nullptr);
      *image = VK_NULL_HANDLE;
    }
    if (memory && *memory != VK_NULL_HANDLE) {
      context->vk.FreeMemory(context->device, *memory, nullptr);
      *memory = VK_NULL_HANDLE;
    }
    return false;
  };
  if (!context || context->device == VK_NULL_HANDLE || !image || !memory ||
      !allocation_size || !memory_type_index) {
    return fail("invalid Vulkan image arguments");
  }
  *image = VK_NULL_HANDLE;
  *memory = VK_NULL_HANDLE;
  *allocation_size = 0;
  *memory_type_index = 0;

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
  if (context->vk.CreateImage(context->device, &image_info, nullptr, image) !=
      VK_SUCCESS) {
    return fail("vkCreateImage failed");
  }
  VkMemoryRequirements requirements = {};
  context->vk.GetImageMemoryRequirements(context->device, *image,
                                         &requirements);
  *allocation_size = requirements.size;
  if (!FindVulkanMemoryType(&context->vk, context->physical_device,
                            requirements.memoryTypeBits,
                            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                            memory_type_index)) {
    return fail("Vulkan image memory type not found");
  }
  VkMemoryAllocateInfo allocation_info = {};
  allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocation_info.allocationSize = requirements.size;
  allocation_info.memoryTypeIndex = *memory_type_index;
  if (context->vk.AllocateMemory(context->device, &allocation_info, nullptr,
                                 memory) != VK_SUCCESS) {
    return fail("vkAllocateMemory image failed");
  }
  if (context->vk.BindImageMemory(context->device, *image, *memory, 0) !=
      VK_SUCCESS) {
    return fail("vkBindImageMemory failed");
  }
  return true;
}

bool ReadbackVulkanImageHandle(VulkanProbeContext* context,
                               VkImage image,
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
  to_transfer.image = image;
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
  vk.CmdCopyImageToBuffer(command_buffer, image,
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

bool ReadbackVulkanImage(VulkanProbeContext* context,
                         uint32_t width,
                         uint32_t height,
                         VkImageLayout current_layout,
                         std::vector<uint32_t>* pixels,
                         std::string* failure) {
  return ReadbackVulkanImageHandle(context, context->image, width, height,
                                   current_layout, pixels, failure);
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
  const uint32_t observed_background = pixel_at(8, 8);
  const uint32_t observed_box = pixel_at(40, 40);
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

  if (observed_background != kExpectedBackground || background_pixels == 0 ||
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

bool RunVulkanDedicatedThreadFirstPublishSmoke() {
  constexpr uint32_t kLogicalWidth = 1280;
  constexpr uint32_t kLogicalHeight = 720;
  constexpr uint32_t kPhysicalWidth = 2560;
  constexpr uint32_t kPhysicalHeight = 1440;
  constexpr uint32_t kExpectedBackground = 0xff123456u;
  constexpr uint32_t kExpectedBox = 0xffd06329u;

  VulkanProbeContext context;
  std::string failure;
  if (!InitializeVulkanProbeContext(&context, kPhysicalWidth, kPhysicalHeight,
                                    &failure)) {
    std::printf("static_gpu_external_target_smoke: blocked "
                "vulkan_dedicated=0 failure=%s\n",
                failure.c_str());
    return true;
  }

  VkImage mask_image = VK_NULL_HANDLE;
  VkDeviceMemory mask_memory = VK_NULL_HANDLE;
  VkDeviceSize mask_allocation_size = 0;
  uint32_t mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(&context, kPhysicalWidth, kPhysicalHeight,
                              &mask_image, &mask_memory, &mask_allocation_size,
                              &mask_memory_type_index, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_mask_image failure=%s\n",
                 failure.c_str());
    DestroyVulkanProbeContext(&context);
    return false;
  }

  auto destroy_mask = [&]() {
    if (context.device != VK_NULL_HANDLE) {
      if (context.vk.DeviceWaitIdle) {
        context.vk.DeviceWaitIdle(context.device);
      }
      if (mask_image != VK_NULL_HANDLE) {
        context.vk.DestroyImage(context.device, mask_image, nullptr);
        mask_image = VK_NULL_HANDLE;
      }
      if (mask_memory != VK_NULL_HANDLE) {
        context.vk.FreeMemory(context.device, mask_memory, nullptr);
        mask_memory = VK_NULL_HANDLE;
      }
    }
  };

  blink_standalone_renderer_config_t config = {};
  config.width = static_cast<int>(kLogicalWidth);
  config.height = static_cast<int>(kLogicalHeight);
  config.device_scale_factor = 2.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create_dedicated_thread(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return Fail("vulkan create_dedicated_thread");
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
                 "static_gpu_external_target_smoke: failed "
                 "configure_vulkan_dedicated status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;width:100%;height:100%;"
      "background:linear-gradient(90deg,#123456,#2878d8)}#box{position:"
      "absolute;left:16px;top:12px;width:80px;height:32px;background:#d06329}"
      "#glass{position:absolute;left:120px;top:80px;width:360px;height:180px;"
      "border-radius:28px;background:rgba(255,255,255,.25);"
      "backdrop-filter:blur(12px) saturate(160%);"
      "-webkit-backdrop-filter:blur(12px) saturate(160%)}#dynamic{position:"
      "absolute;left:160px;top:300px;width:220px;height:120px;background:"
      "#1b5e20}#label{position:"
      "absolute;left:120px;top:300px;color:white;font:700 160px Arial,"
      "sans-serif;line-height:1}</style><div id='box'></div>"
      "<style id='live_style'>#dynamic{background:#1b5e20}</style>"
      "<div id='glass'></div><div id='dynamic'></div>"
      "<div id='label'>IIIIIIIIII</div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "set_document_vulkan_dedicated status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(
          renderer, BLINK_STANDALONE_GPU_BACKEND_VULKAN);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0 ||
      (capabilities & BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET) == 0) {
    std::printf(
        "static_gpu_external_target_smoke: blocked vulkan_dedicated=0 "
        "capabilities=%u\n",
        capabilities);
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return true;
  }

  blink_standalone_external_gpu_target_t target = {};
  target.common.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
  target.common.logical_width = kLogicalWidth;
  target.common.logical_height = kLogicalHeight;
  target.common.physical_width = kPhysicalWidth;
  target.common.physical_height = kPhysicalHeight;
  target.common.device_scale_factor = 2.0f;
  target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
  target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
  target.common.generation = 1;
  target.vulkan.vk_image = context.image;
  target.vulkan.vk_device = context.device;
  target.vulkan.vk_physical_device = context.physical_device;
  target.vulkan.vk_device_memory = context.image_memory;
  target.vulkan.vk_format = VK_FORMAT_R8G8B8A8_UNORM;
  target.vulkan.width = kPhysicalWidth;
  target.vulkan.height = kPhysicalHeight;
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

  blink_standalone_external_gpu_target_t mask_target = target;
  mask_target.common.generation = 1;
  mask_target.vulkan.vk_image = mask_image;
  mask_target.vulkan.vk_device_memory = mask_memory;
  mask_target.vulkan.allocation_size = mask_allocation_size;
  mask_target.vulkan.memory_type_index = mask_memory_type_index;

  blink_standalone_dedicated_thread_gpu_frame_request_t request = {};
  request.timeline_time_seconds = 0.016;
  request.poll_interval_ms = 1;
  request.max_poll_iterations = 5000;
  request.source_request.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
  request.source_request.request_generation = 1;
  request.source_request.timeline_time_seconds = request.timeline_time_seconds;
  request.source_request.logical_width = kLogicalWidth;
  request.source_request.logical_height = kLogicalHeight;
  request.source_request.physical_width = kPhysicalWidth;
  request.source_request.physical_height = kPhysicalHeight;
  request.source_request.device_scale_factor = 2.0f;
  request.source_request.max_work_budget_ms = 1000.0;
  request.render_request.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
  request.render_request.request_generation = 1;
  request.render_request.flags =
      BLINK_STANDALONE_GPU_ASYNC_BACKDROP_MASK_REQUIRED;
  request.render_request.mask_encoding =
      BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_RGBA8_ID_COVERAGE;
  request.render_request.main_target = target;
  request.render_request.backdrop_mask_target = mask_target;

  blink_standalone_dedicated_thread_gpu_frame_result_t command_result = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &request, &command_result);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_vulkan_dedicated status=%d result_status=%u "
                 "state=%u error=%s\n",
                 status, command_result.status, command_result.state,
                 command_result.error_message
                     ? command_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const uint64_t command_id = command_result.command_id;
  const auto mutation_start = std::chrono::steady_clock::now();
  status = blink_standalone_renderer_set_element_text(
      renderer, "live_style", "#dynamic{background:#ff00ff}");
  const auto mutation_end = std::chrono::steady_clock::now();
  const double mutation_ms =
      std::chrono::duration<double, std::milli>(mutation_end - mutation_start)
          .count();
  if (status != BLINK_STANDALONE_STATUS_OK || mutation_ms > 10.0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_mutation_enqueue status=%d elapsed_ms=%.3f "
                 "error=%s\n",
                 status, mutation_ms,
                 blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  for (uint32_t poll = 0;
       command_result.state ==
               BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING &&
       poll < 10000;
       ++poll) {
    ::Sleep(1);
    status = blink_standalone_renderer_poll_dedicated_thread_gpu_frame(
        renderer, command_id, &command_result);
    if (status != BLINK_STANDALONE_STATUS_OK &&
        status != BLINK_STANDALONE_STATUS_PENDING) {
      break;
    }
  }

  if (status != BLINK_STANDALONE_STATUS_OK ||
      command_result.state !=
          BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED ||
      command_result.render_result.main_target_written == 0 ||
      command_result.render_result.backdrop_mask_written == 0 ||
      command_result.render_result.effect_count == 0 ||
      command_result.render_result.physical_width != kPhysicalWidth ||
      command_result.render_result.physical_height != kPhysicalHeight) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_first_publish status=%d result_status=%u "
                 "state=%u render_state=%u written=%u mask_written=%u "
                 "effects=%u size=%ux%u source_state=%u source_status=%u "
                 "poll_iterations=%u elapsed_ms=%.3f source_ms=%.3f "
                 "submit_ms=%.3f poll_ms=%.3f error=%s\n",
                 status, command_result.status, command_result.state,
                 command_result.render_result.state,
                 command_result.render_result.main_target_written,
                 command_result.render_result.backdrop_mask_written,
                 command_result.render_result.effect_count,
                 command_result.render_result.physical_width,
                 command_result.render_result.physical_height,
                 command_result.source_result.state,
                 command_result.source_result.status,
                 command_result.poll_iterations, command_result.elapsed_ms,
                 command_result.source_tick_ms, command_result.submit_ms,
                 command_result.poll_ms,
                 command_result.error_message
                     ? command_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    if (command_result.state ==
        BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING) {
      blink_standalone_dedicated_thread_gpu_frame_result_t cancel_result = {};
      blink_standalone_renderer_cancel_dedicated_thread_gpu_frame(
          renderer, command_id, &cancel_result);
    }
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  if (!ValidatePublicGpuBackdropEffectTable(
          renderer, command_result.render_result.effect_count,
          "vulkan_dedicated")) {
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  std::vector<uint32_t> pixels;
  if (!ReadbackVulkanImage(&context, kPhysicalWidth, kPhysicalHeight,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, &pixels,
                           &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }
  auto pixel_at = [&](uint32_t x, uint32_t y) {
    const uint32_t rgba =
        pixels[static_cast<size_t>(y) * kPhysicalWidth + x];
    return (rgba & 0xff000000u) | ((rgba & 0x000000ffu) << 16) |
           (rgba & 0x0000ff00u) | ((rgba & 0x00ff0000u) >> 16);
  };
  const uint32_t observed_background = pixel_at(8, 8);
  const uint32_t observed_box = pixel_at(40, 40);
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

  if (observed_background != kExpectedBackground || background_pixels == 0 ||
      box_pixels == 0 || nontransparent_pixels == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_pixels observed_background=%08x "
                 "observed_box=%08x background_pixels=%u box_pixels=%u "
                 "nontransparent=%u\n",
                 observed_background, observed_box, background_pixels,
                 box_pixels, nontransparent_pixels);
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  target.common.generation = 2;
  target.vulkan.current_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  mask_target.common.generation = 2;
  mask_target.vulkan.current_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  request.timeline_time_seconds = 0.032;
  request.source_request.request_generation = 2;
  request.source_request.timeline_time_seconds = request.timeline_time_seconds;
  request.render_request.request_generation = 2;
  request.render_request.main_target = target;
  request.render_request.backdrop_mask_target = mask_target;

  blink_standalone_dedicated_thread_gpu_frame_result_t mutation_result = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &request, &mutation_result);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_vulkan_dedicated_mutation status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }
  const uint64_t mutation_command_id = mutation_result.command_id;
  for (uint32_t poll = 0;
       mutation_result.state ==
               BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING &&
       poll < 10000;
       ++poll) {
    ::Sleep(1);
    status = blink_standalone_renderer_poll_dedicated_thread_gpu_frame(
        renderer, mutation_command_id, &mutation_result);
    if (status != BLINK_STANDALONE_STATUS_OK &&
        status != BLINK_STANDALONE_STATUS_PENDING) {
      break;
    }
  }
  if (status != BLINK_STANDALONE_STATUS_OK ||
      mutation_result.state !=
          BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED ||
      mutation_result.render_result.main_target_written == 0 ||
      mutation_result.render_result.backdrop_mask_written == 0 ||
      mutation_result.render_result.effect_count == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_mutation_frame status=%d result_status=%u "
                 "state=%u render_state=%u written=%u mask_written=%u "
                 "effects=%u error=%s\n",
                 status, mutation_result.status, mutation_result.state,
                 mutation_result.render_result.state,
                 mutation_result.render_result.main_target_written,
                 mutation_result.render_result.backdrop_mask_written,
                 mutation_result.render_result.effect_count,
                 mutation_result.error_message
                     ? mutation_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }
  if (!ValidatePublicGpuBackdropEffectTable(
          renderer, mutation_result.render_result.effect_count,
          "vulkan_dedicated_mutation")) {
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }
  std::vector<uint32_t> mutated_pixels;
  if (!ReadbackVulkanImage(&context, kPhysicalWidth, kPhysicalHeight,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                           &mutated_pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_mutation_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }
  uint32_t mutation_changed_pixels = 0;
  const uint32_t compare_left = 320;
  const uint32_t compare_top = 600;
  const uint32_t compare_right = 760;
  const uint32_t compare_bottom = 840;
  for (uint32_t y = compare_top; y < compare_bottom; ++y) {
    for (uint32_t x = compare_left; x < compare_right; ++x) {
      const size_t index = static_cast<size_t>(y) * kPhysicalWidth + x;
      if (pixels[index] != mutated_pixels[index]) {
        ++mutation_changed_pixels;
      }
    }
  }
  if (mutation_changed_pixels < 1000) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_dedicated_mutation_pixels changed=%u\n",
                 mutation_changed_pixels);
    DestroyRenderer(renderer);
    destroy_mask();
    DestroyVulkanProbeContext(&context);
    return false;
  }

  DestroyRenderer(renderer);
  destroy_mask();
  DestroyVulkanProbeContext(&context);

  std::printf(
      "static_gpu_external_target_smoke: ok vulkan_dedicated=1 "
      "main_written=1 mask_written=%u effects=%u mutation_changed=%u "
      "mutation_enqueue_ms=%.3f size=%ux%u command_id=%llu "
      "mutation_command_id=%llu polls=%u mutation_polls=%u elapsed_ms=%.3f "
      "source_ms=%.3f submit_ms=%.3f poll_ms=%.3f\n",
      command_result.render_result.backdrop_mask_written,
      command_result.render_result.effect_count, mutation_changed_pixels,
      mutation_ms,
      command_result.render_result.physical_width,
      command_result.render_result.physical_height,
      static_cast<unsigned long long>(command_id),
      static_cast<unsigned long long>(mutation_command_id),
      command_result.poll_iterations, mutation_result.poll_iterations,
      command_result.elapsed_ms,
      command_result.source_tick_ms, command_result.submit_ms,
      command_result.poll_ms);
  return true;
}

bool RunVulkanDedicatedThreadResizeCancelSmoke() {
  constexpr uint32_t kInitialLogicalWidth = 1280;
  constexpr uint32_t kInitialLogicalHeight = 720;
  constexpr uint32_t kInitialPhysicalWidth = 2560;
  constexpr uint32_t kInitialPhysicalHeight = 1440;
  constexpr uint32_t kResizedLogicalWidth = 1266;
  constexpr uint32_t kResizedLogicalHeight = 641;
  constexpr uint32_t kResizedPhysicalWidth = 2532;
  constexpr uint32_t kResizedPhysicalHeight = 1282;
  constexpr uint32_t kExpectedBackground = 0xff123456u;
  constexpr uint32_t kExpectedBox = 0xffd06329u;

  VulkanProbeContext context;
  std::string failure;
  if (!InitializeVulkanProbeContext(&context, kInitialPhysicalWidth,
                                    kInitialPhysicalHeight, &failure)) {
    std::printf("static_gpu_external_target_smoke: blocked "
                "vulkan_dedicated_resize_cancel=0 failure=%s\n",
                failure.c_str());
    return true;
  }

  auto destroy_image = [&](VkImage* image, VkDeviceMemory* memory) {
    if (context.device == VK_NULL_HANDLE) {
      return;
    }
    if (context.vk.DeviceWaitIdle) {
      context.vk.DeviceWaitIdle(context.device);
    }
    if (image && *image != VK_NULL_HANDLE) {
      context.vk.DestroyImage(context.device, *image, nullptr);
      *image = VK_NULL_HANDLE;
    }
    if (memory && *memory != VK_NULL_HANDLE) {
      context.vk.FreeMemory(context.device, *memory, nullptr);
      *memory = VK_NULL_HANDLE;
    }
  };

  VkImage initial_mask_image = VK_NULL_HANDLE;
  VkDeviceMemory initial_mask_memory = VK_NULL_HANDLE;
  VkDeviceSize initial_mask_allocation_size = 0;
  uint32_t initial_mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(
          &context, kInitialPhysicalWidth, kInitialPhysicalHeight,
          &initial_mask_image, &initial_mask_memory,
          &initial_mask_allocation_size, &initial_mask_memory_type_index,
          &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_initial_mask failure=%s\n",
                 failure.c_str());
    DestroyVulkanProbeContext(&context);
    return false;
  }

  blink_standalone_renderer_config_t config = {};
  config.width = static_cast<int>(kInitialLogicalWidth);
  config.height = static_cast<int>(kInitialLogicalHeight);
  config.device_scale_factor = 2.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create_dedicated_thread(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return Fail("vulkan resize create_dedicated_thread");
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
                 "static_gpu_external_target_smoke: failed "
                 "configure_vulkan_resize status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;width:100%;height:100%;"
      "background:#123456}#box{position:absolute;left:16px;top:12px;"
      "width:80px;height:32px;background:#d06329}#glass{position:absolute;"
      "left:120px;top:80px;width:360px;height:180px;border-radius:28px;"
      "background:rgba(255,255,255,.25);backdrop-filter:blur(12px) "
      "saturate(160%);-webkit-backdrop-filter:blur(12px) "
      "saturate(160%)}</style><div id='box'></div><div id='glass'></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "set_document_vulkan_resize status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  auto make_target = [&](uint32_t logical_width, uint32_t logical_height,
                         uint32_t physical_width, uint32_t physical_height,
                         uint64_t generation, VkImage image,
                         VkDeviceMemory memory, VkDeviceSize allocation_size,
                         uint32_t memory_type_index) {
    blink_standalone_external_gpu_target_t target = {};
    target.common.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
    target.common.logical_width = logical_width;
    target.common.logical_height = logical_height;
    target.common.physical_width = physical_width;
    target.common.physical_height = physical_height;
    target.common.device_scale_factor = 2.0f;
    target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
    target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
    target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
    target.common.generation = generation;
    target.vulkan.vk_image = image;
    target.vulkan.vk_device = context.device;
    target.vulkan.vk_physical_device = context.physical_device;
    target.vulkan.vk_device_memory = memory;
    target.vulkan.vk_format = VK_FORMAT_R8G8B8A8_UNORM;
    target.vulkan.width = physical_width;
    target.vulkan.height = physical_height;
    target.vulkan.current_layout = VK_IMAGE_LAYOUT_UNDEFINED;
    target.vulkan.required_final_layout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    target.vulkan.queue_family_index = context.queue_family_index;
    target.vulkan.allocation_size = allocation_size;
    target.vulkan.memory_type_index = memory_type_index;
    target.vulkan.image_tiling = VK_IMAGE_TILING_OPTIMAL;
    target.vulkan.image_usage_flags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                                      VK_IMAGE_USAGE_SAMPLED_BIT |
                                      VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                                      VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    target.vulkan.sample_count = VK_SAMPLE_COUNT_1_BIT;
    target.vulkan.level_count = 1;
    return target;
  };

  auto make_request = [](uint64_t generation, uint32_t logical_width,
                         uint32_t logical_height, uint32_t physical_width,
                         uint32_t physical_height, double timeline,
                         const blink_standalone_external_gpu_target_t& main,
                         const blink_standalone_external_gpu_target_t& mask) {
    blink_standalone_dedicated_thread_gpu_frame_request_t request = {};
    request.timeline_time_seconds = timeline;
    request.poll_interval_ms = 1;
    request.max_poll_iterations = 5000;
    request.source_request.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
    request.source_request.request_generation = generation;
    request.source_request.timeline_time_seconds = timeline;
    request.source_request.logical_width = logical_width;
    request.source_request.logical_height = logical_height;
    request.source_request.physical_width = physical_width;
    request.source_request.physical_height = physical_height;
    request.source_request.device_scale_factor = 2.0f;
    request.source_request.max_work_budget_ms = 1000.0;
    request.render_request.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
    request.render_request.request_generation = generation;
    request.render_request.flags =
        BLINK_STANDALONE_GPU_ASYNC_BACKDROP_MASK_REQUIRED;
    request.render_request.mask_encoding =
        BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_RGBA8_ID_COVERAGE;
    request.render_request.main_target = main;
    request.render_request.backdrop_mask_target = mask;
    return request;
  };

  auto wait_for_command =
      [&](const char* label, uint64_t command_id,
          blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
        blink_standalone_status_code_t wait_status =
            result->status == BLINK_STANDALONE_STATUS_PENDING
                ? BLINK_STANDALONE_STATUS_PENDING
                : static_cast<blink_standalone_status_code_t>(result->status);
        for (uint32_t poll = 0;
             result->state ==
                     BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING &&
             poll < 10000;
             ++poll) {
          ::Sleep(1);
          wait_status = blink_standalone_renderer_poll_dedicated_thread_gpu_frame(
              renderer, command_id, result);
          if (wait_status != BLINK_STANDALONE_STATUS_OK &&
              wait_status != BLINK_STANDALONE_STATUS_PENDING) {
            break;
          }
        }
        if (wait_status != BLINK_STANDALONE_STATUS_OK ||
            result->state !=
                BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED ||
            result->render_result.main_target_written == 0 ||
            result->render_result.backdrop_mask_written == 0 ||
            result->render_result.effect_count == 0) {
          std::fprintf(stderr,
                       "static_gpu_external_target_smoke: failed %s "
                       "status=%d result_status=%u state=%u render_state=%u "
                       "written=%u mask_written=%u effects=%u size=%ux%u "
                       "source_state=%u source_status=%u polls=%u "
                       "elapsed_ms=%.3f source_ms=%.3f submit_ms=%.3f "
                       "poll_ms=%.3f error=%s\n",
                       label, wait_status, result->status, result->state,
                       result->render_result.state,
                       result->render_result.main_target_written,
                       result->render_result.backdrop_mask_written,
                       result->render_result.effect_count,
                       result->render_result.physical_width,
                       result->render_result.physical_height,
                       result->source_result.state, result->source_result.status,
                       result->poll_iterations, result->elapsed_ms,
                       result->source_tick_ms, result->submit_ms,
                       result->poll_ms,
                       result->error_message
                           ? result->error_message
                           : blink_standalone_renderer_last_error(renderer));
          if (result->state ==
              BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING) {
            blink_standalone_dedicated_thread_gpu_frame_result_t cancel = {};
            blink_standalone_renderer_cancel_dedicated_thread_gpu_frame(
                renderer, command_id, &cancel);
          }
          return false;
        }
        return true;
      };

  blink_standalone_external_gpu_target_t initial_main = make_target(
      kInitialLogicalWidth, kInitialLogicalHeight, kInitialPhysicalWidth,
      kInitialPhysicalHeight, 1, context.image, context.image_memory,
      context.image_allocation_size, context.image_memory_type_index);
  blink_standalone_external_gpu_target_t initial_mask = make_target(
      kInitialLogicalWidth, kInitialLogicalHeight, kInitialPhysicalWidth,
      kInitialPhysicalHeight, 1, initial_mask_image, initial_mask_memory,
      initial_mask_allocation_size, initial_mask_memory_type_index);
  blink_standalone_dedicated_thread_gpu_frame_request_t initial_request =
      make_request(1, kInitialLogicalWidth, kInitialLogicalHeight,
                   kInitialPhysicalWidth, kInitialPhysicalHeight, 0.016,
                   initial_main, initial_mask);
  blink_standalone_dedicated_thread_gpu_frame_result_t initial_result = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &initial_request, &initial_result);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_vulkan_resize_initial status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  if (!wait_for_command("vulkan_resize_initial",
                        initial_result.command_id, &initial_result)) {
    DestroyRenderer(renderer);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  status = blink_standalone_renderer_set_viewport(
      renderer, static_cast<int>(kResizedLogicalWidth),
      static_cast<int>(kResizedLogicalHeight), 2.0f);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "set_viewport_vulkan_resize status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  VkImage cancel_main_image = VK_NULL_HANDLE;
  VkDeviceMemory cancel_main_memory = VK_NULL_HANDLE;
  VkDeviceSize cancel_main_allocation_size = 0;
  uint32_t cancel_main_memory_type_index = 0;
  VkImage cancel_mask_image = VK_NULL_HANDLE;
  VkDeviceMemory cancel_mask_memory = VK_NULL_HANDLE;
  VkDeviceSize cancel_mask_allocation_size = 0;
  uint32_t cancel_mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(&context, kResizedPhysicalWidth,
                              kResizedPhysicalHeight, &cancel_main_image,
                              &cancel_main_memory,
                              &cancel_main_allocation_size,
                              &cancel_main_memory_type_index, &failure) ||
      !CreateVulkanProbeImage(&context, kResizedPhysicalWidth,
                              kResizedPhysicalHeight, &cancel_mask_image,
                              &cancel_mask_memory,
                              &cancel_mask_allocation_size,
                              &cancel_mask_memory_type_index, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_cancel_images failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_image(&cancel_mask_image, &cancel_mask_memory);
    destroy_image(&cancel_main_image, &cancel_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  blink_standalone_external_gpu_target_t cancel_main = make_target(
      kResizedLogicalWidth, kResizedLogicalHeight, kResizedPhysicalWidth,
      kResizedPhysicalHeight, 2, cancel_main_image, cancel_main_memory,
      cancel_main_allocation_size, cancel_main_memory_type_index);
  blink_standalone_external_gpu_target_t cancel_mask = make_target(
      kResizedLogicalWidth, kResizedLogicalHeight, kResizedPhysicalWidth,
      kResizedPhysicalHeight, 2, cancel_mask_image, cancel_mask_memory,
      cancel_mask_allocation_size, cancel_mask_memory_type_index);
  blink_standalone_dedicated_thread_gpu_frame_request_t cancel_request =
      make_request(2, kResizedLogicalWidth, kResizedLogicalHeight,
                   kResizedPhysicalWidth, kResizedPhysicalHeight, 0.032,
                   cancel_main, cancel_mask);
  blink_standalone_dedicated_thread_gpu_frame_result_t cancel_post = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &cancel_request, &cancel_post);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_vulkan_resize_cancel status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&cancel_mask_image, &cancel_mask_memory);
    destroy_image(&cancel_main_image, &cancel_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  blink_standalone_dedicated_thread_gpu_frame_result_t cancel_result = {};
  status = blink_standalone_renderer_cancel_dedicated_thread_gpu_frame(
      renderer, cancel_post.command_id, &cancel_result);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      (cancel_result.state != BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_CANCELLED &&
       cancel_result.state != BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_cancel_result status=%d state=%u "
                 "render_state=%u size=%ux%u error=%s\n",
                 status, cancel_result.state,
                 cancel_result.render_result.state,
                 cancel_result.render_result.physical_width,
                 cancel_result.render_result.physical_height,
                 cancel_result.error_message
                     ? cancel_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&cancel_mask_image, &cancel_mask_memory);
    destroy_image(&cancel_main_image, &cancel_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  if (cancel_result.state == BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED &&
      (cancel_result.render_result.physical_width == 0 ||
       cancel_result.render_result.physical_height == 0)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_cancel_zero_size_trap size=%ux%u\n",
                 cancel_result.render_result.physical_width,
                 cancel_result.render_result.physical_height);
    DestroyRenderer(renderer);
    destroy_image(&cancel_mask_image, &cancel_mask_memory);
    destroy_image(&cancel_main_image, &cancel_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  destroy_image(&cancel_mask_image, &cancel_mask_memory);
  destroy_image(&cancel_main_image, &cancel_main_memory);

  VkImage final_main_image = VK_NULL_HANDLE;
  VkDeviceMemory final_main_memory = VK_NULL_HANDLE;
  VkDeviceSize final_main_allocation_size = 0;
  uint32_t final_main_memory_type_index = 0;
  VkImage final_mask_image = VK_NULL_HANDLE;
  VkDeviceMemory final_mask_memory = VK_NULL_HANDLE;
  VkDeviceSize final_mask_allocation_size = 0;
  uint32_t final_mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(&context, kResizedPhysicalWidth,
                              kResizedPhysicalHeight, &final_main_image,
                              &final_main_memory,
                              &final_main_allocation_size,
                              &final_main_memory_type_index, &failure) ||
      !CreateVulkanProbeImage(&context, kResizedPhysicalWidth,
                              kResizedPhysicalHeight, &final_mask_image,
                              &final_mask_memory,
                              &final_mask_allocation_size,
                              &final_mask_memory_type_index, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_final_images failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  blink_standalone_external_gpu_target_t final_main = make_target(
      kResizedLogicalWidth, kResizedLogicalHeight, kResizedPhysicalWidth,
      kResizedPhysicalHeight, 3, final_main_image, final_main_memory,
      final_main_allocation_size, final_main_memory_type_index);
  blink_standalone_external_gpu_target_t final_mask = make_target(
      kResizedLogicalWidth, kResizedLogicalHeight, kResizedPhysicalWidth,
      kResizedPhysicalHeight, 3, final_mask_image, final_mask_memory,
      final_mask_allocation_size, final_mask_memory_type_index);
  blink_standalone_dedicated_thread_gpu_frame_request_t final_request =
      make_request(3, kResizedLogicalWidth, kResizedLogicalHeight,
                   kResizedPhysicalWidth, kResizedPhysicalHeight, 0.048,
                   final_main, final_mask);
  blink_standalone_dedicated_thread_gpu_frame_result_t final_result = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &final_request, &final_result);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_vulkan_resize_final status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  if (!wait_for_command("vulkan_resize_final", final_result.command_id,
                        &final_result) ||
      final_result.render_result.physical_width != kResizedPhysicalWidth ||
      final_result.render_result.physical_height != kResizedPhysicalHeight) {
    if (final_result.render_result.physical_width == 0 ||
        final_result.render_result.physical_height == 0) {
      std::fprintf(stderr,
                   "static_gpu_external_target_smoke: failed "
                   "vulkan_resize_final_zero_size_trap size=%ux%u\n",
                   final_result.render_result.physical_width,
                   final_result.render_result.physical_height);
    }
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  if (!ValidatePublicGpuBackdropEffectTable(
          renderer, final_result.render_result.effect_count,
          "vulkan_dedicated_resize_cancel")) {
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  std::vector<uint32_t> pixels;
  if (!ReadbackVulkanImageHandle(
          &context, final_main_image, kResizedPhysicalWidth,
          kResizedPhysicalHeight, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
          &pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_final_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&initial_mask_image, &initial_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  auto pixel_at = [&](uint32_t x, uint32_t y) {
    const uint32_t rgba =
        pixels[static_cast<size_t>(y) * kResizedPhysicalWidth + x];
    return (rgba & 0xff000000u) | ((rgba & 0x000000ffu) << 16) |
           (rgba & 0x0000ff00u) | ((rgba & 0x00ff0000u) >> 16);
  };
  const uint32_t observed_background = pixel_at(8, 8);
  const uint32_t observed_box = pixel_at(40, 40);
  uint32_t background_pixels = 0;
  uint32_t box_pixels = 0;
  for (uint32_t rgba : pixels) {
    const uint32_t pixel = (rgba & 0xff000000u) |
                           ((rgba & 0x000000ffu) << 16) |
                           (rgba & 0x0000ff00u) |
                           ((rgba & 0x00ff0000u) >> 16);
    if (pixel == kExpectedBackground) {
      ++background_pixels;
    }
    if (pixel == kExpectedBox) {
      ++box_pixels;
    }
  }

  DestroyRenderer(renderer);
  destroy_image(&final_mask_image, &final_mask_memory);
  destroy_image(&final_main_image, &final_main_memory);
  destroy_image(&initial_mask_image, &initial_mask_memory);
  DestroyVulkanProbeContext(&context);

  if (observed_background != kExpectedBackground ||
      observed_box != kExpectedBox || background_pixels == 0 ||
      box_pixels == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_final_pixels observed_background=%08x "
                 "observed_box=%08x background_pixels=%u box_pixels=%u\n",
                 observed_background, observed_box, background_pixels,
                 box_pixels);
    return false;
  }

  std::printf(
      "static_gpu_external_target_smoke: ok "
      "vulkan_dedicated_resize_cancel=1 initial_written=%u final_written=%u "
      "final_mask_written=%u effects=%u initial_size=%ux%u final_size=%ux%u "
      "cancel_state=%u final_command_id=%llu final_polls=%u "
      "final_elapsed_ms=%.3f\n",
      initial_result.render_result.main_target_written,
      final_result.render_result.main_target_written,
      final_result.render_result.backdrop_mask_written,
      final_result.render_result.effect_count,
      initial_result.render_result.physical_width,
      initial_result.render_result.physical_height,
      final_result.render_result.physical_width,
      final_result.render_result.physical_height, cancel_result.state,
      static_cast<unsigned long long>(final_result.command_id),
      final_result.poll_iterations, final_result.elapsed_ms);
  return true;
}

bool RunVulkanResizeReturnSmoke() {
  constexpr uint32_t kLargeWidth = 2560;
  constexpr uint32_t kLargeHeight = 1440;
  constexpr uint32_t kSmallWidth = 1280;
  constexpr uint32_t kSmallHeight = 720;
  constexpr uint32_t kExpectedBackground = 0xff123456u;
  constexpr uint32_t kExpectedBox = 0xffd06329u;

  VulkanProbeContext context;
  std::string failure;
  if (!InitializeVulkanProbeContext(&context, kLargeWidth, kLargeHeight,
                                    &failure)) {
    std::printf("static_gpu_external_target_smoke: blocked "
                "vulkan_resize_return=0 failure=%s\n",
                failure.c_str());
    return true;
  }

  auto destroy_image = [&](VkImage* image, VkDeviceMemory* memory) {
    if (context.device == VK_NULL_HANDLE) {
      return;
    }
    if (context.vk.DeviceWaitIdle) {
      context.vk.DeviceWaitIdle(context.device);
    }
    if (image && *image != VK_NULL_HANDLE) {
      context.vk.DestroyImage(context.device, *image, nullptr);
      *image = VK_NULL_HANDLE;
    }
    if (memory && *memory != VK_NULL_HANDLE) {
      context.vk.FreeMemory(context.device, *memory, nullptr);
      *memory = VK_NULL_HANDLE;
    }
  };

  blink_standalone_renderer_config_t config = {};
  config.width = static_cast<int>(kLargeWidth);
  config.height = static_cast<int>(kLargeHeight);
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    DestroyVulkanProbeContext(&context);
    return Fail("vulkan resize_return create");
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
                 "static_gpu_external_target_smoke: failed "
                 "configure_vulkan_resize_return status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;width:100%;height:100%;"
      "background:#123456}#box{position:absolute;left:16px;top:12px;"
      "width:80px;height:32px;background:#d06329}#glass{position:absolute;"
      "left:120px;top:80px;width:360px;height:180px;border-radius:28px;"
      "background:rgba(255,255,255,.25);backdrop-filter:blur(12px) "
      "saturate(160%);-webkit-backdrop-filter:blur(12px) "
      "saturate(160%)}</style><div id='box'></div><div id='glass'></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "set_document_vulkan_resize_return status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  auto make_target = [&](uint32_t width, uint32_t height, uint64_t generation,
                         VkImage image, VkDeviceMemory memory,
                         VkDeviceSize allocation_size,
                         uint32_t memory_type_index) {
    blink_standalone_external_gpu_target_t target = {};
    target.common.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
    target.common.logical_width = width;
    target.common.logical_height = height;
    target.common.physical_width = width;
    target.common.physical_height = height;
    target.common.device_scale_factor = 1.0f;
    target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
    target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
    target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
    target.common.generation = generation;
    target.vulkan.vk_image = image;
    target.vulkan.vk_device = context.device;
    target.vulkan.vk_physical_device = context.physical_device;
    target.vulkan.vk_device_memory = memory;
    target.vulkan.vk_format = VK_FORMAT_R8G8B8A8_UNORM;
    target.vulkan.width = width;
    target.vulkan.height = height;
    target.vulkan.current_layout = VK_IMAGE_LAYOUT_UNDEFINED;
    target.vulkan.required_final_layout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    target.vulkan.queue_family_index = context.queue_family_index;
    target.vulkan.allocation_size = allocation_size;
    target.vulkan.memory_type_index = memory_type_index;
    target.vulkan.image_tiling = VK_IMAGE_TILING_OPTIMAL;
    target.vulkan.image_usage_flags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                                      VK_IMAGE_USAGE_SAMPLED_BIT |
                                      VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                                      VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    target.vulkan.sample_count = VK_SAMPLE_COUNT_1_BIT;
    target.vulkan.level_count = 1;
    return target;
  };

  uint32_t pending_count = 0;
  auto render_size = [&](const char* label, uint32_t width, uint32_t height,
                         uint64_t generation, VkImage main_image,
                         VkDeviceMemory main_memory,
                         VkDeviceSize main_allocation_size,
                         uint32_t main_memory_type_index, VkImage mask_image,
                         VkDeviceMemory mask_memory,
                         VkDeviceSize mask_allocation_size,
                         uint32_t mask_memory_type_index,
                         blink_standalone_gpu_backdrop_render_result* result) {
    blink_standalone_status_code_t viewport_status =
        blink_standalone_renderer_set_viewport(
            renderer, static_cast<int>(width), static_cast<int>(height), 1.0f);
    if (viewport_status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "static_gpu_external_target_smoke: failed %s_viewport "
                   "status=%d error=%s\n",
                   label, viewport_status,
                   blink_standalone_renderer_last_error(renderer));
      return false;
    }
    blink_standalone_external_gpu_target_t main_target = make_target(
        width, height, generation, main_image, main_memory,
        main_allocation_size, main_memory_type_index);
    blink_standalone_external_gpu_target_t mask_target = make_target(
        width, height, generation, mask_image, mask_memory,
        mask_allocation_size, mask_memory_type_index);
    for (uint32_t retry = 0; retry < 64; ++retry) {
      blink_standalone_gpu_backdrop_render_request_t request = {};
      request.backend = BLINK_STANDALONE_GPU_BACKEND_VULKAN;
      request.flags = BLINK_STANDALONE_GPU_ASYNC_BACKDROP_MASK_REQUIRED;
      request.mask_encoding =
          BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_RGBA8_ID_COVERAGE;
      main_target.common.generation = generation + retry;
      mask_target.common.generation = generation + retry;
      request.main_target = main_target;
      request.backdrop_mask_target = mask_target;
      *result = blink_standalone_gpu_backdrop_render_result_t{};
      blink_standalone_status_code_t render_status =
          blink_standalone_renderer_render_gpu_backdrop_frame(renderer,
                                                              &request, result);
      if (render_status == BLINK_STANDALONE_STATUS_PENDING) {
        ++pending_count;
        blink_standalone_update_result_t update = {};
        blink_standalone_renderer_update(
            renderer, 0.016 * static_cast<double>(generation + retry + 1),
            &update);
        continue;
      }
      if (render_status != BLINK_STANDALONE_STATUS_OK ||
          result->main_target_written == 0 ||
          result->backdrop_mask_written == 0 || result->effect_count == 0 ||
          result->physical_width != width || result->physical_height != height) {
        std::fprintf(stderr,
                     "static_gpu_external_target_smoke: failed %s_render "
                     "status=%d result_status=%u main=%u mask=%u effects=%u "
                     "size=%ux%u pending_count=%u error=%s\n",
                     label, render_status, result->status,
                     result->main_target_written, result->backdrop_mask_written,
                     result->effect_count, result->physical_width,
                     result->physical_height, pending_count,
                     blink_standalone_renderer_last_error(renderer));
        return false;
      }
      return true;
    }
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed %s_render "
                 "exhausted pending retries error=%s\n",
                 label, blink_standalone_renderer_last_error(renderer));
    return false;
  };

  VkImage large_mask_image = VK_NULL_HANDLE;
  VkDeviceMemory large_mask_memory = VK_NULL_HANDLE;
  VkDeviceSize large_mask_allocation_size = 0;
  uint32_t large_mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(&context, kLargeWidth, kLargeHeight,
                              &large_mask_image, &large_mask_memory,
                              &large_mask_allocation_size,
                              &large_mask_memory_type_index, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_return_large_mask failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  blink_standalone_gpu_backdrop_render_result initial_result = {};
  if (!render_size("vulkan_resize_return_initial", kLargeWidth, kLargeHeight, 1,
                   context.image, context.image_memory,
                   context.image_allocation_size,
                   context.image_memory_type_index, large_mask_image,
                   large_mask_memory, large_mask_allocation_size,
                   large_mask_memory_type_index, &initial_result)) {
    DestroyRenderer(renderer);
    destroy_image(&large_mask_image, &large_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  VkImage small_main_image = VK_NULL_HANDLE;
  VkDeviceMemory small_main_memory = VK_NULL_HANDLE;
  VkDeviceSize small_main_allocation_size = 0;
  uint32_t small_main_memory_type_index = 0;
  VkImage small_mask_image = VK_NULL_HANDLE;
  VkDeviceMemory small_mask_memory = VK_NULL_HANDLE;
  VkDeviceSize small_mask_allocation_size = 0;
  uint32_t small_mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(&context, kSmallWidth, kSmallHeight,
                              &small_main_image, &small_main_memory,
                              &small_main_allocation_size,
                              &small_main_memory_type_index, &failure) ||
      !CreateVulkanProbeImage(&context, kSmallWidth, kSmallHeight,
                              &small_mask_image, &small_mask_memory,
                              &small_mask_allocation_size,
                              &small_mask_memory_type_index, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_return_small_images failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_image(&small_mask_image, &small_mask_memory);
    destroy_image(&small_main_image, &small_main_memory);
    destroy_image(&large_mask_image, &large_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  blink_standalone_gpu_backdrop_render_result small_result = {};
  if (!render_size("vulkan_resize_return_small", kSmallWidth, kSmallHeight, 100,
                   small_main_image, small_main_memory,
                   small_main_allocation_size, small_main_memory_type_index,
                   small_mask_image, small_mask_memory,
                   small_mask_allocation_size, small_mask_memory_type_index,
                   &small_result)) {
    DestroyRenderer(renderer);
    destroy_image(&small_mask_image, &small_mask_memory);
    destroy_image(&small_main_image, &small_main_memory);
    destroy_image(&large_mask_image, &large_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  destroy_image(&small_mask_image, &small_mask_memory);
  destroy_image(&small_main_image, &small_main_memory);

  VkImage final_main_image = VK_NULL_HANDLE;
  VkDeviceMemory final_main_memory = VK_NULL_HANDLE;
  VkDeviceSize final_main_allocation_size = 0;
  uint32_t final_main_memory_type_index = 0;
  VkImage final_mask_image = VK_NULL_HANDLE;
  VkDeviceMemory final_mask_memory = VK_NULL_HANDLE;
  VkDeviceSize final_mask_allocation_size = 0;
  uint32_t final_mask_memory_type_index = 0;
  if (!CreateVulkanProbeImage(&context, kLargeWidth, kLargeHeight,
                              &final_main_image, &final_main_memory,
                              &final_main_allocation_size,
                              &final_main_memory_type_index, &failure) ||
      !CreateVulkanProbeImage(&context, kLargeWidth, kLargeHeight,
                              &final_mask_image, &final_mask_memory,
                              &final_mask_allocation_size,
                              &final_mask_memory_type_index, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_return_final_images failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&large_mask_image, &large_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  blink_standalone_gpu_backdrop_render_result final_result = {};
  if (!render_size("vulkan_resize_return_final", kLargeWidth, kLargeHeight, 200,
                   final_main_image, final_main_memory,
                   final_main_allocation_size, final_main_memory_type_index,
                   final_mask_image, final_mask_memory,
                   final_mask_allocation_size, final_mask_memory_type_index,
                   &final_result)) {
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&large_mask_image, &large_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }

  std::vector<uint32_t> pixels;
  if (!ReadbackVulkanImageHandle(
          &context, final_main_image, kLargeWidth, kLargeHeight,
          VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, &pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_return_final_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    destroy_image(&final_mask_image, &final_mask_memory);
    destroy_image(&final_main_image, &final_main_memory);
    destroy_image(&large_mask_image, &large_mask_memory);
    DestroyVulkanProbeContext(&context);
    return false;
  }
  auto pixel_at = [&](uint32_t x, uint32_t y) {
    const uint32_t rgba = pixels[static_cast<size_t>(y) * kLargeWidth + x];
    return (rgba & 0xff000000u) | ((rgba & 0x000000ffu) << 16) |
           (rgba & 0x0000ff00u) | ((rgba & 0x00ff0000u) >> 16);
  };
  const uint32_t observed_background = pixel_at(8, 8);
  const uint32_t observed_box = pixel_at(40, 40);

  DestroyRenderer(renderer);
  destroy_image(&final_mask_image, &final_mask_memory);
  destroy_image(&final_main_image, &final_main_memory);
  destroy_image(&large_mask_image, &large_mask_memory);
  DestroyVulkanProbeContext(&context);

  if (observed_background != kExpectedBackground ||
      observed_box != kExpectedBox) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "vulkan_resize_return_pixels observed_background=%08x "
                 "observed_box=%08x\n",
                 observed_background, observed_box);
    return false;
  }

  std::printf(
      "static_gpu_external_target_smoke: ok vulkan_resize_return=1 "
      "initial=%ux%u small=%ux%u final=%ux%u effects=%u pending_count=%u "
      "observed_background=%08x observed_box=%08x\n",
      initial_result.physical_width, initial_result.physical_height,
      small_result.physical_width, small_result.physical_height,
      final_result.physical_width, final_result.physical_height,
      final_result.effect_count, pending_count, observed_background,
      observed_box);
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

bool RunD3D12DedicatedThreadFirstPublishSmoke() {
  constexpr uint32_t kLogicalWidth = 1280;
  constexpr uint32_t kLogicalHeight = 720;
  constexpr uint32_t kPhysicalWidth = 2560;
  constexpr uint32_t kPhysicalHeight = 1440;
  constexpr uint32_t kExpectedBackground = 0xff123456u;
  constexpr uint32_t kExpectedBox = 0xffd06329u;

  Microsoft::WRL::ComPtr<ID3D12Device> device;
  HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0,
                                 IID_PPV_ARGS(&device));
  if (FAILED(hr) || !device) {
    std::printf(
        "static_gpu_external_target_smoke: blocked d3d12_dedicated=0 "
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
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_queue hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  D3D12_HEAP_PROPERTIES heap_properties = {};
  heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
  heap_properties.CreationNodeMask = 1;
  heap_properties.VisibleNodeMask = 1;
  D3D12_RESOURCE_DESC resource_desc = {};
  resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Width = kPhysicalWidth;
  resource_desc.Height = kPhysicalHeight;
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
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_target hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  Microsoft::WRL::ComPtr<ID3D12Resource> mask_resource;
  hr = device->CreateCommittedResource(
      &heap_properties, D3D12_HEAP_FLAG_SHARED, &resource_desc,
      D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&mask_resource));
  if (FAILED(hr) || !mask_resource) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mask_target hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  HANDLE shared_handle = nullptr;
  hr = device->CreateSharedHandle(target_resource.Get(), nullptr, GENERIC_ALL,
                                  nullptr, &shared_handle);
  if (FAILED(hr) || !shared_handle) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_shared_handle hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    return false;
  }

  HANDLE mask_shared_handle = nullptr;
  hr = device->CreateSharedHandle(mask_resource.Get(), nullptr, GENERIC_ALL,
                                  nullptr, &mask_shared_handle);
  if (FAILED(hr) || !mask_shared_handle) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mask_shared_handle hr=0x%08lx\n",
                 static_cast<unsigned long>(hr));
    ::CloseHandle(shared_handle);
    return false;
  }

  blink_standalone_renderer_config_t config = {};
  config.width = static_cast<int>(kLogicalWidth);
  config.height = static_cast<int>(kLogicalHeight);
  config.device_scale_factor = 2.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create_dedicated_thread(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return Fail("create_dedicated_thread");
  }

  blink_standalone_d3d12_external_device_t external_device = {};
  external_device.d3d12_device = device.Get();
  external_device.d3d12_command_queue = queue.Get();
  status = blink_standalone_renderer_configure_d3d12_external_device(
      renderer, &external_device);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "configure_d3d12_dedicated status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;width:100%;height:100%;"
      "background:linear-gradient(90deg,#123456,#2878d8)}#box{position:"
      "absolute;left:16px;top:12px;width:80px;height:32px;background:#d06329}"
      "#glass{position:absolute;left:120px;top:80px;width:360px;height:180px;"
      "border-radius:28px;background:rgba(255,255,255,.25);"
      "backdrop-filter:blur(12px) saturate(160%);"
      "-webkit-backdrop-filter:blur(12px) saturate(160%)}#dynamic{position:"
      "absolute;left:160px;top:300px;width:220px;height:120px;background:"
      "#1b5e20}#label{position:"
      "absolute;left:120px;top:300px;color:white;font:700 160px Arial,"
      "sans-serif;line-height:1}</style><div id='box'></div>"
      "<style id='live_style'>#dynamic{background:#1b5e20}</style>"
      "<div id='glass'></div><div id='dynamic'></div>"
      "<div id='label'>IIIIIIIIII</div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "set_document_dedicated status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(
          renderer, BLINK_STANDALONE_GPU_BACKEND_D3D12);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0 ||
      (capabilities & BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET) == 0) {
    std::printf(
        "static_gpu_external_target_smoke: blocked d3d12_dedicated=0 "
        "capabilities=%u\n",
        capabilities);
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return true;
  }

  blink_standalone_external_gpu_target_t target = {};
  target.common.backend = BLINK_STANDALONE_GPU_BACKEND_D3D12;
  target.common.logical_width = kLogicalWidth;
  target.common.logical_height = kLogicalHeight;
  target.common.physical_width = kPhysicalWidth;
  target.common.physical_height = kPhysicalHeight;
  target.common.device_scale_factor = 2.0f;
  target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
  target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
  target.common.generation = 1;
  target.d3d12.d3d12_device = device.Get();
  target.d3d12.d3d12_command_queue = queue.Get();
  target.d3d12.d3d12_resource = target_resource.Get();
  target.d3d12.shared_handle = shared_handle;
  target.d3d12.dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;
  target.d3d12.width = kPhysicalWidth;
  target.d3d12.height = kPhysicalHeight;
  target.d3d12.current_state = D3D12_RESOURCE_STATE_COMMON;
  target.d3d12.required_final_state =
      D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

  blink_standalone_external_gpu_target_t mask_target = {};
  mask_target.common.backend = BLINK_STANDALONE_GPU_BACKEND_D3D12;
  mask_target.common.logical_width = kLogicalWidth;
  mask_target.common.logical_height = kLogicalHeight;
  mask_target.common.physical_width = kPhysicalWidth;
  mask_target.common.physical_height = kPhysicalHeight;
  mask_target.common.device_scale_factor = 2.0f;
  mask_target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  mask_target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
  mask_target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
  mask_target.common.generation = 1;
  mask_target.d3d12.d3d12_device = device.Get();
  mask_target.d3d12.d3d12_command_queue = queue.Get();
  mask_target.d3d12.d3d12_resource = mask_resource.Get();
  mask_target.d3d12.shared_handle = mask_shared_handle;
  mask_target.d3d12.dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;
  mask_target.d3d12.width = kPhysicalWidth;
  mask_target.d3d12.height = kPhysicalHeight;
  mask_target.d3d12.current_state = D3D12_RESOURCE_STATE_COMMON;
  mask_target.d3d12.required_final_state =
      D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

  blink_standalone_dedicated_thread_gpu_frame_request_t request = {};
  request.timeline_time_seconds = 0.016;
  request.poll_interval_ms = 1;
  request.max_poll_iterations = 5000;
  request.source_request.backend = BLINK_STANDALONE_GPU_BACKEND_D3D12;
  request.source_request.request_generation = 1;
  request.source_request.timeline_time_seconds = request.timeline_time_seconds;
  request.source_request.logical_width = kLogicalWidth;
  request.source_request.logical_height = kLogicalHeight;
  request.source_request.physical_width = kPhysicalWidth;
  request.source_request.physical_height = kPhysicalHeight;
  request.source_request.device_scale_factor = 2.0f;
  request.source_request.max_work_budget_ms = 1000.0;
  request.render_request.backend = BLINK_STANDALONE_GPU_BACKEND_D3D12;
  request.render_request.request_generation = 1;
  request.render_request.flags =
      BLINK_STANDALONE_GPU_ASYNC_BACKDROP_MASK_REQUIRED;
  request.render_request.mask_encoding =
      BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_RGBA8_ID_COVERAGE;
  request.render_request.main_target = target;
  request.render_request.backdrop_mask_target = mask_target;

  blink_standalone_dedicated_thread_gpu_frame_result_t command_result = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &request, &command_result);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_d3d12_dedicated status=%d result_status=%u "
                 "state=%u error=%s\n",
                 status, command_result.status, command_result.state,
                 command_result.error_message
                     ? command_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  const uint64_t command_id = command_result.command_id;
  const auto mutation_start = std::chrono::steady_clock::now();
  status = blink_standalone_renderer_set_element_text(
      renderer, "live_style", "#dynamic{background:#ff00ff}");
  const auto mutation_end = std::chrono::steady_clock::now();
  const double mutation_ms =
      std::chrono::duration<double, std::milli>(mutation_end - mutation_start)
          .count();
  if (status != BLINK_STANDALONE_STATUS_OK || mutation_ms > 10.0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mutation_enqueue status=%d elapsed_ms=%.3f "
                 "error=%s\n",
                 status, mutation_ms,
                 blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  for (uint32_t poll = 0;
       command_result.state ==
               BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING &&
       poll < 10000;
       ++poll) {
    ::Sleep(1);
    status = blink_standalone_renderer_poll_dedicated_thread_gpu_frame(
        renderer, command_id, &command_result);
    if (status != BLINK_STANDALONE_STATUS_OK &&
        status != BLINK_STANDALONE_STATUS_PENDING) {
      break;
    }
  }

  if (status != BLINK_STANDALONE_STATUS_OK ||
      command_result.state !=
          BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED ||
      command_result.render_result.main_target_written == 0 ||
      command_result.render_result.physical_width != kPhysicalWidth ||
      command_result.render_result.physical_height != kPhysicalHeight) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_first_publish status=%d result_status=%u "
                 "state=%u render_state=%u written=%u size=%ux%u "
                 "mask_written=%u effects=%u "
                 "source_state=%u source_status=%u poll_iterations=%u "
                 "elapsed_ms=%.3f source_ms=%.3f submit_ms=%.3f "
                 "poll_ms=%.3f error=%s\n",
                 status, command_result.status, command_result.state,
                 command_result.render_result.state,
                 command_result.render_result.main_target_written,
                 command_result.render_result.physical_width,
                 command_result.render_result.physical_height,
                 command_result.render_result.backdrop_mask_written,
                 command_result.render_result.effect_count,
                 command_result.source_result.state,
                 command_result.source_result.status,
                 command_result.poll_iterations, command_result.elapsed_ms,
                 command_result.source_tick_ms, command_result.submit_ms,
                 command_result.poll_ms,
                 command_result.error_message
                     ? command_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    if (command_result.state ==
        BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING) {
      blink_standalone_dedicated_thread_gpu_frame_result_t cancel_result = {};
      blink_standalone_renderer_cancel_dedicated_thread_gpu_frame(
          renderer, command_id, &cancel_result);
    }
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  if (command_result.render_result.backdrop_mask_written == 0 ||
      command_result.render_result.effect_count == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_backdrop_publish mask_written=%u "
                 "effects=%u state=%u render_state=%u error=%s\n",
                 command_result.render_result.backdrop_mask_written,
                 command_result.render_result.effect_count,
                 command_result.state, command_result.render_result.state,
                 command_result.error_message
                     ? command_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }
  if (!ValidatePublicGpuBackdropEffectTable(
          renderer, command_result.render_result.effect_count,
          "d3d12_dedicated")) {
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  std::vector<uint32_t> pixels;
  std::string failure;
  if (!ReadbackD3D12Texture(
          device.Get(), queue.Get(), target_resource.Get(), kPhysicalWidth,
          kPhysicalHeight,
          static_cast<D3D12_RESOURCE_STATES>(target.d3d12.required_final_state),
          &pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  std::vector<uint32_t> mask_pixels;
  if (!ReadbackD3D12Texture(
          device.Get(), queue.Get(), mask_resource.Get(), kPhysicalWidth,
          kPhysicalHeight,
          static_cast<D3D12_RESOURCE_STATES>(
              mask_target.d3d12.required_final_state),
          &mask_pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mask_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }
  uint32_t mask_pixels_written = 0;
  for (uint32_t pixel : mask_pixels) {
    if ((pixel & 0x00ffff00u) != 0) {
      ++mask_pixels_written;
    }
  }

  const uint32_t observed_background = pixels[8 * kPhysicalWidth + 8];
  const uint32_t observed_box = pixels[40 * kPhysicalWidth + 40];
  if (observed_background != kExpectedBackground ||
      observed_box != kExpectedBox) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_pixels observed_background=%08x "
                 "observed_box=%08x\n",
                 observed_background, observed_box);
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }
  if (mask_pixels_written == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mask_empty\n");
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  target.common.generation = 2;
  target.d3d12.current_state = D3D12_RESOURCE_STATE_COPY_SOURCE;
  mask_target.common.generation = 2;
  mask_target.d3d12.current_state = D3D12_RESOURCE_STATE_COPY_SOURCE;
  request.timeline_time_seconds = 0.032;
  request.source_request.request_generation = 2;
  request.source_request.timeline_time_seconds = request.timeline_time_seconds;
  request.render_request.request_generation = 2;
  request.render_request.main_target = target;
  request.render_request.backdrop_mask_target = mask_target;

  blink_standalone_dedicated_thread_gpu_frame_result_t mutation_result = {};
  status = blink_standalone_renderer_post_dedicated_thread_gpu_frame(
      renderer, &request, &mutation_result);
  if (status != BLINK_STANDALONE_STATUS_OK &&
      status != BLINK_STANDALONE_STATUS_PENDING) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "post_d3d12_dedicated_mutation status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }
  const uint64_t mutation_command_id = mutation_result.command_id;
  for (uint32_t poll = 0;
       mutation_result.state ==
               BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING &&
       poll < 10000;
       ++poll) {
    ::Sleep(1);
    status = blink_standalone_renderer_poll_dedicated_thread_gpu_frame(
        renderer, mutation_command_id, &mutation_result);
    if (status != BLINK_STANDALONE_STATUS_OK &&
        status != BLINK_STANDALONE_STATUS_PENDING) {
      break;
    }
  }
  if (status != BLINK_STANDALONE_STATUS_OK ||
      mutation_result.state !=
          BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED ||
      mutation_result.render_result.main_target_written == 0 ||
      mutation_result.render_result.backdrop_mask_written == 0 ||
      mutation_result.render_result.effect_count == 0) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mutation_frame status=%d result_status=%u "
                 "state=%u render_state=%u written=%u mask_written=%u "
                 "effects=%u error=%s\n",
                 status, mutation_result.status, mutation_result.state,
                 mutation_result.render_result.state,
                 mutation_result.render_result.main_target_written,
                 mutation_result.render_result.backdrop_mask_written,
                 mutation_result.render_result.effect_count,
                 mutation_result.error_message
                     ? mutation_result.error_message
                     : blink_standalone_renderer_last_error(renderer));
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }
  if (!ValidatePublicGpuBackdropEffectTable(
          renderer, mutation_result.render_result.effect_count,
          "d3d12_dedicated_mutation")) {
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  std::vector<uint32_t> mutated_pixels;
  if (!ReadbackD3D12Texture(
          device.Get(), queue.Get(), target_resource.Get(), kPhysicalWidth,
          kPhysicalHeight,
          static_cast<D3D12_RESOURCE_STATES>(target.d3d12.required_final_state),
          &mutated_pixels, &failure)) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mutation_readback failure=%s\n",
                 failure.c_str());
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }
  uint32_t mutation_changed_pixels = 0;
  const uint32_t compare_left = 320;
  const uint32_t compare_top = 600;
  const uint32_t compare_right = 760;
  const uint32_t compare_bottom = 840;
  for (uint32_t y = compare_top; y < compare_bottom; ++y) {
    for (uint32_t x = compare_left; x < compare_right; ++x) {
      const size_t index = static_cast<size_t>(y) * kPhysicalWidth + x;
      if (pixels[index] != mutated_pixels[index]) {
        ++mutation_changed_pixels;
      }
    }
  }
  if (mutation_changed_pixels < 1000) {
    std::fprintf(stderr,
                 "static_gpu_external_target_smoke: failed "
                 "d3d12_dedicated_mutation_pixels changed=%u\n",
                 mutation_changed_pixels);
    DestroyRenderer(renderer);
    ::CloseHandle(mask_shared_handle);
    ::CloseHandle(shared_handle);
    return false;
  }

  DestroyRenderer(renderer);
  ::CloseHandle(mask_shared_handle);
  ::CloseHandle(shared_handle);

  std::printf(
      "static_gpu_external_target_smoke: ok d3d12_dedicated=1 "
      "main_written=%u mask_written=%u effects=%u mask_pixels=%u "
      "mutation_changed=%u mutation_enqueue_ms=%.3f size=%ux%u "
      "command_id=%llu mutation_command_id=%llu polls=%u mutation_polls=%u "
      "elapsed_ms=%.3f source_ms=%.3f submit_ms=%.3f poll_ms=%.3f\n",
      command_result.render_result.main_target_written,
      command_result.render_result.backdrop_mask_written,
      command_result.render_result.effect_count, mask_pixels_written,
      mutation_changed_pixels, mutation_ms,
      command_result.render_result.physical_width,
      command_result.render_result.physical_height,
      static_cast<unsigned long long>(command_id),
      static_cast<unsigned long long>(mutation_command_id),
      command_result.poll_iterations, mutation_result.poll_iterations,
      command_result.elapsed_ms,
      command_result.source_tick_ms, command_result.submit_ms,
      command_result.poll_ms);
  return true;
}

#endif  // defined(_WIN32)

}  // namespace

int main(int argc, char** argv) {
#if defined(_WIN32)
  bool d3d12_dedicated_only = false;
  bool vulkan_dedicated_only = false;
  bool vulkan_dedicated_resize_cancel_only = false;
  bool vulkan_resize_return_only = false;
  bool skip_dedicated = false;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--d3d12-dedicated-only") == 0) {
      d3d12_dedicated_only = true;
    } else if (std::strcmp(argv[i], "--vulkan-dedicated-only") == 0) {
      vulkan_dedicated_only = true;
    } else if (std::strcmp(argv[i],
                           "--vulkan-dedicated-resize-cancel-only") == 0) {
      vulkan_dedicated_resize_cancel_only = true;
    } else if (std::strcmp(argv[i], "--vulkan-resize-return-only") == 0) {
      vulkan_resize_return_only = true;
    } else if (std::strcmp(argv[i], "--skip-dedicated") == 0) {
      skip_dedicated = true;
    }
  }
  if (d3d12_dedicated_only) {
    return RunD3D12DedicatedThreadFirstPublishSmoke() ? 0 : 1;
  }
  if (vulkan_dedicated_only) {
#if BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS
    return RunVulkanDedicatedThreadFirstPublishSmoke() ? 0 : 1;
#else
    std::printf(
        "static_gpu_external_target_smoke: blocked vulkan_dedicated=0 "
        "failure=static package lacks Vulkan headers\n");
    return 0;
#endif
  }
  if (vulkan_dedicated_resize_cancel_only) {
#if BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS
    return RunVulkanDedicatedThreadResizeCancelSmoke() ? 0 : 1;
#else
    std::printf(
        "static_gpu_external_target_smoke: blocked "
        "vulkan_dedicated_resize_cancel=0 "
        "failure=static package lacks Vulkan headers\n");
    return 0;
#endif
  }
  if (vulkan_resize_return_only) {
#if BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS
    return RunVulkanResizeReturnSmoke() ? 0 : 1;
#else
    std::printf(
        "static_gpu_external_target_smoke: blocked vulkan_resize_return=0 "
        "failure=static package lacks Vulkan headers\n");
    return 0;
#endif
  }
  bool ok = true;
#if BLINK_STATIC_PROBE_HAS_VULKAN_HEADERS
  ok = RunVulkanExternalTargetSmoke() && ok;
#else
  std::printf(
      "static_gpu_external_target_smoke: blocked vulkan=0 "
      "failure=static package lacks Vulkan headers\n");
#endif
  ok = RunD3D12ExternalTargetSmoke() && ok;
  if (!skip_dedicated) {
    std::printf(
        "static_gpu_external_target_smoke: blocked d3d12_dedicated=0 "
        "vulkan_dedicated=0 failure=run --d3d12-dedicated-only or "
        "--vulkan-dedicated-only in a fresh process because Blink main-thread "
        "identity is process-global\n");
  }
  return ok ? 0 : 1;
#else
  std::printf(
      "static_gpu_external_target_smoke: blocked platform=non_windows "
      "d3d12=0 vulkan=blocked_package_lacks_vulkan_headers_and_loader_metadata\n");
  return 0;
#endif
}
