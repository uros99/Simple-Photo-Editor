#include "Image.h"
#include"Operation.h"
#include"Composite.h"
#include"BMPFormatter.h"
#include"PAMFormatter.h"
#include"MyFormatter.h"

int Image::width = 0;
int Image::height = 0;
bool Image::saveWork = false;

void Image::addSelection()
{
	deleteSelection();
	std::string name;
	std::cout << "Enter the name of selection" << std::endl;
	std::cin >> name;
	selectPixels = new Selection(name);
	int width, height;
	std::pair<int, int> position;
	while (true) {
		std::cout << "Enter the dimensioins for rectangles, if you are done enter 0" << std::endl;
		std::cout << "Width: ";
		std::cin >> width;
		if (width == 0)break;
		std::cout << "Height: ";
		std::cin >> height;
		std::cout << "Position x: ";
		std::cin >> position.first;
		std::cout << "Position y: ";
		std::cin >> position.second;
		if (Image::width < width + position.first || Image::height < height + position.second) {
			delete selectPixels;
			selectPixels = nullptr;
			throw Errors("SELECTION IS OUTSIDE SKOPE OF THE IMAGE");
		}
		Rectangle r(position, width, height);
		selectPixels->addRectangle(r);
		std::cout << "Your ractangle has been added to selection" << std::endl;
	}
}

void Image::createSelection()
{
	if (arrayofLayers.size() == 0) throw Errors("THERE IS NO LAYER TO OPERATE WITH, YOU NEED TO ADD LAYER FIRST");
	if (selectPixels != nullptr) {
		std::string text;
		std::cout << "The selection already exists" << std::endl;
		std::cout << "Do you want to replace it?(Yes/No)" << std::endl;
		std::cin >> text;
		if (text == "Yes")addSelection();
	}
	else addSelection();
}

void Image::deleteSelection()
{
	if (selectPixels != nullptr) {
		delete selectPixels;
		selectPixels = nullptr;
		std::cout << "SELECTION SUCCESSFULLY DELETED" << std::endl;
	}
}

void Image::addLayer()
{
	std::string text;
	Layer *l = nullptr;
	std::cout << "Do you want to add the path of existing image?(Yes/No)" << std::endl;
	std::cin >> text;
	if (text == "Yes") {
		std::string path;
		int transparency;
		std::cout << "Add path: ";
		std::cin >> path;
		std::cout << "Add transparency of layer: ";
		std::cin >> transparency;
		l = new Layer(path, transparency);
	}
	else {
		int width, height, transparency;
		std::cout << "Add width of layer: ";
		std::cin >> width;
		std::cout << "Add height of layer: ";
		std::cin >> height;
		std::cout << "Add transparency of layer";
		std::cin >> transparency;
		l = new Layer(width, height, transparency);
	}
	if (arrayofLayers.size() == 0) {
		width = l->getWidth();
		height = l->getHeight();
	}
	arrayofLayers.push_back(l);
	if (width != l->getWidth() || height != l->getHeight()) {
		width = width < l->getWidth() ? l->getWidth() : width;
		height = height < l->getHeight() ? l->getHeight() : height;
		resize();
	}
}

void Image::addLayer(std::string fname)
{
	Layer *l = new Layer(fname);
	arrayofLayers.push_back(l);
}

void Image::deleteLayer()
{
	if (arrayofLayers.size() == 0) throw Errors("THERE IS NO LAYER");
	uint32_t ind;
	std::cout << "What layer do you want to delete" << std::endl;
	std::cin >> ind;
	if (ind > arrayofLayers.size()) throw Errors("OUT OF BOUNDS");
	delete arrayofLayers[ind - 1];
	arrayofLayers[ind - 1] = nullptr;
	arrayofLayers.erase(arrayofLayers.begin() + ind - 1);
	std::cout << "LAYER SUCCESSFULLY DELETED" << std::endl;
}

void Image::loadProject()
{
	std::string fname;
	std::cout << "Write a path to your project" << std::endl;
	std::cin >> fname;
	MyFormatter *myFormatter = new MyFormatter(this);
	myFormatter->read(fname, *image);
	std::cout << "Your project has been loaded" << std::endl;
}

void Image::saveProject()
{
	std::string fname;
	std::cout << "Write a path to directory where you want to save it" << std::endl;
	std::cin >> fname;
	MyFormatter *formatter = new MyFormatter(this);
	formatter->write(fname, *image);
	std::cout << "Your project has been saved" << std::endl;
}

void Image::add()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Add(this, arg);
	operation->fun();
}

void Image::sub()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Sub(this, arg);
	operation->fun();
}

void Image::invertSub()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new InvertSub(this, arg);
	operation->fun();
}

void Image::mul()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Mul(this, arg);
	operation->fun();
}

void Image::div()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Div(this, arg);
	operation->fun();
}

void Image::invertDiv()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new InvertDiv(this, arg);
	operation->fun();
}

void Image::abs()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	operation = new Abs(this);
	operation->fun();
}

void Image::log()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	operation = new Log(this);
	operation->fun();
}

void Image::power()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Power(this, arg);
	operation->fun();
}

void Image::min()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Min(this, arg);
	operation->fun();
}

void Image::max()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	int arg;
	std::cout << "Enter the argument" << std::endl;
	std::cin >> arg;
	operation = new Max(this, arg);
	operation->fun();
}

void Image::inversion()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	operation = new Inversion(this);
	operation->fun();
}

void Image::blackandwhite()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	operation = new BlackandWhite(this);
	operation->fun();
}

void Image::shadesOfGray()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	operation = new ShadesofGray(this);
	operation->fun();
}

void Image::median()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	operation = new Median(this);
	operation->fun();
}

void Image::mergeLayers()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	for (Layer *l : arrayofLayers) {
		if (l->getVisible() == 1) {
			image = l;
			break;
		}
	}
	for (Layer *l : arrayofLayers) {
		if (image != l && l->getVisible()) {
			std::vector<Pixel*> pixelsImage = image->getPixels();
			std::vector<Pixel*> pixelsLayer = l->getPixels();
			for (uint32_t i = 0;i < pixelsImage.size();i++) {
				double t = image->getTransparency();
				double A0 = pixelsImage[i]->getAlpha();
				double A1 = pixelsLayer[i]->getAlpha();

				double R0 = pixelsImage[i]->getRed();
				double G0 = pixelsImage[i]->getGreen();
				double B0 = pixelsImage[i]->getBlue();
				double R1 = pixelsLayer[i]->getRed();
				double G1 = pixelsLayer[i]->getGreen();
				double B1 = pixelsLayer[i]->getBlue();
				pixelsImage[i]->setRed(static_cast<int32_t>(t*R0 + (1 - t)*R1));
				pixelsImage[i]->setGreen(static_cast<int32_t>(t*G0 + (1 - t)*G1));
				pixelsImage[i]->setBlue(static_cast<int32_t>(t*B0 + (1 - t)*B1));
				pixelsImage[i]->setAlpha(static_cast<int32_t>(t*A0 + (1 - t)*A1));
			}
			image->setTransparency(image->getTransparency() + l->getTransparency() - image->getTransparency()*l->getTransparency());
		}
	}
}

void Image::readComposite()
{
	std::string fname;
	std::cout << "Enter the path to your composite function" << std::endl;
	std::cin >> fname;
	operation = new Composite(this, fname);
	operation->fun();
}

void Image::doCompositeFunction()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	if (dynamic_cast<Composite*>(operation) == nullptr) {
		readComposite();
	}
	else {
		std::string text;
		std::cout << "Composite function already loaded,do you want to change it?(Yes/No)" << std::endl;
		std::cin >> text;
		if (text == "Yes") {
			readComposite();
		}
		else if (text == "No")
			operation->fun();
	}
	std::cout << "Composite function has been done" << std::endl;
}

void Image::doCompositeFunction(std::string fname)
{
	operation = new Composite(this, fname);
	operation->fun();
}

void Image::resize()
{
	std::for_each(arrayofLayers.begin(), arrayofLayers.end(), [&](Layer *l) {
		l->resizeLayer(width, height);
	});
}

void Image::write()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	this->mergeLayers();
	if (image == nullptr) throw Errors("THERE IS NO IMAGE TO EXPORT");
	std::string fname;
	std::cout << "Enter the path where do you want to export image" << std::endl;
	std::cin >> fname;
	Formatter *formatter;
	std::regex r("[^.]*.(.*)");
	std::smatch result;
	if (std::regex_match(fname, result, r)) {
		if (result.str(1) == "bmp") {
			formatter = new BMPFormatter(image->getWidth(), image->getHeight());
			formatter->write(fname, *image);
		}
		else if (result.str(1) == "pam") {
			formatter = new PAMFormatter();
			formatter->write(fname, *image);
		}
		else
			throw Errors("WE ONLY SUPPORT BMP AND PAM FORMATS");
	}
	else
		throw Errors("THE PATH IS INCORRECT");
}

void Image::write(std::string path)
{
	arrayofLayers[0]->write(path);
}

void Image::setVisualFlag()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	uint32_t ind;
	std::cout << "Check the layer you want to set visible flag" << std::endl;
	std::cin >> ind;
	if (ind > arrayofLayers.size()) throw Errors("Out of bounds");
	arrayofLayers[ind - 1]->setVisible();
}

void Image::resetVisualFlag()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	uint32_t ind;
	std::cout << "Check the layer you want to reset visible flag" << std::endl;
	std::cin >> ind;
	if (ind > arrayofLayers.size()) throw Errors("Out of bounds");
	arrayofLayers[ind - 1]->resetVisible();
}

void Image::setActiveFlag()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	uint32_t ind;
	std::cout << "Check the layer you want to set active flag" << std::endl;
	std::cin >> ind;
	if (ind > arrayofLayers.size()) throw Errors("Out of bounds");
	arrayofLayers[ind - 1]->setActive();
}

void Image::resetActiveFlag()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	uint32_t ind;
	std::cout << "Check the layer you want to reset active flag" << std::endl;
	std::cin >> ind;
	if (ind > arrayofLayers.size()) throw Errors("Out of bounds");
	arrayofLayers[ind - 1]->resetActive();
}

void Image::setTransparency()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	uint32_t ind;
	std::cout << "Check the layer you want to reset active flag" << std::endl;
	std::cin >> ind;
	if (ind > arrayofLayers.size()) throw Errors("Out of bounds");
	double transparency;
	std::cout << "Enter new transparency value of the layer" << std::endl;
	std::cin >> transparency;
	arrayofLayers[ind - 1]->setTransparency(transparency);
}

void Image::paintLayer()
{
	if (arrayofLayers.size() == 0) throw Errors("You do not have any layer that could be operated on\n");
	uint32_t i;
	std::cout << "Which layer do you want to paint" << std::endl;
	std::cin >> i;
	if (i > arrayofLayers.size()) throw Errors("Out of bounds!");
	int R, G, B;
	std::cout << "Enter component values(in this order R,G,B): ";
	std::cin >> R >> G >> B;
	arrayofLayers[i - 1]->fillSelection(selectPixels, R, G, B);
}

Image::~Image()
{
}
