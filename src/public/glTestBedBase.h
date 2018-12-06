#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


class glTestBedBase
{
public:
    glTestBedBase() {}
    ~glTestBedBase() {}

    /**
     * @brief Sets up the window
     * @parameter windowX Horizontal size of the window
     * @parameter windowY Vertical size of the window
     * @parameter windowTitle Title of the window
     */
    void windowSetup(int windowX = 720, int windowY = 480, std::string windowTitle = "GL Default");

    /** 
     * @brief Sets up the OpenGL context
     */
    void glSetup();

    /**
     * @brief Begins the render loop
     */
    void renderLoop();

    //setup shaders

private:
    GLFWwindow* window;
};
