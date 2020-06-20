#include<iostream>
#include"Menu.h"

int main(int argc,char* argv[]) {
	Menu start;
	if (argc == 1)
		start.menu();
	else if (argc == 3) {
		start.menuSecond(argv[1],argv[2]);
	}
	system("pause");
}
	
	
    