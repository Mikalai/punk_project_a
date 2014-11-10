#ifndef _H_ASSIGNMENT
#define _H_ASSIGNMENT

#include <config.h>
#include <functional>
#include <vector>

PUNK_ENGINE_BEGIN
namespace Math {

	struct tagAlgorithmForward;
	struct tagAlgorithmReverse;
	struct tagAlgorithmCombined;
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

	template<class P, class O, class tag> class Data;

	template < class P, class O >
	class Data < P, O, tagDenseData > {
	protected:
		enum Result {
			Ok,			
			NoUnassignedPersons,
			PriceToHigh,
			PersonAssigned
		};

	public:		
		void setPersons(int count, std::function<P*(int)> get_person) {
			persons.resize(count);
			for (int i = 0; i < count; ++i) {
				persons[i].index = i;
				persons[i].data = get_person(i);
			}
			personsCountChanged();
		}

		void setObjects(int count, std::function<O*(int)> get_object) {
			objects.resize(count);
			for (int i = 0; i < count; ++i) {
				objects[i].index = i;
				objects[i].data = get_object(i);
			}
			objectsCountChanged();
		}

	protected:

		const Person<P>& person(int i) const {
			return persons[i];
		}

		Person<P>& person(int i) {
			return persons[i];
		}

		const Object<O>& object(int i) const {
			return objects[i];
		}

		Object<O>& object(int i) {
			return objects[i];
		}

		int personsCount() const {
			return (int)persons.size();
		}

		int objectsCount() const {
			return (int)objects.size();
		}

		Result findUnassignedPerson(int& person) {
			person = -1;
			for (auto& p : persons) {
				if (p.assigned_object == -1) {
					person = p.index;
					return Ok;
				}
			}
			return NoUnassignedPersons;
		}

		Result findUnassignedObject(int& object, float lambda) {
			object = -1;
			Result result = NoUnassignedPersons;
			for (auto& o : objects) {
				if (o.assigned_person == -1) {
					if (o.price > lambda) {
						object = o.index;
						return Ok;
					}
					else {
						result = PriceToHigh;
					}
				}
			}
			return result;
		}

		bool isObjectAssigned(int object) const {
			return objects[object].assigned_person != -1;
		}

		bool isPersonAssigned(int person) const {
			return persons[person].assigned_object != -1;
		}

		int assignedObject(int p) const {
			return person(p).assigned_object;
		}

		void assignObject(int p, int o) {
			int assigned_person = object(o).assigned_person;
			if (assigned_person != -1) {
				person(assigned_person).assigned_object = -1;				
			}
			int assigned_object = person(p).assigned_object;
			if (assigned_object != -1) {
				object(assigned_object).assigned_person = -1;
			}
			object(o).assigned_person = p;
			person(p).assigned_object = o;
		}

		P* personData(int p) {
			return person(p).data;
		}

		O* objectData(int o) {
			return object(o).data;
		}

	protected:
		virtual void objectsCountChanged() = 0;
		virtual void personsCountChanged() = 0;

	private:
		std::vector<Person<P>> persons;
		std::vector<Object<O>> objects;
	};

	template<class P, class O, class tag> class Cost;

	template<class P, class O>
	class Cost<P, O, tagDenseData> : public Data < P, O, tagDenseData > {
	public:

		void applyCostFunction(std::function<float(P*, O*)> F) {
			for (int p = 0; p < personsCount(); ++p) {
				for (int o = 0; o < objectsCount(); ++o) {
					cost(p, o) = F(person(p).data, object(o).data);
				}
			}
		}

		void applyRestrictionFunction(std::function<bool(P*, O*)> F) {
			for (int p = 0; p < personsCount(); ++p) {
				for (int o = 0; o < objectsCount(); ++o) {
					canAssign(p, o) = F(person(p).data, object(o).data);
				}
			}
		}

		void getResult(std::vector<std::pair<P*, O*>>& result) {
			result.clear();
			for (int p = 0, max_p = personsCount(); p < max_p; ++p) {
				auto o = assignedObject(p);
				if (o != -1) {
					result.push_back(std::pair < P*, O* > {personData(p), objectData(o)});
				}
			}
		}

	protected:

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

		Result forward() {
			int person;
			Result result = findUnassignedPerson(person);
			if (result == NoUnassignedPersons)
				return result;

			float v, w;
			int best_object = findBestObject(person, v);
			int second_best_object = findSecondBestObject(person, best_object, w);

			price(best_object) = std::max(lambda(), cost(person, best_object) - w + epsilon());
			profit(person) = w - epsilon();

			if (lambda() <= cost(person, best_object) - w + epsilon()) {
				assignObject(person, best_object);
				result = PersonAssigned;
			}

			return result;
		}

		Result reverse() {
			int object;
			Result result = findUnassignedObject(object, lambda());
			if (result == NoUnassignedPersons || result == PriceToHigh)
				return result;

			float b, g;
			int best_person = findBestPerson(object, b);
			int second_best_person = findSecondBestPerson(object, best_person, g);

			if (b >= lambda() + epsilon()) {
				price(object) = std::max(lambda(), g - epsilon());
				profit(best_person) = cost(best_person, object) - std::max(lambda(), g - epsilon());
				assignObject(best_person, object);

				result = PersonAssigned;
			}
			else {
				price(object) = b - epsilon();
				advanceLambda();
			}
			return result;
		}

		void advanceLambda() {
			int m = personsCount();
			int n = objectsCount();
			int c = 0;
			float min_price = -std::numeric_limits<float>::max();
			for (int o = 0; o < n || c > n - m; ++o) {
				if (price(o) < lambda()) {
					c++;
					min_price = std::max(min_price, price(o));
				}
			}
			if (c > n - m) {
				setLambda(min_price);
			}
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
					if (w < c - p) {
						w = c - p;
						result = o;
					}
				}
				else {
					assigned = true;
					result = o;
					auto c = cost(person, o);
					auto p = price(o);
					w = c - p;
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
					if (v < c - p) {
						v = c - p;
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
			bool assigned = false;
			int result = -1;
			for (int p = 0; p < personsCount(); ++p) {
				if (!canAssign(p, object))
					continue;
				if (assigned) {
					auto c = cost(p, object);
					auto g = profit(p);
					if (b < c - g) {
						b = c - g;
						result = p;
					}
				}
				else {
					auto c = cost(p, object);
					auto g = profit(p);
					b = c - g;
					result = p;
					assigned = true;
				}
			}
			return result;
		}

		int findSecondBestPerson(int object, int best_person, float& g) {
			int result = -1;
			bool assigned = false;
			for (int p = 0; p < personsCount(); ++p) {
				if (p == best_person)
					continue;
				if (!canAssign(p, object))
					continue;
				if (assigned) {
					auto c = cost(p, object);
					auto h = profit(p);
					if (g < c - h) {
						g = c - h;
						result = p;
					}
				}
				else {
					auto c = cost(p, object);
					auto h = profit(p);
					g = c - h;
					result = p;
					assigned = true;
				}
			}
			return result;
		}

		float lambda() const {
			return m_lambda;
		}

		void setLambda(float value) {
			m_lambda = value;
		}

		float epsilon() const {
			return m_epsilon;
		}

		void setEpsilon(float value) {
			m_epsilon = value;
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
			return m_cells[person*objectsCount() + object];
		}

		const Node& at(int person, int object) const {
			return m_cells[person*objectsCount() + object];
		}

		void objectsCountChanged() override {
			auto size = personsCount()*objectsCount();
			if (size > m_cells.size()) {
				m_cells.resize(size);
			}
		}

		void personsCountChanged() override {
			auto size = personsCount()*objectsCount();
			if (size > m_cells.size()) {
				m_cells.resize(size);
			}
			m_epsilon = 1.0f / (float)size;
		}

	private:

		float m_lambda{ 0 };
		float m_epsilon{ 0 };
		std::vector<Node> m_cells;
	};


	template<class P, class O, class tagData, class tagAlgorithm> class Auction;

	template<class P, class O, class tagData> 
	class Auction<P, O, tagData, tagAlgorithmForward> : public Cost < P, O, tagData > {
	public:
		void run(std::vector<std::pair<P*, O*>>& result) {
			//	tune lambda thus lambda >= price(j) for all unassigned objects j
			setLambda(-std::numeric_limits<float>::max());
			for (int o = 0, max_o = objectsCount(); o < max_o; ++o) {
				setLambda(std::max(price(o), lambda()));
			}

			//	tune e-CS
			setEpsilon(1 / (float)personsCount());

			while (forward() != NoUnassignedPersons);

			getResult(result);
		}
	};

	template<class P, class O, class tagData>
	class Auction<P, O, tagData, tagAlgorithmReverse> : public Cost < P, O, tagData >{
	public:
		void run(std::vector<std::pair<P*, O*>>& result) {
			//	tune lambda thus lambda >= price(j) for all unassigned objects j
			setLambda(-std::numeric_limits<float>::max());
			for (int o = 0, max_o = objectsCount(); o < max_o; ++o) {
				setLambda(-std::numeric_limits<float>::max());
			}

			//	tune e-CS
			setEpsilon(1 / (float)personsCount());

			while (reverse() != NoUnassignedPersons);

			getResult(result);
		}
	};

	template<class P, class O, class tagData>
	class Auction<P, O, tagData, tagAlgorithmCombined> : public Cost < P, O, tagData >{
	public:
		void run(std::vector<std::pair<P*, O*>>& result) {
			//	tune e-CS
			setEpsilon(1 / (float)personsCount());

			while (true) {
				//	1 stage
				if (forward() == PersonAssigned) {
					while (true) {
						//	2 stage
						auto r = reverse();
						if (r == PriceToHigh || r == PersonAssigned)
							break;
						if (r == NoUnassignedPersons) {
							//	3 stage
							while (reverse() != NoUnassignedPersons);
							goto result;
						}
					}
				}
				else {
					//	3 stage
					while (reverse() != NoUnassignedPersons);
					goto result;
				} 
			}

		result:
			getResult(result);
		}
	};	

	template<class P, class O, class A = tagAlgorithmCombined>
	void assign(int persons_count, int objects_count, std::function<P*(int)> get_person, std::function<O*(int)> get_object, std::function<float(P*, O*)> get_cost, std::vector<std::pair<P*, O*>>& result) {
		if (persons_count <= objects_count) {
			Auction<P, O, tagDenseData, A> auction;
			auction.setObjects(objects_count, get_object);
			auction.setPersons(persons_count, get_person);
			auction.applyCostFunction(get_cost);
			//auction.runForwardAlgorithm(result);
			auction.run(result);
		}
		else {
			Auction<O, P, tagDenseData, A> auction;
			auction.setObjects(persons_count, get_person);
			auction.setPersons(objects_count, get_object);
			auction.applyCostFunction([get_cost](O* o, P* p) {
				return get_cost(p, o);
			});
			std::vector<std::pair<O*, P*>> temp;
			auction.run(temp);
			for (auto& r : temp){
				result.push_back(std::make_pair(r.second, r.first));
			}
		}
	}
}
PUNK_ENGINE_END

#endif	//	_H_ASSIGNMENT