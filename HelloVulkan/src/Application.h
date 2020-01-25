#pragma once

#include "VulkanRenderer.h"

#include <memory>

class Application
{
public:
	void Run()
	{
		Init();
		MainLoop();
		CleanUp();
	}

private:
	void Init();
	void MainLoop();
	void CleanUp();

private:
	GLFWwindow* m_Window;
	std::unique_ptr<VulkanRenderer> m_Renderer;
};