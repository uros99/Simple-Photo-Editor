#pragma once
#include"Formatter.h"
#include<vector>
#include<fstream>

enum ArbitraryTuplType {
	BlackAndWhite,
	BlackAndWhiteAlpha,
	Grayscale,
	GrayscaleAlpha,
	RGB,
	RGBAlpha
};
struct PAMHEADER {
	std::string fileType;
	uint32_t width{ 0 };
	uint32_t height{ 0 };
	uint32_t depth{ 0 };
	uint32_t maxVal{ 0 };
	std::string tuplType{ 0 };
	std::string ENDHDR;
	PAMHEADER() {};
};

class Layer;

class PAMFormatter:public Formatter
{
	PAMHEADER pamHeader;
	std::vector<uint8_t> data;
public:
	PAMFormatter();
	void read(std::string fname, Layer &layer) override;
	void write(std::string fname, Layer &layer)override;
	~PAMFormatter();
};


