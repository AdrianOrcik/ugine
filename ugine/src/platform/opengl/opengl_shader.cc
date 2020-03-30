#include "uepch.h"
#include "opengl_shader.h"

#include "ugine/log.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ugine 
{
	static unsigned int ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		UE_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	Ugine::OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string source = ReadFile(filePath);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);
	}

	Ugine::OpenGLShader::OpenGLShader(const std::string & vertexSrc, const std::string fragmentSrc)
	{
		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	Ugine::OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererID_);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string result;
		// todo: check this
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			UE_CORE_ERROR("Could not open file '{0}'", filePath);
		}

		return result;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::PreProcess(const std::string & source)
	{
		std::unordered_map<unsigned int, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			UE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			UE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source .substr(nextLinePos, 
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<unsigned int, std::string>& shaderSource)
	{
		GLuint program = glCreateProgram();
		std::vector<unsigned int> glShaderIds(shaderSource.size());
		for (auto& kv : shaderSource)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLenum shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);
			
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				UE_CORE_ERROR("{0}", infoLog.data());
				UE_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIds.push_back(shader);
		}

		rendererID_ = program;
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIds)
				glDeleteShader(id);


			UE_CORE_ERROR("{0}", infoLog.data());
			UE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIds)
			glDetachShader(program, id);

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
