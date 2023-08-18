#pragma once
#include "Strategy.h"
#include "network.h"


class Terminal
{
public:
	Terminal(const Terminal&) = delete;
	static Terminal& Get() {
		static Terminal instance;
		return instance;
	}
	void openTerminal();
	void loadFile();
	void path();
	void printStation();
	void printLine() const;

	void StrategyTwoSame(StrategyPrint* strat, int code1, int code2);
private:
	Terminal() {
		graph = new Network;
	};
	 Network* graph;
	
	// void StrategyOne();

};
 // iz nekog razloga mora da se definise... 

