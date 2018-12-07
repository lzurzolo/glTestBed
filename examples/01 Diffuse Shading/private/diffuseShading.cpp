#include "../public/diffuseShading.h"

diffuseShading::diffuseShading()
{
    viewPosition = glm::vec3(0.0f, 0.0f, 2.0f);
    viewFront = glm::vec3(0.0f, 0.0f, -1.0f);
    viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void diffuseShading::loadModel()
{
    std::string modelPath = "../assets/models/sphere/sphere.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if(!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, modelPath.c_str()))
    { 
        std::cerr << err << std::endl;
        exit(EXIT_FAILURE);
    }

    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            Vertex vertex = {};

            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.normal = {
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }

    // TODO: handle materials

    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);
    glCreateBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);
}

void diffuseShading::updateUniforms()
{
    shaders["diffuse_shading"]->use();

    shaders["diffuse_shading"]->setVec4("LightPosition", glm::vec4(sin((float)glfwGetTime()), 0.0f, 0.0f, 1.0f));
    shaders["diffuse_shading"]->setVec3("Kd", glm::vec3(0.5f, 0.5f, 0.5f));
    shaders["diffuse_shading"]->setVec3("Ld", glm::vec3(1.0f, 1.0f, 1.0f));
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::lookAt(viewPosition, viewPosition + viewFront, viewUp);
    glm::mat4 projection = glm::perspective(90.0f, 1280.0f/720.0f, 0.1f, 100.0f);
    shaders["diffuse_shading"]->setMat4("Projection", projection);

    glm::mat4 modelView = view * model;
    shaders["diffuse_shading"]->setMat4("ModelView", modelView);

    glm::mat3 normal = glm::transpose(glm::inverse(modelView));
    shaders["diffuse_shading"]->setMat3("Normal", normal);

    glm::mat4 modelViewProjection = projection * view * model;
    shaders["diffuse_shading"]->setMat4("ModelViewProjection", modelViewProjection);

    shaders["diffuse_shading_light"]->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(sin((float)glfwGetTime()), 0.0f, 0.0f));
    modelViewProjection = projection * view * model;
    shaders["diffuse_shading_light"]->setMat4("ModelViewProjection", modelViewProjection);
}
void diffuseShading::draw()
{
    shaders["diffuse_shading"]->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    shaders["diffuse_shading_light"]->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

int main(int argc, char const *argv[])
{
    diffuseShading* example = new diffuseShading();
    example->windowSetup(1280, 720, "Diffuse Shading");
    example->glSetup();
    example->loadModel();
    example->shaderSetup("diffuse_shading", "../shaders/diffuse_shading.vs", "../shaders/diffuse_shading.fs");
    example->shaderSetup("diffuse_shading_light", "../shaders/diffuse_shading_light.vs", "../shaders/diffuse_shading_light.fs" );    
    example->renderLoop();

    return 0;
}