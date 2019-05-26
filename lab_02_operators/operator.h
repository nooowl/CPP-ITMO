#ifndef _OPERATOR_H_
#define _OPERATOR_H_

struct complex{
	double re, im;
	operator double();
};

complex operator *(complex x, double a);

complex operator +(complex x, complex y);

complex operator *(complex x, complex y);

void printComplex(complex x);

struct queue{
	int head;
	int arr[100];
	int size;

	int operator >>(int &x);
};

queue operator <<(queue q, int x);

void printQueue(queue q);

#endif