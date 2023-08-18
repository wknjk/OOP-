#pragma once
#include <string>
#include<map>
#include <set>
#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include "stations.h"
#include "lines.h"




struct TravelInfo {
	int id1_;
	int id2_;
	std::string lineName_;
	TravelInfo() {
		id1_ = 0;
		id2_ = 0;
		lineName_ = "";
	};
	TravelInfo(const int& id1, const int& id2, const std::string& linename) {
		id1_ = id1;
		id2_ = id2;

		lineName_ = linename;
	}
};



class Network
{
public:
Network();
void loadStations(const std::string& fileStations);
void loadLines(const std::string& fileLines);
void printGraph();
void stategyOne(int code1, int code2);
std::stack<TravelInfo*> strategyTwo(int code1, int code2);
const void printLines(const std::string& lineName);
const void printStation(const int& stationCode);
//void printStrOne();

//void findPath(PathStrategy&strat, int code1, int code2);

int numSt;
int numLn;
int numImpSt;

std::map <int, Stations*> mapIdSt; // mapira indekse grafa u pokazivac na stajaliste, da bih lako pristupala svim informacijama kroz graf
std::map <Stations*, int > mapStId;
std::map <int, Stations*> mapCodeSt; // mapira sifru stajalista u pokazivac na stajaliste da bih lako pristupila stajalistu kada ga ucitavam iz file liste

std::map <std::string, Lines*> mapLines; // mapira ime linije u pokazivac na objekat klase linije aka sva stajalista kroz koja prolazi data linija
std::map <int, Lines*> mapIdLines;

std::vector <Stations*> vectImportant;
std::vector<std::list<std::pair<int, Lines*> > > graph; // pravim graf koji je reprezentovan kao lista povezanosti samo su to u ovom slucaju vektori jer se graf ne menja



void makeGraph(const std::string&);

std::set<Lines*> makeSetOfLines(int id);
void printStrategyTwo(std::stack<TravelInfo*>stacky, int station1, int station2);
void strategyThree(int code1, int code2);
};
