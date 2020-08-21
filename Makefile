
WeCraft: main.o IndexBuffer.o VertexBuffer.o Renderer.o VertexArray.o Shader.o Texture.o
	g++ main.o IndexBuffer.o VertexBuffer.o Renderer.o VertexArray.o Shader.o Texture.o -o WeCraft -lglfw3 -lopengl32 -lglew32 -lgdi32

main.o: main.cpp
	g++ -c main.cpp

IndexBuffer.o: utilities/IndexBuffer.cpp
	g++ -c utilities/IndexBuffer.cpp

VertexBuffer.o: utilities/VertexBuffer.cpp
	g++ -c utilities/VertexBuffer.cpp

Renderer.o: utilities/Renderer.cpp
	g++ -c utilities/Renderer.cpp

VertexArray.o: utilities/VertexArray.cpp
	g++ -c utilities/VertexArray.cpp

Shader.o: utilities/Shader.cpp
	g++ -c utilities/Shader.cpp

Texture.o: utilities/Texture.cpp
	g++ -c utilities/Texture.cpp

clean:
	del *.o WeCraft.exe