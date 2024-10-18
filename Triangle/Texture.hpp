#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.hpp"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* filePath, const char* texType, GLenum slot, GLenum colorFormat, GLenum pixelType);

	void Bind();
	void Unbind();
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Delete();
};

#endif // !TEXTURE_CLASS_H
