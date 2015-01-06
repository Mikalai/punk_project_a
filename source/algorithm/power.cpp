#include <fstream>
#include <algorithm>
#include <vector>

std::ifstream input("power.in");
std::ofstream output("power.out");

int a, n;

std::vector<short> res;

const std::vector<short> mult(const std::vector<short>& l, const std::vector<short>& r) {
	std::vector<short> res;
	res.resize(l.size() + r.size());

	std::fill(res.begin(), res.end(), 0);

	for (int i = 0, max_i = (int)r.size(); i < max_i; ++i) {
		
		short offset = 0;
		short cary = 0;
		
		int j = 0, max_j = (int)l.size();
		for (; j < max_j; ++j) {
			short v = l[j] * r[i] + cary;
			res[i + j] += v;
			cary = res[i + j] / 10;
			res[i + j] = res[i + j] % 10;
		}
		
		if (cary)
			res[i + j] = cary;
	}
	return res;
}

int main() {
	N
	input >> a >> n;

	auto r = mult({ 1, 2, 3, 4 }, { 9, 8, 7 });


}