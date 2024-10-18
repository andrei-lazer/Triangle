#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> indices,
        std::vector<Texture> textures) {
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex),
            (void *)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex),
            (void *)(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex),
            (void *)(9 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera) {
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (int i = 0; i < textures.size(); i++) {
        std::string numStr;
        std::string type = textures[i].type;

        if (type == "diffuse") {
            numStr = std::to_string(numDiffuse++);
        } else if (type == "specular") {
            numStr = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + numStr).c_str(), i);
        textures[i].Bind();
    }

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x,
            camera.position.y, camera.position.z);
    camera.exportMatrix(shader, "camMatrix");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

