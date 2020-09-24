#ifndef utilities_hpp
#define utilities_hpp

#pragma once

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>

namespace CG_vkRender {
    extern const char* APP_NAME;
    extern const uint32_t APP_VERSION;
    extern const char* ENGINE_NAME;
    extern const uint32_t ENGINE_VERSION;
    extern const uint32_t API_VERSION;

    extern const bool enableValidationLayers;
    extern const std::vector<const char*> validationLayers;
};

namespace CG_window {
    extern const uint32_t WINDOW_WIDTH;
    extern const uint32_t WINDOW_HEIGHT;
    extern const char* WINDOW_NAME;
}


#endif /* utilities_hpp */
