
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
	private:
		std::string m_filePathV;
		std::string m_filePathF;

		unsigned int m_RendererID;

		std::unordered_map<std::string,int> m_UniformLocationCache;

	public:
		Shader(const std::string& filepathV,const std::string& filepathF);
		~Shader();

		void Bind() const;
		void Unbind() const;


		// Set uniforms
		void setUniform1i(const std::string& name,int v0);
		void setUniform1f(const std::string& name,float v0);
		void setUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
		int GetUniformLocation(const std::string& name);
		unsigned int CompileShader(unsigned int type,const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		std::string parseShader(const std::string& filepath);
		ShaderProgramSource parseShaders();

};