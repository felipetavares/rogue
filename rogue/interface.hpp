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
			static CharBuf subtract (CharBuf&,CharBuf&);
			static void copy (CharBuf&,CharBuf&);

			void updateSize(int,int);
			string getCharAt(int,int);
			void setCharAt(int,int,string);
			void fillWith (string);
			int getWidth();
			int getHeight();
			bool inside(int,int);
			bool inside(int);

			void render();
			void economicRender();
		};

		class Display {
			struct termios prevAttr;
			int width,height;
			CharBuf screen;
			CharBuf backScreen;
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
