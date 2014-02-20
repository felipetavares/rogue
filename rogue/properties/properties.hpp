#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
using namespace std;

namespace rogue {
	class Object;

	class Propertie {
	public:
		// This returns the name of this propertie, for an given object
		virtual string getName(Object*) = 0;
		// This applies this propertie over a given object
		virtual void execute(Object&) = 0;
	};
}

#endif /* PROPERTIES_H */
