#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

std::ifstream input("longsum.in");
std::ofstream output("longsum.out");

std::string source_m;
std::string source_n;

std::vector<short> m;
std::vector<short> n;

std::vector<short> sum(const std::vector<short>& l, const std::vector<short>& r) {

	std::vector<short> res;
	res.resize(std::max(l.size(), r.size()) + 1);

	std::fill(res.begin(), res.end(), 0);

	int cary = 0;

	for (int i = 0, max_i = (int)r.size(); i < max_i; ++i) {
		int v = l[i] + r[i] + cary;
		if (v > 9) {
			v -= 10;
			cary = 1;
		}
		else {
			cary = 0;
		}

		res[i] = v;
	}	

	if (cary != 0) {
		res.back() = cary;
	}

	while (res.back() == 0 && res.size() > 1)
		res.pop_back();

	return res;
}

int main() {

	input >> source_m >> source_n;

	int size = std::max(source_m.size(), source_n.size());

	m.resize(size);
	n.resize(size);

	std::fill(m.begin(), m.end(), 0);
	std::fill(n.begin(), n.end(), 0);

	for (auto i = 0, max_i = (int)source_m.size(); i < max_i; ++i) {
		m[max_i - i - 1] = source_m[i] - '0';
	}
	
	for (auto i = 0, max_i = (int)source_n.size(); i < max_i; ++i) {
		n[max_i - i - 1] = source_n[i] - '0';
	}


	auto res = sum(m, n);

	for (auto it = res.rbegin(); it != res.rend(); ++it) {
		output << *it;
	}
}
