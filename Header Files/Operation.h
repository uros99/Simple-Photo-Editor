#pragma once
#include"Image.h"
#include<algorithm>
class Operation
{
public:
	Operation() { Pixel::resetComposite(); };
	virtual void fun() = 0;
	virtual std::string nameofOperation() = 0;
	virtual std::string getArg() = 0;
	~Operation() {};
};

class Add :
	public Operation
{
	Image *image;
	int k;
public:
	Add(Image *i, int x) :image(i), k(x) {};
	void fun()override;
	std::string nameofOperation()override {
		return "Add";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~Add() {};
};

class Abs :
	public Operation
{
	Image *image;
public:
	Abs(Image *i) :image(i) {}
	void fun() override;
	std::string nameofOperation() override{
		return "Abs";
	}
	std::string getArg()override {
		return "No parametar";
	}
	virtual ~Abs() {};
};

class BlackandWhite :
	public Operation
{
	Image *image;
public:
	BlackandWhite(Image *i) :image(i) {};
	void fun()override;
	std::string nameofOperation()override {
		return "BlackandWhite";
	}
	std::string getArg()override {
		return "No parametar";
	}
	virtual ~BlackandWhite() {};
};

class Div :
	public Operation
{
	Image *image;
	int k;
public:
	Div(Image *i, int x) :image(i), k(x) {}
	void fun()override;
	std::string nameofOperation()override {
		return "Div";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~Div() {};
};

class Inversion :
	public Operation
{
	Image *image;
public:
	Inversion(Image *i) :image(i) {}
	void fun()override;
	std::string nameofOperation()override {
		return "Inversion";
	}
	std::string getArg()override {
		return "No parametar";
	}
	virtual ~Inversion() {};
};

class InvertDiv :
	public Operation
{
	Image *image;
	int k;
public:
	InvertDiv(Image *i, int x) :image(i), k(x) {}
	void fun()override;
	std::string nameofOperation() override {
		return "InvertDiv";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~InvertDiv() {};
};

class InvertSub :
	public Operation
{
	Image *image;
	int k;
public:
	InvertSub(Image *i, int x) :image(i), k(x) {}
	void fun() override;
	std::string nameofOperation() override {
		return "InvertSub";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~InvertSub() {};
};

class Log :
	public Operation
{
	Image *image;
public:
	Log(Image *i) :image(i) {}
	void fun()override;
	std::string nameofOperation() override {
		return "Log";
	}
	std::string getArg()override {
		return "No parametar";
	}
	virtual ~Log() {};
};

class Max :
	public Operation
{
	Image *image;
	int k;
public:
	Max(Image *i, int x) :image(i), k(x) {}
	void fun()override;
	std::string nameofOperation() override {
		return "Max";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~Max() {};
};

class Min :
	public Operation
{
	Image *image;
	int k;
public:
	Min(Image *i, int x) :image(i), k(x) {}
	void fun()override;
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	std::string nameofOperation() override {
		return "Min";
	}
	virtual ~Min() {};
};

class Mul :
	public Operation
{
	Image *image;
	int k;
public:
	Mul(Image *i, int x) :image(i), k(x) {}
	void fun() override;
	std::string nameofOperation() override {
		return "Mul";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~Mul() {};
};

class Power :
	public Operation
{
	Image *image;
	int k;
public:
	Power(Image *i, int x) :image(i), k(x) {}
	void fun()override;
	std::string nameofOperation() override {
		return "Power";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~Power() {};
};

class ShadesofGray :
	public Operation
{
	Image *image;
public:
	ShadesofGray(Image *i) :image(i) {}
	void fun()override;
	std::string nameofOperation() override {
		return "ShadesofGray";
	}
	std::string getArg()override {
		return "No parametar";
	}
	virtual ~ShadesofGray() {}
};

class Sub :
	public Operation
{
	Image *image;
	int k;
public:
	Sub(Image *i, int x) :image(i), k(x) {}
	void fun()override;
	std::string nameofOperation() override {
		return "Sub";
	}
	std::string getArg()override {
		std::string param = std::to_string(k);
		return param;
	}
	virtual ~Sub() {}
};

class Median :
	public Operation
{
	Image *image;
	std::vector<int32_t> red;
	std::vector<int32_t> green;
	std::vector<int32_t> blue;
public:
	Median(Image *i) :image(i) {}
	void fun()override;
	std::string nameofOperation() override {
		return "Median";
	}
	std::string getArg()override {
		return "No parametar";
	}
	void insertionSort(std::vector<int32_t> &arr,int n) {
		int i, key, j;
		for (i = 1; i < n; i++)
		{
			key = arr[i];
			j = i - 1;

			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
	}
	virtual ~Median() {}
};