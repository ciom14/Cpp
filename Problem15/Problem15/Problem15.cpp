#include <iostream>
#include <string>
#include <vector>

class Company;
class Director;
class Employee;
class Promise;

class Promise {
public:
	std::string id;
	double salary;
	bool isPaid;

	Promise(std::string workerId, double s) : id(workerId), salary(s), isPaid(false) {

	}
};

class Employee {
public:
	std::string name;
	std::string surname;
	std::string id;
	Promise* contract;

	Employee(std::string n, std::string s, std::string workerId) : name(n), surname(s), id(workerId) {

	}
};

class Company {
public:
	Director* dir;
	double profit;
	std::vector<Employee*> employees;

	Company(double p) {
		profit = p;
		dir = nullptr;
	}

	void createDirector(std::string name, std::string surname, int idNum, double salary);

	void createEmployee(std::string name, std::string surname, int idNum, double salary) {
		std::string id = std::to_string(idNum);
		Employee* emp = new Employee(name, surname, id);
		emp->contract = new Promise(id, salary);
		employees.push_back(emp);
	}

	void getProfit(double profit) {

	}

	void paySalaries() {

	}

	void setProfit(double p) {
		profit = p;
	}

	bool fulfillPromise();

	Director& director() {
		return *dir;
	}
};

class Director : public Employee {
private:
	Company* company;

public:
	Director(std::string n, std::string s, std::string workerId, Company* comp) :
		Employee(n, s, workerId), company(comp) {

	}

	bool checkPromises() {
		if (company == nullptr) return false;

		for (Employee* emp : company->employees) {
			if (emp != nullptr && emp->contract != nullptr && !emp->contract->isPaid) {
				return true;
			}
		}

		if (contract != nullptr && !contract->isPaid) {
			return true;
		}

		return false;
	}
};

void Company::createDirector(std::string name, std::string surname, int idNum, double salary) {
	std::string id = std::to_string(idNum);
	dir = new Director(name, surname, id, this);
	dir->contract = new Promise(id, salary);
}

bool Company::fulfillPromise() {
	double totalSalary = 0;

	if (dir != nullptr && dir->contract != nullptr) {
		totalSalary += dir->contract->salary;
	}

	for (Employee* emp : employees) {
		if (emp != nullptr && emp->contract != nullptr) {
			totalSalary += emp->contract->salary;
		}
	}

	if (profit >= totalSalary) {
		if (dir != nullptr && dir->contract != nullptr) {
			dir->contract->isPaid = true;
		}

		for (Employee* emp : employees) {
			if (emp != nullptr && emp->contract != nullptr) {
				emp->contract->isPaid = true;
			}
		}

		profit -= totalSalary;
		return true;
	}

	return false;
}

int main() {
	auto vk = Company(50);
	vk.createDirector(
		"Владимир",
		"Кириенко",
		1,
		15
	);

	vk.createEmployee(
		"Елена",
		"Иванова",
		2,
		8
	);

	vk.createEmployee(
		"Виктор",
		"Кузнецов",
		3,
		6
	);

	vk.setProfit(145.12);
	vk.fulfillPromise();

	auto director = vk.director();
	director.checkPromises(); // true

	vk.setProfit(-200);
	vk.fulfillPromise();

	director.checkPromises(); // false
}