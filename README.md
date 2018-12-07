# glTestBed
This is a series of Computer Graphics examples demonstrated with the OpenGL rendering API.

## Requirements
An OpenGL 4.x capable graphics card<br />
[glfw](https://github.com/glfw/glfw)<br />
[glm](https://github.com/g-truc/glm)<br />
[gl3w](https://github.com/skaslev/gl3w)<br />

## Included External Libs
[tinyobjloader](https://github.com/syoyo/tinyobjloader) Courtesy of syoyo

## Instructions
Execute `make` in the desired example directory. Binary will be written to the bin directory.

# Examples
## 01. Diffuse Lighting
Demonstrates the diffuse lighting equation, *L = K<sub>d</sub>L<sub>d</sub>(s·n)*, using per-vertex lighting<br />
![Example](https://github.com/lzurzolo/glTestBed/blob/master/examples/01_Diffuse_Shading/example_01.png)

## 02. Phong Shading
Demonstrates the Phong reflection model, *I<sub></sub> = I<sub>a</sub> + I<sub>d</sub> + I<sub>s</sub>* utlizing 3 instances of the same Utah teapot with different material properties using per-vertex lighting. This showcases how the different materials respond when exposed to the same light source<br />
![Example](https://github.com/lzurzolo/glTestBed/blob/master/examples/02_Phong_Shading/example_02.png)
