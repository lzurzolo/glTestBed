#include "phongShading.h"

phongShading::phongShading()
{
    viewPosition = glm::vec3(0.0f, 8.0f, 7.0f);
    viewFront = glm::vec3(0.0f, -0.5f, -0.5f);
    viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
    numberOfObjects = 3;
    objectPositions.resize(numberOfObjects);
    objectKds.resize(numberOfObjects);
    objectKas.resize(numberOfObjects);
    objectKss.resize(numberOfObjects);
    objectShininess.resize(numberOfObjects);

    objectPositions[0] = glm::vec3( 0.0f,  0.0f, 0.0f);
    objectPositions[1] = glm::vec3( 5.0f,  0.0f, 0.0f);
    objectPositions[2] = glm::vec3(-5.0f,  0.0f, 0.0f);

    objectKas[0] = glm::vec3(0.8f, 0.8f, 0.8f);
    objectKas[1] = glm::vec3(0.2f, 0.5f, 0.9f);
    objectKas[2] = glm::vec3(0.8f, 0.3f, 0.4f);

    objectKds[0] = glm::vec3(0.3f, 0.5f, 0.7f);
    objectKds[1] = glm::vec3(0.5f, 0.6f, 0.2f);
    objectKds[2] = glm::vec3(0.6f, 0.3f, 0.6f);

    objectKss[0] = glm::vec3(0.4f, 0.5f, 0.0f);
    objectKss[1] = glm::vec3(0.8f, 0.8f, 0.2f);
    objectKss[2] = glm::vec3(0.3f, 0.9f, 0.2f);

    objectShininess[0] = 50;
    objectShininess[1] = 10;
    objectShininess[2] = 120;
}

void phongShading::loadModel()
{
    std::string modelPath = "../assets/models/teapot/teapot.obj";
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

void phongShading::updateUniforms(int index)
{
    shaders["phong_shading"]->use();

    shaders["phong_shading"]->setVec4("LightPosition", glm::vec4(20.0f, 20.0f, 0.0f, 1.0f));
    shaders["phong_shading"]->setVec3("Ld", glm::vec3(1.0f, 0.0f, 1.0f));
    shaders["phong_shading"]->setVec3("La", glm::vec3(0.5f, 0.9f, 0.5f));
    shaders["phong_shading"]->setVec3("Ls", glm::vec3(0.5f, 0.0f, 1.0f));

    
    shaders["phong_shading"]->setVec3("Kd", objectKds[index]);
    shaders["phong_shading"]->setVec3("Ka", objectKas[index]);
    shaders["phong_shading"]->setVec3("Ks", objectKss[index]);
    shaders["phong_shading"]->setFloat("Shininess", objectShininess[index]);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, objectPositions[index]);
    model = glm::rotate(model, (float)glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(viewPosition, viewPosition + viewFront, viewUp);
    glm::mat4 projection = glm::perspective(45.0f, 1280.0f/720.0f, 0.1f, 100.0f);
    shaders["phong_shading"]->setMat4("Projection", projection);

    glm::mat4 modelView = view * model;
    shaders["phong_shading"]->setMat4("ModelView", modelView);

    glm::mat3 normal = glm::transpose(glm::inverse(modelView));
    shaders["phong_shading"]->setMat3("Normal", normal);

    glm::mat4 modelViewProjection = projection * view * model;
    shaders["phong_shading"]->setMat4("ModelViewProjection", modelViewProjection);
}

void phongShading::draw()
{
    shaders["phong_shading"]->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

int main(int argc, char const *argv[])
{
    phongShading* example = new phongShading();
    example->windowSetup(1280, 720, "Phong Shading");
    example->glSetup();
    example->loadModel();
    example->shaderSetup("phong_shading", "../shaders/phong_shading.vs", "../shaders/phong_shading.fs");
    example->renderLoop(); 
    return 0;
}
