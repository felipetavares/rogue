#include <termios.h>
#include <fcntl.h>
#include <string>
using namespace std;

namespace rogue {
	namespace interface {
		class CharBuf {
			int width,height;
			string *data;
		public:
			CharBuf(int,int);
			~CharBuf();

			static void blit (CharBuf&,CharBuf&,
							  int, int);

			void updateSize(int,int);
			string getCharAt(int,int);
			void setCharAt(int,int,string);
			void fillWith (string);
			int getWidth();
			int getHeight();
			bool inside(int,int);
			bool inside(int);

			void render();
		};

		class Display {
			struct termios prevAttr;
			int width,height;
			CharBuf screen;
		public:
			Display();
			~Display();

			int getWidth();
			int getHeight();
			void updateSize();
			void draw();
		private:
			void openFrame();
			void closeFrame();
			void nonCanonicalStdin ();
			void restoreStdin();
		};
	}
}
