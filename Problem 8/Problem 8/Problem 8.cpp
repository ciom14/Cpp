#include <iostream>;
#include <string>;

int main() {
	std::string dna;
	std::cin >> dna;
	int len;
	len = dna.length();
	for (int i = 0; i <= len - 1; i++) {
		if (dna[i] == 'A') {
			dna[i] = 'T';
		}
		else if (dna[i] == 'T') {
			dna[i] = 'A';
		}
		else if (dna[i] == 'C') {
			dna[i] = 'G';
		}
		else if (dna[i] == 'G') {
			dna[i] = 'C';
		}
	}
	std::cout << dna;
}