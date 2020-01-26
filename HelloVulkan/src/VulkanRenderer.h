#pragma once

#include "Vertex.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#include <vector>

#include <optional>

struct GLFWwindow;



#include <iostream>
#define ASSERT(x, msg) { if(!(x)) { throw std::runtime_error(msg); } }
#define LOG(msg) { std::cout << msg << std::endl; }

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	LOG("Vulkan validation layer: " << pCallbackData->pMessage);
	return VK_FALSE;
}








struct QueueFamilyIndices
{
	std::optional<uint32_t> GraphicsFamily;
	std::optional<uint32_t> PresentFamily;

	bool IsComplete()
	{
		return GraphicsFamily.has_value() && PresentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR Capabilities;
	std::vector<VkSurfaceFormatKHR> Formats;
	std::vector<VkPresentModeKHR> PresentModes;
};



class VulkanRenderer
{
public:
	VulkanRenderer(GLFWwindow* windowHandle);

	void Init();
	void DrawFrame();
	void ExitMainLoop();
	void CleanUp();

	void OnWindowResize(int width, int height);

private:
	void RecreateSwapChain();
	void CleanupSwapChain();

// Initialization functions
private:
	void CreateInstance();
	void SetupDebugMessenger();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateGraphicsPipeline();
	void CreateFrameBuffers();
	void CreateCommandPool();
	void CreateVertexBuffer();
	void CreateCommandBuffers();
	void CreateSyncObjects();


// Util functions
private:
	bool CheckValidationLayerSupport();
	std::vector<const char*> GetRequiredExtensions();

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	bool IsDeviceSuitable(VkPhysicalDevice device);
	int RateDeviceSuitability(VkPhysicalDevice device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


private:

	// How many frames should be processed concurrently.
	const int MAX_FRAMES_IN_FLIGHT = 2;

	const std::vector<const char*> m_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> m_DeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<Vertex> m_Vertices = {
		{{0.0f, -0.75f}, {1.0f, 1.0f, 1.0f}},
		{{0.25f, 0.5f}, {0.0f, 1.0f, 0.0f}},
		{{-0.25f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	};



private:

	GLFWwindow* m_Window;
	VkInstance m_Instance;

	VkPhysicalDevice m_PhysicalDevice;
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;

	VkSurfaceKHR m_Surface;
	VkQueue m_PresentQueue;

	VkSwapchainKHR m_SwapChain; 
	std::vector<VkImage> m_SwapChainImages;
	VkFormat m_SwapChainImageFormat;
	VkExtent2D m_SwapChainExtent;
	std::vector<VkImageView> m_SwapChainImageViews;

	VkPipelineLayout m_PipelineLayout;
	VkRenderPass m_RenderPass;
	VkPipeline m_GraphicsPipeline;

	VkBuffer m_VertexBuffer;
	VkDeviceMemory m_VertexBufferMemory;

	std::vector<VkFramebuffer> m_SwapChainFramebuffers;
	VkCommandPool m_CommandPool;
	std::vector<VkCommandBuffer> m_CommandBuffers;


	// Each frame has its own semaphore

	std::vector<VkSemaphore> m_ImageAvailableSemaphores;
	std::vector<VkSemaphore> m_RenderFinishedSemaphores;
	std::vector<VkFence> m_InFlightFences;
	std::vector<VkFence> m_ImagesInFlight; // Track each swap chain image if a frame in flight is currently using it
	size_t m_CurrentFrame = 0;

	bool m_FramebufferResized = false;

	bool m_EnableValidationLayers;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
};