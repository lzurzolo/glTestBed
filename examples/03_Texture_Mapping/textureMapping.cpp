#include "textureMapping.h"

textureMapping::textureMapping()
{
    viewPosition = glm::vec3(0.0f, 6.0f, 5.0f);
    viewFront = glm::vec3(0.0f, -0.5f, -0.5f);
    viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
    numberOfObjects = 1;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 view = glm::lookAt(viewPosition, viewPosition + viewFront, viewUp);
    glm::mat4 projection = glm::perspective(45.0f, 1280.0f/720.0f, 0.1f, 100.0f);
    modelViewProjection = projection * view * model;
}

void textureMapping::loadModel()
{
    std::string modelPath = "../assets/models/brick/brick.obj";
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

            vertex.uv = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
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

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glBindVertexArray(0);
}

void textureMapping::loadTexture()
{
    int x, y, channels;
    pixels = stbi_load(
        "../assets/textures/brick.jpg", 
        &x, 
        &y,
        &channels,
        0);

    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(pixels)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to create texture from image" << std::endl;
        exit(EXIT_FAILURE);
    }
    stbi_image_free(pixels);
}

void textureMapping::updateUniforms(int index)
{
    shaders["texture_mapping"]->use();
    shaders["texture_mapping"]->setMat4("ModelViewProjection", modelViewProjection);
}

void textureMapping::draw()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    shaders["texture_mapping"]->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


int main(int argc, char const *argv[])
{
    textureMapping* example = new textureMapping();
    example->windowSetup(1280, 720, "Texture Mapping");
    example->glSetup();
    example->loadModel();
    example->loadTexture();
    example->shaderSetup("texture_mapping", "../shaders/texture_mapping.vs", "../shaders/texture_mapping.fs");
    example->renderLoop(); 
    return 0;
}