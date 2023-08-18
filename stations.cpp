#include "stations.h"
#include "Exceptions.h"
#include <istream>
#include <sstream>
std::ostream& operator<<(std::ostream& os, const Stations& s)
{
	os << s.code << " " << s.name;

	if (s.important) os << " [!]";
	return os;

}

Stations::Stations(const std::string& pars)
{
	std::stringstream s(pars);
	std::string a;
	getline(s, a, ' ');
	if (a.size() > 0) {
		code = stoi(a);
	}
	else throw new WrongData;

	a = "";
	getline(s, a, '[');
	if (a.size() > 0)
		name = a;
	else throw new WrongData;
	a = "";
	getline(s, a);
	if (a.size() != 0) important = 1;

		

}

Stations::Stations()
{
	
	code = 0;
	name = "";
	important = 0;
}



int Stations::getCode()
{
	return code;
}

std::string Stations::getName()
{
	return name;
}

bool Stations::getImportant()
{
	return important;
}
