#include <iostream>;
#include <vector>;

int main() {
	std::vector<int> arr;
	int num;
	while (true) {
		std::cin >> num;
		if (num == 0) {
			break;
		}
		arr.push_back(num);
	}
	int len = arr.size();
	int max = arr[0];
	int count = 1;
	for (int i = 1; i < len; i++) {
		if (arr[i] > max) {
			max = arr[i];
			count = 1;
		}
		else if (arr[i] == max) {
			count++;
		}
	}
	std::cout << count;
}