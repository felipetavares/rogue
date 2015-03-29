STD=c++11
CXX=clang++-3.5

all:
	$(CXX) -std=$(STD) *.cpp rogue/*.cpp rogue/*/*.cpp -o game -g
