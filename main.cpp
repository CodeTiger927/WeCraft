#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static std::string parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream src;
    while(getline(stream,line)) {
         src << line << '\n';
    }

    return src.str();
}

static ShaderProgramSource parseShaders(const std::string& filepathV,const std::string& filepathF) {
    return ShaderProgramSource{parseShader(filepathV),parseShader(filepathF)};
}

static unsigned int CompileShader(unsigned int type,const std::string& source) {
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
    	-0.5f, -0.5f,
    	-0.5f, 0.5f,
    	0.5f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    va.Bind();
    VertexBuffer vb(positions,2 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.pushFloat(2);
    va.addBuffer(vb,layout);

    IndexBuffer ib(indices,6);


    ShaderProgramSource source = parseShaders("resources/shaders/Basic.vert","resources/shaders/Basic.frag");

    unsigned int shader = CreateShader(source.vertexSource,source.fragmentSource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader,"u_Color");

    glUniform4f(location,0.8f,0.3f,0.8f,1.0f);

    float r = 0.0f;
    float increment = 0.01f;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shader);
        glUniform4f(location,r,0.3f,0.8f,1.0f);

        va.Bind();
        vb.Bind();
        ib.Bind();

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

        r += increment;

        if(r > 1.0f) {
            increment = -0.01f;
        }else if(r < 0.0f) {
            increment = 0.01f;
        }
    
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}