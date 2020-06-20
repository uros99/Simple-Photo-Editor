#pragma once
#include<regex>
#include"Layer.h"

class Operation;
class MyFormatter;
class Image
{
	std::vector<Layer*> arrayofLayers;
	Selection *selectPixels = nullptr;
	Layer *image;
	Operation *operation;
	static int width;
	static int height;
	void readComposite();
	void resize();
	void addSelection();
protected:
	Image() { selectPixels = nullptr; image = nullptr; operation = nullptr; }
	static bool saveWork;
public:
	friend MyFormatter;
	friend Layer;
	void createSelection();
	void deleteSelection();
	void addLayer();
	void addLayer(std::string fname);
	void deleteLayer();
	void loadProject();
	void saveProject();
	void add();
	void sub();
	void invertSub();
	void mul();
	void div();
	void invertDiv();
	void abs();
	void log();
	void power();
	void min();
	void max();
	void inversion();
	void blackandwhite();
	void shadesOfGray();
	void median();
	void mergeLayers();
	void doCompositeFunction();
	void doCompositeFunction(std::string fname);
	void write();
	void write(std::string path);
	void setVisualFlag();
	void resetVisualFlag();
	void setActiveFlag();
	void resetActiveFlag();
	void setTransparency();
	void paintLayer();
	std::vector<Layer*> getLayers() { return arrayofLayers; }
	Selection* getSelectioin() { return selectPixels; }
	~Image();
};

