#pragma once
#include <iostream>
#include <cmath>


class ComplexNumber;

int compare_complex(ComplexNumber num1, ComplexNumber num2); //Функція порівняння двох комплексних чисел

class ComplexNumber { //Клас комплексне число
	int rp; //Дійсна частина
	int ip; //Уявна частина

public:
	//Конструктор
	ComplexNumber(int rp = 0, int ip = 0) {
		this->rp = rp;
		this->ip = ip;
	}
	//Деструктор
	~ComplexNumber() {

	}
	//Повернненя уявної частини
	int getIp() const{
		return this->ip;
	}
	//Повернненя дійсної частини
	int getRp() const{
		return this->rp;
	}
	
	
	bool operator>(const ComplexNumber& num2) const {
		if (compare_complex(*this, num2) == 1)
			return true;
		return false;
	}

	bool operator<(const ComplexNumber& num2) const{
		if (compare_complex(*this, num2) == 0)
			return true;
		return false;
	}

	bool operator==(const ComplexNumber& num2) const{
		if (compare_complex(*this, num2) == 2)
			return true;
		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& dt) {
		return os << dt.getRp() << "+ i*(" << dt.getIp()<<")";
	}

};

