#include <iostream>
#include <vector>
#include "math.h"
#include "operator.h"

using namespace std;

complex::operator double(){
	return sqrt(pow(re, 2) + pow(im, 2));
}

complex operator *(complex x, double a){
	complex y;
	y.re = x.re * a;
	y.im = x.im * a;
	return y;
}

complex operator +(complex x, complex y){
	complex z;
	z.re = x.re + y.re;
	z.im = x.im + y.im;
	return z;
}

complex operator *(complex x, complex y){
	complex z;
	z.re = x.re * y.re - x.im * y.im;
	z.im = x.re * y.im - x.im * y.re;
	return z;
}

void printComplex(complex x){
	cout << x.re;
	if (x.im > 0)
		cout << '+';
	cout << x.im << 'i' << endl;
}

int queue:: operator >>(int &x){
		head = arr[0];
		for (int i = 1; i < size; i++)
			arr[i - 1] = arr[i];
		size--;
		x = head;
		return x;
}

queue operator <<(queue q, int x){
	q.arr[q.size] = x;
	q.size++;
	return q;
}


void printQueue(queue q){
	for (int i = 0; i < q.size; i++)
		cout << q.arr[i] << " ";
	cout << endl;
}