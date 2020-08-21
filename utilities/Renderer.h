#include <GL/glew.h>

class VertexArray;
class IndexBuffer;
class Shader;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))


void GLClearError();
bool GLLogCall(const char* function,const char* file,int line);

class Renderer {
	public:
		Renderer();
		~Renderer();
		void draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;
		void clear() const;
	private:

};