#include <vector>
#include <sstream>
#include <fstream>

std::ofstream output("primes.out");
std::ifstream input("primes.in");

int m, n;
std::vector<int> primes;

inline bool is_prime(int v) {
	
	while (true) {
		bool complex = false;
		int max = (int)sqrtf(v);
		if (!primes.empty() && max <= primes.back()) {
			int last = primes.front();
			for (int j = 0, max_j = (int)primes.size(); j < max_j; ++j) {
				last = primes[j];
				if (last > max)
					break;
				if ((v % last) == 0) {
					complex = true;
					break;
				}
			}

			if (complex)
				return false;

			return true;
		}

		int count = primes.size();
		int start = primes.empty() ? 2 : (primes.back() + 1);
		for (int i = start; i <= max; ++i) {
			int max_j = (int)sqrtf(i);
			complex = false;
			for (int j = 2; j <= max_j; ++j) {
				if ((i % j) == 0) {
					complex = true;
					break;
				}
			}
			if (!complex) {
				primes.push_back(i);
			}
		}

		if (count == primes.size()) {
			return false;
		}
	}
}

int main() {

	std::iostream::sync_with_stdio(false);

	input >> m >> n;

	primes.reserve(10000);
	

	bool has_any = false;
	for (int i = m; i <= n; ++i) {
		bool complex = false;
		for (int j = 2, max_j = (int)sqrtf(i); j <= max_j; ++j) {
			if (i % j == 0) {
				complex = true;
				break;
			}
		}
		if (!complex) {
			primes.push_back(i);
		}
	}

	if (primes.empty()) {
		output << "Absent";
	}
	else {
		//	direct write to file cause time out
		std::stringstream stream;
		for (auto v : primes)
			stream << v << std::endl;
		output << stream.str();
	}
}