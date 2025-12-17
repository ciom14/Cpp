#include <iostream>;

int main() {
	int size;
	std::cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		std::cin >> arr[i];
	}
	int max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	std::cout << max;
}