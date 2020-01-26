#pragma once

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
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool IsComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};



class VulkanRenderer
{
public:
	VulkanRenderer(GLFWwindow* windowHandle);

	void Init();
	void CleanUp();


// Initialization functions
private:
	void CreateInstance();
	void SetupDebugMessenger();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();


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



private:
	GLFWwindow* m_Window;
	VkInstance m_Instance;

	VkPhysicalDevice m_PhysicalDevice;
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;

	VkSurfaceKHR m_Surface;
	VkQueue m_PresentQueue;

	bool m_EnableValidationLayers;
	std::vector<const char*> m_ValidationLayers;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
};