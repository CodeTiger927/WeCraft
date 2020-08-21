#include "Renderer.h"

#include "Shader.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>


Shader::Shader(const std::string& filePathV,const std::string& filePathF): m_filePathV(filePathV),m_filePathF(filePathF),m_RendererID(0) {
	ShaderProgramSource source = parseShaders();
    m_RendererID = CreateShader(source.vertexSource,source.fragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
}

unsigned int Shader::CompileShader(unsigned int type,const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if(!result) {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


std::string Shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream src;
    while(getline(stream,line)) {
         src << line << '\n';
    }

    return src.str();
}

ShaderProgramSource Shader::parseShaders() {
    return ShaderProgramSource{parseShader(m_filePathV),parseShader(m_filePathF)};
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vS = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fS = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vS);
    glAttachShader(program,fS);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vS);
    glDeleteShader(fS);

    return program;
}

void Shader::Bind() const {
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
	GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name,float v0,float v1,float v2,float v3) {
	GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3))
}

void Shader::setUniform1i(const std::string& name,int v0) {
    GLCall(glUniform1i(GetUniformLocation(name),v0));
}

void Shader::setUniform1f(const std::string& name,float v0) {
    GLCall(glUniform1f(GetUniformLocation(name),v0));
}

int Shader::GetUniformLocation(const std::string& name) {
	if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
	if(location == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}

	m_UniformLocationCache[name] = location; 
	
	return location;
}