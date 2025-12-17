#include <iostream>;

int main() {
	int size;
	std::cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		std::cin >> arr[i];
	}
	int twodigarr[100];
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] >= 10 && arr[i] <= 99) {
			twodigarr[count] = arr[i];
			count++;
		}
	}
	int sum = 0;
	for (int i = 0; i < count; i++) {
		if (twodigarr[i] % 8 == 0) {
			sum += twodigarr[i];
		}
	}
	std::cout << sum;
}