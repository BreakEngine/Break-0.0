namespace Break{
	namespace GXWrapper{

		struct Primitive{

			enum Type
			{
				POINTS = 0,
				LINES = 1,
				LINE_STRIP = 2,
				LINE_LOOP = 3,
				TRIANGLES = 4,
				TRIANGLE_STRIP = 5,
				TRIANGLE_FAN = 6
			};

			enum Mode
			{
				NORMAL = 0,
				INDEXED = 1,
				NORMAL_INSTANCED = 2,
				INDEX_INSTANCED
			};

		};

		//interface to Draw Everything
		class IDrawable
		{
		public:
			/*
			everything will draw throw this ..
			*/


			virtual void draw(Primitive::Mode _mode) = 0;
		};

	}
}
