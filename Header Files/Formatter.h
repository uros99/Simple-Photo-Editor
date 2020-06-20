#pragma once
#include<vector>
#include"Pixel.h"
#include"Errors.h"

class Layer;

class Formatter
{
public:
	Formatter() {}
	virtual void read(std::string fname, Layer &layer) = 0;
	virtual void write(std::string directory, Layer &layer) = 0;
	~Formatter() {}
};

