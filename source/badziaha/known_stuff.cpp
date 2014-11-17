#include "known_stuff.h"
#include "items.h"

static std::unique_ptr<Stuff> g_stuff;

int Stuff::Clothes::SimpleBoots;
int Stuff::Clothes::SimpleGloves;
int Stuff::Clothes::SimpleHelmet;
int Stuff::Clothes::SimpleJacket;
int Stuff::Clothes::SimplePants;

Stuff::Stuff() {
	Clothes::SimpleBoots = ::Clothes::find("Simple boots");
	Clothes::SimpleGloves = ::Clothes::find("Simple gloves");
	Clothes::SimpleHelmet = ::Clothes::find("Simple helmet");
	Clothes::SimpleJacket = ::Clothes::find("Simple jacket");
	Clothes::SimplePants = ::Clothes::find("Simple pants");
}

void createStuff() {
	g_stuff.reset(new Stuff{});
}