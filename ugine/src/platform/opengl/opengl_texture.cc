#include "uepch.h"
#include "opengl_texture.h"

#include "stb_image.h"

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

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);

	glTextureStorage2D(rendererID_, 1, GL_RGB8, width_, heigth_);

	glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(rendererID_, 0, 0, 0, width_, heigth_, GL_RGB, GL_UNSIGNED_BYTE, data);

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
