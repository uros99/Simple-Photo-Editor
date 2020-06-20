#pragma once
#include<iostream>
#include<vector>
#include"Rectangle.h"
class Selection
{
	std::vector<Rectangle> selection;
	std::string nameOfSelection;
	bool activeSelection;
public:
	Selection(std::string ime) :nameOfSelection(ime) {}
	Selection(std::vector<Rectangle> selection, std::string name, bool active=1) :selection(selection), nameOfSelection(name),activeSelection(active) {}
	void addRectangle(Rectangle r) { selection.push_back(r); }
	std::string getNameofSelection() { return nameOfSelection; }
	bool isActive() { return activeSelection; }
	std::vector<Rectangle> getSelection() { return selection; }
	~Selection() {}
};

