#include "uepch.h"
#include "opengl_texture.h"

#include "stb_image.h"
#include "ugine/log.h"

#include <glad/glad.h>

Ugine::OpenGLTexture2D::OpenGLTexture2D(const std::string & path)
	:path_(path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	UE_CORE_ASSERT(data, "Failed to load image!");
	width_ = width;
	heigth_ = height;

	// todo: later do quick function
	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
	glTextureStorage2D(rendererID_, 1, internalFormat, width_, heigth_);

	glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// note: use for texture update
	//glTextureSubImage2D(rendererID_, 0, 0, 0, width_, heigth_, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Ugine::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &rendererID_);
}

void Ugine::OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTexture(slot, rendererID_);
}
