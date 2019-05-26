#include "class.h"

bool operator ==(Point a, Point b){
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}

bool operator !=(Point a, Point b){
	return !(a == b);
}

bool operator ==(Complex a, Complex b){
	if (a.re == b.re && a.im == b.im)
		return true;
	return false;
}

bool operator !=(Complex a, Complex b){
	return !(a == b);
}

bool operator >(Complex a, int b){
	return a.re > b;
}

bool operator <(Complex a, int b){
	return a.re < b;
}

void Complex::skip(std::string s){
	int i = 0;
	std::string sNew = "";
	while (i != s.length()){
		if (s[i] != ' ')
			sNew += s[i];
		i++;
	}
	s = sNew;
}

void Complex::scanComplex(){
	std::string s;
	std::getline(std::cin, s);
	skip(s);
	int i = 0, sign = 1, cur = 0;
	if (s[0] == '-'){
		sign = -1;
		i++;
	}
	while (i != s.length()){
		if (s[i] >= '0' && s[i] <= '9')
			cur = cur * 10 + s[i] - '0';

		if (s[i] == '+' || s[i] == '-'){
			re = cur;
			re *= sign;
			if (s[i] == '+')
				sign = 1;
			else sign = -1;
			cur = 0;
		}
		if (s[i] == 'i'){
			im = cur;
			im *= sign;
		}
		i++;
	}
}

void Point::scanPoint(){
	std::string s;
	std::getline(std::cin, s);
	int i = 0, k = 1, sign = 1;
	while (i != s.length()){
		if (s[i] >= '0' && s[i] <= '9'){
			if (k == 1)
				x = x * 10 + s[i] - '0';
			if (k == 2)
				y = y * 10 + s[i] - '0';
		}
		if (s[i] == '-')
			sign = -1;
		if (s[i] == ','){
			k = 2;
			x *= sign;
			sign = 1;
		}
		if (s[i] == ')') y *= sign;
		i++;
	}
}