#include <iostream>;

int main() {
	int a, b;
	std::cin >> a;
	std::cin >> b;
	int is = 0;
	while (a <= b) {
		if (b % 7 == 0) {
			std::cout << b;
			is++;
			break;
		}
		else {
			b = b - 1;
		}
	}
	if (is == 0) {
		std::cout << -1;
	}
}