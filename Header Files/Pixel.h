#pragma once
#include<iostream>
class Pixel
{
	static bool composite;
	int red_mask;
	int green_mask;
	int blue_mask;
	int alpha_mask;
public:
	Pixel(uint8_t blue_mask = 0, uint8_t green_mask = 0, uint8_t red_mask = 0, uint8_t alpha_mask = 0);
	Pixel(const Pixel& p);
	Pixel& operator+=(int32_t T);
	friend Pixel operator+(int32_t T, Pixel pixel);
	friend Pixel operator+(Pixel pixel, int32_t T);
	Pixel& operator-=(int32_t T);
	friend Pixel operator-(Pixel pixel, int32_t T);
	friend Pixel operator-(int32_t T, Pixel pixel);
	Pixel& operator*=(int32_t T);
	friend Pixel operator*(Pixel pixel, int32_t T);
	friend Pixel operator*(int32_t T, Pixel pixel);
	Pixel& operator/=(int32_t T);
	friend Pixel operator/(Pixel pixel, int32_t T);
	friend Pixel operator/(int32_t T, Pixel pixel);
	void power(int32_t E);
	void log();
	void abs();
	void min(int k);
	void max(int k);
	int avg();
	void inverse();
	void blackAndWhite();
	int getRed()const { return red_mask; }
	int getBlue()const { return blue_mask; }
	int getGreen()const { return green_mask; }
	int getAlpha()const { return alpha_mask; }
	void setRed(int32_t Red) { red_mask = Red; }
	void setBlue(int32_t Blue) { blue_mask = Blue; }
	void setGreen(int32_t Green) { green_mask = Green; }
	void setAlpha(int32_t Alpha) { alpha_mask = Alpha; }
	static void setComposite() { composite = true; }
	static void resetComposite() { composite = false; }
	friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
	~Pixel();
};

