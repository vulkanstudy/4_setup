#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class MyApplication
{
private:
	GLFWwindow* window_;
public:
	MyApplication(): window_(nullptr){}
	~MyApplication() {}

	void run()
	{
		// ������
		initializeWindow();
		initializeVulkan();

		// �ʏ폈��
		mainloop();

		// ��Еt��
		finalizeVulkan();
		finalizeWindow();
	}

	// �\���E�B���h�E�̐ݒ�
	void initializeWindow()
	{
		const int WIDTH = 800;
		const int HEIGHT = 600;

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window_ = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan�@Application", nullptr, nullptr);
	}

	void finalizeWindow()
	{
		glfwDestroyWindow(window_);

		glfwTerminate();
	}

	// Vulkan�̐ݒ�
	void initializeVulkan()
	{
	}

	void finalizeVulkan()
	{
	}

	// �ʏ�̏���
	void mainloop()
	{
		while (!glfwWindowShouldClose(window_)) 
		{
			glfwPollEvents();
		}
	}
};
