#pragma once
#include<iostream>
#include<exception>
#include<string>
class Errors:public _exception
{
	std::string message;
public:
	Errors(std::string message) :message(message) {};
	friend std::ostream& operator<<(std::ostream& os, const Errors& err) {
		return os << err.message << std::endl;
	}
	~Errors() {}
};

