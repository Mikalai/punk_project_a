#include "known_stuff.h"
#include "items.h"

static std::unique_ptr<Stuff> g_stuff;

int Stuff::Clothes::SimpleLeftBoots;
int Stuff::Clothes::SimpleRightBoots;
int Stuff::Clothes::SimpleLeftGloves;
int Stuff::Clothes::SimpleRightGloves;
int Stuff::Clothes::SimpleHelmet;
int Stuff::Clothes::SimpleJacket;
int Stuff::Clothes::SimplePants;

Stuff::Stuff() {
	Clothes::SimpleLeftBoots = ::Clothes::find("Simple left boot");
	Clothes::SimpleRightBoots = ::Clothes::find("Simple right boot");
	Clothes::SimpleLeftGloves = ::Clothes::find("Simple left glove");
	Clothes::SimpleRightGloves = ::Clothes::find("Simple right glove");
	Clothes::SimpleHelmet = ::Clothes::find("Simple helmet");
	Clothes::SimpleJacket = ::Clothes::find("Simple jacket");
	Clothes::SimplePants = ::Clothes::find("Simple pants");
}

void createStuff() {
	g_stuff.reset(new Stuff{});
}