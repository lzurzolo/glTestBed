#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../src/public/glTestBedBase.h"
#include "../../include/tiny_obj_loader.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

class diffuseShading : public glTestBedBase
{
public:
    diffuseShading();
    ~diffuseShading() {}

    /**
     * @brief Loads model data from file and packs into VBO/VAO
     */
    void loadModel();

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

    std::vector<Vertex> vertices;   //!< Geometry vertex data
    std::vector<uint32_t> indices;  //!< Geometry index data

    // Uniforms
    glm::vec4 lightPosition;        //!< Position of a single light
    glm::vec3 kd;                   //!< Surface diffuse reflectivity
    glm::vec3 ld;                   //!< Diffuse light intensity
    glm::mat4 modelView;            //!< Model View matrix
    glm::mat4 modelViewProjection;  //!< Model View Projection matrix
    glm::mat4 normal;               //!< Normal matrix
    glm::mat4 projection;           //!< Projection matrix
};