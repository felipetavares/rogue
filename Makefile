STD=c++11

all:
	g++ -std=$(STD) *.cpp rogue/*.cpp rogue/*/*.cpp -o zombie -g