#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Shader.h"


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

    /**
     * @brief Loads shaders from files, compiles, links and attaches them to shader program
     * @parameter Path to the vertex shader
     * @parameter Path to the fragment shader
     * @parameter Path to the geometry shader
     */
    void shaderSetup(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

private:
    GLFWwindow* window;
    Shader* shader;
};
