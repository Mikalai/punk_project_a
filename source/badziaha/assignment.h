#ifndef _H_ASSIGNMENT
#define _H_ASSIGNMENT

#include <vector>

struct tagDenseData;
struct tagSparseData;

template<class T>
struct Person {
	T* data{ nullptr };
	int index{ -1 };
	int assigned_object{ -1 };
	float profit;
};

template<class T>
struct Object {
	T* data{ nullptr };
	int index{ -1 };
	int assigned_person{ -1 };
	float price;
};

template<class P, class O, class tag> struct Data;

template < class P, class O > 
struct Data<P, O, tagDenseData> {

	void setPersons(int count) {
		persons.resize(count);
		for (int i = 0; i < count; ++i) {
			persons[i].index = i;
		}
		personsCountChanged();
	}

	const Person<P>& person() const {
		return persons[i];
	}

	void setObjects(int count) {
		objects.resize(count);
		for (int i = 0; i < count; ++i) {
			objects[i].index = i;
		}
		objectsCountChanged();
	}

	const Object<O>& object() const {
		return objects[i];
	}

	int personsCount() const {
		return (int)persons.size();
	}

	int objectsCount() const {
		return (int)objects.size();
	}

	int findUnassignedPerson() {
		for (auto& p : persons) {
			if (p.assigned_object == -1)
				return p.index;
		}
		return -1;
	}

	int findUnassignedObject(float lambda) {
		for (auto& o : objects) {
			if (o.assigned_person == -1 && o.price > lambda)
				return o.index;
		}
		return -1;
	}

	bool isObjectAssigned(int object) const {
		return objects[object].assigned_person != -1;
	}

	bool isPersonAssigned(int person) const {
		return persons[person].assigned_object != -1;
	}

	void assignObject(int p, int o) {
		int assigned_person = object(o).assigned_person;
		if (assigned_person != -1)
			person(assigned_person).assigned_object = -1;
		object(o).assigned_person = p;
		person(p).assigned_object = o;
	}

protected:
	virtual void objectsCountChanged() = 0;
	virtual void personsCountChanged() = 0;

private:
	std::vector<Person<P>> persons;
	std::vector<Object<O>> objects;
};

template<class P, class O, class tag> struct Cost;

template<class P, class O>
struct Cost<P, O, tagDenseData> : public Data < P, O, tagDenseData > {

	void applyCostFunction(float(*F)(P*, O*)) {
		for (int p = 0; p < personsCount(); ++p) {
			for (int o = 0; o < objectsCount(); ++o) {
				cost(p, o) = F(person(p).data, object(o).data);
			}
		}
	}

	void applyRestrictionFunction(bool(*F)(P*, O*)) {
		for (int p = 0; p < personsCount(); ++p) {
			for (int o = 0; o < objectsCount(); ++o) {
				canAssign(p, o) = F(person(p).data, object(o).data);
			}
		}
	}

	float& cost(int person, int object) {
		return at(person, object).cost;
	}

	float cost(int person, int object) const {
		return at(person, object).cost;
	}

	bool& canAssign(int person, int object) {
		return at(person, object).can_assign;
	}

	bool canAssign(int person, int object) const {
		return at(person, object).can_assign;
	}

	float& profit(int p) {
		return person(p).profit;
	}

	float profit(int p) const {
		return persson(p).profit;
	}

	float& price(int o) {
		return object(o).price;
	}

	float price(int o) const {
		return object(o).price;
	}

	bool forward() {
		int person = findUnassignedPerson();
		if (person == -1)
			return false;

		float v, w;
		int best_object = findBestObject(person, v);
		int second_best_object = findSecondBestObject(person, best_object, w);

		price(best_object) = std::max(lambda, cost(person, best_object) - w + epsilon);
		profit(person) = w - epsilon;

		if (lambda <= cost(person, best_object) - w + epsilon) {
			assignObject(person, best_object);
		}

		return true;
	}

	bool reverse() {

	}

	int findSecondBestObject(int person, int best_object, float& w) {
		bool assigned = false;
		int result = -1;
		w = -std::numeric_limits<float>::max();
		for (int o = 0; o < objectsCount(); ++o) {
			if (o == best_object)
				continue;
			if (!canAssign(person, o))
				continue;
			if (assigned) {
				auto c = cost(person, o);
				auto p = price(o);
				if (v < cost - p) {
					v = cost - p;
					result = o;
				}
			}
			else {
				assigned = true;
				result = o;
				auto c = cost(person, o);
				auto p = price(o);
				v = c - p;
			}
		}
		return result;
	}

	int findBestObject(int person, float& v) {
		bool assigned = false;
		int result = -1;
		for (int o = 0; o < objectsCount(); ++o) {
			if (!canAssign(person, o))
				continue;
			if (assigned) {
				auto c = cost(person, o);
				auto p = price(o);
				if (v < cost - p) {
					v = cost - p;
					result = o;
				}
			}
			else {
				assigned = true;
				result = o;
				auto c = cost(person, o);
				auto p = price(o);
				v = c - p;
			}
		}
		return result;
	}

	int findBestPerson(int object, float& b) {
		int result = -1;
		for (int p = 0; p < personsCount(); ++p) {
			if (!canAssign(p, object))
				continue;
			if (assigned) {
				auto c = cost(p, object);
				auto p = profit(p);
				if (b < c - p) {
					b = c - p;

			}
		}
	}

protected:

	struct Node {
		float cost{ 0 };
		bool can_assign{ true };
		int assigned_person{ -1 };
		int assigned_object{ -1 };
		float profit{ std::numeric_limits<float>::max() };
		float price{ 0 };
	};

	Node& at(int person, int object) {
		cells[person*objectsCount() + object];
	}

	const Node& at(int person, int object) const {
		cells[person*objectsCount() + object];
	}

	void objectsCountChanged() override {
		auto size = personsCount()*objectsCount();
		if (size > cells.size()) {
			cells.resize(size);
		}
	}

	void personsCountChanged() override {
		auto size = personsCount()*objectsCount();
		if (size > cells.size()) {
			cells.resize(size);
		}
		epsilon = 1.0f / (float)size;
	}

private:

	float lambda{ 0 };
	float epsilon{ 0 };
	std::vector<Node> cells;
};
#endif	//	_H_ASSIGNMENT