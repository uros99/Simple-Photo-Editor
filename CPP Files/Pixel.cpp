#include "Pixel.h"
#include<cmath>

bool Pixel::composite = false;

Pixel::Pixel(uint8_t blue_mask, uint8_t green_mask, uint8_t red_mask, uint8_t alpha_mask)
{
	this->red_mask = red_mask;
	this->green_mask = green_mask;
	this->blue_mask = blue_mask;
	this->alpha_mask = alpha_mask;
}

Pixel::Pixel(const Pixel & p)
{
	red_mask = p.red_mask;
	blue_mask = p.blue_mask;
	green_mask = p.green_mask;
	alpha_mask = p.alpha_mask;

}

Pixel & Pixel::operator+=(int32_t T)
{
	red_mask = red_mask + T >= 255 && !composite ? 255 : red_mask + T;
	green_mask = green_mask + T >= 255 && !composite ? 255 : green_mask + T;
	blue_mask = blue_mask + T >= 255 && !composite ? 255 : blue_mask + T;
	return *this;
}

Pixel & Pixel::operator-=(int32_t T)
{
	red_mask = red_mask - T <= 0 && !composite ? 0 : red_mask - T;
	blue_mask = blue_mask - T <= 0 && !composite ? 0 : blue_mask - T;
	green_mask = green_mask - T <= 0 && !composite ? 0 : green_mask - T;
	return *this;
}

Pixel & Pixel::operator*=(int32_t T)
{
	red_mask = red_mask * T >= 255 && !composite ? 255 : red_mask * T;
	green_mask = green_mask * T >= 255 && !composite ? 255 : green_mask * T;
	blue_mask = blue_mask * T >= 255 && !composite ? 255 : blue_mask * T;
	return *this;
}

Pixel & Pixel::operator/=(int32_t T)
{
	red_mask = red_mask / T <= 0 && !composite ? 0 : red_mask / T;
	blue_mask = blue_mask / T <= 0 && !composite ? 0 : blue_mask / T;
	green_mask = green_mask / T <= 0 && !composite ? 0 : green_mask / T;
	return *this;
}

void Pixel::power(int32_t E)
{
	red_mask = pow(red_mask, E) >= 255 && !composite ? 255 : static_cast<int32_t>(pow(red_mask, E));
	green_mask = pow(green_mask, E) >= 255 && !composite ? 255 : static_cast<int32_t>(pow(green_mask, E));
	blue_mask = pow(blue_mask, E) >= 255 && !composite ? 255 : static_cast<int32_t>(pow(blue_mask, E));
}

void Pixel::log()
{
	red_mask = red_mask > 0 ? static_cast<int32_t>(std::log(red_mask)) : 0;
	green_mask = green_mask > 0 ? static_cast<int32_t>(std::log(green_mask)) : 0;
	blue_mask = blue_mask > 0 ? static_cast<int32_t>(std::log(blue_mask)) : 0;
}

void Pixel::abs()
{
	red_mask=std::abs(red_mask);
	green_mask=std::abs(green_mask);
	blue_mask=std::abs(blue_mask);
}

void Pixel::min(int k)
{
	red_mask = red_mask > k ? k : red_mask;
	green_mask = green_mask > k ? k : green_mask;
	blue_mask = blue_mask > k ? k : blue_mask;
}

void Pixel::max(int k)
{
	red_mask = red_mask < k ? k : red_mask;
	green_mask = green_mask < k ? k : green_mask;
	blue_mask = blue_mask < k ? k : blue_mask;
}

int Pixel::avg()
{
	return (red_mask + blue_mask + green_mask) / 3;
}

void Pixel::inverse()
{
	red_mask = 255 - red_mask;
	green_mask = 255 - green_mask;
	blue_mask = 255 - blue_mask;
}

void Pixel::blackAndWhite()
{
	int avg = this->avg();
	if (avg < 127) {
		red_mask = green_mask = blue_mask = 0;
	}
	else
		red_mask = green_mask = blue_mask = 255;
}

Pixel::~Pixel()
{
}

Pixel operator+(int32_t T, Pixel pixel)
{
	Pixel tmpPixel;
	tmpPixel.red_mask = pixel.red_mask + T >= 255 && !Pixel::composite ? 255 : pixel.red_mask + T;
	tmpPixel.green_mask = pixel.green_mask + T >= 255 && !Pixel::composite ? 255 : pixel.green_mask + T;
	tmpPixel.blue_mask = pixel.blue_mask + T >= 255 && !Pixel::composite ? 255 : pixel.blue_mask + T;
	tmpPixel.alpha_mask = pixel.alpha_mask;
	return tmpPixel;
}

Pixel operator+(Pixel pixel, int32_t T)
{
	return T + pixel;
}


Pixel operator-(Pixel pixel, int32_t T)
{
	Pixel tmpPixel;
	tmpPixel.red_mask = pixel.red_mask - T <= 0 && !Pixel::composite ? 0 : pixel.red_mask - T;
	tmpPixel.green_mask = pixel.green_mask - T <= 0 && !Pixel::composite ? 0 : pixel.green_mask - T;
	tmpPixel.blue_mask = pixel.blue_mask - T <= 0 && !Pixel::composite ? 0 : pixel.blue_mask - T;
	tmpPixel.alpha_mask = pixel.alpha_mask;
	return tmpPixel;
}

Pixel operator-(int32_t T, Pixel pixel)
{
	Pixel tmpPixel;
	tmpPixel.red_mask = T - pixel.red_mask <= 0 && !Pixel::composite ? 0 : T - pixel.red_mask;
	tmpPixel.green_mask = T - pixel.green_mask <= 0 && !Pixel::composite ? 0 : T - pixel.green_mask;
	tmpPixel.blue_mask = T - pixel.blue_mask <= 0 && !Pixel::composite ? 0 : T - pixel.blue_mask;
	tmpPixel.alpha_mask = pixel.alpha_mask;
	return tmpPixel;
}

Pixel operator*(Pixel pixel, int32_t T)
{
	Pixel tmpPixel;
	tmpPixel.red_mask = pixel.red_mask * T >= 255 && !Pixel::composite ? 255 : pixel.red_mask * T;
	tmpPixel.green_mask = pixel.green_mask * T >= 255 && !Pixel::composite ? 255 : pixel.green_mask * T;
	tmpPixel.blue_mask = pixel.blue_mask * T >= 255 && !Pixel::composite ? 255 : pixel.blue_mask * T;
	tmpPixel.alpha_mask = pixel.alpha_mask;
	return tmpPixel;
}

Pixel operator*(int32_t T, Pixel pixel)
{
	return pixel * T;
}

Pixel operator/(Pixel pixel, int32_t T)
{
	Pixel tmpPixel;
	tmpPixel.red_mask = pixel.red_mask / T <= 0 && !Pixel::composite ? 0 : pixel.red_mask / T;
	tmpPixel.green_mask = pixel.green_mask / T <= 0 && !Pixel::composite ? 0 : pixel.green_mask / T;
	tmpPixel.blue_mask = pixel.blue_mask / T <= 0 && !Pixel::composite ? 0 : pixel.blue_mask / T;
	tmpPixel.alpha_mask = pixel.alpha_mask;
	return tmpPixel;
}

Pixel operator/(int32_t T, Pixel pixel)
{
	Pixel tmpPixel;
	tmpPixel.red_mask = T / pixel.red_mask <= 0 && !Pixel::composite ? 0 : T / pixel.red_mask;
	tmpPixel.green_mask = T / pixel.green_mask <= 0 && !Pixel::composite ? 0 : T / pixel.green_mask;
	tmpPixel.blue_mask = T / pixel.blue_mask <= 0 && !Pixel::composite ? 0 : T / pixel.blue_mask;
	tmpPixel.alpha_mask = pixel.alpha_mask;
	return tmpPixel;
}

std::ostream & operator<<(std::ostream & os, const Pixel & p)
{
	os <<"Crvena: "<< p.red_mask << std::endl;
	os << "Zelena: " << p.green_mask << std::endl;
	os << "Plava: " << p.blue_mask << std::endl;
	os << "Alpha: " << p.alpha_mask << std::endl;
	return os;
}
