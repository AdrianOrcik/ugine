#include "uepch.h"
#include "opengl_texture.h"

#include "stb_image.h"
#include "ugine/log.h"

#include <glad/glad.h>

//todo: fix bug with texture creating
//		currently last loaded texture is override other textures
Ugine::OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
	: width_(width), heigth_(height)
{
	internalFormat_ = GL_RGBA8;
	dataFormat_ = GL_RGBA;

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
	glTextureStorage2D(rendererID_, 1, internalFormat_, width_, heigth_);

	glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

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

	internalFormat_ = internalFormat;
	dataFormat_ = dataFormat;

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
	glTextureStorage2D(rendererID_, 1, internalFormat, width_, heigth_);

	glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// note: use for texture update
	glTexSubImage2D(rendererID_, 0, 0, 0, width_, heigth_, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Ugine::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &rendererID_);
}

void Ugine::OpenGLTexture2D::SetData(void * data, uint32_t size)
{
	uint32_t bpp = dataFormat_ == GL_RGBA ? 4 : 3;
	UE_CORE_ASSERT(size == width_ * heigth_ * bpp, "Data must be entire texture!");
	//glTextureSubImage2D(rendererID_, 0, 0, 0, width_, heigth_, dataFormat_, GL_UNSIGNED_BYTE, data);

	glTexImage2D(GL_TEXTURE_2D, 0, dataFormat_, width_, heigth_, 0, dataFormat_, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);
}

void Ugine::OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTexture(slot, rendererID_);
}
