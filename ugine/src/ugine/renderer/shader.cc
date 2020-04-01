#include "uepch.h"
#include "shader.h"

#include "ugine/log.h"
#include "renderer.h"
#include "platform/opengl/opengl_shader.h"

namespace Ugine
{
	std::shared_ptr<Shader> Shader::Create(const std::string & filePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:  UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string & name, const std::shared_ptr<Shader>& shader)
	{
		UE_CORE_ASSERT(!IsExist(name), "Shader already exists!");
		shaders_[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string & filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string & name, const std::string & filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string & name)
	{
		UE_CORE_ASSERT(IsExist(name), "Shader not found!");
		return shaders_[name];
	}

	bool ShaderLibrary::IsExist(const std::string & name) const
	{
		return shaders_.find(name) != shaders_.end();
	}
}