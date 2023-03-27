#pragma once
#include <iostream>
#include <cmath>


class ComplexNumber {
	int rp;
	int ip;

public:
	ComplexNumber(int rp = 0, int ip = 0) {
		this->rp = rp;
		this->ip = ip;
	}

	~ComplexNumber() {

	}

	int getIp() {
		return this->ip;
	}

	int getRp() {
		return this->rp;
	}
	
	
};

int compare_complex(ComplexNumber num1,ComplexNumber num2);
