#include "vkRender.hpp"

vkRender::vkRender(GLFWwindow* window) {
    try {
        createInstance();
    } catch (std::exception &err){
        std::cerr << "std::exception: " << err.what() << std::endl;
        exit(-1);
    } catch (...){
        std::cerr << "unknown error\n";
        exit(-1);
    }
}

vkRender::~vkRender(){
    vkDestroyInstance(instance, nullptr);
}

void vkRender::draw(){

}

void vkRender::createInstance(){
    VkApplicationInfo appInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = CG_vkRender::APP_NAME,
        .applicationVersion = CG_vkRender::APP_VERSION,
        .pEngineName = CG_vkRender::ENGINE_NAME,
        .engineVersion = CG_vkRender::ENGINE_VERSION,
        .apiVersion = CG_vkRender::API_VERSION
    };
    
    std::vector<const char*> requiredExtensions = getRequiredExtensions();
    if(!checkExtensionsSupport(requiredExtensions)){
        throw std::runtime_error("failed to create instance: not all requested extensions supported.");
    }
    
    if(CG_vkRender::enableValidationLayers && !checkValidationLayerSupport()){
        throw std::runtime_error("validation layers requested, but not available.");
    }
    
    VkInstanceCreateInfo instanceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size()),
        .ppEnabledExtensionNames = requiredExtensions.data()
    };
    
    if(CG_vkRender::enableValidationLayers){
        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(CG_vkRender::validationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = CG_vkRender::validationLayers.data();
        
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo{};
        populateDebugMessengerCreateInfo(debugUtilsCreateInfo);
        instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugUtilsCreateInfo;
    } else {
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.pNext = nullptr;
    }
    
    VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    if(result != VK_SUCCESS){
        throw std::runtime_error("failed to create vulkan instance.");
    }
}

std::vector<const char*> vkRender::getRequiredExtensions(){
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (CG_vkRender::enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

bool vkRender::checkExtensionsSupport(const std::vector<const char*> &requiredExtensions) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
    
    return std::all_of(requiredExtensions.begin(), requiredExtensions.end(), [&availableExtensions](const char* requiredExtension) {
        return std::find_if(availableExtensions.begin(), availableExtensions.end(), [&requiredExtension](VkExtensionProperties const & availableExtension){
            return strcmp(availableExtension.extensionName, requiredExtension) == 0;
        }) != availableExtensions.end();
    });
}

bool vkRender::checkValidationLayerSupport() { 
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    
    return std::all_of(CG_vkRender::validationLayers.begin(), CG_vkRender::validationLayers.end(), [&availableLayers](const char* requiredLayer) {
        return std::find_if(availableLayers.begin(), availableLayers.end(), [&requiredLayer](VkLayerProperties const & availableLayer){
            return strcmp(availableLayer.layerName, requiredLayer) == 0;
        }) != availableLayers.end();
    });
}


void vkRender::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo){
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugMessageFunc;
}

VKAPI_ATTR VkBool32 VKAPI_CALL vkRender::debugMessageFunc(VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
                                                          VkDebugUtilsMessageTypeFlagsEXT              messageTypes,
                                                          VkDebugUtilsMessengerCallbackDataEXT const * pCallbackData,
                                                          void* pUserData){
    std::cerr << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}
