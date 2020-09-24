#include "utilities.hpp"

// application
const char* CG_vkRender::APP_NAME = "Crater Graphics Renderer";
const uint32_t CG_vkRender::APP_VERSION = VK_MAKE_VERSION(0, 1, 0);
const char* CG_vkRender::ENGINE_NAME = "Crater Graphics Engine";
const uint32_t CG_vkRender::ENGINE_VERSION = VK_MAKE_VERSION(0, 1, 0);
const uint32_t CG_vkRender::API_VERSION = VK_API_VERSION_1_2;

// validation layer
#ifdef NDEBUG
    const bool CG_vkRender::enableValidationLayers = false;
#else
    const bool CG_vkRender::enableValidationLayers = true;
#endif


// window constants
const uint32_t CG_window::WINDOW_WIDTH = 1503;
const uint32_t CG_window::WINDOW_HEIGHT = 903;
const char* CG_window::WINDOW_NAME = "Crater Engine";
