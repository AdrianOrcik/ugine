#pragma once

#include "ugine/renderer/texture.h"

namespace Ugine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		// Inherited via Texture2D
		virtual uint32_t GetWidth() const override {return width_;}
		virtual uint32_t GetHeight() const override { return heigth_; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string path_;
		uint32_t width_, heigth_;
		uint32_t rendererID_;
	};
}