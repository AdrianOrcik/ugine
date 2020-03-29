#include "uepch.h"
#include "opengl_shader.h"

#include "ugine/log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ugine 
{
	Ugine::OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string fragmentSrc)
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
		rendererID_ = glCreateProgram();
		GLuint program = rendererID_;

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

	Ugine::OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererID_);
	}

	void Ugine::OpenGLShader::Bind() const
	{
		glUseProgram(rendererID_);
	}

	void Ugine::OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void Ugine::OpenGLShader::SetUniformInt(const std::string & name, int value)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform1i(location, value);
	}

	void Ugine::OpenGLShader::SetUniformFloat(const std::string & name, float value)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform1f(location, value);
	}

	void Ugine::OpenGLShader::SetUniformFloat2(const std::string & name, const glm::vec2 & value)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void Ugine::OpenGLShader::SetUniformFloat3(const std::string & name, const glm::vec3 & value)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Ugine::OpenGLShader::SetUniformFloat4(const std::string & name, const glm::vec4 & value)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Ugine::OpenGLShader::SetUniformMat3(const std::string & name, const glm::mat3 & matrix)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Ugine::OpenGLShader::SetUniformMat4(const std::string & name, const glm::mat4 & matrix)
	{
		GLint location = glGetUniformLocation(rendererID_, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
