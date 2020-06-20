#pragma once
#include"Operation.h"
#include"Errors.h"
#include<regex>
#include<map>
#include<fstream>

class Composite :
	public Operation
{
	enum Functions {
		ADD, SUB, INVERTSUB, MUL, DIV, INVERTDIV, LOG, ABS, POWER, MIN, MAX, SHADESOFGRAY, INVERSION, BLACKWHITE, MEDIAN, COMPOSITE
	};
	std::vector<Operation*> operations;
	std::string fname;
	std::map<std::string, Functions> functions;
	Image *image;
public:
	Composite(Image *i,std::string fname);
	void fun()override;
	void write(std::string);
	std::string nameofOperation()override;
	std::string getArg()override;
	virtual ~Composite();
};

