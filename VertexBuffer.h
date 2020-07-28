class VertexBuffer {
	private:
		unsigned int m_RendererID;
		unsigned int m_Size;
	public:
		VertexBuffer(const void* data,unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		inline unsigned int getSize() const { return m_Size;}
};