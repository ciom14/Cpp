#include <iostream>;
#include <cmath>;

int main() {
	int num;
	std::cin >> num;
	int n = 0;
	int icounter;
	for (int i = 0; n < num; i++) {
		n = pow(2, i);
		if (n <= num) {
			std::cout << n << ' ';
		}
	}
}