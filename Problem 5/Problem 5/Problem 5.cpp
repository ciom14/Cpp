#include <iostream>;
#include <vector>;

int main() {
	int num = 0;
	int min = 0;
	int counter = 0;
	std::cin >> num;
	std::vector<int> arr(num);
	for (int i = 0; i < num; i++) {
		std::cin >> arr[i];
	};
	min = arr[0];
	for (int i = 1; i < num; i++) {
		if (arr[i] < min) {
			counter = 1;
			min = arr[i];
		}
		else if (arr[i] == min) {
			counter++;
		};
	};
	std::cout << counter;

}