#pragma once
#include <string>
#include <iostream>
class Stations
{
public:
	Stations(const std::string &);
	Stations();

	friend std::ostream& operator<<(std::ostream& os, const Stations& S);


	int getId();
	int getCode();
	std::string getName();
	bool getImportant();

	int code;
	std::string name;
	bool important;
};

