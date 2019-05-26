#include "exñeption.h"
#include <string>

Exception::Exception(const std::string &message, const std::string &name){
	_message = message;
	_name = name;
}

std::string Exception::getMessage() {
	return _message;
}

std::string Exception::getName() {
	return _name;
}

IndexException::IndexException(int a, int b) : Exception("Index out of array!\n" + std::to_string(a) + " " + std::to_string(b), "IndexException") {
}