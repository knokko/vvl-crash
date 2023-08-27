#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
	const char* validationLayer = "VK_LAYER_KHRONOS_validation";

	VkInstanceCreateInfo ciInstance = { 0 };
	ciInstance.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ciInstance.enabledLayerCount = 1;
	ciInstance.ppEnabledLayerNames = &validationLayer;

	VkInstance instance;
	printf("instance result is %d\n", vkCreateInstance(&ciInstance, NULL, &instance));

	VkPhysicalDevice physicalDevice;
	uint32_t deviceCount = 1;
	printf("physical device result is %d\n", vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevice));

	VkDeviceCreateInfo ciDevice = { 0 };
	ciDevice.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	// This example doesn't even need a queue, but the spec demands that queueCreateInfoCount > 0
	float queuePriorities = 1.0;
	VkDeviceQueueCreateInfo ciQueue = { 0 };
	ciQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	ciQueue.queueCount = 1;
	ciQueue.pQueuePriorities = &queuePriorities;

	ciDevice.queueCreateInfoCount = 1;
	ciDevice.pQueueCreateInfos = &ciQueue;
	
	VkDevice device;
	printf("device result is %d\n", vkCreateDevice(physicalDevice, &ciDevice, NULL, &device));

	char* shaderFileName = "crash.tese.spv";

	FILE *shaderFile;
	shaderFile = fopen(shaderFileName, "rb");
	struct stat shaderFileStats;
	if (stat(shaderFileName, &shaderFileStats) == -1) {
		printf("failed to get shader file size\n");
		return -1;
	}
	char* shaderContent = malloc(shaderFileStats.st_size);
	fread(shaderContent, shaderFileStats.st_size, 1, shaderFile);
	fclose(shaderFile);

	VkShaderModuleCreateInfo ciShader = { 0 };
	ciShader.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ciShader.codeSize = shaderFileStats.st_size;
	ciShader.pCode = (uint32_t*) shaderContent;

	printf("code size is %ld and first code is %d and last code is %d\n", ciShader.codeSize, ciShader.pCode[0], ciShader.pCode[ciShader.codeSize / 4 - 1]);
	// Expecting code size is 1952 and first code is 119734787 and last code is 65592

	VkShaderModule shader;
	printf("shader result is %d\n", vkCreateShaderModule(device, &ciShader, NULL, &shader));
}

