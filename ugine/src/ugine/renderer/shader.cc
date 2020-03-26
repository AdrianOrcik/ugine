#include "uepch.h"
#include "shader.h"

#include "ugine/log.h"
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Ugine
{
	//todo: refactor shader class
	Shader::Shader(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		// create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertexSource = vertexSrc.c_str();

		glShaderSource(vertexShader, 1, &vertexSource, 0);
		glCompileShader(vertexShader);

		GLint vertexShaderIsCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderIsCompiled);
		if (vertexShaderIsCompiled == GL_FALSE)
		{
			GLint maxLength;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			CORE_LOG_ERROR("{0}", infoLog.data());
			UE_CORE_ASSERT(false, "VertexShader compilation failed!");
			return;
		}

		// create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentSource = fragmentSrc.c_str();

		glShaderSource(fragmentShader, 1, &fragmentSource, 0);
		glCompileShader(fragmentShader);

		GLint fragmentShaderIsCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderIsCompiled);
		if (fragmentShaderIsCompiled == GL_FALSE)
		{
			GLint maxLength;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			CORE_LOG_ERROR("{0}", infoLog.data());
			UE_CORE_ASSERT(false, "FragmentShader compilation failed!");
			return;
		}

		// bind vertex & fragment shaders into shader program
		renderID_ = glCreateProgram();
		GLuint program = renderID_;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LOG_ERROR("{0}", infoLog.data());
			UE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(renderID_);
	}
	
	void Shader::Bind() const
	{
		glUseProgram(renderID_);
	}
	
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
	void Shader::SetUniformMat4(const std::string & name, const glm::mat4 & matrix)
	{
		GLint location = glGetUniformLocation(renderID_, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}
}