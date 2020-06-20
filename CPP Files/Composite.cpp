#include "Composite.h"

Composite::Composite(Image *i,std::string fname)
{
	image = i;
	this->fname = fname;
	functions["Add"] = Functions::ADD;
	functions["Sub"] = Functions::SUB;
	functions["InvSub"] = Functions::INVERTSUB;
	functions["Mul"] = Functions::MUL;
	functions["Div"] = Functions::DIV;
	functions["InvDiv"] = Functions::INVERTDIV;
	functions["Power"] = Functions::POWER;
	functions["Log"] = Functions::LOG;
	functions["Abs"] = Functions::ABS;
	functions["Min"] = Functions::MIN;
	functions["Max"] = Functions::MAX;
	functions["Inversion"] = Functions::INVERSION;
	functions["BlackandWhite"] = Functions::BLACKWHITE;
	functions["ShadesofGray"] = Functions::SHADESOFGRAY;
	functions["Median"] = Functions::MEDIAN;
	functions["Composite"] = Functions::COMPOSITE;

	std::ifstream file(fname);
	if (file) {
		std::regex header(".*(<CompositeFunction>)");
		std::regex function(".*<function>([^<]*)</function>.*");
		std::regex param(".*<param>([^<]*)</param>");
		std::regex end("(.*</CompositeFunction>)");
		std::string textLine;
		std::smatch result;
		getline(file, textLine);
		if (std::regex_match(textLine, result, header)) {
			while (getline(file, textLine)) {
				if (std::regex_match(textLine, result, end)) break;
				if (std::regex_match(textLine, result, function)) {
					std::string composite = result.str(1);
					getline(file, textLine);
					if (std::regex_match(textLine, result, param)) {
						std::string arg = result.str(1);
						switch (functions[composite.c_str()])
						{
						case Functions::ADD: operations.push_back(new Add(image, std::atoi(arg.c_str())));break;
						case Functions::ABS: operations.push_back(new Abs(image));break;
						case Functions::BLACKWHITE: operations.push_back(new BlackandWhite(image));break;
						case Functions::DIV: operations.push_back(new Div(image, std::atoi(arg.c_str())));break;
						case Functions::INVERSION: operations.push_back(new Inversion(image));break;
						case Functions::INVERTDIV: operations.push_back(new InvertDiv(image, std::atoi(arg.c_str())));break;
						case Functions::INVERTSUB: operations.push_back(new InvertSub(image, std::atoi(arg.c_str())));break;
						case Functions::LOG: operations.push_back(new Log(image));break;
						case Functions::MAX: operations.push_back(new Max(image, std::atoi(arg.c_str())));break;
						case Functions::MIN: operations.push_back(new Min(image, std::atoi(arg.c_str())));break;
						case Functions::MEDIAN: operations.push_back(new Median(image));break;
						case Functions::MUL: operations.push_back(new Mul(image, std::atoi(arg.c_str())));break;
						case Functions::POWER: operations.push_back(new Power(image, std::atoi(arg.c_str())));break;
						case Functions::SHADESOFGRAY: operations.push_back(new ShadesofGray(image));break;
						case Functions::SUB: operations.push_back(new Sub(image, std::atoi(arg.c_str())));break;
						case Functions::COMPOSITE: operations.push_back(new Composite(i, arg));break;
						}
					}
				}
			}
		}
		else {
			throw Errors("No suitable format of compsite function");
		}
	}
	else {
		throw Errors("File not found\n");
	}
	file.close();
}

void Composite::fun()
{
	Pixel::setComposite();
	for (Operation *o : operations) {
		o->fun();
	}
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [&](Layer *l) {
		std::vector<Pixel*> pixels = l->getPixels();
		std::for_each(pixels.begin(), pixels.end(), [&](Pixel *p) {
			if (p->getRed() > 255)p->setRed(255);
			else if (p->getRed() < 0)p->setRed(0);
			if (p->getGreen() > 255)p->setGreen(255);
			else if (p->getGreen() < 0)p->setGreen(0);
			if (p->getBlue() > 255)p->setBlue(255);
			else if (p->getBlue() < 0)p->setBlue(0);
			if (p->getAlpha() > 255)p->setAlpha(255);
			else if (p->getAlpha() < 0)p->setAlpha(0);
		});
	});
}

void Composite::write(std::string fname)
{
	std::ofstream file(fname);
	if (file) {
		file << "<CompositeFunction>" << std::endl;
		for (Operation *it : operations) {
			file << "/t<function>" << it->nameofOperation() << "</function>" << std::endl;
			file << "/t/t<param>" << it->getArg() << "</param>" << std::endl;
		}
		file << "</CompositeFunction>";
	}
	else
		throw Errors("File not found!");
	file.close();
}

std::string Composite::nameofOperation()
{
	return "Composite";
}

std::string Composite::getArg()
{
	return fname;
}

Composite::~Composite()
{
}
