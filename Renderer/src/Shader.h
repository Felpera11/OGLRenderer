#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	const std::string VertexSource;
	const std::string FragmentSource;
};


class Shader
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_LocationCache;

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int value);

private:
	int GetUniformLocation(const std::string& name);
};

//static functions


//Takes a shader source code file and returns it in a struct
static ShaderProgramSource ParseShader(const std::string& filepath);

//Takes a shader type and a shader source code and returns the id of the compiled shader
static unsigned int CompileShader(unsigned int type, const std::string& source);

//Compiles a shader program using the provided source code
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

//Compiles a shader program using the provided source code
static unsigned int CreateShader(ShaderProgramSource source);