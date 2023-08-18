#pragma once
#include <string>
#include<vector>
#include <string>
#include <list>
#include "stations.h"

class Lines {
public:
	Lines(const std::string& );
	Lines();
	std::string lineName;
	std::vector<Stations*> stations;

private:
	bool checkStation(int stCode);
};
