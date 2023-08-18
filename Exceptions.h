#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
#include <exception>
using namespace std;

class FileDoesntExists : public exception {
public:
	FileDoesntExists() : exception("File doesnt exists.\n") {};
};

class WrongData : public exception {
public:
	WrongData() : exception("Data in file is in wrong format ") {};

};

class StationDoesntExsist : public exception {
public:
	StationDoesntExsist() : exception("This station doesn't exist") {};
};
#endif