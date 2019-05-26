#include "exñeption.h"
#include <string>

template <int N, typename T>
class Array{
private:
	T _array[N];
public:
	Array(T* array){
		for (int i = 0; i < N; i++)
			_array[i] = array[i];
	};
	void swap(int a, int b){
		if (a >= N || b >= N || b < 0 || a < 0) throw IndexException(a, b);
		else {
			T temp(_array[a]);
			_array[a] = _array[b];
			_array[b] = temp;
		}
	};
	void print(){
		for (int i = 0; i < N; i++)
			cout << _array[i] << " ";
	};
};





