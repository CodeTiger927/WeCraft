
WeCraft: main.o IndexBuffer.o VertexBuffer.o Renderer.o VertexArray.o
	g++ main.o IndexBuffer.o VertexBuffer.o Renderer.o VertexArray.o -o WeCraft -lglfw3 -lopengl32 -lglew32 -lgdi32

main.o: main.cpp
	g++ -c main.cpp

IndexBuffer.o: IndexBuffer.cpp
	g++ -c IndexBuffer.cpp

VertexBuffer.o: VertexBuffer.cpp
	g++ -c VertexBuffer.cpp

Renderer.o: Renderer.cpp
	g++ -c Renderer.cpp

VertexArray.o: VertexArray.cpp
	g++ -c VertexArray.cpp

clean:
	del *.o WeCraft.exe