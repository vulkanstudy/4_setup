#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

// Debug フラグ
#ifdef NDEBUG
// Vulkan は、高速化のために常にエラーチェックをするわけではない。
// といっても、何も表示されないとデバッグが困難なので、
// 開発中に使うものとして、エラーチェックを行う層(Layer)に置き換えられるようにしている
// この、エラーチェック用のシステムを挟むのが、validation Layer
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class MyApplication
{
private:
	constexpr static char APP_NAME[] = "Vulkan Application";

	const static std::vector<char*> validationLayers;

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

		// GLFW が要求するvalkanの拡張機能を取得して、初期化データに追加
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		// 検証レイヤーの有効化
		if (enableValidationLayers) 
		{
			static const std::vector<const char*> validationLayers = {
				"VK_LAYER_KHRONOS_validation"
			};

			// 検証レイヤーの確認
			if (!checkValidationLayerSupport(validationLayers)) {
				throw std::runtime_error("validation layers requested, but not available!");
			}

			// インスタンスへの設定
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}

		// インスタンスの生成
		if (vkCreateInstance(&createInfo, nullptr, dest) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	// 検証レイヤーに対応しているか確認
	static bool checkValidationLayerSupport(const std::vector<const char*> &validationLayers)
	{
		// レイヤー数の取得
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		// レイヤーのプロパティを取得
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		// 全てのレイヤーが検証レイヤーに対応しているか確認
		for (const char* layerName : validationLayers) {
			// レイヤーが検証レイヤーのどれかを持っているか確認
			auto has_prperty = [layerName, availableLayers](const char* layerName, const auto &availableLayers) {
				for (const auto& layerProperties : availableLayers) {
					if (strcmp(layerName, layerProperties.layerName) == 0) {return true;}
				}
				return false;
			};
			// どこかのレイヤーがvalidationLayersのレイヤーに対応してなければダメ
			if (has_prperty(layerName, availableLayers)) { return false; }
		}

		return true;
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
