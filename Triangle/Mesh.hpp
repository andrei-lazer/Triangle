#ifndef MESH_H
#include <string.h>
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include <vector>

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>indices, std::vector<Texture> textures);

	void Draw(Shader& shader, Camera& camera);

};
#endif // !MESH_H
