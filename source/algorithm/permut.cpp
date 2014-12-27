#include <string>
#include <fstream>

std::string g_source;
int g_len;

std::ifstream input("permut.in");
std::ofstream output("permut.out");

void permut(std::string& src, int index) {

	output << src << std::endl;

	for (int i = index, max_i = g_len - 1; i < max_i; ++i) {
		for (int j = i + 1, max_j = g_len; j < max_j; ++j) {
			std::swap(src[i], src[j]);
			permut(src, i + 1);
			std::swap(src[i], src[j]);
		}
	}
}

int main() {

	input >> g_source;
	g_len = g_source.size();

	permut(g_source, 0);
}