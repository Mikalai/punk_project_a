#include <vector>
#include <fstream>

int g_sum;

std::ifstream input("expr.in");
std::ofstream output("expr.out");

enum class Sign{
	Plus,
	Minus
};

int calc_sum(const std::vector<int>& numbers, const std::vector<Sign>& signs) {
	int sum = numbers[0];
	for (int i = 0, max_i = signs.size(); i < max_i; ++i) {
		if (signs[i] == Sign::Plus)
			sum += numbers[i + 1];
		else if (signs[i] == Sign::Minus)
			sum -= numbers[i + 1];
	}
	return sum;
}

void print(const std::vector<int>& numbers, const std::vector<Sign>& signs) {
	output << numbers[0];
	for (int i = 0, max_i = signs.size(); i < max_i; ++i) {
		output << (signs[i] == Sign::Plus ? '+' : '-');
		output << numbers[i + 1];
	}
	output << '=' << g_sum << std::endl;
}

bool run(const std::vector<int>& numbers, std::vector<Sign>& signs, int index, int sum) {

	if (sum == g_sum) {
		print(numbers, signs);
		return true;
	}

	if (index != signs.size()) {
		for (int i = index, max_i = signs.size(); i < max_i; ++i) {
			auto new_sum = sum - 2 * numbers[i + 1];
			signs[i] = Sign::Minus;
			if (run(numbers, signs, i + 1, new_sum))
				return true;
			signs[i] = Sign::Plus;
		}
	}
	return false;
}

int main() {

	int n;
	input >> n >> g_sum;

	std::vector<int> numbers;
	numbers.resize(n);

	for (int i = 0; i < n; ++i) {
		input >> numbers[i];
	}

	std::vector<Sign> signs;
	signs.resize(n - 1u);
	std::fill(signs.begin(), signs.end(), Sign::Plus);

	int sum = 0;
	for (auto v : numbers) {
		sum += v;
	}

	if (!run(numbers, signs, 0, sum)) {
		output << "No solution" << std::endl;
	}
}