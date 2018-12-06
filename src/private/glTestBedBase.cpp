#include "../public/glTestBedBase.h"

void glTestBedBase::glSetup()
{
    if(gl3wInit())
    {
        std::cerr << "Failed to initialize OpenGL." << std::endl;
        exit(EXIT_FAILURE);
    }

    if(!gl3wIsSupported(4, 5))
    {
        std::cerr << "OpenGL 4.5 is not supported." << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
}

void glTestBedBase::windowSetup(int windowX, int windowY, std::string windowTitle)
{
    if(glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Failed to initialize GLFW3." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowX, windowY, windowTitle.c_str(), nullptr, nullptr);
    if(!window)
    {
        std::cerr << "Failed to create window." << std::endl;
    }
    glfwMakeContextCurrent(window);
}

void glTestBedBase::renderLoop()
{
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

int main(int argc, char const *argv[])
{
    glTestBedBase* example = new glTestBedBase();
    example->windowSetup(1280, 720, "Testing");
    example->glSetup();
    example->renderLoop();
    
    return 0;
}