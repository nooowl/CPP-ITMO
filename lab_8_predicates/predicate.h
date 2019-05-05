#ifndef _CLASS_H_
#define _CLASS_H_
#include <string>
#include <iostream>

class Point{
public:
	int x = 0, y = 0;
	void scanPoint();
};

class Complex{
private:
	void skip(std::string);
public:
	int re = 0, im = 0;
	void scanComplex();
};

bool operator ==(Point a, Point b);

bool operator !=(Point a, Point b);

bool operator ==(Complex a, Complex b);

bool operator !=(Complex a, Complex b);

bool operator >(Complex a, int b);

bool operator <(Complex a, int b);

template <class ForwardIterator, class Type>
bool all_of(ForwardIterator first, ForwardIterator last, bool pred(Type)){
	for (ForwardIterator it = first; it != last; ++it)
		if (!pred(*it))
			return false;
	return true;
}

template <class ForwardIterator, class Type>
bool is_partitioned(ForwardIterator first, ForwardIterator last, bool pred(Type)){
	int k = 0;
	last--;
	for (ForwardIterator it = first; it != last;) { 
		if (pred(*it) != pred(*(++it)))
			k++;
	}
	if (k == 1)
		return true;
	return false;
}

template <class ForwardIterator, class Type>
ForwardIterator find_backward(ForwardIterator first, ForwardIterator last, Type a){
	ForwardIterator res = last;
	for (ForwardIterator it = first; it != last; ++it) 
		if (*it == a) 
			res = it;
	return res;
}

#endif