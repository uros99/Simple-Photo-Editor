#include "BMPFormatter.h"
#include"Layer.h"

void BMPFormatter::write_headers(std::ofstream & of)
{
	of.write((const char*)&bmpHeader, sizeof(bmpHeader));
	of.write((const char*)&bmpInfo, sizeof(bmpInfo));
	if (bmpInfo.bit_count == 32) {
		of.write((const char*)&bmpColor, sizeof(bmpColor));
	}
}

void BMPFormatter::write_headers_and_data(std::ofstream & of)
{
	write_headers(of);
	of.write((const char*)data.data(), data.size());
}

BMPFormatter::BMPFormatter()
{
}

BMPFormatter::BMPFormatter(int32_t width, int32_t height, bool has_alpha)
{

     if (width <= 0 || height <= 0) {
        throw std::runtime_error("The image width and height must be positive numbers.");
	 }
	 bmpInfo.width = width;
	 bmpInfo.height = height;
	 bmpInfo.size = sizeof(BMPINFOHEADER) + sizeof(BMPCOLORHEADER);
     bmpHeader.offsetData = sizeof(BMPFILEHEADER) + sizeof(BMPINFOHEADER) + sizeof(BMPCOLORHEADER);		
     bmpInfo.bit_count = 32;
	 bmpInfo.compression = 3;
	 row_stride = width * 4;
	 data.resize(row_stride * height);
	 bmpHeader.fileSize = bmpHeader.offsetData + data.size();
	 bmpHeader.fileType = 0x4D42;
}

void BMPFormatter::read(std::string fname, Layer &layer)
{
	std::ifstream file(fname, std::ios_base::binary);
	if (file) {
		file.read((char*)&bmpHeader, sizeof(bmpHeader));
		if (bmpHeader.fileType != 0x4D42) {
			throw Errors("Error! Unrecognized file format");
		}
		file.read((char*)&bmpInfo, sizeof(bmpInfo));
		file.read((char*)&bmpColor, sizeof(bmpColor));
	//	check_color_header(bmpColor);
		file.seekg(bmpHeader.offsetData, file.beg);
		bmpInfo.size = sizeof(BMPINFOHEADER) + sizeof(BMPCOLORHEADER);
		bmpHeader.offsetData = sizeof(BMPFILEHEADER) + sizeof(BMPINFOHEADER) + sizeof(BMPCOLORHEADER);
		bmpHeader.fileSize = bmpHeader.offsetData;
		if (bmpInfo.height < 0) {
			throw Errors("Height<0");
		}
		data.resize(bmpInfo.width*bmpInfo.height*bmpInfo.bit_count / 8);
		file.read((char*)data.data(), data.size());
		bmpHeader.fileSize += data.size();
		int32_t channels = bmpInfo.bit_count / 8;
		for (int32_t y = bmpInfo.height-1; y >=0; --y) {
			for (int32_t x = 0; x < bmpInfo.width; ++x) {
				layer.pixels.push_back(new Pixel(data[channels * (y * bmpInfo.width + x) + 0],
					data[channels * (y * bmpInfo.width + x) + 1],
					data[channels * (y * bmpInfo.width + x) + 2],
					data[channels * (y * bmpInfo.width + x) + 3]));
			}
		}
		layer.width = bmpInfo.width;
		layer.height = bmpInfo.height;
	}
	else {
		throw Errors("Unable to open file");
	}
	file.close();
}

void BMPFormatter::write(std::string fname, Layer &layer)
{
	bmpInfo.height = layer.height;
	bmpInfo.width = layer.width;
	data.clear();
	data.resize(layer.getWidth()*layer.getHeight()*bmpInfo.bit_count / 8);
	std::ofstream of{ fname, std::ios_base::binary };
	if (of) {
		int i = 0;
		int32_t channels = bmpInfo.bit_count / 8;
		for (int32_t y = bmpInfo.height - 1; y >= 0; --y) {
			for (int32_t x = 0; x < layer.width; ++x) {
				data[channels * (y * layer.width + x) + 0] = layer.pixels[i]->getBlue();
				data[channels * (y * layer.width + x) + 1] = layer.pixels[i]->getGreen();
				data[channels * (y * layer.width + x) + 2] = layer.pixels[i]->getRed();
				data[channels * (y * layer.width + x) + 3] = layer.pixels[i]->getAlpha();
				i++;
			}
		}
		write_headers_and_data(of);	
	}
	else {
		throw Errors("Unable to open the output image file.");
	}
	of.close();
}

BMPFormatter::~BMPFormatter()
{
}