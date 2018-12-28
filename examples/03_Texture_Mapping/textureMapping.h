#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../../src/public/glTestBedBase.h"
#include "../../include/tiny_obj_loader.h"
#include "../../include/stb_image.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

class textureMapping : public glTestBedBase
{
public:
    textureMapping();
    ~textureMapping() {}

    /**
     * @brief Loads model data from file and packs into VBO/VAO
     */
    void loadModel();

    /**
     * @brief Loads texture data from file and pack into buffer object
     */ 
    void loadTexture();

    /**
     * @brief Sets uniform variables for an attached shader
     */
    void updateUniforms(int index);

    /**
     * @brief Draws geometry
     */
    void draw();

private:
    glm::vec3 viewPosition;         //!< World space position of camera
    glm::vec3 viewFront;            //!< World space target of camera
    glm::vec3 viewUp;               //!< Camera up vector

    unsigned int VBO;               //!< A vertex buffer object
    unsigned int VAO;               //!< A vertex array object
    unsigned int EBO;               //!< An element array buffer object
    unsigned int textureID;
    
    std::vector<Vertex> vertices;   //!< Geometry vertex data
    std::vector<uint32_t> indices;  //!< Geometry index data
    stbi_uc* pixels;
    
    // Uniforms
    glm::mat4 modelViewProjection;
};