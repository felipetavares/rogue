#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <cstring>
#include <string>
#include "interface.hpp"
using namespace std;

namespace rogue {
	namespace interface {
		CharBuf::CharBuf (int width, int height) {
			this->width = width;
			this->height = height;

			data = new string[width*height];
		}

		CharBuf::~CharBuf () {
			delete[] data;
		}

		void CharBuf::updateSize (int width, int height) {
			this->width = width;
			this->height = height;

			delete[] data;
			data = new string[width*height];
		}

		string CharBuf::getCharAt(int x, int y) {
			if (inside(x,y)) {
				return data[y*width+x];
			}
			return "";
		}

		void CharBuf::setCharAt (int x, int y, string character) {
			if (inside(x,y)) {
				data[y*width+x] = character;
			}
		}

		void CharBuf::fillWith (string character) {
			int end = width*height;
			for (int i=0;i<end;i++)
				data[i] = character;
		}

		int CharBuf::getWidth () {
			return width;
		}

		int CharBuf::getHeight () {
			return height;
		}

		bool CharBuf::inside (int x, int y) {
			if (x >= 0 && x < width &&
				y >= 0 && y < height)
				return true;
			return false;
		}

		bool CharBuf::inside (int p) {
			if (p >= 0 && p < width*height)
				return true;
			return false;
		}

		void CharBuf::render () {
			for (int y=0;y<height;y++) {
				for (int x=0;x<width;x++)
					cout << getCharAt(x,y);
				cout << endl;
			}
		}

		void CharBuf::economicRender () {
			for (int y=0;y<height;y++)
				for (int x=0;x<width;x++)
					if (getCharAt(x,y) != "") {
						// Move to the character position
						cout << "\33[" << y+1 << ";" << x+1 << "H";
						cout << getCharAt(x,y);
					}
		}

		void CharBuf::blit (CharBuf& to, CharBuf& from, int x, int y) {
			int f = 0;
			int t = to.width*y+x;

			// Copy all lines
			for (int i=0;i<from.height;i++,t+=to.width-from.width)
				// All chars
				for (int j=0;j<from.width;j++)
					if (to.inside(t) && from.inside(f))
						to.data[t++] = from.data[f++];
		}

		CharBuf CharBuf::subtract (CharBuf& a, CharBuf& b) {
			CharBuf sub (0,0);
			if (a.width == b.width &&
				a.height == b.height) {
				sub.updateSize(a.width,a.height);
				int size = a.width*a.height;
				for (int i=0;i<size;i++) {
					sub.data[i] = a.data[i]==b.data[i]?"":string(b.data[i]);
				}
			}
			return sub;
		}

		void CharBuf::copy (CharBuf& to, CharBuf& from) {
			if (to.width == from.width &&
				to.height == from.height) {
				int size = to.width*to.height;
				for (int i=0;i<size;i++) {
					to.data[i] = from.data[i];
				}
			}
		}

		Display::Display ():
			screen(0,0),
			backScreen(0,0) {
			openFrame();
			updateSize();
			screen.updateSize(width,height);
			backScreen.updateSize(width,height);
		}

		Display::~Display () {
			closeFrame();
		}

		int Display::getWidth () {
			return width;
		}

		int Display::getHeight () {
			return height;
		}

		void Display::updateSize () {
			struct winsize ts;
			ioctl(0, TIOCGWINSZ, &ts);

			width = ts.ws_col;
			height = ts.ws_row;
		}

		void Display::nonCanonicalStdin () {
			struct termios serialAttr;
			    
			bzero (&serialAttr, sizeof (struct termios));

			serialAttr.c_oflag |= OCRNL | ONLCR | ONLRET | ONOCR | OPOST;
			serialAttr.c_cc[VMIN]  = 1;
			serialAttr.c_cc[VTIME] = 0;

			tcgetattr (1, &prevAttr);
			tcsetattr (1,TCSANOW,&serialAttr);
		}

		void Display::restoreStdin () {
  			tcsetattr (1,TCSANOW,&prevAttr);
		}

		void Display::openFrame () {
			cout << "\33\133\77" << "1049h";
		}

		void Display::closeFrame () {
			cout << "\33\133\77" << "1049l";
		}

		void Display::draw () {
			CharBuf aFilled = CharBuf(10,10);
			aFilled.fillWith(" ");
			backScreen.fillWith("-");

			for (int i=0;i<80;i++) {
				screen.fillWith(".");

				CharBuf::blit(screen, aFilled, (width-aFilled.getWidth())/2+i,
											   (height-aFilled.getHeight())/2);

				// Render only the portion of the screen that was updated
				CharBuf::subtract (backScreen,screen).economicRender();

				CharBuf::copy(backScreen,screen);

				usleep(100000);
				cout.flush();
			}
		}
	}
}