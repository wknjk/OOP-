#include "Strategy.h"
#include <fstream>
#include <sstream>
#include <set>
#include <queue>

#include "network.h"
#include "stations.h"
#include "lines.h"
#include "Exceptions.h"



#include "Strategy.h"

void StrategyPrintTwo::Print(std::stack<TravelInfo*> stacky, int code1, int code2, std::map <std::string, Lines*>& mapLines) {
	std::ofstream fout;
	std::string filename = "putanja_" + std::to_string(code1) + "_" + std::to_string(code2) + ".txt";
	fout.open(filename);
	bool first = 1;
	std::string lastName;
	std::string lineName;
	int id1;
	int id2;

	while (!stacky.empty()) {
		id1 = stacky.top()->id1_;
		id2 = stacky.top()->id2_;
		lineName = stacky.top()->lineName_;
		if (first) {
			fout << "->";
			fout << lineName << "\n";
			first = 0;
		}
		else {
			fout << "\n";
			fout << lastName << "->" << lineName << "\n";
		}
		int indeks1 = 0;
		int indeks2 = 0;
		for (int i = 0; i < mapLines[lineName]->stations.size(); i++)
		{
			
			if (mapLines[lineName]->stations[i]->code == code1) indeks1 = i;
			else if (mapLines[lineName]->stations[i]->code == code2) indeks2 = i;
		}

		if (indeks1 < indeks2) {
			for (int i = indeks1; i <= indeks2; i++) 
			{
				fout << mapLines[lineName]->stations[i]->code << " ";
			}
		}
		else
		{
			for (int i = indeks1; i >= indeks2; i--)
			{
				fout << mapLines[lineName]->stations[i]->code << " ";
			}
		}
		lastName = lineName;
		stacky.pop();
	}
	fout.close();
}

void StrategyPrintThree::Print(std::stack<TravelInfo*> stacky, int currCode1, int currCode2, std::map <std::string, Lines*>& mapLines) {
	
	std::ofstream fout;
	
	
	std::string filename = "putanja_" + std::to_string(code1) + "_" + std::to_string(code2) + ".txt";
	fout.open(filename, ios::app);
	
	
	bool first = 1;
	std::string lastName;
	std::string lineName;
	int id1;
	int id2;
	while (!stacky.empty()) {
		id1 = stacky.top()->id1_;
		id2 = stacky.top()->id2_;
		lineName = stacky.top()->lineName_;
		if (first) {
			fout << "->";
			fout << lineName << "\n";
			first = 0;
		}
		else {
			fout << "\n";
			fout << lastName << "->" << lineName << "\n";
		}
		int indeks1 = 0;
		int indeks2 = 0;
		for (int i = 0; i < mapLines[lineName]->stations.size(); i++)
		{

			if (mapLines[lineName]->stations[i]->code == currCode1) indeks1 = i;
			else if (mapLines[lineName]->stations[i]->code == currCode2) indeks2 = i;
		}

		if (indeks1 < indeks2) {
			for (int i = indeks1; i <= indeks2; i++)
			{
				fout << mapLines[lineName]->stations[i]->code << " ";
			}
		}
		else
		{
			for (int i = indeks1; i >= indeks2; i--)
			{
				fout << mapLines[lineName]->stations[i]->code << " ";
			}
		}
		lastName = lineName;
		stacky.pop();
	}
	fout.close();

}