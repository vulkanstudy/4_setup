#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class MyApplication
{
private:
	constexpr static char APP_NAME[] = "Vulkan Application";

	GLFWwindow* window_;
	VkInstance instance_;
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

		window_ = glfwCreateWindow(WIDTH, HEIGHT, APP_NAME, nullptr, nullptr);
	}

	void finalizeWindow()
	{
		glfwDestroyWindow(window_);

		glfwTerminate();
	}

	// Vulkanの設定
	void initializeVulkan()
	{
		createInstance(&instance_);
	}

	void finalizeVulkan()
	{
		vkDestroyInstance(instance_, nullptr);
	}

private:
	static void createInstance(VkInstance *dest)
	{
		VkApplicationInfo appInfo = {};// アプケーション情報を定めるための構造体
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;			// 構造体の種類
		appInfo.pApplicationName = APP_NAME;						// アプリケーション名
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);		// 開発者が決めるバージョン番号
		appInfo.pEngineName = "My Engine";							// ゲームエンジン名
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);			// ゲームエンジンのバージョン
		appInfo.apiVersion = VK_API_VERSION_1_0;					// 使用するAPIのバージョン

		VkInstanceCreateInfo createInfo = {};// 新しく作られるインスタンスの設定の構造体
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;	// 構造体の種類
		createInfo.pApplicationInfo = &appInfo;						// VkApplicationInfoの情報
		createInfo.enabledLayerCount = 0;							// 後から説明：ひとまず0

		// GLFW が要求するvalkanの拡張機能を取得して、初期化データに追加
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		// インスタンスの生成
		if (vkCreateInstance(&createInfo, nullptr, dest) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

public:

	// 通常の処理
	void mainloop()
	{
		while (!glfwWindowShouldClose(window_)) 
		{
			glfwPollEvents();
		}
	}
};
