#pragma once
#include<iostream>
#include<vector>
#include<regex>
#include"Formatter.h"
#include"Pixel.h"
#include"Selection.h"

class BMPFormatter;
class PAMFormatter;
class Image;
class Layer
{
	std::vector<Pixel*> pixels;
	bool visibleFlag;
	bool activeFlag;
	double transparency;
	int width;
	int height;
	Formatter *formatter;
	void fillRectangle(Rectangle r, int R, int G, int B);
public:
	friend BMPFormatter;
	friend PAMFormatter;
	Layer();
	Layer(std::string directory, double transparency=100);
	Layer(int width, int height,double transparency=100);
	Layer(const Layer&);
	void setVisible() { visibleFlag = true; }
	void resetVisible() { visibleFlag = false; }
	void setActive() { activeFlag = true; }
	void resetActive() { activeFlag = false; }
	void setTransparency(double T);
	double getTransparency()const { return transparency; }
	bool getVisible()const { return visibleFlag; }
	bool getActive()const { return activeFlag; }
	int getWidth()const { return width; }
	int getHeight()const { return height; }
	void fillSelection(Selection* s, int R, int G, int B);
	void write(std::string fname) { formatter->write(fname, *this); }
	std::vector<Pixel*> getPixels()const { return pixels; }
	void setPixels(std::vector<Pixel*> pixels) { this->pixels = pixels; }
	void resizeLayer(int w,int h);
	Formatter* getFormatter() { return formatter; }
	~Layer() {};
};

