#include "Shader.h"
#include <GL/glew.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader(const std::string& filename)
{
	ShaderProgramSource source = ParseShader(filename);
	m_RendererID = CreateShader(source);
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int location = GetUniformLocation(name);
	if (location == -1)
	{
		return;
	}
	glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	int location = GetUniformLocation(name);
	if (location == -1)
	{
		return;
	}		
	glUniform1i(location, value);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_LocationCache.find(name) != m_LocationCache.end())
	{
		return m_LocationCache[name];
	}

    int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
	{
		std::cout << "[Invalid Uniform Location]" << std::endl;
	}
	else
	{
		m_LocationCache[name] = location;
		return location;
	}
}




static ShaderProgramSource ParseShader(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;

	std::ifstream stream(filepath);
	std::string line;

	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[int(type)] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

//Takes a shader type and a shader source code and returns the id of the compiled shader
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);//after the shader is linked we can delete the itermediate objects
	glDeleteShader(fs);

	return program;
}

static unsigned int CreateShader(ShaderProgramSource source)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);//after the shader is linked we can delete the intermediate objects
	glDeleteShader(fs);

	return program;
}
