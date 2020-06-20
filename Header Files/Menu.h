#pragma once
#include "Image.h"
class Menu :
	public Image
{
public:
	Menu() {};
	void menu() {
		int i = 0;
		do {
			try {
				std::cout << "If you want to do some of function below, pick the number" << std::endl;
				std::cout << "To exit program press button 0" << std::endl;
				std::cout << "1.Create selection" << std::endl;
				std::cout << "2.Add a layer in your image" << std::endl;
				std::cout << "3.Combine layers" << std::endl;
				std::cout << "4.Export image" << std::endl;
				std::cout << "5.Do composite funtion" << std::endl;
				std::cout << "6.Do arithmetic functioin" << std::endl;
				std::cout << "7.Do you want to change flags or tansparency on some layers?" << std::endl;
				std::cout << "8.Load existing project" << std::endl;
				std::cout << "9.Save your work" << std::endl;
				std::cout << "10.Do you want to paint a layer" << std::endl;
				std::cout << "11.Do you want to delete selection" << std::endl;
				std::cout << "12.Do you want to delete some layer" << std::endl;
				std::cin >> i;
				switch (i) {
				case 0:exitProgram();break;
				case 1:createSelection();saveWork = true;break;
				case 2:addLayer();saveWork = true;break;
				case 3:mergeLayers();saveWork = true;break;
				case 4:write();saveWork = false;break;
				case 5:doCompositeFunction();saveWork = true;break;
				case 6:arithmeticFunction();break;
				case 7:changeFlags();break;
				case 8:loadProject();break;
				case 9:saveProject();break;
				case 10:paintLayer();saveWork = true;break;
				case 11:deleteSelection();saveWork = true;break;
				case 12:deleteLayer();saveWork = true;break;
				}
			}
			catch (Errors e) {
				std::cout << e;
			}
		} while (i);
	}

	void exitProgram() {
		if (saveWork) {
			std::string text;
			std::cout << "Do you want to save your work?(Yes/No)" << std::endl;
			std::cin >> text;
			if (text == "Yes") {
				saveProject();
			}
		}
		std::cout << "Program shut down" << std::endl;
	}

	void menuSecond(char *argv1,char* argv2) {
		addLayer(argv1);
		doCompositeFunction(argv2);
		write(argv1);
	}

	void arithmeticFunction() {
		int i;
		std::cout << "Pick one of arithmetic functions" << std::endl;
		std::cout << "1.Addition" << std::endl;
		std::cout << "2.Subtraction" << std::endl;
		std::cout << "3.Invert Subtraction" << std::endl;
		std::cout << "4.Multiplication" << std::endl;
		std::cout << "5.Division" << std::endl;
		std::cout << "6.Invert Division" << std::endl;
		std::cout << "7.Absolute value" << std::endl;
		std::cout << "8.Logarithm" << std::endl;
		std::cout << "9.Power" << std::endl;
		std::cout << "10.Min" << std::endl;
		std::cout << "11.Max" << std::endl;
		std::cout << "12.Inversion" << std::endl;
		std::cout << "13.Black and White" << std::endl;
		std::cout << "14.Shades of Gray" << std::endl;
		std::cout << "15.Madian" << std::endl;
		std::cin >> i;
		switch (i) {
		case 1:add();break;
		case 2:sub();break;
		case 3:invertSub();break;
		case 4:mul();break;
		case 5:div();break;
		case 6:invertDiv();break;
		case 7:abs();break;
		case 8:log();break;
		case 9:power();break;
		case 10:min();break;
		case 11:max();break;
		case 12:inversion();break;
		case 13:blackandwhite();break;
		case 14:shadesOfGray();break;
		case 15:median();break;
		}
		saveWork = true;
	}
	void changeFlags() {
		int i;
		std::cout << "Pick what you want to do" << std::endl;
		std::cout << "1.Set visible flag on layer" << std::endl;
		std::cout << "2.Reset visible flag on layer" << std::endl;
		std::cout << "3.Set active flag on layer" << std::endl;
		std::cout << "4.Reset active flag on layer" << std::endl;
		std::cout << "5.Set new transparency on a layer" << std::endl;
		std::cin >> i;
		switch (i) {
		case 1:setVisualFlag();break;
		case 2:resetVisualFlag();break;
		case 3:setActiveFlag();break;
		case 4:resetActiveFlag();break;
		case 5:setTransparency();break;
		}
		saveWork = true;
	}
	virtual ~Menu() {};
};

