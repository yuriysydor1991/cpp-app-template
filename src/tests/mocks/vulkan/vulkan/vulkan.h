#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_VULKAN_MOCK_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_VULKAN_MOCK_H

// Header-only mock of the subset of the Vulkan API used by the project's Vulkan
// component sources. It lets the Vulkan unit tests compile and run without
// linking the real Vulkan loader or touching a real driver: the loader touching
// functions are no-ops that return defaults. The real Vulkan interactions stay
// covered by the component tests, which link the real Vulkan loader.
//
// Only the handles, structures, enumerators, version helpers and the entry
// points actually referenced by the production code are reproduced here, with
// the same names and (compatible) signatures the real <vulkan/vulkan.h> exposes.

#include <cstdint>

// ---- handles --------------------------------------------------------------
// Vulkan dispatchable handles are opaque pointers in the real header too, which
// is exactly why the unit tests can hand out a fake, never dereferenced handle.
typedef struct VkInstance_T* VkInstance;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;

#define VK_NULL_HANDLE nullptr

// Only ever used as a pointer (the allocator argument), so an incomplete type
// is enough.
struct VkAllocationCallbacks;

// ---- result codes ---------------------------------------------------------
typedef int VkResult;

#define VK_SUCCESS 0
#define VK_NOT_READY 1
#define VK_INCOMPLETE 5
#define VK_ERROR_INITIALIZATION_FAILED (-3)

// ---- version helpers ------------------------------------------------------
// Defined with C++ casts (instead of the real header's C-style casts) so the
// mock does not trip the project's -Wold-style-cast on the unit test sources.
#define VK_MAKE_VERSION(major, minor, patch)                \
  ((static_cast<std::uint32_t>(major) << 22) |              \
   (static_cast<std::uint32_t>(minor) << 12) |              \
   static_cast<std::uint32_t>(patch))

#define VK_VERSION_MAJOR(version) (static_cast<std::uint32_t>(version) >> 22)
#define VK_VERSION_MINOR(version) \
  ((static_cast<std::uint32_t>(version) >> 12) & 0x3FFu)
#define VK_VERSION_PATCH(version) (static_cast<std::uint32_t>(version) & 0xFFFu)

#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)

#define VK_MAX_PHYSICAL_DEVICE_NAME_SIZE 256

// ---- enumerations ---------------------------------------------------------
typedef enum VkStructureType
{
  VK_STRUCTURE_TYPE_APPLICATION_INFO = 0,
  VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO = 1,
} VkStructureType;

typedef enum VkPhysicalDeviceType
{
  VK_PHYSICAL_DEVICE_TYPE_OTHER = 0,
  VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = 1,
  VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = 2,
  VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = 3,
  VK_PHYSICAL_DEVICE_TYPE_CPU = 4,
} VkPhysicalDeviceType;

// ---- structures -----------------------------------------------------------
typedef struct VkApplicationInfo
{
  VkStructureType sType;
  const void* pNext;
  const char* pApplicationName;
  std::uint32_t applicationVersion;
  const char* pEngineName;
  std::uint32_t engineVersion;
  std::uint32_t apiVersion;
} VkApplicationInfo;

typedef struct VkInstanceCreateInfo
{
  VkStructureType sType;
  const void* pNext;
  std::uint32_t flags;
  const VkApplicationInfo* pApplicationInfo;
  std::uint32_t enabledLayerCount;
  const char* const* ppEnabledLayerNames;
  std::uint32_t enabledExtensionCount;
  const char* const* ppEnabledExtensionNames;
} VkInstanceCreateInfo;

// Only the fields read by the production handler are reproduced; the real
// struct carries many more (limits, sparse properties, ...) that the project
// does not touch.
typedef struct VkPhysicalDeviceProperties
{
  std::uint32_t apiVersion;
  std::uint32_t driverVersion;
  std::uint32_t vendorID;
  std::uint32_t deviceID;
  VkPhysicalDeviceType deviceType;
  char deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
} VkPhysicalDeviceProperties;

// ---- test hooks -----------------------------------------------------------
namespace vkmock
{

/**
 * @brief Test hook: while true, the next instance creation reports a failure
 * (exactly as the real loader does when no usable driver is available), so the
 * controller's init / create error paths can be exercised.
 */
inline bool& fail_instance_creation()
{
  static bool flag = false;
  return flag;
}

}  // namespace vkmock

// ---- entry points ---------------------------------------------------------
inline VkResult vkCreateInstance(const VkInstanceCreateInfo*,
                                 const VkAllocationCallbacks*,
                                 VkInstance* pInstance)
{
  if (vkmock::fail_instance_creation()) {
    if (pInstance != nullptr) {
      *pInstance = VK_NULL_HANDLE;
    }
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  static int placeholder = 0;

  if (pInstance != nullptr) {
    *pInstance = reinterpret_cast<VkInstance>(&placeholder);
  }

  return VK_SUCCESS;
}

inline void vkDestroyInstance(VkInstance, const VkAllocationCallbacks*) {}

inline VkResult vkEnumeratePhysicalDevices(VkInstance,
                                           std::uint32_t* pPhysicalDeviceCount,
                                           VkPhysicalDevice* pPhysicalDevices)
{
  // The mock reports no physical devices: the production fetch_devices() seam is
  // overridden in the unit tests, so this default only needs to keep the
  // factory / handler sources that reference the symbol compilable and linkable.
  if (pPhysicalDeviceCount != nullptr && pPhysicalDevices == nullptr) {
    *pPhysicalDeviceCount = 0;
  }

  return VK_SUCCESS;
}

inline void vkGetPhysicalDeviceProperties(
    VkPhysicalDevice, VkPhysicalDeviceProperties* pProperties)
{
  if (pProperties != nullptr) {
    *pProperties = VkPhysicalDeviceProperties{};
  }
}

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_VULKAN_MOCK_H
