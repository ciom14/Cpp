#include <iostream>;

int fibonacci(int n) {
	if (n <= 2) {
		return n;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
};

int main() {
	int num = 0;
	int fib = 1;
	int i = 1;
	std::cin >> num;
	while (fib < num) {
		fib = fibonacci(i);
		i++;
	}
	if (fib == num) {
		std::cout << i;
	}
	else {
		std::cout << -1;
	}
}