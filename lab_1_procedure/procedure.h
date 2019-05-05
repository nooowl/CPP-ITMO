#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

struct complex{
	int re;
	int im;
};

void sumPointers(int* x, int* y);

void sumReferences(int& x, int& y); 

void negatePointer(float* x);

void negateReference(float& x);

void conjugatePointer(complex* x);

void conjugateReference(complex& x);

void multMatrixPointers(float** n, float* x);

void multMatrixReferences(float (&n)[3][3], float& x);

#endif