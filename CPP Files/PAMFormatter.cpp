#include "PAMFormatter.h"
#include"Layer.h"
#include<regex>
#include<string>
PAMFormatter::PAMFormatter() {
	pamHeader.depth = 4;
	pamHeader.ENDHDR = "ENDHDR";
	pamHeader.fileType = "P7";
	pamHeader.tuplType = "RGB_ALPHA";
	pamHeader.maxVal = 255;
}

void PAMFormatter::read(std::string fname, Layer &layer)
{
	
	std::regex r("([^ ]*) [^ ]* ([^ ]*) [^ ]* ([^ ]*) [^ ]* (.) [^ ]* ([^ ]*) [^ ]* ([^ ]*) ([^ ]*) .*");
	std::ifstream file(fname, std::ios_base::binary);
	std::string textline = "";
	std::string buffer;
	std::smatch result;
	if (file) {
		while (std::getline(file, buffer)) {
			textline += buffer + " ";
			if (buffer == "ENDHDR") break;
		}
		if (std::regex_match(textline, result, r)) {
			pamHeader.fileType = result.str(1);
			pamHeader.width = std::atoi(result.str(2).c_str());
			pamHeader.height = std::atoi(result.str(3).c_str());
			pamHeader.depth = std::atoi(result.str(4).c_str());
			pamHeader.maxVal = std::atoi(result.str(5).c_str());
			pamHeader.tuplType = result.str(6);
			pamHeader.ENDHDR = result.str(7);
		}
		data.resize(pamHeader.width*pamHeader.height*pamHeader.depth);
		file.read((char*)data.data(), data.size());
		for (uint32_t y = 0; y < pamHeader.height; ++y) {
			for (uint32_t x = 0; x < pamHeader.width; ++x) {
				layer.pixels.push_back(new Pixel(data[4 * (y * pamHeader.width + x) + 2],
					data[4 * (y * pamHeader.width + x) + 1],
					data[4 * (y * pamHeader.width + x) + 0],
					data[4 * (y * pamHeader.width + x) + 3]));
			}
		}
		layer.width = pamHeader.width;
		layer.height = pamHeader.height;
	}
	else {
		throw Errors("File not found");
	}
	file.close();
}

void PAMFormatter::write(std::string fname,Layer &layer)
{
	pamHeader.height = layer.height;
	pamHeader.width = layer.width;
	data.clear();
	data.resize(layer.getWidth()*layer.getHeight()*pamHeader.depth);
	int i = 0;
	for (int32_t y = 0; y < layer.height; ++y) {
		for (int32_t x = 0; x < layer.width; ++x) {
			data[pamHeader.depth*(y*layer.width + x)+0] = layer.pixels[i]->getRed();
			data[pamHeader.depth*(y*layer.width + x)+1] = layer.pixels[i]->getGreen();
			data[pamHeader.depth*(y*layer.width + x)+2] = layer.pixels[i]->getBlue();
			data[pamHeader.depth*(y*layer.width + x)+3] = layer.pixels[i]->getAlpha();
			i++;
		}
	}
	std::ofstream file(fname, std::ios_base::binary);
	if (file) {
		file << pamHeader.fileType << std::endl;
		file << "WIDTH " << pamHeader.width << std::endl;
		file << "HEIGHT " << pamHeader.height << std::endl;
		file << "DEPTH " << pamHeader.depth << std::endl;
		file << "MAXVAL " << pamHeader.maxVal << std::endl;
		file << "TUPLTYPE " << pamHeader.tuplType << std::endl;
		file << pamHeader.ENDHDR << std::endl;
		file.write((char*)data.data(), data.size());
	}
	else {
		throw Errors("Error!");
	}
	file.close();
}

PAMFormatter::~PAMFormatter()
{
}
