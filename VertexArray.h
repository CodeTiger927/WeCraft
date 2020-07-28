#include "VertexBufferLayout.h"

class VertexArray {
	private:
		unsigned int m_RendererID;

	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vb,const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
};