#include "ShaderLoad.h"

ShaderLoad::ShaderLoad(const char* vertexShader, const char* fragmentShader)
{
	std::string vertexCore, fragmentCode;
	std::ifstream vFile, fFile;

	try
	{
		vFile.open(vertexShader);
		fFile.open(fragmentShader);

		std::stringstream vStream, fStream;
		vStream << vFile.rdbuf();
		fStream << fFile.rdbuf();

		vFile.close();
		fFile.close();

		vertexCore = vStream.str();
		fragmentCode = fStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR OPEN SHADERS" << std::endl;
	}

	const GLchar* vSh = vertexCore.c_str();
	const GLchar* fSh = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vSh, NULL);
	glShaderSource(fragment, 1, &fSh, NULL);

	glCompileShader(vertex);
	glCompileShader(fragment);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	std::cout << "shader load" << std::endl;
}

void ShaderLoad::Use()
{
	glUseProgram(program);
}

GLuint ShaderLoad::getProgram()
{
	return program;
}
