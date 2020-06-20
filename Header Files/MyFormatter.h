#pragma once
#include "Formatter.h"
#include<fstream>
#include<regex>

class Image;

class MyFormatter :
	public Formatter
{
	Image *image;
	void readLayers(std::ifstream &file, Image *image);
	void readSelection(std::ifstream &file, Image *image);
	void readCombinedImage(std::ifstream &file, Image *image);
	void writeSelection(std::ofstream &file, Image *image);
	void writeLayers(std::ofstream &file, Image *image,std::string fname);
	void writeCombinedImage(std::ofstream &file, Image *image,std::string fname);
public:
	MyFormatter(Image *i) :image(i) {};
	void read(std::string fname, Layer &l)override;
	void write(std::string fname, Layer &l)override;
	virtual ~MyFormatter();
};

