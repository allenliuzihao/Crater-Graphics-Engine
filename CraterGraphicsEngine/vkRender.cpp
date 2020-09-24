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
    
}

void vkRender::draw(){
    VkApplicationInfo appInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = CG_vkRender::APP_NAME,
        .applicationVersion = CG_vkRender::APP_VERSION,
        .pEngineName = CG_vkRender::ENGINE_NAME,
        .engineVersion = CG_vkRender::ENGINE_VERSION,
        .apiVersion = CG_vkRender::API_VERSION
    };
    
    
    
}

void vkRender::createInstance(){
    
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

bool vkRender::checkExtensionSupport(const std::vector<const char*> &requiredExtensions) {
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
