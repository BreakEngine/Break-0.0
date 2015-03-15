#pragma once
namespace Break{
	namespace GXWrapper{
		class VertexElement{
		public:
			//element start offset
			unsigned int _offset;
			//element size in bytes
			unsigned int _size;
			//element component count
			unsigned int _components;

			VertexElement(int offset, int size, int components);
			VertexElement(const VertexElement& val);
			~VertexElement();
		};
	}
}