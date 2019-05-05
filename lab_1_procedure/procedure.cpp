#include <math.h>

struct complex{
	int re;
	int im;
};

void sumPointers(int* x, int* y){
	*x += *y;
}

void sumReferences(int& x, int& y){
	x += y;
}

void negatePointer(float* x){
	*x = -*x;
}

void negateReference(float& x){
	x = -x;
}

void conjugatePointer(complex* x){
	complex y;
	y.re = x->re;
	y.im = -x->im;
	*x = y;
}

void conjugateReference(complex& x){
	complex y;
	y.re = x.re;
	y.im = -x.im;
	x = y;
}

void multMatrixPointers(float** n, float* x){
	for (int i = 0; i != 3; i++)
		for (int j = 0; j != 3; j++)
			n[i][j] *= *x;
}

void multMatrixReferences(float(&n)[3][3], float& x){
	for (int i = 0; i != 3; i++)
		for (int j = 0; j != 3; j++)
			n[i][j] *= x;
}


