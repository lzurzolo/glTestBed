#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <map>

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
     * @brief Updates uniform buffers
     */
    virtual void updateUniforms() = 0; 

    /**
     * @brief Begin GL Frame
     */
    void startFrame();

    /**
     * @brief End GL Frame
     */
    void endFrame();

    /**
     * @brief Draws geometry
     */
    virtual void draw() = 0;

    /**
     * @brief Begins the render loop
     */
    virtual void renderLoop();

    /**
     * @brief Loads shaders from files, compiles, links and attaches them to shader program
     * @parameter Path to the vertex shader
     * @parameter Path to the fragment shader
     * @parameter Path to the geometry shader
     */
    void shaderSetup(std::string shaderName, std::string vertexPath, std::string fragmentPath, std::string geometryPath = std::string());
    
    Shader* shader;     //!< A pointer to a shader program

    std::map<std::string, Shader*> shaders;
    float deltaTime;
    float lastFrame;

private:
    GLFWwindow* window; //!< A pointer to a GLFW window
};
