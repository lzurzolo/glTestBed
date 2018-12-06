#include "../public/flatShading.h"


int main(int argc, char const *argv[])
{
    flatShading* example = new flatShading();
    example->windowSetup(1280, 720, "Flat Shading");
    example->glSetup();
    example->renderLoop();
    
    return 0;
}