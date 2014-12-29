#include <stack>
#include <string>
#include <vector>
#include <fstream>

struct Data {
	int weight{ 0 };
	int length{ std::numeric_limits<int>::max() };
	std::pair<int, int> from{ -1, -1 };
};

std::vector<Data> data;
int n;

std::ifstream input("route.in");
std::ofstream output("route.out");

inline Data& at(int x, int y) {
	return data[y + x *n];
}

inline Data& at(const std::pair<int,int>& p) {
	return data[p.second + p.first *n];
}


int main() {

	input >> n;
	data.resize(n*n);
	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			char c;
			input >> c;
			at(x, y).weight = (int)c;
		}
	}
	
	std::pair<int, int> p{ 0, 0 };
	at(p).length = at(p).weight;
	std::stack<std::pair<int, int>> stack;
	stack.push(p);

	while (!stack.empty()) {
		auto p = stack.top();
		stack.pop();

		auto& cell = at(p);
		if (p.first < n-1) {
			auto& right_cell = at(p.first + 1, p.second);
			auto new_length = cell.length + right_cell.weight;
			if (new_length < right_cell.length) {
				right_cell.length = new_length;
				right_cell.from = p;
				stack.push({ p.first + 1, p.second });
			}			
		}

		if (p.second < n-1) {
			auto& bottom_cell = at(p.first, p.second + 1);
			auto new_length = cell.length + bottom_cell.weight;
			if (new_length < bottom_cell.length) {
				bottom_cell.length = new_length;
				bottom_cell.from = p;
				stack.push({ p.first, p.second + 1 });
			}			
		}
	}


	//	output
	std::vector<char> map;
	map.resize(n*n);
	std::fill(map.begin(), map.end(), '-');
	
	p = std::pair < int, int > { n - 1, n - 1 };
	
	while (true) {				
		map[p.second + p.first * n] = '#';
		p = at(p).from;

		if (p.first == -1 && p.second == -1)
			break;
	}

	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x) {
			output << map[y + x*n];
		}
		output << std::endl;
	}
}