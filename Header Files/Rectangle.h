#pragma once
#include<iostream>

class Rectangle
{
	std::pair<int, int> position;
	int width;
	int height;
public:
	Rectangle(std::pair<int, int> position, int width, int height) : position(position), width(width), height(height) {}
	int getWidth()const { return width; }
	int getHeight()const { return height; }
	std::pair<int, int> getPosition() { return position; }
	~Rectangle() {}
};

