#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"



Shader::Shader(const std::string& filepath) : m_Filepath(filepath) , m_RendererID(0)
{
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = createShader(source.VertexSource, source.FragmentSource);
	
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}


ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	std::string line;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)  //invalid string position
		{
			if (line.find("vertex") != std::string::npos)       //set mode to vertex
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)       //set mode to fragment
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); //or &source[0]   // pointer to the actual source character data
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error handling 
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result); //i for integer, v for vector
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));        //alocate size on stack DYNAMICALLY
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;

}
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);       //after successfully got the program, delete the shader
	glDeleteShader(fs);

	return program;
}

void Shader::bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1i(const std::string & name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_LocationCache.find(name) != m_LocationCache.end())
		return m_LocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());

	m_LocationCache[name] = location;
	return location;
}