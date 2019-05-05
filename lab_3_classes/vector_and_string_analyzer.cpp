#include <iostream>
#include <math.h>
#include <string>
#include "class.h"

using namespace std;

vector::vector(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}

vector vector::sum(vector f, vector s) {
	vector p(f.x + s.x, f.y + s.y, f.z + s.z);
	return p;
}

vector vector::sub(vector f, vector s) {
	vector p(f.x - s.x, f.y - s.y, f.z - s.z);
	return p;
}

double vector::angle(vector n) {
	return (x*n.x + y*n.y + z*n.z) / (len()*n.len());
}

double vector::len() {
	return sqrt(x*x + y*y + z*z);
}

void vector::print(){
	printf("(%f, %f, %f)\n", get_x(), get_y(), get_z());
}

double vector::get_x() {
	return x;
}

double vector::get_y() {
	return y;
}

double vector::get_z() {
	return z;
}

stringAnalyzer::stringAnalyzer(string newS){
	s = newS;
	length = newS.length();
}

void stringAnalyzer::addChar(char c){
	splitChars.insert(c);
}

void stringAnalyzer::clear(){
	splitChars.clear();
}

void stringAnalyzer::skipSplit(){
	while (pos < length && splitChars.count(s[pos])){
		pos++;
	}
}

string stringAnalyzer::nextString(){
	skipSplit();
	string res = "";
	while (pos < length && !splitChars.count(s[pos])) {
		res += s[pos];
		pos++;
	}
	return res;
}

bool stringAnalyzer::isEnd(){
	if (length == pos) {
		return true;
	}
	return false;
}



