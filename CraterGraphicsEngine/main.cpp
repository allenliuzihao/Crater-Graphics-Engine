#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include "utilities.hpp"
#include "vkRender.hpp"

vkRender* render = nullptr;

int main(int argc, const char * argv[]) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(CG_window::WINDOW_WIDTH, CG_window::WINDOW_HEIGHT, CG_window::WINDOW_NAME, nullptr, nullptr);

    // init render
    render = new vkRender(window);
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    delete render;

    glfwDestroyWindow(window);

    glfwTerminate();

    
    return 0;
}
