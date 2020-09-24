#ifndef vkRender_hpp
#define vkRender_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "utilities.hpp"

class vkRender{
public:
    vkRender(GLFWwindow* window);
    ~vkRender();
    
    void draw();
    
private:
    VkInstance          instance;
    
    VkDevice            logicalDevice;
    VkPhysicalDevice    physicalDevice;
    
    VkSurfaceKHR        surface;
    
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapchainFramebuffers;
        
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    
    
    void createInstance();
    
    
    std::vector<const char*> getRequiredExtensions();

    
    bool checkExtensionsSupport(const std::vector<const char*> &requiredExtensions);
    bool checkValidationLayerSupport();
    
    // debuggers
    VkDebugUtilsMessengerEXT debugMessenger;
    void setUpDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugMessageFunc(VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
                                                           VkDebugUtilsMessageTypeFlagsEXT              messageTypes,
                                                           VkDebugUtilsMessengerCallbackDataEXT const * pCallbackData,
                                                           void* pUserData);
};

#endif /* vkRender_hpp */
