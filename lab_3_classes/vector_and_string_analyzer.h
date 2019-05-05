#ifndef _CLASS_H_
#define _CLASS_H_
#include <set>
#include <string>

class vector{
	private:
		double x, y, z;
	public:
		vector(double a, double b, double c);
		double get_x();
		double get_y();
		double get_z();
		static vector sum(vector f, vector s);
		static vector sub(vector f, vector s);
		double len();
		double angle(vector n);
		void print();
};

class stringAnalyzer{
	private:
		std::string s;
		std::set<char> splitChars;		
		int pos = 0;
		int length;
		void skipSplit();
	public:
		stringAnalyzer(std::string newS);
		void addChar(char c);
		void clear();
		std::string nextString();
		bool isEnd();
};

#endif