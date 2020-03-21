#pragma once

#include <string>

namespace Ugine
{

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int renderID_;
	};

}