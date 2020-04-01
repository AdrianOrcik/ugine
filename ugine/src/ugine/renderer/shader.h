#pragma once

#include <string>
#include <unordered_map>

namespace Ugine
{

	// todo: cant replace std::shared_ptr<Shader> to Ref<Shader>
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& filePath);
		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		void Add(const std::shared_ptr<Shader>& shader);
		std::shared_ptr<Shader> Load(const std::string& filePath);
		std::shared_ptr<Shader> Load(const std::string& name, const std::string& filePath);

		std::shared_ptr<Shader> Get(const std::string& name);

		bool IsExist(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;
	};

}