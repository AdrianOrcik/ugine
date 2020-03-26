#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Ugine
{

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		unsigned int renderID_;
	};

}