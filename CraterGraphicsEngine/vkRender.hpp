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
    
    
    bool checkExtensionSupport(const std::vector<const char*> &requiredExtensions);
    std::vector<const char*> getRequiredExtensions();
};

#endif /* vkRender_hpp */
