#include <iostream>;

int main() {
	int size;
	std::cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		std::cin >> arr[i];
	}
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] > 0) {
			counter++;
		}
	}
	std::cout << counter;
}