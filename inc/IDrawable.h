
namespace Break{
	namespace GXWrapper{

		struct Primative{

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
				Normal = 0,
				Indexed = 1,
				Normal_Instanced = 2,
				Index_Instanced
			};

		};

		//interface to Draw Everything
		class IDrawable
		{
		public:
			/*
			everything will draw throw this ..
			*/


			virtual void Draw(Primative::Type _primative , Primative::Mode _mode) = 0;
		};

	}
}