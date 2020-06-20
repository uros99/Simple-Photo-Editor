#include "MyFormatter.h"
#include"Image.h"
#include"Composite.h"
#include"BMPFormatter.h"
#include"PAMFormatter.h"
void MyFormatter::read(std::string fname, Layer & l)
{
	std::ifstream file(fname);
	std::regex begin("<MyProject>");
	std::regex end("</MyProject>");
	std::regex header("\t<header>");
	std::regex endHeader("\t</header>");
	std::regex selection("\t<selection>");
	std::regex beginofLayers("\t<arrayofLayers>");
	std::regex composite("\t<compositeFunction>([^<]*)</compositeFunction>");
	std::regex combinedImage("\t<combinedImage>");
	std::smatch result;

	if (file) {
		std::string textline;
		getline(file, textline);
		if (std::regex_match(textline, result, begin)) {
			getline(file, textline);
			if (std::regex_match(textline, result, header)) {
				getline(file, textline);
				if (std::regex_match(textline, result, selection)) {
					readSelection(file, image);
					getline(file, textline);
				}
				if (std::regex_match(textline, result, beginofLayers)) {
					readLayers(file, image);
					getline(file, textline);
				}
				if (std::regex_match(textline, result, composite)) {
					std::string fname = result.str(1);
					image->operation = new Composite(image, fname);
					getline(file, textline);
				}
				if (std::regex_match(textline, result, endHeader)) {
					getline(file, textline);
					if (std::regex_match(textline, result, combinedImage)) {
						readCombinedImage(file, image);
						getline(file, textline);
					}
					if (std::regex_match(textline, result, end)) {
						std::cout << "Your project is successfully loaded" << std::endl;
					}
				}
			}
			else
				throw Errors("This project does not contain a header");
		}
		else
			throw Errors("Wrong Format");
	}
	else
		throw Errors("File not found!");
	file.close();
}

void MyFormatter::write(std::string fname, Layer & l)
{
	std::ofstream file(fname + "\\MyProject.txt");
	if (file) {
		file << "<MyProject>" << std::endl;
		file << "\t<header>" << std::endl;
		if (image->selectPixels != nullptr) {
			writeSelection(file, image);
		}
		if (image->arrayofLayers.size() > 0) {
			writeLayers(file, image,fname);
		}
		if (dynamic_cast<Composite*>(image->operation) != nullptr) {
			Composite *composite = (Composite*)image->operation;
			composite->write(fname + "\\Composite.fun");
			file << "\t<compositeFunction>" << fname + "\\Composite.fun" << "</compositeFunction>" << std::endl;
		}
		file << "\t</header>" << std::endl;
		if (image->image != nullptr) {
			writeCombinedImage(file, image,fname);
		}
		file << "</MyProject>";
	}
	else
		throw Errors("File not found!");
	file.close();
}

void MyFormatter::readLayers(std::ifstream & file, Image * image)
{
	std::regex path("\t\t\t<path>([^<]*)</path>");
	std::regex opacity("\t\t\t<transparency>([^<]*)</transparency>");
	std::regex width("\t\t\t<width>([^<]*)</width>");
	std::regex height("\t\t\t<height>([^<]*)</height>");
	std::regex visibleFlag("\t\t\t<visibleFlag>(.)</visibleFlag>");
	std::regex activeFlag("\t\t\t<activeFlag>(.)</activeFlag>");
	std::regex endofLayers("\t</arrayofLayers>");
	std::regex layer("\t\t<layer>");
	std::regex end("\t\t</layer>");
	std::string textline;
	std::smatch result;
	while (getline(file, textline)) {
		if (std::regex_match(textline, result, endofLayers))break;
		if (std::regex_match(textline, result, layer)) {
			getline(file, textline);
			if (std::regex_match(textline, result, path)) {
				std::string fname = result.str(1);
				getline(file, textline);
				std::regex_match(textline, result, opacity);
				int transparency = atoi(result.str(1).c_str());
				getline(file, textline);
				std::regex_match(textline, result, visibleFlag);
				int visible = atoi(result.str(1).c_str());
				getline(file, textline);
				std::regex_match(textline, result, activeFlag);
				int active = atoi(result.str(1).c_str());
				Layer *l = new Layer(fname, transparency);
				visible == 1 ? l->setVisible() : l->resetVisible();
				active == 1 ? l->setActive() : l->resetActive();
				l->setTransparency(transparency);
				image->arrayofLayers.push_back(l);
				getline(file, textline);
				if (std::regex_match(textline, result, end))continue;
			}
			else if (std::regex_match(textline, result, width)) {
				int width = atoi(result.str(1).c_str());
				getline(file, textline);
				std::regex_match(textline, result, height);
				int height = atoi(result.str(1).c_str());
				getline(file, textline);
				std::regex_match(textline, result, opacity);
				int transparency = atoi(result.str(1).c_str());
				getline(file, textline);
				std::regex_match(textline, result, visibleFlag);
				int visible = atoi(result.str(1).c_str());
				getline(file, textline);
				std::regex_match(textline, result, activeFlag);
				int active = atoi(result.str(1).c_str());
				Layer *l = new Layer(width, height, transparency);
				visible == 1 ? l->setVisible() : l->resetVisible();
				active == 1 ? l->setActive() : l->resetActive();
				image->arrayofLayers.push_back(l);
				getline(file, textline);
				if (std::regex_match(textline, result, end))continue;
			}
		}
	}
}

void MyFormatter::readSelection(std::ifstream & file, Image * image)
{
	std::regex nameofSelection("\t\t<name>([^<]*)</name>");
	std::regex endofSelection("\t</selection>");
	std::regex rectPosition("\t\t<RectanglePosition>([^,]*),([^<]*)</RectanglePosition>.*");
	std::regex rectDimension("\t\t<RectangleDimension>([^,]*),([^<]*)</RectangleDimension>.*");
	std::string textline;
	std::smatch result;
	getline(file, textline);
	std::regex_match(textline, result, nameofSelection);
	std::string name = result.str(1);
	image->selectPixels = new Selection(name);
	while (getline(file, textline)) {
		if (std::regex_match(textline, result, endofSelection))break;
		std::regex_match(textline, result, rectPosition);
		int x = atoi(result.str(1).c_str());
		int y = atoi(result.str(2).c_str());
		std::pair<int, int> position = std::make_pair(x, y);
		getline(file, textline);
		std::regex_match(textline, result, rectDimension);
		int width = atoi(result.str(1).c_str());
		int height = atoi(result.str(2).c_str());
		Rectangle r(position, width, height);
		image->selectPixels->addRectangle(r);
	}
}

void MyFormatter::readCombinedImage(std::ifstream & file, Image * image)
{
	std::regex path("\t\t<path>([^<]*)</path>");
	std::regex opacity("\t\t<transparency>([^<]*)</transparency>");
	std::regex width("\t\t<width>([^<]*)</width>");
	std::regex height("\t\t<height>([^<]*)</height>");
	std::regex visibleFlag("\t\t<visibleFlag>(.)</visibleFlag>");
	std::regex activeFlag("\t\t<activeFlag>(.)</activeFlag>");
	std::regex end("\t</combinedImage>");
	std::smatch result;
	std::string textline;
	while (getline(file, textline)) {
		if (std::regex_match(textline, result, end))break;
		if (std::regex_match(textline, result, path)) {
			std::string fname = result.str(1);
			getline(file, textline);
			std::regex_match(textline, result, opacity);
			int transparency = atoi(result.str(1).c_str());
			getline(file, textline);
			std::regex_match(textline, result, visibleFlag);
			int visible = atoi(result.str(1).c_str());
			getline(file, textline);
			std::regex_match(textline, result, activeFlag);
			int active = atoi(result.str(1).c_str());
			Layer *l = new Layer(fname, transparency);
			visible == 1 ? l->setVisible() : l->resetVisible();
			active == 1 ? l->setActive() : l->resetActive();
			l->setTransparency(transparency);
			image->image = l;
		}
	}
}

void MyFormatter::writeSelection(std::ofstream & file, Image * image)
{
	file << "\t<selection>" << std::endl;
	file << "\t\t<name>" << image->selectPixels->getNameofSelection() << "</name>" << std::endl;
	for (Rectangle r : image->selectPixels->getSelection()) {
		file << "\t\t<RectanglePosition>" << r.getPosition().first << "," << r.getPosition().second << "</RectanglePosition>" << std::endl;
		file << "\t\t<RectangleDimension>" << r.getWidth() << "," << r.getHeight() << "</RectangleDimension>" << std::endl;
	}
	file << "\t</selection>" << std::endl;
}

void MyFormatter::writeLayers(std::ofstream & file, Image * image,std::string fname)
{
	file << "\t<arrayofLayers>" << std::endl;
	char i = 0;
	for (Layer *l : image->arrayofLayers) {
		file << "\t\t<layer>" << std::endl;
		if (l->getFormatter() != nullptr) {
			std::string format;
			if (dynamic_cast<BMPFormatter*>(l->getFormatter()) != nullptr) {
				format = ".bmp";
			}
			else
				format = ".pam";
			file << "\t\t\t<path>" << fname + "\\Layer" + std::to_string(i) + format << "</path>" << std::endl;
			file << "\t\t\t<transparency>" << l->getTransparency()*100 << "</transparency>" << std::endl;
			file << "\t\t\t<visibleFlag>" << l->getVisible() << "</visibleFlag>" << std::endl;
			file << "\t\t\t<activeFlag>" << l->getActive() << "</activeFlag>" << std::endl;
			l->write(fname + "\\Layer" + std::to_string(i) + format);
			i++;
		}
		else {
			file << "\t\t\t<width>" << l->getWidth() << "</width>" << std::endl;
			file << "\t\t\t<height>" << l->getHeight() << "</height>" << std::endl;
			file << "\t\t\t<transparency>" << l->getTransparency()*100 << "</transparency>" << std::endl;
			file << "\t\t\t<visibleFlag>" << l->getVisible() << "</visibleFlag>" << std::endl;
			file << "\t\t\t<activeFlag>" << l->getActive() << "</activeFlag>" << std::endl;
		}
		file << "\t\t</layer>" << std::endl;
	}
	file << "\t</arrayofLayers>" << std::endl;
}

void MyFormatter::writeCombinedImage(std::ofstream & file, Image * image,std::string fname)
{
	std::string format;
	std::cout << "Do you want to save your final image in pam or bmp format?(pam/bmp)" << std::endl;
	std::cin >> format;
	Formatter *formatter;
	if (format == "bmp")
		formatter = new BMPFormatter(image->image->getWidth(), image->image->getHeight());
	else if (format == "pam")
		formatter = new PAMFormatter();
	else
		throw Errors("WE DO NOT SUPPORT THAT FORMAT");

	file << "\t<combinedImage>" << std::endl;
	file << "\t\t<path>" << fname + "\\CombinedImage." + format << "</path>" << std::endl;
	file << "\t\t<transparency>" << image->image->getTransparency() << "</transparency>" << std::endl;
	file << "\t\t<visibleFlag>" << image->image->getVisible() << "</visibleFlag>" << std::endl;
	file << "\t\t<activeFlag>" << image->image->getActive() << "</activeFlag>" << std::endl;
	file << "\t</combinedImage>" << std::endl;
	formatter->write(fname + "\\CombinedImage." + format, *image->image);
}


MyFormatter::~MyFormatter()
{
}
