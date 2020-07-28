#include <vector>

struct VertexBufferElement {
	unsigned int count;
	unsigned int type;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch(type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
	private:
		unsigned int m_Stride;
		std::vector<VertexBufferElement> m_Elements;

	public:
		VertexBufferLayout(): m_Stride(0) {}
		~VertexBufferLayout() {}

		void pushFloat(unsigned int count) {
			m_Elements.push_back({count,GL_FLOAT,GL_FALSE});
			m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
		}

		void pushUint(unsigned int count) {
			m_Elements.push_back({count,GL_UNSIGNED_INT,GL_FALSE});
			m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
		}

		void pushUchar(unsigned int count) {
			m_Elements.push_back({count,GL_UNSIGNED_BYTE,GL_TRUE});
			m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement> getElements() const& {return m_Elements;}
		inline unsigned int getStride() const {return m_Stride;}
};