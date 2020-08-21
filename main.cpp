#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <sstream>

#include "utilities/Texture.h"
#include "utilities/VertexBufferLayout.h"
#include "utilities/IndexBuffer.h"
#include "utilities/Shader.h"
#include "utilities/VertexArray.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 1080, "Hello World", NULL, NULL);

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
    	-0.5f, -0.5f, 0.0f, 0.0f,
    	0.5f, -0.5f, 1.0f, 0.0f,
    	0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    va.Bind();
    VertexBuffer vb(positions,4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.pushFloat(2);
    layout.pushFloat(2);
    va.addBuffer(vb,layout);

    IndexBuffer ib(indices,6);


    Shader shader("resources/shaders/Basic.vert","resources/shaders/Basic.frag");
    shader.Bind();
    Texture texture("resources/textures/dirt.png");
    shader.setUniform1i("u_Texture",0);
    // shader.setUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);
    texture.Bind();

    va.Unbind();
    shader.Unbind();
    vb.Unbind();
    ib.Unbind();


    Renderer renderer;

    float r = 0.0f;
    float increment = 0.01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        renderer.clear();

        shader.Bind();
        // shader.setUniform4f("u_Color",r,0.3f,0.8f,1.0f);

        renderer.draw(va,ib,shader);

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

    shader.Unbind();

    glfwTerminate();
    return 0;
}