#include <utility>
#include <algorithm>
#include <vector>
#include <fstream>


std::ifstream input("incseq.in");
std::ofstream output("incseq.out");

int g_n;
std::vector<std::pair<int, int>> g_numbers;

int main() {

	input >> g_n;
	g_numbers.resize(g_n);
	for (int i = 0; i < g_n; ++i) {
		input >> g_numbers[i].first;
	}

	int max_len = 1;

	for (int i = 0, max_i = g_numbers.size(); i < max_i; ++i) {
		g_numbers[i].second = 1;
		for (int j = 0; j < i; ++j) {
			if (g_numbers[i].first > g_numbers[j].first && g_numbers[i].second <= g_numbers[j].second) {
				g_numbers[i].second = g_numbers[j].second + 1;
				max_len = std::max(g_numbers[i].second, max_len);
			}
		}
	}

	std::vector<int> result;
	for (int i = g_numbers.size() - 1; i >= 0; --i) {
		if (g_numbers[i].second == max_len) {
			result.push_back(g_numbers[i].first);
			max_len--;
		}
	}

	output << result.size() << std::endl;
	for (auto v = result.rbegin(); v != result.rend(); ++v) {
		output << *v << ' ';
	}

	output << std::endl;
}