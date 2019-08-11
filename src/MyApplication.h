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
		// 初期化
		initializeWindow();
		initializeVulkan();

		// 通常処理
		mainloop();

		// 後片付け
		finalizeVulkan();
		finalizeWindow();
	}

	// 表示ウィンドウの設定
	void initializeWindow()
	{
		const int WIDTH = 800;
		const int HEIGHT = 600;

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window_ = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan　Application", nullptr, nullptr);
	}

	void finalizeWindow()
	{
		glfwDestroyWindow(window_);

		glfwTerminate();
	}

	// Vulkanの設定
	void initializeVulkan()
	{
	}

	void finalizeVulkan()
	{
	}

	// 通常の処理
	void mainloop()
	{
		while (!glfwWindowShouldClose(window_)) 
		{
			glfwPollEvents();
		}
	}
};
