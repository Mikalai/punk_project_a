/*
	Contains codes for all ingame items, clothes, weapons and etc.
*/
#ifndef _H_KNOWN_STUFF
#define _H_KNOWN_STUFF

class Stuff {
public:
	Stuff();

	class Clothes {
	public:
		static int SimpleLeftBoots;
		static int SimpleRightBoots;
		static int SimpleHelmet;
		static int SimpleJacket;
		static int SimplePants;
		static int SimpleLeftGloves;
		static int SimpleRightGloves;
	};	
};

void createStuff();
#endif	//	_H_KNOWN_STUFF