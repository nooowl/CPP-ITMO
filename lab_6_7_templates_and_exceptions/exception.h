#ifndef _EXÑEPTION_H_
#define _EXÑEPTION_H_
#include <string>

class Exception{
protected:
	std::string _message;
	std::string _name;
public:
	explicit Exception(const std::string& message, const std::string &name);
	std::string getMessage();
	std::string getName();
};

class IndexException : public Exception{
public:
	 IndexException(int a, int b);
};
#endif