#include "Layer.h"
#include"BMPFormatter.h"
#include"PAMFormatter.h"
#include"Image.h"
Layer::Layer() {
	width = Image::width;
	height = Image::height;
	transparency = 0.5;
}
Layer::Layer(std::string directory, double transparency)
{
	this->visibleFlag = this->activeFlag = 1;
	this->transparency = transparency/100.0;
	formatter = nullptr;
	std::regex r("[^.]*.(.*)");
	std::smatch result;
	if (std::regex_match(directory, result, r)) {
		if (result.str(1) == "bmp") {
			formatter = new BMPFormatter();
			formatter->read(directory, *this);
			Image::width = Image::width < this->width ? Image::width : this->width;
			Image::height = Image::height < this->height ? Image::height : this->height;
		}
		else if (result.str(1) == "pam") {
			formatter = new PAMFormatter();
			formatter->read(directory, *this);
			Image::width = Image::width < this->width ? Image::width : this->width;
			Image::height = Image::height < this->height ? Image::height : this->height;
		}
		else
			throw Errors("WE DO NOT SUPPORT THAT FORMAT, WE ONLY SUPPORT BMP AND PAM FORMATS");
		
	}
	else
		throw Errors("WRONG PATH");
}
Layer::Layer(int width, int height, double transparency)
{
	this->width = width;
	this->height = height;
	this->transparency = transparency/100.;
	activeFlag = 0;
	visibleFlag = 0;
	formatter = nullptr;
	pixels.resize(width*height);
	for (uint32_t i = 0;i < pixels.size();i++) {
		pixels[i] = new Pixel(0, 0, 0, 255);
	}
	Image::width = Image::width < this->width ? Image::width : this->width;
	Image::height = Image::height < this->height ? Image::height : this->height;
}
Layer::Layer(const Layer &l)
{
	this->activeFlag = l.activeFlag;
	this->visibleFlag = l.visibleFlag;
	this->height = l.height;
	this->width = l.width;
	for (Pixel *p : l.pixels) {
		Pixel *pi = new Pixel(*p);
		pixels.push_back(pi);
	}
}

void Layer::setTransparency(double T)
{
	if (T > 100.) throw Errors("TRANSPARENSY RANGE NEED TO BE BETWEEN 0 AND 100");
	transparency = T;
}

void Layer::fillSelection(Selection *s,int R,int G, int B)
{
	if (s != nullptr) {
		for (Rectangle r : s->getSelection()) {
			fillRectangle(r, R, G, B);
		}
	}
	else {
		std::pair<int, int> position = std::make_pair(0, 0);
		Rectangle r(position, this->width, this->height);
		fillRectangle(r, R, G, B);
	}
}

void Layer::fillRectangle(Rectangle r,int R,int G,int B)
{
	for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
		for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
			pixels[y*width + x]->setRed(R);
			pixels[y*width + x]->setGreen(G);
			pixels[y*width + x]->setBlue(B);
		}
	}
}

void Layer::resizeLayer(int w, int h)
{
	std::vector<Pixel*> p = pixels;
	pixels.resize(w*h);
	for(int y=0;y<h;y++)
		for (int x = 0;x < w;x++) {
			if (x >= width || y>=height)
				pixels[(y*w + x)] = new Pixel(0, 0, 0, 0);
			else pixels[y*w + x] = p[y*width + x];
		}
	width = w;
	height = h;
}
