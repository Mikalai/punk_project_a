#include <math.h>
#include <iostream>
#include <QtWidgets/qapplication.h>
#include "forms/main_window.h"
#include <math/assignment.h>

using namespace Punk::Engine::Math;

struct MyPerson {
	int value;
	int location;
};

struct MyObject {
	int value;
	int location;
};

int main(int argc, char** argv) {
	std::vector<MyPerson> persons{ 2 };
	std::vector<MyObject> objects{ 3 };

	int k = 0;
	for (auto& p : persons) {
		p.value = ++k;
		p.location = rand() % 10;
	}

	k = 0;
	for (auto& o : objects) {
		o.value = ++k;
		o.location = rand() % 10;
	}

	Auction<MyPerson, MyObject, tagDenseData, tagAlgorithmCombined> auction;
	auction.setObjects(objects.size(), [&objects](int index) {
		return &objects[index];
	});
	
	auction.setPersons(persons.size(), [&persons](int index) -> MyPerson* {
		return &persons[(size_t)index];
	});

	auction.applyCostFunction([](MyPerson* p, MyObject* o) -> float {
		return fabsf(p->location - o->location);
	});

	std::vector<std::pair<MyPerson*, MyObject*>> result;

	//auction.runForwardAlgorithm(result);

	assign<MyPerson, MyObject>(persons.size(), objects.size(), 
		[&persons](int index) -> MyPerson* {
		return &persons[index]; },
			[&objects](int index) {
			return &objects[index]; },
				[](MyPerson* p, MyObject* o) -> float {
				return fabsf(p->location - o->location);
			}, result);

	for (auto& person : persons) {
		std::cout << "Person: " << person.value << " " << person.location << std::endl;
	}

	for (auto& object : objects) {
		std::cout << "Object: " << object.value << " " << object.location << std::endl;
	}

	for (auto& r : result) {
		std::cout << r.first->value << " -> " << r.second->value << std::endl;
	}

	return 0;

	QApplication app(argc, argv);
	MainWindow w;
	w.show();
	return app.exec();
}