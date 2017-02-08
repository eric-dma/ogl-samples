///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Samples Pack (ogl-samples.g-truc.net)
///
/// Copyright (c) 2004 - 2014 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////

#define VK_USE_PLATFORM_XCB_KHR
#include <iostream>
#include <vulkan/vulkan.h>
//#include <vulkan/vulkan_mesa_prerelease.h>
#include "test.hpp"
#include <GL/gl_mesa_prerelease.h>
#include <GL/glx.h>

// Macro to check and display Vulkan return results
#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << res << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}

namespace
{
	char const * VERT_SHADER_SOURCE("gl-450/culling.vert");
	char const * FRAG_SHADER_SOURCE("gl-450/culling.frag");
	char const * TEXTURE_DIFFUSE("kueken7_rgba8_srgb.dds");

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fv2f);
	glf::vertex_v2fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v2fv2f(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace buffer
	{
		enum type
		{
			VERTEX,
			ELEMENT,
			TRANSFORM,
			MAX
		};
	}//namespace buffer
	 
	GLuint PipelineName(0);
	GLuint ProgramName(0);
	GLuint VertexArrayName(0);
	GLuint BufferName[buffer::MAX] = {0, 0, 0};
	GLuint TextureName(0);
}//namespace



struct GlDriver {
    PFN_glGenMemoryObjectsKHR pfnGenMemoryObjectsKHR;
    PFN_glTexStorageMem2DKHR pfnTexStorageMem2DKHR;
    PFN_glImportMemoryFdKHR pfnImportMemoryFdKHR;
};

struct GlDriver glDriver;

void initGlDriver()
{
    glDriver.pfnGenMemoryObjectsKHR =
        (PFN_glGenMemoryObjectsKHR)glXGetProcAddressARB((const GLubyte*)"glCreateMemoryObjectsEXT");
    glDriver.pfnTexStorageMem2DKHR =
        (PFN_glTexStorageMem2DKHR)glXGetProcAddressARB((const GLubyte*)"glTexStorageMem2DEXT");
    glDriver.pfnImportMemoryFdKHR =
        (PFN_glImportMemoryFdKHR)glXGetProcAddressARB((const GLubyte*)"glImportMemoryFdEXT");
    if (!glDriver.pfnImportMemoryFdKHR
        || !glDriver.pfnTexStorageMem2DKHR
        || !glDriver.pfnGenMemoryObjectsKHR) {
        printf("Failed to load gl extensions\n");
        exit(1);
    }
}

struct VkDriver {
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memProperties;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    VkDevice device;
    VkQueue queue;
    PFN_vkGetMemoryFdKHX pfnGetMemoryFdKHX;
};

struct VkDriver vkDriver;

int getQueueFamilyIndex(VkQueueFlagBits bits)
{
    for (int i = 0; i < vkDriver.queueFamilyProperties.size(); i++) {
        if (vkDriver.queueFamilyProperties[i].queueFlags & bits)
            return i;
    }
    assert(false);
    return -1;
}

int getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32 *memTypeFound = nullptr)
{
    for (int i = 0; i < vkDriver.memProperties.memoryTypeCount; i++) {
        if ((typeBits & 1) == 1) {
            if ((vkDriver.memProperties.memoryTypes[i].propertyFlags & properties)
                    == properties) {
                return i;
            }
        }
        typeBits >>= 1;
    }

    assert(false);
    return -1;
}

GLuint vkAllocateGlMemObj(gli::texture2d &texture)
{
    /**
     * Image creation
     */
    VkImage image;


    VkImageCreateInfo imageCreateInfo = {};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.pNext = NULL;
    imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
    imageCreateInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    imageCreateInfo.flags = VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_KHX;
    imageCreateInfo.mipLevels = texture.levels();
    imageCreateInfo.arrayLayers = 1;
    imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.tiling = VK_IMAGE_TILING_LINEAR;
    imageCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_GENERAL;
    imageCreateInfo.extent = { (uint32_t)texture[0].extent().x,
                               (uint32_t)texture[0].extent().y,
                               (uint32_t)texture[0].extent().z };
    imageCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;

    VK_CHECK_RESULT(vkCreateImage(vkDriver.device,
                                    &imageCreateInfo,
                                    NULL,
                                    &image));
    /**
     * Get memory requirements
     */
    VkMemoryRequirements memReqs = {};
    vkGetImageMemoryRequirements(vkDriver.device, image, &memReqs);

    /**
     * Memory allocation
     */
    VkDeviceMemory memory;

    VkDedicatedAllocationMemoryAllocateInfoNV dedicated = {};
    dedicated.sType = VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV;
    dedicated.image = image;

    VkMemoryAllocateInfo memAllocInfo = {};
    memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllocInfo.pNext = &dedicated;
    memAllocInfo.allocationSize = memReqs.size;
    memAllocInfo.memoryTypeIndex = getMemoryType(memReqs.memoryTypeBits,
                                                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

    VK_CHECK_RESULT(vkAllocateMemory(vkDriver.device,
                                        &memAllocInfo,
                                        NULL,
                                        &memory));
    VK_CHECK_RESULT(vkBindImageMemory(vkDriver.device,
                                        image,
                                        memory,
                                        0));
    /**
     * Initialize memory
     */
    uint8_t *data;
    VK_CHECK_RESULT(vkMapMemory(vkDriver.device,
                                memory,
                                0,
                                memReqs.size,
                                0,
                                (void **)&data));
    memcpy(data, texture.data(), texture.size());
    vkUnmapMemory(vkDriver.device, memory);

    /**
     * Export memory as FD
     */
    int fd = -1;
    vkDriver.pfnGetMemoryFdKHX(vkDriver.device, memory, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHX, &fd);

    /**
     * THESE ARE THE NEW PARTS REQUIRED IN VRCLIENT
     */

    /**
     * Import memory into GL
     */
    GLuint memObjName;
    glDriver.pfnGenMemoryObjectsKHR(1, &memObjName);
    glDriver.pfnImportMemoryFdKHR(memObjName, memReqs.size, GL_HANDLE_TYPE_OPAQUE_FD_KHR, fd);

    return memObjName;
}

void initVkDevice()
{
    std::vector<const char*> instanceExtensions;
    instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
    instanceExtensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

    /**
     * Instance creation
     */
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "interop test";
    appInfo.pEngineName = "sample";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = NULL;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

    VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, NULL, &vkDriver.instance));

    /**
     * Physical device creation
     */
    uint32_t deviceCount = 0;
    VK_CHECK_RESULT(vkEnumeratePhysicalDevices(vkDriver.instance, &deviceCount, NULL));

    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    VK_CHECK_RESULT(vkEnumeratePhysicalDevices(vkDriver.instance,
                    &deviceCount, physicalDevices.data()));
    vkDriver.physicalDevice = physicalDevices[0];

    /**
     * Get physical device information
     */
    vkGetPhysicalDeviceProperties(vkDriver.physicalDevice, &vkDriver.properties);
    vkGetPhysicalDeviceFeatures(vkDriver.physicalDevice, &vkDriver.features);
    vkGetPhysicalDeviceMemoryProperties(vkDriver.physicalDevice, &vkDriver.memProperties);

    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(vkDriver.physicalDevice, &queueFamilyCount, nullptr);
    vkDriver.queueFamilyProperties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vkDriver.physicalDevice, &queueFamilyCount, vkDriver.queueFamilyProperties.data());

    /**
     * Queue creation
     */
    const float defaultQueuePriority = 0.0f;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

    VkDeviceQueueCreateInfo queueInfo{};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.pNext = NULL;
    queueInfo.queueFamilyIndex = getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &defaultQueuePriority;
    queueCreateInfos.push_back(queueInfo);

    /**
     * Device creation
     */
    std::vector<const char*> deviceExtensions;
    deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.pEnabledFeatures = NULL;
    deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

    VK_CHECK_RESULT(vkCreateDevice(vkDriver.physicalDevice,
                                    &deviceCreateInfo,
                                    NULL,
                                    &vkDriver.device));

    vkGetDeviceQueue(vkDriver.device, queueInfo.queueFamilyIndex, 0, &vkDriver.queue);

    vkDriver.pfnGetMemoryFdKHX = (PFN_vkGetMemoryFdKHX)vkGetDeviceProcAddr(vkDriver.device, "vkGetMemoryFdKHX");

    return;
}

class gl_450_culling : public test
{
public:
	gl_450_culling(int argc, char* argv[]) :
		test(argc, argv, "gl-450-culling", test::CORE, 4, 2)
	{}

private:
	bool initProgram()
	{
		bool Validated(true);
	
		glGenProgramPipelines(1, &PipelineName);

		if(Validated)
		{
			compiler Compiler;
			GLuint VertShaderName = Compiler.create(GL_VERTEX_SHADER, getDataDirectory() + VERT_SHADER_SOURCE, "--version 420 --profile core");
			GLuint FragShaderName = Compiler.create(GL_FRAGMENT_SHADER, getDataDirectory() + FRAG_SHADER_SOURCE, "--version 420 --profile core");
			Validated = Validated && Compiler.check();

			ProgramName = glCreateProgram();
			glProgramParameteri(ProgramName, GL_PROGRAM_SEPARABLE, GL_TRUE);
			glAttachShader(ProgramName, VertShaderName);
			glAttachShader(ProgramName, FragShaderName);
			glLinkProgram(ProgramName);

			Validated = Validated && Compiler.check_program(ProgramName);
		}

		if(Validated)
			glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT, ProgramName);

		return Validated;
	}

	bool initBuffer()
	{
		bool Validated(true);

		glGenBuffers(buffer::MAX, BufferName);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLint UniformBufferOffset(0);

		glGetIntegerv(
			GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
			&UniformBufferOffset);

		GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4)), UniformBufferOffset);

		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
		glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		return Validated;
	}

	bool initTexture()
    {
        GLuint memObjName;

        initVkDevice();
        initGlDriver();

        gli::texture2d Texture(gli::load_dds((getDataDirectory() + TEXTURE_DIFFUSE).c_str()));

        /**
         * Allocate memory
         */
        memObjName = vkAllocateGlMemObj(Texture);

        gli::gl GL(gli::gl::PROFILE_GL33);
        gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &TextureName);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureName);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glDriver.pfnTexStorageMem2DKHR(GL_TEXTURE_2D,
                                       static_cast<GLint>(Texture.levels()),
                                       Format.Internal,
                                       static_cast<GLsizei>(Texture[0].extent().x),
                                       static_cast<GLsizei>(Texture[0].extent().y),
                                       memObjName,
                                       0);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        return true;
    }

	bool initVertexArray()
	{
		glGenVertexArrays(1, &VertexArrayName);
		glBindVertexArray(VertexArrayName);
			glVertexAttribBinding(semantic::attr::POSITION, 0);
			glVertexAttribFormat(semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0);

			glVertexAttribBinding(semantic::attr::TEXCOORD, 0);
			glVertexAttribFormat(semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2));

			glEnableVertexAttribArray(semantic::attr::POSITION);
			glEnableVertexAttribArray(semantic::attr::TEXCOORD);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
			glBindVertexBuffer(0, BufferName[buffer::VERTEX], 0, sizeof(glf::vertex_v2fv2f));
		glBindVertexArray(0);

		return true;
	}

	bool begin()
	{
		bool Validated = this->checkExtension("GL_ARB_cull_distance");

		if(Validated)
			Validated = initTexture();
		if(Validated)
			Validated = initProgram();
		if(Validated)
			Validated = initBuffer();
		if(Validated)
			Validated = initVertexArray();

		return Validated;
	}

	bool end()
	{
		bool Validated(true);

		glDeleteProgramPipelines(1, &PipelineName);
		glDeleteProgram(ProgramName);
		glDeleteBuffers(buffer::MAX, BufferName);
		glDeleteTextures(1, &TextureName);
		glDeleteVertexArrays(1, &VertexArrayName);

		return Validated;
	}

	bool render()
	{
		glm::vec2 WindowSize(this->getWindowSize());

		{
			glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
			glm::mat4* Pointer = (glm::mat4*)glMapBufferRange(
				GL_UNIFORM_BUFFER, 0,	sizeof(glm::mat4),
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

			glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, WindowSize.x / WindowSize.y, 0.1f, 100.0f);
			glm::mat4 Model = glm::mat4(1.0f);
		
			*Pointer = Projection * this->view() * Model;

			// Make sure the uniform buffer is uploaded
			glUnmapBuffer(GL_UNIFORM_BUFFER);
		}

		glViewportIndexedf(0, 0, 0, WindowSize.x, WindowSize.y);
		glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		// Bind rendering objects
		glBindBufferBase(GL_UNIFORM_BUFFER, semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);
		glBindProgramPipeline(PipelineName);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureName);
		glBindVertexArray(VertexArrayName);

		glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, 0, 1, 0, 0);

		return true;
	}
};

int main(int argc, char* argv[])
{
	int Error(0);

	gl_450_culling Test(argc, argv);
	Error += Test();

	return Error;
}

