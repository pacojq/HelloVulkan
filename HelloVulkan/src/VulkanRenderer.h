#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vulkan.h>
#include <vector>

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
	//void PickPhysicalDevice();
	//void CreateSurface();


	bool CheckValidationLayerSupport();
	std::vector<const char*> GetRequiredExtensions();

	int RateDeviceSuitability(VkPhysicalDevice device);


private:
	GLFWwindow* m_WindowHandle;
	VkInstance m_Instance;

	bool m_EnableValidationLayers;
	std::vector<const char*> m_ValidationLayers;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
};