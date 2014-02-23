#include <iostream>
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

		Display::Display ():
			screen(1,1) {
			//openFrame();
			updateSize();
			screen.updateSize(width,height);
		}

		Display::~Display () {
			//closeFrame();
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
			aFilled.fillWith("#");

			screen.fillWith(".");

			CharBuf::blit(screen, aFilled, (width-aFilled.getWidth())/2,
										   (height-aFilled.getHeight())/2);

			screen.render();
		}
	}
}