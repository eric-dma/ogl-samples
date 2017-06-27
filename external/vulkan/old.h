/* WARNING: this file contains pre-release extensions
 *
 * The function prototypes hereby presented have not been
 * ratified by the Khronos group, and are subject to change
 * without notification
 *
 * Here be dragons
 */

#ifndef __VULKAN_RADV_PRE_RELEASE_H__
#define __VULKAN_RADV_PRE_RELEASE_H__

#include "vulkan.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define VK_ERROR_INVALID_EXTERNAL_HANDLE_KHX (VkResult) -1000072003

#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO_KHX (VkStructureType)1000071000
#define VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES_KHX (VkStructureType)1000071001
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO_KHX (VkStructureType)1000071002
#define VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES_KHX (VkStructureType)1000071003
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES_KHX (VkStructureType)1000071004
#define VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO_KHX (VkStructureType)1000072000
#define VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHX (VkStructureType)1000072001
#define VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_KHX (VkStructureType)1000072002
#define VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHX (VkStructureType)1000073000
#define VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHX (VkStructureType)1000073001
#define VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHX (VkStructureType)1000074000
#define VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHX (VkStructureType)1000074001
#define VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHX (VkStructureType)1000075000
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO_KHX (VkStructureType)1000076000
#define VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES_KHX (VkStructureType)1000076001
#define VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO_KHX (VkStructureType)1000077000
#define VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHX (VkStructureType)1000078000
#define VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHX (VkStructureType)1000078001
#define VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHX (VkStructureType)1000078002
#define VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHX (VkStructureType)1000079000


#define VK_KHX_external_memory_capabilities 1
#define VK_LUID_SIZE_KHX                  8
#define VK_KHX_EXTERNAL_MEMORY_CAPABILITIES_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME "VK_KHX_external_memory_capabilities"


typedef enum VkExternalMemoryHandleTypeFlagBitsKHX {
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHX = 0x00000001,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_KHX = 0x00000002,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_KHX = 0x00000004,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT_KHX = 0x00000008,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT_KHX = 0x00000010,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT_KHX = 0x00000020,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT_KHX = 0x00000040,
    VK_EXTERNAL_MEMORY_HANDLE_TYPE_FLAG_BITS_MAX_ENUM_KHX = 0x7FFFFFFF
} VkExternalMemoryHandleTypeFlagBitsKHX;

typedef enum VkExternalMemoryFeatureFlagBitsKHX {
    VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_KHX = 0x00000001,
    VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_KHX = 0x00000002,
    VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_KHX = 0x00000004,
    VK_EXTERNAL_MEMORY_FEATURE_FLAG_BITS_MAX_ENUM_KHX = 0x7FFFFFFF
} VkExternalMemoryFeatureFlagBitsKHX;

typedef VkFlags VkExternalMemoryHandleTypeFlagsKHX;
typedef VkFlags VkExternalMemoryFeatureFlagsKHX;

typedef struct VkExternalMemoryPropertiesKHX {
    VkExternalMemoryFeatureFlagsKHX       externalMemoryFeatures;
    VkExternalMemoryHandleTypeFlagsKHX    exportFromImportedHandleTypes;
    VkExternalMemoryHandleTypeFlagsKHX    compatibleHandleTypes;
} VkExternalMemoryPropertiesKHX;

typedef struct VkPhysicalDeviceExternalImageFormatInfoKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkExternalMemoryHandleTypeFlagBitsKHX    handleType;
} VkPhysicalDeviceExternalImageFormatInfoKHX;

typedef struct VkExternalImageFormatPropertiesKHX {
    VkStructureType                  sType;
    const void*                      pNext;
    VkExternalMemoryPropertiesKHX    externalMemoryProperties;
} VkExternalImageFormatPropertiesKHX;

typedef struct VkPhysicalDeviceExternalBufferInfoKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkBufferCreateFlags                      flags;
    VkBufferUsageFlags                       usage;
    VkExternalMemoryHandleTypeFlagBitsKHX    handleType;
} VkPhysicalDeviceExternalBufferInfoKHX;

typedef struct VkExternalBufferPropertiesKHX {
    VkStructureType                  sType;
    const void*                      pNext;
    VkExternalMemoryPropertiesKHX    externalMemoryProperties;
} VkExternalBufferPropertiesKHX;

typedef struct VkPhysicalDeviceIDPropertiesKHX {
    VkStructureType    sType;
    const void*        pNext;
    uint8_t            deviceUUID[VK_UUID_SIZE];
    uint8_t            deviceLUID[VK_LUID_SIZE_KHX];
    VkBool32           deviceLUIDValid;
} VkPhysicalDeviceIDPropertiesKHX;


typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHX)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHX* pExternalBufferInfo, VkExternalBufferPropertiesKHX* pExternalBufferProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferPropertiesKHX(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalBufferInfoKHX* pExternalBufferInfo,
    VkExternalBufferPropertiesKHX*              pExternalBufferProperties);
#endif

#define VK_KHX_external_memory 1
#define VK_KHX_EXTERNAL_MEMORY_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_MEMORY_EXTENSION_NAME "VK_KHX_external_memory"
#define VK_QUEUE_FAMILY_EXTERNAL_KHX      (~0U-1)

typedef struct VkExternalMemoryImageCreateInfoKHX {
    VkStructureType                       sType;
    const void*                           pNext;
    VkExternalMemoryHandleTypeFlagsKHX    handleTypes;
} VkExternalMemoryImageCreateInfoKHX;

typedef struct VkExternalMemoryBufferCreateInfoKHX {
    VkStructureType                       sType;
    const void*                           pNext;
    VkExternalMemoryHandleTypeFlagsKHX    handleTypes;
} VkExternalMemoryBufferCreateInfoKHX;

typedef struct VkExportMemoryAllocateInfoKHX {
    VkStructureType                       sType;
    const void*                           pNext;
    VkExternalMemoryHandleTypeFlagsKHX    handleTypes;
} VkExportMemoryAllocateInfoKHX;



#ifdef VK_USE_PLATFORM_WIN32_KHR
#define VK_KHX_external_memory_win32 1
#define VK_KHX_EXTERNAL_MEMORY_WIN32_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME "VK_KHX_external_memory_win32"

typedef struct VkImportMemoryWin32HandleInfoKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkExternalMemoryHandleTypeFlagBitsKHX    handleType;
    HANDLE                                   handle;
} VkImportMemoryWin32HandleInfoKHX;

typedef struct VkExportMemoryWin32HandleInfoKHX {
    VkStructureType               sType;
    const void*                   pNext;
    const SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportMemoryWin32HandleInfoKHX;


typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryWin32HandleKHX)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagBitsKHX handleType, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHX(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkExternalMemoryHandleTypeFlagBitsKHX       handleType,
    HANDLE*                                     pHandle);
#endif
#endif /* VK_USE_PLATFORM_WIN32_KHR */

#define VK_KHX_external_memory_fd 1
#define VK_KHX_EXTERNAL_MEMORY_FD_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_MEMORY_FD_EXTENSION_NAME "VK_KHX_external_memory_fd"

typedef struct VkImportMemoryFdInfoKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkExternalMemoryHandleTypeFlagBitsKHX    handleType;
    int                                      fd;
} VkImportMemoryFdInfoKHX;

typedef struct VkMemoryFdPropertiesKHX {
    VkStructureType    sType;
    void*              pNext;
    uint32_t           memoryTypeBits;
} VkMemoryFdPropertiesKHX;

typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryFdKHX)(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagBitsKHX handleType, int* pFd);
typedef VkResult (VKAPI_PTR *PFN_vkGetMemoryFdPropertiesKHX)(VkDevice device, VkExternalMemoryHandleTypeFlagBitsKHX handleType, int fd, VkMemoryFdPropertiesKHX* pMemoryFdProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdKHX(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkExternalMemoryHandleTypeFlagBitsKHX       handleType,
    int*                                        pFd);

VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdPropertiesKHX(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBitsKHX       handleType,
    int                                         fd,
    VkMemoryFdPropertiesKHX*                    pMemoryFdProperties);
#endif

#ifdef VK_USE_PLATFORM_WIN32_KHR
#define VK_KHX_win32_keyed_mutex 1
#define VK_KHX_WIN32_KEYED_MUTEX_SPEC_VERSION 1
#define VK_KHX_WIN32_KEYED_MUTEX_EXTENSION_NAME "VK_KHX_win32_keyed_mutex"

typedef struct VkWin32KeyedMutexAcquireReleaseInfoKHX {
    VkStructureType          sType;
    const void*              pNext;
    uint32_t                 acquireCount;
    const VkDeviceMemory*    pAcquireSyncs;
    const uint64_t*          pAcquireKeys;
    const uint32_t*          pAcquireTimeouts;
    uint32_t                 releaseCount;
    const VkDeviceMemory*    pReleaseSyncs;
    const uint64_t*          pReleaseKeys;
} VkWin32KeyedMutexAcquireReleaseInfoKHX;


#endif /* VK_USE_PLATFORM_WIN32_KHR */

#define VK_KHX_external_semaphore_capabilities 1
#define VK_KHX_EXTERNAL_SEMAPHORE_CAPABILITIES_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME "VK_KHX_external_semaphore_capabilities"


typedef enum VkExternalSemaphoreHandleTypeFlagBitsKHX {
    VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT_KHX = 0x00000001,
    VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT_KHX = 0x00000002,
    VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_KHX = 0x00000004,
    VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT_KHX = 0x00000008,
    VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_FENCE_FD_BIT_KHX = 0x00000010,
    VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_FLAG_BITS_MAX_ENUM_KHX = 0x7FFFFFFF
} VkExternalSemaphoreHandleTypeFlagBitsKHX;

typedef enum VkExternalSemaphoreFeatureFlagBitsKHX {
    VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT_KHX = 0x00000001,
    VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT_KHX = 0x00000002,
    VK_EXTERNAL_SEMAPHORE_FEATURE_FLAG_BITS_MAX_ENUM_KHX = 0x7FFFFFFF
} VkExternalSemaphoreFeatureFlagBitsKHX;

typedef VkFlags VkExternalSemaphoreHandleTypeFlagsKHX;
typedef VkFlags VkExternalSemaphoreFeatureFlagsKHX;

typedef struct VkPhysicalDeviceExternalSemaphoreInfoKHX {
    VkStructureType                             sType;
    const void*                                 pNext;
    VkExternalSemaphoreHandleTypeFlagBitsKHX    handleType;
} VkPhysicalDeviceExternalSemaphoreInfoKHX;

typedef struct VkExternalSemaphorePropertiesKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkExternalSemaphoreHandleTypeFlagsKHX    exportFromImportedHandleTypes;
    VkExternalSemaphoreHandleTypeFlagsKHX    compatibleHandleTypes;
    VkExternalSemaphoreFeatureFlagsKHX       externalSemaphoreFeatures;
} VkExternalSemaphorePropertiesKHX;


typedef void (VKAPI_PTR *PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHX)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHX* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHX* pExternalSemaphoreProperties);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphorePropertiesKHX(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfoKHX* pExternalSemaphoreInfo,
    VkExternalSemaphorePropertiesKHX*           pExternalSemaphoreProperties);
#endif

#define VK_KHX_external_semaphore 1
#define VK_KHX_EXTERNAL_SEMAPHORE_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_SEMAPHORE_EXTENSION_NAME "VK_KHX_external_semaphore"

typedef struct VkExportSemaphoreCreateInfoKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkExternalSemaphoreHandleTypeFlagsKHX    handleTypes;
} VkExportSemaphoreCreateInfoKHX;



#ifdef VK_USE_PLATFORM_WIN32_KHX
#define VK_KHX_external_semaphore_win32 1
#define VK_KHX_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME "VK_KHX_external_semaphore_win32"

typedef struct VkImportSemaphoreWin32HandleInfoKHX {
    VkStructureType                          sType;
    const void*                              pNext;
    VkSemaphore                              semaphore;
    VkExternalSemaphoreHandleTypeFlagsKHX    handleType;
    HANDLE                                   handle;
} VkImportSemaphoreWin32HandleInfoKHX;

typedef struct VkExportSemaphoreWin32HandleInfoKHX {
    VkStructureType               sType;
    const void*                   pNext;
    const SECURITY_ATTRIBUTES*    pAttributes;
    DWORD                         dwAccess;
    LPCWSTR                       name;
} VkExportSemaphoreWin32HandleInfoKHX;

typedef struct VkD3D12FenceSubmitInfoKHX {
    VkStructureType    sType;
    const void*        pNext;
    const uint64_t*    pWaitSemaphoreValues;
    const uint64_t*    pSignalSemaphoreValues;
} VkD3D12FenceSubmitInfoKHX;


typedef VkResult (VKAPI_PTR *PFN_vkImportSemaphoreWin32HandleKHX)(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHX* pImportSemaphoreWin32HandleInfo);
typedef VkResult (VKAPI_PTR *PFN_vkGetSemaphoreWin32HandleKHX)(VkDevice device, VkSemaphore semaphore, VkExternalSemaphoreHandleTypeFlagBitsKHX handleType, HANDLE* pHandle);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHX(
    VkDevice                                    device,
    const VkImportSemaphoreWin32HandleInfoKHX*  pImportSemaphoreWin32HandleInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHX(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    VkExternalSemaphoreHandleTypeFlagBitsKHX    handleType,
    HANDLE*                                     pHandle);
#endif
#endif /* VK_USE_PLATFORM_WIN32_KHX */

#define VK_KHX_external_semaphore_fd 1
#define VK_KHX_EXTERNAL_SEMAPHORE_FD_SPEC_VERSION 1
#define VK_KHX_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME "VK_KHX_external_semaphore_fd"

typedef struct VkImportSemaphoreFdInfoKHX {
    VkStructureType                             sType;
    const void*                                 pNext;
    VkSemaphore                                 semaphore;
    VkExternalSemaphoreHandleTypeFlagBitsKHX    handleType;
    int                                         fd;
} VkImportSemaphoreFdInfoKHX;


typedef VkResult (VKAPI_PTR *PFN_vkImportSemaphoreFdKHX)(VkDevice device, const VkImportSemaphoreFdInfoKHX* pImportSemaphoreFdInfo);
typedef VkResult (VKAPI_PTR *PFN_vkGetSemaphoreFdKHX)(VkDevice device, VkSemaphore semaphore, VkExternalSemaphoreHandleTypeFlagBitsKHX handleType, int* pFd);

#ifndef VK_NO_PROTOTYPES
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreFdKHX(
    VkDevice                                    device,
    const VkImportSemaphoreFdInfoKHX*           pImportSemaphoreFdInfo);

VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreFdKHX(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    VkExternalSemaphoreHandleTypeFlagBitsKHX    handleType,
    int*                                        pFd);
#endif


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // __VULKAN_RADV_PRE_RELEASE_H__
